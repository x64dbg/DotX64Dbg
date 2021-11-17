#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_module.h"
#include "Register.hpp"
#include "pluginsdk/TitanEngine/TitanEngine.h"

#include "Marshal.hpp"

namespace Dotx64Dbg {

    public ref class X64DbgSettings
    {
    public:
        static System::String^ Get(System::String^ section, System::String^ key)
        {
            auto sectionStr = interop::toUTF8(section);
            auto keyStr = interop::toUTF8(key);

            char buf[1024]{};
            if (!BridgeSettingGet(sectionStr.c_str(), keyStr.c_str(), buf))
                return nullptr;

            return interop::stringFromUTF8(buf);
        }
    };

}
