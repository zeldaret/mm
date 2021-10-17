.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_800967A0
/* 022992 0x800967A0 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 022993 0x800967A4 AFBF001C */ sw	$ra, 0X1C($sp)
/* 022994 0x800967A8 AFA40028 */ sw	$a0, 0X28($sp)
/* 022995 0x800967AC AFA5002C */ sw	$a1, 0X2C($sp)
/* 022996 0x800967B0 AFA60030 */ sw	$a2, 0X30($sp)
/* 022997 0x800967B4 0C024698 */ jal	__osDisableInt
/* 022998 0x800967B8 AFB00018 */ sw	$s0, 0X18($sp)
/* 022999 0x800967BC 8FAF0028 */ lw	$t7, 0X28($sp)
/* 023000 0x800967C0 8FAE002C */ lw	$t6, 0X2C($sp)
/* 023001 0x800967C4 8FA80028 */ lw	$t0, 0X28($sp)
/* 023002 0x800967C8 3C018009 */ lui	$at, %hi(D_80097DE0)
/* 023003 0x800967CC 000FC0C0 */ sll	$t8, $t7, 3
/* 023004 0x800967D0 00380821 */ addu	$at, $at, $t8
/* 023005 0x800967D4 AC2E7DE0 */ sw	$t6, %lo(D_80097DE0)($at)
/* 023006 0x800967D8 8FB90030 */ lw	$t9, 0X30($sp)
/* 023007 0x800967DC 3C018009 */ lui	$at, %hi(D_80097DE4)
/* 023008 0x800967E0 000848C0 */ sll	$t1, $t0, 3
/* 023009 0x800967E4 00408025 */ move	$s0, $v0
/* 023010 0x800967E8 00290821 */ addu	$at, $at, $t1
/* 023011 0x800967EC 02002025 */ move	$a0, $s0
/* 023012 0x800967F0 0C0246B4 */ jal	__osRestoreInt
/* 023013 0x800967F4 AC397DE4 */ sw	$t9, %lo(D_80097DE4)($at)
/* 023014 0x800967F8 8FBF001C */ lw	$ra, 0X1C($sp)
/* 023015 0x800967FC 8FB00018 */ lw	$s0, 0X18($sp)
/* 023016 0x80096800 27BD0028 */ addiu	$sp, $sp, 0X28
/* 023017 0x80096804 03E00008 */ jr	$ra
/* 023018 0x80096808 00000000 */ nop
/* 023019 0x8009680C 00000000 */ nop
