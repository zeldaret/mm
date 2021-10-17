.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Warp_tag_InitVars
/* 000544 0x809C0FE0 */ .word	0x01160700
/* 000545 0x809C0FE4 */ .word	0x0A000011
/* 000546 0x809C0FE8 */ .word	0x00010000
/* 000547 0x809C0FEC */ .word	0x00000164
/* 000548 0x809C0FF0 */ .word	EnWarptag_Init
/* 000549 0x809C0FF4 */ .word	EnWarptag_Destroy
/* 000550 0x809C0FF8 */ .word	EnWarptag_Update
/* 000551 0x809C0FFC */ .word	0x00000000
glabel D_809C1000
/* 000552 0x809C1000 */ .word	0x28292A2B
/* 000553 0x809C1004 */ .word	0x2D2C0000
glabel D_809C1008
/* 000554 0x809C1008 */ .word	0xC0580001
/* 000555 0x809C100C */ .word	0x50BC0000
