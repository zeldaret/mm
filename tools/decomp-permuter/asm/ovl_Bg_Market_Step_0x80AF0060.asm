.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel BgMarketStep_Init
/* 000000 0x80AF0060 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x80AF0064 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x80AF0068 AFA5001C */ sw	$a1, 0X1C($sp)
/* 000003 0x80AF006C 3C0580AF */ lui	$a1, %hi(D_80AF0110)
/* 000004 0x80AF0070 0C03FEB7 */ jal	Actor_ProcessInitChain
/* 000005 0x80AF0074 24A50110 */ addiu	$a1, $a1, %lo(D_80AF0110)
/* 000006 0x80AF0078 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000007 0x80AF007C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000008 0x80AF0080 03E00008 */ jr	$ra
/* 000009 0x80AF0084 00000000 */ nop

glabel BgMarketStep_Draw
/* 000010 0x80AF0088 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 000011 0x80AF008C AFBF0014 */ sw	$ra, 0X14($sp)
/* 000012 0x80AF0090 AFA50024 */ sw	$a1, 0X24($sp)
/* 000013 0x80AF0094 00803025 */ move	$a2, $a0
/* 000014 0x80AF0098 84C2001C */ lh	$v0, 0X1C($a2)
/* 000015 0x80AF009C 3C0580AF */ lui	$a1, %hi(D_80AF0120)
/* 000016 0x80AF00A0 8FA40024 */ lw	$a0, 0X24($sp)
/* 000017 0x80AF00A4 30420001 */ andi	$v0, $v0, 0X1
/* 000018 0x80AF00A8 00021880 */ sll	$v1, $v0, 2
/* 000019 0x80AF00AC 00A32821 */ addu	$a1, $a1, $v1
/* 000020 0x80AF00B0 8CA50120 */ lw	$a1, %lo(D_80AF0120)($a1)
/* 000021 0x80AF00B4 0C02F7F0 */ jal	func_800BDFC0
/* 000022 0x80AF00B8 AFA30018 */ sw	$v1, 0X18($sp)
/* 000023 0x80AF00BC 8FA30018 */ lw	$v1, 0X18($sp)
/* 000024 0x80AF00C0 3C0580AF */ lui	$a1, %hi(D_80AF0128)
/* 000025 0x80AF00C4 8FA40024 */ lw	$a0, 0X24($sp)
/* 000026 0x80AF00C8 00A32821 */ addu	$a1, $a1, $v1
/* 000027 0x80AF00CC 0C02F7F0 */ jal	func_800BDFC0
/* 000028 0x80AF00D0 8CA50128 */ lw	$a1, %lo(D_80AF0128)($a1)
/* 000029 0x80AF00D4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000030 0x80AF00D8 27BD0020 */ addiu	$sp, $sp, 0X20
/* 000031 0x80AF00DC 03E00008 */ jr	$ra
/* 000032 0x80AF00E0 00000000 */ nop
/* 000033 0x80AF00E4 00000000 */ nop
/* 000034 0x80AF00E8 00000000 */ nop
/* 000035 0x80AF00EC 00000000 */ nop
