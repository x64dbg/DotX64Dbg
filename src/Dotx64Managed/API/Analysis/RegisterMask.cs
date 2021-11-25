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

        public RegisterMaskGp Add(Registers.Id reg)
        {
            var index = Registers.GetIndex(reg);
            if (index == -1)
                throw new InvalidOperationException("Invalid register type");

            Mask |= (UInt16)(1u << index);

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
                    var regId = Registers.Id.Rax + i;
#else
                    var regId = Registers.Id.Eax + i;
#endif
                    res[idx] = Operands.Reg(regId);
                    idx++;
                }
            }
        }

        public Registers.Id[] GetRegisters()
        {
            var res = new Registers.Id[Count];

            var idx = 0;
            for (int i = 0; i < 32; i++)
            {
                if ((Mask & (1u << i)) != 0)
                {
#if _X64_
                    var regId = Registers.Id.Rax + i;
#else
                    var regId = Registers.Id.Eax + i;
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
