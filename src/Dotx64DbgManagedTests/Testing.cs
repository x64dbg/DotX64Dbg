#nullable enable

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace Dotx64Dbg.Managed.Tests
{
    public class Test : Attribute { }

    public class AssertException : Exception
    {
        public string MemberName { get; private set; }
        public string SourceFile { get; private set; }
        public int LineNumber { get; private set; }
        public AssertException(string message,
            string memberName,
            string sourceFilePath,
            int lineNumber) : base(message)
        {
            MemberName = memberName;
            SourceFile = sourceFilePath;
            LineNumber = lineNumber;
        }
    }

    public static class Testing
    {
        public static void AssertEq<T>(T? a, T? b,
            [CallerMemberName] string memberName = "",
            [CallerFilePath] string sourceFilePath = "",
            [CallerLineNumber] int sourceLineNumber = 0)
        {
            if (!EqualityComparer<T>.Default.Equals(a, b))
            {
                throw new AssertException($"Assertion: {a} == {b}", memberName, sourceFilePath, sourceLineNumber);
            }
        }

        public static void AssertNeq<T>(T? a, T? b,
            [CallerMemberName] string memberName = "",
            [CallerFilePath] string sourceFilePath = "",
            [CallerLineNumber] int sourceLineNumber = 0)
        {
            if (EqualityComparer<T>.Default.Equals(a, b))
            {
                throw new AssertException($"Assertion: {a} == {b}", memberName, sourceFilePath, sourceLineNumber);
            }
        }
    }
}
