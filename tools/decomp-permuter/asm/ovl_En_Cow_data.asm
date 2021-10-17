.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Cow_InitVars
/* 001240 0x8099D5F0 */ .word	0x00F30400
/* 001241 0x8099D5F4 */ .word	0x00000009
/* 001242 0x8099D5F8 */ .word	0x01460000
/* 001243 0x8099D5FC */ .word	0x00000278
/* 001244 0x8099D600 */ .word	EnCow_Init
/* 001245 0x8099D604 */ .word	EnCow_Destroy
/* 001246 0x8099D608 */ .word	EnCow_Update
/* 001247 0x8099D60C */ .word	EnCow_Draw
glabel D_8099D610
/* 001248 0x8099D610 */ .word	0x0A001139
/* 001249 0x8099D614 */ .word	0x10010000
/* 001250 0x8099D618 */ .word	0x00000000
/* 001251 0x8099D61C */ .word	0x00000000
/* 001252 0x8099D620 */ .word	0x00000000
/* 001253 0x8099D624 */ .word	0xF7CFFFFF
/* 001254 0x8099D628 */ .word	0x00000000
/* 001255 0x8099D62C */ .word	0x00010100
/* 001256 0x8099D630 */ .word	0x001E0028
/* 001257 0x8099D634 */ .word	0x00000000
/* 001258 0x8099D638 */ .word	0x00000000
glabel D_8099D63C
/* 001259 0x8099D63C */ .word	0x00000000
/* 001260 0x8099D640 */ .word	0xC4A28000
/* 001261 0x8099D644 */ .word	0x44898000
/* 001262 0x8099D648 */ .word	0x00000000
/* 001263 0x8099D64C */ .word	0x00000000
