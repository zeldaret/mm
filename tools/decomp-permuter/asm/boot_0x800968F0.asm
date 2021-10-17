.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_800968f0
/* 023076 0x800968F0 90A20000 */ lbu	$v0, 0X0($a1)
/* 023077 0x800968F4 00801825 */ move	$v1, $a0
/* 023078 0x800968F8 50400008 */ beqzl	$v0, .L8009691C
/* 023079 0x800968FC A0600000 */ sb	$zero, 0X0($v1)
/* 023080 0x80096900 A0620000 */ sb	$v0, 0X0($v1)
.L80096904:
/* 023081 0x80096904 90A20001 */ lbu	$v0, 0X1($a1)
/* 023082 0x80096908 24630001 */ addiu	$v1, $v1, 0X1
/* 023083 0x8009690C 24A50001 */ addiu	$a1, $a1, 0X1
/* 023084 0x80096910 5440FFFC */ bnezl	$v0, .L80096904
/* 023085 0x80096914 A0620000 */ sb	$v0, 0X0($v1)
/* 023086 0x80096918 A0600000 */ sb	$zero, 0X0($v1)
.L8009691C:
/* 023087 0x8009691C 03E00008 */ jr	$ra
/* 023088 0x80096920 00801025 */ move	$v0, $a0
/* 023089 0x80096924 00000000 */ nop
/* 023090 0x80096928 00000000 */ nop
/* 023091 0x8009692C 00000000 */ nop
