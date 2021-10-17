glabel Collision_InitTouchDefault
/* 060159 0x800E06BC AFA40000 */ sw	$a0, 0X0($sp)
/* 060160 0x800E06C0 3C0E801C */ lui	$t6, %hi(defaultColTouch)
/* 060161 0x800E06C4 25CEA258 */ addiu	$t6, $t6, %lo(defaultColTouch)
/* 060162 0x800E06C8 8DD80000 */ lw	$t8, 0X0($t6)
/* 060163 0x800E06CC 24020001 */ li	$v0, 0X1
/* 060164 0x800E06D0 ACB80000 */ sw	$t8, 0X0($a1)
/* 060165 0x800E06D4 8DCF0004 */ lw	$t7, 0X4($t6)
/* 060166 0x800E06D8 ACAF0004 */ sw	$t7, 0X4($a1)
/* 060167 0x800E06DC 03E00008 */ jr	$ra
/* 060168 0x800E06E0 00000000 */ nop

