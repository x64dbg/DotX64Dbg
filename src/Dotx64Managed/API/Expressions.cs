using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace Dotx64Dbg
{
    /// <summary>
    /// Expression attribute to dynamically register expression functions in x64Dbg.
    /// </summary>
    public class Expression : Attribute
    {
        /// <summary>
        /// Name of the command.
        /// </summary>
        public string Name { get; internal set; }

        /// <summary>
        /// Default constructor.
        /// </summary>
        public Expression(string Name)
        {
            this.Name = Name;
        }
    }

    public static class Expressions
    {
        internal struct ExpressionInfo
        {
            public Plugin plugin;
        }

        internal static Dictionary<string, ExpressionInfo> Registered;

        internal static void Initialize()
        {
            Registered = new();
        }

        /// <summary>
        /// Evaluates the given expression and results the evaluated value.
        /// </summary>
        /// <param name="expr">Expression</param>
        /// <param name="value">Resulting value</param>
        /// <returns>True on success, false in case of errors</returns>
        /// <example>
        /// <code>
        /// ulong val = 0;
        /// if(Expression.TryEvaluate("rip", val)) { Console.WriteLine("Value of rip {0}", val); }
        /// </code>
        /// </example>
        public static bool TryEvaluate(string expr, out ulong value)
        {
            return Native.Expressions.TryEvaluate(expr, out value);
        }

        /// <summary>
        /// Same as TryEvaluate except the function throws if the expression is invalid.
        /// </summary>
        /// <see cref="TryEvaluate"/>
        public static ulong Evaluate(string expr)
        {
            return Native.Expressions.Evaluate(expr);
        }

        /// <summary>
        /// Formats the given the expression and results the formatted string.
        /// </summary>
        /// <param name="expr">Expression to format</param>
        /// <param name="value">Resulting formatted expression</param>
        /// <returns>True on success, false in case of any errors</returns>
        /// <example>
        /// <code>
        /// string formatted;
        /// if(Expression.TryFormat("rip = {rip}", formatted)) { Console.WriteLine("Formatted: {0}", formatted); }
        /// </code>
        /// </example>
        public static bool TryFormat(string expr, out string value)
        {
            return Native.Expressions.TryFormat(expr, out value);
        }

        /// <summary>
        /// Same as TryFormat except the function throws if the expression is invalid.
        /// </summary>
        /// <see cref="TryFormat"/>
        public static string Format(string expr)
        {
            return Native.Expressions.Format(expr);
        }

        /// <summary>
        /// Checks if the provided expression is valid.
        /// </summary>
        /// <param name="expr">Expression to validate</param>
        /// <returns>True if the expression is valid, false in case of errors</returns>
        public static bool IsValidExpression(string expr)
        {
            return Native.Expressions.IsValidExpression(expr);
        }

        public delegate nuint ExpressionFunc0();
        public delegate nuint ExpressionFunc1(nuint a);
        public delegate nuint ExpressionFunc2(nuint a, nuint b);
        public delegate nuint ExpressionFunc3(nuint a, nuint b, nuint c);

        internal static int PointerSize = Marshal.SizeOf(typeof(System.IntPtr));

        internal static void Register(Plugin plugin, string name)
        {
            var info = new ExpressionInfo()
            {
                plugin = plugin
            };
            Registered.Add(name, info);
        }

        internal static bool Register(Plugin plugin, string name, ExpressionFunc0 func)
        {
            var registered = Native.Expressions.RegisterExpression(Manager.PluginHandle, name, 0, delegate (int argc, System.IntPtr argv, System.IntPtr x)
            {
                var res = func();
                return (System.UIntPtr)res;
            });
            if (registered)
            {
                Register(plugin, name);
            }
            return registered;
        }

        internal static bool Register(Plugin plugin, string name, ExpressionFunc1 func)
        {
            var registered = Native.Expressions.RegisterExpression(Manager.PluginHandle, name, 1, delegate (int argc, System.IntPtr argv, System.IntPtr x)
            {
                var arg0 = (ulong)Marshal.ReadIntPtr(argv, 0 * PointerSize);
                return func((nuint)arg0);
            });
            if (registered)
            {
                Register(plugin, name);
            }
            return registered;
        }

        internal static bool Register(Plugin plugin, string name, ExpressionFunc2 func)
        {
            var registered = Native.Expressions.RegisterExpression(Manager.PluginHandle, name, 2, delegate (int argc, System.IntPtr argv, System.IntPtr x)
            {
                var arg0 = (ulong)Marshal.ReadIntPtr(argv, 0 * PointerSize);
                var arg1 = (ulong)Marshal.ReadIntPtr(argv, 1 * PointerSize);
                return func((nuint)arg0, (nuint)arg1);
            });
            if (registered)
            {
                Register(plugin, name);
            }
            return registered;
        }

        internal static bool Register(Plugin plugin, string name, ExpressionFunc3 func)
        {
            var registered = Native.Expressions.RegisterExpression(Manager.PluginHandle, name, 3, delegate (int argc, System.IntPtr argv, System.IntPtr x)
            {
                var arg0 = (ulong)Marshal.ReadIntPtr(argv, 0 * PointerSize);
                var arg1 = (ulong)Marshal.ReadIntPtr(argv, 1 * PointerSize);
                var arg2 = (ulong)Marshal.ReadIntPtr(argv, 2 * PointerSize);
                return func((nuint)arg0, (nuint)arg1, (nuint)arg2);
            });
            if (registered)
            {
                Register(plugin, name);
            }
            return registered;
        }

        internal static bool Remove(string name)
        {
            if (!Registered.ContainsKey(name))
            {
                return false;
            }
            Registered.Remove(name);
            return Native.Expressions.UnregisterExpression(Manager.PluginHandle, name);
        }

        internal static bool RemoveAllFor(Plugin plugin)
        {
            Registered.Where(x => x.Value.plugin == plugin)
                .Select(x => x.Key)
                .ToList()
                .ForEach(name =>
            {
                Remove(name);
            });

            return true;
        }
    }
}