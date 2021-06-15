#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"
#include "Register.hpp"
#include "pluginsdk/TitanEngine/TitanEngine.h"

namespace Dotx64Dbg::Native
{
    public ref struct ThreadInfo
    {
        uint32_t Id;
        uint64_t Handle;
        uintptr_t IP;
        uint32_t SuspendCount;
        uint32_t LastError;
        uint64_t UserTime;
        uint64_t KernelTime;
        uint64_t CreationTime;
        uint64_t Cycles;
    };

    public ref class Thread
    {
    public:
        static uint32_t GetActiveThreadId()
        {
            return DbgGetThreadId();
        }

        static bool SetActiveThreadId(uint32_t threadId)
        {
            char cmd[128] = {};
            sprintf_s(cmd, "switchthread %X", (uint32_t)threadId);

            return DbgCmdExecDirect(cmd);
        }

        static uint32_t GetMainThreadId()
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            uint32_t id = 0;
            for (int i = 0; i < tl.count; i++)
            {
                const auto& th = tl.list[i];
                if (th.BasicInfo.ThreadNumber == 0)
                {
                    id = th.BasicInfo.ThreadId;
                    break;
                }
            }

            BridgeFree(tl.list);
            return id;
        }

        static bool IsValid(uint32_t threadId)
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            bool valid = false;
            for (int i = 0; i < tl.count; i++)
            {
                if (threadId == tl.list[i].BasicInfo.ThreadId)
                {
                    valid = true;
                    break;
                }
            }

            BridgeFree(tl.list);

            return valid;
        }

        static array<System::UInt32>^ GetThreads()
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            array<System::UInt32>^ res = gcnew array<System::UInt32>(tl.count);
            for (int i = 0; i < tl.count; i++)
            {
                res[i] = tl.list[i].BasicInfo.ThreadId;
            }

            BridgeFree(tl.list);

            return res;
        }

        static bool Resume(uint64_t hThread)
        {
            return false;
        }

        static bool Pause(uint64_t hThread)
        {
            return false;
        }

        static ThreadInfo^ GetThreadInfo(uint32_t id)
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            ThreadInfo^ res = nullptr;
            for (int i = 0; i < tl.count; i++)
            {
                auto& th = tl.list[i];
                if (th.BasicInfo.ThreadId != id)
                    continue;

                res = gcnew ThreadInfo();
                res->Id = id;
                res->Handle = reinterpret_cast<uint64_t>(th.BasicInfo.Handle);
                res->IP = th.ThreadCip;
                res->SuspendCount = th.SuspendCount;
                res->LastError = th.LastError;
                res->UserTime = static_cast<uint64_t>(th.UserTime.dwHighDateTime) << 32 | th.UserTime.dwLowDateTime;
                res->KernelTime = static_cast<uint64_t>(th.KernelTime.dwHighDateTime) << 32 | th.KernelTime.dwLowDateTime;
                res->CreationTime = static_cast<uint64_t>(th.CreationTime.dwHighDateTime) << 32 | th.CreationTime.dwLowDateTime;
                res->Cycles = th.Cycles;

                break;
            }

            BridgeFree(tl.list);

            return res;
        }

        static array<System::Byte>^ ReadRegister(uint64_t hThread, int reg, int size, int offset)
        {
            array<System::Byte>^ res = gcnew array<System::Byte>(size);

            pin_ptr<uint8_t> p = &res[0];
            uint8_t* data = p;

            ULONG_PTR val = GetContextDataEx(reinterpret_cast<HANDLE>(hThread), reg);
            std::memcpy(data, reinterpret_cast<const uint8_t*>(&val) + offset, size);

            return res;
        }

        static array<System::Byte>^ ReadRegister(uint64_t hThread, int reg, int size)
        {
            return ReadRegister(hThread, reg, size, 0);
        }

        static array<System::Byte>^ GetRegisterData(uint64_t hThread, Register reg)
        {
            switch (reg)
            {
            case Register::None:
                return gcnew array<System::Byte>(0);
            case Register::Al:
                return ReadRegister(hThread, UE_RAX, 1);
            case Register::Cl:
                return ReadRegister(hThread, UE_RCX, 1);
            case Register::Dl:
                return ReadRegister(hThread, UE_RDX, 1);
            case Register::Bl:
                return ReadRegister(hThread, UE_RBX, 1);
            case Register::Ah:
                return ReadRegister(hThread, UE_RAX, 1, 1);
            case Register::Ch:
                return ReadRegister(hThread, UE_RCX, 1, 1);
            case Register::Dh:
                return ReadRegister(hThread, UE_RDX, 1, 1);
            case Register::Bh:
                return ReadRegister(hThread, UE_RBX, 1, 1);
            case Register::Spl:
                return ReadRegister(hThread, UE_RSP, 1);
            case Register::Bpl:
                return ReadRegister(hThread, UE_RBP, 1);
            case Register::Sil:
                return ReadRegister(hThread, UE_RSI, 1);
            case Register::Dil:
                return ReadRegister(hThread, UE_RDI, 1);
            case Register::R8b:
                return ReadRegister(hThread, UE_R8, 1);
            case Register::R9b:
                return ReadRegister(hThread, UE_R9, 1);
            case Register::R10b:
                return ReadRegister(hThread, UE_R10, 1);
            case Register::R11b:
                return ReadRegister(hThread, UE_R11, 1);
            case Register::R12b:
                return ReadRegister(hThread, UE_R12, 1);
            case Register::R13b:
                return ReadRegister(hThread, UE_R13, 1);
            case Register::R14b:
                return ReadRegister(hThread, UE_R14, 1);
            case Register::R15b:
                return ReadRegister(hThread, UE_R15, 1);
            case Register::Ax:
                return ReadRegister(hThread, UE_RAX, 2);
            case Register::Cx:
                return ReadRegister(hThread, UE_RCX, 2);
            case Register::Dx:
                return ReadRegister(hThread, UE_RDX, 2);
            case Register::Bx:
                return ReadRegister(hThread, UE_RBX, 2);
            case Register::Sp:
                return ReadRegister(hThread, UE_RSP, 2);
            case Register::Bp:
                return ReadRegister(hThread, UE_RBP, 2);
            case Register::Si:
                return ReadRegister(hThread, UE_RSI, 2);
            case Register::Di:
                return ReadRegister(hThread, UE_RDI, 2);
            case Register::R8w:
                return ReadRegister(hThread, UE_R8, 2);
            case Register::R9w:
                return ReadRegister(hThread, UE_R9, 2);
            case Register::R10w:
                return ReadRegister(hThread, UE_R10, 2);
            case Register::R11w:
                return ReadRegister(hThread, UE_R11, 2);
            case Register::R12w:
                return ReadRegister(hThread, UE_R12, 2);
            case Register::R13w:
                return ReadRegister(hThread, UE_R13, 2);
            case Register::R14w:
                return ReadRegister(hThread, UE_R14, 2);
            case Register::R15w:
                return ReadRegister(hThread, UE_R15, 2);
            case Register::Eax:
                return ReadRegister(hThread, UE_RAX, 4);
            case Register::Ecx:
                return ReadRegister(hThread, UE_RCX, 4);
            case Register::Edx:
                return ReadRegister(hThread, UE_RDX, 4);
            case Register::Ebx:
                return ReadRegister(hThread, UE_RBX, 4);
            case Register::Esp:
                return ReadRegister(hThread, UE_RSP, 4);
            case Register::Ebp:
                return ReadRegister(hThread, UE_RBP, 4);
            case Register::Esi:
                return ReadRegister(hThread, UE_RSI, 4);
            case Register::Edi:
                return ReadRegister(hThread, UE_RDI, 4);
            case Register::R8d:
                return ReadRegister(hThread, UE_R8, 4);
            case Register::R9d:
                return ReadRegister(hThread, UE_R9, 4);
            case Register::R10d:
                return ReadRegister(hThread, UE_R10, 4);
            case Register::R11d:
                return ReadRegister(hThread, UE_R11, 4);
            case Register::R12d:
                return ReadRegister(hThread, UE_R12, 4);
            case Register::R13d:
                return ReadRegister(hThread, UE_R13, 4);
            case Register::R14d:
                return ReadRegister(hThread, UE_R14, 4);
            case Register::R15d:
                return ReadRegister(hThread, UE_R15, 4);
            case Register::Rax:
                return ReadRegister(hThread, UE_RAX, 8);
            case Register::Rcx:
                return ReadRegister(hThread, UE_RCX, 8);
            case Register::Rdx:
                return ReadRegister(hThread, UE_RDX, 8);
            case Register::Rbx:
                return ReadRegister(hThread, UE_RBP, 8);
            case Register::Rsp:
                return ReadRegister(hThread, UE_RSP, 8);
            case Register::Rbp:
                return ReadRegister(hThread, UE_RBP, 8);
            case Register::Rsi:
                return ReadRegister(hThread, UE_RSI, 8);
            case Register::Rdi:
                return ReadRegister(hThread, UE_RDI, 8);
            case Register::R8:
                return ReadRegister(hThread, UE_R8, 8);
            case Register::R9:
                return ReadRegister(hThread, UE_R9, 8);
            case Register::R10:
                return ReadRegister(hThread, UE_R10, 8);
            case Register::R11:
                return ReadRegister(hThread, UE_R11, 8);
            case Register::R12:
                return ReadRegister(hThread, UE_R12, 8);
            case Register::R13:
                return ReadRegister(hThread, UE_R13, 8);
            case Register::R14:
                return ReadRegister(hThread, UE_R14, 8);
            case Register::R15:
                return ReadRegister(hThread, UE_R15, 8);
            case Register::St0:
                break;
            case Register::St1:
                break;
            case Register::St2:
                break;
            case Register::St3:
                break;
            case Register::St4:
                break;
            case Register::St5:
                break;
            case Register::St6:
                break;
            case Register::St7:
                break;
            case Register::X87Control:
                break;
            case Register::X87Status:
                break;
            case Register::X87Tag:
                break;
            case Register::Mm0:
                break;
            case Register::Mm1:
                break;
            case Register::Mm2:
                break;
            case Register::Mm3:
                break;
            case Register::Mm4:
                break;
            case Register::Mm5:
                break;
            case Register::Mm6:
                break;
            case Register::Mm7:
                break;
            case Register::Xmm0:
                break;
            case Register::Xmm1:
                break;
            case Register::Xmm2:
                break;
            case Register::Xmm3:
                break;
            case Register::Xmm4:
                break;
            case Register::Xmm5:
                break;
            case Register::Xmm6:
                break;
            case Register::Xmm7:
                break;
            case Register::Xmm8:
                break;
            case Register::Xmm9:
                break;
            case Register::Xmm10:
                break;
            case Register::Xmm11:
                break;
            case Register::Xmm12:
                break;
            case Register::Xmm13:
                break;
            case Register::Xmm14:
                break;
            case Register::Xmm15:
                break;
            case Register::Xmm16:
                break;
            case Register::Xmm17:
                break;
            case Register::Xmm18:
                break;
            case Register::Xmm19:
                break;
            case Register::Xmm20:
                break;
            case Register::Xmm21:
                break;
            case Register::Xmm22:
                break;
            case Register::Xmm23:
                break;
            case Register::Xmm24:
                break;
            case Register::Xmm25:
                break;
            case Register::Xmm26:
                break;
            case Register::Xmm27:
                break;
            case Register::Xmm28:
                break;
            case Register::Xmm29:
                break;
            case Register::Xmm30:
                break;
            case Register::Xmm31:
                break;
            case Register::Ymm0:
                break;
            case Register::Ymm1:
                break;
            case Register::Ymm2:
                break;
            case Register::Ymm3:
                break;
            case Register::Ymm4:
                break;
            case Register::Ymm5:
                break;
            case Register::Ymm6:
                break;
            case Register::Ymm7:
                break;
            case Register::Ymm8:
                break;
            case Register::Ymm9:
                break;
            case Register::Ymm10:
                break;
            case Register::Ymm11:
                break;
            case Register::Ymm12:
                break;
            case Register::Ymm13:
                break;
            case Register::Ymm14:
                break;
            case Register::Ymm15:
                break;
            case Register::Ymm16:
                break;
            case Register::Ymm17:
                break;
            case Register::Ymm18:
                break;
            case Register::Ymm19:
                break;
            case Register::Ymm20:
                break;
            case Register::Ymm21:
                break;
            case Register::Ymm22:
                break;
            case Register::Ymm23:
                break;
            case Register::Ymm24:
                break;
            case Register::Ymm25:
                break;
            case Register::Ymm26:
                break;
            case Register::Ymm27:
                break;
            case Register::Ymm28:
                break;
            case Register::Ymm29:
                break;
            case Register::Ymm30:
                break;
            case Register::Ymm31:
                break;
            case Register::Zmm0:
                break;
            case Register::Zmm1:
                break;
            case Register::Zmm2:
                break;
            case Register::Zmm3:
                break;
            case Register::Zmm4:
                break;
            case Register::Zmm5:
                break;
            case Register::Zmm6:
                break;
            case Register::Zmm7:
                break;
            case Register::Zmm8:
                break;
            case Register::Zmm9:
                break;
            case Register::Zmm10:
                break;
            case Register::Zmm11:
                break;
            case Register::Zmm12:
                break;
            case Register::Zmm13:
                break;
            case Register::Zmm14:
                break;
            case Register::Zmm15:
                break;
            case Register::Zmm16:
                break;
            case Register::Zmm17:
                break;
            case Register::Zmm18:
                break;
            case Register::Zmm19:
                break;
            case Register::Zmm20:
                break;
            case Register::Zmm21:
                break;
            case Register::Zmm22:
                break;
            case Register::Zmm23:
                break;
            case Register::Zmm24:
                break;
            case Register::Zmm25:
                break;
            case Register::Zmm26:
                break;
            case Register::Zmm27:
                break;
            case Register::Zmm28:
                break;
            case Register::Zmm29:
                break;
            case Register::Zmm30:
                break;
            case Register::Zmm31:
                break;
            case Register::Flags:
                return ReadRegister(hThread, UE_RFLAGS, 2);
            case Register::EFlags:
                return ReadRegister(hThread, UE_RFLAGS, 4);
            case Register::RFlags:
                return ReadRegister(hThread, UE_RFLAGS, 8);
            case Register::Ip:
                return ReadRegister(hThread, UE_RIP, 2);
            case Register::Eip:
                return ReadRegister(hThread, UE_RIP, 4);
            case Register::Rip:
                return ReadRegister(hThread, UE_RIP, 8);
            case Register::Es:
                return ReadRegister(hThread, UE_SEG_ES, 2);
            case Register::Cs:
                return ReadRegister(hThread, UE_SEG_CS, 2);
            case Register::Ss:
                return ReadRegister(hThread, UE_SEG_SS, 2);
            case Register::Ds:
                return ReadRegister(hThread, UE_SEG_DS, 2);
            case Register::Fs:
                return ReadRegister(hThread, UE_SEG_FS, 2);
            case Register::Gs:
                return ReadRegister(hThread, UE_SEG_GS, 2);
            case Register::Gdtr:
                break;
            case Register::Ldtr:
                break;
            case Register::Idtr:
                break;
            case Register::Tr:
                break;
            case Register::Tr0:
                break;
            case Register::Tr1:
                break;
            case Register::Tr2:
                break;
            case Register::Tr3:
                break;
            case Register::Tr4:
                break;
            case Register::Tr5:
                break;
            case Register::Tr6:
                break;
            case Register::Tr7:
                break;
            case Register::Cr0:
                break;
            case Register::Cr1:
                break;
            case Register::Cr2:
                break;
            case Register::Cr3:
                break;
            case Register::Cr4:
                break;
            case Register::Cr5:
                break;
            case Register::Cr6:
                break;
            case Register::Cr7:
                break;
            case Register::Cr8:
                break;
            case Register::Cr9:
                break;
            case Register::Cr10:
                break;
            case Register::Cr11:
                break;
            case Register::Cr12:
                break;
            case Register::Cr13:
                break;
            case Register::Cr14:
                break;
            case Register::Cr15:
                break;
            case Register::Dr0:
                break;
            case Register::Dr1:
                break;
            case Register::Dr2:
                break;
            case Register::Dr3:
                break;
            case Register::Dr4:
                break;
            case Register::Dr5:
                break;
            case Register::Dr6:
                break;
            case Register::Dr7:
                break;
            case Register::Dr8:
                break;
            case Register::Dr9:
                break;
            case Register::Dr10:
                break;
            case Register::Dr11:
                break;
            case Register::Dr12:
                break;
            case Register::Dr13:
                break;
            case Register::Dr14:
                break;
            case Register::Dr15:
                break;
            case Register::K0:
                break;
            case Register::K1:
                break;
            case Register::K2:
                break;
            case Register::K3:
                break;
            case Register::K4:
                break;
            case Register::K5:
                break;
            case Register::K6:
                break;
            case Register::K7:
                break;
            case Register::Bnd0:
                break;
            case Register::Bnd1:
                break;
            case Register::Bnd2:
                break;
            case Register::Bnd3:
                break;
            case Register::BndCfg:
                break;
            case Register::BndStatus:
                break;
            case Register::Mxcsr:
                break;
            case Register::Pkru:
                break;
            case Register::Xcr0:
                break;
            default:
                break;
            }

            // Unsupported.
            return gcnew array<System::Byte>(0);
        }

        static void WriteRegister(uint64_t hThread, array<System::Byte>^ data, int reg, int size, int offset)
        {
            pin_ptr<uint8_t> p = &data[0];
            const uint8_t* ptr = p;

            // This is terrible, but to preserve the data when the write happens on smaller regs we need the
            // value not to be zero.
            ULONG_PTR val = size < sizeof(ULONG_PTR) ? GetContextDataEx(reinterpret_cast<HANDLE>(hThread), reg) : 0;

            std::memcpy(reinterpret_cast<uint8_t*>(&val) + offset, ptr, std::min<size_t>(data->Length, size));

            SetContextDataEx(reinterpret_cast<HANDLE>(hThread), reg, val);
        }

        static void WriteRegister(uint64_t hThread, array<System::Byte>^ data, int reg, int size)
        {
            WriteRegister(hThread, data, reg, size, 0);
            GuiUpdateRegisterView();
        }

        static void SetRegisterData(uint64_t hThread, Register reg, array<System::Byte>^ data)
        {
            switch (reg)
            {
            case Register::None:
                return;
            case Register::Al:
                return WriteRegister(hThread, data, UE_RAX, 1);
            case Register::Cl:
                return WriteRegister(hThread, data, UE_RCX, 1);
            case Register::Dl:
                return WriteRegister(hThread, data, UE_RDX, 1);
            case Register::Bl:
                return WriteRegister(hThread, data, UE_RBX, 1);
            case Register::Ah:
                return WriteRegister(hThread, data, UE_RAX, 1, 1);
            case Register::Ch:
                return WriteRegister(hThread, data, UE_RCX, 1, 1);
            case Register::Dh:
                return WriteRegister(hThread, data, UE_RDX, 1, 1);
            case Register::Bh:
                return WriteRegister(hThread, data, UE_RBX, 1, 1);
            case Register::Spl:
                return WriteRegister(hThread, data, UE_RSP, 1);
            case Register::Bpl:
                return WriteRegister(hThread, data, UE_RBP, 1);
            case Register::Sil:
                return WriteRegister(hThread, data, UE_RSI, 1);
            case Register::Dil:
                return WriteRegister(hThread, data, UE_RDI, 1);
            case Register::R8b:
                return WriteRegister(hThread, data, UE_R8, 1);
            case Register::R9b:
                return WriteRegister(hThread, data, UE_R9, 1);
            case Register::R10b:
                return WriteRegister(hThread, data, UE_R10, 1);
            case Register::R11b:
                return WriteRegister(hThread, data, UE_R11, 1);
            case Register::R12b:
                return WriteRegister(hThread, data, UE_R12, 1);
            case Register::R13b:
                return WriteRegister(hThread, data, UE_R13, 1);
            case Register::R14b:
                return WriteRegister(hThread, data, UE_R14, 1);
            case Register::R15b:
                return WriteRegister(hThread, data, UE_R15, 1);
            case Register::Ax:
                return WriteRegister(hThread, data, UE_RAX, 2);
            case Register::Cx:
                return WriteRegister(hThread, data, UE_RCX, 2);
            case Register::Dx:
                return WriteRegister(hThread, data, UE_RDX, 2);
            case Register::Bx:
                return WriteRegister(hThread, data, UE_RBX, 2);
            case Register::Sp:
                return WriteRegister(hThread, data, UE_RSP, 2);
            case Register::Bp:
                return WriteRegister(hThread, data, UE_RBP, 2);
            case Register::Si:
                return WriteRegister(hThread, data, UE_RSI, 2);
            case Register::Di:
                return WriteRegister(hThread, data, UE_RDI, 2);
            case Register::R8w:
                return WriteRegister(hThread, data, UE_R8, 2);
            case Register::R9w:
                return WriteRegister(hThread, data, UE_R9, 2);
            case Register::R10w:
                return WriteRegister(hThread, data, UE_R10, 2);
            case Register::R11w:
                return WriteRegister(hThread, data, UE_R11, 2);
            case Register::R12w:
                return WriteRegister(hThread, data, UE_R12, 2);
            case Register::R13w:
                return WriteRegister(hThread, data, UE_R13, 2);
            case Register::R14w:
                return WriteRegister(hThread, data, UE_R14, 2);
            case Register::R15w:
                return WriteRegister(hThread, data, UE_R15, 2);
            case Register::Eax:
                return WriteRegister(hThread, data, UE_RAX, 4);
            case Register::Ecx:
                return WriteRegister(hThread, data, UE_RCX, 4);
            case Register::Edx:
                return WriteRegister(hThread, data, UE_RDX, 4);
            case Register::Ebx:
                return WriteRegister(hThread, data, UE_RBX, 4);
            case Register::Esp:
                return WriteRegister(hThread, data, UE_RSP, 4);
            case Register::Ebp:
                return WriteRegister(hThread, data, UE_RBP, 4);
            case Register::Esi:
                return WriteRegister(hThread, data, UE_RSI, 4);
            case Register::Edi:
                return WriteRegister(hThread, data, UE_RDI, 4);
            case Register::R8d:
                return WriteRegister(hThread, data, UE_R8, 4);
            case Register::R9d:
                return WriteRegister(hThread, data, UE_R9, 4);
            case Register::R10d:
                return WriteRegister(hThread, data, UE_R10, 4);
            case Register::R11d:
                return WriteRegister(hThread, data, UE_R11, 4);
            case Register::R12d:
                return WriteRegister(hThread, data, UE_R12, 4);
            case Register::R13d:
                return WriteRegister(hThread, data, UE_R13, 4);
            case Register::R14d:
                return WriteRegister(hThread, data, UE_R14, 4);
            case Register::R15d:
                return WriteRegister(hThread, data, UE_R15, 4);
            case Register::Rax:
                return WriteRegister(hThread, data, UE_RAX, 8);
            case Register::Rcx:
                return WriteRegister(hThread, data, UE_RCX, 8);
            case Register::Rdx:
                return WriteRegister(hThread, data, UE_RDX, 8);
            case Register::Rbx:
                return WriteRegister(hThread, data, UE_RBP, 8);
            case Register::Rsp:
                return WriteRegister(hThread, data, UE_RSP, 8);
            case Register::Rbp:
                return WriteRegister(hThread, data, UE_RBP, 8);
            case Register::Rsi:
                return WriteRegister(hThread, data, UE_RSI, 8);
            case Register::Rdi:
                return WriteRegister(hThread, data, UE_RDI, 8);
            case Register::R8:
                return WriteRegister(hThread, data, UE_R8, 8);
            case Register::R9:
                return WriteRegister(hThread, data, UE_R9, 8);
            case Register::R10:
                return WriteRegister(hThread, data, UE_R10, 8);
            case Register::R11:
                return WriteRegister(hThread, data, UE_R11, 8);
            case Register::R12:
                return WriteRegister(hThread, data, UE_R12, 8);
            case Register::R13:
                return WriteRegister(hThread, data, UE_R13, 8);
            case Register::R14:
                return WriteRegister(hThread, data, UE_R14, 8);
            case Register::R15:
                return WriteRegister(hThread, data, UE_R15, 8);
            case Register::St0:
                break;
            case Register::St1:
                break;
            case Register::St2:
                break;
            case Register::St3:
                break;
            case Register::St4:
                break;
            case Register::St5:
                break;
            case Register::St6:
                break;
            case Register::St7:
                break;
            case Register::X87Control:
                break;
            case Register::X87Status:
                break;
            case Register::X87Tag:
                break;
            case Register::Mm0:
                break;
            case Register::Mm1:
                break;
            case Register::Mm2:
                break;
            case Register::Mm3:
                break;
            case Register::Mm4:
                break;
            case Register::Mm5:
                break;
            case Register::Mm6:
                break;
            case Register::Mm7:
                break;
            case Register::Xmm0:
                break;
            case Register::Xmm1:
                break;
            case Register::Xmm2:
                break;
            case Register::Xmm3:
                break;
            case Register::Xmm4:
                break;
            case Register::Xmm5:
                break;
            case Register::Xmm6:
                break;
            case Register::Xmm7:
                break;
            case Register::Xmm8:
                break;
            case Register::Xmm9:
                break;
            case Register::Xmm10:
                break;
            case Register::Xmm11:
                break;
            case Register::Xmm12:
                break;
            case Register::Xmm13:
                break;
            case Register::Xmm14:
                break;
            case Register::Xmm15:
                break;
            case Register::Xmm16:
                break;
            case Register::Xmm17:
                break;
            case Register::Xmm18:
                break;
            case Register::Xmm19:
                break;
            case Register::Xmm20:
                break;
            case Register::Xmm21:
                break;
            case Register::Xmm22:
                break;
            case Register::Xmm23:
                break;
            case Register::Xmm24:
                break;
            case Register::Xmm25:
                break;
            case Register::Xmm26:
                break;
            case Register::Xmm27:
                break;
            case Register::Xmm28:
                break;
            case Register::Xmm29:
                break;
            case Register::Xmm30:
                break;
            case Register::Xmm31:
                break;
            case Register::Ymm0:
                break;
            case Register::Ymm1:
                break;
            case Register::Ymm2:
                break;
            case Register::Ymm3:
                break;
            case Register::Ymm4:
                break;
            case Register::Ymm5:
                break;
            case Register::Ymm6:
                break;
            case Register::Ymm7:
                break;
            case Register::Ymm8:
                break;
            case Register::Ymm9:
                break;
            case Register::Ymm10:
                break;
            case Register::Ymm11:
                break;
            case Register::Ymm12:
                break;
            case Register::Ymm13:
                break;
            case Register::Ymm14:
                break;
            case Register::Ymm15:
                break;
            case Register::Ymm16:
                break;
            case Register::Ymm17:
                break;
            case Register::Ymm18:
                break;
            case Register::Ymm19:
                break;
            case Register::Ymm20:
                break;
            case Register::Ymm21:
                break;
            case Register::Ymm22:
                break;
            case Register::Ymm23:
                break;
            case Register::Ymm24:
                break;
            case Register::Ymm25:
                break;
            case Register::Ymm26:
                break;
            case Register::Ymm27:
                break;
            case Register::Ymm28:
                break;
            case Register::Ymm29:
                break;
            case Register::Ymm30:
                break;
            case Register::Ymm31:
                break;
            case Register::Zmm0:
                break;
            case Register::Zmm1:
                break;
            case Register::Zmm2:
                break;
            case Register::Zmm3:
                break;
            case Register::Zmm4:
                break;
            case Register::Zmm5:
                break;
            case Register::Zmm6:
                break;
            case Register::Zmm7:
                break;
            case Register::Zmm8:
                break;
            case Register::Zmm9:
                break;
            case Register::Zmm10:
                break;
            case Register::Zmm11:
                break;
            case Register::Zmm12:
                break;
            case Register::Zmm13:
                break;
            case Register::Zmm14:
                break;
            case Register::Zmm15:
                break;
            case Register::Zmm16:
                break;
            case Register::Zmm17:
                break;
            case Register::Zmm18:
                break;
            case Register::Zmm19:
                break;
            case Register::Zmm20:
                break;
            case Register::Zmm21:
                break;
            case Register::Zmm22:
                break;
            case Register::Zmm23:
                break;
            case Register::Zmm24:
                break;
            case Register::Zmm25:
                break;
            case Register::Zmm26:
                break;
            case Register::Zmm27:
                break;
            case Register::Zmm28:
                break;
            case Register::Zmm29:
                break;
            case Register::Zmm30:
                break;
            case Register::Zmm31:
                break;
            case Register::Flags:
                return WriteRegister(hThread, data, UE_RFLAGS, 2);
            case Register::EFlags:
                return WriteRegister(hThread, data, UE_RFLAGS, 4);
            case Register::RFlags:
                return WriteRegister(hThread, data, UE_RFLAGS, 8);
            case Register::Ip:
                return WriteRegister(hThread, data, UE_RIP, 2);
            case Register::Eip:
                return WriteRegister(hThread, data, UE_RIP, 4);
            case Register::Rip:
                return WriteRegister(hThread, data, UE_RIP, 8);
            case Register::Es:
                return WriteRegister(hThread, data, UE_SEG_ES, 2);
            case Register::Cs:
                return WriteRegister(hThread, data, UE_SEG_CS, 2);
            case Register::Ss:
                return WriteRegister(hThread, data, UE_SEG_SS, 2);
            case Register::Ds:
                return WriteRegister(hThread, data, UE_SEG_DS, 2);
            case Register::Fs:
                return WriteRegister(hThread, data, UE_SEG_FS, 2);
            case Register::Gs:
                return WriteRegister(hThread, data, UE_SEG_GS, 2);
            case Register::Gdtr:
                break;
            case Register::Ldtr:
                break;
            case Register::Idtr:
                break;
            case Register::Tr:
                break;
            case Register::Tr0:
                break;
            case Register::Tr1:
                break;
            case Register::Tr2:
                break;
            case Register::Tr3:
                break;
            case Register::Tr4:
                break;
            case Register::Tr5:
                break;
            case Register::Tr6:
                break;
            case Register::Tr7:
                break;
            case Register::Cr0:
                break;
            case Register::Cr1:
                break;
            case Register::Cr2:
                break;
            case Register::Cr3:
                break;
            case Register::Cr4:
                break;
            case Register::Cr5:
                break;
            case Register::Cr6:
                break;
            case Register::Cr7:
                break;
            case Register::Cr8:
                break;
            case Register::Cr9:
                break;
            case Register::Cr10:
                break;
            case Register::Cr11:
                break;
            case Register::Cr12:
                break;
            case Register::Cr13:
                break;
            case Register::Cr14:
                break;
            case Register::Cr15:
                break;
            case Register::Dr0:
                break;
            case Register::Dr1:
                break;
            case Register::Dr2:
                break;
            case Register::Dr3:
                break;
            case Register::Dr4:
                break;
            case Register::Dr5:
                break;
            case Register::Dr6:
                break;
            case Register::Dr7:
                break;
            case Register::Dr8:
                break;
            case Register::Dr9:
                break;
            case Register::Dr10:
                break;
            case Register::Dr11:
                break;
            case Register::Dr12:
                break;
            case Register::Dr13:
                break;
            case Register::Dr14:
                break;
            case Register::Dr15:
                break;
            case Register::K0:
                break;
            case Register::K1:
                break;
            case Register::K2:
                break;
            case Register::K3:
                break;
            case Register::K4:
                break;
            case Register::K5:
                break;
            case Register::K6:
                break;
            case Register::K7:
                break;
            case Register::Bnd0:
                break;
            case Register::Bnd1:
                break;
            case Register::Bnd2:
                break;
            case Register::Bnd3:
                break;
            case Register::BndCfg:
                break;
            case Register::BndStatus:
                break;
            case Register::Mxcsr:
                break;
            case Register::Pkru:
                break;
            case Register::Xcr0:
                break;
            default:
                break;
            }
        }

    };
}
