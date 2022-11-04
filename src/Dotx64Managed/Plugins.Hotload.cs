using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Threading;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    class TransitionContext : IDisposable
    {
        Dictionary<object, object> ReferenceMap = new();
        List<object> NewObjects = new();
        public Assembly OldAssembly
        {
            get;
        }
        public Assembly NewAssembly
        {
            get;
        }

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
            var entries = assembly.GetTypes().Where(a => a.GetInterface(nameof(IPlugin)) != null).ToArray();
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

        object AdaptArray(TransitionContext ctx, object oldInstance, Type newArrayType)
        {
            object res;
            if (ctx.GetNewReference(oldInstance, out res))
            {
                return res;
            }

            var oldArrayType = oldInstance.GetType();
            var oldSize = oldArrayType.GetArrayRank();

            var elemType = oldArrayType.GetElementType();
            if (elemType.IsValueType || elemType.IsPrimitive)
            {
                return oldInstance;
            }
            else if (elemType.IsClass)
            {
                throw new Exception("Unsupported state transfer of nested array");
            }
            else
            {
                res = ctx.Create(newArrayType);
                var dst = (object[])res;
                var src = (object[])oldInstance;
                for (int i = 0; i < oldSize; i++)
                {
                    dst[i] = AdaptObject(ctx, src[i], elemType, elemType);
                }
            }

            return res;
        }

        object AdaptList(TransitionContext ctx, object oldInstance, Type newListType)
        {
            object res;
            if (ctx.GetNewReference(oldInstance, out res))
            {
                return res;
            }

            var elemType = newListType.GenericTypeArguments[0];
            if (elemType.IsValueType || elemType.IsPrimitive)
            {
                Utils.DebugPrintLine("[Hotload] Adapting list by move.");
                return oldInstance;
            }
            else
            {
                Utils.DebugPrintLine("[Hotload] Adapting List<> by copy.");

                var oldList = (IList)oldInstance;
                var newList = (IList)typeof(List<>)
                    .MakeGenericType(newListType.GenericTypeArguments)
                    .GetConstructor(System.Type.EmptyTypes)
                    .Invoke(null);

                foreach (var entry in oldList)
                {
                    var newEntry = AdaptObject(ctx, entry, elemType, elemType);
                    newList.Add(newEntry);
                }

                res = newList;
            }

            return res;
        }

        object AdaptDictionary(TransitionContext ctx, object oldInstance, Type newListType)
        {
            object res;
            if (ctx.GetNewReference(oldInstance, out res))
            {
                return res;
            }

            var elemKeyType = newListType.GenericTypeArguments[0];
            var elemValType = newListType.GenericTypeArguments[1];
            if ((elemKeyType.IsValueType || elemKeyType.IsPrimitive) && (elemValType.IsValueType || elemValType.IsPrimitive))
            {
                Utils.DebugPrintLine("[Hotload] Adapting Dictionary<> by move.");
                return oldInstance;
            }
            else
            {
                Utils.DebugPrintLine("[Hotload] Adapting Dictionary by copy.");

                var oldList = (IDictionary)oldInstance;
                var newList = (IDictionary)typeof(Dictionary<,>)
                    .MakeGenericType(newListType.GenericTypeArguments)
                    .GetConstructor(System.Type.EmptyTypes)
                    .Invoke(null);

                var enumerator = oldList.GetEnumerator();
                while (enumerator.MoveNext())
                {
                    var newKey = AdaptObject(ctx, enumerator.Key, elemKeyType, elemKeyType);
                    var newVal = AdaptObject(ctx, enumerator.Value, elemValType, elemValType);
                    newList.Add(newKey, newVal);
                }

                res = newList;
            }

            return res;
        }

        object AdaptObject(TransitionContext ctx, object oldInstance, Type oldType, Type newType)
        {
            if (oldInstance == null)
                return null;

            // Types from other assemblies will be moved.
            if (oldType.Assembly != ctx.OldAssembly)
            {
                return oldInstance;
            }

            if (oldType.FullName != newType.FullName)
            {
                Utils.DebugPrintLine($"[Hotload] Type mismatch '{oldType.FullName}' to '{newType.FullName}', skipping.");
                return null;
            }

            if (oldType.IsValueType && newType.IsValueType)
            {
                return oldInstance;
            }

            if (oldType.IsPrimitive && newType.IsPrimitive)
            {
                return oldInstance;
            }

            object res;
            if (ctx.GetNewReference(oldInstance, out res))
            {
                return res;
            }

            if (newType == typeof(string))
            {
                return oldInstance;
            }
            else if (newType.IsClass)
            {
                if (newType.IsGenericType)
                {
                    var genericType = newType.GetGenericTypeDefinition();
                    if (genericType == typeof(List<>))
                    {
                        res = AdaptList(ctx, oldInstance, newType);
                    }
                    else if (genericType == typeof(Dictionary<,>))
                    {
                        res = AdaptDictionary(ctx, oldInstance, newType);
                    }
                    else
                    {
                        Utils.DebugPrintLine($"[Hotload] Unsupported transition for '{oldType.FullName}', skipping.");
                    }
                    // TODO: Add more support for generic collections.
                }
                else
                {
                    res = AdaptClass(ctx, oldInstance, oldType, res, newType);
                }
            }
            else if (newType.IsArray)
            {
                res = AdaptArray(ctx, oldInstance, newType);
            }

            return res;
        }

        void AdaptField(TransitionContext ctx, object oldInstance, FieldInfo oldField, object newInstance, FieldInfo newField)
        {
            var newFieldType = newField.FieldType;
            var oldFieldType = oldField.FieldType;

            var oldValue = oldField.GetValue(oldInstance);
            var newObject = AdaptObject(ctx, oldValue, oldFieldType, newFieldType);

            newField.SetValue(newInstance, newObject);
            if (Nullable.GetUnderlyingType(oldFieldType) != null)
            {
                oldField.SetValue(oldInstance, null);
            }
        }

        object AdaptClass(TransitionContext ctx, object oldInstance, Type oldType, object newInstance, Type newType)
        {
            if (oldType.Assembly != ctx.OldAssembly)
            {
                return oldInstance;
            }

            Utils.DebugPrintLine($"[Hotload] Adapting instance of Class: {oldType.Name}");

            if (newInstance == null)
                newInstance = ctx.Create(newType);

            ctx.MapReference(oldInstance, newInstance);

            var fields = newType.GetRuntimeFields();
            foreach (var newField in fields)
            {
                Utils.DebugPrintLine($"[Hotload] Field: {newField.Name}, Type: {newField.FieldType}");

                var oldField = oldType.GetRuntimeFields().FirstOrDefault(a => a.Name == newField.Name);
                if (oldField != null)
                {
                    if (oldField.FieldType.Name == newField.FieldType.Name)
                    {
                        AdaptField(ctx, oldInstance, oldField, newInstance, newField);
                    }
                }
            }

            return newInstance;
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

        void UnloadPluginInstance(Plugin plugin, CancellationToken token, bool isReloading = false)
        {
            token.ThrowIfCancellationRequested();

            if (plugin.Instance == null)
                return;

            var pluginName = plugin.Info != null ? plugin.Info.Name : plugin.Path;
            Utils.DebugPrintLine($"Unloading plugin: {plugin.Path}");

            if (!isReloading)
            {
                plugin.Instance.Shutdown();
            }

            Commands.RemoveAllFor(plugin);
            Expressions.RemoveAllFor(plugin);
            Menus.RemoveAllFor(plugin);

            Console.WriteLine($"Unloaded plugin: {pluginName}");
        }

        void RegisterPluginCommand(Plugin plugin, MethodInfo fn, Command cmd, object obj)
        {
            Commands.Handler cb = null;

            var hasArgs = fn.GetParameters().Length > 0;

            if (fn.ReturnType == typeof(void) && hasArgs)
            {
                var cb2 = fn.CreateDelegate<Commands.HandlerVoid>(obj);
                cb = (string[] args) =>
                {
                    cb2(args);
                    return true;
                };
            }
            if (fn.ReturnType == typeof(void) && !hasArgs)
            {
                var cb2 = fn.CreateDelegate<Commands.HandlerVoidNoArgs>(obj);
                cb = (string[] args) =>
                {
                    cb2();
                    return true;
                };
            }
            else if (fn.ReturnType == typeof(bool) && !hasArgs)
            {
                var cb2 = fn.CreateDelegate<Commands.HandlerNoArgs>(obj);
                cb = (string[] args) =>
                {
                    return cb2();
                };
            }
            else if (fn.ReturnType == typeof(bool) && hasArgs)
            {
                cb = fn.CreateDelegate<Commands.Handler>(obj);
            }

            Commands.Register(plugin, cmd.Name, cmd.DebugOnly, cb);
        }

        void RegisterExpression(Plugin plugin, MethodInfo fn, Expression expr, object obj)
        {
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

            Menus.AddMenu(plugin, $"{rootMenu}/{plugin.Info.Name}/{menuPath}", cb);
        }

        void LoadPluginInstanceRecursive(Plugin plugin, object obj, HashSet<object> processed, CancellationToken token)
        {
            token.ThrowIfCancellationRequested();

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
                        LoadPluginInstanceRecursive(plugin, nextObj, processed, token);
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
                        LoadPluginInstanceRecursive(plugin, nextObj, processed, token);
                    }
                }
            }

        }

        void LoadPluginInstance(Plugin plugin, CancellationToken token)
        {
            token.ThrowIfCancellationRequested();

            if (plugin.Instance == null)
                return;

            LoadPluginInstanceRecursive(plugin, plugin.Instance, new(), token);
        }

        bool ReloadPlugin(Plugin plugin, string newAssemblyPath, CancellationToken token)
        {
            token.ThrowIfCancellationRequested();

            var hotReload = plugin.Instance != null;
            Console.WriteLine($"{(hotReload ? "Reloading" : "Loading")} '{plugin.Info.Name}'");

            try
            {
                UnloadPluginInstance(plugin, token, hotReload);

                var loader = new AssemblyLoader();
                loader.AddExternalRequiredAssemblies(plugin.ResolveDependencies(dependencyResolver, token));
                var newAssembly = loader.LoadFromFile(newAssemblyPath);

                var pluginClass = GetPluginClass(newAssembly);
                if (pluginClass != null)
                {
                    Utils.DebugPrintLine("[DEBUG] Entry class: {0}", pluginClass.Name);
                }

                // NOTE: RemapContext stores old references, to fully unload the dll
                // it must be disposed first.
                using (var ctx = new TransitionContext(plugin.Loader?.Current, newAssembly))
                {
                    var newInstance = ctx.Create(pluginClass);

                    if (hotReload)
                    {
                        AdaptClasses(ctx, plugin.Loader.Current, newAssembly);
                        AdaptClass(ctx, plugin.Instance, plugin.InstanceType, newInstance, pluginClass);
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
                                Utils.PrintException(ex);
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

                    token.ThrowIfCancellationRequested();

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
                            Utils.DebugPrintLine("WARNING: Unable to remove old assembly, ensure no references are stored.");
                        }

                        // Remove previous debug symbols.
                        // NOTE: If the debugger is attached this may be locked.
                        try
                        {
                            System.IO.File.Delete(oldPdbPath);
                        }
                        catch (Exception)
                        {
                            Utils.DebugPrintLine("WARNING: Unable to remove old PDB file, will be removed next start, probably locked by debugger.");
                        }
                    });
                }

                plugin.Loader = loader;
                plugin.AssemblyPath = newAssemblyPath;

                LoadPluginInstance(plugin, token);

                Menus.AddPluginMenu(plugin);
            }
            catch (Exception ex)
            {
                Utils.PrintException(ex);
                return false;
            }

            Console.WriteLine($"{(hotReload ? "Reloaded" : "Loaded")} '{plugin.Info.Name}'");
            return true;
        }

        public void UnloadPlugin(Plugin plugin, CancellationToken token = default(CancellationToken))
        {
            if (plugin.Instance != null)
            {
                UnloadPluginInstance(plugin, token);
                plugin.Instance = null;
            }

            if (plugin.Loader != null)
            {
                plugin.Loader.UnloadCurrent();
                plugin.Loader = null;
            }

            plugin.RequiresRebuild = false;
        }

    }
}
