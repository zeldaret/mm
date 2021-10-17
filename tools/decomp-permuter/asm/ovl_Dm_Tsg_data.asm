.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Tsg_InitVars
/* 000236 0x80A3B010 */ .word	0x01540700
/* 000237 0x80A3B014 */ .word	0x00000030
/* 000238 0x80A3B018 */ .word	0x019F0000
/* 000239 0x80A3B01C */ .word	0x00000920
/* 000240 0x80A3B020 */ .word	DmTsg_Init
/* 000241 0x80A3B024 */ .word	DmTsg_Destroy
/* 000242 0x80A3B028 */ .word	DmTsg_Update
/* 000243 0x80A3B02C */ .word	DmTsg_Draw
