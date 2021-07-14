#include <cstdint>
#include <utility>

#include <zydis/zydis.h>
#include "Instruction.hpp"

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"

namespace Dotx64Dbg {

    static constexpr uint32_t Flags[] =
    {
        (1 << 0),  // ZYDIS_CPUFLAG_CF
        (1 << 2),  // ZYDIS_CPUFLAG_PF,
        (1 << 4),  // ZYDIS_CPUFLAG_AF,
        (1 << 6),  // ZYDIS_CPUFLAG_ZF,
        (1 << 7),  // ZYDIS_CPUFLAG_SF,
        (1 << 8),  // ZYDIS_CPUFLAG_TF,
        (1 << 9),  // ZYDIS_CPUFLAG_IF,
        (1 << 10), // ZYDIS_CPUFLAG_DF,
        (1 << 11), // ZYDIS_CPUFLAG_OF,
        (1 << 12), // ZYDIS_CPUFLAG_IOPL,
        (1 << 14), // ZYDIS_CPUFLAG_NT,
        (1 << 16), // ZYDIS_CPUFLAG_RF,
        (1 << 17), // ZYDIS_CPUFLAG_VM,
        (1 << 18), // ZYDIS_CPUFLAG_AC,
        (1 << 19), // ZYDIS_CPUFLAG_VIF,
        (1 << 20), // ZYDIS_CPUFLAG_VIP,
        (1 << 21), // ZYDIS_CPUFLAG_ID,
        (1 << 22), // ZYDIS_CPUFLAG_C0
        (1 << 23), // ZYDIS_CPUFLAG_C1,
        (1 << 24), // ZYDIS_CPUFLAG_C2,
        (1 << 25), // ZYDIS_CPUFLAG_C3,
    };

    public ref class Decoder
    {
        ZydisDecoder* _decoder;

    private:
        Decoder()
        {
            _decoder = new ZydisDecoder();
#ifdef _M_AMD64
            ZydisDecoderInit(_decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
#else
            ZydisDecoderInit(_decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_ADDRESS_WIDTH_32);
#endif
        }

    public:
        ~Decoder()
        {
            delete _decoder;
        }

        static Decoder^ Create()
        {
            return gcnew Decoder();
        }

        Instruction^ Decode(array<System::Byte>^ data, uint64_t address)
        {
            pin_ptr<uint8_t> ptr = &data[0];
            const uint8_t* buf = ptr;

            ZydisDecodedInstruction instr{};
            if (auto status = ZydisDecoderDecodeBuffer(_decoder, buf, data->Length, &instr); status != ZYAN_STATUS_SUCCESS)
            {
                return nullptr;
            }

            return Convert(instr, address);
        }

        Instruction^ Decode(uintptr_t va)
        {
            duint readSize = 0;

            uint8_t buf[15];
            if (!Script::Memory::Read(static_cast<duint>(va), buf, sizeof(buf), &readSize))
                return nullptr;

            ZydisDecodedInstruction instr{};
            if (auto status = ZydisDecoderDecodeBuffer(_decoder, buf, readSize, &instr); status != ZYAN_STATUS_SUCCESS)
            {
                return nullptr;
            }

            return Convert(instr, va);
        }

    private:
        IOperand^ ConvertOperandImm(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
        {
            Operand::OpImm^ res = gcnew Operand::OpImm();
            res->Value = op.imm.value.s;
            if (op.imm.is_relative)
            {
                res->Value += instr.length + addr;
            }
            return res;
        }

        IOperand^ ConvertOperandReg(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
        {
            return gcnew Operand::OpReg(static_cast<Register>(op.reg.value));
        }

        IOperand^ ConvertOperandMem(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
        {
            const auto& mem = op.mem;

            Operand::OpMem^ res = gcnew Operand::OpMem();

            res->Size = op.size;
            res->Segment = static_cast<Register>(mem.segment);
            res->Base = static_cast<Register>(mem.base);
            res->Index = static_cast<Register>(mem.index);
            res->Scale = mem.scale;
            res->Displacement = mem.disp.value;

            if (res->Base == Register::Rip || res->Base == Register::Eip)
            {
                res->Displacement += instr.length + addr;
                res->Base = Register::None;
            }

            return res;
        }

        IOperand^ ConvertOperand(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
        {
            if (op.type == ZYDIS_OPERAND_TYPE_IMMEDIATE)
            {
                return ConvertOperandImm(instr, op, addr);
            }
            else if (op.type == ZYDIS_OPERAND_TYPE_REGISTER)
            {
                return ConvertOperandReg(instr, op, addr);
            }
            else if (op.type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                return ConvertOperandMem(instr, op, addr);
            }
            else if (op.type == ZYDIS_OPERAND_TYPE_UNUSED)
            {
                return Operand::None;
            }
            // ??
            return Operand::None;
        }

        static std::pair<uint32_t, uint32_t> getEFlags(const ZydisDecodedInstruction& ins)
        {
            uint32_t flagsR = 0;
            uint32_t flagsW = 0;

            size_t idx = 0;
            for (auto& fl : ins.accessed_flags)
            {
                if (fl.action == ZYDIS_CPUFLAG_ACTION_NONE)
                {
                    idx++;
                    continue;
                }
                if (fl.action == ZYDIS_CPUFLAG_ACTION_SET_0 || fl.action == ZYDIS_CPUFLAG_ACTION_SET_1
                    || fl.action == ZYDIS_CPUFLAG_ACTION_UNDEFINED || fl.action == ZYDIS_CPUFLAG_ACTION_TESTED_MODIFIED
                    || fl.action == ZYDIS_CPUFLAG_ACTION_MODIFIED)
                {
                    flagsW |= Flags[idx];
                }
                if (fl.action == ZYDIS_CPUFLAG_ACTION_TESTED || fl.action == ZYDIS_CPUFLAG_ACTION_TESTED_MODIFIED)
                {
                    flagsR |= Flags[idx];
                }
                idx++;
            }

            return { flagsR, flagsW };
        }

        Instruction^ Convert(ZydisDecodedInstruction& instr, uint64_t addr)
        {
            auto res = gcnew Instruction();

            res->Size = instr.length;
            res->Address = addr;
            res->Id = static_cast<Mnemonic>(instr.mnemonic);

            if (instr.attributes & ZYDIS_ATTRIB_HAS_LOCK)
                res->Attribs |= Instruction::Attributes::Lock;

            if (instr.attributes & ZYDIS_ATTRIB_HAS_REP)
                res->Attribs |= Instruction::Attributes::Rep;

            if (instr.attributes & ZYDIS_ATTRIB_HAS_REPE)
                res->Attribs |= Instruction::Attributes::RepEq;

            if (instr.attributes & ZYDIS_ATTRIB_HAS_REPNE)
                res->Attribs |= Instruction::Attributes::RepNe;

            if (instr.attributes & ZYDIS_ATTRIB_HAS_REPNZ)
                res->Attribs |= Instruction::Attributes::RepNz;

            for (int i = 0; i < instr.operand_count; i++)
            {
                auto& op = instr.operands[i];

                IOperand^ newOp = ConvertOperand(instr, op, addr);

                if (op.visibility == ZYDIS_OPERAND_VISIBILITY_EXPLICIT)
                    newOp->Visibility = OperandVisibility::Explicit;
                else if (op.visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
                    newOp->Visibility = OperandVisibility::Hidden;
                else if (op.visibility == ZYDIS_OPERAND_VISIBILITY_IMPLICIT)
                    newOp->Visibility = OperandVisibility::Implicit;
                else
                    newOp->Visibility = OperandVisibility::Invalid;

                if (op.actions & ZYDIS_OPERAND_ACTION_MASK_READ)
                    newOp->Access |= OperandAccess::Read;

                if (op.actions & ZYDIS_OPERAND_ACTION_MASK_WRITE)
                    newOp->Access |= OperandAccess::Write;

                res->SetOperand(i, newOp);

#ifdef _DEBUG
                auto [flagsR, flagsW] = getEFlags(instr);
                if (res->FlagsRead != (EFlags)flagsR)
                {
                    __debugbreak();
                }

                if (res->FlagsWrite != (EFlags)flagsW)
                {
                    __debugbreak();
                }
#endif
            }

            return res;
        }
    };
}
