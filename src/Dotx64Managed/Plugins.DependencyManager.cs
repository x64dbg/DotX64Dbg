using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Reflection;

using NuGet.Frameworks;
using NuGet.Packaging;
using NuGet.Packaging.Core;
using NuGet.Protocol;
using NuGet.Protocol.Core.Types;
using NuGet.Versioning;
using System.Threading.Tasks;
using NuGet.Common;

namespace Dotx64Dbg
{
    internal partial class Plugins
    {
        internal abstract class DependencyResolver
        {
            readonly Dictionary<int, (int depsHash, string[] cachedResolvedDependencies)> pluginDepsCache;
            
            public DependencyResolver()
            {
                AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
                pluginDepsCache = new();
            }

            public string[] ResolvePluginDepencies(Plugin plugin, CancellationToken cancellationToken)
            {
                if (plugin.Info.Dependencies is null || plugin.Info!.Dependencies.Length == 0)
                    return Array.Empty<string>();

                if (!HasDependenciesChanged(plugin))
                    return pluginDepsCache[plugin.GetHashCode()].cachedResolvedDependencies;
                string[] deps = GetPluginDepencies(plugin, cancellationToken);

                AddPluginToCache(plugin, deps);

                return deps;
            }

            public string[] ResolvePluginDepencies(string pluginPath) => throw new NotImplementedException();

            protected abstract string[] GetPluginDepencies(Plugin plugin, CancellationToken cancellationToken);

            private static int GetDepenciesHash(Plugin plugin)
            {
                int hash = 0;
                foreach (var p in plugin.Info.Dependencies)
                    hash ^= p.GetHashCode();
                return hash;
            }

            private bool HasDependenciesChanged(Plugin plugin)
            {
                int pluginInstanceHash = plugin.GetHashCode();
                int currentDepsHash = GetDepenciesHash(plugin);
                if (!pluginDepsCache.TryGetValue(pluginInstanceHash, out var cache))
                {
                    return true;
                }
                return currentDepsHash != cache.depsHash;
            }

            private void AddPluginToCache(Plugin plugin, string[] resolvedDepencies)
            {
                int pluginInstanceHash = plugin.GetHashCode();
                int currentDepsHash = GetDepenciesHash(plugin);
                pluginDepsCache[pluginInstanceHash] = (currentDepsHash, resolvedDepencies);
            }


            /// <summary>
            /// Resolves external assemblies to the current domain
            /// </summary>
            /// <remarks>
            /// Any external dependency required by plugins needs to be loaded in the current domain otherwise, the execution fails.
            /// </remarks>
            /// <param name="sender"></param>
            /// <param name="args"></param>
            /// <returns>The loaded assembly</returns>
            private System.Reflection.Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
            {
                var assemblyName = new AssemblyName(args.Name);
                var pluginDeps = pluginDepsCache.Values
                    .Select(values => values.cachedResolvedDependencies);
                foreach(var deps in pluginDeps)
                {
                    var assemblyPath = deps
                        .FirstOrDefault(file => Path.GetFileNameWithoutExtension(file).Equals(assemblyName.Name, StringComparison.OrdinalIgnoreCase));

                    if(assemblyPath != null)
                    {
                        return Assembly.LoadFrom(assemblyPath);
                    }
                }
                return null;
            }

        }

        internal partial class NuGetDependencyResolver : DependencyResolver
        {
            static readonly string NugetSource = "https://api.nuget.org/v3/index.json";
            static string LocalNugetRepo => Path.Combine(Manager.PluginManager.PluginsPath, ".nuget");

            private readonly NuGet.Common.ILogger Logger;

            private static readonly object _lock = new();
            readonly SourceRepository localRepository;
            readonly SourceRepository globalCache;

            public NuGetDependencyResolver()
            {
                this.localRepository = new SourceRepository(new(LocalNugetRepo), Repository.Provider.GetCoreV3());
                this.globalCache = new SourceRepository(new(GetGlobalPackagesPath()), Repository.Provider.GetCoreV3());
                Logger = new NuGetDependencyResolverLogger(Console.Out);
            }

            protected override string[] GetPluginDepencies(Plugin plugin, CancellationToken cancellationToken)
            {
                if (plugin.Info is null)
                    return Array.Empty<string>();

                List<string> requiredLibs = new();
                foreach (string dep in plugin.Info.Dependencies)
                {
                    if(!VersioningHelper.IsValidDotNetFrameworkName(dep))
                    {
                        requiredLibs.Add(dep); //  We can't resolve this library, let it pass through
                        continue;
                    }

                    string pkgId = dep[..dep.IndexOf(',')];
                    string pkgVersion = VersioningHelper.GetFrameworkVersion(dep);

                    var packageInfo = FindLocalOrDownloadPackage(pkgId, pkgVersion, cancellationToken);
                    if (packageInfo is null)
                    {
                        Logger.LogError($"Failed to acquire nuget package: {pkgId}");
                        continue;
                    }

                    var executingFramework = VersioningHelper.GetFrameworkFromAssembly(Assembly.GetExecutingAssembly());
                    using var pkgReader = packageInfo.GetReader();
                    var requiredPkg = pkgReader.GetLibItems().GetNearest(executingFramework);
                    var requiredPkgDeps = ResolvePackageDepencies(pkgId, pkgVersion, requiredPkg.TargetFramework, cancellationToken);

                    requiredLibs.AddRange(requiredPkg.Items
                        .Where(item => Path.GetExtension(item).Equals(".dll"))
                        .Select((item) => Path.GetFullPath(Path.Combine(Path.GetDirectoryName(packageInfo.Path), item)))
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

                return requiredLibs.ToArray();
            }

            private static string GetOrCreatePackageDirectory(string pkgId, string version)
            {
                string path = System.IO.Path.Combine(LocalNugetRepo, pkgId, version);
                if (!System.IO.Directory.Exists(path))
                    return System.IO.Directory.CreateDirectory(path).FullName;
                return path;
            }

            private static string CreateNuGetArchiveFileName(string pkgId, string version) =>
                string.Format("{0}.{1}", pkgId, version + PackagingCoreConstants.NupkgExtension);

            private static string GetGlobalPackagesPath()
            {
                var settings = NuGet.Configuration.Settings.LoadDefaultSettings(null);
                string globalPkgFolder = NuGet.Configuration.SettingsUtility.GetGlobalPackagesFolder(settings);
                return globalPkgFolder;
            }

            private static bool InitializePackageFolder(string pkgFullName, CancellationToken token)
            {
                var pkgArchiveReader = new NuGet.Packaging.PackageArchiveReader(pkgFullName);

                var copiedFiles = pkgArchiveReader.CopyFiles(
                    Path.GetDirectoryName(pkgFullName),
                    pkgArchiveReader.GetFiles(),
                    new ExtractPackageFileDelegate((pkgFileName, targetFilePath, Stream) =>
                    {
                        var fileInfo = new FileInfo(targetFilePath);
                        fileInfo.Directory!.Create();
                        using var fs = File.Create(fileInfo.FullName);
                        Stream.CopyTo(fs);
                        fs.Close();
                        return targetFilePath;
                    }),
                    NuGet.Common.NullLogger.Instance,
                    token
                );

                if (!copiedFiles.All(filePath => File.Exists(filePath)))
                    return false;

                // NuGetV3 - https://github.com/NuGet/Home/wiki/Nupkg-Metadata-File#solution
                NuGet.Packaging.NupkgMetadataFile nupkgMetadataFile = new()
                {
                    ContentHash = pkgArchiveReader.GetContentHash(token),
                    Version = 2,
                    Source = NugetSource
                };

                //  NuGet package original hash
                string hashFilePath = Path.Combine(
                    Path.GetDirectoryName(pkgFullName), 
                    Path.GetFileNameWithoutExtension(pkgFullName) + PackagingCoreConstants.HashFileExtension);
                using var hashFile = File.Create(hashFilePath);

                // Write operations
                try
                {
                    // Metadada
                    NuGet.Packaging.NupkgMetadataFileFormat.Write(
                        System.IO.Path.Combine(
                            System.IO.Path.GetDirectoryName(pkgFullName),
                            PackagingCoreConstants.NupkgMetadataFileExtension),
                        nupkgMetadataFile
                    );

                    // Hash file
                    hashFile.Write(Encoding.UTF8.GetBytes(nupkgMetadataFile.ContentHash));

                } catch (IOException)
                {
                    return false;
                }

                return true;
            }

            private static bool IsPackageInitialized(string pkgFullName, CancellationToken token)
            {
                if (!File.Exists(pkgFullName))
                    return false;

                string hashFilePath = Path.Combine(
                    Path.GetDirectoryName(pkgFullName),
                    Path.GetFileNameWithoutExtension(pkgFullName) + PackagingCoreConstants.HashFileExtension);
                if (!File.Exists(hashFilePath))
                    return false;

                string metadataFilePath = Path.Combine(
                           Path.GetDirectoryName(pkgFullName),
                           PackagingCoreConstants.NupkgMetadataFileExtension);
                if (!File.Exists(metadataFilePath))
                    return false;

                var pkgArchiveReader = new PackageArchiveReader(pkgFullName);
                var metadataFile = NupkgMetadataFileFormat.Read(metadataFilePath);

                string hashFileHash = File.OpenText(hashFilePath).ReadToEnd();
                string nupkgHash = pkgArchiveReader.GetContentHash(token);

                return nupkgHash.Equals(hashFileHash, StringComparison.InvariantCultureIgnoreCase) &&
                    nupkgHash.Equals(metadataFile.ContentHash, StringComparison.InvariantCultureIgnoreCase);
            }

            private bool DownloadPackage(string pkgId, string version, System.IO.Stream destStream, CancellationToken token)
            {
                SourceCacheContext cache = new();
                var repo = Repository.Factory.GetCoreV3(NugetSource);

                var resource = repo.GetResource<FindPackageByIdResource>();

                var pkgVersion = new NuGetVersion(version);

                return resource.CopyNupkgToStreamAsync(
                        pkgId,
                        pkgVersion,
                        destStream,
                        cache,
                        Logger,
                        token
                ).GetAwaiter().GetResult();
            }

            private LocalPackageInfo FindPackage(SourceRepository sourceRepository, string pkgId, string version, CancellationToken token)
            {
                var searchLocalResource = sourceRepository.GetResource<FindLocalPackagesResource>();

                var result = searchLocalResource.FindPackagesById(
                        pkgId,
                        Logger,
                        token
                );

                return result.Where(pkg => pkg.Identity.Version.OriginalVersion == version).FirstOrDefault();
            }

            private LocalPackageInfo FindPackageOnLocalRepo(string pkgId, string version, CancellationToken token) =>
                FindPackage(localRepository, pkgId, version, token);

            private LocalPackageInfo FindPackageOnGlobalCache(string pkgId, string version, CancellationToken token) =>
                FindPackage(globalCache, pkgId, version, token);

            private LocalPackageInfo FindLocalOrDownloadPackage(string pkgId, string version, CancellationToken token, bool allowDownload = true)
            {
                LocalPackageInfo localPackageInfo = FindPackageOnGlobalCache(pkgId, version, token);

                if (localPackageInfo == null && allowDownload)
                {
                    string pkgFullName = System.IO.Path.Combine(
                        GetOrCreatePackageDirectory(pkgId, version),
                        CreateNuGetArchiveFileName(pkgId, version));

                    lock (_lock)
                    {
                        if (!File.Exists(pkgFullName))
                        {
                            using var fs = new FileStream(
                                pkgFullName,
                                FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.Read
                            );
                            if (!DownloadPackage(pkgId, version, fs, token))
                                return null;
                        }
                        if(!IsPackageInitialized(pkgFullName, token) && !InitializePackageFolder(pkgFullName, token))
                        {
                            Logger.LogError($"Package '{pkgId}' directory initialization failed!");
                            File.Delete(pkgFullName); // Maybe the nupkg is corrupted?
                        }
                    }
                    localPackageInfo = FindPackageOnLocalRepo(pkgId, version, token);
                }

                return localPackageInfo;
            }

            private List<LocalPackageInfo> ResolvePackageDepencies(string pkgId, string version, NuGet.Frameworks.NuGetFramework framework, CancellationToken token, bool download = true)
            {
                LocalPackageInfo localPackageInfo = FindLocalOrDownloadPackage(pkgId, version, token, download);
                if (localPackageInfo is null)
                    return null;

                var dependencyGroup = localPackageInfo.GetReader().GetPackageDependencies()
                    .Single(depGroup => depGroup.TargetFramework.Equals(framework));

                List<LocalPackageInfo> localPackages = new();

                foreach (var pkg in dependencyGroup.Packages)
                {
                    var depPkg = FindLocalOrDownloadPackage(pkg.Id, pkg.VersionRange.OriginalString, token, download);
                    localPackages.Add(depPkg);
                }

                return localPackages;
            }

            public class VersioningHelper
            {
                private static readonly string FrameworkNamePattern =
                    @"^(?<Name>[a-zA-Z.]*),{1}(?:Version=v(?<Version>(?:(?<Major>\d*)\.(?<Minor>\d*)\.?(?<Revision>\d*)?)))$";

                private readonly static System.Text.RegularExpressions.Regex Regex = new(FrameworkNamePattern); 

                public static NuGet.Frameworks.NuGetFramework GetFrameworkFromAssembly(System.Reflection.Assembly assembly)
                {
                    var frameworks = assembly.GetCustomAttributes(true).
                        OfType<System.Runtime.Versioning.TargetFrameworkAttribute>();
                    var framework = frameworks.FirstOrDefault();

                    var match = Regex.Match(framework.FrameworkName);

                    int major = int.Parse(match.Groups["Major"].Value);
                    int minor = int.Parse(match.Groups["Minor"].Value);
                    if (!int.TryParse(match.Groups["Build"]?.Value, out int build))
                        build = 0;

                    return new NuGet.Frameworks.NuGetFramework(
                        match.Groups["Name"].Value,
                        new Version(major, minor, build)
                    );
                }

                public static string GetFrameworkName(string dotNetFrameworkName) =>
                    Regex.Match(dotNetFrameworkName)?.Groups["Name"].Value;

                public static string GetFrameworkVersion(string dotNetFrameworkName) =>
                    Regex.Match(dotNetFrameworkName)?.Groups["Version"].Value;

                public static bool IsValidDotNetFrameworkName(string dotNetFrameworkName) => Regex.IsMatch(dotNetFrameworkName);
            }

            internal class NuGetDependencyResolverLogger : NuGet.Common.LoggerBase
            {
                private readonly TextWriter textWriter;

                public NuGetDependencyResolverLogger(TextWriter textWriter)
                {
                    this.textWriter = textWriter;
                }

                string FormatLog(ILogMessage message) => string.Format(
                        "[{0}] {1}: {2}",
                        message.Level,
                        nameof(NuGetDependencyResolver),
                        message.Message);

                public override void Log(ILogMessage message) => textWriter.WriteLine(FormatLog(message));

                public override Task LogAsync(ILogMessage message) => Task.Run(() => Log(message));
            }
        }

        
    }

    internal static class DependencyResolverExtensions
    {
        public static string[] ResolveDependencies(this Plugin plugin, Plugins.DependencyResolver resolver, CancellationToken token)
        {
            return resolver.ResolvePluginDepencies(plugin, token);
        }
        
        public static string[] ResolveDependencies(this Plugin plugin, Plugins.DependencyResolver resolver) =>
            plugin.ResolveDependencies(resolver, CancellationToken.None);
    }
}


