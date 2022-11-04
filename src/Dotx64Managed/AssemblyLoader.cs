using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Loader;

namespace Dotx64Dbg
{
    internal class AssemblyLoader : AssemblyLoadContext
    {
        public Assembly Current;

        public AssemblyLoader()
            : base(true)
        {
            /*
             * Some plugin dependencies don't trigger the AssemblyLoadContext.Load()
             * So we need to load any missing dependency to the app domain 'manually'
            */
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
        }

        private Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            var assemblyName = new System.Reflection.AssemblyName(args.Name);

            var extenalDll = externalAssemblies.FirstOrDefault(file => System.IO.Path.GetFileNameWithoutExtension(file)
                .Equals(assemblyName.Name, StringComparison.InvariantCultureIgnoreCase));

            if (extenalDll is not null)
            {
                externalAssemblies.Remove(extenalDll);
                return System.Reflection.Assembly.LoadFrom(extenalDll);
            }

            // If the required assembly is not in the list it's probably because it is already loaded in the current domain.
            // So as the last resource we gonna try to find it in the current domain;
            var requiredAssembly = AppDomain.CurrentDomain.GetAssemblies().FirstOrDefault(assembly => assembly.FullName == assemblyName.FullName);
            return requiredAssembly;
        }

        protected override Assembly Load(AssemblyName assemblyName)
        {
#if DEBUG
            Console.WriteLine("[DEBUG] LoaderContext.Load({0})", assemblyName.Name);
#endif
            var extenalDll = externalAssemblies.FirstOrDefault(file => System.IO.Path.GetFileNameWithoutExtension(file)
                .Equals(assemblyName.Name, StringComparison.InvariantCultureIgnoreCase));

            if (extenalDll is not null)
            {
                externalAssemblies.Remove(extenalDll);
                return Assembly.LoadFile(extenalDll);
            }

            return Assembly.Load(assemblyName); // The assembly is already loaded in the context (We hope so)
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

        public void AddExternalRequiredAssemblies(ICollection<string> assembliesPath)
        {
            var loadedAssemblies = AppDomain.CurrentDomain.GetAssemblies();
            foreach (string assemblyPath in assembliesPath)
            {
                // Filter assemblies that are already loaded
                var assemblyName = System.Reflection.AssemblyName.GetAssemblyName(assemblyPath);
                if (loadedAssemblies.Any(assembly => assembly.FullName == assemblyName.FullName))
                    continue;
                externalAssemblies.Add(assemblyPath);
            }
        }

        public bool IsLoaded()
        {
            return Current != null;
        }

        ~AssemblyLoader()
        {
            AppDomain.CurrentDomain.AssemblyResolve -= CurrentDomain_AssemblyResolve;
        }

        private HashSet<string> externalAssemblies = new();
    }
}
