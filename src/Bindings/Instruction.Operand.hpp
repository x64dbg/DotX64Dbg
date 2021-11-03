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
        ref class Register : public IOperand
        {
            RegisterId _Value;

        public:
            Register()
            {
                _Value = RegisterId::None;
            }

            Register(RegisterId reg)
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
                    return _Value != RegisterId::None;
                }
            }

            /// <summary>
            /// The register id.
            /// </summary>
            property RegisterId Value
            {
                RegisterId get()
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
            property RegisterId RootId
            {
                RegisterId get()
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
                    return RegisterGetRoot(_Value) != RegisterId::None;
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
                return gcnew Register(RegisterGetRoot(_Value));
            }

            /// <summary>
            /// Retrieves the parent register id, will be Register.None if none.
            /// </summary>
            property RegisterId ParentId
            {
                RegisterId get()
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
                    return RegisterGetParent(_Value) != RegisterId::None;
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
                return gcnew Register(RegisterGetParent(_Value));
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
        ref class Memory : public IOperand
        {
            int MemSize = 0;

        public:
            Memory()
            {
            }

            Memory(int size, RegisterId seg, RegisterId base, RegisterId index, int32_t scale, int64_t disp)
            {
                Size = size;
                Segment = seg;
                Base = base;
                Index = index;
                Scale = scale;
                Displacement = disp;
            }

            Memory(int size, RegisterId base, RegisterId index, int32_t scale, int64_t disp)
            {
                Size = size;
                Segment = RegisterId::Ds;
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

            property RegisterId Segment;
            property RegisterId Base;
            property RegisterId Index;
            property int32_t Scale;
            property int64_t Displacement;

            Memory^ WithSegment(RegisterId reg)
            {
                Segment = reg;
                return this;
            }

            Memory^ WithSegment(Register^ reg)
            {
                Segment = reg->Value;
                return this;
            }

            Memory^ WithBase(RegisterId reg)
            {
                Base = reg;
                return this;
            }
            Memory^ WithBase(Register^ reg)
            {
                Base = reg->Value;
                return this;
            }

            Memory^ WithIndex(RegisterId reg)
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

                if (Segment != RegisterId::Ds && Segment != RegisterId::Cs)
                {
                    p += snprintf(temp + p, sizeof(temp) - p, "%s:", RegisterGetName(Segment));
                }

                if (Base != RegisterId::None)
                {
                    p += snprintf(temp + p, sizeof(temp) - p, "%s", RegisterGetName(Base));
                }

                if (Index != RegisterId::None)
                {
                    if (Base != RegisterId::None)
                        p += snprintf(temp + p, sizeof(temp) - p, "+");

                    p += snprintf(temp + p, sizeof(temp) - p, "%s", RegisterGetName(Index));
                }

                if (Scale > 0)
                {
                    if (Index != RegisterId::None)
                        p += snprintf(temp + p, sizeof(temp) - p, "*");

                    p += snprintf(temp + p, sizeof(temp) - p, "%d", Scale);
                }

                if (Displacement > 0)
                {
                    if (Base != RegisterId::None || Index != RegisterId::None)
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

}
