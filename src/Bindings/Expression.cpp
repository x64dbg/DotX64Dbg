#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_misc.h"
#include "pluginsdk/_dbgfunctions.h"

#include <msclr/marshal.h>

namespace Dotx64Dbg
{
    using namespace System::Runtime::InteropServices;

    public ref class Expression
    {
    public:

        /// <summary>
        /// Evaluates the given expression and results the evaluated value.
        /// </summary>
        /// <param name="expr">Expression</param>
        /// <param name="value">Resulting value</param>
        /// <returns>True on success, false in case of errors</returns>
        /// <example>
        /// <code>
        /// ulong val = 0;
        /// if(Expression.TryEvaluate("rip", val)) { Console.WriteLine("Value of rip {0}", val); }
        /// </code>
        /// </example>
        static bool TryEvaluate(System::String^ expr, [Out] uint64_t% value)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(expr);

            duint val = 0;
            bool res = Script::Misc::ParseExpression(cstr, &val);

            value = val;
            return res;
        }

        /// <summary>
        /// Same as TryEvaluate except the function throws if the expression is invalid.
        /// </summary>
        /// <see cref="TryEvaluate"/>
        static uint64_t Evaluate(System::String^ expr)
        {
            uint64_t res = 0;
            if (!TryEvaluate(expr, res))
            {
                throw gcnew System::Exception("Invalid expression");
            }
            return res;
        }


        /// <summary>
        /// Formats the given the expression and results the formatted string.
        /// </summary>
        /// <param name="expr">Expression to format</param>
        /// <param name="value">Resulting formatted expression</param>
        /// <returns>True on success, false in case of any errors</returns>
        /// <example>
        /// <code>
        /// string formatted;
        /// if(Expression.TryFormat("rip = {rip}", formatted)) { Console.WriteLine("Formatted: {0}", formatted); }
        /// </code>
        /// </example>
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

        /// <summary>
        /// Same as TryFormat except the function throws if the expression is invalid.
        /// </summary>
        /// <see cref="TryFormat"/>
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
    };
}
