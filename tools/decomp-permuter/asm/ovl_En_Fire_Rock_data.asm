.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Fire_Rock_InitVars
/* 000016 0x808E2020 */ .word	0x00600500
/* 000017 0x808E2024 */ .word	0x00000030
/* 000018 0x808E2028 */ .word	0x00700000
/* 000019 0x808E202C */ .word	0x000001D8
/* 000020 0x808E2030 */ .word	EnFireRock_Init
/* 000021 0x808E2034 */ .word	EnFireRock_Destroy
/* 000022 0x808E2038 */ .word	EnFireRock_Update
/* 000023 0x808E203C */ .word	EnFireRock_Draw
