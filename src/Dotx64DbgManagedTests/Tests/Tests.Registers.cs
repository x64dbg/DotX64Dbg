using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Dotx64Dbg.Managed.Tests
{
    using static Testing;

    class TestRegisters
    {
        public TestRegisters()
        {
            // Warm-up purpose. Dll loading is deferred.
            _ = Operand.Al.RootId;
        }

        [Test]
        public void TestRoot()
        {
            AssertEq(Operand.Reg(Register.None).RootId, Register.None);
#if _X64_
            AssertEq(Operand.Al.RootId, Register.Rax);
            AssertEq(Operand.Cl.RootId, Register.Rcx);
            AssertEq(Operand.Dl.RootId, Register.Rdx);
            AssertEq(Operand.Bl.RootId, Register.Rbx);
            AssertEq(Operand.Ah.RootId, Register.Rax);
            AssertEq(Operand.Ch.RootId, Register.Rcx);
            AssertEq(Operand.Dh.RootId, Register.Rdx);
            AssertEq(Operand.Bh.RootId, Register.Rbx);
            AssertEq(Operand.Spl.RootId, Register.Rsp);
            AssertEq(Operand.Bpl.RootId, Register.Rbp);
            AssertEq(Operand.Sil.RootId, Register.Rsi);
            AssertEq(Operand.Dil.RootId, Register.Rdi);
            AssertEq(Operand.R8b.RootId, Register.R8);
            AssertEq(Operand.R9b.RootId, Register.R9);
            AssertEq(Operand.R10b.RootId, Register.R10);
            AssertEq(Operand.R11b.RootId, Register.R11);
            AssertEq(Operand.R12b.RootId, Register.R12);
            AssertEq(Operand.R13b.RootId, Register.R13);
            AssertEq(Operand.R14b.RootId, Register.R14);
            AssertEq(Operand.R15b.RootId, Register.R15);
            AssertEq(Operand.Ax.RootId, Register.Rax);
            AssertEq(Operand.Cx.RootId, Register.Rcx);
            AssertEq(Operand.Dx.RootId, Register.Rdx);
            AssertEq(Operand.Bx.RootId, Register.Rbx);
            AssertEq(Operand.Sp.RootId, Register.Rsp);
            AssertEq(Operand.Bp.RootId, Register.Rbp);
            AssertEq(Operand.Si.RootId, Register.Rsi);
            AssertEq(Operand.Di.RootId, Register.Rdi);
            AssertEq(Operand.R8w.RootId, Register.R8);
            AssertEq(Operand.R9w.RootId, Register.R9);
            AssertEq(Operand.R10w.RootId, Register.R10);
            AssertEq(Operand.R11w.RootId, Register.R11);
            AssertEq(Operand.R12w.RootId, Register.R12);
            AssertEq(Operand.R13w.RootId, Register.R13);
            AssertEq(Operand.R14w.RootId, Register.R14);
            AssertEq(Operand.R15w.RootId, Register.R15);
            AssertEq(Operand.Eax.RootId, Register.Rax);
            AssertEq(Operand.Ecx.RootId, Register.Rcx);
            AssertEq(Operand.Edx.RootId, Register.Rdx);
            AssertEq(Operand.Ebx.RootId, Register.Rbx);
            AssertEq(Operand.Esp.RootId, Register.Rsp);
            AssertEq(Operand.Ebp.RootId, Register.Rbp);
            AssertEq(Operand.Esi.RootId, Register.Rsi);
            AssertEq(Operand.Edi.RootId, Register.Rdi);
            AssertEq(Operand.R8d.RootId, Register.R8);
            AssertEq(Operand.R9d.RootId, Register.R9);
            AssertEq(Operand.R10d.RootId, Register.R10);
            AssertEq(Operand.R11d.RootId, Register.R11);
            AssertEq(Operand.R12d.RootId, Register.R12);
            AssertEq(Operand.R13d.RootId, Register.R13);
            AssertEq(Operand.R14d.RootId, Register.R14);
            AssertEq(Operand.R15d.RootId, Register.R15);
            AssertEq(Operand.Rax.RootId, Register.None);
            AssertEq(Operand.Rcx.RootId, Register.None);
            AssertEq(Operand.Rdx.RootId, Register.None);
            AssertEq(Operand.Rbx.RootId, Register.None);
            AssertEq(Operand.Rsp.RootId, Register.None);
            AssertEq(Operand.Rbp.RootId, Register.None);
            AssertEq(Operand.Rsi.RootId, Register.None);
            AssertEq(Operand.Rdi.RootId, Register.None);
            AssertEq(Operand.R8.RootId, Register.None);
            AssertEq(Operand.R9.RootId, Register.None);
            AssertEq(Operand.R10.RootId, Register.None);
            AssertEq(Operand.R11.RootId, Register.None);
            AssertEq(Operand.R12.RootId, Register.None);
            AssertEq(Operand.R13.RootId, Register.None);
            AssertEq(Operand.R14.RootId, Register.None);
            AssertEq(Operand.R15.RootId, Register.None);
#else
            AssertEq(Operand.Al.RootId, Register.Eax);
            AssertEq(Operand.Cl.RootId, Register.Ecx);
            AssertEq(Operand.Dl.RootId, Register.Edx);
            AssertEq(Operand.Bl.RootId, Register.Ebx);
            AssertEq(Operand.Ah.RootId, Register.Eax);
            AssertEq(Operand.Ch.RootId, Register.Ecx);
            AssertEq(Operand.Dh.RootId, Register.Edx);
            AssertEq(Operand.Bh.RootId, Register.Ebx);
            AssertEq(Operand.Spl.RootId, Register.Esp);
            AssertEq(Operand.Bpl.RootId, Register.Ebp);
            AssertEq(Operand.Sil.RootId, Register.Esi);
            AssertEq(Operand.Dil.RootId, Register.Edi);
            AssertEq(Operand.Ax.RootId, Register.Eax);
            AssertEq(Operand.Cx.RootId, Register.Ecx);
            AssertEq(Operand.Dx.RootId, Register.Edx);
            AssertEq(Operand.Bx.RootId, Register.Ebx);
            AssertEq(Operand.Sp.RootId, Register.Esp);
            AssertEq(Operand.Bp.RootId, Register.Ebp);
            AssertEq(Operand.Si.RootId, Register.Esi);
            AssertEq(Operand.Di.RootId, Register.Edi);
            AssertEq(Operand.Eax.RootId, Register.None);
            AssertEq(Operand.Ecx.RootId, Register.None);
            AssertEq(Operand.Edx.RootId, Register.None);
            AssertEq(Operand.Ebx.RootId, Register.None);
            AssertEq(Operand.Esp.RootId, Register.None);
            AssertEq(Operand.Ebp.RootId, Register.None);
            AssertEq(Operand.Esi.RootId, Register.None);
            AssertEq(Operand.Edi.RootId, Register.None);
            AssertEq(Operand.R8d.RootId, Register.None);
            AssertEq(Operand.R9d.RootId, Register.None);
            AssertEq(Operand.R10d.RootId, Register.None);
            AssertEq(Operand.R11d.RootId, Register.None);
            AssertEq(Operand.R12d.RootId, Register.None);
            AssertEq(Operand.R13d.RootId, Register.None);
            AssertEq(Operand.R14d.RootId, Register.None);
            AssertEq(Operand.R15d.RootId, Register.None);
#endif
        }

        [Test]
        public void TestParent()
        {
            AssertEq(Operand.Al.ParentId, Register.Ax);
            AssertEq(Operand.Cl.ParentId, Register.Cx);
            AssertEq(Operand.Dl.ParentId, Register.Dx);
            AssertEq(Operand.Bl.ParentId, Register.Bx);
            AssertEq(Operand.Ah.ParentId, Register.Ax);
            AssertEq(Operand.Ch.ParentId, Register.Cx);
            AssertEq(Operand.Dh.ParentId, Register.Dx);
            AssertEq(Operand.Bh.ParentId, Register.Bx);
            AssertEq(Operand.Spl.ParentId, Register.Sp);
            AssertEq(Operand.Bpl.ParentId, Register.Bp);
            AssertEq(Operand.Sil.ParentId, Register.Si);
            AssertEq(Operand.Dil.ParentId, Register.Di);
#if _X64_
            AssertEq(Operand.R8b.ParentId, Register.R8w);
            AssertEq(Operand.R9b.ParentId, Register.R9w);
            AssertEq(Operand.R10b.ParentId, Register.R10w);
            AssertEq(Operand.R11b.ParentId, Register.R11w);
            AssertEq(Operand.R12b.ParentId, Register.R12w);
            AssertEq(Operand.R13b.ParentId, Register.R13w);
            AssertEq(Operand.R14b.ParentId, Register.R14w);
            AssertEq(Operand.R15b.ParentId, Register.R15w);
#endif
            AssertEq(Operand.Ax.ParentId, Register.Eax);
            AssertEq(Operand.Cx.ParentId, Register.Ecx);
            AssertEq(Operand.Dx.ParentId, Register.Edx);
            AssertEq(Operand.Bx.ParentId, Register.Ebx);
            AssertEq(Operand.Sp.ParentId, Register.Esp);
            AssertEq(Operand.Bp.ParentId, Register.Ebp);
            AssertEq(Operand.Si.ParentId, Register.Esi);
            AssertEq(Operand.Di.ParentId, Register.Edi);
#if _X64_
            AssertEq(Operand.R8w.ParentId, Register.R8d);
            AssertEq(Operand.R9w.ParentId, Register.R9d);
            AssertEq(Operand.R10w.ParentId, Register.R10d);
            AssertEq(Operand.R11w.ParentId, Register.R11d);
            AssertEq(Operand.R12w.ParentId, Register.R12d);
            AssertEq(Operand.R13w.ParentId, Register.R13d);
            AssertEq(Operand.R14w.ParentId, Register.R14d);
            AssertEq(Operand.R15w.ParentId, Register.R15d);
#endif

#if _X64_
            AssertEq(Operand.Eax.ParentId, Register.Rax);
            AssertEq(Operand.Ecx.ParentId, Register.Rcx);
            AssertEq(Operand.Edx.ParentId, Register.Rdx);
            AssertEq(Operand.Ebx.ParentId, Register.Rbx);
            AssertEq(Operand.Esp.ParentId, Register.Rsp);
            AssertEq(Operand.Ebp.ParentId, Register.Rbp);
            AssertEq(Operand.Esi.ParentId, Register.Rsi);
            AssertEq(Operand.Edi.ParentId, Register.Rdi);
#else
            AssertEq(Operand.Eax.ParentId, Register.None);
            AssertEq(Operand.Ecx.ParentId, Register.None);
            AssertEq(Operand.Edx.ParentId, Register.None);
            AssertEq(Operand.Ebx.ParentId, Register.None);
            AssertEq(Operand.Esp.ParentId, Register.None);
            AssertEq(Operand.Ebp.ParentId, Register.None);
            AssertEq(Operand.Esi.ParentId, Register.None);
            AssertEq(Operand.Edi.ParentId, Register.None);
#endif
#if _X64_
            AssertEq(Operand.R8d.ParentId, Register.R8);
            AssertEq(Operand.R9d.ParentId, Register.R9);
            AssertEq(Operand.R10d.ParentId, Register.R10);
            AssertEq(Operand.R11d.ParentId, Register.R11);
            AssertEq(Operand.R12d.ParentId, Register.R12);
            AssertEq(Operand.R13d.ParentId, Register.R13);
            AssertEq(Operand.R14d.ParentId, Register.R14);
            AssertEq(Operand.R15d.ParentId, Register.R15);
            AssertEq(Operand.Rax.ParentId, Register.None);
            AssertEq(Operand.Rcx.ParentId, Register.None);
            AssertEq(Operand.Rdx.ParentId, Register.None);
            AssertEq(Operand.Rbx.ParentId, Register.None);
            AssertEq(Operand.Rsp.ParentId, Register.None);
            AssertEq(Operand.Rbp.ParentId, Register.None);
            AssertEq(Operand.Rsi.ParentId, Register.None);
            AssertEq(Operand.Rdi.ParentId, Register.None);
            AssertEq(Operand.R8.ParentId, Register.None);
            AssertEq(Operand.R9.ParentId, Register.None);
            AssertEq(Operand.R10.ParentId, Register.None);
            AssertEq(Operand.R11.ParentId, Register.None);
            AssertEq(Operand.R12.ParentId, Register.None);
            AssertEq(Operand.R13.ParentId, Register.None);
            AssertEq(Operand.R14.ParentId, Register.None);
            AssertEq(Operand.R15.ParentId, Register.None);
#endif
        }
    }
}
