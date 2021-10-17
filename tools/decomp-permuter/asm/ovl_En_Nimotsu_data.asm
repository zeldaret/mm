.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Nimotsu_InitVars
/* 000196 0x80BE1F90 */ .word	0x02640600
/* 000197 0x80BE1F94 */ .word	0x00000010
/* 000198 0x80BE1F98 */ .word	0x00E30000
/* 000199 0x80BE1F9C */ .word	0x000001DC
/* 000200 0x80BE1FA0 */ .word	EnNimotsu_Init
/* 000201 0x80BE1FA4 */ .word	EnNimotsu_Destroy
/* 000202 0x80BE1FA8 */ .word	EnNimotsu_Update
/* 000203 0x80BE1FAC */ .word	EnNimotsu_Draw
glabel D_80BE1FB0
/* 000204 0x80BE1FB0 */ .word	0x0A000039
/* 000205 0x80BE1FB4 */ .word	0x20010000
/* 000206 0x80BE1FB8 */ .word	0x04000000
/* 000207 0x80BE1FBC */ .word	0x00000000
/* 000208 0x80BE1FC0 */ .word	0x00000000
/* 000209 0x80BE1FC4 */ .word	0x00000000
/* 000210 0x80BE1FC8 */ .word	0x00000000
/* 000211 0x80BE1FCC */ .word	0x00000100
/* 000212 0x80BE1FD0 */ .word	0x000A001E
/* 000213 0x80BE1FD4 */ .word	0x00000000
/* 000214 0x80BE1FD8 */ .word	0x00000000
/* 000215 0x80BE1FDC */ .word	0x00000000
