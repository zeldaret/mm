glabel BgCheck_ActorMeshPolyListsHeadsInit
/* 032924 0x800C5D30 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 032925 0x800C5D34 AFBF0014 */ sw	$ra, 0X14($sp)
/* 032926 0x800C5D38 AFA40018 */ sw	$a0, 0X18($sp)
/* 032927 0x800C5D3C 8FA40018 */ lw	$a0, 0X18($sp)
/* 032928 0x800C5D40 0C02FEE7 */ jal	BgCheck_PolygonLinkedListResetHead
/* 032929 0x800C5D44 24840002 */ addiu	$a0, $a0, 0X2
/* 032930 0x800C5D48 8FA40018 */ lw	$a0, 0X18($sp)
/* 032931 0x800C5D4C 0C02FEE7 */ jal	BgCheck_PolygonLinkedListResetHead
/* 032932 0x800C5D50 24840004 */ addiu	$a0, $a0, 0X4
/* 032933 0x800C5D54 8FA40018 */ lw	$a0, 0X18($sp)
/* 032934 0x800C5D58 0C02FEE7 */ jal	BgCheck_PolygonLinkedListResetHead
/* 032935 0x800C5D5C 24840006 */ addiu	$a0, $a0, 0X6
/* 032936 0x800C5D60 8FBF0014 */ lw	$ra, 0X14($sp)
/* 032937 0x800C5D64 27BD0018 */ addiu	$sp, $sp, 0X18
/* 032938 0x800C5D68 03E00008 */ jr	$ra
/* 032939 0x800C5D6C 00000000 */ nop

