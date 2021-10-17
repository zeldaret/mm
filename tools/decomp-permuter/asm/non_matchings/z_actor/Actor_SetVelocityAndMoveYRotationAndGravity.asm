glabel Actor_SetVelocityAndMoveYRotationAndGravity
/* 017394 0x800B6A88 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 017395 0x800B6A8C AFBF0014 */ sw	$ra, 0X14($sp)
/* 017396 0x800B6A90 AFA40018 */ sw	$a0, 0X18($sp)
/* 017397 0x800B6A94 0C02DA84 */ jal	Actor_SetVelocityYRotationAndGravity
/* 017398 0x800B6A98 8FA40018 */ lw	$a0, 0X18($sp)
/* 017399 0x800B6A9C 0C02DA6B */ jal	Actor_ApplyMovement
/* 017400 0x800B6AA0 8FA40018 */ lw	$a0, 0X18($sp)
/* 017401 0x800B6AA4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 017402 0x800B6AA8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 017403 0x800B6AAC 03E00008 */ jr	$ra
/* 017404 0x800B6AB0 00000000 */ nop

