namespace Dotx64Dbg
{
    public static class Debugger
    {
        public static bool IsActive { get => Native.Debugger.IsActive(); }

        public static void Wait()
        {
            Native.Debugger.Wait();
        }

        public static void Run()
        {
            Native.Debugger.Run();
        }

        public static void Pause()
        {
            Native.Debugger.Pause();
        }

        public static void Stop()
        {
            Native.Debugger.Stop();
        }

        public static void StepIn()
        {
            Native.Debugger.StepIn();
        }

        public static void StepOver()
        {
            Native.Debugger.StepOver();
        }

        public static void StepOut()
        {
            Native.Debugger.StepOut();
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
