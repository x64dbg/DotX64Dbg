namespace Dotx64Dbg.Managed.Tests
{
    using static Testing;

    class TestRegisters
    {
        [Test]
        public void TestRoot()
        {
            AssertEq(Operands.Reg(Registers.Id.None).RootId, Registers.Id.None);
#if _X64_
            AssertEq(Operands.Al.RootId, Registers.Id.Rax);
            AssertEq(Operands.Cl.RootId, Registers.Id.Rcx);
            AssertEq(Operands.Dl.RootId, Registers.Id.Rdx);
            AssertEq(Operands.Bl.RootId, Registers.Id.Rbx);
            AssertEq(Operands.Ah.RootId, Registers.Id.Rax);
            AssertEq(Operands.Ch.RootId, Registers.Id.Rcx);
            AssertEq(Operands.Dh.RootId, Registers.Id.Rdx);
            AssertEq(Operands.Bh.RootId, Registers.Id.Rbx);
            AssertEq(Operands.Spl.RootId, Registers.Id.Rsp);
            AssertEq(Operands.Bpl.RootId, Registers.Id.Rbp);
            AssertEq(Operands.Sil.RootId, Registers.Id.Rsi);
            AssertEq(Operands.Dil.RootId, Registers.Id.Rdi);
            AssertEq(Operands.R8b.RootId, Registers.Id.R8);
            AssertEq(Operands.R9b.RootId, Registers.Id.R9);
            AssertEq(Operands.R10b.RootId, Registers.Id.R10);
            AssertEq(Operands.R11b.RootId, Registers.Id.R11);
            AssertEq(Operands.R12b.RootId, Registers.Id.R12);
            AssertEq(Operands.R13b.RootId, Registers.Id.R13);
            AssertEq(Operands.R14b.RootId, Registers.Id.R14);
            AssertEq(Operands.R15b.RootId, Registers.Id.R15);
            AssertEq(Operands.Ax.RootId, Registers.Id.Rax);
            AssertEq(Operands.Cx.RootId, Registers.Id.Rcx);
            AssertEq(Operands.Dx.RootId, Registers.Id.Rdx);
            AssertEq(Operands.Bx.RootId, Registers.Id.Rbx);
            AssertEq(Operands.Sp.RootId, Registers.Id.Rsp);
            AssertEq(Operands.Bp.RootId, Registers.Id.Rbp);
            AssertEq(Operands.Si.RootId, Registers.Id.Rsi);
            AssertEq(Operands.Di.RootId, Registers.Id.Rdi);
            AssertEq(Operands.R8w.RootId, Registers.Id.R8);
            AssertEq(Operands.R9w.RootId, Registers.Id.R9);
            AssertEq(Operands.R10w.RootId, Registers.Id.R10);
            AssertEq(Operands.R11w.RootId, Registers.Id.R11);
            AssertEq(Operands.R12w.RootId, Registers.Id.R12);
            AssertEq(Operands.R13w.RootId, Registers.Id.R13);
            AssertEq(Operands.R14w.RootId, Registers.Id.R14);
            AssertEq(Operands.R15w.RootId, Registers.Id.R15);
            AssertEq(Operands.Eax.RootId, Registers.Id.Rax);
            AssertEq(Operands.Ecx.RootId, Registers.Id.Rcx);
            AssertEq(Operands.Edx.RootId, Registers.Id.Rdx);
            AssertEq(Operands.Ebx.RootId, Registers.Id.Rbx);
            AssertEq(Operands.Esp.RootId, Registers.Id.Rsp);
            AssertEq(Operands.Ebp.RootId, Registers.Id.Rbp);
            AssertEq(Operands.Esi.RootId, Registers.Id.Rsi);
            AssertEq(Operands.Edi.RootId, Registers.Id.Rdi);
            AssertEq(Operands.R8d.RootId, Registers.Id.R8);
            AssertEq(Operands.R9d.RootId, Registers.Id.R9);
            AssertEq(Operands.R10d.RootId, Registers.Id.R10);
            AssertEq(Operands.R11d.RootId, Registers.Id.R11);
            AssertEq(Operands.R12d.RootId, Registers.Id.R12);
            AssertEq(Operands.R13d.RootId, Registers.Id.R13);
            AssertEq(Operands.R14d.RootId, Registers.Id.R14);
            AssertEq(Operands.R15d.RootId, Registers.Id.R15);
            AssertEq(Operands.Rax.RootId, Registers.Id.None);
            AssertEq(Operands.Rcx.RootId, Registers.Id.None);
            AssertEq(Operands.Rdx.RootId, Registers.Id.None);
            AssertEq(Operands.Rbx.RootId, Registers.Id.None);
            AssertEq(Operands.Rsp.RootId, Registers.Id.None);
            AssertEq(Operands.Rbp.RootId, Registers.Id.None);
            AssertEq(Operands.Rsi.RootId, Registers.Id.None);
            AssertEq(Operands.Rdi.RootId, Registers.Id.None);
            AssertEq(Operands.R8.RootId, Registers.Id.None);
            AssertEq(Operands.R9.RootId, Registers.Id.None);
            AssertEq(Operands.R10.RootId, Registers.Id.None);
            AssertEq(Operands.R11.RootId, Registers.Id.None);
            AssertEq(Operands.R12.RootId, Registers.Id.None);
            AssertEq(Operands.R13.RootId, Registers.Id.None);
            AssertEq(Operands.R14.RootId, Registers.Id.None);
            AssertEq(Operands.R15.RootId, Registers.Id.None);
#else
            AssertEq(Operands.Al.RootId, Registers.Id.Eax);
            AssertEq(Operands.Cl.RootId, Registers.Id.Ecx);
            AssertEq(Operands.Dl.RootId, Registers.Id.Edx);
            AssertEq(Operands.Bl.RootId, Registers.Id.Ebx);
            AssertEq(Operands.Ah.RootId, Registers.Id.Eax);
            AssertEq(Operands.Ch.RootId, Registers.Id.Ecx);
            AssertEq(Operands.Dh.RootId, Registers.Id.Edx);
            AssertEq(Operands.Bh.RootId, Registers.Id.Ebx);
            AssertEq(Operands.Spl.RootId, Registers.Id.Esp);
            AssertEq(Operands.Bpl.RootId, Registers.Id.Ebp);
            AssertEq(Operands.Sil.RootId, Registers.Id.Esi);
            AssertEq(Operands.Dil.RootId, Registers.Id.Edi);
            AssertEq(Operands.Ax.RootId, Registers.Id.Eax);
            AssertEq(Operands.Cx.RootId, Registers.Id.Ecx);
            AssertEq(Operands.Dx.RootId, Registers.Id.Edx);
            AssertEq(Operands.Bx.RootId, Registers.Id.Ebx);
            AssertEq(Operands.Sp.RootId, Registers.Id.Esp);
            AssertEq(Operands.Bp.RootId, Registers.Id.Ebp);
            AssertEq(Operands.Si.RootId, Registers.Id.Esi);
            AssertEq(Operands.Di.RootId, Registers.Id.Edi);
            AssertEq(Operands.Eax.RootId, Registers.Id.None);
            AssertEq(Operands.Ecx.RootId, Registers.Id.None);
            AssertEq(Operands.Edx.RootId, Registers.Id.None);
            AssertEq(Operands.Ebx.RootId, Registers.Id.None);
            AssertEq(Operands.Esp.RootId, Registers.Id.None);
            AssertEq(Operands.Ebp.RootId, Registers.Id.None);
            AssertEq(Operands.Esi.RootId, Registers.Id.None);
            AssertEq(Operands.Edi.RootId, Registers.Id.None);
            AssertEq(Operands.R8d.RootId, Registers.Id.None);
            AssertEq(Operands.R9d.RootId, Registers.Id.None);
            AssertEq(Operands.R10d.RootId, Registers.Id.None);
            AssertEq(Operands.R11d.RootId, Registers.Id.None);
            AssertEq(Operands.R12d.RootId, Registers.Id.None);
            AssertEq(Operands.R13d.RootId, Registers.Id.None);
            AssertEq(Operands.R14d.RootId, Registers.Id.None);
            AssertEq(Operands.R15d.RootId, Registers.Id.None);
#endif
        }

        [Test]
        public void TestParent()
        {
            AssertEq(Operands.Al.ParentId, Registers.Id.Ax);
            AssertEq(Operands.Cl.ParentId, Registers.Id.Cx);
            AssertEq(Operands.Dl.ParentId, Registers.Id.Dx);
            AssertEq(Operands.Bl.ParentId, Registers.Id.Bx);
            AssertEq(Operands.Ah.ParentId, Registers.Id.Ax);
            AssertEq(Operands.Ch.ParentId, Registers.Id.Cx);
            AssertEq(Operands.Dh.ParentId, Registers.Id.Dx);
            AssertEq(Operands.Bh.ParentId, Registers.Id.Bx);
            AssertEq(Operands.Spl.ParentId, Registers.Id.Sp);
            AssertEq(Operands.Bpl.ParentId, Registers.Id.Bp);
            AssertEq(Operands.Sil.ParentId, Registers.Id.Si);
            AssertEq(Operands.Dil.ParentId, Registers.Id.Di);
#if _X64_
            AssertEq(Operands.R8b.ParentId, Registers.Id.R8w);
            AssertEq(Operands.R9b.ParentId, Registers.Id.R9w);
            AssertEq(Operands.R10b.ParentId, Registers.Id.R10w);
            AssertEq(Operands.R11b.ParentId, Registers.Id.R11w);
            AssertEq(Operands.R12b.ParentId, Registers.Id.R12w);
            AssertEq(Operands.R13b.ParentId, Registers.Id.R13w);
            AssertEq(Operands.R14b.ParentId, Registers.Id.R14w);
            AssertEq(Operands.R15b.ParentId, Registers.Id.R15w);
#endif
            AssertEq(Operands.Ax.ParentId, Registers.Id.Eax);
            AssertEq(Operands.Cx.ParentId, Registers.Id.Ecx);
            AssertEq(Operands.Dx.ParentId, Registers.Id.Edx);
            AssertEq(Operands.Bx.ParentId, Registers.Id.Ebx);
            AssertEq(Operands.Sp.ParentId, Registers.Id.Esp);
            AssertEq(Operands.Bp.ParentId, Registers.Id.Ebp);
            AssertEq(Operands.Si.ParentId, Registers.Id.Esi);
            AssertEq(Operands.Di.ParentId, Registers.Id.Edi);
#if _X64_
            AssertEq(Operands.R8w.ParentId, Registers.Id.R8d);
            AssertEq(Operands.R9w.ParentId, Registers.Id.R9d);
            AssertEq(Operands.R10w.ParentId, Registers.Id.R10d);
            AssertEq(Operands.R11w.ParentId, Registers.Id.R11d);
            AssertEq(Operands.R12w.ParentId, Registers.Id.R12d);
            AssertEq(Operands.R13w.ParentId, Registers.Id.R13d);
            AssertEq(Operands.R14w.ParentId, Registers.Id.R14d);
            AssertEq(Operands.R15w.ParentId, Registers.Id.R15d);
#endif

#if _X64_
            AssertEq(Operands.Eax.ParentId, Registers.Id.Rax);
            AssertEq(Operands.Ecx.ParentId, Registers.Id.Rcx);
            AssertEq(Operands.Edx.ParentId, Registers.Id.Rdx);
            AssertEq(Operands.Ebx.ParentId, Registers.Id.Rbx);
            AssertEq(Operands.Esp.ParentId, Registers.Id.Rsp);
            AssertEq(Operands.Ebp.ParentId, Registers.Id.Rbp);
            AssertEq(Operands.Esi.ParentId, Registers.Id.Rsi);
            AssertEq(Operands.Edi.ParentId, Registers.Id.Rdi);
#else
            AssertEq(Operands.Eax.ParentId, Registers.Id.None);
            AssertEq(Operands.Ecx.ParentId, Registers.Id.None);
            AssertEq(Operands.Edx.ParentId, Registers.Id.None);
            AssertEq(Operands.Ebx.ParentId, Registers.Id.None);
            AssertEq(Operands.Esp.ParentId, Registers.Id.None);
            AssertEq(Operands.Ebp.ParentId, Registers.Id.None);
            AssertEq(Operands.Esi.ParentId, Registers.Id.None);
            AssertEq(Operands.Edi.ParentId, Registers.Id.None);
#endif
#if _X64_
            AssertEq(Operands.R8d.ParentId, Registers.Id.R8);
            AssertEq(Operands.R9d.ParentId, Registers.Id.R9);
            AssertEq(Operands.R10d.ParentId, Registers.Id.R10);
            AssertEq(Operands.R11d.ParentId, Registers.Id.R11);
            AssertEq(Operands.R12d.ParentId, Registers.Id.R12);
            AssertEq(Operands.R13d.ParentId, Registers.Id.R13);
            AssertEq(Operands.R14d.ParentId, Registers.Id.R14);
            AssertEq(Operands.R15d.ParentId, Registers.Id.R15);
            AssertEq(Operands.Rax.ParentId, Registers.Id.None);
            AssertEq(Operands.Rcx.ParentId, Registers.Id.None);
            AssertEq(Operands.Rdx.ParentId, Registers.Id.None);
            AssertEq(Operands.Rbx.ParentId, Registers.Id.None);
            AssertEq(Operands.Rsp.ParentId, Registers.Id.None);
            AssertEq(Operands.Rbp.ParentId, Registers.Id.None);
            AssertEq(Operands.Rsi.ParentId, Registers.Id.None);
            AssertEq(Operands.Rdi.ParentId, Registers.Id.None);
            AssertEq(Operands.R8.ParentId, Registers.Id.None);
            AssertEq(Operands.R9.ParentId, Registers.Id.None);
            AssertEq(Operands.R10.ParentId, Registers.Id.None);
            AssertEq(Operands.R11.ParentId, Registers.Id.None);
            AssertEq(Operands.R12.ParentId, Registers.Id.None);
            AssertEq(Operands.R13.ParentId, Registers.Id.None);
            AssertEq(Operands.R14.ParentId, Registers.Id.None);
            AssertEq(Operands.R15.ParentId, Registers.Id.None);
#endif
        }

        [Test]
        public void TestMutating()
        {
            AssertEq(Operands.Al.MutatesParent, false);
            AssertEq(Operands.Cl.MutatesParent, false);
            AssertEq(Operands.Dl.MutatesParent, false);
            AssertEq(Operands.Bl.MutatesParent, false);
            AssertEq(Operands.Ah.MutatesParent, false);
            AssertEq(Operands.Ch.MutatesParent, false);
            AssertEq(Operands.Dh.MutatesParent, false);
            AssertEq(Operands.Bh.MutatesParent, false);
            AssertEq(Operands.Spl.MutatesParent, false);
            AssertEq(Operands.Bpl.MutatesParent, false);
            AssertEq(Operands.Sil.MutatesParent, false);
            AssertEq(Operands.Dil.MutatesParent, false);
#if _X64_
            AssertEq(Operands.R8b.MutatesParent, false);
            AssertEq(Operands.R9b.MutatesParent, false);
            AssertEq(Operands.R10b.MutatesParent, false);
            AssertEq(Operands.R11b.MutatesParent, false);
            AssertEq(Operands.R12b.MutatesParent, false);
            AssertEq(Operands.R13b.MutatesParent, false);
            AssertEq(Operands.R14b.MutatesParent, false);
            AssertEq(Operands.R15b.MutatesParent, false);
#endif
            AssertEq(Operands.Ax.MutatesParent, false);
            AssertEq(Operands.Cx.MutatesParent, false);
            AssertEq(Operands.Dx.MutatesParent, false);
            AssertEq(Operands.Bx.MutatesParent, false);
            AssertEq(Operands.Sp.MutatesParent, false);
            AssertEq(Operands.Bp.MutatesParent, false);
            AssertEq(Operands.Si.MutatesParent, false);
            AssertEq(Operands.Di.MutatesParent, false);
#if _X64_
            AssertEq(Operands.R8w.MutatesParent, false);
            AssertEq(Operands.R9w.MutatesParent, false);
            AssertEq(Operands.R10w.MutatesParent, false);
            AssertEq(Operands.R11w.MutatesParent, false);
            AssertEq(Operands.R12w.MutatesParent, false);
            AssertEq(Operands.R13w.MutatesParent, false);
            AssertEq(Operands.R14w.MutatesParent, false);
            AssertEq(Operands.R15w.MutatesParent, false);
#endif

#if _X64_
            AssertEq(Operands.Eax.MutatesParent, true);
            AssertEq(Operands.Ecx.MutatesParent, true);
            AssertEq(Operands.Edx.MutatesParent, true);
            AssertEq(Operands.Ebx.MutatesParent, true);
            AssertEq(Operands.Esp.MutatesParent, true);
            AssertEq(Operands.Ebp.MutatesParent, true);
            AssertEq(Operands.Edi.MutatesParent, true);
            AssertEq(Operands.Esi.MutatesParent, true);
            AssertEq(Operands.R8d.MutatesParent, true);
            AssertEq(Operands.R9d.MutatesParent, true);
            AssertEq(Operands.R10d.MutatesParent, true);
            AssertEq(Operands.R11d.MutatesParent, true);
            AssertEq(Operands.R12d.MutatesParent, true);
            AssertEq(Operands.R13d.MutatesParent, true);
            AssertEq(Operands.R14d.MutatesParent, true);
            AssertEq(Operands.R15d.MutatesParent, true);
            AssertEq(Operands.Rax.MutatesParent, false);
            AssertEq(Operands.Rcx.MutatesParent, false);
            AssertEq(Operands.Rdx.MutatesParent, false);
            AssertEq(Operands.Rbx.MutatesParent, false);
            AssertEq(Operands.Rsp.MutatesParent, false);
            AssertEq(Operands.Rbp.MutatesParent, false);
            AssertEq(Operands.Rdi.MutatesParent, false);
            AssertEq(Operands.Rsi.MutatesParent, false);
            AssertEq(Operands.R8.MutatesParent, false);
            AssertEq(Operands.R9.MutatesParent, false);
            AssertEq(Operands.R10.MutatesParent, false);
            AssertEq(Operands.R11.MutatesParent, false);
            AssertEq(Operands.R12.MutatesParent, false);
            AssertEq(Operands.R13.MutatesParent, false);
            AssertEq(Operands.R14.MutatesParent, false);
            AssertEq(Operands.R15.MutatesParent, false);
#else
            AssertEq(Operands.Eax.MutatesParent, false);
            AssertEq(Operands.Ecx.MutatesParent, false);
            AssertEq(Operands.Edx.MutatesParent, false);
            AssertEq(Operands.Ebx.MutatesParent, false);
            AssertEq(Operands.Esp.MutatesParent, false);
            AssertEq(Operands.Ebp.MutatesParent, false);
            AssertEq(Operands.Edi.MutatesParent, false);
            AssertEq(Operands.Esi.MutatesParent, false);
            AssertEq(Operands.R8d.MutatesParent, false);
            AssertEq(Operands.R9d.MutatesParent, false);
            AssertEq(Operands.R10d.MutatesParent, false);
            AssertEq(Operands.R11d.MutatesParent, false);
            AssertEq(Operands.R12d.MutatesParent, false);
            AssertEq(Operands.R13d.MutatesParent, false);
            AssertEq(Operands.R14d.MutatesParent, false);
            AssertEq(Operands.R15d.MutatesParent, false);
#endif
        }
    }
}
