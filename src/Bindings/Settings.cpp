#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_module.h"
#include "Register.hpp"
#include "pluginsdk/TitanEngine/TitanEngine.h"

#include "Marshal.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg {

    public ref class X64DbgSettings
    {
    public:
        static System::String^ Get(System::String^ section, System::String^ key)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cSection = oMarshalContext.marshal_as<const char*>(section);
            const char* cKey = oMarshalContext.marshal_as<const char*>(key);

            char buf[1024]{};
            if (!BridgeSettingGet(cSection, cKey, buf))
                return nullptr;

            return gcnew System::String(buf);
        }
    };

}