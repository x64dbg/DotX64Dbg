using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Dotx64Dbg
{
    class Resources
    {
        private static Dictionary<string, byte[]> _resources = new Dictionary<string, byte[]>();
        private static string[] _resourceExtensions = new string[] { ".png", ".bmp", ".gif", ".jpg", ".jpeg", ".ico" };

        static Resources()
        {
            var pluginPath = Utils.GetPluginPath();
            var resourcesPath = Path.Combine(pluginPath, "Resources");

            // Check if directory exists
            if (!Directory.Exists(resourcesPath))
            {
                Console.Error.WriteLine($"Resources directory not found: {resourcesPath}");
                return;
            }

            var files = Directory.EnumerateFiles(resourcesPath, "*.*", SearchOption.AllDirectories);
            foreach (var file in files)
            {
                var ext = Path.GetExtension(file);
                if (_resourceExtensions.Contains(ext))
                {
                    // Load the contents and map filename to contents
                    var contents = File.ReadAllBytes(file);
                    var name = Path.GetFileNameWithoutExtension(file);
                    _resources[name] = contents;
                }
            }

            Utils.DebugPrintLine($"Loaded {_resources.Count} resources");
        }

        public static byte[] GetData(string name)
        {
            if (_resources.TryGetValue(name, out var data))
                return data;

            Utils.DebugPrintLine($"Resource not found: {name}");
            return null;
        }
    }
}
