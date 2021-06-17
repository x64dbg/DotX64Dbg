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
                return Selection.FromNative(NativeUI.UI.GetSelection((NativeUI.WindowType)WndType));
            }

            public static bool SetSelection(Selection selection)
            {
                return NativeUI.UI.SetSelection((NativeUI.WindowType)WndType, selection.ToNative());
            }

            public static void Update()
            {
                NativeUI.UI.Update((NativeUI.WindowType)WndType);
            }
        }
    }
}
