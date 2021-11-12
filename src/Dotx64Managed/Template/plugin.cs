using System;
using Dotx64Dbg;

public partial class MyPlugin : IPlugin, IHotload
{
	/// <summary>
	/// Called as soon the plugin is first loaded, consequent hot-loads will not call this again.
	/// </summary>
    public MyPlugin()
    {
		Console.WriteLine("Hello World");
    }

	/// <summary>
	/// This is called after construction. This is also only called once.
	/// </summary>
    public void Startup()
    {
    }

	/// <summary>
	/// Classes that  have IHotload can implement this to get a notification for whenever
	/// the plugin was hot-loaded due to changes. This is not called for the startup.
	/// </summary>
    public void OnHotload()
    {
    }

	/// <summary>
	/// This is called right before the plugin is about to be shutdown.
	/// </summary>
    public void Shutdown()
    {
    }
}
