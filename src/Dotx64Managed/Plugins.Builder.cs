using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Timers;
using System.Diagnostics;

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

        void RebuildPlugin(Plugin plugin, CancellationToken token)
        {
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
