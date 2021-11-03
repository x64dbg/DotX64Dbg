using System;
using System.Text;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

using NuGet.Protocol.Core.Types;
using NuGet.Protocol;
using NuGet.Versioning;
using NuGet.Frameworks;
using NuGet.Packaging.Core;

namespace Dotx64Dbg
{
    internal partial class Plugins
    {
        class NugetHelper
        {
            static readonly string NugetSource = "https://api.nuget.org/v3/index.json";
            //static readonly string NupkgMetadataFileName = ".nupkg.metadata";
            //static readonly string NupkgHashFileExtension = ".sha512";
            //static readonly string NupkgExtension = ".nupkg";

            private static readonly object _lock = new();

            static string LocalNugetRepo => System.IO.Path.Combine(Manager.PluginManager.PluginsPath, ".nuget");

            private static string GetOrCreatePackageDirectory(string pkgId, string version)
            {
                string path = System.IO.Path.Combine(LocalNugetRepo, pkgId, version);
                if (!System.IO.Directory.Exists(path))
                    return System.IO.Directory.CreateDirectory(path).FullName;
                return path;
            }

            private static string CreateNuGetArchiveFileName(string pkgId, string version) =>
                string.Format("{0}.{1}", pkgId, version + PackagingCoreConstants.NupkgExtension);

            public static string GetGlobalPackagesPath()
            {
                var settings = NuGet.Configuration.Settings.LoadDefaultSettings(null);
                string globalPkgFolder = NuGet.Configuration.SettingsUtility.GetGlobalPackagesFolder(settings);
                return globalPkgFolder;
            }

            private static void InitializePackageFolder(string pkgFullName, CancellationToken token)
            {
                var pkgArchiveReader = new NuGet.Packaging.PackageArchiveReader(pkgFullName);

                pkgArchiveReader.CopyFiles(
                    System.IO.Path.GetDirectoryName(pkgFullName),
                    pkgArchiveReader.GetFiles(),
                    new NuGet.Packaging.Core.ExtractPackageFileDelegate((pkgFileName, targetFilePath, Stream) =>
                    {
                        var fileInfo = new System.IO.FileInfo(targetFilePath);
                        fileInfo.Directory!.Create();
                        using var fs = System.IO.File.OpenWrite(fileInfo.FullName);
                        Stream.CopyTo(fs);
                        fs.Close();
                        return targetFilePath;
                    }),
                    NuGet.Common.NullLogger.Instance,
                    token
                );

                // NuGetV3 - https://github.com/NuGet/Home/wiki/Nupkg-Metadata-File#solution
                NuGet.Packaging.NupkgMetadataFile nupkgMetadataFile = new()
                {
                    ContentHash = pkgArchiveReader.GetContentHash(token),
                    Version = 2,
                    Source = NugetSource
                };
                NuGet.Packaging.NupkgMetadataFileFormat.Write(
                    System.IO.Path.Combine(
                        System.IO.Path.GetDirectoryName(pkgFullName),
                        PackagingCoreConstants.NupkgMetadataFileExtension),
                    nupkgMetadataFile
                );

                //  NuGet package original hash
                using System.IO.StreamWriter hashFileSw = new(
                    System.IO.File.OpenWrite(System.IO.Path.GetFileNameWithoutExtension(pkgFullName) + PackagingCoreConstants.HashFileExtension),
                    Encoding.UTF8
                );
                hashFileSw.Write(nupkgMetadataFile.ContentHash);
            }

            public static bool DownloadPackage(string pkgId, string version, System.IO.Stream destStream, CancellationToken token)
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
                        NuGet.Common.NullLogger.Instance,
                        token
                ).GetAwaiter().GetResult();
            }

            public static LocalPackageInfo FindLocalPackage(string source, string pkgId, string version, CancellationToken token)
            {
                var logger = NuGet.Common.NullLogger.Instance;

                NuGet.Configuration.PackageSource localSource = new(source);
                SourceRepository localRepo = new(localSource, Repository.Provider.GetCoreV3());

                var searchLocalResource = localRepo.GetResource<FindLocalPackagesResource>();

                var result = searchLocalResource.FindPackagesById(
                        pkgId,
                        logger,
                        token
                );
                return result.Where(pkg => pkg.Identity.Version.OriginalVersion == version).FirstOrDefault();
            }

            public static LocalPackageInfo GetGlobalLocalPackage(string pkgId, string version, CancellationToken token)
            {
                string localPkgFolder = GetGlobalPackagesPath();
                return FindLocalPackage(localPkgFolder, pkgId, version, token);
            }

            public static LocalPackageInfo FindLocalOrDownloadPackage(string pkgId, string version, CancellationToken token, bool download = true)
            {
                LocalPackageInfo localPackageInfo = GetGlobalLocalPackage(pkgId, version, token);

                if (localPackageInfo == null && download)
                {
                    string pkgFullName = System.IO.Path.Combine(
                        GetOrCreatePackageDirectory(pkgId, version),
                        CreateNuGetArchiveFileName(pkgId, version));

                    lock (_lock)
                    {
                        if (!System.IO.File.Exists(pkgFullName))
                        {
                            using (var fs = new System.IO.FileStream(
                                pkgFullName,
                                System.IO.FileMode.OpenOrCreate, System.IO.FileAccess.ReadWrite, System.IO.FileShare.Read
                            ))
                            {
                                if (!DownloadPackage(pkgId, version, fs, token))
                                    return null;
                            }

                            InitializePackageFolder(pkgFullName, token);
                        }
                    }
                    localPackageInfo = FindLocalPackage(LocalNugetRepo, pkgId, version, token);
                }

                return localPackageInfo;
            }

            public static List<LocalPackageInfo> ResolvePackageDepencies(string pkgId, string version, NuGet.Frameworks.NuGetFramework framework, CancellationToken token, bool download = true)
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

            public class Versioning
            {
                private static readonly string FrameworkNamePattern = @"(?<Name>\S*),(?:Version=v(?:(?<Major>\d).(?<Minor>\d).?(?<Revision>\d)?))";

                //private static readonly Dictionary<string, string[]> maxSuportedVerDict = new()
                //{
                //    { ".NETStandard", new string[7] { "1.0", "1.2", "1.3", "1.4", "2.0", "2.1", "2.1" } },
                //    { ".NETPlatform", new string[7] { "4.5", "4.5.1", "4.6", "4.6.1", "4.6.1", string.Empty, "4.6.1" } },
                //    { ".NetCoreApp", new string[7] { "1.0", "1.0", "1.0", "1.0", "2.0", "3.0", "5.0" } },
                //};

                //public class Framework
                //{
                //    public string Value { get; }

                //    private Framework(string value) => this.Value = value;

                //    public static Framework NETStandard => new(".NETStandard");
                //    public static Framework NETFramework => new(".NETPlatform");
                //    public static Framework NETCore => new(".NetCoreApp");
                //    public static Framework NET5 => new(".NetCoreApp");
                //}

                public static NuGet.Frameworks.NuGetFramework GetFrameworkFromAssembly(System.Reflection.Assembly assembly)
                {
                    var frameworks = assembly.GetCustomAttributes(true).
                        OfType<System.Runtime.Versioning.TargetFrameworkAttribute>();
                    var framework = frameworks.FirstOrDefault();

                    var ragex = System.Text.RegularExpressions.Regex.Match(framework.FrameworkName, FrameworkNamePattern);

                    int major = int.Parse(ragex.Groups["Major"].Value);
                    int minor = int.Parse(ragex.Groups["Minor"].Value);
                    if (!int.TryParse(ragex.Groups["Build"]?.Value, out int build))
                        build = 0;

                    return new NuGet.Frameworks.NuGetFramework(
                        ragex.Groups["Name"].Value,
                        new Version(major, minor, build)
                    );
                }
            }

        }
    }
}
