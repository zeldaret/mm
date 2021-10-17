.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80927380
/* 001140 0x80927380 */ .word	0x00000000
glabel D_80927384
/* 001141 0x80927384 */ .word	0x00000000
glabel D_80927388
/* 001142 0x80927388 */ .word	0x00000000
glabel D_8092738C
/* 001143 0x8092738C */ .word	0x00000000
glabel Obj_Kibako_InitVars
/* 001144 0x80927390 */ .word	0x00810600
/* 001145 0x80927394 */ .word	0x04000010
/* 001146 0x80927398 */ .word	0x00010000
/* 001147 0x8092739C */ .word	0x0000019C
/* 001148 0x809273A0 */ .word	ObjKibako_Init
/* 001149 0x809273A4 */ .word	ObjKibako_Destroy
/* 001150 0x809273A8 */ .word	ObjKibako_Update
/* 001151 0x809273AC */ .word	0x00000000
glabel D_809273B0
/* 001152 0x809273B0 */ .word	0x0A090939
/* 001153 0x809273B4 */ .word	0x20010000
/* 001154 0x809273B8 */ .word	0x00000000
/* 001155 0x809273BC */ .word	0x00400000
/* 001156 0x809273C0 */ .word	0x00020000
/* 001157 0x809273C4 */ .word	0x058BC79C
/* 001158 0x809273C8 */ .word	0x00000000
/* 001159 0x809273CC */ .word	0x19010100
/* 001160 0x809273D0 */ .word	0x000F001E
/* 001161 0x809273D4 */ .word	0x00000000
/* 001162 0x809273D8 */ .word	0x00000000
glabel D_809273DC
/* 001163 0x809273DC */ .word	0x0003016F
glabel D_809273E0
/* 001164 0x809273E0 */ .word	0x05007980
/* 001165 0x809273E4 */ .word	0x06001A70
glabel D_809273E8
/* 001166 0x809273E8 */ .word	0x05007890
/* 001167 0x809273EC */ .word	0x06001180
glabel D_809273F0
/* 001168 0x809273F0 */ .word	0xB874FA24
/* 001169 0x809273F4 */ .word	0xB878B9B0
/* 001170 0x809273F8 */ .word	0xB100003C
/* 001171 0x809273FC */ .word	0x3104003C
