#pragma once

namespace Dotx64Dbg
{

    public enum class Mnemonic
    {
        Invalid,
        Aaa,
        Aad,
        Aam,
        Aas,
        Adc,
        Adcx,
        Add,
        Addpd,
        Addps,
        Addsd,
        Addss,
        Addsubpd,
        Addsubps,
        Adox,
        Aesdec,
        Aesdec128kl,
        Aesdec256kl,
        Aesdeclast,
        Aesdecwide128kl,
        Aesdecwide256kl,
        Aesenc,
        Aesenc128kl,
        Aesenc256kl,
        Aesenclast,
        Aesencwide128kl,
        Aesencwide256kl,
        Aesimc,
        Aeskeygenassist,
        And,
        Andn,
        Andnpd,
        Andnps,
        Andpd,
        Andps,
        Arpl,
        Bextr,
        Blcfill,
        Blci,
        Blcic,
        Blcmsk,
        Blcs,
        Blendpd,
        Blendps,
        Blendvpd,
        Blendvps,
        Blsfill,
        Blsi,
        Blsic,
        Blsmsk,
        Blsr,
        Bndcl,
        Bndcn,
        Bndcu,
        Bndldx,
        Bndmk,
        Bndmov,
        Bndstx,
        Bound,
        Bsf,
        Bsr,
        Bswap,
        Bt,
        Btc,
        Btr,
        Bts,
        Bzhi,
        Call,
        Cbw,
        Cdq,
        Cdqe,
        Clac,
        Clc,
        Cld,
        Cldemote,
        Clevict0,
        Clevict1,
        Clflush,
        Clflushopt,
        Clgi,
        Cli,
        Clrssbsy,
        Clts,
        Clui,
        Clwb,
        Clzero,
        Cmc,
        Cmovb,
        Cmovbe,
        Cmovl,
        Cmovle,
        Cmovnb,
        Cmovnbe,
        Cmovnl,
        Cmovnle,
        Cmovno,
        Cmovnp,
        Cmovns,
        Cmovnz,
        Cmovo,
        Cmovp,
        Cmovs,
        Cmovz,
        Cmp,
        Cmppd,
        Cmpps,
        Cmpsb,
        Cmpsd,
        Cmpsq,
        Cmpss,
        Cmpsw,
        Cmpxchg,
        Cmpxchg16b,
        Cmpxchg8b,
        Comisd,
        Comiss,
        Cpuid,
        Cqo,
        Crc32,
        Cvtdq2pd,
        Cvtdq2ps,
        Cvtpd2dq,
        Cvtpd2pi,
        Cvtpd2ps,
        Cvtpi2pd,
        Cvtpi2ps,
        Cvtps2dq,
        Cvtps2pd,
        Cvtps2pi,
        Cvtsd2si,
        Cvtsd2ss,
        Cvtsi2sd,
        Cvtsi2ss,
        Cvtss2sd,
        Cvtss2si,
        Cvttpd2dq,
        Cvttpd2pi,
        Cvttps2dq,
        Cvttps2pi,
        Cvttsd2si,
        Cvttss2si,
        Cwd,
        Cwde,
        Daa,
        Das,
        Dec,
        Delay,
        Div,
        Divpd,
        Divps,
        Divsd,
        Divss,
        Dppd,
        Dpps,
        Emms,
        Encls,
        Enclu,
        Enclv,
        Encodekey128,
        Encodekey256,
        Endbr32,
        Endbr64,
        Enqcmd,
        Enqcmds,
        Enter,
        Extractps,
        Extrq,
        F2xm1,
        Fabs,
        Fadd,
        Faddp,
        Fbld,
        Fbstp,
        Fchs,
        Fcmovb,
        Fcmovbe,
        Fcmove,
        Fcmovnb,
        Fcmovnbe,
        Fcmovne,
        Fcmovnu,
        Fcmovu,
        Fcom,
        Fcomi,
        Fcomip,
        Fcomp,
        Fcompp,
        Fcos,
        Fdecstp,
        Fdisi8087_nop,
        Fdiv,
        Fdivp,
        Fdivr,
        Fdivrp,
        Femms,
        Feni8087_nop,
        Ffree,
        Ffreep,
        Fiadd,
        Ficom,
        Ficomp,
        Fidiv,
        Fidivr,
        Fild,
        Fimul,
        Fincstp,
        Fist,
        Fistp,
        Fisttp,
        Fisub,
        Fisubr,
        Fld,
        Fld1,
        Fldcw,
        Fldenv,
        Fldl2e,
        Fldl2t,
        Fldlg2,
        Fldln2,
        Fldpi,
        Fldz,
        Fmul,
        Fmulp,
        Fnclex,
        Fninit,
        Fnop,
        Fnsave,
        Fnstcw,
        Fnstenv,
        Fnstsw,
        Fpatan,
        Fprem,
        Fprem1,
        Fptan,
        Frndint,
        Frstor,
        Fscale,
        Fsetpm287_nop,
        Fsin,
        Fsincos,
        Fsqrt,
        Fst,
        Fstp,
        Fstpnce,
        Fsub,
        Fsubp,
        Fsubr,
        Fsubrp,
        Ftst,
        Fucom,
        Fucomi,
        Fucomip,
        Fucomp,
        Fucompp,
        Fwait,
        Fxam,
        Fxch,
        Fxrstor,
        Fxrstor64,
        Fxsave,
        Fxsave64,
        Fxtract,
        Fyl2x,
        Fyl2xp1,
        Getsec,
        Gf2p8affineinvqb,
        Gf2p8affineqb,
        Gf2p8mulb,
        Haddpd,
        Haddps,
        Hlt,
        Hreset,
        Hsubpd,
        Hsubps,
        Idiv,
        Imul,
        In,
        Inc,
        Incsspd,
        Incsspq,
        Insb,
        Insd,
        Insertps,
        Insertq,
        Insw,
        Int,
        Int1,
        Int3,
        Into,
        Invd,
        Invept,
        Invlpg,
        Invlpga,
        Invlpgb,
        Invpcid,
        Invvpid,
        Iret,
        Iretd,
        Iretq,
        Jb,
        Jbe,
        Jcxz,
        Jecxz,
        Jknzd,
        Jkzd,
        Jl,
        Jle,
        Jmp,
        Jnb,
        Jnbe,
        Jnl,
        Jnle,
        Jno,
        Jnp,
        Jns,
        Jnz,
        Jo,
        Jp,
        Jrcxz,
        Js,
        Jz,
        Kaddb,
        Kaddd,
        Kaddq,
        Kaddw,
        Kand,
        Kandb,
        Kandd,
        Kandn,
        Kandnb,
        Kandnd,
        Kandnq,
        Kandnr,
        Kandnw,
        Kandq,
        Kandw,
        Kconcath,
        Kconcatl,
        Kextract,
        Kmerge2l1h,
        Kmerge2l1l,
        Kmov,
        Kmovb,
        Kmovd,
        Kmovq,
        Kmovw,
        Knot,
        Knotb,
        Knotd,
        Knotq,
        Knotw,
        Kor,
        Korb,
        Kord,
        Korq,
        Kortest,
        Kortestb,
        Kortestd,
        Kortestq,
        Kortestw,
        Korw,
        Kshiftlb,
        Kshiftld,
        Kshiftlq,
        Kshiftlw,
        Kshiftrb,
        Kshiftrd,
        Kshiftrq,
        Kshiftrw,
        Ktestb,
        Ktestd,
        Ktestq,
        Ktestw,
        Kunpckbw,
        Kunpckdq,
        Kunpckwd,
        Kxnor,
        Kxnorb,
        Kxnord,
        Kxnorq,
        Kxnorw,
        Kxor,
        Kxorb,
        Kxord,
        Kxorq,
        Kxorw,
        Lahf,
        Lar,
        Lddqu,
        Ldmxcsr,
        Lds,
        Ldtilecfg,
        Lea,
        Leave,
        Les,
        Lfence,
        Lfs,
        Lgdt,
        Lgs,
        Lidt,
        Lldt,
        Llwpcb,
        Lmsw,
        Loadiwkey,
        Lodsb,
        Lodsd,
        Lodsq,
        Lodsw,
        Loop,
        Loope,
        Loopne,
        Lsl,
        Lss,
        Ltr,
        Lwpins,
        Lwpval,
        Lzcnt,
        Maskmovdqu,
        Maskmovq,
        Maxpd,
        Maxps,
        Maxsd,
        Maxss,
        Mcommit,
        Mfence,
        Minpd,
        Minps,
        Minsd,
        Minss,
        Monitor,
        Monitorx,
        Montmul,
        Mov,
        Movapd,
        Movaps,
        Movbe,
        Movd,
        Movddup,
        Movdir64b,
        Movdiri,
        Movdq2q,
        Movdqa,
        Movdqu,
        Movhlps,
        Movhpd,
        Movhps,
        Movlhps,
        Movlpd,
        Movlps,
        Movmskpd,
        Movmskps,
        Movntdq,
        Movntdqa,
        Movnti,
        Movntpd,
        Movntps,
        Movntq,
        Movntsd,
        Movntss,
        Movq,
        Movq2dq,
        Movsb,
        Movsd,
        Movshdup,
        Movsldup,
        Movsq,
        Movss,
        Movsw,
        Movsx,
        Movsxd,
        Movupd,
        Movups,
        Movzx,
        Mpsadbw,
        Mul,
        Mulpd,
        Mulps,
        Mulsd,
        Mulss,
        Mulx,
        Mwait,
        Mwaitx,
        Neg,
        Nop,
        Not,
        Or,
        Orpd,
        Orps,
        Out,
        Outsb,
        Outsd,
        Outsw,
        Pabsb,
        Pabsd,
        Pabsw,
        Packssdw,
        Packsswb,
        Packusdw,
        Packuswb,
        Paddb,
        Paddd,
        Paddq,
        Paddsb,
        Paddsw,
        Paddusb,
        Paddusw,
        Paddw,
        Palignr,
        Pand,
        Pandn,
        Pause,
        Pavgb,
        Pavgusb,
        Pavgw,
        Pblendvb,
        Pblendw,
        Pclmulqdq,
        Pcmpeqb,
        Pcmpeqd,
        Pcmpeqq,
        Pcmpeqw,
        Pcmpestri,
        Pcmpestrm,
        Pcmpgtb,
        Pcmpgtd,
        Pcmpgtq,
        Pcmpgtw,
        Pcmpistri,
        Pcmpistrm,
        Pconfig,
        Pdep,
        Pext,
        Pextrb,
        Pextrd,
        Pextrq,
        Pextrw,
        Pf2id,
        Pf2iw,
        Pfacc,
        Pfadd,
        Pfcmpeq,
        Pfcmpge,
        Pfcmpgt,
        Pfcpit1,
        Pfmax,
        Pfmin,
        Pfmul,
        Pfnacc,
        Pfpnacc,
        Pfrcp,
        Pfrcpit2,
        Pfrsqit1,
        Pfsqrt,
        Pfsub,
        Pfsubr,
        Phaddd,
        Phaddsw,
        Phaddw,
        Phminposuw,
        Phsubd,
        Phsubsw,
        Phsubw,
        Pi2fd,
        Pi2fw,
        Pinsrb,
        Pinsrd,
        Pinsrq,
        Pinsrw,
        Pmaddubsw,
        Pmaddwd,
        Pmaxsb,
        Pmaxsd,
        Pmaxsw,
        Pmaxub,
        Pmaxud,
        Pmaxuw,
        Pminsb,
        Pminsd,
        Pminsw,
        Pminub,
        Pminud,
        Pminuw,
        Pmovmskb,
        Pmovsxbd,
        Pmovsxbq,
        Pmovsxbw,
        Pmovsxdq,
        Pmovsxwd,
        Pmovsxwq,
        Pmovzxbd,
        Pmovzxbq,
        Pmovzxbw,
        Pmovzxdq,
        Pmovzxwd,
        Pmovzxwq,
        Pmuldq,
        Pmulhrsw,
        Pmulhrw,
        Pmulhuw,
        Pmulhw,
        Pmulld,
        Pmullw,
        Pmuludq,
        Pop,
        Popa,
        Popad,
        Popcnt,
        Popf,
        Popfd,
        Popfq,
        Por,
        Prefetch,
        Prefetchnta,
        Prefetcht0,
        Prefetcht1,
        Prefetcht2,
        Prefetchw,
        Prefetchwt1,
        Psadbw,
        Pshufb,
        Pshufd,
        Pshufhw,
        Pshuflw,
        Pshufw,
        Psignb,
        Psignd,
        Psignw,
        Pslld,
        Pslldq,
        Psllq,
        Psllw,
        Psmash,
        Psrad,
        Psraw,
        Psrld,
        Psrldq,
        Psrlq,
        Psrlw,
        Psubb,
        Psubd,
        Psubq,
        Psubsb,
        Psubsw,
        Psubusb,
        Psubusw,
        Psubw,
        Pswapd,
        Ptest,
        Ptwrite,
        Punpckhbw,
        Punpckhdq,
        Punpckhqdq,
        Punpckhwd,
        Punpcklbw,
        Punpckldq,
        Punpcklqdq,
        Punpcklwd,
        Push,
        Pusha,
        Pushad,
        Pushf,
        Pushfd,
        Pushfq,
        Pvalidate,
        Pxor,
        Rcl,
        Rcpps,
        Rcpss,
        Rcr,
        Rdfsbase,
        Rdgsbase,
        Rdmsr,
        Rdpid,
        Rdpkru,
        Rdpmc,
        Rdpru,
        Rdrand,
        Rdseed,
        Rdsspd,
        Rdsspq,
        Rdtsc,
        Rdtscp,
        Ret,
        Rmpadjust,
        Rmpupdate,
        Rol,
        Ror,
        Rorx,
        Roundpd,
        Roundps,
        Roundsd,
        Roundss,
        Rsm,
        Rsqrtps,
        Rsqrtss,
        Rstorssp,
        Sahf,
        Salc,
        Sar,
        Sarx,
        Saveprevssp,
        Sbb,
        Scasb,
        Scasd,
        Scasq,
        Scasw,
        Seamcall,
        Seamops,
        Seamret,
        Senduipi,
        Serialize,
        Setb,
        Setbe,
        Setl,
        Setle,
        Setnb,
        Setnbe,
        Setnl,
        Setnle,
        Setno,
        Setnp,
        Setns,
        Setnz,
        Seto,
        Setp,
        Sets,
        Setssbsy,
        Setz,
        Sfence,
        Sgdt,
        Sha1msg1,
        Sha1msg2,
        Sha1nexte,
        Sha1rnds4,
        Sha256msg1,
        Sha256msg2,
        Sha256rnds2,
        Shl,
        Shld,
        Shlx,
        Shr,
        Shrd,
        Shrx,
        Shufpd,
        Shufps,
        Sidt,
        Skinit,
        Sldt,
        Slwpcb,
        Smsw,
        Spflt,
        Sqrtpd,
        Sqrtps,
        Sqrtsd,
        Sqrtss,
        Stac,
        Stc,
        Std,
        Stgi,
        Sti,
        Stmxcsr,
        Stosb,
        Stosd,
        Stosq,
        Stosw,
        Str,
        Sttilecfg,
        Stui,
        Sub,
        Subpd,
        Subps,
        Subsd,
        Subss,
        Swapgs,
        Syscall,
        Sysenter,
        Sysexit,
        Sysret,
        T1mskc,
        Tdcall,
        Tdpbf16ps,
        Tdpbssd,
        Tdpbsud,
        Tdpbusd,
        Tdpbuud,
        Test,
        Testui,
        Tileloadd,
        Tileloaddt1,
        Tilerelease,
        Tilestored,
        Tilezero,
        Tlbsync,
        Tpause,
        Tzcnt,
        Tzcnti,
        Tzmsk,
        Ucomisd,
        Ucomiss,
        Ud0,
        Ud1,
        Ud2,
        Uiret,
        Umonitor,
        Umwait,
        Unpckhpd,
        Unpckhps,
        Unpcklpd,
        Unpcklps,
        V4fmaddps,
        V4fmaddss,
        V4fnmaddps,
        V4fnmaddss,
        Vaddnpd,
        Vaddnps,
        Vaddpd,
        Vaddph,
        Vaddps,
        Vaddsd,
        Vaddsetsps,
        Vaddsh,
        Vaddss,
        Vaddsubpd,
        Vaddsubps,
        Vaesdec,
        Vaesdeclast,
        Vaesenc,
        Vaesenclast,
        Vaesimc,
        Vaeskeygenassist,
        Valignd,
        Valignq,
        Vandnpd,
        Vandnps,
        Vandpd,
        Vandps,
        Vblendmpd,
        Vblendmps,
        Vblendpd,
        Vblendps,
        Vblendvpd,
        Vblendvps,
        Vbroadcastf128,
        Vbroadcastf32x2,
        Vbroadcastf32x4,
        Vbroadcastf32x8,
        Vbroadcastf64x2,
        Vbroadcastf64x4,
        Vbroadcasti128,
        Vbroadcasti32x2,
        Vbroadcasti32x4,
        Vbroadcasti32x8,
        Vbroadcasti64x2,
        Vbroadcasti64x4,
        Vbroadcastsd,
        Vbroadcastss,
        Vcmppd,
        Vcmpph,
        Vcmpps,
        Vcmpsd,
        Vcmpsh,
        Vcmpss,
        Vcomisd,
        Vcomish,
        Vcomiss,
        Vcompresspd,
        Vcompressps,
        Vcvtdq2pd,
        Vcvtdq2ph,
        Vcvtdq2ps,
        Vcvtfxpntdq2ps,
        Vcvtfxpntpd2dq,
        Vcvtfxpntpd2udq,
        Vcvtfxpntps2dq,
        Vcvtfxpntps2udq,
        Vcvtfxpntudq2ps,
        Vcvtne2ps2bf16,
        Vcvtneps2bf16,
        Vcvtpd2dq,
        Vcvtpd2ph,
        Vcvtpd2ps,
        Vcvtpd2qq,
        Vcvtpd2udq,
        Vcvtpd2uqq,
        Vcvtph2dq,
        Vcvtph2pd,
        Vcvtph2ps,
        Vcvtph2psx,
        Vcvtph2qq,
        Vcvtph2udq,
        Vcvtph2uqq,
        Vcvtph2uw,
        Vcvtph2w,
        Vcvtps2dq,
        Vcvtps2pd,
        Vcvtps2ph,
        Vcvtps2phx,
        Vcvtps2qq,
        Vcvtps2udq,
        Vcvtps2uqq,
        Vcvtqq2pd,
        Vcvtqq2ph,
        Vcvtqq2ps,
        Vcvtsd2sh,
        Vcvtsd2si,
        Vcvtsd2ss,
        Vcvtsd2usi,
        Vcvtsh2sd,
        Vcvtsh2si,
        Vcvtsh2ss,
        Vcvtsh2usi,
        Vcvtsi2sd,
        Vcvtsi2sh,
        Vcvtsi2ss,
        Vcvtss2sd,
        Vcvtss2sh,
        Vcvtss2si,
        Vcvtss2usi,
        Vcvttpd2dq,
        Vcvttpd2qq,
        Vcvttpd2udq,
        Vcvttpd2uqq,
        Vcvttph2dq,
        Vcvttph2qq,
        Vcvttph2udq,
        Vcvttph2uqq,
        Vcvttph2uw,
        Vcvttph2w,
        Vcvttps2dq,
        Vcvttps2qq,
        Vcvttps2udq,
        Vcvttps2uqq,
        Vcvttsd2si,
        Vcvttsd2usi,
        Vcvttsh2si,
        Vcvttsh2usi,
        Vcvttss2si,
        Vcvttss2usi,
        Vcvtudq2pd,
        Vcvtudq2ph,
        Vcvtudq2ps,
        Vcvtuqq2pd,
        Vcvtuqq2ph,
        Vcvtuqq2ps,
        Vcvtusi2sd,
        Vcvtusi2sh,
        Vcvtusi2ss,
        Vcvtuw2ph,
        Vcvtw2ph,
        Vdbpsadbw,
        Vdivpd,
        Vdivph,
        Vdivps,
        Vdivsd,
        Vdivsh,
        Vdivss,
        Vdpbf16ps,
        Vdppd,
        Vdpps,
        Verr,
        Verw,
        Vexp223ps,
        Vexp2pd,
        Vexp2ps,
        Vexpandpd,
        Vexpandps,
        Vextractf128,
        Vextractf32x4,
        Vextractf32x8,
        Vextractf64x2,
        Vextractf64x4,
        Vextracti128,
        Vextracti32x4,
        Vextracti32x8,
        Vextracti64x2,
        Vextracti64x4,
        Vextractps,
        Vfcmaddcph,
        Vfcmaddcsh,
        Vfcmulcph,
        Vfcmulcsh,
        Vfixupimmpd,
        Vfixupimmps,
        Vfixupimmsd,
        Vfixupimmss,
        Vfixupnanpd,
        Vfixupnanps,
        Vfmadd132pd,
        Vfmadd132ph,
        Vfmadd132ps,
        Vfmadd132sd,
        Vfmadd132sh,
        Vfmadd132ss,
        Vfmadd213pd,
        Vfmadd213ph,
        Vfmadd213ps,
        Vfmadd213sd,
        Vfmadd213sh,
        Vfmadd213ss,
        Vfmadd231pd,
        Vfmadd231ph,
        Vfmadd231ps,
        Vfmadd231sd,
        Vfmadd231sh,
        Vfmadd231ss,
        Vfmadd233ps,
        Vfmaddcph,
        Vfmaddcsh,
        Vfmaddpd,
        Vfmaddps,
        Vfmaddsd,
        Vfmaddss,
        Vfmaddsub132pd,
        Vfmaddsub132ph,
        Vfmaddsub132ps,
        Vfmaddsub213pd,
        Vfmaddsub213ph,
        Vfmaddsub213ps,
        Vfmaddsub231pd,
        Vfmaddsub231ph,
        Vfmaddsub231ps,
        Vfmaddsubpd,
        Vfmaddsubps,
        Vfmsub132pd,
        Vfmsub132ph,
        Vfmsub132ps,
        Vfmsub132sd,
        Vfmsub132sh,
        Vfmsub132ss,
        Vfmsub213pd,
        Vfmsub213ph,
        Vfmsub213ps,
        Vfmsub213sd,
        Vfmsub213sh,
        Vfmsub213ss,
        Vfmsub231pd,
        Vfmsub231ph,
        Vfmsub231ps,
        Vfmsub231sd,
        Vfmsub231sh,
        Vfmsub231ss,
        Vfmsubadd132pd,
        Vfmsubadd132ph,
        Vfmsubadd132ps,
        Vfmsubadd213pd,
        Vfmsubadd213ph,
        Vfmsubadd213ps,
        Vfmsubadd231pd,
        Vfmsubadd231ph,
        Vfmsubadd231ps,
        Vfmsubaddpd,
        Vfmsubaddps,
        Vfmsubpd,
        Vfmsubps,
        Vfmsubsd,
        Vfmsubss,
        Vfmulcph,
        Vfmulcsh,
        Vfnmadd132pd,
        Vfnmadd132ph,
        Vfnmadd132ps,
        Vfnmadd132sd,
        Vfnmadd132sh,
        Vfnmadd132ss,
        Vfnmadd213pd,
        Vfnmadd213ph,
        Vfnmadd213ps,
        Vfnmadd213sd,
        Vfnmadd213sh,
        Vfnmadd213ss,
        Vfnmadd231pd,
        Vfnmadd231ph,
        Vfnmadd231ps,
        Vfnmadd231sd,
        Vfnmadd231sh,
        Vfnmadd231ss,
        Vfnmaddpd,
        Vfnmaddps,
        Vfnmaddsd,
        Vfnmaddss,
        Vfnmsub132pd,
        Vfnmsub132ph,
        Vfnmsub132ps,
        Vfnmsub132sd,
        Vfnmsub132sh,
        Vfnmsub132ss,
        Vfnmsub213pd,
        Vfnmsub213ph,
        Vfnmsub213ps,
        Vfnmsub213sd,
        Vfnmsub213sh,
        Vfnmsub213ss,
        Vfnmsub231pd,
        Vfnmsub231ph,
        Vfnmsub231ps,
        Vfnmsub231sd,
        Vfnmsub231sh,
        Vfnmsub231ss,
        Vfnmsubpd,
        Vfnmsubps,
        Vfnmsubsd,
        Vfnmsubss,
        Vfpclasspd,
        Vfpclassph,
        Vfpclassps,
        Vfpclasssd,
        Vfpclasssh,
        Vfpclassss,
        Vfrczpd,
        Vfrczps,
        Vfrczsd,
        Vfrczss,
        Vgatherdpd,
        Vgatherdps,
        Vgatherpf0dpd,
        Vgatherpf0dps,
        Vgatherpf0hintdpd,
        Vgatherpf0hintdps,
        Vgatherpf0qpd,
        Vgatherpf0qps,
        Vgatherpf1dpd,
        Vgatherpf1dps,
        Vgatherpf1qpd,
        Vgatherpf1qps,
        Vgatherqpd,
        Vgatherqps,
        Vgetexppd,
        Vgetexpph,
        Vgetexpps,
        Vgetexpsd,
        Vgetexpsh,
        Vgetexpss,
        Vgetmantpd,
        Vgetmantph,
        Vgetmantps,
        Vgetmantsd,
        Vgetmantsh,
        Vgetmantss,
        Vgf2p8affineinvqb,
        Vgf2p8affineqb,
        Vgf2p8mulb,
        Vgmaxabsps,
        Vgmaxpd,
        Vgmaxps,
        Vgminpd,
        Vgminps,
        Vhaddpd,
        Vhaddps,
        Vhsubpd,
        Vhsubps,
        Vinsertf128,
        Vinsertf32x4,
        Vinsertf32x8,
        Vinsertf64x2,
        Vinsertf64x4,
        Vinserti128,
        Vinserti32x4,
        Vinserti32x8,
        Vinserti64x2,
        Vinserti64x4,
        Vinsertps,
        Vlddqu,
        Vldmxcsr,
        Vloadunpackhd,
        Vloadunpackhpd,
        Vloadunpackhps,
        Vloadunpackhq,
        Vloadunpackld,
        Vloadunpacklpd,
        Vloadunpacklps,
        Vloadunpacklq,
        Vlog2ps,
        Vmaskmovdqu,
        Vmaskmovpd,
        Vmaskmovps,
        Vmaxpd,
        Vmaxph,
        Vmaxps,
        Vmaxsd,
        Vmaxsh,
        Vmaxss,
        Vmcall,
        Vmclear,
        Vmfunc,
        Vminpd,
        Vminph,
        Vminps,
        Vminsd,
        Vminsh,
        Vminss,
        Vmlaunch,
        Vmload,
        Vmmcall,
        Vmovapd,
        Vmovaps,
        Vmovd,
        Vmovddup,
        Vmovdqa,
        Vmovdqa32,
        Vmovdqa64,
        Vmovdqu,
        Vmovdqu16,
        Vmovdqu32,
        Vmovdqu64,
        Vmovdqu8,
        Vmovhlps,
        Vmovhpd,
        Vmovhps,
        Vmovlhps,
        Vmovlpd,
        Vmovlps,
        Vmovmskpd,
        Vmovmskps,
        Vmovnrapd,
        Vmovnraps,
        Vmovnrngoapd,
        Vmovnrngoaps,
        Vmovntdq,
        Vmovntdqa,
        Vmovntpd,
        Vmovntps,
        Vmovq,
        Vmovsd,
        Vmovsh,
        Vmovshdup,
        Vmovsldup,
        Vmovss,
        Vmovupd,
        Vmovups,
        Vmovw,
        Vmpsadbw,
        Vmptrld,
        Vmptrst,
        Vmread,
        Vmresume,
        Vmrun,
        Vmsave,
        Vmulpd,
        Vmulph,
        Vmulps,
        Vmulsd,
        Vmulsh,
        Vmulss,
        Vmwrite,
        Vmxoff,
        Vmxon,
        Vorpd,
        Vorps,
        Vp2intersectd,
        Vp2intersectq,
        Vp4dpwssd,
        Vp4dpwssds,
        Vpabsb,
        Vpabsd,
        Vpabsq,
        Vpabsw,
        Vpackssdw,
        Vpacksswb,
        Vpackstorehd,
        Vpackstorehpd,
        Vpackstorehps,
        Vpackstorehq,
        Vpackstoreld,
        Vpackstorelpd,
        Vpackstorelps,
        Vpackstorelq,
        Vpackusdw,
        Vpackuswb,
        Vpadcd,
        Vpaddb,
        Vpaddd,
        Vpaddq,
        Vpaddsb,
        Vpaddsetcd,
        Vpaddsetsd,
        Vpaddsw,
        Vpaddusb,
        Vpaddusw,
        Vpaddw,
        Vpalignr,
        Vpand,
        Vpandd,
        Vpandn,
        Vpandnd,
        Vpandnq,
        Vpandq,
        Vpavgb,
        Vpavgw,
        Vpblendd,
        Vpblendmb,
        Vpblendmd,
        Vpblendmq,
        Vpblendmw,
        Vpblendvb,
        Vpblendw,
        Vpbroadcastb,
        Vpbroadcastd,
        Vpbroadcastmb2q,
        Vpbroadcastmw2d,
        Vpbroadcastq,
        Vpbroadcastw,
        Vpclmulqdq,
        Vpcmov,
        Vpcmpb,
        Vpcmpd,
        Vpcmpeqb,
        Vpcmpeqd,
        Vpcmpeqq,
        Vpcmpeqw,
        Vpcmpestri,
        Vpcmpestrm,
        Vpcmpgtb,
        Vpcmpgtd,
        Vpcmpgtq,
        Vpcmpgtw,
        Vpcmpistri,
        Vpcmpistrm,
        Vpcmpltd,
        Vpcmpq,
        Vpcmpub,
        Vpcmpud,
        Vpcmpuq,
        Vpcmpuw,
        Vpcmpw,
        Vpcomb,
        Vpcomd,
        Vpcompressb,
        Vpcompressd,
        Vpcompressq,
        Vpcompressw,
        Vpcomq,
        Vpcomub,
        Vpcomud,
        Vpcomuq,
        Vpcomuw,
        Vpcomw,
        Vpconflictd,
        Vpconflictq,
        Vpdpbusd,
        Vpdpbusds,
        Vpdpwssd,
        Vpdpwssds,
        Vperm2f128,
        Vperm2i128,
        Vpermb,
        Vpermd,
        Vpermf32x4,
        Vpermi2b,
        Vpermi2d,
        Vpermi2pd,
        Vpermi2ps,
        Vpermi2q,
        Vpermi2w,
        Vpermil2pd,
        Vpermil2ps,
        Vpermilpd,
        Vpermilps,
        Vpermpd,
        Vpermps,
        Vpermq,
        Vpermt2b,
        Vpermt2d,
        Vpermt2pd,
        Vpermt2ps,
        Vpermt2q,
        Vpermt2w,
        Vpermw,
        Vpexpandb,
        Vpexpandd,
        Vpexpandq,
        Vpexpandw,
        Vpextrb,
        Vpextrd,
        Vpextrq,
        Vpextrw,
        Vpgatherdd,
        Vpgatherdq,
        Vpgatherqd,
        Vpgatherqq,
        Vphaddbd,
        Vphaddbq,
        Vphaddbw,
        Vphaddd,
        Vphadddq,
        Vphaddsw,
        Vphaddubd,
        Vphaddubq,
        Vphaddubw,
        Vphaddudq,
        Vphadduwd,
        Vphadduwq,
        Vphaddw,
        Vphaddwd,
        Vphaddwq,
        Vphminposuw,
        Vphsubbw,
        Vphsubd,
        Vphsubdq,
        Vphsubsw,
        Vphsubw,
        Vphsubwd,
        Vpinsrb,
        Vpinsrd,
        Vpinsrq,
        Vpinsrw,
        Vplzcntd,
        Vplzcntq,
        Vpmacsdd,
        Vpmacsdqh,
        Vpmacsdql,
        Vpmacssdd,
        Vpmacssdqh,
        Vpmacssdql,
        Vpmacsswd,
        Vpmacssww,
        Vpmacswd,
        Vpmacsww,
        Vpmadcsswd,
        Vpmadcswd,
        Vpmadd231d,
        Vpmadd233d,
        Vpmadd52huq,
        Vpmadd52luq,
        Vpmaddubsw,
        Vpmaddwd,
        Vpmaskmovd,
        Vpmaskmovq,
        Vpmaxsb,
        Vpmaxsd,
        Vpmaxsq,
        Vpmaxsw,
        Vpmaxub,
        Vpmaxud,
        Vpmaxuq,
        Vpmaxuw,
        Vpminsb,
        Vpminsd,
        Vpminsq,
        Vpminsw,
        Vpminub,
        Vpminud,
        Vpminuq,
        Vpminuw,
        Vpmovb2m,
        Vpmovd2m,
        Vpmovdb,
        Vpmovdw,
        Vpmovm2b,
        Vpmovm2d,
        Vpmovm2q,
        Vpmovm2w,
        Vpmovmskb,
        Vpmovq2m,
        Vpmovqb,
        Vpmovqd,
        Vpmovqw,
        Vpmovsdb,
        Vpmovsdw,
        Vpmovsqb,
        Vpmovsqd,
        Vpmovsqw,
        Vpmovswb,
        Vpmovsxbd,
        Vpmovsxbq,
        Vpmovsxbw,
        Vpmovsxdq,
        Vpmovsxwd,
        Vpmovsxwq,
        Vpmovusdb,
        Vpmovusdw,
        Vpmovusqb,
        Vpmovusqd,
        Vpmovusqw,
        Vpmovuswb,
        Vpmovw2m,
        Vpmovwb,
        Vpmovzxbd,
        Vpmovzxbq,
        Vpmovzxbw,
        Vpmovzxdq,
        Vpmovzxwd,
        Vpmovzxwq,
        Vpmuldq,
        Vpmulhd,
        Vpmulhrsw,
        Vpmulhud,
        Vpmulhuw,
        Vpmulhw,
        Vpmulld,
        Vpmullq,
        Vpmullw,
        Vpmultishiftqb,
        Vpmuludq,
        Vpopcntb,
        Vpopcntd,
        Vpopcntq,
        Vpopcntw,
        Vpor,
        Vpord,
        Vporq,
        Vpperm,
        Vprefetch0,
        Vprefetch1,
        Vprefetch2,
        Vprefetche0,
        Vprefetche1,
        Vprefetche2,
        Vprefetchenta,
        Vprefetchnta,
        Vprold,
        Vprolq,
        Vprolvd,
        Vprolvq,
        Vprord,
        Vprorq,
        Vprorvd,
        Vprorvq,
        Vprotb,
        Vprotd,
        Vprotq,
        Vprotw,
        Vpsadbw,
        Vpsbbd,
        Vpsbbrd,
        Vpscatterdd,
        Vpscatterdq,
        Vpscatterqd,
        Vpscatterqq,
        Vpshab,
        Vpshad,
        Vpshaq,
        Vpshaw,
        Vpshlb,
        Vpshld,
        Vpshldd,
        Vpshldq,
        Vpshldvd,
        Vpshldvq,
        Vpshldvw,
        Vpshldw,
        Vpshlq,
        Vpshlw,
        Vpshrdd,
        Vpshrdq,
        Vpshrdvd,
        Vpshrdvq,
        Vpshrdvw,
        Vpshrdw,
        Vpshufb,
        Vpshufbitqmb,
        Vpshufd,
        Vpshufhw,
        Vpshuflw,
        Vpsignb,
        Vpsignd,
        Vpsignw,
        Vpslld,
        Vpslldq,
        Vpsllq,
        Vpsllvd,
        Vpsllvq,
        Vpsllvw,
        Vpsllw,
        Vpsrad,
        Vpsraq,
        Vpsravd,
        Vpsravq,
        Vpsravw,
        Vpsraw,
        Vpsrld,
        Vpsrldq,
        Vpsrlq,
        Vpsrlvd,
        Vpsrlvq,
        Vpsrlvw,
        Vpsrlw,
        Vpsubb,
        Vpsubd,
        Vpsubq,
        Vpsubrd,
        Vpsubrsetbd,
        Vpsubsb,
        Vpsubsetbd,
        Vpsubsw,
        Vpsubusb,
        Vpsubusw,
        Vpsubw,
        Vpternlogd,
        Vpternlogq,
        Vptest,
        Vptestmb,
        Vptestmd,
        Vptestmq,
        Vptestmw,
        Vptestnmb,
        Vptestnmd,
        Vptestnmq,
        Vptestnmw,
        Vpunpckhbw,
        Vpunpckhdq,
        Vpunpckhqdq,
        Vpunpckhwd,
        Vpunpcklbw,
        Vpunpckldq,
        Vpunpcklqdq,
        Vpunpcklwd,
        Vpxor,
        Vpxord,
        Vpxorq,
        Vrangepd,
        Vrangeps,
        Vrangesd,
        Vrangess,
        Vrcp14pd,
        Vrcp14ps,
        Vrcp14sd,
        Vrcp14ss,
        Vrcp23ps,
        Vrcp28pd,
        Vrcp28ps,
        Vrcp28sd,
        Vrcp28ss,
        Vrcpph,
        Vrcpps,
        Vrcpsh,
        Vrcpss,
        Vreducepd,
        Vreduceph,
        Vreduceps,
        Vreducesd,
        Vreducesh,
        Vreducess,
        Vrndfxpntpd,
        Vrndfxpntps,
        Vrndscalepd,
        Vrndscaleph,
        Vrndscaleps,
        Vrndscalesd,
        Vrndscalesh,
        Vrndscaless,
        Vroundpd,
        Vroundps,
        Vroundsd,
        Vroundss,
        Vrsqrt14pd,
        Vrsqrt14ps,
        Vrsqrt14sd,
        Vrsqrt14ss,
        Vrsqrt23ps,
        Vrsqrt28pd,
        Vrsqrt28ps,
        Vrsqrt28sd,
        Vrsqrt28ss,
        Vrsqrtph,
        Vrsqrtps,
        Vrsqrtsh,
        Vrsqrtss,
        Vscalefpd,
        Vscalefph,
        Vscalefps,
        Vscalefsd,
        Vscalefsh,
        Vscalefss,
        Vscaleps,
        Vscatterdpd,
        Vscatterdps,
        Vscatterpf0dpd,
        Vscatterpf0dps,
        Vscatterpf0hintdpd,
        Vscatterpf0hintdps,
        Vscatterpf0qpd,
        Vscatterpf0qps,
        Vscatterpf1dpd,
        Vscatterpf1dps,
        Vscatterpf1qpd,
        Vscatterpf1qps,
        Vscatterqpd,
        Vscatterqps,
        Vshuff32x4,
        Vshuff64x2,
        Vshufi32x4,
        Vshufi64x2,
        Vshufpd,
        Vshufps,
        Vsqrtpd,
        Vsqrtph,
        Vsqrtps,
        Vsqrtsd,
        Vsqrtsh,
        Vsqrtss,
        Vstmxcsr,
        Vsubpd,
        Vsubph,
        Vsubps,
        Vsubrpd,
        Vsubrps,
        Vsubsd,
        Vsubsh,
        Vsubss,
        Vtestpd,
        Vtestps,
        Vucomisd,
        Vucomish,
        Vucomiss,
        Vunpckhpd,
        Vunpckhps,
        Vunpcklpd,
        Vunpcklps,
        Vxorpd,
        Vxorps,
        Vzeroall,
        Vzeroupper,
        Wbinvd,
        Wrfsbase,
        Wrgsbase,
        Wrmsr,
        Wrpkru,
        Wrssd,
        Wrssq,
        Wrussd,
        Wrussq,
        Xabort,
        Xadd,
        Xbegin,
        Xchg,
        Xcrypt_cbc,
        Xcrypt_cfb,
        Xcrypt_ctr,
        Xcrypt_ecb,
        Xcrypt_ofb,
        Xend,
        Xgetbv,
        Xlat,
        Xor,
        Xorpd,
        Xorps,
        Xresldtrk,
        Xrstor,
        Xrstor64,
        Xrstors,
        Xrstors64,
        Xsave,
        Xsave64,
        Xsavec,
        Xsavec64,
        Xsaveopt,
        Xsaveopt64,
        Xsaves,
        Xsaves64,
        Xsetbv,
        Xsha1,
        Xsha256,
        Xstore,
        Xsusldtrk,
        Xtest,
    };

    constexpr const char* MnemonicGetString(Mnemonic mnemonic)
    {
        switch (mnemonic)
        {
        case Mnemonic::Invalid:
            return "invalid";
        case Mnemonic::Aaa:
            return "aaa";
        case Mnemonic::Aad:
            return "aad";
        case Mnemonic::Aam:
            return "aam";
        case Mnemonic::Aas:
            return "aas";
        case Mnemonic::Adc:
            return "adc";
        case Mnemonic::Adcx:
            return "adcx";
        case Mnemonic::Add:
            return "add";
        case Mnemonic::Addpd:
            return "addpd";
        case Mnemonic::Addps:
            return "addps";
        case Mnemonic::Addsd:
            return "addsd";
        case Mnemonic::Addss:
            return "addss";
        case Mnemonic::Addsubpd:
            return "addsubpd";
        case Mnemonic::Addsubps:
            return "addsubps";
        case Mnemonic::Adox:
            return "adox";
        case Mnemonic::Aesdec:
            return "aesdec";
        case Mnemonic::Aesdec128kl:
            return "aesdec128kl";
        case Mnemonic::Aesdec256kl:
            return "aesdec256kl";
        case Mnemonic::Aesdeclast:
            return "aesdeclast";
        case Mnemonic::Aesdecwide128kl:
            return "aesdecwide128kl";
        case Mnemonic::Aesdecwide256kl:
            return "aesdecwide256kl";
        case Mnemonic::Aesenc:
            return "aesenc";
        case Mnemonic::Aesenc128kl:
            return "aesenc128kl";
        case Mnemonic::Aesenc256kl:
            return "aesenc256kl";
        case Mnemonic::Aesenclast:
            return "aesenclast";
        case Mnemonic::Aesencwide128kl:
            return "aesencwide128kl";
        case Mnemonic::Aesencwide256kl:
            return "aesencwide256kl";
        case Mnemonic::Aesimc:
            return "aesimc";
        case Mnemonic::Aeskeygenassist:
            return "aeskeygenassist";
        case Mnemonic::And:
            return "and";
        case Mnemonic::Andn:
            return "andn";
        case Mnemonic::Andnpd:
            return "andnpd";
        case Mnemonic::Andnps:
            return "andnps";
        case Mnemonic::Andpd:
            return "andpd";
        case Mnemonic::Andps:
            return "andps";
        case Mnemonic::Arpl:
            return "arpl";
        case Mnemonic::Bextr:
            return "bextr";
        case Mnemonic::Blcfill:
            return "blcfill";
        case Mnemonic::Blci:
            return "blci";
        case Mnemonic::Blcic:
            return "blcic";
        case Mnemonic::Blcmsk:
            return "blcmsk";
        case Mnemonic::Blcs:
            return "blcs";
        case Mnemonic::Blendpd:
            return "blendpd";
        case Mnemonic::Blendps:
            return "blendps";
        case Mnemonic::Blendvpd:
            return "blendvpd";
        case Mnemonic::Blendvps:
            return "blendvps";
        case Mnemonic::Blsfill:
            return "blsfill";
        case Mnemonic::Blsi:
            return "blsi";
        case Mnemonic::Blsic:
            return "blsic";
        case Mnemonic::Blsmsk:
            return "blsmsk";
        case Mnemonic::Blsr:
            return "blsr";
        case Mnemonic::Bndcl:
            return "bndcl";
        case Mnemonic::Bndcn:
            return "bndcn";
        case Mnemonic::Bndcu:
            return "bndcu";
        case Mnemonic::Bndldx:
            return "bndldx";
        case Mnemonic::Bndmk:
            return "bndmk";
        case Mnemonic::Bndmov:
            return "bndmov";
        case Mnemonic::Bndstx:
            return "bndstx";
        case Mnemonic::Bound:
            return "bound";
        case Mnemonic::Bsf:
            return "bsf";
        case Mnemonic::Bsr:
            return "bsr";
        case Mnemonic::Bswap:
            return "bswap";
        case Mnemonic::Bt:
            return "bt";
        case Mnemonic::Btc:
            return "btc";
        case Mnemonic::Btr:
            return "btr";
        case Mnemonic::Bts:
            return "bts";
        case Mnemonic::Bzhi:
            return "bzhi";
        case Mnemonic::Call:
            return "call";
        case Mnemonic::Cbw:
            return "cbw";
        case Mnemonic::Cdq:
            return "cdq";
        case Mnemonic::Cdqe:
            return "cdqe";
        case Mnemonic::Clac:
            return "clac";
        case Mnemonic::Clc:
            return "clc";
        case Mnemonic::Cld:
            return "cld";
        case Mnemonic::Cldemote:
            return "cldemote";
        case Mnemonic::Clevict0:
            return "clevict0";
        case Mnemonic::Clevict1:
            return "clevict1";
        case Mnemonic::Clflush:
            return "clflush";
        case Mnemonic::Clflushopt:
            return "clflushopt";
        case Mnemonic::Clgi:
            return "clgi";
        case Mnemonic::Cli:
            return "cli";
        case Mnemonic::Clrssbsy:
            return "clrssbsy";
        case Mnemonic::Clts:
            return "clts";
        case Mnemonic::Clui:
            return "clui";
        case Mnemonic::Clwb:
            return "clwb";
        case Mnemonic::Clzero:
            return "clzero";
        case Mnemonic::Cmc:
            return "cmc";
        case Mnemonic::Cmovb:
            return "cmovb";
        case Mnemonic::Cmovbe:
            return "cmovbe";
        case Mnemonic::Cmovl:
            return "cmovl";
        case Mnemonic::Cmovle:
            return "cmovle";
        case Mnemonic::Cmovnb:
            return "cmovnb";
        case Mnemonic::Cmovnbe:
            return "cmovnbe";
        case Mnemonic::Cmovnl:
            return "cmovnl";
        case Mnemonic::Cmovnle:
            return "cmovnle";
        case Mnemonic::Cmovno:
            return "cmovno";
        case Mnemonic::Cmovnp:
            return "cmovnp";
        case Mnemonic::Cmovns:
            return "cmovns";
        case Mnemonic::Cmovnz:
            return "cmovnz";
        case Mnemonic::Cmovo:
            return "cmovo";
        case Mnemonic::Cmovp:
            return "cmovp";
        case Mnemonic::Cmovs:
            return "cmovs";
        case Mnemonic::Cmovz:
            return "cmovz";
        case Mnemonic::Cmp:
            return "cmp";
        case Mnemonic::Cmppd:
            return "cmppd";
        case Mnemonic::Cmpps:
            return "cmpps";
        case Mnemonic::Cmpsb:
            return "cmpsb";
        case Mnemonic::Cmpsd:
            return "cmpsd";
        case Mnemonic::Cmpsq:
            return "cmpsq";
        case Mnemonic::Cmpss:
            return "cmpss";
        case Mnemonic::Cmpsw:
            return "cmpsw";
        case Mnemonic::Cmpxchg:
            return "cmpxchg";
        case Mnemonic::Cmpxchg16b:
            return "cmpxchg16b";
        case Mnemonic::Cmpxchg8b:
            return "cmpxchg8b";
        case Mnemonic::Comisd:
            return "comisd";
        case Mnemonic::Comiss:
            return "comiss";
        case Mnemonic::Cpuid:
            return "cpuid";
        case Mnemonic::Cqo:
            return "cqo";
        case Mnemonic::Crc32:
            return "crc32";
        case Mnemonic::Cvtdq2pd:
            return "cvtdq2pd";
        case Mnemonic::Cvtdq2ps:
            return "cvtdq2ps";
        case Mnemonic::Cvtpd2dq:
            return "cvtpd2dq";
        case Mnemonic::Cvtpd2pi:
            return "cvtpd2pi";
        case Mnemonic::Cvtpd2ps:
            return "cvtpd2ps";
        case Mnemonic::Cvtpi2pd:
            return "cvtpi2pd";
        case Mnemonic::Cvtpi2ps:
            return "cvtpi2ps";
        case Mnemonic::Cvtps2dq:
            return "cvtps2dq";
        case Mnemonic::Cvtps2pd:
            return "cvtps2pd";
        case Mnemonic::Cvtps2pi:
            return "cvtps2pi";
        case Mnemonic::Cvtsd2si:
            return "cvtsd2si";
        case Mnemonic::Cvtsd2ss:
            return "cvtsd2ss";
        case Mnemonic::Cvtsi2sd:
            return "cvtsi2sd";
        case Mnemonic::Cvtsi2ss:
            return "cvtsi2ss";
        case Mnemonic::Cvtss2sd:
            return "cvtss2sd";
        case Mnemonic::Cvtss2si:
            return "cvtss2si";
        case Mnemonic::Cvttpd2dq:
            return "cvttpd2dq";
        case Mnemonic::Cvttpd2pi:
            return "cvttpd2pi";
        case Mnemonic::Cvttps2dq:
            return "cvttps2dq";
        case Mnemonic::Cvttps2pi:
            return "cvttps2pi";
        case Mnemonic::Cvttsd2si:
            return "cvttsd2si";
        case Mnemonic::Cvttss2si:
            return "cvttss2si";
        case Mnemonic::Cwd:
            return "cwd";
        case Mnemonic::Cwde:
            return "cwde";
        case Mnemonic::Daa:
            return "daa";
        case Mnemonic::Das:
            return "das";
        case Mnemonic::Dec:
            return "dec";
        case Mnemonic::Delay:
            return "delay";
        case Mnemonic::Div:
            return "div";
        case Mnemonic::Divpd:
            return "divpd";
        case Mnemonic::Divps:
            return "divps";
        case Mnemonic::Divsd:
            return "divsd";
        case Mnemonic::Divss:
            return "divss";
        case Mnemonic::Dppd:
            return "dppd";
        case Mnemonic::Dpps:
            return "dpps";
        case Mnemonic::Emms:
            return "emms";
        case Mnemonic::Encls:
            return "encls";
        case Mnemonic::Enclu:
            return "enclu";
        case Mnemonic::Enclv:
            return "enclv";
        case Mnemonic::Encodekey128:
            return "encodekey128";
        case Mnemonic::Encodekey256:
            return "encodekey256";
        case Mnemonic::Endbr32:
            return "endbr32";
        case Mnemonic::Endbr64:
            return "endbr64";
        case Mnemonic::Enqcmd:
            return "enqcmd";
        case Mnemonic::Enqcmds:
            return "enqcmds";
        case Mnemonic::Enter:
            return "enter";
        case Mnemonic::Extractps:
            return "extractps";
        case Mnemonic::Extrq:
            return "extrq";
        case Mnemonic::F2xm1:
            return "f2xm1";
        case Mnemonic::Fabs:
            return "fabs";
        case Mnemonic::Fadd:
            return "fadd";
        case Mnemonic::Faddp:
            return "faddp";
        case Mnemonic::Fbld:
            return "fbld";
        case Mnemonic::Fbstp:
            return "fbstp";
        case Mnemonic::Fchs:
            return "fchs";
        case Mnemonic::Fcmovb:
            return "fcmovb";
        case Mnemonic::Fcmovbe:
            return "fcmovbe";
        case Mnemonic::Fcmove:
            return "fcmove";
        case Mnemonic::Fcmovnb:
            return "fcmovnb";
        case Mnemonic::Fcmovnbe:
            return "fcmovnbe";
        case Mnemonic::Fcmovne:
            return "fcmovne";
        case Mnemonic::Fcmovnu:
            return "fcmovnu";
        case Mnemonic::Fcmovu:
            return "fcmovu";
        case Mnemonic::Fcom:
            return "fcom";
        case Mnemonic::Fcomi:
            return "fcomi";
        case Mnemonic::Fcomip:
            return "fcomip";
        case Mnemonic::Fcomp:
            return "fcomp";
        case Mnemonic::Fcompp:
            return "fcompp";
        case Mnemonic::Fcos:
            return "fcos";
        case Mnemonic::Fdecstp:
            return "fdecstp";
        case Mnemonic::Fdisi8087_nop:
            return "fdisi8087_nop";
        case Mnemonic::Fdiv:
            return "fdiv";
        case Mnemonic::Fdivp:
            return "fdivp";
        case Mnemonic::Fdivr:
            return "fdivr";
        case Mnemonic::Fdivrp:
            return "fdivrp";
        case Mnemonic::Femms:
            return "femms";
        case Mnemonic::Feni8087_nop:
            return "feni8087_nop";
        case Mnemonic::Ffree:
            return "ffree";
        case Mnemonic::Ffreep:
            return "ffreep";
        case Mnemonic::Fiadd:
            return "fiadd";
        case Mnemonic::Ficom:
            return "ficom";
        case Mnemonic::Ficomp:
            return "ficomp";
        case Mnemonic::Fidiv:
            return "fidiv";
        case Mnemonic::Fidivr:
            return "fidivr";
        case Mnemonic::Fild:
            return "fild";
        case Mnemonic::Fimul:
            return "fimul";
        case Mnemonic::Fincstp:
            return "fincstp";
        case Mnemonic::Fist:
            return "fist";
        case Mnemonic::Fistp:
            return "fistp";
        case Mnemonic::Fisttp:
            return "fisttp";
        case Mnemonic::Fisub:
            return "fisub";
        case Mnemonic::Fisubr:
            return "fisubr";
        case Mnemonic::Fld:
            return "fld";
        case Mnemonic::Fld1:
            return "fld1";
        case Mnemonic::Fldcw:
            return "fldcw";
        case Mnemonic::Fldenv:
            return "fldenv";
        case Mnemonic::Fldl2e:
            return "fldl2e";
        case Mnemonic::Fldl2t:
            return "fldl2t";
        case Mnemonic::Fldlg2:
            return "fldlg2";
        case Mnemonic::Fldln2:
            return "fldln2";
        case Mnemonic::Fldpi:
            return "fldpi";
        case Mnemonic::Fldz:
            return "fldz";
        case Mnemonic::Fmul:
            return "fmul";
        case Mnemonic::Fmulp:
            return "fmulp";
        case Mnemonic::Fnclex:
            return "fnclex";
        case Mnemonic::Fninit:
            return "fninit";
        case Mnemonic::Fnop:
            return "fnop";
        case Mnemonic::Fnsave:
            return "fnsave";
        case Mnemonic::Fnstcw:
            return "fnstcw";
        case Mnemonic::Fnstenv:
            return "fnstenv";
        case Mnemonic::Fnstsw:
            return "fnstsw";
        case Mnemonic::Fpatan:
            return "fpatan";
        case Mnemonic::Fprem:
            return "fprem";
        case Mnemonic::Fprem1:
            return "fprem1";
        case Mnemonic::Fptan:
            return "fptan";
        case Mnemonic::Frndint:
            return "frndint";
        case Mnemonic::Frstor:
            return "frstor";
        case Mnemonic::Fscale:
            return "fscale";
        case Mnemonic::Fsetpm287_nop:
            return "fsetpm287_nop";
        case Mnemonic::Fsin:
            return "fsin";
        case Mnemonic::Fsincos:
            return "fsincos";
        case Mnemonic::Fsqrt:
            return "fsqrt";
        case Mnemonic::Fst:
            return "fst";
        case Mnemonic::Fstp:
            return "fstp";
        case Mnemonic::Fstpnce:
            return "fstpnce";
        case Mnemonic::Fsub:
            return "fsub";
        case Mnemonic::Fsubp:
            return "fsubp";
        case Mnemonic::Fsubr:
            return "fsubr";
        case Mnemonic::Fsubrp:
            return "fsubrp";
        case Mnemonic::Ftst:
            return "ftst";
        case Mnemonic::Fucom:
            return "fucom";
        case Mnemonic::Fucomi:
            return "fucomi";
        case Mnemonic::Fucomip:
            return "fucomip";
        case Mnemonic::Fucomp:
            return "fucomp";
        case Mnemonic::Fucompp:
            return "fucompp";
        case Mnemonic::Fwait:
            return "fwait";
        case Mnemonic::Fxam:
            return "fxam";
        case Mnemonic::Fxch:
            return "fxch";
        case Mnemonic::Fxrstor:
            return "fxrstor";
        case Mnemonic::Fxrstor64:
            return "fxrstor64";
        case Mnemonic::Fxsave:
            return "fxsave";
        case Mnemonic::Fxsave64:
            return "fxsave64";
        case Mnemonic::Fxtract:
            return "fxtract";
        case Mnemonic::Fyl2x:
            return "fyl2x";
        case Mnemonic::Fyl2xp1:
            return "fyl2xp1";
        case Mnemonic::Getsec:
            return "getsec";
        case Mnemonic::Gf2p8affineinvqb:
            return "gf2p8affineinvqb";
        case Mnemonic::Gf2p8affineqb:
            return "gf2p8affineqb";
        case Mnemonic::Gf2p8mulb:
            return "gf2p8mulb";
        case Mnemonic::Haddpd:
            return "haddpd";
        case Mnemonic::Haddps:
            return "haddps";
        case Mnemonic::Hlt:
            return "hlt";
        case Mnemonic::Hreset:
            return "hreset";
        case Mnemonic::Hsubpd:
            return "hsubpd";
        case Mnemonic::Hsubps:
            return "hsubps";
        case Mnemonic::Idiv:
            return "idiv";
        case Mnemonic::Imul:
            return "imul";
        case Mnemonic::In:
            return "in";
        case Mnemonic::Inc:
            return "inc";
        case Mnemonic::Incsspd:
            return "incsspd";
        case Mnemonic::Incsspq:
            return "incsspq";
        case Mnemonic::Insb:
            return "insb";
        case Mnemonic::Insd:
            return "insd";
        case Mnemonic::Insertps:
            return "insertps";
        case Mnemonic::Insertq:
            return "insertq";
        case Mnemonic::Insw:
            return "insw";
        case Mnemonic::Int:
            return "int";
        case Mnemonic::Int1:
            return "int1";
        case Mnemonic::Int3:
            return "int3";
        case Mnemonic::Into:
            return "into";
        case Mnemonic::Invd:
            return "invd";
        case Mnemonic::Invept:
            return "invept";
        case Mnemonic::Invlpg:
            return "invlpg";
        case Mnemonic::Invlpga:
            return "invlpga";
        case Mnemonic::Invlpgb:
            return "invlpgb";
        case Mnemonic::Invpcid:
            return "invpcid";
        case Mnemonic::Invvpid:
            return "invvpid";
        case Mnemonic::Iret:
            return "iret";
        case Mnemonic::Iretd:
            return "iretd";
        case Mnemonic::Iretq:
            return "iretq";
        case Mnemonic::Jb:
            return "jb";
        case Mnemonic::Jbe:
            return "jbe";
        case Mnemonic::Jcxz:
            return "jcxz";
        case Mnemonic::Jecxz:
            return "jecxz";
        case Mnemonic::Jknzd:
            return "jknzd";
        case Mnemonic::Jkzd:
            return "jkzd";
        case Mnemonic::Jl:
            return "jl";
        case Mnemonic::Jle:
            return "jle";
        case Mnemonic::Jmp:
            return "jmp";
        case Mnemonic::Jnb:
            return "jnb";
        case Mnemonic::Jnbe:
            return "jnbe";
        case Mnemonic::Jnl:
            return "jnl";
        case Mnemonic::Jnle:
            return "jnle";
        case Mnemonic::Jno:
            return "jno";
        case Mnemonic::Jnp:
            return "jnp";
        case Mnemonic::Jns:
            return "jns";
        case Mnemonic::Jnz:
            return "jnz";
        case Mnemonic::Jo:
            return "jo";
        case Mnemonic::Jp:
            return "jp";
        case Mnemonic::Jrcxz:
            return "jrcxz";
        case Mnemonic::Js:
            return "js";
        case Mnemonic::Jz:
            return "jz";
        case Mnemonic::Kaddb:
            return "kaddb";
        case Mnemonic::Kaddd:
            return "kaddd";
        case Mnemonic::Kaddq:
            return "kaddq";
        case Mnemonic::Kaddw:
            return "kaddw";
        case Mnemonic::Kand:
            return "kand";
        case Mnemonic::Kandb:
            return "kandb";
        case Mnemonic::Kandd:
            return "kandd";
        case Mnemonic::Kandn:
            return "kandn";
        case Mnemonic::Kandnb:
            return "kandnb";
        case Mnemonic::Kandnd:
            return "kandnd";
        case Mnemonic::Kandnq:
            return "kandnq";
        case Mnemonic::Kandnr:
            return "kandnr";
        case Mnemonic::Kandnw:
            return "kandnw";
        case Mnemonic::Kandq:
            return "kandq";
        case Mnemonic::Kandw:
            return "kandw";
        case Mnemonic::Kconcath:
            return "kconcath";
        case Mnemonic::Kconcatl:
            return "kconcatl";
        case Mnemonic::Kextract:
            return "kextract";
        case Mnemonic::Kmerge2l1h:
            return "kmerge2l1h";
        case Mnemonic::Kmerge2l1l:
            return "kmerge2l1l";
        case Mnemonic::Kmov:
            return "kmov";
        case Mnemonic::Kmovb:
            return "kmovb";
        case Mnemonic::Kmovd:
            return "kmovd";
        case Mnemonic::Kmovq:
            return "kmovq";
        case Mnemonic::Kmovw:
            return "kmovw";
        case Mnemonic::Knot:
            return "knot";
        case Mnemonic::Knotb:
            return "knotb";
        case Mnemonic::Knotd:
            return "knotd";
        case Mnemonic::Knotq:
            return "knotq";
        case Mnemonic::Knotw:
            return "knotw";
        case Mnemonic::Kor:
            return "kor";
        case Mnemonic::Korb:
            return "korb";
        case Mnemonic::Kord:
            return "kord";
        case Mnemonic::Korq:
            return "korq";
        case Mnemonic::Kortest:
            return "kortest";
        case Mnemonic::Kortestb:
            return "kortestb";
        case Mnemonic::Kortestd:
            return "kortestd";
        case Mnemonic::Kortestq:
            return "kortestq";
        case Mnemonic::Kortestw:
            return "kortestw";
        case Mnemonic::Korw:
            return "korw";
        case Mnemonic::Kshiftlb:
            return "kshiftlb";
        case Mnemonic::Kshiftld:
            return "kshiftld";
        case Mnemonic::Kshiftlq:
            return "kshiftlq";
        case Mnemonic::Kshiftlw:
            return "kshiftlw";
        case Mnemonic::Kshiftrb:
            return "kshiftrb";
        case Mnemonic::Kshiftrd:
            return "kshiftrd";
        case Mnemonic::Kshiftrq:
            return "kshiftrq";
        case Mnemonic::Kshiftrw:
            return "kshiftrw";
        case Mnemonic::Ktestb:
            return "ktestb";
        case Mnemonic::Ktestd:
            return "ktestd";
        case Mnemonic::Ktestq:
            return "ktestq";
        case Mnemonic::Ktestw:
            return "ktestw";
        case Mnemonic::Kunpckbw:
            return "kunpckbw";
        case Mnemonic::Kunpckdq:
            return "kunpckdq";
        case Mnemonic::Kunpckwd:
            return "kunpckwd";
        case Mnemonic::Kxnor:
            return "kxnor";
        case Mnemonic::Kxnorb:
            return "kxnorb";
        case Mnemonic::Kxnord:
            return "kxnord";
        case Mnemonic::Kxnorq:
            return "kxnorq";
        case Mnemonic::Kxnorw:
            return "kxnorw";
        case Mnemonic::Kxor:
            return "kxor";
        case Mnemonic::Kxorb:
            return "kxorb";
        case Mnemonic::Kxord:
            return "kxord";
        case Mnemonic::Kxorq:
            return "kxorq";
        case Mnemonic::Kxorw:
            return "kxorw";
        case Mnemonic::Lahf:
            return "lahf";
        case Mnemonic::Lar:
            return "lar";
        case Mnemonic::Lddqu:
            return "lddqu";
        case Mnemonic::Ldmxcsr:
            return "ldmxcsr";
        case Mnemonic::Lds:
            return "lds";
        case Mnemonic::Ldtilecfg:
            return "ldtilecfg";
        case Mnemonic::Lea:
            return "lea";
        case Mnemonic::Leave:
            return "leave";
        case Mnemonic::Les:
            return "les";
        case Mnemonic::Lfence:
            return "lfence";
        case Mnemonic::Lfs:
            return "lfs";
        case Mnemonic::Lgdt:
            return "lgdt";
        case Mnemonic::Lgs:
            return "lgs";
        case Mnemonic::Lidt:
            return "lidt";
        case Mnemonic::Lldt:
            return "lldt";
        case Mnemonic::Llwpcb:
            return "llwpcb";
        case Mnemonic::Lmsw:
            return "lmsw";
        case Mnemonic::Loadiwkey:
            return "loadiwkey";
        case Mnemonic::Lodsb:
            return "lodsb";
        case Mnemonic::Lodsd:
            return "lodsd";
        case Mnemonic::Lodsq:
            return "lodsq";
        case Mnemonic::Lodsw:
            return "lodsw";
        case Mnemonic::Loop:
            return "loop";
        case Mnemonic::Loope:
            return "loope";
        case Mnemonic::Loopne:
            return "loopne";
        case Mnemonic::Lsl:
            return "lsl";
        case Mnemonic::Lss:
            return "lss";
        case Mnemonic::Ltr:
            return "ltr";
        case Mnemonic::Lwpins:
            return "lwpins";
        case Mnemonic::Lwpval:
            return "lwpval";
        case Mnemonic::Lzcnt:
            return "lzcnt";
        case Mnemonic::Maskmovdqu:
            return "maskmovdqu";
        case Mnemonic::Maskmovq:
            return "maskmovq";
        case Mnemonic::Maxpd:
            return "maxpd";
        case Mnemonic::Maxps:
            return "maxps";
        case Mnemonic::Maxsd:
            return "maxsd";
        case Mnemonic::Maxss:
            return "maxss";
        case Mnemonic::Mcommit:
            return "mcommit";
        case Mnemonic::Mfence:
            return "mfence";
        case Mnemonic::Minpd:
            return "minpd";
        case Mnemonic::Minps:
            return "minps";
        case Mnemonic::Minsd:
            return "minsd";
        case Mnemonic::Minss:
            return "minss";
        case Mnemonic::Monitor:
            return "monitor";
        case Mnemonic::Monitorx:
            return "monitorx";
        case Mnemonic::Montmul:
            return "montmul";
        case Mnemonic::Mov:
            return "mov";
        case Mnemonic::Movapd:
            return "movapd";
        case Mnemonic::Movaps:
            return "movaps";
        case Mnemonic::Movbe:
            return "movbe";
        case Mnemonic::Movd:
            return "movd";
        case Mnemonic::Movddup:
            return "movddup";
        case Mnemonic::Movdir64b:
            return "movdir64b";
        case Mnemonic::Movdiri:
            return "movdiri";
        case Mnemonic::Movdq2q:
            return "movdq2q";
        case Mnemonic::Movdqa:
            return "movdqa";
        case Mnemonic::Movdqu:
            return "movdqu";
        case Mnemonic::Movhlps:
            return "movhlps";
        case Mnemonic::Movhpd:
            return "movhpd";
        case Mnemonic::Movhps:
            return "movhps";
        case Mnemonic::Movlhps:
            return "movlhps";
        case Mnemonic::Movlpd:
            return "movlpd";
        case Mnemonic::Movlps:
            return "movlps";
        case Mnemonic::Movmskpd:
            return "movmskpd";
        case Mnemonic::Movmskps:
            return "movmskps";
        case Mnemonic::Movntdq:
            return "movntdq";
        case Mnemonic::Movntdqa:
            return "movntdqa";
        case Mnemonic::Movnti:
            return "movnti";
        case Mnemonic::Movntpd:
            return "movntpd";
        case Mnemonic::Movntps:
            return "movntps";
        case Mnemonic::Movntq:
            return "movntq";
        case Mnemonic::Movntsd:
            return "movntsd";
        case Mnemonic::Movntss:
            return "movntss";
        case Mnemonic::Movq:
            return "movq";
        case Mnemonic::Movq2dq:
            return "movq2dq";
        case Mnemonic::Movsb:
            return "movsb";
        case Mnemonic::Movsd:
            return "movsd";
        case Mnemonic::Movshdup:
            return "movshdup";
        case Mnemonic::Movsldup:
            return "movsldup";
        case Mnemonic::Movsq:
            return "movsq";
        case Mnemonic::Movss:
            return "movss";
        case Mnemonic::Movsw:
            return "movsw";
        case Mnemonic::Movsx:
            return "movsx";
        case Mnemonic::Movsxd:
            return "movsxd";
        case Mnemonic::Movupd:
            return "movupd";
        case Mnemonic::Movups:
            return "movups";
        case Mnemonic::Movzx:
            return "movzx";
        case Mnemonic::Mpsadbw:
            return "mpsadbw";
        case Mnemonic::Mul:
            return "mul";
        case Mnemonic::Mulpd:
            return "mulpd";
        case Mnemonic::Mulps:
            return "mulps";
        case Mnemonic::Mulsd:
            return "mulsd";
        case Mnemonic::Mulss:
            return "mulss";
        case Mnemonic::Mulx:
            return "mulx";
        case Mnemonic::Mwait:
            return "mwait";
        case Mnemonic::Mwaitx:
            return "mwaitx";
        case Mnemonic::Neg:
            return "neg";
        case Mnemonic::Nop:
            return "nop";
        case Mnemonic::Not:
            return "not";
        case Mnemonic::Or:
            return "or";
        case Mnemonic::Orpd:
            return "orpd";
        case Mnemonic::Orps:
            return "orps";
        case Mnemonic::Out:
            return "out";
        case Mnemonic::Outsb:
            return "outsb";
        case Mnemonic::Outsd:
            return "outsd";
        case Mnemonic::Outsw:
            return "outsw";
        case Mnemonic::Pabsb:
            return "pabsb";
        case Mnemonic::Pabsd:
            return "pabsd";
        case Mnemonic::Pabsw:
            return "pabsw";
        case Mnemonic::Packssdw:
            return "packssdw";
        case Mnemonic::Packsswb:
            return "packsswb";
        case Mnemonic::Packusdw:
            return "packusdw";
        case Mnemonic::Packuswb:
            return "packuswb";
        case Mnemonic::Paddb:
            return "paddb";
        case Mnemonic::Paddd:
            return "paddd";
        case Mnemonic::Paddq:
            return "paddq";
        case Mnemonic::Paddsb:
            return "paddsb";
        case Mnemonic::Paddsw:
            return "paddsw";
        case Mnemonic::Paddusb:
            return "paddusb";
        case Mnemonic::Paddusw:
            return "paddusw";
        case Mnemonic::Paddw:
            return "paddw";
        case Mnemonic::Palignr:
            return "palignr";
        case Mnemonic::Pand:
            return "pand";
        case Mnemonic::Pandn:
            return "pandn";
        case Mnemonic::Pause:
            return "pause";
        case Mnemonic::Pavgb:
            return "pavgb";
        case Mnemonic::Pavgusb:
            return "pavgusb";
        case Mnemonic::Pavgw:
            return "pavgw";
        case Mnemonic::Pblendvb:
            return "pblendvb";
        case Mnemonic::Pblendw:
            return "pblendw";
        case Mnemonic::Pclmulqdq:
            return "pclmulqdq";
        case Mnemonic::Pcmpeqb:
            return "pcmpeqb";
        case Mnemonic::Pcmpeqd:
            return "pcmpeqd";
        case Mnemonic::Pcmpeqq:
            return "pcmpeqq";
        case Mnemonic::Pcmpeqw:
            return "pcmpeqw";
        case Mnemonic::Pcmpestri:
            return "pcmpestri";
        case Mnemonic::Pcmpestrm:
            return "pcmpestrm";
        case Mnemonic::Pcmpgtb:
            return "pcmpgtb";
        case Mnemonic::Pcmpgtd:
            return "pcmpgtd";
        case Mnemonic::Pcmpgtq:
            return "pcmpgtq";
        case Mnemonic::Pcmpgtw:
            return "pcmpgtw";
        case Mnemonic::Pcmpistri:
            return "pcmpistri";
        case Mnemonic::Pcmpistrm:
            return "pcmpistrm";
        case Mnemonic::Pconfig:
            return "pconfig";
        case Mnemonic::Pdep:
            return "pdep";
        case Mnemonic::Pext:
            return "pext";
        case Mnemonic::Pextrb:
            return "pextrb";
        case Mnemonic::Pextrd:
            return "pextrd";
        case Mnemonic::Pextrq:
            return "pextrq";
        case Mnemonic::Pextrw:
            return "pextrw";
        case Mnemonic::Pf2id:
            return "pf2id";
        case Mnemonic::Pf2iw:
            return "pf2iw";
        case Mnemonic::Pfacc:
            return "pfacc";
        case Mnemonic::Pfadd:
            return "pfadd";
        case Mnemonic::Pfcmpeq:
            return "pfcmpeq";
        case Mnemonic::Pfcmpge:
            return "pfcmpge";
        case Mnemonic::Pfcmpgt:
            return "pfcmpgt";
        case Mnemonic::Pfcpit1:
            return "pfcpit1";
        case Mnemonic::Pfmax:
            return "pfmax";
        case Mnemonic::Pfmin:
            return "pfmin";
        case Mnemonic::Pfmul:
            return "pfmul";
        case Mnemonic::Pfnacc:
            return "pfnacc";
        case Mnemonic::Pfpnacc:
            return "pfpnacc";
        case Mnemonic::Pfrcp:
            return "pfrcp";
        case Mnemonic::Pfrcpit2:
            return "pfrcpit2";
        case Mnemonic::Pfrsqit1:
            return "pfrsqit1";
        case Mnemonic::Pfsqrt:
            return "pfsqrt";
        case Mnemonic::Pfsub:
            return "pfsub";
        case Mnemonic::Pfsubr:
            return "pfsubr";
        case Mnemonic::Phaddd:
            return "phaddd";
        case Mnemonic::Phaddsw:
            return "phaddsw";
        case Mnemonic::Phaddw:
            return "phaddw";
        case Mnemonic::Phminposuw:
            return "phminposuw";
        case Mnemonic::Phsubd:
            return "phsubd";
        case Mnemonic::Phsubsw:
            return "phsubsw";
        case Mnemonic::Phsubw:
            return "phsubw";
        case Mnemonic::Pi2fd:
            return "pi2fd";
        case Mnemonic::Pi2fw:
            return "pi2fw";
        case Mnemonic::Pinsrb:
            return "pinsrb";
        case Mnemonic::Pinsrd:
            return "pinsrd";
        case Mnemonic::Pinsrq:
            return "pinsrq";
        case Mnemonic::Pinsrw:
            return "pinsrw";
        case Mnemonic::Pmaddubsw:
            return "pmaddubsw";
        case Mnemonic::Pmaddwd:
            return "pmaddwd";
        case Mnemonic::Pmaxsb:
            return "pmaxsb";
        case Mnemonic::Pmaxsd:
            return "pmaxsd";
        case Mnemonic::Pmaxsw:
            return "pmaxsw";
        case Mnemonic::Pmaxub:
            return "pmaxub";
        case Mnemonic::Pmaxud:
            return "pmaxud";
        case Mnemonic::Pmaxuw:
            return "pmaxuw";
        case Mnemonic::Pminsb:
            return "pminsb";
        case Mnemonic::Pminsd:
            return "pminsd";
        case Mnemonic::Pminsw:
            return "pminsw";
        case Mnemonic::Pminub:
            return "pminub";
        case Mnemonic::Pminud:
            return "pminud";
        case Mnemonic::Pminuw:
            return "pminuw";
        case Mnemonic::Pmovmskb:
            return "pmovmskb";
        case Mnemonic::Pmovsxbd:
            return "pmovsxbd";
        case Mnemonic::Pmovsxbq:
            return "pmovsxbq";
        case Mnemonic::Pmovsxbw:
            return "pmovsxbw";
        case Mnemonic::Pmovsxdq:
            return "pmovsxdq";
        case Mnemonic::Pmovsxwd:
            return "pmovsxwd";
        case Mnemonic::Pmovsxwq:
            return "pmovsxwq";
        case Mnemonic::Pmovzxbd:
            return "pmovzxbd";
        case Mnemonic::Pmovzxbq:
            return "pmovzxbq";
        case Mnemonic::Pmovzxbw:
            return "pmovzxbw";
        case Mnemonic::Pmovzxdq:
            return "pmovzxdq";
        case Mnemonic::Pmovzxwd:
            return "pmovzxwd";
        case Mnemonic::Pmovzxwq:
            return "pmovzxwq";
        case Mnemonic::Pmuldq:
            return "pmuldq";
        case Mnemonic::Pmulhrsw:
            return "pmulhrsw";
        case Mnemonic::Pmulhrw:
            return "pmulhrw";
        case Mnemonic::Pmulhuw:
            return "pmulhuw";
        case Mnemonic::Pmulhw:
            return "pmulhw";
        case Mnemonic::Pmulld:
            return "pmulld";
        case Mnemonic::Pmullw:
            return "pmullw";
        case Mnemonic::Pmuludq:
            return "pmuludq";
        case Mnemonic::Pop:
            return "pop";
        case Mnemonic::Popa:
            return "popa";
        case Mnemonic::Popad:
            return "popad";
        case Mnemonic::Popcnt:
            return "popcnt";
        case Mnemonic::Popf:
            return "popf";
        case Mnemonic::Popfd:
            return "popfd";
        case Mnemonic::Popfq:
            return "popfq";
        case Mnemonic::Por:
            return "por";
        case Mnemonic::Prefetch:
            return "prefetch";
        case Mnemonic::Prefetchnta:
            return "prefetchnta";
        case Mnemonic::Prefetcht0:
            return "prefetcht0";
        case Mnemonic::Prefetcht1:
            return "prefetcht1";
        case Mnemonic::Prefetcht2:
            return "prefetcht2";
        case Mnemonic::Prefetchw:
            return "prefetchw";
        case Mnemonic::Prefetchwt1:
            return "prefetchwt1";
        case Mnemonic::Psadbw:
            return "psadbw";
        case Mnemonic::Pshufb:
            return "pshufb";
        case Mnemonic::Pshufd:
            return "pshufd";
        case Mnemonic::Pshufhw:
            return "pshufhw";
        case Mnemonic::Pshuflw:
            return "pshuflw";
        case Mnemonic::Pshufw:
            return "pshufw";
        case Mnemonic::Psignb:
            return "psignb";
        case Mnemonic::Psignd:
            return "psignd";
        case Mnemonic::Psignw:
            return "psignw";
        case Mnemonic::Pslld:
            return "pslld";
        case Mnemonic::Pslldq:
            return "pslldq";
        case Mnemonic::Psllq:
            return "psllq";
        case Mnemonic::Psllw:
            return "psllw";
        case Mnemonic::Psmash:
            return "psmash";
        case Mnemonic::Psrad:
            return "psrad";
        case Mnemonic::Psraw:
            return "psraw";
        case Mnemonic::Psrld:
            return "psrld";
        case Mnemonic::Psrldq:
            return "psrldq";
        case Mnemonic::Psrlq:
            return "psrlq";
        case Mnemonic::Psrlw:
            return "psrlw";
        case Mnemonic::Psubb:
            return "psubb";
        case Mnemonic::Psubd:
            return "psubd";
        case Mnemonic::Psubq:
            return "psubq";
        case Mnemonic::Psubsb:
            return "psubsb";
        case Mnemonic::Psubsw:
            return "psubsw";
        case Mnemonic::Psubusb:
            return "psubusb";
        case Mnemonic::Psubusw:
            return "psubusw";
        case Mnemonic::Psubw:
            return "psubw";
        case Mnemonic::Pswapd:
            return "pswapd";
        case Mnemonic::Ptest:
            return "ptest";
        case Mnemonic::Ptwrite:
            return "ptwrite";
        case Mnemonic::Punpckhbw:
            return "punpckhbw";
        case Mnemonic::Punpckhdq:
            return "punpckhdq";
        case Mnemonic::Punpckhqdq:
            return "punpckhqdq";
        case Mnemonic::Punpckhwd:
            return "punpckhwd";
        case Mnemonic::Punpcklbw:
            return "punpcklbw";
        case Mnemonic::Punpckldq:
            return "punpckldq";
        case Mnemonic::Punpcklqdq:
            return "punpcklqdq";
        case Mnemonic::Punpcklwd:
            return "punpcklwd";
        case Mnemonic::Push:
            return "push";
        case Mnemonic::Pusha:
            return "pusha";
        case Mnemonic::Pushad:
            return "pushad";
        case Mnemonic::Pushf:
            return "pushf";
        case Mnemonic::Pushfd:
            return "pushfd";
        case Mnemonic::Pushfq:
            return "pushfq";
        case Mnemonic::Pvalidate:
            return "pvalidate";
        case Mnemonic::Pxor:
            return "pxor";
        case Mnemonic::Rcl:
            return "rcl";
        case Mnemonic::Rcpps:
            return "rcpps";
        case Mnemonic::Rcpss:
            return "rcpss";
        case Mnemonic::Rcr:
            return "rcr";
        case Mnemonic::Rdfsbase:
            return "rdfsbase";
        case Mnemonic::Rdgsbase:
            return "rdgsbase";
        case Mnemonic::Rdmsr:
            return "rdmsr";
        case Mnemonic::Rdpid:
            return "rdpid";
        case Mnemonic::Rdpkru:
            return "rdpkru";
        case Mnemonic::Rdpmc:
            return "rdpmc";
        case Mnemonic::Rdpru:
            return "rdpru";
        case Mnemonic::Rdrand:
            return "rdrand";
        case Mnemonic::Rdseed:
            return "rdseed";
        case Mnemonic::Rdsspd:
            return "rdsspd";
        case Mnemonic::Rdsspq:
            return "rdsspq";
        case Mnemonic::Rdtsc:
            return "rdtsc";
        case Mnemonic::Rdtscp:
            return "rdtscp";
        case Mnemonic::Ret:
            return "ret";
        case Mnemonic::Rmpadjust:
            return "rmpadjust";
        case Mnemonic::Rmpupdate:
            return "rmpupdate";
        case Mnemonic::Rol:
            return "rol";
        case Mnemonic::Ror:
            return "ror";
        case Mnemonic::Rorx:
            return "rorx";
        case Mnemonic::Roundpd:
            return "roundpd";
        case Mnemonic::Roundps:
            return "roundps";
        case Mnemonic::Roundsd:
            return "roundsd";
        case Mnemonic::Roundss:
            return "roundss";
        case Mnemonic::Rsm:
            return "rsm";
        case Mnemonic::Rsqrtps:
            return "rsqrtps";
        case Mnemonic::Rsqrtss:
            return "rsqrtss";
        case Mnemonic::Rstorssp:
            return "rstorssp";
        case Mnemonic::Sahf:
            return "sahf";
        case Mnemonic::Salc:
            return "salc";
        case Mnemonic::Sar:
            return "sar";
        case Mnemonic::Sarx:
            return "sarx";
        case Mnemonic::Saveprevssp:
            return "saveprevssp";
        case Mnemonic::Sbb:
            return "sbb";
        case Mnemonic::Scasb:
            return "scasb";
        case Mnemonic::Scasd:
            return "scasd";
        case Mnemonic::Scasq:
            return "scasq";
        case Mnemonic::Scasw:
            return "scasw";
        case Mnemonic::Seamcall:
            return "seamcall";
        case Mnemonic::Seamops:
            return "seamops";
        case Mnemonic::Seamret:
            return "seamret";
        case Mnemonic::Senduipi:
            return "senduipi";
        case Mnemonic::Serialize:
            return "serialize";
        case Mnemonic::Setb:
            return "setb";
        case Mnemonic::Setbe:
            return "setbe";
        case Mnemonic::Setl:
            return "setl";
        case Mnemonic::Setle:
            return "setle";
        case Mnemonic::Setnb:
            return "setnb";
        case Mnemonic::Setnbe:
            return "setnbe";
        case Mnemonic::Setnl:
            return "setnl";
        case Mnemonic::Setnle:
            return "setnle";
        case Mnemonic::Setno:
            return "setno";
        case Mnemonic::Setnp:
            return "setnp";
        case Mnemonic::Setns:
            return "setns";
        case Mnemonic::Setnz:
            return "setnz";
        case Mnemonic::Seto:
            return "seto";
        case Mnemonic::Setp:
            return "setp";
        case Mnemonic::Sets:
            return "sets";
        case Mnemonic::Setssbsy:
            return "setssbsy";
        case Mnemonic::Setz:
            return "setz";
        case Mnemonic::Sfence:
            return "sfence";
        case Mnemonic::Sgdt:
            return "sgdt";
        case Mnemonic::Sha1msg1:
            return "sha1msg1";
        case Mnemonic::Sha1msg2:
            return "sha1msg2";
        case Mnemonic::Sha1nexte:
            return "sha1nexte";
        case Mnemonic::Sha1rnds4:
            return "sha1rnds4";
        case Mnemonic::Sha256msg1:
            return "sha256msg1";
        case Mnemonic::Sha256msg2:
            return "sha256msg2";
        case Mnemonic::Sha256rnds2:
            return "sha256rnds2";
        case Mnemonic::Shl:
            return "shl";
        case Mnemonic::Shld:
            return "shld";
        case Mnemonic::Shlx:
            return "shlx";
        case Mnemonic::Shr:
            return "shr";
        case Mnemonic::Shrd:
            return "shrd";
        case Mnemonic::Shrx:
            return "shrx";
        case Mnemonic::Shufpd:
            return "shufpd";
        case Mnemonic::Shufps:
            return "shufps";
        case Mnemonic::Sidt:
            return "sidt";
        case Mnemonic::Skinit:
            return "skinit";
        case Mnemonic::Sldt:
            return "sldt";
        case Mnemonic::Slwpcb:
            return "slwpcb";
        case Mnemonic::Smsw:
            return "smsw";
        case Mnemonic::Spflt:
            return "spflt";
        case Mnemonic::Sqrtpd:
            return "sqrtpd";
        case Mnemonic::Sqrtps:
            return "sqrtps";
        case Mnemonic::Sqrtsd:
            return "sqrtsd";
        case Mnemonic::Sqrtss:
            return "sqrtss";
        case Mnemonic::Stac:
            return "stac";
        case Mnemonic::Stc:
            return "stc";
        case Mnemonic::Std:
            return "std";
        case Mnemonic::Stgi:
            return "stgi";
        case Mnemonic::Sti:
            return "sti";
        case Mnemonic::Stmxcsr:
            return "stmxcsr";
        case Mnemonic::Stosb:
            return "stosb";
        case Mnemonic::Stosd:
            return "stosd";
        case Mnemonic::Stosq:
            return "stosq";
        case Mnemonic::Stosw:
            return "stosw";
        case Mnemonic::Str:
            return "str";
        case Mnemonic::Sttilecfg:
            return "sttilecfg";
        case Mnemonic::Stui:
            return "stui";
        case Mnemonic::Sub:
            return "sub";
        case Mnemonic::Subpd:
            return "subpd";
        case Mnemonic::Subps:
            return "subps";
        case Mnemonic::Subsd:
            return "subsd";
        case Mnemonic::Subss:
            return "subss";
        case Mnemonic::Swapgs:
            return "swapgs";
        case Mnemonic::Syscall:
            return "syscall";
        case Mnemonic::Sysenter:
            return "sysenter";
        case Mnemonic::Sysexit:
            return "sysexit";
        case Mnemonic::Sysret:
            return "sysret";
        case Mnemonic::T1mskc:
            return "t1mskc";
        case Mnemonic::Tdcall:
            return "tdcall";
        case Mnemonic::Tdpbf16ps:
            return "tdpbf16ps";
        case Mnemonic::Tdpbssd:
            return "tdpbssd";
        case Mnemonic::Tdpbsud:
            return "tdpbsud";
        case Mnemonic::Tdpbusd:
            return "tdpbusd";
        case Mnemonic::Tdpbuud:
            return "tdpbuud";
        case Mnemonic::Test:
            return "test";
        case Mnemonic::Testui:
            return "testui";
        case Mnemonic::Tileloadd:
            return "tileloadd";
        case Mnemonic::Tileloaddt1:
            return "tileloaddt1";
        case Mnemonic::Tilerelease:
            return "tilerelease";
        case Mnemonic::Tilestored:
            return "tilestored";
        case Mnemonic::Tilezero:
            return "tilezero";
        case Mnemonic::Tlbsync:
            return "tlbsync";
        case Mnemonic::Tpause:
            return "tpause";
        case Mnemonic::Tzcnt:
            return "tzcnt";
        case Mnemonic::Tzcnti:
            return "tzcnti";
        case Mnemonic::Tzmsk:
            return "tzmsk";
        case Mnemonic::Ucomisd:
            return "ucomisd";
        case Mnemonic::Ucomiss:
            return "ucomiss";
        case Mnemonic::Ud0:
            return "ud0";
        case Mnemonic::Ud1:
            return "ud1";
        case Mnemonic::Ud2:
            return "ud2";
        case Mnemonic::Uiret:
            return "uiret";
        case Mnemonic::Umonitor:
            return "umonitor";
        case Mnemonic::Umwait:
            return "umwait";
        case Mnemonic::Unpckhpd:
            return "unpckhpd";
        case Mnemonic::Unpckhps:
            return "unpckhps";
        case Mnemonic::Unpcklpd:
            return "unpcklpd";
        case Mnemonic::Unpcklps:
            return "unpcklps";
        case Mnemonic::V4fmaddps:
            return "v4fmaddps";
        case Mnemonic::V4fmaddss:
            return "v4fmaddss";
        case Mnemonic::V4fnmaddps:
            return "v4fnmaddps";
        case Mnemonic::V4fnmaddss:
            return "v4fnmaddss";
        case Mnemonic::Vaddnpd:
            return "vaddnpd";
        case Mnemonic::Vaddnps:
            return "vaddnps";
        case Mnemonic::Vaddpd:
            return "vaddpd";
        case Mnemonic::Vaddph:
            return "vaddph";
        case Mnemonic::Vaddps:
            return "vaddps";
        case Mnemonic::Vaddsd:
            return "vaddsd";
        case Mnemonic::Vaddsetsps:
            return "vaddsetsps";
        case Mnemonic::Vaddsh:
            return "vaddsh";
        case Mnemonic::Vaddss:
            return "vaddss";
        case Mnemonic::Vaddsubpd:
            return "vaddsubpd";
        case Mnemonic::Vaddsubps:
            return "vaddsubps";
        case Mnemonic::Vaesdec:
            return "vaesdec";
        case Mnemonic::Vaesdeclast:
            return "vaesdeclast";
        case Mnemonic::Vaesenc:
            return "vaesenc";
        case Mnemonic::Vaesenclast:
            return "vaesenclast";
        case Mnemonic::Vaesimc:
            return "vaesimc";
        case Mnemonic::Vaeskeygenassist:
            return "vaeskeygenassist";
        case Mnemonic::Valignd:
            return "valignd";
        case Mnemonic::Valignq:
            return "valignq";
        case Mnemonic::Vandnpd:
            return "vandnpd";
        case Mnemonic::Vandnps:
            return "vandnps";
        case Mnemonic::Vandpd:
            return "vandpd";
        case Mnemonic::Vandps:
            return "vandps";
        case Mnemonic::Vblendmpd:
            return "vblendmpd";
        case Mnemonic::Vblendmps:
            return "vblendmps";
        case Mnemonic::Vblendpd:
            return "vblendpd";
        case Mnemonic::Vblendps:
            return "vblendps";
        case Mnemonic::Vblendvpd:
            return "vblendvpd";
        case Mnemonic::Vblendvps:
            return "vblendvps";
        case Mnemonic::Vbroadcastf128:
            return "vbroadcastf128";
        case Mnemonic::Vbroadcastf32x2:
            return "vbroadcastf32x2";
        case Mnemonic::Vbroadcastf32x4:
            return "vbroadcastf32x4";
        case Mnemonic::Vbroadcastf32x8:
            return "vbroadcastf32x8";
        case Mnemonic::Vbroadcastf64x2:
            return "vbroadcastf64x2";
        case Mnemonic::Vbroadcastf64x4:
            return "vbroadcastf64x4";
        case Mnemonic::Vbroadcasti128:
            return "vbroadcasti128";
        case Mnemonic::Vbroadcasti32x2:
            return "vbroadcasti32x2";
        case Mnemonic::Vbroadcasti32x4:
            return "vbroadcasti32x4";
        case Mnemonic::Vbroadcasti32x8:
            return "vbroadcasti32x8";
        case Mnemonic::Vbroadcasti64x2:
            return "vbroadcasti64x2";
        case Mnemonic::Vbroadcasti64x4:
            return "vbroadcasti64x4";
        case Mnemonic::Vbroadcastsd:
            return "vbroadcastsd";
        case Mnemonic::Vbroadcastss:
            return "vbroadcastss";
        case Mnemonic::Vcmppd:
            return "vcmppd";
        case Mnemonic::Vcmpph:
            return "vcmpph";
        case Mnemonic::Vcmpps:
            return "vcmpps";
        case Mnemonic::Vcmpsd:
            return "vcmpsd";
        case Mnemonic::Vcmpsh:
            return "vcmpsh";
        case Mnemonic::Vcmpss:
            return "vcmpss";
        case Mnemonic::Vcomisd:
            return "vcomisd";
        case Mnemonic::Vcomish:
            return "vcomish";
        case Mnemonic::Vcomiss:
            return "vcomiss";
        case Mnemonic::Vcompresspd:
            return "vcompresspd";
        case Mnemonic::Vcompressps:
            return "vcompressps";
        case Mnemonic::Vcvtdq2pd:
            return "vcvtdq2pd";
        case Mnemonic::Vcvtdq2ph:
            return "vcvtdq2ph";
        case Mnemonic::Vcvtdq2ps:
            return "vcvtdq2ps";
        case Mnemonic::Vcvtfxpntdq2ps:
            return "vcvtfxpntdq2ps";
        case Mnemonic::Vcvtfxpntpd2dq:
            return "vcvtfxpntpd2dq";
        case Mnemonic::Vcvtfxpntpd2udq:
            return "vcvtfxpntpd2udq";
        case Mnemonic::Vcvtfxpntps2dq:
            return "vcvtfxpntps2dq";
        case Mnemonic::Vcvtfxpntps2udq:
            return "vcvtfxpntps2udq";
        case Mnemonic::Vcvtfxpntudq2ps:
            return "vcvtfxpntudq2ps";
        case Mnemonic::Vcvtne2ps2bf16:
            return "vcvtne2ps2bf16";
        case Mnemonic::Vcvtneps2bf16:
            return "vcvtneps2bf16";
        case Mnemonic::Vcvtpd2dq:
            return "vcvtpd2dq";
        case Mnemonic::Vcvtpd2ph:
            return "vcvtpd2ph";
        case Mnemonic::Vcvtpd2ps:
            return "vcvtpd2ps";
        case Mnemonic::Vcvtpd2qq:
            return "vcvtpd2qq";
        case Mnemonic::Vcvtpd2udq:
            return "vcvtpd2udq";
        case Mnemonic::Vcvtpd2uqq:
            return "vcvtpd2uqq";
        case Mnemonic::Vcvtph2dq:
            return "vcvtph2dq";
        case Mnemonic::Vcvtph2pd:
            return "vcvtph2pd";
        case Mnemonic::Vcvtph2ps:
            return "vcvtph2ps";
        case Mnemonic::Vcvtph2psx:
            return "vcvtph2psx";
        case Mnemonic::Vcvtph2qq:
            return "vcvtph2qq";
        case Mnemonic::Vcvtph2udq:
            return "vcvtph2udq";
        case Mnemonic::Vcvtph2uqq:
            return "vcvtph2uqq";
        case Mnemonic::Vcvtph2uw:
            return "vcvtph2uw";
        case Mnemonic::Vcvtph2w:
            return "vcvtph2w";
        case Mnemonic::Vcvtps2dq:
            return "vcvtps2dq";
        case Mnemonic::Vcvtps2pd:
            return "vcvtps2pd";
        case Mnemonic::Vcvtps2ph:
            return "vcvtps2ph";
        case Mnemonic::Vcvtps2phx:
            return "vcvtps2phx";
        case Mnemonic::Vcvtps2qq:
            return "vcvtps2qq";
        case Mnemonic::Vcvtps2udq:
            return "vcvtps2udq";
        case Mnemonic::Vcvtps2uqq:
            return "vcvtps2uqq";
        case Mnemonic::Vcvtqq2pd:
            return "vcvtqq2pd";
        case Mnemonic::Vcvtqq2ph:
            return "vcvtqq2ph";
        case Mnemonic::Vcvtqq2ps:
            return "vcvtqq2ps";
        case Mnemonic::Vcvtsd2sh:
            return "vcvtsd2sh";
        case Mnemonic::Vcvtsd2si:
            return "vcvtsd2si";
        case Mnemonic::Vcvtsd2ss:
            return "vcvtsd2ss";
        case Mnemonic::Vcvtsd2usi:
            return "vcvtsd2usi";
        case Mnemonic::Vcvtsh2sd:
            return "vcvtsh2sd";
        case Mnemonic::Vcvtsh2si:
            return "vcvtsh2si";
        case Mnemonic::Vcvtsh2ss:
            return "vcvtsh2ss";
        case Mnemonic::Vcvtsh2usi:
            return "vcvtsh2usi";
        case Mnemonic::Vcvtsi2sd:
            return "vcvtsi2sd";
        case Mnemonic::Vcvtsi2sh:
            return "vcvtsi2sh";
        case Mnemonic::Vcvtsi2ss:
            return "vcvtsi2ss";
        case Mnemonic::Vcvtss2sd:
            return "vcvtss2sd";
        case Mnemonic::Vcvtss2sh:
            return "vcvtss2sh";
        case Mnemonic::Vcvtss2si:
            return "vcvtss2si";
        case Mnemonic::Vcvtss2usi:
            return "vcvtss2usi";
        case Mnemonic::Vcvttpd2dq:
            return "vcvttpd2dq";
        case Mnemonic::Vcvttpd2qq:
            return "vcvttpd2qq";
        case Mnemonic::Vcvttpd2udq:
            return "vcvttpd2udq";
        case Mnemonic::Vcvttpd2uqq:
            return "vcvttpd2uqq";
        case Mnemonic::Vcvttph2dq:
            return "vcvttph2dq";
        case Mnemonic::Vcvttph2qq:
            return "vcvttph2qq";
        case Mnemonic::Vcvttph2udq:
            return "vcvttph2udq";
        case Mnemonic::Vcvttph2uqq:
            return "vcvttph2uqq";
        case Mnemonic::Vcvttph2uw:
            return "vcvttph2uw";
        case Mnemonic::Vcvttph2w:
            return "vcvttph2w";
        case Mnemonic::Vcvttps2dq:
            return "vcvttps2dq";
        case Mnemonic::Vcvttps2qq:
            return "vcvttps2qq";
        case Mnemonic::Vcvttps2udq:
            return "vcvttps2udq";
        case Mnemonic::Vcvttps2uqq:
            return "vcvttps2uqq";
        case Mnemonic::Vcvttsd2si:
            return "vcvttsd2si";
        case Mnemonic::Vcvttsd2usi:
            return "vcvttsd2usi";
        case Mnemonic::Vcvttsh2si:
            return "vcvttsh2si";
        case Mnemonic::Vcvttsh2usi:
            return "vcvttsh2usi";
        case Mnemonic::Vcvttss2si:
            return "vcvttss2si";
        case Mnemonic::Vcvttss2usi:
            return "vcvttss2usi";
        case Mnemonic::Vcvtudq2pd:
            return "vcvtudq2pd";
        case Mnemonic::Vcvtudq2ph:
            return "vcvtudq2ph";
        case Mnemonic::Vcvtudq2ps:
            return "vcvtudq2ps";
        case Mnemonic::Vcvtuqq2pd:
            return "vcvtuqq2pd";
        case Mnemonic::Vcvtuqq2ph:
            return "vcvtuqq2ph";
        case Mnemonic::Vcvtuqq2ps:
            return "vcvtuqq2ps";
        case Mnemonic::Vcvtusi2sd:
            return "vcvtusi2sd";
        case Mnemonic::Vcvtusi2sh:
            return "vcvtusi2sh";
        case Mnemonic::Vcvtusi2ss:
            return "vcvtusi2ss";
        case Mnemonic::Vcvtuw2ph:
            return "vcvtuw2ph";
        case Mnemonic::Vcvtw2ph:
            return "vcvtw2ph";
        case Mnemonic::Vdbpsadbw:
            return "vdbpsadbw";
        case Mnemonic::Vdivpd:
            return "vdivpd";
        case Mnemonic::Vdivph:
            return "vdivph";
        case Mnemonic::Vdivps:
            return "vdivps";
        case Mnemonic::Vdivsd:
            return "vdivsd";
        case Mnemonic::Vdivsh:
            return "vdivsh";
        case Mnemonic::Vdivss:
            return "vdivss";
        case Mnemonic::Vdpbf16ps:
            return "vdpbf16ps";
        case Mnemonic::Vdppd:
            return "vdppd";
        case Mnemonic::Vdpps:
            return "vdpps";
        case Mnemonic::Verr:
            return "verr";
        case Mnemonic::Verw:
            return "verw";
        case Mnemonic::Vexp223ps:
            return "vexp223ps";
        case Mnemonic::Vexp2pd:
            return "vexp2pd";
        case Mnemonic::Vexp2ps:
            return "vexp2ps";
        case Mnemonic::Vexpandpd:
            return "vexpandpd";
        case Mnemonic::Vexpandps:
            return "vexpandps";
        case Mnemonic::Vextractf128:
            return "vextractf128";
        case Mnemonic::Vextractf32x4:
            return "vextractf32x4";
        case Mnemonic::Vextractf32x8:
            return "vextractf32x8";
        case Mnemonic::Vextractf64x2:
            return "vextractf64x2";
        case Mnemonic::Vextractf64x4:
            return "vextractf64x4";
        case Mnemonic::Vextracti128:
            return "vextracti128";
        case Mnemonic::Vextracti32x4:
            return "vextracti32x4";
        case Mnemonic::Vextracti32x8:
            return "vextracti32x8";
        case Mnemonic::Vextracti64x2:
            return "vextracti64x2";
        case Mnemonic::Vextracti64x4:
            return "vextracti64x4";
        case Mnemonic::Vextractps:
            return "vextractps";
        case Mnemonic::Vfcmaddcph:
            return "vfcmaddcph";
        case Mnemonic::Vfcmaddcsh:
            return "vfcmaddcsh";
        case Mnemonic::Vfcmulcph:
            return "vfcmulcph";
        case Mnemonic::Vfcmulcsh:
            return "vfcmulcsh";
        case Mnemonic::Vfixupimmpd:
            return "vfixupimmpd";
        case Mnemonic::Vfixupimmps:
            return "vfixupimmps";
        case Mnemonic::Vfixupimmsd:
            return "vfixupimmsd";
        case Mnemonic::Vfixupimmss:
            return "vfixupimmss";
        case Mnemonic::Vfixupnanpd:
            return "vfixupnanpd";
        case Mnemonic::Vfixupnanps:
            return "vfixupnanps";
        case Mnemonic::Vfmadd132pd:
            return "vfmadd132pd";
        case Mnemonic::Vfmadd132ph:
            return "vfmadd132ph";
        case Mnemonic::Vfmadd132ps:
            return "vfmadd132ps";
        case Mnemonic::Vfmadd132sd:
            return "vfmadd132sd";
        case Mnemonic::Vfmadd132sh:
            return "vfmadd132sh";
        case Mnemonic::Vfmadd132ss:
            return "vfmadd132ss";
        case Mnemonic::Vfmadd213pd:
            return "vfmadd213pd";
        case Mnemonic::Vfmadd213ph:
            return "vfmadd213ph";
        case Mnemonic::Vfmadd213ps:
            return "vfmadd213ps";
        case Mnemonic::Vfmadd213sd:
            return "vfmadd213sd";
        case Mnemonic::Vfmadd213sh:
            return "vfmadd213sh";
        case Mnemonic::Vfmadd213ss:
            return "vfmadd213ss";
        case Mnemonic::Vfmadd231pd:
            return "vfmadd231pd";
        case Mnemonic::Vfmadd231ph:
            return "vfmadd231ph";
        case Mnemonic::Vfmadd231ps:
            return "vfmadd231ps";
        case Mnemonic::Vfmadd231sd:
            return "vfmadd231sd";
        case Mnemonic::Vfmadd231sh:
            return "vfmadd231sh";
        case Mnemonic::Vfmadd231ss:
            return "vfmadd231ss";
        case Mnemonic::Vfmadd233ps:
            return "vfmadd233ps";
        case Mnemonic::Vfmaddcph:
            return "vfmaddcph";
        case Mnemonic::Vfmaddcsh:
            return "vfmaddcsh";
        case Mnemonic::Vfmaddpd:
            return "vfmaddpd";
        case Mnemonic::Vfmaddps:
            return "vfmaddps";
        case Mnemonic::Vfmaddsd:
            return "vfmaddsd";
        case Mnemonic::Vfmaddss:
            return "vfmaddss";
        case Mnemonic::Vfmaddsub132pd:
            return "vfmaddsub132pd";
        case Mnemonic::Vfmaddsub132ph:
            return "vfmaddsub132ph";
        case Mnemonic::Vfmaddsub132ps:
            return "vfmaddsub132ps";
        case Mnemonic::Vfmaddsub213pd:
            return "vfmaddsub213pd";
        case Mnemonic::Vfmaddsub213ph:
            return "vfmaddsub213ph";
        case Mnemonic::Vfmaddsub213ps:
            return "vfmaddsub213ps";
        case Mnemonic::Vfmaddsub231pd:
            return "vfmaddsub231pd";
        case Mnemonic::Vfmaddsub231ph:
            return "vfmaddsub231ph";
        case Mnemonic::Vfmaddsub231ps:
            return "vfmaddsub231ps";
        case Mnemonic::Vfmaddsubpd:
            return "vfmaddsubpd";
        case Mnemonic::Vfmaddsubps:
            return "vfmaddsubps";
        case Mnemonic::Vfmsub132pd:
            return "vfmsub132pd";
        case Mnemonic::Vfmsub132ph:
            return "vfmsub132ph";
        case Mnemonic::Vfmsub132ps:
            return "vfmsub132ps";
        case Mnemonic::Vfmsub132sd:
            return "vfmsub132sd";
        case Mnemonic::Vfmsub132sh:
            return "vfmsub132sh";
        case Mnemonic::Vfmsub132ss:
            return "vfmsub132ss";
        case Mnemonic::Vfmsub213pd:
            return "vfmsub213pd";
        case Mnemonic::Vfmsub213ph:
            return "vfmsub213ph";
        case Mnemonic::Vfmsub213ps:
            return "vfmsub213ps";
        case Mnemonic::Vfmsub213sd:
            return "vfmsub213sd";
        case Mnemonic::Vfmsub213sh:
            return "vfmsub213sh";
        case Mnemonic::Vfmsub213ss:
            return "vfmsub213ss";
        case Mnemonic::Vfmsub231pd:
            return "vfmsub231pd";
        case Mnemonic::Vfmsub231ph:
            return "vfmsub231ph";
        case Mnemonic::Vfmsub231ps:
            return "vfmsub231ps";
        case Mnemonic::Vfmsub231sd:
            return "vfmsub231sd";
        case Mnemonic::Vfmsub231sh:
            return "vfmsub231sh";
        case Mnemonic::Vfmsub231ss:
            return "vfmsub231ss";
        case Mnemonic::Vfmsubadd132pd:
            return "vfmsubadd132pd";
        case Mnemonic::Vfmsubadd132ph:
            return "vfmsubadd132ph";
        case Mnemonic::Vfmsubadd132ps:
            return "vfmsubadd132ps";
        case Mnemonic::Vfmsubadd213pd:
            return "vfmsubadd213pd";
        case Mnemonic::Vfmsubadd213ph:
            return "vfmsubadd213ph";
        case Mnemonic::Vfmsubadd213ps:
            return "vfmsubadd213ps";
        case Mnemonic::Vfmsubadd231pd:
            return "vfmsubadd231pd";
        case Mnemonic::Vfmsubadd231ph:
            return "vfmsubadd231ph";
        case Mnemonic::Vfmsubadd231ps:
            return "vfmsubadd231ps";
        case Mnemonic::Vfmsubaddpd:
            return "vfmsubaddpd";
        case Mnemonic::Vfmsubaddps:
            return "vfmsubaddps";
        case Mnemonic::Vfmsubpd:
            return "vfmsubpd";
        case Mnemonic::Vfmsubps:
            return "vfmsubps";
        case Mnemonic::Vfmsubsd:
            return "vfmsubsd";
        case Mnemonic::Vfmsubss:
            return "vfmsubss";
        case Mnemonic::Vfmulcph:
            return "vfmulcph";
        case Mnemonic::Vfmulcsh:
            return "vfmulcsh";
        case Mnemonic::Vfnmadd132pd:
            return "vfnmadd132pd";
        case Mnemonic::Vfnmadd132ph:
            return "vfnmadd132ph";
        case Mnemonic::Vfnmadd132ps:
            return "vfnmadd132ps";
        case Mnemonic::Vfnmadd132sd:
            return "vfnmadd132sd";
        case Mnemonic::Vfnmadd132sh:
            return "vfnmadd132sh";
        case Mnemonic::Vfnmadd132ss:
            return "vfnmadd132ss";
        case Mnemonic::Vfnmadd213pd:
            return "vfnmadd213pd";
        case Mnemonic::Vfnmadd213ph:
            return "vfnmadd213ph";
        case Mnemonic::Vfnmadd213ps:
            return "vfnmadd213ps";
        case Mnemonic::Vfnmadd213sd:
            return "vfnmadd213sd";
        case Mnemonic::Vfnmadd213sh:
            return "vfnmadd213sh";
        case Mnemonic::Vfnmadd213ss:
            return "vfnmadd213ss";
        case Mnemonic::Vfnmadd231pd:
            return "vfnmadd231pd";
        case Mnemonic::Vfnmadd231ph:
            return "vfnmadd231ph";
        case Mnemonic::Vfnmadd231ps:
            return "vfnmadd231ps";
        case Mnemonic::Vfnmadd231sd:
            return "vfnmadd231sd";
        case Mnemonic::Vfnmadd231sh:
            return "vfnmadd231sh";
        case Mnemonic::Vfnmadd231ss:
            return "vfnmadd231ss";
        case Mnemonic::Vfnmaddpd:
            return "vfnmaddpd";
        case Mnemonic::Vfnmaddps:
            return "vfnmaddps";
        case Mnemonic::Vfnmaddsd:
            return "vfnmaddsd";
        case Mnemonic::Vfnmaddss:
            return "vfnmaddss";
        case Mnemonic::Vfnmsub132pd:
            return "vfnmsub132pd";
        case Mnemonic::Vfnmsub132ph:
            return "vfnmsub132ph";
        case Mnemonic::Vfnmsub132ps:
            return "vfnmsub132ps";
        case Mnemonic::Vfnmsub132sd:
            return "vfnmsub132sd";
        case Mnemonic::Vfnmsub132sh:
            return "vfnmsub132sh";
        case Mnemonic::Vfnmsub132ss:
            return "vfnmsub132ss";
        case Mnemonic::Vfnmsub213pd:
            return "vfnmsub213pd";
        case Mnemonic::Vfnmsub213ph:
            return "vfnmsub213ph";
        case Mnemonic::Vfnmsub213ps:
            return "vfnmsub213ps";
        case Mnemonic::Vfnmsub213sd:
            return "vfnmsub213sd";
        case Mnemonic::Vfnmsub213sh:
            return "vfnmsub213sh";
        case Mnemonic::Vfnmsub213ss:
            return "vfnmsub213ss";
        case Mnemonic::Vfnmsub231pd:
            return "vfnmsub231pd";
        case Mnemonic::Vfnmsub231ph:
            return "vfnmsub231ph";
        case Mnemonic::Vfnmsub231ps:
            return "vfnmsub231ps";
        case Mnemonic::Vfnmsub231sd:
            return "vfnmsub231sd";
        case Mnemonic::Vfnmsub231sh:
            return "vfnmsub231sh";
        case Mnemonic::Vfnmsub231ss:
            return "vfnmsub231ss";
        case Mnemonic::Vfnmsubpd:
            return "vfnmsubpd";
        case Mnemonic::Vfnmsubps:
            return "vfnmsubps";
        case Mnemonic::Vfnmsubsd:
            return "vfnmsubsd";
        case Mnemonic::Vfnmsubss:
            return "vfnmsubss";
        case Mnemonic::Vfpclasspd:
            return "vfpclasspd";
        case Mnemonic::Vfpclassph:
            return "vfpclassph";
        case Mnemonic::Vfpclassps:
            return "vfpclassps";
        case Mnemonic::Vfpclasssd:
            return "vfpclasssd";
        case Mnemonic::Vfpclasssh:
            return "vfpclasssh";
        case Mnemonic::Vfpclassss:
            return "vfpclassss";
        case Mnemonic::Vfrczpd:
            return "vfrczpd";
        case Mnemonic::Vfrczps:
            return "vfrczps";
        case Mnemonic::Vfrczsd:
            return "vfrczsd";
        case Mnemonic::Vfrczss:
            return "vfrczss";
        case Mnemonic::Vgatherdpd:
            return "vgatherdpd";
        case Mnemonic::Vgatherdps:
            return "vgatherdps";
        case Mnemonic::Vgatherpf0dpd:
            return "vgatherpf0dpd";
        case Mnemonic::Vgatherpf0dps:
            return "vgatherpf0dps";
        case Mnemonic::Vgatherpf0hintdpd:
            return "vgatherpf0hintdpd";
        case Mnemonic::Vgatherpf0hintdps:
            return "vgatherpf0hintdps";
        case Mnemonic::Vgatherpf0qpd:
            return "vgatherpf0qpd";
        case Mnemonic::Vgatherpf0qps:
            return "vgatherpf0qps";
        case Mnemonic::Vgatherpf1dpd:
            return "vgatherpf1dpd";
        case Mnemonic::Vgatherpf1dps:
            return "vgatherpf1dps";
        case Mnemonic::Vgatherpf1qpd:
            return "vgatherpf1qpd";
        case Mnemonic::Vgatherpf1qps:
            return "vgatherpf1qps";
        case Mnemonic::Vgatherqpd:
            return "vgatherqpd";
        case Mnemonic::Vgatherqps:
            return "vgatherqps";
        case Mnemonic::Vgetexppd:
            return "vgetexppd";
        case Mnemonic::Vgetexpph:
            return "vgetexpph";
        case Mnemonic::Vgetexpps:
            return "vgetexpps";
        case Mnemonic::Vgetexpsd:
            return "vgetexpsd";
        case Mnemonic::Vgetexpsh:
            return "vgetexpsh";
        case Mnemonic::Vgetexpss:
            return "vgetexpss";
        case Mnemonic::Vgetmantpd:
            return "vgetmantpd";
        case Mnemonic::Vgetmantph:
            return "vgetmantph";
        case Mnemonic::Vgetmantps:
            return "vgetmantps";
        case Mnemonic::Vgetmantsd:
            return "vgetmantsd";
        case Mnemonic::Vgetmantsh:
            return "vgetmantsh";
        case Mnemonic::Vgetmantss:
            return "vgetmantss";
        case Mnemonic::Vgf2p8affineinvqb:
            return "vgf2p8affineinvqb";
        case Mnemonic::Vgf2p8affineqb:
            return "vgf2p8affineqb";
        case Mnemonic::Vgf2p8mulb:
            return "vgf2p8mulb";
        case Mnemonic::Vgmaxabsps:
            return "vgmaxabsps";
        case Mnemonic::Vgmaxpd:
            return "vgmaxpd";
        case Mnemonic::Vgmaxps:
            return "vgmaxps";
        case Mnemonic::Vgminpd:
            return "vgminpd";
        case Mnemonic::Vgminps:
            return "vgminps";
        case Mnemonic::Vhaddpd:
            return "vhaddpd";
        case Mnemonic::Vhaddps:
            return "vhaddps";
        case Mnemonic::Vhsubpd:
            return "vhsubpd";
        case Mnemonic::Vhsubps:
            return "vhsubps";
        case Mnemonic::Vinsertf128:
            return "vinsertf128";
        case Mnemonic::Vinsertf32x4:
            return "vinsertf32x4";
        case Mnemonic::Vinsertf32x8:
            return "vinsertf32x8";
        case Mnemonic::Vinsertf64x2:
            return "vinsertf64x2";
        case Mnemonic::Vinsertf64x4:
            return "vinsertf64x4";
        case Mnemonic::Vinserti128:
            return "vinserti128";
        case Mnemonic::Vinserti32x4:
            return "vinserti32x4";
        case Mnemonic::Vinserti32x8:
            return "vinserti32x8";
        case Mnemonic::Vinserti64x2:
            return "vinserti64x2";
        case Mnemonic::Vinserti64x4:
            return "vinserti64x4";
        case Mnemonic::Vinsertps:
            return "vinsertps";
        case Mnemonic::Vlddqu:
            return "vlddqu";
        case Mnemonic::Vldmxcsr:
            return "vldmxcsr";
        case Mnemonic::Vloadunpackhd:
            return "vloadunpackhd";
        case Mnemonic::Vloadunpackhpd:
            return "vloadunpackhpd";
        case Mnemonic::Vloadunpackhps:
            return "vloadunpackhps";
        case Mnemonic::Vloadunpackhq:
            return "vloadunpackhq";
        case Mnemonic::Vloadunpackld:
            return "vloadunpackld";
        case Mnemonic::Vloadunpacklpd:
            return "vloadunpacklpd";
        case Mnemonic::Vloadunpacklps:
            return "vloadunpacklps";
        case Mnemonic::Vloadunpacklq:
            return "vloadunpacklq";
        case Mnemonic::Vlog2ps:
            return "vlog2ps";
        case Mnemonic::Vmaskmovdqu:
            return "vmaskmovdqu";
        case Mnemonic::Vmaskmovpd:
            return "vmaskmovpd";
        case Mnemonic::Vmaskmovps:
            return "vmaskmovps";
        case Mnemonic::Vmaxpd:
            return "vmaxpd";
        case Mnemonic::Vmaxph:
            return "vmaxph";
        case Mnemonic::Vmaxps:
            return "vmaxps";
        case Mnemonic::Vmaxsd:
            return "vmaxsd";
        case Mnemonic::Vmaxsh:
            return "vmaxsh";
        case Mnemonic::Vmaxss:
            return "vmaxss";
        case Mnemonic::Vmcall:
            return "vmcall";
        case Mnemonic::Vmclear:
            return "vmclear";
        case Mnemonic::Vmfunc:
            return "vmfunc";
        case Mnemonic::Vminpd:
            return "vminpd";
        case Mnemonic::Vminph:
            return "vminph";
        case Mnemonic::Vminps:
            return "vminps";
        case Mnemonic::Vminsd:
            return "vminsd";
        case Mnemonic::Vminsh:
            return "vminsh";
        case Mnemonic::Vminss:
            return "vminss";
        case Mnemonic::Vmlaunch:
            return "vmlaunch";
        case Mnemonic::Vmload:
            return "vmload";
        case Mnemonic::Vmmcall:
            return "vmmcall";
        case Mnemonic::Vmovapd:
            return "vmovapd";
        case Mnemonic::Vmovaps:
            return "vmovaps";
        case Mnemonic::Vmovd:
            return "vmovd";
        case Mnemonic::Vmovddup:
            return "vmovddup";
        case Mnemonic::Vmovdqa:
            return "vmovdqa";
        case Mnemonic::Vmovdqa32:
            return "vmovdqa32";
        case Mnemonic::Vmovdqa64:
            return "vmovdqa64";
        case Mnemonic::Vmovdqu:
            return "vmovdqu";
        case Mnemonic::Vmovdqu16:
            return "vmovdqu16";
        case Mnemonic::Vmovdqu32:
            return "vmovdqu32";
        case Mnemonic::Vmovdqu64:
            return "vmovdqu64";
        case Mnemonic::Vmovdqu8:
            return "vmovdqu8";
        case Mnemonic::Vmovhlps:
            return "vmovhlps";
        case Mnemonic::Vmovhpd:
            return "vmovhpd";
        case Mnemonic::Vmovhps:
            return "vmovhps";
        case Mnemonic::Vmovlhps:
            return "vmovlhps";
        case Mnemonic::Vmovlpd:
            return "vmovlpd";
        case Mnemonic::Vmovlps:
            return "vmovlps";
        case Mnemonic::Vmovmskpd:
            return "vmovmskpd";
        case Mnemonic::Vmovmskps:
            return "vmovmskps";
        case Mnemonic::Vmovnrapd:
            return "vmovnrapd";
        case Mnemonic::Vmovnraps:
            return "vmovnraps";
        case Mnemonic::Vmovnrngoapd:
            return "vmovnrngoapd";
        case Mnemonic::Vmovnrngoaps:
            return "vmovnrngoaps";
        case Mnemonic::Vmovntdq:
            return "vmovntdq";
        case Mnemonic::Vmovntdqa:
            return "vmovntdqa";
        case Mnemonic::Vmovntpd:
            return "vmovntpd";
        case Mnemonic::Vmovntps:
            return "vmovntps";
        case Mnemonic::Vmovq:
            return "vmovq";
        case Mnemonic::Vmovsd:
            return "vmovsd";
        case Mnemonic::Vmovsh:
            return "vmovsh";
        case Mnemonic::Vmovshdup:
            return "vmovshdup";
        case Mnemonic::Vmovsldup:
            return "vmovsldup";
        case Mnemonic::Vmovss:
            return "vmovss";
        case Mnemonic::Vmovupd:
            return "vmovupd";
        case Mnemonic::Vmovups:
            return "vmovups";
        case Mnemonic::Vmovw:
            return "vmovw";
        case Mnemonic::Vmpsadbw:
            return "vmpsadbw";
        case Mnemonic::Vmptrld:
            return "vmptrld";
        case Mnemonic::Vmptrst:
            return "vmptrst";
        case Mnemonic::Vmread:
            return "vmread";
        case Mnemonic::Vmresume:
            return "vmresume";
        case Mnemonic::Vmrun:
            return "vmrun";
        case Mnemonic::Vmsave:
            return "vmsave";
        case Mnemonic::Vmulpd:
            return "vmulpd";
        case Mnemonic::Vmulph:
            return "vmulph";
        case Mnemonic::Vmulps:
            return "vmulps";
        case Mnemonic::Vmulsd:
            return "vmulsd";
        case Mnemonic::Vmulsh:
            return "vmulsh";
        case Mnemonic::Vmulss:
            return "vmulss";
        case Mnemonic::Vmwrite:
            return "vmwrite";
        case Mnemonic::Vmxoff:
            return "vmxoff";
        case Mnemonic::Vmxon:
            return "vmxon";
        case Mnemonic::Vorpd:
            return "vorpd";
        case Mnemonic::Vorps:
            return "vorps";
        case Mnemonic::Vp2intersectd:
            return "vp2intersectd";
        case Mnemonic::Vp2intersectq:
            return "vp2intersectq";
        case Mnemonic::Vp4dpwssd:
            return "vp4dpwssd";
        case Mnemonic::Vp4dpwssds:
            return "vp4dpwssds";
        case Mnemonic::Vpabsb:
            return "vpabsb";
        case Mnemonic::Vpabsd:
            return "vpabsd";
        case Mnemonic::Vpabsq:
            return "vpabsq";
        case Mnemonic::Vpabsw:
            return "vpabsw";
        case Mnemonic::Vpackssdw:
            return "vpackssdw";
        case Mnemonic::Vpacksswb:
            return "vpacksswb";
        case Mnemonic::Vpackstorehd:
            return "vpackstorehd";
        case Mnemonic::Vpackstorehpd:
            return "vpackstorehpd";
        case Mnemonic::Vpackstorehps:
            return "vpackstorehps";
        case Mnemonic::Vpackstorehq:
            return "vpackstorehq";
        case Mnemonic::Vpackstoreld:
            return "vpackstoreld";
        case Mnemonic::Vpackstorelpd:
            return "vpackstorelpd";
        case Mnemonic::Vpackstorelps:
            return "vpackstorelps";
        case Mnemonic::Vpackstorelq:
            return "vpackstorelq";
        case Mnemonic::Vpackusdw:
            return "vpackusdw";
        case Mnemonic::Vpackuswb:
            return "vpackuswb";
        case Mnemonic::Vpadcd:
            return "vpadcd";
        case Mnemonic::Vpaddb:
            return "vpaddb";
        case Mnemonic::Vpaddd:
            return "vpaddd";
        case Mnemonic::Vpaddq:
            return "vpaddq";
        case Mnemonic::Vpaddsb:
            return "vpaddsb";
        case Mnemonic::Vpaddsetcd:
            return "vpaddsetcd";
        case Mnemonic::Vpaddsetsd:
            return "vpaddsetsd";
        case Mnemonic::Vpaddsw:
            return "vpaddsw";
        case Mnemonic::Vpaddusb:
            return "vpaddusb";
        case Mnemonic::Vpaddusw:
            return "vpaddusw";
        case Mnemonic::Vpaddw:
            return "vpaddw";
        case Mnemonic::Vpalignr:
            return "vpalignr";
        case Mnemonic::Vpand:
            return "vpand";
        case Mnemonic::Vpandd:
            return "vpandd";
        case Mnemonic::Vpandn:
            return "vpandn";
        case Mnemonic::Vpandnd:
            return "vpandnd";
        case Mnemonic::Vpandnq:
            return "vpandnq";
        case Mnemonic::Vpandq:
            return "vpandq";
        case Mnemonic::Vpavgb:
            return "vpavgb";
        case Mnemonic::Vpavgw:
            return "vpavgw";
        case Mnemonic::Vpblendd:
            return "vpblendd";
        case Mnemonic::Vpblendmb:
            return "vpblendmb";
        case Mnemonic::Vpblendmd:
            return "vpblendmd";
        case Mnemonic::Vpblendmq:
            return "vpblendmq";
        case Mnemonic::Vpblendmw:
            return "vpblendmw";
        case Mnemonic::Vpblendvb:
            return "vpblendvb";
        case Mnemonic::Vpblendw:
            return "vpblendw";
        case Mnemonic::Vpbroadcastb:
            return "vpbroadcastb";
        case Mnemonic::Vpbroadcastd:
            return "vpbroadcastd";
        case Mnemonic::Vpbroadcastmb2q:
            return "vpbroadcastmb2q";
        case Mnemonic::Vpbroadcastmw2d:
            return "vpbroadcastmw2d";
        case Mnemonic::Vpbroadcastq:
            return "vpbroadcastq";
        case Mnemonic::Vpbroadcastw:
            return "vpbroadcastw";
        case Mnemonic::Vpclmulqdq:
            return "vpclmulqdq";
        case Mnemonic::Vpcmov:
            return "vpcmov";
        case Mnemonic::Vpcmpb:
            return "vpcmpb";
        case Mnemonic::Vpcmpd:
            return "vpcmpd";
        case Mnemonic::Vpcmpeqb:
            return "vpcmpeqb";
        case Mnemonic::Vpcmpeqd:
            return "vpcmpeqd";
        case Mnemonic::Vpcmpeqq:
            return "vpcmpeqq";
        case Mnemonic::Vpcmpeqw:
            return "vpcmpeqw";
        case Mnemonic::Vpcmpestri:
            return "vpcmpestri";
        case Mnemonic::Vpcmpestrm:
            return "vpcmpestrm";
        case Mnemonic::Vpcmpgtb:
            return "vpcmpgtb";
        case Mnemonic::Vpcmpgtd:
            return "vpcmpgtd";
        case Mnemonic::Vpcmpgtq:
            return "vpcmpgtq";
        case Mnemonic::Vpcmpgtw:
            return "vpcmpgtw";
        case Mnemonic::Vpcmpistri:
            return "vpcmpistri";
        case Mnemonic::Vpcmpistrm:
            return "vpcmpistrm";
        case Mnemonic::Vpcmpltd:
            return "vpcmpltd";
        case Mnemonic::Vpcmpq:
            return "vpcmpq";
        case Mnemonic::Vpcmpub:
            return "vpcmpub";
        case Mnemonic::Vpcmpud:
            return "vpcmpud";
        case Mnemonic::Vpcmpuq:
            return "vpcmpuq";
        case Mnemonic::Vpcmpuw:
            return "vpcmpuw";
        case Mnemonic::Vpcmpw:
            return "vpcmpw";
        case Mnemonic::Vpcomb:
            return "vpcomb";
        case Mnemonic::Vpcomd:
            return "vpcomd";
        case Mnemonic::Vpcompressb:
            return "vpcompressb";
        case Mnemonic::Vpcompressd:
            return "vpcompressd";
        case Mnemonic::Vpcompressq:
            return "vpcompressq";
        case Mnemonic::Vpcompressw:
            return "vpcompressw";
        case Mnemonic::Vpcomq:
            return "vpcomq";
        case Mnemonic::Vpcomub:
            return "vpcomub";
        case Mnemonic::Vpcomud:
            return "vpcomud";
        case Mnemonic::Vpcomuq:
            return "vpcomuq";
        case Mnemonic::Vpcomuw:
            return "vpcomuw";
        case Mnemonic::Vpcomw:
            return "vpcomw";
        case Mnemonic::Vpconflictd:
            return "vpconflictd";
        case Mnemonic::Vpconflictq:
            return "vpconflictq";
        case Mnemonic::Vpdpbusd:
            return "vpdpbusd";
        case Mnemonic::Vpdpbusds:
            return "vpdpbusds";
        case Mnemonic::Vpdpwssd:
            return "vpdpwssd";
        case Mnemonic::Vpdpwssds:
            return "vpdpwssds";
        case Mnemonic::Vperm2f128:
            return "vperm2f128";
        case Mnemonic::Vperm2i128:
            return "vperm2i128";
        case Mnemonic::Vpermb:
            return "vpermb";
        case Mnemonic::Vpermd:
            return "vpermd";
        case Mnemonic::Vpermf32x4:
            return "vpermf32x4";
        case Mnemonic::Vpermi2b:
            return "vpermi2b";
        case Mnemonic::Vpermi2d:
            return "vpermi2d";
        case Mnemonic::Vpermi2pd:
            return "vpermi2pd";
        case Mnemonic::Vpermi2ps:
            return "vpermi2ps";
        case Mnemonic::Vpermi2q:
            return "vpermi2q";
        case Mnemonic::Vpermi2w:
            return "vpermi2w";
        case Mnemonic::Vpermil2pd:
            return "vpermil2pd";
        case Mnemonic::Vpermil2ps:
            return "vpermil2ps";
        case Mnemonic::Vpermilpd:
            return "vpermilpd";
        case Mnemonic::Vpermilps:
            return "vpermilps";
        case Mnemonic::Vpermpd:
            return "vpermpd";
        case Mnemonic::Vpermps:
            return "vpermps";
        case Mnemonic::Vpermq:
            return "vpermq";
        case Mnemonic::Vpermt2b:
            return "vpermt2b";
        case Mnemonic::Vpermt2d:
            return "vpermt2d";
        case Mnemonic::Vpermt2pd:
            return "vpermt2pd";
        case Mnemonic::Vpermt2ps:
            return "vpermt2ps";
        case Mnemonic::Vpermt2q:
            return "vpermt2q";
        case Mnemonic::Vpermt2w:
            return "vpermt2w";
        case Mnemonic::Vpermw:
            return "vpermw";
        case Mnemonic::Vpexpandb:
            return "vpexpandb";
        case Mnemonic::Vpexpandd:
            return "vpexpandd";
        case Mnemonic::Vpexpandq:
            return "vpexpandq";
        case Mnemonic::Vpexpandw:
            return "vpexpandw";
        case Mnemonic::Vpextrb:
            return "vpextrb";
        case Mnemonic::Vpextrd:
            return "vpextrd";
        case Mnemonic::Vpextrq:
            return "vpextrq";
        case Mnemonic::Vpextrw:
            return "vpextrw";
        case Mnemonic::Vpgatherdd:
            return "vpgatherdd";
        case Mnemonic::Vpgatherdq:
            return "vpgatherdq";
        case Mnemonic::Vpgatherqd:
            return "vpgatherqd";
        case Mnemonic::Vpgatherqq:
            return "vpgatherqq";
        case Mnemonic::Vphaddbd:
            return "vphaddbd";
        case Mnemonic::Vphaddbq:
            return "vphaddbq";
        case Mnemonic::Vphaddbw:
            return "vphaddbw";
        case Mnemonic::Vphaddd:
            return "vphaddd";
        case Mnemonic::Vphadddq:
            return "vphadddq";
        case Mnemonic::Vphaddsw:
            return "vphaddsw";
        case Mnemonic::Vphaddubd:
            return "vphaddubd";
        case Mnemonic::Vphaddubq:
            return "vphaddubq";
        case Mnemonic::Vphaddubw:
            return "vphaddubw";
        case Mnemonic::Vphaddudq:
            return "vphaddudq";
        case Mnemonic::Vphadduwd:
            return "vphadduwd";
        case Mnemonic::Vphadduwq:
            return "vphadduwq";
        case Mnemonic::Vphaddw:
            return "vphaddw";
        case Mnemonic::Vphaddwd:
            return "vphaddwd";
        case Mnemonic::Vphaddwq:
            return "vphaddwq";
        case Mnemonic::Vphminposuw:
            return "vphminposuw";
        case Mnemonic::Vphsubbw:
            return "vphsubbw";
        case Mnemonic::Vphsubd:
            return "vphsubd";
        case Mnemonic::Vphsubdq:
            return "vphsubdq";
        case Mnemonic::Vphsubsw:
            return "vphsubsw";
        case Mnemonic::Vphsubw:
            return "vphsubw";
        case Mnemonic::Vphsubwd:
            return "vphsubwd";
        case Mnemonic::Vpinsrb:
            return "vpinsrb";
        case Mnemonic::Vpinsrd:
            return "vpinsrd";
        case Mnemonic::Vpinsrq:
            return "vpinsrq";
        case Mnemonic::Vpinsrw:
            return "vpinsrw";
        case Mnemonic::Vplzcntd:
            return "vplzcntd";
        case Mnemonic::Vplzcntq:
            return "vplzcntq";
        case Mnemonic::Vpmacsdd:
            return "vpmacsdd";
        case Mnemonic::Vpmacsdqh:
            return "vpmacsdqh";
        case Mnemonic::Vpmacsdql:
            return "vpmacsdql";
        case Mnemonic::Vpmacssdd:
            return "vpmacssdd";
        case Mnemonic::Vpmacssdqh:
            return "vpmacssdqh";
        case Mnemonic::Vpmacssdql:
            return "vpmacssdql";
        case Mnemonic::Vpmacsswd:
            return "vpmacsswd";
        case Mnemonic::Vpmacssww:
            return "vpmacssww";
        case Mnemonic::Vpmacswd:
            return "vpmacswd";
        case Mnemonic::Vpmacsww:
            return "vpmacsww";
        case Mnemonic::Vpmadcsswd:
            return "vpmadcsswd";
        case Mnemonic::Vpmadcswd:
            return "vpmadcswd";
        case Mnemonic::Vpmadd231d:
            return "vpmadd231d";
        case Mnemonic::Vpmadd233d:
            return "vpmadd233d";
        case Mnemonic::Vpmadd52huq:
            return "vpmadd52huq";
        case Mnemonic::Vpmadd52luq:
            return "vpmadd52luq";
        case Mnemonic::Vpmaddubsw:
            return "vpmaddubsw";
        case Mnemonic::Vpmaddwd:
            return "vpmaddwd";
        case Mnemonic::Vpmaskmovd:
            return "vpmaskmovd";
        case Mnemonic::Vpmaskmovq:
            return "vpmaskmovq";
        case Mnemonic::Vpmaxsb:
            return "vpmaxsb";
        case Mnemonic::Vpmaxsd:
            return "vpmaxsd";
        case Mnemonic::Vpmaxsq:
            return "vpmaxsq";
        case Mnemonic::Vpmaxsw:
            return "vpmaxsw";
        case Mnemonic::Vpmaxub:
            return "vpmaxub";
        case Mnemonic::Vpmaxud:
            return "vpmaxud";
        case Mnemonic::Vpmaxuq:
            return "vpmaxuq";
        case Mnemonic::Vpmaxuw:
            return "vpmaxuw";
        case Mnemonic::Vpminsb:
            return "vpminsb";
        case Mnemonic::Vpminsd:
            return "vpminsd";
        case Mnemonic::Vpminsq:
            return "vpminsq";
        case Mnemonic::Vpminsw:
            return "vpminsw";
        case Mnemonic::Vpminub:
            return "vpminub";
        case Mnemonic::Vpminud:
            return "vpminud";
        case Mnemonic::Vpminuq:
            return "vpminuq";
        case Mnemonic::Vpminuw:
            return "vpminuw";
        case Mnemonic::Vpmovb2m:
            return "vpmovb2m";
        case Mnemonic::Vpmovd2m:
            return "vpmovd2m";
        case Mnemonic::Vpmovdb:
            return "vpmovdb";
        case Mnemonic::Vpmovdw:
            return "vpmovdw";
        case Mnemonic::Vpmovm2b:
            return "vpmovm2b";
        case Mnemonic::Vpmovm2d:
            return "vpmovm2d";
        case Mnemonic::Vpmovm2q:
            return "vpmovm2q";
        case Mnemonic::Vpmovm2w:
            return "vpmovm2w";
        case Mnemonic::Vpmovmskb:
            return "vpmovmskb";
        case Mnemonic::Vpmovq2m:
            return "vpmovq2m";
        case Mnemonic::Vpmovqb:
            return "vpmovqb";
        case Mnemonic::Vpmovqd:
            return "vpmovqd";
        case Mnemonic::Vpmovqw:
            return "vpmovqw";
        case Mnemonic::Vpmovsdb:
            return "vpmovsdb";
        case Mnemonic::Vpmovsdw:
            return "vpmovsdw";
        case Mnemonic::Vpmovsqb:
            return "vpmovsqb";
        case Mnemonic::Vpmovsqd:
            return "vpmovsqd";
        case Mnemonic::Vpmovsqw:
            return "vpmovsqw";
        case Mnemonic::Vpmovswb:
            return "vpmovswb";
        case Mnemonic::Vpmovsxbd:
            return "vpmovsxbd";
        case Mnemonic::Vpmovsxbq:
            return "vpmovsxbq";
        case Mnemonic::Vpmovsxbw:
            return "vpmovsxbw";
        case Mnemonic::Vpmovsxdq:
            return "vpmovsxdq";
        case Mnemonic::Vpmovsxwd:
            return "vpmovsxwd";
        case Mnemonic::Vpmovsxwq:
            return "vpmovsxwq";
        case Mnemonic::Vpmovusdb:
            return "vpmovusdb";
        case Mnemonic::Vpmovusdw:
            return "vpmovusdw";
        case Mnemonic::Vpmovusqb:
            return "vpmovusqb";
        case Mnemonic::Vpmovusqd:
            return "vpmovusqd";
        case Mnemonic::Vpmovusqw:
            return "vpmovusqw";
        case Mnemonic::Vpmovuswb:
            return "vpmovuswb";
        case Mnemonic::Vpmovw2m:
            return "vpmovw2m";
        case Mnemonic::Vpmovwb:
            return "vpmovwb";
        case Mnemonic::Vpmovzxbd:
            return "vpmovzxbd";
        case Mnemonic::Vpmovzxbq:
            return "vpmovzxbq";
        case Mnemonic::Vpmovzxbw:
            return "vpmovzxbw";
        case Mnemonic::Vpmovzxdq:
            return "vpmovzxdq";
        case Mnemonic::Vpmovzxwd:
            return "vpmovzxwd";
        case Mnemonic::Vpmovzxwq:
            return "vpmovzxwq";
        case Mnemonic::Vpmuldq:
            return "vpmuldq";
        case Mnemonic::Vpmulhd:
            return "vpmulhd";
        case Mnemonic::Vpmulhrsw:
            return "vpmulhrsw";
        case Mnemonic::Vpmulhud:
            return "vpmulhud";
        case Mnemonic::Vpmulhuw:
            return "vpmulhuw";
        case Mnemonic::Vpmulhw:
            return "vpmulhw";
        case Mnemonic::Vpmulld:
            return "vpmulld";
        case Mnemonic::Vpmullq:
            return "vpmullq";
        case Mnemonic::Vpmullw:
            return "vpmullw";
        case Mnemonic::Vpmultishiftqb:
            return "vpmultishiftqb";
        case Mnemonic::Vpmuludq:
            return "vpmuludq";
        case Mnemonic::Vpopcntb:
            return "vpopcntb";
        case Mnemonic::Vpopcntd:
            return "vpopcntd";
        case Mnemonic::Vpopcntq:
            return "vpopcntq";
        case Mnemonic::Vpopcntw:
            return "vpopcntw";
        case Mnemonic::Vpor:
            return "vpor";
        case Mnemonic::Vpord:
            return "vpord";
        case Mnemonic::Vporq:
            return "vporq";
        case Mnemonic::Vpperm:
            return "vpperm";
        case Mnemonic::Vprefetch0:
            return "vprefetch0";
        case Mnemonic::Vprefetch1:
            return "vprefetch1";
        case Mnemonic::Vprefetch2:
            return "vprefetch2";
        case Mnemonic::Vprefetche0:
            return "vprefetche0";
        case Mnemonic::Vprefetche1:
            return "vprefetche1";
        case Mnemonic::Vprefetche2:
            return "vprefetche2";
        case Mnemonic::Vprefetchenta:
            return "vprefetchenta";
        case Mnemonic::Vprefetchnta:
            return "vprefetchnta";
        case Mnemonic::Vprold:
            return "vprold";
        case Mnemonic::Vprolq:
            return "vprolq";
        case Mnemonic::Vprolvd:
            return "vprolvd";
        case Mnemonic::Vprolvq:
            return "vprolvq";
        case Mnemonic::Vprord:
            return "vprord";
        case Mnemonic::Vprorq:
            return "vprorq";
        case Mnemonic::Vprorvd:
            return "vprorvd";
        case Mnemonic::Vprorvq:
            return "vprorvq";
        case Mnemonic::Vprotb:
            return "vprotb";
        case Mnemonic::Vprotd:
            return "vprotd";
        case Mnemonic::Vprotq:
            return "vprotq";
        case Mnemonic::Vprotw:
            return "vprotw";
        case Mnemonic::Vpsadbw:
            return "vpsadbw";
        case Mnemonic::Vpsbbd:
            return "vpsbbd";
        case Mnemonic::Vpsbbrd:
            return "vpsbbrd";
        case Mnemonic::Vpscatterdd:
            return "vpscatterdd";
        case Mnemonic::Vpscatterdq:
            return "vpscatterdq";
        case Mnemonic::Vpscatterqd:
            return "vpscatterqd";
        case Mnemonic::Vpscatterqq:
            return "vpscatterqq";
        case Mnemonic::Vpshab:
            return "vpshab";
        case Mnemonic::Vpshad:
            return "vpshad";
        case Mnemonic::Vpshaq:
            return "vpshaq";
        case Mnemonic::Vpshaw:
            return "vpshaw";
        case Mnemonic::Vpshlb:
            return "vpshlb";
        case Mnemonic::Vpshld:
            return "vpshld";
        case Mnemonic::Vpshldd:
            return "vpshldd";
        case Mnemonic::Vpshldq:
            return "vpshldq";
        case Mnemonic::Vpshldvd:
            return "vpshldvd";
        case Mnemonic::Vpshldvq:
            return "vpshldvq";
        case Mnemonic::Vpshldvw:
            return "vpshldvw";
        case Mnemonic::Vpshldw:
            return "vpshldw";
        case Mnemonic::Vpshlq:
            return "vpshlq";
        case Mnemonic::Vpshlw:
            return "vpshlw";
        case Mnemonic::Vpshrdd:
            return "vpshrdd";
        case Mnemonic::Vpshrdq:
            return "vpshrdq";
        case Mnemonic::Vpshrdvd:
            return "vpshrdvd";
        case Mnemonic::Vpshrdvq:
            return "vpshrdvq";
        case Mnemonic::Vpshrdvw:
            return "vpshrdvw";
        case Mnemonic::Vpshrdw:
            return "vpshrdw";
        case Mnemonic::Vpshufb:
            return "vpshufb";
        case Mnemonic::Vpshufbitqmb:
            return "vpshufbitqmb";
        case Mnemonic::Vpshufd:
            return "vpshufd";
        case Mnemonic::Vpshufhw:
            return "vpshufhw";
        case Mnemonic::Vpshuflw:
            return "vpshuflw";
        case Mnemonic::Vpsignb:
            return "vpsignb";
        case Mnemonic::Vpsignd:
            return "vpsignd";
        case Mnemonic::Vpsignw:
            return "vpsignw";
        case Mnemonic::Vpslld:
            return "vpslld";
        case Mnemonic::Vpslldq:
            return "vpslldq";
        case Mnemonic::Vpsllq:
            return "vpsllq";
        case Mnemonic::Vpsllvd:
            return "vpsllvd";
        case Mnemonic::Vpsllvq:
            return "vpsllvq";
        case Mnemonic::Vpsllvw:
            return "vpsllvw";
        case Mnemonic::Vpsllw:
            return "vpsllw";
        case Mnemonic::Vpsrad:
            return "vpsrad";
        case Mnemonic::Vpsraq:
            return "vpsraq";
        case Mnemonic::Vpsravd:
            return "vpsravd";
        case Mnemonic::Vpsravq:
            return "vpsravq";
        case Mnemonic::Vpsravw:
            return "vpsravw";
        case Mnemonic::Vpsraw:
            return "vpsraw";
        case Mnemonic::Vpsrld:
            return "vpsrld";
        case Mnemonic::Vpsrldq:
            return "vpsrldq";
        case Mnemonic::Vpsrlq:
            return "vpsrlq";
        case Mnemonic::Vpsrlvd:
            return "vpsrlvd";
        case Mnemonic::Vpsrlvq:
            return "vpsrlvq";
        case Mnemonic::Vpsrlvw:
            return "vpsrlvw";
        case Mnemonic::Vpsrlw:
            return "vpsrlw";
        case Mnemonic::Vpsubb:
            return "vpsubb";
        case Mnemonic::Vpsubd:
            return "vpsubd";
        case Mnemonic::Vpsubq:
            return "vpsubq";
        case Mnemonic::Vpsubrd:
            return "vpsubrd";
        case Mnemonic::Vpsubrsetbd:
            return "vpsubrsetbd";
        case Mnemonic::Vpsubsb:
            return "vpsubsb";
        case Mnemonic::Vpsubsetbd:
            return "vpsubsetbd";
        case Mnemonic::Vpsubsw:
            return "vpsubsw";
        case Mnemonic::Vpsubusb:
            return "vpsubusb";
        case Mnemonic::Vpsubusw:
            return "vpsubusw";
        case Mnemonic::Vpsubw:
            return "vpsubw";
        case Mnemonic::Vpternlogd:
            return "vpternlogd";
        case Mnemonic::Vpternlogq:
            return "vpternlogq";
        case Mnemonic::Vptest:
            return "vptest";
        case Mnemonic::Vptestmb:
            return "vptestmb";
        case Mnemonic::Vptestmd:
            return "vptestmd";
        case Mnemonic::Vptestmq:
            return "vptestmq";
        case Mnemonic::Vptestmw:
            return "vptestmw";
        case Mnemonic::Vptestnmb:
            return "vptestnmb";
        case Mnemonic::Vptestnmd:
            return "vptestnmd";
        case Mnemonic::Vptestnmq:
            return "vptestnmq";
        case Mnemonic::Vptestnmw:
            return "vptestnmw";
        case Mnemonic::Vpunpckhbw:
            return "vpunpckhbw";
        case Mnemonic::Vpunpckhdq:
            return "vpunpckhdq";
        case Mnemonic::Vpunpckhqdq:
            return "vpunpckhqdq";
        case Mnemonic::Vpunpckhwd:
            return "vpunpckhwd";
        case Mnemonic::Vpunpcklbw:
            return "vpunpcklbw";
        case Mnemonic::Vpunpckldq:
            return "vpunpckldq";
        case Mnemonic::Vpunpcklqdq:
            return "vpunpcklqdq";
        case Mnemonic::Vpunpcklwd:
            return "vpunpcklwd";
        case Mnemonic::Vpxor:
            return "vpxor";
        case Mnemonic::Vpxord:
            return "vpxord";
        case Mnemonic::Vpxorq:
            return "vpxorq";
        case Mnemonic::Vrangepd:
            return "vrangepd";
        case Mnemonic::Vrangeps:
            return "vrangeps";
        case Mnemonic::Vrangesd:
            return "vrangesd";
        case Mnemonic::Vrangess:
            return "vrangess";
        case Mnemonic::Vrcp14pd:
            return "vrcp14pd";
        case Mnemonic::Vrcp14ps:
            return "vrcp14ps";
        case Mnemonic::Vrcp14sd:
            return "vrcp14sd";
        case Mnemonic::Vrcp14ss:
            return "vrcp14ss";
        case Mnemonic::Vrcp23ps:
            return "vrcp23ps";
        case Mnemonic::Vrcp28pd:
            return "vrcp28pd";
        case Mnemonic::Vrcp28ps:
            return "vrcp28ps";
        case Mnemonic::Vrcp28sd:
            return "vrcp28sd";
        case Mnemonic::Vrcp28ss:
            return "vrcp28ss";
        case Mnemonic::Vrcpph:
            return "vrcpph";
        case Mnemonic::Vrcpps:
            return "vrcpps";
        case Mnemonic::Vrcpsh:
            return "vrcpsh";
        case Mnemonic::Vrcpss:
            return "vrcpss";
        case Mnemonic::Vreducepd:
            return "vreducepd";
        case Mnemonic::Vreduceph:
            return "vreduceph";
        case Mnemonic::Vreduceps:
            return "vreduceps";
        case Mnemonic::Vreducesd:
            return "vreducesd";
        case Mnemonic::Vreducesh:
            return "vreducesh";
        case Mnemonic::Vreducess:
            return "vreducess";
        case Mnemonic::Vrndfxpntpd:
            return "vrndfxpntpd";
        case Mnemonic::Vrndfxpntps:
            return "vrndfxpntps";
        case Mnemonic::Vrndscalepd:
            return "vrndscalepd";
        case Mnemonic::Vrndscaleph:
            return "vrndscaleph";
        case Mnemonic::Vrndscaleps:
            return "vrndscaleps";
        case Mnemonic::Vrndscalesd:
            return "vrndscalesd";
        case Mnemonic::Vrndscalesh:
            return "vrndscalesh";
        case Mnemonic::Vrndscaless:
            return "vrndscaless";
        case Mnemonic::Vroundpd:
            return "vroundpd";
        case Mnemonic::Vroundps:
            return "vroundps";
        case Mnemonic::Vroundsd:
            return "vroundsd";
        case Mnemonic::Vroundss:
            return "vroundss";
        case Mnemonic::Vrsqrt14pd:
            return "vrsqrt14pd";
        case Mnemonic::Vrsqrt14ps:
            return "vrsqrt14ps";
        case Mnemonic::Vrsqrt14sd:
            return "vrsqrt14sd";
        case Mnemonic::Vrsqrt14ss:
            return "vrsqrt14ss";
        case Mnemonic::Vrsqrt23ps:
            return "vrsqrt23ps";
        case Mnemonic::Vrsqrt28pd:
            return "vrsqrt28pd";
        case Mnemonic::Vrsqrt28ps:
            return "vrsqrt28ps";
        case Mnemonic::Vrsqrt28sd:
            return "vrsqrt28sd";
        case Mnemonic::Vrsqrt28ss:
            return "vrsqrt28ss";
        case Mnemonic::Vrsqrtph:
            return "vrsqrtph";
        case Mnemonic::Vrsqrtps:
            return "vrsqrtps";
        case Mnemonic::Vrsqrtsh:
            return "vrsqrtsh";
        case Mnemonic::Vrsqrtss:
            return "vrsqrtss";
        case Mnemonic::Vscalefpd:
            return "vscalefpd";
        case Mnemonic::Vscalefph:
            return "vscalefph";
        case Mnemonic::Vscalefps:
            return "vscalefps";
        case Mnemonic::Vscalefsd:
            return "vscalefsd";
        case Mnemonic::Vscalefsh:
            return "vscalefsh";
        case Mnemonic::Vscalefss:
            return "vscalefss";
        case Mnemonic::Vscaleps:
            return "vscaleps";
        case Mnemonic::Vscatterdpd:
            return "vscatterdpd";
        case Mnemonic::Vscatterdps:
            return "vscatterdps";
        case Mnemonic::Vscatterpf0dpd:
            return "vscatterpf0dpd";
        case Mnemonic::Vscatterpf0dps:
            return "vscatterpf0dps";
        case Mnemonic::Vscatterpf0hintdpd:
            return "vscatterpf0hintdpd";
        case Mnemonic::Vscatterpf0hintdps:
            return "vscatterpf0hintdps";
        case Mnemonic::Vscatterpf0qpd:
            return "vscatterpf0qpd";
        case Mnemonic::Vscatterpf0qps:
            return "vscatterpf0qps";
        case Mnemonic::Vscatterpf1dpd:
            return "vscatterpf1dpd";
        case Mnemonic::Vscatterpf1dps:
            return "vscatterpf1dps";
        case Mnemonic::Vscatterpf1qpd:
            return "vscatterpf1qpd";
        case Mnemonic::Vscatterpf1qps:
            return "vscatterpf1qps";
        case Mnemonic::Vscatterqpd:
            return "vscatterqpd";
        case Mnemonic::Vscatterqps:
            return "vscatterqps";
        case Mnemonic::Vshuff32x4:
            return "vshuff32x4";
        case Mnemonic::Vshuff64x2:
            return "vshuff64x2";
        case Mnemonic::Vshufi32x4:
            return "vshufi32x4";
        case Mnemonic::Vshufi64x2:
            return "vshufi64x2";
        case Mnemonic::Vshufpd:
            return "vshufpd";
        case Mnemonic::Vshufps:
            return "vshufps";
        case Mnemonic::Vsqrtpd:
            return "vsqrtpd";
        case Mnemonic::Vsqrtph:
            return "vsqrtph";
        case Mnemonic::Vsqrtps:
            return "vsqrtps";
        case Mnemonic::Vsqrtsd:
            return "vsqrtsd";
        case Mnemonic::Vsqrtsh:
            return "vsqrtsh";
        case Mnemonic::Vsqrtss:
            return "vsqrtss";
        case Mnemonic::Vstmxcsr:
            return "vstmxcsr";
        case Mnemonic::Vsubpd:
            return "vsubpd";
        case Mnemonic::Vsubph:
            return "vsubph";
        case Mnemonic::Vsubps:
            return "vsubps";
        case Mnemonic::Vsubrpd:
            return "vsubrpd";
        case Mnemonic::Vsubrps:
            return "vsubrps";
        case Mnemonic::Vsubsd:
            return "vsubsd";
        case Mnemonic::Vsubsh:
            return "vsubsh";
        case Mnemonic::Vsubss:
            return "vsubss";
        case Mnemonic::Vtestpd:
            return "vtestpd";
        case Mnemonic::Vtestps:
            return "vtestps";
        case Mnemonic::Vucomisd:
            return "vucomisd";
        case Mnemonic::Vucomish:
            return "vucomish";
        case Mnemonic::Vucomiss:
            return "vucomiss";
        case Mnemonic::Vunpckhpd:
            return "vunpckhpd";
        case Mnemonic::Vunpckhps:
            return "vunpckhps";
        case Mnemonic::Vunpcklpd:
            return "vunpcklpd";
        case Mnemonic::Vunpcklps:
            return "vunpcklps";
        case Mnemonic::Vxorpd:
            return "vxorpd";
        case Mnemonic::Vxorps:
            return "vxorps";
        case Mnemonic::Vzeroall:
            return "vzeroall";
        case Mnemonic::Vzeroupper:
            return "vzeroupper";
        case Mnemonic::Wbinvd:
            return "wbinvd";
        case Mnemonic::Wrfsbase:
            return "wrfsbase";
        case Mnemonic::Wrgsbase:
            return "wrgsbase";
        case Mnemonic::Wrmsr:
            return "wrmsr";
        case Mnemonic::Wrpkru:
            return "wrpkru";
        case Mnemonic::Wrssd:
            return "wrssd";
        case Mnemonic::Wrssq:
            return "wrssq";
        case Mnemonic::Wrussd:
            return "wrussd";
        case Mnemonic::Wrussq:
            return "wrussq";
        case Mnemonic::Xabort:
            return "xabort";
        case Mnemonic::Xadd:
            return "xadd";
        case Mnemonic::Xbegin:
            return "xbegin";
        case Mnemonic::Xchg:
            return "xchg";
        case Mnemonic::Xcrypt_cbc:
            return "xcrypt_cbc";
        case Mnemonic::Xcrypt_cfb:
            return "xcrypt_cfb";
        case Mnemonic::Xcrypt_ctr:
            return "xcrypt_ctr";
        case Mnemonic::Xcrypt_ecb:
            return "xcrypt_ecb";
        case Mnemonic::Xcrypt_ofb:
            return "xcrypt_ofb";
        case Mnemonic::Xend:
            return "xend";
        case Mnemonic::Xgetbv:
            return "xgetbv";
        case Mnemonic::Xlat:
            return "xlat";
        case Mnemonic::Xor:
            return "xor";
        case Mnemonic::Xorpd:
            return "xorpd";
        case Mnemonic::Xorps:
            return "xorps";
        case Mnemonic::Xresldtrk:
            return "xresldtrk";
        case Mnemonic::Xrstor:
            return "xrstor";
        case Mnemonic::Xrstor64:
            return "xrstor64";
        case Mnemonic::Xrstors:
            return "xrstors";
        case Mnemonic::Xrstors64:
            return "xrstors64";
        case Mnemonic::Xsave:
            return "xsave";
        case Mnemonic::Xsave64:
            return "xsave64";
        case Mnemonic::Xsavec:
            return "xsavec";
        case Mnemonic::Xsavec64:
            return "xsavec64";
        case Mnemonic::Xsaveopt:
            return "xsaveopt";
        case Mnemonic::Xsaveopt64:
            return "xsaveopt64";
        case Mnemonic::Xsaves:
            return "xsaves";
        case Mnemonic::Xsaves64:
            return "xsaves64";
        case Mnemonic::Xsetbv:
            return "xsetbv";
        case Mnemonic::Xsha1:
            return "xsha1";
        case Mnemonic::Xsha256:
            return "xsha256";
        case Mnemonic::Xstore:
            return "xstore";
        case Mnemonic::Xsusldtrk:
            return "xsusldtrk";
        case Mnemonic::Xtest:
            return "xtest";
        }
        return "invalid";
    }

}
