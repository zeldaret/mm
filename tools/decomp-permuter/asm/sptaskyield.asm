.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osSpTaskYield
/* 011196 0x8008AF50 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 011197 0x8008AF54 AFBF0014 */ sw	$ra, 0X14($sp)
/* 011198 0x8008AF58 0C0254A0 */ jal	__osSpSetStatus
/* 011199 0x8008AF5C 24040400 */ li	$a0, 0X400
/* 011200 0x8008AF60 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011201 0x8008AF64 27BD0018 */ addiu	$sp, $sp, 0X18
/* 011202 0x8008AF68 03E00008 */ jr	$ra
/* 011203 0x8008AF6C 00000000 */ nop
