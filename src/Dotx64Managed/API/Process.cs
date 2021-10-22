using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    public static class Process
    {
        // <see cref="GetPID"/>
        public static UInt32 PID { get { return GetPID(); } }

        /// <summary>
        /// Process id of the current debugged process.
        /// </summary>
        public static UInt32 GetPID()
        {
            return Native.Process.GetPID();
        }

        // <see cref="GetNativeHandle"/>
        public static UIntPtr NativeHandle { get { return GetNativeHandle(); } }

        /// <summary>
        /// Native handle of the current debugged process.
        /// </summary>
        public static UIntPtr GetNativeHandle()
        {
            return Native.Process.GetNativeHandle();
        }

    }
}
