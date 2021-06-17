namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class MemoryMap
        {
            internal static WindowType WndType = WindowType.MemoryMap;

            /// <summary>
            /// Returns the selected range from the memory map.
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
