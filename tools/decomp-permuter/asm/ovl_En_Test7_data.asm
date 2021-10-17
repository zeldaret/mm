.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Test7_InitVars
/* 002804 0x80AF33F0 */ .word	0x01CE0700
/* 002805 0x80AF33F4 */ .word	0x02300030
/* 002806 0x80AF33F8 */ .word	0x00010000
/* 002807 0x80AF33FC */ .word	0x00001E9C
/* 002808 0x80AF3400 */ .word	EnTest7_Init
glabel D_80AF3404
/* 002809 0x80AF3404 */ .word	EnTest7_Destroy
/* 002810 0x80AF3408 */ .word	EnTest7_Update
/* 002811 0x80AF340C */ .word	EnTest7_Draw
glabel D_80AF3410
/* 002812 0x80AF3410 */ .word	0x00000000
glabel D_80AF3414
/* 002813 0x80AF3414 */ .word	0x00000000
/* 002814 0x80AF3418 */ .word	0x3F800000
/* 002815 0x80AF341C */ .word	0x00000000
glabel D_80AF3420
/* 002816 0x80AF3420 */ .word	0x00000000
/* 002817 0x80AF3424 */ .word	0x00000000
/* 002818 0x80AF3428 */ .word	0x3F800000
glabel D_80AF342C
/* 002819 0x80AF342C */ .word	0x40000000
glabel D_80AF3430
/* 002820 0x80AF3430 */ .word	0xDCDCFF00
glabel D_80AF3434
/* 002821 0x80AF3434 */ .word	0x40000000
glabel D_80AF3438
/* 002822 0x80AF3438 */ .word	0xDCDCFF00
/* 002823 0x80AF343C */ .word	0x68B06A60
/* 002824 0x80AF3440 */ .word	0xB2309A80
/* 002825 0x80AF3444 */ .word	0xD8903E40
/* 002826 0x80AF3448 */ .word	0x864084A0
/* 002827 0x80AF344C */ .word	0x2040AA30
glabel D_80AF3450
/* 002828 0x80AF3450 */ .short	0x0000
glabel D_80AF3452
/* 002828 0x80AF3450 */ .short	0x31C7
glabel D_80AF3454
/* 002829 0x80AF3454 */ .word	0x455AC000
/* 002830 0x80AF3458 */ .word	0x00000000
/* 002831 0x80AF345C */ .word	0x00000000
