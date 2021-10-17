.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Torch2_InitVars
/* 000256 0x808A35B0 */ .word	0x00210700
/* 000257 0x808A35B4 */ .word	0x00000010
/* 000258 0x808A35B8 */ .word	0x00010000
/* 000259 0x808A35BC */ .word	0x00000194
/* 000260 0x808A35C0 */ .word	EnTorch2_Init
/* 000261 0x808A35C4 */ .word	EnTorch2_Destroy
/* 000262 0x808A35C8 */ .word	EnTorch2_Update
/* 000263 0x808A35CC */ .word	EnTorch2_Draw
glabel D_808A35D0
/* 000264 0x808A35D0 */ .word	0x09000D39
/* 000265 0x808A35D4 */ .word	0x20010000
/* 000266 0x808A35D8 */ .word	0x02000000
/* 000267 0x808A35DC */ .word	0x00100000
/* 000268 0x808A35E0 */ .word	0x00000000
/* 000269 0x808A35E4 */ .word	0xF7CFFFFF
/* 000270 0x808A35E8 */ .word	0x00000000
/* 000271 0x808A35EC */ .word	0x00050100
/* 000272 0x808A35F0 */ .word	0x0014003C
/* 000273 0x808A35F4 */ .word	0x00000000
/* 000274 0x808A35F8 */ .word	0x00000000
glabel D_808A35FC
/* 000275 0x808A35FC */ .word	0x08B600FF
glabel D_808A3600
/* 000276 0x808A3600 */ .word	0x0401C430
/* 000277 0x808A3604 */ .word	0x04048DF0
/* 000278 0x808A3608 */ .word	0x04089070
/* 000279 0x808A360C */ .word	0x04057B10
/* 000280 0x808A3610 */ .word	0x0401C430
/* 000281 0x808A3614 */ .word	0x00000000
/* 000282 0x808A3618 */ .word	0x00000000
/* 000283 0x808A361C */ .word	0x00000000
