.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objRotliftOverlayInfo
/* 000220 0x80B96190 */ .word	0x00000320
/* 000221 0x80B96194 */ .word	0x00000050
/* 000222 0x80B96198 */ .word	0x00000000
/* 000223 0x80B9619C */ .word	0x00000000
/* 000224 0x80B961A0 */ .word	0x0000000C
glabel objRotliftOverlayRelocations
/* 000225 0x80B961A4 */ .word	0x4500011C
/* 000226 0x80B961A8 */ .word	0x46000120
/* 000227 0x80B961AC */ .word	0x440001C4
/* 000228 0x80B961B0 */ .word	0x450001DC
/* 000229 0x80B961B4 */ .word	0x460001E0
/* 000230 0x80B961B8 */ .word	0x44000284
/* 000231 0x80B961BC */ .word	0x450002D4
/* 000232 0x80B961C0 */ .word	0x460002D8
/* 000233 0x80B961C4 */ .word	0x82000010
/* 000234 0x80B961C8 */ .word	0x82000014
/* 000235 0x80B961CC */ .word	0x82000018
/* 000236 0x80B961D0 */ .word	0x8200001C
/* 000237 0x80B961D4 */ .word	0x00000000
/* 000238 0x80B961D8 */ .word	0x00000000
glabel objRotliftOverlayInfoOffset
/* 000239 0x80B961DC */ .word	0x00000050
