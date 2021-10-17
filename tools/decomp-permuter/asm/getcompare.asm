.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetCompare
/* 017548 0x80091290 40025800 */ mfc0	$v0, $11
/* 017549 0x80091294 03E00008 */ jr	$ra
/* 017550 0x80091298 00000000 */ nop
/* 017551 0x8009129C 00000000 */ nop
