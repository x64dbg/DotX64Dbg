using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Dotx64Dbg
{
    internal static partial class Menus
    {
        internal static void RunScript()
        {
            OpenFileDialog fdlg = new OpenFileDialog();
            fdlg.Title = "Open Dotx64Dbg Script";
            fdlg.Filter = ".cs (*.cs)|*.cs|All files (*.*)|*.*";
            fdlg.FilterIndex = 1;
            fdlg.RestoreDirectory = true;
            if (fdlg.ShowDialog() == DialogResult.OK)
            {
                ScriptLoader.ExecuteScriptFile(fdlg.FileName);
            }
        }

        internal static void OpenEditor(string projectPath)
        {
            System.Diagnostics.Process.Start(new ProcessStartInfo(projectPath) { UseShellExecute = true });
        }
        internal static void OpenFolder(string folder)
        {
            System.Diagnostics.Process.Start(new ProcessStartInfo(folder) { UseShellExecute = true });
        }

        internal static void CreateNewPlugin()
        {
            string pluginName;
            string newPluginPath;

            for (; ; )
            {
                pluginName = Native.UI.InputPrompt("Enter a name for the Plugin");
                if (pluginName == null)
                    return;

                newPluginPath = Path.Combine(Settings.PluginsPath, pluginName);
                if (Directory.Exists(newPluginPath))
                {
                    MessageBox.Show("A plugin with the specified name already exists.\n");
                    continue;
                }

                break;
            }

            var pluginJsonPath = Path.Combine(newPluginPath, "plugin.json");
            var pluginCsPath = Path.Combine(newPluginPath, "plugin.cs");

            // Search and replace keywords in templates.
            var replacements = new Dictionary<string, string> {
                { "%PLUGIN_NAME%", pluginName }
            };

            if (!Utils.CreateDir(newPluginPath))
            {
                // ERROR.
            }

            if (!Utils.WriteReplacedContents(Dotx64Dbg.Properties.Resources.plugin_json, replacements, pluginJsonPath))
            {
                // ERROR.
            }

            if (!Utils.WriteReplacedContents(Dotx64Dbg.Properties.Resources.plugin_cs, replacements, pluginCsPath))
            {
                // ERROR.
            }

            OpenFolder(newPluginPath);
        }

        internal static void InitializeMainMenu()
        {
            AddMenu("Main/Run Script", RunScript);
            AddMenu("Main/Create Plugin", CreateNewPlugin);
            AddSeperator("Main");
        }

        internal static void AddPluginMenu(Plugin plugin)
        {
            if (plugin.Info == null)
                return;

            string rootPath = $"Main/Plugins/{plugin.Info.Name}";

            // Open Editor.
            // TODO: Find a way to determine if something actually handles .csproj
            {
                string path = $"{rootPath}/Open in Editor";
                string projectPath = plugin.ProjectFilePath;
                AddMenu(plugin, path, delegate ()
                {
                    OpenEditor(projectPath);
                });
            }

            // Open in Explorer.
            {
                string path = $"{rootPath}/Open in Explorer";
                string pluginPath = plugin.Path;
                AddMenu(plugin, path, delegate ()
                {
                    OpenFolder(pluginPath);
                });
            }

            AddSeperator(rootPath);

            // About.
            {
                string path = $"{rootPath}/About";
                AddMenu(plugin, path, delegate ()
                {
                    if (plugin.Info == null)
                        return;

                    var info = plugin.Info;
                    MessageBox.Show($"Name: {info.Name}\n" +
                        $"Author: {info.Author}\n" +
                        $"Version: {info.Version}\n" +
                        $"Website: {info.Website}\n" +
                        $"Description: {info.Description}", info.Name, MessageBoxButtons.OK, MessageBoxIcon.Information);
                });
            }

        }


    }
}
