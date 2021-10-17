.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSiRawReadIo
/* 011168 0x8008AEE0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 011169 0x8008AEE4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 011170 0x8008AEE8 AFA40018 */ sw	$a0, 0X18($sp)
/* 011171 0x8008AEEC 0C023E8C */ jal	__osSiDeviceBusy
/* 011172 0x8008AEF0 AFA5001C */ sw	$a1, 0X1C($sp)
/* 011173 0x8008AEF4 10400003 */ beqz	$v0, .L8008AF04
/* 011174 0x8008AEF8 8FAE0018 */ lw	$t6, 0X18($sp)
/* 011175 0x8008AEFC 10000007 */ b	.L8008AF1C
/* 011176 0x8008AF00 2402FFFF */ li	$v0, -0X1
.L8008AF04:
/* 011177 0x8008AF04 3C01A000 */ lui	$at, 0xA000
/* 011178 0x8008AF08 01C17825 */ or	$t7, $t6, $at
/* 011179 0x8008AF0C 8DF80000 */ lw	$t8, 0X0($t7)
/* 011180 0x8008AF10 8FB9001C */ lw	$t9, 0X1C($sp)
/* 011181 0x8008AF14 00001025 */ move	$v0, $zero
/* 011182 0x8008AF18 AF380000 */ sw	$t8, 0X0($t9)
.L8008AF1C:
/* 011183 0x8008AF1C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011184 0x8008AF20 27BD0018 */ addiu	$sp, $sp, 0X18
/* 011185 0x8008AF24 03E00008 */ jr	$ra
/* 011186 0x8008AF28 00000000 */ nop
/* 011187 0x8008AF2C 00000000 */ nop
