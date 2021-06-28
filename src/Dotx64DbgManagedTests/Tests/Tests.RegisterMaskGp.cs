using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg.Managed.Tests
{
    using static Testing;

    class TestRegisterMaskGp
    {
        public TestRegisterMaskGp()
        {
            // Warm-up
            _ = Analysis.RegisterMaskGp.None;
            _ = Register.Al;
            _ = Operand.Reg(Register.Al);
        }

        [Test]
        public void TestMask()
        {
            var mask = Analysis.RegisterMaskGp.None;
            mask.Add(Register.Ah);
            mask.Add(Register.Al);
            mask.Add(Register.Ecx);

            AssertEq(mask.Count, 2);

            Register[] regs;
            mask.GetRegisters(out regs);

#if _X64_
            AssertEq(regs[0], Register.Rax);
            AssertEq(regs[1], Register.Rcx);
#else
            AssertEq(regs[0], Register.Eax);
            AssertEq(regs[1], Register.Ecx);
#endif

            Operand.OpReg[] regs2;
            mask.GetRegisters(out regs2);

            AssertEq(regs2.Length, 2);

            for (int i = 0; i < regs2.Length; i++)
            {
                AssertEq(regs2[i].Value, regs[i]);
            }
        }

        [Test]
        public void TestMask2()
        {
            var mask = Analysis.RegisterMaskGp.None;
            mask.Add(Register.Ah);
            mask.Add(Register.Al);
            mask.Add(Register.R15);

            AssertEq(mask.Count, 2);

            Register[] regs;
            mask.GetRegisters(out regs);

#if _X64_
            AssertEq(regs[0], Register.Rax);
            AssertEq(regs[1], Register.R15);
#else
            AssertEq(regs[0], Register.Eax);
            AssertEq(regs[1], Register.R15d);
#endif

            Operand.OpReg[] regs2;
            mask.GetRegisters(out regs2);

            AssertEq(regs2.Length, 2);

            for (int i = 0; i < regs2.Length; i++)
            {
                AssertEq(regs2[i].Value, regs[i]);
            }
        }
    }
}
