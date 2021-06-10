#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"

namespace Dotx64Dbg
{
    public ref class Memory
    {
    public:
        static array<System::Byte>^ Read(uint64_t addr, int length)
        {
            array<System::Byte>^ res = gcnew array<System::Byte>(length);

            pin_ptr<uint8_t> ptr = &res[0];
            uint8_t* buf = ptr;

            duint readSize = 0;
            if (!Script::Memory::Read(static_cast<duint>(addr), buf, length, &readSize))
            {
                array<System::Byte>::Resize(res, 0);
                return res;
            }

            array<System::Byte>::Resize(res, readSize);
            return res;
        }

        static int Write(uint64_t addr, array<System::Byte>^ data, int length)
        {
            int maxLength = data->Length < length ? data->Length : length;
            if (maxLength <= 0)
                return 0;

            pin_ptr<uint8_t> ptr = &data[0];
            const uint8_t* buf = ptr;

            duint bytesWritten = 0;
            if (!Script::Memory::Write(static_cast<duint>(addr), buf, maxLength, &bytesWritten))
            {
                return 0;
            }

            return bytesWritten;
        }
    };
}
