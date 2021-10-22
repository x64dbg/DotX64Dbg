using System;
using System.Diagnostics;
using System.IO;

namespace Dotx64Dbg
{
    public static class Utils
    {
        public static string GetRootPath()
        {
            var process = System.Diagnostics.Process.GetCurrentProcess();
            string fullPath = process.MainModule.FileName;
            string processPath = Path.GetDirectoryName(fullPath);
            string x64DbgPath = Path.GetFullPath(Path.Combine(processPath, ".."));
            return x64DbgPath;
        }

        public static void PrintFields(object obj)
        {
            var typeInfo = obj.GetType();
            var typeName = typeInfo.Name;

            Console.WriteLine($"{typeName} = {{");

            var typeData = typeInfo.GetFields();
            foreach (var field in typeData)
            {
                Console.WriteLine("  .{0} = {1}", field.Name, field.GetValue(obj));
            }

            Console.WriteLine("}");
        }

        internal static string GetExceptionMessage(Exception ex)
        {
            return ex.ToString();
        }

        internal static void PrintException(Exception ex)
        {
            ex = ex.InnerException ?? ex;
            Console.WriteLine($"Exception: {GetExceptionMessage(ex)}");
        }

        internal static string ReadFileContents(string path, int retryAttempts = 5, int retryTime = 100)
        {
            string res = null;
            for (int i = 0; i < retryAttempts; i++)
            {
                try
                {
                    using (var fs = File.OpenText(path))
                    {
                        res = fs.ReadToEnd();
                        break;
                    }
                }
                catch (Exception)
                {
                    System.Threading.Thread.Sleep(retryTime);
                    continue;
                }
            }
            return res;
        }

        [Conditional("DEBUG")]
        internal static void DebugPrintLine(string fmt, params object[] args)
        {
            string strOut = string.Format(fmt, args);
            Console.WriteLine($"[DEBUG] {strOut}");
        }

        [Conditional("DEBUG")]
        internal static void DebugPrintLine(string line)
        {
            Console.WriteLine($"[DEBUG] {line}");
        }
    }
}
