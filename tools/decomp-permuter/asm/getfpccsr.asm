.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetFpcCsr
/* 019236 0x80092CF0 4442F800 */ cfc1	$v0, $31
/* 019237 0x80092CF4 03E00008 */ jr	$ra
/* 019238 0x80092CF8 00000000 */ nop
/* 019239 0x80092CFC 00000000 */ nop
