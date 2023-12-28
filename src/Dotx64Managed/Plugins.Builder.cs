using System;
using System.Diagnostics;
using System.IO;

namespace Dotx64Dbg
{
    internal partial class Plugins
    {
        System.Threading.Thread BuildThread;
        System.Threading.AutoResetEvent WorkerWakeup = new(false);
        System.Threading.CancellationTokenSource BuildCancellation = new();

        const UInt32 PluginCacheMagic = 0x58746F44; // DotX.
        const UInt32 PluginCacheVersion = 0x00000002;

        bool RebuildInProgress = false;
        bool SkipRebuilding = false;

        void StartBuildWorker()
        {
            BuildThread = new(BuildWorker);
            BuildThread.Start();
        }

        void StopBuildWorker()
        {
            try
            {
                BuildCancellation.Cancel();
                WorkerWakeup.Set();
                BuildThread.Join();
            }
            catch (Exception)
            {
            }
        }

        void BuildWorker()
        {
            try
            {
                var cancelToken = BuildCancellation.Token;

                while (true)
                {
                    WorkerWakeup.WaitOne();

                    cancelToken.ThrowIfCancellationRequested();

                    // Delay this a bit to give the file notification handler a chance
                    // to process multiple files.
                    System.Threading.Thread.Sleep(100);

                    lock (Manager.LoaderLock)
                    {
                        Utils.DebugPrintLine("Begin rebuild");

                        RebuildPlugins(cancelToken);

                        Utils.DebugPrintLine("End rebuild");
                        RebuildInProgress = false;
                    }
                }
            }
            catch (OperationCanceledException)
            {
                Utils.DebugPrintLine("Loop canceled");
                RebuildInProgress = false;
            }
            catch (Exception ex)
            {
                RebuildInProgress = false;
                Utils.PrintException(ex);
            }
        }

        private void TriggerRebuild()
        {
            if (SkipRebuilding)
                return;

            Utils.DebugPrintLine($"TriggerRebuild");

            RebuildInProgress = true;
            WorkerWakeup.Set();
        }

        private void WaitForRebuild()
        {
            while (RebuildInProgress)
            {
                System.Threading.Thread.Sleep(10);
            }
        }

        bool RebuildPlugin(Plugin plugin, System.Threading.CancellationToken token)
        {
            var stopwatch = new Stopwatch();

            Console.WriteLine("Rebuilding plugin '{0}'...", plugin.Info.Name);
            stopwatch.Start();

            var compiler = new Compiler(plugin.Info.Name, plugin.BuildOutputPath)
                .WithDependencies(plugin.ResolveDependencies(dependencyResolver, token));

            var res = compiler.Compile(plugin.SourceFiles.ToArray());
            stopwatch.Stop();

            if (!res.Success)
            {
                Console.WriteLine("Build failed");
                return false;
            }

            Console.WriteLine("Compiled plugin '{0}' in {1} ms", plugin.Info.Name, stopwatch.ElapsedMilliseconds);

            // Successfully built.
            plugin.RequiresRebuild = false;

            return ReloadPlugin(plugin, res.OutputAssemblyPath, token);
        }

        void RebuildPlugins(System.Threading.CancellationToken token)
        {
            // TODO: Investigate building in parallel            
            //Parallel.ForEach(Registered, plugin =>
            Registered.ForEach(plugin =>
            {
                token.ThrowIfCancellationRequested();

                if (plugin.Info == null || plugin.RequiresRebuild == false)
                {
                    return;
                }

                if (plugin.SourceFiles.Count == 0)
                {
                    Utils.DebugPrintLine($"Plugin {plugin.Path} has no source files, skipping.");
                    return;
                }

                // We need to check if a rebuild is indeed necessary
                var cacheDirectory = new DirectoryInfo(Path.Combine(plugin.BuildOutputPath, ".cache"));
                cacheDirectory.Create();
                var cacheFile = Path.Combine(cacheDirectory.FullName, "last_build");
                if (plugin.AssemblyPath is null && File.Exists(cacheFile))
                {
                    if (InitializePluginFromCache(plugin, cacheFile))
                    {
                        if (ReloadPlugin(plugin, plugin.AssemblyPath, token))
                        {
                            Utils.DebugPrintLine($"Loaded plugin '{plugin.Info.Name}' from cache");
                        }
                        DeleteNotUsedPluginCache(plugin);
                        plugin.RequiresRebuild = false;
                        return;
                    }
                    else
                        Utils.DebugPrintLine($"Skipking cache...");
                }
                if (RebuildPlugin(plugin, token))
                {
                    CachePluginBuild(plugin, cacheFile);
                }
                DeleteNotUsedPluginCache(plugin);
            });

            void DeleteNotUsedPluginCache(Plugin plugin)
            {
                var oldFiles = Directory.GetFiles(plugin.BuildOutputPath, "*.*", SearchOption.AllDirectories);
                string baseFileName = Path.GetFileNameWithoutExtension(plugin.AssemblyPath);

                foreach (var oldFile in oldFiles)
                {
                    if (Path.GetFileNameWithoutExtension(oldFile).Equals(baseFileName, StringComparison.OrdinalIgnoreCase))
                        continue;

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
            }

            uint ComputePluginSourcesHash(Plugin plugin)
            {
                uint hash = uint.MaxValue;
                var md5 = System.Security.Cryptography.MD5.Create();
                foreach (var source in plugin.SourceFiles)
                {
                    var md5Hash = md5.ComputeHash(File.ReadAllBytes(source));
                    foreach (byte b in md5Hash)
                        hash = (hash >> 8) ^ b;
                }
                return hash;
            }

            void CachePluginBuild(Plugin plugin, string cacheFilePath)
            {
                using var fs = File.OpenWrite(cacheFilePath);
                using System.IO.Compression.ZipArchive zipArchive = new(fs, System.IO.Compression.ZipArchiveMode.Create);
                var entry = zipArchive.CreateEntry(nameof(Plugin));
                using BinaryWriter bw = new(entry.Open());
                bw.Write(PluginCacheMagic);
                bw.Write(PluginCacheVersion);
                bw.Write(Utils.GetVersionHash());
                bw.Write(ComputePluginSourcesHash(plugin)); // uint32 hash
                bw.Write(plugin.AssemblyPath);
                bw.Write(plugin.BuildOutputPath);
                bw.Write(PluginCacheMagic);
            }

            bool InitializePluginFromCache(Plugin plugin, string cacheFilePath)
            {
                try
                {
                    using System.IO.Compression.ZipArchive zipArchive = System.IO.Compression.ZipFile.OpenRead(cacheFilePath);
                    var entry = zipArchive.GetEntry(nameof(Plugin));
                    if (entry is null)
                        return false;

                    using BinaryReader br = new(entry.Open());

                    if (br.ReadUInt32() != PluginCacheMagic)
                    {
                        Utils.DebugPrintLine($"Invalid cache for plugin '{plugin.Path}'");
                        return false;
                    }

                    var cacheVersion = br.ReadUInt32();
                    if (cacheVersion < PluginCacheVersion)
                    {
                        Utils.DebugPrintLine($"Cache version mismatch for plugin '{plugin.Path}': {cacheVersion} < {PluginCacheVersion}");
                        return false;
                    }

                    var versionHash = br.ReadUInt32();
                    if (versionHash != Utils.GetVersionHash())
                    {
                        Utils.DebugPrintLine($"Version hash mismatch for plugin '{plugin.Path}': {versionHash} != {Utils.GetVersionHash()}");
                        return false;
                    }

                    uint hash = br.ReadUInt32();
                    if (hash != ComputePluginSourcesHash(plugin))
                    {
                        Utils.DebugPrintLine($"Source hash mismatch for plugin '{plugin.Path}': {hash} != {ComputePluginSourcesHash(plugin)}");
                        return false;
                    }

                    string assemblyPath = br.ReadString();
                    if (!File.Exists(assemblyPath))
                    {
                        Utils.DebugPrintLine($"Assembly '{assemblyPath}' does not exist for plugin '{plugin.Path}'");
                        return false;
                    }
                    string buildOutputPath = br.ReadString();

                    if (br.ReadUInt32() != PluginCacheMagic)
                    {
                        Utils.DebugPrintLine($"Invalid cache for plugin '{plugin.Path}'");
                        return false;
                    }

                    plugin.AssemblyPath = assemblyPath;
                    plugin.BuildOutputPath = buildOutputPath;
                    return true;

                }
                catch (Exception ex)
                {
                    if (ex is FormatException || ex is EndOfStreamException || ex is InvalidDataException)
                    {
                        Utils.DebugPrintLine($"Failed to read cache for plugin '{plugin.Path}': {ex.Message}");
                        return false;
                    }
                    throw;
                }
            }
        }
    }
}
