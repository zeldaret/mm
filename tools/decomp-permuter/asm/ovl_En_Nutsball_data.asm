.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Nutsball_InitVars
/* 000356 0x809861D0 */ .word	0x00DA0600
/* 000357 0x809861D4 */ .word	0x00000010
/* 000358 0x809861D8 */ .word	0x00010000
/* 000359 0x809861DC */ .word	0x00000194
/* 000360 0x809861E0 */ .word	EnNutsball_Init
/* 000361 0x809861E4 */ .word	EnNutsball_Destroy
/* 000362 0x809861E8 */ .word	EnNutsball_Update
/* 000363 0x809861EC */ .word	EnNutsball_Draw
glabel D_809861F0
/* 000364 0x809861F0 */ .word	0x0A110939
/* 000365 0x809861F4 */ .word	0x20010000
/* 000366 0x809861F8 */ .word	0x00000000
/* 000367 0x809861FC */ .word	0xF7CFFFFF
/* 000368 0x80986200 */ .word	0x00040000
/* 000369 0x80986204 */ .word	0xF7CFFFFF
/* 000370 0x80986208 */ .word	0x00000000
/* 000371 0x8098620C */ .word	0x11010100
/* 000372 0x80986210 */ .word	0x000D000D
/* 000373 0x80986214 */ .word	0x00000000
/* 000374 0x80986218 */ .word	0x00000000
/* 000375 0x8098621C */ .word	0x00000000
