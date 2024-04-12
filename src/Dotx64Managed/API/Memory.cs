using System;

namespace Dotx64Dbg
{
    public static partial class Memory
    {
        [Flags]
        public enum Protection
        {
            Invalid = 0,
            NoAccess = 0x01,
            ReadOnly = 0x02,
            ReadWrite = 0x04,
            WriteCopy = 0x08,
            Execute = 0x10,
            ExecuteRead = 0x20,
            ExecuteWriteRead = 0x40,
            ExecuteWriteCopy,
            // Extra flags.
            Guard = 0x100,
            NoCache = 0x200,
            WriteCombine = 0x400,
            // CFG Settings.
            PageTargetsInvalid = 0x40000000,
            PageTargetsNoUpdate = 0x40000000,
        }

        /// <summary>
        /// Attempt to read memory from the debugged process.
        /// </summary>
        /// <param name="addr">Virtual address in the debugged process space</param>
        /// <param name="length">Amount of bytes to read</param>
        /// <returns>The bytes read from the process</returns>
        public static byte[] Read(nuint addr, int length)
        {
            return Native.Memory.Read(addr, length);
        }

        /// <see cref="Read(nuint, int)"/>
        public static byte[] Read(nuint addr, nuint length)
        {
            return Native.Memory.Read(addr, (int)length);
        }

        /// <see cref="Read(nuint, int)"/>
        public static byte[] Read(ulong addr, int length)
        {
            return Native.Memory.Read((nuint)addr, length);
        }

        /// <summary>
        /// Attempt to read pointer sized value from the debugged process.
        /// </summary>
        /// <param name="addr">Virtual address in the debugged process space</param>
        /// <returns>Value as nuint</returns>
        public static nuint ReadPtr(ulong addr)
        {
#if _X64_
            var data = Read(addr, 8);
            var val = BitConverter.ToInt64(data, 0);
#else
            var data = Read(addr, 4);
            var val = BitConverter.ToInt32(data, 0);
#endif
            return (nuint)val;
        }

        /// <summary>
        /// Attempt to write memory to the debugged process.
        /// </summary>
        /// <param name="address">Virtual address in the debugged process space</param>
        /// <param name="data">The bytes to be written</param>
        /// <param name="length">The maximum amount of bytes to write, can not be bigger than `data`</param>
        /// <returns>The amount of bytes written</returns>
        public static int Write(nuint address, byte[] data, int length)
        {
            return Native.Memory.Write(address, data, length);
        }

        /// <see cref="Write(nuint, byte[], int)"/>
        public static int Write(nuint address, byte[] data, nuint length)
        {
            return Native.Memory.Write(address, data, (int)length);
        }

        /// <see cref="Write(nuint, byte[], int)"/>
        public static int Write(ulong address, byte[] data, int length)
        {
            return Native.Memory.Write((nuint)address, data, length);
        }

        /// <summary>
        /// Attempt to write value of pointer size to the debugged process.
        /// </summary>
        /// <param name="addr">Virtual address in the debugged process space</param>
        /// <param name="value">Value to write</param>
        /// <returns>true if successful, false on failure.</returns>
        public static bool WritePtr(ulong addr, nuint value)
        {
            var data = BitConverter.GetBytes(value);
            return Write(addr, data) == data.Length;
        }

        /// <summary>
        /// Attempt to write memory to the debugged process.
        /// </summary>
        /// <param name="address">Virtual address in the debugged process space</param>
        /// <param name="data">The bytes to be written</param>
        /// <returns>The amount of bytes written</returns>
        public static int Write(nuint address, byte[] data)
        {
            return Write(address, data, data.Length);
        }

        /// <see cref="Write(nuint, byte[])"/>
        public static int Write(ulong address, byte[] data)
        {
            return Write((nuint)address, data, data.Length);
        }

        /// <summary>
        /// Returns the size of the specified memory region, the address must be the base address of the region.
        /// </summary>
        /// <param name="address">Virtual address in the debugged process space</param>
        /// <returns>Size of memory region</returns>
        public static nuint GetSize(nuint address)
        {
            return (nuint)Native.Memory.GetSize(address);
        }

        /// <see cref="GetSize(nuint)"/> 
        public static nuint GetSize(ulong address)
        {
            return GetSize((nuint)address);
        }

        /// <summary>
        /// Returns the address of where the memory region starts.
        /// </summary>
        /// <param name="address">Virtual address in the debugged process space</param>
        /// <returns>Base address</returns>
        public static nuint GetBase(nuint address)
        {
            return Native.Memory.GetBase(address);
        }

        /// <see cref="GetBase(nuint)"/>
        public static nuint GetBase(ulong address)
        {
            return GetBase((nuint)address);
        }

        /// <summary>
        /// Gets the protection of the memory, if the cache is used this is the last queried page info.
        /// It is normally safe to use the cache for performance, when the cache is used the internal
        /// API will not use a syscall to determine the protection.
        /// </summary>
        /// <param name="address">Address of the page to query</param>
        /// <param name="useCache">If this is true it will use the last queried page information</param>
        /// <returns>In case of failure the result is Protection.Invalid otherwise actual protection</returns>
        public static Protection GetProtection(nuint address, bool useCache)
        {
            return (Protection)Native.Memory.GetProtection(address, useCache);
        }
        public static Protection GetProtection(ulong address, bool useCache)
        {
            return GetProtection((nuint)address, useCache);
        }

        /// <summary>
        /// Sets a new protection on the specified address, the address will be aligned to page
        /// boundaries and sets the entire page which is by 4 KiB. This may split up
        /// an existing range from the memory map.
        /// Internally the size will be always aligned to a minimum of a single page, if the size
        /// spans more than two pages then both pages will be modified.
        /// <note>This will also update the cached protection info</note>
        /// </summary>
        /// <param name="address">Address of the page</param>
        /// <param name="protect">New protection</param>
        /// <param name="size">The size of the range</param>
        /// <returns>True on success</returns>
        public static bool SetProtection(nuint address, Protection protect, int size)
        {
            return Native.Memory.SetProtection(address, (UInt32)protect, size);
        }
        public static bool SetProtection(ulong address, Protection protect, int size)
        {
            return SetProtection((nuint)address, protect, size);
        }

        public static nuint RemoteAlloc(nuint address, int size)
        {
            return Native.Memory.RemoteAlloc(address, size);
        }
        public static nuint RemoteAlloc(ulong address, int size)
        {
            return RemoteAlloc((nuint)address, size);
        }

        public static bool RemoteFree(nuint address)
        {
            return Native.Memory.RemoteFree(address);
        }

        public static bool RemoteFree(ulong address)
        {
            return RemoteFree((nuint)address);
        }
    };
}
