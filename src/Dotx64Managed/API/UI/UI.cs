using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Dotx64Dbg;

namespace Dotx64Dbg
{
    public static partial class UI
    {
        public enum WindowType
        {
            Disassembly = Native.UI.WindowType.Disassembly,
            Dump = Native.UI.WindowType.Dump,
            Stack = Native.UI.WindowType.Stack,
            Graph = Native.UI.WindowType.Graph,
            MemoryMap = Native.UI.WindowType.MemoryMap,
            SymbolModule = Native.UI.WindowType.SymbolModule,
        };

        public class Selection
        {
            public Selection() { }

            public Selection(ulong start, ulong end) { Start = start; End = end; }

            internal Selection(Native.UI.Selection sel)
            {
                Start = sel.Start;
                End = sel.End;
            }

            internal static Selection FromNative(Native.UI.Selection sel)
            {
                if (sel == null)
                    return null;
                return new Selection() { Start = sel.Start, End = sel.End };
            }

            internal Native.UI.Selection ToNative()
            {
                return new Native.UI.Selection()
                {
                    Start = this.Start,
                    End = this.End,
                };
            }

            //
            // Summary:
            //     Start address of the selection.
            public ulong Start;
            //
            // Summary:
            //     End address of the selection.
            public ulong End;

            //
            // Summary:
            //     The size of the selection, End - Start.
            public ulong Size { get; }
        }

        /// <summary>
        /// Allows to suppress UI updates, this can speed up certain actions.
        /// </summary>
        public static bool UpdatesEnabled
        {
            get
            {
                return Native.UI.UpdatesEnabled();
            }

            set
            {
                Native.UI.EnableUpdates(value);
            }
        }

        public static void Update()
        {
            Native.UI.Update();
        }
    }
}
