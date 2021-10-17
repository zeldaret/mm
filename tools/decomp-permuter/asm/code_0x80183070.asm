.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80183070
/* 226668 0x80183070 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 226669 0x80183074 AFBF0014 */ sw	$ra, 0X14($sp)
.L80183078:
/* 226670 0x80183078 0C021E9B */ jal	func_80087A6C
/* 226671 0x8018307C 240403E8 */ li	$a0, 0X3E8
/* 226672 0x80183080 1000FFFD */ b	.L80183078
/* 226673 0x80183084 00000000 */ nop
/* 226674 0x80183088 8FBF0014 */ lw	$ra, 0X14($sp)
/* 226675 0x8018308C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 226676 0x80183090 03E00008 */ jr	$ra
/* 226677 0x80183094 00000000 */ nop
/* 226678 0x80183098 00000000 */ nop
/* 226679 0x8018309C 00000000 */ nop
