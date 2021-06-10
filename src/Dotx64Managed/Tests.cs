using System;
using System.Reflection;

namespace Dotx64Dbg
{
    partial class Tests
    {
        public void Run()
        {
            // Run all test functions within this class.
            var type = this.GetType();

            var methods = type.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.DeclaredOnly);
            foreach (var method in methods)
            {
                if (!method.Name.StartsWith("Test"))
                    continue;

                method.Invoke(this, Array.Empty<object>());
            }
        }
    }
}
