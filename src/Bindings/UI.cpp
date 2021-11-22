#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_gui.h"

#include "Marshal.hpp"

#pragma comment(lib, "Gdi32.lib")

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native
{
    public ref class UI
    {
    public:
        /// <summary>
        /// Selection holds the start and end address of the selected elements in a window.
        /// </summary>
        ref class Selection
        {
        public:
            /// <summary>
            /// Start address of the selection.
            /// </summary>
            uint64_t Start;

            /// <summary>
            /// End address of the selection.
            /// </summary>
            uint64_t End;

            /// <summary>
            /// The size of the selection, End - Start.
            /// </summary>
            property uint64_t Size
            {
                uint64_t get()
                {
                    return End - Start;
                }
            }
        };

        enum class WindowType
        {
            Disassembly = GUI_DISASSEMBLY,
            Dump = GUI_DUMP,
            Stack = GUI_STACK,
            Graph = GUI_GRAPH,
            MemoryMap = GUI_MEMMAP,
            SymbolModule = GUI_SYMMOD,
            Types, // No native id for this one.
        };

    public:
        static Selection^ GetSelection(WindowType wndType)
        {
            GUISELECTIONTYPE wndType2 = static_cast<GUISELECTIONTYPE>(wndType);

            SELECTIONDATA data{};
            if (!GuiSelectionGet(wndType2, &data))
                return nullptr;

            Selection^ res = gcnew Selection();
            res->Start = data.start;
            res->End = data.end;

            return res;
        }

        static bool SetSelection(WindowType wndType, Selection^ sel)
        {
            if (sel == nullptr)
                return false;

            SELECTIONDATA data{};
            data.start = (duint)sel->Start;
            data.end = (duint)sel->End;

            GUISELECTIONTYPE wndType2 = static_cast<GUISELECTIONTYPE>(wndType);
            return GuiSelectionSet(wndType2, &data);
        }

        static void SetStatusBarText(String^ str)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(str);

            GuiAddStatusBarMessage(cstr);
        }

        static void Update()
        {
            GuiUpdateAllViews();
        }

        static void Update(WindowType wndType)
        {
            switch (wndType)
            {
            case WindowType::Disassembly:
                GuiUpdateDisassemblyView();
                break;
            case WindowType::Dump:
                GuiUpdateDumpView();
                break;
            case WindowType::Stack:
                GuiUpdateCallStack();
                break;
            case WindowType::Graph:
                GuiUpdateGraphView();
                break;
            case WindowType::MemoryMap:
                GuiUpdateMemoryView();
                break;
            case WindowType::SymbolModule:
                GuiUpdateAllViews();
                break;
            case WindowType::Types:
                GuiUpdateTypeWidget();
                break;
            default:
                break;
            }
        }

        static bool UpdatesEnabled()
        {
            return GuiIsUpdateDisabled();
        }

        static void EnableUpdates(bool enabled)
        {
            if (enabled)
                GuiUpdateEnable(true);
            else
                GuiUpdateDisable();
        }

        static void ClearLog()
        {
            GuiLogClear();
        }

        ref class Menu
        {
        public:
            static int Add(int parent, System::String^ name)
            {
                msclr::interop::marshal_context oMarshalContext;

                const char* cstr = oMarshalContext.marshal_as<const char*>(name);

                return _plugin_menuadd(parent, cstr);
            }

            static bool SetIcon(int hMenu, System::Drawing::Image^ image)
            {
                auto data = GetIconData(image);

                ICONDATA icon{ 0 };
                icon.data = &data[0];
                if (icon.size = data.size(); !icon.size)
                    return false;

                _plugin_menuseticon(hMenu, &icon);

                return true;
            }

            static bool SetEntryIcon(int hPlugin, int hEntry, System::Drawing::Image^ image)
            {
                auto data = GetIconData(image);

                ICONDATA icon{ 0 };
                icon.data = &data[0];
                if (icon.size = data.size(); !icon.size)
                    return false;

                _plugin_menuentryseticon(hPlugin, hEntry, &icon);

                return true;
            }

            static bool AddEntry(int parent, int id, System::String^ name)
            {
                msclr::interop::marshal_context oMarshalContext;

                const char* cstr = oMarshalContext.marshal_as<const char*>(name);

                return _plugin_menuaddentry(parent, id, cstr);
            }

            static bool AddSeperator(int parent)
            {
                return _plugin_menuaddseparator(parent);
            }

            static bool RemoveEntry(int pluginHandle, int id)
            {
                return _plugin_menuentryremove(pluginHandle, id);
            }

            static bool Remove(int id)
            {
                return _plugin_menuremove(id);
            }

        private:

            static std::vector<uint8_t> GetIconData(_In_ System::Drawing::Image^ image)
            {
                System::Drawing::Bitmap bitmap(image);
                bitmap.MakeTransparent();
                HBITMAP hBitmap = (HBITMAP)bitmap.GetHbitmap().ToPointer(); // Used only for bitmap info

                BITMAP bmp{ 0 };
                if (!GetObject(hBitmap, sizeof(BITMAP), &bmp))
                    return {};

                LONG pixelArraySize = bmp.bmWidthBytes * bmp.bmHeight;
                const size_t bitmapSize = pixelArraySize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER);
                auto bitmapData = std::vector<uint8_t>(bitmapSize);

                BITMAPFILEHEADER bmfh{ 0 };
                bmfh.bfType = 0x4D42;
                bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER);
                bmfh.bfSize = (DWORD)bitmapSize;

                BITMAPV5HEADER bmh{ 0 };
                bmh.bV5Size = sizeof(BITMAPV5HEADER);
                bmh.bV5Width = bmp.bmWidth;
                bmh.bV5Height = -bmp.bmHeight;
                bmh.bV5Planes = 1;
                bmh.bV5BitCount = bmp.bmBitsPixel;
                bmh.bV5Compression = BI_RGB | BI_BITFIELDS,
                bmh.bV5RedMask = 0xFF << 16;
                bmh.bV5GreenMask = 0xFF << 8;
                bmh.bV5BlueMask = 0xFF;
                bmh.bV5AlphaMask = 0xFF << 24;
                bmh.bV5SizeImage = pixelArraySize;
                bmh.bV5XPelsPerMeter = 0;
                bmh.bV5YPelsPerMeter = 0;
                bmh.bV5CSType = LCS_sRGB;
                bmh.bV5Intent = LCS_GM_GRAPHICS;

                /*
                    Don't get the DI bitmap bits from a handle retrieved by 'Bitmap::GetHbitmap()' because the alpha channel gets destroy.
                    For this, use the Gdiplus functions like 'LockBits' for retrieving the bitmap data.
                    Note: Functions and classes fom 'System::Drawing' are pretty much wrappers for Gdiplus
                */
                System::Drawing::Rectangle regionRect(0, 0, bmp.bmWidth, bmp.bmHeight);
                auto bmpData = bitmap.LockBits(regionRect, System::Drawing::Imaging::ImageLockMode::ReadOnly, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
                void* bmpBits = bmpData->Scan0.ToPointer();
                // pixel array
                memcpy_s(
                    &bitmapData[bmfh.bfOffBits],
                    bitmapSize - bmfh.bfOffBits,
                    bmpBits,
                    pixelArraySize
                );
                bitmap.UnlockBits(bmpData);
                // bmp file header
                memcpy_s(&bitmapData[0], bitmapSize, &bmfh, sizeof(BITMAPFILEHEADER));
                // bmp v5 header
                memcpy_s(
                    &bitmapData[sizeof(BITMAPFILEHEADER)],
                    bitmapSize - sizeof(BITMAPFILEHEADER),
                    &bmh,
                    sizeof(BITMAPV5HEADER)
                );

                return bitmapData;
            }
        };

        static System::String^ InputPrompt(System::String^ title)
        {
            auto titleStr = interop::toUTF8(title);

            auto buf = std::make_unique<char[]>(GUI_MAX_LINE_SIZE);
            if (!Script::Gui::InputLine(titleStr.c_str(), buf.get()))
            {
                return nullptr;
            }

            return interop::stringFromUTF8(buf.get());
        }
    };
}
