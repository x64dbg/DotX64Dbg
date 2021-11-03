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
            AssertEq(Operands.Reg(RegisterId.None).RootId, RegisterId.None);
#if _X64_
            AssertEq(Operands.Al.RootId, RegisterId.Rax);
            AssertEq(Operands.Cl.RootId, RegisterId.Rcx);
            AssertEq(Operands.Dl.RootId, RegisterId.Rdx);
            AssertEq(Operands.Bl.RootId, RegisterId.Rbx);
            AssertEq(Operands.Ah.RootId, RegisterId.Rax);
            AssertEq(Operands.Ch.RootId, RegisterId.Rcx);
            AssertEq(Operands.Dh.RootId, RegisterId.Rdx);
            AssertEq(Operands.Bh.RootId, RegisterId.Rbx);
            AssertEq(Operands.Spl.RootId, RegisterId.Rsp);
            AssertEq(Operands.Bpl.RootId, RegisterId.Rbp);
            AssertEq(Operands.Sil.RootId, RegisterId.Rsi);
            AssertEq(Operands.Dil.RootId, RegisterId.Rdi);
            AssertEq(Operands.R8b.RootId, RegisterId.R8);
            AssertEq(Operands.R9b.RootId, RegisterId.R9);
            AssertEq(Operands.R10b.RootId, RegisterId.R10);
            AssertEq(Operands.R11b.RootId, RegisterId.R11);
            AssertEq(Operands.R12b.RootId, RegisterId.R12);
            AssertEq(Operands.R13b.RootId, RegisterId.R13);
            AssertEq(Operands.R14b.RootId, RegisterId.R14);
            AssertEq(Operands.R15b.RootId, RegisterId.R15);
            AssertEq(Operands.Ax.RootId, RegisterId.Rax);
            AssertEq(Operands.Cx.RootId, RegisterId.Rcx);
            AssertEq(Operands.Dx.RootId, RegisterId.Rdx);
            AssertEq(Operands.Bx.RootId, RegisterId.Rbx);
            AssertEq(Operands.Sp.RootId, RegisterId.Rsp);
            AssertEq(Operands.Bp.RootId, RegisterId.Rbp);
            AssertEq(Operands.Si.RootId, RegisterId.Rsi);
            AssertEq(Operands.Di.RootId, RegisterId.Rdi);
            AssertEq(Operands.R8w.RootId, RegisterId.R8);
            AssertEq(Operands.R9w.RootId, RegisterId.R9);
            AssertEq(Operands.R10w.RootId, RegisterId.R10);
            AssertEq(Operands.R11w.RootId, RegisterId.R11);
            AssertEq(Operands.R12w.RootId, RegisterId.R12);
            AssertEq(Operands.R13w.RootId, RegisterId.R13);
            AssertEq(Operands.R14w.RootId, RegisterId.R14);
            AssertEq(Operands.R15w.RootId, RegisterId.R15);
            AssertEq(Operands.Eax.RootId, RegisterId.Rax);
            AssertEq(Operands.Ecx.RootId, RegisterId.Rcx);
            AssertEq(Operands.Edx.RootId, RegisterId.Rdx);
            AssertEq(Operands.Ebx.RootId, RegisterId.Rbx);
            AssertEq(Operands.Esp.RootId, RegisterId.Rsp);
            AssertEq(Operands.Ebp.RootId, RegisterId.Rbp);
            AssertEq(Operands.Esi.RootId, RegisterId.Rsi);
            AssertEq(Operands.Edi.RootId, RegisterId.Rdi);
            AssertEq(Operands.R8d.RootId, RegisterId.R8);
            AssertEq(Operands.R9d.RootId, RegisterId.R9);
            AssertEq(Operands.R10d.RootId, RegisterId.R10);
            AssertEq(Operands.R11d.RootId, RegisterId.R11);
            AssertEq(Operands.R12d.RootId, RegisterId.R12);
            AssertEq(Operands.R13d.RootId, RegisterId.R13);
            AssertEq(Operands.R14d.RootId, RegisterId.R14);
            AssertEq(Operands.R15d.RootId, RegisterId.R15);
            AssertEq(Operands.Rax.RootId, RegisterId.None);
            AssertEq(Operands.Rcx.RootId, RegisterId.None);
            AssertEq(Operands.Rdx.RootId, RegisterId.None);
            AssertEq(Operands.Rbx.RootId, RegisterId.None);
            AssertEq(Operands.Rsp.RootId, RegisterId.None);
            AssertEq(Operands.Rbp.RootId, RegisterId.None);
            AssertEq(Operands.Rsi.RootId, RegisterId.None);
            AssertEq(Operands.Rdi.RootId, RegisterId.None);
            AssertEq(Operands.R8.RootId, RegisterId.None);
            AssertEq(Operands.R9.RootId, RegisterId.None);
            AssertEq(Operands.R10.RootId, RegisterId.None);
            AssertEq(Operands.R11.RootId, RegisterId.None);
            AssertEq(Operands.R12.RootId, RegisterId.None);
            AssertEq(Operands.R13.RootId, RegisterId.None);
            AssertEq(Operands.R14.RootId, RegisterId.None);
            AssertEq(Operands.R15.RootId, RegisterId.None);
#else
            AssertEq(Operands.Al.RootId, RegisterId.Eax);
            AssertEq(Operands.Cl.RootId, RegisterId.Ecx);
            AssertEq(Operands.Dl.RootId, RegisterId.Edx);
            AssertEq(Operands.Bl.RootId, RegisterId.Ebx);
            AssertEq(Operands.Ah.RootId, RegisterId.Eax);
            AssertEq(Operands.Ch.RootId, RegisterId.Ecx);
            AssertEq(Operands.Dh.RootId, RegisterId.Edx);
            AssertEq(Operands.Bh.RootId, RegisterId.Ebx);
            AssertEq(Operands.Spl.RootId, RegisterId.Esp);
            AssertEq(Operands.Bpl.RootId, RegisterId.Ebp);
            AssertEq(Operands.Sil.RootId, RegisterId.Esi);
            AssertEq(Operands.Dil.RootId, RegisterId.Edi);
            AssertEq(Operands.Ax.RootId, RegisterId.Eax);
            AssertEq(Operands.Cx.RootId, RegisterId.Ecx);
            AssertEq(Operands.Dx.RootId, RegisterId.Edx);
            AssertEq(Operands.Bx.RootId, RegisterId.Ebx);
            AssertEq(Operands.Sp.RootId, RegisterId.Esp);
            AssertEq(Operands.Bp.RootId, RegisterId.Ebp);
            AssertEq(Operands.Si.RootId, RegisterId.Esi);
            AssertEq(Operands.Di.RootId, RegisterId.Edi);
            AssertEq(Operands.Eax.RootId, RegisterId.None);
            AssertEq(Operands.Ecx.RootId, RegisterId.None);
            AssertEq(Operands.Edx.RootId, RegisterId.None);
            AssertEq(Operands.Ebx.RootId, RegisterId.None);
            AssertEq(Operands.Esp.RootId, RegisterId.None);
            AssertEq(Operands.Ebp.RootId, RegisterId.None);
            AssertEq(Operands.Esi.RootId, RegisterId.None);
            AssertEq(Operands.Edi.RootId, RegisterId.None);
            AssertEq(Operands.R8d.RootId, RegisterId.None);
            AssertEq(Operands.R9d.RootId, RegisterId.None);
            AssertEq(Operands.R10d.RootId, RegisterId.None);
            AssertEq(Operands.R11d.RootId, RegisterId.None);
            AssertEq(Operands.R12d.RootId, RegisterId.None);
            AssertEq(Operands.R13d.RootId, RegisterId.None);
            AssertEq(Operands.R14d.RootId, RegisterId.None);
            AssertEq(Operands.R15d.RootId, RegisterId.None);
#endif
        }

        [Test]
        public void TestParent()
        {
            AssertEq(Operands.Al.ParentId, RegisterId.Ax);
            AssertEq(Operands.Cl.ParentId, RegisterId.Cx);
            AssertEq(Operands.Dl.ParentId, RegisterId.Dx);
            AssertEq(Operands.Bl.ParentId, RegisterId.Bx);
            AssertEq(Operands.Ah.ParentId, RegisterId.Ax);
            AssertEq(Operands.Ch.ParentId, RegisterId.Cx);
            AssertEq(Operands.Dh.ParentId, RegisterId.Dx);
            AssertEq(Operands.Bh.ParentId, RegisterId.Bx);
            AssertEq(Operands.Spl.ParentId, RegisterId.Sp);
            AssertEq(Operands.Bpl.ParentId, RegisterId.Bp);
            AssertEq(Operands.Sil.ParentId, RegisterId.Si);
            AssertEq(Operands.Dil.ParentId, RegisterId.Di);
#if _X64_
            AssertEq(Operands.R8b.ParentId, RegisterId.R8w);
            AssertEq(Operands.R9b.ParentId, RegisterId.R9w);
            AssertEq(Operands.R10b.ParentId, RegisterId.R10w);
            AssertEq(Operands.R11b.ParentId, RegisterId.R11w);
            AssertEq(Operands.R12b.ParentId, RegisterId.R12w);
            AssertEq(Operands.R13b.ParentId, RegisterId.R13w);
            AssertEq(Operands.R14b.ParentId, RegisterId.R14w);
            AssertEq(Operands.R15b.ParentId, RegisterId.R15w);
#endif
            AssertEq(Operands.Ax.ParentId, RegisterId.Eax);
            AssertEq(Operands.Cx.ParentId, RegisterId.Ecx);
            AssertEq(Operands.Dx.ParentId, RegisterId.Edx);
            AssertEq(Operands.Bx.ParentId, RegisterId.Ebx);
            AssertEq(Operands.Sp.ParentId, RegisterId.Esp);
            AssertEq(Operands.Bp.ParentId, RegisterId.Ebp);
            AssertEq(Operands.Si.ParentId, RegisterId.Esi);
            AssertEq(Operands.Di.ParentId, RegisterId.Edi);
#if _X64_
            AssertEq(Operands.R8w.ParentId, RegisterId.R8d);
            AssertEq(Operands.R9w.ParentId, RegisterId.R9d);
            AssertEq(Operands.R10w.ParentId, RegisterId.R10d);
            AssertEq(Operands.R11w.ParentId, RegisterId.R11d);
            AssertEq(Operands.R12w.ParentId, RegisterId.R12d);
            AssertEq(Operands.R13w.ParentId, RegisterId.R13d);
            AssertEq(Operands.R14w.ParentId, RegisterId.R14d);
            AssertEq(Operands.R15w.ParentId, RegisterId.R15d);
#endif

#if _X64_
            AssertEq(Operands.Eax.ParentId, RegisterId.Rax);
            AssertEq(Operands.Ecx.ParentId, RegisterId.Rcx);
            AssertEq(Operands.Edx.ParentId, RegisterId.Rdx);
            AssertEq(Operands.Ebx.ParentId, RegisterId.Rbx);
            AssertEq(Operands.Esp.ParentId, RegisterId.Rsp);
            AssertEq(Operands.Ebp.ParentId, RegisterId.Rbp);
            AssertEq(Operands.Esi.ParentId, RegisterId.Rsi);
            AssertEq(Operands.Edi.ParentId, RegisterId.Rdi);
#else
            AssertEq(Operands.Eax.ParentId, RegisterId.None);
            AssertEq(Operands.Ecx.ParentId, RegisterId.None);
            AssertEq(Operands.Edx.ParentId, RegisterId.None);
            AssertEq(Operands.Ebx.ParentId, RegisterId.None);
            AssertEq(Operands.Esp.ParentId, RegisterId.None);
            AssertEq(Operands.Ebp.ParentId, RegisterId.None);
            AssertEq(Operands.Esi.ParentId, RegisterId.None);
            AssertEq(Operands.Edi.ParentId, RegisterId.None);
#endif
#if _X64_
            AssertEq(Operands.R8d.ParentId, RegisterId.R8);
            AssertEq(Operands.R9d.ParentId, RegisterId.R9);
            AssertEq(Operands.R10d.ParentId, RegisterId.R10);
            AssertEq(Operands.R11d.ParentId, RegisterId.R11);
            AssertEq(Operands.R12d.ParentId, RegisterId.R12);
            AssertEq(Operands.R13d.ParentId, RegisterId.R13);
            AssertEq(Operands.R14d.ParentId, RegisterId.R14);
            AssertEq(Operands.R15d.ParentId, RegisterId.R15);
            AssertEq(Operands.Rax.ParentId, RegisterId.None);
            AssertEq(Operands.Rcx.ParentId, RegisterId.None);
            AssertEq(Operands.Rdx.ParentId, RegisterId.None);
            AssertEq(Operands.Rbx.ParentId, RegisterId.None);
            AssertEq(Operands.Rsp.ParentId, RegisterId.None);
            AssertEq(Operands.Rbp.ParentId, RegisterId.None);
            AssertEq(Operands.Rsi.ParentId, RegisterId.None);
            AssertEq(Operands.Rdi.ParentId, RegisterId.None);
            AssertEq(Operands.R8.ParentId, RegisterId.None);
            AssertEq(Operands.R9.ParentId, RegisterId.None);
            AssertEq(Operands.R10.ParentId, RegisterId.None);
            AssertEq(Operands.R11.ParentId, RegisterId.None);
            AssertEq(Operands.R12.ParentId, RegisterId.None);
            AssertEq(Operands.R13.ParentId, RegisterId.None);
            AssertEq(Operands.R14.ParentId, RegisterId.None);
            AssertEq(Operands.R15.ParentId, RegisterId.None);
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
