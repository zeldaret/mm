.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Lightswitch_InitVars
/* 000992 0x80960B70 */ .word	0x00B20000
/* 000993 0x80960B74 */ .word	0x00000010
/* 000994 0x80960B78 */ .word	0x00F70000
/* 000995 0x80960B7C */ .word	0x000001C0
/* 000996 0x80960B80 */ .word	ObjLightswitch_Init
/* 000997 0x80960B84 */ .word	ObjLightswitch_Destroy
/* 000998 0x80960B88 */ .word	ObjLightswitch_Update
/* 000999 0x80960B8C */ .word	ObjLightswitch_Draw
glabel D_80960B90
/* 001000 0x80960B90 */ .word	0x00000000
/* 001001 0x80960B94 */ .word	0x00000000
/* 001002 0x80960B98 */ .word	0x00000000
/* 001003 0x80960B9C */ .word	0x00202000
/* 001004 0x80960BA0 */ .word	0x00000000
/* 001005 0x80960BA4 */ .word	0x00010100
/* 001006 0x80960BA8 */ .word	0x00000000
/* 001007 0x80960BAC */ .word	0x00000000
/* 001008 0x80960BB0 */ .word	0x00130064
glabel D_80960BB4
/* 001009 0x80960BB4 */ .word	0x0A002939
/* 001010 0x80960BB8 */ .word	0x20000000
/* 001011 0x80960BBC */ .word	0x00000001
/* 001012 0x80960BC0 */ .word	D_80960B90
glabel D_80960BC4
/* 001013 0x80960BC4 */ .word	0x06000C20
/* 001014 0x80960BC8 */ .word	0x06000420
/* 001015 0x80960BCC */ .word	0x06001420
glabel D_80960BD0
/* 001016 0x80960BD0 */ .word	0xFFFFA0A0
glabel D_80960BD4
/* 001017 0x80960BD4 */ .word	0xFF000000
glabel D_80960BD8
/* 001018 0x80960BD8 */ .word	0xC8580064
/* 001019 0x80960BDC */ .word	0xB0FC0FA0
/* 001020 0x80960BE0 */ .word	0xB10000C8
/* 001021 0x80960BE4 */ .word	0x310400C8
/* 001022 0x80960BE8 */ .word	0x00000000
/* 001023 0x80960BEC */ .word	0x00000000
