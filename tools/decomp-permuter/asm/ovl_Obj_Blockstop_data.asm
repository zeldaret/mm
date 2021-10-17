.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Blockstop_InitVars
/* 000120 0x80946880 */ .word	0x00A00600
/* 000121 0x80946884 */ .word	0x00000010
/* 000122 0x80946888 */ .word	0x00010000
/* 000123 0x8094688C */ .word	0x00000148
/* 000124 0x80946890 */ .word	ObjBlockstop_Init
/* 000125 0x80946894 */ .word	func_800BDFB0
/* 000126 0x80946898 */ .word	ObjBlockstop_Update
/* 000127 0x8094689C */ .word	0x00000000
