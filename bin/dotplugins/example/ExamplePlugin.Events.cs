using Dotx64Dbg;
using System;

public partial class ExamplePlugin
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
    
    public void OnDebuggerResume()
    {
    }
    
    public void OnDebuggerPause()
    {
    }
    
    public void OnModuleLoadEvent(ModuleLoadEventInfo ev)
    {
        //Utils.PrintFields(ev);
    }
    
    public void OnModuleUnloadEvent(ModuleUnloadEventInfo ev)
    {
        //Utils.PrintFields(ev);
    } 
}
