.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel BgMbarChair_Init
/* 000000 0x80B7E930 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x80B7E934 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x80B7E938 AFA40018 */ sw	$a0, 0X18($sp)
/* 000003 0x80B7E93C AFA5001C */ sw	$a1, 0X1C($sp)
/* 000004 0x80B7E940 3C0580B8 */ lui	$a1, %hi(bgMbarChairInitVars)
/* 000005 0x80B7E944 24A5EA20 */ addiu	$a1, $a1, %lo(bgMbarChairInitVars)
/* 000006 0x80B7E948 0C03FEB7 */ jal	Actor_ProcessInitChain
/* 000007 0x80B7E94C 8FA40018 */ lw	$a0, 0X18($sp)
/* 000008 0x80B7E950 8FA40018 */ lw	$a0, 0X18($sp)
/* 000009 0x80B7E954 0C032B84 */ jal	BcCheck3_BgActorInit
/* 000010 0x80B7E958 00002825 */ move	$a1, $zero
/* 000011 0x80B7E95C 3C060600 */ lui	$a2, 0x0600
/* 000012 0x80B7E960 24C619B4 */ addiu	$a2, $a2, 0X19B4
/* 000013 0x80B7E964 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000014 0x80B7E968 0C032B8D */ jal	BgCheck3_LoadMesh
/* 000015 0x80B7E96C 8FA50018 */ lw	$a1, 0X18($sp)
/* 000016 0x80B7E970 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000017 0x80B7E974 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000018 0x80B7E978 03E00008 */ jr	$ra
/* 000019 0x80B7E97C 00000000 */ nop

glabel BgMbarChair_Destroy
/* 000020 0x80B7E980 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000021 0x80B7E984 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000022 0x80B7E988 AFA40018 */ sw	$a0, 0X18($sp)
/* 000023 0x80B7E98C 00A03825 */ move	$a3, $a1
/* 000024 0x80B7E990 8FAE0018 */ lw	$t6, 0X18($sp)
/* 000025 0x80B7E994 00E02025 */ move	$a0, $a3
/* 000026 0x80B7E998 24E50880 */ addiu	$a1, $a3, 0X880
/* 000027 0x80B7E99C 0C031933 */ jal	BgCheck_RemoveActorMesh
/* 000028 0x80B7E9A0 8DC60144 */ lw	$a2, 0X144($t6)
/* 000029 0x80B7E9A4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000030 0x80B7E9A8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000031 0x80B7E9AC 03E00008 */ jr	$ra
/* 000032 0x80B7E9B0 00000000 */ nop

glabel BgMbarChair_Update
/* 000033 0x80B7E9B4 AFA40000 */ sw	$a0, 0X0($sp)
/* 000034 0x80B7E9B8 AFA50004 */ sw	$a1, 0X4($sp)
/* 000035 0x80B7E9BC 03E00008 */ jr	$ra
/* 000036 0x80B7E9C0 00000000 */ nop

glabel BgMbarChair_Draw
/* 000037 0x80B7E9C4 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000038 0x80B7E9C8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000039 0x80B7E9CC AFA40018 */ sw	$a0, 0X18($sp)
/* 000040 0x80B7E9D0 00A03025 */ move	$a2, $a1
/* 000041 0x80B7E9D4 3C050600 */ lui	$a1, 0x0600
/* 000042 0x80B7E9D8 24A50288 */ addiu	$a1, $a1, 0X288
/* 000043 0x80B7E9DC 0C02F7F0 */ jal	func_800BDFC0
/* 000044 0x80B7E9E0 00C02025 */ move	$a0, $a2
/* 000045 0x80B7E9E4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000046 0x80B7E9E8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000047 0x80B7E9EC 03E00008 */ jr	$ra
/* 000048 0x80B7E9F0 00000000 */ nop
/* 000049 0x80B7E9F4 00000000 */ nop
/* 000050 0x80B7E9F8 00000000 */ nop
/* 000051 0x80B7E9FC 00000000 */ nop
