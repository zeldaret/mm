.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel sqrtf
/* 013736 0x8008D700 03E00008 */ jr	$ra
/* 013737 0x8008D704 46006004 */ sqrt.s	$f0, $f12
/* 013738 0x8008D708 00000000 */ nop
/* 013739 0x8008D70C 00000000 */ nop
