.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Lbfshot_InitVars
/* 000048 0x80C181E0 */ .word	0x02970100
/* 000049 0x80C181E4 */ .word	0x00000000
/* 000050 0x80C181E8 */ .word	0x027F0000
/* 000051 0x80C181EC */ .word	0x00000160
/* 000052 0x80C181F0 */ .word	BgLbfshot_Init
/* 000053 0x80C181F4 */ .word	BgLbfshot_Destroy
/* 000054 0x80C181F8 */ .word	func_800BDFB0
/* 000055 0x80C181FC */ .word	BgLbfshot_Draw
glabel D_80C18200
/* 000056 0x80C18200 */ .word	0x48580064
/* 000057 0x80C18204 */ .word	0x00000000
/* 000058 0x80C18208 */ .word	0x00000000
/* 000059 0x80C1820C */ .word	0x00000000
