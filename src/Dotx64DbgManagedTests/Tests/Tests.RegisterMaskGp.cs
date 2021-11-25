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
            mask.Add(Registers.Id.Ah);
            mask.Add(Registers.Id.Al);
            mask.Add(Registers.Id.Ecx);

            AssertEq(mask.Count, 2);

            var regs = mask.GetRegisters();
            AssertEq(regs.Length, 2);

#if _X64_
            AssertEq(regs[0], Registers.Id.Rax);
            AssertEq(regs[1], Registers.Id.Rcx);
#else
            AssertEq(regs[0], Registers.Id.Eax);
            AssertEq(regs[1], Registers.Id.Ecx);
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
            mask.Add(Registers.Id.Ah);
            mask.Add(Registers.Id.Al);
            mask.Add(Registers.Id.R15);

            AssertEq(mask.Count, 2);

            var regs = mask.GetRegisters();
            AssertEq(regs.Length, 2);

#if _X64_
            AssertEq(regs[0], Registers.Id.Rax);
            AssertEq(regs[1], Registers.Id.R15);
#else
            AssertEq(regs[0], Registers.Id.Eax);
            AssertEq(regs[1], Registers.Id.R15d);
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
            Registers.Id[] regs = new[] {
                Registers.Id.Eax,
                Registers.Id.Ebx,
                Registers.Id.Ecx,
                Registers.Id.Edx,
                Registers.Id.Ebp,
                Registers.Id.Esp,
                Registers.Id.Edi,
                Registers.Id.R8d,
                Registers.Id.R9d,
                Registers.Id.R10d,
                Registers.Id.R11d,
                Registers.Id.R12d,
                Registers.Id.R13d,
                Registers.Id.R14d,
                Registers.Id.R15d
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
            List<Registers.Id> regs = new()
            {
                Registers.Id.Eax,
                Registers.Id.Ebx,
                Registers.Id.Ecx,
                Registers.Id.Edx,
                Registers.Id.Ebp,
                Registers.Id.Esp,
                Registers.Id.Edi,
                Registers.Id.R8d,
                Registers.Id.R9d,
                Registers.Id.R10d,
                Registers.Id.R11d,
                Registers.Id.R12d,
                Registers.Id.R13d,
                Registers.Id.R14d,
                Registers.Id.R15d
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
            List<Registers.Id> regs = new()
            {
                Registers.Id.Eax,
                Registers.Id.Ebx,
                Registers.Id.Ecx,
                Registers.Id.Edx,
                Registers.Id.Ebp,
                Registers.Id.Esp,
                Registers.Id.Edi,
                Registers.Id.R8d,
                Registers.Id.R9d,
                Registers.Id.R10d,
                Registers.Id.R11d,
                Registers.Id.R12d,
                Registers.Id.R13d,
                Registers.Id.R14d,
                Registers.Id.R15d
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
