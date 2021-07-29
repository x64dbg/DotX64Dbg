using Dotx64Dbg;
using System;

public partial class MyPlugin
{
    // Works at any given time.
    [Command("TestExpression")]
    void MyCommand(string[] args)
    {
        string res;
        if (Expressions.TryFormat("rip = {rip}", out res))
        {
            Console.WriteLine($"Working: {res}");
        }
    }

	[Command("SetStatusText")]
	void SetStatusBarText(string[] args)
	{
		UI.StatusBar.Text = args[1] ?? "";
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

    [Command("Selection")]
    void PrintSelection(string[] args)
    {
        var sel = Dotx64Dbg.UI.Disassembly.GetSelection();
        if (sel == null)
        {
            Console.WriteLine("No selection");
            return;
        }
        Console.WriteLine($"Selection Start: {sel.Start:X}, End: {sel.End:X}");
    }
}
