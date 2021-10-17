glabel func_809C1124
/* 000029 0x809C1124 3C03801F */ lui	$v1, %hi(gSaveContext)
/* 000030 0x809C1128 2463F670 */ addiu	$v1, $v1, %lo(gSaveContext)
/* 000031 0x809C112C 3C0E801F */ lui	$t6, %hi(gStaticContext)
/* 000032 0x809C1130 8DCE3F60 */ lw	$t6, %lo(gStaticContext)($t6)
/* 000033 0x809C1134 9462000C */ lhu	$v0, 0XC($v1)
/* 000034 0x809C1138 94790016 */ lhu	$t9, 0X16($v1)
/* 000035 0x809C113C 95CF0032 */ lhu	$t7, 0X32($t6)
/* 000036 0x809C1140 01E2C021 */ addu	$t8, $t7, $v0
/* 000037 0x809C1144 A478000C */ sh	$t8, 0XC($v1)
/* 000038 0x809C1148 03384021 */ addu	$t0, $t9, $t8
/* 000039 0x809C114C A468000C */ sh	$t0, 0XC($v1)
/* 000040 0x809C1150 03E00008 */ jr	$ra
/* 000041 0x809C1154 00000000 */ nop

