using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;

namespace Dotx64Dbg
{
    internal partial class Hotload
    {
        internal class Context : IDisposable
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

            public Context(Assembly oldAssembly, Assembly newAssembly)
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
    }
}
