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

                    lock (this)
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

        /// <summary>
        /// Gets all the packages references in the csproj.
        /// </summary>
        /// <param name="csProjectPath">The path to the csharp project</param>
        /// <returns>A list containing nuget dependencies</returns>
        /// <remarks>TODO: Maybe write proper code for handling cs projects</remarks>
        [Obsolete]
        static List<NuGetFramework> GetProjectPackagesReferences(string csProjectPath)
        {
            List<NuGetFramework> requiredLibs = new();
            System.Xml.XmlDocument csProject = new();
            csProject.Load(csProjectPath);
            var packages = csProject.GetElementsByTagName("PackageReference");
            foreach (System.Xml.XmlNode package in packages)
            {
                string pkgId = package.Attributes.GetNamedItem("Include")!.Value;
                string pkgVersion = package.Attributes.GetNamedItem("Version")!.Value;
                requiredLibs.Add(new NuGetFramework(pkgId, new Version(pkgVersion)));
            }
            return requiredLibs;
        }

        /// <summary>
        /// Update the plugin info dependencies for the dependency manager. This is a temporary 
        /// attempt for handling the 'synchronization' between the plugin JSON and the local csproj
        /// </summary>
        /// <remarks>TODO: write a more proper code for handling references between the csproj and the plugin JSON</remarks>
        /// <param name="plugin"></param>
        [Obsolete]
        static void UpdatePluginInfoPackagseReferences(Plugin plugin)
        {
            var projectFilePath = Path.Combine(plugin.Path, plugin.Info.Name + ".csproj");

            if (!File.Exists(projectFilePath))
                return;

            List<string> references = new(plugin.Info.Dependencies);
            var notIncludeFrameworks = GetProjectPackagesReferences(projectFilePath)
                .Where(framework => !references.Any(_ref => framework.DotNetFrameworkName.Equals(_ref, StringComparison.OrdinalIgnoreCase)));
            
            bool requireUpdate = notIncludeFrameworks.Any();
            foreach (var framework in notIncludeFrameworks)
            {
                references.Add(framework.DotNetFrameworkName);
            }
            
            if(requireUpdate)
            {
                plugin.Info.Dependencies = references.ToArray();
                string json = System.Text.Json.JsonSerializer.Serialize(
                    plugin.Info, 
                    typeof(PluginInfo), 
                    new System.Text.Json.JsonSerializerOptions() { WriteIndented = true}
                );
                using var pluginFile = File.Create(Path.Combine(plugin.Path, "plugin.json"));
                pluginFile.Write(Encoding.UTF8.GetBytes(json));
            }
        }

        void RebuildPlugin(Plugin plugin, CancellationToken token)
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
            }
            else
            {
                Console.WriteLine("Compiled plugin '{0}' in {1} ms", plugin.Info.Name, stopwatch.ElapsedMilliseconds);

                ReloadPlugin(plugin, res.OutputAssemblyPath, token);

                // Successfully built.
                plugin.RequiresRebuild = false;
            }
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
                UpdatePluginInfoPackagseReferences(plugin);

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

                RebuildPlugin(plugin, token);
            }
        }
    }
}
