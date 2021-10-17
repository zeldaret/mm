.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_800E03A0
/* 059960 0x800E03A0 04800003 */ bltz	$a0, .L800E03B0
/* 059961 0x800E03A4 28810017 */ slti	$at, $a0, 0X17
/* 059962 0x800E03A8 14200003 */ bnez	$at, .L800E03B8
/* 059963 0x800E03AC 00047140 */ sll	$t6, $a0, 5
.L800E03B0:
/* 059964 0x800E03B0 03E00008 */ jr	$ra
/* 059965 0x800E03B4 00001025 */ move	$v0, $zero
.L800E03B8:
/* 059966 0x800E03B8 3C0F801C */ lui	$t7, %hi(D_801B9F20)
/* 059967 0x800E03BC 25EF9F20 */ addiu	$t7, $t7, %lo(D_801B9F20)
/* 059968 0x800E03C0 01CF1021 */ addu	$v0, $t6, $t7
/* 059969 0x800E03C4 03E00008 */ jr	$ra
/* 059970 0x800E03C8 00000000 */ nop

glabel func_800E03CC
/* 059971 0x800E03CC 00801825 */ move	$v1, $a0
/* 059972 0x800E03D0 24040020 */ li	$a0, 0X20
/* 059973 0x800E03D4 00001025 */ move	$v0, $zero
.L800E03D8:
/* 059974 0x800E03D8 24420004 */ addiu	$v0, $v0, 0X4
/* 059975 0x800E03DC A0600001 */ sb	$zero, 0X1($v1)
/* 059976 0x800E03E0 A0600002 */ sb	$zero, 0X2($v1)
/* 059977 0x800E03E4 A0600003 */ sb	$zero, 0X3($v1)
/* 059978 0x800E03E8 24630004 */ addiu	$v1, $v1, 0X4
/* 059979 0x800E03EC 1444FFFA */ bne	$v0, $a0, .L800E03D8
/* 059980 0x800E03F0 A060FFFC */ sb	$zero, -0X4($v1)
/* 059981 0x800E03F4 03E00008 */ jr	$ra
/* 059982 0x800E03F8 00000000 */ nop
/* 059983 0x800E03FC 00000000 */ nop
/* 059984 0x800E0400 00000000 */ nop
/* 059985 0x800E0404 00000000 */ nop
/* 059986 0x800E0408 00000000 */ nop
/* 059987 0x800E040C 00000000 */ nop
