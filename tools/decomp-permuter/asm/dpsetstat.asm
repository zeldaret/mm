.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osDpSetStatus
/* 017556 0x800912B0 3C0EA410 */ lui	$t6, 0xA410
/* 017557 0x800912B4 03E00008 */ jr	$ra
/* 017558 0x800912B8 ADC4000C */ sw	$a0, 0XC($t6)
/* 017559 0x800912BC 00000000 */ nop
