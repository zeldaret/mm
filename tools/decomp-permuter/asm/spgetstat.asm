.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSpGetStatus
/* 021636 0x80095270 3C0EA404 */ lui	$t6, 0xA404
/* 021637 0x80095274 03E00008 */ jr	$ra
/* 021638 0x80095278 8DC20010 */ lw	$v0, 0X10($t6)
/* 021639 0x8009527C 00000000 */ nop
