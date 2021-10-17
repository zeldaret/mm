.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80098280
/* 024712 0x80098280 */ .word	0x53505F53
/* 024713 0x80098284 */ .word	0x54415455
/* 024714 0x80098288 */ .word	0x53202530
/* 024715 0x8009828C */ .word	0x38780000
glabel D_80098290
/* 024716 0x80098290 */ .word	0x524F4D5F
/* 024717 0x80098294 */ .word	0x46205B43
/* 024718 0x80098298 */ .word	0x72656174
/* 024719 0x8009829C */ .word	0x6F723A25
/* 024720 0x800982A0 */ .word	0x735D0000
glabel D_800982A4
/* 024721 0x800982A4 */ .word	0x5B446174
/* 024722 0x800982A8 */ .word	0x653A2573
/* 024723 0x800982AC */ .word	0x5D000000
