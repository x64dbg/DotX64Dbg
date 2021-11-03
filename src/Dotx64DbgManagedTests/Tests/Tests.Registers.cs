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
        [Test]
        public void TestRoot()
        {
            AssertEq(Operands.Reg(Register.None).RootId, Register.None);
#if _X64_
            AssertEq(Operands.Al.RootId, Register.Rax);
            AssertEq(Operands.Cl.RootId, Register.Rcx);
            AssertEq(Operands.Dl.RootId, Register.Rdx);
            AssertEq(Operands.Bl.RootId, Register.Rbx);
            AssertEq(Operands.Ah.RootId, Register.Rax);
            AssertEq(Operands.Ch.RootId, Register.Rcx);
            AssertEq(Operands.Dh.RootId, Register.Rdx);
            AssertEq(Operands.Bh.RootId, Register.Rbx);
            AssertEq(Operands.Spl.RootId, Register.Rsp);
            AssertEq(Operands.Bpl.RootId, Register.Rbp);
            AssertEq(Operands.Sil.RootId, Register.Rsi);
            AssertEq(Operands.Dil.RootId, Register.Rdi);
            AssertEq(Operands.R8b.RootId, Register.R8);
            AssertEq(Operands.R9b.RootId, Register.R9);
            AssertEq(Operands.R10b.RootId, Register.R10);
            AssertEq(Operands.R11b.RootId, Register.R11);
            AssertEq(Operands.R12b.RootId, Register.R12);
            AssertEq(Operands.R13b.RootId, Register.R13);
            AssertEq(Operands.R14b.RootId, Register.R14);
            AssertEq(Operands.R15b.RootId, Register.R15);
            AssertEq(Operands.Ax.RootId, Register.Rax);
            AssertEq(Operands.Cx.RootId, Register.Rcx);
            AssertEq(Operands.Dx.RootId, Register.Rdx);
            AssertEq(Operands.Bx.RootId, Register.Rbx);
            AssertEq(Operands.Sp.RootId, Register.Rsp);
            AssertEq(Operands.Bp.RootId, Register.Rbp);
            AssertEq(Operands.Si.RootId, Register.Rsi);
            AssertEq(Operands.Di.RootId, Register.Rdi);
            AssertEq(Operands.R8w.RootId, Register.R8);
            AssertEq(Operands.R9w.RootId, Register.R9);
            AssertEq(Operands.R10w.RootId, Register.R10);
            AssertEq(Operands.R11w.RootId, Register.R11);
            AssertEq(Operands.R12w.RootId, Register.R12);
            AssertEq(Operands.R13w.RootId, Register.R13);
            AssertEq(Operands.R14w.RootId, Register.R14);
            AssertEq(Operands.R15w.RootId, Register.R15);
            AssertEq(Operands.Eax.RootId, Register.Rax);
            AssertEq(Operands.Ecx.RootId, Register.Rcx);
            AssertEq(Operands.Edx.RootId, Register.Rdx);
            AssertEq(Operands.Ebx.RootId, Register.Rbx);
            AssertEq(Operands.Esp.RootId, Register.Rsp);
            AssertEq(Operands.Ebp.RootId, Register.Rbp);
            AssertEq(Operands.Esi.RootId, Register.Rsi);
            AssertEq(Operands.Edi.RootId, Register.Rdi);
            AssertEq(Operands.R8d.RootId, Register.R8);
            AssertEq(Operands.R9d.RootId, Register.R9);
            AssertEq(Operands.R10d.RootId, Register.R10);
            AssertEq(Operands.R11d.RootId, Register.R11);
            AssertEq(Operands.R12d.RootId, Register.R12);
            AssertEq(Operands.R13d.RootId, Register.R13);
            AssertEq(Operands.R14d.RootId, Register.R14);
            AssertEq(Operands.R15d.RootId, Register.R15);
            AssertEq(Operands.Rax.RootId, Register.None);
            AssertEq(Operands.Rcx.RootId, Register.None);
            AssertEq(Operands.Rdx.RootId, Register.None);
            AssertEq(Operands.Rbx.RootId, Register.None);
            AssertEq(Operands.Rsp.RootId, Register.None);
            AssertEq(Operands.Rbp.RootId, Register.None);
            AssertEq(Operands.Rsi.RootId, Register.None);
            AssertEq(Operands.Rdi.RootId, Register.None);
            AssertEq(Operands.R8.RootId, Register.None);
            AssertEq(Operands.R9.RootId, Register.None);
            AssertEq(Operands.R10.RootId, Register.None);
            AssertEq(Operands.R11.RootId, Register.None);
            AssertEq(Operands.R12.RootId, Register.None);
            AssertEq(Operands.R13.RootId, Register.None);
            AssertEq(Operands.R14.RootId, Register.None);
            AssertEq(Operands.R15.RootId, Register.None);
#else
            AssertEq(Operands.Al.RootId, Register.Eax);
            AssertEq(Operands.Cl.RootId, Register.Ecx);
            AssertEq(Operands.Dl.RootId, Register.Edx);
            AssertEq(Operands.Bl.RootId, Register.Ebx);
            AssertEq(Operands.Ah.RootId, Register.Eax);
            AssertEq(Operands.Ch.RootId, Register.Ecx);
            AssertEq(Operands.Dh.RootId, Register.Edx);
            AssertEq(Operands.Bh.RootId, Register.Ebx);
            AssertEq(Operands.Spl.RootId, Register.Esp);
            AssertEq(Operands.Bpl.RootId, Register.Ebp);
            AssertEq(Operands.Sil.RootId, Register.Esi);
            AssertEq(Operands.Dil.RootId, Register.Edi);
            AssertEq(Operands.Ax.RootId, Register.Eax);
            AssertEq(Operands.Cx.RootId, Register.Ecx);
            AssertEq(Operands.Dx.RootId, Register.Edx);
            AssertEq(Operands.Bx.RootId, Register.Ebx);
            AssertEq(Operands.Sp.RootId, Register.Esp);
            AssertEq(Operands.Bp.RootId, Register.Ebp);
            AssertEq(Operands.Si.RootId, Register.Esi);
            AssertEq(Operands.Di.RootId, Register.Edi);
            AssertEq(Operands.Eax.RootId, Register.None);
            AssertEq(Operands.Ecx.RootId, Register.None);
            AssertEq(Operands.Edx.RootId, Register.None);
            AssertEq(Operands.Ebx.RootId, Register.None);
            AssertEq(Operands.Esp.RootId, Register.None);
            AssertEq(Operands.Ebp.RootId, Register.None);
            AssertEq(Operands.Esi.RootId, Register.None);
            AssertEq(Operands.Edi.RootId, Register.None);
            AssertEq(Operands.R8d.RootId, Register.None);
            AssertEq(Operands.R9d.RootId, Register.None);
            AssertEq(Operands.R10d.RootId, Register.None);
            AssertEq(Operands.R11d.RootId, Register.None);
            AssertEq(Operands.R12d.RootId, Register.None);
            AssertEq(Operands.R13d.RootId, Register.None);
            AssertEq(Operands.R14d.RootId, Register.None);
            AssertEq(Operands.R15d.RootId, Register.None);
#endif
        }

        [Test]
        public void TestParent()
        {
            AssertEq(Operands.Al.ParentId, Register.Ax);
            AssertEq(Operands.Cl.ParentId, Register.Cx);
            AssertEq(Operands.Dl.ParentId, Register.Dx);
            AssertEq(Operands.Bl.ParentId, Register.Bx);
            AssertEq(Operands.Ah.ParentId, Register.Ax);
            AssertEq(Operands.Ch.ParentId, Register.Cx);
            AssertEq(Operands.Dh.ParentId, Register.Dx);
            AssertEq(Operands.Bh.ParentId, Register.Bx);
            AssertEq(Operands.Spl.ParentId, Register.Sp);
            AssertEq(Operands.Bpl.ParentId, Register.Bp);
            AssertEq(Operands.Sil.ParentId, Register.Si);
            AssertEq(Operands.Dil.ParentId, Register.Di);
#if _X64_
            AssertEq(Operands.R8b.ParentId, Register.R8w);
            AssertEq(Operands.R9b.ParentId, Register.R9w);
            AssertEq(Operands.R10b.ParentId, Register.R10w);
            AssertEq(Operands.R11b.ParentId, Register.R11w);
            AssertEq(Operands.R12b.ParentId, Register.R12w);
            AssertEq(Operands.R13b.ParentId, Register.R13w);
            AssertEq(Operands.R14b.ParentId, Register.R14w);
            AssertEq(Operands.R15b.ParentId, Register.R15w);
#endif
            AssertEq(Operands.Ax.ParentId, Register.Eax);
            AssertEq(Operands.Cx.ParentId, Register.Ecx);
            AssertEq(Operands.Dx.ParentId, Register.Edx);
            AssertEq(Operands.Bx.ParentId, Register.Ebx);
            AssertEq(Operands.Sp.ParentId, Register.Esp);
            AssertEq(Operands.Bp.ParentId, Register.Ebp);
            AssertEq(Operands.Si.ParentId, Register.Esi);
            AssertEq(Operands.Di.ParentId, Register.Edi);
#if _X64_
            AssertEq(Operands.R8w.ParentId, Register.R8d);
            AssertEq(Operands.R9w.ParentId, Register.R9d);
            AssertEq(Operands.R10w.ParentId, Register.R10d);
            AssertEq(Operands.R11w.ParentId, Register.R11d);
            AssertEq(Operands.R12w.ParentId, Register.R12d);
            AssertEq(Operands.R13w.ParentId, Register.R13d);
            AssertEq(Operands.R14w.ParentId, Register.R14d);
            AssertEq(Operands.R15w.ParentId, Register.R15d);
#endif

#if _X64_
            AssertEq(Operands.Eax.ParentId, Register.Rax);
            AssertEq(Operands.Ecx.ParentId, Register.Rcx);
            AssertEq(Operands.Edx.ParentId, Register.Rdx);
            AssertEq(Operands.Ebx.ParentId, Register.Rbx);
            AssertEq(Operands.Esp.ParentId, Register.Rsp);
            AssertEq(Operands.Ebp.ParentId, Register.Rbp);
            AssertEq(Operands.Esi.ParentId, Register.Rsi);
            AssertEq(Operands.Edi.ParentId, Register.Rdi);
#else
            AssertEq(Operands.Eax.ParentId, Register.None);
            AssertEq(Operands.Ecx.ParentId, Register.None);
            AssertEq(Operands.Edx.ParentId, Register.None);
            AssertEq(Operands.Ebx.ParentId, Register.None);
            AssertEq(Operands.Esp.ParentId, Register.None);
            AssertEq(Operands.Ebp.ParentId, Register.None);
            AssertEq(Operands.Esi.ParentId, Register.None);
            AssertEq(Operands.Edi.ParentId, Register.None);
#endif
#if _X64_
            AssertEq(Operands.R8d.ParentId, Register.R8);
            AssertEq(Operands.R9d.ParentId, Register.R9);
            AssertEq(Operands.R10d.ParentId, Register.R10);
            AssertEq(Operands.R11d.ParentId, Register.R11);
            AssertEq(Operands.R12d.ParentId, Register.R12);
            AssertEq(Operands.R13d.ParentId, Register.R13);
            AssertEq(Operands.R14d.ParentId, Register.R14);
            AssertEq(Operands.R15d.ParentId, Register.R15);
            AssertEq(Operands.Rax.ParentId, Register.None);
            AssertEq(Operands.Rcx.ParentId, Register.None);
            AssertEq(Operands.Rdx.ParentId, Register.None);
            AssertEq(Operands.Rbx.ParentId, Register.None);
            AssertEq(Operands.Rsp.ParentId, Register.None);
            AssertEq(Operands.Rbp.ParentId, Register.None);
            AssertEq(Operands.Rsi.ParentId, Register.None);
            AssertEq(Operands.Rdi.ParentId, Register.None);
            AssertEq(Operands.R8.ParentId, Register.None);
            AssertEq(Operands.R9.ParentId, Register.None);
            AssertEq(Operands.R10.ParentId, Register.None);
            AssertEq(Operands.R11.ParentId, Register.None);
            AssertEq(Operands.R12.ParentId, Register.None);
            AssertEq(Operands.R13.ParentId, Register.None);
            AssertEq(Operands.R14.ParentId, Register.None);
            AssertEq(Operands.R15.ParentId, Register.None);
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
