#include <cstdint>
#include <utility>
#include <vector>
#include <string>

#include "Encoder.Converter.hpp"

namespace Dotx64Dbg::Internal {

    bool encodeInstruction(asmjit::x86::Assembler* a,
        System::Collections::Generic::Dictionary<Label^, UInt32>^ labels,
        Instruction::Attributes attrib,
        Mnemonic mnemonic,
        IOperand^ op0_,
        IOperand^ op1_,
        IOperand^ op2_,
        IOperand^ op3_
    );
}
