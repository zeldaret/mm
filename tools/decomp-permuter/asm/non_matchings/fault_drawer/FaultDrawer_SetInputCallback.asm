glabel FaultDrawer_SetInputCallback
/* 004625 0x800848A4 3C0E8009 */ lui	$t6, %hi(sFaultDrawContext)
/* 004626 0x800848A8 8DCE6BE0 */ lw	$t6, %lo(sFaultDrawContext)($t6)
/* 004627 0x800848AC ADC40038 */ sw	$a0, 0X38($t6)
/* 004628 0x800848B0 03E00008 */ jr	$ra
/* 004629 0x800848B4 00000000 */ nop

