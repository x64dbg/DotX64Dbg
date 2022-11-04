using Dotx64Dbg;
using System;

// All classes that have the interface IHotload will fire the OnHotload event
// when the code is compiled and loaded.
public partial class NestedClass : IHotload
{
    public static int MyNestedStatic = 0;

    private int XY = 100;

    private System.Collections.Generic.List<int> IntegerList = new() { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


    public void TestFunc()
    {
        Console.WriteLine("NestedClass::TestFunc()");
        Console.WriteLine("Test::IntegerList = {0}", IntegerList.ToString());
    }

    public void OnHotload()
    {
        Console.WriteLine("Test::XY = {0}", XY);
        Console.WriteLine("Test::MyNestedStatic = {0}", ++MyNestedStatic);
        Console.WriteLine("Test::IntegerList = {0}", IntegerList.ToString());
    }
}
