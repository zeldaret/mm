glabel Actor_SetVelocityAndMoveXYRotation
/* 017433 0x800B6B24 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 017434 0x800B6B28 AFBF0014 */ sw	$ra, 0X14($sp)
/* 017435 0x800B6B2C AFA40018 */ sw	$a0, 0X18($sp)
/* 017436 0x800B6B30 0C02DAAD */ jal	Actor_SetVelocityXYRotation
/* 017437 0x800B6B34 8FA40018 */ lw	$a0, 0X18($sp)
/* 017438 0x800B6B38 0C02DA6B */ jal	Actor_ApplyMovement
/* 017439 0x800B6B3C 8FA40018 */ lw	$a0, 0X18($sp)
/* 017440 0x800B6B40 8FBF0014 */ lw	$ra, 0X14($sp)
/* 017441 0x800B6B44 27BD0018 */ addiu	$sp, $sp, 0X18
/* 017442 0x800B6B48 03E00008 */ jr	$ra
/* 017443 0x800B6B4C 00000000 */ nop

