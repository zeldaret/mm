.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Iknv_Doukutu_InitVars
/* 000684 0x80BD79C0 */ .word	0x025B0100
/* 000685 0x80BD79C4 */ .word	0x00000030
/* 000686 0x80BD79C8 */ .word	0x02370000
/* 000687 0x80BD79CC */ .word	0x00000168
/* 000688 0x80BD79D0 */ .word	BgIknvDoukutu_Init
/* 000689 0x80BD79D4 */ .word	BgIknvDoukutu_Destroy
/* 000690 0x80BD79D8 */ .word	BgIknvDoukutu_Update
/* 000691 0x80BD79DC */ .word	BgIknvDoukutu_Draw
