namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class Log
        {
            /// <summary>
            /// Clears log window.
            /// </summary>
            public static void Clear()
            {
                NativeUI.UI.ClearLog();
            }
        }
    }
}
