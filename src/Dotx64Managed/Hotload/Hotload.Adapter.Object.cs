using System.Collections.Generic;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {
        public static object AdaptObject(Hotload.Context ctx, object oldInstance, System.Type oldType, System.Type newType)
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
            else if (newType.IsArray)
            {
                res = AdaptArray(ctx, oldInstance, newType);
            }
            else if (newType.IsClass)
            {
                if (newType.IsGenericType)
                {
                    var genericType = newType.GetGenericTypeDefinition();
                    if (genericType == typeof(List<>))
                    {
                        res = AdaptGenericList(ctx, oldInstance, newType);
                    }
                    else if (genericType == typeof(Stack<>))
                    {
                        res = AdaptGenericList(ctx, oldInstance, newType);
                    }
                    else if (genericType == typeof(HashSet<>))
                    {
                        res = AdaptGenericList(ctx, oldInstance, newType);
                    }
                    else if (genericType == typeof(SortedSet<>))
                    {
                        res = AdaptGenericList(ctx, oldInstance, newType);
                    }
                    else if (genericType == typeof(Dictionary<,>))
                    {
                        res = AdaptGenericDictionary(ctx, oldInstance, newType);
                    }
                    else if (genericType == typeof(SortedDictionary<,>))
                    {
                        res = AdaptGenericDictionary(ctx, oldInstance, newType);
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

            return res;
        }
    }
}
