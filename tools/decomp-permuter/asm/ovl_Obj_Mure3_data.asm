.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Mure3_InitVars
/* 000440 0x8098F720 */ .word	0x00E80100
/* 000441 0x8098F724 */ .word	0x00000000
/* 000442 0x8098F728 */ .word	0x00010000
/* 000443 0x8098F72C */ .word	0x00000168
/* 000444 0x8098F730 */ .word	ObjMure3_Init
/* 000445 0x8098F734 */ .word	ObjMure3_Destroy
/* 000446 0x8098F738 */ .word	ObjMure3_Update
/* 000447 0x8098F73C */ .word	0x00000000
glabel D_8098F740
/* 000448 0x8098F740 */ .word	0x00050005
/* 000449 0x8098F744 */ .word	0x00070000
glabel D_8098F748
/* 000450 0x8098F748 */ .word	0xB0FC0064
/* 000451 0x8098F74C */ .word	0xB1000708
/* 000452 0x8098F750 */ .word	0x31040064
glabel D_8098F754
/* 000453 0x8098F754 */ .word	func_8098F040
/* 000454 0x8098F758 */ .word	func_8098F110
/* 000455 0x8098F75C */ .word	func_8098F220
