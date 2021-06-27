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
            property bool Valid
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

            System::String^ ToString() override
            {
                return gcnew System::String(RegisterGetName(_Value));
            }
        };

        // General purpose registers  8-bit
        initonly static const OpReg^ Al = gcnew OpReg(Register::Al);
        initonly static const OpReg^ Cl = gcnew OpReg(Register::Cl);
        initonly static const OpReg^ Dl = gcnew OpReg(Register::Dl);
        initonly static const OpReg^ Bl = gcnew OpReg(Register::Bl);
        initonly static const OpReg^ Ah = gcnew OpReg(Register::Ah);
        initonly static const OpReg^ Ch = gcnew OpReg(Register::Ch);
        initonly static const OpReg^ Dh = gcnew OpReg(Register::Dh);
        initonly static const OpReg^ Bh = gcnew OpReg(Register::Bh);
        initonly static const OpReg^ Spl = gcnew OpReg(Register::Spl);
        initonly static const OpReg^ Bpl = gcnew OpReg(Register::Bpl);
        initonly static const OpReg^ Sil = gcnew OpReg(Register::Sil);
        initonly static const OpReg^ Dil = gcnew OpReg(Register::Dil);
#ifdef _M_AMD64
        initonly static const OpReg^ R8b = gcnew OpReg(Register::R8b);
        initonly static const OpReg^ R9b = gcnew OpReg(Register::R9b);
        initonly static const OpReg^ R10b = gcnew OpReg(Register::R10b);
        initonly static const OpReg^ R11b = gcnew OpReg(Register::R11b);
        initonly static const OpReg^ R12b = gcnew OpReg(Register::R12b);
        initonly static const OpReg^ R13b = gcnew OpReg(Register::R13b);
        initonly static const OpReg^ R14b = gcnew OpReg(Register::R14b);
        initonly static const OpReg^ R15b = gcnew OpReg(Register::R15b);
#endif
        // General purpose registers 16-bit
        initonly static const OpReg^ Ax = gcnew OpReg(Register::Ax);
        initonly static const OpReg^ Cx = gcnew OpReg(Register::Cx);
        initonly static const OpReg^ Dx = gcnew OpReg(Register::Dx);
        initonly static const OpReg^ Bx = gcnew OpReg(Register::Bx);
        initonly static const OpReg^ Sp = gcnew OpReg(Register::Sp);
        initonly static const OpReg^ Bp = gcnew OpReg(Register::Bp);
        initonly static const OpReg^ Si = gcnew OpReg(Register::Si);
        initonly static const OpReg^ Di = gcnew OpReg(Register::Di);
#ifdef _M_AMD64
        initonly static const OpReg^ R8w = gcnew OpReg(Register::R8w);
        initonly static const OpReg^ R9w = gcnew OpReg(Register::R9w);
        initonly static const OpReg^ R10w = gcnew OpReg(Register::R10w);
        initonly static const OpReg^ R11w = gcnew OpReg(Register::R11w);
        initonly static const OpReg^ R12w = gcnew OpReg(Register::R12w);
        initonly static const OpReg^ R13w = gcnew OpReg(Register::R13w);
        initonly static const OpReg^ R14w = gcnew OpReg(Register::R14w);
        initonly static const OpReg^ R15w = gcnew OpReg(Register::R15w);
#endif
        // General purpose registers 32-bit
        initonly static const OpReg^ Eax = gcnew OpReg(Register::Eax);
        initonly static const OpReg^ Ecx = gcnew OpReg(Register::Ecx);
        initonly static const OpReg^ Edx = gcnew OpReg(Register::Edx);
        initonly static const OpReg^ Ebx = gcnew OpReg(Register::Ebx);
        initonly static const OpReg^ Esp = gcnew OpReg(Register::Esp);
        initonly static const OpReg^ Ebp = gcnew OpReg(Register::Ebp);
        initonly static const OpReg^ Esi = gcnew OpReg(Register::Esi);
        initonly static const OpReg^ Edi = gcnew OpReg(Register::Edi);
        initonly static const OpReg^ R8d = gcnew OpReg(Register::R8d);
        initonly static const OpReg^ R9d = gcnew OpReg(Register::R9d);
        initonly static const OpReg^ R10d = gcnew OpReg(Register::R10d);
        initonly static const OpReg^ R11d = gcnew OpReg(Register::R11d);
        initonly static const OpReg^ R12d = gcnew OpReg(Register::R12d);
        initonly static const OpReg^ R13d = gcnew OpReg(Register::R13d);
        initonly static const OpReg^ R14d = gcnew OpReg(Register::R14d);
        initonly static const OpReg^ R15d = gcnew OpReg(Register::R15d);
#ifdef _M_AMD64
        // General purpose registers 64-bit
        initonly static const OpReg^ Rax = gcnew OpReg(Register::Rax);
        initonly static const OpReg^ Rcx = gcnew OpReg(Register::Rcx);
        initonly static const OpReg^ Rdx = gcnew OpReg(Register::Rdx);
        initonly static const OpReg^ Rbx = gcnew OpReg(Register::Rbx);
        initonly static const OpReg^ Rsp = gcnew OpReg(Register::Rsp);
        initonly static const OpReg^ Rbp = gcnew OpReg(Register::Rbp);
        initonly static const OpReg^ Rsi = gcnew OpReg(Register::Rsi);
        initonly static const OpReg^ Rdi = gcnew OpReg(Register::Rdi);
        initonly static const OpReg^ R8 = gcnew OpReg(Register::R8);
        initonly static const OpReg^ R9 = gcnew OpReg(Register::R9);
        initonly static const OpReg^ R10 = gcnew OpReg(Register::R10);
        initonly static const OpReg^ R11 = gcnew OpReg(Register::R11);
        initonly static const OpReg^ R12 = gcnew OpReg(Register::R12);
        initonly static const OpReg^ R13 = gcnew OpReg(Register::R13);
        initonly static const OpReg^ R14 = gcnew OpReg(Register::R14);
        initonly static const OpReg^ R15 = gcnew OpReg(Register::R15);
#endif
        // Floating point legacy registers
        initonly static const OpReg^ St0 = gcnew OpReg(Register::St0);
        initonly static const OpReg^ St1 = gcnew OpReg(Register::St1);
        initonly static const OpReg^ St2 = gcnew OpReg(Register::St2);
        initonly static const OpReg^ St3 = gcnew OpReg(Register::St3);
        initonly static const OpReg^ St4 = gcnew OpReg(Register::St4);
        initonly static const OpReg^ St5 = gcnew OpReg(Register::St5);
        initonly static const OpReg^ St6 = gcnew OpReg(Register::St6);
        initonly static const OpReg^ St7 = gcnew OpReg(Register::St7);
        initonly static const OpReg^ X87Control = gcnew OpReg(Register::X87Control);
        initonly static const OpReg^ X87Status = gcnew OpReg(Register::X87Status);
        initonly static const OpReg^ X87Tag = gcnew OpReg(Register::X87Tag);
        // Floating point multimedia registers
        initonly static const OpReg^ Mm0 = gcnew OpReg(Register::Mm0);
        initonly static const OpReg^ Mm1 = gcnew OpReg(Register::Mm1);
        initonly static const OpReg^ Mm2 = gcnew OpReg(Register::Mm2);
        initonly static const OpReg^ Mm3 = gcnew OpReg(Register::Mm3);
        initonly static const OpReg^ Mm4 = gcnew OpReg(Register::Mm4);
        initonly static const OpReg^ Mm5 = gcnew OpReg(Register::Mm5);
        initonly static const OpReg^ Mm6 = gcnew OpReg(Register::Mm6);
        initonly static const OpReg^ Mm7 = gcnew OpReg(Register::Mm7);
        // Floating point vector registers 128-bit
        initonly static const OpReg^ Xmm0 = gcnew OpReg(Register::Xmm0);
        initonly static const OpReg^ Xmm1 = gcnew OpReg(Register::Xmm1);
        initonly static const OpReg^ Xmm2 = gcnew OpReg(Register::Xmm2);
        initonly static const OpReg^ Xmm3 = gcnew OpReg(Register::Xmm3);
        initonly static const OpReg^ Xmm4 = gcnew OpReg(Register::Xmm4);
        initonly static const OpReg^ Xmm5 = gcnew OpReg(Register::Xmm5);
        initonly static const OpReg^ Xmm6 = gcnew OpReg(Register::Xmm6);
        initonly static const OpReg^ Xmm7 = gcnew OpReg(Register::Xmm7);
        initonly static const OpReg^ Xmm8 = gcnew OpReg(Register::Xmm8);
        initonly static const OpReg^ Xmm9 = gcnew OpReg(Register::Xmm9);
        initonly static const OpReg^ Xmm10 = gcnew OpReg(Register::Xmm10);
        initonly static const OpReg^ Xmm11 = gcnew OpReg(Register::Xmm11);
        initonly static const OpReg^ Xmm12 = gcnew OpReg(Register::Xmm12);
        initonly static const OpReg^ Xmm13 = gcnew OpReg(Register::Xmm13);
        initonly static const OpReg^ Xmm14 = gcnew OpReg(Register::Xmm14);
        initonly static const OpReg^ Xmm15 = gcnew OpReg(Register::Xmm15);
        initonly static const OpReg^ Xmm16 = gcnew OpReg(Register::Xmm16);
        initonly static const OpReg^ Xmm17 = gcnew OpReg(Register::Xmm17);
        initonly static const OpReg^ Xmm18 = gcnew OpReg(Register::Xmm18);
        initonly static const OpReg^ Xmm19 = gcnew OpReg(Register::Xmm19);
        initonly static const OpReg^ Xmm20 = gcnew OpReg(Register::Xmm20);
        initonly static const OpReg^ Xmm21 = gcnew OpReg(Register::Xmm21);
        initonly static const OpReg^ Xmm22 = gcnew OpReg(Register::Xmm22);
        initonly static const OpReg^ Xmm23 = gcnew OpReg(Register::Xmm23);
        initonly static const OpReg^ Xmm24 = gcnew OpReg(Register::Xmm24);
        initonly static const OpReg^ Xmm25 = gcnew OpReg(Register::Xmm25);
        initonly static const OpReg^ Xmm26 = gcnew OpReg(Register::Xmm26);
        initonly static const OpReg^ Xmm27 = gcnew OpReg(Register::Xmm27);
        initonly static const OpReg^ Xmm28 = gcnew OpReg(Register::Xmm28);
        initonly static const OpReg^ Xmm29 = gcnew OpReg(Register::Xmm29);
        initonly static const OpReg^ Xmm30 = gcnew OpReg(Register::Xmm30);
        initonly static const OpReg^ Xmm31 = gcnew OpReg(Register::Xmm31);
        // Floating point vector registers 256-bit
        initonly static const OpReg^ Ymm0 = gcnew OpReg(Register::Ymm0);
        initonly static const OpReg^ Ymm1 = gcnew OpReg(Register::Ymm1);
        initonly static const OpReg^ Ymm2 = gcnew OpReg(Register::Ymm2);
        initonly static const OpReg^ Ymm3 = gcnew OpReg(Register::Ymm3);
        initonly static const OpReg^ Ymm4 = gcnew OpReg(Register::Ymm4);
        initonly static const OpReg^ Ymm5 = gcnew OpReg(Register::Ymm5);
        initonly static const OpReg^ Ymm6 = gcnew OpReg(Register::Ymm6);
        initonly static const OpReg^ Ymm7 = gcnew OpReg(Register::Ymm7);
        initonly static const OpReg^ Ymm8 = gcnew OpReg(Register::Ymm8);
        initonly static const OpReg^ Ymm9 = gcnew OpReg(Register::Ymm9);
        initonly static const OpReg^ Ymm10 = gcnew OpReg(Register::Ymm10);
        initonly static const OpReg^ Ymm11 = gcnew OpReg(Register::Ymm11);
        initonly static const OpReg^ Ymm12 = gcnew OpReg(Register::Ymm12);
        initonly static const OpReg^ Ymm13 = gcnew OpReg(Register::Ymm13);
        initonly static const OpReg^ Ymm14 = gcnew OpReg(Register::Ymm14);
        initonly static const OpReg^ Ymm15 = gcnew OpReg(Register::Ymm15);
        initonly static const OpReg^ Ymm16 = gcnew OpReg(Register::Ymm16);
        initonly static const OpReg^ Ymm17 = gcnew OpReg(Register::Ymm17);
        initonly static const OpReg^ Ymm18 = gcnew OpReg(Register::Ymm18);
        initonly static const OpReg^ Ymm19 = gcnew OpReg(Register::Ymm19);
        initonly static const OpReg^ Ymm20 = gcnew OpReg(Register::Ymm20);
        initonly static const OpReg^ Ymm21 = gcnew OpReg(Register::Ymm21);
        initonly static const OpReg^ Ymm22 = gcnew OpReg(Register::Ymm22);
        initonly static const OpReg^ Ymm23 = gcnew OpReg(Register::Ymm23);
        initonly static const OpReg^ Ymm24 = gcnew OpReg(Register::Ymm24);
        initonly static const OpReg^ Ymm25 = gcnew OpReg(Register::Ymm25);
        initonly static const OpReg^ Ymm26 = gcnew OpReg(Register::Ymm26);
        initonly static const OpReg^ Ymm27 = gcnew OpReg(Register::Ymm27);
        initonly static const OpReg^ Ymm28 = gcnew OpReg(Register::Ymm28);
        initonly static const OpReg^ Ymm29 = gcnew OpReg(Register::Ymm29);
        initonly static const OpReg^ Ymm30 = gcnew OpReg(Register::Ymm30);
        initonly static const OpReg^ Ymm31 = gcnew OpReg(Register::Ymm31);
        // Floating point vector registers 512-bit
        initonly static const OpReg^ Zmm0 = gcnew OpReg(Register::Zmm0);
        initonly static const OpReg^ Zmm1 = gcnew OpReg(Register::Zmm1);
        initonly static const OpReg^ Zmm2 = gcnew OpReg(Register::Zmm2);
        initonly static const OpReg^ Zmm3 = gcnew OpReg(Register::Zmm3);
        initonly static const OpReg^ Zmm4 = gcnew OpReg(Register::Zmm4);
        initonly static const OpReg^ Zmm5 = gcnew OpReg(Register::Zmm5);
        initonly static const OpReg^ Zmm6 = gcnew OpReg(Register::Zmm6);
        initonly static const OpReg^ Zmm7 = gcnew OpReg(Register::Zmm7);
        initonly static const OpReg^ Zmm8 = gcnew OpReg(Register::Zmm8);
        initonly static const OpReg^ Zmm9 = gcnew OpReg(Register::Zmm9);
        initonly static const OpReg^ Zmm10 = gcnew OpReg(Register::Zmm10);
        initonly static const OpReg^ Zmm11 = gcnew OpReg(Register::Zmm11);
        initonly static const OpReg^ Zmm12 = gcnew OpReg(Register::Zmm12);
        initonly static const OpReg^ Zmm13 = gcnew OpReg(Register::Zmm13);
        initonly static const OpReg^ Zmm14 = gcnew OpReg(Register::Zmm14);
        initonly static const OpReg^ Zmm15 = gcnew OpReg(Register::Zmm15);
        initonly static const OpReg^ Zmm16 = gcnew OpReg(Register::Zmm16);
        initonly static const OpReg^ Zmm17 = gcnew OpReg(Register::Zmm17);
        initonly static const OpReg^ Zmm18 = gcnew OpReg(Register::Zmm18);
        initonly static const OpReg^ Zmm19 = gcnew OpReg(Register::Zmm19);
        initonly static const OpReg^ Zmm20 = gcnew OpReg(Register::Zmm20);
        initonly static const OpReg^ Zmm21 = gcnew OpReg(Register::Zmm21);
        initonly static const OpReg^ Zmm22 = gcnew OpReg(Register::Zmm22);
        initonly static const OpReg^ Zmm23 = gcnew OpReg(Register::Zmm23);
        initonly static const OpReg^ Zmm24 = gcnew OpReg(Register::Zmm24);
        initonly static const OpReg^ Zmm25 = gcnew OpReg(Register::Zmm25);
        initonly static const OpReg^ Zmm26 = gcnew OpReg(Register::Zmm26);
        initonly static const OpReg^ Zmm27 = gcnew OpReg(Register::Zmm27);
        initonly static const OpReg^ Zmm28 = gcnew OpReg(Register::Zmm28);
        initonly static const OpReg^ Zmm29 = gcnew OpReg(Register::Zmm29);
        initonly static const OpReg^ Zmm30 = gcnew OpReg(Register::Zmm30);
        initonly static const OpReg^ Zmm31 = gcnew OpReg(Register::Zmm31);
        // Flags registers
        initonly static const OpReg^ Flags = gcnew OpReg(Register::Flags);
        initonly static const OpReg^ EFlags = gcnew OpReg(Register::EFlags);
        initonly static const OpReg^ RFlags = gcnew OpReg(Register::RFlags);
        // Instruction-pointer registers
        initonly static const OpReg^ Ip = gcnew OpReg(Register::Ip);
        initonly static const OpReg^ Eip = gcnew OpReg(Register::Eip);
        initonly static const OpReg^ Rip = gcnew OpReg(Register::Rip);
        // Segment registers
        initonly static const OpReg^ Es = gcnew OpReg(Register::Es);
        initonly static const OpReg^ Cs = gcnew OpReg(Register::Cs);
        initonly static const OpReg^ Ss = gcnew OpReg(Register::Ss);
        initonly static const OpReg^ Ds = gcnew OpReg(Register::Ds);
        initonly static const OpReg^ Fs = gcnew OpReg(Register::Fs);
        initonly static const OpReg^ Gs = gcnew OpReg(Register::Gs);
        // Table registers
        initonly static const OpReg^ Gdtr = gcnew OpReg(Register::Gdtr);
        initonly static const OpReg^ Ldtr = gcnew OpReg(Register::Ldtr);
        initonly static const OpReg^ Idtr = gcnew OpReg(Register::Idtr);
        initonly static const OpReg^ Tr = gcnew OpReg(Register::Tr);
        // Test registers
        initonly static const OpReg^ Tr0 = gcnew OpReg(Register::Tr0);
        initonly static const OpReg^ Tr1 = gcnew OpReg(Register::Tr1);
        initonly static const OpReg^ Tr2 = gcnew OpReg(Register::Tr2);
        initonly static const OpReg^ Tr3 = gcnew OpReg(Register::Tr3);
        initonly static const OpReg^ Tr4 = gcnew OpReg(Register::Tr4);
        initonly static const OpReg^ Tr5 = gcnew OpReg(Register::Tr5);
        initonly static const OpReg^ Tr6 = gcnew OpReg(Register::Tr6);
        initonly static const OpReg^ Tr7 = gcnew OpReg(Register::Tr7);
        // Control registers
        initonly static const OpReg^ Cr0 = gcnew OpReg(Register::Cr0);
        initonly static const OpReg^ Cr1 = gcnew OpReg(Register::Cr1);
        initonly static const OpReg^ Cr2 = gcnew OpReg(Register::Cr2);
        initonly static const OpReg^ Cr3 = gcnew OpReg(Register::Cr3);
        initonly static const OpReg^ Cr4 = gcnew OpReg(Register::Cr4);
        initonly static const OpReg^ Cr5 = gcnew OpReg(Register::Cr5);
        initonly static const OpReg^ Cr6 = gcnew OpReg(Register::Cr6);
        initonly static const OpReg^ Cr7 = gcnew OpReg(Register::Cr7);
        initonly static const OpReg^ Cr8 = gcnew OpReg(Register::Cr8);
        initonly static const OpReg^ Cr9 = gcnew OpReg(Register::Cr9);
        initonly static const OpReg^ Cr10 = gcnew OpReg(Register::Cr10);
        initonly static const OpReg^ Cr11 = gcnew OpReg(Register::Cr11);
        initonly static const OpReg^ Cr12 = gcnew OpReg(Register::Cr12);
        initonly static const OpReg^ Cr13 = gcnew OpReg(Register::Cr13);
        initonly static const OpReg^ Cr14 = gcnew OpReg(Register::Cr14);
        initonly static const OpReg^ Cr15 = gcnew OpReg(Register::Cr15);
        // Debug registers
        initonly static const OpReg^ Dr0 = gcnew OpReg(Register::Dr0);
        initonly static const OpReg^ Dr1 = gcnew OpReg(Register::Dr1);
        initonly static const OpReg^ Dr2 = gcnew OpReg(Register::Dr2);
        initonly static const OpReg^ Dr3 = gcnew OpReg(Register::Dr3);
        initonly static const OpReg^ Dr4 = gcnew OpReg(Register::Dr4);
        initonly static const OpReg^ Dr5 = gcnew OpReg(Register::Dr5);
        initonly static const OpReg^ Dr6 = gcnew OpReg(Register::Dr6);
        initonly static const OpReg^ Dr7 = gcnew OpReg(Register::Dr7);
        initonly static const OpReg^ Dr8 = gcnew OpReg(Register::Dr8);
        initonly static const OpReg^ Dr9 = gcnew OpReg(Register::Dr9);
        initonly static const OpReg^ Dr10 = gcnew OpReg(Register::Dr10);
        initonly static const OpReg^ Dr11 = gcnew OpReg(Register::Dr11);
        initonly static const OpReg^ Dr12 = gcnew OpReg(Register::Dr12);
        initonly static const OpReg^ Dr13 = gcnew OpReg(Register::Dr13);
        initonly static const OpReg^ Dr14 = gcnew OpReg(Register::Dr14);
        initonly static const OpReg^ Dr15 = gcnew OpReg(Register::Dr15);
        // Mask registers
        initonly static const OpReg^ K0 = gcnew OpReg(Register::K0);
        initonly static const OpReg^ K1 = gcnew OpReg(Register::K1);
        initonly static const OpReg^ K2 = gcnew OpReg(Register::K2);
        initonly static const OpReg^ K3 = gcnew OpReg(Register::K3);
        initonly static const OpReg^ K4 = gcnew OpReg(Register::K4);
        initonly static const OpReg^ K5 = gcnew OpReg(Register::K5);
        initonly static const OpReg^ K6 = gcnew OpReg(Register::K6);
        initonly static const OpReg^ K7 = gcnew OpReg(Register::K7);
        // Bound registers
        initonly static const OpReg^ Bnd0 = gcnew OpReg(Register::Bnd0);
        initonly static const OpReg^ Bnd1 = gcnew OpReg(Register::Bnd1);
        initonly static const OpReg^ Bnd2 = gcnew OpReg(Register::Bnd2);
        initonly static const OpReg^ Bnd3 = gcnew OpReg(Register::Bnd3);
        initonly static const OpReg^ BndCfg = gcnew OpReg(Register::BndCfg);
        initonly static const OpReg^ BndStatus = gcnew OpReg(Register::BndStatus);
        // Uncategorized
        initonly static const OpReg^ Mxcsr = gcnew OpReg(Register::Mxcsr);
        initonly static const OpReg^ Pkru = gcnew OpReg(Register::Pkru);
        initonly static const OpReg^ Xcr0 = gcnew OpReg(Register::Xcr0);

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
