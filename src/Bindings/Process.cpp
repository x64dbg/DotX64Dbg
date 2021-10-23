#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "Register.hpp"
#include "pluginsdk/TitanEngine/TitanEngine.h"

#include "Marshal.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native
{
    public ref class Process
    {
    public:
        static uint32_t GetPID()
        {
            return DbgGetProcessId();
        }

        static System::UIntPtr GetNativeHandle()
        {
            return System::UIntPtr(DbgGetProcessHandle());
        }
    };
}
