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

            var oldElemType = oldArrayType.GetElementType();
            var newElemType = newArrayType.GetElementType();
            if (oldElemType.IsValueType || oldElemType.IsPrimitive)
            {
                // Take ownership.
                return oldInstance;
            }
            else
            {
                var src = oldInstance as System.Array;
                var dst = ctx.CreateArray(newArrayType.GetElementType(), src.Length) as System.Array;
                for (int i = 0; i < src.Length; i++)
                {
                    var oldEntry = src.GetValue(i);
                    var newObj = AdaptObject(ctx, oldEntry, oldElemType, newElemType);
                    dst.SetValue(newObj, i);
                }

                res = dst;
                ctx.MapReference(oldInstance, res);
            }

            return res;
        }
    }
}
