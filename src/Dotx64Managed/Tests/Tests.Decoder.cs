using System;
using System.Diagnostics;

namespace Dotx64Dbg
{
    partial class Tests
    {
        void TestDecoder()
        {
            var decoder = Decoder.Create();

            {
                // 00007FF67A766E88 | 48:83EC 28               | sub rsp,28
                var instr = decoder.Decode(new byte[] { 0x48, 0x83, 0xEC, 0x28 }, 0x00007FF67A766E88);
                Debug.Assert(instr != null);
            }

        }
        public void TestInstruction()
        {
            var instr = new Instruction(Mnemonic.Add, Operand.Reg(Register.Rax), Operand.Imm(32));

            var op0 = instr.GetOperand(0);
            Debug.Assert(op0.Type == OperandType.Register);

            var op1 = instr.GetOperand(1);
            Debug.Assert(op1.Type == OperandType.Immediate);
            Debug.Assert(op1.Size == 8);

            var op2 = instr.GetOperand(2);
            Debug.Assert(op2.Type == OperandType.None);
            Debug.Assert(op2 == Operand.None);

            var op3 = instr.GetOperand(3);
            Debug.Assert(op3.Type == OperandType.None);
            Debug.Assert(op3 == Operand.None);

            var str = instr.ToString();
            Console.WriteLine(str);
        }

        public void TestOperandImm()
        {
            var imm1 = Operand.Imm(1);
            Debug.Assert(imm1.Size == 8);

            var imm2 = Operand.Imm(0xFF);
            Debug.Assert(imm2.Size == 8);

            var imm3 = Operand.Imm(0xFF + 1);
            Debug.Assert(imm3.Size == 16);

            var imm4 = Operand.Imm(-1);
            Debug.Assert(imm4.Size == 8);

            var imm5 = Operand.Imm(-255);
            Debug.Assert(imm5.Size == 8);

            var imm6 = Operand.Imm(-256);
            Debug.Assert(imm6.Size == 16);
        }

        public void TestOperandReg()
        {
            var al = Operand.Reg(Register.Al);
            Debug.Assert(al.Size == 8);

            var ax = Operand.Reg(Register.Ax);
            Debug.Assert(ax.Size == 16);

            var eax = Operand.Reg(Register.Eax);
            Debug.Assert(eax.Size == 32);

            var rax = Operand.Reg(Register.Rax);
            Debug.Assert(rax.Size == 64);
        }

        public void TestOperandMemory8()
        {
            var mem1 = Operand.byte_ptr(Register.Rax);
            Debug.Assert(mem1.Size == 8);
            Debug.Assert(mem1.Base == Register.Rax);

            var str1 = mem1.ToString();
            Debug.Assert(str1 == "byte ptr [rax]");

            var mem2 = Operand.byte_ptr(Register.Rax, Register.Rdx);
            Debug.Assert(mem2.Size == 8);
            Debug.Assert(mem2.Base == Register.Rax);
            Debug.Assert(mem2.Index == Register.Rdx);

            var str2 = mem2.ToString();
            Debug.Assert(str2 == "byte ptr [rax+rdx]");
        }

        public void TestOperandMemory16()
        {
            var mem1 = Operand.word_ptr(Register.Rax);
            Debug.Assert(mem1.Size == 16);
            Debug.Assert(mem1.Base == Register.Rax);

            var str1 = mem1.ToString();
            Debug.Assert(str1 == "word ptr [rax]");

            var mem2 = Operand.word_ptr(Register.Rax, Register.Rdx);
            Debug.Assert(mem2.Size == 16);
            Debug.Assert(mem2.Base == Register.Rax);
            Debug.Assert(mem2.Index == Register.Rdx);

            var str2 = mem2.ToString();
            Debug.Assert(str2 == "word ptr [rax+rdx]");
        }
    }
}
