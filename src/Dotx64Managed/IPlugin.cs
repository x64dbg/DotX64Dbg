namespace Dotx64Dbg
{
    public interface IHotload
    {
        // Called as soon the plugin is compiled and reloaded.
        public void OnHotload();
    }

    public interface IPlugin
    {
        // Called when the plugin is loaded.
        public void Startup()
        {
        }

        // Called when the plugin is unloaded.
        public void Shutdown()
        {
        }

        // Debug Events
        public void OnExceptionEvent(ExceptionEventInfo ev)
        {
        }
        public void OnThreadCreateEvent(ThreadCreateEventInfo ev)
        {
        }
        public void OnThreadExitEvent(ThreadExitEventInfo ev)
        {
        }
        public void OnProcessCreateEvent(ProcessCreateEventInfo ev)
        {
        }
        public void OnProcessExitEvent(ProcessExitEventInfo ev)
        {
        }
        public void OnBreakpointEvent(BreakpointEventInfo ev)
        {
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
        }
        public void OnModuleUnloadEvent(ModuleUnloadEventInfo ev)
        {
        }
    }
}
