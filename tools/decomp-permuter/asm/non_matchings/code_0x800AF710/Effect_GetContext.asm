glabel Effect_GetContext
/* 010004 0x800AF710 3C02801E */ lui	$v0, %hi(sEffTable)
/* 010005 0x800AF714 8C423FB0 */ lw	$v0, %lo(sEffTable)($v0)
/* 010006 0x800AF718 03E00008 */ jr	$ra
/* 010007 0x800AF71C 00000000 */ nop

