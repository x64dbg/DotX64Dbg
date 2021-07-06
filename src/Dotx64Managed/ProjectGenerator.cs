using System;
using System.Xml;

namespace Dotx64Dbg
{
    class ProjectGenerator
    {
        public string Sdk = "Microsoft.NET.Sdk";

        public string TargetFramework = "net5.0";

        public string Platforms = "x64;x86";

        public string[] References = new string[0];

        public string ReferencePathX86;

        public string ReferencePathX64;

        public bool Save(string file)
        {
            try
            {
                XmlDocument doc = new();

                var nodeProject = doc.CreateElement("Project");
                nodeProject.SetAttribute("Sdk", Sdk);

                var nodePropsGroup = doc.CreateElement("PropertyGroup");

                var nodeTargetFramework = doc.CreateElement("TargetFramework");
                nodeTargetFramework.InnerText = TargetFramework;

                nodePropsGroup.AppendChild(nodeTargetFramework);

                var nodePlatforms = doc.CreateElement("Platforms");

                //var nodePlatformsInner = doc.CreateTextNode(Platforms);
                nodePlatforms.InnerText = Platforms;
                //nodePlatforms.Value = Platforms;

                nodePropsGroup.AppendChild(nodePlatforms);

                nodeProject.AppendChild(nodePropsGroup);

                // X86 References
                var nodeItemsX86 = doc.CreateElement("ItemGroup");
                nodeItemsX86.SetAttribute("Condition", "'$(PlatformName)' == 'x86'");

                foreach (var fileRef in References)
                {
                    var nodeRef = doc.CreateElement("Reference");
                    var refPath = System.IO.Path.Combine(ReferencePathX86, fileRef);
                    nodeRef.SetAttribute("Include", refPath);

                    nodeItemsX86.AppendChild(nodeRef);
                }

                nodeProject.AppendChild(nodeItemsX86);

                // X64 References
                var nodeItemsX64 = doc.CreateElement("ItemGroup");
                nodeItemsX64.SetAttribute("Condition", "'$(PlatformName)' == 'x64'");

                foreach (var fileRef in References)
                {
                    var nodeRef = doc.CreateElement("Reference");
                    var refPath = System.IO.Path.Combine(ReferencePathX64, fileRef);
                    nodeRef.SetAttribute("Include", refPath);

                    nodeItemsX64.AppendChild(nodeRef);
                }

                nodeProject.AppendChild(nodeItemsX64);

                doc.AppendChild(nodeProject);

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
