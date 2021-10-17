.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Elfbub_InitVars
/* 000352 0x80ACE250 */ .word	0x01B10800
/* 000353 0x80ACE254 */ .word	0x00000001
/* 000354 0x80ACE258 */ .word	0x000E0000
/* 000355 0x80ACE25C */ .word	0x000001A4
/* 000356 0x80ACE260 */ .word	EnElfbub_Init
/* 000357 0x80ACE264 */ .word	EnElfbub_Destroy
/* 000358 0x80ACE268 */ .word	EnElfbub_Update
/* 000359 0x80ACE26C */ .word	EnElfbub_Draw
glabel D_80ACE270
/* 000360 0x80ACE270 */ .word	0x0A000909
/* 000361 0x80ACE274 */ .word	0x10010000
/* 000362 0x80ACE278 */ .word	0x00000000
/* 000363 0x80ACE27C */ .word	0x00000000
/* 000364 0x80ACE280 */ .word	0x00000000
/* 000365 0x80ACE284 */ .word	0xF7CFFFFF
/* 000366 0x80ACE288 */ .word	0x00000000
/* 000367 0x80ACE28C */ .word	0x00010100
/* 000368 0x80ACE290 */ .word	0x00100020
/* 000369 0x80ACE294 */ .word	0x00000000
/* 000370 0x80ACE298 */ .word	0x00000000
glabel D_80ACE29C
/* 000371 0x80ACE29C */ .word	0xFFFFFFFF
glabel D_80ACE2A0
/* 000372 0x80ACE2A0 */ .word	0x96969600
glabel D_80ACE2A4
/* 000373 0x80ACE2A4 */ .word	0x00000000
/* 000374 0x80ACE2A8 */ .word	0xBF000000
/* 000375 0x80ACE2AC */ .word	0x00000000
