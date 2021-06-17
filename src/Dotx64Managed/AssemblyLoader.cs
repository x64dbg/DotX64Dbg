using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Loader;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    internal class AssemblyLoader : AssemblyLoadContext
    {
        public Assembly Current;

        public AssemblyLoader()
            : base(true)
        {
        }

        protected override Assembly Load(AssemblyName assemblyName)
        {
#if DEBUG
            Console.WriteLine("[DEBUG] LoaderContext.Load({0})", assemblyName.Name);
#endif
            return Assembly.Load(assemblyName);
        }

        public Assembly LoadFromFile(string path)
        {
            Current = LoadFromAssemblyPath(path);
            return Current;
        }

        public bool UnloadCurrent()
        {
            if (Current == null)
                return false;

            Unload();
            Current = null;

            return true;
        }

        public bool IsLoaded()
        {
            return Current != null;
        }
    }
}
