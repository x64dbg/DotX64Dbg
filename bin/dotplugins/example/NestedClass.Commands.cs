using Dotx64Dbg;
using System;

public partial class NestedClass
{
	int x = 0;
	
    [Command("Test5")]
    void NestedCommand(string[] args)
    {
        Console.WriteLine($"Yup {x}");
    }
}
