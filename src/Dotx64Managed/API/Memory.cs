using System;

namespace Dotx64Dbg
{
    public class Memory
    {
        [Flags]
        public enum Protection
        {
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

        public static byte[] Read(ulong addr, int length)
        {
            return Native.Memory.Read((nuint)addr, length);
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

        public static int Write(ulong address, byte[] data, int length)
        {
            return Native.Memory.Write((nuint)address, data, length);
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

        public static int Write(ulong address, byte[] data)
        {
            return Write((nuint)address, data, data.Length);
        }
    };
}
