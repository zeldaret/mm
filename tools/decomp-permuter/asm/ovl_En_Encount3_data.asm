.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Encount3_InitVars
/* 000556 0x809AD7F0 */ .word	0x01120500
/* 000557 0x809AD7F4 */ .word	0x08000030
/* 000558 0x809AD7F8 */ .word	0x023B0000
/* 000559 0x809AD7FC */ .word	0x000001CC
/* 000560 0x809AD800 */ .word	EnEncount3_Init
/* 000561 0x809AD804 */ .word	EnEncount3_Destroy
/* 000562 0x809AD808 */ .word	EnEncount3_Update
/* 000563 0x809AD80C */ .word	EnEncount3_Draw
glabel D_809AD810
/* 000564 0x809AD810 */ .word	0x00000000
/* 000565 0x809AD814 */ .word	0x00000000
/* 000566 0x809AD818 */ .word	0x00000000
/* 000567 0x809AD81C */ .word	0x00000000
