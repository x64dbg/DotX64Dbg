using System;
using System.Numerics;

namespace Dotx64Dbg
{
    public partial class Thread
    {
        private byte GetRegisterU8(Registers.Id reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return bytes[0];
        }

        private void SetRegisterU8(Registers.Id reg, byte val)
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private ushort GetRegisterU16(Registers.Id reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt16(bytes);
        }

        private void SetRegisterU16(Registers.Id reg, ushort val)
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private uint GetRegisterU32(Registers.Id reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt32(bytes);
        }

#if _X64_
        private void SetRegisterU32(Registers.Id reg, uint val)
#else

        private void SetRegisterU32(Registers.Id reg, nuint val)
#endif
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        private ulong GetRegisterU64(Registers.Id reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return BitConverter.ToUInt64(bytes);
        }


#if _X64_
        private void SetRegisterU64(Registers.Id reg, nuint val)
#else

        private void SetRegisterU64(Registers.Id reg, ulong val)
#endif
        {
            Native.Thread.SetRegisterData(Handle, reg, BitConverter.GetBytes(val));
        }

        public BigInteger GetRegister(Registers.Id reg)
        {
            var bytes = Native.Thread.GetRegisterData(Handle, reg);
            return new BigInteger(bytes, true);
        }

        public void SetRegister(Registers.Id reg, BigInteger val)
        {
            Native.Thread.SetRegisterData(Handle, reg, val.ToByteArray());
        }

        public byte Al { get => GetRegisterU8(Registers.Id.Al); set => SetRegisterU8(Registers.Id.Al, value); }
        public byte Cl { get => GetRegisterU8(Registers.Id.Cl); set => SetRegisterU8(Registers.Id.Cl, value); }
        public byte Dl { get => GetRegisterU8(Registers.Id.Dl); set => SetRegisterU8(Registers.Id.Dl, value); }
        public byte Bl { get => GetRegisterU8(Registers.Id.Bl); set => SetRegisterU8(Registers.Id.Bl, value); }
        public byte Ah { get => GetRegisterU8(Registers.Id.Ah); set => SetRegisterU8(Registers.Id.Ah, value); }
        public byte Ch { get => GetRegisterU8(Registers.Id.Ch); set => SetRegisterU8(Registers.Id.Ch, value); }
        public byte Dh { get => GetRegisterU8(Registers.Id.Dh); set => SetRegisterU8(Registers.Id.Dh, value); }
        public byte Bh { get => GetRegisterU8(Registers.Id.Bh); set => SetRegisterU8(Registers.Id.Bh, value); }
        public byte Spl { get => GetRegisterU8(Registers.Id.Spl); set => SetRegisterU8(Registers.Id.Spl, value); }
        public byte Bpl { get => GetRegisterU8(Registers.Id.Bpl); set => SetRegisterU8(Registers.Id.Bpl, value); }
        public byte Sil { get => GetRegisterU8(Registers.Id.Sil); set => SetRegisterU8(Registers.Id.Sil, value); }
        public byte Dil { get => GetRegisterU8(Registers.Id.Dil); set => SetRegisterU8(Registers.Id.Dil, value); }
#if _X64_
        public byte R8b { get => GetRegisterU8(Registers.Id.R8b); set => SetRegisterU8(Registers.Id.R8b, value); }
        public byte R9b { get => GetRegisterU8(Registers.Id.R9b); set => SetRegisterU8(Registers.Id.R9b, value); }
        public byte R10b { get => GetRegisterU8(Registers.Id.R10b); set => SetRegisterU8(Registers.Id.R10b, value); }
        public byte R11b { get => GetRegisterU8(Registers.Id.R11b); set => SetRegisterU8(Registers.Id.R11b, value); }
        public byte R12b { get => GetRegisterU8(Registers.Id.R12b); set => SetRegisterU8(Registers.Id.R12b, value); }
        public byte R13b { get => GetRegisterU8(Registers.Id.R13b); set => SetRegisterU8(Registers.Id.R13b, value); }
        public byte R14b { get => GetRegisterU8(Registers.Id.R14b); set => SetRegisterU8(Registers.Id.R14b, value); }
        public byte R15b { get => GetRegisterU8(Registers.Id.R15b); set => SetRegisterU8(Registers.Id.R15b, value); }
#endif
        public ushort Ax { get => GetRegisterU16(Registers.Id.Ax); set => SetRegisterU16(Registers.Id.Ax, value); }
        public ushort Cx { get => GetRegisterU16(Registers.Id.Cx); set => SetRegisterU16(Registers.Id.Cx, value); }
        public ushort Dx { get => GetRegisterU16(Registers.Id.Dx); set => SetRegisterU16(Registers.Id.Dx, value); }
        public ushort Bx { get => GetRegisterU16(Registers.Id.Bx); set => SetRegisterU16(Registers.Id.Bx, value); }
        public ushort Sp { get => GetRegisterU16(Registers.Id.Sp); set => SetRegisterU16(Registers.Id.Sp, value); }
        public ushort Bp { get => GetRegisterU16(Registers.Id.Bp); set => SetRegisterU16(Registers.Id.Bp, value); }
        public ushort Si { get => GetRegisterU16(Registers.Id.Si); set => SetRegisterU16(Registers.Id.Si, value); }
        public ushort Di { get => GetRegisterU16(Registers.Id.Di); set => SetRegisterU16(Registers.Id.Di, value); }
#if _X64_
        public ushort R8w { get => GetRegisterU16(Registers.Id.R8w); set => SetRegisterU16(Registers.Id.R8w, value); }
        public ushort R9w { get => GetRegisterU16(Registers.Id.R9w); set => SetRegisterU16(Registers.Id.R9w, value); }
        public ushort R10w { get => GetRegisterU16(Registers.Id.R10w); set => SetRegisterU16(Registers.Id.R10w, value); }
        public ushort R11w { get => GetRegisterU16(Registers.Id.R11w); set => SetRegisterU16(Registers.Id.R11w, value); }
        public ushort R12w { get => GetRegisterU16(Registers.Id.R12w); set => SetRegisterU16(Registers.Id.R12w, value); }
        public ushort R13w { get => GetRegisterU16(Registers.Id.R13w); set => SetRegisterU16(Registers.Id.R13w, value); }
        public ushort R14w { get => GetRegisterU16(Registers.Id.R14w); set => SetRegisterU16(Registers.Id.R14w, value); }
        public ushort R15w { get => GetRegisterU16(Registers.Id.R15w); set => SetRegisterU16(Registers.Id.R15w, value); }
#endif

#if _X64_
        public uint Eax { get => GetRegisterU32(Registers.Id.Eax); set => SetRegisterU32(Registers.Id.Eax, value); }
        public uint Ecx { get => GetRegisterU32(Registers.Id.Ecx); set => SetRegisterU32(Registers.Id.Ecx, value); }
        public uint Edx { get => GetRegisterU32(Registers.Id.Edx); set => SetRegisterU32(Registers.Id.Edx, value); }
        public uint Ebx { get => GetRegisterU32(Registers.Id.Ebx); set => SetRegisterU32(Registers.Id.Ebx, value); }
        public uint Esp { get => GetRegisterU32(Registers.Id.Esp); set => SetRegisterU32(Registers.Id.Esp, value); }
        public uint Ebp { get => GetRegisterU32(Registers.Id.Ebp); set => SetRegisterU32(Registers.Id.Ebp, value); }
        public uint Esi { get => GetRegisterU32(Registers.Id.Esi); set => SetRegisterU32(Registers.Id.Esi, value); }
        public uint Edi { get => GetRegisterU32(Registers.Id.Edi); set => SetRegisterU32(Registers.Id.Edi, value); }
#else
        public nuint Eax { get => (nuint)GetRegisterU32(Registers.Id.Eax); set => SetRegisterU32(Registers.Id.Eax, value); }
        public nuint Ecx { get => (nuint)GetRegisterU32(Registers.Id.Ecx); set => SetRegisterU32(Registers.Id.Ecx, value); }
        public nuint Edx { get => (nuint)GetRegisterU32(Registers.Id.Edx); set => SetRegisterU32(Registers.Id.Edx, value); }
        public nuint Ebx { get => (nuint)GetRegisterU32(Registers.Id.Ebx); set => SetRegisterU32(Registers.Id.Ebx, value); }
        public nuint Esp { get => (nuint)GetRegisterU32(Registers.Id.Esp); set => SetRegisterU32(Registers.Id.Esp, value); }
        public nuint Ebp { get => (nuint)GetRegisterU32(Registers.Id.Ebp); set => SetRegisterU32(Registers.Id.Ebp, value); }
        public nuint Esi { get => (nuint)GetRegisterU32(Registers.Id.Esi); set => SetRegisterU32(Registers.Id.Esi, value); }
        public nuint Edi { get => (nuint)GetRegisterU32(Registers.Id.Edi); set => SetRegisterU32(Registers.Id.Edi, value); }
#endif

#if _X64_
        public uint R8d { get => GetRegisterU32(Registers.Id.R8d); set => SetRegisterU32(Registers.Id.R8d, value); }
        public uint R9d { get => GetRegisterU32(Registers.Id.R9d); set => SetRegisterU32(Registers.Id.R9d, value); }
        public uint R10d { get => GetRegisterU32(Registers.Id.R10d); set => SetRegisterU32(Registers.Id.R10d, value); }
        public uint R11d { get => GetRegisterU32(Registers.Id.R11d); set => SetRegisterU32(Registers.Id.R11d, value); }
        public uint R12d { get => GetRegisterU32(Registers.Id.R12d); set => SetRegisterU32(Registers.Id.R12d, value); }
        public uint R13d { get => GetRegisterU32(Registers.Id.R13d); set => SetRegisterU32(Registers.Id.R13d, value); }
        public uint R14d { get => GetRegisterU32(Registers.Id.R14d); set => SetRegisterU32(Registers.Id.R14d, value); }
        public uint R15d { get => GetRegisterU32(Registers.Id.R15d); set => SetRegisterU32(Registers.Id.R15d, value); }
        public nuint Rax { get => (nuint)GetRegisterU64(Registers.Id.Rax); set => SetRegisterU64(Registers.Id.Rax, value); }
        public nuint Rcx { get => (nuint)GetRegisterU64(Registers.Id.Rcx); set => SetRegisterU64(Registers.Id.Rcx, value); }
        public nuint Rdx { get => (nuint)GetRegisterU64(Registers.Id.Rdx); set => SetRegisterU64(Registers.Id.Rdx, value); }
        public nuint Rbx { get => (nuint)GetRegisterU64(Registers.Id.Rbx); set => SetRegisterU64(Registers.Id.Rbx, value); }
        public nuint Rsp { get => (nuint)GetRegisterU64(Registers.Id.Rsp); set => SetRegisterU64(Registers.Id.Rsp, value); }
        public nuint Rbp { get => (nuint)GetRegisterU64(Registers.Id.Rbp); set => SetRegisterU64(Registers.Id.Rbp, value); }
        public nuint Rsi { get => (nuint)GetRegisterU64(Registers.Id.Rsi); set => SetRegisterU64(Registers.Id.Rsi, value); }
        public nuint Rdi { get => (nuint)GetRegisterU64(Registers.Id.Rdi); set => SetRegisterU64(Registers.Id.Rdi, value); }
        public nuint R8 { get => (nuint)GetRegisterU64(Registers.Id.R8); set => SetRegisterU64(Registers.Id.R8, value); }
        public nuint R9 { get => (nuint)GetRegisterU64(Registers.Id.R9); set => SetRegisterU64(Registers.Id.R9, value); }
        public nuint R10 { get => (nuint)GetRegisterU64(Registers.Id.R10); set => SetRegisterU64(Registers.Id.R10, value); }
        public nuint R11 { get => (nuint)GetRegisterU64(Registers.Id.R11); set => SetRegisterU64(Registers.Id.R11, value); }
        public nuint R12 { get => (nuint)GetRegisterU64(Registers.Id.R12); set => SetRegisterU64(Registers.Id.R12, value); }
        public nuint R13 { get => (nuint)GetRegisterU64(Registers.Id.R13); set => SetRegisterU64(Registers.Id.R13, value); }
        public nuint R14 { get => (nuint)GetRegisterU64(Registers.Id.R14); set => SetRegisterU64(Registers.Id.R14, value); }
        public nuint R15 { get => (nuint)GetRegisterU64(Registers.Id.R15); set => SetRegisterU64(Registers.Id.R15, value); }
#endif
        public BigInteger St0 { get => GetRegister(Registers.Id.St0); set => SetRegister(Registers.Id.St0, value); }
        public BigInteger St1 { get => GetRegister(Registers.Id.St1); set => SetRegister(Registers.Id.St1, value); }
        public BigInteger St2 { get => GetRegister(Registers.Id.St2); set => SetRegister(Registers.Id.St2, value); }
        public BigInteger St3 { get => GetRegister(Registers.Id.St3); set => SetRegister(Registers.Id.St3, value); }
        public BigInteger St4 { get => GetRegister(Registers.Id.St4); set => SetRegister(Registers.Id.St4, value); }
        public BigInteger St5 { get => GetRegister(Registers.Id.St5); set => SetRegister(Registers.Id.St5, value); }
        public BigInteger St6 { get => GetRegister(Registers.Id.St6); set => SetRegister(Registers.Id.St6, value); }
        public BigInteger St7 { get => GetRegister(Registers.Id.St7); set => SetRegister(Registers.Id.St7, value); }
        public BigInteger X87Control { get => GetRegister(Registers.Id.X87Control); set => SetRegister(Registers.Id.X87Control, value); }
        public BigInteger X87Status { get => GetRegister(Registers.Id.X87Status); set => SetRegister(Registers.Id.X87Status, value); }
        public BigInteger X87Tag { get => GetRegister(Registers.Id.X87Tag); set => SetRegister(Registers.Id.X87Tag, value); }
        public BigInteger Mm0 { get => GetRegister(Registers.Id.Mm0); set => SetRegister(Registers.Id.Mm0, value); }
        public BigInteger Mm1 { get => GetRegister(Registers.Id.Mm1); set => SetRegister(Registers.Id.Mm1, value); }
        public BigInteger Mm2 { get => GetRegister(Registers.Id.Mm2); set => SetRegister(Registers.Id.Mm2, value); }
        public BigInteger Mm3 { get => GetRegister(Registers.Id.Mm3); set => SetRegister(Registers.Id.Mm3, value); }
        public BigInteger Mm4 { get => GetRegister(Registers.Id.Mm4); set => SetRegister(Registers.Id.Mm4, value); }
        public BigInteger Mm5 { get => GetRegister(Registers.Id.Mm5); set => SetRegister(Registers.Id.Mm5, value); }
        public BigInteger Mm6 { get => GetRegister(Registers.Id.Mm6); set => SetRegister(Registers.Id.Mm6, value); }
        public BigInteger Mm7 { get => GetRegister(Registers.Id.Mm7); set => SetRegister(Registers.Id.Mm7, value); }
        public BigInteger Xmm0 { get => GetRegister(Registers.Id.Xmm0); set => SetRegister(Registers.Id.Xmm0, value); }
        public BigInteger Xmm1 { get => GetRegister(Registers.Id.Xmm1); set => SetRegister(Registers.Id.Xmm1, value); }
        public BigInteger Xmm2 { get => GetRegister(Registers.Id.Xmm2); set => SetRegister(Registers.Id.Xmm2, value); }
        public BigInteger Xmm3 { get => GetRegister(Registers.Id.Xmm3); set => SetRegister(Registers.Id.Xmm3, value); }
        public BigInteger Xmm4 { get => GetRegister(Registers.Id.Xmm4); set => SetRegister(Registers.Id.Xmm4, value); }
        public BigInteger Xmm5 { get => GetRegister(Registers.Id.Xmm5); set => SetRegister(Registers.Id.Xmm5, value); }
        public BigInteger Xmm6 { get => GetRegister(Registers.Id.Xmm6); set => SetRegister(Registers.Id.Xmm6, value); }
        public BigInteger Xmm7 { get => GetRegister(Registers.Id.Xmm7); set => SetRegister(Registers.Id.Xmm7, value); }
        public BigInteger Xmm8 { get => GetRegister(Registers.Id.Xmm8); set => SetRegister(Registers.Id.Xmm8, value); }
        public BigInteger Xmm9 { get => GetRegister(Registers.Id.Xmm9); set => SetRegister(Registers.Id.Xmm9, value); }
        public BigInteger Xmm10 { get => GetRegister(Registers.Id.Xmm10); set => SetRegister(Registers.Id.Xmm10, value); }
        public BigInteger Xmm11 { get => GetRegister(Registers.Id.Xmm11); set => SetRegister(Registers.Id.Xmm11, value); }
        public BigInteger Xmm12 { get => GetRegister(Registers.Id.Xmm12); set => SetRegister(Registers.Id.Xmm12, value); }
        public BigInteger Xmm13 { get => GetRegister(Registers.Id.Xmm13); set => SetRegister(Registers.Id.Xmm13, value); }
        public BigInteger Xmm14 { get => GetRegister(Registers.Id.Xmm14); set => SetRegister(Registers.Id.Xmm14, value); }
        public BigInteger Xmm15 { get => GetRegister(Registers.Id.Xmm15); set => SetRegister(Registers.Id.Xmm15, value); }
        public BigInteger Xmm16 { get => GetRegister(Registers.Id.Xmm16); set => SetRegister(Registers.Id.Xmm16, value); }
        public BigInteger Xmm17 { get => GetRegister(Registers.Id.Xmm17); set => SetRegister(Registers.Id.Xmm17, value); }
        public BigInteger Xmm18 { get => GetRegister(Registers.Id.Xmm18); set => SetRegister(Registers.Id.Xmm18, value); }
        public BigInteger Xmm19 { get => GetRegister(Registers.Id.Xmm19); set => SetRegister(Registers.Id.Xmm19, value); }
        public BigInteger Xmm20 { get => GetRegister(Registers.Id.Xmm20); set => SetRegister(Registers.Id.Xmm20, value); }
        public BigInteger Xmm21 { get => GetRegister(Registers.Id.Xmm21); set => SetRegister(Registers.Id.Xmm21, value); }
        public BigInteger Xmm22 { get => GetRegister(Registers.Id.Xmm22); set => SetRegister(Registers.Id.Xmm22, value); }
        public BigInteger Xmm23 { get => GetRegister(Registers.Id.Xmm23); set => SetRegister(Registers.Id.Xmm23, value); }
        public BigInteger Xmm24 { get => GetRegister(Registers.Id.Xmm24); set => SetRegister(Registers.Id.Xmm24, value); }
        public BigInteger Xmm25 { get => GetRegister(Registers.Id.Xmm25); set => SetRegister(Registers.Id.Xmm25, value); }
        public BigInteger Xmm26 { get => GetRegister(Registers.Id.Xmm26); set => SetRegister(Registers.Id.Xmm26, value); }
        public BigInteger Xmm27 { get => GetRegister(Registers.Id.Xmm27); set => SetRegister(Registers.Id.Xmm27, value); }
        public BigInteger Xmm28 { get => GetRegister(Registers.Id.Xmm28); set => SetRegister(Registers.Id.Xmm28, value); }
        public BigInteger Xmm29 { get => GetRegister(Registers.Id.Xmm29); set => SetRegister(Registers.Id.Xmm29, value); }
        public BigInteger Xmm30 { get => GetRegister(Registers.Id.Xmm30); set => SetRegister(Registers.Id.Xmm30, value); }
        public BigInteger Xmm31 { get => GetRegister(Registers.Id.Xmm31); set => SetRegister(Registers.Id.Xmm31, value); }
        public BigInteger Ymm0 { get => GetRegister(Registers.Id.Ymm0); set => SetRegister(Registers.Id.Ymm0, value); }
        public BigInteger Ymm1 { get => GetRegister(Registers.Id.Ymm1); set => SetRegister(Registers.Id.Ymm1, value); }
        public BigInteger Ymm2 { get => GetRegister(Registers.Id.Ymm2); set => SetRegister(Registers.Id.Ymm2, value); }
        public BigInteger Ymm3 { get => GetRegister(Registers.Id.Ymm3); set => SetRegister(Registers.Id.Ymm3, value); }
        public BigInteger Ymm4 { get => GetRegister(Registers.Id.Ymm4); set => SetRegister(Registers.Id.Ymm4, value); }
        public BigInteger Ymm5 { get => GetRegister(Registers.Id.Ymm5); set => SetRegister(Registers.Id.Ymm5, value); }
        public BigInteger Ymm6 { get => GetRegister(Registers.Id.Ymm6); set => SetRegister(Registers.Id.Ymm6, value); }
        public BigInteger Ymm7 { get => GetRegister(Registers.Id.Ymm7); set => SetRegister(Registers.Id.Ymm7, value); }
        public BigInteger Ymm8 { get => GetRegister(Registers.Id.Ymm8); set => SetRegister(Registers.Id.Ymm8, value); }
        public BigInteger Ymm9 { get => GetRegister(Registers.Id.Ymm9); set => SetRegister(Registers.Id.Ymm9, value); }
        public BigInteger Ymm10 { get => GetRegister(Registers.Id.Ymm10); set => SetRegister(Registers.Id.Ymm10, value); }
        public BigInteger Ymm11 { get => GetRegister(Registers.Id.Ymm11); set => SetRegister(Registers.Id.Ymm11, value); }
        public BigInteger Ymm12 { get => GetRegister(Registers.Id.Ymm12); set => SetRegister(Registers.Id.Ymm12, value); }
        public BigInteger Ymm13 { get => GetRegister(Registers.Id.Ymm13); set => SetRegister(Registers.Id.Ymm13, value); }
        public BigInteger Ymm14 { get => GetRegister(Registers.Id.Ymm14); set => SetRegister(Registers.Id.Ymm14, value); }
        public BigInteger Ymm15 { get => GetRegister(Registers.Id.Ymm15); set => SetRegister(Registers.Id.Ymm15, value); }
        public BigInteger Ymm16 { get => GetRegister(Registers.Id.Ymm16); set => SetRegister(Registers.Id.Ymm16, value); }
        public BigInteger Ymm17 { get => GetRegister(Registers.Id.Ymm17); set => SetRegister(Registers.Id.Ymm17, value); }
        public BigInteger Ymm18 { get => GetRegister(Registers.Id.Ymm18); set => SetRegister(Registers.Id.Ymm18, value); }
        public BigInteger Ymm19 { get => GetRegister(Registers.Id.Ymm19); set => SetRegister(Registers.Id.Ymm19, value); }
        public BigInteger Ymm20 { get => GetRegister(Registers.Id.Ymm20); set => SetRegister(Registers.Id.Ymm20, value); }
        public BigInteger Ymm21 { get => GetRegister(Registers.Id.Ymm21); set => SetRegister(Registers.Id.Ymm21, value); }
        public BigInteger Ymm22 { get => GetRegister(Registers.Id.Ymm22); set => SetRegister(Registers.Id.Ymm22, value); }
        public BigInteger Ymm23 { get => GetRegister(Registers.Id.Ymm23); set => SetRegister(Registers.Id.Ymm23, value); }
        public BigInteger Ymm24 { get => GetRegister(Registers.Id.Ymm24); set => SetRegister(Registers.Id.Ymm24, value); }
        public BigInteger Ymm25 { get => GetRegister(Registers.Id.Ymm25); set => SetRegister(Registers.Id.Ymm25, value); }
        public BigInteger Ymm26 { get => GetRegister(Registers.Id.Ymm26); set => SetRegister(Registers.Id.Ymm26, value); }
        public BigInteger Ymm27 { get => GetRegister(Registers.Id.Ymm27); set => SetRegister(Registers.Id.Ymm27, value); }
        public BigInteger Ymm28 { get => GetRegister(Registers.Id.Ymm28); set => SetRegister(Registers.Id.Ymm28, value); }
        public BigInteger Ymm29 { get => GetRegister(Registers.Id.Ymm29); set => SetRegister(Registers.Id.Ymm29, value); }
        public BigInteger Ymm30 { get => GetRegister(Registers.Id.Ymm30); set => SetRegister(Registers.Id.Ymm30, value); }
        public BigInteger Ymm31 { get => GetRegister(Registers.Id.Ymm31); set => SetRegister(Registers.Id.Ymm31, value); }
        public BigInteger Zmm0 { get => GetRegister(Registers.Id.Zmm0); set => SetRegister(Registers.Id.Zmm0, value); }
        public BigInteger Zmm1 { get => GetRegister(Registers.Id.Zmm1); set => SetRegister(Registers.Id.Zmm1, value); }
        public BigInteger Zmm2 { get => GetRegister(Registers.Id.Zmm2); set => SetRegister(Registers.Id.Zmm2, value); }
        public BigInteger Zmm3 { get => GetRegister(Registers.Id.Zmm3); set => SetRegister(Registers.Id.Zmm3, value); }
        public BigInteger Zmm4 { get => GetRegister(Registers.Id.Zmm4); set => SetRegister(Registers.Id.Zmm4, value); }
        public BigInteger Zmm5 { get => GetRegister(Registers.Id.Zmm5); set => SetRegister(Registers.Id.Zmm5, value); }
        public BigInteger Zmm6 { get => GetRegister(Registers.Id.Zmm6); set => SetRegister(Registers.Id.Zmm6, value); }
        public BigInteger Zmm7 { get => GetRegister(Registers.Id.Zmm7); set => SetRegister(Registers.Id.Zmm7, value); }
        public BigInteger Zmm8 { get => GetRegister(Registers.Id.Zmm8); set => SetRegister(Registers.Id.Zmm8, value); }
        public BigInteger Zmm9 { get => GetRegister(Registers.Id.Zmm9); set => SetRegister(Registers.Id.Zmm9, value); }
        public BigInteger Zmm10 { get => GetRegister(Registers.Id.Zmm10); set => SetRegister(Registers.Id.Zmm10, value); }
        public BigInteger Zmm11 { get => GetRegister(Registers.Id.Zmm11); set => SetRegister(Registers.Id.Zmm11, value); }
        public BigInteger Zmm12 { get => GetRegister(Registers.Id.Zmm12); set => SetRegister(Registers.Id.Zmm12, value); }
        public BigInteger Zmm13 { get => GetRegister(Registers.Id.Zmm13); set => SetRegister(Registers.Id.Zmm13, value); }
        public BigInteger Zmm14 { get => GetRegister(Registers.Id.Zmm14); set => SetRegister(Registers.Id.Zmm14, value); }
        public BigInteger Zmm15 { get => GetRegister(Registers.Id.Zmm15); set => SetRegister(Registers.Id.Zmm15, value); }
        public BigInteger Zmm16 { get => GetRegister(Registers.Id.Zmm16); set => SetRegister(Registers.Id.Zmm16, value); }
        public BigInteger Zmm17 { get => GetRegister(Registers.Id.Zmm17); set => SetRegister(Registers.Id.Zmm17, value); }
        public BigInteger Zmm18 { get => GetRegister(Registers.Id.Zmm18); set => SetRegister(Registers.Id.Zmm18, value); }
        public BigInteger Zmm19 { get => GetRegister(Registers.Id.Zmm19); set => SetRegister(Registers.Id.Zmm19, value); }
        public BigInteger Zmm20 { get => GetRegister(Registers.Id.Zmm20); set => SetRegister(Registers.Id.Zmm20, value); }
        public BigInteger Zmm21 { get => GetRegister(Registers.Id.Zmm21); set => SetRegister(Registers.Id.Zmm21, value); }
        public BigInteger Zmm22 { get => GetRegister(Registers.Id.Zmm22); set => SetRegister(Registers.Id.Zmm22, value); }
        public BigInteger Zmm23 { get => GetRegister(Registers.Id.Zmm23); set => SetRegister(Registers.Id.Zmm23, value); }
        public BigInteger Zmm24 { get => GetRegister(Registers.Id.Zmm24); set => SetRegister(Registers.Id.Zmm24, value); }
        public BigInteger Zmm25 { get => GetRegister(Registers.Id.Zmm25); set => SetRegister(Registers.Id.Zmm25, value); }
        public BigInteger Zmm26 { get => GetRegister(Registers.Id.Zmm26); set => SetRegister(Registers.Id.Zmm26, value); }
        public BigInteger Zmm27 { get => GetRegister(Registers.Id.Zmm27); set => SetRegister(Registers.Id.Zmm27, value); }
        public BigInteger Zmm28 { get => GetRegister(Registers.Id.Zmm28); set => SetRegister(Registers.Id.Zmm28, value); }
        public BigInteger Zmm29 { get => GetRegister(Registers.Id.Zmm29); set => SetRegister(Registers.Id.Zmm29, value); }
        public BigInteger Zmm30 { get => GetRegister(Registers.Id.Zmm30); set => SetRegister(Registers.Id.Zmm30, value); }
        public BigInteger Zmm31 { get => GetRegister(Registers.Id.Zmm31); set => SetRegister(Registers.Id.Zmm31, value); }
        public BigInteger Flags { get => GetRegister(Registers.Id.Flags); set => SetRegister(Registers.Id.Flags, value); }

#if _X64_
        public uint EFlags { get => GetRegisterU32(Registers.Id.EFlags); set => SetRegisterU32(Registers.Id.EFlags, value); }
        public nuint RFlags { get => (nuint)GetRegisterU64(Registers.Id.RFlags); set => SetRegisterU64(Registers.Id.RFlags, value); }
#else
        public nuint EFlags { get => (nuint)GetRegisterU32(Registers.Id.EFlags); set => SetRegisterU32(Registers.Id.EFlags, value); }
#endif
        public ushort Ip { get => GetRegisterU16(Registers.Id.Ip); set => SetRegisterU16(Registers.Id.Ip, value); }

#if _X64_
        public uint Eip { get => GetRegisterU32(Registers.Id.Eip); set => SetRegisterU32(Registers.Id.Eip, value); }
        public nuint Rip { get => (nuint)GetRegisterU64(Registers.Id.Rip); set => SetRegisterU64(Registers.Id.Rip, value); }
#else
        public nuint Eip { get => (nuint)GetRegisterU32(Registers.Id.Eip); set => SetRegisterU32(Registers.Id.Eip, value); }
#endif

        public ushort Es { get => GetRegisterU16(Registers.Id.Es); set => SetRegisterU16(Registers.Id.Es, value); }
        public ushort Cs { get => GetRegisterU16(Registers.Id.Cs); set => SetRegisterU16(Registers.Id.Cs, value); }
        public ushort Ss { get => GetRegisterU16(Registers.Id.Ss); set => SetRegisterU16(Registers.Id.Ss, value); }
        public ushort Ds { get => GetRegisterU16(Registers.Id.Ds); set => SetRegisterU16(Registers.Id.Ds, value); }
        public ushort Fs { get => GetRegisterU16(Registers.Id.Fs); set => SetRegisterU16(Registers.Id.Fs, value); }
        public ushort Gs { get => GetRegisterU16(Registers.Id.Gs); set => SetRegisterU16(Registers.Id.Gs, value); }
        public BigInteger Gdtr { get => GetRegister(Registers.Id.Gdtr); set => SetRegister(Registers.Id.Gdtr, value); }
        public BigInteger Ldtr { get => GetRegister(Registers.Id.Ldtr); set => SetRegister(Registers.Id.Ldtr, value); }
        public BigInteger Idtr { get => GetRegister(Registers.Id.Idtr); set => SetRegister(Registers.Id.Idtr, value); }
        public BigInteger Tr { get => GetRegister(Registers.Id.Tr); set => SetRegister(Registers.Id.Tr, value); }
        public BigInteger Tr0 { get => GetRegister(Registers.Id.Tr0); set => SetRegister(Registers.Id.Tr0, value); }
        public BigInteger Tr1 { get => GetRegister(Registers.Id.Tr1); set => SetRegister(Registers.Id.Tr1, value); }
        public BigInteger Tr2 { get => GetRegister(Registers.Id.Tr2); set => SetRegister(Registers.Id.Tr2, value); }
        public BigInteger Tr3 { get => GetRegister(Registers.Id.Tr3); set => SetRegister(Registers.Id.Tr3, value); }
        public BigInteger Tr4 { get => GetRegister(Registers.Id.Tr4); set => SetRegister(Registers.Id.Tr4, value); }
        public BigInteger Tr5 { get => GetRegister(Registers.Id.Tr5); set => SetRegister(Registers.Id.Tr5, value); }
        public BigInteger Tr6 { get => GetRegister(Registers.Id.Tr6); set => SetRegister(Registers.Id.Tr6, value); }
        public BigInteger Tr7 { get => GetRegister(Registers.Id.Tr7); set => SetRegister(Registers.Id.Tr7, value); }
        public BigInteger Cr0 { get => GetRegister(Registers.Id.Cr0); set => SetRegister(Registers.Id.Cr0, value); }
        public BigInteger Cr1 { get => GetRegister(Registers.Id.Cr1); set => SetRegister(Registers.Id.Cr1, value); }
        public BigInteger Cr2 { get => GetRegister(Registers.Id.Cr2); set => SetRegister(Registers.Id.Cr2, value); }
        public BigInteger Cr3 { get => GetRegister(Registers.Id.Cr3); set => SetRegister(Registers.Id.Cr3, value); }
        public BigInteger Cr4 { get => GetRegister(Registers.Id.Cr4); set => SetRegister(Registers.Id.Cr4, value); }
        public BigInteger Cr5 { get => GetRegister(Registers.Id.Cr5); set => SetRegister(Registers.Id.Cr5, value); }
        public BigInteger Cr6 { get => GetRegister(Registers.Id.Cr6); set => SetRegister(Registers.Id.Cr6, value); }
        public BigInteger Cr7 { get => GetRegister(Registers.Id.Cr7); set => SetRegister(Registers.Id.Cr7, value); }
        public BigInteger Cr8 { get => GetRegister(Registers.Id.Cr8); set => SetRegister(Registers.Id.Cr8, value); }
        public BigInteger Cr9 { get => GetRegister(Registers.Id.Cr9); set => SetRegister(Registers.Id.Cr9, value); }
        public BigInteger Cr10 { get => GetRegister(Registers.Id.Cr10); set => SetRegister(Registers.Id.Cr10, value); }
        public BigInteger Cr11 { get => GetRegister(Registers.Id.Cr11); set => SetRegister(Registers.Id.Cr11, value); }
        public BigInteger Cr12 { get => GetRegister(Registers.Id.Cr12); set => SetRegister(Registers.Id.Cr12, value); }
        public BigInteger Cr13 { get => GetRegister(Registers.Id.Cr13); set => SetRegister(Registers.Id.Cr13, value); }
        public BigInteger Cr14 { get => GetRegister(Registers.Id.Cr14); set => SetRegister(Registers.Id.Cr14, value); }
        public BigInteger Cr15 { get => GetRegister(Registers.Id.Cr15); set => SetRegister(Registers.Id.Cr15, value); }
#if _X64_
        public nuint Dr0 { get => (nuint)GetRegisterU64(Registers.Id.Dr0); set => SetRegisterU64(Registers.Id.Dr0, value); }
        public nuint Dr1 { get => (nuint)GetRegisterU64(Registers.Id.Dr1); set => SetRegisterU64(Registers.Id.Dr1, value); }
        public nuint Dr2 { get => (nuint)GetRegisterU64(Registers.Id.Dr2); set => SetRegisterU64(Registers.Id.Dr2, value); }
        public nuint Dr3 { get => (nuint)GetRegisterU64(Registers.Id.Dr3); set => SetRegisterU64(Registers.Id.Dr3, value); }
        public nuint Dr4 { get => (nuint)GetRegisterU64(Registers.Id.Dr4); set => SetRegisterU64(Registers.Id.Dr4, value); }
        public nuint Dr5 { get => (nuint)GetRegisterU64(Registers.Id.Dr5); set => SetRegisterU64(Registers.Id.Dr5, value); }
        public nuint Dr6 { get => (nuint)GetRegisterU64(Registers.Id.Dr6); set => SetRegisterU64(Registers.Id.Dr6, value); }
        public nuint Dr7 { get => (nuint)GetRegisterU64(Registers.Id.Dr7); set => SetRegisterU64(Registers.Id.Dr7, value); }
        public nuint Dr8 { get => (nuint)GetRegisterU64(Registers.Id.Dr8); set => SetRegisterU64(Registers.Id.Dr8, value); }
        public nuint Dr9 { get => (nuint)GetRegisterU64(Registers.Id.Dr9); set => SetRegisterU64(Registers.Id.Dr9, value); }
        public nuint Dr10 { get => (nuint)GetRegisterU64(Registers.Id.Dr10); set => SetRegisterU64(Registers.Id.Dr10, value); }
        public nuint Dr11 { get => (nuint)GetRegisterU64(Registers.Id.Dr11); set => SetRegisterU64(Registers.Id.Dr11, value); }
        public nuint Dr12 { get => (nuint)GetRegisterU64(Registers.Id.Dr12); set => SetRegisterU64(Registers.Id.Dr12, value); }
        public nuint Dr13 { get => (nuint)GetRegisterU64(Registers.Id.Dr13); set => SetRegisterU64(Registers.Id.Dr13, value); }
        public nuint Dr14 { get => (nuint)GetRegisterU64(Registers.Id.Dr14); set => SetRegisterU64(Registers.Id.Dr14, value); }
        public nuint Dr15 { get => (nuint)GetRegisterU64(Registers.Id.Dr15); set => SetRegisterU64(Registers.Id.Dr15, value); }
#else
        public nuint Dr0 { get => (nuint)GetRegisterU32(Registers.Id.Dr0); set => SetRegisterU32(Registers.Id.Dr0, value); }
        public nuint Dr1 { get => (nuint)GetRegisterU32(Registers.Id.Dr1); set => SetRegisterU32(Registers.Id.Dr1, value); }
        public nuint Dr2 { get => (nuint)GetRegisterU32(Registers.Id.Dr2); set => SetRegisterU32(Registers.Id.Dr2, value); }
        public nuint Dr3 { get => (nuint)GetRegisterU32(Registers.Id.Dr3); set => SetRegisterU32(Registers.Id.Dr3, value); }
        public nuint Dr4 { get => (nuint)GetRegisterU32(Registers.Id.Dr4); set => SetRegisterU32(Registers.Id.Dr4, value); }
        public nuint Dr5 { get => (nuint)GetRegisterU32(Registers.Id.Dr5); set => SetRegisterU32(Registers.Id.Dr5, value); }
        public nuint Dr6 { get => (nuint)GetRegisterU32(Registers.Id.Dr6); set => SetRegisterU32(Registers.Id.Dr6, value); }
        public nuint Dr7 { get => (nuint)GetRegisterU32(Registers.Id.Dr7); set => SetRegisterU32(Registers.Id.Dr7, value); }
        public nuint Dr8 { get => (nuint)GetRegisterU32(Registers.Id.Dr8); set => SetRegisterU32(Registers.Id.Dr8, value); }
        public nuint Dr9 { get => (nuint)GetRegisterU32(Registers.Id.Dr9); set => SetRegisterU32(Registers.Id.Dr9, value); }
        public nuint Dr10 { get => (nuint)GetRegisterU32(Registers.Id.Dr10); set => SetRegisterU32(Registers.Id.Dr10, value); }
        public nuint Dr11 { get => (nuint)GetRegisterU32(Registers.Id.Dr11); set => SetRegisterU32(Registers.Id.Dr11, value); }
        public nuint Dr12 { get => (nuint)GetRegisterU32(Registers.Id.Dr12); set => SetRegisterU32(Registers.Id.Dr12, value); }
        public nuint Dr13 { get => (nuint)GetRegisterU32(Registers.Id.Dr13); set => SetRegisterU32(Registers.Id.Dr13, value); }
        public nuint Dr14 { get => (nuint)GetRegisterU32(Registers.Id.Dr14); set => SetRegisterU32(Registers.Id.Dr14, value); }
        public nuint Dr15 { get => (nuint)GetRegisterU32(Registers.Id.Dr15); set => SetRegisterU32(Registers.Id.Dr15, value); }
#endif
        public BigInteger K0 { get => GetRegister(Registers.Id.K0); set => SetRegister(Registers.Id.K0, value); }
        public BigInteger K1 { get => GetRegister(Registers.Id.K1); set => SetRegister(Registers.Id.K1, value); }
        public BigInteger K2 { get => GetRegister(Registers.Id.K2); set => SetRegister(Registers.Id.K2, value); }
        public BigInteger K3 { get => GetRegister(Registers.Id.K3); set => SetRegister(Registers.Id.K3, value); }
        public BigInteger K4 { get => GetRegister(Registers.Id.K4); set => SetRegister(Registers.Id.K4, value); }
        public BigInteger K5 { get => GetRegister(Registers.Id.K5); set => SetRegister(Registers.Id.K5, value); }
        public BigInteger K6 { get => GetRegister(Registers.Id.K6); set => SetRegister(Registers.Id.K6, value); }
        public BigInteger K7 { get => GetRegister(Registers.Id.K7); set => SetRegister(Registers.Id.K7, value); }
        public BigInteger Bnd0 { get => GetRegister(Registers.Id.Bnd0); set => SetRegister(Registers.Id.Bnd0, value); }
        public BigInteger Bnd1 { get => GetRegister(Registers.Id.Bnd1); set => SetRegister(Registers.Id.Bnd1, value); }
        public BigInteger Bnd2 { get => GetRegister(Registers.Id.Bnd2); set => SetRegister(Registers.Id.Bnd2, value); }
        public BigInteger Bnd3 { get => GetRegister(Registers.Id.Bnd3); set => SetRegister(Registers.Id.Bnd3, value); }
        public BigInteger BndCfg { get => GetRegister(Registers.Id.BndCfg); set => SetRegister(Registers.Id.BndCfg, value); }
        public BigInteger BndStatus { get => GetRegister(Registers.Id.BndStatus); set => SetRegister(Registers.Id.BndStatus, value); }
        public BigInteger Mxcsr { get => GetRegister(Registers.Id.Mxcsr); set => SetRegister(Registers.Id.Mxcsr, value); }
        public BigInteger Pkru { get => GetRegister(Registers.Id.Pkru); set => SetRegister(Registers.Id.Pkru, value); }
        public BigInteger Xcr0 { get => GetRegister(Registers.Id.Xcr0); set => SetRegister(Registers.Id.Xcr0, value); }

        // Host Specific
#if _X64_
        public nuint Nax { get => (nuint)GetRegisterU64(Registers.Id.Rax); set => SetRegisterU64(Registers.Id.Rax, value); }
        public nuint Ncx { get => (nuint)GetRegisterU64(Registers.Id.Rcx); set => SetRegisterU64(Registers.Id.Rcx, value); }
        public nuint Ndx { get => (nuint)GetRegisterU64(Registers.Id.Rdx); set => SetRegisterU64(Registers.Id.Rdx, value); }
        public nuint Nbx { get => (nuint)GetRegisterU64(Registers.Id.Rbx); set => SetRegisterU64(Registers.Id.Rbx, value); }
        public nuint Nsp { get => (nuint)GetRegisterU64(Registers.Id.Rsp); set => SetRegisterU64(Registers.Id.Rsp, value); }
        public nuint Nbp { get => (nuint)GetRegisterU64(Registers.Id.Rbp); set => SetRegisterU64(Registers.Id.Rbp, value); }
        public nuint Nsi { get => (nuint)GetRegisterU64(Registers.Id.Rsi); set => SetRegisterU64(Registers.Id.Rsi, value); }
        public nuint Ndi { get => (nuint)GetRegisterU64(Registers.Id.Rdi); set => SetRegisterU64(Registers.Id.Rdi, value); }
        public nuint Nip { get => (nuint)GetRegisterU64(Registers.Id.Rip); set => SetRegisterU64(Registers.Id.Rip, value); }
#else
        public nuint Nax { get => (nuint)GetRegisterU32(Registers.Id.Eax); set => SetRegisterU32(Registers.Id.Eax, value); }
        public nuint Ncx { get => (nuint)GetRegisterU32(Registers.Id.Ecx); set => SetRegisterU32(Registers.Id.Ecx, value); }
        public nuint Ndx { get => (nuint)GetRegisterU32(Registers.Id.Edx); set => SetRegisterU32(Registers.Id.Edx, value); }
        public nuint Nbx { get => (nuint)GetRegisterU32(Registers.Id.Ebx); set => SetRegisterU32(Registers.Id.Ebx, value); }
        public nuint Nsp { get => (nuint)GetRegisterU32(Registers.Id.Esp); set => SetRegisterU32(Registers.Id.Esp, value); }
        public nuint Nbp { get => (nuint)GetRegisterU32(Registers.Id.Ebp); set => SetRegisterU32(Registers.Id.Ebp, value); }
        public nuint Nsi { get => (nuint)GetRegisterU32(Registers.Id.Esi); set => SetRegisterU32(Registers.Id.Esi, value); }
        public nuint Ndi { get => (nuint)GetRegisterU32(Registers.Id.Edi); set => SetRegisterU32(Registers.Id.Edi, value); }
        public nuint Nip { get => (nuint)GetRegisterU32(Registers.Id.Eip); set => SetRegisterU32(Registers.Id.Eip, value); }
#endif
    }
}
