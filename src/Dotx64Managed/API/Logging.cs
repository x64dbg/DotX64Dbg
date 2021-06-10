using System.Linq;

namespace Dotx64Dbg
{
    public static class Logging
    {
        static object TransformArg(object arg)
        {
            if (arg == null)
                return "null";

            if (arg is byte[] bytes)
            {
                string joinedBytes = string.Join(", ", bytes.Select(b => string.Format("0x{0:X2}", b)));
                return $"new byte[] {{ {joinedBytes} }}";
            }

            return arg;
        }

        static object[] TransformArgs(object[] args)
        {
            object[] res = new object[args.Length];
            for (int i = 0; i < args.Length; i++)
            {
                res[i] = TransformArg(args[i]);
            }
            return res;
        }

        public static void Write(string line)
        {
            Native.Logging.Write(line);
        }

        public static void Write(string line, params object[] args)
        {
            string fmt = string.Format(line, TransformArgs(args));
            Native.Logging.Write(fmt);
        }

        public static void WriteLine(string line)
        {
            Native.Logging.WriteLine(line);
        }

        public static void WriteLine(string line, params object[] args)
        {
            string fmt = string.Format(line, TransformArgs(args));
            Native.Logging.WriteLine(fmt);
        }
    }
}
