using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace Dotx64Dbg
{
    public static class Utils
    {
        public static UInt32 VersionHash = 0x00000000;

        public static UInt32 GetVersionHash()
        {
            if (VersionHash != 0)
                return VersionHash;

            // Get the hash of the executing assembly
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();
            var assemblyPath = assembly.Location;
            var fileData = File.ReadAllBytes(assemblyPath);

            // Create a simple hash of all the bytes in the assembly.
            UInt32 hash = UInt32.MaxValue;
            foreach (var b in fileData)
            {
                // Rotate and xor.
                hash = (hash << 1) | (hash >> 31);
                hash ^= b;
            }

            VersionHash = hash;
            return VersionHash;
        }

        public static string GetRootPath()
        {
            var process = System.Diagnostics.Process.GetCurrentProcess();
            string fullPath = process.MainModule.FileName;
            string processPath = Path.GetDirectoryName(fullPath);
            string x64DbgPath = Path.GetFullPath(Path.Combine(processPath, ".."));
            return x64DbgPath;
        }

        // Returns the path to the folder of where this x64dbg plugin is located.
        public static string GetPluginPath()
        {
            // Get the current assembly path
            var fullPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            return Path.GetDirectoryName(fullPath);
        }

        public static string DotX64DbgNugetDepsPath => GetPluginPath();

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

        /// <summary>
        /// Replaces the contents of inputText with replacements before writing to targetFile.
        /// </summary>
        internal static bool WriteReplacedContents(string inputText, Dictionary<string, string> replacements, string targetFile)
        {
            try
            {
                foreach (var kv in replacements)
                {
                    inputText = inputText.Replace(kv.Key, kv.Value);
                }
                
                File.WriteAllText(targetFile, inputText, new UTF8Encoding(false));
            }
            catch (Exception)
            {
                return false;
            }
            return true;
        }

        internal static bool CreateDir(string path)
        {
            try
            {
                System.IO.Directory.CreateDirectory(path);
            }
            catch (Exception)
            {
                return false;
            }
            return true;
        }
    }
}
