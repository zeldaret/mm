.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Elf_Msg2_InitVars
/* 000276 0x8096F090 */ .word	0x00C60100
/* 000277 0x8096F094 */ .word	0x00000010
/* 000278 0x8096F098 */ .word	0x00010000
/* 000279 0x8096F09C */ .word	0x00000148
/* 000280 0x8096F0A0 */ .word	ElfMsg2_Init
/* 000281 0x8096F0A4 */ .word	ElfMsg2_Destroy
/* 000282 0x8096F0A8 */ .word	ElfMsg2_Update
/* 000283 0x8096F0AC */ .word	0x00000000
glabel D_8096F0B0
/* 000284 0x8096F0B0 */ .word	0xC85800C8
/* 000285 0x8096F0B4 */ .word	0x30FC03E8
/* 000286 0x8096F0B8 */ .word	0x00000000
/* 000287 0x8096F0BC */ .word	0x00000000
