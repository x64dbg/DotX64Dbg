#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"

namespace Dotx64Dbg::Native
{
    public ref class Thread
    {
    public:
        static uint32_t GetActiveThreadId()
        {
            return DbgGetThreadId();
        }

        static bool SetActiveThreadId(uint32_t threadId)
        {
            char cmd[128] = {};
            sprintf_s(cmd, "switchthread %X", (uint32_t)threadId);

            return DbgCmdExecDirect(cmd);
        }

        static uint32_t GetMainThreadId()
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            uint32_t id = 0;
            for (int i = 0; i < tl.count; i++)
            {
                const auto& th = tl.list[i];
                if (th.BasicInfo.ThreadNumber == 0)
                {
                    id = th.BasicInfo.ThreadId;
                    break;
                }
            }

            BridgeFree(tl.list);
            return id;
        }

        static bool IsValid(uint32_t threadId)
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            bool valid = false;
            for (int i = 0; i < tl.count; i++)
            {
                if (threadId == tl.list[i].BasicInfo.ThreadId)
                {
                    valid = true;
                    break;
                }
            }

            BridgeFree(tl.list);

            return valid;
        }

        static array<System::UInt32>^ GetThreads()
        {
            THREADLIST tl{};
            DbgGetThreadList(&tl);

            array<System::UInt32>^ res = gcnew array<System::UInt32>(tl.count);
            for (int i = 0; i < tl.count; i++)
            {
                res[i] = tl.list[i].BasicInfo.ThreadId;
            }

            BridgeFree(tl.list);

            return res;
        }
    };
}
