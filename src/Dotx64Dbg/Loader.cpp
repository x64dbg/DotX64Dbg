#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"
#include "pluginsdk/_scriptapi_register.h"

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

    static void SetMenuData(PLUG_SETUPSTRUCT* setupStruct)
    {
        Dotx64Dbg::MenuData data;
        data.hMenu = setupStruct->hMenu;
        data.hMenuDisasm = setupStruct->hMenuDisasm;
        data.hMenuDump = setupStruct->hMenuDump;
        data.hMenuStack = setupStruct->hMenuStack;
        data.hMenuGraph = setupStruct->hMenuGraph;
        data.hMenuMemmap = setupStruct->hMenuMemmap;
        data.hMenuSymmod = setupStruct->hMenuSymmod;
        Dotx64Dbg::Manager::SetMenuData(data);
    }

    static void DebugEvent(PLUG_CB_DEBUGEVENT* ev)
    {
        switch (ev->DebugEvent->dwDebugEventCode)
        {
        case EXCEPTION_DEBUG_EVENT:
        {
            auto& src = ev->DebugEvent->u.Exception;

            Dotx64Dbg::ExceptionEventInfo dst{};
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

            Dotx64Dbg::ThreadCreateEventInfo dst{};
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

            Dotx64Dbg::ThreadExitEventInfo dst{};
            dst.ProcessId = ev->DebugEvent->dwProcessId;
            dst.ThreadId = ev->DebugEvent->dwThreadId;
            dst.ExitCode = src.dwExitCode;

            Dotx64Dbg::Manager::OnThreadExitEvent(dst);
            break;
        }
        case EXIT_PROCESS_DEBUG_EVENT:
        {
            auto& src = ev->DebugEvent->u.ExitProcess;

            Dotx64Dbg::ProcessExitEventInfo dst{};
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

        Dotx64Dbg::ProcessCreateEventInfo dst{};
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

    static void OnBreakpointEvent(PLUG_CB_BREAKPOINT* info, bool systemBp)
    {
        Dotx64Dbg::BreakpointEventInfo dst{};

        if (info == nullptr && systemBp)
        {
            auto addr = Script::Register::Get(Script::Register::CIP);
            char modName[1024]{};
            DbgGetModuleAt(addr, modName);

            dst.Type = Dotx64Dbg::Breakpoints::Type::System;
            dst.Address = addr;
            dst.Name = gcnew System::String("System Breakpoint");
            dst.Slot = 0xFFFF;
            dst.HitCount = 1;
            dst.Active = false;
            dst.Module = gcnew System::String(modName);
        }
        else
        {
            const auto* bp = info->breakpoint;

            dst.Type = (Dotx64Dbg::Breakpoints::Type)bp->type;
            dst.Address = bp->addr;
            dst.Enabled = bp->enabled;
            dst.Singleshot = bp->singleshoot;
            dst.Active = bp->active;
            dst.Name = gcnew System::String(bp->name);
            dst.Module = gcnew System::String(bp->mod);
            dst.Slot = bp->slot;
            dst.TypeEx = bp->typeEx;
            dst.Size = static_cast<int>(bp->hwSize);
            dst.HitCount = bp->hitCount;
            dst.FastResume = bp->fastResume;
            dst.Silent = bp->silent;
            dst.BreakCondition = gcnew System::String(bp->breakCondition);
            dst.LogText = gcnew System::String(bp->logText);
            dst.LogCondition = gcnew System::String(bp->logCondition);
            dst.CommandText = gcnew System::String(bp->commandText);
            dst.CommandCondition = gcnew System::String(bp->commandCondition);
        }

        Dotx64Dbg::Manager::OnBreakpointEvent(dst);
    }

    static void MenuCallback(int id)
    {
        Dotx64Dbg::Manager::OnMenuCallback(id);
    }

    static bool EvalScript(const char* input)
    {
        auto str = gcnew System::String(input);
        return Dotx64Dbg::Manager::EvalScript(str);
    }

    static void OnSteppedEvent()
    {
        Dotx64Dbg::Manager::OnSteppedEvent();
    }

    static void OnDebuggerStart(const char* file)
    {
        auto str = gcnew System::String(file);
        Dotx64Dbg::Manager::OnDebuggerStart(str);
    }

    static void OnDebuggerStop()
    {
        Dotx64Dbg::Manager::OnDebuggerStop();
    }
};

// Unmanaged section.
#pragma unmanaged

#define PLUG_EXPORT extern "C" __declspec(dllexport)

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
    Wrapper::MenuCallback(info->hEntry);
}

PLUG_EXPORT void CBINITDEBUG(CBTYPE cbType, PLUG_CB_INITDEBUG* info)
{
    Wrapper::OnDebuggerStart(info->szFileName);
}

PLUG_EXPORT void CBSTOPDEBUG(CBTYPE cbType, PLUG_CB_STOPDEBUG* info)
{
    Wrapper::OnDebuggerStop();
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

PLUG_EXPORT void CBBREAKPOINT(CBTYPE cbType, PLUG_CB_BREAKPOINT* info)
{
    Wrapper::OnBreakpointEvent(info, false);
}

PLUG_EXPORT void CBSYSTEMBREAKPOINT(CBTYPE cbType, PLUG_CB_SYSTEMBREAKPOINT* info)
{
    Wrapper::OnBreakpointEvent(nullptr, true);
}

PLUG_EXPORT void CBRESUMEDEBUG(CBTYPE cbType, PLUG_CB_RESUMEDEBUG* info)
{
}

PLUG_EXPORT void CBSTEPPED(CBTYPE cbType, PLUG_CB_STEPPED* info)
{
    Wrapper::OnSteppedEvent();
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

bool CBEXECUTESCRIPT(const char* text)
{
    return Wrapper::EvalScript(text);
}

void CBSCRIPTAUTOCOMPLETE(const char* text, char** entries, int* entryCount)
{
    if (entryCount)
        *entryCount = 0;
}

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    Wrapper::Init(initStruct->pluginHandle);

    initStruct->pluginVersion = 1;
    initStruct->sdkVersion = 1;
    strncpy_s(initStruct->pluginName, "DotX64Dbg", _TRUNCATE);

    SCRIPTTYPEINFO sti = {};
    sti.execute = CBEXECUTESCRIPT;
    // Lets hope this never collides with any other plugin :shrug:
    sti.id = 'D' + 'o' + 't' + 'x' + '6' + '4' + 'D' + 'b' + 'g';
    strcpy_s(sti.name, "Dotx64Dbg");

    GuiRegisterScriptLanguage(&sti);


    return true;
}

PLUG_EXPORT bool plugstop()
{
    Wrapper::Shutdown();
    return true;
}

PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    Wrapper::SetMenuData(setupStruct);
}
