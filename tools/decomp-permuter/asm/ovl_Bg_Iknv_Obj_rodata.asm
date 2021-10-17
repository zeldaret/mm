.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgIknvObjOverlayInfo
/* 000476 0x80BD8220 */ .word	0x00000720
/* 000477 0x80BD8224 */ .word	0x00000050
/* 000478 0x80BD8228 */ .word	0x00000000
/* 000479 0x80BD822C */ .word	0x00000000
/* 000480 0x80BD8230 */ .word	0x0000001B
glabel bgIknvObjOverlayRelocations
/* 000481 0x80BD8234 */ .word	0x4500002C
/* 000482 0x80BD8238 */ .word	0x46000030
/* 000483 0x80BD823C */ .word	0x45000070
/* 000484 0x80BD8240 */ .word	0x46000078
/* 000485 0x80BD8244 */ .word	0x450000D8
/* 000486 0x80BD8248 */ .word	0x460000DC
/* 000487 0x80BD824C */ .word	0x450000F4
/* 000488 0x80BD8250 */ .word	0x460000FC
/* 000489 0x80BD8254 */ .word	0x45000140
/* 000490 0x80BD8258 */ .word	0x46000144
/* 000491 0x80BD825C */ .word	0x44000444
/* 000492 0x80BD8260 */ .word	0x45000458
/* 000493 0x80BD8264 */ .word	0x46000460
/* 000494 0x80BD8268 */ .word	0x450004BC
/* 000495 0x80BD826C */ .word	0x460004C8
/* 000496 0x80BD8270 */ .word	0x44000548
/* 000497 0x80BD8274 */ .word	0x45000558
/* 000498 0x80BD8278 */ .word	0x46000560
/* 000499 0x80BD827C */ .word	0x440005A4
/* 000500 0x80BD8280 */ .word	0x450005B8
/* 000501 0x80BD8284 */ .word	0x460005BC
/* 000502 0x80BD8288 */ .word	0x45000608
/* 000503 0x80BD828C */ .word	0x46000618
/* 000504 0x80BD8290 */ .word	0x82000010
/* 000505 0x80BD8294 */ .word	0x82000014
/* 000506 0x80BD8298 */ .word	0x82000018
/* 000507 0x80BD829C */ .word	0x8200001C
/* 000508 0x80BD82A0 */ .word	0x00000000
/* 000509 0x80BD82A4 */ .word	0x00000000
/* 000510 0x80BD82A8 */ .word	0x00000000
glabel bgIknvObjOverlayInfoOffset
/* 000511 0x80BD82AC */ .word	0x00000090
