glabel ObjYado_Update
/* 000025 0x80C16244 AFA50004 */ sw	$a1, 0X4($sp)
/* 000026 0x80C16248 3C0E801F */ lui	$t6, %hi(gSaveContext + 0x10)
/* 000027 0x80C1624C 8DCEF680 */ lw	$t6, %lo(gSaveContext + 0x10)($t6)
/* 000028 0x80C16250 A08E0144 */ sb	$t6, 0X144($a0)
/* 000029 0x80C16254 03E00008 */ jr	$ra
/* 000030 0x80C16258 00000000 */ nop

