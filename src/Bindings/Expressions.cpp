#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_misc.h"
#include "pluginsdk/_dbgfunctions.h"

#include "Marshal.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native
{
    [UnmanagedFunctionPointer(CallingConvention::Cdecl)]
    public delegate System::UIntPtr ExpressionHandler(int argc, System::IntPtr, System::IntPtr);

    public ref class Expressions
    {
    public:
        static bool TryEvaluate(System::String^ expr, [Out] IntPtr% value)
        {
            auto exprStr = interop::toUTF8(expr);

            duint val = 0;
            bool res = Script::Misc::ParseExpression(exprStr.c_str(), &val);

#ifdef _WIN64
            value = IntPtr((long long)val);
#else
            value = IntPtr((int)val);
#endif
            return res;
        }

        static System::IntPtr Evaluate(System::String^ expr)
        {
            IntPtr res = IntPtr(0);
            if (!TryEvaluate(expr, res))
            {
                throw gcnew System::Exception("Invalid expression");
            }
            return res;
        }

        static bool TryFormat(System::String^ expr, [Out] System::String^% value)
        {
            if (!DbgFunctions()->StringFormatInline)
                return false;

            auto exprStr = interop::toUTF8(expr);

            char buf[1024]{};
            if (!DbgFunctions()->StringFormatInline(exprStr.c_str(), sizeof(buf), buf))
            {
                return false;
            }

            value = interop::stringFromUTF8(buf);
            return true;
        }

        static System::String^ Format(System::String^ expr)
        {
            if (!DbgFunctions()->StringFormatInline)
                return nullptr;

            auto exprStr = interop::toUTF8(expr);

            char buf[1024]{};
            if (!DbgFunctions()->StringFormatInline(exprStr.c_str(), sizeof(buf), buf))
            {
                throw gcnew System::Exception("Invalid expression");
            }

            return interop::stringFromUTF8(buf);
        }

        static bool IsValidExpression(System::String^ expr)
        {
            auto exprStr = interop::toUTF8(expr);
            return DbgIsValidExpression(exprStr.c_str());
        }

        static bool RegisterExpression(int pluginHandle, System::String^ name, int argc, ExpressionHandler^ cb)
        {
            GCHandle gcCb = GCHandle::Alloc(cb);

            IntPtr ip = Marshal::GetFunctionPointerForDelegate(cb);
            auto* fn = static_cast<CBPLUGINEXPRFUNCTION>(ip.ToPointer());

            auto nameStr = interop::toUTF8(name);
            return _plugin_registerexprfunction(pluginHandle, nameStr.c_str(), argc, fn, nullptr);
        }

        static bool UnregisterExpression(int pluginHandle, System::String^ name)
        {
            auto nameStr = interop::toUTF8(name);
            return _plugin_unregisterexprfunction(pluginHandle, nameStr.c_str());
        }

    };

}
