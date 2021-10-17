.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnHs2_Init
/* 000000 0x8098EF60 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000001 0x8098EF64 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000002 0x8098EF68 AFA40018 */ sw	$a0, 0X18($sp)
/* 000003 0x8098EF6C AFA5001C */ sw	$a1, 0X1C($sp)
/* 000004 0x8098EF70 8FA40018 */ lw	$a0, 0X18($sp)
/* 000005 0x8098EF74 0C02D9F8 */ jal	Actor_SetScale
/* 000006 0x8098EF78 3C053F80 */ lui	$a1, 0x3F80
/* 000007 0x8098EF7C 8FAF0018 */ lw	$t7, 0X18($sp)
/* 000008 0x8098EF80 3C0E8099 */ lui	$t6, %hi(EnHs2_DoNothing)
/* 000009 0x8098EF84 25CEEFAC */ addiu	$t6, $t6, %lo(EnHs2_DoNothing)
/* 000010 0x8098EF88 ADEE0394 */ sw	$t6, 0X394($t7)
/* 000011 0x8098EF8C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000012 0x8098EF90 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000013 0x8098EF94 03E00008 */ jr	$ra
/* 000014 0x8098EF98 00000000 */ nop

glabel EnHs2_Destroy
/* 000015 0x8098EF9C AFA40000 */ sw	$a0, 0X0($sp)
/* 000016 0x8098EFA0 AFA50004 */ sw	$a1, 0X4($sp)
/* 000017 0x8098EFA4 03E00008 */ jr	$ra
/* 000018 0x8098EFA8 00000000 */ nop

glabel EnHs2_DoNothing
/* 000019 0x8098EFAC AFA40000 */ sw	$a0, 0X0($sp)
/* 000020 0x8098EFB0 AFA50004 */ sw	$a1, 0X4($sp)
/* 000021 0x8098EFB4 03E00008 */ jr	$ra
/* 000022 0x8098EFB8 00000000 */ nop

glabel EnHs2_Update
/* 000023 0x8098EFBC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000024 0x8098EFC0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000025 0x8098EFC4 8C990394 */ lw	$t9, 0X394($a0)
/* 000026 0x8098EFC8 0320F809 */ jalr	$t9
/* 000027 0x8098EFCC 00000000 */ nop
/* 000028 0x8098EFD0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000029 0x8098EFD4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000030 0x8098EFD8 03E00008 */ jr	$ra
/* 000031 0x8098EFDC 00000000 */ nop

glabel EnHs2_Draw
/* 000032 0x8098EFE0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000033 0x8098EFE4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000034 0x8098EFE8 03E00008 */ jr	$ra
/* 000035 0x8098EFEC 00000000 */ nop
