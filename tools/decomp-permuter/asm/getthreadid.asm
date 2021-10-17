.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osGetThreadId
/* 011188 0x8008AF30 14800003 */ bnez	$a0, .L8008AF40
/* 011189 0x8008AF34 00000000 */ nop
/* 011190 0x8008AF38 3C048009 */ lui	$a0, %hi(__osRunningThread)
/* 011191 0x8008AF3C 8C847E20 */ lw	$a0, %lo(__osRunningThread)($a0)
.L8008AF40:
/* 011192 0x8008AF40 03E00008 */ jr	$ra
/* 011193 0x8008AF44 8C820014 */ lw	$v0, 0X14($a0)
/* 011194 0x8008AF48 00000000 */ nop
/* 011195 0x8008AF4C 00000000 */ nop
