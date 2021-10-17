.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osGetThreadPri
/* 016160 0x8008FCE0 14800003 */ bnez	$a0, .L8008FCF0
/* 016161 0x8008FCE4 00000000 */ nop
/* 016162 0x8008FCE8 3C048009 */ lui	$a0, %hi(__osRunningThread)
/* 016163 0x8008FCEC 8C847E20 */ lw	$a0, %lo(__osRunningThread)($a0)
.L8008FCF0:
/* 016164 0x8008FCF0 03E00008 */ jr	$ra
/* 016165 0x8008FCF4 8C820004 */ lw	$v0, 0X4($a0)
/* 016166 0x8008FCF8 00000000 */ nop
/* 016167 0x8008FCFC 00000000 */ nop
