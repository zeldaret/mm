.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Chikuwa_InitVars
/* 000660 0x809B1FA0 */ .word	0x01140100
/* 000661 0x809B1FA4 */ .word	0x00000010
/* 000662 0x809B1FA8 */ .word	0x00ED0000
/* 000663 0x809B1FAC */ .word	0x000009A8
/* 000664 0x809B1FB0 */ .word	ObjChikuwa_Init
/* 000665 0x809B1FB4 */ .word	ObjChikuwa_Destroy
/* 000666 0x809B1FB8 */ .word	ObjChikuwa_Update
/* 000667 0x809B1FBC */ .word	ObjChikuwa_Draw
glabel D_809B1FC0
/* 000668 0x809B1FC0 */ .word	0xB0FC0FA0
/* 000669 0x809B1FC4 */ .word	0xB10005DC
/* 000670 0x809B1FC8 */ .word	0xB10405DC
/* 000671 0x809B1FCC */ .word	0x48580064
glabel D_809B1FD0
/* 000672 0x809B1FD0 */ .word	0x00000000
/* 000673 0x809B1FD4 */ .word	0xBE99999A
/* 000674 0x809B1FD8 */ .word	0x00000000
glabel D_809B1FDC
/* 000675 0x809B1FDC */ .word	0x00000000
/* 000676 0x809B1FE0 */ .word	0x3F333333
/* 000677 0x809B1FE4 */ .word	0x00000000
/* 000678 0x809B1FE8 */ .word	0x00000000
/* 000679 0x809B1FEC */ .word	0x00000000
