using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    class PluginInfo
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public string Version { get; set; }
        public string Author { get; set; }
        public string Website { get; set; }
    }

    class Plugin
    {
        public PluginInfo Info;
        public string Path;
        public string BuildOutputPath;
        public List<string> SourceFiles;
        public bool RequiresRebuild;
        internal LoaderContext Loader;
        internal string AssemblyPath;
        internal IPlugin Instance;
        internal Type InstanceType;
    }

    internal partial class Loader
    {
        string PluginsPath = "dotplugins";
        string AppDataPath;
        string PluginOutputPath;

        FileSystemWatcher PluginWatch;

        List<Plugin> Plugins = new();
        Dictionary<FileSystemWatcher, Plugin> Watches = new();

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

        public void Startup()
        {
            SetupDirectories();

            PluginWatch = new FileSystemWatcher(PluginsPath);
            PluginWatch.NotifyFilter = NotifyFilters.FileName | NotifyFilters.Size | NotifyFilters.LastWrite;
            PluginWatch.IncludeSubdirectories = false;
            PluginWatch.EnableRaisingEvents = true;
            PluginWatch.Created += OnPluginCreate;
            PluginWatch.Deleted += OnPluginRemove;
            PluginWatch.Renamed += OnPluginRename;

            RegisterPlugins();
            RebuildPlugins();
        }

        public void Shutdown()
        {
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
            foreach (var plugin in Plugins)
            {
                if (plugin.RequiresRebuild == false)
                    continue;

                RebuildPlugin(plugin);
            }
        }

        void RebuildPlugin(Plugin plugin)
        {
            var stopwatch = new Stopwatch();

            Console.WriteLine("Rebuilding plugin '{0}'...", plugin.Info.Name);
            stopwatch.Start();

            var compiler = new Compiler(plugin.BuildOutputPath, plugin.Info.Name);

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
            if (!File.Exists(jsonFile))
            {
                Console.WriteLine("[WARN] Plugin directory {0} has no 'plugin.json', skipping.", path);
                return;
            }

            var pluginInfo = GetPluginInfo(jsonFile);
            if (pluginInfo == null)
            {
                Console.WriteLine("[WARN] Failed to read {0}, skipping.", jsonFile);
                return;
            }

            var plugin = new Plugin()
            {
                Info = pluginInfo,
                Path = path,
                RequiresRebuild = true,
                BuildOutputPath = Path.Combine(PluginOutputPath, pluginInfo.Name),
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

            var watcher = new FileSystemWatcher(PluginsPath, "*.*");
            watcher.NotifyFilter = NotifyFilters.FileName | NotifyFilters.Size | NotifyFilters.LastWrite;
            watcher.IncludeSubdirectories = true;
            watcher.EnableRaisingEvents = true;
            watcher.Created += OnSourceCreate;
            watcher.Deleted += OnSourceRemove;
            watcher.Renamed += OnSourceRename;
            watcher.Changed += OnSourceChange;

            Watches.Add(watcher, plugin);
            Plugins.Add(plugin);

            Console.WriteLine("Registered C# plugin '{0}'", plugin.Info.Name);
        }

        void OnPluginRemove(object sender, FileSystemEventArgs e)
        {
        }

        void OnPluginCreate(object sender, FileSystemEventArgs e)
        {
        }

        void OnPluginRename(object sender, RenamedEventArgs e)
        {
            foreach (var plugin in Plugins)
            {
                if (plugin.Path == e.OldFullPath)
                {
                    plugin.Path = e.FullPath;
                    Console.WriteLine("Plugin {0}, path was renamed.", plugin.Info.Name);
                    break;
                }
            }

            BeginRebuild();
        }

        void OnSourceCreate(object sender, FileSystemEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            //Logging.WriteLine("File create {0}", e.FullPath);
            plugin.SourceFiles.Add(e.FullPath);
            plugin.RequiresRebuild = true;

            BeginRebuild();
        }

        void OnSourceRemove(object sender, FileSystemEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            //Logging.WriteLine("File remove {0}", e.FullPath);
            plugin.SourceFiles.Remove(e.FullPath);
            plugin.RequiresRebuild = true;

            BeginRebuild();
        }

        void OnSourceChange(object sender, FileSystemEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            //Logging.WriteLine("File change {0}", e.FullPath);
            plugin.RequiresRebuild = true;

            BeginRebuild();
        }

        void OnSourceRename(object sender, RenamedEventArgs e)
        {
            var watcher = sender as FileSystemWatcher;

            Plugin plugin;
            if (!Watches.TryGetValue(watcher, out plugin))
            {
                Console.WriteLine("[ERR] Unable to find plugin for path {0}", e.FullPath);
                return;
            }

            //Logging.WriteLine("File rename {0}, {1}", e.OldFullPath, e.FullPath);
            plugin.SourceFiles.Remove(e.OldFullPath);
            plugin.SourceFiles.Add(e.FullPath);
            plugin.RequiresRebuild = true;

            BeginRebuild();
        }

        private void BeginRebuild()
        {
            if (RebuildTask != null)
                return;

            // We delay the rebuilding a bit in case a lot of files are being saved at once.
            RebuildTask = Task.Run(async delegate
            {
                await Task.Delay(100);
                RebuildPlugins();

                RebuildTask = null;
            });
        }

        public List<IPlugin> GetPluginInstances()
        {
            return Plugins
                .Select(x => x.Instance)
                .Where(x => x != null)
                .ToList();
        }
    }
}
