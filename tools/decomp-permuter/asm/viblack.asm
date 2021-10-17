.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osViBlack
/* 011140 0x8008AE70 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 011141 0x8008AE74 AFBF0014 */ sw	$ra, 0X14($sp)
/* 011142 0x8008AE78 0C024698 */ jal	__osDisableInt
/* 011143 0x8008AE7C AFA40018 */ sw	$a0, 0X18($sp)
/* 011144 0x8008AE80 93AE001B */ lbu	$t6, 0X1B($sp)
/* 011145 0x8008AE84 00402025 */ move	$a0, $v0
/* 011146 0x8008AE88 3C02800A */ lui	$v0, %hi(__osViNext)
/* 011147 0x8008AE8C 11C00007 */ beqz	$t6, .L8008AEAC
/* 011148 0x8008AE90 00000000 */ nop
/* 011149 0x8008AE94 3C02800A */ lui	$v0, %hi(__osViNext)
/* 011150 0x8008AE98 8C4280C4 */ lw	$v0, %lo(__osViNext)($v0)
/* 011151 0x8008AE9C 944F0000 */ lhu	$t7, 0X0($v0)
/* 011152 0x8008AEA0 35F80020 */ ori	$t8, $t7, 0X20
/* 011153 0x8008AEA4 10000005 */ b	.L8008AEBC
/* 011154 0x8008AEA8 A4580000 */ sh	$t8, 0X0($v0)
.L8008AEAC:
/* 011155 0x8008AEAC 8C4280C4 */ lw	$v0, %lo(__osViNext)($v0)
/* 011156 0x8008AEB0 94590000 */ lhu	$t9, 0X0($v0)
/* 011157 0x8008AEB4 3328FFDF */ andi	$t0, $t9, 0XFFDF
/* 011158 0x8008AEB8 A4480000 */ sh	$t0, 0X0($v0)
.L8008AEBC:
/* 011159 0x8008AEBC 0C0246B4 */ jal	__osRestoreInt
/* 011160 0x8008AEC0 00000000 */ nop
/* 011161 0x8008AEC4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011162 0x8008AEC8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 011163 0x8008AECC 03E00008 */ jr	$ra
/* 011164 0x8008AED0 00000000 */ nop
/* 011165 0x8008AED4 00000000 */ nop
/* 011166 0x8008AED8 00000000 */ nop
/* 011167 0x8008AEDC 00000000 */ nop
