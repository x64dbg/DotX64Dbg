using System.Diagnostics;
using System.IO;

namespace Dotx64Dbg
{
    class Utils
    {
        public static string GetRootPath()
        {
            var process = Process.GetCurrentProcess();
            string fullPath = process.MainModule.FileName;
            string processPath = Path.GetDirectoryName(fullPath);
            string x64DbgPath = Path.GetFullPath(Path.Combine(processPath, ".."));
            return x64DbgPath;
        }
    }
}
