.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Item_Inbox_InitVars
/* 000068 0x80945600 */ .word	0x009E0400
/* 000069 0x80945604 */ .word	0x00000009
/* 000070 0x80945608 */ .word	0x00010000
/* 000071 0x8094560C */ .word	0x00000148
/* 000072 0x80945610 */ .word	ItemInbox_Init
/* 000073 0x80945614 */ .word	ItemInbox_Destroy
/* 000074 0x80945618 */ .word	ItemInbox_Update
/* 000075 0x8094561C */ .word	ItemInbox_Draw
