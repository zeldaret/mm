glabel BgCheck_ActorMeshPolyListsInit
/* 032940 0x800C5D70 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 032941 0x800C5D74 AFBF0014 */ sw	$ra, 0X14($sp)
/* 032942 0x800C5D78 0C03174C */ jal	BgCheck_ActorMeshPolyListsHeadsInit
/* 032943 0x800C5D7C A4800000 */ sh	$zero, 0X0($a0)
/* 032944 0x800C5D80 8FBF0014 */ lw	$ra, 0X14($sp)
/* 032945 0x800C5D84 27BD0018 */ addiu	$sp, $sp, 0X18
/* 032946 0x800C5D88 03E00008 */ jr	$ra
/* 032947 0x800C5D8C 00000000 */ nop

