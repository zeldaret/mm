.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Dnb_InitVars
/* 000944 0x80A50C90 */ .word	0x01670100
/* 000945 0x80A50C94 */ .word	0x000000B0
/* 000946 0x80A50C98 */ .word	0x01890000
/* 000947 0x80A50C9C */ .word	0x00003538
/* 000948 0x80A50CA0 */ .word	EnDnb_Init
/* 000949 0x80A50CA4 */ .word	EnDnb_Destroy
/* 000950 0x80A50CA8 */ .word	EnDnb_Update
/* 000951 0x80A50CAC */ .word	EnDnb_Draw
glabel D_80A50CB0
/* 000952 0x80A50CB0 */ .word	0x00000000
/* 000953 0x80A50CB4 */ .word	0x00000000
/* 000954 0x80A50CB8 */ .word	0x447A0000
glabel D_80A50CBC
/* 000955 0x80A50CBC */ .word	0x0408F7E0
/* 000956 0x80A50CC0 */ .word	0x0408F3E0
/* 000957 0x80A50CC4 */ .word	0x0408EFE0
/* 000958 0x80A50CC8 */ .word	0x0408EBE0
/* 000959 0x80A50CCC */ .word	0x0408E7E0
/* 000960 0x80A50CD0 */ .word	0x0408E3E0
/* 000961 0x80A50CD4 */ .word	0x0408DFE0
/* 000962 0x80A50CD8 */ .word	0x0408DBE0
/* 000963 0x80A50CDC */ .word	0x00000000
