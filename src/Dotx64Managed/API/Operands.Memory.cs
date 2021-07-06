using System;

namespace Dotx64Dbg
{
    public static partial class Operands
    {
        // Byte
        //////////////////////////////////////////////////////////////////////////
        public static Operand.OpMem BytePtr(Register baseReg)
        {
            return new Operand.OpMem(8, baseReg, Register.None, 0, 0);
        }
        public static Operand.OpMem BytePtr(Operand.OpReg baseReg)
        {
            return new Operand.OpMem(8, baseReg.Value, Register.None, 0, 0);
        }

        public static Operand.OpMem BytePtr(Register baseReg, Int64 disp)
        {
            return new Operand.OpMem(8, baseReg, Register.None, 0, disp);
        }
        public static Operand.OpMem BytePtr(Operand.OpReg baseReg, Int64 disp)
        {
            return new Operand.OpMem(8, baseReg.Value, Register.None, 0, disp);
        }

        public static Operand.OpMem BytePtr(Register baseReg, Register index)
        {
            return new Operand.OpMem(8, baseReg, index, 0, 0);
        }
        public static Operand.OpMem BytePtr(Operand.OpReg baseReg, Operand.OpReg index)
        {
            return new Operand.OpMem(8, baseReg.Value, index.Value, 0, 0);
        }

        public static Operand.OpMem BytePtr(Register baseReg, Register index, Int64 disp)
        {
            return new Operand.OpMem(8, baseReg, index, 0, disp);
        }
        public static Operand.OpMem BytePtr(Operand.OpReg baseReg, Operand.OpReg index, Int64 disp)
        {
            return new Operand.OpMem(8, baseReg.Value, index.Value, 0, disp);
        }

        public static Operand.OpMem BytePtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(8, baseReg, index, scale, disp);
        }
        public static Operand.OpMem BytePtr(Operand.OpReg baseReg, Operand.OpReg index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(8, baseReg.Value, index.Value, scale, disp);
        }

        // Word
        //////////////////////////////////////////////////////////////////////////
        public static Operand.OpMem WordPtr(Register baseReg)
        {
            return new Operand.OpMem(16, baseReg, Register.None, 0, 0);
        }
        public static Operand.OpMem WordPtr(Operand.OpReg baseReg)
        {
            return new Operand.OpMem(16, baseReg.Value, Register.None, 0, 0);
        }

        public static Operand.OpMem WordPtr(Register baseReg, Int64 disp)
        {
            return new Operand.OpMem(16, baseReg, Register.None, 0, disp);
        }
        public static Operand.OpMem WordPtr(Operand.OpReg baseReg, Int64 disp)
        {
            return new Operand.OpMem(16, baseReg.Value, Register.None, 0, disp);
        }

        public static Operand.OpMem WordPtr(Register baseReg, Register index)
        {
            return new Operand.OpMem(16, baseReg, index, 0, 0);
        }
        public static Operand.OpMem WordPtr(Operand.OpReg baseReg, Operand.OpReg index)
        {
            return new Operand.OpMem(16, baseReg.Value, index.Value, 0, 0);
        }

        public static Operand.OpMem WordPtr(Register baseReg, Register index, Int64 disp)
        {
            return new Operand.OpMem(16, baseReg, index, 0, disp);
        }
        public static Operand.OpMem WordPtr(Operand.OpReg baseReg, Operand.OpReg index, Int64 disp)
        {
            return new Operand.OpMem(16, baseReg.Value, index.Value, 0, disp);
        }

        public static Operand.OpMem WordPtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(16, baseReg, index, scale, disp);
        }
        public static Operand.OpMem WordPtr(Operand.OpReg baseReg, Operand.OpReg index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(16, baseReg.Value, index.Value, scale, disp);
        }

        // Dword
        //////////////////////////////////////////////////////////////////////////
        public static Operand.OpMem DwordPtr(Register baseReg)
        {
            return new Operand.OpMem(32, baseReg, Register.None, 0, 0);
        }
        public static Operand.OpMem DwordPtr(Operand.OpReg baseReg)
        {
            return new Operand.OpMem(32, baseReg.Value, Register.None, 0, 0);
        }

        public static Operand.OpMem DwordPtr(Register baseReg, Int64 disp)
        {
            return new Operand.OpMem(32, baseReg, Register.None, 0, disp);
        }
        public static Operand.OpMem DwordPtr(Operand.OpReg baseReg, Int64 disp)
        {
            return new Operand.OpMem(32, baseReg.Value, Register.None, 0, disp);
        }

        public static Operand.OpMem DwordPtr(Register baseReg, Register index)
        {
            return new Operand.OpMem(32, baseReg, index, 0, 0);
        }
        public static Operand.OpMem DwordPtr(Operand.OpReg baseReg, Operand.OpReg index)
        {
            return new Operand.OpMem(32, baseReg.Value, index.Value, 0, 0);
        }

        public static Operand.OpMem DwordPtr(Register baseReg, Register index, Int64 disp)
        {
            return new Operand.OpMem(32, baseReg, index, 0, disp);
        }
        public static Operand.OpMem DwordPtr(Operand.OpReg baseReg, Operand.OpReg index, Int64 disp)
        {
            return new Operand.OpMem(32, baseReg.Value, index.Value, 0, disp);
        }

        public static Operand.OpMem DwordPtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(32, baseReg, index, scale, disp);
        }
        public static Operand.OpMem DwordPtr(Operand.OpReg baseReg, Operand.OpReg index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(32, baseReg.Value, index.Value, scale, disp);
        }

        // Qword
        //////////////////////////////////////////////////////////////////////////
        public static Operand.OpMem QwordPtr(Register baseReg)
        {
            return new Operand.OpMem(64, baseReg, Register.None, 0, 0);
        }
        public static Operand.OpMem QwordPtr(Operand.OpReg baseReg)
        {
            return new Operand.OpMem(64, baseReg.Value, Register.None, 0, 0);
        }


        public static Operand.OpMem QwordPtr(Register baseReg, Int64 disp)
        {
            return new Operand.OpMem(64, baseReg, Register.None, 0, disp);
        }
        public static Operand.OpMem QwordPtr(Operand.OpReg baseReg, Int64 disp)
        {
            return new Operand.OpMem(64, baseReg.Value, Register.None, 0, disp);
        }

        public static Operand.OpMem QwordPtr(Register baseReg, Register index)
        {
            return new Operand.OpMem(64, baseReg, index, 0, 0);
        }
        public static Operand.OpMem QwordPtr(Operand.OpReg baseReg, Operand.OpReg index)
        {
            return new Operand.OpMem(64, baseReg.Value, index.Value, 0, 0);
        }

        public static Operand.OpMem QwordPtr(Register baseReg, Register index, Int64 disp)
        {
            return new Operand.OpMem(64, baseReg, index, 0, disp);
        }
        public static Operand.OpMem QwordPtr(Operand.OpReg baseReg, Operand.OpReg index, Int64 disp)
        {
            return new Operand.OpMem(64, baseReg.Value, index.Value, 0, disp);
        }

        public static Operand.OpMem QwordPtr(Register baseReg, Register index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(64, baseReg, index, scale, disp);
        }
        public static Operand.OpMem QwordPtr(Operand.OpReg baseReg, Operand.OpReg index, Int32 scale, Int64 disp)
        {
            return new Operand.OpMem(64, baseReg.Value, index.Value, scale, disp);
        }
    }
}
