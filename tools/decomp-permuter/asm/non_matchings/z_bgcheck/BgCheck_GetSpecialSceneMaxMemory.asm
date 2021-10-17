glabel BgCheck_GetSpecialSceneMaxMemory
/* 030510 0x800C3778 3C03801B */ lui	$v1, %hi(bgSpecialSceneMaxMemory)
/* 030511 0x800C377C 3C02801B */ lui	$v0, %hi(bgSpecialSceneMeshSubdivisions)
/* 030512 0x800C3780 244246DC */ addiu	$v0, $v0, %lo(bgSpecialSceneMeshSubdivisions)
/* 030513 0x800C3784 246346D4 */ addiu	$v1, $v1, %lo(bgSpecialSceneMaxMemory)
/* 030514 0x800C3788 846E0000 */ lh	$t6, 0X0($v1)
.L800C378C:
/* 030515 0x800C378C 548E0006 */ bnel	$a0, $t6, .L800C37A8
/* 030516 0x800C3790 24630008 */ addiu	$v1, $v1, 0X8
/* 030517 0x800C3794 8C6F0004 */ lw	$t7, 0X4($v1)
/* 030518 0x800C3798 24020001 */ li	$v0, 0X1
/* 030519 0x800C379C 03E00008 */ jr	$ra
/* 030520 0x800C37A0 ACAF0000 */ sw	$t7, 0X0($a1)
/* 030521 0x800C37A4 24630008 */ addiu	$v1, $v1, 0X8
.L800C37A8:
/* 030522 0x800C37A8 5462FFF8 */ bnel	$v1, $v0, .L800C378C
/* 030523 0x800C37AC 846E0000 */ lh	$t6, 0X0($v1)
/* 030524 0x800C37B0 00001025 */ move	$v0, $zero
/* 030525 0x800C37B4 03E00008 */ jr	$ra
/* 030526 0x800C37B8 00000000 */ nop

