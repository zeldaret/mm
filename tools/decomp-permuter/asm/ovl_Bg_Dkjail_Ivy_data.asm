.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Dkjail_Ivy_InitVars
/* 000448 0x80ADE930 */ .word	0x01BE0100
/* 000449 0x80ADE934 */ .word	0x00000000
/* 000450 0x80ADE938 */ .word	0x01A70000
/* 000451 0x80ADE93C */ .word	0x000001B0
/* 000452 0x80ADE940 */ .word	BgDkjailIvy_Init
/* 000453 0x80ADE944 */ .word	BgDkjailIvy_Destroy
/* 000454 0x80ADE948 */ .word	BgDkjailIvy_Update
/* 000455 0x80ADE94C */ .word	BgDkjailIvy_Draw
glabel D_80ADE950
/* 000456 0x80ADE950 */ .word	0x0A000900
/* 000457 0x80ADE954 */ .word	0x00010000
/* 000458 0x80ADE958 */ .word	0x00000000
/* 000459 0x80ADE95C */ .word	0x00000000
/* 000460 0x80ADE960 */ .word	0x00000000
/* 000461 0x80ADE964 */ .word	0x01000200
/* 000462 0x80ADE968 */ .word	0x00000000
/* 000463 0x80ADE96C */ .word	0x00010000
/* 000464 0x80ADE970 */ .word	0x00140050
/* 000465 0x80ADE974 */ .word	0x00000000
/* 000466 0x80ADE978 */ .word	0x00000000
glabel D_80ADE97C
/* 000467 0x80ADE97C */ .word	0x040527F0
/* 000468 0x80ADE980 */ .word	0x040528B0
glabel D_80ADE984
/* 000469 0x80ADE984 */ .word	0x006E0050
/* 000470 0x80ADE988 */ .word	0x003C0028
glabel D_80ADE98C
/* 000471 0x80ADE98C */ .word	0xB0FC0FA0
/* 000472 0x80ADE990 */ .word	0xB10000C8
/* 000473 0x80ADE994 */ .word	0xB10400C8
/* 000474 0x80ADE998 */ .word	0x48580064
/* 000475 0x80ADE99C */ .word	0x00000000
