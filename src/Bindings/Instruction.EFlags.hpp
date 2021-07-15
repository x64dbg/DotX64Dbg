#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdio>

namespace Dotx64Dbg {

    using namespace System;

    [System::Flags]
    public enum class EFlags
    {
        None = 0,
        Cf = (1 << 0),
        Pf = (1 << 2),
        Af = (1 << 4),
        Zf = (1 << 6),
        Sf = (1 << 7),
        Tf = (1 << 8),
        If = (1 << 9),
        Df = (1 << 10),
        Of = (1 << 11),
        Iopl = (1 << 12),
        Nt = (1 << 14),
        Rf = (1 << 16),
        Vm = (1 << 17),
        Ac = (1 << 18),
        Vif = (1 << 19),
        Vip = (1 << 20),
        Id = (1 << 21),
        C0 = (1 << 22),
        C1 = (1 << 23),
        C2 = (1 << 24),
        C3 = (1 << 25),
    };

}
