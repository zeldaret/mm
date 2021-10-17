glabel ObjLightswitch_Destroy
/* 000247 0x8095FFCC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000248 0x8095FFD0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 000249 0x8095FFD4 00803025 */ move	$a2, $a0
/* 000250 0x8095FFD8 00A03825 */ move	$a3, $a1
/* 000251 0x8095FFDC 00E02025 */ move	$a0, $a3
/* 000252 0x8095FFE0 0C038306 */ jal	Collision_FiniSphereGroup
/* 000253 0x8095FFE4 24C50144 */ addiu	$a1, $a2, 0X144
/* 000254 0x8095FFE8 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000255 0x8095FFEC 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000256 0x8095FFF0 03E00008 */ jr	$ra
/* 000257 0x8095FFF4 00000000 */ nop

