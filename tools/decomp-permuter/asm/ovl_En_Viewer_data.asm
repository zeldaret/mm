.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8089F3E0
/* 000368 0x8089F3E0 */ .word	0x00000000
glabel D_8089F3E4
/* 000369 0x8089F3E4 */ .word	0x00000000
glabel En_Viewer_InitVars
/* 000370 0x8089F3E8 */ .word	0x001C0700
/* 000371 0x8089F3EC */ .word	0x00200030
/* 000372 0x8089F3F0 */ .word	0x00010000
/* 000373 0x8089F3F4 */ .word	0x00000158
/* 000374 0x8089F3F8 */ .word	EnViewer_Init
/* 000375 0x8089F3FC */ .word	EnViewer_Destroy
/* 000376 0x8089F400 */ .word	EnViewer_Update
/* 000377 0x8089F404 */ .word	EnViewer_Draw
/* 000378 0x8089F408 */ .word	0x00000000
/* 000379 0x8089F40C */ .word	0x00000000
