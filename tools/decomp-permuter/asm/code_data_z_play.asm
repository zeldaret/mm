.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D0D50
/* 306340 0x801D0D50 */ .word	0x00000000
glabel D_801D0D54
/* 306341 0x801D0D54 */ .word	0x00000000
glabel D_801D0D58
/* 306342 0x801D0D58 */ .word	0xFFFF0000
glabel D_801D0D5C
/* 306343 0x801D0D5C */ .word	0x00000000
glabel D_801D0D60
/* 306344 0x801D0D60 */ .word	0x00000000
glabel D_801D0D64
/* 306345 0x801D0D64 */ .word	0xFFFDFFFE
/* 306346 0x801D0D68 */ .word	0xFFFCFFFB
/* 306347 0x801D0D6C */ .word	0xFFF9FFF5
/* 306348 0x801D0D70 */ .word	0xFFF8FFF7
/* 306349 0x801D0D74 */ .word	0xFFFAFFF0
/* 306350 0x801D0D78 */ .short	0x0000
glabel D_801D0D7A
/* 306350 0x801D0D78 */ .short	0x0000
/* 306351 0x801D0D7C */ .word	0x00000000
