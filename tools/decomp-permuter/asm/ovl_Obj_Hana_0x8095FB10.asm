.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel ObjHana_Init
/* 000000 0x8095FB10 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x8095FB14 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x8095FB18 AFA5001C */ sw	$a1, 0X1C($sp)
/* 000003 0x8095FB1C 3C058096 */ lui	$a1, %hi(D_8095FBB0)
/* 000004 0x8095FB20 0C03FEB7 */ jal	Actor_ProcessInitChain
/* 000005 0x8095FB24 24A5FBB0 */ addiu	$a1, $a1, %lo(D_8095FBB0)
/* 000006 0x8095FB28 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000007 0x8095FB2C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000008 0x8095FB30 03E00008 */ jr	$ra
/* 000009 0x8095FB34 00000000 */ nop

glabel ObjHana_Destroy
/* 000010 0x8095FB38 AFA40000 */ sw	$a0, 0X0($sp)
/* 000011 0x8095FB3C AFA50004 */ sw	$a1, 0X4($sp)
/* 000012 0x8095FB40 03E00008 */ jr	$ra
/* 000013 0x8095FB44 00000000 */ nop

glabel ObjHana_Update
/* 000014 0x8095FB48 AFA40000 */ sw	$a0, 0X0($sp)
/* 000015 0x8095FB4C AFA50004 */ sw	$a1, 0X4($sp)
/* 000016 0x8095FB50 03E00008 */ jr	$ra
/* 000017 0x8095FB54 00000000 */ nop

glabel ObjHana_Draw
/* 000018 0x8095FB58 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000019 0x8095FB5C AFBF0014 */ sw	$ra, 0X14($sp)
/* 000020 0x8095FB60 AFA40018 */ sw	$a0, 0X18($sp)
/* 000021 0x8095FB64 00A03025 */ move	$a2, $a1
/* 000022 0x8095FB68 3C050600 */ lui	$a1, 0x0600
/* 000023 0x8095FB6C 24A50500 */ addiu	$a1, $a1, 0X500
/* 000024 0x8095FB70 0C02F7F0 */ jal	func_800BDFC0
/* 000025 0x8095FB74 00C02025 */ move	$a0, $a2
/* 000026 0x8095FB78 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000027 0x8095FB7C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000028 0x8095FB80 03E00008 */ jr	$ra
/* 000029 0x8095FB84 00000000 */ nop
/* 000030 0x8095FB88 00000000 */ nop
/* 000031 0x8095FB8C 00000000 */ nop
