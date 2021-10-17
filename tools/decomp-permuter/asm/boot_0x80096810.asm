.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetWatchLo
/* 023020 0x80096810 40029000 */ mfc0	$v0, $18
/* 023021 0x80096814 03E00008 */ jr	$ra
/* 023022 0x80096818 00000000 */ nop
/* 023023 0x8009681C 00000000 */ nop
