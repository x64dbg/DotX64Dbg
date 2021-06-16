namespace Dotx64Dbg.UI
{
    public static class Stack
    {
        internal static WindowType WndType = WindowType.Stack;

        /// <summary>
        /// Returns the selected range from the stack.
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
