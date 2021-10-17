.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetCurrFaultedThread
/* 021860 0x800955F0 3C028009 */ lui	$v0, %hi(__osFaultedThread)
/* 021861 0x800955F4 03E00008 */ jr	$ra
/* 021862 0x800955F8 8C427E24 */ lw	$v0, %lo(__osFaultedThread)($v0)
/* 021863 0x800955FC 00000000 */ nop
