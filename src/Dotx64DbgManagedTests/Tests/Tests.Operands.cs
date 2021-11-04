using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg.Managed.Tests
{
    using static Testing;
    using static Operands;

    class TestOperands
    {
        [Test]
        public void TestOperandImm()
        {
            var imm1 = Operands.Imm(1);
            AssertEq(imm1.Size, 8);

            var imm2 = Operands.Imm(0xFF);
            AssertEq(imm2.Size, 8);

            var imm3 = Operands.Imm(0xFF + 1);
            AssertEq(imm3.Size, 16);

            var imm4 = Operands.Imm(-1);
            AssertEq(imm4.Size, 8);

            var imm5 = Operands.Imm(-255);
            AssertEq(imm5.Size, 8);

            var imm6 = Operands.Imm(-256);
            AssertEq(imm6.Size, 16);
        }

        [Test]
        public void TestOperandReg()
        {
            var al = Operands.Reg(RegisterId.Al);
            AssertEq(al.Size, 8);

            var ax = Operands.Reg(RegisterId.Ax);
            AssertEq(ax.Size, 16);

            var eax = Operands.Reg(RegisterId.Eax);
            AssertEq(eax.Size, 32);

            var rax = Operands.Reg(RegisterId.Rax);
            AssertEq(rax.Size, 64);
        }

        [Test]
        public void TestOperandMemory8()
        {
            var mem1 = Operands.BytePtr(RegisterId.Rax);
            AssertEq(mem1.Size, 8);
            AssertEq(mem1.Base, RegisterId.Rax);

            var str1 = mem1.ToString();
            AssertEq(str1, "byte ptr [rax]");

            var mem2 = Operands.BytePtr(RegisterId.Rax, RegisterId.Rdx);
            AssertEq(mem2.Size, 8);
            AssertEq(mem2.Base, RegisterId.Rax);
            AssertEq(mem2.Index, RegisterId.Rdx);

            var str2 = mem2.ToString();
            AssertEq(str2, "byte ptr [rax+rdx]");
        }

        [Test]
        public void TestOperandMemory16()
        {
            var mem1 = Operands.WordPtr(RegisterId.Rax);
            AssertEq(mem1.Size, 16);
            AssertEq(mem1.Base, RegisterId.Rax);

            var str1 = mem1.ToString();
            AssertEq(str1, "word ptr [rax]");

            var mem2 = Operands.WordPtr(RegisterId.Rax, RegisterId.Rdx);
            AssertEq(mem2.Size, 16);
            AssertEq(mem2.Base, RegisterId.Rax);
            AssertEq(mem2.Index, RegisterId.Rdx);

            var str2 = mem2.ToString();
            AssertEq(str2, "word ptr [rax+rdx]");
        }
    }
}
