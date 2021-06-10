namespace Dotx64Dbg
{
    public static class Loader
    {
        public static void Startup()
        {
            var files = new string[1];
            files[0] = @"E:\Debugging\x64Dbg\scripts\Test.cs";

            Compiler.Compile(files);
        }

        public static void Shutdown()
        {
        }
    }
}
