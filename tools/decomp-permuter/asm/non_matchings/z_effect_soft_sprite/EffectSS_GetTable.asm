glabel EffectSS_GetTable
/* 010704 0x800B0200 3C02801B */ lui	$v0, %hi(EffectSS2Info)
/* 010705 0x800B0204 8C42E3A0 */ lw	$v0, %lo(EffectSS2Info)($v0)
/* 010706 0x800B0208 03E00008 */ jr	$ra
/* 010707 0x800B020C 00000000 */ nop

