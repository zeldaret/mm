glabel FaultDrawer_Init
/* 004630 0x800848B8 3C09FFFA */ lui	$t1, 0xFFFA
/* 004631 0x800848BC 03A05025 */ move	$t2, $sp
/* 004632 0x800848C0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 004633 0x800848C4 35295A5A */ ori	$t1, $t1, 0X5A5A
.L800848C8:
/* 004634 0x800848C8 254AFFF8 */ addiu	$t2, $t2, -0X8
/* 004635 0x800848CC AD490000 */ sw	$t1, 0X0($t2)
/* 004636 0x800848D0 155DFFFD */ bne	$t2, $sp, .L800848C8
/* 004637 0x800848D4 AD490004 */ sw	$t1, 0X4($t2)
/* 004638 0x800848D8 3C028009 */ lui	$v0, %hi(sFaultDrawContext)
/* 004639 0x800848DC 24426BE0 */ addiu	$v0, $v0, %lo(sFaultDrawContext)
/* 004640 0x800848E0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 004641 0x800848E4 3C0E800A */ lui	$t6, %hi(sFaultDrawerStruct)
/* 004642 0x800848E8 25C5CCD0 */ addiu	$a1, $t6, %lo(sFaultDrawerStruct)
/* 004643 0x800848EC 3C048009 */ lui	$a0, %hi(sFaultDrawerDefault)
/* 004644 0x800848F0 AC450000 */ sw	$a1, 0X0($v0)
/* 004645 0x800848F4 24846BE4 */ addiu	$a0, $a0, %lo(sFaultDrawerDefault)
/* 004646 0x800848F8 0C0244B0 */ jal	_bcopy
/* 004647 0x800848FC 2406003C */ li	$a2, 0X3C
/* 004648 0x80084900 3C0F8000 */ lui	$t7, %hi(osMemSize)
/* 004649 0x80084904 8DEF0318 */ lw	$t7, %lo(osMemSize)($t7)
/* 004650 0x80084908 3C018000 */ lui	$at, 0x8000
/* 004651 0x8008490C 3C088009 */ lui	$t0, %hi(sFaultDrawContext)
/* 004652 0x80084910 01E1C025 */ or	$t8, $t7, $at
/* 004653 0x80084914 8D086BE0 */ lw	$t0, %lo(sFaultDrawContext)($t0)
/* 004654 0x80084918 3C01FFFD */ lui	$at, 0xFFFD
/* 004655 0x8008491C 3421A800 */ ori	$at, $at, 0XA800
/* 004656 0x80084920 0301C821 */ addu	$t9, $t8, $at
/* 004657 0x80084924 AD190000 */ sw	$t9, 0X0($t0)
/* 004658 0x80084928 8FBF0014 */ lw	$ra, 0X14($sp)
/* 004659 0x8008492C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 004660 0x80084930 03E00008 */ jr	$ra
/* 004661 0x80084934 00000000 */ nop
/* 004662 0x80084938 00000000 */ nop
/* 004663 0x8008493C 00000000 */ nop
