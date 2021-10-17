.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801C5CB0
/* 295036 0x801C5CB0 */ .word	SkelAnime_LinkAnimetionLoaded
/* 295037 0x801C5CB4 */ .word	SkelAnime_AnimationType1Loaded
/* 295038 0x801C5CB8 */ .word	SkelAnime_AnimationType2Loaded
/* 295039 0x801C5CBC */ .word	SkelAnime_AnimationType3Loaded
/* 295040 0x801C5CC0 */ .word	SkelAnime_AnimationType4Loaded
/* 295041 0x801C5CC4 */ .word	SkelAnime_AnimationType5Loaded
/* 295042 0x801C5CC8 */ .word	0x00000000
/* 295043 0x801C5CCC */ .word	0x00000000
