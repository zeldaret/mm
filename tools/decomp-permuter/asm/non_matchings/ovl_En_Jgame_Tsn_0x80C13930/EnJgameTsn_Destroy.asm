glabel EnJgameTsn_Destroy
/* 000130 0x80C13B38 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000131 0x80C13B3C AFBF0014 */ sw	$ra, 0X14($sp)
/* 000132 0x80C13B40 00803025 */ move	$a2, $a0
/* 000133 0x80C13B44 00A03825 */ move	$a3, $a1
/* 000134 0x80C13B48 00E02025 */ move	$a0, $a3
/* 000135 0x80C13B4C 0C03847B */ jal	Collision_FiniCylinder
/* 000136 0x80C13B50 24C50144 */ addiu	$a1, $a2, 0X144
/* 000137 0x80C13B54 3C02801F */ lui	$v0, %hi(gSaveContext)
/* 000138 0x80C13B58 2442F670 */ addiu	$v0, $v0, %lo(gSaveContext)
/* 000139 0x80C13B5C 904E0F52 */ lbu	$t6, 0XF52($v0)
/* 000140 0x80C13B60 31CF00DF */ andi	$t7, $t6, 0XDF
/* 000141 0x80C13B64 A04F0F52 */ sb	$t7, 0XF52($v0)
/* 000142 0x80C13B68 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000143 0x80C13B6C 03E00008 */ jr	$ra
/* 000144 0x80C13B70 27BD0018 */ addiu	$sp, $sp, 0X18

