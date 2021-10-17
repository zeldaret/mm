.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetCause
/* 020300 0x80093D90 40026800 */ mfc0	$v0, $13
/* 020301 0x80093D94 03E00008 */ jr	$ra
/* 020302 0x80093D98 00000000 */ nop
/* 020303 0x80093D9C 00000000 */ nop
