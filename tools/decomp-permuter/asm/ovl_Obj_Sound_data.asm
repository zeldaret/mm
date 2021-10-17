.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Sound_InitVars
/* 000112 0x8099AAE0 */ .word	0x00F00700
/* 000113 0x8099AAE4 */ .word	0x00000030
/* 000114 0x8099AAE8 */ .word	0x00010000
/* 000115 0x8099AAEC */ .word	0x00000148
/* 000116 0x8099AAF0 */ .word	ObjSound_Init
/* 000117 0x8099AAF4 */ .word	ObjSound_Destroy
/* 000118 0x8099AAF8 */ .word	ObjSound_Update
/* 000119 0x8099AAFC */ .word	0x00000000
