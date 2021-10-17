.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Haka_Curtain_InitVars
/* 000232 0x80B6DF80 */ .word	0x020D0100
/* 000233 0x80B6DF84 */ .word	0x00000010
/* 000234 0x80B6DF88 */ .word	0x01E00000
/* 000235 0x80B6DF8C */ .word	0x00000160
/* 000236 0x80B6DF90 */ .word	BgHakaCurtain_Init
/* 000237 0x80B6DF94 */ .word	BgHakaCurtain_Destroy
/* 000238 0x80B6DF98 */ .word	BgHakaCurtain_Update
/* 000239 0x80B6DF9C */ .word	BgHakaCurtain_Draw
glabel D_80B6DFA0
/* 000240 0x80B6DFA0 */ .word	0xB0FC0FA0
/* 000241 0x80B6DFA4 */ .word	0xB10002BC
/* 000242 0x80B6DFA8 */ .word	0xB1040258
/* 000243 0x80B6DFAC */ .word	0x48580064
