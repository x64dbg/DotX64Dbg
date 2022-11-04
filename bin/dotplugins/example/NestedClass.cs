using Dotx64Dbg;
using System;

public class DataClass
{
    public int Value = 0;

    public DataClass(int val)
    {
        Value = val;
    }

    public override string ToString()
    {
        return $"{Value}";
    }
}

// All classes that have the interface IHotload will fire the OnHotload event
// when the code is compiled and loaded.
public partial class NestedClass : IHotload
{
    public static int MyNestedStatic = 0;

    private int XY = 100;

    private System.Collections.Generic.List<int> IntegerList = new() { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    private System.Collections.Generic.HashSet<string> StringSet = new() { "Hello", "World", "foo", "foo", "Bar", "Foo" };

    DataClass[] ClassArray = new DataClass[10] {
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1),
        new DataClass(1)
    };

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

        int i = 0;
        foreach (var data in ClassArray)
        {
            data.Value = ++i;
        }
    }

    public void OnHotload()
    {
        Console.WriteLine("Test::XY = {0}", XY);
        Console.WriteLine("Test::MyNestedStatic = {0}", ++MyNestedStatic);
        Console.WriteLine("Test::IntegerList = {0}", string.Join(",", IntegerList));
        Console.WriteLine("Test::StringSet = {0}", string.Join(",", StringSet));
        Console.WriteLine("Test::NestedStringVar = {0}", NestedStringVar);
        int i = 0;
        foreach (var data in ClassArray)
        {
            Console.WriteLine("Test::ClassArray[{0}] = {1}", i++, data);
        }
    }
}
