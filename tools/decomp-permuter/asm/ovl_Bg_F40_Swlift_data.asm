.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8096F510
/* 000236 0x8096F510 */ .word	0x000000FF
glabel D_8096F514
/* 000237 0x8096F514 */ .word	0x000000FF
/* 000238 0x8096F518 */ .word	0x000000FF
/* 000239 0x8096F51C */ .word	0x000000FF
glabel Bg_F40_Swlift_InitVars
/* 000240 0x8096F520 */ .word	0x00C70100
/* 000241 0x8096F524 */ .word	0x00000010
/* 000242 0x8096F528 */ .word	0x005C0000
/* 000243 0x8096F52C */ .word	0x00000160
/* 000244 0x8096F530 */ .word	BgF40Swlift_Init
/* 000245 0x8096F534 */ .word	BgF40Swlift_Destroy
/* 000246 0x8096F538 */ .word	BgF40Swlift_Update
/* 000247 0x8096F53C */ .word	BgF40Swlift_Draw
glabel D_8096F540
/* 000248 0x8096F540 */ .word	0xB1000226
/* 000249 0x8096F544 */ .word	0xB0FC1388
/* 000250 0x8096F548 */ .word	0x48580064
/* 000251 0x8096F54C */ .word	0x00000000
