using System;
using System.Linq;
using System.Reflection;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {
        internal static void AdaptField(Hotload.Context ctx, object oldInstance, FieldInfo oldField, object newInstance, FieldInfo newField)
        {
            var oldFieldType = oldField.FieldType;
            var newFieldType = newField.FieldType;

            var oldValue = oldField.GetValue(oldInstance);
            var newObject = AdaptObject(ctx, oldValue, oldFieldType, newFieldType);

            if (newFieldType.IsEnum)
            {
                newObject = Enum.ToObject(newFieldType, newObject);
            }

            newField.SetValue(newInstance, newObject);

            if (Nullable.GetUnderlyingType(oldFieldType) != null)
            {
                oldField.SetValue(oldInstance, null);
            }
        }

        internal static object AdaptClass(Hotload.Context ctx, object oldInstance, System.Type oldType, object newInstance, System.Type newType)
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
    }
}
