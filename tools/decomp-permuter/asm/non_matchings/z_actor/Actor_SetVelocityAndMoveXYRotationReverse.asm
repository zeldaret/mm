glabel Actor_SetVelocityAndMoveXYRotationReverse
/* 017478 0x800B6BD8 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 017479 0x800B6BDC AFBF0014 */ sw	$ra, 0X14($sp)
/* 017480 0x800B6BE0 AFA40018 */ sw	$a0, 0X18($sp)
/* 017481 0x800B6BE4 0C02DAD4 */ jal	Actor_SetVelocityXYRotationReverse
/* 017482 0x800B6BE8 8FA40018 */ lw	$a0, 0X18($sp)
/* 017483 0x800B6BEC 0C02DA6B */ jal	Actor_ApplyMovement
/* 017484 0x800B6BF0 8FA40018 */ lw	$a0, 0X18($sp)
/* 017485 0x800B6BF4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 017486 0x800B6BF8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 017487 0x800B6BFC 03E00008 */ jr	$ra
/* 017488 0x800B6C00 00000000 */ nop

