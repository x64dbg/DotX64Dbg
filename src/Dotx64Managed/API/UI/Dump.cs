namespace Dotx64Dbg.UI
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
            return Native.UI.GetSelection(WndType);
        }

        public static bool SetSelection(Selection selection)
        {
            return Native.UI.SetSelection(WndType, selection);
        }

        public static void Update()
        {
            Native.UI.Update(WndType);
        }
    }
}
