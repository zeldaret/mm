glabel FaultDrawer_VPrintf
/* 004551 0x8008477C 3C0EFFFA */ lui	$t6, 0xFFFA
/* 004552 0x80084780 03A07825 */ move	$t7, $sp
/* 004553 0x80084784 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 004554 0x80084788 35CE5A5A */ ori	$t6, $t6, 0X5A5A
.L8008478C:
/* 004555 0x8008478C 25EFFFF8 */ addiu	$t7, $t7, -0X8
/* 004556 0x80084790 ADEE0000 */ sw	$t6, 0X0($t7)
/* 004557 0x80084794 15FDFFFD */ bne	$t7, $sp, .L8008478C
/* 004558 0x80084798 ADEE0004 */ sw	$t6, 0X4($t7)
/* 004559 0x8008479C AFBF0014 */ sw	$ra, 0X14($sp)
/* 004560 0x800847A0 00803025 */ move	$a2, $a0
/* 004561 0x800847A4 00A03825 */ move	$a3, $a1
/* 004562 0x800847A8 3C048008 */ lui	$a0, %hi(FaultDrawer_FormatStringFunc)
/* 004563 0x800847AC 3C058009 */ lui	$a1, %hi(sFaultDrawContext)
/* 004564 0x800847B0 8CA56BE0 */ lw	$a1, %lo(sFaultDrawContext)($a1)
/* 004565 0x800847B4 0C023814 */ jal	_Printf
/* 004566 0x800847B8 24844568 */ addiu	$a0, $a0, %lo(FaultDrawer_FormatStringFunc)
/* 004567 0x800847BC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 004568 0x800847C0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 004569 0x800847C4 03E00008 */ jr	$ra
/* 004570 0x800847C8 00000000 */ nop

