.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Test5_InitVars
/* 000204 0x80A906E0 */ .word	0x018B0700
/* 000205 0x80A906E4 */ .word	0x00000010
/* 000206 0x80A906E8 */ .word	0x00010000
/* 000207 0x80A906EC */ .word	0x0000015C
/* 000208 0x80A906F0 */ .word	EnTest5_Init
/* 000209 0x80A906F4 */ .word	EnTest5_Destroy
/* 000210 0x80A906F8 */ .word	EnTest5_Update
/* 000211 0x80A906FC */ .word	0x00000000
