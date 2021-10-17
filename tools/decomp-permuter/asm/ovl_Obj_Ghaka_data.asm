.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Ghaka_InitVars
/* 000440 0x80B3C940 */ .word	0x01FB0600
/* 000441 0x80B3C944 */ .word	0x00000029
/* 000442 0x80B3C948 */ .word	0x01D20000
/* 000443 0x80B3C94C */ .word	0x0000016C
/* 000444 0x80B3C950 */ .word	ObjGhaka_Init
/* 000445 0x80B3C954 */ .word	ObjGhaka_Destroy
/* 000446 0x80B3C958 */ .word	ObjGhaka_Update
/* 000447 0x80B3C95C */ .word	ObjGhaka_Draw
glabel D_80B3C960
/* 000448 0x80B3C960 */ .word	0x00000000
/* 000449 0x80B3C964 */ .word	0x00000000
/* 000450 0x80B3C968 */ .word	0x00000000
glabel D_80B3C96C
/* 000451 0x80B3C96C */ .word	0x801F0000
/* 000452 0x80B3C970 */ .word	0x3054001E
/* 000453 0x80B3C974 */ .word	0x00000000
/* 000454 0x80B3C978 */ .word	0x00000000
/* 000455 0x80B3C97C */ .word	0x00000000
