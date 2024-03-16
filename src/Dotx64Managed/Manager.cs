using System;
using System.IO;
using System.Linq;

namespace Dotx64Dbg
{
    public static partial class Manager
    {
        // Lock used to avoid a fight between main thread events and
        // plugin hot-load events.
        internal static Object LoaderLock = new Object();

        internal static Plugins PluginManager;
        internal static int PluginHandle;

        private static void RunTests()
        {
            var tests = new Tests();
            tests.Run();
        }

        public static bool Init(int pluginHandle)
        {
            try
            {
                lock (LoaderLock)
                {
                    PluginHandle = pluginHandle;

                    AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_NugetDepsAssemblyResolve;

                    Logging.Initialize();
                    Commands.Initialize();
                    Expressions.Initialize();
                    ScriptLoader.Initialize();
                    Menus.Initialize();

                    if (!Settings.Load(Path.Combine(Utils.GetRootPath(), "dotx64dbg.json")))
                    {
                        Console.WriteLine("[DotX64Dbg] Failed to load settings, using default configuration");
                    }

                    if (Settings.EnableTests)
                    {
                        RunTests();
                    }

                    Console.WriteLine("[DotX64Dbg] Manager initialized");
                }
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"Exception: {ex.Message}");
                return false;
            }

            return true;
        }

        private static System.Reflection.Assembly CurrentDomain_NugetDepsAssemblyResolve(object sender, ResolveEventArgs args)
        {
            var libs = new DirectoryInfo(Utils.DotX64DbgNugetDepsPath).GetFiles("*.dll");
            var assemblyName = new System.Reflection.AssemblyName(args.Name);

            var dll = libs.FirstOrDefault(file => Path.GetFileNameWithoutExtension(file.Name)
                .Equals(assemblyName.Name, StringComparison.InvariantCultureIgnoreCase));

            if (dll is not null)
            {
                return System.Reflection.Assembly.LoadFrom(dll.FullName);
            }
            return null;
        }

        public static void Setup()
        {
        }

        public static void Shutdown()
        {
            PluginManager.Shutdown();
            PluginManager = null;
        }

        public static void SetMenuData(MenuData data)
        {
            lock (LoaderLock)
            {
                Menus.InitializeMenus(data);

                PluginManager = new();
                PluginManager.Initialize();
            }
        }

        public static void OnMenuCallback(int id)
        {
            Menus.HandleCallback(id);
        }

        public static bool EvalScript(string code)
        {
            return ScriptLoader.ExecuteCode(code);
        }

        internal static Plugins GetPlugins()
        {
            return PluginManager;
        }
    }
}
