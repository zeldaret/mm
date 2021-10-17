.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel ObjVisiblock_Init
/* 000000 0x80ADEA70 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x80ADEA74 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x80ADEA78 AFA40018 */ sw	$a0, 0X18($sp)
/* 000003 0x80ADEA7C AFA5001C */ sw	$a1, 0X1C($sp)
/* 000004 0x80ADEA80 3C0580AE */ lui	$a1, %hi(D_80ADEB50)
/* 000005 0x80ADEA84 24A5EB50 */ addiu	$a1, $a1, %lo(D_80ADEB50)
/* 000006 0x80ADEA88 0C03FEB7 */ jal	Actor_ProcessInitChain
/* 000007 0x80ADEA8C 8FA40018 */ lw	$a0, 0X18($sp)
/* 000008 0x80ADEA90 8FA40018 */ lw	$a0, 0X18($sp)
/* 000009 0x80ADEA94 0C032B84 */ jal	BcCheck3_BgActorInit
/* 000010 0x80ADEA98 00002825 */ move	$a1, $zero
/* 000011 0x80ADEA9C 3C060600 */ lui	$a2, 0x0600
/* 000012 0x80ADEAA0 24C60AD0 */ addiu	$a2, $a2, 0XAD0
/* 000013 0x80ADEAA4 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000014 0x80ADEAA8 0C032B8D */ jal	BgCheck3_LoadMesh
/* 000015 0x80ADEAAC 8FA50018 */ lw	$a1, 0X18($sp)
/* 000016 0x80ADEAB0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000017 0x80ADEAB4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000018 0x80ADEAB8 03E00008 */ jr	$ra
/* 000019 0x80ADEABC 00000000 */ nop

glabel ObjVisiblock_Destroy
/* 000020 0x80ADEAC0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000021 0x80ADEAC4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000022 0x80ADEAC8 AFA40018 */ sw	$a0, 0X18($sp)
/* 000023 0x80ADEACC 00A03825 */ move	$a3, $a1
/* 000024 0x80ADEAD0 8FAE0018 */ lw	$t6, 0X18($sp)
/* 000025 0x80ADEAD4 00E02025 */ move	$a0, $a3
/* 000026 0x80ADEAD8 24E50880 */ addiu	$a1, $a3, 0X880
/* 000027 0x80ADEADC 0C031933 */ jal	BgCheck_RemoveActorMesh
/* 000028 0x80ADEAE0 8DC60144 */ lw	$a2, 0X144($t6)
/* 000029 0x80ADEAE4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000030 0x80ADEAE8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000031 0x80ADEAEC 03E00008 */ jr	$ra
/* 000032 0x80ADEAF0 00000000 */ nop

glabel ObjVisiblock_Draw
/* 000033 0x80ADEAF4 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000034 0x80ADEAF8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000035 0x80ADEAFC AFA40018 */ sw	$a0, 0X18($sp)
/* 000036 0x80ADEB00 00A03025 */ move	$a2, $a1
/* 000037 0x80ADEB04 3C050600 */ lui	$a1, 0x0600
/* 000038 0x80ADEB08 24A50140 */ addiu	$a1, $a1, 0X140
/* 000039 0x80ADEB0C 0C02F80F */ jal	func_800BE03C
/* 000040 0x80ADEB10 00C02025 */ move	$a0, $a2
/* 000041 0x80ADEB14 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000042 0x80ADEB18 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000043 0x80ADEB1C 03E00008 */ jr	$ra
/* 000044 0x80ADEB20 00000000 */ nop
/* 000045 0x80ADEB24 00000000 */ nop
/* 000046 0x80ADEB28 00000000 */ nop
/* 000047 0x80ADEB2C 00000000 */ nop
