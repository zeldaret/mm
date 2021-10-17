.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Haka_Tomb_InitVars
/* 000192 0x80BD6880 */ .word	0x02590100
/* 000193 0x80BD6884 */ .word	0x00000000
/* 000194 0x80BD6888 */ .word	0x01E00000
/* 000195 0x80BD688C */ .word	0x00000164
/* 000196 0x80BD6890 */ .word	BgHakaTomb_Init
/* 000197 0x80BD6894 */ .word	BgHakaTomb_Destroy
/* 000198 0x80BD6898 */ .word	BgHakaTomb_Update
/* 000199 0x80BD689C */ .word	BgHakaTomb_Draw
glabel D_80BD68A0
/* 000200 0x80BD68A0 */ .word	0x48580064
glabel D_80BD68A4
/* 000201 0x80BD68A4 */ .word	0x41F00000
/* 000202 0x80BD68A8 */ .word	0x42B40000
/* 000203 0x80BD68AC */ .word	0x00000000
