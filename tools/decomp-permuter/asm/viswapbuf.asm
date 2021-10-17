.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osViSwapBuffer
/* 016256 0x8008FE60 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 016257 0x8008FE64 AFBF0014 */ sw	$ra, 0X14($sp)
/* 016258 0x8008FE68 0C024698 */ jal	__osDisableInt
/* 016259 0x8008FE6C AFA40018 */ sw	$a0, 0X18($sp)
/* 016260 0x8008FE70 3C05800A */ lui	$a1, %hi(__osViNext)
/* 016261 0x8008FE74 24A580C4 */ addiu	$a1, $a1, %lo(__osViNext)
/* 016262 0x8008FE78 8CAF0000 */ lw	$t7, 0X0($a1)
/* 016263 0x8008FE7C 8FAE0018 */ lw	$t6, 0X18($sp)
/* 016264 0x8008FE80 00402025 */ move	$a0, $v0
/* 016265 0x8008FE84 ADEE0004 */ sw	$t6, 0X4($t7)
/* 016266 0x8008FE88 8CA30000 */ lw	$v1, 0X0($a1)
/* 016267 0x8008FE8C 94780000 */ lhu	$t8, 0X0($v1)
/* 016268 0x8008FE90 37190010 */ ori	$t9, $t8, 0X10
/* 016269 0x8008FE94 0C0246B4 */ jal	__osRestoreInt
/* 016270 0x8008FE98 A4790000 */ sh	$t9, 0X0($v1)
/* 016271 0x8008FE9C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 016272 0x8008FEA0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 016273 0x8008FEA4 03E00008 */ jr	$ra
/* 016274 0x8008FEA8 00000000 */ nop
/* 016275 0x8008FEAC 00000000 */ nop
