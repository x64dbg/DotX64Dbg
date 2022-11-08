using System.Collections;
using System.Collections.Generic;
using System.Reflection;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {
        private static MethodInfo GetCollectionInserterMethod(System.Type collectionType)
        {
            if (collectionType.GetGenericTypeDefinition() == typeof(Stack<>))
            {
                return collectionType.GetMethod("Push");
            }
            else if (collectionType.GetGenericTypeDefinition() == typeof(Queue<>))
            {
                return collectionType.GetMethod("Enqueue");
            }
            else if (collectionType.GetGenericTypeDefinition() == typeof(List<>))
            {
                return collectionType.GetMethod("Add");
            }
            else if (collectionType.GetGenericTypeDefinition() == typeof(HashSet<>))
            {
                return collectionType.GetMethod("Add");
            }
            else if (collectionType.GetGenericTypeDefinition() == typeof(SortedSet<>))
            {
                return collectionType.GetMethod("Add");
            }
            else
            {
                Utils.DebugPrintLine($"[Hotload] Unsupported collection type '{collectionType.FullName}', skipping.");
            }

            return null;
        }

        // Adapt a collection type that only holds values, it must have the base of IEnumerable.
        internal static object AdaptGenericList(Hotload.Context ctx, object oldInstance, System.Type newListType)
        {
            var oldList = oldInstance as IEnumerable;
            if (oldList == null)
            {
                Utils.DebugPrintLine($"[Hotload] '{newListType.FullName}' has no IEnumerable base.");
                return null;
            }

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

                var newList = newListType.MakeGenericType(newListType.GenericTypeArguments)
                    .GetConstructor(System.Type.EmptyTypes)
                    .Invoke(null);

                var inserterMethod = GetCollectionInserterMethod(newListType);
                if (inserterMethod == null)
                {
                    return null;
                }

                foreach (var entry in oldList)
                {
                    var newEntry = AdaptObject(ctx, entry, elemType, elemType);
                    inserterMethod.Invoke(newList, new object[] { newEntry });
                }

                res = newList;

                ctx.MapReference(oldInstance, res);
            }

            return res;
        }
    }
}
