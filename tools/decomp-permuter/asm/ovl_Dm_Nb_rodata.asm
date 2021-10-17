.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel dmNbOverlayInfo
/* 000216 0x80C1E230 */ .word	0x00000310
/* 000217 0x80C1E234 */ .word	0x00000050
/* 000218 0x80C1E238 */ .word	0x00000000
/* 000219 0x80C1E23C */ .word	0x00000000
/* 000220 0x80C1E240 */ .word	0x0000000F
glabel dmNbOverlayRelocations
/* 000221 0x80C1E244 */ .word	0x45000020
/* 000222 0x80C1E248 */ .word	0x4600002C
/* 000223 0x80C1E24C */ .word	0x4500005C
/* 000224 0x80C1E250 */ .word	0x46000060
/* 000225 0x80C1E254 */ .word	0x44000124
/* 000226 0x80C1E258 */ .word	0x4400015C
/* 000227 0x80C1E25C */ .word	0x440001E0
/* 000228 0x80C1E260 */ .word	0x45000208
/* 000229 0x80C1E264 */ .word	0x4600020C
/* 000230 0x80C1E268 */ .word	0x450002CC
/* 000231 0x80C1E26C */ .word	0x460002D0
/* 000232 0x80C1E270 */ .word	0x82000010
/* 000233 0x80C1E274 */ .word	0x82000014
/* 000234 0x80C1E278 */ .word	0x82000018
/* 000235 0x80C1E27C */ .word	0x8200001C
/* 000236 0x80C1E280 */ .word	0x00000000
/* 000237 0x80C1E284 */ .word	0x00000000
/* 000238 0x80C1E288 */ .word	0x00000000
glabel dmNbOverlayInfoOffset
/* 000239 0x80C1E28C */ .word	0x00000060
