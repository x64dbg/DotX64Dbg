#include <cstdint>
#include <utility>
#include <vector>

#include "Encoder.Converter.hpp"

namespace Dotx64Dbg {

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
        }

    public:
        ~Encoder()
        {
            delete _assembler;
            delete _code;
        }

        static Encoder^ Create(uintptr_t baseVA)
        {
            return gcnew Encoder(baseVA);
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
            auto op0 = convertOp(instr->GetOperand(0));
            auto op1 = convertOp(instr->GetOperand(1));
            auto op2 = convertOp(instr->GetOperand(2));
            auto op3 = convertOp(instr->GetOperand(3));

            auto mnemonic = convertMnemonic(instr->Id);

            if ((instr->Attribs & Instruction::Attributes::Lock) != Instruction::Attributes::None)
                _assembler->lock();

            if ((instr->Attribs & Instruction::Attributes::Rep) != Instruction::Attributes::None)
                _assembler->rep();

            if ((instr->Attribs & Instruction::Attributes::RepNe) != Instruction::Attributes::None)
                _assembler->repne();

            if ((instr->Attribs & Instruction::Attributes::RepEq) != Instruction::Attributes::None)
                _assembler->repe();

            if ((instr->Attribs & Instruction::Attributes::RepNz) != Instruction::Attributes::None)
                _assembler->repnz();

            switch (instr->Id)
            {
            case Mnemonic::Cmpsb:
                if (_assembler->cmpsb() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Cmpsw:
                if (_assembler->cmpsw() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Cmpsd:
                if (_assembler->cmpsd() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Cmpsq:
                if (_assembler->cmpsq() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Movsb:
                if (_assembler->movsb() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Movsw:
                if (_assembler->movsw() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Movsd:
                if (_assembler->movsd() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Movsq:
                if (_assembler->movsq() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Lodsb:
                if (_assembler->lodsb() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Lodsw:
                if (_assembler->lodsw() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Lodsd:
                if (_assembler->lodsd() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Lodsq:
                if (_assembler->lodsq() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Stosb:
                if (_assembler->stosb() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Stosw:
                if (_assembler->stosw() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Stosd:
                if (_assembler->stosd() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Stosq:
                if (_assembler->stosq() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Scasb:
                if (_assembler->scasb() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Scasw:
                if (_assembler->scasw() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Scasd:
                if (_assembler->scasd() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            case Mnemonic::Scasq:
                if (_assembler->scasq() != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            default:
                if (_assembler->emit(mnemonic, op0, op1, op2, op3) != asmjit::kErrorOk)
                {
                    return false;
                }
                break;
            }

            return true;
        }

        bool RelocateTo(uintptr_t newBaseVA)
        {
            if (auto res = _code->relocateToBase(newBaseVA); res != asmjit::kErrorOk)
            {
                return false;
            }
            return true;
        }

        array<System::Byte>^ GetData()
        {
            const size_t codeSize = _code->codeSize();

            array<System::Byte>^ res = gcnew array<System::Byte>(codeSize);

            pin_ptr<uint8_t> ptr = &res[0];
            uint8_t* buf = ptr;

            _code->copyFlattenedData(ptr, codeSize);

            return res;
        }

    private:
        inline asmjit::Operand convertOp(IOperand^ op)
        {
            if (op->Type == OperandType::Register)
            {
                auto opReg = (Operand::OpReg^)op;
                return convertRegister(opReg->Value);
            }
            else if (op->Type == OperandType::Immediate)
            {
                auto opImm = (Operand::OpImm^)op;
                return asmjit::Imm(opImm->Value);
            }
            else if (op->Type == OperandType::Memory)
            {
                auto opMem = (Operand::OpMem^)op;
                auto mem = asmjit::x86::Mem();
                mem.setBase(convertRegister(opMem->Base));
                mem.setIndex(convertRegister(opMem->Index), opMem->Scale);
                mem.setSegment(convertRegister(opMem->Segment).as<asmjit::x86::SReg>());
                mem.setSize(opMem->Size);
                mem.setOffset(opMem->Displacement);
                return mem;
            }
            else if (op->Type == OperandType::Label)
            {
                auto opLabel = (Label^)op;

                asmjit::Label realLabel{};

                UInt32 labelId;
                if (_labels->TryGetValue(opLabel, labelId))
                {
                    realLabel = asmjit::Label{ labelId };
                }
                else
                {
                    realLabel = _assembler->newLabel();
                    _labels->Add(opLabel, realLabel.id());
                }

                return realLabel;
            }
            return {};
        }
    };

}
