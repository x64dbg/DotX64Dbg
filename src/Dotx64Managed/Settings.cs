using System;
using System.IO;
using System.Text.Json;

namespace Dotx64Dbg
{
    class SettingsData
    {
        public string PluginsPath
        {
            get; set;
        }
        public bool EnableTests
        {
            get; set;
        } = false;
        public bool EnableHotloading
        {
            get; set;
        } = false;
    }

    static class Settings
    {
        private static SettingsData Data = new();

        public static string PluginsPath
        {
            get => Data.PluginsPath;
        }

        public static bool EnableTests
        {
            get => Data.EnableTests;
        }

        public static bool EnableHotloading
        {
            get => Data.EnableHotloading;
        }

        static void LoadDefaults()
        {
            Data.PluginsPath = "dotplugins";
            Data.EnableTests = false;
            Data.EnableHotloading = false;
        }

        public static bool Load(string file)
        {
            try
            {
                var fileData = System.IO.File.ReadAllText(file);
                Data = JsonSerializer.Deserialize<SettingsData>(fileData);

                if (!Path.IsPathFullyQualified(PluginsPath))
                {
                    Data.PluginsPath = Path.GetFullPath(Path.Combine(Utils.GetRootPath(), PluginsPath));
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[DotX64Dbg] Exception while loading settings, using defaults.\n{ex}");
                LoadDefaults();
                return false;
            }
            return true;
        }
    }
}
