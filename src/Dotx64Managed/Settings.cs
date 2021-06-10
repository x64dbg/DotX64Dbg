using System;
using System.Text.Json;

namespace Dotx64Dbg
{
    class SettingsData
    {
        public string PluginsPath { get; set; }
        public bool EnableTests { get; set; }
    }

    static class Settings
    {
        private static SettingsData Data = new();

        public static string PluginsPath { get => Data.PluginsPath; }

        public static bool EnableTests { get => Data.EnableTests; }

        static void LoadDefaults()
        {
            Data.PluginsPath = "dotplugins";
            Data.EnableTests = false;
        }

        public static bool Load(string file)
        {
            try
            {
                var fileData = System.IO.File.ReadAllText(file);
                Data = JsonSerializer.Deserialize<SettingsData>(fileData);
            }
            catch (Exception)
            {
                LoadDefaults();
                return false;
            }
            return true;
        }
    }
}
