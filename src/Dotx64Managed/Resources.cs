using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Dotx64Dbg
{
    class Resources
    {
        private static Dictionary<string, byte[]> _resources = new Dictionary<string, byte[]>();

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
                var name = file.Substring(resourcesPath.Length + 1);
                name = name.Replace('\\', '/');
                _resources[name] = File.ReadAllBytes(file);
            }

            Utils.DebugPrintLine($"Loaded {_resources.Count} resources");
        }

        public static byte[] GetData(string name)
        {
            name = name.Replace('\\', '/');
            if (_resources.TryGetValue(name, out var data))
                return data;

            Utils.DebugPrintLine($"Resource not found: {name}");
            return null;
        }

        public static string GetString(string name)
        {
            name = name.Replace('\\', '/');
            var data = GetData(name);
            if (data == null)
                return null;

            return System.Text.Encoding.UTF8.GetString(data);
        }
    }
}
