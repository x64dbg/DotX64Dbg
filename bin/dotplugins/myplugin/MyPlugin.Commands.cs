using Dotx64Dbg;
using System;

public partial class MyPlugin
{
    // Works at any given time.
    [Command("Test1")]
    void MyCommand(string[] args)
    {
        Console.WriteLine("Sup dawg");
    }

    // Works only when the debugger is active.
    [Command("Test2", DebugOnly = true)]
    void MyCommand2(string[] args)
    {
        Console.WriteLine("Oh no");
    }

    // Allows to return a status
    [Command("Test3")]
    bool MyCommand3(string[] args)
    {
        Console.WriteLine("Oh no");
        return false; // Indicates failure.
    }
}
