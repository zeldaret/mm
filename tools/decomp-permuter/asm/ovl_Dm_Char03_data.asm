.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Char03_InitVars
/* 000432 0x80AABB60 */ .word	0x01950700
/* 000433 0x80AABB64 */ .word	0x00000030
/* 000434 0x80AABB68 */ .word	0x01A30000
/* 000435 0x80AABB6C */ .word	0x0000019C
/* 000436 0x80AABB70 */ .word	DmChar03_Init
/* 000437 0x80AABB74 */ .word	DmChar03_Destroy
/* 000438 0x80AABB78 */ .word	DmChar03_Update
/* 000439 0x80AABB7C */ .word	DmChar03_Draw
glabel D_80AABB80
/* 000440 0x80AABB80 */ .word	0x06020530
/* 000441 0x80AABB84 */ .word	0x3F800000
/* 000442 0x80AABB88 */ .word	0x00000000
/* 000443 0x80AABB8C */ .word	0xBF800000
/* 000444 0x80AABB90 */ .word	0x02000000
/* 000445 0x80AABB94 */ .word	0x00000000
/* 000446 0x80AABB98 */ .word	0x00000000
/* 000447 0x80AABB9C */ .word	0x00000000
