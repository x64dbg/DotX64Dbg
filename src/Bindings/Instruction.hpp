#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include "Register.hpp"
#include "Mnemonic.hpp"
#include "Instruction.Meta.hpp"
#include "Instruction.Operand.hpp"
#include "Instruction.EFlags.hpp"

namespace Dotx64Dbg {

    using namespace System;

    public ref class Instruction
    {
        array<IOperand^>^ Operands;
        array<OperandVisibility>^ Visibility;
        array<OperandAccess>^ Access;
        InstructionMeta^ _Meta;
        Mnemonic _Id;

    private:
        void Init(Mnemonic mnemonic)
        {
            _Id = mnemonic;
            _Meta = InstructionMetaData::get(Id);

            Operands = gcnew array<IOperand^>(5);
            Visibility = gcnew array<OperandVisibility>(5);
            Access = gcnew array<OperandAccess>(5);

            for (int i = 0; i < 5; i++)
            {
                Operands[i] = _Meta->Operands[i];
                Visibility[i] = _Meta->Visibility[i];
                Access[i] = _Meta->Access[i];
            }
        }

    public:
        [System::Flags]
        enum class Attributes
        {
            None = 0,
            Lock = (1 << 0),
            Rep = (1 << 1),
            RepNe = (1 << 2),
            RepEq = (1 << 3),
            RepNz = (1 << 4),
        };

        Instruction()
        {
            Init(Mnemonic::Invalid);
        }

        Instruction(Attributes attribs, Mnemonic id)
        {
            Init(id);
            Attribs = attribs;
        }

        Instruction(Attributes attribs, Mnemonic id, IOperand^ op0)
        {
            Init(id);
            Attribs = attribs;
            SetOperand(0, op0);
        }

        Instruction(Attributes attribs, Mnemonic id, IOperand^ op0, IOperand^ op1)
        {
            Init(id);
            Attribs = attribs;
            SetOperand(0, op0);
            SetOperand(1, op1);
        }

        Instruction(Attributes attribs, Mnemonic id, IOperand^ op0, IOperand^ op1, IOperand^ op2)
        {
            Init(id);
            Attribs = attribs;
            SetOperand(0, op0);
            SetOperand(1, op1);
            SetOperand(2, op2);
        }

        Instruction(Attributes attribs, Mnemonic id, IOperand^ op0, IOperand^ op1, IOperand^ op2, IOperand^ op3)
        {
            Init(id);
            Attribs = attribs;
            SetOperand(0, op0);
            SetOperand(1, op1);
            SetOperand(2, op2);
            SetOperand(3, op3);
        }

        Instruction(Mnemonic id)
        {
            Init(id);
        }

        Instruction(Mnemonic id, IOperand^ op0)
        {
            Init(id);
            SetOperand(0, op0);
        }

        Instruction(Mnemonic id, IOperand^ op0, IOperand^ op1)
        {
            Init(id);
            SetOperand(0, op0);
            SetOperand(1, op1);
        }

        Instruction(Mnemonic id, IOperand^ op0, IOperand^ op1, IOperand^ op2)
        {
            Init(id);
            SetOperand(0, op0);
            SetOperand(1, op1);
            SetOperand(2, op2);
        }

        Instruction(Mnemonic id, IOperand^ op0, IOperand^ op1, IOperand^ op2, IOperand^ op3)
        {
            Init(id);
            SetOperand(0, op0);
            SetOperand(1, op1);
            SetOperand(2, op2);
            SetOperand(3, op3);
        }

        property int Size;
        property uint64_t Address;

        property Mnemonic Id
        {
            Mnemonic get()
            {
                return _Id;
            }
        }

        property InstructionMeta^ Meta
        {
            InstructionMeta^ get()
            {
                return _Meta;
            }
        }

        property EFlags FlagsWrite
        {
            EFlags get()
            {
                return (EFlags)_Meta->FlagsModified;
            }
        }

        property EFlags FlagsRead
        {
            EFlags get()
            {
                return (EFlags)_Meta->FlagsRead;
            }
        }

        property EFlags FlagsUndefined
        {
            EFlags get()
            {
                return (EFlags)_Meta->FlagsUndefined;
            }
        }

        property Attributes Attribs;

        property bool IsControlFlow
        {
            bool get()
            {
                return InstructionMetaData::isControlFlow(Id);
            }
        }

        property bool IsConditionalControlFlow
        {
            bool get()
            {
                return InstructionMetaData::isCondControlFlow(Id);
            }
        }

        property bool HasCondition
        {
            bool get()
            {
                return FlagsRead != EFlags::None;
            }
        }

        property bool IsCall
        {
            bool get()
            {
                return InstructionMetaData::IsCall(Id);
            }
        }

        property bool IsJmp
        {
            bool get()
            {
                return Id == Mnemonic::Jmp;
            }
        }

        property bool IsRet
        {
            bool get()
            {
                return InstructionMetaData::isRet(Id);
            }
        }

        IOperand^ GetOperand(int index)
        {
            if (index >= Operands->Length)
                return nullptr;

            return Operands[index];
        }

        OperandAccess GetOperandAccess(int index)
        {
            if (index >= Operands->Length)
                return OperandAccess::None;

            return Access[index];
        }


        OperandVisibility GetOperandVisibility(int index)
        {
            if (index >= Visibility->Length)
                return OperandVisibility::Invalid;

            return Visibility[index];
        }

        void SetOperandAccess(int index, OperandAccess access)
        {
            Access[index] = access;
        }

        void SetOperandVisibility(int index, OperandVisibility vis)
        {
            Visibility[index] = vis;
        }

        void SetOperand(int index, IOperand^ op)
        {
            Operands[index] = op;
        }

        void SetOperand(int index, IOperand^ op, OperandAccess access, OperandVisibility vis)
        {
            Operands[index] = op;
            Visibility[index] = vis;
            Access[index] = access;
        }

        System::String^ ToString() override;
    };


}
