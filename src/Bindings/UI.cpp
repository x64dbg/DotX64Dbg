#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::UI
{
    /// <summary>
    /// Selection holds the start and end address of the selected elements in a window.
    /// </summary>
    public ref class Selection
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

    public enum class WindowType
    {
        Disassembly = GUI_DISASSEMBLY,
        Dump = GUI_DUMP,
        Stack = GUI_STACK,
        Graph = GUI_GRAPH,
        MemoryMap = GUI_MEMMAP,
        SymbolModule = GUI_SYMMOD,
    };
}

namespace Dotx64Dbg::Native
{
    public ref class UI
    {
    public:
        static Dotx64Dbg::UI::Selection^ GetSelection(Dotx64Dbg::UI::WindowType wndType)
        {
            using namespace Dotx64Dbg::UI;

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

        static bool SetSelection(Dotx64Dbg::UI::WindowType wndType, Dotx64Dbg::UI::Selection^ sel)
        {
            if (sel == nullptr)
                return false;

            SELECTIONDATA data{};
            data.start = sel->Start;
            data.end = sel->End;

            GUISELECTIONTYPE wndType2 = static_cast<GUISELECTIONTYPE>(wndType);
            return GuiSelectionSet(wndType2, &data);
        }

        static void Update(Dotx64Dbg::UI::WindowType wndType)
        {
            switch (wndType)
            {
            case Dotx64Dbg::UI::WindowType::Disassembly:
                GuiUpdateDisassemblyView();
                break;
            case Dotx64Dbg::UI::WindowType::Dump:
                GuiUpdateDumpView();
                break;
            case Dotx64Dbg::UI::WindowType::Stack:
                GuiUpdateCallStack();
                break;
            case Dotx64Dbg::UI::WindowType::Graph:
                GuiUpdateGraphView();
                break;
            case Dotx64Dbg::UI::WindowType::MemoryMap:
                GuiUpdateMemoryView();
                break;
            case Dotx64Dbg::UI::WindowType::SymbolModule:
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
            if (enabled == true)
                GuiUpdateEnable(false);
            else
                GuiUpdateDisable();
        }

        static void ClearLog()
        {
            GuiLogClear();
        }

    };
}
