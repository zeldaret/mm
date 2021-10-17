.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Tag_InitVars
/* 000544 0x80C22BD0 */ .word	0x02A60700
/* 000545 0x80C22BD4 */ .word	0x00000010
/* 000546 0x80C22BD8 */ .word	0x00010000
/* 000547 0x80C22BDC */ .word	0x000001AC
/* 000548 0x80C22BE0 */ .word	DmTag_Init
/* 000549 0x80C22BE4 */ .word	DmTag_Destroy
/* 000550 0x80C22BE8 */ .word	DmTag_Update
/* 000551 0x80C22BEC */ .word	0x00000000
glabel D_80C22BF0
/* 000552 0x80C22BF0 */ .word	0x0E28F00C
/* 000553 0x80C22BF4 */ .word	0x15090000
/* 000554 0x80C22BF8 */ .word	0x10000000
glabel D_80C22BFC
/* 000555 0x80C22BFC */ .word	0x0900000E
/* 000556 0x80C22C00 */ .word	0x28F10C09
/* 000557 0x80C22C04 */ .word	0x00000E28
/* 000558 0x80C22C08 */ .word	0xF20C0900
/* 000559 0x80C22C0C */ .word	0x000E28F3
/* 000560 0x80C22C10 */ .word	0x0C090000
/* 000561 0x80C22C14 */ .word	0x0E28F40C
/* 000562 0x80C22C18 */ .word	0x0900000E
/* 000563 0x80C22C1C */ .word	0x28F50C09
/* 000564 0x80C22C20 */ .word	0x00000E28
/* 000565 0x80C22C24 */ .word	0xF60C1511
/* 000566 0x80C22C28 */ .word	0x55040900
/* 000567 0x80C22C2C */ .word	0x00100000
glabel D_80C22C30
/* 000568 0x80C22C30 */ .word	0x0E28EF0C
/* 000569 0x80C22C34 */ .word	0x10000000
/* 000570 0x80C22C38 */ .word	0x00000000
/* 000571 0x80C22C3C */ .word	0x00000000
