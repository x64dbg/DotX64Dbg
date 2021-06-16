namespace Dotx64Dbg.UI
{
    public static class Main
    {
        /// <summary>
        /// Allows to suppress UI updates, this can speed up certain actions.
        /// </summary>
        static bool UpdatesEnabled
        {
            get
            {
                return Native.UI.UpdatesEnabled();
            }

            set
            {
                Native.UI.EnableUpdates(value);
            }
        }
    }
}
