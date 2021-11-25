#pragma once

namespace Dotx64Dbg
{
    public ref class Registers
    {
    public:
        enum class Class
        {
            Invalid,
            /**
            * @brief   8-bit general-purpose registers.
            */
            Gp8,
            /**
            * @brief   16-bit general-purpose registers.
            */
            Gp16,
            /**
            * @brief   32-bit general-purpose registers.
            */
            Gp32,
            /**
            * @brief   64-bit general-purpose registers.
            */
            Gp64,
            /**
            * @brief   Floating point legacy registers.
            */
            X87,
            /**
            * @brief   Floating point multimedia registers.
            */
            Mmx,
            /**
            * @brief   128-bit vector registers.
            */
            Xmm,
            /**
            * @brief   256-bit vector registers.
            */
            Ymm,
            /**
            * @brief   512-bit vector registers.
            */
            Zmm,
            /**
            * @brief   Flags registers.
            */
            Flags,
            /**
            * @brief   Instruction-pointer registers.
            */
            IP,
            /**
            * @brief   Segment registers.
            */
            Segment,
            /**
            * @brief   Test registers.
            */
            Test,
            /**
            * @brief   Control registers.
            */
            Control,
            /**
            * @brief   Debug registers.
            */
            Debug,
            /**
            * @brief   Mask registers.
            */
            Mask,
            /**
            * @brief   Bound registers.
            */
            Bound,
        };

        enum class Category
        {
            Invalid = -1,
            Gp = 0,
            X87,
            Simd,
            Flags,
            Debug,
            Segment,
            Mask,
            Control,
        };

        enum class Id
        {
            None,
            // General purpose registers  8-bit
            Al,
            Cl,
            Dl,
            Bl,
            Ah,
            Ch,
            Dh,
            Bh,
            Spl,
            Bpl,
            Sil,
            Dil,
            R8b,
            R9b,
            R10b,
            R11b,
            R12b,
            R13b,
            R14b,
            R15b,
            // General purpose registers 16-bit
            Ax,
            Cx,
            Dx,
            Bx,
            Sp,
            Bp,
            Si,
            Di,
            R8w,
            R9w,
            R10w,
            R11w,
            R12w,
            R13w,
            R14w,
            R15w,
            // General purpose registers 32-bit
            Eax,
            Ecx,
            Edx,
            Ebx,
            Esp,
            Ebp,
            Esi,
            Edi,
            R8d,
            R9d,
            R10d,
            R11d,
            R12d,
            R13d,
            R14d,
            R15d,
            // General purpose registers 64-bit
            Rax,
            Rcx,
            Rdx,
            Rbx,
            Rsp,
            Rbp,
            Rsi,
            Rdi,
            R8,
            R9,
            R10,
            R11,
            R12,
            R13,
            R14,
            R15,
            // Floating point legacy registers
            St0,
            St1,
            St2,
            St3,
            St4,
            St5,
            St6,
            St7,
            X87Control,
            X87Status,
            X87Tag,
            // Floating point multimedia registers
            Mm0,
            Mm1,
            Mm2,
            Mm3,
            Mm4,
            Mm5,
            Mm6,
            Mm7,
            // Floating point vector registers 128-bit
            Xmm0,
            Xmm1,
            Xmm2,
            Xmm3,
            Xmm4,
            Xmm5,
            Xmm6,
            Xmm7,
            Xmm8,
            Xmm9,
            Xmm10,
            Xmm11,
            Xmm12,
            Xmm13,
            Xmm14,
            Xmm15,
            Xmm16,
            Xmm17,
            Xmm18,
            Xmm19,
            Xmm20,
            Xmm21,
            Xmm22,
            Xmm23,
            Xmm24,
            Xmm25,
            Xmm26,
            Xmm27,
            Xmm28,
            Xmm29,
            Xmm30,
            Xmm31,
            // Floating point vector registers 256-bit
            Ymm0,
            Ymm1,
            Ymm2,
            Ymm3,
            Ymm4,
            Ymm5,
            Ymm6,
            Ymm7,
            Ymm8,
            Ymm9,
            Ymm10,
            Ymm11,
            Ymm12,
            Ymm13,
            Ymm14,
            Ymm15,
            Ymm16,
            Ymm17,
            Ymm18,
            Ymm19,
            Ymm20,
            Ymm21,
            Ymm22,
            Ymm23,
            Ymm24,
            Ymm25,
            Ymm26,
            Ymm27,
            Ymm28,
            Ymm29,
            Ymm30,
            Ymm31,
            // Floating point vector registers 512-bit
            Zmm0,
            Zmm1,
            Zmm2,
            Zmm3,
            Zmm4,
            Zmm5,
            Zmm6,
            Zmm7,
            Zmm8,
            Zmm9,
            Zmm10,
            Zmm11,
            Zmm12,
            Zmm13,
            Zmm14,
            Zmm15,
            Zmm16,
            Zmm17,
            Zmm18,
            Zmm19,
            Zmm20,
            Zmm21,
            Zmm22,
            Zmm23,
            Zmm24,
            Zmm25,
            Zmm26,
            Zmm27,
            Zmm28,
            Zmm29,
            Zmm30,
            Zmm31,
            // Matrix registers
            Tmm0,
            Tmm1,
            Tmm2,
            Tmm3,
            Tmm4,
            Tmm5,
            Tmm6,
            Tmm7,
            // Flags registers
            Flags,
            EFlags,
            RFlags,
            // Instruction-pointer registers
            Ip,
            Eip,
            Rip,
            // Segment registers
            Es,
            Cs,
            Ss,
            Ds,
            Fs,
            Gs,
            // Table registers
            Gdtr,
            Ldtr,
            Idtr,
            Tr,
            // Test registers
            Tr0,
            Tr1,
            Tr2,
            Tr3,
            Tr4,
            Tr5,
            Tr6,
            Tr7,
            // Control registers
            Cr0,
            Cr1,
            Cr2,
            Cr3,
            Cr4,
            Cr5,
            Cr6,
            Cr7,
            Cr8,
            Cr9,
            Cr10,
            Cr11,
            Cr12,
            Cr13,
            Cr14,
            Cr15,
            // Debug registers
            Dr0,
            Dr1,
            Dr2,
            Dr3,
            Dr4,
            Dr5,
            Dr6,
            Dr7,
            Dr8,
            Dr9,
            Dr10,
            Dr11,
            Dr12,
            Dr13,
            Dr14,
            Dr15,
            // Mask registers
            K0,
            K1,
            K2,
            K3,
            K4,
            K5,
            K6,
            K7,
            // Bound registers
            Bnd0,
            Bnd1,
            Bnd2,
            Bnd3,
            BndCfg,
            BndStatus,
            // Uncategorized
            Mxcsr,
            Pkru,
            Xcr0,

            // Host Aliases
#ifdef _M_AMD64
            Nax = Rax,
            Ncx = Rcx,
            Ndx = Rdx,
            Nbx = Rbx,
            Nsp = Rsp,
            Nbp = Rbp,
            Nsi = Rsi,
            Ndi = Rdi,
            N8 = R8,
            N9 = R9,
            N10 = R10,
            N11 = R11,
            N12 = R12,
            N13 = R13,
            N14 = R14,
            N15 = R15,
            Nip = Rip,
            NFlags = RFlags,
#else
            Nax = Eax,
            Ncx = Ecx,
            Ndx = Edx,
            Nbx = Ebx,
            Nsp = Esp,
            Nbp = Ebp,
            Nsi = Esi,
            Ndi = Edi,
            N8 = R8d,
            N9 = R9d,
            N10 = R10d,
            N11 = R11d,
            N12 = R12d,
            N13 = R13d,
            N14 = R14d,
            N15 = R15d,
            Nip = Eip,
            NFlags = EFlags,
#endif
            Invalid = 0xFFFF,
        };

        static const char* GetName(Id id)
        {
            switch (id)
            {
            case Id::None:
                return "none";
            case Id::Al:
                return "al";
            case Id::Cl:
                return "cl";
            case Id::Dl:
                return "dl";
            case Id::Bl:
                return "bl";
            case Id::Ah:
                return "ah";
            case Id::Ch:
                return "ch";
            case Id::Dh:
                return "dh";
            case Id::Bh:
                return "bh";
            case Id::Spl:
                return "spl";
            case Id::Bpl:
                return "bpl";
            case Id::Sil:
                return "sil";
            case Id::Dil:
                return "dil";
            case Id::R8b:
                return "r8b";
            case Id::R9b:
                return "r9b";
            case Id::R10b:
                return "r10b";
            case Id::R11b:
                return "r11b";
            case Id::R12b:
                return "r12b";
            case Id::R13b:
                return "r13b";
            case Id::R14b:
                return "r14b";
            case Id::R15b:
                return "r15b";
            case Id::Ax:
                return "ax";
            case Id::Cx:
                return "cx";
            case Id::Dx:
                return "dx";
            case Id::Bx:
                return "bx";
            case Id::Sp:
                return "sp";
            case Id::Bp:
                return "bp";
            case Id::Si:
                return "si";
            case Id::Di:
                return "di";
            case Id::R8w:
                return "r8w";
            case Id::R9w:
                return "r9w";
            case Id::R10w:
                return "r10w";
            case Id::R11w:
                return "r11w";
            case Id::R12w:
                return "r12w";
            case Id::R13w:
                return "r13w";
            case Id::R14w:
                return "r14w";
            case Id::R15w:
                return "r15w";
            case Id::Eax:
                return "eax";
            case Id::Ecx:
                return "ecx";
            case Id::Edx:
                return "edx";
            case Id::Ebx:
                return "ebx";
            case Id::Esp:
                return "esp";
            case Id::Ebp:
                return "ebp";
            case Id::Esi:
                return "esi";
            case Id::Edi:
                return "edi";
            case Id::R8d:
                return "r8d";
            case Id::R9d:
                return "r9d";
            case Id::R10d:
                return "r10d";
            case Id::R11d:
                return "r11d";
            case Id::R12d:
                return "r12d";
            case Id::R13d:
                return "r13d";
            case Id::R14d:
                return "r14d";
            case Id::R15d:
                return "r15d";
            case Id::Rax:
                return "rax";
            case Id::Rcx:
                return "rcx";
            case Id::Rdx:
                return "rdx";
            case Id::Rbx:
                return "rbx";
            case Id::Rsp:
                return "rsp";
            case Id::Rbp:
                return "rbp";
            case Id::Rsi:
                return "rsi";
            case Id::Rdi:
                return "rdi";
            case Id::R8:
                return "r8";
            case Id::R9:
                return "r9";
            case Id::R10:
                return "r10";
            case Id::R11:
                return "r11";
            case Id::R12:
                return "r12";
            case Id::R13:
                return "r13";
            case Id::R14:
                return "r14";
            case Id::R15:
                return "r15";
            case Id::St0:
                return "st0";
            case Id::St1:
                return "st1";
            case Id::St2:
                return "st2";
            case Id::St3:
                return "st3";
            case Id::St4:
                return "st4";
            case Id::St5:
                return "st5";
            case Id::St6:
                return "st6";
            case Id::St7:
                return "st7";
            case Id::X87Control:
                return "x87control";
            case Id::X87Status:
                return "x87status";
            case Id::X87Tag:
                return "x87tag";
            case Id::Mm0:
                return "mm0";
            case Id::Mm1:
                return "mm1";
            case Id::Mm2:
                return "mm2";
            case Id::Mm3:
                return "mm3";
            case Id::Mm4:
                return "mm4";
            case Id::Mm5:
                return "mm5";
            case Id::Mm6:
                return "mm6";
            case Id::Mm7:
                return "mm7";
                // Floating point vector registers 128-bit
            case Id::Xmm0:
                return "xmm0";
            case Id::Xmm1:
                return "xmm1";
            case Id::Xmm2:
                return "xmm2";
            case Id::Xmm3:
                return "xmm3";
            case Id::Xmm4:
                return "xmm4";
            case Id::Xmm5:
                return "xmm5";
            case Id::Xmm6:
                return "xmm6";
            case Id::Xmm7:
                return "xmm7";
            case Id::Xmm8:
                return "xmm8";
            case Id::Xmm9:
                return "xmm9";
            case Id::Xmm10:
                return "xmm10";
            case Id::Xmm11:
                return "xmm11";
            case Id::Xmm12:
                return "xmm12";
            case Id::Xmm13:
                return "xmm13";
            case Id::Xmm14:
                return "xmm14";
            case Id::Xmm15:
                return "xmm15";
            case Id::Xmm16:
                return "xmm16";
            case Id::Xmm17:
                return "xmm17";
            case Id::Xmm18:
                return "xmm18";
            case Id::Xmm19:
                return "xmm19";
            case Id::Xmm20:
                return "xmm20";
            case Id::Xmm21:
                return "xmm21";
            case Id::Xmm22:
                return "xmm22";
            case Id::Xmm23:
                return "xmm23";
            case Id::Xmm24:
                return "xmm24";
            case Id::Xmm25:
                return "xmm25";
            case Id::Xmm26:
                return "xmm26";
            case Id::Xmm27:
                return "xmm27";
            case Id::Xmm28:
                return "xmm28";
            case Id::Xmm29:
                return "xmm29";
            case Id::Xmm30:
                return "xmm30";
            case Id::Xmm31:
                return "xmm31";
                // Floating point vector registers 256-bit
            case Id::Ymm0:
                return "ymm0";
            case Id::Ymm1:
                return "ymm1";
            case Id::Ymm2:
                return "ymm2";
            case Id::Ymm3:
                return "ymm3";
            case Id::Ymm4:
                return "ymm4";
            case Id::Ymm5:
                return "ymm5";
            case Id::Ymm6:
                return "ymm6";
            case Id::Ymm7:
                return "ymm7";
            case Id::Ymm8:
                return "ymm8";
            case Id::Ymm9:
                return "ymm9";
            case Id::Ymm10:
                return "ymm10";
            case Id::Ymm11:
                return "ymm11";
            case Id::Ymm12:
                return "ymm12";
            case Id::Ymm13:
                return "ymm13";
            case Id::Ymm14:
                return "ymm14";
            case Id::Ymm15:
                return "ymm15";
            case Id::Ymm16:
                return "ymm16";
            case Id::Ymm17:
                return "ymm17";
            case Id::Ymm18:
                return "ymm18";
            case Id::Ymm19:
                return "ymm19";
            case Id::Ymm20:
                return "ymm20";
            case Id::Ymm21:
                return "ymm21";
            case Id::Ymm22:
                return "ymm22";
            case Id::Ymm23:
                return "ymm23";
            case Id::Ymm24:
                return "ymm24";
            case Id::Ymm25:
                return "ymm25";
            case Id::Ymm26:
                return "ymm26";
            case Id::Ymm27:
                return "ymm27";
            case Id::Ymm28:
                return "ymm28";
            case Id::Ymm29:
                return "ymm29";
            case Id::Ymm30:
                return "ymm30";
            case Id::Ymm31:
                return "ymm31";
                // Floating point vector registers 512-bit
            case Id::Zmm0:
                return "zmm0";
            case Id::Zmm1:
                return "zmm1";
            case Id::Zmm2:
                return "zmm2";
            case Id::Zmm3:
                return "zmm3";
            case Id::Zmm4:
                return "zmm4";
            case Id::Zmm5:
                return "zmm5";
            case Id::Zmm6:
                return "zmm6";
            case Id::Zmm7:
                return "zmm7";
            case Id::Zmm8:
                return "zmm8";
            case Id::Zmm9:
                return "zmm9";
            case Id::Zmm10:
                return "zmm10";
            case Id::Zmm11:
                return "zmm11";
            case Id::Zmm12:
                return "zmm12";
            case Id::Zmm13:
                return "zmm13";
            case Id::Zmm14:
                return "zmm14";
            case Id::Zmm15:
                return "zmm15";
            case Id::Zmm16:
                return "zmm16";
            case Id::Zmm17:
                return "zmm17";
            case Id::Zmm18:
                return "zmm18";
            case Id::Zmm19:
                return "zmm19";
            case Id::Zmm20:
                return "zmm20";
            case Id::Zmm21:
                return "zmm21";
            case Id::Zmm22:
                return "zmm22";
            case Id::Zmm23:
                return "zmm23";
            case Id::Zmm24:
                return "zmm24";
            case Id::Zmm25:
                return "zmm25";
            case Id::Zmm26:
                return "zmm26";
            case Id::Zmm27:
                return "zmm27";
            case Id::Zmm28:
                return "zmm28";
            case Id::Zmm29:
                return "zmm29";
            case Id::Zmm30:
                return "zmm30";
            case Id::Zmm31:
                return "zmm31";
                // Matrix registers
            case Id::Tmm0:
                return "tmm0";
            case Id::Tmm1:
                return "tmm1";
            case Id::Tmm2:
                return "tmm2";
            case Id::Tmm3:
                return "tmm3";
            case Id::Tmm4:
                return "tmm4";
            case Id::Tmm5:
                return "tmm5";
            case Id::Tmm6:
                return "tmm6";
            case Id::Tmm7:
                return "tmm7";
            case Id::Flags:
                return "flags";
            case Id::EFlags:
                return "eflags";
            case Id::RFlags:
                return "rflags";
            case Id::Ip:
                return "ip";
            case Id::Eip:
                return "eip";
            case Id::Rip:
                return "rip";
            case Id::Es:
                return "es";
            case Id::Cs:
                return "cs";
            case Id::Ss:
                return "ss";
            case Id::Ds:
                return "ds";
            case Id::Fs:
                return "fs";
            case Id::Gs:
                return "gs";
            case Id::Gdtr:
                return "gdtr";
            case Id::Ldtr:
                return "ldtr";
            case Id::Idtr:
                return "idtr";
            case Id::Tr:
                return "tr";
            case Id::Tr0:
                return "tr0";
            case Id::Tr1:
                return "tr1";
            case Id::Tr2:
                return "tr2";
            case Id::Tr3:
                return "tr3";
            case Id::Tr4:
                return "tr4";
            case Id::Tr5:
                return "tr5";
            case Id::Tr6:
                return "tr6";
            case Id::Tr7:
                return "tr7";
                // Control registers
            case Id::Cr0:
                return "cr0";
            case Id::Cr1:
                return "cr1";
            case Id::Cr2:
                return "cr2";
            case Id::Cr3:
                return "cr3";
            case Id::Cr4:
                return "cr4";
            case Id::Cr5:
                return "cr5";
            case Id::Cr6:
                return "cr6";
            case Id::Cr7:
                return "cr7";
            case Id::Cr8:
                return "cr8";
            case Id::Cr9:
                return "cr9";
            case Id::Cr10:
                return "cr10";
            case Id::Cr11:
                return "cr11";
            case Id::Cr12:
                return "cr12";
            case Id::Cr13:
                return "cr13";
            case Id::Cr14:
                return "cr14";
            case Id::Cr15:
                return "cr15";
                // Debug registers
            case Id::Dr0:
                return "dr0";
            case Id::Dr1:
                return "dr1";
            case Id::Dr2:
                return "dr2";
            case Id::Dr3:
                return "dr3";
            case Id::Dr4:
                return "dr4";
            case Id::Dr5:
                return "dr5";
            case Id::Dr6:
                return "dr6";
            case Id::Dr7:
                return "dr7";
            case Id::Dr8:
                return "dr8";
            case Id::Dr9:
                return "dr9";
            case Id::Dr10:
                return "dr10";
            case Id::Dr11:
                return "dr11";
            case Id::Dr12:
                return "dr12";
            case Id::Dr13:
                return "dr13";
            case Id::Dr14:
                return "dr14";
            case Id::Dr15:
                return "dr15";
            case Id::K0:
                return "k0";
            case Id::K1:
                return "k1";
            case Id::K2:
                return "k2";
            case Id::K3:
                return "k3";
            case Id::K4:
                return "k4";
            case Id::K5:
                return "k5";
            case Id::K6:
                return "k6";
            case Id::K7:
                return "k7";
            case Id::Bnd0:
                return "bnd0";
            case Id::Bnd1:
                return "bnd1";
            case Id::Bnd2:
                return "bnd2";
            case Id::Bnd3:
                return "bnd3";
            case Id::BndCfg:
                return "bndcfg";
            case Id::BndStatus:
                return "bndstatus";
            case Id::Mxcsr:
                return "mxcsr";
            case Id::Pkru:
                return "pkru";
            case Id::Xcr0:
                return "xcr0";
            }
            return "invalid";
        }

        static int GetSize(Id id)
        {
            switch (id)
            {
            case Id::None:
                return 0;
            case Id::Al:
            case Id::Cl:
            case Id::Dl:
            case Id::Bl:
            case Id::Ah:
            case Id::Ch:
            case Id::Dh:
            case Id::Bh:
            case Id::Spl:
            case Id::Bpl:
            case Id::Sil:
            case Id::Dil:
            case Id::R8b:
            case Id::R9b:
            case Id::R10b:
            case Id::R11b:
            case Id::R12b:
            case Id::R13b:
            case Id::R14b:
            case Id::R15b:
                return 8;
            case Id::Ax:
            case Id::Cx:
            case Id::Dx:
            case Id::Bx:
            case Id::Sp:
            case Id::Bp:
            case Id::Si:
            case Id::Di:
            case Id::R8w:
            case Id::R9w:
            case Id::R10w:
            case Id::R11w:
            case Id::R12w:
            case Id::R13w:
            case Id::R14w:
            case Id::R15w:
                return 16;
            case Id::Eax:
            case Id::Ecx:
            case Id::Edx:
            case Id::Ebx:
            case Id::Esp:
            case Id::Ebp:
            case Id::Esi:
            case Id::Edi:
            case Id::R8d:
            case Id::R9d:
            case Id::R10d:
            case Id::R11d:
            case Id::R12d:
            case Id::R13d:
            case Id::R14d:
            case Id::R15d:
                return 32;
            case Id::Rax:
            case Id::Rcx:
            case Id::Rdx:
            case Id::Rbx:
            case Id::Rsp:
            case Id::Rbp:
            case Id::Rsi:
            case Id::Rdi:
            case Id::R8:
            case Id::R9:
            case Id::R10:
            case Id::R11:
            case Id::R12:
            case Id::R13:
            case Id::R14:
            case Id::R15:
                return 64;
            case Id::St0:
            case Id::St1:
            case Id::St2:
            case Id::St3:
            case Id::St4:
            case Id::St5:
            case Id::St6:
            case Id::St7:
                return 80;
            case Id::X87Control:
            case Id::X87Status:
            case Id::X87Tag:
                return 16;
            case Id::Mm0:
            case Id::Mm1:
            case Id::Mm2:
            case Id::Mm3:
            case Id::Mm4:
            case Id::Mm5:
            case Id::Mm6:
            case Id::Mm7:
                return 64;
            case Id::Xmm0:
            case Id::Xmm1:
            case Id::Xmm2:
            case Id::Xmm3:
            case Id::Xmm4:
            case Id::Xmm5:
            case Id::Xmm6:
            case Id::Xmm7:
            case Id::Xmm8:
            case Id::Xmm9:
            case Id::Xmm10:
            case Id::Xmm11:
            case Id::Xmm12:
            case Id::Xmm13:
            case Id::Xmm14:
            case Id::Xmm15:
            case Id::Xmm16:
            case Id::Xmm17:
            case Id::Xmm18:
            case Id::Xmm19:
            case Id::Xmm20:
            case Id::Xmm21:
            case Id::Xmm22:
            case Id::Xmm23:
            case Id::Xmm24:
            case Id::Xmm25:
            case Id::Xmm26:
            case Id::Xmm27:
            case Id::Xmm28:
            case Id::Xmm29:
            case Id::Xmm30:
            case Id::Xmm31:
                return 128;
            case Id::Ymm0:
            case Id::Ymm1:
            case Id::Ymm2:
            case Id::Ymm3:
            case Id::Ymm4:
            case Id::Ymm5:
            case Id::Ymm6:
            case Id::Ymm7:
            case Id::Ymm8:
            case Id::Ymm9:
            case Id::Ymm10:
            case Id::Ymm11:
            case Id::Ymm12:
            case Id::Ymm13:
            case Id::Ymm14:
            case Id::Ymm15:
            case Id::Ymm16:
            case Id::Ymm17:
            case Id::Ymm18:
            case Id::Ymm19:
            case Id::Ymm20:
            case Id::Ymm21:
            case Id::Ymm22:
            case Id::Ymm23:
            case Id::Ymm24:
            case Id::Ymm25:
            case Id::Ymm26:
            case Id::Ymm27:
            case Id::Ymm28:
            case Id::Ymm29:
            case Id::Ymm30:
            case Id::Ymm31:
                return 256;
            case Id::Zmm0:
            case Id::Zmm1:
            case Id::Zmm2:
            case Id::Zmm3:
            case Id::Zmm4:
            case Id::Zmm5:
            case Id::Zmm6:
            case Id::Zmm7:
            case Id::Zmm8:
            case Id::Zmm9:
            case Id::Zmm10:
            case Id::Zmm11:
            case Id::Zmm12:
            case Id::Zmm13:
            case Id::Zmm14:
            case Id::Zmm15:
            case Id::Zmm16:
            case Id::Zmm17:
            case Id::Zmm18:
            case Id::Zmm19:
            case Id::Zmm20:
            case Id::Zmm21:
            case Id::Zmm22:
            case Id::Zmm23:
            case Id::Zmm24:
            case Id::Zmm25:
            case Id::Zmm26:
            case Id::Zmm27:
            case Id::Zmm28:
            case Id::Zmm29:
            case Id::Zmm30:
            case Id::Zmm31:
                return 512;
            case Id::Tmm0:
            case Id::Tmm1:
            case Id::Tmm2:
            case Id::Tmm3:
            case Id::Tmm4:
            case Id::Tmm5:
            case Id::Tmm6:
            case Id::Tmm7:
                return 8192;
            case Id::Flags:
                return 16;
            case Id::EFlags:
                return 32;
            case Id::RFlags:
                return 64;
            case Id::Ip:
                return 16;
            case Id::Eip:
                return 32;
            case Id::Rip:
                return 64;
            case Id::Es:
            case Id::Cs:
            case Id::Ss:
            case Id::Ds:
            case Id::Fs:
            case Id::Gs:
                return 16;
            case Id::Gdtr:
            case Id::Ldtr:
            case Id::Idtr:
            case Id::Tr:
                return 16;
            case Id::Tr0:
            case Id::Tr1:
            case Id::Tr2:
            case Id::Tr3:
            case Id::Tr4:
            case Id::Tr5:
            case Id::Tr6:
            case Id::Tr7:
                return 64;
            case Id::Cr0:
            case Id::Cr1:
            case Id::Cr2:
            case Id::Cr3:
            case Id::Cr4:
            case Id::Cr5:
            case Id::Cr6:
            case Id::Cr7:
            case Id::Cr8:
            case Id::Cr9:
            case Id::Cr10:
            case Id::Cr11:
            case Id::Cr12:
            case Id::Cr13:
            case Id::Cr14:
            case Id::Cr15:
                return 64;
            case Id::Dr0:
            case Id::Dr1:
            case Id::Dr2:
            case Id::Dr3:
            case Id::Dr4:
            case Id::Dr5:
            case Id::Dr6:
            case Id::Dr7:
            case Id::Dr8:
            case Id::Dr9:
            case Id::Dr10:
            case Id::Dr11:
            case Id::Dr12:
            case Id::Dr13:
            case Id::Dr14:
            case Id::Dr15:
#ifdef _M_AMD64
                return 64;
#else
                return 32;
#endif
            case Id::K0:
            case Id::K1:
            case Id::K2:
            case Id::K3:
            case Id::K4:
            case Id::K5:
            case Id::K6:
            case Id::K7:
                return 64;
            case Id::Bnd0:
            case Id::Bnd1:
            case Id::Bnd2:
            case Id::Bnd3:
                return 128;
            case Id::BndCfg:
            case Id::BndStatus:
                return 16;
            case Id::Mxcsr:
                return 32;
            case Id::Pkru:
            case Id::Xcr0:
                return 0;
            }
            return 0;
        }

        static Id GetRoot(Id id)
        {
            switch (id)
            {
            case Id::Al:
            case Id::Ax:
            case Id::Ah:
#ifdef _M_AMD64
                return Id::Rax;
#else
                return Id::Eax;
#endif
            case Id::Cl:
            case Id::Cx:
            case Id::Ch:
#ifdef _M_AMD64
                return Id::Rcx;
#else
                return Id::Ecx;
#endif
            case Id::Dl:
            case Id::Dx:
            case Id::Dh:
#ifdef _M_AMD64
                return Id::Rdx;
#else
                return Id::Edx;
#endif
            case Id::Bl:
            case Id::Bx:
            case Id::Bh:
#ifdef _M_AMD64
                return Id::Rbx;
#else
                return Id::Ebx;
#endif
            case Id::Sp:
            case Id::Spl:
#ifdef _M_AMD64
                return Id::Rsp;
#else
                return Id::Esp;
#endif
            case Id::Bpl:
            case Id::Bp:
#ifdef _M_AMD64
                return Id::Rbp;
#else
                return Id::Ebp;
#endif
            case Id::Si:
            case Id::Sil:
#ifdef _M_AMD64
                return Id::Rsi;
#else
                return Id::Esi;
#endif
            case Id::Di:
            case Id::Dil:
#ifdef _M_AMD64
                return Id::Rdi;
#else
                return Id::Edi;
#endif
#ifdef _M_AMD64
            case Id::R8b:
            case Id::R8w:
                return Id::R8;
            case Id::R9b:
            case Id::R9w:
                return Id::R9;
            case Id::R10b:
            case Id::R10w:
                return Id::R10;
            case Id::R11b:
            case Id::R11w:
                return Id::R11;
            case Id::R12b:
            case Id::R12w:
                return Id::R12;
            case Id::R13b:
            case Id::R13w:
                return Id::R13;
            case Id::R14b:
            case Id::R14w:
                return Id::R14;
            case Id::R15b:
            case Id::R15w:
                return Id::R15;
#endif
            case Id::Eax:
#ifdef _M_AMD64
                return Id::Rax;
#endif
            case Id::Ecx:
#ifdef _M_AMD64
                return Id::Rcx;
#endif
            case Id::Edx:
#ifdef _M_AMD64
                return Id::Rdx;
#endif
            case Id::Ebx:
#ifdef _M_AMD64
                return Id::Rbx;
#endif
            case Id::Esp:
#ifdef _M_AMD64
                return Id::Rsp;
#endif
            case Id::Ebp:
#ifdef _M_AMD64
                return Id::Rbp;
#endif
            case Id::Esi:
#ifdef _M_AMD64
                return Id::Rsi;
#endif
            case Id::Edi:
#ifdef _M_AMD64
                return Id::Rdi;
#endif
                break;
#ifdef _M_AMD64
            case Id::R8d:
#    ifdef _M_AMD64
                return Id::R8;
#    endif
            case Id::R9d:
#    ifdef _M_AMD64
                return Id::R9;
#    endif
            case Id::R10d:
#    ifdef _M_AMD64
                return Id::R10;
#    endif
            case Id::R11d:
#    ifdef _M_AMD64
                return Id::R11;
#    endif
            case Id::R12d:
#    ifdef _M_AMD64
                return Id::R12;
#    endif
            case Id::R13d:
#    ifdef _M_AMD64
                return Id::R13;
#    endif
            case Id::R14d:
#    ifdef _M_AMD64
                return Id::R14;
#    endif
            case Id::R15d:
#    ifdef _M_AMD64
                return Id::R15;
#    endif
                break;
#endif
            case Id::Flags:
#ifdef _M_AMD64
                return Id::RFlags;
#else
                return Id::EFlags;
#endif
            case Id::EFlags:
#ifdef _M_AMD64
                return Id::RFlags;
#endif
            case Id::RFlags:
            case Id::Ip:
#ifdef _M_AMD64
                return Id::Rip;
#else
                return Id::Eip;
#endif
            case Id::Eip:
#ifdef _M_AMD64
                return Id::Rip;
#endif
            case Id::Rip:
                break;
            }
            return Id::None;
        }

        static Id GetParent(Id id)
        {
            switch (id)
            {
            case Id::Al:
                return Id::Ax;
            case Id::Ax:
                return Id::Eax;
            case Id::Ah:
                return Id::Ax;
            case Id::Cl:
                return Id::Cx;
            case Id::Cx:
                return Id::Ecx;
            case Id::Ch:
                return Id::Cx;
            case Id::Dl:
                return Id::Dx;
            case Id::Dx:
                return Id::Edx;
            case Id::Dh:
                return Id::Dx;
            case Id::Bl:
                return Id::Bx;
            case Id::Bx:
                return Id::Ebx;
            case Id::Bh:
                return Id::Bx;
            case Id::Sp:
                return Id::Esp;
            case Id::Spl:
                return Id::Sp;
            case Id::Bpl:
                return Id::Bp;
            case Id::Bp:
                return Id::Ebp;
            case Id::Si:
                return Id::Esi;
            case Id::Sil:
                return Id::Si;
            case Id::Di:
                return Id::Edi;
            case Id::Dil:
                return Id::Di;
#ifdef _M_AMD64
            case Id::R8b:
                return Id::R8w;
            case Id::R8w:
                return Id::R8d;
            case Id::R9b:
                return Id::R9w;
            case Id::R9w:
                return Id::R9d;
            case Id::R10b:
                return Id::R10w;
            case Id::R10w:
                return Id::R10d;
            case Id::R11b:
                return Id::R11w;
            case Id::R11w:
                return Id::R11d;
            case Id::R12b:
                return Id::R12w;
            case Id::R12w:
                return Id::R12d;
            case Id::R13b:
                return Id::R13w;
            case Id::R13w:
                return Id::R13d;
            case Id::R14b:
                return Id::R14w;
            case Id::R14w:
                return Id::R14d;
            case Id::R15b:
                return Id::R15w;
            case Id::R15w:
                return Id::R15d;
#endif
            case Id::Eax:
#ifdef _M_AMD64
                return Id::Rax;
#else
                return Id::None;
#endif
            case Id::Ecx:
#ifdef _M_AMD64
                return Id::Rcx;
#else
                return Id::None;
#endif
            case Id::Edx:
#ifdef _M_AMD64
                return Id::Rdx;
#else
                return Id::None;
#endif
            case Id::Ebx:
#ifdef _M_AMD64
                return Id::Rbx;
#endif
            case Id::Esp:
#ifdef _M_AMD64
                return Id::Rsp;
#else
                return Id::None;
#endif
            case Id::Ebp:
#ifdef _M_AMD64
                return Id::Rbp;
#else
                return Id::None;
#endif
            case Id::Esi:
#ifdef _M_AMD64
                return Id::Rsi;
#else
                return Id::None;
#endif
            case Id::Edi:
#ifdef _M_AMD64
                return Id::Rdi;
#else
                return Id::None;
#endif

#ifdef _M_AMD64
            case Id::R8d:
#    ifdef _M_AMD64
                return Id::R8;
#    else
                return Id::None;
#    endif
            case Id::R9d:
#    ifdef _M_AMD64
                return Id::R9;
#    else
                return Id::None;
#    endif
            case Id::R10d:
#    ifdef _M_AMD64
                return Id::R10;
#    else
                return Id::None;
#    endif
            case Id::R11d:
#    ifdef _M_AMD64
                return Id::R11;
#    else
                return Id::None;
#    endif
            case Id::R12d:
#    ifdef _M_AMD64
                return Id::R12;
#    else
                return Id::None;
#    endif
            case Id::R13d:
#    ifdef _M_AMD64
                return Id::R13;
#    else
                return Id::None;
#    endif
            case Id::R14d:
#    ifdef _M_AMD64
                return Id::R14;
#    else
                return Id::None;
#    endif
            case Id::R15d:
#    ifdef _M_AMD64
                return Id::R15;
#    else
                return Id::None;
#    endif

#endif
            case Id::Flags:
#ifdef _M_AMD64
                return Id::RFlags;
#else
                return Id::EFlags;
#endif
            case Id::EFlags:
#ifdef _M_AMD64
                return Id::RFlags;
#endif
            case Id::RFlags:
            case Id::Ip:
#ifdef _M_AMD64
                return Id::Rip;
#else
                return Id::Eip;
#endif
            case Id::Eip:
#ifdef _M_AMD64
                return Id::Rip;
#else
                return Id::None;
#endif
            case Id::Rip:
                break;
            }

            return Id::None;
        }

        static int32_t GetOffsetForRoot(Id id)
        {
            switch (id)
            {
            case Id::Ah:
            case Id::Bh:
            case Id::Ch:
            case Id::Dh:
                return 8;
            }
            return 0;
        }

        static Class GetClass(Id id)
        {
            switch (id)
            {
            case Id::None:
                return Class::Invalid;
            case Id::Al:
            case Id::Cl:
            case Id::Dl:
            case Id::Bl:
            case Id::Ah:
            case Id::Ch:
            case Id::Dh:
            case Id::Bh:
            case Id::Spl:
            case Id::Bpl:
            case Id::Sil:
            case Id::Dil:
            case Id::R8b:
            case Id::R9b:
            case Id::R10b:
            case Id::R11b:
            case Id::R12b:
            case Id::R13b:
            case Id::R14b:
            case Id::R15b:
                return Class::Gp8;
            case Id::Ax:
            case Id::Cx:
            case Id::Dx:
            case Id::Bx:
            case Id::Sp:
            case Id::Bp:
            case Id::Si:
            case Id::Di:
            case Id::R8w:
            case Id::R9w:
            case Id::R10w:
            case Id::R11w:
            case Id::R12w:
            case Id::R13w:
            case Id::R14w:
            case Id::R15w:
                return Class::Gp16;
            case Id::Eax:
            case Id::Ecx:
            case Id::Edx:
            case Id::Ebx:
            case Id::Esp:
            case Id::Ebp:
            case Id::Esi:
            case Id::Edi:
            case Id::R8d:
            case Id::R9d:
            case Id::R10d:
            case Id::R11d:
            case Id::R12d:
            case Id::R13d:
            case Id::R14d:
            case Id::R15d:
                return Class::Gp32;
            case Id::Rax:
            case Id::Rcx:
            case Id::Rdx:
            case Id::Rbx:
            case Id::Rsp:
            case Id::Rbp:
            case Id::Rsi:
            case Id::Rdi:
            case Id::R8:
            case Id::R9:
            case Id::R10:
            case Id::R11:
            case Id::R12:
            case Id::R13:
            case Id::R14:
            case Id::R15:
                return Class::Gp64;
            case Id::St0:
            case Id::St1:
            case Id::St2:
            case Id::St3:
            case Id::St4:
            case Id::St5:
            case Id::St6:
            case Id::St7:
                return Class::X87;
            case Id::X87Control:
            case Id::X87Status:
            case Id::X87Tag:
                return Class::Control;
            case Id::Mm0:
            case Id::Mm1:
            case Id::Mm2:
            case Id::Mm3:
            case Id::Mm4:
            case Id::Mm5:
            case Id::Mm6:
            case Id::Mm7:
                return Class::Mmx;
            case Id::Xmm0:
            case Id::Xmm1:
            case Id::Xmm2:
            case Id::Xmm3:
            case Id::Xmm4:
            case Id::Xmm5:
            case Id::Xmm6:
            case Id::Xmm7:
            case Id::Xmm8:
            case Id::Xmm9:
            case Id::Xmm10:
            case Id::Xmm11:
            case Id::Xmm12:
            case Id::Xmm13:
            case Id::Xmm14:
            case Id::Xmm15:
            case Id::Xmm16:
            case Id::Xmm17:
            case Id::Xmm18:
            case Id::Xmm19:
            case Id::Xmm20:
            case Id::Xmm21:
            case Id::Xmm22:
            case Id::Xmm23:
            case Id::Xmm24:
            case Id::Xmm25:
            case Id::Xmm26:
            case Id::Xmm27:
            case Id::Xmm28:
            case Id::Xmm29:
            case Id::Xmm30:
            case Id::Xmm31:
                return Class::Xmm;
            case Id::Ymm0:
            case Id::Ymm1:
            case Id::Ymm2:
            case Id::Ymm3:
            case Id::Ymm4:
            case Id::Ymm5:
            case Id::Ymm6:
            case Id::Ymm7:
            case Id::Ymm8:
            case Id::Ymm9:
            case Id::Ymm10:
            case Id::Ymm11:
            case Id::Ymm12:
            case Id::Ymm13:
            case Id::Ymm14:
            case Id::Ymm15:
            case Id::Ymm16:
            case Id::Ymm17:
            case Id::Ymm18:
            case Id::Ymm19:
            case Id::Ymm20:
            case Id::Ymm21:
            case Id::Ymm22:
            case Id::Ymm23:
            case Id::Ymm24:
            case Id::Ymm25:
            case Id::Ymm26:
            case Id::Ymm27:
            case Id::Ymm28:
            case Id::Ymm29:
            case Id::Ymm30:
            case Id::Ymm31:
                return Class::Ymm;
            case Id::Zmm0:
            case Id::Zmm1:
            case Id::Zmm2:
            case Id::Zmm3:
            case Id::Zmm4:
            case Id::Zmm5:
            case Id::Zmm6:
            case Id::Zmm7:
            case Id::Zmm8:
            case Id::Zmm9:
            case Id::Zmm10:
            case Id::Zmm11:
            case Id::Zmm12:
            case Id::Zmm13:
            case Id::Zmm14:
            case Id::Zmm15:
            case Id::Zmm16:
            case Id::Zmm17:
            case Id::Zmm18:
            case Id::Zmm19:
            case Id::Zmm20:
            case Id::Zmm21:
            case Id::Zmm22:
            case Id::Zmm23:
            case Id::Zmm24:
            case Id::Zmm25:
            case Id::Zmm26:
            case Id::Zmm27:
            case Id::Zmm28:
            case Id::Zmm29:
            case Id::Zmm30:
            case Id::Zmm31:
                return Class::Zmm;
            case Id::Flags:
            case Id::EFlags:
            case Id::RFlags:
                return Class::Flags;
            case Id::Ip:
            case Id::Eip:
            case Id::Rip:
                return Class::IP;
            case Id::Es:
            case Id::Cs:
            case Id::Ss:
            case Id::Ds:
            case Id::Fs:
            case Id::Gs:
            case Id::Gdtr:
            case Id::Ldtr:
            case Id::Idtr:
                return Class::Segment;
            case Id::Tr:
            case Id::Tr0:
            case Id::Tr1:
            case Id::Tr2:
            case Id::Tr3:
            case Id::Tr4:
            case Id::Tr5:
            case Id::Tr6:
            case Id::Tr7:
                return Class::Test;
            case Id::Cr0:
            case Id::Cr1:
            case Id::Cr2:
            case Id::Cr3:
            case Id::Cr4:
            case Id::Cr5:
            case Id::Cr6:
            case Id::Cr7:
            case Id::Cr8:
            case Id::Cr9:
            case Id::Cr10:
            case Id::Cr11:
            case Id::Cr12:
            case Id::Cr13:
            case Id::Cr14:
            case Id::Cr15:
                return Class::Control;
            case Id::Dr0:
            case Id::Dr1:
            case Id::Dr2:
            case Id::Dr3:
            case Id::Dr4:
            case Id::Dr5:
            case Id::Dr6:
            case Id::Dr7:
            case Id::Dr8:
            case Id::Dr9:
            case Id::Dr10:
            case Id::Dr11:
            case Id::Dr12:
            case Id::Dr13:
            case Id::Dr14:
            case Id::Dr15:
                return Class::Debug;
            case Id::K0:
            case Id::K1:
            case Id::K2:
            case Id::K3:
            case Id::K4:
            case Id::K5:
            case Id::K6:
            case Id::K7:
                return Class::Mask;
            case Id::Bnd0:
            case Id::Bnd1:
            case Id::Bnd2:
            case Id::Bnd3:
            case Id::BndCfg:
            case Id::BndStatus:
                return Class::Bound;
            }
            return Class::Invalid;
        }

        static Category GetCategory(Id reg)
        {
            switch (GetClass(reg))
            {
            case Class::Gp8:
            case Class::Gp16:
            case Class::Gp32:
            case Class::Gp64:
            case Class::IP:
                return Category::Gp;
            case Class::X87:
                return Category::X87;
            case Class::Mmx:
                break;
            case Class::Xmm:
            case Class::Ymm:
            case Class::Zmm:
                return Category::Simd;
            case Class::Flags:
                return Category::Flags;
            case Class::Segment:
                return Category::Segment;
            case Class::Control:
                return Category::Control;
            case Class::Debug:
                return Category::Debug;
            case Class::Mask:
                return Category::Mask;
            default:
                break;
            }
            return Category::Invalid;
        }

        static int GetIndex(Id reg)
        {
            if (reg == Id::None)
                return -1;

            if (reg >= Id::Al && reg <= Id::R15)
            {
                // Gp.
                if (reg >= Id::Al && reg <= Id::R15b)
                {
                    auto index = (int)reg - (int)Id::Al;
                    if (reg >= Id::Ah && reg <= Id::Bh)
                    {
                        index -= 4;
                    }
                    return index;
                }
                else if (reg >= Id::Ax && reg <= Id::R15w)
                {
                    return  (int)reg - (int)Id::Ax;
                }
                else if (reg >= Id::Eax && reg <= Id::R15d)
                {
                    return (int)reg - (int)Id::Eax;
                }
                else if (reg >= Id::Rax && reg <= Id::R15)
                {
                    return (int)reg - (int)Id::Rax;
                }
            }
            else if (reg >= Id::St0 && reg <= Id::St1)
            {
                return (int)reg - (int)Id::St0;
            }
            else if (reg >= Id::X87Control && reg <= Id::X87Tag)
            {
                return (int)reg - (int)Id::X87Control;
            }
            else if (reg >= Id::Mm0 && reg <= Id::Mm7)
            {
                return (int)reg - (int)Id::Mm0;
            }
            else if (reg >= Id::Xmm0 && reg <= Id::Xmm31)
            {
                return (int)reg - (int)Id::Xmm0;
            }
            else if (reg >= Id::Ymm0 && reg <= Id::Ymm31)
            {
                return (int)reg - (int)Id::Ymm0;
            }
            else if (reg >= Id::Zmm0 && reg <= Id::Zmm31)
            {
                return (int)reg - (int)Id::Zmm0;
            }
            else if (reg >= Id::Flags && reg <= Id::RFlags)
            {
                return (int)reg - (int)Id::Flags;
            }
            else if (reg >= Id::Ip && reg <= Id::Rip)
            {
                return (int)reg - (int)Id::Ip;
            }
            return -1;
        }

    };

} // namespace Dotx64Dbg
