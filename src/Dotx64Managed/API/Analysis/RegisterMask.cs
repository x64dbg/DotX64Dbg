using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg.Analysis
{
    public struct RegisterMaskGp
    {
        private UInt16 Mask;

        public static readonly RegisterMaskGp None = new RegisterMaskGp();
        public static readonly RegisterMaskGp All = new RegisterMaskGp { Mask = 0b1111111111111111 };

        public RegisterMaskGp Add(Dotx64Dbg.Operand.OpReg reg)
        {
            return Add(reg.Value);
        }

        public RegisterMaskGp Add(Register reg)
        {
            if (reg == Register.None)
                return this;

            if (reg >= Register.Al && reg <= Register.R15b)
            {
                var index = (int)reg - (int)Register.Al;
                if (reg >= Register.Ah && reg <= Register.Bh)
                {
                    index -= 4;
                }
                Mask |= (UInt16)(1u << index);
            }
            else if (reg >= Register.Ax && reg <= Register.R15w)
            {
                var index = (int)reg - (int)Register.Ax;
                Mask |= (UInt16)(1u << index);
            }
            else if (reg >= Register.Eax && reg <= Register.R15d)
            {
                var index = (int)reg - (int)Register.Eax;
                Mask |= (UInt16)(1u << index);
            }
            else if (reg >= Register.Rax && reg <= Register.R15)
            {
                var index = (int)reg - (int)Register.Rax;
                Mask |= (UInt16)(1u << index);
            }
            else
            {
                throw new InvalidOperationException("Invalid register type");
            }
            return this;
        }

        public int Count
        {
            get
            {
                var res = 0;
                var val = Mask;
                var maxCount = 0;
                if ((Mask & 0x000000FFu) != 0)
                    maxCount = 8;
                if ((Mask & 0x0000FF00u) != 0)
                    maxCount = 16;
                if ((Mask & 0x00FF0000u) != 0)
                    maxCount = 24;
                if ((Mask & 0xFF000000u) != 0)
                    maxCount = 32;
                for (int i = 0; i < maxCount; i++)
                {
                    if ((val & 1u) != 0)
                        res++;
                    val >>= 1;
                }
                return res;
            }
        }

        public void GetRegisters(out Operand.OpReg[] res)
        {
            res = new Operand.OpReg[Count];

            var idx = 0;
            for (int i = 0; i < 32; i++)
            {
                if ((Mask & (1u << i)) != 0)
                {
#if _X64_
                    var regId = Register.Rax + i;
#else
                    var regId = Register.Eax + i;
#endif
                    res[idx] = Operand.Reg(regId);
                    idx++;
                }
            }
        }
        public void GetRegisters(out Register[] res)
        {
            res = new Register[Count];

            var idx = 0;
            for (int i = 0; i < 32; i++)
            {
                if ((Mask & (1u << i)) != 0)
                {
#if _X64_
                    var regId = Register.Rax + i;
#else
                    var regId = Register.Eax + i;
#endif
                    res[idx] = regId;
                    idx++;
                }
            }
        }

        public static RegisterMaskGp operator &(RegisterMaskGp left, RegisterMaskGp right)
        {
            return new() { Mask = (UInt16)(left.Mask & right.Mask) };
        }

        public static RegisterMaskGp operator |(RegisterMaskGp left, RegisterMaskGp right)
        {
            return new() { Mask = (UInt16)(left.Mask | right.Mask) };
        }

        public static RegisterMaskGp operator ^(RegisterMaskGp left, RegisterMaskGp right)
        {
            return new() { Mask = (UInt16)(left.Mask ^ right.Mask) };
        }

        public static RegisterMaskGp operator ~(RegisterMaskGp left)
        {
            return new() { Mask = (UInt16)~left.Mask };
        }
    }
}
