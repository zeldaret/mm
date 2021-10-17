.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Crow_InitVars
/* 001352 0x8099C050 */ .word	0x00F10500
/* 001353 0x8099C054 */ .word	0x00005005
/* 001354 0x8099C058 */ .word	0x00060000
/* 001355 0x8099C05C */ .word	0x0000029C
/* 001356 0x8099C060 */ .word	EnCrow_Init
/* 001357 0x8099C064 */ .word	EnCrow_Destroy
/* 001358 0x8099C068 */ .word	EnCrow_Update
/* 001359 0x8099C06C */ .word	EnCrow_Draw
glabel D_8099C070
/* 001360 0x8099C070 */ .word	0x00000000
/* 001361 0x8099C074 */ .word	0xF7CFFFFF
/* 001362 0x8099C078 */ .word	0x00080000
/* 001363 0x8099C07C */ .word	0xF7CFFFFF
/* 001364 0x8099C080 */ .word	0x00000000
/* 001365 0x8099C084 */ .word	0x09010100
/* 001366 0x8099C088 */ .word	0x01000000
/* 001367 0x8099C08C */ .word	0x00000000
/* 001368 0x8099C090 */ .word	0x00140064
glabel D_8099C094
/* 001369 0x8099C094 */ .word	0x03110939
/* 001370 0x8099C098 */ .word	0x10000000
/* 001371 0x8099C09C */ .word	0x00000001
glabel D_8099C0A0
/* 001372 0x8099C0A0 */ .word	D_8099C070
glabel D_8099C0A4
/* 001373 0x8099C0A4 */ .word	0x0100000F
/* 001374 0x8099C0A8 */ .word	0x001E1E00
glabel D_8099C0AC
/* 001375 0x8099C0AC */ .word	0x10010101
/* 001376 0x8099C0B0 */ .word	0x01010001
/* 001377 0x8099C0B4 */ .word	0x01010122
/* 001378 0x8099C0B8 */ .word	0x32420101
/* 001379 0x8099C0BC */ .word	0x01021050
/* 001380 0x8099C0C0 */ .word	0x00000101
/* 001381 0x8099C0C4 */ .word	0x01000000
/* 001382 0x8099C0C8 */ .word	0x00000001
glabel D_8099C0CC
/* 001383 0x8099C0CC */ .word	0x00000000
glabel D_8099C0D0
/* 001384 0x8099C0D0 */ .word	0xB0FC0BB8
/* 001385 0x8099C0D4 */ .word	0x891F0058
/* 001386 0x8099C0D8 */ .word	0xB874FE0C
/* 001387 0x8099C0DC */ .word	0x305407D0
