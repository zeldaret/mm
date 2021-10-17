glabel EnKendoJs_Destroy
/* 000151 0x80B264FC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000152 0x80B26500 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000153 0x80B26504 00803025 */ move	$a2, $a0
/* 000154 0x80B26508 00A03825 */ move	$a3, $a1
/* 000155 0x80B2650C 00E02025 */ move	$a0, $a3
/* 000156 0x80B26510 0C03847B */ jal	Collision_FiniCylinder
/* 000157 0x80B26514 24C50144 */ addiu	$a1, $a2, 0X144
/* 000158 0x80B26518 3C02801F */ lui	$v0, %hi(gSaveContext)
/* 000159 0x80B2651C 2442F670 */ addiu	$v0, $v0, %lo(gSaveContext)
/* 000160 0x80B26520 904E0F4A */ lbu	$t6, 0XF4A($v0)
/* 000161 0x80B26524 31CF00F7 */ andi	$t7, $t6, 0XF7
/* 000162 0x80B26528 A04F0F4A */ sb	$t7, 0XF4A($v0)
/* 000163 0x80B2652C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000164 0x80B26530 03E00008 */ jr	$ra
/* 000165 0x80B26534 27BD0018 */ addiu	$sp, $sp, 0X18

