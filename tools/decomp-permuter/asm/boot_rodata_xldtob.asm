.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80099460
/* 025856 0x80099460 */ .word	0x40240000
/* 025857 0x80099464 */ .word	0x00000000
/* 025858 0x80099468 */ .word	0x40590000
/* 025859 0x8009946C */ .word	0x00000000
/* 025860 0x80099470 */ .word	0x40C38800
/* 025861 0x80099474 */ .word	0x00000000
/* 025862 0x80099478 */ .word	0x4197D784
/* 025863 0x8009947C */ .word	0x00000000
/* 025864 0x80099480 */ .word	0x4341C379
/* 025865 0x80099484 */ .word	0x37E08000
/* 025866 0x80099488 */ .word	0x4693B8B5
/* 025867 0x8009948C */ .word	0xB5056E17
/* 025868 0x80099490 */ .word	0x4D384F03
/* 025869 0x80099494 */ .word	0xE93FF9F5
/* 025870 0x80099498 */ .word	0x5A827748
/* 025871 0x8009949C */ .word	0xF9301D32
/* 025872 0x800994A0 */ .word	0x75154FDD
/* 025873 0x800994A4 */ .word	0x7F73BF3C
glabel D_800994A8
/* 025874 0x800994A8 */ .word	0x4E614E00
glabel D_800994AC
/* 025875 0x800994AC */ .word	0x496E6600
glabel D_800994B0
/* 025876 0x800994B0 */ .byte	0x30
glabel D_800994B1
/* 025876 0x800994B0 */ .byte	0x00
/* 025876 0x800994B0 */ .short	0x0000
/* 025877 0x800994B4 */ .word	0x00000000
glabel D_800994B8
/* 025878 0x800994B8 */ .word	0x4197D784
/* 025879 0x800994BC */ .word	0x00000000
