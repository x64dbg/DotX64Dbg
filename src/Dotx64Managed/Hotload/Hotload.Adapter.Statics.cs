using System.Reflection;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {
        internal static void AdaptStatics(Hotload.Context ctx, Assembly oldAssembly, Assembly newAssembly)
        {
            foreach (var newType in newAssembly.GetTypes())
            {
                if (!newType.IsClass)
                    continue;

                // TODO: Fix all statics.
            }
        }
    }
}
