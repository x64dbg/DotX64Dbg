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
        ref struct Selection
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

            static bool SetIcon(int hMenu, array<System::Byte>^ image)
            {
                pin_ptr<uint8_t> data = &image[0];

                ICONDATA icon{ 0 };
                icon.data = data;
                if (icon.size = image->Length; !icon.size)
                    return false;

                _plugin_menuseticon(hMenu, &icon);

                return true;
            }

            static bool SetEntryIcon(int hPlugin, int hEntry, array<System::Byte>^ image)
            {
                pin_ptr<uint8_t> data = &image[0];

                ICONDATA icon{ 0 };
                icon.data = data;
                if (icon.size = image->Length; !icon.size)
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
