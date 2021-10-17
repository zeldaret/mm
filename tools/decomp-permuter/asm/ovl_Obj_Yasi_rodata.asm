.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objYasiOverlayInfo
/* 000176 0x80BB4DB0 */ .word	0x00000280
/* 000177 0x80BB4DB4 */ .word	0x00000030
/* 000178 0x80BB4DB8 */ .word	0x00000010
/* 000179 0x80BB4DBC */ .word	0x00000000
/* 000180 0x80BB4DC0 */ .word	0x0000000E
glabel objYasiOverlayRelocations
/* 000181 0x80BB4DC4 */ .word	0x45000014
/* 000182 0x80BB4DC8 */ .word	0x46000018
/* 000183 0x80BB4DCC */ .word	0x4500004C
/* 000184 0x80BB4DD0 */ .word	0x4600005C
/* 000185 0x80BB4DD4 */ .word	0x45000158
/* 000186 0x80BB4DD8 */ .word	0x4600015C
/* 000187 0x80BB4DDC */ .word	0x45000168
/* 000188 0x80BB4DE0 */ .word	0x46000190
/* 000189 0x80BB4DE4 */ .word	0x4500023C
/* 000190 0x80BB4DE8 */ .word	0x46000240
/* 000191 0x80BB4DEC */ .word	0x82000010
/* 000192 0x80BB4DF0 */ .word	0x82000014
/* 000193 0x80BB4DF4 */ .word	0x82000018
/* 000194 0x80BB4DF8 */ .word	0x8200001C
glabel objYasiOverlayInfoOffset
/* 000195 0x80BB4DFC */ .word	0x00000050
