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

	static IOperand^ ConvertOperandImm(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
	{
		Operand::Immediate^ res = gcnew Operand::Immediate();
		res->Value = op.imm.value.s;
		if (op.imm.is_relative)
		{
			res->Value += instr.length + addr;
		}
		return res;
	}

	static IOperand^ ConvertOperandReg(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
	{
		const auto reg = convertZydisRegister(op.reg.value);
		return gcnew Operand::Register(reg);
	}

	static IOperand^ ConvertOperandMem(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
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

	static IOperand^ ConvertOperand(const ZydisDecodedInstruction& instr, const ZydisDecodedOperand& op, uint64_t addr)
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

	static Instruction^ Convert(ZydisDecodedInstruction& instr, uint64_t addr)
	{
		const auto id = convertZydisMnemonic(instr.mnemonic);

		auto attribs = Instruction::Attributes::None;

		auto addAttribute = [&](Instruction::Attributes a, Instruction::Attributes b)
		{
			return static_cast<Instruction::Attributes>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
		};

		if (instr.attributes & ZYDIS_ATTRIB_HAS_LOCK)
		{
			attribs = addAttribute(attribs, Instruction::Attributes::Lock);
		}

		if (instr.attributes & ZYDIS_ATTRIB_HAS_REP)
		{
			attribs = addAttribute(attribs, Instruction::Attributes::Rep);
		}

		if (instr.attributes & ZYDIS_ATTRIB_HAS_REPE)
		{
			attribs = addAttribute(attribs, Instruction::Attributes::RepEq);
		}

		if (instr.attributes & ZYDIS_ATTRIB_HAS_REPNE)
		{
			attribs = addAttribute(attribs, Instruction::Attributes::RepNe);
		}

		if (instr.attributes & ZYDIS_ATTRIB_HAS_REPNZ)
		{
			attribs = addAttribute(attribs, Instruction::Attributes::RepNz);
		}

		auto res = gcnew Instruction(attribs, id);
		res->_Size = instr.length;
		res->_Address = addr;

		auto instrFlags = getEFlags(instr);
		res->_FlagsModified = (EFlags)instrFlags.write;
		res->_FlagsRead = (EFlags)instrFlags.read;

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
			{
				access = static_cast<OperandAccess>(
					static_cast<uint32_t>(access) | static_cast<uint32_t>(OperandAccess::Read));
			}

			if (op.actions & ZYDIS_OPERAND_ACTION_MASK_WRITE)
			{
				access = static_cast<OperandAccess>(
					static_cast<uint32_t>(access) | static_cast<uint32_t>(OperandAccess::Write));
			}

			res->SetOperand(opIndex, newOp, access, vis);
			opIndex++;
		}

		return res;
	}

	Instruction^ decodeInstruction(const ZydisDecoder* decoder, const uint8_t* buf, size_t len, uint64_t address)
	{
		ZydisDecodedInstruction instr{};
		if (auto status = ZydisDecoderDecodeBuffer(decoder, buf, len, &instr); status != ZYAN_STATUS_SUCCESS)
		{
			return nullptr;
		}

		return Convert(instr, address);
	}

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

			return decodeInstruction(_decoder, buf, data->Length, address);
        }

        Instruction^ Decode(System::UIntPtr address)
        {
            auto va = static_cast<duint>(address.ToUInt64());
            duint readSize = 0;

            uint8_t buf[15];
            if (!Script::Memory::Read(static_cast<duint>(va), buf, sizeof(buf), &readSize))
                return nullptr;

			return decodeInstruction(_decoder, buf, readSize, va);
        }

    private:
        
    };
} // namespace Dotx64Dbg
