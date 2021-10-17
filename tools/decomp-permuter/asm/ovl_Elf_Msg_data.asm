.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Elf_Msg_InitVars
/* 000304 0x8092E450 */ .word	0x008B0700
/* 000305 0x8092E454 */ .word	0x00000010
/* 000306 0x8092E458 */ .word	0x00010000
/* 000307 0x8092E45C */ .word	0x00000148
/* 000308 0x8092E460 */ .word	ElfMsg_Init
/* 000309 0x8092E464 */ .word	ElfMsg_Destroy
/* 000310 0x8092E468 */ .word	ElfMsg_Update
/* 000311 0x8092E46C */ .word	0x00000000
glabel D_8092E470
/* 000312 0x8092E470 */ .word	0xC85803E8
/* 000313 0x8092E474 */ .word	0x30FC03E8
/* 000314 0x8092E478 */ .word	0x00000000
/* 000315 0x8092E47C */ .word	0x00000000
