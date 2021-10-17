.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osGetActiveQueue
/* 017516 0x80091210 3C028009 */ lui	$v0, %hi(__osActiveQueue)
/* 017517 0x80091214 03E00008 */ jr	$ra
/* 017518 0x80091218 8C427E1C */ lw	$v0, %lo(__osActiveQueue)($v0)
/* 017519 0x8009121C 00000000 */ nop
