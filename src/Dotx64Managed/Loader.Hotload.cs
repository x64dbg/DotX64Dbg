using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Loader;
using System.Runtime.Serialization;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    internal class LoaderContext : AssemblyLoadContext
    {
        public Assembly Current;

        public LoaderContext()
            : base(true)
        {
        }

        protected override Assembly Load(AssemblyName assemblyName)
        {
            Logging.WriteLine("LoaderContext.Load({0})", assemblyName.Name);
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

    class TransitionContext : IDisposable
    {
        Dictionary<object, object> ReferenceMap = new();
        List<object> NewObjects = new();

        public void Dispose()
        {
            ReferenceMap.Clear();
            ReferenceMap = null;
        }

        public object Create(Type type)
        {
            var obj = FormatterServices.GetUninitializedObject(type);
            NewObjects.Add(obj);
            return obj;
        }

        public bool GetNewReference(object oldObj, out object newObj)
        {
            return ReferenceMap.TryGetValue(oldObj, out newObj);
        }

        public void MapReference(object oldObj, object newObj)
        {
            ReferenceMap.Add(oldObj, newObj);
        }

        public object[] GetObjectsWithInterface(Type type)
        {
            var res = NewObjects.Where(a => a.GetType().GetInterface(type.Name) != null).ToArray();
            return res;
        }
    }

    internal partial class Loader
    {
        Type GetPluginClass(Assembly assembly)
        {
            var entries = assembly.GetTypes().Where(a => a.GetInterface("IPlugin") != null).ToArray();
            if (entries.Length > 1)
            {
                throw new Exception("Assembly has multiple classes with IPlugin, can have only one entry.");
            }
            if (entries.Length == 0)
            {
                throw new Exception("Assembly has no IPlugin class.");
            }
            return entries.First();
        }

        void AdaptField(TransitionContext ctx, object oldInstance, FieldInfo oldField, object newInstance, FieldInfo newField)
        {
            var oldValue = oldField.GetValue(oldInstance);
            if (newField.FieldType.IsValueType)
            {
                newField.SetValue(newInstance, oldValue);
            }
            else if (newField.FieldType.IsPrimitive)
            {
                newField.SetValue(newInstance, oldValue);
            }
            else if (newField.FieldType.IsClass)
            {
                object newValue;

                if (!ctx.GetNewReference(oldValue, out newValue))
                {
                    newValue = ctx.Create(newField.FieldType);
                    AdaptInstance(ctx, oldValue, oldField.FieldType, newValue, newField.FieldType);
                }

                newField.SetValue(newInstance, newValue);
            }
        }

        void AdaptInstance(TransitionContext ctx, object oldInstance, Type oldType, object newInstance, Type newType)
        {
            ctx.MapReference(oldInstance, newInstance);

            var fields = newType.GetRuntimeFields();
            foreach (var newField in fields)
            {
                var oldField = oldType.GetRuntimeFields().FirstOrDefault(a => a.Name == newField.Name);
                if (oldField == null)
                    continue;

                AdaptField(ctx, oldInstance, oldField, newInstance, newField);
            }
        }

        void ReloadPlugin(Plugin plugin, string newAssemblyPath)
        {
            Logging.WriteLine("Reloading '{0}'", plugin.Info.Name);

            try
            {
                var loader = new LoaderContext();
                var newAssembly = loader.LoadFromFile(newAssemblyPath);

                var pluginClass = GetPluginClass(newAssembly);
                if (pluginClass != null)
                {
                    Logging.WriteLine("Entry class: {0}", pluginClass.Name);
                }

                // NOTE: RemapContext stores old references, to fully unload the dll
                // it must be disposed first.
                using (var ctx = new TransitionContext())
                {
                    var newInstance = ctx.Create(pluginClass);
                    var hotReload = false;

                    if (plugin.Instance != null)
                    {
                        AdaptInstance(ctx, plugin.Instance, plugin.InstanceType, newInstance, pluginClass);

                        plugin.Instance = newInstance as IPlugin;
                        plugin.InstanceType = pluginClass;
                        hotReload = true;
                    }
                    else
                    {
                        // Initial startup.
                        var ctor = pluginClass.GetConstructor(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic, null, Array.Empty<Type>(), null);
                        if (ctor != null)
                        {
                            ctor.Invoke(newInstance, Array.Empty<object>());
                        }

                        var startup = pluginClass.GetMethod("Startup");
                        if (startup != null)
                        {
                            startup.Invoke(newInstance, Array.Empty<object>());
                        }
                    }

                    plugin.Instance = newInstance as IPlugin;
                    plugin.InstanceType = pluginClass;

                    if (hotReload)
                    {
                        var reloadables = ctx.GetObjectsWithInterface(typeof(IHotload));
                        foreach (var obj in reloadables)
                        {
                            var reloadable = obj as IHotload;
                            reloadable.OnHotload();
                        }
                    }
                }


                if (plugin.Loader != null)
                {
                    var cur = plugin.Loader;
                    plugin.Loader = null;

                    var oldAssemblyPath = plugin.AssemblyPath;
                    var oldPdbPath = oldAssemblyPath.Replace(".dll", ".pdb");

                    cur.UnloadCurrent();
                    cur = null;

                    for (int i = 0; i < 50; i++)
                    {
                        GC.Collect();
                        GC.WaitForPendingFinalizers();
                    }

                    Task.Run(async delegate
                    {
                        bool removed = false;
                        await Task.Delay(2000);
                        try
                        {
                            System.IO.File.Delete(oldAssemblyPath);
                            removed = true;
                            System.IO.File.Delete(oldPdbPath);
                        }
                        catch (Exception)
                        {
                            if (!removed)
                                Logging.WriteLine("WARNING: Unable to remove old assembly, ensure no references are stored.");
                        }
                    });
                }

                plugin.Loader = loader;
                plugin.AssemblyPath = newAssemblyPath;
            }
            catch (System.Exception ex)
            {
                Logging.WriteLine("Exception: {0}", ex.ToString());
                return;
            }

            Logging.WriteLine("Reloaded '{0}'", plugin.Info.Name);
        }

        IPlugin CreatePluginInstance(Plugin plugin)
        {
            return null;
        }

        void UnloadPlugin(Plugin plugin)
        {

        }


    }
}
