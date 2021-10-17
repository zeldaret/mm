.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Invisible_Ruppe_InitVars
/* 000164 0x80C25B30 */ .word	0x02AF0400
/* 000165 0x80C25B34 */ .word	0x00000000
/* 000166 0x80C25B38 */ .word	0x00010000
/* 000167 0x80C25B3C */ .word	0x00000198
/* 000168 0x80C25B40 */ .word	EnInvisibleRuppe_Init
/* 000169 0x80C25B44 */ .word	EnInvisibleRuppe_Destroy
/* 000170 0x80C25B48 */ .word	EnInvisibleRuppe_Update
/* 000171 0x80C25B4C */ .word	0x00000000
glabel D_80C25B50
/* 000172 0x80C25B50 */ .word	0x0A00000D
/* 000173 0x80C25B54 */ .word	0x20010000
/* 000174 0x80C25B58 */ .word	0x04000000
/* 000175 0x80C25B5C */ .word	0x00000000
/* 000176 0x80C25B60 */ .word	0x00000000
/* 000177 0x80C25B64 */ .word	0x00000000
/* 000178 0x80C25B68 */ .word	0x00000000
/* 000179 0x80C25B6C */ .word	0x00000100
/* 000180 0x80C25B70 */ .word	0x000A001E
/* 000181 0x80C25B74 */ .word	0x00000000
/* 000182 0x80C25B78 */ .word	0x00000000
/* 000183 0x80C25B7C */ .word	0x00000000
