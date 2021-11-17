#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"

#include "Marshal.hpp"

namespace Dotx64Dbg::Native
{
    using namespace System;
    using namespace System::Runtime::InteropServices;

    [UnmanagedFunctionPointer(CallingConvention::Cdecl)]
    public delegate bool CommandCallback(int argc, System::IntPtr);

    public ref class Commands
    {
    public:
        static bool RegisterCommand(int pluginHandle, System::String^ cmd, bool debugOnly, CommandCallback^ cb)
        {
            GCHandle gcCb = GCHandle::Alloc(cb);

            IntPtr ip = Marshal::GetFunctionPointerForDelegate(cb);
            auto* fn = static_cast<CBPLUGINCOMMAND>(ip.ToPointer());

            auto cmdStr = interop::toUTF8(cmd);
            return _plugin_registercommand(pluginHandle, cmdStr.c_str(), fn, debugOnly);
        }

        static bool UnregisterCommand(int pluginHandle, System::String^ cmd)
        {
            auto cmdStr = interop::toUTF8(cmd);
            return _plugin_unregistercommand(pluginHandle, cmdStr.c_str());
        }
    };
}
