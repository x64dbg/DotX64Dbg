using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg.Managed.Tests
{
    using static Testing;
    using static Operands;

    class TestAssembler
    {
#if _X64_
        [Test]
        public void TestEncodeXorRaxRax()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Xor(Rax, Rax);
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(3, data.Length);
            AssertEq(0x48, data[0]);
            AssertEq(0x31, data[1]);
            AssertEq(0xC0, data[2]);
        }
#endif

        [Test]
        public void TestEncodeXorEaxEax()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Xor(Eax, Eax);
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(2, data.Length);
            AssertEq(0x31, data[0]);
            AssertEq(0xC0, data[1]);
        }
    }
}
