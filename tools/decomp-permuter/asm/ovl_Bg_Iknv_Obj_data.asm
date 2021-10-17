.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Iknv_Obj_InitVars
/* 000456 0x80BD81D0 */ .word	0x025C0100
/* 000457 0x80BD81D4 */ .word	0x00000010
/* 000458 0x80BD81D8 */ .word	0x02370000
/* 000459 0x80BD81DC */ .word	0x000001B0
/* 000460 0x80BD81E0 */ .word	BgIknvObj_Init
/* 000461 0x80BD81E4 */ .word	BgIknvObj_Destroy
/* 000462 0x80BD81E8 */ .word	BgIknvObj_Update
/* 000463 0x80BD81EC */ .word	BgIknvObj_Draw
glabel BgIknvObjCollisionInit
/* 000464 0x80BD81F0 */ .word	0x0A001139
/* 000465 0x80BD81F4 */ .word	0x10010000
/* 000466 0x80BD81F8 */ .word	0x00000000
/* 000467 0x80BD81FC */ .word	0x00000000
/* 000468 0x80BD8200 */ .word	0x00000000
/* 000469 0x80BD8204 */ .word	0xF7CFFFFF
/* 000470 0x80BD8208 */ .word	0x00000000
/* 000471 0x80BD820C */ .word	0x00010100
/* 000472 0x80BD8210 */ .word	0x00280028
/* 000473 0x80BD8214 */ .word	0x00000000
/* 000474 0x80BD8218 */ .word	0x00000000
/* 000475 0x80BD821C */ .word	0x00000000
