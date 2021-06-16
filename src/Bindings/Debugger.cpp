#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_debug.h"

#include <msclr/marshal.h>

namespace Dotx64Dbg::Native
{
    public ref class Debugger
    {
    public:
        static void Wait()
        {
            Script::Debug::Wait();
        }

        static void Run()
        {
            //Script::Debug::Run();
            DbgCmdExec("run");
        }

        static void Pause()
        {
            Script::Debug::Pause();
        }

        static void Stop()
        {
            //Script::Debug::Stop();
            DbgCmdExec("stop");
        }

        static void StepIn()
        {
            //Script::Debug::StepIn();
            DbgCmdExec("sti");
        }

        static void StepOver()
        {
            //Script::Debug::StepOver();
            DbgCmdExec("sto");
        }

        static void StepOut()
        {
            //Script::Debug::StepOut();
            DbgCmdExec("rtr");
        }

        static bool IsActive()
        {
            return DbgIsDebugging();
        }

        static bool RunCommand(System::String^ cmd)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(cmd);

            return DbgCmdExecDirect(cstr);
        }

        static bool RunCommandAsync(System::String^ cmd)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(cmd);

            return DbgCmdExec(cstr);
        }
    };
}
