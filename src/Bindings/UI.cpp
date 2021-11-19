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
                HANDLE hProcessHeap = GetProcessHeap();

                // A pointer for the bitmap data
                LPVOID lpIconData;
                // The size of the bitmap
                size_t iconDataSize;

                iconDataSize = GetIconData(nullptr, 0, image); // Get the amount of memory required for the bitmap
                if (!iconDataSize)
                    return false;

                if (lpIconData = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, iconDataSize); !lpIconData)
                    return false;

                if (!GetIconData(lpIconData, iconDataSize, image))  // Get the actual bitmap data
                {
                    HeapFree(lpIconData, 0, lpIconData);
                    return false;
                }

                ICONDATA icon{ 0 };
                icon.size = iconDataSize;
                icon.data = lpIconData;

                _plugin_menuseticon(hMenu, &icon);

                HeapFree(
                    hProcessHeap,
                    0,
                    lpIconData
                );

                return true;
            }

            static bool SetEntryIcon(int hPlugin, int hEntry, System::Drawing::Image^ image)
            {
                HANDLE hProcessHeap = GetProcessHeap();

                // A pointer for the bitmap data
                LPVOID lpIconData;
                // The size of the bitmap
                size_t iconDataSize;

                iconDataSize = GetIconData(nullptr, 0, image); // Get the amount of memory required for the bitmap
                if (!iconDataSize)
                    return false;

                if (lpIconData = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, iconDataSize); !lpIconData)
                    return false;

                if (!GetIconData(lpIconData, iconDataSize, image))  // Get the actual bitmap data
                {
                    HeapFree(hProcessHeap, 0, lpIconData);
                    return false;
                }

                ICONDATA icon{ 0 };
                icon.size = iconDataSize;
                icon.data = lpIconData;

                _plugin_menuentryseticon(hPlugin, hEntry, &icon);

                HeapFree(
                    hProcessHeap,
                    0,
                    lpIconData
                );

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

            _Success_( return != 0)
            static size_t GetIconData(_Out_writes_bytes_to_opt_(bufferSize, return) LPVOID lpData, size_t bufferSize, _In_ System::Drawing::Image^ image)
            {
                auto bitmap = gcnew System::Drawing::Bitmap(image);
                HBITMAP hIcon = (HBITMAP)bitmap->GetHbitmap().ToPointer();

                BITMAP bmp{ 0 };
                if (!GetObject(hIcon, sizeof(BITMAP), &bmp) || !bmp.bmBits)
                    return 0;

                LONG pixelArraySize = bmp.bmWidthBytes * bmp.bmHeight;
                const size_t bitmapSize = pixelArraySize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER);

                if (lpData == nullptr)
                    return bitmapSize; // Return the required size for the bitmap
                if (bufferSize < bitmapSize)
                    return 0;   // Not enouth memory

                BITMAPFILEHEADER bmfh{ 0 };
                bmfh.bfType = 0x4D42;
                bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER);
                bmfh.bfSize = (DWORD)bitmapSize;

                BITMAPV5HEADER bmh{ 0 };
                bmh.bV5Size = sizeof(BITMAPV5HEADER);
                bmh.bV5Width = bmp.bmWidth;
                bmh.bV5Height = bmp.bmHeight;
                bmh.bV5Planes = bmp.bmPlanes;
                bmh.bV5BitCount = bmp.bmBitsPixel;
                bmh.bV5Compression = BI_RGB;
                bmh.bV5SizeImage = 0;
                bmh.bV5XPelsPerMeter = 0;
                bmh.bV5YPelsPerMeter = 0;
                bmh.bV5CSType = (DWORD)bmp.bmType;

                // pixel array
                memcpy_s(
                    (char*)lpData + bmfh.bfOffBits,
                    bufferSize - bmfh.bfOffBits,
                    bmp.bmBits,
                    pixelArraySize
                );
                // bmp file header
                memcpy_s(lpData, bufferSize, &bmfh, sizeof(BITMAPFILEHEADER));
                // bmp v5 header
                memcpy_s(
                    (char*)lpData + sizeof(BITMAPFILEHEADER),
                    bufferSize - sizeof(BITMAPFILEHEADER),
                    &bmh,
                    sizeof(BITMAPV5HEADER)
                );

                return bitmapSize;
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
