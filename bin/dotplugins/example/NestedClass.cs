using Dotx64Dbg;
using System;

// All classes that have the interface IHotload will fire the OnHotload event
// when the code is compiled and loaded.
public partial class NestedClass : IHotload
{
    public static int MyNestedStatic = 0;

    private int XY = 100;

    public void TestFunc()
    {
        Console.WriteLine("Hello World");
    }

    public void OnHotload()
    {
        Console.WriteLine("Test::XY = {0}", XY);
        Console.WriteLine("Test::MyNestedStatic = {0}", ++MyNestedStatic);
    }
}
