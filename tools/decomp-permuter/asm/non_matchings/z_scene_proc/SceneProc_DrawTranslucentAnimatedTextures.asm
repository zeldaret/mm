glabel SceneProc_DrawTranslucentAnimatedTextures
/* 143245 0x801318F4 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 143246 0x801318F8 AFBF001C */ sw	$ra, 0X1C($sp)
/* 143247 0x801318FC 00C03825 */ move	$a3, $a2
/* 143248 0x80131900 240E0002 */ li	$t6, 0X2
/* 143249 0x80131904 AFAE0010 */ sw	$t6, 0X10($sp)
/* 143250 0x80131908 0C04C5A4 */ jal	SceneProc_DrawAnimatedTextures
/* 143251 0x8013190C 3C063F80 */ lui	$a2, 0x3F80
/* 143252 0x80131910 8FBF001C */ lw	$ra, 0X1C($sp)
/* 143253 0x80131914 27BD0020 */ addiu	$sp, $sp, 0X20
/* 143254 0x80131918 03E00008 */ jr	$ra
/* 143255 0x8013191C 00000000 */ nop

