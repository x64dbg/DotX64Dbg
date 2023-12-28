using System;

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

        public enum MsgBoxType
        {
            Ok = Native.UI.MsgBoxType.Ok,
            OkCancel = Native.UI.MsgBoxType.OkCancel,
            YesNo = Native.UI.MsgBoxType.YesNo,
            YesNoCancel = Native.UI.MsgBoxType.YesNoCancel,
        };

        public enum MsgBoxResult
        {
            Ok = Native.UI.MsgBoxResult.Ok,
            Cancel = Native.UI.MsgBoxResult.Cancel,
            Yes = Native.UI.MsgBoxResult.Yes,
            No = Native.UI.MsgBoxResult.No,
        };

        public enum MsgBoxIcon
        {
            None = Native.UI.MsgBoxIcon.None,
            Error = Native.UI.MsgBoxIcon.Error,
            Warning = Native.UI.MsgBoxIcon.Warning,
            Information = Native.UI.MsgBoxIcon.Information,
            Question = Native.UI.MsgBoxIcon.Question,
        };

        public class Selection
        {
            public Selection()
            {
            }

            public Selection(ulong start, ulong end)
            {
                Start = (nuint)start;
                End = (nuint)end;
            }

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
            public nuint Size
            {
                get => End - Start;
            }
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
            private bool wasEnabled;

            public UpdateSuppressor()
            {
                wasEnabled = UpdatesEnabled;
                if (wasEnabled)
                    UpdatesEnabled = false;
            }

            public void Dispose()
            {
                if (wasEnabled)
                    UpdatesEnabled = true;
            }
        }

        public static MsgBoxResult MsgBox(string title, string text, MsgBoxType type = MsgBoxType.Ok, MsgBoxIcon icon = MsgBoxIcon.None)
        {
            return (MsgBoxResult)Native.UI.MsgBox(title, text, (Native.UI.MsgBoxType)type, (Native.UI.MsgBoxIcon)icon);
        }

    }
}
