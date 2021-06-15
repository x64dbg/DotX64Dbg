using Dotx64Dbg;
using System;

public partial class MyPlugin
{
    // Works at any given time.
    [Command("TestExpression")]
    void MyCommand(string[] args)
    {
        string res;
        if (Expression.TryFormat("rip = {rip}", out res))
        {
            Console.WriteLine($"Working: {res}");
        }
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
