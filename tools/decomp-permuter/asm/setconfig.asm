.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSetConfig
/* 011672 0x8008B6C0 40848000 */ mtc0	$a0, $16
/* 011673 0x8008B6C4 03E00008 */ jr	$ra
/* 011674 0x8008B6C8 00000000 */ nop
/* 011675 0x8008B6CC 00000000 */ nop
