glabel FaultDrawer_SetOsSyncPrintfEnabled
/* 003988 0x80083EB0 3C0E8009 */ lui	$t6, %hi(sFaultDrawContext)
/* 003989 0x80083EB4 8DCE6BE0 */ lw	$t6, %lo(sFaultDrawContext)($t6)
/* 003990 0x80083EB8 A1C40035 */ sb	$a0, 0X35($t6)
/* 003991 0x80083EBC 03E00008 */ jr	$ra
/* 003992 0x80083EC0 00000000 */ nop

