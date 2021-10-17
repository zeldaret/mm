.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSiDeviceBusy
/* 015988 0x8008FA30 3C0EA480 */ lui	$t6, 0xA480
/* 015989 0x8008FA34 8DC20018 */ lw	$v0, 0X18($t6)
/* 015990 0x8008FA38 304F0003 */ andi	$t7, $v0, 0X3
/* 015991 0x8008FA3C 11E00003 */ beqz	$t7, .L8008FA4C
/* 015992 0x8008FA40 00001025 */ move	$v0, $zero
/* 015993 0x8008FA44 03E00008 */ jr	$ra
/* 015994 0x8008FA48 24020001 */ li	$v0, 0X1
.L8008FA4C:
/* 015995 0x8008FA4C 03E00008 */ jr	$ra
/* 015996 0x8008FA50 00000000 */ nop
/* 015997 0x8008FA54 00000000 */ nop
/* 015998 0x8008FA58 00000000 */ nop
/* 015999 0x8008FA5C 00000000 */ nop
