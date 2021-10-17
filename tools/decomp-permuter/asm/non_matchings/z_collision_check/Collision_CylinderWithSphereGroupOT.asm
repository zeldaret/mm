glabel Collision_CylinderWithSphereGroupOT
/* 066857 0x800E6F64 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 066858 0x800E6F68 AFA70024 */ sw	$a3, 0X24($sp)
/* 066859 0x800E6F6C 00C03825 */ move	$a3, $a2
/* 066860 0x800E6F70 AFBF0014 */ sw	$ra, 0X14($sp)
/* 066861 0x800E6F74 AFA60020 */ sw	$a2, 0X20($sp)
/* 066862 0x800E6F78 0C039B21 */ jal	Collision_SphereGroupWithCylinderOT
/* 066863 0x800E6F7C 8FA60024 */ lw	$a2, 0X24($sp)
/* 066864 0x800E6F80 8FBF0014 */ lw	$ra, 0X14($sp)
/* 066865 0x800E6F84 27BD0018 */ addiu	$sp, $sp, 0X18
/* 066866 0x800E6F88 03E00008 */ jr	$ra
/* 066867 0x800E6F8C 00000000 */ nop

