using System;
using System.Diagnostics;
using System.IO;

namespace Dotx64Dbg
{
    public static class Utils
    {
        public static string GetRootPath()
        {
            var process = Process.GetCurrentProcess();
            string fullPath = process.MainModule.FileName;
            string processPath = Path.GetDirectoryName(fullPath);
            string x64DbgPath = Path.GetFullPath(Path.Combine(processPath, ".."));
            return x64DbgPath;
        }

        public static void PrintFields(object obj)
        {
            var typeInfo = obj.GetType();
            var typeName = typeInfo.Name;

            Console.WriteLine($"Event {typeName} = {{");

            var typeData = typeInfo.GetFields();
            foreach (var field in typeData)
            {
                Console.WriteLine("  .{0} = {1}", field.Name, field.GetValue(obj));
            }

            Console.WriteLine("}");
        }
    }
}
