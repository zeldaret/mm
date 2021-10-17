.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80B66CD0
/* 000172 0x80B66CD0 */ .word	0x452AA000
/* 000173 0x80B66CD4 */ .word	0x00000000
/* 000174 0x80B66CD8 */ .word	0x00000000
/* 000175 0x80B66CDC */ .word	0x00000000
glabel objHarikoOverlayInfo
/* 000176 0x80B66CE0 */ .word	0x00000290
/* 000177 0x80B66CE4 */ .word	0x00000020
/* 000178 0x80B66CE8 */ .word	0x00000010
/* 000179 0x80B66CEC */ .word	0x00000000
/* 000180 0x80B66CF0 */ .word	0x0000000E
glabel objHarikoOverlayRelocations
/* 000181 0x80B66CF4 */ .word	0x44000034
/* 000182 0x80B66CF8 */ .word	0x4500005C
/* 000183 0x80B66CFC */ .word	0x46000060
/* 000184 0x80B66D00 */ .word	0x45000080
/* 000185 0x80B66D04 */ .word	0x46000084
/* 000186 0x80B66D08 */ .word	0x45000088
/* 000187 0x80B66D0C */ .word	0x4600008C
/* 000188 0x80B66D10 */ .word	0x4400013C
/* 000189 0x80B66D14 */ .word	0x44000174
/* 000190 0x80B66D18 */ .word	0x440001A4
/* 000191 0x80B66D1C */ .word	0x82000010
/* 000192 0x80B66D20 */ .word	0x82000014
/* 000193 0x80B66D24 */ .word	0x82000018
/* 000194 0x80B66D28 */ .word	0x8200001C
glabel objHarikoOverlayInfoOffset
/* 000195 0x80B66D2C */ .word	0x00000050
