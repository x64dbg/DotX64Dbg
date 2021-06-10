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
    }
}
