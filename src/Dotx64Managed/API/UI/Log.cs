namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class Log
        {
            internal static Menu.Id MenuId = 0;

            /// <summary>
            /// Clears log window.
            /// </summary>
            public static void Clear()
            {
                Native.UI.ClearLog();
            }

            internal static Menu.Id GetMenu()
            {
                return MenuId;
            }

            internal static void SetMenuId(Menu.Id id)
            {
                MenuId = id;
            }
        }
    }
}
