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
        /// Resolve all the project dependencies via NuGet
        /// </summary>
        /// <param name="csProjectPath">The path to the csharp project</param>
        /// <param name="token">The cancelation token</param>
        /// <returns>A list containing the full path for the dependencies</returns>
        static List<string> GetProjectDependencies(string csProjectPath, CancellationToken token)
        {
            List<string> requiredLibs = new();
            System.Xml.XmlDocument csProject = new();
            csProject.Load(csProjectPath);
            var packages = csProject.GetElementsByTagName("PackageReference");
            foreach (System.Xml.XmlNode package in packages)
            {
                string pkgId = package.Attributes.GetNamedItem("Include")!.Value;
                string pkgVersion = package.Attributes.GetNamedItem("Version")!.Value;

                var packageInfo = NugetHelper.FindLocalOrDownloadPackage(pkgId, pkgVersion, token);
                if (packageInfo is null)
                {
                    Console.WriteLine("Failed to acquire nuget package: {0}", pkgId);
                    continue;
                }

                var executingFramework = NugetHelper.Versioning.GetFrameworkFromAssembly(System.Reflection.Assembly.GetExecutingAssembly());
                using var pkgReader = packageInfo.GetReader();
                var requiredPkg = pkgReader.GetLibItems().GetNearest(executingFramework);
                var requiredPkgDeps = NugetHelper.ResolvePackageDepencies(pkgId, pkgVersion, requiredPkg.TargetFramework, token);

                requiredLibs.AddRange(requiredPkg.Items
                    .Where(item => Path.GetExtension(item).Equals(".dll"))
                    // TODO: Resolve the load context:
                    .Select((item) => System.Reflection.Assembly.LoadFrom(Path.Combine(Path.GetDirectoryName(packageInfo.Path), item)).Location)
                );

                foreach (var pkgDep in requiredPkgDeps)
                {
                    using var depPkgReader = pkgDep.GetReader();
                    var libItems = depPkgReader.GetLibItems().GetNearest(requiredPkg.TargetFramework);
                    requiredLibs.AddRange(libItems.Items
                        .Where(item => Path.GetExtension(item).Equals(".dll"))
                        .Select(item => Path.GetFullPath(Path.Combine(Path.GetDirectoryName(pkgDep.Path), item)))
                    );
                }
            }
            return requiredLibs;
        }

        void RebuildPlugin(Plugin plugin, CancellationToken token)
        {
            var stopwatch = new Stopwatch();

            Console.WriteLine("Rebuilding plugin '{0}'...", plugin.Info.Name);
            stopwatch.Start();

            string csProjctPath = System.IO.Path.Combine(plugin.Path, plugin.Info.Name + ".csproj");
            if (System.IO.File.Exists(csProjctPath))
            {
                var projctDeps = GetProjectDependencies(csProjctPath, token);
                if (plugin.Info.Dependencies != null)
                {
                    var distinct = plugin.Info.Dependencies.Where(libItem => !projctDeps.Any(depLib => depLib == libItem));
                    projctDeps.AddRange(distinct);
                }

                plugin.Info.Dependencies = projctDeps.ToArray();
            }

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
