.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osAiGetLength
/* 020176 0x80093BA0 3C0EA450 */ lui	$t6, 0xA450
/* 020177 0x80093BA4 03E00008 */ jr	$ra
/* 020178 0x80093BA8 8DC20004 */ lw	$v0, 0X4($t6)
/* 020179 0x80093BAC 00000000 */ nop
