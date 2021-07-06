using System;
using Dotx64Dbg;
using static Dotx64Dbg.Operands;

public class AssemblerTest : IHotload
{
    public AssemblerTest()
    {
        TestAssembler();
    }

    public void OnHotload()
    {
        TestAssembler();
    }

    private void TestAssembler()
    {
        var asm = new Assembler();
        asm
            .Mov(R9, R10)
            .Shl(R9, Imm(1))
            .Push(Rax)
            .Pop(Rdx)
            .Lea(Rsp, QwordPtr(Rsp, -8))
            .Xchg(Rax, Rdx)
            .Ret()
            ;

        asm.Cursor = null; // Before head.
        asm
            .Push(R9)
            .Pop(R10)
            ;

        var popInstr = (asm.Cursor as Assembler.NodeInstr).Value;
        Console.WriteLine($"Pop Instr: {popInstr}");

        var nodes = asm.GetNodes();
        var node = nodes.Head;
        while(node != null)
        {
            if(node is Assembler.NodeInstr instr)
            {
                Console.WriteLine($"{instr.Value}");
            }
            node = node.Next;
        }
    }
}