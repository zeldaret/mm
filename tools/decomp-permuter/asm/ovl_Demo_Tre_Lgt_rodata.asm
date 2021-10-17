.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel demoTreLgtOverlayInfo
/* 000424 0x808E14E0 */ .word	0x00000650
/* 000425 0x808E14E4 */ .word	0x00000050
/* 000426 0x808E14E8 */ .word	0x00000000
/* 000427 0x808E14EC */ .word	0x00000000
/* 000428 0x808E14F0 */ .word	0x00000018
glabel demoTreLgtOverlayRelocations
/* 000429 0x808E14F4 */ .word	0x45000018
/* 000430 0x808E14F8 */ .word	0x4600001C
/* 000431 0x808E14FC */ .word	0x44000060
/* 000432 0x808E1500 */ .word	0x440000F4
/* 000433 0x808E1504 */ .word	0x45000140
/* 000434 0x808E1508 */ .word	0x4600016C
/* 000435 0x808E150C */ .word	0x45000130
/* 000436 0x808E1510 */ .word	0x4600013C
/* 000437 0x808E1514 */ .word	0x450001B4
/* 000438 0x808E1518 */ .word	0x460001B8
/* 000439 0x808E151C */ .word	0x450001CC
/* 000440 0x808E1520 */ .word	0x460001D0
/* 000441 0x808E1524 */ .word	0x45000208
/* 000442 0x808E1528 */ .word	0x4600020C
/* 000443 0x808E152C */ .word	0x4500043C
/* 000444 0x808E1530 */ .word	0x46000448
/* 000445 0x808E1534 */ .word	0x45000618
/* 000446 0x808E1538 */ .word	0x46000624
/* 000447 0x808E153C */ .word	0x82000030
/* 000448 0x808E1540 */ .word	0x82000034
/* 000449 0x808E1544 */ .word	0x82000038
/* 000450 0x808E1548 */ .word	0x8200003C
/* 000451 0x808E154C */ .word	0x82000048
/* 000452 0x808E1550 */ .word	0x8200004C
/* 000453 0x808E1554 */ .word	0x00000000
/* 000454 0x808E1558 */ .word	0x00000000
glabel demoTreLgtOverlayInfoOffset
/* 000455 0x808E155C */ .word	0x00000080
