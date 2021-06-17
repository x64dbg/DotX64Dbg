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
            Disassembly = NativeUI.WindowType.Disassembly,
            Dump = NativeUI.WindowType.Dump,
            Stack = NativeUI.WindowType.Stack,
            Graph = NativeUI.WindowType.Graph,
            MemoryMap = NativeUI.WindowType.MemoryMap,
            SymbolModule = NativeUI.WindowType.SymbolModule,
        };

        public class Selection
        {
            public Selection() { }

            public Selection(ulong start, ulong end) { Start = start; End = end; }

            internal Selection(NativeUI.Selection sel)
            {
                Start = sel.Start;
                End = sel.End;
            }

            internal static Selection FromNative(NativeUI.Selection sel)
            {
                if (sel == null)
                    return null;
                return new Selection() { Start = sel.Start, End = sel.End };
            }

            internal NativeUI.Selection ToNative()
            {
                return new NativeUI.Selection()
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
                return NativeUI.UI.UpdatesEnabled();
            }

            set
            {
                NativeUI.UI.EnableUpdates(value);
            }
        }

        public static void Update()
        {
            NativeUI.UI.Update();
        }
    }
}
