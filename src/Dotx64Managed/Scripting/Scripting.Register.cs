using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    internal class BadRegisterAccess : Exception
    {
        internal BadRegisterAccess(string message)
            : base(message)
        {
        }
    }

    public static partial class Scripting
    {
        internal static Thread GetThread()
        {
            var active = Thread.Active;

            if (active == null)
                throw new BadRegisterAccess("Register access requires an active thread");

            return active;
        }

        public static byte Al { get => GetThread().Al; set => GetThread().Al = value; }
        public static byte Cl { get => GetThread().Cl; set => GetThread().Cl = value; }
        public static byte Dl { get => GetThread().Dl; set => GetThread().Dl = value; }
        public static byte Bl { get => GetThread().Bl; set => GetThread().Bl = value; }
        public static byte Ah { get => GetThread().Ah; set => GetThread().Ah = value; }
        public static byte Ch { get => GetThread().Ch; set => GetThread().Ch = value; }
        public static byte Dh { get => GetThread().Dh; set => GetThread().Dh = value; }
        public static byte Bh { get => GetThread().Bh; set => GetThread().Bh = value; }
        public static byte Spl { get => GetThread().Spl; set => GetThread().Spl = value; }
        public static byte Bpl { get => GetThread().Bpl; set => GetThread().Bpl = value; }
        public static byte Sil { get => GetThread().Sil; set => GetThread().Sil = value; }
        public static byte Dil { get => GetThread().Dil; set => GetThread().Dil = value; }
#if _X64_
        public static byte R8b { get => GetThread().R8b; set => GetThread().R8b = value; }
        public static byte R9b { get => GetThread().R9b; set => GetThread().R9b = value; }
        public static byte R10b { get => GetThread().R10b; set => GetThread().R10b = value; }
        public static byte R11b { get => GetThread().R11b; set => GetThread().R11b = value; }
        public static byte R12b { get => GetThread().R12b; set => GetThread().R12b = value; }
        public static byte R13b { get => GetThread().R13b; set => GetThread().R13b = value; }
        public static byte R14b { get => GetThread().R14b; set => GetThread().R14b = value; }
        public static byte R15b { get => GetThread().R15b; set => GetThread().R15b = value; }
#endif
        public static ushort Ax { get => GetThread().Ax; set => GetThread().Ax = value; }
        public static ushort Cx { get => GetThread().Cx; set => GetThread().Cx = value; }
        public static ushort Dx { get => GetThread().Dx; set => GetThread().Dx = value; }
        public static ushort Bx { get => GetThread().Bx; set => GetThread().Bx = value; }
        public static ushort Sp { get => GetThread().Sp; set => GetThread().Sp = value; }
        public static ushort Bp { get => GetThread().Bp; set => GetThread().Bp = value; }
        public static ushort Si { get => GetThread().Si; set => GetThread().Si = value; }
        public static ushort Di { get => GetThread().Di; set => GetThread().Di = value; }
#if _X64_
        public static ushort R8w { get => GetThread().R8w; set => GetThread().R8w = value; }
        public static ushort R9w { get => GetThread().R9w; set => GetThread().R9w = value; }
        public static ushort R10w { get => GetThread().R10w; set => GetThread().R10w = value; }
        public static ushort R11w { get => GetThread().R11w; set => GetThread().R11w = value; }
        public static ushort R12w { get => GetThread().R12w; set => GetThread().R12w = value; }
        public static ushort R13w { get => GetThread().R13w; set => GetThread().R13w = value; }
        public static ushort R14w { get => GetThread().R14w; set => GetThread().R14w = value; }
        public static ushort R15w { get => GetThread().R15w; set => GetThread().R15w = value; }
#endif

#if _X64_
        public static uint Eax { get => GetThread().Eax; set => GetThread().Eax = value; }
        public static uint Ecx { get => GetThread().Ecx; set => GetThread().Ecx = value; }
        public static uint Edx { get => GetThread().Edx; set => GetThread().Edx = value; }
        public static uint Ebx { get => GetThread().Ebx; set => GetThread().Ebx = value; }
        public static uint Esp { get => GetThread().Esp; set => GetThread().Esp = value; }
        public static uint Ebp { get => GetThread().Ebp; set => GetThread().Ebp = value; }
        public static uint Esi { get => GetThread().Esi; set => GetThread().Esi = value; }
        public static uint Edi { get => GetThread().Edi; set => GetThread().Edi = value; }

        public static uint R8d { get => GetThread().R8d; set => GetThread().R8d = value; }
        public static uint R9d { get => GetThread().R9d; set => GetThread().R9d = value; }
        public static uint R10d { get => GetThread().R10d; set => GetThread().R10d = value; }
        public static uint R11d { get => GetThread().R11d; set => GetThread().R11d = value; }
        public static uint R12d { get => GetThread().R12d; set => GetThread().R12d = value; }
        public static uint R13d { get => GetThread().R13d; set => GetThread().R13d = value; }
        public static uint R14d { get => GetThread().R14d; set => GetThread().R14d = value; }
        public static uint R15d { get => GetThread().R15d; set => GetThread().R15d = value; }
        public static nuint Rax { get => GetThread().Rax; set => GetThread().Rax = value; }
        public static nuint Rcx { get => GetThread().Rcx; set => GetThread().Rcx = value; }
        public static nuint Rdx { get => GetThread().Rdx; set => GetThread().Rdx = value; }
        public static nuint Rbx { get => GetThread().Rbx; set => GetThread().Rbx = value; }
        public static nuint Rsp { get => GetThread().Rsp; set => GetThread().Rsp = value; }
        public static nuint Rbp { get => GetThread().Rbp; set => GetThread().Rbp = value; }
        public static nuint Rsi { get => GetThread().Rsi; set => GetThread().Rsi = value; }
        public static nuint Rdi { get => GetThread().Rdi; set => GetThread().Rdi = value; }
        public static nuint R8 { get => GetThread().R8; set => GetThread().R8 = value; }
        public static nuint R9 { get => GetThread().R9; set => GetThread().R9 = value; }
        public static nuint R10 { get => GetThread().R10; set => GetThread().R10 = value; }
        public static nuint R11 { get => GetThread().R11; set => GetThread().R11 = value; }
        public static nuint R12 { get => GetThread().R12; set => GetThread().R12 = value; }
        public static nuint R13 { get => GetThread().R13; set => GetThread().R13 = value; }
        public static nuint R14 { get => GetThread().R14; set => GetThread().R14 = value; }
        public static nuint R15 { get => GetThread().R15; set => GetThread().R15 = value; }
#else
        public static nuint Eax { get => GetThread().Eax; set => GetThread().Eax = value; }
        public static nuint Ecx { get => GetThread().Ecx; set => GetThread().Ecx = value; }
        public static nuint Edx { get => GetThread().Edx; set => GetThread().Edx = value; }
        public static nuint Ebx { get => GetThread().Ebx; set => GetThread().Ebx = value; }
        public static nuint Esp { get => GetThread().Esp; set => GetThread().Esp = value; }
        public static nuint Ebp { get => GetThread().Ebp; set => GetThread().Ebp = value; }
        public static nuint Esi { get => GetThread().Esi; set => GetThread().Esi = value; }
        public static nuint Edi { get => GetThread().Edi; set => GetThread().Edi = value; }
#endif
        public static BigInteger St0 { get => GetThread().St0; set => GetThread().St0 = value; }
        public static BigInteger St1 { get => GetThread().St1; set => GetThread().St1 = value; }
        public static BigInteger St2 { get => GetThread().St2; set => GetThread().St2 = value; }
        public static BigInteger St3 { get => GetThread().St3; set => GetThread().St3 = value; }
        public static BigInteger St4 { get => GetThread().St4; set => GetThread().St4 = value; }
        public static BigInteger St5 { get => GetThread().St5; set => GetThread().St5 = value; }
        public static BigInteger St6 { get => GetThread().St6; set => GetThread().St6 = value; }
        public static BigInteger St7 { get => GetThread().St7; set => GetThread().St7 = value; }
        public static BigInteger X87Control { get => GetThread().X87Control; set => GetThread().X87Control = value; }
        public static BigInteger X87Status { get => GetThread().X87Status; set => GetThread().X87Status = value; }
        public static BigInteger X87Tag { get => GetThread().X87Tag; set => GetThread().X87Tag = value; }
        public static BigInteger Mm0 { get => GetThread().Mm0; set => GetThread().Mm0 = value; }
        public static BigInteger Mm1 { get => GetThread().Mm1; set => GetThread().Mm1 = value; }
        public static BigInteger Mm2 { get => GetThread().Mm2; set => GetThread().Mm2 = value; }
        public static BigInteger Mm3 { get => GetThread().Mm3; set => GetThread().Mm3 = value; }
        public static BigInteger Mm4 { get => GetThread().Mm4; set => GetThread().Mm4 = value; }
        public static BigInteger Mm5 { get => GetThread().Mm5; set => GetThread().Mm5 = value; }
        public static BigInteger Mm6 { get => GetThread().Mm6; set => GetThread().Mm6 = value; }
        public static BigInteger Mm7 { get => GetThread().Mm7; set => GetThread().Mm7 = value; }
        public static BigInteger Xmm0 { get => GetThread().Xmm0; set => GetThread().Xmm0 = value; }
        public static BigInteger Xmm1 { get => GetThread().Xmm1; set => GetThread().Xmm1 = value; }
        public static BigInteger Xmm2 { get => GetThread().Xmm2; set => GetThread().Xmm2 = value; }
        public static BigInteger Xmm3 { get => GetThread().Xmm3; set => GetThread().Xmm3 = value; }
        public static BigInteger Xmm4 { get => GetThread().Xmm4; set => GetThread().Xmm4 = value; }
        public static BigInteger Xmm5 { get => GetThread().Xmm5; set => GetThread().Xmm5 = value; }
        public static BigInteger Xmm6 { get => GetThread().Xmm6; set => GetThread().Xmm6 = value; }
        public static BigInteger Xmm7 { get => GetThread().Xmm7; set => GetThread().Xmm7 = value; }
        public static BigInteger Xmm8 { get => GetThread().Xmm8; set => GetThread().Xmm8 = value; }
        public static BigInteger Xmm9 { get => GetThread().Xmm9; set => GetThread().Xmm9 = value; }
        public static BigInteger Xmm10 { get => GetThread().Xmm10; set => GetThread().Xmm10 = value; }
        public static BigInteger Xmm11 { get => GetThread().Xmm11; set => GetThread().Xmm11 = value; }
        public static BigInteger Xmm12 { get => GetThread().Xmm12; set => GetThread().Xmm12 = value; }
        public static BigInteger Xmm13 { get => GetThread().Xmm13; set => GetThread().Xmm13 = value; }
        public static BigInteger Xmm14 { get => GetThread().Xmm14; set => GetThread().Xmm14 = value; }
        public static BigInteger Xmm15 { get => GetThread().Xmm15; set => GetThread().Xmm15 = value; }
        public static BigInteger Xmm16 { get => GetThread().Xmm16; set => GetThread().Xmm16 = value; }
        public static BigInteger Xmm17 { get => GetThread().Xmm17; set => GetThread().Xmm17 = value; }
        public static BigInteger Xmm18 { get => GetThread().Xmm18; set => GetThread().Xmm18 = value; }
        public static BigInteger Xmm19 { get => GetThread().Xmm19; set => GetThread().Xmm19 = value; }
        public static BigInteger Xmm20 { get => GetThread().Xmm20; set => GetThread().Xmm20 = value; }
        public static BigInteger Xmm21 { get => GetThread().Xmm21; set => GetThread().Xmm21 = value; }
        public static BigInteger Xmm22 { get => GetThread().Xmm22; set => GetThread().Xmm22 = value; }
        public static BigInteger Xmm23 { get => GetThread().Xmm23; set => GetThread().Xmm23 = value; }
        public static BigInteger Xmm24 { get => GetThread().Xmm24; set => GetThread().Xmm24 = value; }
        public static BigInteger Xmm25 { get => GetThread().Xmm25; set => GetThread().Xmm25 = value; }
        public static BigInteger Xmm26 { get => GetThread().Xmm26; set => GetThread().Xmm26 = value; }
        public static BigInteger Xmm27 { get => GetThread().Xmm27; set => GetThread().Xmm27 = value; }
        public static BigInteger Xmm28 { get => GetThread().Xmm28; set => GetThread().Xmm28 = value; }
        public static BigInteger Xmm29 { get => GetThread().Xmm29; set => GetThread().Xmm29 = value; }
        public static BigInteger Xmm30 { get => GetThread().Xmm30; set => GetThread().Xmm30 = value; }
        public static BigInteger Xmm31 { get => GetThread().Xmm31; set => GetThread().Xmm31 = value; }
        public static BigInteger Ymm0 { get => GetThread().Ymm0; set => GetThread().Ymm0 = value; }
        public static BigInteger Ymm1 { get => GetThread().Ymm1; set => GetThread().Ymm1 = value; }
        public static BigInteger Ymm2 { get => GetThread().Ymm2; set => GetThread().Ymm2 = value; }
        public static BigInteger Ymm3 { get => GetThread().Ymm3; set => GetThread().Ymm3 = value; }
        public static BigInteger Ymm4 { get => GetThread().Ymm4; set => GetThread().Ymm4 = value; }
        public static BigInteger Ymm5 { get => GetThread().Ymm5; set => GetThread().Ymm5 = value; }
        public static BigInteger Ymm6 { get => GetThread().Ymm6; set => GetThread().Ymm6 = value; }
        public static BigInteger Ymm7 { get => GetThread().Ymm7; set => GetThread().Ymm7 = value; }
        public static BigInteger Ymm8 { get => GetThread().Ymm8; set => GetThread().Ymm8 = value; }
        public static BigInteger Ymm9 { get => GetThread().Ymm9; set => GetThread().Ymm9 = value; }
        public static BigInteger Ymm10 { get => GetThread().Ymm10; set => GetThread().Ymm10 = value; }
        public static BigInteger Ymm11 { get => GetThread().Ymm11; set => GetThread().Ymm11 = value; }
        public static BigInteger Ymm12 { get => GetThread().Ymm12; set => GetThread().Ymm12 = value; }
        public static BigInteger Ymm13 { get => GetThread().Ymm13; set => GetThread().Ymm13 = value; }
        public static BigInteger Ymm14 { get => GetThread().Ymm14; set => GetThread().Ymm14 = value; }
        public static BigInteger Ymm15 { get => GetThread().Ymm15; set => GetThread().Ymm15 = value; }
        public static BigInteger Ymm16 { get => GetThread().Ymm16; set => GetThread().Ymm16 = value; }
        public static BigInteger Ymm17 { get => GetThread().Ymm17; set => GetThread().Ymm17 = value; }
        public static BigInteger Ymm18 { get => GetThread().Ymm18; set => GetThread().Ymm18 = value; }
        public static BigInteger Ymm19 { get => GetThread().Ymm19; set => GetThread().Ymm19 = value; }
        public static BigInteger Ymm20 { get => GetThread().Ymm20; set => GetThread().Ymm20 = value; }
        public static BigInteger Ymm21 { get => GetThread().Ymm21; set => GetThread().Ymm21 = value; }
        public static BigInteger Ymm22 { get => GetThread().Ymm22; set => GetThread().Ymm22 = value; }
        public static BigInteger Ymm23 { get => GetThread().Ymm23; set => GetThread().Ymm23 = value; }
        public static BigInteger Ymm24 { get => GetThread().Ymm24; set => GetThread().Ymm24 = value; }
        public static BigInteger Ymm25 { get => GetThread().Ymm25; set => GetThread().Ymm25 = value; }
        public static BigInteger Ymm26 { get => GetThread().Ymm26; set => GetThread().Ymm26 = value; }
        public static BigInteger Ymm27 { get => GetThread().Ymm27; set => GetThread().Ymm27 = value; }
        public static BigInteger Ymm28 { get => GetThread().Ymm28; set => GetThread().Ymm28 = value; }
        public static BigInteger Ymm29 { get => GetThread().Ymm29; set => GetThread().Ymm29 = value; }
        public static BigInteger Ymm30 { get => GetThread().Ymm30; set => GetThread().Ymm30 = value; }
        public static BigInteger Ymm31 { get => GetThread().Ymm31; set => GetThread().Ymm31 = value; }
        public static BigInteger Zmm0 { get => GetThread().Zmm0; set => GetThread().Zmm0 = value; }
        public static BigInteger Zmm1 { get => GetThread().Zmm1; set => GetThread().Zmm1 = value; }
        public static BigInteger Zmm2 { get => GetThread().Zmm2; set => GetThread().Zmm2 = value; }
        public static BigInteger Zmm3 { get => GetThread().Zmm3; set => GetThread().Zmm3 = value; }
        public static BigInteger Zmm4 { get => GetThread().Zmm4; set => GetThread().Zmm4 = value; }
        public static BigInteger Zmm5 { get => GetThread().Zmm5; set => GetThread().Zmm5 = value; }
        public static BigInteger Zmm6 { get => GetThread().Zmm6; set => GetThread().Zmm6 = value; }
        public static BigInteger Zmm7 { get => GetThread().Zmm7; set => GetThread().Zmm7 = value; }
        public static BigInteger Zmm8 { get => GetThread().Zmm8; set => GetThread().Zmm8 = value; }
        public static BigInteger Zmm9 { get => GetThread().Zmm9; set => GetThread().Zmm9 = value; }
        public static BigInteger Zmm10 { get => GetThread().Zmm10; set => GetThread().Zmm10 = value; }
        public static BigInteger Zmm11 { get => GetThread().Zmm11; set => GetThread().Zmm11 = value; }
        public static BigInteger Zmm12 { get => GetThread().Zmm12; set => GetThread().Zmm12 = value; }
        public static BigInteger Zmm13 { get => GetThread().Zmm13; set => GetThread().Zmm13 = value; }
        public static BigInteger Zmm14 { get => GetThread().Zmm14; set => GetThread().Zmm14 = value; }
        public static BigInteger Zmm15 { get => GetThread().Zmm15; set => GetThread().Zmm15 = value; }
        public static BigInteger Zmm16 { get => GetThread().Zmm16; set => GetThread().Zmm16 = value; }
        public static BigInteger Zmm17 { get => GetThread().Zmm17; set => GetThread().Zmm17 = value; }
        public static BigInteger Zmm18 { get => GetThread().Zmm18; set => GetThread().Zmm18 = value; }
        public static BigInteger Zmm19 { get => GetThread().Zmm19; set => GetThread().Zmm19 = value; }
        public static BigInteger Zmm20 { get => GetThread().Zmm20; set => GetThread().Zmm20 = value; }
        public static BigInteger Zmm21 { get => GetThread().Zmm21; set => GetThread().Zmm21 = value; }
        public static BigInteger Zmm22 { get => GetThread().Zmm22; set => GetThread().Zmm22 = value; }
        public static BigInteger Zmm23 { get => GetThread().Zmm23; set => GetThread().Zmm23 = value; }
        public static BigInteger Zmm24 { get => GetThread().Zmm24; set => GetThread().Zmm24 = value; }
        public static BigInteger Zmm25 { get => GetThread().Zmm25; set => GetThread().Zmm25 = value; }
        public static BigInteger Zmm26 { get => GetThread().Zmm26; set => GetThread().Zmm26 = value; }
        public static BigInteger Zmm27 { get => GetThread().Zmm27; set => GetThread().Zmm27 = value; }
        public static BigInteger Zmm28 { get => GetThread().Zmm28; set => GetThread().Zmm28 = value; }
        public static BigInteger Zmm29 { get => GetThread().Zmm29; set => GetThread().Zmm29 = value; }
        public static BigInteger Zmm30 { get => GetThread().Zmm30; set => GetThread().Zmm30 = value; }
        public static BigInteger Zmm31 { get => GetThread().Zmm31; set => GetThread().Zmm31 = value; }
        public static BigInteger Flags { get => GetThread().Flags; set => GetThread().Flags = value; }
#if _X64_
        public static uint EFlags { get => GetThread().EFlags; set => GetThread().EFlags = value; }
        public static nuint RFlags { get => GetThread().RFlags; set => GetThread().RFlags = value; }
#else
        public static nuint EFlags { get => GetThread().EFlags; set => GetThread().EFlags = value; }
#endif
        public static ushort Ip { get => GetThread().Ip; set => GetThread().Ip = value; }

#if _X64_
        public static uint Eip { get => GetThread().Eip; set => GetThread().Eip = value; }
        public static nuint Rip { get => GetThread().Rip; set => GetThread().Rip = value; }
#else
        public static nuint Eip { get => GetThread().Eip; set => GetThread().Eip = value; }
#endif

        public static ushort Es { get => GetThread().Es; set => GetThread().Es = value; }
        public static ushort Cs { get => GetThread().Cs; set => GetThread().Cs = value; }
        public static ushort Ss { get => GetThread().Ss; set => GetThread().Ss = value; }
        public static ushort Ds { get => GetThread().Ds; set => GetThread().Ds = value; }
        public static ushort Fs { get => GetThread().Fs; set => GetThread().Fs = value; }
        public static ushort Gs { get => GetThread().Gs; set => GetThread().Gs = value; }
        public static BigInteger Gdtr { get => GetThread().Gdtr; set => GetThread().Gdtr = value; }
        public static BigInteger Ldtr { get => GetThread().Ldtr; set => GetThread().Ldtr = value; }
        public static BigInteger Idtr { get => GetThread().Idtr; set => GetThread().Idtr = value; }
        public static BigInteger Tr { get => GetThread().Tr; set => GetThread().Tr = value; }
        public static BigInteger Tr0 { get => GetThread().Tr0; set => GetThread().Tr0 = value; }
        public static BigInteger Tr1 { get => GetThread().Tr1; set => GetThread().Tr1 = value; }
        public static BigInteger Tr2 { get => GetThread().Tr2; set => GetThread().Tr2 = value; }
        public static BigInteger Tr3 { get => GetThread().Tr3; set => GetThread().Tr3 = value; }
        public static BigInteger Tr4 { get => GetThread().Tr4; set => GetThread().Tr4 = value; }
        public static BigInteger Tr5 { get => GetThread().Tr5; set => GetThread().Tr5 = value; }
        public static BigInteger Tr6 { get => GetThread().Tr6; set => GetThread().Tr6 = value; }
        public static BigInteger Tr7 { get => GetThread().Tr7; set => GetThread().Tr7 = value; }
        public static BigInteger Cr0 { get => GetThread().Cr0; set => GetThread().Cr0 = value; }
        public static BigInteger Cr1 { get => GetThread().Cr1; set => GetThread().Cr1 = value; }
        public static BigInteger Cr2 { get => GetThread().Cr2; set => GetThread().Cr2 = value; }
        public static BigInteger Cr3 { get => GetThread().Cr3; set => GetThread().Cr3 = value; }
        public static BigInteger Cr4 { get => GetThread().Cr4; set => GetThread().Cr4 = value; }
        public static BigInteger Cr5 { get => GetThread().Cr5; set => GetThread().Cr5 = value; }
        public static BigInteger Cr6 { get => GetThread().Cr6; set => GetThread().Cr6 = value; }
        public static BigInteger Cr7 { get => GetThread().Cr7; set => GetThread().Cr7 = value; }
        public static BigInteger Cr8 { get => GetThread().Cr8; set => GetThread().Cr8 = value; }
        public static BigInteger Cr9 { get => GetThread().Cr9; set => GetThread().Cr9 = value; }
        public static BigInteger Cr10 { get => GetThread().Cr10; set => GetThread().Cr10 = value; }
        public static BigInteger Cr11 { get => GetThread().Cr11; set => GetThread().Cr11 = value; }
        public static BigInteger Cr12 { get => GetThread().Cr12; set => GetThread().Cr12 = value; }
        public static BigInteger Cr13 { get => GetThread().Cr13; set => GetThread().Cr13 = value; }
        public static BigInteger Cr14 { get => GetThread().Cr14; set => GetThread().Cr14 = value; }
        public static BigInteger Cr15 { get => GetThread().Cr15; set => GetThread().Cr15 = value; }

        public static nuint Dr0 { get => GetThread().Dr0; set => GetThread().Dr0 = value; }
        public static nuint Dr1 { get => GetThread().Dr1; set => GetThread().Dr1 = value; }
        public static nuint Dr2 { get => GetThread().Dr2; set => GetThread().Dr2 = value; }
        public static nuint Dr3 { get => GetThread().Dr3; set => GetThread().Dr3 = value; }
        public static nuint Dr4 { get => GetThread().Dr4; set => GetThread().Dr4 = value; }
        public static nuint Dr5 { get => GetThread().Dr5; set => GetThread().Dr5 = value; }
        public static nuint Dr6 { get => GetThread().Dr6; set => GetThread().Dr6 = value; }
        public static nuint Dr7 { get => GetThread().Dr7; set => GetThread().Dr7 = value; }
        public static nuint Dr8 { get => GetThread().Dr8; set => GetThread().Dr8 = value; }
        public static nuint Dr9 { get => GetThread().Dr9; set => GetThread().Dr9 = value; }
        public static nuint Dr10 { get => GetThread().Dr10; set => GetThread().Dr10 = value; }
        public static nuint Dr11 { get => GetThread().Dr11; set => GetThread().Dr11 = value; }
        public static nuint Dr12 { get => GetThread().Dr12; set => GetThread().Dr12 = value; }
        public static nuint Dr13 { get => GetThread().Dr13; set => GetThread().Dr13 = value; }
        public static nuint Dr14 { get => GetThread().Dr14; set => GetThread().Dr14 = value; }
        public static nuint Dr15 { get => GetThread().Dr15; set => GetThread().Dr15 = value; }

        public static BigInteger K0 { get => GetThread().K0; set => GetThread().K0 = value; }
        public static BigInteger K1 { get => GetThread().K1; set => GetThread().K1 = value; }
        public static BigInteger K2 { get => GetThread().K2; set => GetThread().K2 = value; }
        public static BigInteger K3 { get => GetThread().K3; set => GetThread().K3 = value; }
        public static BigInteger K4 { get => GetThread().K4; set => GetThread().K4 = value; }
        public static BigInteger K5 { get => GetThread().K5; set => GetThread().K5 = value; }
        public static BigInteger K6 { get => GetThread().K6; set => GetThread().K6 = value; }
        public static BigInteger K7 { get => GetThread().K7; set => GetThread().K7 = value; }
        public static BigInteger Bnd0 { get => GetThread().Bnd0; set => GetThread().Bnd0 = value; }
        public static BigInteger Bnd1 { get => GetThread().Bnd1; set => GetThread().Bnd1 = value; }
        public static BigInteger Bnd2 { get => GetThread().Bnd2; set => GetThread().Bnd2 = value; }
        public static BigInteger Bnd3 { get => GetThread().Bnd3; set => GetThread().Bnd3 = value; }
        public static BigInteger BndCfg { get => GetThread().BndCfg; set => GetThread().BndCfg = value; }
        public static BigInteger BndStatus { get => GetThread().BndStatus; set => GetThread().BndStatus = value; }
        public static BigInteger Mxcsr { get => GetThread().Mxcsr; set => GetThread().Mxcsr = value; }
        public static BigInteger Pkru { get => GetThread().Pkru; set => GetThread().Pkru = value; }
        public static BigInteger Xcr0 { get => GetThread().Xcr0; set => GetThread().Xcr0 = value; }

        // Host Specific
#if _X64_
        public static nuint Nax { get => GetThread().Rax; set => GetThread().Rax = value; }
        public static nuint Ncx { get => GetThread().Rcx; set => GetThread().Rcx = value; }
        public static nuint Ndx { get => GetThread().Rdx; set => GetThread().Rdx = value; }
        public static nuint Nbx { get => GetThread().Rbx; set => GetThread().Rbx = value; }
        public static nuint Nsp { get => GetThread().Rsp; set => GetThread().Rsp = value; }
        public static nuint Nbp { get => GetThread().Rbp; set => GetThread().Rbp = value; }
        public static nuint Nsi { get => GetThread().Rsi; set => GetThread().Rsi = value; }
        public static nuint Ndi { get => GetThread().Rdi; set => GetThread().Rdi = value; }
        public static nuint Nip { get => GetThread().Rip; set => GetThread().Rip = value; }
#else 
        public static nuint Nax { get => GetThread().Eax; set => GetThread().Eax = value; }
        public static nuint Ncx { get => GetThread().Ecx; set => GetThread().Ecx = value; }
        public static nuint Ndx { get => GetThread().Edx; set => GetThread().Edx = value; }
        public static nuint Nbx { get => GetThread().Ebx; set => GetThread().Ebx = value; }
        public static nuint Nsp { get => GetThread().Esp; set => GetThread().Esp = value; }
        public static nuint Nbp { get => GetThread().Ebp; set => GetThread().Ebp = value; }
        public static nuint Nsi { get => GetThread().Esi; set => GetThread().Esi = value; }
        public static nuint Ndi { get => GetThread().Edi; set => GetThread().Edi = value; }
        public static nuint Nip { get => GetThread().Eip; set => GetThread().Eip = value; }
#endif
    }
}
