.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Estone_InitVars
/* 000812 0x80A9AB50 */ .word	0x018E0600
/* 000813 0x80A9AB54 */ .word	0x00000030
/* 000814 0x80A9AB58 */ .word	0x018D0000
/* 000815 0x80A9AB5C */ .word	0x00002D74
/* 000816 0x80A9AB60 */ .word	EnEstone_Init
/* 000817 0x80A9AB64 */ .word	EnEstone_Destroy
/* 000818 0x80A9AB68 */ .word	EnEstone_Update
/* 000819 0x80A9AB6C */ .word	EnEstone_Draw
glabel D_80A9AB70
/* 000820 0x80A9AB70 */ .word	0x0C110900
/* 000821 0x80A9AB74 */ .word	0x20010000
/* 000822 0x80A9AB78 */ .word	0x00000000
/* 000823 0x80A9AB7C */ .word	0xF7CFFFFF
/* 000824 0x80A9AB80 */ .word	0x00040000
/* 000825 0x80A9AB84 */ .word	0xF7CFFFFF
/* 000826 0x80A9AB88 */ .word	0x00000000
/* 000827 0x80A9AB8C */ .word	0x01010000
/* 000828 0x80A9AB90 */ .word	0x001E001E
/* 000829 0x80A9AB94 */ .word	0xFFF60000
/* 000830 0x80A9AB98 */ .word	0x00000000
/* 000831 0x80A9AB9C */ .word	0x00000000
