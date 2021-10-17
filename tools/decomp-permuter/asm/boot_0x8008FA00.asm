.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSpDeviceBusy
/* 015976 0x8008FA00 3C0EA404 */ lui	$t6, 0xA404
/* 015977 0x8008FA04 8DC20010 */ lw	$v0, 0X10($t6)
/* 015978 0x8008FA08 304F001C */ andi	$t7, $v0, 0X1C
/* 015979 0x8008FA0C 11E00003 */ beqz	$t7, .L8008FA1C
/* 015980 0x8008FA10 00001025 */ move	$v0, $zero
/* 015981 0x8008FA14 03E00008 */ jr	$ra
/* 015982 0x8008FA18 24020001 */ li	$v0, 0X1
.L8008FA1C:
/* 015983 0x8008FA1C 03E00008 */ jr	$ra
/* 015984 0x8008FA20 00000000 */ nop
/* 015985 0x8008FA24 00000000 */ nop
/* 015986 0x8008FA28 00000000 */ nop
/* 015987 0x8008FA2C 00000000 */ nop
