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

        public RegisterMaskGp Add(Dotx64Dbg.Operand.Register reg)
        {
            return Add(reg.Value);
        }

        public RegisterMaskGp Add(RegisterId reg)
        {
            if (reg == RegisterId.None)
                return this;

            if (reg >= RegisterId.Al && reg <= RegisterId.R15b)
            {
                var index = (int)reg - (int)RegisterId.Al;
                if (reg >= RegisterId.Ah && reg <= RegisterId.Bh)
                {
                    index -= 4;
                }
                Mask |= (RegisterMaskType)(1u << index);
            }
            else if (reg >= RegisterId.Ax && reg <= RegisterId.R15w)
            {
                var index = (int)reg - (int)RegisterId.Ax;
                Mask |= (UInt16)(1u << index);
            }
            else if (reg >= RegisterId.Eax && reg <= RegisterId.R15d)
            {
                var index = (int)reg - (int)RegisterId.Eax;
                Mask |= (UInt16)(1u << index);
            }
            else if (reg >= RegisterId.Rax && reg <= RegisterId.R15)
            {
                var index = (int)reg - (int)RegisterId.Rax;
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
                return (int)System.Runtime.Intrinsics.X86.Popcnt.PopCount(Mask);
            }
        }

        public void GetRegisters(out Operand.Register[] res)
        {
            res = new Operand.Register[Count];

            var idx = 0;
            for (int i = 0; i < MaxRegisters; i++)
            {
                if ((Mask & (1u << i)) != 0)
                {
#if _X64_
                    var regId = RegisterId.Rax + i;
#else
                    var regId = RegisterId.Eax + i;
#endif
                    res[idx] = Operands.Reg(regId);
                    idx++;
                }
            }
        }

        public RegisterId[] GetRegisters()
        {
            var res = new RegisterId[Count];

            var idx = 0;
            for (int i = 0; i < 32; i++)
            {
                if ((Mask & (1u << i)) != 0)
                {
#if _X64_
                    var regId = RegisterId.Rax + i;
#else
                    var regId = RegisterId.Eax + i;
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
