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
            Types = Native.UI.WindowType.Types,
        };

        public class Selection
        {
            public Selection() { }

            public Selection(ulong start, ulong end) { Start = (nuint)start; End = (nuint)end; }

            internal Selection(Native.UI.Selection sel)
            {
                Start = (nuint)sel.Start;
                End = (nuint)sel.End;
            }

            internal static Selection FromNative(Native.UI.Selection sel)
            {
                if (sel == null)
                    return null;
                return new Selection() { Start = (nuint)sel.Start, End = (nuint)sel.End };
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
            public nuint Start;
            //
            // Summary:
            //     End address of the selection.
            public nuint End;

            //
            // Summary:
            //     The size of the selection, End - Start.
            public nuint Size { get => End - Start; }
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
        public class UpdateSuppressor : IDisposable
        {
            public UpdateSuppressor()
            {
                UpdatesEnabled = false;
            }

            public void Dispose()
            {
                UpdatesEnabled = true;
            }
        }
    }


}
