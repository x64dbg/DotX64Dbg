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

        static bool SetBreakpoint(System::UIntPtr address)
        {
            return Script::Debug::SetBreakpoint(static_cast<duint>(address.ToUInt64()));
        }

        static bool DeleteBreakpoint(System::UIntPtr address)
        {
            return Script::Debug::DeleteBreakpoint(static_cast<duint>(address.ToUInt64()));
        }

        static bool DisableBreakpoint(System::UIntPtr address)
        {
            return Script::Debug::DisableBreakpoint(static_cast<duint>(address.ToUInt64()));
        }

        static bool SetHardwareBreakpoint(System::UIntPtr address, HardwareType type)
        {
            auto va = static_cast<duint>(address.ToUInt64());
            switch (type)
            {
            case HardwareType::HardwareAccess:
                return Script::Debug::SetHardwareBreakpoint(va, Script::Debug::HardwareType::HardwareAccess);
            case HardwareType::HardwareWrite:
                return Script::Debug::SetHardwareBreakpoint(va, Script::Debug::HardwareType::HardwareWrite);
            case HardwareType::HardwareExecute:
                return Script::Debug::SetHardwareBreakpoint(va, Script::Debug::HardwareType::HardwareExecute);
            default:
                break;
            }
            return false;
        }

        static bool DeleteHardwareBreakpoint(System::UIntPtr address)
        {
            return Script::Debug::DeleteHardwareBreakpoint(static_cast<duint>(address.ToUInt64()));
        }
    };
}
