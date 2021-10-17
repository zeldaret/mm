.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Lightblock_InitVars
/* 000348 0x80AF3E80 */ .word	0x01CF0100
/* 000349 0x80AF3E84 */ .word	0x00000000
/* 000350 0x80AF3E88 */ .word	0x01B30000
/* 000351 0x80AF3E8C */ .word	0x000001B0
/* 000352 0x80AF3E90 */ .word	ObjLightblock_Init
/* 000353 0x80AF3E94 */ .word	ObjLightblock_Destroy
/* 000354 0x80AF3E98 */ .word	ObjLightblock_Update
/* 000355 0x80AF3E9C */ .word	ObjLightblock_Draw
glabel D_80AF3EA0
/* 000356 0x80AF3EA0 */ .word	0x0A002900
/* 000357 0x80AF3EA4 */ .word	0x00010000
/* 000358 0x80AF3EA8 */ .word	0x00000000
/* 000359 0x80AF3EAC */ .word	0x00000000
/* 000360 0x80AF3EB0 */ .word	0x00000000
/* 000361 0x80AF3EB4 */ .word	0x00202000
/* 000362 0x80AF3EB8 */ .word	0x00000000
/* 000363 0x80AF3EBC */ .word	0x00010000
/* 000364 0x80AF3EC0 */ .word	0x00540078
/* 000365 0x80AF3EC4 */ .word	0x00000000
/* 000366 0x80AF3EC8 */ .word	0x00000000
glabel D_80AF3ECC
/* 000367 0x80AF3ECC */ .word	0x3DCCCCCD
/* 000368 0x80AF3ED0 */ .word	0x004C0050
/* 000369 0x80AF3ED4 */ .word	0x00130000
/* 000370 0x80AF3ED8 */ .word	0x00000002
/* 000371 0x80AF3EDC */ .word	0x3E2AAAAB
/* 000372 0x80AF3EE0 */ .word	0x007E0090
/* 000373 0x80AF3EE4 */ .word	0x00130000
/* 000374 0x80AF3EE8 */ .word	0x00000003
glabel D_80AF3EEC
/* 000375 0x80AF3EEC */ .word	0xB0FC0FA0
/* 000376 0x80AF3EF0 */ .word	0xB10001F4
/* 000377 0x80AF3EF4 */ .word	0x310401F4
/* 000378 0x80AF3EF8 */ .word	0x00000000
/* 000379 0x80AF3EFC */ .word	0x00000000
