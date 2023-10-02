namespace Dotx64Dbg.Managed.Tests
{
    using static Operands;
    using static Testing;

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

        [Test]
        public void TestEncodeLeaBasic64()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Rax, QwordPtr(Rax));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(4, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x48, data[1]);
            AssertEq(0x8d, data[2]);
            AssertEq(0x00, data[3]);
        }

        [Test]
        public void TestEncodeLeaBasic32()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Eax, DwordPtr(Eax));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(4, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x67, data[1]);
            AssertEq(0x8D, data[2]);
            AssertEq(0x00, data[3]);
        }

        [Test]
        public void TestEncodeMemSegment64()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Mov(Rax, QwordPtr(0x60).WithSegment(Gs));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(9, data.Length);
            AssertEq(0x65, data[0]);
            AssertEq(0x48, data[1]);
            AssertEq(0x8B, data[2]);
            AssertEq(0x04, data[3]);
            AssertEq(0x25, data[4]);
            AssertEq(0x60, data[5]);
            AssertEq(0x00, data[6]);
            AssertEq(0x00, data[7]);
            AssertEq(0x00, data[8]);
        }

        [Test]
        public void TestEncodeLeaScale2()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Rax, DwordPtr(Rax, Rdx, 2, 0));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(5, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x48, data[1]);
            AssertEq(0x8D, data[2]);
            AssertEq(0x04, data[3]);
            AssertEq(0x50, data[4]);
        }


        [Test]
        public void TestEncodeLeaScale4()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Rax, DwordPtr(Rax, Rdx, 4, 0));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(5, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x48, data[1]);
            AssertEq(0x8D, data[2]);
            AssertEq(0x04, data[3]);
            AssertEq(0x90, data[4]);
        }


        [Test]
        public void TestEncodeLeaScale8()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Rax, DwordPtr(Rax, Rdx, 8, 0));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(5, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x48, data[1]);
            AssertEq(0x8D, data[2]);
            AssertEq(0x04, data[3]);
            AssertEq(0xD0, data[4]);
        }
#else
        [Test]
        public void TestEncodeLeaBasic32()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Eax, DwordPtr(Eax));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(3, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x8D, data[1]);
            AssertEq(0x00, data[2]);
        }

        [Test]
        public void TestEncodeMemSegment32()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Mov(Eax, DwordPtr(0x30).WithSegment(Fs));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(6, data.Length);
            AssertEq(0x64, data[0]);
            AssertEq(0xA1, data[1]);
            AssertEq(0x30, data[2]);
            AssertEq(0x00, data[3]);
            AssertEq(0x00, data[4]);
            AssertEq(0x00, data[5]);
        }

        [Test]
        public void TestEncodeLeaScale2()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Eax, DwordPtr(Eax, Edx, 2, 0));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(4, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x8D, data[1]);
            AssertEq(0x04, data[2]);
            AssertEq(0x50, data[3]);
        }


        [Test]
        public void TestEncodeLeaScale4()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Eax, DwordPtr(Eax, Edx, 4, 0));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(4, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x8D, data[1]);
            AssertEq(0x04, data[2]);
            AssertEq(0x90, data[3]);
        }


        [Test]
        public void TestEncodeLeaScale8()
        {
            var assembler = new Dotx64Dbg.Assembler();
            assembler.Lea(Eax, DwordPtr(Eax, Edx, 8, 0));
            assembler.Finalize();

            var data = assembler.GetData();
            AssertEq(4, data.Length);
            AssertEq(0x3E, data[0]);
            AssertEq(0x8D, data[1]);
            AssertEq(0x04, data[2]);
            AssertEq(0xD0, data[3]);
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
