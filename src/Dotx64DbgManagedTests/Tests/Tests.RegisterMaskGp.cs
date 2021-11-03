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

        [Test]
        public void TestMaskCountForward()
        {
            Register[] regs = new[] {
                Register.Eax,
                Register.Ebx,
                Register.Ecx,
                Register.Edx,
                Register.Ebp,
                Register.Esp,
                Register.Edi,
                Register.R8d,
                Register.R9d,
                Register.R10d,
                Register.R11d,
                Register.R12d,
                Register.R13d,
                Register.R14d,
                Register.R15d
            };

            var mask = Analysis.RegisterMaskGp.None;
            var i = 0;
            foreach (var reg in regs)
            {
                mask.Add(reg);

                i++;
                AssertEq(mask.Count, i);
            }

        }

        [Test]
        public void TestMaskCountReverse()
        {
            List<Register> regs = new()
            {
                Register.Eax,
                Register.Ebx,
                Register.Ecx,
                Register.Edx,
                Register.Ebp,
                Register.Esp,
                Register.Edi,
                Register.R8d,
                Register.R9d,
                Register.R10d,
                Register.R11d,
                Register.R12d,
                Register.R13d,
                Register.R14d,
                Register.R15d
            };

            var mask = Analysis.RegisterMaskGp.None;
            var i = 0;

            regs.Reverse();
            foreach (var reg in regs)
            {
                mask.Add(reg);

                i++;
                AssertEq(mask.Count, i);
            }

        }

        [Test]
        public void TestMaskCountRandom()
        {
            List<Register> regs = new()
            {
                Register.Eax,
                Register.Ebx,
                Register.Ecx,
                Register.Edx,
                Register.Ebp,
                Register.Esp,
                Register.Edi,
                Register.R8d,
                Register.R9d,
                Register.R10d,
                Register.R11d,
                Register.R12d,
                Register.R13d,
                Register.R14d,
                Register.R15d
            };

            for (int seed = 0; seed < 100; seed++)
            {
                var mask = Analysis.RegisterMaskGp.None;
                var i = 0;
                var prng = new System.Random(seed);

                while (regs.Count > 0)
                {
                    var idx = prng.Next(0, regs.Count - 1);
                    var reg = regs[idx];
                    regs.RemoveAt(idx);

                    mask.Add(reg);

                    i++;
                    AssertEq(mask.Count, i);
                }
            }

        }


    }
}
