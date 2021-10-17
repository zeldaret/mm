.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_8008D2E0
/* 013472 0x8008D2E0 3C013780 */ lui	$at, 0x3780
/* 013473 0x8008D2E4 44810000 */ mtc1	$at, $f0
/* 013474 0x8008D2E8 3C19FFFF */ lui	$t9, 0xFFFF
/* 013475 0x8008D2EC 24B80020 */ addiu	$t8, $a1, 0X20
.L8008D2F0:
/* 013476 0x8008D2F0 8CA80000 */ lw	$t0, 0X0($a1)
/* 013477 0x8008D2F4 8CA90020 */ lw	$t1, 0X20($a1)
/* 013478 0x8008D2F8 24A50004 */ addiu	$a1, $a1, 0X4
/* 013479 0x8008D2FC 01195024 */ and	$t2, $t0, $t9
/* 013480 0x8008D300 00095C02 */ srl	$t3, $t1, 16
/* 013481 0x8008D304 014B6025 */ or	$t4, $t2, $t3
/* 013482 0x8008D308 448C2000 */ mtc1	$t4, $f4
/* 013483 0x8008D30C 00086C00 */ sll	$t5, $t0, 16
/* 013484 0x8008D310 312EFFFF */ andi	$t6, $t1, 0XFFFF
/* 013485 0x8008D314 01AE7825 */ or	$t7, $t5, $t6
/* 013486 0x8008D318 468021A0 */ cvt.s.w	$f6, $f4
/* 013487 0x8008D31C 448F5000 */ mtc1	$t7, $f10
/* 013488 0x8008D320 24840008 */ addiu	$a0, $a0, 0X8
/* 013489 0x8008D324 46805420 */ cvt.s.w	$f16, $f10
/* 013490 0x8008D328 46003202 */ mul.s	$f8, $f6, $f0
/* 013491 0x8008D32C 00000000 */ nop
/* 013492 0x8008D330 46008482 */ mul.s	$f18, $f16, $f0
/* 013493 0x8008D334 E488FFF8 */ swc1	$f8, -0X8($a0)
/* 013494 0x8008D338 14B8FFED */ bne	$a1, $t8, .L8008D2F0
/* 013495 0x8008D33C E492FFFC */ swc1	$f18, -0X4($a0)
/* 013496 0x8008D340 03E00008 */ jr	$ra
/* 013497 0x8008D344 00000000 */ nop
/* 013498 0x8008D348 00000000 */ nop
/* 013499 0x8008D34C 00000000 */ nop
