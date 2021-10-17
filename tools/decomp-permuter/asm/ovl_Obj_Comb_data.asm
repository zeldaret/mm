.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Comb_InitVars
/* 001400 0x8098E420 */ .word	0x00E40600
/* 001401 0x8098E424 */ .word	0x00000000
/* 001402 0x8098E428 */ .word	0x01B90000
/* 001403 0x8098E42C */ .word	0x000001BC
/* 001404 0x8098E430 */ .word	ObjComb_Init
/* 001405 0x8098E434 */ .word	ObjComb_Destroy
/* 001406 0x8098E438 */ .word	ObjComb_Update
/* 001407 0x8098E43C */ .word	ObjComb_Draw
glabel D_8098E440
/* 001408 0x8098E440 */ .word	0x00000000
/* 001409 0x8098E444 */ .word	0x00000000
/* 001410 0x8098E448 */ .word	0x00000000
/* 001411 0x8098E44C */ .word	0x05CBFFBE
/* 001412 0x8098E450 */ .word	0x00000000
/* 001413 0x8098E454 */ .word	0x00010100
/* 001414 0x8098E458 */ .word	0x00000000
/* 001415 0x8098E45C */ .word	0x00000000
/* 001416 0x8098E460 */ .word	0x000F0064
glabel D_8098E464
/* 001417 0x8098E464 */ .word	0x0A000909
/* 001418 0x8098E468 */ .word	0x20000000
/* 001419 0x8098E46C */ .word	0x00000001
/* 001420 0x8098E470 */ .word	D_8098E440
glabel D_8098E474
/* 001421 0x8098E474 */ .word	0xC8580064
/* 001422 0x8098E478 */ .word	0xB0FC04B0
/* 001423 0x8098E47C */ .word	0xB1000064
/* 001424 0x8098E480 */ .word	0x31040064
/* 001425 0x8098E484 */ .word	0x00000000
/* 001426 0x8098E488 */ .word	0x00000000
/* 001427 0x8098E48C */ .word	0x00000000
