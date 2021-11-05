#include "Instruction.Generator.hpp"
#include "Instruction.Encoder.hpp"
#include "Instruction.Decoder.hpp"
#include "AsmJitHelper.hpp"

#include <asmjit/asmjit.h>
#include <zydis/Zydis.h>

namespace Dotx64Dbg
{
    struct EncoderErrorHandler : asmjit::ErrorHandler
    {
        void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override
        {
            auto errMsg = getAsmjitErrorString(err);
            if (!errMsg)
                return;

            auto exMsg = "Generator Error: " + *errMsg;
            if (message != nullptr && strlen(message) > 0)
            {
                exMsg += "\nMessage: " + std::string(message);
            }
            auto strMessage = gcnew System::String(exMsg.c_str());
            throw gcnew System::InvalidOperationException(strMessage);
        }
    };

    static EncoderErrorHandler _errHandler{};

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

    // NOTE: This has to be within rel32
    constexpr int32_t DispMagic = 0xF000BA;
    constexpr int32_t LabelMagic = 0xF111BA;
    constexpr int32_t TargetMagic = 0xF222BA;
    constexpr int8_t LoopMagic = 0x5F;

    // Because we encode at the address zero we have to make sure certain values
    // are within the range of rel32 due to x86 restrictions.
    // Labels will be replaced by LabelMagic and memory displacements will be
    // replaced by DispMagic.
    // Those values will be set back to the original once decoded.
    static IOperand^ HandleOperand(Mnemonic mnemonic, int index, IOperand^ op)
    {
        if (op->Type == OperandType::None)
            return op;

        if (op->Type == OperandType::Memory)
        {
            auto mem = (Operand::Memory^)op;
            if (mem->Displacement != 0)
            {
                auto replacement = gcnew Operand::Memory();
                replacement->Size = mem->Size;
                replacement->Segment = mem->Segment;
                replacement->Base = mem->Base;
                replacement->Index = mem->Index;
                replacement->Scale = mem->Scale;
                replacement->Displacement = DispMagic;
                return replacement;
            }
        }
        else if (op->Type == OperandType::Label)
        {
            return gcnew Operand::Immediate(LabelMagic);
        }
        else if (op->Type == OperandType::Immediate)
        {
            // Temporarily swap immediate for control flow instructions.
            if (index == 0 &&
                InstructionMetaData::isControlFlow(mnemonic) &&
                !InstructionMetaData::isRet(mnemonic))
            {
                if(InstructionMetaData::isLoop(mnemonic))
                    return gcnew Operand::Immediate(LoopMagic);
                else
                    return gcnew Operand::Immediate(TargetMagic);
            }
        }

        return op;
    }

    Instruction^ InstructionGenerator::Generate(Instruction::Attributes attribs, Mnemonic mnemonic, IOperand^ op0, IOperand^ op1, IOperand^ op2, IOperand^ op3)
    {
        asmjit::CodeHolder code;
        code.init(asmjit::Environment::host(), 0);
        code.setErrorHandler(&_errHandler);

        asmjit::x86::Assembler assembler(&code);

        bool encoded = Internal::encodeInstruction(&assembler,
            nullptr,
            attribs,
            mnemonic,
            HandleOperand(mnemonic, 0, op0),
            HandleOperand(mnemonic, 1, op1),
            HandleOperand(mnemonic, 2, op2),
            HandleOperand(mnemonic, 3, op3));

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

        // Switch out the operands if required.
        if (op0 != nullptr && op0->Type != OperandType::None)
        {
            auto newOp = instr->GetOperand(0);
            if (op0->Type == OperandType::Label)
            {
                if (newOp->Type == OperandType::Immediate)
                {
                    auto imm = (Operand::Immediate^)newOp;
                    if (imm->Value == LabelMagic)
                    {
                        instr->SetOperand(0, op0);
                    }
                }
            }
            else if (op0->Type == OperandType::Memory)
            {
                if (newOp->Type == OperandType::Memory)
                {
                    auto mem = (Operand::Memory^)newOp;
                    if (mem->Displacement == DispMagic)
                    {
                        instr->SetOperand(0, op0);
                    }
                }
            }
            else if (op0->Type == OperandType::Immediate)
            {
                if (InstructionMetaData::isControlFlow(mnemonic) && !InstructionMetaData::isRet(mnemonic))
                {
                    auto magicVal = InstructionMetaData::isLoop(mnemonic) ? LoopMagic : TargetMagic;
                    auto imm = (Operand::Immediate^)newOp;
                    if (imm->Value == magicVal)
                    {
                        instr->SetOperand(0, op0);
                    }
                }
            }
        }
        if (op1 != nullptr && op1->Type != OperandType::None)
        {
            if (op1->Type == OperandType::Memory)
            {
                auto newOp = instr->GetOperand(1);
                if (newOp->Type == OperandType::Memory)
                {
                    auto mem = (Operand::Memory^)newOp;
                    if (mem->Displacement == DispMagic)
                    {
                        instr->SetOperand(1, op1);
                    }
                }
            }
        }
        if (op2 != nullptr && op2->Type != OperandType::None)
        {
            if (op2->Type == OperandType::Memory)
            {
                auto newOp = instr->GetOperand(2);
                if (newOp->Type == OperandType::Memory)
                {
                    auto mem = (Operand::Memory^)newOp;
                    if (mem->Displacement == DispMagic)
                    {
                        instr->SetOperand(2, op2);
                    }
                }
            }
        }
        if (op3 != nullptr && op3->Type != OperandType::None)
        {
            if (op2->Type == OperandType::Memory)
            {
                auto newOp = instr->GetOperand(3);
                if (newOp->Type == OperandType::Memory)
                {
                    auto mem = (Operand::Memory^)newOp;
                    if (mem->Displacement == DispMagic)
                    {
                        instr->SetOperand(3, op3);
                    }
                }
            }
        }

        return instr;
    }

}
