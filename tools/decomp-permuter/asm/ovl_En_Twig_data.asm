.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Twig_InitVars
/* 000536 0x80AC1090 */ .word	0x01A50800
/* 000537 0x80AC1094 */ .word	0x00000010
/* 000538 0x80AC1098 */ .word	0x01990000
/* 000539 0x80AC109C */ .word	0x0000018C
/* 000540 0x80AC10A0 */ .word	EnTwig_Init
/* 000541 0x80AC10A4 */ .word	EnTwig_Destroy
/* 000542 0x80AC10A8 */ .word	EnTwig_Update
/* 000543 0x80AC10AC */ .word	EnTwig_Draw
glabel D_80AC10B0
/* 000544 0x80AC10B0 */ .word	0x00000000
/* 000545 0x80AC10B4 */ .word	0x060020A0
/* 000546 0x80AC10B8 */ .word	0x060016C0
glabel D_80AC10BC
/* 000547 0x80AC10BC */ .word	0x00000000
glabel D_80AC10C0
/* 000548 0x80AC10C0 */ .word	0xB1000028
/* 000549 0x80AC10C4 */ .word	0xB1040028
/* 000550 0x80AC10C8 */ .word	0xB0FC03E8
/* 000551 0x80AC10CC */ .word	0x4858000A
glabel D_80AC10D0
/* 000552 0x80AC10D0 */ .word	0x00000000
/* 000553 0x80AC10D4 */ .word	0x00000000
/* 000554 0x80AC10D8 */ .word	0x3F800000
glabel D_80AC10DC
/* 000555 0x80AC10DC */ .word	0x00000000
/* 000556 0x80AC10E0 */ .word	0xBD4CCCCD
/* 000557 0x80AC10E4 */ .word	0x00000000
glabel D_80AC10E8
/* 000558 0x80AC10E8 */ .word	0x00000000
/* 000559 0x80AC10EC */ .word	0xBCCCCCCD
/* 000560 0x80AC10F0 */ .word	0x00000000
glabel D_80AC10F4
/* 000561 0x80AC10F4 */ .word	0xFFFFFF82
glabel D_80AC10F8
/* 000562 0x80AC10F8 */ .word	0xFFFF0000
/* 000563 0x80AC10FC */ .word	0x00000000
