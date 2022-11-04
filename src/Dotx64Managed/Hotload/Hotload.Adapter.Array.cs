using System;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {
        internal static object AdaptArray(Context ctx, object oldInstance, System.Type newArrayType)
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
                // Take ownership.
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

                ctx.MapReference(oldInstance, res);
            }

            return res;
        }
    }
}
