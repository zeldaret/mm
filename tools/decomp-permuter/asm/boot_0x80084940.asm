.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80084940
/* 004664 0x80084940 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 004665 0x80084944 AFBF0014 */ sw	$ra, 0X14($sp)
/* 004666 0x80084948 0C02549C */ jal	__osSpGetStatus
/* 004667 0x8008494C 00000000 */ nop
/* 004668 0x80084950 0C0244A8 */ jal	osDpGetStatus
/* 004669 0x80084954 AFA2001C */ sw	$v0, 0X1C($sp)
/* 004670 0x80084958 8FBF0014 */ lw	$ra, 0X14($sp)
/* 004671 0x8008495C 27BD0020 */ addiu	$sp, $sp, 0X20
/* 004672 0x80084960 03E00008 */ jr	$ra
/* 004673 0x80084964 00000000 */ nop

glabel func_80084968
/* 004674 0x80084968 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 004675 0x8008496C AFBF0014 */ sw	$ra, 0X14($sp)
/* 004676 0x80084970 0C021250 */ jal	func_80084940
/* 004677 0x80084974 00000000 */ nop
/* 004678 0x80084978 0C0244AC */ jal	osDpSetStatus
/* 004679 0x8008497C 24040028 */ li	$a0, 0X28
/* 004680 0x80084980 0C0254A0 */ jal	__osSpSetStatus
/* 004681 0x80084984 24044082 */ li	$a0, 0X4082
/* 004682 0x80084988 0C021250 */ jal	func_80084940
/* 004683 0x8008498C 00000000 */ nop
/* 004684 0x80084990 8FBF0014 */ lw	$ra, 0X14($sp)
/* 004685 0x80084994 27BD0018 */ addiu	$sp, $sp, 0X18
/* 004686 0x80084998 03E00008 */ jr	$ra
/* 004687 0x8008499C 00000000 */ nop
