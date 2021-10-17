.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel BgIkanaRay_Init
/* 000000 0x80BD53C0 27BDFFD0 */ addiu	$sp, $sp, -0X30
/* 000001 0x80BD53C4 AFB00018 */ sw	$s0, 0X18($sp)
/* 000002 0x80BD53C8 00808025 */ move	$s0, $a0
/* 000003 0x80BD53CC AFBF001C */ sw	$ra, 0X1C($sp)
/* 000004 0x80BD53D0 AFA50034 */ sw	$a1, 0X34($sp)
/* 000005 0x80BD53D4 3C0580BD */ lui	$a1, %hi(bgIkanaRayCompInit)
/* 000006 0x80BD53D8 24A5561C */ addiu	$a1, $a1, %lo(bgIkanaRayCompInit)
/* 000007 0x80BD53DC 0C03FEB7 */ jal	Actor_ProcessInitChain
/* 000008 0x80BD53E0 02002025 */ move	$a0, $s0
/* 000009 0x80BD53E4 26050144 */ addiu	$a1, $s0, 0X144
/* 000010 0x80BD53E8 AFA50024 */ sw	$a1, 0X24($sp)
/* 000011 0x80BD53EC 0C038467 */ jal	Collision_InitCylinderDefault
/* 000012 0x80BD53F0 8FA40034 */ lw	$a0, 0X34($sp)
/* 000013 0x80BD53F4 3C0780BD */ lui	$a3, %hi(bgIkanaRayCylinderInit)
/* 000014 0x80BD53F8 24E755F0 */ addiu	$a3, $a3, %lo(bgIkanaRayCylinderInit)
/* 000015 0x80BD53FC 8FA40034 */ lw	$a0, 0X34($sp)
/* 000016 0x80BD5400 8FA50024 */ lw	$a1, 0X24($sp)
/* 000017 0x80BD5404 0C0384C3 */ jal	Collision_InitCylinderWithData
/* 000018 0x80BD5408 02003025 */ move	$a2, $s0
/* 000019 0x80BD540C 02002025 */ move	$a0, $s0
/* 000020 0x80BD5410 0C039F7E */ jal	Collision_CylinderMoveToActor
/* 000021 0x80BD5414 8FA50024 */ lw	$a1, 0X24($sp)
/* 000022 0x80BD5418 3C040600 */ lui	$a0, 0x0600
/* 000023 0x80BD541C 0C040141 */ jal	Lib_PtrSegToVirt
/* 000024 0x80BD5420 24841228 */ addiu	$a0, $a0, 0X1228
/* 000025 0x80BD5424 8605001C */ lh	$a1, 0X1C($s0)
/* 000026 0x80BD5428 AE020190 */ sw	$v0, 0X190($s0)
/* 000027 0x80BD542C 8FA40034 */ lw	$a0, 0X34($sp)
/* 000028 0x80BD5430 0C02D6EC */ jal	Actor_GetSwitchFlag
/* 000029 0x80BD5434 30A5007F */ andi	$a1, $a1, 0X7F
/* 000030 0x80BD5438 10400005 */ beqz	$v0, .L80BD5450
/* 000031 0x80BD543C 00000000 */ nop
/* 000032 0x80BD5440 0C2F5540 */ jal	BgIkanaRay_SetActivated
/* 000033 0x80BD5444 02002025 */ move	$a0, $s0
/* 000034 0x80BD5448 10000004 */ b	.L80BD545C
/* 000035 0x80BD544C 8FBF001C */ lw	$ra, 0X1C($sp)
.L80BD5450:
/* 000036 0x80BD5450 0C2F5526 */ jal	BgIkanaRay_SetDeactivated
/* 000037 0x80BD5454 02002025 */ move	$a0, $s0
/* 000038 0x80BD5458 8FBF001C */ lw	$ra, 0X1C($sp)
.L80BD545C:
/* 000039 0x80BD545C 8FB00018 */ lw	$s0, 0X18($sp)
/* 000040 0x80BD5460 27BD0030 */ addiu	$sp, $sp, 0X30
/* 000041 0x80BD5464 03E00008 */ jr	$ra
/* 000042 0x80BD5468 00000000 */ nop

glabel BgIkanaRay_Destroy
/* 000043 0x80BD546C 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000044 0x80BD5470 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000045 0x80BD5474 00803025 */ move	$a2, $a0
/* 000046 0x80BD5478 00A03825 */ move	$a3, $a1
/* 000047 0x80BD547C 00E02025 */ move	$a0, $a3
/* 000048 0x80BD5480 0C03847B */ jal	Collision_FiniCylinder
/* 000049 0x80BD5484 24C50144 */ addiu	$a1, $a2, 0X144
/* 000050 0x80BD5488 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000051 0x80BD548C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000052 0x80BD5490 03E00008 */ jr	$ra
/* 000053 0x80BD5494 00000000 */ nop

glabel BgIkanaRay_SetDeactivated
/* 000054 0x80BD5498 8C8E0004 */ lw	$t6, 0X4($a0)
/* 000055 0x80BD549C 3C1880BD */ lui	$t8, %hi(BgIkanaRay_UpdateCheckForActivation)
/* 000056 0x80BD54A0 271854BC */ addiu	$t8, $t8, %lo(BgIkanaRay_UpdateCheckForActivation)
/* 000057 0x80BD54A4 35CF0010 */ ori	$t7, $t6, 0X10
/* 000058 0x80BD54A8 AC80013C */ sw	$zero, 0X13C($a0)
/* 000059 0x80BD54AC AC8F0004 */ sw	$t7, 0X4($a0)
/* 000060 0x80BD54B0 AC980194 */ sw	$t8, 0X194($a0)
/* 000061 0x80BD54B4 03E00008 */ jr	$ra
/* 000062 0x80BD54B8 00000000 */ nop

glabel BgIkanaRay_UpdateCheckForActivation
/* 000063 0x80BD54BC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000064 0x80BD54C0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000065 0x80BD54C4 AFA40018 */ sw	$a0, 0X18($sp)
/* 000066 0x80BD54C8 00A03025 */ move	$a2, $a1
/* 000067 0x80BD54CC 8FAE0018 */ lw	$t6, 0X18($sp)
/* 000068 0x80BD54D0 00C02025 */ move	$a0, $a2
/* 000069 0x80BD54D4 85C5001C */ lh	$a1, 0X1C($t6)
/* 000070 0x80BD54D8 0C02D6EC */ jal	Actor_GetSwitchFlag
/* 000071 0x80BD54DC 30A5007F */ andi	$a1, $a1, 0X7F
/* 000072 0x80BD54E0 50400004 */ beqzl	$v0, .L80BD54F4
/* 000073 0x80BD54E4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000074 0x80BD54E8 0C2F5540 */ jal	BgIkanaRay_SetActivated
/* 000075 0x80BD54EC 8FA40018 */ lw	$a0, 0X18($sp)
/* 000076 0x80BD54F0 8FBF0014 */ lw	$ra, 0X14($sp)
.L80BD54F4:
/* 000077 0x80BD54F4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000078 0x80BD54F8 03E00008 */ jr	$ra
/* 000079 0x80BD54FC 00000000 */ nop

glabel BgIkanaRay_SetActivated
/* 000080 0x80BD5500 8C8F0004 */ lw	$t7, 0X4($a0)
/* 000081 0x80BD5504 3C0E80BD */ lui	$t6, %hi(BgIkanaRay_Draw)
/* 000082 0x80BD5508 2401FFEF */ li	$at, -0X11
/* 000083 0x80BD550C 3C1980BD */ lui	$t9, %hi(BgIkanaRay_UpdateActivated)
/* 000084 0x80BD5510 25CE5590 */ addiu	$t6, $t6, %lo(BgIkanaRay_Draw)
/* 000085 0x80BD5514 27395530 */ addiu	$t9, $t9, %lo(BgIkanaRay_UpdateActivated)
/* 000086 0x80BD5518 01E1C024 */ and	$t8, $t7, $at
/* 000087 0x80BD551C AC8E013C */ sw	$t6, 0X13C($a0)
/* 000088 0x80BD5520 AC980004 */ sw	$t8, 0X4($a0)
/* 000089 0x80BD5524 AC990194 */ sw	$t9, 0X194($a0)
/* 000090 0x80BD5528 03E00008 */ jr	$ra
/* 000091 0x80BD552C 00000000 */ nop

glabel BgIkanaRay_UpdateActivated
/* 000092 0x80BD5530 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000093 0x80BD5534 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000094 0x80BD5538 AFA40018 */ sw	$a0, 0X18($sp)
/* 000095 0x80BD553C 00A03825 */ move	$a3, $a1
/* 000096 0x80BD5540 8FA60018 */ lw	$a2, 0X18($sp)
/* 000097 0x80BD5544 3C010001 */ lui	$at, 0x0001
/* 000098 0x80BD5548 34218884 */ ori	$at, $at, 0X8884
/* 000099 0x80BD554C 00E12821 */ addu	$a1, $a3, $at
/* 000100 0x80BD5550 00E02025 */ move	$a0, $a3
/* 000101 0x80BD5554 0C038956 */ jal	Collision_AddAT
/* 000102 0x80BD5558 24C60144 */ addiu	$a2, $a2, 0X144
/* 000103 0x80BD555C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000104 0x80BD5560 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000105 0x80BD5564 03E00008 */ jr	$ra
/* 000106 0x80BD5568 00000000 */ nop

glabel BgIkanaRay_Update
/* 000107 0x80BD556C 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000108 0x80BD5570 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000109 0x80BD5574 8C990194 */ lw	$t9, 0X194($a0)
/* 000110 0x80BD5578 0320F809 */ jalr	$t9
/* 000111 0x80BD557C 00000000 */ nop
/* 000112 0x80BD5580 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000113 0x80BD5584 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000114 0x80BD5588 03E00008 */ jr	$ra
/* 000115 0x80BD558C 00000000 */ nop

glabel BgIkanaRay_Draw
/* 000116 0x80BD5590 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000117 0x80BD5594 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000118 0x80BD5598 AFA5001C */ sw	$a1, 0X1C($sp)
/* 000119 0x80BD559C 00803025 */ move	$a2, $a0
/* 000120 0x80BD55A0 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000121 0x80BD55A4 0C04C5D6 */ jal	SceneProc_DrawAllSceneAnimatedTextures
/* 000122 0x80BD55A8 8CC50190 */ lw	$a1, 0X190($a2)
/* 000123 0x80BD55AC 3C050600 */ lui	$a1, 0x0600
/* 000124 0x80BD55B0 24A51100 */ addiu	$a1, $a1, 0X1100
/* 000125 0x80BD55B4 0C02F80F */ jal	func_800BE03C
/* 000126 0x80BD55B8 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000127 0x80BD55BC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000128 0x80BD55C0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000129 0x80BD55C4 03E00008 */ jr	$ra
/* 000130 0x80BD55C8 00000000 */ nop
/* 000131 0x80BD55CC 00000000 */ nop
