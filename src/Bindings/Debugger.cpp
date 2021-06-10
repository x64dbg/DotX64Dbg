#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_debug.h"

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
            Script::Debug::Run();
        }

        static void Pause()
        {
            Script::Debug::Pause();
        }

        static void Stop()
        {
            Script::Debug::Stop();
        }

        static void StepIn()
        {
            Script::Debug::StepIn();
        }

        static void StepOver()
        {
            Script::Debug::StepOver();
        }

        static void StepOut()
        {
            Script::Debug::StepOut();
        }

        static bool IsActive()
        {
            return DbgIsDebugging();
        }
    };
}
