using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Dotx64Dbg
{
    public class Command : Attribute
    {
        public string Name { get; internal set; }
        public bool DebugOnly { get; set; } = false;

        public Command(string Name)
        {
            this.Name = Name;
        }
    }

    public static class Commands
    {
        public delegate bool Handler(string[] args);
        internal delegate void HandlerVoid(string[] args);

        internal struct CommandInfo
        {
            public Handler handler;
        }

        static Dictionary<string, CommandInfo> Registered;

        internal static void Initialize()
        {
            Registered = new();
        }

        internal static bool CommandHandler(string cmd, int argc, IntPtr ptr)
        {
            CommandInfo info;

            if (!Registered.TryGetValue(cmd, out info))
                return false;

            string[] args = new string[argc];

            int elementSize = Marshal.SizeOf(typeof(IntPtr));
            for (int i = 0; i < argc; i++)
            {
                var stringPtr = Marshal.ReadIntPtr(ptr, i * elementSize);
                args[i] = Marshal.PtrToStringAnsi(stringPtr);
            }

            return info.handler(args);
        }

        public static bool Register(string cmd, bool debugOnly, Handler handler)
        {
            if (Registered.ContainsKey(cmd))
            {
                throw new Exception($"Command '{cmd}' already registered");
            }

            CommandInfo info = new()
            {
                handler = handler
            };

            Registered.Add(cmd, info);

            return Native.Commands.RegisterCommand(Manager.PluginHandle, cmd, debugOnly, delegate (int argc, System.IntPtr argv)
            {
                return CommandHandler(cmd, argc, argv);
            });
        }

        public static bool Remove(string cmd)
        {
            if (!Registered.ContainsKey(cmd))
            {
                throw new Exception($"Command '{cmd}' not registered");
            }

            Registered.Remove(cmd);

            return Native.Commands.UnregisterCommand(Manager.PluginHandle, cmd);
        }

        public static bool RemoveAll()
        {
            bool res = true;

            foreach (var kv in Registered)
            {
                if (!Native.Commands.UnregisterCommand(Manager.PluginHandle, kv.Key))
                    res = false;
            }

            Registered.Clear();

            return res;
        }

    }
}
