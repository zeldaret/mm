.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_8008AE20
/* 011120 0x8008AE20 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 011121 0x8008AE24 AFBF0014 */ sw	$ra, 0X14($sp)
/* 011122 0x8008AE28 0C024698 */ jal	__osDisableInt
/* 011123 0x8008AE2C AFA40018 */ sw	$a0, 0X18($sp)
/* 011124 0x8008AE30 3C038009 */ lui	$v1, %hi(__osPiTable)
/* 011125 0x8008AE34 24637E8C */ addiu	$v1, $v1, %lo(__osPiTable)
/* 011126 0x8008AE38 8FA50018 */ lw	$a1, 0X18($sp)
/* 011127 0x8008AE3C 8C6E0000 */ lw	$t6, 0X0($v1)
/* 011128 0x8008AE40 00402025 */ move	$a0, $v0
/* 011129 0x8008AE44 ACAE0000 */ sw	$t6, 0X0($a1)
/* 011130 0x8008AE48 0C0246B4 */ jal	__osRestoreInt
/* 011131 0x8008AE4C AC650000 */ sw	$a1, 0X0($v1)
/* 011132 0x8008AE50 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011133 0x8008AE54 27BD0018 */ addiu	$sp, $sp, 0X18
/* 011134 0x8008AE58 00001025 */ move	$v0, $zero
/* 011135 0x8008AE5C 03E00008 */ jr	$ra
/* 011136 0x8008AE60 00000000 */ nop
/* 011137 0x8008AE64 00000000 */ nop
/* 011138 0x8008AE68 00000000 */ nop
/* 011139 0x8008AE6C 00000000 */ nop
