namespace Dotx64Dbg
{
    using BreakpointsNative = Native.Breakpoints;

    public static class Breakpoints
    {
        public enum Type
        {
            None = 0,
            Normal = (1 << 0),
            Hardware = (1 << 1),
            Memory = (1 << 2),
            Dll = (1 << 3),
            Exception = (1 << 4),
            System = (1 << 5),
        };

        public enum HardwareType
        {
            Access = BreakpointsNative.HardwareType.HardwareAccess,
            Write = BreakpointsNative.HardwareType.HardwareWrite,
            Execute = BreakpointsNative.HardwareType.HardwareExecute
        };

        public static bool SetBreakpoint(nuint address)
        {
            return BreakpointsNative.SetBreakpoint(address);
        }

        public static bool DeleteBreakpoint(nuint address)
        {
            return BreakpointsNative.DeleteBreakpoint(address);
        }

        public static bool DisableBreakpoint(nuint address)
        {
            return BreakpointsNative.DisableBreakpoint(address);
        }

        public static bool SetHardwareBreakpoint(nuint address, HardwareType type)
        {
            return BreakpointsNative.SetHardwareBreakpoint(address, (BreakpointsNative.HardwareType)type);
        }

        public static bool DeleteHardwareBreakpoint(nuint address)
        {
            return BreakpointsNative.DeleteHardwareBreakpoint(address);
        }
    }
}
