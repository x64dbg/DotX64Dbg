using System;
using System.IO;

namespace Dotx64Dbg
{
    public static partial class Manager
    {
        internal static Plugins PluginManager;
        internal static int PluginHandle;

        private static void RunTests()
        {
            var tests = new Tests();
            tests.Run();
        }

        public static void Init(int pluginHandle)
        {
            PluginHandle = pluginHandle;

            Logging.Initialize();
            Commands.Initialize();

            if (!Settings.Load(Path.Combine(Utils.GetRootPath(), "dotx64dbg.json")))
            {
                Console.WriteLine("Failed to load settings, using default configuration");
            }

            if (Settings.EnableTests)
            {
                RunTests();
            }

            Console.WriteLine("Dotx64Dbg.Managed initialized");

            PluginManager = new();
            PluginManager.Startup();
        }

        public static void Setup()
        {
        }

        public static void Shutdown()
        {
            PluginManager.Shutdown();
            PluginManager = null;
        }
    }
}
