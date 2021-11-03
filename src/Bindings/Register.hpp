#pragma once

namespace Dotx64Dbg
{

    public enum class RegisterClass
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

    public enum class RegisterCategory
    {
        Gp,
        X87,
        Simd,
    };

    public enum class RegisterId
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

    inline const char* RegisterGetName(RegisterId id)
    {
        switch (id)
        {
        case RegisterId::None:
            return "none";
        case RegisterId::Al:
            return "al";
        case RegisterId::Cl:
            return "cl";
        case RegisterId::Dl:
            return "dl";
        case RegisterId::Bl:
            return "bl";
        case RegisterId::Ah:
            return "ah";
        case RegisterId::Ch:
            return "ch";
        case RegisterId::Dh:
            return "dh";
        case RegisterId::Bh:
            return "bh";
        case RegisterId::Spl:
            return "spl";
        case RegisterId::Bpl:
            return "bpl";
        case RegisterId::Sil:
            return "sil";
        case RegisterId::Dil:
            return "dil";
        case RegisterId::R8b:
            return "r8b";
        case RegisterId::R9b:
            return "r9b";
        case RegisterId::R10b:
            return "r10b";
        case RegisterId::R11b:
            return "r11b";
        case RegisterId::R12b:
            return "r12b";
        case RegisterId::R13b:
            return "r13b";
        case RegisterId::R14b:
            return "r14b";
        case RegisterId::R15b:
            return "r15b";
        case RegisterId::Ax:
            return "ax";
        case RegisterId::Cx:
            return "cx";
        case RegisterId::Dx:
            return "dx";
        case RegisterId::Bx:
            return "bx";
        case RegisterId::Sp:
            return "sp";
        case RegisterId::Bp:
            return "bp";
        case RegisterId::Si:
            return "si";
        case RegisterId::Di:
            return "di";
        case RegisterId::R8w:
            return "r8w";
        case RegisterId::R9w:
            return "r9w";
        case RegisterId::R10w:
            return "r10w";
        case RegisterId::R11w:
            return "r11w";
        case RegisterId::R12w:
            return "r12w";
        case RegisterId::R13w:
            return "r13w";
        case RegisterId::R14w:
            return "r14w";
        case RegisterId::R15w:
            return "r15w";
        case RegisterId::Eax:
            return "eax";
        case RegisterId::Ecx:
            return "ecx";
        case RegisterId::Edx:
            return "edx";
        case RegisterId::Ebx:
            return "ebx";
        case RegisterId::Esp:
            return "esp";
        case RegisterId::Ebp:
            return "ebp";
        case RegisterId::Esi:
            return "esi";
        case RegisterId::Edi:
            return "edi";
        case RegisterId::R8d:
            return "r8d";
        case RegisterId::R9d:
            return "r9d";
        case RegisterId::R10d:
            return "r10d";
        case RegisterId::R11d:
            return "r11d";
        case RegisterId::R12d:
            return "r12d";
        case RegisterId::R13d:
            return "r13d";
        case RegisterId::R14d:
            return "r14d";
        case RegisterId::R15d:
            return "r15d";
        case RegisterId::Rax:
            return "rax";
        case RegisterId::Rcx:
            return "rcx";
        case RegisterId::Rdx:
            return "rdx";
        case RegisterId::Rbx:
            return "rbx";
        case RegisterId::Rsp:
            return "rsp";
        case RegisterId::Rbp:
            return "rbp";
        case RegisterId::Rsi:
            return "rsi";
        case RegisterId::Rdi:
            return "rdi";
        case RegisterId::R8:
            return "r8";
        case RegisterId::R9:
            return "r9";
        case RegisterId::R10:
            return "r10";
        case RegisterId::R11:
            return "r11";
        case RegisterId::R12:
            return "r12";
        case RegisterId::R13:
            return "r13";
        case RegisterId::R14:
            return "r14";
        case RegisterId::R15:
            return "r15";
        case RegisterId::St0:
            return "st0";
        case RegisterId::St1:
            return "st1";
        case RegisterId::St2:
            return "st2";
        case RegisterId::St3:
            return "st3";
        case RegisterId::St4:
            return "st4";
        case RegisterId::St5:
            return "st5";
        case RegisterId::St6:
            return "st6";
        case RegisterId::St7:
            return "st7";
        case RegisterId::X87Control:
            return "x87control";
        case RegisterId::X87Status:
            return "x87status";
        case RegisterId::X87Tag:
            return "x87tag";
        case RegisterId::Mm0:
            return "mm0";
        case RegisterId::Mm1:
            return "mm1";
        case RegisterId::Mm2:
            return "mm2";
        case RegisterId::Mm3:
            return "mm3";
        case RegisterId::Mm4:
            return "mm4";
        case RegisterId::Mm5:
            return "mm5";
        case RegisterId::Mm6:
            return "mm6";
        case RegisterId::Mm7:
            return "mm7";
            // Floating point vector registers 128-bit
        case RegisterId::Xmm0:
            return "xmm0";
        case RegisterId::Xmm1:
            return "xmm1";
        case RegisterId::Xmm2:
            return "xmm2";
        case RegisterId::Xmm3:
            return "xmm3";
        case RegisterId::Xmm4:
            return "xmm4";
        case RegisterId::Xmm5:
            return "xmm5";
        case RegisterId::Xmm6:
            return "xmm6";
        case RegisterId::Xmm7:
            return "xmm7";
        case RegisterId::Xmm8:
            return "xmm8";
        case RegisterId::Xmm9:
            return "xmm9";
        case RegisterId::Xmm10:
            return "xmm10";
        case RegisterId::Xmm11:
            return "xmm11";
        case RegisterId::Xmm12:
            return "xmm12";
        case RegisterId::Xmm13:
            return "xmm13";
        case RegisterId::Xmm14:
            return "xmm14";
        case RegisterId::Xmm15:
            return "xmm15";
        case RegisterId::Xmm16:
            return "xmm16";
        case RegisterId::Xmm17:
            return "xmm17";
        case RegisterId::Xmm18:
            return "xmm18";
        case RegisterId::Xmm19:
            return "xmm19";
        case RegisterId::Xmm20:
            return "xmm20";
        case RegisterId::Xmm21:
            return "xmm21";
        case RegisterId::Xmm22:
            return "xmm22";
        case RegisterId::Xmm23:
            return "xmm23";
        case RegisterId::Xmm24:
            return "xmm24";
        case RegisterId::Xmm25:
            return "xmm25";
        case RegisterId::Xmm26:
            return "xmm26";
        case RegisterId::Xmm27:
            return "xmm27";
        case RegisterId::Xmm28:
            return "xmm28";
        case RegisterId::Xmm29:
            return "xmm29";
        case RegisterId::Xmm30:
            return "xmm30";
        case RegisterId::Xmm31:
            return "xmm31";
            // Floating point vector registers 256-bit
        case RegisterId::Ymm0:
            return "ymm0";
        case RegisterId::Ymm1:
            return "ymm1";
        case RegisterId::Ymm2:
            return "ymm2";
        case RegisterId::Ymm3:
            return "ymm3";
        case RegisterId::Ymm4:
            return "ymm4";
        case RegisterId::Ymm5:
            return "ymm5";
        case RegisterId::Ymm6:
            return "ymm6";
        case RegisterId::Ymm7:
            return "ymm7";
        case RegisterId::Ymm8:
            return "ymm8";
        case RegisterId::Ymm9:
            return "ymm9";
        case RegisterId::Ymm10:
            return "ymm10";
        case RegisterId::Ymm11:
            return "ymm11";
        case RegisterId::Ymm12:
            return "ymm12";
        case RegisterId::Ymm13:
            return "ymm13";
        case RegisterId::Ymm14:
            return "ymm14";
        case RegisterId::Ymm15:
            return "ymm15";
        case RegisterId::Ymm16:
            return "ymm16";
        case RegisterId::Ymm17:
            return "ymm17";
        case RegisterId::Ymm18:
            return "ymm18";
        case RegisterId::Ymm19:
            return "ymm19";
        case RegisterId::Ymm20:
            return "ymm20";
        case RegisterId::Ymm21:
            return "ymm21";
        case RegisterId::Ymm22:
            return "ymm22";
        case RegisterId::Ymm23:
            return "ymm23";
        case RegisterId::Ymm24:
            return "ymm24";
        case RegisterId::Ymm25:
            return "ymm25";
        case RegisterId::Ymm26:
            return "ymm26";
        case RegisterId::Ymm27:
            return "ymm27";
        case RegisterId::Ymm28:
            return "ymm28";
        case RegisterId::Ymm29:
            return "ymm29";
        case RegisterId::Ymm30:
            return "ymm30";
        case RegisterId::Ymm31:
            return "ymm31";
            // Floating point vector registers 512-bit
        case RegisterId::Zmm0:
            return "zmm0";
        case RegisterId::Zmm1:
            return "zmm1";
        case RegisterId::Zmm2:
            return "zmm2";
        case RegisterId::Zmm3:
            return "zmm3";
        case RegisterId::Zmm4:
            return "zmm4";
        case RegisterId::Zmm5:
            return "zmm5";
        case RegisterId::Zmm6:
            return "zmm6";
        case RegisterId::Zmm7:
            return "zmm7";
        case RegisterId::Zmm8:
            return "zmm8";
        case RegisterId::Zmm9:
            return "zmm9";
        case RegisterId::Zmm10:
            return "zmm10";
        case RegisterId::Zmm11:
            return "zmm11";
        case RegisterId::Zmm12:
            return "zmm12";
        case RegisterId::Zmm13:
            return "zmm13";
        case RegisterId::Zmm14:
            return "zmm14";
        case RegisterId::Zmm15:
            return "zmm15";
        case RegisterId::Zmm16:
            return "zmm16";
        case RegisterId::Zmm17:
            return "zmm17";
        case RegisterId::Zmm18:
            return "zmm18";
        case RegisterId::Zmm19:
            return "zmm19";
        case RegisterId::Zmm20:
            return "zmm20";
        case RegisterId::Zmm21:
            return "zmm21";
        case RegisterId::Zmm22:
            return "zmm22";
        case RegisterId::Zmm23:
            return "zmm23";
        case RegisterId::Zmm24:
            return "zmm24";
        case RegisterId::Zmm25:
            return "zmm25";
        case RegisterId::Zmm26:
            return "zmm26";
        case RegisterId::Zmm27:
            return "zmm27";
        case RegisterId::Zmm28:
            return "zmm28";
        case RegisterId::Zmm29:
            return "zmm29";
        case RegisterId::Zmm30:
            return "zmm30";
        case RegisterId::Zmm31:
            return "zmm31";
            // Matrix registers
        case RegisterId::Tmm0:
            return "tmm0";
        case RegisterId::Tmm1:
            return "tmm1";
        case RegisterId::Tmm2:
            return "tmm2";
        case RegisterId::Tmm3:
            return "tmm3";
        case RegisterId::Tmm4:
            return "tmm4";
        case RegisterId::Tmm5:
            return "tmm5";
        case RegisterId::Tmm6:
            return "tmm6";
        case RegisterId::Tmm7:
            return "tmm7";
        case RegisterId::Flags:
            return "flags";
        case RegisterId::EFlags:
            return "eflags";
        case RegisterId::RFlags:
            return "rflags";
        case RegisterId::Ip:
            return "ip";
        case RegisterId::Eip:
            return "eip";
        case RegisterId::Rip:
            return "rip";
        case RegisterId::Es:
            return "es";
        case RegisterId::Cs:
            return "cs";
        case RegisterId::Ss:
            return "ss";
        case RegisterId::Ds:
            return "ds";
        case RegisterId::Fs:
            return "fs";
        case RegisterId::Gs:
            return "gs";
        case RegisterId::Gdtr:
            return "gdtr";
        case RegisterId::Ldtr:
            return "ldtr";
        case RegisterId::Idtr:
            return "idtr";
        case RegisterId::Tr:
            return "tr";
        case RegisterId::Tr0:
            return "tr0";
        case RegisterId::Tr1:
            return "tr1";
        case RegisterId::Tr2:
            return "tr2";
        case RegisterId::Tr3:
            return "tr3";
        case RegisterId::Tr4:
            return "tr4";
        case RegisterId::Tr5:
            return "tr5";
        case RegisterId::Tr6:
            return "tr6";
        case RegisterId::Tr7:
            return "tr7";
            // Control registers
        case RegisterId::Cr0:
            return "cr0";
        case RegisterId::Cr1:
            return "cr1";
        case RegisterId::Cr2:
            return "cr2";
        case RegisterId::Cr3:
            return "cr3";
        case RegisterId::Cr4:
            return "cr4";
        case RegisterId::Cr5:
            return "cr5";
        case RegisterId::Cr6:
            return "cr6";
        case RegisterId::Cr7:
            return "cr7";
        case RegisterId::Cr8:
            return "cr8";
        case RegisterId::Cr9:
            return "cr9";
        case RegisterId::Cr10:
            return "cr10";
        case RegisterId::Cr11:
            return "cr11";
        case RegisterId::Cr12:
            return "cr12";
        case RegisterId::Cr13:
            return "cr13";
        case RegisterId::Cr14:
            return "cr14";
        case RegisterId::Cr15:
            return "cr15";
            // Debug registers
        case RegisterId::Dr0:
            return "dr0";
        case RegisterId::Dr1:
            return "dr1";
        case RegisterId::Dr2:
            return "dr2";
        case RegisterId::Dr3:
            return "dr3";
        case RegisterId::Dr4:
            return "dr4";
        case RegisterId::Dr5:
            return "dr5";
        case RegisterId::Dr6:
            return "dr6";
        case RegisterId::Dr7:
            return "dr7";
        case RegisterId::Dr8:
            return "dr8";
        case RegisterId::Dr9:
            return "dr9";
        case RegisterId::Dr10:
            return "dr10";
        case RegisterId::Dr11:
            return "dr11";
        case RegisterId::Dr12:
            return "dr12";
        case RegisterId::Dr13:
            return "dr13";
        case RegisterId::Dr14:
            return "dr14";
        case RegisterId::Dr15:
            return "dr15";
        case RegisterId::K0:
            return "k0";
        case RegisterId::K1:
            return "k1";
        case RegisterId::K2:
            return "k2";
        case RegisterId::K3:
            return "k3";
        case RegisterId::K4:
            return "k4";
        case RegisterId::K5:
            return "k5";
        case RegisterId::K6:
            return "k6";
        case RegisterId::K7:
            return "k7";
        case RegisterId::Bnd0:
            return "bnd0";
        case RegisterId::Bnd1:
            return "bnd1";
        case RegisterId::Bnd2:
            return "bnd2";
        case RegisterId::Bnd3:
            return "bnd3";
        case RegisterId::BndCfg:
            return "bndcfg";
        case RegisterId::BndStatus:
            return "bndstatus";
        case RegisterId::Mxcsr:
            return "mxcsr";
        case RegisterId::Pkru:
            return "pkru";
        case RegisterId::Xcr0:
            return "xcr0";
        }
        return "invalid";
    }

    inline int RegisterGetSize(RegisterId id)
    {
        switch (id)
        {
        case RegisterId::None:
            return 0;
        case RegisterId::Al:
        case RegisterId::Cl:
        case RegisterId::Dl:
        case RegisterId::Bl:
        case RegisterId::Ah:
        case RegisterId::Ch:
        case RegisterId::Dh:
        case RegisterId::Bh:
        case RegisterId::Spl:
        case RegisterId::Bpl:
        case RegisterId::Sil:
        case RegisterId::Dil:
        case RegisterId::R8b:
        case RegisterId::R9b:
        case RegisterId::R10b:
        case RegisterId::R11b:
        case RegisterId::R12b:
        case RegisterId::R13b:
        case RegisterId::R14b:
        case RegisterId::R15b:
            return 8;
        case RegisterId::Ax:
        case RegisterId::Cx:
        case RegisterId::Dx:
        case RegisterId::Bx:
        case RegisterId::Sp:
        case RegisterId::Bp:
        case RegisterId::Si:
        case RegisterId::Di:
        case RegisterId::R8w:
        case RegisterId::R9w:
        case RegisterId::R10w:
        case RegisterId::R11w:
        case RegisterId::R12w:
        case RegisterId::R13w:
        case RegisterId::R14w:
        case RegisterId::R15w:
            return 16;
        case RegisterId::Eax:
        case RegisterId::Ecx:
        case RegisterId::Edx:
        case RegisterId::Ebx:
        case RegisterId::Esp:
        case RegisterId::Ebp:
        case RegisterId::Esi:
        case RegisterId::Edi:
        case RegisterId::R8d:
        case RegisterId::R9d:
        case RegisterId::R10d:
        case RegisterId::R11d:
        case RegisterId::R12d:
        case RegisterId::R13d:
        case RegisterId::R14d:
        case RegisterId::R15d:
            return 32;
        case RegisterId::Rax:
        case RegisterId::Rcx:
        case RegisterId::Rdx:
        case RegisterId::Rbx:
        case RegisterId::Rsp:
        case RegisterId::Rbp:
        case RegisterId::Rsi:
        case RegisterId::Rdi:
        case RegisterId::R8:
        case RegisterId::R9:
        case RegisterId::R10:
        case RegisterId::R11:
        case RegisterId::R12:
        case RegisterId::R13:
        case RegisterId::R14:
        case RegisterId::R15:
            return 64;
        case RegisterId::St0:
        case RegisterId::St1:
        case RegisterId::St2:
        case RegisterId::St3:
        case RegisterId::St4:
        case RegisterId::St5:
        case RegisterId::St6:
        case RegisterId::St7:
            return 80;
        case RegisterId::X87Control:
        case RegisterId::X87Status:
        case RegisterId::X87Tag:
            return 16;
        case RegisterId::Mm0:
        case RegisterId::Mm1:
        case RegisterId::Mm2:
        case RegisterId::Mm3:
        case RegisterId::Mm4:
        case RegisterId::Mm5:
        case RegisterId::Mm6:
        case RegisterId::Mm7:
            return 64;
        case RegisterId::Xmm0:
        case RegisterId::Xmm1:
        case RegisterId::Xmm2:
        case RegisterId::Xmm3:
        case RegisterId::Xmm4:
        case RegisterId::Xmm5:
        case RegisterId::Xmm6:
        case RegisterId::Xmm7:
        case RegisterId::Xmm8:
        case RegisterId::Xmm9:
        case RegisterId::Xmm10:
        case RegisterId::Xmm11:
        case RegisterId::Xmm12:
        case RegisterId::Xmm13:
        case RegisterId::Xmm14:
        case RegisterId::Xmm15:
        case RegisterId::Xmm16:
        case RegisterId::Xmm17:
        case RegisterId::Xmm18:
        case RegisterId::Xmm19:
        case RegisterId::Xmm20:
        case RegisterId::Xmm21:
        case RegisterId::Xmm22:
        case RegisterId::Xmm23:
        case RegisterId::Xmm24:
        case RegisterId::Xmm25:
        case RegisterId::Xmm26:
        case RegisterId::Xmm27:
        case RegisterId::Xmm28:
        case RegisterId::Xmm29:
        case RegisterId::Xmm30:
        case RegisterId::Xmm31:
            return 128;
        case RegisterId::Ymm0:
        case RegisterId::Ymm1:
        case RegisterId::Ymm2:
        case RegisterId::Ymm3:
        case RegisterId::Ymm4:
        case RegisterId::Ymm5:
        case RegisterId::Ymm6:
        case RegisterId::Ymm7:
        case RegisterId::Ymm8:
        case RegisterId::Ymm9:
        case RegisterId::Ymm10:
        case RegisterId::Ymm11:
        case RegisterId::Ymm12:
        case RegisterId::Ymm13:
        case RegisterId::Ymm14:
        case RegisterId::Ymm15:
        case RegisterId::Ymm16:
        case RegisterId::Ymm17:
        case RegisterId::Ymm18:
        case RegisterId::Ymm19:
        case RegisterId::Ymm20:
        case RegisterId::Ymm21:
        case RegisterId::Ymm22:
        case RegisterId::Ymm23:
        case RegisterId::Ymm24:
        case RegisterId::Ymm25:
        case RegisterId::Ymm26:
        case RegisterId::Ymm27:
        case RegisterId::Ymm28:
        case RegisterId::Ymm29:
        case RegisterId::Ymm30:
        case RegisterId::Ymm31:
            return 256;
        case RegisterId::Zmm0:
        case RegisterId::Zmm1:
        case RegisterId::Zmm2:
        case RegisterId::Zmm3:
        case RegisterId::Zmm4:
        case RegisterId::Zmm5:
        case RegisterId::Zmm6:
        case RegisterId::Zmm7:
        case RegisterId::Zmm8:
        case RegisterId::Zmm9:
        case RegisterId::Zmm10:
        case RegisterId::Zmm11:
        case RegisterId::Zmm12:
        case RegisterId::Zmm13:
        case RegisterId::Zmm14:
        case RegisterId::Zmm15:
        case RegisterId::Zmm16:
        case RegisterId::Zmm17:
        case RegisterId::Zmm18:
        case RegisterId::Zmm19:
        case RegisterId::Zmm20:
        case RegisterId::Zmm21:
        case RegisterId::Zmm22:
        case RegisterId::Zmm23:
        case RegisterId::Zmm24:
        case RegisterId::Zmm25:
        case RegisterId::Zmm26:
        case RegisterId::Zmm27:
        case RegisterId::Zmm28:
        case RegisterId::Zmm29:
        case RegisterId::Zmm30:
        case RegisterId::Zmm31:
            return 512;
        case RegisterId::Tmm0:
        case RegisterId::Tmm1:
        case RegisterId::Tmm2:
        case RegisterId::Tmm3:
        case RegisterId::Tmm4:
        case RegisterId::Tmm5:
        case RegisterId::Tmm6:
        case RegisterId::Tmm7:
            return 8192;
        case RegisterId::Flags:
            return 16;
        case RegisterId::EFlags:
            return 32;
        case RegisterId::RFlags:
            return 64;
        case RegisterId::Ip:
            return 16;
        case RegisterId::Eip:
            return 32;
        case RegisterId::Rip:
            return 64;
        case RegisterId::Es:
        case RegisterId::Cs:
        case RegisterId::Ss:
        case RegisterId::Ds:
        case RegisterId::Fs:
        case RegisterId::Gs:
            return 16;
        case RegisterId::Gdtr:
        case RegisterId::Ldtr:
        case RegisterId::Idtr:
        case RegisterId::Tr:
            return 16;
        case RegisterId::Tr0:
        case RegisterId::Tr1:
        case RegisterId::Tr2:
        case RegisterId::Tr3:
        case RegisterId::Tr4:
        case RegisterId::Tr5:
        case RegisterId::Tr6:
        case RegisterId::Tr7:
            return 64;
        case RegisterId::Cr0:
        case RegisterId::Cr1:
        case RegisterId::Cr2:
        case RegisterId::Cr3:
        case RegisterId::Cr4:
        case RegisterId::Cr5:
        case RegisterId::Cr6:
        case RegisterId::Cr7:
        case RegisterId::Cr8:
        case RegisterId::Cr9:
        case RegisterId::Cr10:
        case RegisterId::Cr11:
        case RegisterId::Cr12:
        case RegisterId::Cr13:
        case RegisterId::Cr14:
        case RegisterId::Cr15:
            return 64;
        case RegisterId::Dr0:
        case RegisterId::Dr1:
        case RegisterId::Dr2:
        case RegisterId::Dr3:
        case RegisterId::Dr4:
        case RegisterId::Dr5:
        case RegisterId::Dr6:
        case RegisterId::Dr7:
        case RegisterId::Dr8:
        case RegisterId::Dr9:
        case RegisterId::Dr10:
        case RegisterId::Dr11:
        case RegisterId::Dr12:
        case RegisterId::Dr13:
        case RegisterId::Dr14:
        case RegisterId::Dr15:
#ifdef _M_AMD64
            return 64;
#else
            return 32;
#endif
        case RegisterId::K0:
        case RegisterId::K1:
        case RegisterId::K2:
        case RegisterId::K3:
        case RegisterId::K4:
        case RegisterId::K5:
        case RegisterId::K6:
        case RegisterId::K7:
            return 64;
        case RegisterId::Bnd0:
        case RegisterId::Bnd1:
        case RegisterId::Bnd2:
        case RegisterId::Bnd3:
            return 128;
        case RegisterId::BndCfg:
        case RegisterId::BndStatus:
            return 16;
        case RegisterId::Mxcsr:
            return 32;
        case RegisterId::Pkru:
        case RegisterId::Xcr0:
            return 0;
        }
        return 0;
    }

    inline RegisterId RegisterGetRoot(RegisterId id)
    {
        switch (id)
        {
        case RegisterId::Al:
        case RegisterId::Ax:
        case RegisterId::Ah:
#ifdef _M_AMD64
            return RegisterId::Rax;
#else
            return RegisterId::Eax;
#endif
        case RegisterId::Cl:
        case RegisterId::Cx:
        case RegisterId::Ch:
#ifdef _M_AMD64
            return RegisterId::Rcx;
#else
            return RegisterId::Ecx;
#endif
        case RegisterId::Dl:
        case RegisterId::Dx:
        case RegisterId::Dh:
#ifdef _M_AMD64
            return RegisterId::Rdx;
#else
            return RegisterId::Edx;
#endif
        case RegisterId::Bl:
        case RegisterId::Bx:
        case RegisterId::Bh:
#ifdef _M_AMD64
            return RegisterId::Rbx;
#else
            return RegisterId::Ebx;
#endif
        case RegisterId::Sp:
        case RegisterId::Spl:
#ifdef _M_AMD64
            return RegisterId::Rsp;
#else
            return RegisterId::Esp;
#endif
        case RegisterId::Bpl:
        case RegisterId::Bp:
#ifdef _M_AMD64
            return RegisterId::Rbp;
#else
            return RegisterId::Ebp;
#endif
        case RegisterId::Si:
        case RegisterId::Sil:
#ifdef _M_AMD64
            return RegisterId::Rsi;
#else
            return RegisterId::Esi;
#endif
        case RegisterId::Di:
        case RegisterId::Dil:
#ifdef _M_AMD64
            return RegisterId::Rdi;
#else
            return RegisterId::Edi;
#endif
#ifdef _M_AMD64
        case RegisterId::R8b:
        case RegisterId::R8w:
            return RegisterId::R8;
        case RegisterId::R9b:
        case RegisterId::R9w:
            return RegisterId::R9;
        case RegisterId::R10b:
        case RegisterId::R10w:
            return RegisterId::R10;
        case RegisterId::R11b:
        case RegisterId::R11w:
            return RegisterId::R11;
        case RegisterId::R12b:
        case RegisterId::R12w:
            return RegisterId::R12;
        case RegisterId::R13b:
        case RegisterId::R13w:
            return RegisterId::R13;
        case RegisterId::R14b:
        case RegisterId::R14w:
            return RegisterId::R14;
        case RegisterId::R15b:
        case RegisterId::R15w:
            return RegisterId::R15;
#endif
        case RegisterId::Eax:
#ifdef _M_AMD64
            return RegisterId::Rax;
#endif
        case RegisterId::Ecx:
#ifdef _M_AMD64
            return RegisterId::Rcx;
#endif
        case RegisterId::Edx:
#ifdef _M_AMD64
            return RegisterId::Rdx;
#endif
        case RegisterId::Ebx:
#ifdef _M_AMD64
            return RegisterId::Rbx;
#endif
        case RegisterId::Esp:
#ifdef _M_AMD64
            return RegisterId::Rsp;
#endif
        case RegisterId::Ebp:
#ifdef _M_AMD64
            return RegisterId::Rbp;
#endif
        case RegisterId::Esi:
#ifdef _M_AMD64
            return RegisterId::Rsi;
#endif
        case RegisterId::Edi:
#ifdef _M_AMD64
            return RegisterId::Rdi;
#endif
            break;
#ifdef _M_AMD64
        case RegisterId::R8d:
#    ifdef _M_AMD64
            return RegisterId::R8;
#    endif
        case RegisterId::R9d:
#    ifdef _M_AMD64
            return RegisterId::R9;
#    endif
        case RegisterId::R10d:
#    ifdef _M_AMD64
            return RegisterId::R10;
#    endif
        case RegisterId::R11d:
#    ifdef _M_AMD64
            return RegisterId::R11;
#    endif
        case RegisterId::R12d:
#    ifdef _M_AMD64
            return RegisterId::R12;
#    endif
        case RegisterId::R13d:
#    ifdef _M_AMD64
            return RegisterId::R13;
#    endif
        case RegisterId::R14d:
#    ifdef _M_AMD64
            return RegisterId::R14;
#    endif
        case RegisterId::R15d:
#    ifdef _M_AMD64
            return RegisterId::R15;
#    endif
            break;
#endif
        case RegisterId::Flags:
#ifdef _M_AMD64
            return RegisterId::RFlags;
#else
            return RegisterId::EFlags;
#endif
        case RegisterId::EFlags:
#ifdef _M_AMD64
            return RegisterId::RFlags;
#endif
        case RegisterId::RFlags:
        case RegisterId::Ip:
#ifdef _M_AMD64
            return RegisterId::Rip;
#else
            return RegisterId::Eip;
#endif
        case RegisterId::Eip:
#ifdef _M_AMD64
            return RegisterId::Rip;
#endif
        case RegisterId::Rip:
            break;
        }
        return RegisterId::None;
    }

    inline RegisterId RegisterGetParent(RegisterId id)
    {
        switch (id)
        {
        case RegisterId::Al:
            return RegisterId::Ax;
        case RegisterId::Ax:
            return RegisterId::Eax;
        case RegisterId::Ah:
            return RegisterId::Ax;
        case RegisterId::Cl:
            return RegisterId::Cx;
        case RegisterId::Cx:
            return RegisterId::Ecx;
        case RegisterId::Ch:
            return RegisterId::Cx;
        case RegisterId::Dl:
            return RegisterId::Dx;
        case RegisterId::Dx:
            return RegisterId::Edx;
        case RegisterId::Dh:
            return RegisterId::Dx;
        case RegisterId::Bl:
            return RegisterId::Bx;
        case RegisterId::Bx:
            return RegisterId::Ebx;
        case RegisterId::Bh:
            return RegisterId::Bx;
        case RegisterId::Sp:
            return RegisterId::Esp;
        case RegisterId::Spl:
            return RegisterId::Sp;
        case RegisterId::Bpl:
            return RegisterId::Bp;
        case RegisterId::Bp:
            return RegisterId::Ebp;
        case RegisterId::Si:
            return RegisterId::Esi;
        case RegisterId::Sil:
            return RegisterId::Si;
        case RegisterId::Di:
            return RegisterId::Edi;
        case RegisterId::Dil:
            return RegisterId::Di;
#ifdef _M_AMD64
        case RegisterId::R8b:
            return RegisterId::R8w;
        case RegisterId::R8w:
            return RegisterId::R8d;
        case RegisterId::R9b:
            return RegisterId::R9w;
        case RegisterId::R9w:
            return RegisterId::R9d;
        case RegisterId::R10b:
            return RegisterId::R10w;
        case RegisterId::R10w:
            return RegisterId::R10d;
        case RegisterId::R11b:
            return RegisterId::R11w;
        case RegisterId::R11w:
            return RegisterId::R11d;
        case RegisterId::R12b:
            return RegisterId::R12w;
        case RegisterId::R12w:
            return RegisterId::R12d;
        case RegisterId::R13b:
            return RegisterId::R13w;
        case RegisterId::R13w:
            return RegisterId::R13d;
        case RegisterId::R14b:
            return RegisterId::R14w;
        case RegisterId::R14w:
            return RegisterId::R14d;
        case RegisterId::R15b:
            return RegisterId::R15w;
        case RegisterId::R15w:
            return RegisterId::R15d;
#endif
        case RegisterId::Eax:
#ifdef _M_AMD64
            return RegisterId::Rax;
#else
            return RegisterId::None;
#endif
        case RegisterId::Ecx:
#ifdef _M_AMD64
            return RegisterId::Rcx;
#else
            return RegisterId::None;
#endif
        case RegisterId::Edx:
#ifdef _M_AMD64
            return RegisterId::Rdx;
#else
            return RegisterId::None;
#endif
        case RegisterId::Ebx:
#ifdef _M_AMD64
            return RegisterId::Rbx;
#endif
        case RegisterId::Esp:
#ifdef _M_AMD64
            return RegisterId::Rsp;
#else
            return RegisterId::None;
#endif
        case RegisterId::Ebp:
#ifdef _M_AMD64
            return RegisterId::Rbp;
#else
            return RegisterId::None;
#endif
        case RegisterId::Esi:
#ifdef _M_AMD64
            return RegisterId::Rsi;
#else
            return RegisterId::None;
#endif
        case RegisterId::Edi:
#ifdef _M_AMD64
            return RegisterId::Rdi;
#else
            return RegisterId::None;
#endif

#ifdef _M_AMD64
        case RegisterId::R8d:
#    ifdef _M_AMD64
            return RegisterId::R8;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R9d:
#    ifdef _M_AMD64
            return RegisterId::R9;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R10d:
#    ifdef _M_AMD64
            return RegisterId::R10;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R11d:
#    ifdef _M_AMD64
            return RegisterId::R11;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R12d:
#    ifdef _M_AMD64
            return RegisterId::R12;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R13d:
#    ifdef _M_AMD64
            return RegisterId::R13;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R14d:
#    ifdef _M_AMD64
            return RegisterId::R14;
#    else
            return RegisterId::None;
#    endif
        case RegisterId::R15d:
#    ifdef _M_AMD64
            return RegisterId::R15;
#    else
            return RegisterId::None;
#    endif

#endif
        case RegisterId::Flags:
#ifdef _M_AMD64
            return RegisterId::RFlags;
#else
            return RegisterId::EFlags;
#endif
        case RegisterId::EFlags:
#ifdef _M_AMD64
            return RegisterId::RFlags;
#endif
        case RegisterId::RFlags:
        case RegisterId::Ip:
#ifdef _M_AMD64
            return RegisterId::Rip;
#else
            return RegisterId::Eip;
#endif
        case RegisterId::Eip:
#ifdef _M_AMD64
            return RegisterId::Rip;
#else
            return RegisterId::None;
#endif
        case RegisterId::Rip:
            break;
        }

        return RegisterId::None;
    }

    inline int32_t RegisterGetOffsetForRoot(RegisterId id)
    {
        switch (id)
        {
        case RegisterId::Ah:
        case RegisterId::Bh:
        case RegisterId::Ch:
        case RegisterId::Dh:
            return 8;
        }
        return 0;
    }

    inline RegisterClass RegisterGetClass(RegisterId id)
    {
        switch (id)
        {
        case RegisterId::None:
            return RegisterClass::Invalid;
        case RegisterId::Al:
        case RegisterId::Cl:
        case RegisterId::Dl:
        case RegisterId::Bl:
        case RegisterId::Ah:
        case RegisterId::Ch:
        case RegisterId::Dh:
        case RegisterId::Bh:
        case RegisterId::Spl:
        case RegisterId::Bpl:
        case RegisterId::Sil:
        case RegisterId::Dil:
        case RegisterId::R8b:
        case RegisterId::R9b:
        case RegisterId::R10b:
        case RegisterId::R11b:
        case RegisterId::R12b:
        case RegisterId::R13b:
        case RegisterId::R14b:
        case RegisterId::R15b:
            return RegisterClass::Gp8;
        case RegisterId::Ax:
        case RegisterId::Cx:
        case RegisterId::Dx:
        case RegisterId::Bx:
        case RegisterId::Sp:
        case RegisterId::Bp:
        case RegisterId::Si:
        case RegisterId::Di:
        case RegisterId::R8w:
        case RegisterId::R9w:
        case RegisterId::R10w:
        case RegisterId::R11w:
        case RegisterId::R12w:
        case RegisterId::R13w:
        case RegisterId::R14w:
        case RegisterId::R15w:
            return RegisterClass::Gp16;
        case RegisterId::Eax:
        case RegisterId::Ecx:
        case RegisterId::Edx:
        case RegisterId::Ebx:
        case RegisterId::Esp:
        case RegisterId::Ebp:
        case RegisterId::Esi:
        case RegisterId::Edi:
        case RegisterId::R8d:
        case RegisterId::R9d:
        case RegisterId::R10d:
        case RegisterId::R11d:
        case RegisterId::R12d:
        case RegisterId::R13d:
        case RegisterId::R14d:
        case RegisterId::R15d:
            return RegisterClass::Gp32;
        case RegisterId::Rax:
        case RegisterId::Rcx:
        case RegisterId::Rdx:
        case RegisterId::Rbx:
        case RegisterId::Rsp:
        case RegisterId::Rbp:
        case RegisterId::Rsi:
        case RegisterId::Rdi:
        case RegisterId::R8:
        case RegisterId::R9:
        case RegisterId::R10:
        case RegisterId::R11:
        case RegisterId::R12:
        case RegisterId::R13:
        case RegisterId::R14:
        case RegisterId::R15:
            return RegisterClass::Gp64;
        case RegisterId::St0:
        case RegisterId::St1:
        case RegisterId::St2:
        case RegisterId::St3:
        case RegisterId::St4:
        case RegisterId::St5:
        case RegisterId::St6:
        case RegisterId::St7:
            return RegisterClass::X87;
        case RegisterId::X87Control:
        case RegisterId::X87Status:
        case RegisterId::X87Tag:
            return RegisterClass::Control;
        case RegisterId::Mm0:
        case RegisterId::Mm1:
        case RegisterId::Mm2:
        case RegisterId::Mm3:
        case RegisterId::Mm4:
        case RegisterId::Mm5:
        case RegisterId::Mm6:
        case RegisterId::Mm7:
            return RegisterClass::Mmx;
        case RegisterId::Xmm0:
        case RegisterId::Xmm1:
        case RegisterId::Xmm2:
        case RegisterId::Xmm3:
        case RegisterId::Xmm4:
        case RegisterId::Xmm5:
        case RegisterId::Xmm6:
        case RegisterId::Xmm7:
        case RegisterId::Xmm8:
        case RegisterId::Xmm9:
        case RegisterId::Xmm10:
        case RegisterId::Xmm11:
        case RegisterId::Xmm12:
        case RegisterId::Xmm13:
        case RegisterId::Xmm14:
        case RegisterId::Xmm15:
        case RegisterId::Xmm16:
        case RegisterId::Xmm17:
        case RegisterId::Xmm18:
        case RegisterId::Xmm19:
        case RegisterId::Xmm20:
        case RegisterId::Xmm21:
        case RegisterId::Xmm22:
        case RegisterId::Xmm23:
        case RegisterId::Xmm24:
        case RegisterId::Xmm25:
        case RegisterId::Xmm26:
        case RegisterId::Xmm27:
        case RegisterId::Xmm28:
        case RegisterId::Xmm29:
        case RegisterId::Xmm30:
        case RegisterId::Xmm31:
            return RegisterClass::Xmm;
        case RegisterId::Ymm0:
        case RegisterId::Ymm1:
        case RegisterId::Ymm2:
        case RegisterId::Ymm3:
        case RegisterId::Ymm4:
        case RegisterId::Ymm5:
        case RegisterId::Ymm6:
        case RegisterId::Ymm7:
        case RegisterId::Ymm8:
        case RegisterId::Ymm9:
        case RegisterId::Ymm10:
        case RegisterId::Ymm11:
        case RegisterId::Ymm12:
        case RegisterId::Ymm13:
        case RegisterId::Ymm14:
        case RegisterId::Ymm15:
        case RegisterId::Ymm16:
        case RegisterId::Ymm17:
        case RegisterId::Ymm18:
        case RegisterId::Ymm19:
        case RegisterId::Ymm20:
        case RegisterId::Ymm21:
        case RegisterId::Ymm22:
        case RegisterId::Ymm23:
        case RegisterId::Ymm24:
        case RegisterId::Ymm25:
        case RegisterId::Ymm26:
        case RegisterId::Ymm27:
        case RegisterId::Ymm28:
        case RegisterId::Ymm29:
        case RegisterId::Ymm30:
        case RegisterId::Ymm31:
            return RegisterClass::Ymm;
        case RegisterId::Zmm0:
        case RegisterId::Zmm1:
        case RegisterId::Zmm2:
        case RegisterId::Zmm3:
        case RegisterId::Zmm4:
        case RegisterId::Zmm5:
        case RegisterId::Zmm6:
        case RegisterId::Zmm7:
        case RegisterId::Zmm8:
        case RegisterId::Zmm9:
        case RegisterId::Zmm10:
        case RegisterId::Zmm11:
        case RegisterId::Zmm12:
        case RegisterId::Zmm13:
        case RegisterId::Zmm14:
        case RegisterId::Zmm15:
        case RegisterId::Zmm16:
        case RegisterId::Zmm17:
        case RegisterId::Zmm18:
        case RegisterId::Zmm19:
        case RegisterId::Zmm20:
        case RegisterId::Zmm21:
        case RegisterId::Zmm22:
        case RegisterId::Zmm23:
        case RegisterId::Zmm24:
        case RegisterId::Zmm25:
        case RegisterId::Zmm26:
        case RegisterId::Zmm27:
        case RegisterId::Zmm28:
        case RegisterId::Zmm29:
        case RegisterId::Zmm30:
        case RegisterId::Zmm31:
            return RegisterClass::Zmm;
        case RegisterId::Flags:
        case RegisterId::EFlags:
        case RegisterId::RFlags:
            return RegisterClass::Flags;
        case RegisterId::Ip:
        case RegisterId::Eip:
        case RegisterId::Rip:
            return RegisterClass::IP;
        case RegisterId::Es:
        case RegisterId::Cs:
        case RegisterId::Ss:
        case RegisterId::Ds:
        case RegisterId::Fs:
        case RegisterId::Gs:
        case RegisterId::Gdtr:
        case RegisterId::Ldtr:
        case RegisterId::Idtr:
            return RegisterClass::Segment;
        case RegisterId::Tr:
        case RegisterId::Tr0:
        case RegisterId::Tr1:
        case RegisterId::Tr2:
        case RegisterId::Tr3:
        case RegisterId::Tr4:
        case RegisterId::Tr5:
        case RegisterId::Tr6:
        case RegisterId::Tr7:
            return RegisterClass::Test;
        case RegisterId::Cr0:
        case RegisterId::Cr1:
        case RegisterId::Cr2:
        case RegisterId::Cr3:
        case RegisterId::Cr4:
        case RegisterId::Cr5:
        case RegisterId::Cr6:
        case RegisterId::Cr7:
        case RegisterId::Cr8:
        case RegisterId::Cr9:
        case RegisterId::Cr10:
        case RegisterId::Cr11:
        case RegisterId::Cr12:
        case RegisterId::Cr13:
        case RegisterId::Cr14:
        case RegisterId::Cr15:
            return RegisterClass::Control;
        case RegisterId::Dr0:
        case RegisterId::Dr1:
        case RegisterId::Dr2:
        case RegisterId::Dr3:
        case RegisterId::Dr4:
        case RegisterId::Dr5:
        case RegisterId::Dr6:
        case RegisterId::Dr7:
        case RegisterId::Dr8:
        case RegisterId::Dr9:
        case RegisterId::Dr10:
        case RegisterId::Dr11:
        case RegisterId::Dr12:
        case RegisterId::Dr13:
        case RegisterId::Dr14:
        case RegisterId::Dr15:
            return RegisterClass::Debug;
        case RegisterId::K0:
        case RegisterId::K1:
        case RegisterId::K2:
        case RegisterId::K3:
        case RegisterId::K4:
        case RegisterId::K5:
        case RegisterId::K6:
        case RegisterId::K7:
            return RegisterClass::Mask;
        case RegisterId::Bnd0:
        case RegisterId::Bnd1:
        case RegisterId::Bnd2:
        case RegisterId::Bnd3:
        case RegisterId::BndCfg:
        case RegisterId::BndStatus:
            return RegisterClass::Bound;
        }
        return RegisterClass::Invalid;
    }

} // namespace Dotx64Dbg
