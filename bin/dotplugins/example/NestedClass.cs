using Dotx64Dbg;
using System;

// All classes that have the interface IHotload will fire the OnHotload event
// when the code is compiled and loaded.
public partial class NestedClass : IHotload
{
    public static int MyNestedStatic = 0;

    private int XY = 100;

    private System.Collections.Generic.List<int> IntegerList = new() { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    private System.Collections.Generic.HashSet<string> StringSet = new() { "Hello", "World", "foo", "foo", "Bar", "Foo" };

    private string NestedStringVar = "hello world";


    public void TestFunc()
    {
        Console.WriteLine("NestedClass::TestFunc()");
        Console.WriteLine("Test::IntegerList = {0}", string.Join(",", IntegerList));
        Console.WriteLine("Test::StringSet = {0}", string.Join(",", StringSet));
        Console.WriteLine("Test::NestedStringVar = {0}", NestedStringVar);

        NestedStringVar = "I changed my string";
        IntegerList.Add(500);
        StringSet.Add("Test");
    }

    public void OnHotload()
    {
        Console.WriteLine("Test::XY = {0}", XY);
        Console.WriteLine("Test::MyNestedStatic = {0}", ++MyNestedStatic);
        Console.WriteLine("Test::IntegerList = {0}", string.Join(",", IntegerList));
        Console.WriteLine("Test::StringSet = {0}", string.Join(",", StringSet));
        Console.WriteLine("Test::NestedStringVar = {0}", NestedStringVar);
    }
}
