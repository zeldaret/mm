.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osDpGetStatus
/* 017552 0x800912A0 3C0EA410 */ lui	$t6, 0xA410
/* 017553 0x800912A4 03E00008 */ jr	$ra
/* 017554 0x800912A8 8DC2000C */ lw	$v0, 0XC($t6)
/* 017555 0x800912AC 00000000 */ nop
