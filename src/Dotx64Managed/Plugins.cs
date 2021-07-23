using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    internal class PluginInfo
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public string Version { get; set; }
        public string Author { get; set; }
        public string Website { get; set; }

        public string[] Dependencies { get; set; }
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
        internal object Instance;
        internal Type InstanceType;
    }

    internal partial class Plugins
    {
        string PluginsPath = "dotplugins";
        string AppDataPath;
        string PluginOutputPath;

        FileSystemWatcher PluginWatch;

        List<Plugin> Registered = new();
        Dictionary<FileSystemWatcher, Plugin> Watches = new();

        CancellationTokenSource Canceller { get; set; }
        Task RebuildTask;

        private void SetupDirectories()
        {
            PluginsPath = Settings.PluginsPath;
            if (!Path.IsPathFullyQualified(PluginsPath))
            {
                PluginsPath = Path.GetFullPath(Path.Combine(Utils.GetRootPath(), PluginsPath));
            }

            if (!Directory.Exists(PluginsPath))
            {
                try
                {
                    Directory.CreateDirectory(PluginsPath);
                }
                catch (Exception)
                {
                    Console.WriteLine("Unable to create directory for plugins: {0}", PluginsPath);
                }
            }

            Console.WriteLine("DotX64Dbg Plugins Path: {0}", PluginsPath);

            AppDataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "DotX64Dbg");
            if (!Directory.Exists(AppDataPath))
            {
                Directory.CreateDirectory(AppDataPath);
            }

            PluginOutputPath = Path.Combine(AppDataPath, "Plugins");
            if (!Directory.Exists(PluginOutputPath))
            {
                Directory.CreateDirectory(PluginOutputPath);
            }
        }

        public void Initialize()
        {
            SetupDirectories();

            PluginWatch = new FileSystemWatcher(PluginsPath, "*.*");
            PluginWatch.NotifyFilter = NotifyFilters.FileName | NotifyFilters.DirectoryName | NotifyFilters.Size | NotifyFilters.LastWrite | NotifyFilters.Attributes;
            PluginWatch.IncludeSubdirectories = false;
            PluginWatch.EnableRaisingEvents = true;
            PluginWatch.Created += OnPluginCreate;
            PluginWatch.Deleted += OnPluginRemove;
            PluginWatch.Renamed += OnPluginRename;

            RegisterPlugins();
            GenerateProjects();
            BeginRebuild(false);
        }

        public void Shutdown()
        {
            if (RebuildTask != null)
            {
                Canceller.Cancel();
                RebuildTask.Wait();
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

        void RebuildPlugins()
        {
            foreach (var plugin in Registered)
            {
                if (plugin.Info == null)
                    continue;

                if (plugin.RequiresRebuild == false)
                    continue;

                RebuildPlugin(plugin);
            }
        }

        void GenerateProjects()
        {
            var binaryPathX86 = Path.Combine(Utils.GetRootPath(), "x86", "plugins");
            var binaryPathX64 = Path.Combine(Utils.GetRootPath(), "x64", "plugins");
            var assemblies = new string[] {
                "Dotx64Dbg.Bindings.dll", "Dotx64Dbg.Managed.dll"
            };

            foreach (var plugin in Registered)
            {
                if (plugin.Info == null)
                    continue;

                var projectFilePath = Path.Combine(plugin.Path, plugin.Info.Name + ".csproj");
                if (File.Exists(projectFilePath))
                    continue;

                Console.WriteLine($"Generating project file for {plugin.Info.Name}");

                var projGen = new ProjectGenerator();
                projGen.ReferencePathX86 = binaryPathX86;
                projGen.ReferencePathX64 = binaryPathX64;
                projGen.References = assemblies;

                projGen.Save(projectFilePath);
            }
        }

        void RebuildPlugin(Plugin plugin)
        {
            if (plugin.SourceFiles.Count == 0)
                return;

            var stopwatch = new Stopwatch();

            Console.WriteLine("Rebuilding plugin '{0}'...", plugin.Info.Name);
            stopwatch.Start();

            var compiler = new Compiler(plugin.Info.Name, plugin.BuildOutputPath)
                .WithDependencies(plugin.Info.Dependencies ?? Array.Empty<string>());

            var res = compiler.Compile(plugin.SourceFiles.ToArray());
            stopwatch.Stop();

            if (!res.Success)
            {
                Console.WriteLine("Build failed");
            }
            else
            {
                Console.WriteLine("Compiled plugin '{0}' in {1} ms", plugin.Info.Name, stopwatch.ElapsedMilliseconds);

                ReloadPlugin(plugin, res.OutputAssemblyPath);

                // Successfully built.
                plugin.RequiresRebuild = false;
            }
        }

        List<string> EnumerateSourceFiles(string path)
        {
            return new List<string>(Directory.EnumerateFiles(path, "*.cs", new EnumerationOptions()
            {
                RecurseSubdirectories = true,
            }));
        }

        PluginInfo GetPluginInfo(string jsonFile)
        {
            try
            {
                var jsonString = File.ReadAllText(jsonFile);
                var pluginInfo = JsonSerializer.Deserialize<PluginInfo>(jsonString);

                return JsonSerializer.Deserialize<PluginInfo>(jsonString);
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

            // Delete the old cache.
            var oldFiles = Directory.GetFiles(plugin.BuildOutputPath, "*.*", SearchOption.AllDirectories);
            foreach (var oldFile in oldFiles)
            {
                try
                {
                    if (oldFile.EndsWith(".dll") || oldFile.EndsWith(".pdb"))
                    {
                        File.Delete(oldFile);
                    }
                }
                catch (Exception)
                {
                }
            }

            SetupPluginWatch(plugin, path);
            Registered.Add(plugin);

            if (plugin.Info != null)
            {
                plugin.RequiresRebuild = true;
                BeginRebuild(true);
            }
        }

        void RemovePlugin(Plugin plugin)
        {
            UnloadPlugin(plugin);
            RemovePluginWatch(plugin);
        }

        void RemovePluginWatch(Plugin plugin)
        {
            foreach (var kv in Watches)
            {
                if (kv.Value == plugin)
                {
                    var watch = kv.Key;
                    watch.EnableRaisingEvents = false;
                    watch.Dispose();

                    Watches.Remove(watch);
                    return;
                }
            }
        }

        void SetupPluginWatch(Plugin plugin, string path)
        {
            var watcher = new FileSystemWatcher(path, "*.*");
            watcher.NotifyFilter = NotifyFilters.FileName | NotifyFilters.Size | NotifyFilters.LastWrite | NotifyFilters.Attributes;
            watcher.IncludeSubdirectories = true;
            watcher.EnableRaisingEvents = true;
            watcher.Created += OnPluginFileCreate;
            watcher.Deleted += OnPluginFileRemove;
            watcher.Renamed += OnPluginFileRename;
            watcher.Changed += OnPluginFileChange;

            Watches.Add(watcher, plugin);
        }

        void LoadPlugin(Plugin plugin)
        {
            var pluginInfo = GetPluginInfo(plugin.ConfigPath);
            if (pluginInfo == null)
                return;

            plugin.Info = pluginInfo;

            plugin.RequiresRebuild = true;
            BeginRebuild(true);
        }

        void OnPluginRemove(object sender, FileSystemEventArgs e)
        {
            foreach (var plugin in Registered)
            {
                if (plugin.Path == e.FullPath)
                {
                    RemovePlugin(plugin);
                    break;
                }
            }
        }

        void OnPluginCreate(object sender, FileSystemEventArgs e)
        {
            RegisterPlugin(e.FullPath);

            BeginRebuild(true);
        }

        void OnPluginRename(object sender, RenamedEventArgs e)
        {
            foreach (var plugin in Registered)
            {
                if (plugin.Path == e.OldFullPath)
                {
                    RemovePlugin(plugin);
                    RegisterPlugin(e.FullPath);
                    break;
                }
            }
        }

        void OnPluginFileCreate(object sender, FileSystemEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            var fileName = Path.GetFileName(e.FullPath);
            if (fileName == "plugin.json")
            {
                LoadPlugin(plugin);
            }
            else
            {
                if (!e.FullPath.EndsWith(".cs"))
                    return;

                if (!plugin.SourceFiles.Contains(e.FullPath))
                    plugin.SourceFiles.Add(e.FullPath);

                plugin.RequiresRebuild = true;
                BeginRebuild(true);
            }
        }

        void OnPluginFileRemove(object sender, FileSystemEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            if (plugin.ConfigPath == e.FullPath)
            {
                Utils.DebugPrintLine("plugin.json got removed, unloading plugin");

                plugin.Info = null;
                UnloadPlugin(plugin);
            }
            else
            {
                if (plugin.SourceFiles.Remove(e.FullPath))
                {
                    if (plugin.SourceFiles.Count == 0)
                    {
                        UnloadPlugin(plugin);
                    }
                    else
                    {
                        plugin.RequiresRebuild = true;
                        BeginRebuild(true);
                    }
                }
            }
        }

        void OnPluginFileChange(object sender, FileSystemEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            if (plugin.ConfigPath == e.FullPath)
            {
                var requiresRebuild = plugin.Info == null;

                var pluginInfo = GetPluginInfo(e.FullPath);
                plugin.Info = pluginInfo;

                if (requiresRebuild && pluginInfo != null)
                {
                    plugin.RequiresRebuild = true;
                    BeginRebuild(true);
                }
            }
            else
            {
                if (plugin.SourceFiles.Contains(e.FullPath))
                {
                    plugin.RequiresRebuild = true;

                    BeginRebuild(true);
                }
            }
        }

        void OnPluginFileRename(object sender, RenamedEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            if (plugin.ConfigPath == e.OldFullPath)
            {
                plugin.Info = null;
                UnloadPlugin(plugin);
            }
            else if (plugin.ConfigPath == e.FullPath)
            {
                LoadPlugin(plugin);
            }
            else
            {
                //Logging.WriteLine("File rename {0}, {1}", e.OldFullPath, e.FullPath);
                plugin.SourceFiles.Remove(e.OldFullPath);

                if (!plugin.SourceFiles.Contains(e.FullPath))
                    plugin.SourceFiles.Add(e.FullPath);

                plugin.RequiresRebuild = true;
                BeginRebuild(true);
            }
        }

        private void BeginRebuild(bool delayed)
        {
            if (RebuildTask != null)
                return;

            // We delay the rebuilding a bit in case a lot of files are being saved at once.
            Canceller = new();
            RebuildTask = Task.Run(async delegate
            {
                try
                {
                    if (delayed)
                        await Task.Delay(500, Canceller.Token);

                    RebuildPlugins();
                }
                catch (OperationCanceledException)
                {
                    Console.WriteLine("Rebuild task aborted.");
                }
                RebuildTask = null;
                Canceller = null;
            });
        }

        public List<IPlugin> GetPluginInstances()
        {
            // If we are currently rebuilding we have to wait.
            var rebuildTask = RebuildTask;
            if (rebuildTask != null)
                rebuildTask.Wait();

            return Registered
                .Select(x => x.Instance as IPlugin)
                .Where(x => x != null)
                .ToList();
        }
    }
}
