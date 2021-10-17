.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80087E00
/* 008040 0x80087E00 3C01800A */ lui	$at, %hi(D_8009817C)
/* 008041 0x80087E04 03E00008 */ jr	$ra
/* 008042 0x80087E08 AC24817C */ sw	$a0, %lo(D_8009817C)($at)
/* 008043 0x80087E0C 00000000 */ nop
