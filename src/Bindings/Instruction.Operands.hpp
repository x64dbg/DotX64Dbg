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
        static Operand::Memory^ BytePtr(Int64 disp)
        {
            return gcnew Operand::Memory(8, Registers::Id::None, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ BytePtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(8, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ BytePtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(8, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ BytePtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(8, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ BytePtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(8, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ BytePtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(8, baseReg, index, 0, 0);
        }
        static Operand::Memory^ BytePtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(8, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ BytePtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(8, baseReg, index, 0, disp);
        }
        static Operand::Memory^ BytePtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(8, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ BytePtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(8, baseReg, index, scale, disp);
        }
        static Operand::Memory^ BytePtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(8, baseReg->Value, index->Value, scale, disp);
        }

        // Word
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ WordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(16, Registers::Id::None, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ WordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(16, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ WordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(16, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ WordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(16, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ WordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(16, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ WordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(16, baseReg, index, 0, 0);
        }
        static Operand::Memory^ WordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(16, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ WordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(16, baseReg, index, 0, disp);
        }
        static Operand::Memory^ WordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(16, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ WordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(16, baseReg, index, scale, disp);
        }
        static Operand::Memory^ WordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(16, baseReg->Value, index->Value, scale, disp);
        }

        // Dword
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ DwordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(32, Registers::Id::None, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ DwordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(32, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ DwordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(32, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ DwordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(32, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ DwordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(32, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ DwordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(32, baseReg, index, 0, 0);
        }
        static Operand::Memory^ DwordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(32, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ DwordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(32, baseReg, index, 0, disp);
        }
        static Operand::Memory^ DwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(32, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ DwordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(32, baseReg, index, scale, disp);
        }
        static Operand::Memory^ DwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(32, baseReg->Value, index->Value, scale, disp);
        }

        // Qword
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ QwordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(64, Registers::Id::None, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ QwordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(64, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ QwordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(64, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ QwordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(64, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ QwordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(64, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ QwordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(64, baseReg, index, 0, 0);
        }
        static Operand::Memory^ QwordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(64, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ QwordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(64, baseReg, index, 0, disp);
        }
        static Operand::Memory^ QwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(64, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ QwordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(64, baseReg, index, scale, disp);
        }
        static Operand::Memory^ QwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(64, baseReg->Value, index->Value, scale, disp);
        }

        // Tword
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ TwordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(80, Registers::Id::None, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ TwordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(80, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ TwordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(80, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ TwordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(80, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ TwordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(80, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ TwordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(80, baseReg, index, 0, 0);
        }
        static Operand::Memory^ TwordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(80, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ TwordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(80, baseReg, index, 0, disp);
        }
        static Operand::Memory^ TwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(80, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ TwordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(80, baseReg, index, scale, disp);
        }
        static Operand::Memory^ TwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(80, baseReg->Value, index->Value, scale, disp);
        }

        // Xmmword
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ XmmwordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(128, Registers::Id::None, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ XmmwordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(128, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ XmmwordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(128, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ XmmwordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(128, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ XmmwordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(128, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ XmmwordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(128, baseReg, index, 0, 0);
        }
        static Operand::Memory^ XmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(128, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ XmmwordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(128, baseReg, index, 0, disp);
        }
        static Operand::Memory^ XmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(128, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ XmmwordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(128, baseReg, index, scale, disp);
        }
        static Operand::Memory^ XmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(128, baseReg->Value, index->Value, scale, disp);
        }

        // Ymmword
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ YmmwordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(256, Registers::Id::None, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ YmmwordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(256, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ YmmwordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(256, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ YmmwordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(256, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ YmmwordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(256, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ YmmwordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(256, baseReg, index, 0, 0);
        }
        static Operand::Memory^ YmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(256, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ YmmwordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(256, baseReg, index, 0, disp);
        }
        static Operand::Memory^ YmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(256, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ YmmwordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(256, baseReg, index, scale, disp);
        }
        static Operand::Memory^ YmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(256, baseReg->Value, index->Value, scale, disp);
        }

        // Zmmword
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ ZmmwordPtr(Int64 disp)
        {
            return gcnew Operand::Memory(512, Registers::Id::None, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ ZmmwordPtr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(512, baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ ZmmwordPtr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(512, baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ ZmmwordPtr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(512, baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ ZmmwordPtr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(512, baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ ZmmwordPtr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(512, baseReg, index, 0, 0);
        }
        static Operand::Memory^ ZmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(512, baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ ZmmwordPtr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(512, baseReg, index, 0, disp);
        }
        static Operand::Memory^ ZmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(512, baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ ZmmwordPtr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(512, baseReg, index, scale, disp);
        }
        static Operand::Memory^ ZmmwordPtr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(512, baseReg->Value, index->Value, scale, disp);
        }

        // Host
        //////////////////////////////////////////////////////////////////////////
        static Operand::Memory^ Ptr(Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), Registers::Id::None, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ Ptr(Registers::Id baseReg)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg, Registers::Id::None, 0, 0);
        }
        static Operand::Memory^ Ptr(Operand::Register^ baseReg)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg->Value, Registers::Id::None, 0, 0);
        }

        static Operand::Memory^ Ptr(Registers::Id baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg, Registers::Id::None, 0, disp);
        }
        static Operand::Memory^ Ptr(Operand::Register^ baseReg, Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg->Value, Registers::Id::None, 0, disp);
        }

        static Operand::Memory^ Ptr(Registers::Id baseReg, Registers::Id index)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg, index, 0, 0);
        }
        static Operand::Memory^ Ptr(Operand::Register^ baseReg, Operand::Register^ index)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg->Value, index->Value, 0, 0);
        }

        static Operand::Memory^ Ptr(Registers::Id baseReg, Registers::Id index, Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg, index, 0, disp);
        }
        static Operand::Memory^ Ptr(Operand::Register^ baseReg, Operand::Register^ index, Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg->Value, index->Value, 0, disp);
        }

        static Operand::Memory^ Ptr(Registers::Id baseReg, Registers::Id index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg, index, scale, disp);
        }
        static Operand::Memory^ Ptr(Operand::Register^ baseReg, Operand::Register^ index, Int32 scale, Int64 disp)
        {
            return gcnew Operand::Memory(AddressSize(), baseReg->Value, index->Value, scale, disp);
        }

    public:
        // General purpose registers  8-bit
        static initonly Operand::Register^ Al = gcnew Operand::Register(Registers::Id::Al);
        static initonly Operand::Register^ Cl = gcnew Operand::Register(Registers::Id::Cl);
        static initonly Operand::Register^ Dl = gcnew Operand::Register(Registers::Id::Dl);
        static initonly Operand::Register^ Bl = gcnew Operand::Register(Registers::Id::Bl);
        static initonly Operand::Register^ Ah = gcnew Operand::Register(Registers::Id::Ah);
        static initonly Operand::Register^ Ch = gcnew Operand::Register(Registers::Id::Ch);
        static initonly Operand::Register^ Dh = gcnew Operand::Register(Registers::Id::Dh);
        static initonly Operand::Register^ Bh = gcnew Operand::Register(Registers::Id::Bh);
        static initonly Operand::Register^ Spl = gcnew Operand::Register(Registers::Id::Spl);
        static initonly Operand::Register^ Bpl = gcnew Operand::Register(Registers::Id::Bpl);
        static initonly Operand::Register^ Sil = gcnew Operand::Register(Registers::Id::Sil);
        static initonly Operand::Register^ Dil = gcnew Operand::Register(Registers::Id::Dil);
#if _M_X64
        static initonly Operand::Register^ R8b = gcnew Operand::Register(Registers::Id::R8b);
        static initonly Operand::Register^ R9b = gcnew Operand::Register(Registers::Id::R9b);
        static initonly Operand::Register^ R10b = gcnew Operand::Register(Registers::Id::R10b);
        static initonly Operand::Register^ R11b = gcnew Operand::Register(Registers::Id::R11b);
        static initonly Operand::Register^ R12b = gcnew Operand::Register(Registers::Id::R12b);
        static initonly Operand::Register^ R13b = gcnew Operand::Register(Registers::Id::R13b);
        static initonly Operand::Register^ R14b = gcnew Operand::Register(Registers::Id::R14b);
        static initonly Operand::Register^ R15b = gcnew Operand::Register(Registers::Id::R15b);
#endif
        // General purpose registers 16-bit
        static initonly Operand::Register^ Ax = gcnew Operand::Register(Registers::Id::Ax);
        static initonly Operand::Register^ Cx = gcnew Operand::Register(Registers::Id::Cx);
        static initonly Operand::Register^ Dx = gcnew Operand::Register(Registers::Id::Dx);
        static initonly Operand::Register^ Bx = gcnew Operand::Register(Registers::Id::Bx);
        static initonly Operand::Register^ Sp = gcnew Operand::Register(Registers::Id::Sp);
        static initonly Operand::Register^ Bp = gcnew Operand::Register(Registers::Id::Bp);
        static initonly Operand::Register^ Si = gcnew Operand::Register(Registers::Id::Si);
        static initonly Operand::Register^ Di = gcnew Operand::Register(Registers::Id::Di);
#if _M_X64
        static initonly Operand::Register^ R8w = gcnew Operand::Register(Registers::Id::R8w);
        static initonly Operand::Register^ R9w = gcnew Operand::Register(Registers::Id::R9w);
        static initonly Operand::Register^ R10w = gcnew Operand::Register(Registers::Id::R10w);
        static initonly Operand::Register^ R11w = gcnew Operand::Register(Registers::Id::R11w);
        static initonly Operand::Register^ R12w = gcnew Operand::Register(Registers::Id::R12w);
        static initonly Operand::Register^ R13w = gcnew Operand::Register(Registers::Id::R13w);
        static initonly Operand::Register^ R14w = gcnew Operand::Register(Registers::Id::R14w);
        static initonly Operand::Register^ R15w = gcnew Operand::Register(Registers::Id::R15w);
#endif
        // General purpose registers 32-bit
        static initonly Operand::Register^ Eax = gcnew Operand::Register(Registers::Id::Eax);
        static initonly Operand::Register^ Ecx = gcnew Operand::Register(Registers::Id::Ecx);
        static initonly Operand::Register^ Edx = gcnew Operand::Register(Registers::Id::Edx);
        static initonly Operand::Register^ Ebx = gcnew Operand::Register(Registers::Id::Ebx);
        static initonly Operand::Register^ Esp = gcnew Operand::Register(Registers::Id::Esp);
        static initonly Operand::Register^ Ebp = gcnew Operand::Register(Registers::Id::Ebp);
        static initonly Operand::Register^ Esi = gcnew Operand::Register(Registers::Id::Esi);
        static initonly Operand::Register^ Edi = gcnew Operand::Register(Registers::Id::Edi);
        static initonly Operand::Register^ R8d = gcnew Operand::Register(Registers::Id::R8d);
        static initonly Operand::Register^ R9d = gcnew Operand::Register(Registers::Id::R9d);
        static initonly Operand::Register^ R10d = gcnew Operand::Register(Registers::Id::R10d);
        static initonly Operand::Register^ R11d = gcnew Operand::Register(Registers::Id::R11d);
        static initonly Operand::Register^ R12d = gcnew Operand::Register(Registers::Id::R12d);
        static initonly Operand::Register^ R13d = gcnew Operand::Register(Registers::Id::R13d);
        static initonly Operand::Register^ R14d = gcnew Operand::Register(Registers::Id::R14d);
        static initonly Operand::Register^ R15d = gcnew Operand::Register(Registers::Id::R15d);

#if _M_X64
        // General purpose registers 64-bit
        static initonly Operand::Register^ Rax = gcnew Operand::Register(Registers::Id::Rax);
        static initonly Operand::Register^ Rcx = gcnew Operand::Register(Registers::Id::Rcx);
        static initonly Operand::Register^ Rdx = gcnew Operand::Register(Registers::Id::Rdx);
        static initonly Operand::Register^ Rbx = gcnew Operand::Register(Registers::Id::Rbx);
        static initonly Operand::Register^ Rsp = gcnew Operand::Register(Registers::Id::Rsp);
        static initonly Operand::Register^ Rbp = gcnew Operand::Register(Registers::Id::Rbp);
        static initonly Operand::Register^ Rsi = gcnew Operand::Register(Registers::Id::Rsi);
        static initonly Operand::Register^ Rdi = gcnew Operand::Register(Registers::Id::Rdi);
        static initonly Operand::Register^ R8 = gcnew Operand::Register(Registers::Id::R8);
        static initonly Operand::Register^ R9 = gcnew Operand::Register(Registers::Id::R9);
        static initonly Operand::Register^ R10 = gcnew Operand::Register(Registers::Id::R10);
        static initonly Operand::Register^ R11 = gcnew Operand::Register(Registers::Id::R11);
        static initonly Operand::Register^ R12 = gcnew Operand::Register(Registers::Id::R12);
        static initonly Operand::Register^ R13 = gcnew Operand::Register(Registers::Id::R13);
        static initonly Operand::Register^ R14 = gcnew Operand::Register(Registers::Id::R14);
        static initonly Operand::Register^ R15 = gcnew Operand::Register(Registers::Id::R15);
#endif
        // Floating point legacy registers
        static initonly Operand::Register^ St0 = gcnew Operand::Register(Registers::Id::St0);
        static initonly Operand::Register^ St1 = gcnew Operand::Register(Registers::Id::St1);
        static initonly Operand::Register^ St2 = gcnew Operand::Register(Registers::Id::St2);
        static initonly Operand::Register^ St3 = gcnew Operand::Register(Registers::Id::St3);
        static initonly Operand::Register^ St4 = gcnew Operand::Register(Registers::Id::St4);
        static initonly Operand::Register^ St5 = gcnew Operand::Register(Registers::Id::St5);
        static initonly Operand::Register^ St6 = gcnew Operand::Register(Registers::Id::St6);
        static initonly Operand::Register^ St7 = gcnew Operand::Register(Registers::Id::St7);
        static initonly Operand::Register^ X87Control = gcnew Operand::Register(Registers::Id::X87Control);
        static initonly Operand::Register^ X87Status = gcnew Operand::Register(Registers::Id::X87Status);
        static initonly Operand::Register^ X87Tag = gcnew Operand::Register(Registers::Id::X87Tag);
        // Floating point multimedia registers
        static initonly Operand::Register^ Mm0 = gcnew Operand::Register(Registers::Id::Mm0);
        static initonly Operand::Register^ Mm1 = gcnew Operand::Register(Registers::Id::Mm1);
        static initonly Operand::Register^ Mm2 = gcnew Operand::Register(Registers::Id::Mm2);
        static initonly Operand::Register^ Mm3 = gcnew Operand::Register(Registers::Id::Mm3);
        static initonly Operand::Register^ Mm4 = gcnew Operand::Register(Registers::Id::Mm4);
        static initonly Operand::Register^ Mm5 = gcnew Operand::Register(Registers::Id::Mm5);
        static initonly Operand::Register^ Mm6 = gcnew Operand::Register(Registers::Id::Mm6);
        static initonly Operand::Register^ Mm7 = gcnew Operand::Register(Registers::Id::Mm7);
        // Floating point vector registers 128-bit
        static initonly Operand::Register^ Xmm0 = gcnew Operand::Register(Registers::Id::Xmm0);
        static initonly Operand::Register^ Xmm1 = gcnew Operand::Register(Registers::Id::Xmm1);
        static initonly Operand::Register^ Xmm2 = gcnew Operand::Register(Registers::Id::Xmm2);
        static initonly Operand::Register^ Xmm3 = gcnew Operand::Register(Registers::Id::Xmm3);
        static initonly Operand::Register^ Xmm4 = gcnew Operand::Register(Registers::Id::Xmm4);
        static initonly Operand::Register^ Xmm5 = gcnew Operand::Register(Registers::Id::Xmm5);
        static initonly Operand::Register^ Xmm6 = gcnew Operand::Register(Registers::Id::Xmm6);
        static initonly Operand::Register^ Xmm7 = gcnew Operand::Register(Registers::Id::Xmm7);
        static initonly Operand::Register^ Xmm8 = gcnew Operand::Register(Registers::Id::Xmm8);
        static initonly Operand::Register^ Xmm9 = gcnew Operand::Register(Registers::Id::Xmm9);
        static initonly Operand::Register^ Xmm10 = gcnew Operand::Register(Registers::Id::Xmm10);
        static initonly Operand::Register^ Xmm11 = gcnew Operand::Register(Registers::Id::Xmm11);
        static initonly Operand::Register^ Xmm12 = gcnew Operand::Register(Registers::Id::Xmm12);
        static initonly Operand::Register^ Xmm13 = gcnew Operand::Register(Registers::Id::Xmm13);
        static initonly Operand::Register^ Xmm14 = gcnew Operand::Register(Registers::Id::Xmm14);
        static initonly Operand::Register^ Xmm15 = gcnew Operand::Register(Registers::Id::Xmm15);
        static initonly Operand::Register^ Xmm16 = gcnew Operand::Register(Registers::Id::Xmm16);
        static initonly Operand::Register^ Xmm17 = gcnew Operand::Register(Registers::Id::Xmm17);
        static initonly Operand::Register^ Xmm18 = gcnew Operand::Register(Registers::Id::Xmm18);
        static initonly Operand::Register^ Xmm19 = gcnew Operand::Register(Registers::Id::Xmm19);
        static initonly Operand::Register^ Xmm20 = gcnew Operand::Register(Registers::Id::Xmm20);
        static initonly Operand::Register^ Xmm21 = gcnew Operand::Register(Registers::Id::Xmm21);
        static initonly Operand::Register^ Xmm22 = gcnew Operand::Register(Registers::Id::Xmm22);
        static initonly Operand::Register^ Xmm23 = gcnew Operand::Register(Registers::Id::Xmm23);
        static initonly Operand::Register^ Xmm24 = gcnew Operand::Register(Registers::Id::Xmm24);
        static initonly Operand::Register^ Xmm25 = gcnew Operand::Register(Registers::Id::Xmm25);
        static initonly Operand::Register^ Xmm26 = gcnew Operand::Register(Registers::Id::Xmm26);
        static initonly Operand::Register^ Xmm27 = gcnew Operand::Register(Registers::Id::Xmm27);
        static initonly Operand::Register^ Xmm28 = gcnew Operand::Register(Registers::Id::Xmm28);
        static initonly Operand::Register^ Xmm29 = gcnew Operand::Register(Registers::Id::Xmm29);
        static initonly Operand::Register^ Xmm30 = gcnew Operand::Register(Registers::Id::Xmm30);
        static initonly Operand::Register^ Xmm31 = gcnew Operand::Register(Registers::Id::Xmm31);
        // Floating point vector registers 256-bit
        static initonly Operand::Register^ Ymm0 = gcnew Operand::Register(Registers::Id::Ymm0);
        static initonly Operand::Register^ Ymm1 = gcnew Operand::Register(Registers::Id::Ymm1);
        static initonly Operand::Register^ Ymm2 = gcnew Operand::Register(Registers::Id::Ymm2);
        static initonly Operand::Register^ Ymm3 = gcnew Operand::Register(Registers::Id::Ymm3);
        static initonly Operand::Register^ Ymm4 = gcnew Operand::Register(Registers::Id::Ymm4);
        static initonly Operand::Register^ Ymm5 = gcnew Operand::Register(Registers::Id::Ymm5);
        static initonly Operand::Register^ Ymm6 = gcnew Operand::Register(Registers::Id::Ymm6);
        static initonly Operand::Register^ Ymm7 = gcnew Operand::Register(Registers::Id::Ymm7);
        static initonly Operand::Register^ Ymm8 = gcnew Operand::Register(Registers::Id::Ymm8);
        static initonly Operand::Register^ Ymm9 = gcnew Operand::Register(Registers::Id::Ymm9);
        static initonly Operand::Register^ Ymm10 = gcnew Operand::Register(Registers::Id::Ymm10);
        static initonly Operand::Register^ Ymm11 = gcnew Operand::Register(Registers::Id::Ymm11);
        static initonly Operand::Register^ Ymm12 = gcnew Operand::Register(Registers::Id::Ymm12);
        static initonly Operand::Register^ Ymm13 = gcnew Operand::Register(Registers::Id::Ymm13);
        static initonly Operand::Register^ Ymm14 = gcnew Operand::Register(Registers::Id::Ymm14);
        static initonly Operand::Register^ Ymm15 = gcnew Operand::Register(Registers::Id::Ymm15);
        static initonly Operand::Register^ Ymm16 = gcnew Operand::Register(Registers::Id::Ymm16);
        static initonly Operand::Register^ Ymm17 = gcnew Operand::Register(Registers::Id::Ymm17);
        static initonly Operand::Register^ Ymm18 = gcnew Operand::Register(Registers::Id::Ymm18);
        static initonly Operand::Register^ Ymm19 = gcnew Operand::Register(Registers::Id::Ymm19);
        static initonly Operand::Register^ Ymm20 = gcnew Operand::Register(Registers::Id::Ymm20);
        static initonly Operand::Register^ Ymm21 = gcnew Operand::Register(Registers::Id::Ymm21);
        static initonly Operand::Register^ Ymm22 = gcnew Operand::Register(Registers::Id::Ymm22);
        static initonly Operand::Register^ Ymm23 = gcnew Operand::Register(Registers::Id::Ymm23);
        static initonly Operand::Register^ Ymm24 = gcnew Operand::Register(Registers::Id::Ymm24);
        static initonly Operand::Register^ Ymm25 = gcnew Operand::Register(Registers::Id::Ymm25);
        static initonly Operand::Register^ Ymm26 = gcnew Operand::Register(Registers::Id::Ymm26);
        static initonly Operand::Register^ Ymm27 = gcnew Operand::Register(Registers::Id::Ymm27);
        static initonly Operand::Register^ Ymm28 = gcnew Operand::Register(Registers::Id::Ymm28);
        static initonly Operand::Register^ Ymm29 = gcnew Operand::Register(Registers::Id::Ymm29);
        static initonly Operand::Register^ Ymm30 = gcnew Operand::Register(Registers::Id::Ymm30);
        static initonly Operand::Register^ Ymm31 = gcnew Operand::Register(Registers::Id::Ymm31);
        // Floating point vector registers 512-bit
        static initonly Operand::Register^ Zmm0 = gcnew Operand::Register(Registers::Id::Zmm0);
        static initonly Operand::Register^ Zmm1 = gcnew Operand::Register(Registers::Id::Zmm1);
        static initonly Operand::Register^ Zmm2 = gcnew Operand::Register(Registers::Id::Zmm2);
        static initonly Operand::Register^ Zmm3 = gcnew Operand::Register(Registers::Id::Zmm3);
        static initonly Operand::Register^ Zmm4 = gcnew Operand::Register(Registers::Id::Zmm4);
        static initonly Operand::Register^ Zmm5 = gcnew Operand::Register(Registers::Id::Zmm5);
        static initonly Operand::Register^ Zmm6 = gcnew Operand::Register(Registers::Id::Zmm6);
        static initonly Operand::Register^ Zmm7 = gcnew Operand::Register(Registers::Id::Zmm7);
        static initonly Operand::Register^ Zmm8 = gcnew Operand::Register(Registers::Id::Zmm8);
        static initonly Operand::Register^ Zmm9 = gcnew Operand::Register(Registers::Id::Zmm9);
        static initonly Operand::Register^ Zmm10 = gcnew Operand::Register(Registers::Id::Zmm10);
        static initonly Operand::Register^ Zmm11 = gcnew Operand::Register(Registers::Id::Zmm11);
        static initonly Operand::Register^ Zmm12 = gcnew Operand::Register(Registers::Id::Zmm12);
        static initonly Operand::Register^ Zmm13 = gcnew Operand::Register(Registers::Id::Zmm13);
        static initonly Operand::Register^ Zmm14 = gcnew Operand::Register(Registers::Id::Zmm14);
        static initonly Operand::Register^ Zmm15 = gcnew Operand::Register(Registers::Id::Zmm15);
        static initonly Operand::Register^ Zmm16 = gcnew Operand::Register(Registers::Id::Zmm16);
        static initonly Operand::Register^ Zmm17 = gcnew Operand::Register(Registers::Id::Zmm17);
        static initonly Operand::Register^ Zmm18 = gcnew Operand::Register(Registers::Id::Zmm18);
        static initonly Operand::Register^ Zmm19 = gcnew Operand::Register(Registers::Id::Zmm19);
        static initonly Operand::Register^ Zmm20 = gcnew Operand::Register(Registers::Id::Zmm20);
        static initonly Operand::Register^ Zmm21 = gcnew Operand::Register(Registers::Id::Zmm21);
        static initonly Operand::Register^ Zmm22 = gcnew Operand::Register(Registers::Id::Zmm22);
        static initonly Operand::Register^ Zmm23 = gcnew Operand::Register(Registers::Id::Zmm23);
        static initonly Operand::Register^ Zmm24 = gcnew Operand::Register(Registers::Id::Zmm24);
        static initonly Operand::Register^ Zmm25 = gcnew Operand::Register(Registers::Id::Zmm25);
        static initonly Operand::Register^ Zmm26 = gcnew Operand::Register(Registers::Id::Zmm26);
        static initonly Operand::Register^ Zmm27 = gcnew Operand::Register(Registers::Id::Zmm27);
        static initonly Operand::Register^ Zmm28 = gcnew Operand::Register(Registers::Id::Zmm28);
        static initonly Operand::Register^ Zmm29 = gcnew Operand::Register(Registers::Id::Zmm29);
        static initonly Operand::Register^ Zmm30 = gcnew Operand::Register(Registers::Id::Zmm30);
        static initonly Operand::Register^ Zmm31 = gcnew Operand::Register(Registers::Id::Zmm31);
        // Flags registers
        static initonly Operand::Register^ Flags = gcnew Operand::Register(Registers::Id::Flags);
        static initonly Operand::Register^ EFlags = gcnew Operand::Register(Registers::Id::EFlags);
        static initonly Operand::Register^ RFlags = gcnew Operand::Register(Registers::Id::RFlags);
        // Instruction-pointer registers
        static initonly Operand::Register^ Ip = gcnew Operand::Register(Registers::Id::Ip);
        static initonly Operand::Register^ Eip = gcnew Operand::Register(Registers::Id::Eip);
        static initonly Operand::Register^ Rip = gcnew Operand::Register(Registers::Id::Rip);
        // Segment registers
        static initonly Operand::Register^ Es = gcnew Operand::Register(Registers::Id::Es);
        static initonly Operand::Register^ Cs = gcnew Operand::Register(Registers::Id::Cs);
        static initonly Operand::Register^ Ss = gcnew Operand::Register(Registers::Id::Ss);
        static initonly Operand::Register^ Ds = gcnew Operand::Register(Registers::Id::Ds);
        static initonly Operand::Register^ Fs = gcnew Operand::Register(Registers::Id::Fs);
        static initonly Operand::Register^ Gs = gcnew Operand::Register(Registers::Id::Gs);
        // Table registers
        static initonly Operand::Register^ Gdtr = gcnew Operand::Register(Registers::Id::Gdtr);
        static initonly Operand::Register^ Ldtr = gcnew Operand::Register(Registers::Id::Ldtr);
        static initonly Operand::Register^ Idtr = gcnew Operand::Register(Registers::Id::Idtr);
        static initonly Operand::Register^ Tr = gcnew Operand::Register(Registers::Id::Tr);
        // Test registers
        static initonly Operand::Register^ Tr0 = gcnew Operand::Register(Registers::Id::Tr0);
        static initonly Operand::Register^ Tr1 = gcnew Operand::Register(Registers::Id::Tr1);
        static initonly Operand::Register^ Tr2 = gcnew Operand::Register(Registers::Id::Tr2);
        static initonly Operand::Register^ Tr3 = gcnew Operand::Register(Registers::Id::Tr3);
        static initonly Operand::Register^ Tr4 = gcnew Operand::Register(Registers::Id::Tr4);
        static initonly Operand::Register^ Tr5 = gcnew Operand::Register(Registers::Id::Tr5);
        static initonly Operand::Register^ Tr6 = gcnew Operand::Register(Registers::Id::Tr6);
        static initonly Operand::Register^ Tr7 = gcnew Operand::Register(Registers::Id::Tr7);
        // Control registers
        static initonly Operand::Register^ Cr0 = gcnew Operand::Register(Registers::Id::Cr0);
        static initonly Operand::Register^ Cr1 = gcnew Operand::Register(Registers::Id::Cr1);
        static initonly Operand::Register^ Cr2 = gcnew Operand::Register(Registers::Id::Cr2);
        static initonly Operand::Register^ Cr3 = gcnew Operand::Register(Registers::Id::Cr3);
        static initonly Operand::Register^ Cr4 = gcnew Operand::Register(Registers::Id::Cr4);
        static initonly Operand::Register^ Cr5 = gcnew Operand::Register(Registers::Id::Cr5);
        static initonly Operand::Register^ Cr6 = gcnew Operand::Register(Registers::Id::Cr6);
        static initonly Operand::Register^ Cr7 = gcnew Operand::Register(Registers::Id::Cr7);
        static initonly Operand::Register^ Cr8 = gcnew Operand::Register(Registers::Id::Cr8);
        static initonly Operand::Register^ Cr9 = gcnew Operand::Register(Registers::Id::Cr9);
        static initonly Operand::Register^ Cr10 = gcnew Operand::Register(Registers::Id::Cr10);
        static initonly Operand::Register^ Cr11 = gcnew Operand::Register(Registers::Id::Cr11);
        static initonly Operand::Register^ Cr12 = gcnew Operand::Register(Registers::Id::Cr12);
        static initonly Operand::Register^ Cr13 = gcnew Operand::Register(Registers::Id::Cr13);
        static initonly Operand::Register^ Cr14 = gcnew Operand::Register(Registers::Id::Cr14);
        static initonly Operand::Register^ Cr15 = gcnew Operand::Register(Registers::Id::Cr15);
        // Debug registers
        static initonly Operand::Register^ Dr0 = gcnew Operand::Register(Registers::Id::Dr0);
        static initonly Operand::Register^ Dr1 = gcnew Operand::Register(Registers::Id::Dr1);
        static initonly Operand::Register^ Dr2 = gcnew Operand::Register(Registers::Id::Dr2);
        static initonly Operand::Register^ Dr3 = gcnew Operand::Register(Registers::Id::Dr3);
        static initonly Operand::Register^ Dr4 = gcnew Operand::Register(Registers::Id::Dr4);
        static initonly Operand::Register^ Dr5 = gcnew Operand::Register(Registers::Id::Dr5);
        static initonly Operand::Register^ Dr6 = gcnew Operand::Register(Registers::Id::Dr6);
        static initonly Operand::Register^ Dr7 = gcnew Operand::Register(Registers::Id::Dr7);
        static initonly Operand::Register^ Dr8 = gcnew Operand::Register(Registers::Id::Dr8);
        static initonly Operand::Register^ Dr9 = gcnew Operand::Register(Registers::Id::Dr9);
        static initonly Operand::Register^ Dr10 = gcnew Operand::Register(Registers::Id::Dr10);
        static initonly Operand::Register^ Dr11 = gcnew Operand::Register(Registers::Id::Dr11);
        static initonly Operand::Register^ Dr12 = gcnew Operand::Register(Registers::Id::Dr12);
        static initonly Operand::Register^ Dr13 = gcnew Operand::Register(Registers::Id::Dr13);
        static initonly Operand::Register^ Dr14 = gcnew Operand::Register(Registers::Id::Dr14);
        static initonly Operand::Register^ Dr15 = gcnew Operand::Register(Registers::Id::Dr15);
        // Mask registers
        static initonly Operand::Register^ K0 = gcnew Operand::Register(Registers::Id::K0);
        static initonly Operand::Register^ K1 = gcnew Operand::Register(Registers::Id::K1);
        static initonly Operand::Register^ K2 = gcnew Operand::Register(Registers::Id::K2);
        static initonly Operand::Register^ K3 = gcnew Operand::Register(Registers::Id::K3);
        static initonly Operand::Register^ K4 = gcnew Operand::Register(Registers::Id::K4);
        static initonly Operand::Register^ K5 = gcnew Operand::Register(Registers::Id::K5);
        static initonly Operand::Register^ K6 = gcnew Operand::Register(Registers::Id::K6);
        static initonly Operand::Register^ K7 = gcnew Operand::Register(Registers::Id::K7);
        // Bound registers
        static initonly Operand::Register^ Bnd0 = gcnew Operand::Register(Registers::Id::Bnd0);
        static initonly Operand::Register^ Bnd1 = gcnew Operand::Register(Registers::Id::Bnd1);
        static initonly Operand::Register^ Bnd2 = gcnew Operand::Register(Registers::Id::Bnd2);
        static initonly Operand::Register^ Bnd3 = gcnew Operand::Register(Registers::Id::Bnd3);
        static initonly Operand::Register^ BndCfg = gcnew Operand::Register(Registers::Id::BndCfg);
        static initonly Operand::Register^ BndStatus = gcnew Operand::Register(Registers::Id::BndStatus);
        // Uncategorized
        static initonly Operand::Register^ Mxcsr = gcnew Operand::Register(Registers::Id::Mxcsr);
        static initonly Operand::Register^ Pkru = gcnew Operand::Register(Registers::Id::Pkru);
        static initonly Operand::Register^ Xcr0 = gcnew Operand::Register(Registers::Id::Xcr0);
        // Host specific
        static initonly Operand::Register^ Nax = gcnew Operand::Register(Registers::Id::Nax);
        static initonly Operand::Register^ Ncx = gcnew Operand::Register(Registers::Id::Ncx);
        static initonly Operand::Register^ Ndx = gcnew Operand::Register(Registers::Id::Ndx);
        static initonly Operand::Register^ Nbx = gcnew Operand::Register(Registers::Id::Nbx);
        static initonly Operand::Register^ Nsp = gcnew Operand::Register(Registers::Id::Nsp);
        static initonly Operand::Register^ Nbp = gcnew Operand::Register(Registers::Id::Nbp);
        static initonly Operand::Register^ Nsi = gcnew Operand::Register(Registers::Id::Nsi);
        static initonly Operand::Register^ Ndi = gcnew Operand::Register(Registers::Id::Ndi);
        static initonly Operand::Register^ Nip = gcnew Operand::Register(Registers::Id::Nip);
        static initonly Operand::Register^ NFlags = gcnew Operand::Register(Registers::Id::NFlags);

        static Operand::Register^ Reg(Registers::Id reg)
        {
            return gcnew Operand::Register(reg);
        }

    public:
        static Operand::Immediate^ Imm(Int64 val)
        {
            return gcnew Operand::Immediate(val);
        }
    };

}
