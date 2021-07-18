using System;
using System.Numerics;

namespace Dotx64Dbg
{
    public partial class Thread
    {
        private byte GetRegisterU8(Register reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return bytes[0];
        }

        private void SetRegisterU8(Register reg, byte val)
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private ushort GetRegisterU16(Register reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt16(bytes);
        }

        private void SetRegisterU16(Register reg, ushort val)
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private uint GetRegisterU32(Register reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt32(bytes);
        }

#if _X64_
        private void SetRegisterU32(Register reg, uint val)
#else

        private void SetRegisterU32(Register reg, nuint val)
#endif
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private ulong GetRegisterU64(Register reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt64(bytes);
        }


#if _X64_
        private void SetRegisterU64(Register reg, nuint val)
#else

        private void SetRegisterU64(Register reg, ulong val)
#endif
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        public BigInteger GetRegister(Register reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return new BigInteger(bytes, true);
        }

        public void SetRegister(Register reg, BigInteger val)
        {
            Native.Thread.SetRegisterData(Handle, reg, val.ToByteArray());
        }

        public byte Al { get => GetRegisterU8(Register.Al); set => SetRegisterU8(Register.Al, value); }
        public byte Cl { get => GetRegisterU8(Register.Cl); set => SetRegisterU8(Register.Cl, value); }
        public byte Dl { get => GetRegisterU8(Register.Dl); set => SetRegisterU8(Register.Dl, value); }
        public byte Bl { get => GetRegisterU8(Register.Bl); set => SetRegisterU8(Register.Bl, value); }
        public byte Ah { get => GetRegisterU8(Register.Ah); set => SetRegisterU8(Register.Ah, value); }
        public byte Ch { get => GetRegisterU8(Register.Ch); set => SetRegisterU8(Register.Ch, value); }
        public byte Dh { get => GetRegisterU8(Register.Dh); set => SetRegisterU8(Register.Dh, value); }
        public byte Bh { get => GetRegisterU8(Register.Bh); set => SetRegisterU8(Register.Bh, value); }
        public byte Spl { get => GetRegisterU8(Register.Spl); set => SetRegisterU8(Register.Spl, value); }
        public byte Bpl { get => GetRegisterU8(Register.Bpl); set => SetRegisterU8(Register.Bpl, value); }
        public byte Sil { get => GetRegisterU8(Register.Sil); set => SetRegisterU8(Register.Sil, value); }
        public byte Dil { get => GetRegisterU8(Register.Dil); set => SetRegisterU8(Register.Dil, value); }
#if _X64_
        public byte R8b { get => GetRegisterU8(Register.R8b); set => SetRegisterU8(Register.R8b, value); }
        public byte R9b { get => GetRegisterU8(Register.R9b); set => SetRegisterU8(Register.R9b, value); }
        public byte R10b { get => GetRegisterU8(Register.R10b); set => SetRegisterU8(Register.R10b, value); }
        public byte R11b { get => GetRegisterU8(Register.R11b); set => SetRegisterU8(Register.R11b, value); }
        public byte R12b { get => GetRegisterU8(Register.R12b); set => SetRegisterU8(Register.R12b, value); }
        public byte R13b { get => GetRegisterU8(Register.R13b); set => SetRegisterU8(Register.R13b, value); }
        public byte R14b { get => GetRegisterU8(Register.R14b); set => SetRegisterU8(Register.R14b, value); }
        public byte R15b { get => GetRegisterU8(Register.R15b); set => SetRegisterU8(Register.R15b, value); }
#endif
        public ushort Ax { get => GetRegisterU16(Register.Ax); set => SetRegisterU16(Register.Ax, value); }
        public ushort Cx { get => GetRegisterU16(Register.Cx); set => SetRegisterU16(Register.Cx, value); }
        public ushort Dx { get => GetRegisterU16(Register.Dx); set => SetRegisterU16(Register.Dx, value); }
        public ushort Bx { get => GetRegisterU16(Register.Bx); set => SetRegisterU16(Register.Bx, value); }
        public ushort Sp { get => GetRegisterU16(Register.Sp); set => SetRegisterU16(Register.Sp, value); }
        public ushort Bp { get => GetRegisterU16(Register.Bp); set => SetRegisterU16(Register.Bp, value); }
        public ushort Si { get => GetRegisterU16(Register.Si); set => SetRegisterU16(Register.Si, value); }
        public ushort Di { get => GetRegisterU16(Register.Di); set => SetRegisterU16(Register.Di, value); }
#if _X64_
        public ushort R8w { get => GetRegisterU16(Register.R8w); set => SetRegisterU16(Register.R8w, value); }
        public ushort R9w { get => GetRegisterU16(Register.R9w); set => SetRegisterU16(Register.R9w, value); }
        public ushort R10w { get => GetRegisterU16(Register.R10w); set => SetRegisterU16(Register.R10w, value); }
        public ushort R11w { get => GetRegisterU16(Register.R11w); set => SetRegisterU16(Register.R11w, value); }
        public ushort R12w { get => GetRegisterU16(Register.R12w); set => SetRegisterU16(Register.R12w, value); }
        public ushort R13w { get => GetRegisterU16(Register.R13w); set => SetRegisterU16(Register.R13w, value); }
        public ushort R14w { get => GetRegisterU16(Register.R14w); set => SetRegisterU16(Register.R14w, value); }
        public ushort R15w { get => GetRegisterU16(Register.R15w); set => SetRegisterU16(Register.R15w, value); }
#endif

#if _X64_
        public uint Eax { get => GetRegisterU32(Register.Eax); set => SetRegisterU32(Register.Eax, value); }
        public uint Ecx { get => GetRegisterU32(Register.Ecx); set => SetRegisterU32(Register.Ecx, value); }
        public uint Edx { get => GetRegisterU32(Register.Edx); set => SetRegisterU32(Register.Edx, value); }
        public uint Ebx { get => GetRegisterU32(Register.Ebx); set => SetRegisterU32(Register.Ebx, value); }
        public uint Esp { get => GetRegisterU32(Register.Esp); set => SetRegisterU32(Register.Esp, value); }
        public uint Ebp { get => GetRegisterU32(Register.Ebp); set => SetRegisterU32(Register.Ebp, value); }
        public uint Esi { get => GetRegisterU32(Register.Esi); set => SetRegisterU32(Register.Esi, value); }
        public uint Edi { get => GetRegisterU32(Register.Edi); set => SetRegisterU32(Register.Edi, value); }
#else
        public nuint Eax { get => (nuint)GetRegisterU32(Register.Eax); set => SetRegisterU32(Register.Eax, value); }
        public nuint Ecx { get => (nuint)GetRegisterU32(Register.Ecx); set => SetRegisterU32(Register.Ecx, value); }
        public nuint Edx { get => (nuint)GetRegisterU32(Register.Edx); set => SetRegisterU32(Register.Edx, value); }
        public nuint Ebx { get => (nuint)GetRegisterU32(Register.Ebx); set => SetRegisterU32(Register.Ebx, value); }
        public nuint Esp { get => (nuint)GetRegisterU32(Register.Esp); set => SetRegisterU32(Register.Esp, value); }
        public nuint Ebp { get => (nuint)GetRegisterU32(Register.Ebp); set => SetRegisterU32(Register.Ebp, value); }
        public nuint Esi { get => (nuint)GetRegisterU32(Register.Esi); set => SetRegisterU32(Register.Esi, value); }
        public nuint Edi { get => (nuint)GetRegisterU32(Register.Edi); set => SetRegisterU32(Register.Edi, value); }
#endif

#if _X64_
        public uint R8d { get => GetRegisterU32(Register.R8d); set => SetRegisterU32(Register.R8d, value); }
        public uint R9d { get => GetRegisterU32(Register.R9d); set => SetRegisterU32(Register.R9d, value); }
        public uint R10d { get => GetRegisterU32(Register.R10d); set => SetRegisterU32(Register.R10d, value); }
        public uint R11d { get => GetRegisterU32(Register.R11d); set => SetRegisterU32(Register.R11d, value); }
        public uint R12d { get => GetRegisterU32(Register.R12d); set => SetRegisterU32(Register.R12d, value); }
        public uint R13d { get => GetRegisterU32(Register.R13d); set => SetRegisterU32(Register.R13d, value); }
        public uint R14d { get => GetRegisterU32(Register.R14d); set => SetRegisterU32(Register.R14d, value); }
        public uint R15d { get => GetRegisterU32(Register.R15d); set => SetRegisterU32(Register.R15d, value); }
        public nuint Rax { get => (nuint)GetRegisterU64(Register.Rax); set => SetRegisterU64(Register.Rax, value); }
        public nuint Rcx { get => (nuint)GetRegisterU64(Register.Rcx); set => SetRegisterU64(Register.Rcx, value); }
        public nuint Rdx { get => (nuint)GetRegisterU64(Register.Rdx); set => SetRegisterU64(Register.Rdx, value); }
        public nuint Rbx { get => (nuint)GetRegisterU64(Register.Rbx); set => SetRegisterU64(Register.Rbx, value); }
        public nuint Rsp { get => (nuint)GetRegisterU64(Register.Rsp); set => SetRegisterU64(Register.Rsp, value); }
        public nuint Rbp { get => (nuint)GetRegisterU64(Register.Rbp); set => SetRegisterU64(Register.Rbp, value); }
        public nuint Rsi { get => (nuint)GetRegisterU64(Register.Rsi); set => SetRegisterU64(Register.Rsi, value); }
        public nuint Rdi { get => (nuint)GetRegisterU64(Register.Rdi); set => SetRegisterU64(Register.Rdi, value); }
        public nuint R8 { get => (nuint)GetRegisterU64(Register.R8); set => SetRegisterU64(Register.R8, value); }
        public nuint R9 { get => (nuint)GetRegisterU64(Register.R9); set => SetRegisterU64(Register.R9, value); }
        public nuint R10 { get => (nuint)GetRegisterU64(Register.R10); set => SetRegisterU64(Register.R10, value); }
        public nuint R11 { get => (nuint)GetRegisterU64(Register.R11); set => SetRegisterU64(Register.R11, value); }
        public nuint R12 { get => (nuint)GetRegisterU64(Register.R12); set => SetRegisterU64(Register.R12, value); }
        public nuint R13 { get => (nuint)GetRegisterU64(Register.R13); set => SetRegisterU64(Register.R13, value); }
        public nuint R14 { get => (nuint)GetRegisterU64(Register.R14); set => SetRegisterU64(Register.R14, value); }
        public nuint R15 { get => (nuint)GetRegisterU64(Register.R15); set => SetRegisterU64(Register.R15, value); }
#endif
        public BigInteger St0 { get => GetRegister(Register.St0); set => SetRegister(Register.St0, value); }
        public BigInteger St1 { get => GetRegister(Register.St1); set => SetRegister(Register.St1, value); }
        public BigInteger St2 { get => GetRegister(Register.St2); set => SetRegister(Register.St2, value); }
        public BigInteger St3 { get => GetRegister(Register.St3); set => SetRegister(Register.St3, value); }
        public BigInteger St4 { get => GetRegister(Register.St4); set => SetRegister(Register.St4, value); }
        public BigInteger St5 { get => GetRegister(Register.St5); set => SetRegister(Register.St5, value); }
        public BigInteger St6 { get => GetRegister(Register.St6); set => SetRegister(Register.St6, value); }
        public BigInteger St7 { get => GetRegister(Register.St7); set => SetRegister(Register.St7, value); }
        public BigInteger X87Control { get => GetRegister(Register.X87Control); set => SetRegister(Register.X87Control, value); }
        public BigInteger X87Status { get => GetRegister(Register.X87Status); set => SetRegister(Register.X87Status, value); }
        public BigInteger X87Tag { get => GetRegister(Register.X87Tag); set => SetRegister(Register.X87Tag, value); }
        public BigInteger Mm0 { get => GetRegister(Register.Mm0); set => SetRegister(Register.Mm0, value); }
        public BigInteger Mm1 { get => GetRegister(Register.Mm1); set => SetRegister(Register.Mm1, value); }
        public BigInteger Mm2 { get => GetRegister(Register.Mm2); set => SetRegister(Register.Mm2, value); }
        public BigInteger Mm3 { get => GetRegister(Register.Mm3); set => SetRegister(Register.Mm3, value); }
        public BigInteger Mm4 { get => GetRegister(Register.Mm4); set => SetRegister(Register.Mm4, value); }
        public BigInteger Mm5 { get => GetRegister(Register.Mm5); set => SetRegister(Register.Mm5, value); }
        public BigInteger Mm6 { get => GetRegister(Register.Mm6); set => SetRegister(Register.Mm6, value); }
        public BigInteger Mm7 { get => GetRegister(Register.Mm7); set => SetRegister(Register.Mm7, value); }
        public BigInteger Xmm0 { get => GetRegister(Register.Xmm0); set => SetRegister(Register.Xmm0, value); }
        public BigInteger Xmm1 { get => GetRegister(Register.Xmm1); set => SetRegister(Register.Xmm1, value); }
        public BigInteger Xmm2 { get => GetRegister(Register.Xmm2); set => SetRegister(Register.Xmm2, value); }
        public BigInteger Xmm3 { get => GetRegister(Register.Xmm3); set => SetRegister(Register.Xmm3, value); }
        public BigInteger Xmm4 { get => GetRegister(Register.Xmm4); set => SetRegister(Register.Xmm4, value); }
        public BigInteger Xmm5 { get => GetRegister(Register.Xmm5); set => SetRegister(Register.Xmm5, value); }
        public BigInteger Xmm6 { get => GetRegister(Register.Xmm6); set => SetRegister(Register.Xmm6, value); }
        public BigInteger Xmm7 { get => GetRegister(Register.Xmm7); set => SetRegister(Register.Xmm7, value); }
        public BigInteger Xmm8 { get => GetRegister(Register.Xmm8); set => SetRegister(Register.Xmm8, value); }
        public BigInteger Xmm9 { get => GetRegister(Register.Xmm9); set => SetRegister(Register.Xmm9, value); }
        public BigInteger Xmm10 { get => GetRegister(Register.Xmm10); set => SetRegister(Register.Xmm10, value); }
        public BigInteger Xmm11 { get => GetRegister(Register.Xmm11); set => SetRegister(Register.Xmm11, value); }
        public BigInteger Xmm12 { get => GetRegister(Register.Xmm12); set => SetRegister(Register.Xmm12, value); }
        public BigInteger Xmm13 { get => GetRegister(Register.Xmm13); set => SetRegister(Register.Xmm13, value); }
        public BigInteger Xmm14 { get => GetRegister(Register.Xmm14); set => SetRegister(Register.Xmm14, value); }
        public BigInteger Xmm15 { get => GetRegister(Register.Xmm15); set => SetRegister(Register.Xmm15, value); }
        public BigInteger Xmm16 { get => GetRegister(Register.Xmm16); set => SetRegister(Register.Xmm16, value); }
        public BigInteger Xmm17 { get => GetRegister(Register.Xmm17); set => SetRegister(Register.Xmm17, value); }
        public BigInteger Xmm18 { get => GetRegister(Register.Xmm18); set => SetRegister(Register.Xmm18, value); }
        public BigInteger Xmm19 { get => GetRegister(Register.Xmm19); set => SetRegister(Register.Xmm19, value); }
        public BigInteger Xmm20 { get => GetRegister(Register.Xmm20); set => SetRegister(Register.Xmm20, value); }
        public BigInteger Xmm21 { get => GetRegister(Register.Xmm21); set => SetRegister(Register.Xmm21, value); }
        public BigInteger Xmm22 { get => GetRegister(Register.Xmm22); set => SetRegister(Register.Xmm22, value); }
        public BigInteger Xmm23 { get => GetRegister(Register.Xmm23); set => SetRegister(Register.Xmm23, value); }
        public BigInteger Xmm24 { get => GetRegister(Register.Xmm24); set => SetRegister(Register.Xmm24, value); }
        public BigInteger Xmm25 { get => GetRegister(Register.Xmm25); set => SetRegister(Register.Xmm25, value); }
        public BigInteger Xmm26 { get => GetRegister(Register.Xmm26); set => SetRegister(Register.Xmm26, value); }
        public BigInteger Xmm27 { get => GetRegister(Register.Xmm27); set => SetRegister(Register.Xmm27, value); }
        public BigInteger Xmm28 { get => GetRegister(Register.Xmm28); set => SetRegister(Register.Xmm28, value); }
        public BigInteger Xmm29 { get => GetRegister(Register.Xmm29); set => SetRegister(Register.Xmm29, value); }
        public BigInteger Xmm30 { get => GetRegister(Register.Xmm30); set => SetRegister(Register.Xmm30, value); }
        public BigInteger Xmm31 { get => GetRegister(Register.Xmm31); set => SetRegister(Register.Xmm31, value); }
        public BigInteger Ymm0 { get => GetRegister(Register.Ymm0); set => SetRegister(Register.Ymm0, value); }
        public BigInteger Ymm1 { get => GetRegister(Register.Ymm1); set => SetRegister(Register.Ymm1, value); }
        public BigInteger Ymm2 { get => GetRegister(Register.Ymm2); set => SetRegister(Register.Ymm2, value); }
        public BigInteger Ymm3 { get => GetRegister(Register.Ymm3); set => SetRegister(Register.Ymm3, value); }
        public BigInteger Ymm4 { get => GetRegister(Register.Ymm4); set => SetRegister(Register.Ymm4, value); }
        public BigInteger Ymm5 { get => GetRegister(Register.Ymm5); set => SetRegister(Register.Ymm5, value); }
        public BigInteger Ymm6 { get => GetRegister(Register.Ymm6); set => SetRegister(Register.Ymm6, value); }
        public BigInteger Ymm7 { get => GetRegister(Register.Ymm7); set => SetRegister(Register.Ymm7, value); }
        public BigInteger Ymm8 { get => GetRegister(Register.Ymm8); set => SetRegister(Register.Ymm8, value); }
        public BigInteger Ymm9 { get => GetRegister(Register.Ymm9); set => SetRegister(Register.Ymm9, value); }
        public BigInteger Ymm10 { get => GetRegister(Register.Ymm10); set => SetRegister(Register.Ymm10, value); }
        public BigInteger Ymm11 { get => GetRegister(Register.Ymm11); set => SetRegister(Register.Ymm11, value); }
        public BigInteger Ymm12 { get => GetRegister(Register.Ymm12); set => SetRegister(Register.Ymm12, value); }
        public BigInteger Ymm13 { get => GetRegister(Register.Ymm13); set => SetRegister(Register.Ymm13, value); }
        public BigInteger Ymm14 { get => GetRegister(Register.Ymm14); set => SetRegister(Register.Ymm14, value); }
        public BigInteger Ymm15 { get => GetRegister(Register.Ymm15); set => SetRegister(Register.Ymm15, value); }
        public BigInteger Ymm16 { get => GetRegister(Register.Ymm16); set => SetRegister(Register.Ymm16, value); }
        public BigInteger Ymm17 { get => GetRegister(Register.Ymm17); set => SetRegister(Register.Ymm17, value); }
        public BigInteger Ymm18 { get => GetRegister(Register.Ymm18); set => SetRegister(Register.Ymm18, value); }
        public BigInteger Ymm19 { get => GetRegister(Register.Ymm19); set => SetRegister(Register.Ymm19, value); }
        public BigInteger Ymm20 { get => GetRegister(Register.Ymm20); set => SetRegister(Register.Ymm20, value); }
        public BigInteger Ymm21 { get => GetRegister(Register.Ymm21); set => SetRegister(Register.Ymm21, value); }
        public BigInteger Ymm22 { get => GetRegister(Register.Ymm22); set => SetRegister(Register.Ymm22, value); }
        public BigInteger Ymm23 { get => GetRegister(Register.Ymm23); set => SetRegister(Register.Ymm23, value); }
        public BigInteger Ymm24 { get => GetRegister(Register.Ymm24); set => SetRegister(Register.Ymm24, value); }
        public BigInteger Ymm25 { get => GetRegister(Register.Ymm25); set => SetRegister(Register.Ymm25, value); }
        public BigInteger Ymm26 { get => GetRegister(Register.Ymm26); set => SetRegister(Register.Ymm26, value); }
        public BigInteger Ymm27 { get => GetRegister(Register.Ymm27); set => SetRegister(Register.Ymm27, value); }
        public BigInteger Ymm28 { get => GetRegister(Register.Ymm28); set => SetRegister(Register.Ymm28, value); }
        public BigInteger Ymm29 { get => GetRegister(Register.Ymm29); set => SetRegister(Register.Ymm29, value); }
        public BigInteger Ymm30 { get => GetRegister(Register.Ymm30); set => SetRegister(Register.Ymm30, value); }
        public BigInteger Ymm31 { get => GetRegister(Register.Ymm31); set => SetRegister(Register.Ymm31, value); }
        public BigInteger Zmm0 { get => GetRegister(Register.Zmm0); set => SetRegister(Register.Zmm0, value); }
        public BigInteger Zmm1 { get => GetRegister(Register.Zmm1); set => SetRegister(Register.Zmm1, value); }
        public BigInteger Zmm2 { get => GetRegister(Register.Zmm2); set => SetRegister(Register.Zmm2, value); }
        public BigInteger Zmm3 { get => GetRegister(Register.Zmm3); set => SetRegister(Register.Zmm3, value); }
        public BigInteger Zmm4 { get => GetRegister(Register.Zmm4); set => SetRegister(Register.Zmm4, value); }
        public BigInteger Zmm5 { get => GetRegister(Register.Zmm5); set => SetRegister(Register.Zmm5, value); }
        public BigInteger Zmm6 { get => GetRegister(Register.Zmm6); set => SetRegister(Register.Zmm6, value); }
        public BigInteger Zmm7 { get => GetRegister(Register.Zmm7); set => SetRegister(Register.Zmm7, value); }
        public BigInteger Zmm8 { get => GetRegister(Register.Zmm8); set => SetRegister(Register.Zmm8, value); }
        public BigInteger Zmm9 { get => GetRegister(Register.Zmm9); set => SetRegister(Register.Zmm9, value); }
        public BigInteger Zmm10 { get => GetRegister(Register.Zmm10); set => SetRegister(Register.Zmm10, value); }
        public BigInteger Zmm11 { get => GetRegister(Register.Zmm11); set => SetRegister(Register.Zmm11, value); }
        public BigInteger Zmm12 { get => GetRegister(Register.Zmm12); set => SetRegister(Register.Zmm12, value); }
        public BigInteger Zmm13 { get => GetRegister(Register.Zmm13); set => SetRegister(Register.Zmm13, value); }
        public BigInteger Zmm14 { get => GetRegister(Register.Zmm14); set => SetRegister(Register.Zmm14, value); }
        public BigInteger Zmm15 { get => GetRegister(Register.Zmm15); set => SetRegister(Register.Zmm15, value); }
        public BigInteger Zmm16 { get => GetRegister(Register.Zmm16); set => SetRegister(Register.Zmm16, value); }
        public BigInteger Zmm17 { get => GetRegister(Register.Zmm17); set => SetRegister(Register.Zmm17, value); }
        public BigInteger Zmm18 { get => GetRegister(Register.Zmm18); set => SetRegister(Register.Zmm18, value); }
        public BigInteger Zmm19 { get => GetRegister(Register.Zmm19); set => SetRegister(Register.Zmm19, value); }
        public BigInteger Zmm20 { get => GetRegister(Register.Zmm20); set => SetRegister(Register.Zmm20, value); }
        public BigInteger Zmm21 { get => GetRegister(Register.Zmm21); set => SetRegister(Register.Zmm21, value); }
        public BigInteger Zmm22 { get => GetRegister(Register.Zmm22); set => SetRegister(Register.Zmm22, value); }
        public BigInteger Zmm23 { get => GetRegister(Register.Zmm23); set => SetRegister(Register.Zmm23, value); }
        public BigInteger Zmm24 { get => GetRegister(Register.Zmm24); set => SetRegister(Register.Zmm24, value); }
        public BigInteger Zmm25 { get => GetRegister(Register.Zmm25); set => SetRegister(Register.Zmm25, value); }
        public BigInteger Zmm26 { get => GetRegister(Register.Zmm26); set => SetRegister(Register.Zmm26, value); }
        public BigInteger Zmm27 { get => GetRegister(Register.Zmm27); set => SetRegister(Register.Zmm27, value); }
        public BigInteger Zmm28 { get => GetRegister(Register.Zmm28); set => SetRegister(Register.Zmm28, value); }
        public BigInteger Zmm29 { get => GetRegister(Register.Zmm29); set => SetRegister(Register.Zmm29, value); }
        public BigInteger Zmm30 { get => GetRegister(Register.Zmm30); set => SetRegister(Register.Zmm30, value); }
        public BigInteger Zmm31 { get => GetRegister(Register.Zmm31); set => SetRegister(Register.Zmm31, value); }
        public BigInteger Flags { get => GetRegister(Register.Flags); set => SetRegister(Register.Flags, value); }

#if _X64_
        public uint EFlags { get => GetRegisterU32(Register.EFlags); set => SetRegisterU32(Register.EFlags, value); }
        public nuint RFlags { get => (nuint)GetRegisterU64(Register.RFlags); set => SetRegisterU64(Register.RFlags, value); }
#else
        public nuint EFlags { get => (nuint)GetRegisterU32(Register.EFlags); set => SetRegisterU32(Register.EFlags, value); }
#endif
        public ushort Ip { get => GetRegisterU16(Register.Ip); set => SetRegisterU16(Register.Ip, value); }

#if _X64_
        public uint Eip { get => GetRegisterU32(Register.Eip); set => SetRegisterU32(Register.Eip, value); }
        public nuint Rip { get => (nuint)GetRegisterU64(Register.Rip); set => SetRegisterU64(Register.Rip, value); }
#else
        public nuint Eip { get => (nuint)GetRegisterU32(Register.Eip); set => SetRegisterU32(Register.Eip, value); }
#endif

        public ushort Es { get => GetRegisterU16(Register.Es); set => SetRegisterU16(Register.Es, value); }
        public ushort Cs { get => GetRegisterU16(Register.Cs); set => SetRegisterU16(Register.Cs, value); }
        public ushort Ss { get => GetRegisterU16(Register.Ss); set => SetRegisterU16(Register.Ss, value); }
        public ushort Ds { get => GetRegisterU16(Register.Ds); set => SetRegisterU16(Register.Ds, value); }
        public ushort Fs { get => GetRegisterU16(Register.Fs); set => SetRegisterU16(Register.Fs, value); }
        public ushort Gs { get => GetRegisterU16(Register.Gs); set => SetRegisterU16(Register.Gs, value); }
        public BigInteger Gdtr { get => GetRegister(Register.Gdtr); set => SetRegister(Register.Gdtr, value); }
        public BigInteger Ldtr { get => GetRegister(Register.Ldtr); set => SetRegister(Register.Ldtr, value); }
        public BigInteger Idtr { get => GetRegister(Register.Idtr); set => SetRegister(Register.Idtr, value); }
        public BigInteger Tr { get => GetRegister(Register.Tr); set => SetRegister(Register.Tr, value); }
        public BigInteger Tr0 { get => GetRegister(Register.Tr0); set => SetRegister(Register.Tr0, value); }
        public BigInteger Tr1 { get => GetRegister(Register.Tr1); set => SetRegister(Register.Tr1, value); }
        public BigInteger Tr2 { get => GetRegister(Register.Tr2); set => SetRegister(Register.Tr2, value); }
        public BigInteger Tr3 { get => GetRegister(Register.Tr3); set => SetRegister(Register.Tr3, value); }
        public BigInteger Tr4 { get => GetRegister(Register.Tr4); set => SetRegister(Register.Tr4, value); }
        public BigInteger Tr5 { get => GetRegister(Register.Tr5); set => SetRegister(Register.Tr5, value); }
        public BigInteger Tr6 { get => GetRegister(Register.Tr6); set => SetRegister(Register.Tr6, value); }
        public BigInteger Tr7 { get => GetRegister(Register.Tr7); set => SetRegister(Register.Tr7, value); }
        public BigInteger Cr0 { get => GetRegister(Register.Cr0); set => SetRegister(Register.Cr0, value); }
        public BigInteger Cr1 { get => GetRegister(Register.Cr1); set => SetRegister(Register.Cr1, value); }
        public BigInteger Cr2 { get => GetRegister(Register.Cr2); set => SetRegister(Register.Cr2, value); }
        public BigInteger Cr3 { get => GetRegister(Register.Cr3); set => SetRegister(Register.Cr3, value); }
        public BigInteger Cr4 { get => GetRegister(Register.Cr4); set => SetRegister(Register.Cr4, value); }
        public BigInteger Cr5 { get => GetRegister(Register.Cr5); set => SetRegister(Register.Cr5, value); }
        public BigInteger Cr6 { get => GetRegister(Register.Cr6); set => SetRegister(Register.Cr6, value); }
        public BigInteger Cr7 { get => GetRegister(Register.Cr7); set => SetRegister(Register.Cr7, value); }
        public BigInteger Cr8 { get => GetRegister(Register.Cr8); set => SetRegister(Register.Cr8, value); }
        public BigInteger Cr9 { get => GetRegister(Register.Cr9); set => SetRegister(Register.Cr9, value); }
        public BigInteger Cr10 { get => GetRegister(Register.Cr10); set => SetRegister(Register.Cr10, value); }
        public BigInteger Cr11 { get => GetRegister(Register.Cr11); set => SetRegister(Register.Cr11, value); }
        public BigInteger Cr12 { get => GetRegister(Register.Cr12); set => SetRegister(Register.Cr12, value); }
        public BigInteger Cr13 { get => GetRegister(Register.Cr13); set => SetRegister(Register.Cr13, value); }
        public BigInteger Cr14 { get => GetRegister(Register.Cr14); set => SetRegister(Register.Cr14, value); }
        public BigInteger Cr15 { get => GetRegister(Register.Cr15); set => SetRegister(Register.Cr15, value); }
#if _X64_
        public nuint Dr0 { get => (nuint)GetRegisterU64(Register.Dr0); set => SetRegisterU64(Register.Dr0, value); }
        public nuint Dr1 { get => (nuint)GetRegisterU64(Register.Dr1); set => SetRegisterU64(Register.Dr1, value); }
        public nuint Dr2 { get => (nuint)GetRegisterU64(Register.Dr2); set => SetRegisterU64(Register.Dr2, value); }
        public nuint Dr3 { get => (nuint)GetRegisterU64(Register.Dr3); set => SetRegisterU64(Register.Dr3, value); }
        public nuint Dr4 { get => (nuint)GetRegisterU64(Register.Dr4); set => SetRegisterU64(Register.Dr4, value); }
        public nuint Dr5 { get => (nuint)GetRegisterU64(Register.Dr5); set => SetRegisterU64(Register.Dr5, value); }
        public nuint Dr6 { get => (nuint)GetRegisterU64(Register.Dr6); set => SetRegisterU64(Register.Dr6, value); }
        public nuint Dr7 { get => (nuint)GetRegisterU64(Register.Dr7); set => SetRegisterU64(Register.Dr7, value); }
        public nuint Dr8 { get => (nuint)GetRegisterU64(Register.Dr8); set => SetRegisterU64(Register.Dr8, value); }
        public nuint Dr9 { get => (nuint)GetRegisterU64(Register.Dr9); set => SetRegisterU64(Register.Dr9, value); }
        public nuint Dr10 { get => (nuint)GetRegisterU64(Register.Dr10); set => SetRegisterU64(Register.Dr10, value); }
        public nuint Dr11 { get => (nuint)GetRegisterU64(Register.Dr11); set => SetRegisterU64(Register.Dr11, value); }
        public nuint Dr12 { get => (nuint)GetRegisterU64(Register.Dr12); set => SetRegisterU64(Register.Dr12, value); }
        public nuint Dr13 { get => (nuint)GetRegisterU64(Register.Dr13); set => SetRegisterU64(Register.Dr13, value); }
        public nuint Dr14 { get => (nuint)GetRegisterU64(Register.Dr14); set => SetRegisterU64(Register.Dr14, value); }
        public nuint Dr15 { get => (nuint)GetRegisterU64(Register.Dr15); set => SetRegisterU64(Register.Dr15, value); }
#else
        public nuint Dr0 { get => (nuint)GetRegisterU32(Register.Dr0); set => SetRegisterU32(Register.Dr0, value); }
        public nuint Dr1 { get => (nuint)GetRegisterU32(Register.Dr1); set => SetRegisterU32(Register.Dr1, value); }
        public nuint Dr2 { get => (nuint)GetRegisterU32(Register.Dr2); set => SetRegisterU32(Register.Dr2, value); }
        public nuint Dr3 { get => (nuint)GetRegisterU32(Register.Dr3); set => SetRegisterU32(Register.Dr3, value); }
        public nuint Dr4 { get => (nuint)GetRegisterU32(Register.Dr4); set => SetRegisterU32(Register.Dr4, value); }
        public nuint Dr5 { get => (nuint)GetRegisterU32(Register.Dr5); set => SetRegisterU32(Register.Dr5, value); }
        public nuint Dr6 { get => (nuint)GetRegisterU32(Register.Dr6); set => SetRegisterU32(Register.Dr6, value); }
        public nuint Dr7 { get => (nuint)GetRegisterU32(Register.Dr7); set => SetRegisterU32(Register.Dr7, value); }
        public nuint Dr8 { get => (nuint)GetRegisterU32(Register.Dr8); set => SetRegisterU32(Register.Dr8, value); }
        public nuint Dr9 { get => (nuint)GetRegisterU32(Register.Dr9); set => SetRegisterU32(Register.Dr9, value); }
        public nuint Dr10 { get => (nuint)GetRegisterU32(Register.Dr10); set => SetRegisterU32(Register.Dr10, value); }
        public nuint Dr11 { get => (nuint)GetRegisterU32(Register.Dr11); set => SetRegisterU32(Register.Dr11, value); }
        public nuint Dr12 { get => (nuint)GetRegisterU32(Register.Dr12); set => SetRegisterU32(Register.Dr12, value); }
        public nuint Dr13 { get => (nuint)GetRegisterU32(Register.Dr13); set => SetRegisterU32(Register.Dr13, value); }
        public nuint Dr14 { get => (nuint)GetRegisterU32(Register.Dr14); set => SetRegisterU32(Register.Dr14, value); }
        public nuint Dr15 { get => (nuint)GetRegisterU32(Register.Dr15); set => SetRegisterU32(Register.Dr15, value); }
#endif
        public BigInteger K0 { get => GetRegister(Register.K0); set => SetRegister(Register.K0, value); }
        public BigInteger K1 { get => GetRegister(Register.K1); set => SetRegister(Register.K1, value); }
        public BigInteger K2 { get => GetRegister(Register.K2); set => SetRegister(Register.K2, value); }
        public BigInteger K3 { get => GetRegister(Register.K3); set => SetRegister(Register.K3, value); }
        public BigInteger K4 { get => GetRegister(Register.K4); set => SetRegister(Register.K4, value); }
        public BigInteger K5 { get => GetRegister(Register.K5); set => SetRegister(Register.K5, value); }
        public BigInteger K6 { get => GetRegister(Register.K6); set => SetRegister(Register.K6, value); }
        public BigInteger K7 { get => GetRegister(Register.K7); set => SetRegister(Register.K7, value); }
        public BigInteger Bnd0 { get => GetRegister(Register.Bnd0); set => SetRegister(Register.Bnd0, value); }
        public BigInteger Bnd1 { get => GetRegister(Register.Bnd1); set => SetRegister(Register.Bnd1, value); }
        public BigInteger Bnd2 { get => GetRegister(Register.Bnd2); set => SetRegister(Register.Bnd2, value); }
        public BigInteger Bnd3 { get => GetRegister(Register.Bnd3); set => SetRegister(Register.Bnd3, value); }
        public BigInteger BndCfg { get => GetRegister(Register.BndCfg); set => SetRegister(Register.BndCfg, value); }
        public BigInteger BndStatus { get => GetRegister(Register.BndStatus); set => SetRegister(Register.BndStatus, value); }
        public BigInteger Mxcsr { get => GetRegister(Register.Mxcsr); set => SetRegister(Register.Mxcsr, value); }
        public BigInteger Pkru { get => GetRegister(Register.Pkru); set => SetRegister(Register.Pkru, value); }
        public BigInteger Xcr0 { get => GetRegister(Register.Xcr0); set => SetRegister(Register.Xcr0, value); }

        // Host Specific
#if _X64_
        public nuint Nax { get => (nuint)GetRegisterU64(Register.Rax); set => SetRegisterU64(Register.Rax, value); }
        public nuint Ncx { get => (nuint)GetRegisterU64(Register.Rcx); set => SetRegisterU64(Register.Rcx, value); }
        public nuint Ndx { get => (nuint)GetRegisterU64(Register.Rdx); set => SetRegisterU64(Register.Rdx, value); }
        public nuint Nbx { get => (nuint)GetRegisterU64(Register.Rbx); set => SetRegisterU64(Register.Rbx, value); }
        public nuint Nsp { get => (nuint)GetRegisterU64(Register.Rsp); set => SetRegisterU64(Register.Rsp, value); }
        public nuint Nbp { get => (nuint)GetRegisterU64(Register.Rbp); set => SetRegisterU64(Register.Rbp, value); }
        public nuint Nsi { get => (nuint)GetRegisterU64(Register.Rsi); set => SetRegisterU64(Register.Rsi, value); }
        public nuint Ndi { get => (nuint)GetRegisterU64(Register.Rdi); set => SetRegisterU64(Register.Rdi, value); }
        public nuint Nip { get => (nuint)GetRegisterU64(Register.Rip); set => SetRegisterU64(Register.Rip, value); }
#else
        public nuint Nax { get => (nuint)GetRegisterU32(Register.Eax); set => SetRegisterU32(Register.Eax, value); }
        public nuint Ncx { get => (nuint)GetRegisterU32(Register.Ecx); set => SetRegisterU32(Register.Ecx, value); }
        public nuint Ndx { get => (nuint)GetRegisterU32(Register.Edx); set => SetRegisterU32(Register.Edx, value); }
        public nuint Nbx { get => (nuint)GetRegisterU32(Register.Ebx); set => SetRegisterU32(Register.Ebx, value); }
        public nuint Nsp { get => (nuint)GetRegisterU32(Register.Esp); set => SetRegisterU32(Register.Esp, value); }
        public nuint Nbp { get => (nuint)GetRegisterU32(Register.Ebp); set => SetRegisterU32(Register.Ebp, value); }
        public nuint Nsi { get => (nuint)GetRegisterU32(Register.Esi); set => SetRegisterU32(Register.Esi, value); }
        public nuint Ndi { get => (nuint)GetRegisterU32(Register.Edi); set => SetRegisterU32(Register.Edi, value); }
        public nuint Nip { get => (nuint)GetRegisterU32(Register.Eip); set => SetRegisterU32(Register.Eip, value); }
#endif
    }
}
