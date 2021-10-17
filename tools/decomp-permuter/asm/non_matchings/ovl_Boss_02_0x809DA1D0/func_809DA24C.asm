glabel func_809DA24C
/* 000031 0x809DA24C AFA40000 */ sw	$a0, 0X0($sp)
/* 000032 0x809DA250 3C0E801F */ lui	$t6, %hi(gStaticContext)
/* 000033 0x809DA254 8DCE3F60 */ lw	$t6, %lo(gStaticContext)($t6)
/* 000034 0x809DA258 A5C00454 */ sh	$zero, 0X454($t6)
/* 000035 0x809DA25C 03E00008 */ jr	$ra
/* 000036 0x809DA260 00000000 */ nop

