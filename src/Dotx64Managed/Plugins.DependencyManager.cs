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
        internal class PluginDependencyConsumer
        {
            public PluginInfo PluginInfo { get; }

            public bool HasNext => (_currentNode is null & _head.Next is not null) | _currentNode?.Next is not null;

            public bool HasAny => _head.Next is not null;

            public string Name => _currentNode?.Name ?? throw new NullReferenceException($"The consumer was not initialized with '{nameof(MoveNext)}'");

            public string[] ResolvedDepencies => fullpathDeps.ToArray();

            public bool ResetIterator()
            {
                if (_head.Next is null)
                    return false;
                _currentNode = null;
                return true;
            }

            public bool MoveNext()
            {
                if (!HasNext)
                {
                    if(_head.Next?.Resolved ?? false)
                        _head.Next = null; // The last item was consumed
                    return false;
                }

                if (_currentNode is null)
                {
                    _currentNode = _head.Next;
                    return true;
                }

                if(_currentNode.Resolved) // Detach from list
                {
                    _currentNode.Previous.Next = _currentNode.Next;
                    if (_currentNode.Next is not null)
                        _currentNode.Next.Previous = _currentNode.Previous;
                }
                _currentNode = _currentNode.Next;

                return true;
            }

            public bool Resolve(string libFullPath)
            {
                if (_currentNode == null)
                    throw new NullReferenceException($"The consumer was not initialized with '{nameof(MoveNext)}'");

                if (_currentNode.Resolved || !File.Exists(libFullPath))
                    return false;

                _currentNode.Resolved = true;
                fullpathDeps.Add(libFullPath);
                return true;
            }

            public bool AddRequiredAssemblies(IEnumerable<string> libsFullPath) =>
                AddRequiredAssemblies(libsFullPath.ToArray());

            public bool AddRequiredAssemblies(string[] libsFullPath)
            {
                if (!_currentNode.Resolved || libsFullPath.Any(path => !Path.IsPathFullyQualified(path) || !File.Exists(path)))
                    return false;

                fullpathDeps.AddRange(libsFullPath);
                return true;
            }

            public PluginDependencyConsumer(PluginInfo pluginInfo)
            {
                this.PluginInfo = pluginInfo;

                string[] deps = pluginInfo.Dependencies;
                if (deps is null)
                    return;

                var it = _head;
                foreach (var dep in deps)
                {
                    DependencyNode node = new(dep);
                    node.Previous = it;
                    it.Next = node;
                    it = node;
                }
            }

            private readonly DependencyNode _head = DependencyNode.Null;
            private DependencyNode _currentNode = null;
            private readonly HashSet<string> fullpathDeps = new();

            class DependencyNode : IEquatable<DependencyNode>
            {
                public static DependencyNode Null => new();

                public DependencyNode Next { get; set; }
                public DependencyNode Previous { get; set; }
                public bool Resolved { get; set; } = false;

                public int Id { get; } = 0;
                public string Name { get; } = string.Empty;

                public DependencyNode(string name)
                {
                    Name = name;
                    Id = name.GetHashCode();
                }

                private DependencyNode() { }

                public bool Equals(DependencyNode other) => Id == other.Id;

                public override bool Equals(object obj) => Equals(obj as DependencyNode);

                public override int GetHashCode() => Id;
            }
        }


        /// <summary>
        /// Represents a class that can resolve full paths from dependencies names
        /// </summary>
        internal interface IDependencyResolver
        {
            void ResolveFullpathToDependency(PluginDependencyConsumer dependencyConsumer, CancellationToken token);
        }

        internal class DependencyResolver
        {
            public DependencyResolver()
            {
                pluginDepsCache = new();
            }

            public string[] ResolvePluginDependencies(Plugin plugin, CancellationToken cancellationToken)
            {
                if (plugin.Info.Dependencies is null || plugin.Info!.Dependencies.Length == 0)
                    return Array.Empty<string>();

                if (!HasDependenciesChanged(plugin))
                    return pluginDepsCache[plugin.GetHashCode()].cachedResolvedDependencies;

                PluginDependencyConsumer dependencyConsumer = new (plugin.Info);

                foreach (var resolver in resolvers)
                {
                    resolver.ResolveFullpathToDependency(dependencyConsumer, cancellationToken);
                    if (!dependencyConsumer.HasAny)
                        break; // We don't need to continue, all deps are resolved
                    dependencyConsumer.ResetIterator();
                }

                if(dependencyConsumer.HasAny)
                {
                    // TODO: Create a proper exception for this
                    throw new Exception("The current resolvers where not able to resolve all the dependencies");
                }

                var deps = dependencyConsumer.ResolvedDepencies;
                AddPluginToCache(plugin, deps);
                return deps;
            }

            public void AddResolver(IDependencyResolver dependencyResolver)
            {
                resolvers.Add(dependencyResolver);
            }

            private static int GetDependenciesHash(Plugin plugin)
            {
                int hash = 0;
                foreach (var p in plugin.Info.Dependencies)
                    hash ^= p.GetHashCode();
                return hash;
            }

            private bool HasDependenciesChanged(Plugin plugin)
            {
                int pluginInstanceHash = plugin.GetHashCode();
                int currentDepsHash = GetDependenciesHash(plugin);
                if (!pluginDepsCache.TryGetValue(pluginInstanceHash, out var cache))
                {
                    return true;
                }
                return currentDepsHash != cache.depsHash;
            }

            private void AddPluginToCache(Plugin plugin, string[] resolvedDepencies)
            {
                int pluginInstanceHash = plugin.GetHashCode();
                int currentDepsHash = GetDependenciesHash(plugin);
                pluginDepsCache[pluginInstanceHash] = (currentDepsHash, resolvedDepencies);
            }

            readonly Dictionary<int, (int depsHash, string[] cachedResolvedDependencies)> pluginDepsCache;
            readonly List<IDependencyResolver> resolvers = new();
        }

        /// <summary>
        /// A class that can resolve dependencies via nuget
        /// </summary>
        internal class NuGetDependencyResolver : IDependencyResolver
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

            public void ResolveFullpathToDependency(PluginDependencyConsumer dependencyConsumer, CancellationToken token)
            {
                while (dependencyConsumer.MoveNext())
                {
                    string name = dependencyConsumer.Name;
                    if (!VersioningHelper.IsValidDotNetFrameworkName(name))
                    {
                        continue; //  We can't resolve this library
                    }

                    string pkgId = name[..name.IndexOf(',')];
                    string pkgVersion = VersioningHelper.GetFrameworkVersion(name);

                    var packageInfo = FindLocalOrDownloadPackage(pkgId, pkgVersion, token);
                    if (packageInfo is null)
                    {
                        Logger.LogError($"Failed to acquire nuget package: {pkgId}");
                        continue;
                    }

                    var executingFramework = VersioningHelper.GetFrameworkFromAssembly(Assembly.GetExecutingAssembly());
                    using var pkgReader = packageInfo.GetReader();
                    var requiredPkg = pkgReader.GetLibItems().GetNearest(executingFramework);
                    var requiredPkgDeps = ResolvePackageDepencies(pkgId, pkgVersion, requiredPkg.TargetFramework, token);

                    dependencyConsumer.Resolve(requiredPkg.Items
                        .Where(item => Path.GetExtension(item).Equals(".dll"))
                        .Select((item) => Path.GetFullPath(Path.Combine(Path.GetDirectoryName(packageInfo.Path), item)))
                        .First()
                    );

                    foreach (var pkgDep in requiredPkgDeps)
                    {
                        using var depPkgReader = pkgDep.GetReader();
                        var libItems = depPkgReader.GetLibItems().GetNearest(requiredPkg.TargetFramework);
                        dependencyConsumer.AddRequiredAssemblies(libItems.Items
                            .Where(item => Path.GetExtension(item).Equals(".dll"))
                            .Select(item => Path.GetFullPath(Path.Combine(Path.GetDirectoryName(pkgDep.Path), item)))
                        );
                    }
                }
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
                    @"^(?<Name>[a-zA-Z.]+),Version=v(?<Version>(?<Major>[\d]+)\.(?<Minor>[\d]+)(?:\.(?<Build>[\d]+))?)$";

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

        internal class LocalAssembliesResolver : IDependencyResolver
        {
            public void ResolveFullpathToDependency(PluginDependencyConsumer dependencyConsumer, CancellationToken token)
            {
                while(dependencyConsumer.MoveNext())
                {
                    token.ThrowIfCancellationRequested();

                    string assemblyName = dependencyConsumer.Name;
                    var coreAssemblyPath = Path.GetDirectoryName(typeof(object).Assembly.Location);
                    dependencyConsumer.Resolve(Path.Combine(coreAssemblyPath, assemblyName));
                }
            }
        }
    }

    internal static class DependencyResolverExtensions
    {
        public static string[] ResolveDependencies(this Plugin plugin, Plugins.DependencyResolver resolver, CancellationToken token)
        {
            return resolver.ResolvePluginDependencies(plugin, token);
        }
        
        public static string[] ResolveDependencies(this Plugin plugin, Plugins.DependencyResolver resolver) =>
            plugin.ResolveDependencies(resolver, CancellationToken.None);
    }
}


