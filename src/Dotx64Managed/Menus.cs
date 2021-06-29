using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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

    internal static class Menus
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

        internal static void Initialize()
        {
            Registered = new();
            Handlers = new();
        }

        internal static void SetMenuData(MenuData data)
        {
            UI.Disassembly.SetMenuId(data.hMenuDisasm);
            Registered.Add("Disassembly", new() { plugin = null, id = data.hMenuDisasm, parent = -1 });

            UI.Dump.SetMenuId(data.hMenuDump);
            Registered.Add("Dump", new() { plugin = null, id = data.hMenuDump, parent = -1 });

            UI.MemoryMap.SetMenuId(data.hMenuMemmap);
            Registered.Add("MemoryMap", new() { plugin = null, id = data.hMenuMemmap, parent = -1 });

            UI.Stack.SetMenuId(data.hMenuStack);
            Registered.Add("Stack", new() { plugin = null, id = data.hMenuStack, parent = -1 });
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
                    Console.WriteLine($"Exception: {ex}");
                }
            }
        }

        internal static void Register(Plugin plugin, string path, UI.Menu.MenuDelegate func)
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
                    var parentId = entry.id;

                    nextEntry = new()
                    {
                        plugin = plugin,
                        parent = parentId,
                        id = Native.UI.Menu.Add(parentId, entryName),
                        subEntry = false,
                    };
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

            Registered.Add(path, nextEntry);

            Handlers.Add(nextEntry.id, func);

            entryName = path.Substring(prev);
            Native.UI.Menu.AddEntry(nextEntry.parent, nextEntry.id, entryName);

            NextInternalId++;
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
