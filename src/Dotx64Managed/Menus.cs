using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Dotx64Dbg
{
    public struct MenuData
    {
        public int hMenu; //plugin menu handle
        public int hMenuDisasm; //plugin disasm menu handle
        public int hMenuDump; //plugin dump menu handle
        public int hMenuStack; //plugin stack menu handle
        public int hMenuGraph; //plugin graph menu handle
        public int hMenuMemmap; //plugin memory map menu handle
        public int hMenuSymmod; //plugin symbol module menu handle
    }

    internal static partial class Menus
    {
        internal class MenuEntry
        {
            internal Plugin plugin;
            internal UI.Menu.Id id;
            internal UI.Menu.Id parent;
            internal bool subEntry;
        }

        internal static Dictionary<string, MenuEntry> Registered;
        internal static Dictionary<int, UI.Menu.MenuDelegate> Handlers;

        internal static UI.Menu.Id NextInternalId = 0;
        internal static UI.Menu.Id MainMenu;

        // Reserved menu paths that can not belong to a plugin.
        private static readonly string[] PreservedMenus =
        {
            "Main",
            "Main/Plugins",
        };

        internal static void Initialize()
        {
            Registered = new();
            Handlers = new();
        }

        internal static byte[] ImageToBytes(System.Drawing.Image image)
        {
            if (image == null)
                return null;

            var ms = new MemoryStream();
#pragma warning disable CA1416 // We only support Windows.
            image.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
#pragma warning restore CA1416
            return ms.ToArray();
        }

        internal static void InitializeMenus(MenuData data)
        {
            MainMenu = data.hMenu;
            Registered.Add("Main", new()
            {
                plugin = null,
                id = data.hMenu,
                parent = -1
            });

            UI.Disassembly.SetMenuId(data.hMenuDisasm);
            Registered.Add("Disassembly", new()
            {
                plugin = null,
                id = data.hMenuDisasm,
                parent = -1
            });

            UI.Dump.SetMenuId(data.hMenuDump);
            Registered.Add("Dump", new()
            {
                plugin = null,
                id = data.hMenuDump,
                parent = -1
            });

            UI.MemoryMap.SetMenuId(data.hMenuMemmap);
            Registered.Add("MemoryMap", new()
            {
                plugin = null,
                id = data.hMenuMemmap,
                parent = -1
            });

            UI.Stack.SetMenuId(data.hMenuStack);
            Registered.Add("Stack", new()
            {
                plugin = null,
                id = data.hMenuStack,
                parent = -1
            });

            InitializeMainMenu();
        }

        internal static void HandleCallback(int id)
        {
            UI.Menu.MenuDelegate func;
            if (Handlers.TryGetValue(id, out func))
            {
                try
                {
                    func();
                }
                catch (Exception ex)
                {
                    Utils.PrintException(ex);
                }
            }
        }

        internal static void AddMenu(string path, UI.Menu.MenuDelegate func) =>
            AddMenu(path, null, func);

        internal static void AddMenu(string path, System.Drawing.Image image, UI.Menu.MenuDelegate func) =>
            AddMenu(null, path, image, func);

        internal static void AddMenu(Plugin plugin, string path, UI.Menu.MenuDelegate func) =>
            AddMenu(plugin, path, null, func);

        internal static void AddMenu(Plugin plugin, string path, System.Drawing.Image image, UI.Menu.MenuDelegate func)
        {
            var pos = 0;
            var prev = 0;
            var entryName = "";

            MenuEntry entry = null;
            MenuEntry nextEntry = null;

            pos = path.IndexOf('/', pos);
            while (pos > 0)
            {
                var currentPath = path.Substring(0, pos);
                entryName = path.Substring(prev, (pos - prev));

                if (!Registered.TryGetValue(currentPath, out nextEntry))
                {
                    var parentId = entry != null ? entry.id : (UI.Menu.Id)(-1);

                    nextEntry = new()
                    {
                        plugin = plugin,
                        parent = parentId,
                        id = Native.UI.Menu.Add(parentId, entryName),
                        subEntry = false,
                    };
                    if (PreservedMenus.Contains(currentPath))
                    {
                        nextEntry.plugin = null;
                    }
                    Registered.Add(currentPath, nextEntry);

                    entry = nextEntry;
                }
                else
                {
                    entry = nextEntry;
                }

                prev = pos + 1;
                pos = path.IndexOf('/', pos + 1);
            }

            // Add the final entry.
            nextEntry = new MenuEntry()
            {
                plugin = plugin,
                parent = entry.id,
                id = NextInternalId,
                subEntry = true,
            };
            if (PreservedMenus.Contains(path))
            {
                nextEntry.plugin = null;
            }
            Registered.Add(path, nextEntry);

            Handlers.Add(nextEntry.id, func);

            entryName = path.Substring(prev);
            Native.UI.Menu.AddEntry(nextEntry.parent, nextEntry.id, entryName);
            if (image is not null)
            {
                byte[] imageData = ImageToBytes(image);
                Native.UI.Menu.SetEntryIcon(Manager.PluginHandle, nextEntry.id, imageData);
            }

            NextInternalId++;
        }

        internal static bool TryFindMenu(string path, out UI.Menu.Id id)
        {
            MenuEntry entry = null;
            if (!Registered.TryGetValue(path, out entry))
            {
                id = -1;
                return false;
            }
            id = entry.id;
            return true;
        }

        internal static bool AddSeperator(string path)
        {
            UI.Menu.Id id;
            if (!TryFindMenu(path, out id))
            {
                return false;
            }
            return Native.UI.Menu.AddSeperator(id);
        }

        internal static bool Remove(string name)
        {
            MenuEntry entry;
            if (Registered.TryGetValue(name, out entry))
            {
                if (entry.subEntry)
                    Native.UI.Menu.RemoveEntry(Manager.PluginHandle, entry.id);
                else
                    Native.UI.Menu.Remove(entry.id);

                Handlers.Remove(entry.id);
                Registered.Remove(name);

                return true;
            }

            return false;
        }

        internal static bool RemoveAllFor(Plugin plugin)
        {
            Registered.Where(x => x.Value.plugin == plugin)
                .Select(x => x.Key)
                .ToList()
                .ForEach(name =>
                {
                    Remove(name);
                });

            return true;
        }

    }
}
