using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;

namespace Dotx64Dbg
{
    internal class PluginInfo
    {
        public string Name
        {
            get; set;
        }
        public string Description
        {
            get; set;
        }
        public string Version
        {
            get; set;
        }
        public string Author
        {
            get; set;
        }
        public string Website
        {
            get; set;
        }

        public string[] Dependencies
        {
            get; set;
        }
    }

    internal class Plugin
    {
        public PluginInfo Info;
        public string Path;
        public string ConfigPath;
        public string BuildOutputPath;
        public List<string> SourceFiles;
        public bool RequiresRebuild;
        internal AssemblyLoader Loader;
        internal string AssemblyPath;
        internal IPlugin Instance;
        internal Type InstanceType;

        public string ProjectFilePath
        {
            get
            {
                if (Info == null)
                    return null;
                return System.IO.Path.Combine(Path, Info.Name + ".csproj");
            }
        }

        public string SolutionFilePath
        {
            get
            {
                if (Info == null)
                    return null;
                return System.IO.Path.Combine(Path, Info.Name + ".sln");
            }
        }

        public string Name => Info?.Name;
    }

    internal partial class Plugins
    {
        string PluginsPath = "dotplugins";
        string AppDataPath;
        string PluginOutputPath;

        DependencyResolver dependencyResolver;

        List<Plugin> Registered = new();

        private void SetupDirectories()
        {
            PluginsPath = Settings.PluginsPath;
            if (!Directory.Exists(PluginsPath))
            {
                try
                {
                    Directory.CreateDirectory(PluginsPath);
                }
                catch (Exception)
                {
                    Console.WriteLine("[DotX64Dbg] Unable to create directory for plugins: {0}", PluginsPath);
                }
            }

            Console.WriteLine("[DotX64Dbg] Plugins Path: {0}", PluginsPath);

            AppDataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "DotX64Dbg");
#if _X64_
            PluginOutputPath = Path.Combine(AppDataPath, "x64");
#else
            PluginOutputPath = Path.Combine(AppDataPath, "x86");
#endif
            PluginOutputPath = Path.Combine(PluginOutputPath, "Plugins");
            if (!Directory.Exists(PluginOutputPath))
            {
                Directory.CreateDirectory(PluginOutputPath);
            }
        }

        public void Initialize()
        {
            SetupDirectories();
            InitializeWatcher();

            dependencyResolver = new();
            dependencyResolver.AddResolver(new NuGetDependencyResolver());
            dependencyResolver.AddResolver(new LocalAssembliesResolver());

            SkipRebuilding = true;
            RegisterPlugins();
            GenerateProjects();
            StartBuildWorker();

            SkipRebuilding = false;
            TriggerRebuild();
        }

        public void Shutdown()
        {
            StopBuildWorker();
            foreach (var plugin in Registered)
            {
                UnloadPlugin(plugin);
            }
        }

        void RegisterPlugins()
        {
            var dirs = new List<string>(Directory.EnumerateDirectories(PluginsPath));
            foreach (var dir in dirs)
            {
                RegisterPlugin(dir);
            }
        }

        static Guid SeededGuid(int seed)
        {
            var random = new Random(seed);
            return Guid.Parse(string.Format("{0:X4}{1:X4}-{2:X4}-{3:X4}-{4:X4}-{5:X4}{6:X4}{7:X4}",
                random.Next(0, 0xffff), random.Next(0, 0xffff),
                random.Next(0, 0xffff),
                random.Next(0, 0xffff) | 0x4000,
                random.Next(0, 0x3fff) | 0x8000,
                random.Next(0, 0xffff), random.Next(0, 0xffff), random.Next(0, 0xffff)));
        }

        static uint FNV1a(string str)
        {
            uint hash = 0x811C9DC5;
            foreach (var ch in Encoding.UTF8.GetBytes(str))
            {
                hash ^= (byte)ch;
                hash *= 0x1000193;
            }
            return hash;
        }

        public static void GenerateProject(Plugin plugin)
        {
            var binaryPathX86 = Path.Combine(Utils.GetRootPath(), "x86", "plugins", "Dotx64Dbg");
            var binaryPathX64 = Path.Combine(Utils.GetRootPath(), "x64", "plugins", "Dotx64Dbg");
            var assemblies = new string[] {
                "Dotx64DbgBindings.dll", "Dotx64DbgManaged.dll"
            };

            if (plugin.Info == null)
                return;

            var projectFilePath = plugin.ProjectFilePath;
            Console.WriteLine($"[DotX64Dbg] Generating project for {plugin.Info.Name}");

            var projGen = new ProjectGenerator();
            projGen.ReferencePathX86 = binaryPathX86;
            projGen.ReferencePathX64 = binaryPathX64;
            projGen.References = assemblies;
            if (plugin.Info.Dependencies is not null)
            {
                projGen.Frameworks = plugin.Info.Dependencies
                    .Where(deps => NuGetDependencyResolver.VersioningHelper.IsValidDotNetFrameworkName(deps))
                    .Select(deps => new NuGet.Frameworks.NuGetFramework(
                            NuGetDependencyResolver.VersioningHelper.GetFrameworkName(deps),
                            new Version(NuGetDependencyResolver.VersioningHelper.GetFrameworkVersion(deps)))
                    ).ToArray();
            }

            projGen.Save(projectFilePath);

            var guid = SeededGuid((int)FNV1a(plugin.Info.Name)).ToString().ToUpper();
            var solutionText = $@"
Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.3.32929.385
MinimumVisualStudioVersion = 10.0.40219.1
Project(""{{9A19103F-16F7-4668-BE54-9A1E7A4F7556}}"") = ""{plugin.Info.Name}"", ""{plugin.Info.Name}.csproj"", ""{{{guid}}}""
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Release|x64 = Release|x64
		Release|x86 = Release|x86
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{{{guid}}}.Release|x64.ActiveCfg = Release|x64
		{{{guid}}}.Release|x64.Build.0 = Release|x64
		{{{guid}}}.Release|x86.ActiveCfg = Release|x86
		{{{guid}}}.Release|x86.Build.0 = Release|x86
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
	GlobalSection(ExtensibilityGlobals) = postSolution
		SolutionGuid = {{8BF78ACB-FDCE-407F-89A6-C8FE26E643E6}}
	EndGlobalSection
EndGlobal
".ReplaceLineEndings();

            var solutionFilePath = plugin.SolutionFilePath;
            if (File.Exists(solutionFilePath))
            {
                // Do not recreate the solution if it's already up to date
                var existingText = File.ReadAllText(solutionFilePath, Encoding.UTF8);
                if (existingText != solutionText)
                {
                    File.WriteAllText(solutionFilePath, solutionText, Encoding.UTF8);
                }
            }
            else
            {
                File.WriteAllText(solutionFilePath, solutionText, Encoding.UTF8);
            }
        }

        void GenerateProjects()
        {
            foreach (var plugin in Registered)
            {
                GenerateProject(plugin);
            }
        }

        List<string> EnumerateSourceFiles(string pluginPath)
        {
            return Directory.EnumerateFiles(pluginPath, "*.cs", new EnumerationOptions()
            {
                RecurseSubdirectories = true,
            }).Where(file => !IsExcludedFileOrFolder(pluginPath, file)).ToList();
        }

        PluginInfo GetPluginInfo(string jsonFile)
        {
            try
            {
                var jsonString = Utils.ReadFileContents(jsonFile);
                var pluginInfo = JsonSerializer.Deserialize<PluginInfo>(jsonString);

                var res = JsonSerializer.Deserialize<PluginInfo>(jsonString);
                if (res.Dependencies == null)
                {
                    // Ensure this is never null.
                    res.Dependencies = Array.Empty<string>();
                }

                // Ensure no duplicates exist.
                res.Dependencies = res.Dependencies.Distinct().ToArray();

                // This list has to be sorted to avoid rebuilds when only the order changes.
                Array.Sort(res.Dependencies);

                return res;
            }
            catch (System.Exception)
            {
                return null;
            }
        }

        void RegisterPlugin(string path)
        {
            var jsonFile = Path.Combine(path, "plugin.json");
            var pluginInfo = GetPluginInfo(jsonFile);
            if(pluginInfo == null)
            {
                Console.WriteLine($"[DotX64Dbg] Unable to load plugin info: {jsonFile}");
                return;
            }

            var pathName = Path.GetFileName(path);
            var plugin = new Plugin()
            {
                Info = pluginInfo,
                Path = path,
                ConfigPath = jsonFile,
                RequiresRebuild = false,
                BuildOutputPath = Path.Combine(PluginOutputPath, pathName),
                SourceFiles = EnumerateSourceFiles(path),
            };

            if (!Directory.Exists(plugin.BuildOutputPath))
            {
                Directory.CreateDirectory(plugin.BuildOutputPath);
            }

            Registered.Add(plugin);
            Utils.DebugPrintLine($"Registered new plugin: {plugin.Path}");

            if (plugin.Info != null)
            {
                LoadPlugin(plugin);
            }
        }

        void RemovePlugin(Plugin plugin)
        {
            Utils.DebugPrintLine($"Removing plugin: {plugin.Path}");

            UnloadPlugin(plugin);

            for (var i = 0; i < Registered.Count; ++i)
            {
                if (Registered[i].Path == plugin.Path)
                {
                    Registered.RemoveAt(i);
                    break;
                }
            }
        }

        void LoadPlugin(Plugin plugin)
        {
            var pluginInfo = GetPluginInfo(plugin.ConfigPath);
            if (pluginInfo == null)
            {
                Utils.DebugPrintLine($"[{plugin.Name}] Unable to load plugin info.");
                return;
            }

            Utils.DebugPrintLine($"[{plugin.Name}] Plugin meta loaded, activating plugin.");
            plugin.Info = pluginInfo;

            if (!File.Exists(plugin.ProjectFilePath))
            {
                GenerateProject(plugin);
            }

            plugin.RequiresRebuild = true;
            TriggerRebuild();
        }

        Plugin FindPlugin(string path)
        {
            foreach (var plugin in Registered)
            {
                if (plugin.Path == path)
                {
                    return plugin;
                }
            }
            return null;
        }

        void RebuildOrUnloadPlugin(Plugin plugin, bool unloadWithoutSources = true)
        {
            if (unloadWithoutSources)
            {
                if (plugin.Instance != null && plugin.SourceFiles.Count == 0)
                {
                    Utils.DebugPrintLine($"[PluginWatch] Plugin {plugin.Name} has no sources, unloading.");
                    UnloadPlugin(plugin);
                    return;
                }
            }

            plugin.RequiresRebuild = true;
            TriggerRebuild();
        }

        bool CheckDependeniesChanged(string[] left, string[] right)
        {
            if (left.Length != right.Length)
                return true;

            if (Enumerable.SequenceEqual(left, right))
                return false;

            return true;
        }

        public List<IPlugin> GetPluginInstances()
        {
            // If we are currently rebuilding we have to wait.
            WaitForRebuild();

            return Registered
                .Select(x => x.Instance as IPlugin)
                .Where(x => x != null)
                .ToList();
        }

        internal bool IsPluginNameTaken(string pluginName)
        {
            var path = Path.Combine(Settings.PluginsPath, pluginName);
            if (Directory.Exists(path))
            {
                return true;
            }
            return false;
        }

        public string CreatePluginTemplate(string pluginName)
        {
            var pluginPath = Path.Combine(Settings.PluginsPath, pluginName);
            if (Directory.Exists(pluginPath))
            {
                return null;
            }

            var pluginJsonPath = Path.Combine(pluginPath, "plugin.json");
            var pluginCsPath = Path.Combine(pluginPath, "plugin.cs");

            // Search and replace keywords in templates.
            var replacements = new Dictionary<string, string> {
                { "%PLUGIN_NAME%", pluginName }
            };

            if (!Utils.CreateDir(pluginPath))
            {
                // ERROR.
                return null;
            }


            if (!Utils.WriteReplacedContents(Resources.GetString("Template/plugin.json"), replacements, pluginJsonPath))
            {
                // ERROR.
                return null;
            }

            if (!Utils.WriteReplacedContents(Resources.GetString("Template/plugin.cs"), replacements, pluginCsPath))
            {
                // ERROR.
                return null;
            }

            return pluginPath;
        }
    }
}
