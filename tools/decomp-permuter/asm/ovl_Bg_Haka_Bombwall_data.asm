.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Haka_Bombwall_InitVars
/* 000416 0x80BD6480 */ .word	0x02580100
/* 000417 0x80BD6484 */ .word	0x00000000
/* 000418 0x80BD6488 */ .word	0x01E00000
/* 000419 0x80BD648C */ .word	0x000001B0
/* 000420 0x80BD6490 */ .word	BgHakaBombwall_Init
/* 000421 0x80BD6494 */ .word	BgHakaBombwall_Destroy
/* 000422 0x80BD6498 */ .word	BgHakaBombwall_Update
/* 000423 0x80BD649C */ .word	BgHakaBombwall_Draw
glabel D_80BD64A0
/* 000424 0x80BD64A0 */ .word	0x0A000900
/* 000425 0x80BD64A4 */ .word	0x00010000
/* 000426 0x80BD64A8 */ .word	0x00000000
/* 000427 0x80BD64AC */ .word	0x00000000
/* 000428 0x80BD64B0 */ .word	0x00000000
/* 000429 0x80BD64B4 */ .word	0x00000008
/* 000430 0x80BD64B8 */ .word	0x00000000
/* 000431 0x80BD64BC */ .word	0x00010000
/* 000432 0x80BD64C0 */ .word	0x00500050
/* 000433 0x80BD64C4 */ .word	0x00000000
/* 000434 0x80BD64C8 */ .word	0x00000000
glabel D_80BD64CC
/* 000435 0x80BD64CC */ .word	0x0018000F
/* 000436 0x80BD64D0 */ .word	0x000A0005
glabel D_80BD64D4
/* 000437 0x80BD64D4 */ .word	0xB0FC0FA0
/* 000438 0x80BD64D8 */ .word	0xB10001F4
/* 000439 0x80BD64DC */ .word	0xB10401F4
/* 000440 0x80BD64E0 */ .word	0x48580064
/* 000441 0x80BD64E4 */ .word	0x00000000
/* 000442 0x80BD64E8 */ .word	0x00000000
/* 000443 0x80BD64EC */ .word	0x00000000
