namespace Dotx64Dbg
{
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
            HardwareAccess,
            HardwareWrite,
            HardwareExecute
        };
    }
}
