glabel func_80BAA8D0
/* 000128 0x80BAA8D0 3C03801F */ lui	$v1, %hi(gSaveContext)
/* 000129 0x80BAA8D4 2463F670 */ addiu	$v1, $v1, %lo(gSaveContext)
/* 000130 0x80BAA8D8 3C0E801F */ lui	$t6, %hi(gStaticContext)
/* 000131 0x80BAA8DC 8DCE3F60 */ lw	$t6, %lo(gStaticContext)($t6)
/* 000132 0x80BAA8E0 9462000C */ lhu	$v0, 0XC($v1)
/* 000133 0x80BAA8E4 94790016 */ lhu	$t9, 0X16($v1)
/* 000134 0x80BAA8E8 95CF0032 */ lhu	$t7, 0X32($t6)
/* 000135 0x80BAA8EC 01E2C021 */ addu	$t8, $t7, $v0
/* 000136 0x80BAA8F0 A478000C */ sh	$t8, 0XC($v1)
/* 000137 0x80BAA8F4 03384021 */ addu	$t0, $t9, $t8
/* 000138 0x80BAA8F8 A468000C */ sh	$t0, 0XC($v1)
/* 000139 0x80BAA8FC 03E00008 */ jr	$ra
/* 000140 0x80BAA900 00000000 */ nop

