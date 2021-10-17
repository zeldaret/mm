.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Lupygamelift_InitVars
/* 000364 0x80AF0720 */ .word	0x01CD0100
/* 000365 0x80AF0724 */ .word	0x00000030
/* 000366 0x80AF0728 */ .word	0x01630000
/* 000367 0x80AF072C */ .word	0x00000174
/* 000368 0x80AF0730 */ .word	ObjLupygamelift_Init
/* 000369 0x80AF0734 */ .word	ObjLupygamelift_Destroy
/* 000370 0x80AF0738 */ .word	ObjLupygamelift_Update
/* 000371 0x80AF073C */ .word	ObjLupygamelift_Draw
glabel D_80AF0740
/* 000372 0x80AF0740 */ .word	0xB0FC0FA0
/* 000373 0x80AF0744 */ .word	0xB10000C8
/* 000374 0x80AF0748 */ .word	0xB1040190
/* 000375 0x80AF074C */ .word	0x48580064
glabel D_80AF0750
/* 000376 0x80AF0750 */ .word	0x42C80000
glabel D_80AF0754
/* 000377 0x80AF0754 */ .word	0x437F0000
glabel D_80AF0758
/* 000378 0x80AF0758 */ .word	0x40A00000
glabel D_80AF075C
/* 000379 0x80AF075C */ .word	0x41200000
glabel D_80AF0760
/* 000380 0x80AF0760 */ .word	0xC3700000
glabel D_80AF0764
/* 000381 0x80AF0764 */ .word	0x41F00000
/* 000382 0x80AF0768 */ .word	0x00000000
/* 000383 0x80AF076C */ .word	0x00000000
