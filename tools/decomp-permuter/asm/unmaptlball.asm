.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osUnmapTLBAll
/* 015200 0x8008EDE0 40085000 */ mfc0	$t0, $10
/* 015201 0x8008EDE4 2409001E */ li	$t1, 0X1E
/* 015202 0x8008EDE8 3C0A8000 */ lui	$t2, 0x8000
/* 015203 0x8008EDEC 408A5000 */ mtc0	$t2, $10
/* 015204 0x8008EDF0 40801000 */ mtc0	$zero, $2
/* 015205 0x8008EDF4 40801800 */ mtc0	$zero, $3
.L8008EDF8:
/* 015206 0x8008EDF8 40890000 */ mtc0	$t1, $0
/* 015207 0x8008EDFC 00000000 */ nop
/* 015208 0x8008EE00 42000002 */ tlbwi
/* 015209 0x8008EE04 00000000 */ nop
/* 015210 0x8008EE08 00000000 */ nop
/* 015211 0x8008EE0C 2129FFFF */ addi	$t1, $t1, -0X1
/* 015212 0x8008EE10 0521FFF9 */ bgez	$t1, .L8008EDF8
/* 015213 0x8008EE14 00000000 */ nop
/* 015214 0x8008EE18 40885000 */ mtc0	$t0, $10
/* 015215 0x8008EE1C 03E00008 */ jr	$ra
/* 015216 0x8008EE20 00000000 */ nop
/* 015217 0x8008EE24 00000000 */ nop
/* 015218 0x8008EE28 00000000 */ nop
/* 015219 0x8008EE2C 00000000 */ nop
