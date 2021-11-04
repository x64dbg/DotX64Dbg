#include "Instruction.Generator.hpp"
#include "Instruction.Encoder.hpp"
#include "Instruction.Decoder.hpp"

#include <asmjit/asmjit.h>
#include <zydis/Zydis.h>

namespace Dotx64Dbg
{
    Instruction^ InstructionGenerator::Generate(Mnemonic mnemonic)
    {
        return Generate(Instruction::Attributes::None, mnemonic);
    }

    Instruction^ InstructionGenerator::Generate(Mnemonic mnemonic, IOperand^ op0)
    {
        return Generate(Instruction::Attributes::None, mnemonic, op0);
    }

    Instruction^ InstructionGenerator::Generate(Mnemonic mnemonic, IOperand^ op0, IOperand^ op1)
    {
        return Generate(Instruction::Attributes::None, mnemonic, op0, op1);
    }

    Instruction^ InstructionGenerator::Generate(Mnemonic mnemonic, IOperand^ op0, IOperand^ op1, IOperand^ op2)
    {
        return Generate(Instruction::Attributes::None, mnemonic, op0, op1, op2);
    }

    Instruction^ InstructionGenerator::Generate(Mnemonic mnemonic, IOperand^ op0, IOperand^ op1, IOperand^ op2, IOperand^ op3)
    {
        return Generate(Instruction::Attributes::None, mnemonic, op0, op1, op2, op3);
    }

    Instruction^ InstructionGenerator::Generate(Instruction::Attributes attribs, Mnemonic mnemonic)
    {
        return Generate(attribs, mnemonic, Operand::None, Operand::None, Operand::None, Operand::None);
    }

    Instruction^ InstructionGenerator::Generate(Instruction::Attributes attribs, Mnemonic mnemonic, IOperand^ op0)
    {
        return Generate(attribs, mnemonic, op0, Operand::None, Operand::None, Operand::None);
    }

    Instruction^ InstructionGenerator::Generate(Instruction::Attributes attribs, Mnemonic mnemonic, IOperand^ op0, IOperand^ op1)
    {
        return Generate(attribs, mnemonic, op0, op1, Operand::None, Operand::None);
    }

    Instruction^ InstructionGenerator::Generate(Instruction::Attributes attribs, Mnemonic mnemonic, IOperand^ op0, IOperand^ op1, IOperand^ op2)
    {
        return Generate(attribs, mnemonic, op0, op1, op2, Operand::None);
    }

    Instruction^ InstructionGenerator::Generate(Instruction::Attributes attribs, Mnemonic mnemonic, IOperand^ op0, IOperand^ op1, IOperand^ op2, IOperand^ op3)
    {
        asmjit::CodeHolder code;
        code.init(asmjit::Environment::host(), 0);

        asmjit::x86::Assembler assembler(&code);

        bool encoded = Internal::encodeInstruction(&assembler, nullptr, attribs, mnemonic, op0, op1, op2, op3);

        if (!encoded)
            return nullptr;

        uint8_t buffer[64]{};

        auto codeSize = code.codeSize();
        code.copyFlattenedData(buffer, sizeof(buffer));

        ZydisDecoder decoder;
#ifdef _M_AMD64
        auto mode = ZYDIS_MACHINE_MODE_LONG_64;
        auto addrSize = ZYDIS_ADDRESS_WIDTH_64;
#else
        auto mode = ZYDIS_MACHINE_MODE_LEGACY_32;
        auto addrSize = ZYDIS_ADDRESS_WIDTH_32;
#endif
        if (auto status = ZydisDecoderInit(&decoder, mode, addrSize);
            status != ZYAN_STATUS_SUCCESS)
        {
            return nullptr;
        }

        auto instr = Internal::decodeInstruction(&decoder, buffer, codeSize, 0);

        // Switch back the labels.
        if (op0 != nullptr && op0->Type == OperandType::Label)
        {
            instr->SetOperand(0, op0);
        }

        // FIXME: Do this for memory operands, currently unsupported to have labels.

        return instr;
    }

}
