.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Jc_Mato_InitVars
/* 000196 0x80B9E1F0 */ .word	0x022F0600
/* 000197 0x80B9E1F4 */ .word	0x00004030
/* 000198 0x80B9E1F8 */ .word	0x018E0000
/* 000199 0x80B9E1FC */ .word	0x000001B0
/* 000200 0x80B9E200 */ .word	EnJcMato_Init
/* 000201 0x80B9E204 */ .word	EnJcMato_Destroy
/* 000202 0x80B9E208 */ .word	EnJcMato_Update
/* 000203 0x80B9E20C */ .word	EnJcMato_Draw
glabel D_80B9E210
/* 000204 0x80B9E210 */ .word	0x0A000939
/* 000205 0x80B9E214 */ .word	0x10040000
/* 000206 0x80B9E218 */ .word	0x00000000
/* 000207 0x80B9E21C */ .word	0xF7CFFFFF
/* 000208 0x80B9E220 */ .word	0x00000000
/* 000209 0x80B9E224 */ .word	0xF7CFFFFF
/* 000210 0x80B9E228 */ .word	0x00000000
/* 000211 0x80B9E22C */ .word	0x00010100
/* 000212 0x80B9E230 */ .word	0x00000000
/* 000213 0x80B9E234 */ .word	0x00000000
/* 000214 0x80B9E238 */ .word	0x000F0064
glabel D_80B9E23C
/* 000215 0x80B9E23C */ .word	0x01010101
/* 000216 0x80B9E240 */ .word	0x01F10101
/* 000217 0x80B9E244 */ .word	0x010101F1
/* 000218 0x80B9E248 */ .word	0xF1F10101
/* 000219 0x80B9E24C */ .word	0x01010101
/* 000220 0x80B9E250 */ .word	0x01010101
/* 000221 0x80B9E254 */ .word	0x01010101
/* 000222 0x80B9E258 */ .word	0x01010101
glabel D_80B9E25C
/* 000223 0x80B9E25C */ .word	0x00000000
/* 000224 0x80B9E260 */ .word	0xC51C4000
/* 000225 0x80B9E264 */ .word	0x00000000
/* 000226 0x80B9E268 */ .word	0x00000000
/* 000227 0x80B9E26C */ .word	0x00000000
