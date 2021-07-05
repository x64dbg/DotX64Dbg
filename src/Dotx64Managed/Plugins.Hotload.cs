using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Loader;
using System.Runtime.Serialization;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    class TransitionContext : IDisposable
    {
        Dictionary<object, object> ReferenceMap = new();
        List<object> NewObjects = new();
        public Assembly OldAssembly { get; }
        public Assembly NewAssembly { get; }

        public TransitionContext(Assembly oldAssembly, Assembly newAssembly)
        {
            OldAssembly = oldAssembly;
            NewAssembly = newAssembly;
        }

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

    internal partial class Plugins
    {
        internal bool IsSystemType(Type t)
        {
            return false;
        }

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
            var newFieldType = newField.FieldType;
            var oldFieldType = oldField.FieldType;

            var oldValue = oldField.GetValue(oldInstance);
            if (oldValue == null)
            {
                newField.SetValue(newInstance, null);
            }
            else if (newFieldType.IsValueType)
            {
                newField.SetValue(newInstance, oldValue);
            }
            else if (newFieldType.IsPrimitive)
            {
                newField.SetValue(newInstance, oldValue);
            }
            else if (newFieldType.IsArray)
            {
                var elemType = newField.FieldType.GetElementType();
                if (elemType.IsValueType)
                {
                    newField.SetValue(newInstance, oldValue);
                }
                else if (elemType.IsClass)
                {
                    throw new Exception("Unsupported state transfer of nested array");
                }
                else
                {
                    // TODO: Iterate and swap everything.
                    object newValue;
                    if (!ctx.GetNewReference(oldValue, out newValue))
                    {
                        newValue = ctx.Create(newField.FieldType);
                        AdaptInstance(ctx, oldValue, oldField.FieldType, newValue, newField.FieldType);
                    }
                }
            }
            else if (newField.FieldType.IsClass)
            {
                if (newFieldType.IsGenericType && newFieldType.GetGenericTypeDefinition() == typeof(List<>) &&
                    oldFieldType.IsGenericType && oldFieldType.GetGenericTypeDefinition() == typeof(List<>))
                {
                    var newListType = newFieldType.GenericTypeArguments[0];
                    var oldListType = oldFieldType.GenericTypeArguments[0];
                    if (newListType.IsValueType)
                    {
                        // Swap
                        newField.SetValue(newInstance, oldValue);
                        oldField.SetValue(oldInstance, null);
                    }
                    else if (newListType.IsClass)
                    {
                        var oldList = (IList)oldValue;
                        var newList = (IList)typeof(List<>)
                            .MakeGenericType(newListType)
                            .GetConstructor(System.Type.EmptyTypes)
                            .Invoke(null);

                        foreach (var oldListEntry in oldList)
                        {
                            object newValue;
                            if (!ctx.GetNewReference(oldValue, out newValue))
                            {
                                newValue = ctx.Create(newListType);
                                AdaptInstance(ctx, oldListEntry, oldListType, newValue, newListType);
                            }

                            newList.Add(newValue);
                        }
                        newField.SetValue(newInstance, newList);
                    }
                }
                else if (newFieldType == typeof(Type))
                {
                    // Lookup the new type info.
                    var typeInfo = oldValue as Type;
                    if (typeInfo.Assembly == ctx.OldAssembly)
                    {
                        // From plugin assembly.
                        var types = ctx.NewAssembly.GetTypes();
                        var newTypeInfo = Array.Find(types, x => x.FullName == typeInfo.FullName);
                        newField.SetValue(newInstance, newTypeInfo);
                    }
                    else
                    {
                        // External, swap.
                        newField.SetValue(newInstance, oldValue);
                        oldField.SetValue(oldInstance, null);

                    }
                }
                else if (newFieldType == typeof(System.Object) && oldValue.GetType().IsValueType)
                {
                    newField.SetValue(newInstance, oldValue);
                }
                else if (newFieldType == typeof(string))
                {
                    newField.SetValue(newInstance, oldValue);
                    oldField.SetValue(oldInstance, null);
                }
                else
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
        }

        void AdaptInstance(TransitionContext ctx, object oldInstance, Type oldType, object newInstance, Type newType)
        {
            if (oldType.Assembly != ctx.OldAssembly)
                return;

#if DEBUG
            Console.WriteLine($"[DEBUG] Adapting instance of Class: {oldType.Name}");
#endif

            ctx.MapReference(oldInstance, newInstance);

            var fields = newType.GetRuntimeFields();
            foreach (var newField in fields)
            {
#if DEBUG
                Console.WriteLine($"[DEBUG] Field: {newField.Name}, Type: {newField.FieldType}");
#endif
                var oldField = oldType.GetRuntimeFields().FirstOrDefault(a => a.Name == newField.Name);
                if (oldField != null)
                {
                    if (oldField.FieldType.Name == newField.FieldType.Name)
                    {
                        AdaptField(ctx, oldInstance, oldField, newInstance, newField);
                    }
                }

            }
        }
        void AdaptClasses(TransitionContext ctx, Assembly oldAssembly, Assembly newAssembly)
        {
            foreach (var newType in newAssembly.GetTypes())
            {
                if (!newType.IsClass)
                    continue;

                // TODO: Fix all statics.
            }
        }

        void UnloadPluginInstanceRecursive(Plugin plugin, object obj, HashSet<object> processed)
        {
            if (obj == null)
                return;

            if (obj.GetType().Assembly != plugin.Loader.Current)
                return;

            processed.Add(obj);

            var instType = obj.GetType();

            var fields = instType.GetRuntimeFields();
            foreach (var field in fields)
            {
                var fieldType = field.FieldType;
                if (IsSystemType(field.FieldType))
                    continue;

                if (fieldType.IsClass && !fieldType.IsArray)
                {
                    var nextObj = field.GetValue(obj);
                    if (!processed.Contains(nextObj))
                        UnloadPluginInstanceRecursive(plugin, nextObj, processed);
                }
            }

            var props = instType.GetRuntimeProperties();
            foreach (var prop in props)
            {
                var fieldType = prop.PropertyType;
                if (IsSystemType(fieldType))
                    continue;
                if (prop.GetIndexParameters().Count() > 0)
                    continue;
                if (fieldType.IsClass && !fieldType.IsArray)
                {
                    var nextObj = prop.GetValue(obj);
                    if (!processed.Contains(nextObj))
                        UnloadPluginInstanceRecursive(plugin, nextObj, processed);
                }
            }
        }

        void UnloadPluginInstance(Plugin plugin)
        {
            if (plugin.Instance == null)
                return;

            if (Canceller.IsCancellationRequested)
                return;

            UnloadPluginInstanceRecursive(plugin, plugin.Instance, new());

            Commands.RemoveAllFor(plugin);
            Expressions.RemoveAllFor(plugin);
            Menus.RemoveAllFor(plugin);
        }

        void RegisterPluginCommand(Plugin plugin, MethodInfo fn, Command cmd, object obj)
        {
            if (Canceller.IsCancellationRequested)
                return;

            Commands.Handler cb = null;

            if (fn.ReturnType == typeof(void))
            {
                var cb2 = fn.CreateDelegate<Commands.HandlerVoid>(obj);
                cb = (string[] args) =>
                {
                    cb2(args);
                    return true;
                };
            }
            else if (fn.ReturnType == typeof(bool))
            {
                cb = fn.CreateDelegate<Commands.Handler>(obj);
            }

            if (!Canceller.IsCancellationRequested)
                Commands.Register(plugin, cmd.Name, cmd.DebugOnly, cb);
        }

        void RegisterExpression(Plugin plugin, MethodInfo fn, Expression expr, object obj)
        {
            if (Canceller.IsCancellationRequested)
                return;

            if (fn.ReturnType != typeof(nuint))
            {
                throw new Exception($"Expression functions must return 'nuint', Function: {fn.Name}");
            }

            var args = fn.GetParameters();
            foreach (var arg in args)
            {
                if (arg.ParameterType != typeof(nuint))
                {
                    throw new Exception($"Expression arguments must be 'nuint', Function: {fn.Name}");
                }
            }

            if (args.Length == 0)
            {
                var cb = fn.CreateDelegate<Expressions.ExpressionFunc0>(obj);
                Expressions.Register(plugin, expr.Name, cb);
            }
            else if (args.Length == 1)
            {
                var cb = fn.CreateDelegate<Expressions.ExpressionFunc1>(obj);
                Expressions.Register(plugin, expr.Name, cb);
            }
            else if (args.Length == 2)
            {
                var cb = fn.CreateDelegate<Expressions.ExpressionFunc2>(obj);
                Expressions.Register(plugin, expr.Name, cb);
            }
            else if (args.Length == 3)
            {
                var cb = fn.CreateDelegate<Expressions.ExpressionFunc3>(obj);
                Expressions.Register(plugin, expr.Name, cb);
            }
        }

        void RegisterMenu(Plugin plugin, MethodInfo fn, UI.Menu menu, object obj)
        {
            var cb = fn.CreateDelegate<UI.Menu.MenuDelegate>(obj);

            var menuPath = menu.Path;
            var rootMenu = menu.Parent.ToString();

            Menus.Register(plugin, $"{rootMenu}/{plugin.Info.Name}/{menuPath}", cb);
        }

        void LoadPluginInstanceRecursive(Plugin plugin, object obj, HashSet<object> processed)
        {
            if (Canceller.IsCancellationRequested)
                return;

            if (obj == null)
                return;

            if (obj.GetType().Assembly != plugin.Loader.Current)
                return;

            processed.Add(obj);

            var instType = obj.GetType();
            var funcs = instType.GetRuntimeMethods();

            foreach (var fn in funcs)
            {
                var attribs = fn.GetCustomAttributes();
                foreach (var attrib in attribs)
                {
                    if (attrib is Command cmd)
                    {
                        RegisterPluginCommand(plugin, fn, cmd, obj);
                    }
                    else if (attrib is Expression expr)
                    {
                        RegisterExpression(plugin, fn, expr, obj);
                    }
                    else if (attrib is UI.Menu menu)
                    {
                        RegisterMenu(plugin, fn, menu, obj);
                    }
                }
            }

            var fields = instType.GetRuntimeFields();
            foreach (var field in fields)
            {
                var fieldType = field.FieldType;
                if (IsSystemType(fieldType))
                    continue;

                if (fieldType.IsClass && !fieldType.IsArray)
                {
                    var nextObj = field.GetValue(obj);
                    if (!processed.Contains(nextObj))
                    {
                        LoadPluginInstanceRecursive(plugin, nextObj, processed);
                    }
                }
            }

            var props = instType.GetRuntimeProperties();
            foreach (var prop in props)
            {
                var fieldType = prop.PropertyType;
                if (IsSystemType(fieldType))
                    continue;
                if (prop.GetIndexParameters().Count() > 0)
                    continue;

                if (fieldType.IsClass && !fieldType.IsArray)
                {
                    var nextObj = prop.GetValue(obj);
                    if (!processed.Contains(nextObj))
                    {
                        LoadPluginInstanceRecursive(plugin, nextObj, processed);
                    }
                }
            }

        }

        void LoadPluginInstance(Plugin plugin)
        {
            if (Canceller.IsCancellationRequested)
                return;

            if (plugin.Instance == null)
                return;

            LoadPluginInstanceRecursive(plugin, plugin.Instance, new());
        }

        void ReloadPlugin(Plugin plugin, string newAssemblyPath)
        {
            if (Canceller.IsCancellationRequested)
                return;

            var isReload = plugin.Instance != null;
            Console.WriteLine($"{(isReload ? "Reloading" : "Loading")} '{plugin.Info.Name}'");

            try
            {
                UnloadPluginInstance(plugin);

                var loader = new AssemblyLoader();
                var newAssembly = loader.LoadFromFile(newAssemblyPath);

                var pluginClass = GetPluginClass(newAssembly);
                if (pluginClass != null)
                {
#if DEBUG
                    Console.WriteLine("[DEBUG] Entry class: {0}", pluginClass.Name);
#endif
                }

                // NOTE: RemapContext stores old references, to fully unload the dll
                // it must be disposed first.
                using (var ctx = new TransitionContext(plugin.Loader?.Current, newAssembly))
                {
                    var newInstance = ctx.Create(pluginClass);
                    var hotReload = false;

                    if (plugin.Instance != null)
                    {
                        AdaptClasses(ctx, plugin.Loader.Current, newAssembly);
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
                            try
                            {
                                startup.Invoke(newInstance, Array.Empty<object>());
                            }
                            catch (Exception ex)
                            {
                                throw;
                            }
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

                    Canceller.Token.ThrowIfCancellationRequested();

                    Task.Run(async delegate
                    {
                        await Task.Delay(2000);

                        // Remove previous assembly.
                        try
                        {
                            System.IO.File.Delete(oldAssemblyPath);
                        }
                        catch (Exception)
                        {
#if DEBUG
                            Console.WriteLine("WARNING: Unable to remove old assembly, ensure no references are stored.");
#endif
                        }

                        // Remove previous debug symbols.
                        // NOTE: If the debugger is attached this may be locked.
                        try
                        {
                            System.IO.File.Delete(oldPdbPath);
                        }
                        catch (Exception)
                        {
#if DEBUG
                            Console.WriteLine("WARNING: Unable to remove old PDB file, will be removed next start, probably locked by debugger.");
#endif
                        }
                    });
                }

                plugin.Loader = loader;
                plugin.AssemblyPath = newAssemblyPath;

                LoadPluginInstance(plugin);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: {0}", ex.ToString());
                return;
            }

            if (Canceller.IsCancellationRequested)
                return;

            Console.WriteLine($"{(isReload ? "Reloaded" : "Loaded")} '{plugin.Info.Name}'");
        }

    }
}
