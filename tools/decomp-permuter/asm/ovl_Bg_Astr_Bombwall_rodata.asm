.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgAstrBombwallOverlayInfo
/* 000508 0x80C0A6C0 */ .word	0x00000730
/* 000509 0x80C0A6C4 */ .word	0x000000B0
/* 000510 0x80C0A6C8 */ .word	0x00000010
/* 000511 0x80C0A6CC */ .word	0x00000000
/* 000512 0x80C0A6D0 */ .word	0x0000001A
glabel bgAstrBombwallOverlayRelocations
/* 000513 0x80C0A6D4 */ .word	0x45000130
/* 000514 0x80C0A6D8 */ .word	0x46000134
/* 000515 0x80C0A6DC */ .word	0x4500019C
/* 000516 0x80C0A6E0 */ .word	0x460001B8
/* 000517 0x80C0A6E4 */ .word	0x450001C8
/* 000518 0x80C0A6E8 */ .word	0x460001DC
/* 000519 0x80C0A6EC */ .word	0x440001E8
/* 000520 0x80C0A6F0 */ .word	0x44000200
/* 000521 0x80C0A6F4 */ .word	0x450003C0
/* 000522 0x80C0A6F8 */ .word	0x460003C4
/* 000523 0x80C0A6FC */ .word	0x450003F0
/* 000524 0x80C0A700 */ .word	0x460003F4
/* 000525 0x80C0A704 */ .word	0x450004A8
/* 000526 0x80C0A708 */ .word	0x460004AC
/* 000527 0x80C0A70C */ .word	0x44000504
/* 000528 0x80C0A710 */ .word	0x45000534
/* 000529 0x80C0A714 */ .word	0x46000538
/* 000530 0x80C0A718 */ .word	0x44000570
/* 000531 0x80C0A71C */ .word	0x440005B8
/* 000532 0x80C0A720 */ .word	0x450005CC
/* 000533 0x80C0A724 */ .word	0x460005D0
/* 000534 0x80C0A728 */ .word	0x82000010
/* 000535 0x80C0A72C */ .word	0x82000014
/* 000536 0x80C0A730 */ .word	0x82000018
/* 000537 0x80C0A734 */ .word	0x8200001C
/* 000538 0x80C0A738 */ .word	0x820000A4
glabel bgAstrBombwallOverlayInfoOffset
/* 000539 0x80C0A73C */ .word	0x00000080
