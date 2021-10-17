.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_A_Obj_InitVars
/* 270568 0x801ADE60 */ .word	0x00260600
/* 270569 0x801ADE64 */ .word	0x00000009
/* 270570 0x801ADE68 */ .word	0x00010000
/* 270571 0x801ADE6C */ .word	0x00000194
/* 270572 0x801ADE70 */ .word	EnAObj_Init
/* 270573 0x801ADE74 */ .word	EnAObj_Destroy
/* 270574 0x801ADE78 */ .word	EnAObj_Update
/* 270575 0x801ADE7C */ .word	EnAObj_Draw
glabel enAObjCylinderInit
/* 270576 0x801ADE80 */ .word	0x0A000039
/* 270577 0x801ADE84 */ .word	0x20010000
/* 270578 0x801ADE88 */ .word	0x00000000
/* 270579 0x801ADE8C */ .word	0x00000000
/* 270580 0x801ADE90 */ .word	0x00000000
/* 270581 0x801ADE94 */ .word	0xF7CFFFFF
/* 270582 0x801ADE98 */ .word	0x00000000
/* 270583 0x801ADE9C */ .word	0x00000100
/* 270584 0x801ADEA0 */ .word	0x0019003C
/* 270585 0x801ADEA4 */ .word	0x00000000
/* 270586 0x801ADEA8 */ .word	0x00000000
glabel enAObjInitVar
/* 270587 0x801ADEAC */ .word	0x001F0000
glabel enAObjDisplayLists
/* 270588 0x801ADEB0 */ .word	0x0405AED0
/* 270589 0x801ADEB4 */ .word	0x0405B430
/* 270590 0x801ADEB8 */ .word	0x00000000
/* 270591 0x801ADEBC */ .word	0x00000000
