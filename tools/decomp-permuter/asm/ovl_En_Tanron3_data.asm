.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80BB9720
/* 001120 0x80BB9720 */ .word	0x00000000
/* 001121 0x80BB9724 */ .word	0x00000000
/* 001122 0x80BB9728 */ .word	0x00000000
glabel D_80BB972C
/* 001123 0x80BB972C */ .word	0x00000000
glabel En_Tanron3_InitVars
/* 001124 0x80BB9730 */ .word	0x023F0900
/* 001125 0x80BB9734 */ .word	0x00000035
/* 001126 0x80BB9738 */ .word	0x015C0000
/* 001127 0x80BB973C */ .word	0x000002FC
/* 001128 0x80BB9740 */ .word	EnTanron3_Init
/* 001129 0x80BB9744 */ .word	EnTanron3_Destroy
/* 001130 0x80BB9748 */ .word	EnTanron3_Update
/* 001131 0x80BB974C */ .word	EnTanron3_Draw
glabel D_80BB9750
/* 001132 0x80BB9750 */ .word	0x03110939
/* 001133 0x80BB9754 */ .word	0x10010000
/* 001134 0x80BB9758 */ .word	0x03000000
/* 001135 0x80BB975C */ .word	0xF7CFFFFF
/* 001136 0x80BB9760 */ .word	0x00020000
/* 001137 0x80BB9764 */ .word	0xF7CFFFFF
/* 001138 0x80BB9768 */ .word	0x00000000
/* 001139 0x80BB976C */ .word	0x01010100
/* 001140 0x80BB9770 */ .word	0x0007000A
/* 001141 0x80BB9774 */ .word	0xFFFB0000
/* 001142 0x80BB9778 */ .word	0x00000000
/* 001143 0x80BB977C */ .word	0x03110939
/* 001144 0x80BB9780 */ .word	0x10010000
/* 001145 0x80BB9784 */ .word	0x03000000
/* 001146 0x80BB9788 */ .word	0xF7CFFFFF
/* 001147 0x80BB978C */ .word	0x00020000
/* 001148 0x80BB9790 */ .word	0xF7CFFFFF
/* 001149 0x80BB9794 */ .word	0x00000000
/* 001150 0x80BB9798 */ .word	0x01010100
/* 001151 0x80BB979C */ .word	0x00140014
/* 001152 0x80BB97A0 */ .word	0xFFF60000
/* 001153 0x80BB97A4 */ .word	0x00000000
glabel D_80BB97A8
/* 001154 0x80BB97A8 */ .word	0x643737FF
glabel D_80BB97AC
/* 001155 0x80BB97AC */ .word	0x320A0AFF
