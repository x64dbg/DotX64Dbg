using System.Diagnostics;
using System.IO;

namespace Dotx64Dbg
{
    internal static partial class Menus
    {
        internal static void RunScript()
        {
            var fileFilter = "C# File (*.cs)|*.cs|All files (*.*)|*.*";
            var scriptPath = Platform.OpenFileBrowse("Open Dotx64Dbg Script", fileFilter);
            if (scriptPath == null)
                return;

            ScriptLoader.ExecuteScriptFile(scriptPath);
        }

        internal static void OpenEditor(string projectPath)
        {
            System.Diagnostics.Process.Start(new ProcessStartInfo(projectPath) { UseShellExecute = true });
        }
        internal static void OpenFolder(string folder)
        {
            System.Diagnostics.Process.Start(new ProcessStartInfo(folder) { UseShellExecute = true });
        }

        internal static string PromptPluginName()
        {
            var plugins = Manager.GetPlugins();

            for (; ; )
            {
                var pluginName = Native.UI.InputPrompt("Enter a name for the Plugin");
                if (pluginName == null)
                    return null;

                if (plugins.IsPluginNameTaken(pluginName))
                {
                    UI.MsgBox("Error", "A plugin with the specified name already exists.", UI.MsgBoxType.Ok);
                    continue;
                }

                return pluginName;
            }
        }

        internal static void CreateNewPlugin()
        {
            var plugins = Manager.GetPlugins();

            string pluginName = PromptPluginName();
            if (pluginName == null)
                return;

            var pluginPath = plugins.CreatePluginTemplate(pluginName);
            if (pluginPath == null)
            {
                UI.MsgBox("Error", "Failed to create new plugin", UI.MsgBoxType.Ok);
                return;
            }

            OpenFolder(pluginPath);
        }

        internal static void InitializeMainMenu()
        {
            // Plugin icon
            Native.UI.Menu.SetIcon(MainMenu, Resources.GetData("Dotx64DbgIcon"));

            AddMenu("Main/Run Script", Resources.GetData("RunIcon"), RunScript);
            AddMenu("Main/Create Plugin", Resources.GetData("NewScriptIcon"), CreateNewPlugin);
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
                    if (!File.Exists(plugin.ProjectFilePath))
                    {
                        Plugins.GenerateProject(plugin);
                    }
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
                    UI.MsgBox($"Name: {info.Name}\n" +
                        $"Author: {info.Author}\n" +
                        $"Version: {info.Version}\n" +
                        $"Website: {info.Website}\n" +
                        $"Description: {info.Description}", info.Name, UI.MsgBoxType.Ok, UI.MsgBoxIcon.Information);
                });
            }

        }


    }
}
