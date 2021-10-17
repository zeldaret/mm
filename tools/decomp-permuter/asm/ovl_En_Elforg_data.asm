.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Elforg_InitVars
/* 001384 0x80ACDA10 */ .word	0x01B00700
/* 001385 0x80ACDA14 */ .word	0x00000010
/* 001386 0x80ACDA18 */ .word	0x00010000
/* 001387 0x80ACDA1C */ .word	0x00000230
/* 001388 0x80ACDA20 */ .word	EnElforg_Init
/* 001389 0x80ACDA24 */ .word	EnElforg_Destroy
/* 001390 0x80ACDA28 */ .word	EnElforg_Update
/* 001391 0x80ACDA2C */ .word	EnElforg_Draw
glabel D_80ACDA30
/* 001392 0x80ACDA30 */ .word	0x0A000909
/* 001393 0x80ACDA34 */ .word	0x10010000
/* 001394 0x80ACDA38 */ .word	0x00000000
/* 001395 0x80ACDA3C */ .word	0x00000000
/* 001396 0x80ACDA40 */ .word	0x00000000
/* 001397 0x80ACDA44 */ .word	0xF7CFFFFF
/* 001398 0x80ACDA48 */ .word	0x00000000
/* 001399 0x80ACDA4C */ .word	0x00010000
/* 001400 0x80ACDA50 */ .word	0x00100020
/* 001401 0x80ACDA54 */ .word	0x00000000
/* 001402 0x80ACDA58 */ .word	0x00000000
glabel D_80ACDA5C
/* 001403 0x80ACDA5C */ .word	0x00000000
/* 001404 0x80ACDA60 */ .word	0xBD4CCCCD
/* 001405 0x80ACDA64 */ .word	0x00000000
glabel D_80ACDA68
/* 001406 0x80ACDA68 */ .word	0x00000000
/* 001407 0x80ACDA6C */ .word	0xBCCCCCCD
/* 001408 0x80ACDA70 */ .word	0x00000000
glabel D_80ACDA74
/* 001409 0x80ACDA74 */ .word	0xFFEBDCFF
/* 001410 0x80ACDA78 */ .word	0xFFDCDCFF
/* 001411 0x80ACDA7C */ .word	0xDCFFDCFF
/* 001412 0x80ACDA80 */ .word	0xDCDCFFFF
/* 001413 0x80ACDA84 */ .word	0xFFFFC8FF
glabel D_80ACDA88
/* 001414 0x80ACDA88 */ .word	0xFF9600FF
/* 001415 0x80ACDA8C */ .word	0xFF0000FF
/* 001416 0x80ACDA90 */ .word	0x00FF00FF
/* 001417 0x80ACDA94 */ .word	0x0000FFFF
/* 001418 0x80ACDA98 */ .word	0xFFFF00FF
/* 001419 0x80ACDA9C */ .word	0x00000000
