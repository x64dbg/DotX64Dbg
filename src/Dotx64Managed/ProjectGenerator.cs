using System;
using System.Xml;

namespace Dotx64Dbg
{
    class ProjectGenerator
    {
        public string Sdk = "Microsoft.NET.Sdk";

        public string TargetFramework = "net6.0";

        public string Platforms = "x64;x86";

        public string[] References = Array.Empty<string>();

        public NuGet.Frameworks.NuGetFramework[] Frameworks = Array.Empty<NuGet.Frameworks.NuGetFramework>();

        public string ReferencePathX86;

        public string ReferencePathX64;

        public bool Save(string file)
        {
            try
            {
                XmlDocument doc = new();

                var nodeProject = doc.CreateElement("Project");
                doc.AppendChild(nodeProject);

                // PropertyGroup
                {
                    var nodePropsGroup = doc.CreateElement("PropertyGroup");
                    nodeProject.AppendChild(nodePropsGroup);

                    void AppendTextNode(string name, string innerText)
                    {
                        var node = doc.CreateElement(name);
                        node.InnerText = innerText;
                        nodePropsGroup.AppendChild(node);
                    }

                    AppendTextNode("BaseIntermediateOutputPath", @".vs\obj");
                    AppendTextNode("MSBUildProjectExtensionsPath", @".vs\obj");
                    AppendTextNode("MSBuildWarningsAsMessages", "$(MSBuildWarningsAsMessages);MSB3277");
                    AppendTextNode("Configurations", "Release");
                }

                // Import SDK
                {
                    var nodeImport = doc.CreateElement("Import");
                    nodeImport.SetAttribute("Project", "Sdk.props");
                    nodeImport.SetAttribute("Sdk", Sdk);
                    nodeProject.AppendChild(nodeImport);
                }

                // PropertyGroup
                {
                    var nodePropsGroup = doc.CreateElement("PropertyGroup");
                    nodeProject.AppendChild(nodePropsGroup);

                    // TargetFrameWork
                    var nodeTargetFramework = doc.CreateElement("TargetFramework");
                    nodeTargetFramework.InnerText = TargetFramework;
                    nodePropsGroup.AppendChild(nodeTargetFramework);

                    // Platforms
                    var nodePlatforms = doc.CreateElement("Platforms");
                    nodePlatforms.InnerText = Platforms;
                    nodePropsGroup.AppendChild(nodePlatforms);

                    // AppendTargetFrameworkToOutputPath
                    var nodeAppendTargetFrameworkToOutputPath = doc.CreateElement("AppendTargetFrameworkToOutputPath");
                    nodeAppendTargetFrameworkToOutputPath.InnerText = "false";
                    nodePropsGroup.AppendChild(nodeAppendTargetFrameworkToOutputPath);

                    // AppendRuntimeIdentifierToOutputPath
                    var nodeAppendRuntimeIdentifierToOutputPath = doc.CreateElement("AppendRuntimeIdentifierToOutputPath");
                    nodeAppendRuntimeIdentifierToOutputPath.InnerText = "false";
                    nodePropsGroup.AppendChild(nodeAppendRuntimeIdentifierToOutputPath);

                    // BaseOutputPath
                    var nodeBaseOutputPath = doc.CreateElement("BaseOutputPath");
                    nodeBaseOutputPath.InnerText = ".vs\\bin";
                    nodePropsGroup.AppendChild(nodeBaseOutputPath);

                    // UseCommonOutputDirectory
                    var nodeUseCommonOutputDirectory = doc.CreateElement("UseCommonOutputDirectory");
                    nodeUseCommonOutputDirectory.InnerText = "false";
                    nodePropsGroup.AppendChild(nodeUseCommonOutputDirectory);
                }

                // X86 References
                {
                    var nodeItemGroup = doc.CreateElement("ItemGroup");
                    nodeItemGroup.SetAttribute("Condition", "'$(PlatformName)' == 'x86'");

                    foreach (var fileRef in References)
                    {
                        var nodeRef = doc.CreateElement("Reference");
                        var refPath = System.IO.Path.Combine(ReferencePathX86, fileRef);
                        nodeRef.SetAttribute("Include", refPath);

                        nodeItemGroup.AppendChild(nodeRef);
                    }

                    nodeProject.AppendChild(nodeItemGroup);
                }

                // X64 References
                {
                    var nodeItemGroup = doc.CreateElement("ItemGroup");
                    nodeItemGroup.SetAttribute("Condition", "'$(PlatformName)' == 'x64'");

                    foreach (var fileRef in References)
                    {
                        var nodeRef = doc.CreateElement("Reference");
                        var refPath = System.IO.Path.Combine(ReferencePathX64, fileRef);
                        nodeRef.SetAttribute("Include", refPath);

                        nodeItemGroup.AppendChild(nodeRef);
                    }

                    nodeProject.AppendChild(nodeItemGroup);
                }

                // Packages References
                {
                    var nodePkgRefs = doc.CreateElement("ItemGroup");
                    foreach (var pkg in Frameworks)
                    {
                        var nodeRef = doc.CreateElement("PackageReference");
                        nodeRef.SetAttribute("Include", pkg.Framework);
                        nodeRef.SetAttribute("Version", pkg.Version.ToString(3));

                        nodePkgRefs.AppendChild(nodeRef);
                    }

                    nodeProject.AppendChild(nodePkgRefs);
                }

                // Import targets
                {
                    var nodeImport = doc.CreateElement("Import");
                    nodeImport.SetAttribute("Project", "Sdk.targets");
                    nodeImport.SetAttribute("Sdk", Sdk);
                    nodeProject.AppendChild(nodeImport);
                }

                // Override build target
                {
                    var nodeTarget = doc.CreateElement("Target");
                    nodeTarget.SetAttribute("Name", "PostBuildWarn");
                    nodeTarget.SetAttribute("AfterTargets", "PostBuildEvent");

                    nodeProject.AppendChild(nodeTarget);

                    var nodeMsg = doc.CreateElement("Message");
                    nodeMsg.SetAttribute("Text", "NOTE: Building the project is not required, Dotx64Dbg will automatically build and reload on source code changes.");
                    nodeMsg.SetAttribute("Importance", "High");

                    nodeTarget.AppendChild(nodeMsg);
                }

                doc.Save(file);
            }
            catch (System.Exception ex)
            {
                Utils.PrintException(ex);
                return false;
            }

            return true;
        }
    }
}
