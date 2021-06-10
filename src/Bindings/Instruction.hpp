#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include "Register.hpp"
#include "Mnemonic.hpp"

namespace Dotx64Dbg {

    using namespace System;

    public enum class OperandType
    {
        None = 0,
        Immediate,
        Register,
        Memory,
    };

    public enum class OperandVisibility
    {
        Invalid = 0,
        Explicit,
        Implicit,
        Hidden,
    };

    [System::Flags]
    public enum class OperandAccess
    {
        Read = (1 << 0),
        Write = (1 << 1),
    };

    [System::Flags]
    public enum class EFlags
    {
        Cf = (1 << 0),
        Pf = (1 << 2),
        Af = (1 << 4),
        Zf = (1 << 6),
        Sf = (1 << 7),
        Tf = (1 << 8),
        If = (1 << 9),
        Df = (1 << 10),
        Of = (1 << 11),
        Iopl = (1 << 12),
        Nt = (1 << 14),
        Rf = (1 << 16),
        Vm = (1 << 17),
        Ac = (1 << 18),
        Vif = (1 << 19),
        Vip = (1 << 20),
        Id = (1 << 21),
        C0 = (1 << 22),
        C1 = (1 << 23),
        C2 = (1 << 24),
        C3 = (1 << 25),
    };

    public interface class IOperand
    {
    public:
        virtual property OperandVisibility Visibility;
        virtual property OperandAccess Access;
        virtual property OperandType Type
        {
            OperandType get();
        }
        virtual property int Size
        {
            int get();
        }
    };

    public ref class Operand
    {

    public:
        ref class NoneType : public IOperand
        {
        public:
            virtual property OperandVisibility Visibility;
            virtual property OperandAccess Access;
            virtual property OperandType Type
            {
                OperandType get()
                {
                    return OperandType::None;
                }
            }
            virtual property int Size
            {
                int get()
                {
                    return 0;
                }
            }
        };

    private:
        static NoneType^ _None = gcnew NoneType();

    public:
        static property NoneType^ None {
            NoneType^ get()
            {
                return _None;
            }
        }

        // Immediate
        ref class OpImm : public IOperand
        {
        public:
            OpImm()
            {
                Value = 0;
            }

            OpImm(int64_t value)
            {
                Value = value;
            }

            virtual property OperandVisibility Visibility;
            virtual property OperandAccess Access;

            virtual property OperandType Type
            {
                OperandType get()
                {
                    return OperandType::Immediate;
                }
            }

            virtual property int Size
            {
                int get()
                {
                    uint64_t val = static_cast<uint64_t>(std::abs(Value));
                    int res = 0;
                    do
                    {
                        res++;
                    } while (val >>= 8);
                    return res * 8;
                }
            }

            property int64_t Value;

            System::String^ ToString() override
            {
                char temp[128];
                if (Value < 0)
                    snprintf(temp, sizeof(temp), "-0x%llx", std::abs(Value));
                else
                    snprintf(temp, sizeof(temp), "0x%llx", Value);
                return gcnew System::String(temp);
            }
        };

        static OpImm^ Imm(int64_t value)
        {
            return gcnew OpImm(value);
        }

        // Register
        ref class OpReg : public IOperand
        {
            Register _Value;

        public:
            OpReg()
            {
                _Value = Register::None;
            }

            OpReg(Register reg)
            {
                _Value = reg;
            }

            virtual property OperandVisibility Visibility;
            virtual property OperandAccess Access;

            virtual property OperandType Type
            {
                OperandType get()
                {
                    return OperandType::Register;
                }
            }

            virtual property int Size
            {
                int get()
                {
                    return RegisterGetSize(_Value);
                }
            }

            property Register Value
            {
                Register get()
                {
                    return _Value;
                }
            }

            System::String^ ToString() override
            {
                return gcnew System::String(RegisterGetName(_Value));
            }
        };

        static OpReg^ Reg(Register reg)
        {
            return gcnew OpReg(reg);
        }

        // Memory
        ref class OpMem : public IOperand
        {
            int MemSize = 0;

        public:
            OpMem()
            {
            }

            OpMem(int size, Register seg, Register base, Register index, int32_t scale, int64_t disp)
            {
                Size = size;
                Segment = seg;
                Base = base;
                Index = index;
                Scale = scale;
                Displacement = disp;
            }

            OpMem(int size, Register base, Register index, int32_t scale, int64_t disp)
            {
                Size = size;
                Segment = Register::Ds;
                Base = base;
                Index = index;
                Scale = scale;
                Displacement = disp;
            }

            virtual property OperandVisibility Visibility;
            virtual property OperandAccess Access;
            virtual property OperandType Type
            {
                OperandType get()
                {
                    return OperandType::Memory;
                }
            }

            virtual property int Size
            {
                int get()
                {
                    return MemSize;
                }
                void set(int value)
                {
                    MemSize = value;
                }
            }

            property Register Segment;
            property Register Base;
            property Register Index;
            property int32_t Scale;
            property int64_t Displacement;

            System::String^ ToString() override
            {
                char temp[128];
                int p = 0;

                switch (Size)
                {
                case 8:
                    p += snprintf(temp + p, sizeof(temp) - p, "byte ptr [");
                    break;
                case 16:
                    p += snprintf(temp + p, sizeof(temp) - p, "word ptr [");
                    break;
                case 32:
                    p += snprintf(temp + p, sizeof(temp) - p, "dword ptr [");
                    break;
                case 64:
                    p += snprintf(temp + p, sizeof(temp) - p, "qword ptr [");
                    break;
                }

                if (Segment != Register::Ds && Segment != Register::Cs)
                {
                    p += snprintf(temp + p, sizeof(temp) - p, "%s:", RegisterGetName(Segment));
                }

                if (Base != Register::None)
                {
                    p += snprintf(temp + p, sizeof(temp) - p, "%s", RegisterGetName(Base));
                }

                if (Index != Register::None)
                {
                    if (Base != Register::None)
                        p += snprintf(temp + p, sizeof(temp) - p, "+");

                    p += snprintf(temp + p, sizeof(temp) - p, "%s", RegisterGetName(Index));
                }

                if (Scale > 0)
                {
                    if (Index != Register::None)
                        p += snprintf(temp + p, sizeof(temp) - p, "*");

                    p += snprintf(temp + p, sizeof(temp) - p, "%d", Scale);
                }

                if (Displacement > 0)
                {
                    if (Base != Register::None || Index != Register::None)
                    {
                        if (Displacement < 0)
                            p += snprintf(temp + p, sizeof(temp) - p, "-");
                        else
                            p += snprintf(temp + p, sizeof(temp) - p, "+");
                    }
                    p += snprintf(temp + p, sizeof(temp) - p, "%llu", std::abs(Displacement));
                }

                p += snprintf(temp + p, sizeof(temp) - p, "]");

                return gcnew System::String(temp);
            }
        };

        // Byte
        //////////////////////////////////////////////////////////////////////////
        static OpMem^ byte_ptr(Register base)
        {
            return gcnew OpMem(8, base, Register::None, 0, 0);
        }

        static OpMem^ byte_ptr(Register base, int64_t disp)
        {
            return gcnew OpMem(8, base, Register::None, 0, disp);
        }

        static OpMem^ byte_ptr(Register base, Register index)
        {
            return gcnew OpMem(8, base, index, 0, 0);
        }

        static OpMem^ byte_ptr(Register base, Register index, int64_t disp)
        {
            return gcnew OpMem(8, base, index, 0, disp);
        }

        static OpMem^ byte_ptr(Register base, Register index, int32_t scale, int64_t disp)
        {
            return gcnew OpMem(8, base, index, scale, disp);
        }

        // Word
        //////////////////////////////////////////////////////////////////////////
        static OpMem^ word_ptr(Register base)
        {
            return gcnew OpMem(16, base, Register::None, 0, 0);
        }

        static OpMem^ word_ptr(Register base, int64_t disp)
        {
            return gcnew OpMem(16, base, Register::None, 0, disp);
        }

        static OpMem^ word_ptr(Register base, Register index)
        {
            return gcnew OpMem(16, base, index, 0, 0);
        }

        static OpMem^ word_ptr(Register base, Register index, int64_t disp)
        {
            return gcnew OpMem(16, base, index, 0, disp);
        }

        static OpMem^ word_ptr(Register base, Register index, int32_t scale, int64_t disp)
        {
            return gcnew OpMem(16, base, index, scale, disp);
        }

        // Dword
        //////////////////////////////////////////////////////////////////////////
        static OpMem^ dword_ptr(Register base)
        {
            return gcnew OpMem(32, base, Register::None, 0, 0);
        }

        static OpMem^ dword_ptr(Register base, int64_t disp)
        {
            return gcnew OpMem(32, base, Register::None, 0, disp);
        }

        static OpMem^ dword_ptr(Register base, Register index)
        {
            return gcnew OpMem(32, base, index, 0, 0);
        }

        static OpMem^ dword_ptr(Register base, Register index, int64_t disp)
        {
            return gcnew OpMem(32, base, index, 0, disp);
        }

        static OpMem^ dword_ptr(Register base, Register index, int32_t scale, int64_t disp)
        {
            return gcnew OpMem(32, base, index, scale, disp);
        }

        // Qword
        //////////////////////////////////////////////////////////////////////////
        static OpMem^ qword_ptr(Register base)
        {
            return gcnew OpMem(64, base, Register::None, 0, 0);
        }

        static OpMem^ qword_ptr(Register base, int64_t disp)
        {
            return gcnew OpMem(64, base, Register::None, 0, disp);
        }

        static OpMem^ qword_ptr(Register base, Register index)
        {
            return gcnew OpMem(64, base, index, 0, 0);
        }

        static OpMem^ qword_ptr(Register base, Register index, int64_t disp)
        {
            return gcnew OpMem(64, base, index, 0, disp);
        }

        static OpMem^ qword_ptr(Register base, Register index, int32_t scale, int64_t disp)
        {
            return gcnew OpMem(64, base, index, scale, disp);
        }
    };

    public ref class Instruction
    {
        array<IOperand^>^ Operands;

    public:
        Instruction()
        {
            Id = Mnemonic::Invalid;
            Operands = gcnew array<IOperand^>{ Operand::None, Operand::None, Operand::None, Operand::None, Operand::None };
        }

        Instruction(Mnemonic id)
        {
            Id = id;
            Operands = gcnew array<IOperand^>{ Operand::None, Operand::None, Operand::None, Operand::None, Operand::None };
        }

        Instruction(Mnemonic id, IOperand^ op0)
        {
            Id = id;
            Operands = gcnew array<IOperand^>{ op0, Operand::None, Operand::None, Operand::None, Operand::None };
        }

        Instruction(Mnemonic id, IOperand^ op0, IOperand^ op1)
        {
            Id = id;
            Operands = gcnew array<IOperand^>{ op0, op1, Operand::None, Operand::None, Operand::None };
        }

        Instruction(Mnemonic id, IOperand^ op0, IOperand^ op1, IOperand^ op2)
        {
            Id = id;
            Operands = gcnew array<IOperand^>{ op0, op1, op2, Operand::None, Operand::None };
        }

        Instruction(Mnemonic id, IOperand^ op0, IOperand^ op1, IOperand^ op2, IOperand^ op3)
        {
            Id = id;
            Operands = gcnew array<IOperand^>{ op0, op1, op2, op3, Operand::None };
        }

        property int Size;
        property uint64_t Address;
        property Mnemonic Id;
        property EFlags FlagsWrite;
        property EFlags FlagsRead;
        IOperand^ GetOperand(int index)
        {
            if (index >= Operands->Length)
                return nullptr;

            return Operands[index];
        }

        void SetOperand(int index, IOperand^ op)
        {
            if (index >= Operands->Length)
                return;

            Operands[index] = op;
        }

        System::String^ ToString() override;
    };


}
