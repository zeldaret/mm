.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_8008FA60
/* 016000 0x8008FA60 20080001 */ addi	$t0, $zero, 0X1
/* 016001 0x8008FA64 00084C00 */ sll	$t1, $t0, 16
/* 016002 0x8008FA68 AC890000 */ sw	$t1, 0X0($a0)
/* 016003 0x8008FA6C AC800004 */ sw	$zero, 0X4($a0)
/* 016004 0x8008FA70 AC880008 */ sw	$t0, 0X8($a0)
/* 016005 0x8008FA74 AC80000C */ sw	$zero, 0XC($a0)
/* 016006 0x8008FA78 AC800010 */ sw	$zero, 0X10($a0)
/* 016007 0x8008FA7C AC890014 */ sw	$t1, 0X14($a0)
/* 016008 0x8008FA80 AC800018 */ sw	$zero, 0X18($a0)
/* 016009 0x8008FA84 AC88001C */ sw	$t0, 0X1C($a0)
/* 016010 0x8008FA88 AC800020 */ sw	$zero, 0X20($a0)
/* 016011 0x8008FA8C AC800024 */ sw	$zero, 0X24($a0)
/* 016012 0x8008FA90 AC800028 */ sw	$zero, 0X28($a0)
/* 016013 0x8008FA94 AC80002C */ sw	$zero, 0X2C($a0)
/* 016014 0x8008FA98 AC800030 */ sw	$zero, 0X30($a0)
/* 016015 0x8008FA9C AC800034 */ sw	$zero, 0X34($a0)
/* 016016 0x8008FAA0 AC800038 */ sw	$zero, 0X38($a0)
/* 016017 0x8008FAA4 03E00008 */ jr	$ra
/* 016018 0x8008FAA8 AC80003C */ sw	$zero, 0X3C($a0)
/* 016019 0x8008FAAC 00000000 */ nop
