#pragma once

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
        Label,
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
        None = 0,
        Read = (1 << 0),
        Write = (1 << 1),
        ReadWrite = Read | Write,
    };

    public interface class IOperand
    {
    public:
        virtual property OperandType Type
        {
            OperandType get();
        }
        virtual property int Size
        {
            int get();
        }
    };

    public ref class Label : public IOperand
    {
        int _id = -1;

    public:
        property int Value
        {
            int get()
            {
                return _id;
            }
        }

        Label()
        {
        }

        Label(int id)
            : _id(id)
        {
        }

        virtual property OperandType Type
        {
            OperandType get()
            {
                return OperandType::Label;
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

    public ref class Operand
    {

    public:
        ref class NoneType : public IOperand
        {
        public:
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
        ref class Immediate : public IOperand
        {
        public:
            Immediate()
            {
                Value = 0;
            }

            Immediate(int64_t value)
            {
                Value = value;
            }

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
                snprintf(temp, sizeof(temp), "0x%llx", Value);
                return gcnew System::String(temp);
            }
        };

        // Register
        ref class Register : public IOperand
        {
            Registers::Id _Value;

        public:
            Register()
            {
                _Value = Registers::Id::None;
            }

            Register(Registers::Id reg)
            {
                _Value = reg;
            }

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
                    return Registers::GetSize(_Value);
                }
            }

            /// <summary>
            /// This is equivalent to checking against Register.None
            /// </summary>
            property bool IsValid
            {
                bool get()
                {
                    return _Value != Registers::Id::None;
                }
            }

            /// <summary>
            /// The register id.
            /// </summary>
            property Registers::Id Value
            {
                Registers::Id get()
                {
                    return _Value;
                }
            }

            property Registers::Class Class
            {
                Registers::Class get()
                {
                    return Registers::GetClass(_Value);
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
                    case Registers::Class::Gp8:
                    case Registers::Class::Gp16:
                    case Registers::Class::Gp32:
                    case Registers::Class::Gp64:
                        return true;
                    }
                    return false;
                }
            }

            /// <summary>
            /// Retrieves the root register id, will be Register.None if none.
            /// If the register is ax it would result eax on 32 bit and rax on 64 bit.
            /// </summary>
            property Registers::Id RootId
            {
                Registers::Id get()
                {
                    return Registers::GetRoot(_Value);
                }
            }

            /// <summary>
            /// Equivalent to RootId != Register.None
            /// </summary>
            property bool HasRoot
            {
                bool get()
                {
                    return Registers::GetRoot(_Value) != Registers::Id::None;
                }
            }

            /// <see cref="GetRoot" />
            property Register^ Root
            {
                Register^ get()
                {
                    return GetRoot();
                }
            }

            /// <summary>
            /// Retrieves the root register.
            /// If the register is ax it would result eax on 32 bit and rax on 64 bit.
            /// </summary>
            Register^ GetRoot()
            {
                return gcnew Register(Registers::GetRoot(_Value));
            }

            /// <summary>
            /// Retrieves the parent register id, will be Register.None if none.
            /// </summary>
            property Registers::Id ParentId
            {
                Registers::Id get()
                {
                    return Registers::GetParent(_Value);
                }
            }

            /// <summary>
            /// Equivalent to RootId != Register.None
            /// </summary>
            property bool HasParent
            {
                bool get()
                {
                    return Registers::GetParent(_Value) != Registers::Id::None;
                }
            }

            /// <see cref="GetParent" />
            property Register^ Parent
            {
                Register^ get()
                {
                    return GetParent();
                }
            }

            /// <summary>
            /// If the register is part of another register this will return the parent.
            /// So in case the register is ax the parent would be eax and for eax it would be rax on 64 bit.
            /// <returns>New OpReg, this will never result null.</returns>
            /// </summary>
            Register^ GetParent()
            {
                return gcnew Register(Registers::GetParent(_Value));
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
                return Registers::GetOffsetForRoot(_Value);
            }

            /// <summary>
            /// Gets the index of the register within its category so for Gp it would be 0 to 15, Xmm 0 to 31
            /// </summary>
            /// <returns>Index of register</returns>
            int GetIndex()
            {
                return Registers::GetIndex(_Value);
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
                return gcnew System::String(Registers::GetName(_Value));
            }
        };

        // Memory
        ref class Memory : public IOperand
        {
            int MemSize = 0;

        public:
            Memory()
            {
            }

            Memory(int size, Registers::Id seg, Registers::Id base, Registers::Id index, int32_t scale, int64_t disp)
            {
                Size = size;
                Segment = seg;
                Base = base;
                Index = index;
                Scale = scale;
                Displacement = disp;
            }

            Memory(int size, Registers::Id base, Registers::Id index, int32_t scale, int64_t disp)
            {
                Size = size;
                Segment = Registers::Id::Ds;
                Base = base;
                Index = index;
                Scale = scale;
                Displacement = disp;
            }

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

            property Registers::Id Segment;
            property Registers::Id Base;
            property Registers::Id Index;
            property int32_t Scale;
            property int64_t Displacement;

            Memory^ WithSegment(Registers::Id reg)
            {
                Segment = reg;
                return this;
            }

            Memory^ WithSegment(Register^ reg)
            {
                Segment = reg->Value;
                return this;
            }

            Memory^ WithBase(Registers::Id reg)
            {
                Base = reg;
                return this;
            }
            Memory^ WithBase(Register^ reg)
            {
                Base = reg->Value;
                return this;
            }

            Memory^ WithIndex(Registers::Id reg)
            {
                Index = reg;
                return this;
            }
            Memory^ WithIndex(Register^ reg)
            {
                Index = reg->Value;
                return this;
            }

            Memory^ WithScale(int32_t scale)
            {
                Scale = scale;
                return this;
            }

            Memory^ WithDisplacement(int64_t disp)
            {
                Displacement = disp;
                return this;
            }

            System::String^ ToString() override
            {
                char temp[128];
                int p = 0;

                switch (Size)
                {
                case 8:
                    p += snprintf(temp + p, sizeof(temp) - p, "byte ptr ");
                    break;
                case 16:
                    p += snprintf(temp + p, sizeof(temp) - p, "word ptr ");
                    break;
                case 32:
                    p += snprintf(temp + p, sizeof(temp) - p, "dword ptr ");
                    break;
                case 64:
                    p += snprintf(temp + p, sizeof(temp) - p, "qword ptr ");
                    break;
                case 80:
                    p += snprintf(temp + p, sizeof(temp) - p, "tword ptr ");
                    break;
                case 128:
                    p += snprintf(temp + p, sizeof(temp) - p, "xmmword ptr ");
                    break;
                case 256:
                    p += snprintf(temp + p, sizeof(temp) - p, "ymmword ptr ");
                    break;
                case 512:
                    p += snprintf(temp + p, sizeof(temp) - p, "zmmword ptr ");
                    break;
                }

                if (Segment != Registers::Id::Ds && Segment != Registers::Id::Cs)
                {
                    p += snprintf(temp + p, sizeof(temp) - p, "%s:", Registers::GetName(Segment));
                }

                p += snprintf(temp + p, sizeof(temp) - p, "[");

                if (Base != Registers::Id::None)
                {
                    p += snprintf(temp + p, sizeof(temp) - p, "%s", Registers::GetName(Base));
                }

                if (Index != Registers::Id::None)
                {
                    if (Base != Registers::Id::None)
                        p += snprintf(temp + p, sizeof(temp) - p, "+");

                    p += snprintf(temp + p, sizeof(temp) - p, "%s", Registers::GetName(Index));
                }

                if (Scale > 0)
                {
                    if (Index != Registers::Id::None)
                        p += snprintf(temp + p, sizeof(temp) - p, "*");

                    p += snprintf(temp + p, sizeof(temp) - p, "%d", Scale);
                }

                if (Displacement > 0)
                {
                    auto val = Displacement;
                    if (Base != Registers::Id::None || Index != Registers::Id::None)
                    {
                        if (val < 0)
                        {
                            p += snprintf(temp + p, sizeof(temp) - p, "-");
                            val = -val;
                        }
                        else
                        {
                            p += snprintf(temp + p, sizeof(temp) - p, "+");
                        }
                    }
                    p += snprintf(temp + p, sizeof(temp) - p, "%llu", val);
                }

                p += snprintf(temp + p, sizeof(temp) - p, "]");

                return gcnew System::String(temp);
            }
        };
    };

}
