.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Okarina_Tag_InitVars
/* 000252 0x8093E810 */ .word	0x00970000
/* 000253 0x8093E814 */ .word	0x0A000010
/* 000254 0x8093E818 */ .word	0x00010000
/* 000255 0x8093E81C */ .word	0x0000015C
/* 000256 0x8093E820 */ .word	EnOkarinaTag_Init
/* 000257 0x8093E824 */ .word	EnOkarinaTag_Destroy
/* 000258 0x8093E828 */ .word	EnOkarinaTag_Update
/* 000259 0x8093E82C */ .word	0x00000000
