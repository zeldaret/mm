.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_808D03C0
/* 002012 0x808D03C0 */ .word	0x00000000
glabel D_808D03C4
/* 002013 0x808D03C4 */ .word	0x00000000
glabel Demo_Kankyo_InitVars
/* 002014 0x808D03C8 */ .word	0x00490700
/* 002015 0x808D03CC */ .word	0x00000030
/* 002016 0x808D03D0 */ .word	0x00010000
/* 002017 0x808D03D4 */ .word	0x00001650
/* 002018 0x808D03D8 */ .word	DemoKankyo_Init
/* 002019 0x808D03DC */ .word	DemoKankyo_Destroy
/* 002020 0x808D03E0 */ .word	DemoKankyo_Update
/* 002021 0x808D03E4 */ .word	DemoKankyo_Draw
/* 002022 0x808D03E8 */ .short	0x0001
glabel D_808D03EA
/* 002022 0x808D03E8 */ .short	0x000E
/* 002023 0x808D03EC */ .word	0x00000000
