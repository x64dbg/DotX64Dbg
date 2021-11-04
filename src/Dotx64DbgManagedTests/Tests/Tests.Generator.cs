using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Dotx64Dbg;

namespace Dotx64Dbg.Managed.Tests
{
    using static Testing;
    using static Operands;

    class TestGenerator
    {
        static readonly EFlags FlagsSub = Dotx64Dbg.EFlags.Cf | Dotx64Dbg.EFlags.Pf;

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
            for(int i = 0; i < 100000; i++)
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
    }
}
