.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSetFpcCsr
/* 019232 0x80092CE0 4442F800 */ cfc1	$v0, $31
/* 019233 0x80092CE4 44C4F800 */ ctc1	$a0, $31
/* 019234 0x80092CE8 03E00008 */ jr	$ra
/* 019235 0x80092CEC 00000000 */ nop
