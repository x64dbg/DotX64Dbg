#include <cstdint>
#include <utility>
#include <cctype>

#include <zydis/zydis.h>
#include "Instruction.hpp"
#include "Decoder.Converter.hpp"

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"

namespace Dotx64Dbg
{

    static constexpr uint32_t Flags[] = {
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

    struct EFlagsData
    {
        uint32_t read;
        uint32_t write;
    };

    public ref class Decoder
    {
        ZydisDecoder* _decoder;

    private:
        Decoder()
        {
            _decoder = new ZydisDecoder();
#ifdef _M_AMD64
            auto mode = ZYDIS_MACHINE_MODE_LONG_64;
            auto addrSize = ZYDIS_ADDRESS_WIDTH_64;
#else
            auto mode = ZYDIS_MACHINE_MODE_LEGACY_32;
            auto addrSize = ZYDIS_ADDRESS_WIDTH_32;
#endif
            if (auto status = ZydisDecoderInit(_decoder, mode, addrSize);
                status != ZYAN_STATUS_SUCCESS)
            {
                char msg[64]{};
                sprintf_s(msg, "ZydisDecoderInit failed: %u\n", status);
                _plugin_logprint(msg);
            }
            else
            {
                _plugin_logprint("Decoder startup good\n");
            }
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

        Instruction^ Decode(System::UIntPtr address)
        {
            auto va = static_cast<duint>(address.ToUInt64());
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
            const auto reg = convertZydisRegister(op.reg.value);
            return gcnew Operand::Register(reg);
        }

        IOperand^ ConvertOperandMem(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
        {
            const auto& mem = op.mem;

            Operand::Memory^ res = gcnew Operand::Memory();

            res->Size = op.size;
            res->Segment = static_cast<RegisterId>(mem.segment);
            res->Base = static_cast<RegisterId>(mem.base);
            res->Index = static_cast<RegisterId>(mem.index);
            res->Scale = mem.scale;
            res->Displacement = mem.disp.value;

            if (res->Base == RegisterId::Rip || res->Base == RegisterId::Eip)
            {
                res->Displacement += instr.length + addr;
                res->Base = RegisterId::None;
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

        static EFlagsData getEFlags(const ZydisDecodedInstruction& ins)
        {
            EFlagsData res{};

            res.read = ins.cpu_flags_read;
            res.write = ins.cpu_flags_written;

            return res;
        }

        Instruction^ Convert(ZydisDecodedInstruction& instr, uint64_t addr)
        {
            const auto id = convertZydisMnemonic(instr.mnemonic);
            auto res = gcnew Instruction(id);

            res->Size = instr.length;
            res->Address = addr;

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

            bool invalidMeta = false;
            auto instrMeta = res->Meta;

            auto instrFlags = getEFlags(instr);
            if (instrMeta->FlagsModified != (EFlags)instrFlags.write || instrMeta->FlagsRead != (EFlags)instrFlags.read)
            {
                invalidMeta = true;
            }

            int opIndex = 0;
            for (int i = 0; i < instr.operand_count; i++)
            {
                auto& op = instr.operands[i];

                IOperand^ newOp = ConvertOperand(instr, op, addr);
                OperandVisibility vis = OperandVisibility::Invalid;
                if (op.visibility == ZYDIS_OPERAND_VISIBILITY_EXPLICIT)
                    vis = OperandVisibility::Explicit;
                else if (op.visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
                    vis = OperandVisibility::Hidden;
                else if (op.visibility == ZYDIS_OPERAND_VISIBILITY_IMPLICIT)
                    vis = OperandVisibility::Implicit;
                else
                    vis = OperandVisibility::Invalid;

                OperandAccess access = OperandAccess::None;
                if (op.actions & ZYDIS_OPERAND_ACTION_MASK_READ)
                    access = static_cast<OperandAccess>(
                        static_cast<uint32_t>(access) | static_cast<uint32_t>(OperandAccess::Read));

                if (op.actions & ZYDIS_OPERAND_ACTION_MASK_WRITE)
                    access = static_cast<OperandAccess>(
                        static_cast<uint32_t>(access) | static_cast<uint32_t>(OperandAccess::Write));

                if (instrMeta->Access[i] != access || instrMeta->Visibility[i] != vis)
                {
                    invalidMeta = true;
                }

                res->SetOperand(opIndex, newOp, access, vis);
                opIndex++;
            }

            if (invalidMeta)
            {
                std::string infoDump;

                infoDump += "gcnew InstructionMeta(\n";

                std::string mnemonicName = MnemonicGetString(res->Id);
                mnemonicName[0] = std::toupper(mnemonicName[0]);

                infoDump += "    Mnemonic::" + mnemonicName + ", \n";

                char temp[256];
                sprintf_s(temp, "    0x%04X, 0x%04X,\n", instrFlags.read, instrFlags.write);
                infoDump += temp;

                std::string opAccess;
                std::string opVisibility;
                std::string ops;

                for (int i = 0; i < 5; i++)
                {
                    auto op = res->GetOperand(i);

                    auto access = i >= instr.operand_count ? OperandAccess::None : res->GetOperandAccess(i);
                    if (access == OperandAccess::None)
                    {
                        if (i > 0)
                            opAccess += ", ";
                        opAccess += "OperandAccess::None";
                    }
                    else if (access == OperandAccess::Read)
                    {
                        if (i > 0)
                            opAccess += ", ";
                        opAccess += "OperandAccess::Read";
                    }
                    else if (access == OperandAccess::Write)
                    {
                        if (i > 0)
                            opAccess += ", ";
                        opAccess += "OperandAccess::Write";
                    }
                    else if (access == OperandAccess::ReadWrite)
                    {
                        if (i > 0)
                            opAccess += ", ";
                        opAccess += "OperandAccess::ReadWrite";
                    }

                    auto vis = i >= instr.operand_count ? OperandVisibility::Invalid : res->GetOperandVisibility(i);
                    if (vis == OperandVisibility::Invalid)
                    {
                        if (i > 0)
                            opVisibility += ", ";
                        opVisibility += "OperandVisibility::Invalid";
                    }
                    else if (vis == OperandVisibility::Explicit)
                    {
                        if (i > 0)
                            opVisibility += ", ";
                        opVisibility += "OperandVisibility::Explicit";
                    }
                    else if (vis == OperandVisibility::Implicit)
                    {
                        if (i > 0)
                            opVisibility += ", ";
                        opVisibility += "OperandVisibility::Implicit";
                    }
                    else if (vis == OperandVisibility::Hidden)
                    {
                        if (i > 0)
                            opVisibility += ", ";
                        opVisibility += "OperandVisibility::Hidden";
                    }

                    if (i >= instr.operand_count || vis == OperandVisibility::Explicit || vis == OperandVisibility::Implicit)
                    {
                        if (i > 0)
                            ops += ", ";
                        ops += "Operand::None";
                    }
                    else if (vis == OperandVisibility::Hidden)
                    {
                        if (i > 0)
                            ops += ", ";

                        if (op->Type == OperandType::Register)
                        {
                            Operand::Register^ reg = (Operand::Register^)op;
                            auto regId = reg->Value;

                            std::string regName = RegisterGetName(regId);
                            regName[0] = std::toupper(regName[0]);

#if _M_X64
                            if (regId == RegisterId::RFlags)
                            {
                                regName = "NFlags";
                            }
#else
                            if (regId == RegisterId::EFlags)
                            {
                                regName = "NFlags";
                            }
#endif

                            ops += "Operands::Reg(Register::" + regName + ")";
                        }
                        else if (op->Type == OperandType::Memory)
                        {
                            Operand::Memory^ mem = (Operand::Memory^)op;

                            if (mem->Size == 8)
                            {
                                ops += "Operands::BytePtr(";
                            }
                            else if (mem->Size == 16)
                            {
                                ops += "Operands::WordPtr(";
                            }
                            else if (mem->Size == 32)
                            {
#ifdef _M_X64
                                ops += "Operands::DwordPtr(";
#else
                                ops += "Operands::Ptr(";
#endif
                            }
                            else if (mem->Size == 64)
                            {
#ifdef _M_X64
                                ops += "Operands::Ptr(";
#else
                                ops += "Operands::QwordPtr(";
#endif
                            }

                            if (mem->Base != RegisterId::None)
                            {
                                std::string regName = RegisterGetName(mem->Base);
                                regName[0] = std::toupper(regName[0]);

                                ops += "Register::" + regName;
                            }

                            if (mem->Index != RegisterId::None)
                            {
                                std::string regName = RegisterGetName(mem->Base);
                                regName[0] = std::toupper(regName[0]);

                                if (mem->Base != RegisterId::None)
                                    ops += ", ";

                                ops += "Register::" + regName;
                            }

                            ops += ")";
                        }
                    }
                }

                infoDump += "    gcnew array<OperandAccess> { " + opAccess + " },\n";
                infoDump += "    gcnew array<OperandVisibility> { " + opVisibility + " },\n";
                infoDump += "    gcnew array<IOperand^> { " + ops + " }\n";

                infoDump += "),\n";

                _plugin_logprint("Mismatch detected!\n");
                _plugin_logprint(infoDump.c_str());
            }

            return res;
        }
    };
} // namespace Dotx64Dbg
