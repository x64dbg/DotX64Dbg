using System;

namespace Dotx64Dbg.Analysis
{
    using RegisterMaskType = UInt32;

    public struct RegisterMaskGp
    {
        private RegisterMaskType Mask;

        public const uint MaxRegisters = sizeof(RegisterMaskType) * 8u;

        public static readonly RegisterMaskGp None = new RegisterMaskGp();
        public static readonly RegisterMaskGp All = new RegisterMaskGp { Mask = ~0u };

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
                Mask |= (RegisterMaskType)(1u << index);
            }
            else if (reg >= Register.Ax && reg <= Register.R15w)
            {
                var index = (int)reg - (int)Register.Ax;
                Mask |= (RegisterMaskType)(1u << index);
            }
            else if (reg >= Register.Eax && reg <= Register.R15d)
            {
                var index = (int)reg - (int)Register.Eax;
                Mask |= (RegisterMaskType)(1u << index);
            }
            else if (reg >= Register.Rax && reg <= Register.R15)
            {
                var index = (int)reg - (int)Register.Rax;
                Mask |= (RegisterMaskType)(1u << index);
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
                return (int)System.Runtime.Intrinsics.X86.Popcnt.PopCount(Mask);
            }
        }

        public void GetRegisters(out Operand.OpReg[] res)
        {
            res = new Operand.OpReg[Count];

            var idx = 0;
            for (int i = 0; i < MaxRegisters; i++)
            {
                if ((Mask & (1u << i)) != 0)
                {
#if _X64_
                    var regId = Register.Rax + i;
#else
                    var regId = Register.Eax + i;
#endif
                    res[idx] = Operands.Reg(regId);
                    idx++;
                }
            }
        }
        public Register[] GetRegisters()
        {
            var res = new Register[Count];
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
            return res;
        }

        public RegisterMaskType Value()
        {
            return Mask;
        }

        public static RegisterMaskGp operator &(RegisterMaskGp left, RegisterMaskGp right)
        {
            return new() { Mask = (RegisterMaskType)(left.Mask & right.Mask) };
        }

        public static RegisterMaskGp operator |(RegisterMaskGp left, RegisterMaskGp right)
        {
            return new() { Mask = (RegisterMaskType)(left.Mask | right.Mask) };
        }

        public static RegisterMaskGp operator ^(RegisterMaskGp left, RegisterMaskGp right)
        {
            return new() { Mask = (RegisterMaskType)(left.Mask ^ right.Mask) };
        }

        public static RegisterMaskGp operator ~(RegisterMaskGp left)
        {
            return new() { Mask = (RegisterMaskType)~left.Mask };
        }
    }
}
