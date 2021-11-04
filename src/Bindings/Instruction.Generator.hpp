#pragma once

#include "Instruction.hpp"

namespace Dotx64Dbg {

    public ref class InstructionGenerator
    {
    public:
        static Instruction^ Generate(Mnemonic mnemonic);

        static Instruction^ Generate(Mnemonic mnemonic,
            IOperand^ op0);

        static Instruction^ Generate(Mnemonic mnemonic,
            IOperand^ op0,
            IOperand^ op1);

        static Instruction^ Generate(Mnemonic mnemonic,
            IOperand^ op0,
            IOperand^ op1,
            IOperand^ op2);

        static Instruction^ Generate(Mnemonic mnemonic,
            IOperand^ op0,
            IOperand^ op1,
            IOperand^ op2,
            IOperand^ op3);

        static Instruction^ Generate(Instruction::Attributes attribs,
            Mnemonic mnemonic);

        static Instruction^ Generate(Instruction::Attributes attribs,
            Mnemonic mnemonic,
            IOperand^ op0);

        static Instruction^ Generate(Instruction::Attributes attribs,
            Mnemonic mnemonic,
            IOperand^ op0,
            IOperand^ op1);

        static Instruction^ Generate(Instruction::Attributes attribs,
            Mnemonic mnemonic,
            IOperand^ op0,
            IOperand^ op1,
            IOperand^ op2);

        static Instruction^ Generate(Instruction::Attributes attribs,
            Mnemonic mnemonic,
            IOperand^ op0,
            IOperand^ op1,
            IOperand^ op2,
            IOperand^ op3);
    };

}
