using System.CodeDom.Compiler;

namespace Dotx64Dbg
{
    class Compiler
    {
        public static bool Compile(string[] files)
        {
            try
            {
                var provider = new Microsoft.CodeDom.Providers.DotNetCompilerPlatform.CSharpCodeProvider();

                CompilerParameters cp = new CompilerParameters();

                // Generate an executable instead of
                // a class library.
                cp.GenerateExecutable = false;

                // Specify the assembly file name to generate.
                cp.OutputAssembly = "test.dll";

                // Save the assembly as a physical file.
                cp.GenerateInMemory = true;

                // Set whether to treat all warnings as errors.
                cp.TreatWarningsAsErrors = false;

                cp.ReferencedAssemblies.Add("Dotx64Dbg.Bindings");

                var res = provider.CompileAssemblyFromFile(cp, files);

                foreach (var output in res.Output)
                {
                    Logging.WriteLine(output);
                }
            }
            catch (System.Exception ex)
            {
                Logging.WriteLine($"Exception: {ex.ToString()}");
            }

            return true;
        }
    }
}
