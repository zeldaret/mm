.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Tokei_Step_InitVars
/* 000660 0x80AD6600 */ .word	0x01B80100
/* 000661 0x80AD6604 */ .word	0x00400010
/* 000662 0x80AD6608 */ .word	0x01A40000
/* 000663 0x80AD660C */ .word	0x000001EC
/* 000664 0x80AD6610 */ .word	ObjTokeiStep_Init
/* 000665 0x80AD6614 */ .word	ObjTokeiStep_Destroy
/* 000666 0x80AD6618 */ .word	ObjTokeiStep_Update
/* 000667 0x80AD661C */ .word	ObjTokeiStep_Draw
glabel D_80AD6620
/* 000668 0x80AD6620 */ .word	0xC2D20000
/* 000669 0x80AD6624 */ .word	0xC2B40000
/* 000670 0x80AD6628 */ .word	0xC2960000
/* 000671 0x80AD662C */ .word	0xC2700000
/* 000672 0x80AD6630 */ .word	0xC2340000
/* 000673 0x80AD6634 */ .word	0xC1F00000
/* 000674 0x80AD6638 */ .word	0xC1700000
glabel D_80AD663C
/* 000675 0x80AD663C */ .word	0xC2700000
/* 000676 0x80AD6640 */ .word	0xC2200000
/* 000677 0x80AD6644 */ .word	0xC1A00000
/* 000678 0x80AD6648 */ .word	0x00000000
/* 000679 0x80AD664C */ .word	0x41A00000
/* 000680 0x80AD6650 */ .word	0x42200000
/* 000681 0x80AD6654 */ .word	0x42700000
glabel D_80AD6658
/* 000682 0x80AD6658 */ .word	0x00000000
/* 000683 0x80AD665C */ .word	0x3E99999A
/* 000684 0x80AD6660 */ .word	0x00000000
glabel D_80AD6664
/* 000685 0x80AD6664 */ .word	0xB0FC0FA0
/* 000686 0x80AD6668 */ .word	0xB100012C
/* 000687 0x80AD666C */ .word	0xB104012C
/* 000688 0x80AD6670 */ .word	0x48580064
/* 000689 0x80AD6674 */ .word	0x00000000
/* 000690 0x80AD6678 */ .word	0x00000000
/* 000691 0x80AD667C */ .word	0x00000000
