using Dotx64Dbg;

// All classes that have the interface IHotload will fire the OnHotload event
// when the code is compiled and loaded.
public class NestedClass : IHotload
{
    private int XY = 100;

    public void TestFunc()
    {
        Logging.WriteLine("Hello World");
    }

    public void OnHotload()
    {
        Logging.WriteLine("Test::XY = {0}", XY);
    }
}

// Plugin Entry. 
// The hot-load system will try to preserve all members of all classes
// during the reload. All the assigned values will persist accross 
// compilations.
public class MyPlugin : IPlugin, IHotload
{
    private int X = 0;
    private int Y = 2;
    private NestedClass Obj = new();
    private NestedClass Obj2;
    private int Z = 0;

    public MyPlugin()
    {
        Logging.WriteLine("Constructor, only called during first load");
        X = 100;
        Y = 300;
        Obj2 = Obj;
    }

    // Called as soon the plugin is fully initialized, this is called after
    // the constructor and only once the for the initial plugin load.
    public void Startup()
    {
        var test = new NestedClass();
        test.TestFunc();

        // Writes to x64Dbg log.
        Logging.WriteLine("Sheaaeeet, wuasaaa");
    }

    // Called whenever code changes are hot-loaded.
    public void OnHotload()
    {
#if _X64_
        Logging.WriteLine("Is X64");
#elif _X86_
        Logging.WriteLine("Is X86");
#endif
        var threads = Thread.GetThreads();

        Dotx64Dbg.Native.Logging.WriteLine("Hello");

        var mainThread = Thread.GetMain();
        Logging.WriteLine("Main Thread: {0}", mainThread);

        foreach (var thread in threads)
        {
            Logging.WriteLine("Threads: {0}", thread);
        }

        var activeThread = Thread.GetActive();
        Logging.WriteLine("Active Thread: {0}", activeThread.Id);

        Thread.SetActive(Thread.GetMain());

        var res = Memory.Read(0x00007FF67A766E88, 22);
        Logging.WriteLine("Data: {0}", res);

        // Value X and Y have will be 100, 300
        Logging.WriteLine("X = {0}, Y = {1}, Z = {2}", X, Y, Z);

        Logging.WriteLine("Hot Reload!, Herpa");

        if (Obj != Obj2)
        {
            Logging.WriteLine("FUCdddKUaaP!");
        }

        X = X + 11;
        Z = Z + 1;
    }

    // Called before the plugin is about to be unloaded.
    public void Shutdown()
    {
    }
}
