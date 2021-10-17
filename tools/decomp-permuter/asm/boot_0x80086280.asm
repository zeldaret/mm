.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel assert_fail
/* 006280 0x80086280 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 006281 0x80086284 AFBF0014 */ sw	$ra, 0X14($sp)
/* 006282 0x80086288 AFA40018 */ sw	$a0, 0X18($sp)
/* 006283 0x8008628C AFA5001C */ sw	$a1, 0X1C($sp)
/* 006284 0x80086290 0C022BCC */ jal	osGetThreadId
/* 006285 0x80086294 00002025 */ move	$a0, $zero
/* 006286 0x80086298 8FA40018 */ lw	$a0, 0X18($sp)
/* 006287 0x8008629C 0C020F93 */ jal	Fault_AddHungupAndCrash
/* 006288 0x800862A0 8FA5001C */ lw	$a1, 0X1C($sp)
/* 006289 0x800862A4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 006290 0x800862A8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 006291 0x800862AC 03E00008 */ jr	$ra
/* 006292 0x800862B0 00000000 */ nop

glabel func_800862B4
/* 006293 0x800862B4 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 006294 0x800862B8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 006295 0x800862BC 3C04800A */ lui	$a0, %hi(D_800990B0)
/* 006296 0x800862C0 248490B0 */ addiu	$a0, $a0, %lo(D_800990B0)
/* 006297 0x800862C4 0C020F93 */ jal	Fault_AddHungupAndCrash
/* 006298 0x800862C8 00002825 */ move	$a1, $zero
/* 006299 0x800862CC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 006300 0x800862D0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 006301 0x800862D4 03E00008 */ jr	$ra
/* 006302 0x800862D8 00000000 */ nop
/* 006303 0x800862DC 00000000 */ nop
