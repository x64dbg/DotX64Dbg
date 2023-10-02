namespace Dotx64Dbg.Managed.Tests
{
    using static Operands;
    using static Testing;

    class TestInstructionGenerator
    {
        [Test]
        public void TestSubEaxEdx()
        {
            var instr = InstructionGenerator.Generate(Mnemonic.Sub, Eax, Edx);
            AssertNeq(instr, null);
            AssertEq((instr.GetOperand(0) as Operand.Register).Value, Eax.Value);
            AssertEq(instr.GetOperandAccess(0), OperandAccess.ReadWrite);
            AssertEq((instr.GetOperand(1) as Operand.Register).Value, Edx.Value);
            AssertEq(instr.GetOperandAccess(1), OperandAccess.Read);
            AssertEq(instr.FlagsRead, Dotx64Dbg.EFlags.None);
            AssertEq(instr.FlagsWrite, Dotx64Dbg.EFlags.Of |
                Dotx64Dbg.EFlags.Sf |
                Dotx64Dbg.EFlags.Zf |
                Dotx64Dbg.EFlags.Af |
                Dotx64Dbg.EFlags.Pf |
                Dotx64Dbg.EFlags.Cf);
        }

        [Test]
        public void TestSubEaxEdx100000()
        {
            for (int i = 0; i < 100000; i++)
            {
                var instr = InstructionGenerator.Generate(Mnemonic.Sub, Eax, Edx);
                AssertNeq(instr, null);
                AssertEq((instr.GetOperand(0) as Operand.Register).Value, Eax.Value);
                AssertEq(instr.GetOperandAccess(0), OperandAccess.ReadWrite);
                AssertEq((instr.GetOperand(1) as Operand.Register).Value, Edx.Value);
                AssertEq(instr.GetOperandAccess(1), OperandAccess.Read);
                AssertEq(instr.FlagsRead, Dotx64Dbg.EFlags.None);
                AssertEq(instr.FlagsWrite, Dotx64Dbg.EFlags.Of |
                    Dotx64Dbg.EFlags.Sf |
                    Dotx64Dbg.EFlags.Zf |
                    Dotx64Dbg.EFlags.Af |
                    Dotx64Dbg.EFlags.Pf |
                    Dotx64Dbg.EFlags.Cf);
            }
        }

        [Test]
        public void TestLeaNoDisp()
        {
            var instr = InstructionGenerator.Generate(Mnemonic.Lea, Eax, DwordPtr(Eax, Edx));
            AssertNeq(instr, null);
            AssertEq((instr.GetOperand(0) as Operand.Register).Value, Eax.Value);
            AssertEq(instr.GetOperandAccess(0), OperandAccess.Write);
            var op1 = instr.GetOperand(1);
            AssertEq(op1.Type, OperandType.Memory);
            var mem = op1 as Operand.Memory;
            AssertEq(mem.Segment, Registers.Id.Ds);
            AssertEq(mem.Base, Registers.Id.Eax);
            AssertEq(mem.Index, Registers.Id.Edx);
            AssertEq(mem.Displacement, 0);
        }

        [Test]
        public void TestLeaDisp()
        {
            var instr = InstructionGenerator.Generate(Mnemonic.Lea, Eax, DwordPtr(Eax, Edx, 0xBADBABE));
            AssertNeq(instr, null);
            AssertEq((instr.GetOperand(0) as Operand.Register).Value, Eax.Value);
            AssertEq(instr.GetOperandAccess(0), OperandAccess.Write);
            var op1 = instr.GetOperand(1);
            AssertEq(op1.Type, OperandType.Memory);
            var mem = op1 as Operand.Memory;
            AssertEq(mem.Segment, Registers.Id.Ds);
            AssertEq(mem.Base, Registers.Id.Eax);
            AssertEq(mem.Index, Registers.Id.Edx);
            AssertEq(mem.Displacement, 0xBADBABE);
        }
    }
}
