namespace Dotx64Dbg
{
    public static partial class Platform
    {

        public static string OpenFolderBrowse(string title)
        {
            return Native.Platform.BrowseForFolder(title);
        }

        public static string OpenFileBrowse(string title, string filter)
        {
            return Native.Platform.OpenFileBrowse(title, filter);
        }

        public static string SaveFileBrowse(string title, string filter)
        {
            return Native.Platform.SaveFileBrowse(title, filter);
        }

        public static void SetClipboardText(string text)
        {
            Native.Platform.SetClipboardText(text);
        }

        public static void MessageBoxInfo(string text, string title = null)
        {
            Native.Platform.MessageBoxInfo(text, title);
        }

        public static void MessageBoxError(string text, string title = null)
        {
            Native.Platform.MessageBoxError(text, title);
        }
    }
}
