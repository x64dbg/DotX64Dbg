#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include "Register.hpp"
#include "Mnemonic.hpp"
#include "Instruction.Operand.hpp"
#include "Instruction.EFlags.hpp"
#include "Instruction.Meta.hpp"

namespace Dotx64Dbg {

    using namespace System;

    public ref class Instruction
    {
    internal:
        array<IOperand^>^ Operands;
        array<OperandVisibility>^ Visibility;
        array<OperandAccess>^ Access;
        Mnemonic _Id{};
        EFlags _FlagsRead{};
        EFlags _FlagsModified{};
        int _Size{};
        uint64_t _Address{};

    public:
        static initonly int32_t MaxOperands = 8;

    private:

        void Init(Mnemonic mnemonic)
        {
            _Id = mnemonic;

            Operands = gcnew array<IOperand^>(MaxOperands);
            Visibility = gcnew array<OperandVisibility>(MaxOperands);
            Access = gcnew array<OperandAccess>(MaxOperands);

            for (int i = 0; i < MaxOperands; i++)
            {
                Operands[i] = Operand::None;
                Visibility[i] = OperandVisibility::Invalid;
                Access[i] = OperandAccess::None;
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

    internal:
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

    public:
        property uint32_t Size
        {
            uint32_t get()
            {
                return _Size;
            }
        }

        property System::IntPtr Address
        {
            System::IntPtr get()
            {
                return System::IntPtr((long long)_Address);
            }
        }

        property Mnemonic Id
        {
            Mnemonic get()
            {
                return _Id;
            }
        }

        property EFlags FlagsWrite
        {
            EFlags get()
            {
                return _FlagsModified;
            }
        }

        property EFlags FlagsRead
        {
            EFlags get()
            {
                return _FlagsRead;
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
            if (index < 0 || index >= MaxOperands)
                return nullptr;

            return Operands[index];
        }

        OperandAccess GetOperandAccess(int index)
        {
            if (index < 0 || index >= MaxOperands)
                return OperandAccess::None;

            return Access[index];
        }

        OperandVisibility GetOperandVisibility(int index)
        {
            if (index < 0 || index >= MaxOperands)
                return OperandVisibility::Invalid;

            return Visibility[index];
        }

        System::String^ ToString() override;

    internal:
        void SetOperand(int index, IOperand^ op)
        {
            if (index < 0 || index >= MaxOperands)
                return;

            Operands[index] = op;
        }

        void SetOperand(int index, IOperand^ op, OperandAccess access, OperandVisibility vis)
        {
            if (index < 0 || index >= MaxOperands)
                return;

            Operands[index] = op;
            Visibility[index] = vis;
            Access[index] = access;
        }

    };
}
