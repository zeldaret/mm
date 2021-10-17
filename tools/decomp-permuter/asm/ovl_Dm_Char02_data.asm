.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Char02_InitVars
/* 000344 0x80AAB390 */ .word	0x01940700
/* 000345 0x80AAB394 */ .word	0x00000030
/* 000346 0x80AAB398 */ .word	0x01BE0000
/* 000347 0x80AAB39C */ .word	0x000002F4
/* 000348 0x80AAB3A0 */ .word	DmChar02_Init
/* 000349 0x80AAB3A4 */ .word	DmChar02_Destroy
/* 000350 0x80AAB3A8 */ .word	DmChar02_Update
/* 000351 0x80AAB3AC */ .word	DmChar02_Draw
glabel D_80AAB3B0
/* 000352 0x80AAB3B0 */ .word	0x0600A2BC
/* 000353 0x80AAB3B4 */ .word	0x3F800000
/* 000354 0x80AAB3B8 */ .word	0x00000000
/* 000355 0x80AAB3BC */ .word	0xBF800000
/* 000356 0x80AAB3C0 */ .word	0x02000000
/* 000357 0x80AAB3C4 */ .word	0x00000000
/* 000358 0x80AAB3C8 */ .word	0x0600A4C4
/* 000359 0x80AAB3CC */ .word	0x3F800000
/* 000360 0x80AAB3D0 */ .word	0x00000000
/* 000361 0x80AAB3D4 */ .word	0xBF800000
/* 000362 0x80AAB3D8 */ .word	0x02000000
/* 000363 0x80AAB3DC */ .word	0x00000000
/* 000364 0x80AAB3E0 */ .word	0x0600A6D4
/* 000365 0x80AAB3E4 */ .word	0x3F800000
/* 000366 0x80AAB3E8 */ .word	0x00000000
/* 000367 0x80AAB3EC */ .word	0xBF800000
/* 000368 0x80AAB3F0 */ .word	0x00000000
/* 000369 0x80AAB3F4 */ .word	0x00000000
/* 000370 0x80AAB3F8 */ .word	0x0600A104
/* 000371 0x80AAB3FC */ .word	0x3F800000
/* 000372 0x80AAB400 */ .word	0x00000000
/* 000373 0x80AAB404 */ .word	0xBF800000
/* 000374 0x80AAB408 */ .word	0x02000000
/* 000375 0x80AAB40C */ .word	0x00000000
