#include "Instruction.hpp"
#include <cstdio>

namespace Dotx64Dbg {

    System::String^ Instruction::ToString()
    {
        char temp[128]{};

        int p = 0;
        p += snprintf(temp + p, sizeof(temp) - p, "%s", MnemonicGetString(Id));

        System::String^ ins = gcnew System::String(temp);

        for (int i = 0; i < Operands->Length; i++)
        {
            IOperand^ op = GetOperand(i);
            if (op == nullptr || op->Type == OperandType::None)
                break;
            if (GetOperandVisibility(i) == OperandVisibility::Hidden)
                continue;
            if (i > 0)
                ins = ins->Concat(ins, gcnew System::String(", "));
            else
                ins = ins->Concat(ins, gcnew System::String(" "));

            ins = ins->Concat(ins, op->ToString());
        }

        return ins;
    }

}
