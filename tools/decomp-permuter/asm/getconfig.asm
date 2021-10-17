.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetConfig
/* 011668 0x8008B6B0 40028000 */ mfc0	$v0, $16
/* 011669 0x8008B6B4 03E00008 */ jr	$ra
/* 011670 0x8008B6B8 00000000 */ nop
/* 011671 0x8008B6BC 00000000 */ nop
