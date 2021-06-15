using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
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

        public class Result
        {
            internal bool success = false;
            public bool Success { get => success; }
            public string OutputAssemblyPath;
        }

        public Compiler(string outputPath, string name)
        {
            OutputPath = outputPath;
            Name = name;
        }

        private List<SyntaxTree> ParseCode(string[] files)
        {
            List<SyntaxTree> parsed = new();

            foreach (var file in files)
            {
                if (!file.EndsWith(".cs"))
                    continue;

                var parsedFile = ParseFile(file);
                parsed.Add(parsedFile);
            }

            return parsed;
        }

        public Result Compile(string[] files)
        {
            try
            {
                var parsed = ParseCode(files);
                return Compile(parsed);
            }
            catch (System.Exception ex)
            {
                Console.WriteLine($"Exception: {ex.ToString()}");
            }

            return new Result();
        }

        private Result Compile(List<SyntaxTree> parsed)
        {
            var references = new List<MetadataReference>
            {
                MetadataReference.CreateFromFile(typeof(Logging).Assembly.Location),
                MetadataReference.CreateFromFile(typeof(object).Assembly.Location),
                MetadataReference.CreateFromFile(typeof(Console).Assembly.Location),
                MetadataReference.CreateFromFile(typeof(System.Runtime.AssemblyTargetedPatchBandAttribute).Assembly.Location),
                MetadataReference.CreateFromFile(typeof(Microsoft.CSharp.RuntimeBinder.CSharpArgumentInfo).Assembly.Location),
                MetadataReference.CreateFromFile(typeof(Native.Logging).Assembly.Location),
            };

            var coreAssemblyPath = Path.GetDirectoryName(typeof(object).Assembly.Location);
            references.Add(MetadataReference.CreateFromFile(Path.Combine(coreAssemblyPath, "mscorlib.dll")));
            references.Add(MetadataReference.CreateFromFile(Path.Combine(coreAssemblyPath, "System.dll")));
            references.Add(MetadataReference.CreateFromFile(Path.Combine(coreAssemblyPath, "System.Core.dll")));
            references.Add(MetadataReference.CreateFromFile(Path.Combine(coreAssemblyPath, "System.Runtime.dll")));

            Assembly.GetExecutingAssembly().GetReferencedAssemblies()
                    .ToList()
                    .ForEach(a => references.Add(MetadataReference.CreateFromFile(Assembly.Load(a).Location)));

            var guid = Guid.NewGuid().ToString();
            var assemblyName = Name + guid;
            var assemblyPath = Path.Combine(OutputPath, Name + guid + ".dll");
            var debugFilePath = Path.Combine(OutputPath, Name + guid + ".pdb");

            var options = new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary)
                .WithOptimizationLevel(OptimizationLevel.Debug)
                .WithAssemblyIdentityComparer(DesktopAssemblyIdentityComparer.Default)
#if _X86_
                .WithPlatform(Platform.X86)
#else
                .WithPlatform(Platform.X64)
#endif
                .WithModuleName(Name + guid)
            ;


            var compiler = CSharpCompilation.Create(assemblyName,
                parsed,
                references: references,
                options: options);

            try
            {

                EmitResult result = compiler.Emit(assemblyPath, debugFilePath);

                if (!result.Success)
                {
                    Console.WriteLine("Build failed");

                    foreach (var info in result.Diagnostics)
                    {
                        Console.WriteLine(info.ToString());
                    }
                }
                else
                {
                    var res = new Result();

                    res.success = true;
                    res.OutputAssemblyPath = assemblyPath;

                    return res;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: {0}", ex.ToString());
            }

            return new Result();
        }

        private SyntaxTree ParseFile(string file)
        {
            var encoding = Encoding.UTF8;

            var preprocessorSymbols = new List<string>();
#if _X64_
            preprocessorSymbols.Add("_X64_");
#elif _X86_
            preprocessorSymbols.Add("_X86_");
#endif

            var fileContents = System.IO.File.ReadAllText(file, encoding);
            var codeString = SourceText.From(fileContents, encoding);
            var options = CSharpParseOptions.Default
                .WithLanguageVersion(LanguageVersion.CSharp9)
                .WithPreprocessorSymbols(preprocessorSymbols.ToArray())
                ;
            var parsedTree = SyntaxFactory.ParseSyntaxTree(codeString, options, file);

            return parsedTree;
        }
    }
}
