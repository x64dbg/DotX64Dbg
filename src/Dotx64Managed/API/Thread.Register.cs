using System;
using System.Numerics;

namespace Dotx64Dbg
{
    public partial class Thread
    {
        private byte GetRegisterU8(RegisterId reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return bytes[0];
        }

        private void SetRegisterU8(RegisterId reg, byte val)
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private ushort GetRegisterU16(RegisterId reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt16(bytes);
        }

        private void SetRegisterU16(RegisterId reg, ushort val)
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private uint GetRegisterU32(RegisterId reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt32(bytes);
        }

#if _X64_
        private void SetRegisterU32(RegisterId reg, uint val)
#else

        private void SetRegisterU32(RegisterId reg, nuint val)
#endif
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private ulong GetRegisterU64(RegisterId reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt64(bytes);
        }


#if _X64_
        private void SetRegisterU64(RegisterId reg, nuint val)
#else

        private void SetRegisterU64(RegisterId reg, ulong val)
#endif
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        public BigInteger GetRegister(RegisterId reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return new BigInteger(bytes, true);
        }

        public void SetRegister(RegisterId reg, BigInteger val)
        {
            Native.Thread.SetRegisterData(Handle, reg, val.ToByteArray());
        }

        public byte Al { get => GetRegisterU8(RegisterId.Al); set => SetRegisterU8(RegisterId.Al, value); }
        public byte Cl { get => GetRegisterU8(RegisterId.Cl); set => SetRegisterU8(RegisterId.Cl, value); }
        public byte Dl { get => GetRegisterU8(RegisterId.Dl); set => SetRegisterU8(RegisterId.Dl, value); }
        public byte Bl { get => GetRegisterU8(RegisterId.Bl); set => SetRegisterU8(RegisterId.Bl, value); }
        public byte Ah { get => GetRegisterU8(RegisterId.Ah); set => SetRegisterU8(RegisterId.Ah, value); }
        public byte Ch { get => GetRegisterU8(RegisterId.Ch); set => SetRegisterU8(RegisterId.Ch, value); }
        public byte Dh { get => GetRegisterU8(RegisterId.Dh); set => SetRegisterU8(RegisterId.Dh, value); }
        public byte Bh { get => GetRegisterU8(RegisterId.Bh); set => SetRegisterU8(RegisterId.Bh, value); }
        public byte Spl { get => GetRegisterU8(RegisterId.Spl); set => SetRegisterU8(RegisterId.Spl, value); }
        public byte Bpl { get => GetRegisterU8(RegisterId.Bpl); set => SetRegisterU8(RegisterId.Bpl, value); }
        public byte Sil { get => GetRegisterU8(RegisterId.Sil); set => SetRegisterU8(RegisterId.Sil, value); }
        public byte Dil { get => GetRegisterU8(RegisterId.Dil); set => SetRegisterU8(RegisterId.Dil, value); }
#if _X64_
        public byte R8b { get => GetRegisterU8(RegisterId.R8b); set => SetRegisterU8(RegisterId.R8b, value); }
        public byte R9b { get => GetRegisterU8(RegisterId.R9b); set => SetRegisterU8(RegisterId.R9b, value); }
        public byte R10b { get => GetRegisterU8(RegisterId.R10b); set => SetRegisterU8(RegisterId.R10b, value); }
        public byte R11b { get => GetRegisterU8(RegisterId.R11b); set => SetRegisterU8(RegisterId.R11b, value); }
        public byte R12b { get => GetRegisterU8(RegisterId.R12b); set => SetRegisterU8(RegisterId.R12b, value); }
        public byte R13b { get => GetRegisterU8(RegisterId.R13b); set => SetRegisterU8(RegisterId.R13b, value); }
        public byte R14b { get => GetRegisterU8(RegisterId.R14b); set => SetRegisterU8(RegisterId.R14b, value); }
        public byte R15b { get => GetRegisterU8(RegisterId.R15b); set => SetRegisterU8(RegisterId.R15b, value); }
#endif
        public ushort Ax { get => GetRegisterU16(RegisterId.Ax); set => SetRegisterU16(RegisterId.Ax, value); }
        public ushort Cx { get => GetRegisterU16(RegisterId.Cx); set => SetRegisterU16(RegisterId.Cx, value); }
        public ushort Dx { get => GetRegisterU16(RegisterId.Dx); set => SetRegisterU16(RegisterId.Dx, value); }
        public ushort Bx { get => GetRegisterU16(RegisterId.Bx); set => SetRegisterU16(RegisterId.Bx, value); }
        public ushort Sp { get => GetRegisterU16(RegisterId.Sp); set => SetRegisterU16(RegisterId.Sp, value); }
        public ushort Bp { get => GetRegisterU16(RegisterId.Bp); set => SetRegisterU16(RegisterId.Bp, value); }
        public ushort Si { get => GetRegisterU16(RegisterId.Si); set => SetRegisterU16(RegisterId.Si, value); }
        public ushort Di { get => GetRegisterU16(RegisterId.Di); set => SetRegisterU16(RegisterId.Di, value); }
#if _X64_
        public ushort R8w { get => GetRegisterU16(RegisterId.R8w); set => SetRegisterU16(RegisterId.R8w, value); }
        public ushort R9w { get => GetRegisterU16(RegisterId.R9w); set => SetRegisterU16(RegisterId.R9w, value); }
        public ushort R10w { get => GetRegisterU16(RegisterId.R10w); set => SetRegisterU16(RegisterId.R10w, value); }
        public ushort R11w { get => GetRegisterU16(RegisterId.R11w); set => SetRegisterU16(RegisterId.R11w, value); }
        public ushort R12w { get => GetRegisterU16(RegisterId.R12w); set => SetRegisterU16(RegisterId.R12w, value); }
        public ushort R13w { get => GetRegisterU16(RegisterId.R13w); set => SetRegisterU16(RegisterId.R13w, value); }
        public ushort R14w { get => GetRegisterU16(RegisterId.R14w); set => SetRegisterU16(RegisterId.R14w, value); }
        public ushort R15w { get => GetRegisterU16(RegisterId.R15w); set => SetRegisterU16(RegisterId.R15w, value); }
#endif

#if _X64_
        public uint Eax { get => GetRegisterU32(RegisterId.Eax); set => SetRegisterU32(RegisterId.Eax, value); }
        public uint Ecx { get => GetRegisterU32(RegisterId.Ecx); set => SetRegisterU32(RegisterId.Ecx, value); }
        public uint Edx { get => GetRegisterU32(RegisterId.Edx); set => SetRegisterU32(RegisterId.Edx, value); }
        public uint Ebx { get => GetRegisterU32(RegisterId.Ebx); set => SetRegisterU32(RegisterId.Ebx, value); }
        public uint Esp { get => GetRegisterU32(RegisterId.Esp); set => SetRegisterU32(RegisterId.Esp, value); }
        public uint Ebp { get => GetRegisterU32(RegisterId.Ebp); set => SetRegisterU32(RegisterId.Ebp, value); }
        public uint Esi { get => GetRegisterU32(RegisterId.Esi); set => SetRegisterU32(RegisterId.Esi, value); }
        public uint Edi { get => GetRegisterU32(RegisterId.Edi); set => SetRegisterU32(RegisterId.Edi, value); }
#else
        public nuint Eax { get => (nuint)GetRegisterU32(RegisterId.Eax); set => SetRegisterU32(RegisterId.Eax, value); }
        public nuint Ecx { get => (nuint)GetRegisterU32(RegisterId.Ecx); set => SetRegisterU32(RegisterId.Ecx, value); }
        public nuint Edx { get => (nuint)GetRegisterU32(RegisterId.Edx); set => SetRegisterU32(RegisterId.Edx, value); }
        public nuint Ebx { get => (nuint)GetRegisterU32(RegisterId.Ebx); set => SetRegisterU32(RegisterId.Ebx, value); }
        public nuint Esp { get => (nuint)GetRegisterU32(RegisterId.Esp); set => SetRegisterU32(RegisterId.Esp, value); }
        public nuint Ebp { get => (nuint)GetRegisterU32(RegisterId.Ebp); set => SetRegisterU32(RegisterId.Ebp, value); }
        public nuint Esi { get => (nuint)GetRegisterU32(RegisterId.Esi); set => SetRegisterU32(RegisterId.Esi, value); }
        public nuint Edi { get => (nuint)GetRegisterU32(RegisterId.Edi); set => SetRegisterU32(RegisterId.Edi, value); }
#endif

#if _X64_
        public uint R8d { get => GetRegisterU32(RegisterId.R8d); set => SetRegisterU32(RegisterId.R8d, value); }
        public uint R9d { get => GetRegisterU32(RegisterId.R9d); set => SetRegisterU32(RegisterId.R9d, value); }
        public uint R10d { get => GetRegisterU32(RegisterId.R10d); set => SetRegisterU32(RegisterId.R10d, value); }
        public uint R11d { get => GetRegisterU32(RegisterId.R11d); set => SetRegisterU32(RegisterId.R11d, value); }
        public uint R12d { get => GetRegisterU32(RegisterId.R12d); set => SetRegisterU32(RegisterId.R12d, value); }
        public uint R13d { get => GetRegisterU32(RegisterId.R13d); set => SetRegisterU32(RegisterId.R13d, value); }
        public uint R14d { get => GetRegisterU32(RegisterId.R14d); set => SetRegisterU32(RegisterId.R14d, value); }
        public uint R15d { get => GetRegisterU32(RegisterId.R15d); set => SetRegisterU32(RegisterId.R15d, value); }
        public nuint Rax { get => (nuint)GetRegisterU64(RegisterId.Rax); set => SetRegisterU64(RegisterId.Rax, value); }
        public nuint Rcx { get => (nuint)GetRegisterU64(RegisterId.Rcx); set => SetRegisterU64(RegisterId.Rcx, value); }
        public nuint Rdx { get => (nuint)GetRegisterU64(RegisterId.Rdx); set => SetRegisterU64(RegisterId.Rdx, value); }
        public nuint Rbx { get => (nuint)GetRegisterU64(RegisterId.Rbx); set => SetRegisterU64(RegisterId.Rbx, value); }
        public nuint Rsp { get => (nuint)GetRegisterU64(RegisterId.Rsp); set => SetRegisterU64(RegisterId.Rsp, value); }
        public nuint Rbp { get => (nuint)GetRegisterU64(RegisterId.Rbp); set => SetRegisterU64(RegisterId.Rbp, value); }
        public nuint Rsi { get => (nuint)GetRegisterU64(RegisterId.Rsi); set => SetRegisterU64(RegisterId.Rsi, value); }
        public nuint Rdi { get => (nuint)GetRegisterU64(RegisterId.Rdi); set => SetRegisterU64(RegisterId.Rdi, value); }
        public nuint R8 { get => (nuint)GetRegisterU64(RegisterId.R8); set => SetRegisterU64(RegisterId.R8, value); }
        public nuint R9 { get => (nuint)GetRegisterU64(RegisterId.R9); set => SetRegisterU64(RegisterId.R9, value); }
        public nuint R10 { get => (nuint)GetRegisterU64(RegisterId.R10); set => SetRegisterU64(RegisterId.R10, value); }
        public nuint R11 { get => (nuint)GetRegisterU64(RegisterId.R11); set => SetRegisterU64(RegisterId.R11, value); }
        public nuint R12 { get => (nuint)GetRegisterU64(RegisterId.R12); set => SetRegisterU64(RegisterId.R12, value); }
        public nuint R13 { get => (nuint)GetRegisterU64(RegisterId.R13); set => SetRegisterU64(RegisterId.R13, value); }
        public nuint R14 { get => (nuint)GetRegisterU64(RegisterId.R14); set => SetRegisterU64(RegisterId.R14, value); }
        public nuint R15 { get => (nuint)GetRegisterU64(RegisterId.R15); set => SetRegisterU64(RegisterId.R15, value); }
#endif
        public BigInteger St0 { get => GetRegister(RegisterId.St0); set => SetRegister(RegisterId.St0, value); }
        public BigInteger St1 { get => GetRegister(RegisterId.St1); set => SetRegister(RegisterId.St1, value); }
        public BigInteger St2 { get => GetRegister(RegisterId.St2); set => SetRegister(RegisterId.St2, value); }
        public BigInteger St3 { get => GetRegister(RegisterId.St3); set => SetRegister(RegisterId.St3, value); }
        public BigInteger St4 { get => GetRegister(RegisterId.St4); set => SetRegister(RegisterId.St4, value); }
        public BigInteger St5 { get => GetRegister(RegisterId.St5); set => SetRegister(RegisterId.St5, value); }
        public BigInteger St6 { get => GetRegister(RegisterId.St6); set => SetRegister(RegisterId.St6, value); }
        public BigInteger St7 { get => GetRegister(RegisterId.St7); set => SetRegister(RegisterId.St7, value); }
        public BigInteger X87Control { get => GetRegister(RegisterId.X87Control); set => SetRegister(RegisterId.X87Control, value); }
        public BigInteger X87Status { get => GetRegister(RegisterId.X87Status); set => SetRegister(RegisterId.X87Status, value); }
        public BigInteger X87Tag { get => GetRegister(RegisterId.X87Tag); set => SetRegister(RegisterId.X87Tag, value); }
        public BigInteger Mm0 { get => GetRegister(RegisterId.Mm0); set => SetRegister(RegisterId.Mm0, value); }
        public BigInteger Mm1 { get => GetRegister(RegisterId.Mm1); set => SetRegister(RegisterId.Mm1, value); }
        public BigInteger Mm2 { get => GetRegister(RegisterId.Mm2); set => SetRegister(RegisterId.Mm2, value); }
        public BigInteger Mm3 { get => GetRegister(RegisterId.Mm3); set => SetRegister(RegisterId.Mm3, value); }
        public BigInteger Mm4 { get => GetRegister(RegisterId.Mm4); set => SetRegister(RegisterId.Mm4, value); }
        public BigInteger Mm5 { get => GetRegister(RegisterId.Mm5); set => SetRegister(RegisterId.Mm5, value); }
        public BigInteger Mm6 { get => GetRegister(RegisterId.Mm6); set => SetRegister(RegisterId.Mm6, value); }
        public BigInteger Mm7 { get => GetRegister(RegisterId.Mm7); set => SetRegister(RegisterId.Mm7, value); }
        public BigInteger Xmm0 { get => GetRegister(RegisterId.Xmm0); set => SetRegister(RegisterId.Xmm0, value); }
        public BigInteger Xmm1 { get => GetRegister(RegisterId.Xmm1); set => SetRegister(RegisterId.Xmm1, value); }
        public BigInteger Xmm2 { get => GetRegister(RegisterId.Xmm2); set => SetRegister(RegisterId.Xmm2, value); }
        public BigInteger Xmm3 { get => GetRegister(RegisterId.Xmm3); set => SetRegister(RegisterId.Xmm3, value); }
        public BigInteger Xmm4 { get => GetRegister(RegisterId.Xmm4); set => SetRegister(RegisterId.Xmm4, value); }
        public BigInteger Xmm5 { get => GetRegister(RegisterId.Xmm5); set => SetRegister(RegisterId.Xmm5, value); }
        public BigInteger Xmm6 { get => GetRegister(RegisterId.Xmm6); set => SetRegister(RegisterId.Xmm6, value); }
        public BigInteger Xmm7 { get => GetRegister(RegisterId.Xmm7); set => SetRegister(RegisterId.Xmm7, value); }
        public BigInteger Xmm8 { get => GetRegister(RegisterId.Xmm8); set => SetRegister(RegisterId.Xmm8, value); }
        public BigInteger Xmm9 { get => GetRegister(RegisterId.Xmm9); set => SetRegister(RegisterId.Xmm9, value); }
        public BigInteger Xmm10 { get => GetRegister(RegisterId.Xmm10); set => SetRegister(RegisterId.Xmm10, value); }
        public BigInteger Xmm11 { get => GetRegister(RegisterId.Xmm11); set => SetRegister(RegisterId.Xmm11, value); }
        public BigInteger Xmm12 { get => GetRegister(RegisterId.Xmm12); set => SetRegister(RegisterId.Xmm12, value); }
        public BigInteger Xmm13 { get => GetRegister(RegisterId.Xmm13); set => SetRegister(RegisterId.Xmm13, value); }
        public BigInteger Xmm14 { get => GetRegister(RegisterId.Xmm14); set => SetRegister(RegisterId.Xmm14, value); }
        public BigInteger Xmm15 { get => GetRegister(RegisterId.Xmm15); set => SetRegister(RegisterId.Xmm15, value); }
        public BigInteger Xmm16 { get => GetRegister(RegisterId.Xmm16); set => SetRegister(RegisterId.Xmm16, value); }
        public BigInteger Xmm17 { get => GetRegister(RegisterId.Xmm17); set => SetRegister(RegisterId.Xmm17, value); }
        public BigInteger Xmm18 { get => GetRegister(RegisterId.Xmm18); set => SetRegister(RegisterId.Xmm18, value); }
        public BigInteger Xmm19 { get => GetRegister(RegisterId.Xmm19); set => SetRegister(RegisterId.Xmm19, value); }
        public BigInteger Xmm20 { get => GetRegister(RegisterId.Xmm20); set => SetRegister(RegisterId.Xmm20, value); }
        public BigInteger Xmm21 { get => GetRegister(RegisterId.Xmm21); set => SetRegister(RegisterId.Xmm21, value); }
        public BigInteger Xmm22 { get => GetRegister(RegisterId.Xmm22); set => SetRegister(RegisterId.Xmm22, value); }
        public BigInteger Xmm23 { get => GetRegister(RegisterId.Xmm23); set => SetRegister(RegisterId.Xmm23, value); }
        public BigInteger Xmm24 { get => GetRegister(RegisterId.Xmm24); set => SetRegister(RegisterId.Xmm24, value); }
        public BigInteger Xmm25 { get => GetRegister(RegisterId.Xmm25); set => SetRegister(RegisterId.Xmm25, value); }
        public BigInteger Xmm26 { get => GetRegister(RegisterId.Xmm26); set => SetRegister(RegisterId.Xmm26, value); }
        public BigInteger Xmm27 { get => GetRegister(RegisterId.Xmm27); set => SetRegister(RegisterId.Xmm27, value); }
        public BigInteger Xmm28 { get => GetRegister(RegisterId.Xmm28); set => SetRegister(RegisterId.Xmm28, value); }
        public BigInteger Xmm29 { get => GetRegister(RegisterId.Xmm29); set => SetRegister(RegisterId.Xmm29, value); }
        public BigInteger Xmm30 { get => GetRegister(RegisterId.Xmm30); set => SetRegister(RegisterId.Xmm30, value); }
        public BigInteger Xmm31 { get => GetRegister(RegisterId.Xmm31); set => SetRegister(RegisterId.Xmm31, value); }
        public BigInteger Ymm0 { get => GetRegister(RegisterId.Ymm0); set => SetRegister(RegisterId.Ymm0, value); }
        public BigInteger Ymm1 { get => GetRegister(RegisterId.Ymm1); set => SetRegister(RegisterId.Ymm1, value); }
        public BigInteger Ymm2 { get => GetRegister(RegisterId.Ymm2); set => SetRegister(RegisterId.Ymm2, value); }
        public BigInteger Ymm3 { get => GetRegister(RegisterId.Ymm3); set => SetRegister(RegisterId.Ymm3, value); }
        public BigInteger Ymm4 { get => GetRegister(RegisterId.Ymm4); set => SetRegister(RegisterId.Ymm4, value); }
        public BigInteger Ymm5 { get => GetRegister(RegisterId.Ymm5); set => SetRegister(RegisterId.Ymm5, value); }
        public BigInteger Ymm6 { get => GetRegister(RegisterId.Ymm6); set => SetRegister(RegisterId.Ymm6, value); }
        public BigInteger Ymm7 { get => GetRegister(RegisterId.Ymm7); set => SetRegister(RegisterId.Ymm7, value); }
        public BigInteger Ymm8 { get => GetRegister(RegisterId.Ymm8); set => SetRegister(RegisterId.Ymm8, value); }
        public BigInteger Ymm9 { get => GetRegister(RegisterId.Ymm9); set => SetRegister(RegisterId.Ymm9, value); }
        public BigInteger Ymm10 { get => GetRegister(RegisterId.Ymm10); set => SetRegister(RegisterId.Ymm10, value); }
        public BigInteger Ymm11 { get => GetRegister(RegisterId.Ymm11); set => SetRegister(RegisterId.Ymm11, value); }
        public BigInteger Ymm12 { get => GetRegister(RegisterId.Ymm12); set => SetRegister(RegisterId.Ymm12, value); }
        public BigInteger Ymm13 { get => GetRegister(RegisterId.Ymm13); set => SetRegister(RegisterId.Ymm13, value); }
        public BigInteger Ymm14 { get => GetRegister(RegisterId.Ymm14); set => SetRegister(RegisterId.Ymm14, value); }
        public BigInteger Ymm15 { get => GetRegister(RegisterId.Ymm15); set => SetRegister(RegisterId.Ymm15, value); }
        public BigInteger Ymm16 { get => GetRegister(RegisterId.Ymm16); set => SetRegister(RegisterId.Ymm16, value); }
        public BigInteger Ymm17 { get => GetRegister(RegisterId.Ymm17); set => SetRegister(RegisterId.Ymm17, value); }
        public BigInteger Ymm18 { get => GetRegister(RegisterId.Ymm18); set => SetRegister(RegisterId.Ymm18, value); }
        public BigInteger Ymm19 { get => GetRegister(RegisterId.Ymm19); set => SetRegister(RegisterId.Ymm19, value); }
        public BigInteger Ymm20 { get => GetRegister(RegisterId.Ymm20); set => SetRegister(RegisterId.Ymm20, value); }
        public BigInteger Ymm21 { get => GetRegister(RegisterId.Ymm21); set => SetRegister(RegisterId.Ymm21, value); }
        public BigInteger Ymm22 { get => GetRegister(RegisterId.Ymm22); set => SetRegister(RegisterId.Ymm22, value); }
        public BigInteger Ymm23 { get => GetRegister(RegisterId.Ymm23); set => SetRegister(RegisterId.Ymm23, value); }
        public BigInteger Ymm24 { get => GetRegister(RegisterId.Ymm24); set => SetRegister(RegisterId.Ymm24, value); }
        public BigInteger Ymm25 { get => GetRegister(RegisterId.Ymm25); set => SetRegister(RegisterId.Ymm25, value); }
        public BigInteger Ymm26 { get => GetRegister(RegisterId.Ymm26); set => SetRegister(RegisterId.Ymm26, value); }
        public BigInteger Ymm27 { get => GetRegister(RegisterId.Ymm27); set => SetRegister(RegisterId.Ymm27, value); }
        public BigInteger Ymm28 { get => GetRegister(RegisterId.Ymm28); set => SetRegister(RegisterId.Ymm28, value); }
        public BigInteger Ymm29 { get => GetRegister(RegisterId.Ymm29); set => SetRegister(RegisterId.Ymm29, value); }
        public BigInteger Ymm30 { get => GetRegister(RegisterId.Ymm30); set => SetRegister(RegisterId.Ymm30, value); }
        public BigInteger Ymm31 { get => GetRegister(RegisterId.Ymm31); set => SetRegister(RegisterId.Ymm31, value); }
        public BigInteger Zmm0 { get => GetRegister(RegisterId.Zmm0); set => SetRegister(RegisterId.Zmm0, value); }
        public BigInteger Zmm1 { get => GetRegister(RegisterId.Zmm1); set => SetRegister(RegisterId.Zmm1, value); }
        public BigInteger Zmm2 { get => GetRegister(RegisterId.Zmm2); set => SetRegister(RegisterId.Zmm2, value); }
        public BigInteger Zmm3 { get => GetRegister(RegisterId.Zmm3); set => SetRegister(RegisterId.Zmm3, value); }
        public BigInteger Zmm4 { get => GetRegister(RegisterId.Zmm4); set => SetRegister(RegisterId.Zmm4, value); }
        public BigInteger Zmm5 { get => GetRegister(RegisterId.Zmm5); set => SetRegister(RegisterId.Zmm5, value); }
        public BigInteger Zmm6 { get => GetRegister(RegisterId.Zmm6); set => SetRegister(RegisterId.Zmm6, value); }
        public BigInteger Zmm7 { get => GetRegister(RegisterId.Zmm7); set => SetRegister(RegisterId.Zmm7, value); }
        public BigInteger Zmm8 { get => GetRegister(RegisterId.Zmm8); set => SetRegister(RegisterId.Zmm8, value); }
        public BigInteger Zmm9 { get => GetRegister(RegisterId.Zmm9); set => SetRegister(RegisterId.Zmm9, value); }
        public BigInteger Zmm10 { get => GetRegister(RegisterId.Zmm10); set => SetRegister(RegisterId.Zmm10, value); }
        public BigInteger Zmm11 { get => GetRegister(RegisterId.Zmm11); set => SetRegister(RegisterId.Zmm11, value); }
        public BigInteger Zmm12 { get => GetRegister(RegisterId.Zmm12); set => SetRegister(RegisterId.Zmm12, value); }
        public BigInteger Zmm13 { get => GetRegister(RegisterId.Zmm13); set => SetRegister(RegisterId.Zmm13, value); }
        public BigInteger Zmm14 { get => GetRegister(RegisterId.Zmm14); set => SetRegister(RegisterId.Zmm14, value); }
        public BigInteger Zmm15 { get => GetRegister(RegisterId.Zmm15); set => SetRegister(RegisterId.Zmm15, value); }
        public BigInteger Zmm16 { get => GetRegister(RegisterId.Zmm16); set => SetRegister(RegisterId.Zmm16, value); }
        public BigInteger Zmm17 { get => GetRegister(RegisterId.Zmm17); set => SetRegister(RegisterId.Zmm17, value); }
        public BigInteger Zmm18 { get => GetRegister(RegisterId.Zmm18); set => SetRegister(RegisterId.Zmm18, value); }
        public BigInteger Zmm19 { get => GetRegister(RegisterId.Zmm19); set => SetRegister(RegisterId.Zmm19, value); }
        public BigInteger Zmm20 { get => GetRegister(RegisterId.Zmm20); set => SetRegister(RegisterId.Zmm20, value); }
        public BigInteger Zmm21 { get => GetRegister(RegisterId.Zmm21); set => SetRegister(RegisterId.Zmm21, value); }
        public BigInteger Zmm22 { get => GetRegister(RegisterId.Zmm22); set => SetRegister(RegisterId.Zmm22, value); }
        public BigInteger Zmm23 { get => GetRegister(RegisterId.Zmm23); set => SetRegister(RegisterId.Zmm23, value); }
        public BigInteger Zmm24 { get => GetRegister(RegisterId.Zmm24); set => SetRegister(RegisterId.Zmm24, value); }
        public BigInteger Zmm25 { get => GetRegister(RegisterId.Zmm25); set => SetRegister(RegisterId.Zmm25, value); }
        public BigInteger Zmm26 { get => GetRegister(RegisterId.Zmm26); set => SetRegister(RegisterId.Zmm26, value); }
        public BigInteger Zmm27 { get => GetRegister(RegisterId.Zmm27); set => SetRegister(RegisterId.Zmm27, value); }
        public BigInteger Zmm28 { get => GetRegister(RegisterId.Zmm28); set => SetRegister(RegisterId.Zmm28, value); }
        public BigInteger Zmm29 { get => GetRegister(RegisterId.Zmm29); set => SetRegister(RegisterId.Zmm29, value); }
        public BigInteger Zmm30 { get => GetRegister(RegisterId.Zmm30); set => SetRegister(RegisterId.Zmm30, value); }
        public BigInteger Zmm31 { get => GetRegister(RegisterId.Zmm31); set => SetRegister(RegisterId.Zmm31, value); }
        public BigInteger Flags { get => GetRegister(RegisterId.Flags); set => SetRegister(RegisterId.Flags, value); }

#if _X64_
        public uint EFlags { get => GetRegisterU32(RegisterId.EFlags); set => SetRegisterU32(RegisterId.EFlags, value); }
        public nuint RFlags { get => (nuint)GetRegisterU64(RegisterId.RFlags); set => SetRegisterU64(RegisterId.RFlags, value); }
#else
        public nuint EFlags { get => (nuint)GetRegisterU32(RegisterId.EFlags); set => SetRegisterU32(RegisterId.EFlags, value); }
#endif
        public ushort Ip { get => GetRegisterU16(RegisterId.Ip); set => SetRegisterU16(RegisterId.Ip, value); }

#if _X64_
        public uint Eip { get => GetRegisterU32(RegisterId.Eip); set => SetRegisterU32(RegisterId.Eip, value); }
        public nuint Rip { get => (nuint)GetRegisterU64(RegisterId.Rip); set => SetRegisterU64(RegisterId.Rip, value); }
#else
        public nuint Eip { get => (nuint)GetRegisterU32(RegisterId.Eip); set => SetRegisterU32(RegisterId.Eip, value); }
#endif

        public ushort Es { get => GetRegisterU16(RegisterId.Es); set => SetRegisterU16(RegisterId.Es, value); }
        public ushort Cs { get => GetRegisterU16(RegisterId.Cs); set => SetRegisterU16(RegisterId.Cs, value); }
        public ushort Ss { get => GetRegisterU16(RegisterId.Ss); set => SetRegisterU16(RegisterId.Ss, value); }
        public ushort Ds { get => GetRegisterU16(RegisterId.Ds); set => SetRegisterU16(RegisterId.Ds, value); }
        public ushort Fs { get => GetRegisterU16(RegisterId.Fs); set => SetRegisterU16(RegisterId.Fs, value); }
        public ushort Gs { get => GetRegisterU16(RegisterId.Gs); set => SetRegisterU16(RegisterId.Gs, value); }
        public BigInteger Gdtr { get => GetRegister(RegisterId.Gdtr); set => SetRegister(RegisterId.Gdtr, value); }
        public BigInteger Ldtr { get => GetRegister(RegisterId.Ldtr); set => SetRegister(RegisterId.Ldtr, value); }
        public BigInteger Idtr { get => GetRegister(RegisterId.Idtr); set => SetRegister(RegisterId.Idtr, value); }
        public BigInteger Tr { get => GetRegister(RegisterId.Tr); set => SetRegister(RegisterId.Tr, value); }
        public BigInteger Tr0 { get => GetRegister(RegisterId.Tr0); set => SetRegister(RegisterId.Tr0, value); }
        public BigInteger Tr1 { get => GetRegister(RegisterId.Tr1); set => SetRegister(RegisterId.Tr1, value); }
        public BigInteger Tr2 { get => GetRegister(RegisterId.Tr2); set => SetRegister(RegisterId.Tr2, value); }
        public BigInteger Tr3 { get => GetRegister(RegisterId.Tr3); set => SetRegister(RegisterId.Tr3, value); }
        public BigInteger Tr4 { get => GetRegister(RegisterId.Tr4); set => SetRegister(RegisterId.Tr4, value); }
        public BigInteger Tr5 { get => GetRegister(RegisterId.Tr5); set => SetRegister(RegisterId.Tr5, value); }
        public BigInteger Tr6 { get => GetRegister(RegisterId.Tr6); set => SetRegister(RegisterId.Tr6, value); }
        public BigInteger Tr7 { get => GetRegister(RegisterId.Tr7); set => SetRegister(RegisterId.Tr7, value); }
        public BigInteger Cr0 { get => GetRegister(RegisterId.Cr0); set => SetRegister(RegisterId.Cr0, value); }
        public BigInteger Cr1 { get => GetRegister(RegisterId.Cr1); set => SetRegister(RegisterId.Cr1, value); }
        public BigInteger Cr2 { get => GetRegister(RegisterId.Cr2); set => SetRegister(RegisterId.Cr2, value); }
        public BigInteger Cr3 { get => GetRegister(RegisterId.Cr3); set => SetRegister(RegisterId.Cr3, value); }
        public BigInteger Cr4 { get => GetRegister(RegisterId.Cr4); set => SetRegister(RegisterId.Cr4, value); }
        public BigInteger Cr5 { get => GetRegister(RegisterId.Cr5); set => SetRegister(RegisterId.Cr5, value); }
        public BigInteger Cr6 { get => GetRegister(RegisterId.Cr6); set => SetRegister(RegisterId.Cr6, value); }
        public BigInteger Cr7 { get => GetRegister(RegisterId.Cr7); set => SetRegister(RegisterId.Cr7, value); }
        public BigInteger Cr8 { get => GetRegister(RegisterId.Cr8); set => SetRegister(RegisterId.Cr8, value); }
        public BigInteger Cr9 { get => GetRegister(RegisterId.Cr9); set => SetRegister(RegisterId.Cr9, value); }
        public BigInteger Cr10 { get => GetRegister(RegisterId.Cr10); set => SetRegister(RegisterId.Cr10, value); }
        public BigInteger Cr11 { get => GetRegister(RegisterId.Cr11); set => SetRegister(RegisterId.Cr11, value); }
        public BigInteger Cr12 { get => GetRegister(RegisterId.Cr12); set => SetRegister(RegisterId.Cr12, value); }
        public BigInteger Cr13 { get => GetRegister(RegisterId.Cr13); set => SetRegister(RegisterId.Cr13, value); }
        public BigInteger Cr14 { get => GetRegister(RegisterId.Cr14); set => SetRegister(RegisterId.Cr14, value); }
        public BigInteger Cr15 { get => GetRegister(RegisterId.Cr15); set => SetRegister(RegisterId.Cr15, value); }
#if _X64_
        public nuint Dr0 { get => (nuint)GetRegisterU64(RegisterId.Dr0); set => SetRegisterU64(RegisterId.Dr0, value); }
        public nuint Dr1 { get => (nuint)GetRegisterU64(RegisterId.Dr1); set => SetRegisterU64(RegisterId.Dr1, value); }
        public nuint Dr2 { get => (nuint)GetRegisterU64(RegisterId.Dr2); set => SetRegisterU64(RegisterId.Dr2, value); }
        public nuint Dr3 { get => (nuint)GetRegisterU64(RegisterId.Dr3); set => SetRegisterU64(RegisterId.Dr3, value); }
        public nuint Dr4 { get => (nuint)GetRegisterU64(RegisterId.Dr4); set => SetRegisterU64(RegisterId.Dr4, value); }
        public nuint Dr5 { get => (nuint)GetRegisterU64(RegisterId.Dr5); set => SetRegisterU64(RegisterId.Dr5, value); }
        public nuint Dr6 { get => (nuint)GetRegisterU64(RegisterId.Dr6); set => SetRegisterU64(RegisterId.Dr6, value); }
        public nuint Dr7 { get => (nuint)GetRegisterU64(RegisterId.Dr7); set => SetRegisterU64(RegisterId.Dr7, value); }
        public nuint Dr8 { get => (nuint)GetRegisterU64(RegisterId.Dr8); set => SetRegisterU64(RegisterId.Dr8, value); }
        public nuint Dr9 { get => (nuint)GetRegisterU64(RegisterId.Dr9); set => SetRegisterU64(RegisterId.Dr9, value); }
        public nuint Dr10 { get => (nuint)GetRegisterU64(RegisterId.Dr10); set => SetRegisterU64(RegisterId.Dr10, value); }
        public nuint Dr11 { get => (nuint)GetRegisterU64(RegisterId.Dr11); set => SetRegisterU64(RegisterId.Dr11, value); }
        public nuint Dr12 { get => (nuint)GetRegisterU64(RegisterId.Dr12); set => SetRegisterU64(RegisterId.Dr12, value); }
        public nuint Dr13 { get => (nuint)GetRegisterU64(RegisterId.Dr13); set => SetRegisterU64(RegisterId.Dr13, value); }
        public nuint Dr14 { get => (nuint)GetRegisterU64(RegisterId.Dr14); set => SetRegisterU64(RegisterId.Dr14, value); }
        public nuint Dr15 { get => (nuint)GetRegisterU64(RegisterId.Dr15); set => SetRegisterU64(RegisterId.Dr15, value); }
#else
        public nuint Dr0 { get => (nuint)GetRegisterU32(RegisterId.Dr0); set => SetRegisterU32(RegisterId.Dr0, value); }
        public nuint Dr1 { get => (nuint)GetRegisterU32(RegisterId.Dr1); set => SetRegisterU32(RegisterId.Dr1, value); }
        public nuint Dr2 { get => (nuint)GetRegisterU32(RegisterId.Dr2); set => SetRegisterU32(RegisterId.Dr2, value); }
        public nuint Dr3 { get => (nuint)GetRegisterU32(RegisterId.Dr3); set => SetRegisterU32(RegisterId.Dr3, value); }
        public nuint Dr4 { get => (nuint)GetRegisterU32(RegisterId.Dr4); set => SetRegisterU32(RegisterId.Dr4, value); }
        public nuint Dr5 { get => (nuint)GetRegisterU32(RegisterId.Dr5); set => SetRegisterU32(RegisterId.Dr5, value); }
        public nuint Dr6 { get => (nuint)GetRegisterU32(RegisterId.Dr6); set => SetRegisterU32(RegisterId.Dr6, value); }
        public nuint Dr7 { get => (nuint)GetRegisterU32(RegisterId.Dr7); set => SetRegisterU32(RegisterId.Dr7, value); }
        public nuint Dr8 { get => (nuint)GetRegisterU32(RegisterId.Dr8); set => SetRegisterU32(RegisterId.Dr8, value); }
        public nuint Dr9 { get => (nuint)GetRegisterU32(RegisterId.Dr9); set => SetRegisterU32(RegisterId.Dr9, value); }
        public nuint Dr10 { get => (nuint)GetRegisterU32(RegisterId.Dr10); set => SetRegisterU32(RegisterId.Dr10, value); }
        public nuint Dr11 { get => (nuint)GetRegisterU32(RegisterId.Dr11); set => SetRegisterU32(RegisterId.Dr11, value); }
        public nuint Dr12 { get => (nuint)GetRegisterU32(RegisterId.Dr12); set => SetRegisterU32(RegisterId.Dr12, value); }
        public nuint Dr13 { get => (nuint)GetRegisterU32(RegisterId.Dr13); set => SetRegisterU32(RegisterId.Dr13, value); }
        public nuint Dr14 { get => (nuint)GetRegisterU32(RegisterId.Dr14); set => SetRegisterU32(RegisterId.Dr14, value); }
        public nuint Dr15 { get => (nuint)GetRegisterU32(RegisterId.Dr15); set => SetRegisterU32(RegisterId.Dr15, value); }
#endif
        public BigInteger K0 { get => GetRegister(RegisterId.K0); set => SetRegister(RegisterId.K0, value); }
        public BigInteger K1 { get => GetRegister(RegisterId.K1); set => SetRegister(RegisterId.K1, value); }
        public BigInteger K2 { get => GetRegister(RegisterId.K2); set => SetRegister(RegisterId.K2, value); }
        public BigInteger K3 { get => GetRegister(RegisterId.K3); set => SetRegister(RegisterId.K3, value); }
        public BigInteger K4 { get => GetRegister(RegisterId.K4); set => SetRegister(RegisterId.K4, value); }
        public BigInteger K5 { get => GetRegister(RegisterId.K5); set => SetRegister(RegisterId.K5, value); }
        public BigInteger K6 { get => GetRegister(RegisterId.K6); set => SetRegister(RegisterId.K6, value); }
        public BigInteger K7 { get => GetRegister(RegisterId.K7); set => SetRegister(RegisterId.K7, value); }
        public BigInteger Bnd0 { get => GetRegister(RegisterId.Bnd0); set => SetRegister(RegisterId.Bnd0, value); }
        public BigInteger Bnd1 { get => GetRegister(RegisterId.Bnd1); set => SetRegister(RegisterId.Bnd1, value); }
        public BigInteger Bnd2 { get => GetRegister(RegisterId.Bnd2); set => SetRegister(RegisterId.Bnd2, value); }
        public BigInteger Bnd3 { get => GetRegister(RegisterId.Bnd3); set => SetRegister(RegisterId.Bnd3, value); }
        public BigInteger BndCfg { get => GetRegister(RegisterId.BndCfg); set => SetRegister(RegisterId.BndCfg, value); }
        public BigInteger BndStatus { get => GetRegister(RegisterId.BndStatus); set => SetRegister(RegisterId.BndStatus, value); }
        public BigInteger Mxcsr { get => GetRegister(RegisterId.Mxcsr); set => SetRegister(RegisterId.Mxcsr, value); }
        public BigInteger Pkru { get => GetRegister(RegisterId.Pkru); set => SetRegister(RegisterId.Pkru, value); }
        public BigInteger Xcr0 { get => GetRegister(RegisterId.Xcr0); set => SetRegister(RegisterId.Xcr0, value); }

        // Host Specific
#if _X64_
        public nuint Nax { get => (nuint)GetRegisterU64(RegisterId.Rax); set => SetRegisterU64(RegisterId.Rax, value); }
        public nuint Ncx { get => (nuint)GetRegisterU64(RegisterId.Rcx); set => SetRegisterU64(RegisterId.Rcx, value); }
        public nuint Ndx { get => (nuint)GetRegisterU64(RegisterId.Rdx); set => SetRegisterU64(RegisterId.Rdx, value); }
        public nuint Nbx { get => (nuint)GetRegisterU64(RegisterId.Rbx); set => SetRegisterU64(RegisterId.Rbx, value); }
        public nuint Nsp { get => (nuint)GetRegisterU64(RegisterId.Rsp); set => SetRegisterU64(RegisterId.Rsp, value); }
        public nuint Nbp { get => (nuint)GetRegisterU64(RegisterId.Rbp); set => SetRegisterU64(RegisterId.Rbp, value); }
        public nuint Nsi { get => (nuint)GetRegisterU64(RegisterId.Rsi); set => SetRegisterU64(RegisterId.Rsi, value); }
        public nuint Ndi { get => (nuint)GetRegisterU64(RegisterId.Rdi); set => SetRegisterU64(RegisterId.Rdi, value); }
        public nuint Nip { get => (nuint)GetRegisterU64(RegisterId.Rip); set => SetRegisterU64(RegisterId.Rip, value); }
#else
        public nuint Nax { get => (nuint)GetRegisterU32(RegisterId.Eax); set => SetRegisterU32(RegisterId.Eax, value); }
        public nuint Ncx { get => (nuint)GetRegisterU32(RegisterId.Ecx); set => SetRegisterU32(RegisterId.Ecx, value); }
        public nuint Ndx { get => (nuint)GetRegisterU32(RegisterId.Edx); set => SetRegisterU32(RegisterId.Edx, value); }
        public nuint Nbx { get => (nuint)GetRegisterU32(RegisterId.Ebx); set => SetRegisterU32(RegisterId.Ebx, value); }
        public nuint Nsp { get => (nuint)GetRegisterU32(RegisterId.Esp); set => SetRegisterU32(RegisterId.Esp, value); }
        public nuint Nbp { get => (nuint)GetRegisterU32(RegisterId.Ebp); set => SetRegisterU32(RegisterId.Ebp, value); }
        public nuint Nsi { get => (nuint)GetRegisterU32(RegisterId.Esi); set => SetRegisterU32(RegisterId.Esi, value); }
        public nuint Ndi { get => (nuint)GetRegisterU32(RegisterId.Edi); set => SetRegisterU32(RegisterId.Edi, value); }
        public nuint Nip { get => (nuint)GetRegisterU32(RegisterId.Eip); set => SetRegisterU32(RegisterId.Eip, value); }
#endif
    }
}
