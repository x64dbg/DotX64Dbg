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
        public uint DebugInfoFileOffset;
        public uint DebugInfoSize;
        public ulong ThreadLocalBase;
        public ulong StartAddress;
        public ulong ImageName;
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

    /// <summary>Class for synchronization between x64Dbg and this plugin.</summary>
    public static partial class Manager
    {
        /// <summary>Internal function, do not call this.</summary>
        public static void OnExceptionEvent(ExceptionEventInfo ev)
        {
            try
            {
                PluginManager.GetPluginInstances().ForEach(delegate (IPlugin instance)
                {
                    instance.OnExceptionEvent(ev);
                });
            }
            catch (System.Exception ex)
            {
                Console.WriteLine($"Exception {ex.ToString()}");
            }
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnThreadCreateEvent(ThreadCreateEventInfo ev)
        {
            try
            {

                PluginManager.GetPluginInstances().ForEach(delegate (IPlugin instance)
                {
                    instance.OnThreadCreateEvent(ev);
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception {ex.ToString()}");
            }
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnProcessCreateEvent(ProcessCreateEventInfo ev)
        {
            try
            {
                PluginManager.GetPluginInstances().ForEach(delegate (IPlugin instance)
                {
                    instance.OnProcessCreateEvent(ev);
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception {ex.ToString()}");
            }
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnThreadExitEvent(ThreadExitEventInfo ev)
        {
            try
            {
                PluginManager.GetPluginInstances().ForEach(delegate (IPlugin instance)
                {
                    instance.OnThreadExitEvent(ev);
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception {ex.ToString()}");
            }
        }

        /// <summary>Internal function, do not call this.</summary>
        public static void OnProcessExitEvent(ProcessExitEventInfo ev)
        {
            try
            {
                PluginManager.GetPluginInstances().ForEach(delegate (IPlugin instance)
                {
                    instance.OnProcessExitEvent(ev);
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception {ex.ToString()}");
            }

        }
    }
}
