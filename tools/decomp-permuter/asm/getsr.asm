.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetSR
/* 010584 0x8008A5C0 40026000 */ mfc0	$v0, $12
/* 010585 0x8008A5C4 03E00008 */ jr	$ra
/* 010586 0x8008A5C8 00000000 */ nop
/* 010587 0x8008A5CC 00000000 */ nop
