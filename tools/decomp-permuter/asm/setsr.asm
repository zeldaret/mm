.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSetSR
/* 010588 0x8008A5D0 40846000 */ mtc0	$a0, $12
/* 010589 0x8008A5D4 00000000 */ nop
/* 010590 0x8008A5D8 03E00008 */ jr	$ra
/* 010591 0x8008A5DC 00000000 */ nop
