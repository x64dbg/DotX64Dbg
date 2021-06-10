using System.IO;

namespace Dotx64Dbg
{
    public static class Manager
    {
        static Loader ScriptLoader = new();

        private static void RunTests()
        {
            var tests = new Tests();
            tests.Run();
        }

        private static void LoadSettings()
        {
            if (!Settings.Load(Path.Combine(Utils.GetRootPath(), "dotx64dbg.json")))
            {
                Logging.WriteLine("Failed to load settings, using default configuration");
            }
        }

        public static void Init()
        {
            LoadSettings();

            if (Settings.EnableTests)
            {
                RunTests();
            }

            Logging.WriteLine("Dotx64Dbg.Managed initialized");

            ScriptLoader.Startup();
        }

        public static void Setup()
        {
        }

        public static void Shutdown()
        {
            ScriptLoader.Shutdown();
        }
    }
}
