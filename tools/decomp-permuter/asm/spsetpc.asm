.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSpSetPc
/* 022828 0x80096510 3C0EA404 */ lui	$t6, 0xA404
/* 022829 0x80096514 8DC20010 */ lw	$v0, 0X10($t6)
/* 022830 0x80096518 3C18A408 */ lui	$t8, 0xA408
/* 022831 0x8009651C 304F0001 */ andi	$t7, $v0, 0X1
/* 022832 0x80096520 15E00003 */ bnez	$t7, .L80096530
/* 022833 0x80096524 00001025 */ move	$v0, $zero
/* 022834 0x80096528 03E00008 */ jr	$ra
/* 022835 0x8009652C 2402FFFF */ li	$v0, -0X1
.L80096530:
/* 022836 0x80096530 AF040000 */ sw	$a0, 0X0($t8)
/* 022837 0x80096534 03E00008 */ jr	$ra
/* 022838 0x80096538 00000000 */ nop
/* 022839 0x8009653C 00000000 */ nop
