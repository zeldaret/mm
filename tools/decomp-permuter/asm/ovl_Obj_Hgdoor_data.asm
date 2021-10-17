.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Hgdoor_InitVars
/* 000376 0x80BD4670 */ .word	0x02540600
/* 000377 0x80BD4674 */ .word	0x00100000
/* 000378 0x80BD4678 */ .word	0x022C0000
/* 000379 0x80BD467C */ .word	0x00000168
/* 000380 0x80BD4680 */ .word	ObjHgdoor_Init
/* 000381 0x80BD4684 */ .word	ObjHgdoor_Destroy
/* 000382 0x80BD4688 */ .word	ObjHgdoor_Update
/* 000383 0x80BD468C */ .word	ObjHgdoor_Draw
glabel D_80BD4690
/* 000384 0x80BD4690 */ .word	0x00000000
/* 000385 0x80BD4694 */ .word	0x00000000
/* 000386 0x80BD4698 */ .word	0x00000000
/* 000387 0x80BD469C */ .word	0x00000000
