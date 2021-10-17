glabel SceneProc_DrawOpaqueAnimatedTexturesWithAlpha
/* 143267 0x8013194C 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 143268 0x80131950 44866000 */ mtc1	$a2, $f12
/* 143269 0x80131954 AFBF001C */ sw	$ra, 0X1C($sp)
/* 143270 0x80131958 44066000 */ mfc1	$a2, $f12
/* 143271 0x8013195C 240E0001 */ li	$t6, 0X1
/* 143272 0x80131960 0C04C5A4 */ jal	SceneProc_DrawAnimatedTextures
/* 143273 0x80131964 AFAE0010 */ sw	$t6, 0X10($sp)
/* 143274 0x80131968 8FBF001C */ lw	$ra, 0X1C($sp)
/* 143275 0x8013196C 27BD0020 */ addiu	$sp, $sp, 0X20
/* 143276 0x80131970 03E00008 */ jr	$ra
/* 143277 0x80131974 00000000 */ nop

