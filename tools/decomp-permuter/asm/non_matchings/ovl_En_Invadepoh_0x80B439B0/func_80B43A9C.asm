glabel func_80B43A9C
/* 000059 0x80B43A9C 3C02801F */ lui	$v0, %hi(gSaveContext + 0xE98)
/* 000060 0x80B43AA0 8C420508 */ lw	$v0, %lo(gSaveContext + 0xE98)($v0)
/* 000061 0x80B43AA4 304200FF */ andi	$v0, $v0, 0XFF
/* 000062 0x80B43AA8 03E00008 */ jr	$ra
/* 000063 0x80B43AAC 00000000 */ nop

