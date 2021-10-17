glabel BgCheck_HasActorMeshChanged
/* 033026 0x800C5EC8 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 033027 0x800C5ECC AFBF0014 */ sw	$ra, 0X14($sp)
/* 033028 0x800C5ED0 00803025 */ move	$a2, $a0
/* 033029 0x800C5ED4 24C40014 */ addiu	$a0, $a2, 0X14
/* 033030 0x800C5ED8 0C031717 */ jal	BgCheck_AreActorMeshParamsEqual
/* 033031 0x800C5EDC 24C50034 */ addiu	$a1, $a2, 0X34
/* 033032 0x800C5EE0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 033033 0x800C5EE4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 033034 0x800C5EE8 03E00008 */ jr	$ra
/* 033035 0x800C5EEC 00000000 */ nop

