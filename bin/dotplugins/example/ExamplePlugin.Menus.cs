using Dotx64Dbg;
using System;

using static Dotx64Dbg.UI;

public partial class MyPlugin
{
    [Menu(Disassembly.Menu, "Print selection")]
    public void TestMenu01()
    {
        var selection = Disassembly.GetSelection();
        Console.WriteLine($"{this} Disassembly selection, Start {selection.Start:X}, End {selection.End:X}, Len: {selection.Size:X}");
    }

    [Menu(Disassembly.Menu, "Another Menu/Sub Entry")]
    public void TestMenu02()
    {
        Console.WriteLine($"{this} Nesting Menus is easy.");
    }

    [Menu(MemoryMap.Menu, "Do something with selected memory")]
    public void TestMenu03()
    {
        Console.WriteLine("Do something with selected memory");

        var selection = MemoryMap.GetSelection();
        Console.WriteLine($"{this} Memory Map selection, Start {selection.Start:X}, End {selection.End:X}, Len: {selection.Size:X}");
    }

    [Menu(Stack.Menu, "Do something with selected stack")]
    public void TestMenu04()
    {
        Console.WriteLine("Do something with selected stack");

        var selection = Stack.GetSelection();
        Console.WriteLine($"{this} Stack selection, Start {selection.Start:X}, End {selection.End:X}, Len: {selection.Size:X}");
    }
    
    [Menu(Dump.Menu, "Do something with selected dump")]
    public void TestMenu05()
    {
        Console.WriteLine("Do something with selected dump");

        var selection = Dump.GetSelection();
        Console.WriteLine($"{this} Dump selection, Start {selection.Start:X}, End {selection.End:X}, Len: {selection.Size:X}");
    }
    
}

