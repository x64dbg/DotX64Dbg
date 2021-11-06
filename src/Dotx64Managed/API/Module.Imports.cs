namespace Dotx64Dbg
{
    /// <summary>
    /// Object that represents a module in the debugged process.
    /// </summary>
    public partial class Module
    {
        public class Import
        {
            public nuint Rva { get; init; }
            public nuint Address { get; init; }
            public string DecoratedName { get; init; }
            public string UndecoratedName { get; init; }
            public int Ordinal { get; init; }
        }

        public Import[] Imports { get => GetImports(); }

        public Import[] GetImports()
        {
            var entries = Native.Module.GetImports(Base);
            var res = new Import[entries.Length];
            for (int i = 0; i < entries.Length; i++)
            {
                res[i] = new Import()
                {
                    Rva = entries[i].Rva,
                    Address = entries[i].Va,
                    DecoratedName = entries[i].DecoratedName,
                    UndecoratedName = entries[i].UndecoratedName,
                    Ordinal = entries[i].Ordinal,
                };
            }
            return res;
        }


    }
}
