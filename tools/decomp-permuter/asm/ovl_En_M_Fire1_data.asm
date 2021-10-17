.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_M_Fire1_InitVars
/* 000068 0x808B5340 */ .word	0x00340800
/* 000069 0x808B5344 */ .word	0x00000000
/* 000070 0x808B5348 */ .word	0x00010000
/* 000071 0x808B534C */ .word	0x00000194
/* 000072 0x808B5350 */ .word	EnMFire1_Init
/* 000073 0x808B5354 */ .word	EnMFire1_Destroy
/* 000074 0x808B5358 */ .word	EnMFire1_Update
/* 000075 0x808B535C */ .word	0x00000000
glabel D_808B5360
/* 000076 0x808B5360 */ .word	0x0A090000
/* 000077 0x808B5364 */ .word	0x08010000
/* 000078 0x808B5368 */ .word	0x02000000
/* 000079 0x808B536C */ .word	0x00000001
/* 000080 0x808B5370 */ .word	0x00010000
/* 000081 0x808B5374 */ .word	0xF7CFFFFF
/* 000082 0x808B5378 */ .word	0x00000000
/* 000083 0x808B537C */ .word	0x19000000
/* 000084 0x808B5380 */ .word	0x00640064
/* 000085 0x808B5384 */ .word	0x00000000
/* 000086 0x808B5388 */ .word	0x00000000
/* 000087 0x808B538C */ .word	0x00000000
