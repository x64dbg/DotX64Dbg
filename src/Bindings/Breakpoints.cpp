#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_debug.h"

namespace Dotx64Dbg::Native
{
    public enum BreakpointType
    {
        None = 0,
        Normal = (1 << 0),
        Hardware = (1 << 1),
        Memory = (1 << 2),
        Dll = (1 << 3),
        Exception = (1 << 4),
        System = (1 << 5),
    };

    public enum HardwareType
    {
        HardwareAccess,
        HardwareWrite,
        HardwareExecute
    };

    public ref class Breakpoints
    {
    public:

        static void SetBreakpoint(duint address)
        {
            Script::Debug::SetBreakpoint(address);
        }

        static void DeleteBreakpoint(duint address)
        {
            Script::Debug::DeleteBreakpoint(address);
        }

        static void DisableBreakpoint(duint address)
        {
            Script::Debug::DisableBreakpoint(address);
        }

        static void SetHardwareBreakpoint(duint address, HardwareType type)
        {
            switch (type)
            {
            case HardwareAccess:
                Script::Debug::SetHardwareBreakpoint(address, Script::Debug::HardwareType::HardwareAccess);
                break;
            case HardwareWrite:
                Script::Debug::SetHardwareBreakpoint(address, Script::Debug::HardwareType::HardwareWrite);
                break;
            case HardwareExecute:
                Script::Debug::SetHardwareBreakpoint(address, Script::Debug::HardwareType::HardwareExecute);
                break;
            default:
                break;
            }
        }

        static void DeleteHardwareBreakpoint(duint address)
        {
            Script::Debug::DeleteHardwareBreakpoint(address);
        }
    };
}
