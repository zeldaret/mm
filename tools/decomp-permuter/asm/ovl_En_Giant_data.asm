.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Giant_InitVars
/* 001000 0x80B02930 */ .word	0x01DB0400
/* 001001 0x80B02934 */ .word	0x00000030
/* 001002 0x80B02938 */ .word	0x01B80000
/* 001003 0x80B0293C */ .word	0x0000029C
/* 001004 0x80B02940 */ .word	EnGiant_Init
/* 001005 0x80B02944 */ .word	EnGiant_Destroy
/* 001006 0x80B02948 */ .word	EnGiant_Update
/* 001007 0x80B0294C */ .word	EnGiant_Draw
glabel D_80B02950
/* 001008 0x80B02950 */ .word	0x06008394
/* 001009 0x80B02954 */ .word	0x060096E4
/* 001010 0x80B02958 */ .word	0x060102A4
/* 001011 0x80B0295C */ .word	0x060116E4
/* 001012 0x80B02960 */ .word	0x06012A38
/* 001013 0x80B02964 */ .word	0x06013004
/* 001014 0x80B02968 */ .word	0x06013FE8
/* 001015 0x80B0296C */ .word	0x06015334
/* 001016 0x80B02970 */ .word	0x06017944
/* 001017 0x80B02974 */ .word	0x0600A1C4
/* 001018 0x80B02978 */ .word	0x0600D040
/* 001019 0x80B0297C */ .word	0x0600DE84
/* 001020 0x80B02980 */ .word	0x0600ACA4
/* 001021 0x80B02984 */ .word	0x0600B784
/* 001022 0x80B02988 */ .word	0x0600C5D4
glabel D_80B0298C
/* 001023 0x80B0298C */ .word	0x06005A80
/* 001024 0x80B02990 */ .word	0x06006280
/* 001025 0x80B02994 */ .word	0x06006A80
/* 001026 0x80B02998 */ .word	0x00000000
/* 001027 0x80B0299C */ .word	0x00000000
