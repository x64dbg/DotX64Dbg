#include "AsmJitHelper.hpp"
#include "Encoder.Converter.hpp"

#include <cstdint>
#include <utility>
#include <vector>
#include <string>

namespace Dotx64Dbg {

    struct EncoderErrorHandler : asmjit::ErrorHandler
    {
        void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override
        {
            auto errMsg = getAsmjitErrorString(err);
            if (!errMsg)
                return;

            auto exMsg = "Encoder Error: " + *errMsg;
            if (message != nullptr && strlen(message) > 0)
            {
                exMsg += "\nMessage: " + std::string(message);
            }
            auto strMessage = gcnew System::String(exMsg.c_str());
            throw gcnew System::InvalidOperationException(strMessage);
        }
    };

    static EncoderErrorHandler _errHandler{};

    template<typename T>
    static constexpr T getShift(T x)
    {
        if (x == 0)
            return 0;
        T shift = 0;
        while ((x & 1) == 0)
        {
            x >>= 1;
            shift++;
        }
        return shift;
    }

    static uint32_t bitsToBytes(uint32_t bits)
    {
        return bits >> 3;
    }

    static asmjit::Operand convertOp(asmjit::x86::Assembler* a,
        IOperand^ op,
        System::Collections::Generic::Dictionary<Label^, UInt32>^ labels)
    {
        if (op->Type == OperandType::None)
            return {};

        if (op->Type == OperandType::Register)
        {
            auto opReg = (Operand::Register^)op;
            return convertAsmJitRegister(opReg->Value);
        }
        else if (op->Type == OperandType::Immediate)
        {
            auto opImm = (Operand::Immediate^)op;
            return asmjit::Imm(opImm->Value);
        }
        else if (op->Type == OperandType::Memory)
        {
            auto opMem = (Operand::Memory^)op;
            auto mem = asmjit::x86::Mem();
            mem.setBase(convertAsmJitRegister(opMem->Base));
            mem.setIndex(convertAsmJitRegister(opMem->Index), getShift(opMem->Scale));
            mem.setSegment(convertAsmJitRegister(opMem->Segment).as<asmjit::x86::SReg>());
            mem.setSize(bitsToBytes(opMem->Size));
            mem.setOffset(opMem->Displacement);
            return mem;
        }
        else if (op->Type == OperandType::Label)
        {
            if (labels == nullptr)
            {
                return asmjit::Imm(0x7FFFFFFF);
            }
            else
            {
                auto opLabel = (Label^)op;

                asmjit::Label realLabel{};

                UInt32 labelId;
                if (labels->TryGetValue(opLabel, labelId))
                {
                    realLabel = asmjit::Label{ labelId };
                }
                else
                {
                    realLabel = a->newLabel();
                    labels->Add(opLabel, realLabel.id());
                }

                return realLabel;
            }

        }
        return {};
    }

    namespace Internal {

        bool encodeInstruction(asmjit::x86::Assembler* a,
            System::Collections::Generic::Dictionary<Label^, UInt32>^ labels,
            Instruction::Attributes attrib,
            Mnemonic mnemonic,
            IOperand^ op0_,
            IOperand^ op1_,
            IOperand^ op2_,
            IOperand^ op3_)
        {
            auto opCount = 0;

            auto op0 = convertOp(a, op0_, labels);
            if (!op0.isNone())
                opCount++;

            auto op1 = convertOp(a, op1_, labels);
            if (!op1.isNone())
                opCount++;

            auto op2 = convertOp(a, op2_, labels);
            if (!op2.isNone())
                opCount++;

            auto op3 = convertOp(a, op3_, labels);
            if (!op3.isNone())
                opCount++;

            if ((attrib & Instruction::Attributes::Lock) != Instruction::Attributes::None)
                a->lock();

            if ((attrib & Instruction::Attributes::Rep) != Instruction::Attributes::None)
                a->rep();

            if ((attrib & Instruction::Attributes::RepNe) != Instruction::Attributes::None)
                a->repne();

            if ((attrib & Instruction::Attributes::RepEq) != Instruction::Attributes::None)
                a->repe();

            if ((attrib & Instruction::Attributes::RepNz) != Instruction::Attributes::None)
                a->repnz();

            const auto asmjitMnemonic = convertAsmJitMnemonic(mnemonic);
            switch (mnemonic)
            {
            case Mnemonic::Cmpsb:
                if (opCount == 0)
                {
                    if (a->cmpsb() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Cmpsw:
                if (opCount == 0)
                {
                    if (a->cmpsw() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Cmpsd:
                if (opCount == 0)
                {
                    if (a->cmpsd() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Cmpsq:
                if (opCount == 0)
                {
                    if (a->cmpsq() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Movsb:
                if (opCount == 0)
                {
                    if (a->movsb() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Movsw:
                if (opCount == 0)
                {
                    if (a->movsw() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Movsd:
                if (opCount == 0)
                {
                    if (a->movsd() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Movsq:
                if (opCount == 0)
                {
                    if (a->movsq() != asmjit::kErrorOk)
                    {
                        return false;
                    }
                    return true;
                }
                break;
            case Mnemonic::Lodsb:
                if (a->lodsb() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Lodsw:
                if (a->lodsw() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Lodsd:
                if (a->lodsd() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Lodsq:
                if (a->lodsq() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Stosb:
                if (a->stosb() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Stosw:
                if (a->stosw() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Stosd:
                if (a->stosd() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Stosq:
                if (a->stosq() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Scasb:
                if (a->scasb() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Scasw:
                if (a->scasw() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Scasd:
                if (a->scasd() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            case Mnemonic::Scasq:
                if (a->scasq() != asmjit::kErrorOk)
                {
                    return false;
                }
                return true;
            }

            // Generic case.
            if (a->emit(asmjitMnemonic, op0, op1, op2, op3) != asmjit::kErrorOk)
            {
                return false;
            }

            return true;
        }
    }

    static bool encodeInstruction(asmjit::x86::Assembler* a,
        System::Collections::Generic::Dictionary<Label^, UInt32>^ labels,
        Instruction^ instr)
    {
        auto op0 = instr->GetOperandVisibility(0) == OperandVisibility::Hidden ? Operand::None : instr->GetOperand(0);
        auto op1 = instr->GetOperandVisibility(1) == OperandVisibility::Hidden ? Operand::None : instr->GetOperand(1);
        auto op2 = instr->GetOperandVisibility(2) == OperandVisibility::Hidden ? Operand::None : instr->GetOperand(2);
        auto op3 = instr->GetOperandVisibility(3) == OperandVisibility::Hidden ? Operand::None : instr->GetOperand(3);

        auto mnemonic = convertAsmJitMnemonic(instr->Id);

        return Internal::encodeInstruction(a, labels, instr->Attribs, instr->Id, op0, op1, op2, op3);
    }

    public ref class Encoder
    {
        asmjit::CodeHolder* _code{};
        asmjit::x86::Assembler* _assembler{};
        System::Collections::Generic::Dictionary<Label^, UInt32>^ _labels;

    private:
        Encoder(uintptr_t baseVA)
        {
            _labels = gcnew System::Collections::Generic::Dictionary<Label^, UInt32>();
            _code = new asmjit::CodeHolder();
            _code->init(asmjit::Environment::host(), baseVA);
            _assembler = new asmjit::x86::Assembler(_code);
            _assembler->setErrorHandler(&_errHandler);
        }

    public:
        ~Encoder()
        {
            delete _assembler;
            delete _code;
        }

        static Encoder^ Create(System::UIntPtr baseVA)
        {
            return gcnew Encoder(static_cast<uintptr_t>(baseVA.ToUInt64()));
        }

        void Reset()
        {
            _labels->Clear();

            _code->reset(asmjit::ResetPolicy::kSoft);
            _code->attach(_assembler);
        }

        bool BindLabel(Label^ label)
        {
            asmjit::Label realLabel{};

            UInt32 labelId;
            if (_labels->TryGetValue(label, labelId))
            {
                realLabel = asmjit::Label{ labelId };
            }
            else
            {
                realLabel = _assembler->newLabel();
                _labels->Add(label, realLabel.id());
            }

            if (auto res = _assembler->bind(realLabel); res != asmjit::kErrorOk)
            {
                return false;
            }

            return true;
        }

        bool Encode(Instruction^ instr)
        {
            return encodeInstruction(_assembler, _labels, instr);
        }

        System::UIntPtr GetLabelBaseOffset(Label^ label)
        {
            if (label == nullptr)
                return System::UIntPtr((void*)((intptr_t)-1));

            UInt32 labelId;
            if (!_labels->TryGetValue(label, labelId))
                return System::UIntPtr((void*)((intptr_t)-1));

            return System::UIntPtr(_code->labelOffsetFromBase(labelId));
        }

        System::UIntPtr GetLabelOffset(Label^ label)
        {
            if (label == nullptr)
                return System::UIntPtr((void*)((intptr_t)-1));

            UInt32 labelId;
            if (!_labels->TryGetValue(label, labelId))
                return System::UIntPtr((void*)((intptr_t)-1));

            return System::UIntPtr(_code->labelOffset(labelId));
        }

        bool RelocateTo(System::UIntPtr newBaseVA)
        {
            auto va = static_cast<uintptr_t>(newBaseVA.ToUInt64());

            if (auto res = _code->relocateToBase(va); res != asmjit::kErrorOk)
            {
                return false;
            }
            return true;
        }

        array<System::Byte>^ GetData()
        {
            const size_t codeSize = _code->codeSize();

            array<System::Byte>^ res = gcnew array<System::Byte>((int)codeSize);
            if (codeSize == 0)
                return res;

            pin_ptr<uint8_t> ptr = &res[0];
            uint8_t* buf = ptr;

            _code->copyFlattenedData(ptr, codeSize);

            return res;
        }
    };

}
