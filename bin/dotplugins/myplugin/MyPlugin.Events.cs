using Dotx64Dbg;
using System;

public partial class MyPlugin
{
    public void OnExceptionEvent(ExceptionEventInfo ev)
    {
        Utils.PrintFields(ev);
    }

    public void OnThreadCreateEvent(ThreadCreateEventInfo ev)
    {
        Utils.PrintFields(ev);
    }

    public void OnThreadExitEvent(ThreadExitEventInfo ev)
    {
        Utils.PrintFields(ev);
    }

    public void OnProcessCreateEvent(ProcessCreateEventInfo ev)
    {
        var mainThread = Thread.GetMain();
        Console.WriteLine($"Main Thread: {mainThread}");
        Utils.PrintFields(ev);

        var oepData = Memory.Read(ev.StartAddress, 15);
        using (var decoder = Decoder.Create())
        {
            var oepInstr = decoder.Decode(oepData, ev.StartAddress);
            Console.WriteLine($"OEP {oepInstr}");
        }
    }

    public void OnProcessExitEvent(ProcessExitEventInfo ev)
    {
        Utils.PrintFields(ev);
    }

    // Bad
    public void OnBreakpointEvent(BreakpointEventInfo ev)
    {
        Utils.PrintFields(ev);
        if (ev.Type == Breakpoints.Type.System)
        {
            Console.WriteLine("Resuming process");

            Debugger.RunCommandAsync("run");
            Debugger.RunCommand("log test");
        }
    }

    // Ok
    public void OnBreakpointEvent2(BreakpointEventInfo ev)
    {
        Utils.PrintFields(ev);
        if (ev.Type == Breakpoints.Type.System)
        {
            Console.WriteLine("Resuming process");

            Debugger.RunCommandAsync("run");
            Debugger.RunCommandAsync("log test");
        }
    }
}
