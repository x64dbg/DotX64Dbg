using System;
using System.IO;

namespace Dotx64Dbg
{
    public static partial class Manager
    {
        static Loader ScriptLoader = new();

        private static void RunTests()
        {
            var tests = new Tests();
            tests.Run();
        }

        public static void Init()
        {
            Logging.Initialize();

            if (!Settings.Load(Path.Combine(Utils.GetRootPath(), "dotx64dbg.json")))
            {
                Console.WriteLine("Failed to load settings, using default configuration");
            }

            if (Settings.EnableTests)
            {
                RunTests();
            }

            Console.WriteLine("Dotx64Dbg.Managed initialized");

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
