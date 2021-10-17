.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSetCause
/* 007848 0x80087B00 40846800 */ mtc0	$a0, $13
/* 007849 0x80087B04 03E00008 */ jr	$ra
/* 007850 0x80087B08 00000000 */ nop
/* 007851 0x80087B0C 00000000 */ nop
