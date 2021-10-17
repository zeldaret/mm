.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osViGetCurrentContext
/* 021844 0x800955B0 3C02800A */ lui	$v0, %hi(__osViCurr)
/* 021845 0x800955B4 03E00008 */ jr	$ra
/* 021846 0x800955B8 8C4280C0 */ lw	$v0, %lo(__osViCurr)($v0)
/* 021847 0x800955BC 00000000 */ nop
