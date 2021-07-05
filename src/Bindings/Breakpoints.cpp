#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_debug.h"

namespace Dotx64Dbg::Native
{
    public ref class Breakpoints
    {
    public:
        enum class BreakpointType
        {
            None = 0,
            Normal = (1 << 0),
            Hardware = (1 << 1),
            Memory = (1 << 2),
            Dll = (1 << 3),
            Exception = (1 << 4),
            System = (1 << 5),
        };

        enum class HardwareType
        {
            HardwareAccess = 0,
            HardwareWrite,
            HardwareExecute
        };

        static bool SetBreakpoint(duint address)
        {
            return Script::Debug::SetBreakpoint(address);
        }

        static bool DeleteBreakpoint(duint address)
        {
            return Script::Debug::DeleteBreakpoint(address);
        }

        static bool DisableBreakpoint(duint address)
        {
            return Script::Debug::DisableBreakpoint(address);
        }

        static bool SetHardwareBreakpoint(duint address, HardwareType type)
        {
            switch (type)
            {
            case HardwareType::HardwareAccess:
                return Script::Debug::SetHardwareBreakpoint(address, Script::Debug::HardwareType::HardwareAccess);
            case HardwareType::HardwareWrite:
                return Script::Debug::SetHardwareBreakpoint(address, Script::Debug::HardwareType::HardwareWrite);
            case HardwareType::HardwareExecute:
                return Script::Debug::SetHardwareBreakpoint(address, Script::Debug::HardwareType::HardwareExecute);
            default:
                break;
            }
            return false;
        }

        static bool DeleteHardwareBreakpoint(duint address)
        {
            return Script::Debug::DeleteHardwareBreakpoint(address);
        }
    };
}
