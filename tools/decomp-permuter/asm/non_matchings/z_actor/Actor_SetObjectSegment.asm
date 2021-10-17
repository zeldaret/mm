glabel Actor_SetObjectSegment
/* 017231 0x800B67FC 80AE001E */ lb	$t6, 0X1E($a1)
/* 017232 0x800B6800 3C190001 */ lui	$t9, 0x0001
/* 017233 0x800B6804 3C018000 */ lui	$at, 0x8000
/* 017234 0x800B6808 000E7900 */ sll	$t7, $t6, 4
/* 017235 0x800B680C 01EE7821 */ addu	$t7, $t7, $t6
/* 017236 0x800B6810 000F7880 */ sll	$t7, $t7, 2
/* 017237 0x800B6814 008FC021 */ addu	$t8, $a0, $t7
/* 017238 0x800B6818 0338C821 */ addu	$t9, $t9, $t8
/* 017239 0x800B681C 8F397D98 */ lw	$t9, 0X7D98($t9)
/* 017240 0x800B6820 03214021 */ addu	$t0, $t9, $at
/* 017241 0x800B6824 3C018020 */ lui	$at, %hi(gRspSegmentPhysAddrs + 0x18)
/* 017242 0x800B6828 AC288198 */ sw	$t0, %lo(gRspSegmentPhysAddrs + 0x18)($at)
/* 017243 0x800B682C 03E00008 */ jr	$ra
/* 017244 0x800B6830 00000000 */ nop

