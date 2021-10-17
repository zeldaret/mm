.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Rotlift_InitVars
/* 000200 0x80B96140 */ .word	0x02250100
/* 000201 0x80B96144 */ .word	0x00000000
/* 000202 0x80B96148 */ .word	0x02070000
/* 000203 0x80B9614C */ .word	0x00000164
/* 000204 0x80B96150 */ .word	ObjRotlift_Init
/* 000205 0x80B96154 */ .word	ObjRotlift_Destroy
/* 000206 0x80B96158 */ .word	ObjRotlift_Update
/* 000207 0x80B9615C */ .word	ObjRotlift_Draw
glabel D_80B96160
/* 000208 0x80B96160 */ .word	0x06000400
/* 000209 0x80B96164 */ .word	0x06001F98
/* 000210 0x80B96168 */ .word	0x06002190
/* 000211 0x80B9616C */ .word	0x06002CE0
/* 000212 0x80B96170 */ .word	0x06004A08
/* 000213 0x80B96174 */ .word	0x06004DF0
glabel D_80B96178
/* 000214 0x80B96178 */ .word	0xC8580064
/* 000215 0x80B9617C */ .word	0xB0FC0FA0
/* 000216 0x80B96180 */ .word	0xB1000320
/* 000217 0x80B96184 */ .word	0x31040320
/* 000218 0x80B96188 */ .word	0x00000000
/* 000219 0x80B9618C */ .word	0x00000000
