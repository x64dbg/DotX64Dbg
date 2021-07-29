using System;
using Dotx64Dbg;

// Plugin Entry. 
// The hot-load system will try to preserve all members of all classes
// during the reload. All the assigned values will persist accross 
// compilations.
public partial class ExamplePlugin : IPlugin, IHotload
{
    private NestedClass Nested = new();
    private AssemblerTest Assembler = new AssemblerTest();

    public ExamplePlugin()
    {
        // Writes to x64Dbg log.
        Console.WriteLine("ExamplePlugin Constructor");
    }

    // Called as soon the plugin is fully initialized, this is called after
    // the constructor and only once the for the initial plugin load.
    public void Startup()
    {
        Console.WriteLine("ExamplePlugin Startup");
    }

    // Called whenever code changes are hot-loaded.
    public void OnHotload()
    {
        Console.WriteLine("Code got reloaded");
    }

    // Called before the plugin is about to be unloaded.
    public void Shutdown()
    {
        Console.WriteLine("ExamplePlugin Shutdown");
    }
}
