namespace Dotx64Dbg
{
    public static partial class UI
    {
        public static class StatusBar
        {
            public static string Text { set => Native.UI.SetStatusBarText($"{value}\n"); }
        }
    }
}
