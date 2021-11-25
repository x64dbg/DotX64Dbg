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
        System::UIntPtr Handle;
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
                res->Handle = System::UIntPtr(th.BasicInfo.Handle);
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

        static array<System::Byte>^ ReadRegister(System::UIntPtr hThread, int reg, int size, int offset)
        {
            array<System::Byte>^ res = gcnew array<System::Byte>(size);

            pin_ptr<uint8_t> p = &res[0];
            uint8_t* data = p;

            ULONG_PTR val = GetContextDataEx(hThread.ToPointer(), reg);
            std::memcpy(data, reinterpret_cast<const uint8_t*>(&val) + offset, size);

            return res;
        }

        static array<System::Byte>^ ReadRegister(System::UIntPtr hThread, int reg, int size)
        {
            return ReadRegister(hThread, reg, size, 0);
        }

        static array<System::Byte>^ GetRegisterData(System::UIntPtr hThread, Registers::Id reg)
        {
            switch (reg)
            {
            case Registers::Id::None:
                return gcnew array<System::Byte>(0);
#ifdef _M_X64
            case Registers::Id::Al:
                return ReadRegister(hThread, UE_RAX, 1);
            case Registers::Id::Cl:
                return ReadRegister(hThread, UE_RCX, 1);
            case Registers::Id::Dl:
                return ReadRegister(hThread, UE_RDX, 1);
            case Registers::Id::Bl:
                return ReadRegister(hThread, UE_RBX, 1);
            case Registers::Id::Ah:
                return ReadRegister(hThread, UE_RAX, 1, 1);
            case Registers::Id::Ch:
                return ReadRegister(hThread, UE_RCX, 1, 1);
            case Registers::Id::Dh:
                return ReadRegister(hThread, UE_RDX, 1, 1);
            case Registers::Id::Bh:
                return ReadRegister(hThread, UE_RBX, 1, 1);
            case Registers::Id::Spl:
                return ReadRegister(hThread, UE_RSP, 1);
            case Registers::Id::Bpl:
                return ReadRegister(hThread, UE_RBP, 1);
            case Registers::Id::Sil:
                return ReadRegister(hThread, UE_RSI, 1);
            case Registers::Id::Dil:
                return ReadRegister(hThread, UE_RDI, 1);
            case Registers::Id::R8b:
                return ReadRegister(hThread, UE_R8, 1);
            case Registers::Id::R9b:
                return ReadRegister(hThread, UE_R9, 1);
            case Registers::Id::R10b:
                return ReadRegister(hThread, UE_R10, 1);
            case Registers::Id::R11b:
                return ReadRegister(hThread, UE_R11, 1);
            case Registers::Id::R12b:
                return ReadRegister(hThread, UE_R12, 1);
            case Registers::Id::R13b:
                return ReadRegister(hThread, UE_R13, 1);
            case Registers::Id::R14b:
                return ReadRegister(hThread, UE_R14, 1);
            case Registers::Id::R15b:
                return ReadRegister(hThread, UE_R15, 1);
            case Registers::Id::Ax:
                return ReadRegister(hThread, UE_RAX, 2);
            case Registers::Id::Cx:
                return ReadRegister(hThread, UE_RCX, 2);
            case Registers::Id::Dx:
                return ReadRegister(hThread, UE_RDX, 2);
            case Registers::Id::Bx:
                return ReadRegister(hThread, UE_RBX, 2);
            case Registers::Id::Sp:
                return ReadRegister(hThread, UE_RSP, 2);
            case Registers::Id::Bp:
                return ReadRegister(hThread, UE_RBP, 2);
            case Registers::Id::Si:
                return ReadRegister(hThread, UE_RSI, 2);
            case Registers::Id::Di:
                return ReadRegister(hThread, UE_RDI, 2);
            case Registers::Id::R8w:
                return ReadRegister(hThread, UE_R8, 2);
            case Registers::Id::R9w:
                return ReadRegister(hThread, UE_R9, 2);
            case Registers::Id::R10w:
                return ReadRegister(hThread, UE_R10, 2);
            case Registers::Id::R11w:
                return ReadRegister(hThread, UE_R11, 2);
            case Registers::Id::R12w:
                return ReadRegister(hThread, UE_R12, 2);
            case Registers::Id::R13w:
                return ReadRegister(hThread, UE_R13, 2);
            case Registers::Id::R14w:
                return ReadRegister(hThread, UE_R14, 2);
            case Registers::Id::R15w:
                return ReadRegister(hThread, UE_R15, 2);
            case Registers::Id::Eax:
                return ReadRegister(hThread, UE_RAX, 4);
            case Registers::Id::Ecx:
                return ReadRegister(hThread, UE_RCX, 4);
            case Registers::Id::Edx:
                return ReadRegister(hThread, UE_RDX, 4);
            case Registers::Id::Ebx:
                return ReadRegister(hThread, UE_RBX, 4);
            case Registers::Id::Esp:
                return ReadRegister(hThread, UE_RSP, 4);
            case Registers::Id::Ebp:
                return ReadRegister(hThread, UE_RBP, 4);
            case Registers::Id::Esi:
                return ReadRegister(hThread, UE_RSI, 4);
            case Registers::Id::Edi:
                return ReadRegister(hThread, UE_RDI, 4);
            case Registers::Id::R8d:
                return ReadRegister(hThread, UE_R8, 4);
            case Registers::Id::R9d:
                return ReadRegister(hThread, UE_R9, 4);
            case Registers::Id::R10d:
                return ReadRegister(hThread, UE_R10, 4);
            case Registers::Id::R11d:
                return ReadRegister(hThread, UE_R11, 4);
            case Registers::Id::R12d:
                return ReadRegister(hThread, UE_R12, 4);
            case Registers::Id::R13d:
                return ReadRegister(hThread, UE_R13, 4);
            case Registers::Id::R14d:
                return ReadRegister(hThread, UE_R14, 4);
            case Registers::Id::R15d:
                return ReadRegister(hThread, UE_R15, 4);
            case Registers::Id::Rax:
                return ReadRegister(hThread, UE_RAX, 8);
            case Registers::Id::Rcx:
                return ReadRegister(hThread, UE_RCX, 8);
            case Registers::Id::Rdx:
                return ReadRegister(hThread, UE_RDX, 8);
            case Registers::Id::Rbx:
                return ReadRegister(hThread, UE_RBP, 8);
            case Registers::Id::Rsp:
                return ReadRegister(hThread, UE_RSP, 8);
            case Registers::Id::Rbp:
                return ReadRegister(hThread, UE_RBP, 8);
            case Registers::Id::Rsi:
                return ReadRegister(hThread, UE_RSI, 8);
            case Registers::Id::Rdi:
                return ReadRegister(hThread, UE_RDI, 8);
            case Registers::Id::R8:
                return ReadRegister(hThread, UE_R8, 8);
            case Registers::Id::R9:
                return ReadRegister(hThread, UE_R9, 8);
            case Registers::Id::R10:
                return ReadRegister(hThread, UE_R10, 8);
            case Registers::Id::R11:
                return ReadRegister(hThread, UE_R11, 8);
            case Registers::Id::R12:
                return ReadRegister(hThread, UE_R12, 8);
            case Registers::Id::R13:
                return ReadRegister(hThread, UE_R13, 8);
            case Registers::Id::R14:
                return ReadRegister(hThread, UE_R14, 8);
            case Registers::Id::R15:
                return ReadRegister(hThread, UE_R15, 8);
#else
            case Registers::Id::Al:
                return ReadRegister(hThread, UE_EAX, 1);
            case Registers::Id::Cl:
                return ReadRegister(hThread, UE_ECX, 1);
            case Registers::Id::Dl:
                return ReadRegister(hThread, UE_EDX, 1);
            case Registers::Id::Bl:
                return ReadRegister(hThread, UE_EBX, 1);
            case Registers::Id::Ah:
                return ReadRegister(hThread, UE_EAX, 1, 1);
            case Registers::Id::Ch:
                return ReadRegister(hThread, UE_ECX, 1, 1);
            case Registers::Id::Dh:
                return ReadRegister(hThread, UE_EDX, 1, 1);
            case Registers::Id::Bh:
                return ReadRegister(hThread, UE_EBX, 1, 1);
            case Registers::Id::Spl:
                return ReadRegister(hThread, UE_ESP, 1);
            case Registers::Id::Bpl:
                return ReadRegister(hThread, UE_EBP, 1);
            case Registers::Id::Sil:
                return ReadRegister(hThread, UE_ESI, 1);
            case Registers::Id::Dil:
                return ReadRegister(hThread, UE_EDI, 1);
            case Registers::Id::Ax:
                return ReadRegister(hThread, UE_EAX, 2);
            case Registers::Id::Cx:
                return ReadRegister(hThread, UE_ECX, 2);
            case Registers::Id::Dx:
                return ReadRegister(hThread, UE_EDX, 2);
            case Registers::Id::Bx:
                return ReadRegister(hThread, UE_EBX, 2);
            case Registers::Id::Sp:
                return ReadRegister(hThread, UE_ESP, 2);
            case Registers::Id::Bp:
                return ReadRegister(hThread, UE_EBP, 2);
            case Registers::Id::Si:
                return ReadRegister(hThread, UE_ESI, 2);
            case Registers::Id::Di:
                return ReadRegister(hThread, UE_EDI, 2);
            case Registers::Id::Eax:
                return ReadRegister(hThread, UE_EAX, 4);
            case Registers::Id::Ecx:
                return ReadRegister(hThread, UE_ECX, 4);
            case Registers::Id::Edx:
                return ReadRegister(hThread, UE_EDX, 4);
            case Registers::Id::Ebx:
                return ReadRegister(hThread, UE_EBX, 4);
            case Registers::Id::Esp:
                return ReadRegister(hThread, UE_ESP, 4);
            case Registers::Id::Ebp:
                return ReadRegister(hThread, UE_EBP, 4);
            case Registers::Id::Esi:
                return ReadRegister(hThread, UE_ESI, 4);
            case Registers::Id::Edi:
                return ReadRegister(hThread, UE_EDI, 4);
            case Registers::Id::Rax:
                return ReadRegister(hThread, UE_EAX, 8);
#endif
            case Registers::Id::St0:
                break;
            case Registers::Id::St1:
                break;
            case Registers::Id::St2:
                break;
            case Registers::Id::St3:
                break;
            case Registers::Id::St4:
                break;
            case Registers::Id::St5:
                break;
            case Registers::Id::St6:
                break;
            case Registers::Id::St7:
                break;
            case Registers::Id::X87Control:
                break;
            case Registers::Id::X87Status:
                break;
            case Registers::Id::X87Tag:
                break;
            case Registers::Id::Mm0:
                break;
            case Registers::Id::Mm1:
                break;
            case Registers::Id::Mm2:
                break;
            case Registers::Id::Mm3:
                break;
            case Registers::Id::Mm4:
                break;
            case Registers::Id::Mm5:
                break;
            case Registers::Id::Mm6:
                break;
            case Registers::Id::Mm7:
                break;
            case Registers::Id::Xmm0:
                break;
            case Registers::Id::Xmm1:
                break;
            case Registers::Id::Xmm2:
                break;
            case Registers::Id::Xmm3:
                break;
            case Registers::Id::Xmm4:
                break;
            case Registers::Id::Xmm5:
                break;
            case Registers::Id::Xmm6:
                break;
            case Registers::Id::Xmm7:
                break;
            case Registers::Id::Xmm8:
                break;
            case Registers::Id::Xmm9:
                break;
            case Registers::Id::Xmm10:
                break;
            case Registers::Id::Xmm11:
                break;
            case Registers::Id::Xmm12:
                break;
            case Registers::Id::Xmm13:
                break;
            case Registers::Id::Xmm14:
                break;
            case Registers::Id::Xmm15:
                break;
            case Registers::Id::Xmm16:
                break;
            case Registers::Id::Xmm17:
                break;
            case Registers::Id::Xmm18:
                break;
            case Registers::Id::Xmm19:
                break;
            case Registers::Id::Xmm20:
                break;
            case Registers::Id::Xmm21:
                break;
            case Registers::Id::Xmm22:
                break;
            case Registers::Id::Xmm23:
                break;
            case Registers::Id::Xmm24:
                break;
            case Registers::Id::Xmm25:
                break;
            case Registers::Id::Xmm26:
                break;
            case Registers::Id::Xmm27:
                break;
            case Registers::Id::Xmm28:
                break;
            case Registers::Id::Xmm29:
                break;
            case Registers::Id::Xmm30:
                break;
            case Registers::Id::Xmm31:
                break;
            case Registers::Id::Ymm0:
                break;
            case Registers::Id::Ymm1:
                break;
            case Registers::Id::Ymm2:
                break;
            case Registers::Id::Ymm3:
                break;
            case Registers::Id::Ymm4:
                break;
            case Registers::Id::Ymm5:
                break;
            case Registers::Id::Ymm6:
                break;
            case Registers::Id::Ymm7:
                break;
            case Registers::Id::Ymm8:
                break;
            case Registers::Id::Ymm9:
                break;
            case Registers::Id::Ymm10:
                break;
            case Registers::Id::Ymm11:
                break;
            case Registers::Id::Ymm12:
                break;
            case Registers::Id::Ymm13:
                break;
            case Registers::Id::Ymm14:
                break;
            case Registers::Id::Ymm15:
                break;
            case Registers::Id::Ymm16:
                break;
            case Registers::Id::Ymm17:
                break;
            case Registers::Id::Ymm18:
                break;
            case Registers::Id::Ymm19:
                break;
            case Registers::Id::Ymm20:
                break;
            case Registers::Id::Ymm21:
                break;
            case Registers::Id::Ymm22:
                break;
            case Registers::Id::Ymm23:
                break;
            case Registers::Id::Ymm24:
                break;
            case Registers::Id::Ymm25:
                break;
            case Registers::Id::Ymm26:
                break;
            case Registers::Id::Ymm27:
                break;
            case Registers::Id::Ymm28:
                break;
            case Registers::Id::Ymm29:
                break;
            case Registers::Id::Ymm30:
                break;
            case Registers::Id::Ymm31:
                break;
            case Registers::Id::Zmm0:
                break;
            case Registers::Id::Zmm1:
                break;
            case Registers::Id::Zmm2:
                break;
            case Registers::Id::Zmm3:
                break;
            case Registers::Id::Zmm4:
                break;
            case Registers::Id::Zmm5:
                break;
            case Registers::Id::Zmm6:
                break;
            case Registers::Id::Zmm7:
                break;
            case Registers::Id::Zmm8:
                break;
            case Registers::Id::Zmm9:
                break;
            case Registers::Id::Zmm10:
                break;
            case Registers::Id::Zmm11:
                break;
            case Registers::Id::Zmm12:
                break;
            case Registers::Id::Zmm13:
                break;
            case Registers::Id::Zmm14:
                break;
            case Registers::Id::Zmm15:
                break;
            case Registers::Id::Zmm16:
                break;
            case Registers::Id::Zmm17:
                break;
            case Registers::Id::Zmm18:
                break;
            case Registers::Id::Zmm19:
                break;
            case Registers::Id::Zmm20:
                break;
            case Registers::Id::Zmm21:
                break;
            case Registers::Id::Zmm22:
                break;
            case Registers::Id::Zmm23:
                break;
            case Registers::Id::Zmm24:
                break;
            case Registers::Id::Zmm25:
                break;
            case Registers::Id::Zmm26:
                break;
            case Registers::Id::Zmm27:
                break;
            case Registers::Id::Zmm28:
                break;
            case Registers::Id::Zmm29:
                break;
            case Registers::Id::Zmm30:
                break;
            case Registers::Id::Zmm31:
                break;
#ifdef _M_X64
            case Registers::Id::Flags:
                return ReadRegister(hThread, UE_RFLAGS, 2);
            case Registers::Id::EFlags:
                return ReadRegister(hThread, UE_RFLAGS, 4);
            case Registers::Id::RFlags:
                return ReadRegister(hThread, UE_RFLAGS, 8);
#else
            case Registers::Id::Flags:
                return ReadRegister(hThread, UE_EFLAGS, 2);
            case Registers::Id::EFlags:
                return ReadRegister(hThread, UE_EFLAGS, 4);
#endif

#ifdef _M_X64
            case Registers::Id::Ip:
                return ReadRegister(hThread, UE_RIP, 2);
            case Registers::Id::Eip:
                return ReadRegister(hThread, UE_RIP, 4);
            case Registers::Id::Rip:
                return ReadRegister(hThread, UE_RIP, 8);
#else
            case Registers::Id::Ip:
                return ReadRegister(hThread, UE_EIP, 2);
            case Registers::Id::Eip:
                return ReadRegister(hThread, UE_EIP, 4);
#endif
            case Registers::Id::Es:
                return ReadRegister(hThread, UE_SEG_ES, 2);
            case Registers::Id::Cs:
                return ReadRegister(hThread, UE_SEG_CS, 2);
            case Registers::Id::Ss:
                return ReadRegister(hThread, UE_SEG_SS, 2);
            case Registers::Id::Ds:
                return ReadRegister(hThread, UE_SEG_DS, 2);
            case Registers::Id::Fs:
                return ReadRegister(hThread, UE_SEG_FS, 2);
            case Registers::Id::Gs:
                return ReadRegister(hThread, UE_SEG_GS, 2);
            case Registers::Id::Gdtr:
                break;
            case Registers::Id::Ldtr:
                break;
            case Registers::Id::Idtr:
                break;
            case Registers::Id::Tr:
                break;
            case Registers::Id::Tr0:
                break;
            case Registers::Id::Tr1:
                break;
            case Registers::Id::Tr2:
                break;
            case Registers::Id::Tr3:
                break;
            case Registers::Id::Tr4:
                break;
            case Registers::Id::Tr5:
                break;
            case Registers::Id::Tr6:
                break;
            case Registers::Id::Tr7:
                break;
            case Registers::Id::Cr0:
                break;
            case Registers::Id::Cr1:
                break;
            case Registers::Id::Cr2:
                break;
            case Registers::Id::Cr3:
                break;
            case Registers::Id::Cr4:
                break;
            case Registers::Id::Cr5:
                break;
            case Registers::Id::Cr6:
                break;
            case Registers::Id::Cr7:
                break;
            case Registers::Id::Cr8:
                break;
            case Registers::Id::Cr9:
                break;
            case Registers::Id::Cr10:
                break;
            case Registers::Id::Cr11:
                break;
            case Registers::Id::Cr12:
                break;
            case Registers::Id::Cr13:
                break;
            case Registers::Id::Cr14:
                break;
            case Registers::Id::Cr15:
                break;
            case Registers::Id::Dr0:
                break;
            case Registers::Id::Dr1:
                break;
            case Registers::Id::Dr2:
                break;
            case Registers::Id::Dr3:
                break;
            case Registers::Id::Dr4:
                break;
            case Registers::Id::Dr5:
                break;
            case Registers::Id::Dr6:
                break;
            case Registers::Id::Dr7:
                break;
            case Registers::Id::Dr8:
                break;
            case Registers::Id::Dr9:
                break;
            case Registers::Id::Dr10:
                break;
            case Registers::Id::Dr11:
                break;
            case Registers::Id::Dr12:
                break;
            case Registers::Id::Dr13:
                break;
            case Registers::Id::Dr14:
                break;
            case Registers::Id::Dr15:
                break;
            case Registers::Id::K0:
                break;
            case Registers::Id::K1:
                break;
            case Registers::Id::K2:
                break;
            case Registers::Id::K3:
                break;
            case Registers::Id::K4:
                break;
            case Registers::Id::K5:
                break;
            case Registers::Id::K6:
                break;
            case Registers::Id::K7:
                break;
            case Registers::Id::Bnd0:
                break;
            case Registers::Id::Bnd1:
                break;
            case Registers::Id::Bnd2:
                break;
            case Registers::Id::Bnd3:
                break;
            case Registers::Id::BndCfg:
                break;
            case Registers::Id::BndStatus:
                break;
            case Registers::Id::Mxcsr:
                break;
            case Registers::Id::Pkru:
                break;
            case Registers::Id::Xcr0:
                break;
            default:
                break;
            }

            // Unsupported.
            return gcnew array<System::Byte>(0);
        }

        static void WriteRegister(System::UIntPtr hThread, array<System::Byte>^ data, int reg, int size, int offset)
        {
            HANDLE handle = hThread.ToPointer();

            pin_ptr<uint8_t> p = &data[0];
            const uint8_t* ptr = p;

            // This is terrible, but to preserve the data when the write happens on smaller regs we need the
            // value not to be zero.
            ULONG_PTR val = size < sizeof(ULONG_PTR) ? GetContextDataEx(handle, reg) : 0;

            std::memcpy(reinterpret_cast<uint8_t*>(&val) + offset, ptr, std::min<size_t>(data->Length, size));

            if (!SetContextDataEx(handle, reg, val))
            {
                throw gcnew System::Exception("Unable to set context data");
            }
        }

        static void WriteRegister(System::UIntPtr hThread, array<System::Byte>^ data, int reg, int size)
        {
            WriteRegister(hThread, data, reg, size, 0);
            GuiUpdateRegisterView();
        }

        static void SetRegisterData(System::UIntPtr hThread, Registers::Id reg, array<System::Byte>^ data)
        {
            switch (reg)
            {
            case Registers::Id::None:
                return;
#ifdef _M_X64
            case Registers::Id::Al:
                return WriteRegister(hThread, data, UE_RAX, 1);
            case Registers::Id::Cl:
                return WriteRegister(hThread, data, UE_RCX, 1);
            case Registers::Id::Dl:
                return WriteRegister(hThread, data, UE_RDX, 1);
            case Registers::Id::Bl:
                return WriteRegister(hThread, data, UE_RBX, 1);
            case Registers::Id::Ah:
                return WriteRegister(hThread, data, UE_RAX, 1, 1);
            case Registers::Id::Ch:
                return WriteRegister(hThread, data, UE_RCX, 1, 1);
            case Registers::Id::Dh:
                return WriteRegister(hThread, data, UE_RDX, 1, 1);
            case Registers::Id::Bh:
                return WriteRegister(hThread, data, UE_RBX, 1, 1);
            case Registers::Id::Spl:
                return WriteRegister(hThread, data, UE_RSP, 1);
            case Registers::Id::Bpl:
                return WriteRegister(hThread, data, UE_RBP, 1);
            case Registers::Id::Sil:
                return WriteRegister(hThread, data, UE_RSI, 1);
            case Registers::Id::Dil:
                return WriteRegister(hThread, data, UE_RDI, 1);
            case Registers::Id::R8b:
                return WriteRegister(hThread, data, UE_R8, 1);
            case Registers::Id::R9b:
                return WriteRegister(hThread, data, UE_R9, 1);
            case Registers::Id::R10b:
                return WriteRegister(hThread, data, UE_R10, 1);
            case Registers::Id::R11b:
                return WriteRegister(hThread, data, UE_R11, 1);
            case Registers::Id::R12b:
                return WriteRegister(hThread, data, UE_R12, 1);
            case Registers::Id::R13b:
                return WriteRegister(hThread, data, UE_R13, 1);
            case Registers::Id::R14b:
                return WriteRegister(hThread, data, UE_R14, 1);
            case Registers::Id::R15b:
                return WriteRegister(hThread, data, UE_R15, 1);
            case Registers::Id::Ax:
                return WriteRegister(hThread, data, UE_RAX, 2);
            case Registers::Id::Cx:
                return WriteRegister(hThread, data, UE_RCX, 2);
            case Registers::Id::Dx:
                return WriteRegister(hThread, data, UE_RDX, 2);
            case Registers::Id::Bx:
                return WriteRegister(hThread, data, UE_RBX, 2);
            case Registers::Id::Sp:
                return WriteRegister(hThread, data, UE_RSP, 2);
            case Registers::Id::Bp:
                return WriteRegister(hThread, data, UE_RBP, 2);
            case Registers::Id::Si:
                return WriteRegister(hThread, data, UE_RSI, 2);
            case Registers::Id::Di:
                return WriteRegister(hThread, data, UE_RDI, 2);
            case Registers::Id::R8w:
                return WriteRegister(hThread, data, UE_R8, 2);
            case Registers::Id::R9w:
                return WriteRegister(hThread, data, UE_R9, 2);
            case Registers::Id::R10w:
                return WriteRegister(hThread, data, UE_R10, 2);
            case Registers::Id::R11w:
                return WriteRegister(hThread, data, UE_R11, 2);
            case Registers::Id::R12w:
                return WriteRegister(hThread, data, UE_R12, 2);
            case Registers::Id::R13w:
                return WriteRegister(hThread, data, UE_R13, 2);
            case Registers::Id::R14w:
                return WriteRegister(hThread, data, UE_R14, 2);
            case Registers::Id::R15w:
                return WriteRegister(hThread, data, UE_R15, 2);
            case Registers::Id::Eax:
                return WriteRegister(hThread, data, UE_RAX, 4);
            case Registers::Id::Ecx:
                return WriteRegister(hThread, data, UE_RCX, 4);
            case Registers::Id::Edx:
                return WriteRegister(hThread, data, UE_RDX, 4);
            case Registers::Id::Ebx:
                return WriteRegister(hThread, data, UE_RBX, 4);
            case Registers::Id::Esp:
                return WriteRegister(hThread, data, UE_RSP, 4);
            case Registers::Id::Ebp:
                return WriteRegister(hThread, data, UE_RBP, 4);
            case Registers::Id::Esi:
                return WriteRegister(hThread, data, UE_RSI, 4);
            case Registers::Id::Edi:
                return WriteRegister(hThread, data, UE_RDI, 4);
            case Registers::Id::R8d:
                return WriteRegister(hThread, data, UE_R8, 4);
            case Registers::Id::R9d:
                return WriteRegister(hThread, data, UE_R9, 4);
            case Registers::Id::R10d:
                return WriteRegister(hThread, data, UE_R10, 4);
            case Registers::Id::R11d:
                return WriteRegister(hThread, data, UE_R11, 4);
            case Registers::Id::R12d:
                return WriteRegister(hThread, data, UE_R12, 4);
            case Registers::Id::R13d:
                return WriteRegister(hThread, data, UE_R13, 4);
            case Registers::Id::R14d:
                return WriteRegister(hThread, data, UE_R14, 4);
            case Registers::Id::R15d:
                return WriteRegister(hThread, data, UE_R15, 4);
            case Registers::Id::Rax:
                return WriteRegister(hThread, data, UE_RAX, 8);
            case Registers::Id::Rcx:
                return WriteRegister(hThread, data, UE_RCX, 8);
            case Registers::Id::Rdx:
                return WriteRegister(hThread, data, UE_RDX, 8);
            case Registers::Id::Rbx:
                return WriteRegister(hThread, data, UE_RBP, 8);
            case Registers::Id::Rsp:
                return WriteRegister(hThread, data, UE_RSP, 8);
            case Registers::Id::Rbp:
                return WriteRegister(hThread, data, UE_RBP, 8);
            case Registers::Id::Rsi:
                return WriteRegister(hThread, data, UE_RSI, 8);
            case Registers::Id::Rdi:
                return WriteRegister(hThread, data, UE_RDI, 8);
            case Registers::Id::R8:
                return WriteRegister(hThread, data, UE_R8, 8);
            case Registers::Id::R9:
                return WriteRegister(hThread, data, UE_R9, 8);
            case Registers::Id::R10:
                return WriteRegister(hThread, data, UE_R10, 8);
            case Registers::Id::R11:
                return WriteRegister(hThread, data, UE_R11, 8);
            case Registers::Id::R12:
                return WriteRegister(hThread, data, UE_R12, 8);
            case Registers::Id::R13:
                return WriteRegister(hThread, data, UE_R13, 8);
            case Registers::Id::R14:
                return WriteRegister(hThread, data, UE_R14, 8);
            case Registers::Id::R15:
                return WriteRegister(hThread, data, UE_R15, 8);
#else
            case Registers::Id::Al:
                return WriteRegister(hThread, data, UE_EAX, 1);
            case Registers::Id::Cl:
                return WriteRegister(hThread, data, UE_ECX, 1);
            case Registers::Id::Dl:
                return WriteRegister(hThread, data, UE_EDX, 1);
            case Registers::Id::Bl:
                return WriteRegister(hThread, data, UE_EBX, 1);
            case Registers::Id::Ah:
                return WriteRegister(hThread, data, UE_EAX, 1, 1);
            case Registers::Id::Ch:
                return WriteRegister(hThread, data, UE_ECX, 1, 1);
            case Registers::Id::Dh:
                return WriteRegister(hThread, data, UE_EDX, 1, 1);
            case Registers::Id::Bh:
                return WriteRegister(hThread, data, UE_EBX, 1, 1);
            case Registers::Id::Spl:
                return WriteRegister(hThread, data, UE_ESP, 1);
            case Registers::Id::Bpl:
                return WriteRegister(hThread, data, UE_EBP, 1);
            case Registers::Id::Sil:
                return WriteRegister(hThread, data, UE_ESI, 1);
            case Registers::Id::Dil:
                return WriteRegister(hThread, data, UE_EDI, 1);
            case Registers::Id::Ax:
                return WriteRegister(hThread, data, UE_EAX, 2);
            case Registers::Id::Cx:
                return WriteRegister(hThread, data, UE_ECX, 2);
            case Registers::Id::Dx:
                return WriteRegister(hThread, data, UE_EDX, 2);
            case Registers::Id::Bx:
                return WriteRegister(hThread, data, UE_EBX, 2);
            case Registers::Id::Sp:
                return WriteRegister(hThread, data, UE_ESP, 2);
            case Registers::Id::Bp:
                return WriteRegister(hThread, data, UE_EBP, 2);
            case Registers::Id::Si:
                return WriteRegister(hThread, data, UE_ESI, 2);
            case Registers::Id::Di:
                return WriteRegister(hThread, data, UE_EDI, 2);
            case Registers::Id::Eax:
                return WriteRegister(hThread, data, UE_EAX, 4);
            case Registers::Id::Ecx:
                return WriteRegister(hThread, data, UE_ECX, 4);
            case Registers::Id::Edx:
                return WriteRegister(hThread, data, UE_EDX, 4);
            case Registers::Id::Ebx:
                return WriteRegister(hThread, data, UE_EBX, 4);
            case Registers::Id::Esp:
                return WriteRegister(hThread, data, UE_ESP, 4);
            case Registers::Id::Ebp:
                return WriteRegister(hThread, data, UE_EBP, 4);
            case Registers::Id::Esi:
                return WriteRegister(hThread, data, UE_ESI, 4);
            case Registers::Id::Edi:
                return WriteRegister(hThread, data, UE_EDI, 4);
#endif
            case Registers::Id::St0:
                break;
            case Registers::Id::St1:
                break;
            case Registers::Id::St2:
                break;
            case Registers::Id::St3:
                break;
            case Registers::Id::St4:
                break;
            case Registers::Id::St5:
                break;
            case Registers::Id::St6:
                break;
            case Registers::Id::St7:
                break;
            case Registers::Id::X87Control:
                break;
            case Registers::Id::X87Status:
                break;
            case Registers::Id::X87Tag:
                break;
            case Registers::Id::Mm0:
                break;
            case Registers::Id::Mm1:
                break;
            case Registers::Id::Mm2:
                break;
            case Registers::Id::Mm3:
                break;
            case Registers::Id::Mm4:
                break;
            case Registers::Id::Mm5:
                break;
            case Registers::Id::Mm6:
                break;
            case Registers::Id::Mm7:
                break;
            case Registers::Id::Xmm0:
                break;
            case Registers::Id::Xmm1:
                break;
            case Registers::Id::Xmm2:
                break;
            case Registers::Id::Xmm3:
                break;
            case Registers::Id::Xmm4:
                break;
            case Registers::Id::Xmm5:
                break;
            case Registers::Id::Xmm6:
                break;
            case Registers::Id::Xmm7:
                break;
            case Registers::Id::Xmm8:
                break;
            case Registers::Id::Xmm9:
                break;
            case Registers::Id::Xmm10:
                break;
            case Registers::Id::Xmm11:
                break;
            case Registers::Id::Xmm12:
                break;
            case Registers::Id::Xmm13:
                break;
            case Registers::Id::Xmm14:
                break;
            case Registers::Id::Xmm15:
                break;
            case Registers::Id::Xmm16:
                break;
            case Registers::Id::Xmm17:
                break;
            case Registers::Id::Xmm18:
                break;
            case Registers::Id::Xmm19:
                break;
            case Registers::Id::Xmm20:
                break;
            case Registers::Id::Xmm21:
                break;
            case Registers::Id::Xmm22:
                break;
            case Registers::Id::Xmm23:
                break;
            case Registers::Id::Xmm24:
                break;
            case Registers::Id::Xmm25:
                break;
            case Registers::Id::Xmm26:
                break;
            case Registers::Id::Xmm27:
                break;
            case Registers::Id::Xmm28:
                break;
            case Registers::Id::Xmm29:
                break;
            case Registers::Id::Xmm30:
                break;
            case Registers::Id::Xmm31:
                break;
            case Registers::Id::Ymm0:
                break;
            case Registers::Id::Ymm1:
                break;
            case Registers::Id::Ymm2:
                break;
            case Registers::Id::Ymm3:
                break;
            case Registers::Id::Ymm4:
                break;
            case Registers::Id::Ymm5:
                break;
            case Registers::Id::Ymm6:
                break;
            case Registers::Id::Ymm7:
                break;
            case Registers::Id::Ymm8:
                break;
            case Registers::Id::Ymm9:
                break;
            case Registers::Id::Ymm10:
                break;
            case Registers::Id::Ymm11:
                break;
            case Registers::Id::Ymm12:
                break;
            case Registers::Id::Ymm13:
                break;
            case Registers::Id::Ymm14:
                break;
            case Registers::Id::Ymm15:
                break;
            case Registers::Id::Ymm16:
                break;
            case Registers::Id::Ymm17:
                break;
            case Registers::Id::Ymm18:
                break;
            case Registers::Id::Ymm19:
                break;
            case Registers::Id::Ymm20:
                break;
            case Registers::Id::Ymm21:
                break;
            case Registers::Id::Ymm22:
                break;
            case Registers::Id::Ymm23:
                break;
            case Registers::Id::Ymm24:
                break;
            case Registers::Id::Ymm25:
                break;
            case Registers::Id::Ymm26:
                break;
            case Registers::Id::Ymm27:
                break;
            case Registers::Id::Ymm28:
                break;
            case Registers::Id::Ymm29:
                break;
            case Registers::Id::Ymm30:
                break;
            case Registers::Id::Ymm31:
                break;
            case Registers::Id::Zmm0:
                break;
            case Registers::Id::Zmm1:
                break;
            case Registers::Id::Zmm2:
                break;
            case Registers::Id::Zmm3:
                break;
            case Registers::Id::Zmm4:
                break;
            case Registers::Id::Zmm5:
                break;
            case Registers::Id::Zmm6:
                break;
            case Registers::Id::Zmm7:
                break;
            case Registers::Id::Zmm8:
                break;
            case Registers::Id::Zmm9:
                break;
            case Registers::Id::Zmm10:
                break;
            case Registers::Id::Zmm11:
                break;
            case Registers::Id::Zmm12:
                break;
            case Registers::Id::Zmm13:
                break;
            case Registers::Id::Zmm14:
                break;
            case Registers::Id::Zmm15:
                break;
            case Registers::Id::Zmm16:
                break;
            case Registers::Id::Zmm17:
                break;
            case Registers::Id::Zmm18:
                break;
            case Registers::Id::Zmm19:
                break;
            case Registers::Id::Zmm20:
                break;
            case Registers::Id::Zmm21:
                break;
            case Registers::Id::Zmm22:
                break;
            case Registers::Id::Zmm23:
                break;
            case Registers::Id::Zmm24:
                break;
            case Registers::Id::Zmm25:
                break;
            case Registers::Id::Zmm26:
                break;
            case Registers::Id::Zmm27:
                break;
            case Registers::Id::Zmm28:
                break;
            case Registers::Id::Zmm29:
                break;
            case Registers::Id::Zmm30:
                break;
            case Registers::Id::Zmm31:
                break;
#ifdef _M_X64
            case Registers::Id::Flags:
                return WriteRegister(hThread, data, UE_RFLAGS, 2);
            case Registers::Id::EFlags:
                return WriteRegister(hThread, data, UE_RFLAGS, 4);
            case Registers::Id::RFlags:
                return WriteRegister(hThread, data, UE_RFLAGS, 8);
            case Registers::Id::Ip:
                return WriteRegister(hThread, data, UE_RIP, 2);
            case Registers::Id::Eip:
                return WriteRegister(hThread, data, UE_RIP, 4);
            case Registers::Id::Rip:
                return WriteRegister(hThread, data, UE_RIP, 8);
#else
            case Registers::Id::Flags:
                return WriteRegister(hThread, data, UE_EFLAGS, 2);
            case Registers::Id::EFlags:
                return WriteRegister(hThread, data, UE_EFLAGS, 4);
            case Registers::Id::Ip:
                return WriteRegister(hThread, data, UE_EIP, 2);
            case Registers::Id::Eip:
                return WriteRegister(hThread, data, UE_EIP, 4);
#endif
            case Registers::Id::Es:
                return WriteRegister(hThread, data, UE_SEG_ES, 2);
            case Registers::Id::Cs:
                return WriteRegister(hThread, data, UE_SEG_CS, 2);
            case Registers::Id::Ss:
                return WriteRegister(hThread, data, UE_SEG_SS, 2);
            case Registers::Id::Ds:
                return WriteRegister(hThread, data, UE_SEG_DS, 2);
            case Registers::Id::Fs:
                return WriteRegister(hThread, data, UE_SEG_FS, 2);
            case Registers::Id::Gs:
                return WriteRegister(hThread, data, UE_SEG_GS, 2);
            case Registers::Id::Gdtr:
                break;
            case Registers::Id::Ldtr:
                break;
            case Registers::Id::Idtr:
                break;
            case Registers::Id::Tr:
                break;
            case Registers::Id::Tr0:
                break;
            case Registers::Id::Tr1:
                break;
            case Registers::Id::Tr2:
                break;
            case Registers::Id::Tr3:
                break;
            case Registers::Id::Tr4:
                break;
            case Registers::Id::Tr5:
                break;
            case Registers::Id::Tr6:
                break;
            case Registers::Id::Tr7:
                break;
            case Registers::Id::Cr0:
                break;
            case Registers::Id::Cr1:
                break;
            case Registers::Id::Cr2:
                break;
            case Registers::Id::Cr3:
                break;
            case Registers::Id::Cr4:
                break;
            case Registers::Id::Cr5:
                break;
            case Registers::Id::Cr6:
                break;
            case Registers::Id::Cr7:
                break;
            case Registers::Id::Cr8:
                break;
            case Registers::Id::Cr9:
                break;
            case Registers::Id::Cr10:
                break;
            case Registers::Id::Cr11:
                break;
            case Registers::Id::Cr12:
                break;
            case Registers::Id::Cr13:
                break;
            case Registers::Id::Cr14:
                break;
            case Registers::Id::Cr15:
                break;
            case Registers::Id::Dr0:
                break;
            case Registers::Id::Dr1:
                break;
            case Registers::Id::Dr2:
                break;
            case Registers::Id::Dr3:
                break;
            case Registers::Id::Dr4:
                break;
            case Registers::Id::Dr5:
                break;
            case Registers::Id::Dr6:
                break;
            case Registers::Id::Dr7:
                break;
            case Registers::Id::Dr8:
                break;
            case Registers::Id::Dr9:
                break;
            case Registers::Id::Dr10:
                break;
            case Registers::Id::Dr11:
                break;
            case Registers::Id::Dr12:
                break;
            case Registers::Id::Dr13:
                break;
            case Registers::Id::Dr14:
                break;
            case Registers::Id::Dr15:
                break;
            case Registers::Id::K0:
                break;
            case Registers::Id::K1:
                break;
            case Registers::Id::K2:
                break;
            case Registers::Id::K3:
                break;
            case Registers::Id::K4:
                break;
            case Registers::Id::K5:
                break;
            case Registers::Id::K6:
                break;
            case Registers::Id::K7:
                break;
            case Registers::Id::Bnd0:
                break;
            case Registers::Id::Bnd1:
                break;
            case Registers::Id::Bnd2:
                break;
            case Registers::Id::Bnd3:
                break;
            case Registers::Id::BndCfg:
                break;
            case Registers::Id::BndStatus:
                break;
            case Registers::Id::Mxcsr:
                break;
            case Registers::Id::Pkru:
                break;
            case Registers::Id::Xcr0:
                break;
            default:
                break;
            }
        }

    };
}
