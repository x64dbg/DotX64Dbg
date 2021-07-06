using System;

namespace Dotx64Dbg
{
    public static partial class Operands
    {
        public static Operand.OpImm Imm(Int64 val)
        {
            return new Operand.OpImm(val);
        }
    }
}
