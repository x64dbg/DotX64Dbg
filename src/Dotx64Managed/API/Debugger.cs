using System.Threading.Tasks;

namespace Dotx64Dbg
{
    /// <summary>
    /// A class to control the debugger.
    /// </summary>
    public static class Debugger
    {
        /// <summary>
        /// If the debugger has a process and its valid this will be true.
        /// </summary>
        public static bool IsActive { get => Native.Debugger.IsActive(); }

        /// <summary>
        /// Waits for the debugger to be paused.
        /// The function will not return before the debugger paused.
        /// </summary>
        public static void WaitForPause()
        {
            Native.Debugger.Wait();
        }

        /// <summary>
        /// Signals the debugger to resume all execution in the debug process, returns immediately.
        /// </summary>
        public static void Run()
        {
            Native.Debugger.Run();
        }

        public static void RunAsync()
        {
            //Native.Debugger.Run();
            Debugger.RunCommandAsync("run");
        }

        /// <summary>
        /// Signals the debugger to pause, will block until the debugger stopped.
        /// </summary>
        public static void Pause()
        {
            Native.Debugger.Pause();
        }

        /// <summary>
        /// Signals the debugger to stop, will block until the debugger stopped.
        /// </summary>
        public static void Stop()
        {
            Native.Debugger.Stop();
        }

        /// <summary>
        /// Signals the debugger to step in, will block until the debugger stopped.
        /// </summary>
        public static void StepIn()
        {
            Native.Debugger.StepIn();
        }

        public static void StepInAsync()
        {
            Debugger.RunCommandAsync("sti");
        }

        /// <summary>
        /// Signals the debugger to step over, will block until the debugger stopped.
        /// </summary>
        public static void StepOver()
        {
            Native.Debugger.StepOver();
        }

        public static void StepOverAsync()
        {
            Debugger.RunCommandAsync("sto");
        }

        /// <summary>
        /// Signals the debugger to step out, will block until the debugger stopped.
        /// </summary>
        public static void StepOut()
        {
            Native.Debugger.StepOut();
        }

        public static void StepOutAsync()
        {
            Debugger.RunCommandAsync("rtr");
        }

        /// <summary>
        /// Performs synchronous execution of a debugger command. This function call only
        /// returns after the command has completed.
        ///
        /// Example: Debugger.RunCommand("loadlib advapi32.dll")
        /// </summary>
        /// <param name="cmd">The command to execute.</param>
        /// <returns>True if the command executed successfully, False if there was a problem.</returns>
        public static bool RunCommand(string cmd)
        {
            return Native.Debugger.RunCommand(cmd);
        }

        /// <summary>
        /// Asynchronously execute a debugger command by adding it to the command queue.
        /// Note: the command may not have completed before this call returns. Use this
        /// function if you don't care when the command gets executed.
        ///
        /// Example: Debugger.RunCommandAsync("ClearLog")
        /// </summary>
        /// <param name="cmd">The command to execute.</param>
        /// <returns>True if the command was successfully submitted to the command queue. False if the submission failed.</returns>
        public static bool RunCommandAsync(string cmd)
        {
            return Native.Debugger.RunCommandAsync(cmd);
        }
    }
}
