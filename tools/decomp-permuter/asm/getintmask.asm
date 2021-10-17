.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osGetIntMask
/* 008212 0x800880B0 40026000 */ mfc0	$v0, $12
/* 008213 0x800880B4 3042FF01 */ andi	$v0, $v0, 0XFF01
/* 008214 0x800880B8 3C088009 */ lui	$t0, %hi(__OSGlobalIntMask)
/* 008215 0x800880BC 25087E60 */ addiu	$t0, $t0, %lo(__OSGlobalIntMask)
/* 008216 0x800880C0 8D090000 */ lw	$t1, 0X0($t0)
/* 008217 0x800880C4 2401FFFF */ li	$at, -0X1
/* 008218 0x800880C8 01214026 */ xor	$t0, $t1, $at
/* 008219 0x800880CC 3108FF00 */ andi	$t0, $t0, 0XFF00
/* 008220 0x800880D0 00481025 */ or	$v0, $v0, $t0
/* 008221 0x800880D4 3C09A430 */ lui	$t1, 0xA430
/* 008222 0x800880D8 8D29000C */ lw	$t1, 0XC($t1)
/* 008223 0x800880DC 11200008 */ beqz	$t1, .L80088100
/* 008224 0x800880E0 3C088009 */ lui	$t0, %hi(__OSGlobalIntMask)
/* 008225 0x800880E4 25087E60 */ addiu	$t0, $t0, %lo(__OSGlobalIntMask)
/* 008226 0x800880E8 8D080000 */ lw	$t0, 0X0($t0)
/* 008227 0x800880EC 00084402 */ srl	$t0, $t0, 16
/* 008228 0x800880F0 2401FFFF */ li	$at, -0X1
/* 008229 0x800880F4 01014026 */ xor	$t0, $t0, $at
/* 008230 0x800880F8 3108003F */ andi	$t0, $t0, 0X3F
/* 008231 0x800880FC 01284825 */ or	$t1, $t1, $t0
.L80088100:
/* 008232 0x80088100 00095400 */ sll	$t2, $t1, 16
/* 008233 0x80088104 004A1025 */ or	$v0, $v0, $t2
/* 008234 0x80088108 03E00008 */ jr	$ra
/* 008235 0x8008810C 00000000 */ nop
