#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include "Register.hpp"
#include "Mnemonic.hpp"
#include "Instruction.Operand.hpp"

namespace Dotx64Dbg {

    public ref class Operands
    {
    private:
        static int AddressSize()
        {
#ifdef _M_X64
            return 64;
#else
            return 32;
#endif
        }

    public:
        // Byte
        //////////////////////////////////////////////////////////////////////////
        static Operand::OpMem^ BytePtr(Register baseReg)
        {
            return gcnew Operand::OpMem(8, baseReg, Register::None, 0, 0);
        }
        static Operand::OpMem^ BytePtr(Operand::OpReg^ baseReg)
        {
            return gcnew Operand::OpMem(8, baseReg->Value, Register::None, 0, 0);
        }

        static Operand::OpMem^ BytePtr(Register baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(8, baseReg, Register::None, 0, disp);
        }
        static Operand::OpMem^ BytePtr(Operand::OpReg^ baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(8, baseReg->Value, Register::None, 0, disp);
        }

        static Operand::OpMem^ BytePtr(Register baseReg, Register index)
        {
            return gcnew Operand::OpMem(8, baseReg, index, 0, 0);
        }
        static Operand::OpMem^ BytePtr(Operand::OpReg^ baseReg, Operand::OpReg^ index)
        {
            return gcnew Operand::OpMem(8, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::OpMem^ BytePtr(Register baseReg, Register index, Int64 disp)
        {
            return gcnew Operand::OpMem(8, baseReg, index, 0, disp);
        }
        static Operand::OpMem^ BytePtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int64 disp)
        {
            return gcnew Operand::OpMem(8, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::OpMem^ BytePtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(8, baseReg, index, scale, disp);
        }
        static Operand::OpMem^ BytePtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(8, baseReg->Value, index->Value, scale, disp);
        }

        // Word
        //////////////////////////////////////////////////////////////////////////
        static Operand::OpMem^ WordPtr(Register baseReg)
        {
            return gcnew Operand::OpMem(16, baseReg, Register::None, 0, 0);
        }
        static Operand::OpMem^ WordPtr(Operand::OpReg^ baseReg)
        {
            return gcnew Operand::OpMem(16, baseReg->Value, Register::None, 0, 0);
        }

        static Operand::OpMem^ WordPtr(Register baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(16, baseReg, Register::None, 0, disp);
        }
        static Operand::OpMem^ WordPtr(Operand::OpReg^ baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(16, baseReg->Value, Register::None, 0, disp);
        }

        static Operand::OpMem^ WordPtr(Register baseReg, Register index)
        {
            return gcnew Operand::OpMem(16, baseReg, index, 0, 0);
        }
        static Operand::OpMem^ WordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index)
        {
            return gcnew Operand::OpMem(16, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::OpMem^ WordPtr(Register baseReg, Register index, Int64 disp)
        {
            return gcnew Operand::OpMem(16, baseReg, index, 0, disp);
        }
        static Operand::OpMem^ WordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int64 disp)
        {
            return gcnew Operand::OpMem(16, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::OpMem^ WordPtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(16, baseReg, index, scale, disp);
        }
        static Operand::OpMem^ WordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(16, baseReg->Value, index->Value, scale, disp);
        }

        // Dword
        //////////////////////////////////////////////////////////////////////////
        static Operand::OpMem^ DwordPtr(Register baseReg)
        {
            return gcnew Operand::OpMem(32, baseReg, Register::None, 0, 0);
        }
        static Operand::OpMem^ DwordPtr(Operand::OpReg^ baseReg)
        {
            return gcnew Operand::OpMem(32, baseReg->Value, Register::None, 0, 0);
        }

        static Operand::OpMem^ DwordPtr(Register baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(32, baseReg, Register::None, 0, disp);
        }
        static Operand::OpMem^ DwordPtr(Operand::OpReg^ baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(32, baseReg->Value, Register::None, 0, disp);
        }

        static Operand::OpMem^ DwordPtr(Register baseReg, Register index)
        {
            return gcnew Operand::OpMem(32, baseReg, index, 0, 0);
        }
        static Operand::OpMem^ DwordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index)
        {
            return gcnew Operand::OpMem(32, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::OpMem^ DwordPtr(Register baseReg, Register index, Int64 disp)
        {
            return gcnew Operand::OpMem(32, baseReg, index, 0, disp);
        }
        static Operand::OpMem^ DwordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int64 disp)
        {
            return gcnew Operand::OpMem(32, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::OpMem^ DwordPtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(32, baseReg, index, scale, disp);
        }
        static Operand::OpMem^ DwordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(32, baseReg->Value, index->Value, scale, disp);
        }

        // Qword
        //////////////////////////////////////////////////////////////////////////
        static Operand::OpMem^ QwordPtr(Register baseReg)
        {
            return gcnew Operand::OpMem(64, baseReg, Register::None, 0, 0);
        }
        static Operand::OpMem^ QwordPtr(Operand::OpReg^ baseReg)
        {
            return gcnew Operand::OpMem(64, baseReg->Value, Register::None, 0, 0);
        }


        static Operand::OpMem^ QwordPtr(Register baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(64, baseReg, Register::None, 0, disp);
        }
        static Operand::OpMem^ QwordPtr(Operand::OpReg^ baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(64, baseReg->Value, Register::None, 0, disp);
        }

        static Operand::OpMem^ QwordPtr(Register baseReg, Register index)
        {
            return gcnew Operand::OpMem(64, baseReg, index, 0, 0);
        }
        static Operand::OpMem^ QwordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index)
        {
            return gcnew Operand::OpMem(64, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::OpMem^ QwordPtr(Register baseReg, Register index, Int64 disp)
        {
            return gcnew Operand::OpMem(64, baseReg, index, 0, disp);
        }
        static Operand::OpMem^ QwordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int64 disp)
        {
            return gcnew Operand::OpMem(64, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::OpMem^ QwordPtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(64, baseReg, index, scale, disp);
        }
        static Operand::OpMem^ QwordPtr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(64, baseReg->Value, index->Value, scale, disp);
        }

        // Host
        //////////////////////////////////////////////////////////////////////////
        static Operand::OpMem^ Ptr(Register baseReg)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg, Register::None, 0, 0);
        }
        static Operand::OpMem^ Ptr(Operand::OpReg^ baseReg)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg->Value, Register::None, 0, 0);
        }

        static Operand::OpMem^ Ptr(Register baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg, Register::None, 0, disp);
        }
        static Operand::OpMem^ Ptr(Operand::OpReg^ baseReg, Int64 disp)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg->Value, Register::None, 0, disp);
        }

        static Operand::OpMem^ Ptr(Register baseReg, Register index)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg, index, 0, 0);
        }
        static Operand::OpMem^ Ptr(Operand::OpReg^ baseReg, Operand::OpReg^ index)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg->Value, index->Value, 0, 0);
        }

        static Operand::OpMem^ Ptr(Register baseReg, Register index, Int64 disp)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg, index, 0, disp);
        }
        static Operand::OpMem^ Ptr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int64 disp)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg->Value, index->Value, 0, disp);
        }

        static Operand::OpMem^ Ptr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg, index, scale, disp);
        }
        static Operand::OpMem^ Ptr(Operand::OpReg^ baseReg, Operand::OpReg^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::OpMem(AddressSize(), baseReg->Value, index->Value, scale, disp);
        }

    public:
        // General purpose registers  8-bit
        static initonly Operand::OpReg^ Al = gcnew Operand::OpReg(Register::Al);
        static initonly Operand::OpReg^ Cl = gcnew Operand::OpReg(Register::Cl);
        static initonly Operand::OpReg^ Dl = gcnew Operand::OpReg(Register::Dl);
        static initonly Operand::OpReg^ Bl = gcnew Operand::OpReg(Register::Bl);
        static initonly Operand::OpReg^ Ah = gcnew Operand::OpReg(Register::Ah);
        static initonly Operand::OpReg^ Ch = gcnew Operand::OpReg(Register::Ch);
        static initonly Operand::OpReg^ Dh = gcnew Operand::OpReg(Register::Dh);
        static initonly Operand::OpReg^ Bh = gcnew Operand::OpReg(Register::Bh);
        static initonly Operand::OpReg^ Spl = gcnew Operand::OpReg(Register::Spl);
        static initonly Operand::OpReg^ Bpl = gcnew Operand::OpReg(Register::Bpl);
        static initonly Operand::OpReg^ Sil = gcnew Operand::OpReg(Register::Sil);
        static initonly Operand::OpReg^ Dil = gcnew Operand::OpReg(Register::Dil);
#if _M_X64
        static initonly Operand::OpReg^ R8b = gcnew Operand::OpReg(Register::R8b);
        static initonly Operand::OpReg^ R9b = gcnew Operand::OpReg(Register::R9b);
        static initonly Operand::OpReg^ R10b = gcnew Operand::OpReg(Register::R10b);
        static initonly Operand::OpReg^ R11b = gcnew Operand::OpReg(Register::R11b);
        static initonly Operand::OpReg^ R12b = gcnew Operand::OpReg(Register::R12b);
        static initonly Operand::OpReg^ R13b = gcnew Operand::OpReg(Register::R13b);
        static initonly Operand::OpReg^ R14b = gcnew Operand::OpReg(Register::R14b);
        static initonly Operand::OpReg^ R15b = gcnew Operand::OpReg(Register::R15b);
#endif
        // General purpose registers 16-bit
        static initonly Operand::OpReg^ Ax = gcnew Operand::OpReg(Register::Ax);
        static initonly Operand::OpReg^ Cx = gcnew Operand::OpReg(Register::Cx);
        static initonly Operand::OpReg^ Dx = gcnew Operand::OpReg(Register::Dx);
        static initonly Operand::OpReg^ Bx = gcnew Operand::OpReg(Register::Bx);
        static initonly Operand::OpReg^ Sp = gcnew Operand::OpReg(Register::Sp);
        static initonly Operand::OpReg^ Bp = gcnew Operand::OpReg(Register::Bp);
        static initonly Operand::OpReg^ Si = gcnew Operand::OpReg(Register::Si);
        static initonly Operand::OpReg^ Di = gcnew Operand::OpReg(Register::Di);
#if _M_X64
        static initonly Operand::OpReg^ R8w = gcnew Operand::OpReg(Register::R8w);
        static initonly Operand::OpReg^ R9w = gcnew Operand::OpReg(Register::R9w);
        static initonly Operand::OpReg^ R10w = gcnew Operand::OpReg(Register::R10w);
        static initonly Operand::OpReg^ R11w = gcnew Operand::OpReg(Register::R11w);
        static initonly Operand::OpReg^ R12w = gcnew Operand::OpReg(Register::R12w);
        static initonly Operand::OpReg^ R13w = gcnew Operand::OpReg(Register::R13w);
        static initonly Operand::OpReg^ R14w = gcnew Operand::OpReg(Register::R14w);
        static initonly Operand::OpReg^ R15w = gcnew Operand::OpReg(Register::R15w);
#endif
        // General purpose registers 32-bit
        static initonly Operand::OpReg^ Eax = gcnew Operand::OpReg(Register::Eax);
        static initonly Operand::OpReg^ Ecx = gcnew Operand::OpReg(Register::Ecx);
        static initonly Operand::OpReg^ Edx = gcnew Operand::OpReg(Register::Edx);
        static initonly Operand::OpReg^ Ebx = gcnew Operand::OpReg(Register::Ebx);
        static initonly Operand::OpReg^ Esp = gcnew Operand::OpReg(Register::Esp);
        static initonly Operand::OpReg^ Ebp = gcnew Operand::OpReg(Register::Ebp);
        static initonly Operand::OpReg^ Esi = gcnew Operand::OpReg(Register::Esi);
        static initonly Operand::OpReg^ Edi = gcnew Operand::OpReg(Register::Edi);
        static initonly Operand::OpReg^ R8d = gcnew Operand::OpReg(Register::R8d);
        static initonly Operand::OpReg^ R9d = gcnew Operand::OpReg(Register::R9d);
        static initonly Operand::OpReg^ R10d = gcnew Operand::OpReg(Register::R10d);
        static initonly Operand::OpReg^ R11d = gcnew Operand::OpReg(Register::R11d);
        static initonly Operand::OpReg^ R12d = gcnew Operand::OpReg(Register::R12d);
        static initonly Operand::OpReg^ R13d = gcnew Operand::OpReg(Register::R13d);
        static initonly Operand::OpReg^ R14d = gcnew Operand::OpReg(Register::R14d);
        static initonly Operand::OpReg^ R15d = gcnew Operand::OpReg(Register::R15d);
#if _M_X64
        // General purpose registers 64-bit
        static initonly Operand::OpReg^ Rax = gcnew Operand::OpReg(Register::Rax);
        static initonly Operand::OpReg^ Rcx = gcnew Operand::OpReg(Register::Rcx);
        static initonly Operand::OpReg^ Rdx = gcnew Operand::OpReg(Register::Rdx);
        static initonly Operand::OpReg^ Rbx = gcnew Operand::OpReg(Register::Rbx);
        static initonly Operand::OpReg^ Rsp = gcnew Operand::OpReg(Register::Rsp);
        static initonly Operand::OpReg^ Rbp = gcnew Operand::OpReg(Register::Rbp);
        static initonly Operand::OpReg^ Rsi = gcnew Operand::OpReg(Register::Rsi);
        static initonly Operand::OpReg^ Rdi = gcnew Operand::OpReg(Register::Rdi);
        static initonly Operand::OpReg^ R8 = gcnew Operand::OpReg(Register::R8);
        static initonly Operand::OpReg^ R9 = gcnew Operand::OpReg(Register::R9);
        static initonly Operand::OpReg^ R10 = gcnew Operand::OpReg(Register::R10);
        static initonly Operand::OpReg^ R11 = gcnew Operand::OpReg(Register::R11);
        static initonly Operand::OpReg^ R12 = gcnew Operand::OpReg(Register::R12);
        static initonly Operand::OpReg^ R13 = gcnew Operand::OpReg(Register::R13);
        static initonly Operand::OpReg^ R14 = gcnew Operand::OpReg(Register::R14);
        static initonly Operand::OpReg^ R15 = gcnew Operand::OpReg(Register::R15);
#endif
        // Floating point legacy registers
        static initonly Operand::OpReg^ St0 = gcnew Operand::OpReg(Register::St0);
        static initonly Operand::OpReg^ St1 = gcnew Operand::OpReg(Register::St1);
        static initonly Operand::OpReg^ St2 = gcnew Operand::OpReg(Register::St2);
        static initonly Operand::OpReg^ St3 = gcnew Operand::OpReg(Register::St3);
        static initonly Operand::OpReg^ St4 = gcnew Operand::OpReg(Register::St4);
        static initonly Operand::OpReg^ St5 = gcnew Operand::OpReg(Register::St5);
        static initonly Operand::OpReg^ St6 = gcnew Operand::OpReg(Register::St6);
        static initonly Operand::OpReg^ St7 = gcnew Operand::OpReg(Register::St7);
        static initonly Operand::OpReg^ X87Control = gcnew Operand::OpReg(Register::X87Control);
        static initonly Operand::OpReg^ X87Status = gcnew Operand::OpReg(Register::X87Status);
        static initonly Operand::OpReg^ X87Tag = gcnew Operand::OpReg(Register::X87Tag);
        // Floating point multimedia registers
        static initonly Operand::OpReg^ Mm0 = gcnew Operand::OpReg(Register::Mm0);
        static initonly Operand::OpReg^ Mm1 = gcnew Operand::OpReg(Register::Mm1);
        static initonly Operand::OpReg^ Mm2 = gcnew Operand::OpReg(Register::Mm2);
        static initonly Operand::OpReg^ Mm3 = gcnew Operand::OpReg(Register::Mm3);
        static initonly Operand::OpReg^ Mm4 = gcnew Operand::OpReg(Register::Mm4);
        static initonly Operand::OpReg^ Mm5 = gcnew Operand::OpReg(Register::Mm5);
        static initonly Operand::OpReg^ Mm6 = gcnew Operand::OpReg(Register::Mm6);
        static initonly Operand::OpReg^ Mm7 = gcnew Operand::OpReg(Register::Mm7);
        // Floating point vector registers 128-bit
        static initonly Operand::OpReg^ Xmm0 = gcnew Operand::OpReg(Register::Xmm0);
        static initonly Operand::OpReg^ Xmm1 = gcnew Operand::OpReg(Register::Xmm1);
        static initonly Operand::OpReg^ Xmm2 = gcnew Operand::OpReg(Register::Xmm2);
        static initonly Operand::OpReg^ Xmm3 = gcnew Operand::OpReg(Register::Xmm3);
        static initonly Operand::OpReg^ Xmm4 = gcnew Operand::OpReg(Register::Xmm4);
        static initonly Operand::OpReg^ Xmm5 = gcnew Operand::OpReg(Register::Xmm5);
        static initonly Operand::OpReg^ Xmm6 = gcnew Operand::OpReg(Register::Xmm6);
        static initonly Operand::OpReg^ Xmm7 = gcnew Operand::OpReg(Register::Xmm7);
        static initonly Operand::OpReg^ Xmm8 = gcnew Operand::OpReg(Register::Xmm8);
        static initonly Operand::OpReg^ Xmm9 = gcnew Operand::OpReg(Register::Xmm9);
        static initonly Operand::OpReg^ Xmm10 = gcnew Operand::OpReg(Register::Xmm10);
        static initonly Operand::OpReg^ Xmm11 = gcnew Operand::OpReg(Register::Xmm11);
        static initonly Operand::OpReg^ Xmm12 = gcnew Operand::OpReg(Register::Xmm12);
        static initonly Operand::OpReg^ Xmm13 = gcnew Operand::OpReg(Register::Xmm13);
        static initonly Operand::OpReg^ Xmm14 = gcnew Operand::OpReg(Register::Xmm14);
        static initonly Operand::OpReg^ Xmm15 = gcnew Operand::OpReg(Register::Xmm15);
        static initonly Operand::OpReg^ Xmm16 = gcnew Operand::OpReg(Register::Xmm16);
        static initonly Operand::OpReg^ Xmm17 = gcnew Operand::OpReg(Register::Xmm17);
        static initonly Operand::OpReg^ Xmm18 = gcnew Operand::OpReg(Register::Xmm18);
        static initonly Operand::OpReg^ Xmm19 = gcnew Operand::OpReg(Register::Xmm19);
        static initonly Operand::OpReg^ Xmm20 = gcnew Operand::OpReg(Register::Xmm20);
        static initonly Operand::OpReg^ Xmm21 = gcnew Operand::OpReg(Register::Xmm21);
        static initonly Operand::OpReg^ Xmm22 = gcnew Operand::OpReg(Register::Xmm22);
        static initonly Operand::OpReg^ Xmm23 = gcnew Operand::OpReg(Register::Xmm23);
        static initonly Operand::OpReg^ Xmm24 = gcnew Operand::OpReg(Register::Xmm24);
        static initonly Operand::OpReg^ Xmm25 = gcnew Operand::OpReg(Register::Xmm25);
        static initonly Operand::OpReg^ Xmm26 = gcnew Operand::OpReg(Register::Xmm26);
        static initonly Operand::OpReg^ Xmm27 = gcnew Operand::OpReg(Register::Xmm27);
        static initonly Operand::OpReg^ Xmm28 = gcnew Operand::OpReg(Register::Xmm28);
        static initonly Operand::OpReg^ Xmm29 = gcnew Operand::OpReg(Register::Xmm29);
        static initonly Operand::OpReg^ Xmm30 = gcnew Operand::OpReg(Register::Xmm30);
        static initonly Operand::OpReg^ Xmm31 = gcnew Operand::OpReg(Register::Xmm31);
        // Floating point vector registers 256-bit
        static initonly Operand::OpReg^ Ymm0 = gcnew Operand::OpReg(Register::Ymm0);
        static initonly Operand::OpReg^ Ymm1 = gcnew Operand::OpReg(Register::Ymm1);
        static initonly Operand::OpReg^ Ymm2 = gcnew Operand::OpReg(Register::Ymm2);
        static initonly Operand::OpReg^ Ymm3 = gcnew Operand::OpReg(Register::Ymm3);
        static initonly Operand::OpReg^ Ymm4 = gcnew Operand::OpReg(Register::Ymm4);
        static initonly Operand::OpReg^ Ymm5 = gcnew Operand::OpReg(Register::Ymm5);
        static initonly Operand::OpReg^ Ymm6 = gcnew Operand::OpReg(Register::Ymm6);
        static initonly Operand::OpReg^ Ymm7 = gcnew Operand::OpReg(Register::Ymm7);
        static initonly Operand::OpReg^ Ymm8 = gcnew Operand::OpReg(Register::Ymm8);
        static initonly Operand::OpReg^ Ymm9 = gcnew Operand::OpReg(Register::Ymm9);
        static initonly Operand::OpReg^ Ymm10 = gcnew Operand::OpReg(Register::Ymm10);
        static initonly Operand::OpReg^ Ymm11 = gcnew Operand::OpReg(Register::Ymm11);
        static initonly Operand::OpReg^ Ymm12 = gcnew Operand::OpReg(Register::Ymm12);
        static initonly Operand::OpReg^ Ymm13 = gcnew Operand::OpReg(Register::Ymm13);
        static initonly Operand::OpReg^ Ymm14 = gcnew Operand::OpReg(Register::Ymm14);
        static initonly Operand::OpReg^ Ymm15 = gcnew Operand::OpReg(Register::Ymm15);
        static initonly Operand::OpReg^ Ymm16 = gcnew Operand::OpReg(Register::Ymm16);
        static initonly Operand::OpReg^ Ymm17 = gcnew Operand::OpReg(Register::Ymm17);
        static initonly Operand::OpReg^ Ymm18 = gcnew Operand::OpReg(Register::Ymm18);
        static initonly Operand::OpReg^ Ymm19 = gcnew Operand::OpReg(Register::Ymm19);
        static initonly Operand::OpReg^ Ymm20 = gcnew Operand::OpReg(Register::Ymm20);
        static initonly Operand::OpReg^ Ymm21 = gcnew Operand::OpReg(Register::Ymm21);
        static initonly Operand::OpReg^ Ymm22 = gcnew Operand::OpReg(Register::Ymm22);
        static initonly Operand::OpReg^ Ymm23 = gcnew Operand::OpReg(Register::Ymm23);
        static initonly Operand::OpReg^ Ymm24 = gcnew Operand::OpReg(Register::Ymm24);
        static initonly Operand::OpReg^ Ymm25 = gcnew Operand::OpReg(Register::Ymm25);
        static initonly Operand::OpReg^ Ymm26 = gcnew Operand::OpReg(Register::Ymm26);
        static initonly Operand::OpReg^ Ymm27 = gcnew Operand::OpReg(Register::Ymm27);
        static initonly Operand::OpReg^ Ymm28 = gcnew Operand::OpReg(Register::Ymm28);
        static initonly Operand::OpReg^ Ymm29 = gcnew Operand::OpReg(Register::Ymm29);
        static initonly Operand::OpReg^ Ymm30 = gcnew Operand::OpReg(Register::Ymm30);
        static initonly Operand::OpReg^ Ymm31 = gcnew Operand::OpReg(Register::Ymm31);
        // Floating point vector registers 512-bit
        static initonly Operand::OpReg^ Zmm0 = gcnew Operand::OpReg(Register::Zmm0);
        static initonly Operand::OpReg^ Zmm1 = gcnew Operand::OpReg(Register::Zmm1);
        static initonly Operand::OpReg^ Zmm2 = gcnew Operand::OpReg(Register::Zmm2);
        static initonly Operand::OpReg^ Zmm3 = gcnew Operand::OpReg(Register::Zmm3);
        static initonly Operand::OpReg^ Zmm4 = gcnew Operand::OpReg(Register::Zmm4);
        static initonly Operand::OpReg^ Zmm5 = gcnew Operand::OpReg(Register::Zmm5);
        static initonly Operand::OpReg^ Zmm6 = gcnew Operand::OpReg(Register::Zmm6);
        static initonly Operand::OpReg^ Zmm7 = gcnew Operand::OpReg(Register::Zmm7);
        static initonly Operand::OpReg^ Zmm8 = gcnew Operand::OpReg(Register::Zmm8);
        static initonly Operand::OpReg^ Zmm9 = gcnew Operand::OpReg(Register::Zmm9);
        static initonly Operand::OpReg^ Zmm10 = gcnew Operand::OpReg(Register::Zmm10);
        static initonly Operand::OpReg^ Zmm11 = gcnew Operand::OpReg(Register::Zmm11);
        static initonly Operand::OpReg^ Zmm12 = gcnew Operand::OpReg(Register::Zmm12);
        static initonly Operand::OpReg^ Zmm13 = gcnew Operand::OpReg(Register::Zmm13);
        static initonly Operand::OpReg^ Zmm14 = gcnew Operand::OpReg(Register::Zmm14);
        static initonly Operand::OpReg^ Zmm15 = gcnew Operand::OpReg(Register::Zmm15);
        static initonly Operand::OpReg^ Zmm16 = gcnew Operand::OpReg(Register::Zmm16);
        static initonly Operand::OpReg^ Zmm17 = gcnew Operand::OpReg(Register::Zmm17);
        static initonly Operand::OpReg^ Zmm18 = gcnew Operand::OpReg(Register::Zmm18);
        static initonly Operand::OpReg^ Zmm19 = gcnew Operand::OpReg(Register::Zmm19);
        static initonly Operand::OpReg^ Zmm20 = gcnew Operand::OpReg(Register::Zmm20);
        static initonly Operand::OpReg^ Zmm21 = gcnew Operand::OpReg(Register::Zmm21);
        static initonly Operand::OpReg^ Zmm22 = gcnew Operand::OpReg(Register::Zmm22);
        static initonly Operand::OpReg^ Zmm23 = gcnew Operand::OpReg(Register::Zmm23);
        static initonly Operand::OpReg^ Zmm24 = gcnew Operand::OpReg(Register::Zmm24);
        static initonly Operand::OpReg^ Zmm25 = gcnew Operand::OpReg(Register::Zmm25);
        static initonly Operand::OpReg^ Zmm26 = gcnew Operand::OpReg(Register::Zmm26);
        static initonly Operand::OpReg^ Zmm27 = gcnew Operand::OpReg(Register::Zmm27);
        static initonly Operand::OpReg^ Zmm28 = gcnew Operand::OpReg(Register::Zmm28);
        static initonly Operand::OpReg^ Zmm29 = gcnew Operand::OpReg(Register::Zmm29);
        static initonly Operand::OpReg^ Zmm30 = gcnew Operand::OpReg(Register::Zmm30);
        static initonly Operand::OpReg^ Zmm31 = gcnew Operand::OpReg(Register::Zmm31);
        // Flags registers
        static initonly Operand::OpReg^ Flags = gcnew Operand::OpReg(Register::Flags);
        static initonly Operand::OpReg^ EFlags = gcnew Operand::OpReg(Register::EFlags);
        static initonly Operand::OpReg^ RFlags = gcnew Operand::OpReg(Register::RFlags);
        // Instruction-pointer registers
        static initonly Operand::OpReg^ Ip = gcnew Operand::OpReg(Register::Ip);
        static initonly Operand::OpReg^ Eip = gcnew Operand::OpReg(Register::Eip);
        static initonly Operand::OpReg^ Rip = gcnew Operand::OpReg(Register::Rip);
        // Segment registers
        static initonly Operand::OpReg^ Es = gcnew Operand::OpReg(Register::Es);
        static initonly Operand::OpReg^ Cs = gcnew Operand::OpReg(Register::Cs);
        static initonly Operand::OpReg^ Ss = gcnew Operand::OpReg(Register::Ss);
        static initonly Operand::OpReg^ Ds = gcnew Operand::OpReg(Register::Ds);
        static initonly Operand::OpReg^ Fs = gcnew Operand::OpReg(Register::Fs);
        static initonly Operand::OpReg^ Gs = gcnew Operand::OpReg(Register::Gs);
        // Table registers
        static initonly Operand::OpReg^ Gdtr = gcnew Operand::OpReg(Register::Gdtr);
        static initonly Operand::OpReg^ Ldtr = gcnew Operand::OpReg(Register::Ldtr);
        static initonly Operand::OpReg^ Idtr = gcnew Operand::OpReg(Register::Idtr);
        static initonly Operand::OpReg^ Tr = gcnew Operand::OpReg(Register::Tr);
        // Test registers
        static initonly Operand::OpReg^ Tr0 = gcnew Operand::OpReg(Register::Tr0);
        static initonly Operand::OpReg^ Tr1 = gcnew Operand::OpReg(Register::Tr1);
        static initonly Operand::OpReg^ Tr2 = gcnew Operand::OpReg(Register::Tr2);
        static initonly Operand::OpReg^ Tr3 = gcnew Operand::OpReg(Register::Tr3);
        static initonly Operand::OpReg^ Tr4 = gcnew Operand::OpReg(Register::Tr4);
        static initonly Operand::OpReg^ Tr5 = gcnew Operand::OpReg(Register::Tr5);
        static initonly Operand::OpReg^ Tr6 = gcnew Operand::OpReg(Register::Tr6);
        static initonly Operand::OpReg^ Tr7 = gcnew Operand::OpReg(Register::Tr7);
        // Control registers
        static initonly Operand::OpReg^ Cr0 = gcnew Operand::OpReg(Register::Cr0);
        static initonly Operand::OpReg^ Cr1 = gcnew Operand::OpReg(Register::Cr1);
        static initonly Operand::OpReg^ Cr2 = gcnew Operand::OpReg(Register::Cr2);
        static initonly Operand::OpReg^ Cr3 = gcnew Operand::OpReg(Register::Cr3);
        static initonly Operand::OpReg^ Cr4 = gcnew Operand::OpReg(Register::Cr4);
        static initonly Operand::OpReg^ Cr5 = gcnew Operand::OpReg(Register::Cr5);
        static initonly Operand::OpReg^ Cr6 = gcnew Operand::OpReg(Register::Cr6);
        static initonly Operand::OpReg^ Cr7 = gcnew Operand::OpReg(Register::Cr7);
        static initonly Operand::OpReg^ Cr8 = gcnew Operand::OpReg(Register::Cr8);
        static initonly Operand::OpReg^ Cr9 = gcnew Operand::OpReg(Register::Cr9);
        static initonly Operand::OpReg^ Cr10 = gcnew Operand::OpReg(Register::Cr10);
        static initonly Operand::OpReg^ Cr11 = gcnew Operand::OpReg(Register::Cr11);
        static initonly Operand::OpReg^ Cr12 = gcnew Operand::OpReg(Register::Cr12);
        static initonly Operand::OpReg^ Cr13 = gcnew Operand::OpReg(Register::Cr13);
        static initonly Operand::OpReg^ Cr14 = gcnew Operand::OpReg(Register::Cr14);
        static initonly Operand::OpReg^ Cr15 = gcnew Operand::OpReg(Register::Cr15);
        // Debug registers
        static initonly Operand::OpReg^ Dr0 = gcnew Operand::OpReg(Register::Dr0);
        static initonly Operand::OpReg^ Dr1 = gcnew Operand::OpReg(Register::Dr1);
        static initonly Operand::OpReg^ Dr2 = gcnew Operand::OpReg(Register::Dr2);
        static initonly Operand::OpReg^ Dr3 = gcnew Operand::OpReg(Register::Dr3);
        static initonly Operand::OpReg^ Dr4 = gcnew Operand::OpReg(Register::Dr4);
        static initonly Operand::OpReg^ Dr5 = gcnew Operand::OpReg(Register::Dr5);
        static initonly Operand::OpReg^ Dr6 = gcnew Operand::OpReg(Register::Dr6);
        static initonly Operand::OpReg^ Dr7 = gcnew Operand::OpReg(Register::Dr7);
        static initonly Operand::OpReg^ Dr8 = gcnew Operand::OpReg(Register::Dr8);
        static initonly Operand::OpReg^ Dr9 = gcnew Operand::OpReg(Register::Dr9);
        static initonly Operand::OpReg^ Dr10 = gcnew Operand::OpReg(Register::Dr10);
        static initonly Operand::OpReg^ Dr11 = gcnew Operand::OpReg(Register::Dr11);
        static initonly Operand::OpReg^ Dr12 = gcnew Operand::OpReg(Register::Dr12);
        static initonly Operand::OpReg^ Dr13 = gcnew Operand::OpReg(Register::Dr13);
        static initonly Operand::OpReg^ Dr14 = gcnew Operand::OpReg(Register::Dr14);
        static initonly Operand::OpReg^ Dr15 = gcnew Operand::OpReg(Register::Dr15);
        // Mask registers
        static initonly Operand::OpReg^ K0 = gcnew Operand::OpReg(Register::K0);
        static initonly Operand::OpReg^ K1 = gcnew Operand::OpReg(Register::K1);
        static initonly Operand::OpReg^ K2 = gcnew Operand::OpReg(Register::K2);
        static initonly Operand::OpReg^ K3 = gcnew Operand::OpReg(Register::K3);
        static initonly Operand::OpReg^ K4 = gcnew Operand::OpReg(Register::K4);
        static initonly Operand::OpReg^ K5 = gcnew Operand::OpReg(Register::K5);
        static initonly Operand::OpReg^ K6 = gcnew Operand::OpReg(Register::K6);
        static initonly Operand::OpReg^ K7 = gcnew Operand::OpReg(Register::K7);
        // Bound registers
        static initonly Operand::OpReg^ Bnd0 = gcnew Operand::OpReg(Register::Bnd0);
        static initonly Operand::OpReg^ Bnd1 = gcnew Operand::OpReg(Register::Bnd1);
        static initonly Operand::OpReg^ Bnd2 = gcnew Operand::OpReg(Register::Bnd2);
        static initonly Operand::OpReg^ Bnd3 = gcnew Operand::OpReg(Register::Bnd3);
        static initonly Operand::OpReg^ BndCfg = gcnew Operand::OpReg(Register::BndCfg);
        static initonly Operand::OpReg^ BndStatus = gcnew Operand::OpReg(Register::BndStatus);
        // Uncategorized
        static initonly Operand::OpReg^ Mxcsr = gcnew Operand::OpReg(Register::Mxcsr);
        static initonly Operand::OpReg^ Pkru = gcnew Operand::OpReg(Register::Pkru);
        static initonly Operand::OpReg^ Xcr0 = gcnew Operand::OpReg(Register::Xcr0);

        static Operand::OpReg^ Reg(Register reg)
        {
            return gcnew Operand::OpReg(reg);
        }

    public:
        static Operand::OpImm^ Imm(Int64 val)
        {
            return gcnew Operand::OpImm(val);
        }
    };

}
