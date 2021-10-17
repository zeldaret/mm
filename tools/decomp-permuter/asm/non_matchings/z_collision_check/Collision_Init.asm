glabel Collision_Init
/* 062052 0x800E2450 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 062053 0x800E2454 AFBF0014 */ sw	$ra, 0X14($sp)
/* 062054 0x800E2458 0C038920 */ jal	Collision_Reset
/* 062055 0x800E245C A4A00002 */ sh	$zero, 0X2($a1)
/* 062056 0x800E2460 8FBF0014 */ lw	$ra, 0X14($sp)
/* 062057 0x800E2464 27BD0018 */ addiu	$sp, $sp, 0X18
/* 062058 0x800E2468 03E00008 */ jr	$ra
/* 062059 0x800E246C 00000000 */ nop

