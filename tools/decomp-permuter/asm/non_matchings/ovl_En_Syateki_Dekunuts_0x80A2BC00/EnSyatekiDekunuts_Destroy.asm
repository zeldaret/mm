glabel EnSyatekiDekunuts_Destroy
/* 000138 0x80A2BE28 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 000139 0x80A2BE2C AFBF0014 */ sw	$ra, 0X14($sp)
/* 000140 0x80A2BE30 00803025 */ move	$a2, $a0
/* 000141 0x80A2BE34 00A03825 */ move	$a3, $a1
/* 000142 0x80A2BE38 00E02025 */ move	$a0, $a3
/* 000143 0x80A2BE3C 0C03847B */ jal	Collision_FiniCylinder
/* 000144 0x80A2BE40 24C5018C */ addiu	$a1, $a2, 0X18C
/* 000145 0x80A2BE44 8FBF0014 */ lw	$ra, 0X14($sp)
/* 000146 0x80A2BE48 27BD0018 */ addiu	$sp, $sp, 0X18
/* 000147 0x80A2BE4C 03E00008 */ jr	$ra
/* 000148 0x80A2BE50 00000000 */ nop

