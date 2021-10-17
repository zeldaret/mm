.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Spout_Fire_InitVars
/* 000392 0x80A61140 */ .word	0x01720100
/* 000393 0x80A61144 */ .word	0x00000000
/* 000394 0x80A61148 */ .word	0x01530000
/* 000395 0x80A6114C */ .word	0x00000198
/* 000396 0x80A61150 */ .word	BgSpoutFire_Init
/* 000397 0x80A61154 */ .word	BgSpoutFire_Destroy
/* 000398 0x80A61158 */ .word	BgSpoutFire_Update
/* 000399 0x80A6115C */ .word	0x00000000
glabel D_80A61160
/* 000400 0x80A61160 */ .word	0x0A110009
/* 000401 0x80A61164 */ .word	0x20010000
/* 000402 0x80A61168 */ .word	0x00000000
/* 000403 0x80A6116C */ .word	0x20000000
/* 000404 0x80A61170 */ .word	0x01040000
/* 000405 0x80A61174 */ .word	0xF7CFFFFF
/* 000406 0x80A61178 */ .word	0x00000000
/* 000407 0x80A6117C */ .word	0x19000100
/* 000408 0x80A61180 */ .word	0x001E0053
/* 000409 0x80A61184 */ .word	0x00000000
/* 000410 0x80A61188 */ .word	0x00000000
glabel D_80A6118C
/* 000411 0x80A6118C */ .word	0x01000050
/* 000412 0x80A61190 */ .word	0x0064FF00
glabel D_80A61194
/* 000413 0x80A61194 */ .word	0x06003CA0
/* 000414 0x80A61198 */ .word	0x060040A0
/* 000415 0x80A6119C */ .word	0x060044A0
/* 000416 0x80A611A0 */ .word	0x060048A0
/* 000417 0x80A611A4 */ .word	0x06004CA0
/* 000418 0x80A611A8 */ .word	0x060050A0
/* 000419 0x80A611AC */ .word	0x060054A0
/* 000420 0x80A611B0 */ .word	0x060058A0
glabel D_80A611B4
/* 000421 0x80A611B4 */ .word	0x00000000
/* 000422 0x80A611B8 */ .word	0x00000000
/* 000423 0x80A611BC */ .word	0x00000000
