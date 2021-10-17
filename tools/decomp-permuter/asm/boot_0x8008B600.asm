.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel guMtxIdentF
/* 011624 0x8008B600 3C083F80 */ lui	$t0, 0x3F80
/* 011625 0x8008B604 AC880000 */ sw	$t0, 0X0($a0)
/* 011626 0x8008B608 AC800004 */ sw	$zero, 0X4($a0)
/* 011627 0x8008B60C AC800008 */ sw	$zero, 0X8($a0)
/* 011628 0x8008B610 AC80000C */ sw	$zero, 0XC($a0)
/* 011629 0x8008B614 AC800010 */ sw	$zero, 0X10($a0)
/* 011630 0x8008B618 AC880014 */ sw	$t0, 0X14($a0)
/* 011631 0x8008B61C AC800018 */ sw	$zero, 0X18($a0)
/* 011632 0x8008B620 AC80001C */ sw	$zero, 0X1C($a0)
/* 011633 0x8008B624 AC800020 */ sw	$zero, 0X20($a0)
/* 011634 0x8008B628 AC800024 */ sw	$zero, 0X24($a0)
/* 011635 0x8008B62C AC880028 */ sw	$t0, 0X28($a0)
/* 011636 0x8008B630 AC80002C */ sw	$zero, 0X2C($a0)
/* 011637 0x8008B634 AC800030 */ sw	$zero, 0X30($a0)
/* 011638 0x8008B638 AC800034 */ sw	$zero, 0X34($a0)
/* 011639 0x8008B63C AC800038 */ sw	$zero, 0X38($a0)
/* 011640 0x8008B640 03E00008 */ jr	$ra
/* 011641 0x8008B644 AC88003C */ sw	$t0, 0X3C($a0)
/* 011642 0x8008B648 00000000 */ nop
/* 011643 0x8008B64C 00000000 */ nop
