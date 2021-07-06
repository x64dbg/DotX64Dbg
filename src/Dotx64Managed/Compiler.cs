using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.Emit;
using Microsoft.CodeAnalysis.Text;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Dotx64Dbg
{
    class Compiler
    {
        private string OutputPath;
        private string Name;
        private string[] Dependencies = Array.Empty<string>();
        private bool ForScripting = false;

        public class Result
        {
            internal bool success = false;
            public bool Success { get => success; }
            public string OutputAssemblyPath;
            public MemoryStream AssemblyStream;
            public MemoryStream DebugStream;
        }

        public Compiler(string name, string outputPath = "")
        {
            OutputPath = outputPath;
            Name = name;
        }

        public Compiler WithDependencies(string[] deps)
        {
            Dependencies = deps;
            return this;
        }

        private List<SyntaxTree> ParseCode(string[] files, bool forScripting)
        {
            List<SyntaxTree> parsed = new();

            foreach (var file in files)
            {
                if (!file.EndsWith(".cs"))
                    continue;

                var parsedFile = ParseFile(file, forScripting);
                parsed.Add(parsedFile);
            }

            return parsed;
        }

        public Result Compile(string[] files, bool forScripting = false)
        {
            try
            {
                var parsed = ParseCode(files, forScripting);
                if (parsed.Count == 0)
                {
                    return new Result()
                    {
                        success = false
                    };
                }
                return Compile(parsed, forScripting);
            }
            catch (System.Exception ex)
            {
                Utils.PrintException(ex);
            }

            return new Result();
        }

        public Result Compile(string code)
        {
            try
            {
                List<SyntaxTree> parsed = new() { ParseCode(code, true) };
                return Compile(parsed, true);
            }
            catch (System.Exception ex)
            {
                Utils.PrintException(ex);
            }

            return new Result();
        }

        private Result Compile(List<SyntaxTree> parsed, bool forScripting = false)
        {
            var coreAssemblyPath = Path.GetDirectoryName(typeof(object).Assembly.Location);

            var assemblyRefs = new HashSet<string>();
            assemblyRefs.Add(typeof(object).Assembly.Location);
            assemblyRefs.Add(typeof(Logging).Assembly.Location);
            assemblyRefs.Add(typeof(System.Runtime.CompilerServices.DynamicAttribute).Assembly.Location);
            assemblyRefs.Add(typeof(Console).Assembly.Location);
            assemblyRefs.Add(typeof(System.Runtime.AssemblyTargetedPatchBandAttribute).Assembly.Location);
            assemblyRefs.Add(typeof(Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo).Assembly.Location);
            assemblyRefs.Add(typeof(Native.Logging).Assembly.Location);

            assemblyRefs.Add(Path.Combine(coreAssemblyPath, "mscorlib.dll"));
            assemblyRefs.Add(Path.Combine(coreAssemblyPath, "System.dll"));
            assemblyRefs.Add(Path.Combine(coreAssemblyPath, "System.Core.dll"));
            assemblyRefs.Add(Path.Combine(coreAssemblyPath, "System.Runtime.dll"));

            Assembly.GetExecutingAssembly().GetReferencedAssemblies()
                    .ToList()
                    .ForEach(a => assemblyRefs.Add(Assembly.Load(a).Location));

            foreach (var dep in Dependencies)
            {
                assemblyRefs.Add(Path.Combine(coreAssemblyPath, dep));
            }

            var references = new List<MetadataReference>();
            foreach (var assemblyRef in assemblyRefs)
            {
                references.Add(MetadataReference.CreateFromFile(assemblyRef));
            }

            var guid = Guid.NewGuid().ToString();
            var assemblyName = Name + guid;
            var assemblyPath = Path.Combine(OutputPath, Name + guid + ".dll");
            var debugFilePath = Path.Combine(OutputPath, Name + guid + ".pdb");

            var options = new CSharpCompilationOptions(forScripting ? OutputKind.ConsoleApplication : OutputKind.DynamicallyLinkedLibrary)
                .WithOptimizationLevel(OptimizationLevel.Debug)
                .WithAssemblyIdentityComparer(DesktopAssemblyIdentityComparer.Default)
#if _X86_
                .WithPlatform(Platform.X86)
#else
                .WithPlatform(Platform.X64)
#endif
                .WithModuleName(Name + guid)
            ;

            if (forScripting)
            {
                options = options.WithUsings(new[] {
                    "System",
                    "Dotx64Dbg",
                    "Dotx64Dbg.Scripting",
                });
            }

            var compiler = CSharpCompilation.Create(assemblyName,
                parsed,
                references: references,
                options: options);

            try
            {
                var res = new Result();
                EmitResult result;

                if (forScripting)
                {
                    res.AssemblyStream = new MemoryStream();
                    res.DebugStream = new MemoryStream();
                    result = compiler.Emit(res.AssemblyStream, res.DebugStream);
                }
                else
                {
                    result = compiler.Emit(assemblyPath, debugFilePath);
                }

                if (!result.Success)
                {
                    Console.WriteLine("Build failed");

                    foreach (var info in result.Diagnostics)
                    {
                        Console.WriteLine(info.ToString());
                    }

                    res.AssemblyStream.Dispose();
                    res.DebugStream.Dispose();
                    res.AssemblyStream = null;
                    res.DebugStream = null;
                }
                else
                {
                    res.success = true;
                    res.OutputAssemblyPath = assemblyPath;

                    return res;
                }
            }
            catch (Exception ex)
            {
                Utils.PrintException(ex);
            }

            return new Result();
        }

        private SyntaxTree ParseFile(string file, bool forScripting)
        {
            var code = System.IO.File.ReadAllText(file, Encoding.UTF8);
            return ParseCode(code, forScripting, file);
        }

        private UsingDirectiveSyntax CreateUsingDirective(string usingName)
        {
            var name = SyntaxFactory.ParseName(usingName);
            return SyntaxFactory.UsingDirective(name);
        }

        private SyntaxTree ParseCode(string code, bool forScripting, string file = "")
        {
            var preprocessorSymbols = new List<string>();
#if _X64_
            preprocessorSymbols.Add("_X64_");
#elif _X86_
            preprocessorSymbols.Add("_X86_");
#endif
            var codeString = SourceText.From(code, Encoding.UTF8);
            var options = CSharpParseOptions.Default
                .WithLanguageVersion(LanguageVersion.CSharp9)
                .WithPreprocessorSymbols(preprocessorSymbols.ToArray())
                .WithKind(forScripting ? SourceCodeKind.Script : SourceCodeKind.Regular)
                ;
            var parsedTree = SyntaxFactory.ParseSyntaxTree(codeString, options, file);

            return parsedTree;
        }
    }
}
