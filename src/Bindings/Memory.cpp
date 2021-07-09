#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_memory.h"

namespace Dotx64Dbg::Native
{
    public ref class Memory
    {
    public:
        /// <summary>
        /// Attempt to read memory from the debugged process.
        /// </summary>
        /// <param name="addr">Virtual address in the debugged process space</param>
        /// <param name="length">Amount of bytes to read</param>
        /// <returns>The bytes read from the process</returns>
        static array<System::Byte>^ Read(uintptr_t addr, int length)
        {
            array<System::Byte>^ res = gcnew array<System::Byte>((int)length);

            pin_ptr<uint8_t> ptr = &res[0];
            uint8_t* buf = ptr;

            duint readSize = 0;
            if (!Script::Memory::Read(addr, buf, length, &readSize))
            {
                array<System::Byte>::Resize(res, 0);
                return res;
            }

            array<System::Byte>::Resize(res, (int)readSize);
            return res;
        }

        /// <summary>
        /// Attempt to write memory to the debugged process.
        /// </summary>
        /// <param name="addr">Virtual address in the debugged process space</param>
        /// <param name="data">The bytes to be written</param>
        /// <param name="length">The maximum amount of bytes to write, can not be bigger than `data`</param>
        /// <returns>The amount of bytes written</returns>
        static int Write(uintptr_t addr, array<System::Byte>^ data, int length)
        {
            duint maxLength = data->Length < length ? data->Length : length;
            if (maxLength <= 0)
                return 0;

            pin_ptr<uint8_t> ptr = &data[0];
            const uint8_t* buf = ptr;

            duint bytesWritten = 0;
            if (!Script::Memory::Write(addr, buf, maxLength, &bytesWritten))
            {
                return 0;
            }

            return (int)bytesWritten;
        }

        static uint32_t GetProtection(duint addr)
        {
            return 0;
        }

        static uint32_t SetProtection(duint addr, uint32_t prot)
        {
            return 0;
        }
    };
}
