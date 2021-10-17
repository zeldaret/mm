.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Minifrog_InitVars
/* 001452 0x808A4D20 */ .word	0x00220400
/* 001453 0x808A4D24 */ .word	0x00000019
/* 001454 0x808A4D28 */ .word	0x00BC0000
/* 001455 0x808A4D2C */ .word	0x00000304
/* 001456 0x808A4D30 */ .word	EnMinifrog_Init
/* 001457 0x808A4D34 */ .word	EnMinifrog_Destroy
/* 001458 0x808A4D38 */ .word	EnMinifrog_Update
/* 001459 0x808A4D3C */ .word	EnMinifrog_Draw
glabel D_808A4D40
/* 001460 0x808A4D40 */ .word	0x0A000039
/* 001461 0x808A4D44 */ .word	0x10010000
/* 001462 0x808A4D48 */ .word	0x01000000
/* 001463 0x808A4D4C */ .word	0xF7CFFFFF
/* 001464 0x808A4D50 */ .word	0x00000000
/* 001465 0x808A4D54 */ .word	0xF7CFFFFF
/* 001466 0x808A4D58 */ .word	0x00000000
/* 001467 0x808A4D5C */ .word	0x00000100
/* 001468 0x808A4D60 */ .word	0x000C000E
/* 001469 0x808A4D64 */ .word	0x00000000
/* 001470 0x808A4D68 */ .word	0x00000000
glabel D_808A4D6C
/* 001471 0x808A4D6C */ .word	0x0100000C
/* 001472 0x808A4D70 */ .word	0x000EFF00
glabel D_808A4D74
/* 001473 0x808A4D74 */ .word	0x060059A0
/* 001474 0x808A4D78 */ .word	0x06005BA0
glabel D_808A4D7C
/* 001475 0x808A4D7C */ .word	0x00002040
/* 001476 0x808A4D80 */ .word	0x20802101
/* 001477 0x808A4D84 */ .word	0x21020000
glabel D_808A4D88
/* 001478 0x808A4D88 */ .word	0x00000000
glabel D_808A4D8C
/* 001479 0x808A4D8C */ .word	0x3874FCE0
glabel D_808A4D90
/* 001480 0x808A4D90 */ .word	0xFFFFFFFF
glabel D_808A4D94
/* 001481 0x808A4D94 */ .word	0x505050FF
glabel D_808A4D98
/* 001482 0x808A4D98 */ .word	0xC8AA00FF
/* 001483 0x808A4D9C */ .word	0x00AAC8FF
/* 001484 0x808A4DA0 */ .word	0xD27864FF
/* 001485 0x808A4DA4 */ .word	0x7882E6FF
/* 001486 0x808A4DA8 */ .word	0xBEBEBEFF
/* 001487 0x808A4DAC */ .word	0x00000000
