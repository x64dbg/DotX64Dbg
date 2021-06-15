using System;
using System.IO;
using System.Text;

namespace Dotx64Dbg
{
    class ConsoleWriter : TextWriter
    {
        public override Encoding Encoding { get { return Encoding.UTF8; } }

        public override void Write(string value)
        {
            Native.Logging.Write(value);
        }

        public override void WriteLine(string value)
        {
            Native.Logging.WriteLine(value);
        }
        public override void WriteLine()
        {
            Native.Logging.WriteLine();
        }
    }

    public static class Logging
    {
        internal static void Initialize()
        {
            var sink = new ConsoleWriter();
            Console.SetOut(sink);
            Console.SetError(sink);
        }
    }

}
