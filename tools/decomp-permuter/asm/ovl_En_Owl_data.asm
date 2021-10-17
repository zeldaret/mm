.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Owl_InitVars
/* 002928 0x8095D2D0 */ .word	0x00AF0400
/* 002929 0x8095D2D4 */ .word	0x00000019
/* 002930 0x8095D2D8 */ .word	0x00FD0000
/* 002931 0x8095D2DC */ .word	0x00000418
/* 002932 0x8095D2E0 */ .word	EnOwl_Init
/* 002933 0x8095D2E4 */ .word	EnOwl_Destroy
/* 002934 0x8095D2E8 */ .word	EnOwl_Update
/* 002935 0x8095D2EC */ .word	EnOwl_Draw
glabel D_8095D2F0
/* 002936 0x8095D2F0 */ .word	0x0A001139
/* 002937 0x8095D2F4 */ .word	0x10010000
/* 002938 0x8095D2F8 */ .word	0x00000000
/* 002939 0x8095D2FC */ .word	0x00000000
/* 002940 0x8095D300 */ .word	0x00000000
/* 002941 0x8095D304 */ .word	0xF7CFFFFF
/* 002942 0x8095D308 */ .word	0x00000000
/* 002943 0x8095D30C */ .word	0x00010100
/* 002944 0x8095D310 */ .word	0x001E0028
/* 002945 0x8095D314 */ .word	0x00000000
/* 002946 0x8095D318 */ .word	0x00000000
glabel D_8095D31C
/* 002947 0x8095D31C */ .word	0xC8580019
/* 002948 0x8095D320 */ .word	0xB0FC0578
/* 002949 0x8095D324 */ .word	0xB10007D0
/* 002950 0x8095D328 */ .word	0x31040960
glabel D_8095D32C
/* 002951 0x8095D32C */ .word	0x06008EB8
/* 002952 0x8095D330 */ .word	0x060092B8
/* 002953 0x8095D334 */ .word	0x060096B8
/* 002954 0x8095D338 */ .word	0x00000000
/* 002955 0x8095D33C */ .word	0x00000000
