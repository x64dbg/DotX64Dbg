#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native
{
    public ref class Logging
    {
    public:
        static void Write(String^ text)
        {
            char* str = (char*)Marshal::StringToHGlobalAnsi(text).ToPointer();
            _plugin_logprint(str);
            Marshal::FreeHGlobal((IntPtr)str);
        }

        static void WriteLine(String^ text)
        {
            text = text + "\n";

            char* str = (char*)Marshal::StringToHGlobalAnsi(text).ToPointer();
            _plugin_logprint(str);
            Marshal::FreeHGlobal((IntPtr)str);
        }
    };
}
