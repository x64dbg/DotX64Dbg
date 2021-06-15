using System;
using Dotx64Dbg;
using System.Collections.Generic;

// Plugin Entry. 
// The hot-load system will try to preserve all members of all classes
// during the reload. All the assigned values will persist accross 
// compilations.
public partial class MyPlugin : IPlugin, IHotload
{
    private NestedClass Obj = new();
    private List<int> TestList = new();

    private int X = 0;
    private int Y = 2;
    private NestedClass Obj2;
    private int Z = 0;
    public static int MyPublicStatic = 0;
    private static int MyPrivateStatic = 0;
    private static int NewStatic = 100;

    public static byte[] Shit = new byte[] { 0xEC };

    public MyPlugin()
    {
        Console.WriteLine("Constructor, only called during first load");
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
        Console.WriteLine("Sheaaeeet, wuasaaa");

        TestList.Add(12);
        TestList.Add(13);
    }

    // Called whenever code changes are hot-loaded.
    public void OnHotload()
    {
        foreach (var x in TestList)
        {
            Console.WriteLine($"List {x}");
        }

#if _X64_
        Console.WriteLine("Is X64");
#elif _X86_
        Console.WriteLine("Is X86");
#endif
        var threads = Thread.GetThreads();

        var mainThread = Thread.GetMain();
        Console.WriteLine("Main Thread: {0}", mainThread);


        Console.WriteLine("=== Threads ====");
        foreach (var thread in threads)
        {
            Console.WriteLine("-> Thread: {0}", thread);
        }


        var activeThread = Thread.GetActive();
        if (activeThread != null)
        {
            Console.WriteLine("Active Thread: {0}", activeThread.Id);

            Thread.SetActive(Thread.GetMain());

            mainThread.Rax = 0xFFFFFFFFFFFFFFFF;
            Console.WriteLine($"Rax = {mainThread.Rax:X}");

            Console.WriteLine($"Eax = {mainThread.Eax:X}");
            mainThread.Eax++;
            Console.WriteLine($"Eax = {mainThread.Eax:X}");

            Console.WriteLine($"Ax = {mainThread.Ax:X}");
            mainThread.Ax++;
            Console.WriteLine($"Ax = {mainThread.Ax:X}");

            Console.WriteLine($"Ah = {mainThread.Ah:X}");
            mainThread.Ah++;
            Console.WriteLine($"Ah = {mainThread.Ah:X}");

            Console.WriteLine($"Al = {mainThread.Al:X}");
            mainThread.Al++;
            Console.WriteLine($"Al = {mainThread.Al:X}");

            Console.WriteLine($"Rax = {mainThread.Rax:X}");
        }

        var res = Memory.Read(0x00007FF67A766E88, 22);
        Console.WriteLine("Data: {0}", res);

        // Value X and Y have will be 100, 300
        Console.WriteLine("X = {0}, Y = {1}, Z = {2}, MyPublicStatic = {3}, MyPrivateStatic = {4}", X, Y, Z, MyPublicStatic, MyPrivateStatic);
        Console.WriteLine("NewStatic = {0}", NewStatic);
        Console.WriteLine("Hot Reload!, Herpa");

        if (Obj != Obj2)
        {
            Console.WriteLine("FUCdddKUaaP!");
        }

        MyPublicStatic++;
        MyPrivateStatic++;
        X = X + 11;
        Z = Z + 1;
    }

    // Called before the plugin is about to be unloaded.
    public void Shutdown()
    {
    }
}
