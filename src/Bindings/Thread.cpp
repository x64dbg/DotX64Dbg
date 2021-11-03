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

        static array<System::Byte>^ GetRegisterData(System::UIntPtr hThread, RegisterId reg)
        {
            switch (reg)
            {
            case RegisterId::None:
                return gcnew array<System::Byte>(0);
#ifdef _M_X64
            case RegisterId::Al:
                return ReadRegister(hThread, UE_RAX, 1);
            case RegisterId::Cl:
                return ReadRegister(hThread, UE_RCX, 1);
            case RegisterId::Dl:
                return ReadRegister(hThread, UE_RDX, 1);
            case RegisterId::Bl:
                return ReadRegister(hThread, UE_RBX, 1);
            case RegisterId::Ah:
                return ReadRegister(hThread, UE_RAX, 1, 1);
            case RegisterId::Ch:
                return ReadRegister(hThread, UE_RCX, 1, 1);
            case RegisterId::Dh:
                return ReadRegister(hThread, UE_RDX, 1, 1);
            case RegisterId::Bh:
                return ReadRegister(hThread, UE_RBX, 1, 1);
            case RegisterId::Spl:
                return ReadRegister(hThread, UE_RSP, 1);
            case RegisterId::Bpl:
                return ReadRegister(hThread, UE_RBP, 1);
            case RegisterId::Sil:
                return ReadRegister(hThread, UE_RSI, 1);
            case RegisterId::Dil:
                return ReadRegister(hThread, UE_RDI, 1);
            case RegisterId::R8b:
                return ReadRegister(hThread, UE_R8, 1);
            case RegisterId::R9b:
                return ReadRegister(hThread, UE_R9, 1);
            case RegisterId::R10b:
                return ReadRegister(hThread, UE_R10, 1);
            case RegisterId::R11b:
                return ReadRegister(hThread, UE_R11, 1);
            case RegisterId::R12b:
                return ReadRegister(hThread, UE_R12, 1);
            case RegisterId::R13b:
                return ReadRegister(hThread, UE_R13, 1);
            case RegisterId::R14b:
                return ReadRegister(hThread, UE_R14, 1);
            case RegisterId::R15b:
                return ReadRegister(hThread, UE_R15, 1);
            case RegisterId::Ax:
                return ReadRegister(hThread, UE_RAX, 2);
            case RegisterId::Cx:
                return ReadRegister(hThread, UE_RCX, 2);
            case RegisterId::Dx:
                return ReadRegister(hThread, UE_RDX, 2);
            case RegisterId::Bx:
                return ReadRegister(hThread, UE_RBX, 2);
            case RegisterId::Sp:
                return ReadRegister(hThread, UE_RSP, 2);
            case RegisterId::Bp:
                return ReadRegister(hThread, UE_RBP, 2);
            case RegisterId::Si:
                return ReadRegister(hThread, UE_RSI, 2);
            case RegisterId::Di:
                return ReadRegister(hThread, UE_RDI, 2);
            case RegisterId::R8w:
                return ReadRegister(hThread, UE_R8, 2);
            case RegisterId::R9w:
                return ReadRegister(hThread, UE_R9, 2);
            case RegisterId::R10w:
                return ReadRegister(hThread, UE_R10, 2);
            case RegisterId::R11w:
                return ReadRegister(hThread, UE_R11, 2);
            case RegisterId::R12w:
                return ReadRegister(hThread, UE_R12, 2);
            case RegisterId::R13w:
                return ReadRegister(hThread, UE_R13, 2);
            case RegisterId::R14w:
                return ReadRegister(hThread, UE_R14, 2);
            case RegisterId::R15w:
                return ReadRegister(hThread, UE_R15, 2);
            case RegisterId::Eax:
                return ReadRegister(hThread, UE_RAX, 4);
            case RegisterId::Ecx:
                return ReadRegister(hThread, UE_RCX, 4);
            case RegisterId::Edx:
                return ReadRegister(hThread, UE_RDX, 4);
            case RegisterId::Ebx:
                return ReadRegister(hThread, UE_RBX, 4);
            case RegisterId::Esp:
                return ReadRegister(hThread, UE_RSP, 4);
            case RegisterId::Ebp:
                return ReadRegister(hThread, UE_RBP, 4);
            case RegisterId::Esi:
                return ReadRegister(hThread, UE_RSI, 4);
            case RegisterId::Edi:
                return ReadRegister(hThread, UE_RDI, 4);
            case RegisterId::R8d:
                return ReadRegister(hThread, UE_R8, 4);
            case RegisterId::R9d:
                return ReadRegister(hThread, UE_R9, 4);
            case RegisterId::R10d:
                return ReadRegister(hThread, UE_R10, 4);
            case RegisterId::R11d:
                return ReadRegister(hThread, UE_R11, 4);
            case RegisterId::R12d:
                return ReadRegister(hThread, UE_R12, 4);
            case RegisterId::R13d:
                return ReadRegister(hThread, UE_R13, 4);
            case RegisterId::R14d:
                return ReadRegister(hThread, UE_R14, 4);
            case RegisterId::R15d:
                return ReadRegister(hThread, UE_R15, 4);
            case RegisterId::Rax:
                return ReadRegister(hThread, UE_RAX, 8);
            case RegisterId::Rcx:
                return ReadRegister(hThread, UE_RCX, 8);
            case RegisterId::Rdx:
                return ReadRegister(hThread, UE_RDX, 8);
            case RegisterId::Rbx:
                return ReadRegister(hThread, UE_RBP, 8);
            case RegisterId::Rsp:
                return ReadRegister(hThread, UE_RSP, 8);
            case RegisterId::Rbp:
                return ReadRegister(hThread, UE_RBP, 8);
            case RegisterId::Rsi:
                return ReadRegister(hThread, UE_RSI, 8);
            case RegisterId::Rdi:
                return ReadRegister(hThread, UE_RDI, 8);
            case RegisterId::R8:
                return ReadRegister(hThread, UE_R8, 8);
            case RegisterId::R9:
                return ReadRegister(hThread, UE_R9, 8);
            case RegisterId::R10:
                return ReadRegister(hThread, UE_R10, 8);
            case RegisterId::R11:
                return ReadRegister(hThread, UE_R11, 8);
            case RegisterId::R12:
                return ReadRegister(hThread, UE_R12, 8);
            case RegisterId::R13:
                return ReadRegister(hThread, UE_R13, 8);
            case RegisterId::R14:
                return ReadRegister(hThread, UE_R14, 8);
            case RegisterId::R15:
                return ReadRegister(hThread, UE_R15, 8);
#else
            case RegisterId::Al:
                return ReadRegister(hThread, UE_EAX, 1);
            case RegisterId::Cl:
                return ReadRegister(hThread, UE_ECX, 1);
            case RegisterId::Dl:
                return ReadRegister(hThread, UE_EDX, 1);
            case RegisterId::Bl:
                return ReadRegister(hThread, UE_EBX, 1);
            case RegisterId::Ah:
                return ReadRegister(hThread, UE_EAX, 1, 1);
            case RegisterId::Ch:
                return ReadRegister(hThread, UE_ECX, 1, 1);
            case RegisterId::Dh:
                return ReadRegister(hThread, UE_EDX, 1, 1);
            case RegisterId::Bh:
                return ReadRegister(hThread, UE_EBX, 1, 1);
            case RegisterId::Spl:
                return ReadRegister(hThread, UE_ESP, 1);
            case RegisterId::Bpl:
                return ReadRegister(hThread, UE_EBP, 1);
            case RegisterId::Sil:
                return ReadRegister(hThread, UE_ESI, 1);
            case RegisterId::Dil:
                return ReadRegister(hThread, UE_EDI, 1);
            case RegisterId::Ax:
                return ReadRegister(hThread, UE_EAX, 2);
            case RegisterId::Cx:
                return ReadRegister(hThread, UE_ECX, 2);
            case RegisterId::Dx:
                return ReadRegister(hThread, UE_EDX, 2);
            case RegisterId::Bx:
                return ReadRegister(hThread, UE_EBX, 2);
            case RegisterId::Sp:
                return ReadRegister(hThread, UE_ESP, 2);
            case RegisterId::Bp:
                return ReadRegister(hThread, UE_EBP, 2);
            case RegisterId::Si:
                return ReadRegister(hThread, UE_ESI, 2);
            case RegisterId::Di:
                return ReadRegister(hThread, UE_EDI, 2);
            case RegisterId::Eax:
                return ReadRegister(hThread, UE_EAX, 4);
            case RegisterId::Ecx:
                return ReadRegister(hThread, UE_ECX, 4);
            case RegisterId::Edx:
                return ReadRegister(hThread, UE_EDX, 4);
            case RegisterId::Ebx:
                return ReadRegister(hThread, UE_EBX, 4);
            case RegisterId::Esp:
                return ReadRegister(hThread, UE_ESP, 4);
            case RegisterId::Ebp:
                return ReadRegister(hThread, UE_EBP, 4);
            case RegisterId::Esi:
                return ReadRegister(hThread, UE_ESI, 4);
            case RegisterId::Edi:
                return ReadRegister(hThread, UE_EDI, 4);
            case RegisterId::Rax:
                return ReadRegister(hThread, UE_EAX, 8);
#endif
            case RegisterId::St0:
                break;
            case RegisterId::St1:
                break;
            case RegisterId::St2:
                break;
            case RegisterId::St3:
                break;
            case RegisterId::St4:
                break;
            case RegisterId::St5:
                break;
            case RegisterId::St6:
                break;
            case RegisterId::St7:
                break;
            case RegisterId::X87Control:
                break;
            case RegisterId::X87Status:
                break;
            case RegisterId::X87Tag:
                break;
            case RegisterId::Mm0:
                break;
            case RegisterId::Mm1:
                break;
            case RegisterId::Mm2:
                break;
            case RegisterId::Mm3:
                break;
            case RegisterId::Mm4:
                break;
            case RegisterId::Mm5:
                break;
            case RegisterId::Mm6:
                break;
            case RegisterId::Mm7:
                break;
            case RegisterId::Xmm0:
                break;
            case RegisterId::Xmm1:
                break;
            case RegisterId::Xmm2:
                break;
            case RegisterId::Xmm3:
                break;
            case RegisterId::Xmm4:
                break;
            case RegisterId::Xmm5:
                break;
            case RegisterId::Xmm6:
                break;
            case RegisterId::Xmm7:
                break;
            case RegisterId::Xmm8:
                break;
            case RegisterId::Xmm9:
                break;
            case RegisterId::Xmm10:
                break;
            case RegisterId::Xmm11:
                break;
            case RegisterId::Xmm12:
                break;
            case RegisterId::Xmm13:
                break;
            case RegisterId::Xmm14:
                break;
            case RegisterId::Xmm15:
                break;
            case RegisterId::Xmm16:
                break;
            case RegisterId::Xmm17:
                break;
            case RegisterId::Xmm18:
                break;
            case RegisterId::Xmm19:
                break;
            case RegisterId::Xmm20:
                break;
            case RegisterId::Xmm21:
                break;
            case RegisterId::Xmm22:
                break;
            case RegisterId::Xmm23:
                break;
            case RegisterId::Xmm24:
                break;
            case RegisterId::Xmm25:
                break;
            case RegisterId::Xmm26:
                break;
            case RegisterId::Xmm27:
                break;
            case RegisterId::Xmm28:
                break;
            case RegisterId::Xmm29:
                break;
            case RegisterId::Xmm30:
                break;
            case RegisterId::Xmm31:
                break;
            case RegisterId::Ymm0:
                break;
            case RegisterId::Ymm1:
                break;
            case RegisterId::Ymm2:
                break;
            case RegisterId::Ymm3:
                break;
            case RegisterId::Ymm4:
                break;
            case RegisterId::Ymm5:
                break;
            case RegisterId::Ymm6:
                break;
            case RegisterId::Ymm7:
                break;
            case RegisterId::Ymm8:
                break;
            case RegisterId::Ymm9:
                break;
            case RegisterId::Ymm10:
                break;
            case RegisterId::Ymm11:
                break;
            case RegisterId::Ymm12:
                break;
            case RegisterId::Ymm13:
                break;
            case RegisterId::Ymm14:
                break;
            case RegisterId::Ymm15:
                break;
            case RegisterId::Ymm16:
                break;
            case RegisterId::Ymm17:
                break;
            case RegisterId::Ymm18:
                break;
            case RegisterId::Ymm19:
                break;
            case RegisterId::Ymm20:
                break;
            case RegisterId::Ymm21:
                break;
            case RegisterId::Ymm22:
                break;
            case RegisterId::Ymm23:
                break;
            case RegisterId::Ymm24:
                break;
            case RegisterId::Ymm25:
                break;
            case RegisterId::Ymm26:
                break;
            case RegisterId::Ymm27:
                break;
            case RegisterId::Ymm28:
                break;
            case RegisterId::Ymm29:
                break;
            case RegisterId::Ymm30:
                break;
            case RegisterId::Ymm31:
                break;
            case RegisterId::Zmm0:
                break;
            case RegisterId::Zmm1:
                break;
            case RegisterId::Zmm2:
                break;
            case RegisterId::Zmm3:
                break;
            case RegisterId::Zmm4:
                break;
            case RegisterId::Zmm5:
                break;
            case RegisterId::Zmm6:
                break;
            case RegisterId::Zmm7:
                break;
            case RegisterId::Zmm8:
                break;
            case RegisterId::Zmm9:
                break;
            case RegisterId::Zmm10:
                break;
            case RegisterId::Zmm11:
                break;
            case RegisterId::Zmm12:
                break;
            case RegisterId::Zmm13:
                break;
            case RegisterId::Zmm14:
                break;
            case RegisterId::Zmm15:
                break;
            case RegisterId::Zmm16:
                break;
            case RegisterId::Zmm17:
                break;
            case RegisterId::Zmm18:
                break;
            case RegisterId::Zmm19:
                break;
            case RegisterId::Zmm20:
                break;
            case RegisterId::Zmm21:
                break;
            case RegisterId::Zmm22:
                break;
            case RegisterId::Zmm23:
                break;
            case RegisterId::Zmm24:
                break;
            case RegisterId::Zmm25:
                break;
            case RegisterId::Zmm26:
                break;
            case RegisterId::Zmm27:
                break;
            case RegisterId::Zmm28:
                break;
            case RegisterId::Zmm29:
                break;
            case RegisterId::Zmm30:
                break;
            case RegisterId::Zmm31:
                break;
#ifdef _M_X64
            case RegisterId::Flags:
                return ReadRegister(hThread, UE_RFLAGS, 2);
            case RegisterId::EFlags:
                return ReadRegister(hThread, UE_RFLAGS, 4);
            case RegisterId::RFlags:
                return ReadRegister(hThread, UE_RFLAGS, 8);
#else
            case RegisterId::Flags:
                return ReadRegister(hThread, UE_EFLAGS, 2);
            case RegisterId::EFlags:
                return ReadRegister(hThread, UE_EFLAGS, 4);
#endif

#ifdef _M_X64
            case RegisterId::Ip:
                return ReadRegister(hThread, UE_RIP, 2);
            case RegisterId::Eip:
                return ReadRegister(hThread, UE_RIP, 4);
            case RegisterId::Rip:
                return ReadRegister(hThread, UE_RIP, 8);
#else
            case RegisterId::Ip:
                return ReadRegister(hThread, UE_EIP, 2);
            case RegisterId::Eip:
                return ReadRegister(hThread, UE_EIP, 4);
#endif
            case RegisterId::Es:
                return ReadRegister(hThread, UE_SEG_ES, 2);
            case RegisterId::Cs:
                return ReadRegister(hThread, UE_SEG_CS, 2);
            case RegisterId::Ss:
                return ReadRegister(hThread, UE_SEG_SS, 2);
            case RegisterId::Ds:
                return ReadRegister(hThread, UE_SEG_DS, 2);
            case RegisterId::Fs:
                return ReadRegister(hThread, UE_SEG_FS, 2);
            case RegisterId::Gs:
                return ReadRegister(hThread, UE_SEG_GS, 2);
            case RegisterId::Gdtr:
                break;
            case RegisterId::Ldtr:
                break;
            case RegisterId::Idtr:
                break;
            case RegisterId::Tr:
                break;
            case RegisterId::Tr0:
                break;
            case RegisterId::Tr1:
                break;
            case RegisterId::Tr2:
                break;
            case RegisterId::Tr3:
                break;
            case RegisterId::Tr4:
                break;
            case RegisterId::Tr5:
                break;
            case RegisterId::Tr6:
                break;
            case RegisterId::Tr7:
                break;
            case RegisterId::Cr0:
                break;
            case RegisterId::Cr1:
                break;
            case RegisterId::Cr2:
                break;
            case RegisterId::Cr3:
                break;
            case RegisterId::Cr4:
                break;
            case RegisterId::Cr5:
                break;
            case RegisterId::Cr6:
                break;
            case RegisterId::Cr7:
                break;
            case RegisterId::Cr8:
                break;
            case RegisterId::Cr9:
                break;
            case RegisterId::Cr10:
                break;
            case RegisterId::Cr11:
                break;
            case RegisterId::Cr12:
                break;
            case RegisterId::Cr13:
                break;
            case RegisterId::Cr14:
                break;
            case RegisterId::Cr15:
                break;
            case RegisterId::Dr0:
                break;
            case RegisterId::Dr1:
                break;
            case RegisterId::Dr2:
                break;
            case RegisterId::Dr3:
                break;
            case RegisterId::Dr4:
                break;
            case RegisterId::Dr5:
                break;
            case RegisterId::Dr6:
                break;
            case RegisterId::Dr7:
                break;
            case RegisterId::Dr8:
                break;
            case RegisterId::Dr9:
                break;
            case RegisterId::Dr10:
                break;
            case RegisterId::Dr11:
                break;
            case RegisterId::Dr12:
                break;
            case RegisterId::Dr13:
                break;
            case RegisterId::Dr14:
                break;
            case RegisterId::Dr15:
                break;
            case RegisterId::K0:
                break;
            case RegisterId::K1:
                break;
            case RegisterId::K2:
                break;
            case RegisterId::K3:
                break;
            case RegisterId::K4:
                break;
            case RegisterId::K5:
                break;
            case RegisterId::K6:
                break;
            case RegisterId::K7:
                break;
            case RegisterId::Bnd0:
                break;
            case RegisterId::Bnd1:
                break;
            case RegisterId::Bnd2:
                break;
            case RegisterId::Bnd3:
                break;
            case RegisterId::BndCfg:
                break;
            case RegisterId::BndStatus:
                break;
            case RegisterId::Mxcsr:
                break;
            case RegisterId::Pkru:
                break;
            case RegisterId::Xcr0:
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

        static void SetRegisterData(System::UIntPtr hThread, RegisterId reg, array<System::Byte>^ data)
        {
            switch (reg)
            {
            case RegisterId::None:
                return;
#ifdef _M_X64
            case RegisterId::Al:
                return WriteRegister(hThread, data, UE_RAX, 1);
            case RegisterId::Cl:
                return WriteRegister(hThread, data, UE_RCX, 1);
            case RegisterId::Dl:
                return WriteRegister(hThread, data, UE_RDX, 1);
            case RegisterId::Bl:
                return WriteRegister(hThread, data, UE_RBX, 1);
            case RegisterId::Ah:
                return WriteRegister(hThread, data, UE_RAX, 1, 1);
            case RegisterId::Ch:
                return WriteRegister(hThread, data, UE_RCX, 1, 1);
            case RegisterId::Dh:
                return WriteRegister(hThread, data, UE_RDX, 1, 1);
            case RegisterId::Bh:
                return WriteRegister(hThread, data, UE_RBX, 1, 1);
            case RegisterId::Spl:
                return WriteRegister(hThread, data, UE_RSP, 1);
            case RegisterId::Bpl:
                return WriteRegister(hThread, data, UE_RBP, 1);
            case RegisterId::Sil:
                return WriteRegister(hThread, data, UE_RSI, 1);
            case RegisterId::Dil:
                return WriteRegister(hThread, data, UE_RDI, 1);
            case RegisterId::R8b:
                return WriteRegister(hThread, data, UE_R8, 1);
            case RegisterId::R9b:
                return WriteRegister(hThread, data, UE_R9, 1);
            case RegisterId::R10b:
                return WriteRegister(hThread, data, UE_R10, 1);
            case RegisterId::R11b:
                return WriteRegister(hThread, data, UE_R11, 1);
            case RegisterId::R12b:
                return WriteRegister(hThread, data, UE_R12, 1);
            case RegisterId::R13b:
                return WriteRegister(hThread, data, UE_R13, 1);
            case RegisterId::R14b:
                return WriteRegister(hThread, data, UE_R14, 1);
            case RegisterId::R15b:
                return WriteRegister(hThread, data, UE_R15, 1);
            case RegisterId::Ax:
                return WriteRegister(hThread, data, UE_RAX, 2);
            case RegisterId::Cx:
                return WriteRegister(hThread, data, UE_RCX, 2);
            case RegisterId::Dx:
                return WriteRegister(hThread, data, UE_RDX, 2);
            case RegisterId::Bx:
                return WriteRegister(hThread, data, UE_RBX, 2);
            case RegisterId::Sp:
                return WriteRegister(hThread, data, UE_RSP, 2);
            case RegisterId::Bp:
                return WriteRegister(hThread, data, UE_RBP, 2);
            case RegisterId::Si:
                return WriteRegister(hThread, data, UE_RSI, 2);
            case RegisterId::Di:
                return WriteRegister(hThread, data, UE_RDI, 2);
            case RegisterId::R8w:
                return WriteRegister(hThread, data, UE_R8, 2);
            case RegisterId::R9w:
                return WriteRegister(hThread, data, UE_R9, 2);
            case RegisterId::R10w:
                return WriteRegister(hThread, data, UE_R10, 2);
            case RegisterId::R11w:
                return WriteRegister(hThread, data, UE_R11, 2);
            case RegisterId::R12w:
                return WriteRegister(hThread, data, UE_R12, 2);
            case RegisterId::R13w:
                return WriteRegister(hThread, data, UE_R13, 2);
            case RegisterId::R14w:
                return WriteRegister(hThread, data, UE_R14, 2);
            case RegisterId::R15w:
                return WriteRegister(hThread, data, UE_R15, 2);
            case RegisterId::Eax:
                return WriteRegister(hThread, data, UE_RAX, 4);
            case RegisterId::Ecx:
                return WriteRegister(hThread, data, UE_RCX, 4);
            case RegisterId::Edx:
                return WriteRegister(hThread, data, UE_RDX, 4);
            case RegisterId::Ebx:
                return WriteRegister(hThread, data, UE_RBX, 4);
            case RegisterId::Esp:
                return WriteRegister(hThread, data, UE_RSP, 4);
            case RegisterId::Ebp:
                return WriteRegister(hThread, data, UE_RBP, 4);
            case RegisterId::Esi:
                return WriteRegister(hThread, data, UE_RSI, 4);
            case RegisterId::Edi:
                return WriteRegister(hThread, data, UE_RDI, 4);
            case RegisterId::R8d:
                return WriteRegister(hThread, data, UE_R8, 4);
            case RegisterId::R9d:
                return WriteRegister(hThread, data, UE_R9, 4);
            case RegisterId::R10d:
                return WriteRegister(hThread, data, UE_R10, 4);
            case RegisterId::R11d:
                return WriteRegister(hThread, data, UE_R11, 4);
            case RegisterId::R12d:
                return WriteRegister(hThread, data, UE_R12, 4);
            case RegisterId::R13d:
                return WriteRegister(hThread, data, UE_R13, 4);
            case RegisterId::R14d:
                return WriteRegister(hThread, data, UE_R14, 4);
            case RegisterId::R15d:
                return WriteRegister(hThread, data, UE_R15, 4);
            case RegisterId::Rax:
                return WriteRegister(hThread, data, UE_RAX, 8);
            case RegisterId::Rcx:
                return WriteRegister(hThread, data, UE_RCX, 8);
            case RegisterId::Rdx:
                return WriteRegister(hThread, data, UE_RDX, 8);
            case RegisterId::Rbx:
                return WriteRegister(hThread, data, UE_RBP, 8);
            case RegisterId::Rsp:
                return WriteRegister(hThread, data, UE_RSP, 8);
            case RegisterId::Rbp:
                return WriteRegister(hThread, data, UE_RBP, 8);
            case RegisterId::Rsi:
                return WriteRegister(hThread, data, UE_RSI, 8);
            case RegisterId::Rdi:
                return WriteRegister(hThread, data, UE_RDI, 8);
            case RegisterId::R8:
                return WriteRegister(hThread, data, UE_R8, 8);
            case RegisterId::R9:
                return WriteRegister(hThread, data, UE_R9, 8);
            case RegisterId::R10:
                return WriteRegister(hThread, data, UE_R10, 8);
            case RegisterId::R11:
                return WriteRegister(hThread, data, UE_R11, 8);
            case RegisterId::R12:
                return WriteRegister(hThread, data, UE_R12, 8);
            case RegisterId::R13:
                return WriteRegister(hThread, data, UE_R13, 8);
            case RegisterId::R14:
                return WriteRegister(hThread, data, UE_R14, 8);
            case RegisterId::R15:
                return WriteRegister(hThread, data, UE_R15, 8);
#else
            case RegisterId::Al:
                return WriteRegister(hThread, data, UE_EAX, 1);
            case RegisterId::Cl:
                return WriteRegister(hThread, data, UE_ECX, 1);
            case RegisterId::Dl:
                return WriteRegister(hThread, data, UE_EDX, 1);
            case RegisterId::Bl:
                return WriteRegister(hThread, data, UE_EBX, 1);
            case RegisterId::Ah:
                return WriteRegister(hThread, data, UE_EAX, 1, 1);
            case RegisterId::Ch:
                return WriteRegister(hThread, data, UE_ECX, 1, 1);
            case RegisterId::Dh:
                return WriteRegister(hThread, data, UE_EDX, 1, 1);
            case RegisterId::Bh:
                return WriteRegister(hThread, data, UE_EBX, 1, 1);
            case RegisterId::Spl:
                return WriteRegister(hThread, data, UE_ESP, 1);
            case RegisterId::Bpl:
                return WriteRegister(hThread, data, UE_EBP, 1);
            case RegisterId::Sil:
                return WriteRegister(hThread, data, UE_ESI, 1);
            case RegisterId::Dil:
                return WriteRegister(hThread, data, UE_EDI, 1);
            case RegisterId::Ax:
                return WriteRegister(hThread, data, UE_EAX, 2);
            case RegisterId::Cx:
                return WriteRegister(hThread, data, UE_ECX, 2);
            case RegisterId::Dx:
                return WriteRegister(hThread, data, UE_EDX, 2);
            case RegisterId::Bx:
                return WriteRegister(hThread, data, UE_EBX, 2);
            case RegisterId::Sp:
                return WriteRegister(hThread, data, UE_ESP, 2);
            case RegisterId::Bp:
                return WriteRegister(hThread, data, UE_EBP, 2);
            case RegisterId::Si:
                return WriteRegister(hThread, data, UE_ESI, 2);
            case RegisterId::Di:
                return WriteRegister(hThread, data, UE_EDI, 2);
            case RegisterId::Eax:
                return WriteRegister(hThread, data, UE_EAX, 4);
            case RegisterId::Ecx:
                return WriteRegister(hThread, data, UE_ECX, 4);
            case RegisterId::Edx:
                return WriteRegister(hThread, data, UE_EDX, 4);
            case RegisterId::Ebx:
                return WriteRegister(hThread, data, UE_EBX, 4);
            case RegisterId::Esp:
                return WriteRegister(hThread, data, UE_ESP, 4);
            case RegisterId::Ebp:
                return WriteRegister(hThread, data, UE_EBP, 4);
            case RegisterId::Esi:
                return WriteRegister(hThread, data, UE_ESI, 4);
            case RegisterId::Edi:
                return WriteRegister(hThread, data, UE_EDI, 4);
#endif
            case RegisterId::St0:
                break;
            case RegisterId::St1:
                break;
            case RegisterId::St2:
                break;
            case RegisterId::St3:
                break;
            case RegisterId::St4:
                break;
            case RegisterId::St5:
                break;
            case RegisterId::St6:
                break;
            case RegisterId::St7:
                break;
            case RegisterId::X87Control:
                break;
            case RegisterId::X87Status:
                break;
            case RegisterId::X87Tag:
                break;
            case RegisterId::Mm0:
                break;
            case RegisterId::Mm1:
                break;
            case RegisterId::Mm2:
                break;
            case RegisterId::Mm3:
                break;
            case RegisterId::Mm4:
                break;
            case RegisterId::Mm5:
                break;
            case RegisterId::Mm6:
                break;
            case RegisterId::Mm7:
                break;
            case RegisterId::Xmm0:
                break;
            case RegisterId::Xmm1:
                break;
            case RegisterId::Xmm2:
                break;
            case RegisterId::Xmm3:
                break;
            case RegisterId::Xmm4:
                break;
            case RegisterId::Xmm5:
                break;
            case RegisterId::Xmm6:
                break;
            case RegisterId::Xmm7:
                break;
            case RegisterId::Xmm8:
                break;
            case RegisterId::Xmm9:
                break;
            case RegisterId::Xmm10:
                break;
            case RegisterId::Xmm11:
                break;
            case RegisterId::Xmm12:
                break;
            case RegisterId::Xmm13:
                break;
            case RegisterId::Xmm14:
                break;
            case RegisterId::Xmm15:
                break;
            case RegisterId::Xmm16:
                break;
            case RegisterId::Xmm17:
                break;
            case RegisterId::Xmm18:
                break;
            case RegisterId::Xmm19:
                break;
            case RegisterId::Xmm20:
                break;
            case RegisterId::Xmm21:
                break;
            case RegisterId::Xmm22:
                break;
            case RegisterId::Xmm23:
                break;
            case RegisterId::Xmm24:
                break;
            case RegisterId::Xmm25:
                break;
            case RegisterId::Xmm26:
                break;
            case RegisterId::Xmm27:
                break;
            case RegisterId::Xmm28:
                break;
            case RegisterId::Xmm29:
                break;
            case RegisterId::Xmm30:
                break;
            case RegisterId::Xmm31:
                break;
            case RegisterId::Ymm0:
                break;
            case RegisterId::Ymm1:
                break;
            case RegisterId::Ymm2:
                break;
            case RegisterId::Ymm3:
                break;
            case RegisterId::Ymm4:
                break;
            case RegisterId::Ymm5:
                break;
            case RegisterId::Ymm6:
                break;
            case RegisterId::Ymm7:
                break;
            case RegisterId::Ymm8:
                break;
            case RegisterId::Ymm9:
                break;
            case RegisterId::Ymm10:
                break;
            case RegisterId::Ymm11:
                break;
            case RegisterId::Ymm12:
                break;
            case RegisterId::Ymm13:
                break;
            case RegisterId::Ymm14:
                break;
            case RegisterId::Ymm15:
                break;
            case RegisterId::Ymm16:
                break;
            case RegisterId::Ymm17:
                break;
            case RegisterId::Ymm18:
                break;
            case RegisterId::Ymm19:
                break;
            case RegisterId::Ymm20:
                break;
            case RegisterId::Ymm21:
                break;
            case RegisterId::Ymm22:
                break;
            case RegisterId::Ymm23:
                break;
            case RegisterId::Ymm24:
                break;
            case RegisterId::Ymm25:
                break;
            case RegisterId::Ymm26:
                break;
            case RegisterId::Ymm27:
                break;
            case RegisterId::Ymm28:
                break;
            case RegisterId::Ymm29:
                break;
            case RegisterId::Ymm30:
                break;
            case RegisterId::Ymm31:
                break;
            case RegisterId::Zmm0:
                break;
            case RegisterId::Zmm1:
                break;
            case RegisterId::Zmm2:
                break;
            case RegisterId::Zmm3:
                break;
            case RegisterId::Zmm4:
                break;
            case RegisterId::Zmm5:
                break;
            case RegisterId::Zmm6:
                break;
            case RegisterId::Zmm7:
                break;
            case RegisterId::Zmm8:
                break;
            case RegisterId::Zmm9:
                break;
            case RegisterId::Zmm10:
                break;
            case RegisterId::Zmm11:
                break;
            case RegisterId::Zmm12:
                break;
            case RegisterId::Zmm13:
                break;
            case RegisterId::Zmm14:
                break;
            case RegisterId::Zmm15:
                break;
            case RegisterId::Zmm16:
                break;
            case RegisterId::Zmm17:
                break;
            case RegisterId::Zmm18:
                break;
            case RegisterId::Zmm19:
                break;
            case RegisterId::Zmm20:
                break;
            case RegisterId::Zmm21:
                break;
            case RegisterId::Zmm22:
                break;
            case RegisterId::Zmm23:
                break;
            case RegisterId::Zmm24:
                break;
            case RegisterId::Zmm25:
                break;
            case RegisterId::Zmm26:
                break;
            case RegisterId::Zmm27:
                break;
            case RegisterId::Zmm28:
                break;
            case RegisterId::Zmm29:
                break;
            case RegisterId::Zmm30:
                break;
            case RegisterId::Zmm31:
                break;
#ifdef _M_X64
            case RegisterId::Flags:
                return WriteRegister(hThread, data, UE_RFLAGS, 2);
            case RegisterId::EFlags:
                return WriteRegister(hThread, data, UE_RFLAGS, 4);
            case RegisterId::RFlags:
                return WriteRegister(hThread, data, UE_RFLAGS, 8);
            case RegisterId::Ip:
                return WriteRegister(hThread, data, UE_RIP, 2);
            case RegisterId::Eip:
                return WriteRegister(hThread, data, UE_RIP, 4);
            case RegisterId::Rip:
                return WriteRegister(hThread, data, UE_RIP, 8);
#else
            case RegisterId::Flags:
                return WriteRegister(hThread, data, UE_EFLAGS, 2);
            case RegisterId::EFlags:
                return WriteRegister(hThread, data, UE_EFLAGS, 4);
            case RegisterId::Ip:
                return WriteRegister(hThread, data, UE_EIP, 2);
            case RegisterId::Eip:
                return WriteRegister(hThread, data, UE_EIP, 4);
#endif
            case RegisterId::Es:
                return WriteRegister(hThread, data, UE_SEG_ES, 2);
            case RegisterId::Cs:
                return WriteRegister(hThread, data, UE_SEG_CS, 2);
            case RegisterId::Ss:
                return WriteRegister(hThread, data, UE_SEG_SS, 2);
            case RegisterId::Ds:
                return WriteRegister(hThread, data, UE_SEG_DS, 2);
            case RegisterId::Fs:
                return WriteRegister(hThread, data, UE_SEG_FS, 2);
            case RegisterId::Gs:
                return WriteRegister(hThread, data, UE_SEG_GS, 2);
            case RegisterId::Gdtr:
                break;
            case RegisterId::Ldtr:
                break;
            case RegisterId::Idtr:
                break;
            case RegisterId::Tr:
                break;
            case RegisterId::Tr0:
                break;
            case RegisterId::Tr1:
                break;
            case RegisterId::Tr2:
                break;
            case RegisterId::Tr3:
                break;
            case RegisterId::Tr4:
                break;
            case RegisterId::Tr5:
                break;
            case RegisterId::Tr6:
                break;
            case RegisterId::Tr7:
                break;
            case RegisterId::Cr0:
                break;
            case RegisterId::Cr1:
                break;
            case RegisterId::Cr2:
                break;
            case RegisterId::Cr3:
                break;
            case RegisterId::Cr4:
                break;
            case RegisterId::Cr5:
                break;
            case RegisterId::Cr6:
                break;
            case RegisterId::Cr7:
                break;
            case RegisterId::Cr8:
                break;
            case RegisterId::Cr9:
                break;
            case RegisterId::Cr10:
                break;
            case RegisterId::Cr11:
                break;
            case RegisterId::Cr12:
                break;
            case RegisterId::Cr13:
                break;
            case RegisterId::Cr14:
                break;
            case RegisterId::Cr15:
                break;
            case RegisterId::Dr0:
                break;
            case RegisterId::Dr1:
                break;
            case RegisterId::Dr2:
                break;
            case RegisterId::Dr3:
                break;
            case RegisterId::Dr4:
                break;
            case RegisterId::Dr5:
                break;
            case RegisterId::Dr6:
                break;
            case RegisterId::Dr7:
                break;
            case RegisterId::Dr8:
                break;
            case RegisterId::Dr9:
                break;
            case RegisterId::Dr10:
                break;
            case RegisterId::Dr11:
                break;
            case RegisterId::Dr12:
                break;
            case RegisterId::Dr13:
                break;
            case RegisterId::Dr14:
                break;
            case RegisterId::Dr15:
                break;
            case RegisterId::K0:
                break;
            case RegisterId::K1:
                break;
            case RegisterId::K2:
                break;
            case RegisterId::K3:
                break;
            case RegisterId::K4:
                break;
            case RegisterId::K5:
                break;
            case RegisterId::K6:
                break;
            case RegisterId::K7:
                break;
            case RegisterId::Bnd0:
                break;
            case RegisterId::Bnd1:
                break;
            case RegisterId::Bnd2:
                break;
            case RegisterId::Bnd3:
                break;
            case RegisterId::BndCfg:
                break;
            case RegisterId::BndStatus:
                break;
            case RegisterId::Mxcsr:
                break;
            case RegisterId::Pkru:
                break;
            case RegisterId::Xcr0:
                break;
            default:
                break;
            }
        }

    };
}
