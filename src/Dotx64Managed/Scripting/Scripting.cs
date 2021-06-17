using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    /// <summary>
    /// Wrapper to simplify the scripting environment.
    /// </summary>
    public static partial class Scripting
    {
        public static void Print(string line)
        {
            Console.WriteLine(line);
        }
        public static void Print(string fmt, params object[] args)
        {
            Console.WriteLine(fmt, args);
        }

        public static void Sti()
        {
            Debugger.StepIn();
        }

        public static void Sto()
        {
            Debugger.StepOver();
        }

        public static void Run()
        {
            Debugger.Run();
        }

        public static void Pause()
        {
            Debugger.Pause();
        }

        public static void Stop()
        {
            Debugger.Stop();
        }

        public static void Skip(int numInstructions = 1)
        {
            Debugger.RunCommand($"skip {numInstructions}");
        }
    }
}
