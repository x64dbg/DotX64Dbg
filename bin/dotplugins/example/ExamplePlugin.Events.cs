using Dotx64Dbg;
using System;

public partial class MyPlugin
{
    public void OnExceptionEvent(ExceptionEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }

    public void OnThreadCreateEvent(ThreadCreateEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }

    public void OnThreadExitEvent(ThreadExitEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }

    public void OnProcessCreateEvent(ProcessCreateEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }

    public void OnProcessExitEvent(ProcessExitEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }

    public void OnBreakpointEvent(BreakpointEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }
    
    public void OnSteppedEvent()
    {
    }
    
    public void OnDebuggerStart(string fileName)
    {
    }
    
    public void OnDebuggerStop()
    {
    }
}
