.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel demoGetitemOverlayInfo
/* 000204 0x80A4FD70 */ .word	0x00000300
/* 000205 0x80A4FD74 */ .word	0x00000030
/* 000206 0x80A4FD78 */ .word	0x00000000
/* 000207 0x80A4FD7C */ .word	0x00000000
/* 000208 0x80A4FD80 */ .word	0x00000011
glabel demoGetitemOverlayRelocations
/* 000209 0x80A4FD84 */ .word	0x45000044
/* 000210 0x80A4FD88 */ .word	0x46000048
/* 000211 0x80A4FD8C */ .word	0x4500004C
/* 000212 0x80A4FD90 */ .word	0x4600005C
/* 000213 0x80A4FD94 */ .word	0x45000060
/* 000214 0x80A4FD98 */ .word	0x4600006C
/* 000215 0x80A4FD9C */ .word	0x45000074
/* 000216 0x80A4FDA0 */ .word	0x46000088
/* 000217 0x80A4FDA4 */ .word	0x45000104
/* 000218 0x80A4FDA8 */ .word	0x46000108
/* 000219 0x80A4FDAC */ .word	0x450001C4
/* 000220 0x80A4FDB0 */ .word	0x460001CC
/* 000221 0x80A4FDB4 */ .word	0x450001E8
/* 000222 0x80A4FDB8 */ .word	0x46000230
/* 000223 0x80A4FDBC */ .word	0x82000010
/* 000224 0x80A4FDC0 */ .word	0x82000014
/* 000225 0x80A4FDC4 */ .word	0x82000018
/* 000226 0x80A4FDC8 */ .word	0x00000000
glabel demoGetitemOverlayInfoOffset
/* 000227 0x80A4FDCC */ .word	0x00000060
