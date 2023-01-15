using Dotx64Dbg;
using System;

public partial class ExamplePlugin
{
    [Command("EvaluateExpressions01", DebugOnly = true)]
    void EvalExpr01(string[] args)
    {
        // Evaluate the expression "cip"
        var result = Expressions.Evaluate("cip");
        System.Diagnostics.Debug.Assert(result == Dotx64Dbg.Thread.Active.Rip);
        Console.WriteLine($"cip = {result:X}");
    }

    [Command("EvaluateExpressions02", DebugOnly = true)]
    void EvalExpr02(string[] args)
    {
        // Get the address of NtQueryProcessInformation
        var result = Expressions.Evaluate("kernel32:LoadLibraryA");
        System.Diagnostics.Debug.Assert(result != 0);

        var mod = Module.FindByAddress(result);
        System.Diagnostics.Debug.Assert(mod != null);

        Console.WriteLine($"kernel32:LoadLibraryA = {result:X}");
    }

    [Command("EvaluateExpressions03", DebugOnly = true)]
    void EvalExpr03(string[] args)
    {
        // Evaluate the value of eax+5
        var result = Expressions.Evaluate("eax+5");
        System.Diagnostics.Debug.Assert(result == Thread.Active.Rax + 5);

        Console.WriteLine($"eax+5 = {result:X}");
    }

    [Command("EvaluateExpressions04", DebugOnly = true)]
    void EvalExpr04(string[] args)
    {
        // Use a sub expression like ReadPtr to read memory
        var result = Expressions.Evaluate("ReadPtr(csp)");
        System.Diagnostics.Debug.Assert(result == Memory.ReadPtr(Thread.Active.Rsp));

        Console.WriteLine($"ReadPtr(csp) = {result:X}");
    } 
}
