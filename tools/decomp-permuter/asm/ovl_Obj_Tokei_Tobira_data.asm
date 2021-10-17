.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Tokei_Tobira_InitVars
/* 000344 0x80ABD730 */ .word	0x01A20100
/* 000345 0x80ABD734 */ .word	0x00000000
/* 000346 0x80ABD738 */ .word	0x01970000
/* 000347 0x80ABD73C */ .word	0x00000170
/* 000348 0x80ABD740 */ .word	ObjTokeiTobira_Init
/* 000349 0x80ABD744 */ .word	ObjTokeiTobira_Destroy
/* 000350 0x80ABD748 */ .word	ObjTokeiTobira_Update
/* 000351 0x80ABD74C */ .word	ObjTokeiTobira_Draw
glabel D_80ABD750
/* 000352 0x80ABD750 */ .word	0xB0FC0FA0
/* 000353 0x80ABD754 */ .word	0xB100012C
/* 000354 0x80ABD758 */ .word	0xB104012C
/* 000355 0x80ABD75C */ .word	0x48580064
glabel D_80ABD760
/* 000356 0x80ABD760 */ .word	0x00000000
/* 000357 0x80ABD764 */ .word	0x00000000
/* 000358 0x80ABD768 */ .word	0x42A00000
glabel D_80ABD76C
/* 000359 0x80ABD76C */ .word	0xC0004000
glabel D_80ABD770
/* 000360 0x80ABD770 */ .word	0x060012B0
/* 000361 0x80ABD774 */ .word	0x06001590
glabel D_80ABD778
/* 000362 0x80ABD778 */ .word	0x3F800000
/* 000363 0x80ABD77C */ .word	0xBF800000
glabel D_80ABD780
/* 000364 0x80ABD780 */ .word	0x06001108
/* 000365 0x80ABD784 */ .word	0x060013E8
/* 000366 0x80ABD788 */ .word	0x00000000
/* 000367 0x80ABD78C */ .word	0x00000000
