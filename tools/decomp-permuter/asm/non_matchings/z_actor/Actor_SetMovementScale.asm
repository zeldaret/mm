glabel Actor_SetMovementScale
/* 017330 0x800B6988 44842000 */ mtc1	$a0, $f4
/* 017331 0x800B698C 3C013F00 */ lui	$at, 0x3F00
/* 017332 0x800B6990 44814000 */ mtc1	$at, $f8
/* 017333 0x800B6994 468021A0 */ cvt.s.w	$f6, $f4
/* 017334 0x800B6998 3C01801B */ lui	$at, %hi(actorMovementScale)
/* 017335 0x800B699C 46083282 */ mul.s	$f10, $f6, $f8
/* 017336 0x800B69A0 E42AECEC */ swc1	$f10, %lo(actorMovementScale)($at)
/* 017337 0x800B69A4 03E00008 */ jr	$ra
/* 017338 0x800B69A8 00000000 */ nop

