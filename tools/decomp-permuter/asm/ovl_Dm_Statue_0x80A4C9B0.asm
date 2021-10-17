.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel DmStatue_Init
/* 000000 0x80A4C9B0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x80A4C9B4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x80A4C9B8 AFA5001C */ sw	$a1, 0X1C($sp)
/* 000003 0x80A4C9BC 0C02D9F8 */ jal	Actor_SetScale
/* 000004 0x80A4C9C0 3C054120 */ lui	$a1, 0x4120
/* 000005 0x80A4C9C4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000006 0x80A4C9C8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000007 0x80A4C9CC 03E00008 */ jr	$ra
/* 000008 0x80A4C9D0 00000000 */ nop

glabel DmStatue_Destroy
/* 000009 0x80A4C9D4 AFA40000 */ sw	$a0, 0X0($sp)
/* 000010 0x80A4C9D8 AFA50004 */ sw	$a1, 0X4($sp)
/* 000011 0x80A4C9DC 03E00008 */ jr	$ra
/* 000012 0x80A4C9E0 00000000 */ nop

glabel DmStatue_Update
/* 000013 0x80A4C9E4 AFA40000 */ sw	$a0, 0X0($sp)
/* 000014 0x80A4C9E8 AFA50004 */ sw	$a1, 0X4($sp)
/* 000015 0x80A4C9EC 03E00008 */ jr	$ra
/* 000016 0x80A4C9F0 00000000 */ nop

glabel DmStatue_Draw
/* 000017 0x80A4C9F4 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000018 0x80A4C9F8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000019 0x80A4C9FC AFA40018 */ sw	$a0, 0X18($sp)
/* 000020 0x80A4CA00 AFA5001C */ sw	$a1, 0X1C($sp)
/* 000021 0x80A4CA04 3C040600 */ lui	$a0, 0x0600
/* 000022 0x80A4CA08 0C040141 */ jal	Lib_PtrSegToVirt
/* 000023 0x80A4CA0C 24841788 */ addiu	$a0, $a0, 0X1788
/* 000024 0x80A4CA10 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000025 0x80A4CA14 0C04C5D6 */ jal	SceneProc_DrawAllSceneAnimatedTextures
/* 000026 0x80A4CA18 00402825 */ move	$a1, $v0
/* 000027 0x80A4CA1C 3C050600 */ lui	$a1, 0x0600
/* 000028 0x80A4CA20 24A50520 */ addiu	$a1, $a1, 0X520
/* 000029 0x80A4CA24 0C02F80F */ jal	func_800BE03C
/* 000030 0x80A4CA28 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000031 0x80A4CA2C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000032 0x80A4CA30 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000033 0x80A4CA34 03E00008 */ jr	$ra
/* 000034 0x80A4CA38 00000000 */ nop
/* 000035 0x80A4CA3C 00000000 */ nop
