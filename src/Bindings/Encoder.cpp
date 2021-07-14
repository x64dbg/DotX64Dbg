#include <cstdint>
#include <utility>

#include "Encoder.Converter.hpp"

namespace Dotx64Dbg {

    public ref class Encoder
    {
        asmjit::CodeHolder* _code{};
        asmjit::x86::Assembler* _assembler{};

    private:
        Encoder(uintptr_t baseVA)
        {
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

        bool Encode(Instruction^ instr)
        {
            auto op0 = convertOp(instr->GetOperand(0));
            auto op1 = convertOp(instr->GetOperand(1));
            auto op2 = convertOp(instr->GetOperand(2));
            auto op3 = convertOp(instr->GetOperand(3));

            auto mnemonic = convertMnemonic(instr->Id);
            if (_assembler->emit(mnemonic, op0, op1, op2, op3) != asmjit::kErrorOk)
            {
                return false;
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

    };

}
