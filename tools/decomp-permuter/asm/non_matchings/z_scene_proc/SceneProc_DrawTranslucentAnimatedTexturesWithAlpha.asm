glabel SceneProc_DrawTranslucentAnimatedTexturesWithAlpha
/* 143278 0x80131978 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 143279 0x8013197C 44866000 */ mtc1	$a2, $f12
/* 143280 0x80131980 AFBF001C */ sw	$ra, 0X1C($sp)
/* 143281 0x80131984 44066000 */ mfc1	$a2, $f12
/* 143282 0x80131988 240E0002 */ li	$t6, 0X2
/* 143283 0x8013198C 0C04C5A4 */ jal	SceneProc_DrawAnimatedTextures
/* 143284 0x80131990 AFAE0010 */ sw	$t6, 0X10($sp)
/* 143285 0x80131994 8FBF001C */ lw	$ra, 0X1C($sp)
/* 143286 0x80131998 27BD0020 */ addiu	$sp, $sp, 0X20
/* 143287 0x8013199C 03E00008 */ jr	$ra
/* 143288 0x801319A0 00000000 */ nop

