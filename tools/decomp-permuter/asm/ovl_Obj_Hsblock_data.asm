.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Hsblock_InitVars
/* 000284 0x8093E310 */ .word	0x00960100
/* 000285 0x8093E314 */ .word	0x00000000
/* 000286 0x8093E318 */ .word	0x00EC0000
/* 000287 0x8093E31C */ .word	0x00000160
/* 000288 0x8093E320 */ .word	ObjHsblock_Init
/* 000289 0x8093E324 */ .word	ObjHsblock_Destroy
/* 000290 0x8093E328 */ .word	ObjHsblock_Update
/* 000291 0x8093E32C */ .word	ObjHsblock_Draw
glabel D_8093E330
/* 000292 0x8093E330 */ .word	0x42AA0000
/* 000293 0x8093E334 */ .word	0x42AA0000
/* 000294 0x8093E338 */ .word	0x00000000
glabel D_8093E33C
/* 000295 0x8093E33C */ .word	0xC8580064
/* 000296 0x8093E340 */ .word	0xB0FC0FA0
/* 000297 0x8093E344 */ .word	0xB1000064
/* 000298 0x8093E348 */ .word	0x310400C8
glabel D_8093E34C
/* 000299 0x8093E34C */ .word	0x06000730
/* 000300 0x8093E350 */ .word	0x06000730
/* 000301 0x8093E354 */ .word	0x06000578
glabel D_8093E358
/* 000302 0x8093E358 */ .word	0x06000210
/* 000303 0x8093E35C */ .word	0x06000210
/* 000304 0x8093E360 */ .word	0x06000470
glabel D_8093E364
/* 000305 0x8093E364 */ .word	0x3C3C7878
/* 000306 0x8093E368 */ .word	0x64466496
/* 000307 0x8093E36C */ .word	0x78FFFFFF
