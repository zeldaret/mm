glabel SceneProc_DrawAllAnimatedTexturesWithAlpha
/* 143256 0x80131920 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 143257 0x80131924 44866000 */ mtc1	$a2, $f12
/* 143258 0x80131928 AFBF001C */ sw	$ra, 0X1C($sp)
/* 143259 0x8013192C 44066000 */ mfc1	$a2, $f12
/* 143260 0x80131930 240E0003 */ li	$t6, 0X3
/* 143261 0x80131934 0C04C5A4 */ jal	SceneProc_DrawAnimatedTextures
/* 143262 0x80131938 AFAE0010 */ sw	$t6, 0X10($sp)
/* 143263 0x8013193C 8FBF001C */ lw	$ra, 0X1C($sp)
/* 143264 0x80131940 27BD0020 */ addiu	$sp, $sp, 0X20
/* 143265 0x80131944 03E00008 */ jr	$ra
/* 143266 0x80131948 00000000 */ nop

