.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Cha_InitVars
/* 000208 0x80BEB860 */ .word	0x02700600
/* 000209 0x80BEB864 */ .word	0x00000000
/* 000210 0x80BEB868 */ .word	0x02430000
/* 000211 0x80BEB86C */ .word	0x00000194
/* 000212 0x80BEB870 */ .word	EnCha_Init
/* 000213 0x80BEB874 */ .word	EnCha_Destroy
/* 000214 0x80BEB878 */ .word	EnCha_Update
/* 000215 0x80BEB87C */ .word	EnCha_Draw
glabel D_80BEB880
/* 000216 0x80BEB880 */ .word	0x0B000D39
/* 000217 0x80BEB884 */ .word	0x10010000
/* 000218 0x80BEB888 */ .word	0x00000000
/* 000219 0x80BEB88C */ .word	0x00000000
/* 000220 0x80BEB890 */ .word	0x00000000
/* 000221 0x80BEB894 */ .word	0xF7CFFFFF
/* 000222 0x80BEB898 */ .word	0x00000000
/* 000223 0x80BEB89C */ .word	0x00010100
/* 000224 0x80BEB8A0 */ .word	0x000A0028
/* 000225 0x80BEB8A4 */ .word	0x00000000
/* 000226 0x80BEB8A8 */ .word	0x00000000
/* 000227 0x80BEB8AC */ .word	0x00000000
