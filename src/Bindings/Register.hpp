#pragma once

namespace Dotx64Dbg {

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

    public enum class Register
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
        Hax = Rax,
        Hcx = Rcx,
        Hdx = Rdx,
        Hbx = Rbx,
        Hsp = Rsp,
        Hbp = Rbp,
        Hsi = Rsi,
        Hdi = Rdi,
        H8 = R8,
        H9 = R9,
        H10 = R10,
        H11 = R11,
        H12 = R12,
        H13 = R13,
        H14 = R14,
        H15 = R15,
        Hip = Rip,
        HFlags = RFlags,
#else
        Hax = Eax,
        Hcx = Ecx,
        Hdx = Edx,
        Hbx = Ebx,
        Hsp = Esp,
        Hbp = Ebp,
        Hsi = Esi,
        Hdi = Edi,
        H8 = R8d,
        H9 = R9d,
        H10 = R10d,
        H11 = R11d,
        H12 = R12d,
        H13 = R13d,
        H14 = R14d,
        H15 = R15d,
        Hip = Eip,
        HFlags = EFlags,
#endif
    };

    static constexpr const char* RegisterNames[] =
    {
        "none",
        // general purpose registers  8-bit
        "al",
        "cl",
        "dl",
        "bl",
        "ah",
        "ch",
        "dh",
        "bh",
        "spl",
        "bpl",
        "sil",
        "dil",
        "r8b",
        "r9b",
        "r10b",
        "r11b",
        "r12b",
        "r13b",
        "r14b",
        "r15b",
        // general purpose registers 16-bit
        "ax",
        "cx",
        "dx",
        "bx",
        "sp",
        "bp",
        "si",
        "di",
        "r8w",
        "r9w",
        "r10w",
        "r11w",
        "r12w",
        "r13w",
        "r14w",
        "r15w",
        // general purpose registers 32-bit
        "eax",
        "ecx",
        "edx",
        "ebx",
        "esp",
        "ebp",
        "esi",
        "edi",
        "r8d",
        "r9d",
        "r10d",
        "r11d",
        "r12d",
        "r13d",
        "r14d",
        "r15d",
        // general purpose registers 64-bit
        "rax",
        "rcx",
        "rdx",
        "rbx",
        "rsp",
        "rbp",
        "rsi",
        "rdi",
        "r8",
        "r9",
        "r10",
        "r11",
        "r12",
        "r13",
        "r14",
        "r15",
        // floating point legacy registers
        "st0",
        "st1",
        "st2",
        "st3",
        "st4",
        "st5",
        "st6",
        "st7",
        "x87control",
        "x87status",
        "x87tag",
        // floating point multimedia registers
        "mm0",
        "mm1",
        "mm2",
        "mm3",
        "mm4",
        "mm5",
        "mm6",
        "mm7",
        // floating point vector registers 128-bit
        "xmm0",
        "xmm1",
        "xmm2",
        "xmm3",
        "xmm4",
        "xmm5",
        "xmm6",
        "xmm7",
        "xmm8",
        "xmm9",
        "xmm10",
        "xmm11",
        "xmm12",
        "xmm13",
        "xmm14",
        "xmm15",
        "xmm16",
        "xmm17",
        "xmm18",
        "xmm19",
        "xmm20",
        "xmm21",
        "xmm22",
        "xmm23",
        "xmm24",
        "xmm25",
        "xmm26",
        "xmm27",
        "xmm28",
        "xmm29",
        "xmm30",
        "xmm31",
        // floating point vector registers 256-bit
        "ymm0",
        "ymm1",
        "ymm2",
        "ymm3",
        "ymm4",
        "ymm5",
        "ymm6",
        "ymm7",
        "ymm8",
        "ymm9",
        "ymm10",
        "ymm11",
        "ymm12",
        "ymm13",
        "ymm14",
        "ymm15",
        "ymm16",
        "ymm17",
        "ymm18",
        "ymm19",
        "ymm20",
        "ymm21",
        "ymm22",
        "ymm23",
        "ymm24",
        "ymm25",
        "ymm26",
        "ymm27",
        "ymm28",
        "ymm29",
        "ymm30",
        "ymm31",
        // floating point vector registers 512-bit
        "zmm0",
        "zmm1",
        "zmm2",
        "zmm3",
        "zmm4",
        "zmm5",
        "zmm6",
        "zmm7",
        "zmm8",
        "zmm9",
        "zmm10",
        "zmm11",
        "zmm12",
        "zmm13",
        "zmm14",
        "zmm15",
        "zmm16",
        "zmm17",
        "zmm18",
        "zmm19",
        "zmm20",
        "zmm21",
        "zmm22",
        "zmm23",
        "zmm24",
        "zmm25",
        "zmm26",
        "zmm27",
        "zmm28",
        "zmm29",
        "zmm30",
        "zmm31",
        // flags registers
        "flags",
        "eflags",
        "rflags",
        // instruction-pointer registers
        "ip",
        "eip",
        "rip",
        // segment registers
        "es",
        "cs",
        "ss",
        "ds",
        "fs",
        "gs",
        // table registers
        "gdtr",
        "ldtr",
        "idtr",
        "tr",
        // test registers
        "tr0",
        "tr1",
        "tr2",
        "tr3",
        "tr4",
        "tr5",
        "tr6",
        "tr7",
        // control registers
        "cr0",
        "cr1",
        "cr2",
        "cr3",
        "cr4",
        "cr5",
        "cr6",
        "cr7",
        "cr8",
        "cr9",
        "cr10",
        "cr11",
        "cr12",
        "cr13",
        "cr14",
        "cr15",
        // debug registers
        "dr0",
        "dr1",
        "dr2",
        "dr3",
        "dr4",
        "dr5",
        "dr6",
        "dr7",
        "dr8",
        "dr9",
        "dr10",
        "dr11",
        "dr12",
        "dr13",
        "dr14",
        "dr15",
        // mask registers
        "k0",
        "k1",
        "k2",
        "k3",
        "k4",
        "k5",
        "k6",
        "k7",
        // bound registers
        "bnd0",
        "bnd1",
        "bnd2",
        "bnd3",
        "bndcfg",
        "bndstatus",
        // uncategorized
        "mxcsr",
        "pkru",
        "xcr0",
    };

    inline const char* RegisterGetName(Register id)
    {
        return RegisterNames[static_cast<int>(id)];
    }

    inline int RegisterGetSize(Register id)
    {
        switch (id)
        {
        case Register::None:
            return 0;
        case Register::Al:
        case Register::Cl:
        case Register::Dl:
        case Register::Bl:
        case Register::Ah:
        case Register::Ch:
        case Register::Dh:
        case Register::Bh:
        case Register::Spl:
        case Register::Bpl:
        case Register::Sil:
        case Register::Dil:
        case Register::R8b:
        case Register::R9b:
        case Register::R10b:
        case Register::R11b:
        case Register::R12b:
        case Register::R13b:
        case Register::R14b:
        case Register::R15b:
            return 8;
        case Register::Ax:
        case Register::Cx:
        case Register::Dx:
        case Register::Bx:
        case Register::Sp:
        case Register::Bp:
        case Register::Si:
        case Register::Di:
        case Register::R8w:
        case Register::R9w:
        case Register::R10w:
        case Register::R11w:
        case Register::R12w:
        case Register::R13w:
        case Register::R14w:
        case Register::R15w:
            return 16;
        case Register::Eax:
        case Register::Ecx:
        case Register::Edx:
        case Register::Ebx:
        case Register::Esp:
        case Register::Ebp:
        case Register::Esi:
        case Register::Edi:
        case Register::R8d:
        case Register::R9d:
        case Register::R10d:
        case Register::R11d:
        case Register::R12d:
        case Register::R13d:
        case Register::R14d:
        case Register::R15d:
            return 32;
        case Register::Rax:
        case Register::Rcx:
        case Register::Rdx:
        case Register::Rbx:
        case Register::Rsp:
        case Register::Rbp:
        case Register::Rsi:
        case Register::Rdi:
        case Register::R8:
        case Register::R9:
        case Register::R10:
        case Register::R11:
        case Register::R12:
        case Register::R13:
        case Register::R14:
        case Register::R15:
            return 64;
        case Register::St0:
        case Register::St1:
        case Register::St2:
        case Register::St3:
        case Register::St4:
        case Register::St5:
        case Register::St6:
        case Register::St7:
            return 80;
        case Register::X87Control:
        case Register::X87Status:
        case Register::X87Tag:
            return 16;
        case Register::Mm0:
        case Register::Mm1:
        case Register::Mm2:
        case Register::Mm3:
        case Register::Mm4:
        case Register::Mm5:
        case Register::Mm6:
        case Register::Mm7:
            return 64;
        case Register::Xmm0:
        case Register::Xmm1:
        case Register::Xmm2:
        case Register::Xmm3:
        case Register::Xmm4:
        case Register::Xmm5:
        case Register::Xmm6:
        case Register::Xmm7:
        case Register::Xmm8:
        case Register::Xmm9:
        case Register::Xmm10:
        case Register::Xmm11:
        case Register::Xmm12:
        case Register::Xmm13:
        case Register::Xmm14:
        case Register::Xmm15:
        case Register::Xmm16:
        case Register::Xmm17:
        case Register::Xmm18:
        case Register::Xmm19:
        case Register::Xmm20:
        case Register::Xmm21:
        case Register::Xmm22:
        case Register::Xmm23:
        case Register::Xmm24:
        case Register::Xmm25:
        case Register::Xmm26:
        case Register::Xmm27:
        case Register::Xmm28:
        case Register::Xmm29:
        case Register::Xmm30:
        case Register::Xmm31:
            return 128;
        case Register::Ymm0:
        case Register::Ymm1:
        case Register::Ymm2:
        case Register::Ymm3:
        case Register::Ymm4:
        case Register::Ymm5:
        case Register::Ymm6:
        case Register::Ymm7:
        case Register::Ymm8:
        case Register::Ymm9:
        case Register::Ymm10:
        case Register::Ymm11:
        case Register::Ymm12:
        case Register::Ymm13:
        case Register::Ymm14:
        case Register::Ymm15:
        case Register::Ymm16:
        case Register::Ymm17:
        case Register::Ymm18:
        case Register::Ymm19:
        case Register::Ymm20:
        case Register::Ymm21:
        case Register::Ymm22:
        case Register::Ymm23:
        case Register::Ymm24:
        case Register::Ymm25:
        case Register::Ymm26:
        case Register::Ymm27:
        case Register::Ymm28:
        case Register::Ymm29:
        case Register::Ymm30:
        case Register::Ymm31:
            return 256;
        case Register::Zmm0:
        case Register::Zmm1:
        case Register::Zmm2:
        case Register::Zmm3:
        case Register::Zmm4:
        case Register::Zmm5:
        case Register::Zmm6:
        case Register::Zmm7:
        case Register::Zmm8:
        case Register::Zmm9:
        case Register::Zmm10:
        case Register::Zmm11:
        case Register::Zmm12:
        case Register::Zmm13:
        case Register::Zmm14:
        case Register::Zmm15:
        case Register::Zmm16:
        case Register::Zmm17:
        case Register::Zmm18:
        case Register::Zmm19:
        case Register::Zmm20:
        case Register::Zmm21:
        case Register::Zmm22:
        case Register::Zmm23:
        case Register::Zmm24:
        case Register::Zmm25:
        case Register::Zmm26:
        case Register::Zmm27:
        case Register::Zmm28:
        case Register::Zmm29:
        case Register::Zmm30:
        case Register::Zmm31:
            return 512;
        case Register::Flags:
            return 16;
        case Register::EFlags:
            return 32;
        case Register::RFlags:
            return 64;
        case Register::Ip:
            return 16;
        case Register::Eip:
            return 32;
        case Register::Rip:
            return 64;
        case Register::Es:
        case Register::Cs:
        case Register::Ss:
        case Register::Ds:
        case Register::Fs:
        case Register::Gs:
            return 16;
        case Register::Gdtr:
        case Register::Ldtr:
        case Register::Idtr:
        case Register::Tr:
            return 16;
        case Register::Tr0:
        case Register::Tr1:
        case Register::Tr2:
        case Register::Tr3:
        case Register::Tr4:
        case Register::Tr5:
        case Register::Tr6:
        case Register::Tr7:
            return 64;
        case Register::Cr0:
        case Register::Cr1:
        case Register::Cr2:
        case Register::Cr3:
        case Register::Cr4:
        case Register::Cr5:
        case Register::Cr6:
        case Register::Cr7:
        case Register::Cr8:
        case Register::Cr9:
        case Register::Cr10:
        case Register::Cr11:
        case Register::Cr12:
        case Register::Cr13:
        case Register::Cr14:
        case Register::Cr15:
            return 64;
        case Register::Dr0:
        case Register::Dr1:
        case Register::Dr2:
        case Register::Dr3:
        case Register::Dr4:
        case Register::Dr5:
        case Register::Dr6:
        case Register::Dr7:
        case Register::Dr8:
        case Register::Dr9:
        case Register::Dr10:
        case Register::Dr11:
        case Register::Dr12:
        case Register::Dr13:
        case Register::Dr14:
        case Register::Dr15:
#ifdef _M_AMD64
            return 64;
#else
            return 32;
#endif
        case Register::K0:
        case Register::K1:
        case Register::K2:
        case Register::K3:
        case Register::K4:
        case Register::K5:
        case Register::K6:
        case Register::K7:
            return 64;
        case Register::Bnd0:
        case Register::Bnd1:
        case Register::Bnd2:
        case Register::Bnd3:
            return 128;
        case Register::BndCfg:
        case Register::BndStatus:
            return 16;
        case Register::Mxcsr:
            return 32;
        case Register::Pkru:
        case Register::Xcr0:
            return 0;
        }
        return 0;
    }

    inline Register RegisterGetRoot(Register id)
    {
        switch (id)
        {
        case Register::Al:
        case Register::Ax:
        case Register::Ah:
#ifdef _M_AMD64
            return Register::Rax;
#else
            return Register::Eax;
#endif
        case Register::Cl:
        case Register::Cx:
        case Register::Ch:
#ifdef _M_AMD64
            return Register::Rcx;
#else
            return Register::Ecx;
#endif
        case Register::Dl:
        case Register::Dx:
        case Register::Dh:
#ifdef _M_AMD64
            return Register::Rdx;
#else
            return Register::Edx;
#endif
        case Register::Bl:
        case Register::Bx:
        case Register::Bh:
#ifdef _M_AMD64
            return Register::Rbx;
#else
            return Register::Ebx;
#endif
        case Register::Sp:
        case Register::Spl:
#ifdef _M_AMD64
            return Register::Rsp;
#else
            return Register::Esp;
#endif
        case Register::Bpl:
        case Register::Bp:
#ifdef _M_AMD64
            return Register::Rbp;
#else
            return Register::Ebp;
#endif
        case Register::Si:
        case Register::Sil:
#ifdef _M_AMD64
            return Register::Rsi;
#else
            return Register::Esi;
#endif
        case Register::Di:
        case Register::Dil:
#ifdef _M_AMD64
            return Register::Rdi;
#else
            return Register::Edi;
#endif
#ifdef _M_AMD64
        case Register::R8b:
        case Register::R8w:
            return Register::R8;
        case Register::R9b:
        case Register::R9w:
            return Register::R9;
        case Register::R10b:
        case Register::R10w:
            return Register::R10;
        case Register::R11b:
        case Register::R11w:
            return Register::R11;
        case Register::R12b:
        case Register::R12w:
            return Register::R12;
        case Register::R13b:
        case Register::R13w:
            return Register::R13;
        case Register::R14b:
        case Register::R14w:
            return Register::R14;
        case Register::R15b:
        case Register::R15w:
            return Register::R15;
#endif
        case Register::Eax:
#ifdef _M_AMD64
            return Register::Rax;
#endif
        case Register::Ecx:
#ifdef _M_AMD64
            return Register::Rcx;
#endif
        case Register::Edx:
#ifdef _M_AMD64
            return Register::Rdx;
#endif
        case Register::Ebx:
#ifdef _M_AMD64
            return Register::Rbx;
#endif
        case Register::Esp:
#ifdef _M_AMD64
            return Register::Rsp;
#endif
        case Register::Ebp:
#ifdef _M_AMD64
            return Register::Rbp;
#endif
        case Register::Esi:
#ifdef _M_AMD64
            return Register::Rsi;
#endif
        case Register::Edi:
#ifdef _M_AMD64
            return Register::Rdi;
#endif
            break;
#ifdef _M_AMD64
        case Register::R8d:
#ifdef _M_AMD64
            return Register::R8;
#endif
        case Register::R9d:
#ifdef _M_AMD64
            return Register::R9;
#endif
        case Register::R10d:
#ifdef _M_AMD64
            return Register::R10;
#endif
        case Register::R11d:
#ifdef _M_AMD64
            return Register::R11;
#endif
        case Register::R12d:
#ifdef _M_AMD64
            return Register::R12;
#endif
        case Register::R13d:
#ifdef _M_AMD64
            return Register::R13;
#endif
        case Register::R14d:
#ifdef _M_AMD64
            return Register::R14;
#endif
        case Register::R15d:
#ifdef _M_AMD64
            return Register::R15;
#endif
            break;
#endif
        case Register::Flags:
#ifdef _M_AMD64
            return Register::RFlags;
#else
            return Register::EFlags;
#endif
        case Register::EFlags:
#ifdef _M_AMD64
            return Register::RFlags;
#endif
        case Register::RFlags:
        case Register::Ip:
#ifdef _M_AMD64
            return Register::Rip;
#else
            return Register::Eip;
#endif
        case Register::Eip:
#ifdef _M_AMD64
            return Register::Rip;
#endif
        case Register::Rip:
            break;
        }
        return Register::None;
    }

    inline Register RegisterGetParent(Register id)
    {
        switch (id)
        {
        case Register::Al:
            return Register::Ax;
        case Register::Ax:
            return Register::Eax;
        case Register::Ah:
            return Register::Ax;
        case Register::Cl:
            return Register::Cx;
        case Register::Cx:
            return Register::Ecx;
        case Register::Ch:
            return Register::Cx;
        case Register::Dl:
            return Register::Dx;
        case Register::Dx:
            return Register::Edx;
        case Register::Dh:
            return Register::Dx;
        case Register::Bl:
            return Register::Bx;
        case Register::Bx:
            return Register::Ebx;
        case Register::Bh:
            return Register::Bx;
        case Register::Sp:
            return Register::Esp;
        case Register::Spl:
            return Register::Sp;
        case Register::Bpl:
            return Register::Bp;
        case Register::Bp:
            return Register::Ebp;
        case Register::Si:
            return Register::Esi;
        case Register::Sil:
            return Register::Si;
        case Register::Di:
            return Register::Edi;
        case Register::Dil:
            return Register::Di;
#ifdef _M_AMD64
        case Register::R8b:
            return Register::R8w;
        case Register::R8w:
            return Register::R8d;
        case Register::R9b:
            return Register::R9w;
        case Register::R9w:
            return Register::R9d;
        case Register::R10b:
            return Register::R10w;
        case Register::R10w:
            return Register::R10d;
        case Register::R11b:
            return Register::R11w;
        case Register::R11w:
            return Register::R11d;
        case Register::R12b:
            return Register::R12w;
        case Register::R12w:
            return Register::R12d;
        case Register::R13b:
            return Register::R13w;
        case Register::R13w:
            return Register::R13d;
        case Register::R14b:
            return Register::R14w;
        case Register::R14w:
            return Register::R14d;
        case Register::R15b:
            return Register::R15w;
        case Register::R15w:
            return Register::R15d;
#endif
        case Register::Eax:
#ifdef _M_AMD64
            return Register::Rax;
#else
            return Register::None;
#endif
        case Register::Ecx:
#ifdef _M_AMD64
            return Register::Rcx;
#else
            return Register::None;
#endif
        case Register::Edx:
#ifdef _M_AMD64
            return Register::Rdx;
#else
            return Register::None;
#endif
        case Register::Ebx:
#ifdef _M_AMD64
            return Register::Rbx;
#endif
        case Register::Esp:
#ifdef _M_AMD64
            return Register::Rsp;
#else
            return Register::None;
#endif
        case Register::Ebp:
#ifdef _M_AMD64
            return Register::Rbp;
#else
            return Register::None;
#endif
        case Register::Esi:
#ifdef _M_AMD64
            return Register::Rsi;
#else
            return Register::None;
#endif
        case Register::Edi:
#ifdef _M_AMD64
            return Register::Rdi;
#else
            return Register::None;
#endif

#ifdef _M_AMD64
        case Register::R8d:
#ifdef _M_AMD64
            return Register::R8;
#else
            return Register::None;
#endif
        case Register::R9d:
#ifdef _M_AMD64
            return Register::R9;
#else
            return Register::None;
#endif
        case Register::R10d:
#ifdef _M_AMD64
            return Register::R10;
#else
            return Register::None;
#endif
        case Register::R11d:
#ifdef _M_AMD64
            return Register::R11;
#else
            return Register::None;
#endif
        case Register::R12d:
#ifdef _M_AMD64
            return Register::R12;
#else
            return Register::None;
#endif
        case Register::R13d:
#ifdef _M_AMD64
            return Register::R13;
#else
            return Register::None;
#endif
        case Register::R14d:
#ifdef _M_AMD64
            return Register::R14;
#else
            return Register::None;
#endif
        case Register::R15d:
#ifdef _M_AMD64
            return Register::R15;
#else
            return Register::None;
#endif

#endif
        case Register::Flags:
#ifdef _M_AMD64
            return Register::RFlags;
#else
            return Register::EFlags;
#endif
        case Register::EFlags:
#ifdef _M_AMD64
            return Register::RFlags;
#endif
        case Register::RFlags:
        case Register::Ip:
#ifdef _M_AMD64
            return Register::Rip;
#else
            return Register::Eip;
#endif
        case Register::Eip:
#ifdef _M_AMD64
            return Register::Rip;
#else
            return Register::None;
#endif
        case Register::Rip:
            break;
        }

        return Register::None;
    }

    inline int32_t RegisterGetOffsetForRoot(Register id)
    {
        switch (id)
        {
        case Register::Ah:
        case Register::Bh:
        case Register::Ch:
        case Register::Dh:
            return 8;
        }
        return 0;
    }

    inline RegisterClass RegisterGetClass(Register id)
    {
        switch (id)
        {
        case Register::None:
            return RegisterClass::Invalid;
        case Register::Al:
        case Register::Cl:
        case Register::Dl:
        case Register::Bl:
        case Register::Ah:
        case Register::Ch:
        case Register::Dh:
        case Register::Bh:
        case Register::Spl:
        case Register::Bpl:
        case Register::Sil:
        case Register::Dil:
        case Register::R8b:
        case Register::R9b:
        case Register::R10b:
        case Register::R11b:
        case Register::R12b:
        case Register::R13b:
        case Register::R14b:
        case Register::R15b:
            return RegisterClass::Gp8;
        case Register::Ax:
        case Register::Cx:
        case Register::Dx:
        case Register::Bx:
        case Register::Sp:
        case Register::Bp:
        case Register::Si:
        case Register::Di:
        case Register::R8w:
        case Register::R9w:
        case Register::R10w:
        case Register::R11w:
        case Register::R12w:
        case Register::R13w:
        case Register::R14w:
        case Register::R15w:
            return RegisterClass::Gp16;
        case Register::Eax:
        case Register::Ecx:
        case Register::Edx:
        case Register::Ebx:
        case Register::Esp:
        case Register::Ebp:
        case Register::Esi:
        case Register::Edi:
        case Register::R8d:
        case Register::R9d:
        case Register::R10d:
        case Register::R11d:
        case Register::R12d:
        case Register::R13d:
        case Register::R14d:
        case Register::R15d:
            return RegisterClass::Gp32;
        case Register::Rax:
        case Register::Rcx:
        case Register::Rdx:
        case Register::Rbx:
        case Register::Rsp:
        case Register::Rbp:
        case Register::Rsi:
        case Register::Rdi:
        case Register::R8:
        case Register::R9:
        case Register::R10:
        case Register::R11:
        case Register::R12:
        case Register::R13:
        case Register::R14:
        case Register::R15:
            return RegisterClass::Gp64;
        case Register::St0:
        case Register::St1:
        case Register::St2:
        case Register::St3:
        case Register::St4:
        case Register::St5:
        case Register::St6:
        case Register::St7:
            return RegisterClass::X87;
        case Register::X87Control:
        case Register::X87Status:
        case Register::X87Tag:
            return RegisterClass::Control;
        case Register::Mm0:
        case Register::Mm1:
        case Register::Mm2:
        case Register::Mm3:
        case Register::Mm4:
        case Register::Mm5:
        case Register::Mm6:
        case Register::Mm7:
            return RegisterClass::Mmx;
        case Register::Xmm0:
        case Register::Xmm1:
        case Register::Xmm2:
        case Register::Xmm3:
        case Register::Xmm4:
        case Register::Xmm5:
        case Register::Xmm6:
        case Register::Xmm7:
        case Register::Xmm8:
        case Register::Xmm9:
        case Register::Xmm10:
        case Register::Xmm11:
        case Register::Xmm12:
        case Register::Xmm13:
        case Register::Xmm14:
        case Register::Xmm15:
        case Register::Xmm16:
        case Register::Xmm17:
        case Register::Xmm18:
        case Register::Xmm19:
        case Register::Xmm20:
        case Register::Xmm21:
        case Register::Xmm22:
        case Register::Xmm23:
        case Register::Xmm24:
        case Register::Xmm25:
        case Register::Xmm26:
        case Register::Xmm27:
        case Register::Xmm28:
        case Register::Xmm29:
        case Register::Xmm30:
        case Register::Xmm31:
            return RegisterClass::Xmm;
        case Register::Ymm0:
        case Register::Ymm1:
        case Register::Ymm2:
        case Register::Ymm3:
        case Register::Ymm4:
        case Register::Ymm5:
        case Register::Ymm6:
        case Register::Ymm7:
        case Register::Ymm8:
        case Register::Ymm9:
        case Register::Ymm10:
        case Register::Ymm11:
        case Register::Ymm12:
        case Register::Ymm13:
        case Register::Ymm14:
        case Register::Ymm15:
        case Register::Ymm16:
        case Register::Ymm17:
        case Register::Ymm18:
        case Register::Ymm19:
        case Register::Ymm20:
        case Register::Ymm21:
        case Register::Ymm22:
        case Register::Ymm23:
        case Register::Ymm24:
        case Register::Ymm25:
        case Register::Ymm26:
        case Register::Ymm27:
        case Register::Ymm28:
        case Register::Ymm29:
        case Register::Ymm30:
        case Register::Ymm31:
            return RegisterClass::Ymm;
        case Register::Zmm0:
        case Register::Zmm1:
        case Register::Zmm2:
        case Register::Zmm3:
        case Register::Zmm4:
        case Register::Zmm5:
        case Register::Zmm6:
        case Register::Zmm7:
        case Register::Zmm8:
        case Register::Zmm9:
        case Register::Zmm10:
        case Register::Zmm11:
        case Register::Zmm12:
        case Register::Zmm13:
        case Register::Zmm14:
        case Register::Zmm15:
        case Register::Zmm16:
        case Register::Zmm17:
        case Register::Zmm18:
        case Register::Zmm19:
        case Register::Zmm20:
        case Register::Zmm21:
        case Register::Zmm22:
        case Register::Zmm23:
        case Register::Zmm24:
        case Register::Zmm25:
        case Register::Zmm26:
        case Register::Zmm27:
        case Register::Zmm28:
        case Register::Zmm29:
        case Register::Zmm30:
        case Register::Zmm31:
            return RegisterClass::Zmm;
        case Register::Flags:
        case Register::EFlags:
        case Register::RFlags:
            return RegisterClass::Flags;
        case Register::Ip:
        case Register::Eip:
        case Register::Rip:
            return RegisterClass::IP;
        case Register::Es:
        case Register::Cs:
        case Register::Ss:
        case Register::Ds:
        case Register::Fs:
        case Register::Gs:
        case Register::Gdtr:
        case Register::Ldtr:
        case Register::Idtr:
            return RegisterClass::Segment;
        case Register::Tr:
        case Register::Tr0:
        case Register::Tr1:
        case Register::Tr2:
        case Register::Tr3:
        case Register::Tr4:
        case Register::Tr5:
        case Register::Tr6:
        case Register::Tr7:
            return RegisterClass::Test;
        case Register::Cr0:
        case Register::Cr1:
        case Register::Cr2:
        case Register::Cr3:
        case Register::Cr4:
        case Register::Cr5:
        case Register::Cr6:
        case Register::Cr7:
        case Register::Cr8:
        case Register::Cr9:
        case Register::Cr10:
        case Register::Cr11:
        case Register::Cr12:
        case Register::Cr13:
        case Register::Cr14:
        case Register::Cr15:
            return RegisterClass::Control;
        case Register::Dr0:
        case Register::Dr1:
        case Register::Dr2:
        case Register::Dr3:
        case Register::Dr4:
        case Register::Dr5:
        case Register::Dr6:
        case Register::Dr7:
        case Register::Dr8:
        case Register::Dr9:
        case Register::Dr10:
        case Register::Dr11:
        case Register::Dr12:
        case Register::Dr13:
        case Register::Dr14:
        case Register::Dr15:
            return RegisterClass::Debug;
        case Register::K0:
        case Register::K1:
        case Register::K2:
        case Register::K3:
        case Register::K4:
        case Register::K5:
        case Register::K6:
        case Register::K7:
            return RegisterClass::Mask;
        case Register::Bnd0:
        case Register::Bnd1:
        case Register::Bnd2:
        case Register::Bnd3:
        case Register::BndCfg:
        case Register::BndStatus:
            return RegisterClass::Bound;
        }
        return RegisterClass::Invalid;
    }


}
