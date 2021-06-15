#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

struct Wrapper
{
    static void Init(int pluginHandle)
    {
        Dotx64Dbg::Manager::Init(pluginHandle);
    }

    static void Setup()
    {
        Dotx64Dbg::Manager::Setup();
    }

    static void Shutdown()
    {
        Dotx64Dbg::Manager::Shutdown();
    }

    static void DebugEvent(PLUG_CB_DEBUGEVENT* ev)
    {
        switch (ev->DebugEvent->dwDebugEventCode)
        {
        case EXCEPTION_DEBUG_EVENT:
        {
            auto& src = ev->DebugEvent->u.Exception;

            Dotx64Dbg::ExceptionEventInfo dst;
            dst.ProcessId = ev->DebugEvent->dwProcessId;
            dst.ThreadId = ev->DebugEvent->dwThreadId;
            dst.FirstChance = src.dwFirstChance ? true : false;
            dst.ExceptionCode = src.ExceptionRecord.ExceptionCode;
            dst.ExceptionFlags = src.ExceptionRecord.ExceptionFlags;
            dst.ExceptionAddress = reinterpret_cast<uintptr_t>(src.ExceptionRecord.ExceptionAddress);

            Dotx64Dbg::Manager::OnExceptionEvent(dst);
            break;
        }
        case CREATE_THREAD_DEBUG_EVENT:
        {
            auto& src = ev->DebugEvent->u.CreateThread;

            Dotx64Dbg::ThreadCreateEventInfo dst;
            dst.ProcessId = ev->DebugEvent->dwProcessId;
            dst.ThreadId = ev->DebugEvent->dwThreadId;
            dst.Handle = reinterpret_cast<uint64_t>(src.hThread);
            dst.StartAddress = reinterpret_cast<uint64_t>(src.lpStartAddress);
            dst.ThreadLocalBase = reinterpret_cast<uint64_t>(src.lpThreadLocalBase);

            Dotx64Dbg::Manager::OnThreadCreateEvent(dst);
            break;
        }
        case CREATE_PROCESS_DEBUG_EVENT:
        {
            // Moved to OnProcessCreate plugin callback.
            break;
        }
        case EXIT_THREAD_DEBUG_EVENT:
        {
            auto& src = ev->DebugEvent->u.ExitThread;

            Dotx64Dbg::ThreadExitEventInfo dst;
            dst.ProcessId = ev->DebugEvent->dwProcessId;
            dst.ThreadId = ev->DebugEvent->dwThreadId;
            dst.ExitCode = src.dwExitCode;

            Dotx64Dbg::Manager::OnThreadExitEvent(dst);
            break;
        }
        case EXIT_PROCESS_DEBUG_EVENT:
        {
            auto& src = ev->DebugEvent->u.ExitProcess;

            Dotx64Dbg::ProcessExitEventInfo dst;
            dst.ProcessId = ev->DebugEvent->dwProcessId;
            dst.ThreadId = ev->DebugEvent->dwThreadId;
            dst.ExitCode = src.dwExitCode;

            Dotx64Dbg::Manager::OnProcessExitEvent(dst);
            break;
        }
        case LOAD_DLL_DEBUG_EVENT:
        {

            break;
        }
        case UNLOAD_DLL_DEBUG_EVENT:
        {

            break;
        }
        case OUTPUT_DEBUG_STRING_EVENT:
        {

            break;
        }
        case RIP_EVENT:
        {

            break;
        }
        }
    }

    static void OnProcessCreate(PLUG_CB_CREATEPROCESS* info)
    {
        auto* src = info->CreateProcessInfo;

        Dotx64Dbg::ProcessCreateEventInfo dst;
        dst.ProcessId = info->fdProcessInfo->dwProcessId;
        dst.ThreadId = info->fdProcessInfo->dwThreadId;
        dst.FileHandle = reinterpret_cast<uint64_t>(src->hFile);
        dst.ProcessHandle = reinterpret_cast<uint64_t>(info->fdProcessInfo->hProcess);
        dst.ThreadHandle = reinterpret_cast<uint64_t>(info->fdProcessInfo->hThread);
        dst.ImageBase = reinterpret_cast<uint64_t>(src->lpBaseOfImage);
        dst.DebugInfoFileOffset = src->dwDebugInfoFileOffset;
        dst.DebugInfoSize = src->nDebugInfoSize;
        dst.ThreadLocalBase = reinterpret_cast<uint64_t>(src->lpThreadLocalBase);
        dst.StartAddress = reinterpret_cast<uint64_t>(src->lpStartAddress);
        dst.ImageName = reinterpret_cast<uint64_t>(src->lpImageName);
        dst.Unicode = src->fUnicode;

        Dotx64Dbg::Manager::OnProcessCreateEvent(dst);
    }
};

// Unmanaged section.
#pragma unmanaged

#define PLUG_EXPORT extern "C" __declspec(dllexport)

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
}

PLUG_EXPORT void CBINITDEBUG(CBTYPE cbType, PLUG_CB_INITDEBUG* info)
{
}

PLUG_EXPORT void CBSTOPDEBUG(CBTYPE cbType, PLUG_CB_STOPDEBUG* info)
{
}

PLUG_EXPORT void CBEXCEPTION(CBTYPE cbType, PLUG_CB_EXCEPTION* info)
{
}

PLUG_EXPORT void CBPAUSEDEBUG(CBTYPE cbType, PLUG_CB_PAUSEDEBUG* info)
{
}

PLUG_EXPORT void CBCREATEPROCESS(CBTYPE cbType, PLUG_CB_CREATEPROCESS* info)
{
    Wrapper::OnProcessCreate(info);
}

PLUG_EXPORT void CBRESUMEDEBUG(CBTYPE cbType, PLUG_CB_RESUMEDEBUG* info)
{
}

PLUG_EXPORT void CBSTEPPED(CBTYPE cbType, PLUG_CB_STEPPED* info)
{
}

PLUG_EXPORT void CBDEBUGEVENT(CBTYPE cbType, PLUG_CB_DEBUGEVENT* info)
{
    Wrapper::DebugEvent(info);
}

PLUG_EXPORT void CBLOADDLL(CBTYPE cbType, PLUG_CB_LOADDLL* info)
{
}

PLUG_EXPORT void CBUNLOADDLL(CBTYPE cbType, PLUG_CB_UNLOADDLL* info)
{
}

PLUG_EXPORT void CBCREATETHREAD(CBTYPE cbType, PLUG_CB_CREATETHREAD* info)
{
}

PLUG_EXPORT void CBEXITTHREAD(CBTYPE cbType, PLUG_CB_EXITTHREAD* info)
{
}

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    Wrapper::Init(initStruct->pluginHandle);

    initStruct->pluginVersion = 1;
    initStruct->sdkVersion = 1;
    strncpy_s(initStruct->pluginName, "DotX64Dbg", _TRUNCATE);

    return true;
}

PLUG_EXPORT bool plugstop()
{
    Wrapper::Shutdown();

    return true;
}

PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
}
