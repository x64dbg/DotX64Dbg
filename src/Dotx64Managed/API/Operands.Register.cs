using System;

namespace Dotx64Dbg
{
    public static partial class Operands
    {
        // General purpose registers  8-bit
        public static readonly Operand.OpReg Al = new Operand.OpReg(Register.Al);
        public static readonly Operand.OpReg Cl = new Operand.OpReg(Register.Cl);
        public static readonly Operand.OpReg Dl = new Operand.OpReg(Register.Dl);
        public static readonly Operand.OpReg Bl = new Operand.OpReg(Register.Bl);
        public static readonly Operand.OpReg Ah = new Operand.OpReg(Register.Ah);
        public static readonly Operand.OpReg Ch = new Operand.OpReg(Register.Ch);
        public static readonly Operand.OpReg Dh = new Operand.OpReg(Register.Dh);
        public static readonly Operand.OpReg Bh = new Operand.OpReg(Register.Bh);
        public static readonly Operand.OpReg Spl = new Operand.OpReg(Register.Spl);
        public static readonly Operand.OpReg Bpl = new Operand.OpReg(Register.Bpl);
        public static readonly Operand.OpReg Sil = new Operand.OpReg(Register.Sil);
        public static readonly Operand.OpReg Dil = new Operand.OpReg(Register.Dil);
#if _X64_
        public static readonly Operand.OpReg R8b = new Operand.OpReg(Register.R8b);
        public static readonly Operand.OpReg R9b = new Operand.OpReg(Register.R9b);
        public static readonly Operand.OpReg R10b = new Operand.OpReg(Register.R10b);
        public static readonly Operand.OpReg R11b = new Operand.OpReg(Register.R11b);
        public static readonly Operand.OpReg R12b = new Operand.OpReg(Register.R12b);
        public static readonly Operand.OpReg R13b = new Operand.OpReg(Register.R13b);
        public static readonly Operand.OpReg R14b = new Operand.OpReg(Register.R14b);
        public static readonly Operand.OpReg R15b = new Operand.OpReg(Register.R15b);
#endif
        // General purpose registers 16-bit
        public static readonly Operand.OpReg Ax = new Operand.OpReg(Register.Ax);
        public static readonly Operand.OpReg Cx = new Operand.OpReg(Register.Cx);
        public static readonly Operand.OpReg Dx = new Operand.OpReg(Register.Dx);
        public static readonly Operand.OpReg Bx = new Operand.OpReg(Register.Bx);
        public static readonly Operand.OpReg Sp = new Operand.OpReg(Register.Sp);
        public static readonly Operand.OpReg Bp = new Operand.OpReg(Register.Bp);
        public static readonly Operand.OpReg Si = new Operand.OpReg(Register.Si);
        public static readonly Operand.OpReg Di = new Operand.OpReg(Register.Di);
#if _X64_
        public static readonly Operand.OpReg R8w = new Operand.OpReg(Register.R8w);
        public static readonly Operand.OpReg R9w = new Operand.OpReg(Register.R9w);
        public static readonly Operand.OpReg R10w = new Operand.OpReg(Register.R10w);
        public static readonly Operand.OpReg R11w = new Operand.OpReg(Register.R11w);
        public static readonly Operand.OpReg R12w = new Operand.OpReg(Register.R12w);
        public static readonly Operand.OpReg R13w = new Operand.OpReg(Register.R13w);
        public static readonly Operand.OpReg R14w = new Operand.OpReg(Register.R14w);
        public static readonly Operand.OpReg R15w = new Operand.OpReg(Register.R15w);
#endif
        // General purpose registers 32-bit
        public static readonly Operand.OpReg Eax = new Operand.OpReg(Register.Eax);
        public static readonly Operand.OpReg Ecx = new Operand.OpReg(Register.Ecx);
        public static readonly Operand.OpReg Edx = new Operand.OpReg(Register.Edx);
        public static readonly Operand.OpReg Ebx = new Operand.OpReg(Register.Ebx);
        public static readonly Operand.OpReg Esp = new Operand.OpReg(Register.Esp);
        public static readonly Operand.OpReg Ebp = new Operand.OpReg(Register.Ebp);
        public static readonly Operand.OpReg Esi = new Operand.OpReg(Register.Esi);
        public static readonly Operand.OpReg Edi = new Operand.OpReg(Register.Edi);
        public static readonly Operand.OpReg R8d = new Operand.OpReg(Register.R8d);
        public static readonly Operand.OpReg R9d = new Operand.OpReg(Register.R9d);
        public static readonly Operand.OpReg R10d = new Operand.OpReg(Register.R10d);
        public static readonly Operand.OpReg R11d = new Operand.OpReg(Register.R11d);
        public static readonly Operand.OpReg R12d = new Operand.OpReg(Register.R12d);
        public static readonly Operand.OpReg R13d = new Operand.OpReg(Register.R13d);
        public static readonly Operand.OpReg R14d = new Operand.OpReg(Register.R14d);
        public static readonly Operand.OpReg R15d = new Operand.OpReg(Register.R15d);
#if _X64_
        // General purpose registers 64-bit
        public static readonly Operand.OpReg Rax = new Operand.OpReg(Register.Rax);
        public static readonly Operand.OpReg Rcx = new Operand.OpReg(Register.Rcx);
        public static readonly Operand.OpReg Rdx = new Operand.OpReg(Register.Rdx);
        public static readonly Operand.OpReg Rbx = new Operand.OpReg(Register.Rbx);
        public static readonly Operand.OpReg Rsp = new Operand.OpReg(Register.Rsp);
        public static readonly Operand.OpReg Rbp = new Operand.OpReg(Register.Rbp);
        public static readonly Operand.OpReg Rsi = new Operand.OpReg(Register.Rsi);
        public static readonly Operand.OpReg Rdi = new Operand.OpReg(Register.Rdi);
        public static readonly Operand.OpReg R8 = new Operand.OpReg(Register.R8);
        public static readonly Operand.OpReg R9 = new Operand.OpReg(Register.R9);
        public static readonly Operand.OpReg R10 = new Operand.OpReg(Register.R10);
        public static readonly Operand.OpReg R11 = new Operand.OpReg(Register.R11);
        public static readonly Operand.OpReg R12 = new Operand.OpReg(Register.R12);
        public static readonly Operand.OpReg R13 = new Operand.OpReg(Register.R13);
        public static readonly Operand.OpReg R14 = new Operand.OpReg(Register.R14);
        public static readonly Operand.OpReg R15 = new Operand.OpReg(Register.R15);
#endif
        // Floating point legacy registers
        public static readonly Operand.OpReg St0 = new Operand.OpReg(Register.St0);
        public static readonly Operand.OpReg St1 = new Operand.OpReg(Register.St1);
        public static readonly Operand.OpReg St2 = new Operand.OpReg(Register.St2);
        public static readonly Operand.OpReg St3 = new Operand.OpReg(Register.St3);
        public static readonly Operand.OpReg St4 = new Operand.OpReg(Register.St4);
        public static readonly Operand.OpReg St5 = new Operand.OpReg(Register.St5);
        public static readonly Operand.OpReg St6 = new Operand.OpReg(Register.St6);
        public static readonly Operand.OpReg St7 = new Operand.OpReg(Register.St7);
        public static readonly Operand.OpReg X87Control = new Operand.OpReg(Register.X87Control);
        public static readonly Operand.OpReg X87Status = new Operand.OpReg(Register.X87Status);
        public static readonly Operand.OpReg X87Tag = new Operand.OpReg(Register.X87Tag);
        // Floating point multimedia registers
        public static readonly Operand.OpReg Mm0 = new Operand.OpReg(Register.Mm0);
        public static readonly Operand.OpReg Mm1 = new Operand.OpReg(Register.Mm1);
        public static readonly Operand.OpReg Mm2 = new Operand.OpReg(Register.Mm2);
        public static readonly Operand.OpReg Mm3 = new Operand.OpReg(Register.Mm3);
        public static readonly Operand.OpReg Mm4 = new Operand.OpReg(Register.Mm4);
        public static readonly Operand.OpReg Mm5 = new Operand.OpReg(Register.Mm5);
        public static readonly Operand.OpReg Mm6 = new Operand.OpReg(Register.Mm6);
        public static readonly Operand.OpReg Mm7 = new Operand.OpReg(Register.Mm7);
        // Floating point vector registers 128-bit
        public static readonly Operand.OpReg Xmm0 = new Operand.OpReg(Register.Xmm0);
        public static readonly Operand.OpReg Xmm1 = new Operand.OpReg(Register.Xmm1);
        public static readonly Operand.OpReg Xmm2 = new Operand.OpReg(Register.Xmm2);
        public static readonly Operand.OpReg Xmm3 = new Operand.OpReg(Register.Xmm3);
        public static readonly Operand.OpReg Xmm4 = new Operand.OpReg(Register.Xmm4);
        public static readonly Operand.OpReg Xmm5 = new Operand.OpReg(Register.Xmm5);
        public static readonly Operand.OpReg Xmm6 = new Operand.OpReg(Register.Xmm6);
        public static readonly Operand.OpReg Xmm7 = new Operand.OpReg(Register.Xmm7);
        public static readonly Operand.OpReg Xmm8 = new Operand.OpReg(Register.Xmm8);
        public static readonly Operand.OpReg Xmm9 = new Operand.OpReg(Register.Xmm9);
        public static readonly Operand.OpReg Xmm10 = new Operand.OpReg(Register.Xmm10);
        public static readonly Operand.OpReg Xmm11 = new Operand.OpReg(Register.Xmm11);
        public static readonly Operand.OpReg Xmm12 = new Operand.OpReg(Register.Xmm12);
        public static readonly Operand.OpReg Xmm13 = new Operand.OpReg(Register.Xmm13);
        public static readonly Operand.OpReg Xmm14 = new Operand.OpReg(Register.Xmm14);
        public static readonly Operand.OpReg Xmm15 = new Operand.OpReg(Register.Xmm15);
        public static readonly Operand.OpReg Xmm16 = new Operand.OpReg(Register.Xmm16);
        public static readonly Operand.OpReg Xmm17 = new Operand.OpReg(Register.Xmm17);
        public static readonly Operand.OpReg Xmm18 = new Operand.OpReg(Register.Xmm18);
        public static readonly Operand.OpReg Xmm19 = new Operand.OpReg(Register.Xmm19);
        public static readonly Operand.OpReg Xmm20 = new Operand.OpReg(Register.Xmm20);
        public static readonly Operand.OpReg Xmm21 = new Operand.OpReg(Register.Xmm21);
        public static readonly Operand.OpReg Xmm22 = new Operand.OpReg(Register.Xmm22);
        public static readonly Operand.OpReg Xmm23 = new Operand.OpReg(Register.Xmm23);
        public static readonly Operand.OpReg Xmm24 = new Operand.OpReg(Register.Xmm24);
        public static readonly Operand.OpReg Xmm25 = new Operand.OpReg(Register.Xmm25);
        public static readonly Operand.OpReg Xmm26 = new Operand.OpReg(Register.Xmm26);
        public static readonly Operand.OpReg Xmm27 = new Operand.OpReg(Register.Xmm27);
        public static readonly Operand.OpReg Xmm28 = new Operand.OpReg(Register.Xmm28);
        public static readonly Operand.OpReg Xmm29 = new Operand.OpReg(Register.Xmm29);
        public static readonly Operand.OpReg Xmm30 = new Operand.OpReg(Register.Xmm30);
        public static readonly Operand.OpReg Xmm31 = new Operand.OpReg(Register.Xmm31);
        // Floating point vector registers 256-bit
        public static readonly Operand.OpReg Ymm0 = new Operand.OpReg(Register.Ymm0);
        public static readonly Operand.OpReg Ymm1 = new Operand.OpReg(Register.Ymm1);
        public static readonly Operand.OpReg Ymm2 = new Operand.OpReg(Register.Ymm2);
        public static readonly Operand.OpReg Ymm3 = new Operand.OpReg(Register.Ymm3);
        public static readonly Operand.OpReg Ymm4 = new Operand.OpReg(Register.Ymm4);
        public static readonly Operand.OpReg Ymm5 = new Operand.OpReg(Register.Ymm5);
        public static readonly Operand.OpReg Ymm6 = new Operand.OpReg(Register.Ymm6);
        public static readonly Operand.OpReg Ymm7 = new Operand.OpReg(Register.Ymm7);
        public static readonly Operand.OpReg Ymm8 = new Operand.OpReg(Register.Ymm8);
        public static readonly Operand.OpReg Ymm9 = new Operand.OpReg(Register.Ymm9);
        public static readonly Operand.OpReg Ymm10 = new Operand.OpReg(Register.Ymm10);
        public static readonly Operand.OpReg Ymm11 = new Operand.OpReg(Register.Ymm11);
        public static readonly Operand.OpReg Ymm12 = new Operand.OpReg(Register.Ymm12);
        public static readonly Operand.OpReg Ymm13 = new Operand.OpReg(Register.Ymm13);
        public static readonly Operand.OpReg Ymm14 = new Operand.OpReg(Register.Ymm14);
        public static readonly Operand.OpReg Ymm15 = new Operand.OpReg(Register.Ymm15);
        public static readonly Operand.OpReg Ymm16 = new Operand.OpReg(Register.Ymm16);
        public static readonly Operand.OpReg Ymm17 = new Operand.OpReg(Register.Ymm17);
        public static readonly Operand.OpReg Ymm18 = new Operand.OpReg(Register.Ymm18);
        public static readonly Operand.OpReg Ymm19 = new Operand.OpReg(Register.Ymm19);
        public static readonly Operand.OpReg Ymm20 = new Operand.OpReg(Register.Ymm20);
        public static readonly Operand.OpReg Ymm21 = new Operand.OpReg(Register.Ymm21);
        public static readonly Operand.OpReg Ymm22 = new Operand.OpReg(Register.Ymm22);
        public static readonly Operand.OpReg Ymm23 = new Operand.OpReg(Register.Ymm23);
        public static readonly Operand.OpReg Ymm24 = new Operand.OpReg(Register.Ymm24);
        public static readonly Operand.OpReg Ymm25 = new Operand.OpReg(Register.Ymm25);
        public static readonly Operand.OpReg Ymm26 = new Operand.OpReg(Register.Ymm26);
        public static readonly Operand.OpReg Ymm27 = new Operand.OpReg(Register.Ymm27);
        public static readonly Operand.OpReg Ymm28 = new Operand.OpReg(Register.Ymm28);
        public static readonly Operand.OpReg Ymm29 = new Operand.OpReg(Register.Ymm29);
        public static readonly Operand.OpReg Ymm30 = new Operand.OpReg(Register.Ymm30);
        public static readonly Operand.OpReg Ymm31 = new Operand.OpReg(Register.Ymm31);
        // Floating point vector registers 512-bit
        public static readonly Operand.OpReg Zmm0 = new Operand.OpReg(Register.Zmm0);
        public static readonly Operand.OpReg Zmm1 = new Operand.OpReg(Register.Zmm1);
        public static readonly Operand.OpReg Zmm2 = new Operand.OpReg(Register.Zmm2);
        public static readonly Operand.OpReg Zmm3 = new Operand.OpReg(Register.Zmm3);
        public static readonly Operand.OpReg Zmm4 = new Operand.OpReg(Register.Zmm4);
        public static readonly Operand.OpReg Zmm5 = new Operand.OpReg(Register.Zmm5);
        public static readonly Operand.OpReg Zmm6 = new Operand.OpReg(Register.Zmm6);
        public static readonly Operand.OpReg Zmm7 = new Operand.OpReg(Register.Zmm7);
        public static readonly Operand.OpReg Zmm8 = new Operand.OpReg(Register.Zmm8);
        public static readonly Operand.OpReg Zmm9 = new Operand.OpReg(Register.Zmm9);
        public static readonly Operand.OpReg Zmm10 = new Operand.OpReg(Register.Zmm10);
        public static readonly Operand.OpReg Zmm11 = new Operand.OpReg(Register.Zmm11);
        public static readonly Operand.OpReg Zmm12 = new Operand.OpReg(Register.Zmm12);
        public static readonly Operand.OpReg Zmm13 = new Operand.OpReg(Register.Zmm13);
        public static readonly Operand.OpReg Zmm14 = new Operand.OpReg(Register.Zmm14);
        public static readonly Operand.OpReg Zmm15 = new Operand.OpReg(Register.Zmm15);
        public static readonly Operand.OpReg Zmm16 = new Operand.OpReg(Register.Zmm16);
        public static readonly Operand.OpReg Zmm17 = new Operand.OpReg(Register.Zmm17);
        public static readonly Operand.OpReg Zmm18 = new Operand.OpReg(Register.Zmm18);
        public static readonly Operand.OpReg Zmm19 = new Operand.OpReg(Register.Zmm19);
        public static readonly Operand.OpReg Zmm20 = new Operand.OpReg(Register.Zmm20);
        public static readonly Operand.OpReg Zmm21 = new Operand.OpReg(Register.Zmm21);
        public static readonly Operand.OpReg Zmm22 = new Operand.OpReg(Register.Zmm22);
        public static readonly Operand.OpReg Zmm23 = new Operand.OpReg(Register.Zmm23);
        public static readonly Operand.OpReg Zmm24 = new Operand.OpReg(Register.Zmm24);
        public static readonly Operand.OpReg Zmm25 = new Operand.OpReg(Register.Zmm25);
        public static readonly Operand.OpReg Zmm26 = new Operand.OpReg(Register.Zmm26);
        public static readonly Operand.OpReg Zmm27 = new Operand.OpReg(Register.Zmm27);
        public static readonly Operand.OpReg Zmm28 = new Operand.OpReg(Register.Zmm28);
        public static readonly Operand.OpReg Zmm29 = new Operand.OpReg(Register.Zmm29);
        public static readonly Operand.OpReg Zmm30 = new Operand.OpReg(Register.Zmm30);
        public static readonly Operand.OpReg Zmm31 = new Operand.OpReg(Register.Zmm31);
        // Flags registers
        public static readonly Operand.OpReg Flags = new Operand.OpReg(Register.Flags);
        public static readonly Operand.OpReg EFlags = new Operand.OpReg(Register.EFlags);
        public static readonly Operand.OpReg RFlags = new Operand.OpReg(Register.RFlags);
        // Instruction-pointer registers
        public static readonly Operand.OpReg Ip = new Operand.OpReg(Register.Ip);
        public static readonly Operand.OpReg Eip = new Operand.OpReg(Register.Eip);
        public static readonly Operand.OpReg Rip = new Operand.OpReg(Register.Rip);
        // Segment registers
        public static readonly Operand.OpReg Es = new Operand.OpReg(Register.Es);
        public static readonly Operand.OpReg Cs = new Operand.OpReg(Register.Cs);
        public static readonly Operand.OpReg Ss = new Operand.OpReg(Register.Ss);
        public static readonly Operand.OpReg Ds = new Operand.OpReg(Register.Ds);
        public static readonly Operand.OpReg Fs = new Operand.OpReg(Register.Fs);
        public static readonly Operand.OpReg Gs = new Operand.OpReg(Register.Gs);
        // Table registers
        public static readonly Operand.OpReg Gdtr = new Operand.OpReg(Register.Gdtr);
        public static readonly Operand.OpReg Ldtr = new Operand.OpReg(Register.Ldtr);
        public static readonly Operand.OpReg Idtr = new Operand.OpReg(Register.Idtr);
        public static readonly Operand.OpReg Tr = new Operand.OpReg(Register.Tr);
        // Test registers
        public static readonly Operand.OpReg Tr0 = new Operand.OpReg(Register.Tr0);
        public static readonly Operand.OpReg Tr1 = new Operand.OpReg(Register.Tr1);
        public static readonly Operand.OpReg Tr2 = new Operand.OpReg(Register.Tr2);
        public static readonly Operand.OpReg Tr3 = new Operand.OpReg(Register.Tr3);
        public static readonly Operand.OpReg Tr4 = new Operand.OpReg(Register.Tr4);
        public static readonly Operand.OpReg Tr5 = new Operand.OpReg(Register.Tr5);
        public static readonly Operand.OpReg Tr6 = new Operand.OpReg(Register.Tr6);
        public static readonly Operand.OpReg Tr7 = new Operand.OpReg(Register.Tr7);
        // Control registers
        public static readonly Operand.OpReg Cr0 = new Operand.OpReg(Register.Cr0);
        public static readonly Operand.OpReg Cr1 = new Operand.OpReg(Register.Cr1);
        public static readonly Operand.OpReg Cr2 = new Operand.OpReg(Register.Cr2);
        public static readonly Operand.OpReg Cr3 = new Operand.OpReg(Register.Cr3);
        public static readonly Operand.OpReg Cr4 = new Operand.OpReg(Register.Cr4);
        public static readonly Operand.OpReg Cr5 = new Operand.OpReg(Register.Cr5);
        public static readonly Operand.OpReg Cr6 = new Operand.OpReg(Register.Cr6);
        public static readonly Operand.OpReg Cr7 = new Operand.OpReg(Register.Cr7);
        public static readonly Operand.OpReg Cr8 = new Operand.OpReg(Register.Cr8);
        public static readonly Operand.OpReg Cr9 = new Operand.OpReg(Register.Cr9);
        public static readonly Operand.OpReg Cr10 = new Operand.OpReg(Register.Cr10);
        public static readonly Operand.OpReg Cr11 = new Operand.OpReg(Register.Cr11);
        public static readonly Operand.OpReg Cr12 = new Operand.OpReg(Register.Cr12);
        public static readonly Operand.OpReg Cr13 = new Operand.OpReg(Register.Cr13);
        public static readonly Operand.OpReg Cr14 = new Operand.OpReg(Register.Cr14);
        public static readonly Operand.OpReg Cr15 = new Operand.OpReg(Register.Cr15);
        // Debug registers
        public static readonly Operand.OpReg Dr0 = new Operand.OpReg(Register.Dr0);
        public static readonly Operand.OpReg Dr1 = new Operand.OpReg(Register.Dr1);
        public static readonly Operand.OpReg Dr2 = new Operand.OpReg(Register.Dr2);
        public static readonly Operand.OpReg Dr3 = new Operand.OpReg(Register.Dr3);
        public static readonly Operand.OpReg Dr4 = new Operand.OpReg(Register.Dr4);
        public static readonly Operand.OpReg Dr5 = new Operand.OpReg(Register.Dr5);
        public static readonly Operand.OpReg Dr6 = new Operand.OpReg(Register.Dr6);
        public static readonly Operand.OpReg Dr7 = new Operand.OpReg(Register.Dr7);
        public static readonly Operand.OpReg Dr8 = new Operand.OpReg(Register.Dr8);
        public static readonly Operand.OpReg Dr9 = new Operand.OpReg(Register.Dr9);
        public static readonly Operand.OpReg Dr10 = new Operand.OpReg(Register.Dr10);
        public static readonly Operand.OpReg Dr11 = new Operand.OpReg(Register.Dr11);
        public static readonly Operand.OpReg Dr12 = new Operand.OpReg(Register.Dr12);
        public static readonly Operand.OpReg Dr13 = new Operand.OpReg(Register.Dr13);
        public static readonly Operand.OpReg Dr14 = new Operand.OpReg(Register.Dr14);
        public static readonly Operand.OpReg Dr15 = new Operand.OpReg(Register.Dr15);
        // Mask registers
        public static readonly Operand.OpReg K0 = new Operand.OpReg(Register.K0);
        public static readonly Operand.OpReg K1 = new Operand.OpReg(Register.K1);
        public static readonly Operand.OpReg K2 = new Operand.OpReg(Register.K2);
        public static readonly Operand.OpReg K3 = new Operand.OpReg(Register.K3);
        public static readonly Operand.OpReg K4 = new Operand.OpReg(Register.K4);
        public static readonly Operand.OpReg K5 = new Operand.OpReg(Register.K5);
        public static readonly Operand.OpReg K6 = new Operand.OpReg(Register.K6);
        public static readonly Operand.OpReg K7 = new Operand.OpReg(Register.K7);
        // Bound registers
        public static readonly Operand.OpReg Bnd0 = new Operand.OpReg(Register.Bnd0);
        public static readonly Operand.OpReg Bnd1 = new Operand.OpReg(Register.Bnd1);
        public static readonly Operand.OpReg Bnd2 = new Operand.OpReg(Register.Bnd2);
        public static readonly Operand.OpReg Bnd3 = new Operand.OpReg(Register.Bnd3);
        public static readonly Operand.OpReg BndCfg = new Operand.OpReg(Register.BndCfg);
        public static readonly Operand.OpReg BndStatus = new Operand.OpReg(Register.BndStatus);
        // Uncategorized
        public static readonly Operand.OpReg Mxcsr = new Operand.OpReg(Register.Mxcsr);
        public static readonly Operand.OpReg Pkru = new Operand.OpReg(Register.Pkru);
        public static readonly Operand.OpReg Xcr0 = new Operand.OpReg(Register.Xcr0);

        public static Operand.OpReg Reg(Register reg)
        {
            return new(reg);
        }

    }
}
