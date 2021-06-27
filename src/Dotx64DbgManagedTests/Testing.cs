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
        public static void AssertEq(object? a, object? b,
            [CallerMemberName] string memberName = "",
            [CallerFilePath] string sourceFilePath = "",
            [CallerLineNumber] int sourceLineNumber = 0)
        {
            if (a == null && b == null)
                return;
            if (a == null && b != null)
                throw new AssertException($"Assertion: {a} == {b}", memberName, sourceFilePath, sourceLineNumber);
            if (a != null && b == null)
                throw new AssertException($"Assertion: {a} == {b}", memberName, sourceFilePath, sourceLineNumber);
            if (a != null && !a.Equals(b))
                throw new AssertException($"Assertion: {a} == {b}", memberName, sourceFilePath, sourceLineNumber);
        }

        public static void AssertNeq(object? a, object? b,
            [CallerMemberName] string memberName = "",
            [CallerFilePath] string sourceFilePath = "",
            [CallerLineNumber] int sourceLineNumber = 0)
        {
            if (a == null && b != null)
                return;
            if (a != null && b == null)
                return;
            if (a == null && b == null)
                throw new AssertException($"Assertion: {a} != {b}", memberName, sourceFilePath, sourceLineNumber);
            if (a != null && a.Equals(b))
                throw new AssertException($"Assertion: {a} != {b}", memberName, sourceFilePath, sourceLineNumber);
        }
    }
}
