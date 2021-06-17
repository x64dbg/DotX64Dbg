namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class Dump
        {
            internal static WindowType WndType = WindowType.Dump;

            /// <summary>
            /// Returns the selected range from the dump.
            /// </summary>
            /// <returns>Selection</returns>
            public static Selection GetSelection()
            {
                return Selection.FromNative(Native.UI.GetSelection((Native.UI.WindowType)WndType));
            }

            public static bool SetSelection(Selection selection)
            {
                return Native.UI.SetSelection((Native.UI.WindowType)WndType, selection.ToNative());
            }

            public static void Update()
            {
                Native.UI.Update((Native.UI.WindowType)WndType);
            }
        }
    }
}
