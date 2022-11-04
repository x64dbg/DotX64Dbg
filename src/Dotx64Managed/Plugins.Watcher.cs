using System.IO;

namespace Dotx64Dbg
{

    internal class PluginFileInfo
    {
        public string PluginName
        {
            get; set;
        }
        // Absolute path to the plugin folder.
        public string PluginPath
        {
            get; set;
        }
        // The file in question relative to PluginPath.
        public string RelativeFilePath
        {
            get; set;
        }
        // The absolute file path, this is the same as Path.Combine(PluginPath, RelativeFilePath)
        public string FilePath
        {
            get; set;
        }
        // This is set to true if the file/folder in question is PluginPath.
        public bool PluginRootFolder
        {
            get; set;
        }
    }

    internal partial class Plugins
    {
        FileSystemWatcher PluginWatch;

        public void InitializeWatcher()
        {
            PluginWatch = new FileSystemWatcher(PluginsPath, "*.*");
            PluginWatch.NotifyFilter = NotifyFilters.FileName | NotifyFilters.DirectoryName | NotifyFilters.Size | NotifyFilters.LastWrite | NotifyFilters.Attributes;
            PluginWatch.IncludeSubdirectories = true;
            PluginWatch.EnableRaisingEvents = true;
            PluginWatch.Created += OnPluginCreate;
            PluginWatch.Deleted += OnPluginRemove;
            PluginWatch.Renamed += OnPluginRename;
            PluginWatch.Changed += OnPluginChange;
        }

        PluginFileInfo ParseInfo(string path)
        {
            var relativePath = Path.GetRelativePath(PluginsPath, path);
            if (relativePath.Length == 0)
                return null;

            if (relativePath.Contains(Path.DirectorySeparatorChar))
            {
                var pos = relativePath.IndexOf(Path.DirectorySeparatorChar);
                var pluginName = relativePath.Substring(0, pos);
                relativePath = relativePath.Substring(pos + 1);

                return new PluginFileInfo()
                {
                    PluginRootFolder = false,
                    PluginName = pluginName,
                    RelativeFilePath = relativePath,
                    PluginPath = Path.Combine(PluginsPath, pluginName),
                    FilePath = Path.Combine(PluginsPath, pluginName, relativePath),
                };
            }
            else
            {
                return new PluginFileInfo()
                {
                    PluginRootFolder = true,
                    PluginName = relativePath,
                    RelativeFilePath = "",
                    FilePath = Path.Combine(PluginsPath, relativePath),
                    PluginPath = Path.Combine(PluginsPath, relativePath),
                };
            }
        }

        bool IsPathIgnored(string relativePluginPath)
        {
            string[] blockedPaths = { ".vs", "bin", "obj", ".git", ".vscode" };
            foreach (var blockedPath in blockedPaths)
            {
                if (relativePluginPath.Contains(blockedPath))
                    return true;
            }
            return false;
        }

        bool IsExcludedFileOrFolder(string pluginPath, string filePath)
        {
            if (!filePath.EndsWith(".cs"))
                return true;

            string[] excludedFolders = { ".vs" };

            foreach (var folder in excludedFolders)
            {
                var excludedPath = Path.Combine(pluginPath, folder);
                if (filePath.StartsWith(excludedPath))
                    return true;
            }

            return false;
        }

        // FileWatcher Event
        void OnPluginCreate(object sender, FileSystemEventArgs e)
        {
            lock (PluginWatch)
            {
                var info = ParseInfo(e.FullPath);
                if (info == null)
                    return;

                if (IsPathIgnored(info.RelativeFilePath))
                {
                    return;
                }

                if (info.PluginRootFolder)
                {
                    RegisterPlugin(e.FullPath);
                }
                else
                {
                    var plugin = FindPlugin(info.PluginPath);
                    if (plugin == null)
                    {
                        Utils.DebugPrintLine($"[PluginWatch] Unable to find registered plugin for {info.PluginName}");
                        return;
                    }

                    // File was created.
                    OnPluginFileCreate(plugin, info);
                }
            }
        }

        void OnPluginFileCreate(Plugin plugin, PluginFileInfo info)
        {
            if (info.RelativeFilePath == "plugin.json")
            {
                LoadPlugin(plugin);
            }
            else
            {
                if (IsExcludedFileOrFolder(info.PluginPath, info.FilePath))
                    return;

                if (!plugin.SourceFiles.Contains(info.FilePath))
                {
                    Utils.DebugPrintLine($"[PluginWatch] Plugin File Create: {info.FilePath}");

                    plugin.SourceFiles.Add(info.FilePath);

                    RebuildOrUnloadPlugin(plugin);
                }
            }
        }

        // FileWatcher Event
        void OnPluginRemove(object sender, FileSystemEventArgs e)
        {
            lock (PluginWatch)
            {
                var info = ParseInfo(e.FullPath);
                if (info == null)
                    return;

                if (IsPathIgnored(info.RelativeFilePath))
                {
                    return;
                }

                var plugin = FindPlugin(info.PluginPath);
                if (plugin == null)
                {
                    Utils.DebugPrintLine($"[PluginWatch] Unable to find registered plugin for {info.PluginName}");
                    return;
                }

                if (info.PluginRootFolder)
                {
                    RemovePlugin(plugin);
                }
                else
                {
                    OnPluginFileRemove(plugin, info);
                }
            }
        }

        void OnPluginFileRemove(Plugin plugin, PluginFileInfo info)
        {
            if (plugin.ConfigPath == info.FilePath)
            {
                Utils.DebugPrintLine("[PluginWatch] plugin.json got removed, unloading plugin");

                plugin.Info = null;
                UnloadPlugin(plugin);
            }
            else
            {
                if (plugin.SourceFiles.Remove(info.FilePath))
                {
                    Utils.DebugPrintLine($"[PluginWatch] Plugin File Remove: {info.FilePath}");

                    RebuildOrUnloadPlugin(plugin);
                }
            }
        }

        // FileWatcher Event
        void OnPluginRename(object sender, RenamedEventArgs e)
        {
            lock (PluginWatch)
            {
                // Use old path first to identify the current plugin.
                var info = ParseInfo(e.OldFullPath);
                if (info == null)
                    return;

                if (IsPathIgnored(info.RelativeFilePath))
                {
                    return;
                }

                var plugin = FindPlugin(info.PluginPath);
                if (plugin == null)
                {
                    Utils.DebugPrintLine($"[PluginWatch] Unable to find registered plugin for {info.PluginName}");
                    return;
                }

                if (info.PluginRootFolder)
                {
                    RemovePlugin(plugin);
                    RegisterPlugin(e.FullPath);
                }
                else
                {
                    // If its not the root folder use the new full path.
                    info = ParseInfo(e.FullPath);
                    if (info == null)
                        return;

                    plugin = FindPlugin(info.PluginPath);
                    if (plugin == null)
                    {
                        Utils.DebugPrintLine($"[PluginWatch] Unable to find registered plugin for {info.PluginName}");
                        return;
                    }

                    OnPluginFileRename(plugin, info, e.OldFullPath);
                }
            }
        }

        void OnPluginFileRename(Plugin plugin, PluginFileInfo info, string oldFullPath)
        {
            if (plugin.ConfigPath == oldFullPath)
            {
                UnloadPlugin(plugin);
                plugin.Info = null;
            }
            else if (plugin.ConfigPath == info.FilePath)
            {
                LoadPlugin(plugin);
            }
            else
            {
                var isSourceRemoved = plugin.SourceFiles.Remove(oldFullPath);
                var isExcluded = IsExcludedFileOrFolder(info.PluginPath, info.FilePath);
                var isAdded = false;

                if (!isExcluded)
                {
                    if (!plugin.SourceFiles.Contains(info.FilePath))
                    {
                        plugin.SourceFiles.Add(info.FilePath);
                        isAdded = true;
                    }
                }

                // Work-around for issue #66
                // VS temporarily renames source files, don't unload as the next event is another rename.
                var allowUnload = true;
                if (isSourceRemoved && info.FilePath.ToLower().EndsWith(".tmp"))
                {
                    allowUnload = false;
                }

                if (isSourceRemoved || isAdded)
                {
                    Utils.DebugPrintLine($"[PluginWatch] Plugin File Rename: {oldFullPath} -> {info.FilePath}");

                    RebuildOrUnloadPlugin(plugin, allowUnload);
                }
            }
        }

        // FileWatcher Event
        void OnPluginChange(object sender, FileSystemEventArgs e)
        {
            lock (PluginWatch)
            {
                var info = ParseInfo(e.FullPath);
                if (info == null)
                    return;

                if (IsPathIgnored(info.RelativeFilePath))
                {
                    return;
                }

                if (!info.PluginRootFolder)
                {
                    var plugin = FindPlugin(info.PluginPath);
                    if (plugin == null)
                    {
                        Utils.DebugPrintLine($"[PluginWatch] Unable to find registered plugin for {info.PluginName}");
                        return;
                    }

                    OnPluginFileChange(plugin, info);
                }
            }
        }

        void OnPluginFileChange(Plugin plugin, PluginFileInfo info)
        {
            if (plugin.ConfigPath == info.FilePath)
            {
                Utils.DebugPrintLine("[PluginWatch] Plugin info modified, reloading meta...");
                var oldInfo = plugin.Info;

                var pluginInfo = GetPluginInfo(info.FilePath);
                if (pluginInfo == null)
                {
                    Utils.DebugPrintLine("Unable to read plugin meta");
                }

                plugin.Info = pluginInfo;

                var requiresRebuild = false;
                var dependeniesChanged = false;
                if (oldInfo == null && pluginInfo != null)
                {
                    // No info previously
                    requiresRebuild = true;
                    dependeniesChanged = true;
                }
                else if (oldInfo != null && pluginInfo != null)
                {
                    dependeniesChanged = CheckDependeniesChanged(oldInfo.Dependencies, pluginInfo.Dependencies);
                    if (dependeniesChanged)
                    {
                        Utils.DebugPrintLine("Dependencies changed");
                        requiresRebuild = true;
                    }
                }

                // The json drives the project settings.
                if (dependeniesChanged)
                {
                    // Also generate new project, currently doesn't deal with nuget references.
                    GenerateProject(plugin);
                }

                if (requiresRebuild)
                {
                    RebuildOrUnloadPlugin(plugin);
                }
            }
            else
            {
                if (plugin.SourceFiles.Contains(info.FilePath))
                {
                    Utils.DebugPrintLine($"[PluginWatch] Plugin Change: {info.FilePath}");

                    RebuildOrUnloadPlugin(plugin);
                }
            }
        }

    }
}
