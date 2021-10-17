glabel SceneProc_DrawCurrentSceneAnimatedTextures
/* 142144 0x801307C0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 142145 0x801307C4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 142146 0x801307C8 908E00A6 */ lbu	$t6, 0XA6($a0)
/* 142147 0x801307CC 3C19801C */ lui	$t9, %hi(gSceneProcSceneDrawFuncs)
/* 142148 0x801307D0 000E7880 */ sll	$t7, $t6, 2
/* 142149 0x801307D4 032FC821 */ addu	$t9, $t9, $t7
/* 142150 0x801307D8 8F393BB8 */ lw	$t9, %lo(gSceneProcSceneDrawFuncs)($t9)
/* 142151 0x801307DC 0320F809 */ jalr	$t9
/* 142152 0x801307E0 00000000 */ nop
/* 142153 0x801307E4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 142154 0x801307E8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 142155 0x801307EC 03E00008 */ jr	$ra
/* 142156 0x801307F0 00000000 */ nop

