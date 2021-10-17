.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_809CA2B0
/* 000532 0x809CA2B0 */ .word	0x0A110900
/* 000533 0x809CA2B4 */ .word	0x20010000
/* 000534 0x809CA2B8 */ .word	0x00000000
/* 000535 0x809CA2BC */ .word	0xF7CFFFFF
/* 000536 0x809CA2C0 */ .word	0x00040000
/* 000537 0x809CA2C4 */ .word	0xF7CFFFFF
/* 000538 0x809CA2C8 */ .word	0x00000000
/* 000539 0x809CA2CC */ .word	0x01010000
/* 000540 0x809CA2D0 */ .word	0x000D0078
/* 000541 0x809CA2D4 */ .word	0x00000000
/* 000542 0x809CA2D8 */ .word	0x00000000
glabel Bg_Icicle_InitVars
/* 000543 0x809CA2DC */ .word	0x011F0600
/* 000544 0x809CA2E0 */ .word	0x00000000
/* 000545 0x809CA2E4 */ .word	0x01570000
/* 000546 0x809CA2E8 */ .word	0x000001B0
/* 000547 0x809CA2EC */ .word	BgIcicle_Init
/* 000548 0x809CA2F0 */ .word	BgIcicle_Destroy
/* 000549 0x809CA2F4 */ .word	BgIcicle_Update
/* 000550 0x809CA2F8 */ .word	BgIcicle_Draw
glabel D_809CA2FC
/* 000551 0x809CA2FC */ .word	0xB10005DC
/* 000552 0x809CA300 */ .word	0xB074FFFD
/* 000553 0x809CA304 */ .word	0xB078FFE2
/* 000554 0x809CA308 */ .word	0x48580064
glabel D_809CA30C
/* 000555 0x809CA30C */ .word	0x00000000
/* 000556 0x809CA310 */ .word	0xBF800000
/* 000557 0x809CA314 */ .word	0x00000000
glabel D_809CA318
/* 000558 0x809CA318 */ .word	0xAAFFFFFF
glabel D_809CA31C
/* 000559 0x809CA31C */ .word	0x003264FF
