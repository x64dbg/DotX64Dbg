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
            mask.Add(RegisterId.Ah);
            mask.Add(RegisterId.Al);
            mask.Add(RegisterId.Ecx);

            AssertEq(mask.Count, 2);

            var regs = mask.GetRegisters();
            AssertEq(regs.Length, 2);

#if _X64_
            AssertEq(regs[0], RegisterId.Rax);
            AssertEq(regs[1], RegisterId.Rcx);
#else
            AssertEq(regs[0], RegisterId.Eax);
            AssertEq(regs[1], RegisterId.Ecx);
#endif

            Operand.Register[] regs2;
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
            mask.Add(RegisterId.Ah);
            mask.Add(RegisterId.Al);
            mask.Add(RegisterId.R15);

            AssertEq(mask.Count, 2);

            var regs = mask.GetRegisters();
            AssertEq(regs.Length, 2);

#if _X64_
            AssertEq(regs[0], RegisterId.Rax);
            AssertEq(regs[1], RegisterId.R15);
#else
            AssertEq(regs[0], RegisterId.Eax);
            AssertEq(regs[1], RegisterId.R15d);
#endif

            Operand.Register[] regs2;
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
            RegisterId[] regs = new[] {
                RegisterId.Eax,
                RegisterId.Ebx,
                RegisterId.Ecx,
                RegisterId.Edx,
                RegisterId.Ebp,
                RegisterId.Esp,
                RegisterId.Edi,
                RegisterId.R8d,
                RegisterId.R9d,
                RegisterId.R10d,
                RegisterId.R11d,
                RegisterId.R12d,
                RegisterId.R13d,
                RegisterId.R14d,
                RegisterId.R15d
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
            List<RegisterId> regs = new()
            {
                RegisterId.Eax,
                RegisterId.Ebx,
                RegisterId.Ecx,
                RegisterId.Edx,
                RegisterId.Ebp,
                RegisterId.Esp,
                RegisterId.Edi,
                RegisterId.R8d,
                RegisterId.R9d,
                RegisterId.R10d,
                RegisterId.R11d,
                RegisterId.R12d,
                RegisterId.R13d,
                RegisterId.R14d,
                RegisterId.R15d
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
            List<RegisterId> regs = new()
            {
                RegisterId.Eax,
                RegisterId.Ebx,
                RegisterId.Ecx,
                RegisterId.Edx,
                RegisterId.Ebp,
                RegisterId.Esp,
                RegisterId.Edi,
                RegisterId.R8d,
                RegisterId.R9d,
                RegisterId.R10d,
                RegisterId.R11d,
                RegisterId.R12d,
                RegisterId.R13d,
                RegisterId.R14d,
                RegisterId.R15d
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
