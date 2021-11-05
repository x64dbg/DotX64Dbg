#pragma once

#include "Mnemonic.hpp"
#include "Instruction.Operand.hpp"
#include "Instruction.Operands.hpp"
#include "Instruction.EFlags.hpp"

namespace Dotx64Dbg {

    ref class InstructionMetaData
    {
    public:

        static inline bool isControlFlow(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Call:
            case Mnemonic::Ret:
            case Mnemonic::Iret:
            case Mnemonic::Iretd:
            case Mnemonic::Iretq:
            case Mnemonic::Jmp:
            case Mnemonic::Jb:
            case Mnemonic::Jbe:
            case Mnemonic::Jcxz:
            case Mnemonic::Jecxz:
            case Mnemonic::Jknzd:
            case Mnemonic::Jkzd:
            case Mnemonic::Jl:
            case Mnemonic::Jle:
            case Mnemonic::Jnb:
            case Mnemonic::Jnbe:
            case Mnemonic::Jnl:
            case Mnemonic::Jnle:
            case Mnemonic::Jno:
            case Mnemonic::Jnp:
            case Mnemonic::Jns:
            case Mnemonic::Jnz:
            case Mnemonic::Jo:
            case Mnemonic::Jp:
            case Mnemonic::Jrcxz:
            case Mnemonic::Js:
            case Mnemonic::Jz:
            case Mnemonic::Loop:
            case Mnemonic::Loope:
            case Mnemonic::Loopne:
                return true;
            }
            return false;
        }

        static inline bool isLoop(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Loop:
            case Mnemonic::Loope:
            case Mnemonic::Loopne:
                return true;
            }
            return false;
        }

        static inline bool isCondControlFlow(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Jb:
            case Mnemonic::Jbe:
            case Mnemonic::Jcxz:
            case Mnemonic::Jecxz:
            case Mnemonic::Jknzd:
            case Mnemonic::Jkzd:
            case Mnemonic::Jl:
            case Mnemonic::Jle:
            case Mnemonic::Jnb:
            case Mnemonic::Jnbe:
            case Mnemonic::Jnl:
            case Mnemonic::Jnle:
            case Mnemonic::Jno:
            case Mnemonic::Jnp:
            case Mnemonic::Jns:
            case Mnemonic::Jnz:
            case Mnemonic::Jo:
            case Mnemonic::Jp:
            case Mnemonic::Jrcxz:
            case Mnemonic::Js:
            case Mnemonic::Jz:
                return true;
            }
            return false;
        }

        static inline bool IsCall(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Call:
                return true;
            }
            return false;
        }

        static inline bool isRet(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Ret:
            case Mnemonic::Iret:
            case Mnemonic::Iretd:
            case Mnemonic::Iretq:
                return true;
            }
            return false;
        }
    };

}
