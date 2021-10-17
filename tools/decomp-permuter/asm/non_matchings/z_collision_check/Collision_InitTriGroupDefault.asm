glabel Collision_InitTriGroupDefault
/* 061188 0x800E16D0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 061189 0x800E16D4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 061190 0x800E16D8 0C03814E */ jal	Collision_InitCommonDefault
/* 061191 0x800E16DC AFA5001C */ sw	$a1, 0X1C($sp)
/* 061192 0x800E16E0 8FA5001C */ lw	$a1, 0X1C($sp)
/* 061193 0x800E16E4 24020001 */ li	$v0, 0X1
/* 061194 0x800E16E8 ACA00018 */ sw	$zero, 0X18($a1)
/* 061195 0x800E16EC ACA0001C */ sw	$zero, 0X1C($a1)
/* 061196 0x800E16F0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 061197 0x800E16F4 03E00008 */ jr	$ra
/* 061198 0x800E16F8 27BD0018 */ addiu	$sp, $sp, 0X18

