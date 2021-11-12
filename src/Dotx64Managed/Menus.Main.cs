using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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

        internal static void CreateNewPlugin()
        {
        }

        internal static void InitializeMainMenu()
        {
            AddMenu("Main/Run Script", RunScript);
            AddMenu("Main/Create Plugin", CreateNewPlugin);
            AddSeperator("Main");
        }

        internal static void OpenEditor(string projectPath)
        {
            System.Diagnostics.Process.Start(new ProcessStartInfo(projectPath) { UseShellExecute = true });
        }
        internal static void OpenFolder(string folder)
        {
            System.Diagnostics.Process.Start(new ProcessStartInfo(folder) { UseShellExecute = true });
        }

        internal static void AddPluginMenu(Plugin plugin)
        {
            if (plugin.Info == null)
                return;

            string rootPath = $"Main/Plugins/{plugin.Info.Name}";

            // Open Editor.
            // TODO: Find a way to determine if something actually handles .csproj.
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
