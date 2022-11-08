using System.Collections;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {

        internal static object AdaptGenericDictionary(Hotload.Context ctx, object oldInstance, System.Type newListType)
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
                var newList = (IDictionary)newListType.MakeGenericType(newListType.GenericTypeArguments)
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

                ctx.MapReference(oldInstance, res);
            }

            return res;
        }
    }
}
