namespace Dotx64Dbg
{
    /// <summary>
    /// A thread object that represents a module in the debugged process.
    /// </summary>
    public partial class Module
    {
        public readonly nuint Base;

        public static Module Main { get => GetMain(); }

        public string Name { get => GetName(); }

        public string Path { get => GetPath(); }

        public nuint EntryPoint { get => GetEntryPoint(); }

        internal Module(nuint baseAddr)
        {
            Base = baseAddr;
        }

        public static Module GetMain()
        {
            return new Module((nuint)Native.Module.GetMain());
        }

        public static Module FindByName(string name)
        {
            var baseAddr = Native.Module.FindByName(name);
            if (baseAddr == 0)
                return null;

            return new Module((nuint)baseAddr);
        }

        public static Module[] GetAll()
        {
            var mods = Native.Module.GetAll();
            var res = new Module[mods.Length];
            for (int i = 0; i < res.Length; i++)
            {
                res[i] = new Module((nuint)mods[i]);
            }
            return res;
        }

        public string GetName()
        {
            return Native.Module.GetName(Base);
        }

        public string GetPath()
        {
            return Native.Module.GetPath(Base);
        }

        public nuint GetEntryPoint()
        {
            return (nuint)Native.Module.GetEntrypoint(Base);
        }

        /// <summary>Pretty name</summary>
        public override string ToString()
        {
            return $"Module:{Name}";
        }
    }
}
