using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;

namespace Dotx64Dbg.Managed.Tests
{
    public class Tests
    {
        private const ConsoleColor ColorOk = ConsoleColor.DarkGreen;
        private const ConsoleColor ColorBad = ConsoleColor.DarkRed;

        private static void Write(ConsoleColor color, string str)
        {
            var col = Console.ForegroundColor;
            Console.ForegroundColor = color;
            Console.Write(str);
            Console.ForegroundColor = col;
        }

        private static void WriteLine(ConsoleColor color, string str)
        {
            var col = Console.ForegroundColor;
            Console.ForegroundColor = color;
            Console.Write(str);
            Console.ForegroundColor = col;
        }
        private static void WriteLine(string str)
        {
            Console.WriteLine(str);
        }

        private static IEnumerable<MethodInfo> GetMethodsWithAttribute<T>()
        {
            return System.Reflection.Assembly.GetExecutingAssembly()
                .GetTypes()
                .SelectMany(t => t.GetMethods())
                .Where(m => m.GetCustomAttributes(typeof(T), false).Length > 0)
                ;
        }

        class TestGroup
        {
            public Type ClassType;
            public List<TestEntry> Entries;
        }

        class TestEntry
        {
            public string Name;
            public TestGroup Group;
            public MethodInfo Function;
        }

        class TestingState
        {
            public List<TestGroup> Groups = new();
            public List<TestEntry> Failed = new();
            public ulong TotalTime = 0;
            public ulong Ran = 0;
            public ulong Passed = 0;
        }

        private static void SetupTests(TestingState state)
        {
            var tests = state.Groups;

            var testFuncs = GetMethodsWithAttribute<Test>();
            foreach (var func in testFuncs)
            {
                TestGroup entry = tests.Count > 0 ? tests.Single(x => x.ClassType == func.DeclaringType) : null;
                if (entry == null)
                {
                    entry = new TestGroup()
                    {
                        ClassType = func.DeclaringType,
                        Entries = new()
                    };
                    tests.Add(entry);
                }

                entry.Entries.Add(new()
                {
                    Name = $"{entry.ClassType.Name}.{func.Name}",
                    Group = entry,
                    Function = func
                });
            }
        }

        private static bool RunTestGroup(TestingState state, TestGroup group)
        {
            var instance = Activator.CreateInstance(group.ClassType);
            foreach (var func in group.Entries)
            {
                RunTest(state, instance, group, func);
            }
            return false;
        }

        private static void LogException(TestingState state, Exception ex)
        {
            if (ex is AssertException assertEx)
            {
                Write(ColorBad, "[  ASSERT  ] ");
                WriteLine($"{assertEx.Message}");

                Write(ColorBad, "[          ] ");
                WriteLine($"Source: {assertEx.SourceFile}:{assertEx.LineNumber}");
            }
            else
            {
                Write(ColorBad, "[  FAILED  ] ");
                WriteLine($"{ex.Message}");
            }
        }

        private static bool RunTest(TestingState state, object instance, TestGroup group, TestEntry test)
        {
            bool passed = true;

            var sw = new Stopwatch();
            state.Ran++;

            Write(ColorOk, "[ Run      ] ");
            WriteLine($"{test.Name}");

            try
            {
                sw.Restart();
                test.Function.Invoke(instance, Array.Empty<object>());
                sw.Stop();
            }
            catch (Exception ex)
            {
                LogException(state, ex.InnerException ?? ex);
                passed = false;
            }

            if (passed)
            {
                Write(ColorOk, "[       OK ] ");
                WriteLine($"{test.Name} ({sw.ElapsedMilliseconds} ms)");
                state.Passed++;
                state.TotalTime += (ulong)sw.ElapsedMilliseconds;
            }
            else
            {
                Write(ColorBad, "[  FAILED  ] ");
                WriteLine($"{test.Name}");
                state.Failed.Add(test);
            }

            return passed;
        }

        public static void Main(string[] args)
        {
            TestingState state = new();

            SetupTests(state);

            foreach (var test in state.Groups)
            {
                Write(ColorOk, "[----------] ");
                WriteLine($"{test.Entries.Count} test(s) from {test.ClassType.Name}");
                RunTestGroup(state, test);
            }

            WriteLine("");

            Write(ColorOk, $"[==========] ");
            WriteLine($"{state.Ran} tests ran. ({state.TotalTime} ms total)");

            ulong passing = state.Ran - (ulong)state.Failed.Count;
            if (passing == 0)
            {
                Write(ColorBad, $"[  FAILED  ] ");
                WriteLine($"No tests passed.");
            }
            else
            {
                Write(ColorOk, $"[  PASSED  ] ");
                WriteLine($"{state.Ran - (ulong)state.Failed.Count} tests.");
            }

            if (state.Failed.Count > 0)
            {
                Write(ColorBad, $"[  FAILED  ] ");
                WriteLine($"{state.Failed.Count} tests, listed below:");
                foreach (var failedTest in state.Failed)
                {
                    Write(ColorBad, $"[  FAILED  ] ");
                    WriteLine($"{failedTest.Name}");
                }

                Environment.ExitCode = -1;
            }
            else
            {
                Environment.ExitCode = 0;
            }

        }

    }
}