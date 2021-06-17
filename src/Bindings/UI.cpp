#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

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
            duint Start;

            /// <summary>
            /// End address of the selection.
            /// </summary>
            duint End;

            /// <summary>
            /// The size of the selection, End - Start.
            /// </summary>
            property duint Size
            {
                duint get()
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
            // NOTE: This is always off by 1, long term bug that wont be fixed for compatibility
            // reasons.
            res->End = data.end + 1;

            return res;
        }

        static bool SetSelection(WindowType wndType, Selection^ sel)
        {
            if (sel == nullptr)
                return false;

            SELECTIONDATA data{};
            data.start = sel->Start;
            data.end = sel->End;

            GUISELECTIONTYPE wndType2 = static_cast<GUISELECTIONTYPE>(wndType);
            return GuiSelectionSet(wndType2, &data);
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

    };
}
