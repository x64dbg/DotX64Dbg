#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_misc.h"
#include "pluginsdk/_dbgfunctions.h"

#include <msclr/marshal.h>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native
{
    public delegate System::UIntPtr ExpressionHandler(int argc, System::IntPtr, System::IntPtr);

    public ref class Expressions
    {
    public:
        static bool TryEvaluate(System::String^ expr, [Out] IntPtr% value)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(expr);

            duint val = 0;
            bool res = Script::Misc::ParseExpression(cstr, &val);

#ifdef _WIN64
            value = IntPtr((unsigned long long)val);
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

            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(expr);

            char buf[1024]{};
            if (!DbgFunctions()->StringFormatInline(cstr, sizeof(buf), buf))
            {
                return false;
            }

            value = gcnew System::String(buf);
            return true;
        }

        static System::String^ Format(System::String^ expr)
        {
            if (!DbgFunctions()->StringFormatInline)
                return nullptr;

            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(expr);

            char buf[1024]{};
            if (!DbgFunctions()->StringFormatInline(cstr, sizeof(buf), buf))
            {
                throw gcnew System::Exception("Invalid expression");
            }

            return gcnew System::String(buf);
        }

        static bool IsValidExpression(System::String^ expr)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(expr);

            return DbgIsValidExpression(cstr);
        }

        static bool RegisterExpression(int pluginHandle, System::String^ name, int argc, ExpressionHandler^ cb)
        {
            GCHandle gcCb = GCHandle::Alloc(cb);

            IntPtr ip = Marshal::GetFunctionPointerForDelegate(cb);
            auto* fn = static_cast<CBPLUGINEXPRFUNCTION>(ip.ToPointer());

            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(name);
            return _plugin_registerexprfunction(pluginHandle, cstr, argc, fn, nullptr);
        }

        static bool UnregisterExpression(int pluginHandle, System::String^ name)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(name);

            return _plugin_unregisterexprfunction(pluginHandle, cstr);
        }

    };

}
