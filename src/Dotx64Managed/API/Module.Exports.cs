namespace Dotx64Dbg
{
    /// <summary>
    /// Object that represents a module in the debugged process.
    /// </summary>
    public partial class Module
    {
        public class Export
        {
            public nuint Rva { get; init; }
            public nuint Address { get; init; }
            public string DecoratedName { get; init; }
            public string UndecoratedName { get; init; }
            public string ForwarderName { get; init; }
            public int Ordinal { get; init; }
        }

        public Export[] Exports { get => GetExports(); }

        public Export[] GetExports()
        {
            var entries = Native.Module.GetExports(Base);
            var res = new Export[entries.Length];
            for (int i = 0; i < entries.Length; i++)
            {
                res[i] = new Export()
                {
                    Rva = entries[i].Rva,
                    Address = entries[i].Va,
                    DecoratedName = entries[i].DecoratedName,
                    UndecoratedName = entries[i].UndecoratedName,
                    ForwarderName = entries[i].ForwarderName,
                    Ordinal = entries[i].Ordinal,
                };
            }
            return res;
        }


    }
}
