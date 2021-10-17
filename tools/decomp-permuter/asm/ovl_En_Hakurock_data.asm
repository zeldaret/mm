.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Hakurock_InitVars
/* 000984 0x80B22A60 */ .word	0x01EA0700
/* 000985 0x80B22A64 */ .word	0x00000030
/* 000986 0x80B22A68 */ .word	0x01BB0000
/* 000987 0x80B22A6C */ .word	0x00000198
/* 000988 0x80B22A70 */ .word	EnHakurock_Init
/* 000989 0x80B22A74 */ .word	EnHakurock_Destroy
/* 000990 0x80B22A78 */ .word	EnHakurock_Update
/* 000991 0x80B22A7C */ .word	0x00000000
glabel D_80B22A80
/* 000992 0x80B22A80 */ .word	0x0C110D3D
/* 000993 0x80B22A84 */ .word	0x10010000
/* 000994 0x80B22A88 */ .word	0x00000000
/* 000995 0x80B22A8C */ .word	0x20000000
/* 000996 0x80B22A90 */ .word	0x00000000
/* 000997 0x80B22A94 */ .word	0xF3CFBBFF
/* 000998 0x80B22A98 */ .word	0x00000000
/* 000999 0x80B22A9C */ .word	0x09010100
/* 001000 0x80B22AA0 */ .word	0x003C003C
/* 001001 0x80B22AA4 */ .word	0xFFE20000
/* 001002 0x80B22AA8 */ .word	0x00000000
glabel D_80B22AAC
/* 001003 0x80B22AAC */ .word	0x0000003C
/* 001004 0x80B22AB0 */ .word	0x003CFF00
/* 001005 0x80B22AB4 */ .word	0x00000000
/* 001006 0x80B22AB8 */ .word	0x00000000
/* 001007 0x80B22ABC */ .word	0x00000000
