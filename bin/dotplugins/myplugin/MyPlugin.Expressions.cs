using Dotx64Dbg;
using System;

public partial class MyPlugin
{
    [Expression("expr_no_input")]
    public nuint MyExpr1()
    {
        var th = Thread.Active;
        if (th != null)
        {
#if _X64_
            return (nuint)th.Rip;
#else
            return (nuint)th.Eip;
#endif
        }
        else
            Console.WriteLine("No active thread");

        return 0;

    }

    [Expression("expr_one_input")]
    public nuint MyExpr2(nuint a)
    {
        return a;

    }

    [Expression("expr_two_inputs")]
    public nuint MyExpr3(nuint a, nuint b)
    {
        return a + b;

    }
}