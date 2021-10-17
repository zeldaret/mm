glabel SceneProc_DrawSceneConfig1
/* 143289 0x801319A4 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 143290 0x801319A8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 143291 0x801319AC 3C050002 */ lui	$a1, 0x0002
/* 143292 0x801319B0 00A42821 */ addu	$a1, $a1, $a0
/* 143293 0x801319B4 0C04C5D6 */ jal	SceneProc_DrawAllSceneAnimatedTextures
/* 143294 0x801319B8 8CA5886C */ lw	$a1, -0X7794($a1)
/* 143295 0x801319BC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 143296 0x801319C0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 143297 0x801319C4 03E00008 */ jr	$ra
/* 143298 0x801319C8 00000000 */ nop

