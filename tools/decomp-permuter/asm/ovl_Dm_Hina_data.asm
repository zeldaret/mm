.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Hina_InitVars
/* 000616 0x80A1FDB0 */ .word	0x01400700
/* 000617 0x80A1FDB4 */ .word	0x00000030
/* 000618 0x80A1FDB8 */ .word	0x01CC0000
/* 000619 0x80A1FDBC */ .word	0x00000184
/* 000620 0x80A1FDC0 */ .word	DmHina_Init
/* 000621 0x80A1FDC4 */ .word	DmHina_Destroy
/* 000622 0x80A1FDC8 */ .word	DmHina_Update
/* 000623 0x80A1FDCC */ .word	DmHina_Draw
