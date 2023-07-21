using System;

namespace Dotx64Dbg
{
    /// <summary>
    /// Passed in OnExceptionEvent
    /// </summary>
    public struct ExceptionEventInfo
    {

        public uint ProcessId;
        public uint ThreadId;
        public bool FirstChance;
        public uint ExceptionCode;
        public uint ExceptionFlags;
        public ulong ExceptionAddress;
    }

    /// <summary>
    /// Passed in OnThreadCreateEvent
    /// </summary>
    public struct ThreadCreateEventInfo
    {
        public uint ProcessId;
        public uint ThreadId;
        public ulong Handle;
        public ulong ThreadLocalBase;
        public ulong StartAddress;
    }

    /// <summary>
    /// Passed in OnThreadExitEvent
    /// </summary>
    public struct ThreadExitEventInfo
    {
        public uint ProcessId;
        public uint ThreadId;
        public uint ExitCode;
    }

    /// <summary>
    /// Passed in OnProcessCreateEvent
    /// </summary>
    public struct ProcessCreateEventInfo
    {
        public uint ProcessId;
        public uint ThreadId;
        public ulong FileHandle;
        public ulong ProcessHandle;
        public ulong ThreadHandle;
        public ulong ImageBase;
        public ulong ImageSize;
        public uint DebugInfoFileOffset;
        public uint DebugInfoSize;
        public ulong ThreadLocalBase;
        public ulong StartAddress;
        public string FilePath;
        public short Unicode;
    }

    /// <summary>Passed in OnProcessExitEvent</summary>
    public struct ProcessExitEventInfo
    {
        /// <summary>Native process id.</summary>
        public uint ProcessId;
        public uint ThreadId;
        public uint ExitCode;
    }

    /// <summary>Passed in OnBreakpointEvent</summary>
    public struct BreakpointEventInfo
    {
        public Breakpoints.Type Type;
        public ulong Address;
        public bool Enabled;
        public bool Singleshot;
        public bool Active;
        public string Name;
        public string Module;
        public ushort Slot;
        public int TypeEx;
        public int Size;
        public uint HitCount;
        public bool FastResume;
        public bool Silent;
        public string BreakCondition;
        public string LogText;
        public string LogCondition;
        public string CommandText;
        public string CommandCondition;
    }

    public struct ModuleLoadEventInfo
    {
        public ulong ImageBase;
        public ulong ImageSize;
        public string FilePath;
        public uint DebugInfoFileOffset;
        public uint DebugInfoSize;
    }

    public struct ModuleUnloadEventInfo
    {
        public ulong ImageBase;
        public ulong ImageSize;
        public string FilePath;
    }

    /// <summary>Class for synchronization between x64Dbg and this plugin.</summary>
    public static partial class Manager
    {
        internal static void PluginEventCall(Action<IPlugin> action)
        {
            PluginManager.GetPluginInstances().ForEach(delegate (IPlugin instance)
            {
                try
                {
                    action(instance);
                }
                catch (Exception ex)
                {
                    Utils.PrintException(ex);
                }
            });
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnExceptionEvent(ExceptionEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnExceptionEvent(ev);
            });
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnThreadCreateEvent(ThreadCreateEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnThreadCreateEvent(ev);
            });
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnProcessCreateEvent(ProcessCreateEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnProcessCreateEvent(ev);
            });
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnThreadExitEvent(ThreadExitEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnThreadExitEvent(ev);
            });
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnProcessExitEvent(ProcessExitEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnProcessExitEvent(ev);
            });
        }

        public static void OnBreakpointEvent(BreakpointEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnBreakpointEvent(ev);
            });
        }

        public static void OnSteppedEvent()
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnSteppedEvent();
            });
        }

        public static void OnDebuggerStart(string fileName)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnDebuggerStart(fileName);
            });
        }

        public static void OnDebuggerStop()
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnDebuggerStop();
            });
        }
        public static void OnDebuggerResume()
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnDebuggerResume();
            });
        }
        public static void OnDebuggerPause()
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnDebuggerPause();
            });
        }

        public static void OnModuleLoadEvent(ModuleLoadEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnModuleLoadEvent(ev);
            });
        }

        public static void OnModuleUnloadEvent(ModuleUnloadEventInfo ev)
        {
            PluginEventCall(delegate (IPlugin instance)
            {
                instance.OnModuleUnloadEvent(ev);
            });
        }
    }
}
