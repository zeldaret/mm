.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80096770
/* 022980 0x80096770 000470C0 */ sll	$t6, $a0, 3
/* 022981 0x80096774 3C0F8009 */ lui	$t7, %hi(D_80097DE0)
/* 022982 0x80096778 01EE7821 */ addu	$t7, $t7, $t6
/* 022983 0x8009677C 8DEF7DE0 */ lw	$t7, %lo(D_80097DE0)($t7)
/* 022984 0x80096780 0004C0C0 */ sll	$t8, $a0, 3
/* 022985 0x80096784 3C198009 */ lui	$t9, %hi(D_80097DE4)
/* 022986 0x80096788 0338C821 */ addu	$t9, $t9, $t8
/* 022987 0x8009678C ACAF0000 */ sw	$t7, 0X0($a1)
/* 022988 0x80096790 8F397DE4 */ lw	$t9, %lo(D_80097DE4)($t9)
/* 022989 0x80096794 03E00008 */ jr	$ra
/* 022990 0x80096798 ACD90000 */ sw	$t9, 0X0($a2)
/* 022991 0x8009679C 00000000 */ nop
