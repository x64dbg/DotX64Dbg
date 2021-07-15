using System;
using Dotx64Dbg;
using static Dotx64Dbg.Operands;

public class AssemblerTest
{
    public AssemblerTest()
    {
    }

    [Command("TestAssembler")]
    public void BasicAssembly(string[] args)
    {
        using (var asm = new Assembler((nuint)Thread.Active.Rip))
        {
            // Create some assembly.
            asm
                .Mov(R9, R10)
                .Shl(R9, Imm(1))
                .Push(Rax)
                .Pop(Rdx)
                .Lea(Rsp, QwordPtr(Rsp, -8))
                .Xchg(Rax, Rdx)
                .Ret()
                ;

            // Insert at the beginning.
            asm.Cursor = null;
            asm
                .Push(R9)
                .Pop(R10)
                ;

            // Serialize the nodes into x86.
            asm.Finalize();

            // Write into process.
            var bytes = asm.GetData();

            var bytesWritten = Memory.Write(Thread.Active.Rip, bytes);
            Console.WriteLine($"Wrote {bytesWritten} bytes");

            UI.Disassembly.Update();

        }
    }

    [Command("AssembleFromIP")]
    public void EncodeIntoAssembler(string[] args)
    {
        var decoder = Decoder.Create();
        var asm = new Assembler((nuint)Thread.Active.Rip);

        var instr = decoder.Decode(Thread.Active.Rip);
        asm.Emit(instr);

        // Serialize the nodes into x86.
        asm.Finalize();

        // Write into process.
        var bytes = asm.GetData();

        var bytesWritten = Memory.Write(Thread.Active.Rip, bytes);
        Console.WriteLine($"Wrote {bytesWritten} bytes");

        UI.Disassembly.Update();
    }

    [Command("AssembleWithLabel")]
    public void AssemblerWithLabels(string[] args)
    {
        var asm = new Assembler((nuint)Thread.Active.Rip);

        var myLabel = asm.CreateLabel();

        asm.Mov(Rax, Imm(12))
            .Xor(Rdx, Rdx)
            .Cmp(Rax, Rdx)
            .Jmp(myLabel)
            .Nop()
            .Nop()
            .BindLabel(myLabel)
            .Ret()
            ;

        // Serialize the nodes into x86.
        asm.Finalize();

        // Write into process.
        var bytes = asm.GetData();

        var bytesWritten = Memory.Write(Thread.Active.Rip, bytes);
        Console.WriteLine($"Wrote {bytesWritten} bytes");

        UI.Disassembly.Update();
    }
}