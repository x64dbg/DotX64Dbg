using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Timers;
using System.Diagnostics;

using NuGet.Packaging;
using NuGet.Frameworks;

namespace Dotx64Dbg
{
    internal partial class Plugins
    {
        System.Threading.Thread BuildThread;
        CancellationTokenSource BuildCancellation = new();

        bool RequiresRebuild = false;
        int RebuildDelay = 0;
        Stopwatch RebuildTimer = new();

        bool RebuildInProgress = false;

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
                    cancelToken.ThrowIfCancellationRequested();

                    System.Threading.Thread.Sleep(10);

                    lock (Manager.LoaderLock)
                    {
                        if (!RequiresRebuild)
                            continue;

                        if (RebuildTimer.ElapsedMilliseconds < RebuildDelay)
                            continue;

                        RequiresRebuild = false;

                        Utils.DebugPrintLine("Begin rebuild");

                        RebuildInProgress = true;
                        RebuildPlugins(cancelToken);
                        RebuildInProgress = false;

                        Utils.DebugPrintLine("End rebuild");
                    }
                }
            }
            catch (OperationCanceledException)
            {
                Utils.DebugPrintLine("Loop cancelled");
                RebuildInProgress = false;
            }
            catch (Exception ex)
            {
                RebuildInProgress = false;
                Utils.PrintException(ex);
            }
        }

        private void TriggerRebuild(int delayMilliseconds = 0)
        {
            Utils.DebugPrintLine($"TriggerRebuild {delayMilliseconds}");
            lock (this)
            {
                RequiresRebuild = true;
                RebuildTimer.Restart();
                RebuildDelay = delayMilliseconds;
            }
        }

        private void WaitForRebuild()
        {
            while (RebuildInProgress)
            {
                System.Threading.Thread.Sleep(1);
            }
        }

        bool RebuildPlugin(Plugin plugin, CancellationToken token)
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

        void RebuildPlugins(CancellationToken token)
        {
            // We have to make sure things aren't build in parallel.
            foreach (var plugin in Registered)
            {
                token.ThrowIfCancellationRequested();

                if (plugin.Info == null)
                {
                    Utils.DebugPrintLine($"Plugin without json: {plugin.Path}, skipping.");
                    continue;
                }

                if (plugin.RequiresRebuild == false)
                {
                    Utils.DebugPrintLine($"Plugin {plugin.Path} requires no rebuild, skipping.");
                    continue;
                }

                if (plugin.SourceFiles.Count == 0)
                {
                    Utils.DebugPrintLine($"Plugin {plugin.Path} has no source files, skipping.");
                    continue;
                }

                // We need to check if a rebuild is indeed necessary
                var cacheDirectory = new DirectoryInfo(Path.Combine(plugin.BuildOutputPath, ".cache"));
                cacheDirectory.Create();
                var cacheFile = Path.Combine(cacheDirectory.FullName, "last_build");
                if (plugin.AssemblyPath is null && File.Exists(cacheFile))
                {
                    if (InitializePluginFromCache(plugin, cacheFile))
                    {
                        if(ReloadPlugin(plugin, plugin.AssemblyPath, token))
                        {
                            Utils.DebugPrintLine($"Loaded plugin '{plugin.Info.Name}' from CACHE");
                        }
                        DeleteNotUsedPluginCache(plugin);
                        plugin.RequiresRebuild = false;
                        continue;
                    }
                    else
                        Utils.DebugPrintLine($"Skiping cache...");
                }
                if (RebuildPlugin(plugin, token))
                {
                    CachePluginBuild(plugin, cacheFile);
                }
                DeleteNotUsedPluginCache(plugin);
            }

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
                bw.Write((uint)0x4D5A); // ZM magic number ;)
                bw.Write(ComputePluginSourcesHash(plugin)); // uint32 hash
                bw.Write(plugin.AssemblyPath);
                bw.Write(plugin.BuildOutputPath);
                bw.Write((uint)0x4D5A);
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

                    if (br.ReadUInt32() != 0x4D5A) // Check magic
                        return false;

                    uint hash = br.ReadUInt32();
                    if (hash != ComputePluginSourcesHash(plugin)) // Modified source files
                        return false;

                    string assemblyPath = br.ReadString();
                    if (!File.Exists(assemblyPath)) // Invalid cache
                        return false;
                    string buildOutputPath = br.ReadString();

                    if (br.ReadUInt32() != 0x4D5A) // Check magic
                        return false;

                    plugin.AssemblyPath = assemblyPath;
                    plugin.BuildOutputPath = buildOutputPath;
                    return true;

                }
                catch (Exception ex)
                {
                    if (ex is FormatException || ex is EndOfStreamException || ex is InvalidDataException)
                        return false;
                    throw;
                }
            }
        }
    }
}
