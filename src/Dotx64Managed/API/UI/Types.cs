namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class Types
        {
            internal static WindowType WndType = WindowType.Types;
            internal static Menu.Id MenuId = 0;

            /// <summary>
            /// Updates the Types window
            /// </summary>
            public static void Update()
            {
                Native.UI.Update((Native.UI.WindowType)WndType);
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
