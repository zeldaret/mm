.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Demo_Shd_InitVars
/* 000016 0x8092C570 */ .word	0x00890500
/* 000017 0x8092C574 */ .word	0x00000030
/* 000018 0x8092C578 */ .word	0x01530000
/* 000019 0x8092C57C */ .word	0x000012D0
/* 000020 0x8092C580 */ .word	DemoShd_Init
/* 000021 0x8092C584 */ .word	DemoShd_Destroy
/* 000022 0x8092C588 */ .word	DemoShd_Update
/* 000023 0x8092C58C */ .word	DemoShd_Draw
