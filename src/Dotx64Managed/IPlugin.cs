namespace Dotx64Dbg
{
    public interface IHotload
    {
        // Called as soon the plugin is compiled and reloaded.
        public void OnHotload();
    }

    public interface IPlugin
    {
        // Called when the plugin is loaded.
        public void Startup() { }

        // Called when the plugin is unloaded.
        public void Shutdown() { }
    }
}
