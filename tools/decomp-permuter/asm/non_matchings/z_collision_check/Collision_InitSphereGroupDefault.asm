glabel Collision_InitSphereGroupDefault
/* 060451 0x800E0B4C 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 060452 0x800E0B50 AFBF0014 */ sw	$ra, 0X14($sp)
/* 060453 0x800E0B54 0C03814E */ jal	Collision_InitCommonDefault
/* 060454 0x800E0B58 AFA5001C */ sw	$a1, 0X1C($sp)
/* 060455 0x800E0B5C 8FA5001C */ lw	$a1, 0X1C($sp)
/* 060456 0x800E0B60 24020001 */ li	$v0, 0X1
/* 060457 0x800E0B64 ACA00018 */ sw	$zero, 0X18($a1)
/* 060458 0x800E0B68 ACA0001C */ sw	$zero, 0X1C($a1)
/* 060459 0x800E0B6C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 060460 0x800E0B70 03E00008 */ jr	$ra
/* 060461 0x800E0B74 27BD0018 */ addiu	$sp, $sp, 0X18

