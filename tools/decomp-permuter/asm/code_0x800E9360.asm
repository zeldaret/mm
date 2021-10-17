.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_800E9360
/* 069160 0x800E9360 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 069161 0x800E9364 3C04801F */ lui	$a0, %hi(gSaveContext)
/* 069162 0x800E9368 2484F670 */ addiu	$a0, $a0, %lo(gSaveContext)
/* 069163 0x800E936C AFBF0014 */ sw	$ra, 0X14($sp)
/* 069164 0x800E9370 0C02258C */ jal	bzero
/* 069165 0x800E9374 240548E8 */ li	$a1, 0X48E8
/* 069166 0x800E9378 3C04801F */ lui	$a0, %hi(gSaveContext)
/* 069167 0x800E937C 2484F670 */ addiu	$a0, $a0, %lo(gSaveContext)
/* 069168 0x800E9380 240200FF */ li	$v0, 0XFF
/* 069169 0x800E9384 24030001 */ li	$v1, 0X1
/* 069170 0x800E9388 340EFFEF */ ori	$t6, $zero, 0XFFEF
/* 069171 0x800E938C 340FFFFF */ ori	$t7, $zero, 0XFFFF
/* 069172 0x800E9390 24180032 */ li	$t8, 0X32
/* 069173 0x800E9394 A0800020 */ sb	$zero, 0X20($a0)
/* 069174 0x800E9398 A0823F16 */ sb	$v0, 0X3F16($a0)
/* 069175 0x800E939C A0823F17 */ sb	$v0, 0X3F17($a0)
/* 069176 0x800E93A0 A4803F46 */ sh	$zero, 0X3F46($a0)
/* 069177 0x800E93A4 A48E3F4A */ sh	$t6, 0X3F4A($a0)
/* 069178 0x800E93A8 A0803F4C */ sb	$zero, 0X3F4C($a0)
/* 069179 0x800E93AC A0803F4D */ sb	$zero, 0X3F4D($a0)
/* 069180 0x800E93B0 A48F3F4E */ sh	$t7, 0X3F4E($a0)
/* 069181 0x800E93B4 A4803F52 */ sh	$zero, 0X3F52($a0)
/* 069182 0x800E93B8 A0833F54 */ sb	$v1, 0X3F54($a0)
/* 069183 0x800E93BC A0823F55 */ sb	$v0, 0X3F55($a0)
/* 069184 0x800E93C0 A4983F26 */ sh	$t8, 0X3F26($a0)
/* 069185 0x800E93C4 A0833F42 */ sb	$v1, 0X3F42($a0)
/* 069186 0x800E93C8 A0803F43 */ sb	$zero, 0X3F43($a0)
/* 069187 0x800E93CC A0803F45 */ sb	$zero, 0X3F45($a0)
/* 069188 0x800E93D0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 069189 0x800E93D4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 069190 0x800E93D8 03E00008 */ jr	$ra
/* 069191 0x800E93DC 00000000 */ nop
