.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Dblue_Waterfall_InitVars
/* 001460 0x80B85350 */ .word	0x021C0600
/* 001461 0x80B85354 */ .word	0x00000010
/* 001462 0x80B85358 */ .word	0x01840000
/* 001463 0x80B8535C */ .word	0x000001AC
/* 001464 0x80B85360 */ .word	BgDblueWaterfall_Init
/* 001465 0x80B85364 */ .word	BgDblueWaterfall_Destroy
/* 001466 0x80B85368 */ .word	BgDblueWaterfall_Update
/* 001467 0x80B8536C */ .word	BgDblueWaterfall_Draw
glabel D_80B85370
/* 001468 0x80B85370 */ .word	0x0A000939
/* 001469 0x80B85374 */ .word	0x20010000
/* 001470 0x80B85378 */ .word	0x04000000
/* 001471 0x80B8537C */ .word	0x00000000
/* 001472 0x80B85380 */ .word	0x00000000
/* 001473 0x80B85384 */ .word	0x00CBFBB0
/* 001474 0x80B85388 */ .word	0x00000000
/* 001475 0x80B8538C */ .word	0x00010100
/* 001476 0x80B85390 */ .word	0x003202E4
/* 001477 0x80B85394 */ .word	0xFD1C0000
/* 001478 0x80B85398 */ .word	0x00000000
glabel D_80B8539C
/* 001479 0x80B8539C */ .word	0xC8FFFFFF
glabel D_80B853A0
/* 001480 0x80B853A0 */ .word	0xC8C8C800
glabel D_80B853A4
/* 001481 0x80B853A4 */ .word	0x00000000
glabel D_80B853A8
/* 001482 0x80B853A8 */ .word	0xB0FC0FA0
/* 001483 0x80B853AC */ .word	0xB10005DC
/* 001484 0x80B853B0 */ .word	0xB10405DC
/* 001485 0x80B853B4 */ .word	0x48580064
/* 001486 0x80B853B8 */ .word	0x00000000
/* 001487 0x80B853BC */ .word	0x00000000
