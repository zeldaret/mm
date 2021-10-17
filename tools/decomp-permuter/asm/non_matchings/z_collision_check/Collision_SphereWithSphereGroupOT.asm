glabel Collision_SphereWithSphereGroupOT
/* 066972 0x800E7130 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 066973 0x800E7134 AFA70024 */ sw	$a3, 0X24($sp)
/* 066974 0x800E7138 00C03825 */ move	$a3, $a2
/* 066975 0x800E713C AFBF0014 */ sw	$ra, 0X14($sp)
/* 066976 0x800E7140 AFA60020 */ sw	$a2, 0X20($sp)
/* 066977 0x800E7144 0C039B7D */ jal	Collision_SphereGroupWithSphereOT
/* 066978 0x800E7148 8FA60024 */ lw	$a2, 0X24($sp)
/* 066979 0x800E714C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 066980 0x800E7150 27BD0018 */ addiu	$sp, $sp, 0X18
/* 066981 0x800E7154 03E00008 */ jr	$ra
/* 066982 0x800E7158 00000000 */ nop

