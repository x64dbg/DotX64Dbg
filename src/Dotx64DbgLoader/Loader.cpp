#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"
#include "pluginsdk/_scriptapi_register.h"

static HMODULE _module{};

template<typename T>
class CallHelper
{
    T _f;
public:
    CallHelper(HMODULE mod, const char* name)
    {
        _f = reinterpret_cast<T>(GetProcAddress(mod, name));
    }

    operator bool() const
    {
        return _f != nullptr;
    }

    template<typename ...Args>
    auto operator()(Args&& ...args)
    {
        return _f(std::forward<Args&&>(args)...);
    }
};

#define PLUG_EXPORT extern "C" __declspec(dllexport)

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
    static CallHelper<decltype(&CBMENUENTRY)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBINITDEBUG(CBTYPE cbType, PLUG_CB_INITDEBUG* info)
{
    static CallHelper<decltype(&CBINITDEBUG)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBSTOPDEBUG(CBTYPE cbType, PLUG_CB_STOPDEBUG* info)
{
    static CallHelper<decltype(&CBSTOPDEBUG)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBEXCEPTION(CBTYPE cbType, PLUG_CB_EXCEPTION* info)
{
    static CallHelper<decltype(&CBEXCEPTION)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBPAUSEDEBUG(CBTYPE cbType, PLUG_CB_PAUSEDEBUG* info)
{
    static CallHelper<decltype(&CBPAUSEDEBUG)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBCREATEPROCESS(CBTYPE cbType, PLUG_CB_CREATEPROCESS* info)
{
    static CallHelper<decltype(&CBCREATEPROCESS)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBBREAKPOINT(CBTYPE cbType, PLUG_CB_BREAKPOINT* info)
{
    static CallHelper<decltype(&CBBREAKPOINT)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBSYSTEMBREAKPOINT(CBTYPE cbType, PLUG_CB_SYSTEMBREAKPOINT* info)
{
    static CallHelper<decltype(&CBSYSTEMBREAKPOINT)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBRESUMEDEBUG(CBTYPE cbType, PLUG_CB_RESUMEDEBUG* info)
{
    static CallHelper<decltype(&CBRESUMEDEBUG)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBSTEPPED(CBTYPE cbType, PLUG_CB_STEPPED* info)
{
    static CallHelper<decltype(&CBSTEPPED)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBDEBUGEVENT(CBTYPE cbType, PLUG_CB_DEBUGEVENT* info)
{
    static CallHelper<decltype(&CBDEBUGEVENT)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBLOADDLL(CBTYPE cbType, PLUG_CB_LOADDLL* info)
{
    static CallHelper<decltype(&CBLOADDLL)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBUNLOADDLL(CBTYPE cbType, PLUG_CB_UNLOADDLL* info)
{
    static CallHelper<decltype(&CBUNLOADDLL)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBCREATETHREAD(CBTYPE cbType, PLUG_CB_CREATETHREAD* info)
{
    static CallHelper<decltype(&CBCREATETHREAD)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

PLUG_EXPORT void CBEXITTHREAD(CBTYPE cbType, PLUG_CB_EXITTHREAD* info)
{
    static CallHelper<decltype(&CBEXITTHREAD)> f(_module, __FUNCTION__);
    if (f)
        return f(cbType, info);
}

bool CBEXECUTESCRIPT(const char* text)
{
    static CallHelper<decltype(&CBEXECUTESCRIPT)> f(_module, __FUNCTION__);
    if (f)
        return f(text);

    return false;
}

void CBSCRIPTAUTOCOMPLETE(const char* text, char** entries, int* entryCount)
{
    static CallHelper<decltype(&CBSCRIPTAUTOCOMPLETE)> f(_module, __FUNCTION__);
    if (f)
        return f(text, entries, entryCount);
}

static HMODULE _thisModule = nullptr;

int DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        _thisModule = hmodule;
    }
    return TRUE;
}

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    char curPath[1024]{};
    GetModuleFileNameA(_thisModule, curPath, sizeof(curPath));

    if (auto* p = strrchr(curPath, '\\'); p != nullptr)
    {
        *p = '\0';
    }

    char dllPath[1024]{};
    sprintf_s(dllPath, "%s\\Dotx64Dbg.dll", curPath);

    _module = LoadLibraryA(dllPath);
    if (_module == nullptr)
    {
        _plugin_logprintf("Unable to load Dotx64Dbg (%s) (%08X), make sure you have following installed:\n"
            "- .NET 6.0 Runtime (https://dotnet.microsoft.com/download/dotnet/6.0)\n"
            "- Visual Studio 2019 Runtime (https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0)\n",
            dllPath,
            GetLastError()
        );
        return false;
    }

    static CallHelper<decltype(&pluginit)> f(_module, __FUNCTION__);
    if (f)
        return f(initStruct);

    return false;
}

PLUG_EXPORT bool plugstop()
{
    if (_module == nullptr)
        return false;

    static CallHelper<decltype(&plugstop)> f(_module, __FUNCTION__);
    if (f)
    {
        f();
    }

    FreeLibrary(_module);
    return true;
}

PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    static CallHelper<decltype(&plugsetup)> f(_module, __FUNCTION__);
    if (f)
    {
        return f(setupStruct);
    }
}
