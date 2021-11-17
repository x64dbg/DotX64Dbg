#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "Marshal.hpp"

namespace Dotx64Dbg::Native
{
    public ref class Logging
    {
    public:
        static void Write(System::String^ text)
        {
            auto textStr = interop::toUTF8(text);
            _plugin_logprint(textStr.c_str());
        }

        static void WriteLine(System::String^ text)
        {
            auto textStr = interop::toUTF8(text);
            textStr = textStr + "\n";
            _plugin_logprint(textStr.c_str());
        }

        static void WriteLine()
        {
            _plugin_logprint("\n");
        }
    };
}
