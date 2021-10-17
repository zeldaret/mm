.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel BgLbfshot_Init
/* 000000 0x80C18120 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x80C18124 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x80C18128 AFA40018 */ sw	$a0, 0X18($sp)
/* 000003 0x80C1812C AFA5001C */ sw	$a1, 0X1C($sp)
/* 000004 0x80C18130 3C0580C2 */ lui	$a1, %hi(D_80C18200)
/* 000005 0x80C18134 24A58200 */ addiu	$a1, $a1, %lo(D_80C18200)
/* 000006 0x80C18138 0C03FEB7 */ jal	Actor_ProcessInitChain
/* 000007 0x80C1813C 8FA40018 */ lw	$a0, 0X18($sp)
/* 000008 0x80C18140 3C01457A */ lui	$at, 0x457A
/* 000009 0x80C18144 8FA40018 */ lw	$a0, 0X18($sp)
/* 000010 0x80C18148 44812000 */ mtc1	$at, $f4
/* 000011 0x80C1814C 24050001 */ li	$a1, 0X1
/* 000012 0x80C18150 0C032B84 */ jal	BcCheck3_BgActorInit
/* 000013 0x80C18154 E48400FC */ swc1	$f4, 0XFC($a0)
/* 000014 0x80C18158 3C060600 */ lui	$a2, 0x0600
/* 000015 0x80C1815C 24C614D8 */ addiu	$a2, $a2, 0X14D8
/* 000016 0x80C18160 8FA4001C */ lw	$a0, 0X1C($sp)
/* 000017 0x80C18164 0C032B8D */ jal	BgCheck3_LoadMesh
/* 000018 0x80C18168 8FA50018 */ lw	$a1, 0X18($sp)
/* 000019 0x80C1816C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000020 0x80C18170 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000021 0x80C18174 03E00008 */ jr	$ra
/* 000022 0x80C18178 00000000 */ nop

glabel BgLbfshot_Destroy
/* 000023 0x80C1817C 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000024 0x80C18180 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000025 0x80C18184 AFA40018 */ sw	$a0, 0X18($sp)
/* 000026 0x80C18188 00A03825 */ move	$a3, $a1
/* 000027 0x80C1818C 8FAE0018 */ lw	$t6, 0X18($sp)
/* 000028 0x80C18190 00E02025 */ move	$a0, $a3
/* 000029 0x80C18194 24E50880 */ addiu	$a1, $a3, 0X880
/* 000030 0x80C18198 0C031933 */ jal	BgCheck_RemoveActorMesh
/* 000031 0x80C1819C 8DC60144 */ lw	$a2, 0X144($t6)
/* 000032 0x80C181A0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000033 0x80C181A4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000034 0x80C181A8 03E00008 */ jr	$ra
/* 000035 0x80C181AC 00000000 */ nop

glabel BgLbfshot_Draw
/* 000036 0x80C181B0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000037 0x80C181B4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000038 0x80C181B8 AFA40018 */ sw	$a0, 0X18($sp)
/* 000039 0x80C181BC 00A03025 */ move	$a2, $a1
/* 000040 0x80C181C0 3C050600 */ lui	$a1, 0x0600
/* 000041 0x80C181C4 24A50228 */ addiu	$a1, $a1, 0X228
/* 000042 0x80C181C8 0C02F7F0 */ jal	func_800BDFC0
/* 000043 0x80C181CC 00C02025 */ move	$a0, $a2
/* 000044 0x80C181D0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000045 0x80C181D4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000046 0x80C181D8 03E00008 */ jr	$ra
/* 000047 0x80C181DC 00000000 */ nop
