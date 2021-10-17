.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Zl4_InitVars
/* 000236 0x809A1F60 */ .word	0x00FD0700
/* 000237 0x809A1F64 */ .word	0x00000030
/* 000238 0x809A1F68 */ .word	0x01920000
/* 000239 0x809A1F6C */ .word	0x000002F4
/* 000240 0x809A1F70 */ .word	EnZl4_Init
/* 000241 0x809A1F74 */ .word	EnZl4_Destroy
/* 000242 0x809A1F78 */ .word	EnZl4_Update
/* 000243 0x809A1F7C */ .word	EnZl4_Draw
glabel D_809A1F80
/* 000244 0x809A1F80 */ .word	0x0600CC94
/* 000245 0x809A1F84 */ .word	0x3F800000
/* 000246 0x809A1F88 */ .word	0x00000000
/* 000247 0x809A1F8C */ .word	0xBF800000
/* 000248 0x809A1F90 */ .word	0x00000000
/* 000249 0x809A1F94 */ .word	0x00000000
glabel D_809A1F98
/* 000250 0x809A1F98 */ .word	0x00000000
/* 000251 0x809A1F9C */ .word	0x00000000
/* 000252 0x809A1FA0 */ .word	0x00000000
/* 000253 0x809A1FA4 */ .word	0x00000000
/* 000254 0x809A1FA8 */ .word	0x00000000
/* 000255 0x809A1FAC */ .word	0x00000000
