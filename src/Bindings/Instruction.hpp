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

            /// <summary>
            /// Register  size in bits.
            /// </summary>
            virtual property int Size
            {
                int get()
                {
                    return RegisterGetSize(_Value);
                }
            }

            /// <summary>
            /// This is equivalent to checking against Register.None
            /// </summary>
            property bool IsValid
            {
                bool get()
                {
                    return _Value != Register::None;
                }
            }

            /// <summary>
            /// The register id.
            /// </summary>
            property Register Value
            {
                Register get()
                {
                    return _Value;
                }
            }

            property RegisterClass Class
            {
                RegisterClass get()
                {
                    return RegisterGetClass(_Value);
                }
            }

            /// <summary>
            /// This will be true if the register class is one of the general purpose types.
            /// </summary>
            property bool IsGp
            {
                bool get()
                {
                    switch (Class)
                    {
                    case RegisterClass::Gp8:
                    case RegisterClass::Gp16:
                    case RegisterClass::Gp32:
                    case RegisterClass::Gp64:
                        return true;
                    }
                    return false;
                }
            }

            /// <summary>
            /// Retrieves the root register id, will be Register.None if none.
            /// If the register is ax it would result eax on 32 bit and rax on 64 bit.
            /// </summary>
            property Register RootId
            {
                Register get()
                {
                    return RegisterGetRoot(_Value);
                }
            }

            /// <summary>
            /// Equivalent to RootId != Register.None
            /// </summary>
            property bool HasRoot
            {
                bool get()
                {
                    return RegisterGetRoot(_Value) != Register::None;
                }
            }

            /// <see cref="GetRoot" />
            property OpReg^ Root
            {
                OpReg^ get()
                {
                    return GetRoot();
                }
            }

            /// <summary>
            /// Retrieves the root register.
            /// If the register is ax it would result eax on 32 bit and rax on 64 bit.
            /// </summary>
            OpReg^ GetRoot()
            {
                return gcnew OpReg(RegisterGetRoot(_Value));
            }

            /// <summary>
            /// Retrieves the parent register id, will be Register.None if none.
            /// </summary>
            property Register ParentId
            {
                Register get()
                {
                    return RegisterGetParent(_Value);
                }
            }

            /// <summary>
            /// Equivalent to RootId != Register.None
            /// </summary>
            property bool HasParent
            {
                bool get()
                {
                    return RegisterGetParent(_Value) != Register::None;
                }
            }

            /// <see cref="GetParent" />
            property OpReg^ Parent
            {
                OpReg^ get()
                {
                    return GetParent();
                }
            }

            /// <summary>
            /// If the register is part of another register this will return the parent.
            /// So in case the register is ax the parent would be eax and for eax it would be rax on 64 bit.
            /// <returns>New OpReg, this will never result null.</returns>
            /// </summary>
            OpReg^ GetParent()
            {
                return gcnew OpReg(RegisterGetParent(_Value));
            }

            /// <see cref="GetPosition" />
            property int Position
            {
                int get()
                {
                    return GetPosition();
                }
            }

            /// <summary>
            /// This returns number of bits offset from the root register.
            /// In case of Register.Ax this would result 8.
            /// <returns>Returns number of bits at where the register is located in the root register</returns>
            /// </summary>
            int GetPosition()
            {
                return RegisterGetOffsetForRoot(_Value);
            }

            /// <summary>
            /// A small helper to determine if the parent register would be mutated
            /// if the register is modified.
            /// This is primarily useful for the 64 bit architecture where modifying a register
            /// such as eax would result in the upper 32 bit of rax being modified/mutated.
            /// </summary>
            property bool MutatesParent
            {
                bool get()
                {
#ifdef _M_AMD64
                    if (IsGp && Size == 32)
                        return true;
#endif
                    return false;
                }
            }

            System::String^ ToString() override
            {
                return gcnew System::String(RegisterGetName(_Value));
            }
        };

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
