.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Kinoko_InitVars
/* 000220 0x80BB4A70 */ .word	0x023B0700
/* 000221 0x80BB4A74 */ .word	0x00000010
/* 000222 0x80BB4A78 */ .word	0x00010000
/* 000223 0x80BB4A7C */ .word	0x00000144
/* 000224 0x80BB4A80 */ .word	ObjKinoko_Init
/* 000225 0x80BB4A84 */ .word	ObjKinoko_Destroy
/* 000226 0x80BB4A88 */ .word	ObjKinoko_Update
/* 000227 0x80BB4A8C */ .word	ObjKinoko_Draw
