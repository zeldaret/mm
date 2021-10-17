.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSetCompare
/* 017544 0x80091280 40845800 */ mtc0	$a0, $11
/* 017545 0x80091284 03E00008 */ jr	$ra
/* 017546 0x80091288 00000000 */ nop
/* 017547 0x8009128C 00000000 */ nop
