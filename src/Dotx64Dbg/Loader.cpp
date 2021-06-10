#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

struct Wrapper
{
    static void Init()
    {
        Dotx64Dbg::Manager::Init();
    }
    static void Setup()
    {
        Dotx64Dbg::Manager::Setup();
    }
    static void Stop()
    {
        Dotx64Dbg::Manager::Shutdown();
    }
};

// Unmanaged section.
#pragma unmanaged

#define PLUG_EXPORT extern "C" __declspec(dllexport)

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
}

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    Wrapper::Init();

    initStruct->pluginVersion = 1;
    initStruct->sdkVersion = 1;
    strncpy_s(initStruct->pluginName, "DotX64Dbg", _TRUNCATE);



    return true;
}

PLUG_EXPORT bool plugstop()
{
    return true;
}

PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
}
