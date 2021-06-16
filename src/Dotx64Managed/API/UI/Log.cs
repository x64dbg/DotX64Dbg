namespace Dotx64Dbg.UI
{
    public static class Log
    {
        /// <summary>
        /// Clears log window.
        /// </summary>
        public static void Clear()
        {
            Native.UI.ClearLog();
        }
    }
}
