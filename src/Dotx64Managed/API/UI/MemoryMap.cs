namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class MemoryMap
        {
            internal static WindowType WndType = WindowType.MemoryMap;
            internal static Menu.Id MenuId = 0;

            public const Menu.Root Menu = UI.Menu.Root.MemoryMap;

            /// <summary>
            /// Returns the selected range from the memory map.
            /// </summary>
            /// <returns>Selection</returns>
            public static Selection GetSelection()
            {
                var sel = Selection.FromNative(Native.UI.GetSelection((Native.UI.WindowType)WndType));
                if (sel != null)
                {
                    // NOTE: Compensate that selection is off by 1, include entire length.
                    sel.End++;
                }
                return sel;
            }

            public static bool SetSelection(Selection selection)
            {
                return Native.UI.SetSelection((Native.UI.WindowType)WndType, selection.ToNative());
            }

            public static void Update()
            {
                Native.UI.Update((Native.UI.WindowType)WndType);
            }

            internal static Menu.Id GetMenuId()
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
