using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    public static partial class UI
    {
        /// <summary>
        /// Adding this attribute to functions dynamically registers a new menu.
        /// </summary>
        /// <remarks>
        /// Menus that have children can not be clicked.
        /// </remarks>
        public class Menu : Attribute
        {
            public enum Root
            {
                Disassembly,
                Dump,
                Stack,
                MemoryMap,
            }

            public string Path { get; init; }

            public Root Parent { get; init; }

            /// <summary>
            /// Adding this attribute to functions dynamically registers a new menu.
            /// </summary>
            /// <param name="parent">One of the root menus such as Disassembly or Stack</param>
            /// <param name="path">This must be a path such as "My Menu" or "Sub Menus/Entry"</param>
            /// <remarks>
            /// Menus that have children can not be clicked.
            /// </remarks>
            public Menu(Root parent, string path)
            {
                Path = path;
                Parent = parent;
            }

            internal struct Id
            {
                int Value { get; init; }

                public static implicit operator Id(int id)
                {
                    return new Id { Value = id };
                }

                public static implicit operator int(Id id)
                {
                    return id.Value;
                }
            }

            public delegate void MenuDelegate();
        }
    }
}