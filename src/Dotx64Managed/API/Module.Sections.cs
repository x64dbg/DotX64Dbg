namespace Dotx64Dbg
{
    /// <summary>
    /// Object that represents a module in the debugged process.
    /// </summary>
    public partial class Module
    {
        public class Section
        {
            public string Name { get; init; }
            public nuint Address { get; init; }
            public nuint Size { get; init; }
        }

        public int SectionCount { get => GetSectionCount(); }

        public Section[] Sections { get => GetSections(); }

        public int GetSectionCount()
        {
            return Native.Module.GetSectionCount(Base);
        }

        public Section GetSection(int index)
        {
            var sect = Native.Module.GetSection(Base, index);
            return new Section()
            {
                Name = sect.Name,
                Address = (nuint)sect.Address,
                Size = (nuint)sect.Size
            };
        }

        public Section[] GetSections()
        {
            var res = new Section[SectionCount];
            for (int i = 0; i < SectionCount; i++)
            {
                res[i] = GetSection(i);
            }
            return res;
        }


    }
}
