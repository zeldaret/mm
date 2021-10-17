.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Raillift_InitVars
/* 000672 0x80A1A390 */ .word	0x013C0100
/* 000673 0x80A1A394 */ .word	0x00000010
/* 000674 0x80A1A398 */ .word	0x01630000
/* 000675 0x80A1A39C */ .word	0x0000018C
/* 000676 0x80A1A3A0 */ .word	ObjRaillift_Init
/* 000677 0x80A1A3A4 */ .word	ObjRaillift_Destroy
/* 000678 0x80A1A3A8 */ .word	ObjRaillift_Update
/* 000679 0x80A1A3AC */ .word	ObjRaillift_Draw
glabel D_80A1A3B0
/* 000680 0x80A1A3B0 */ .word	0xB0FC0FA0
/* 000681 0x80A1A3B4 */ .word	0xB10000C8
/* 000682 0x80A1A3B8 */ .word	0xB1040190
/* 000683 0x80A1A3BC */ .word	0x48580064
glabel D_80A1A3C0
/* 000684 0x80A1A3C0 */ .word	0x06004FF8
glabel D_80A1A3C4
/* 000685 0x80A1A3C4 */ .word	0x060048D0
/* 000686 0x80A1A3C8 */ .word	0x00000000
/* 000687 0x80A1A3CC */ .word	0x00000000
