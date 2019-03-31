#include <ultra64.h>
#include <global.h>

#pragma intrinsic (sqrtf)
extern float fabsf(float);
#pragma intrinsic (fabsf)

void* func_800FEC90(void* dst, void* src, size_t n) {
    _bcopy(src, dst, n);

    return dst;
}

#ifdef NONMATCHING

void* func_800FECC0(u8* a0, u32 a1, u32 a2) {
    u8* v0;

    // XXX: realloc is messed up
    if (a1 == 0) {
        _blkclr((void*)a0, (u32)a2);

        return a0;
    }

    for (v0 = a0; a2 != 0; a2--) {
        *v0++ = a1;
    }

    return a0;
}

#else

GLOBAL_ASM(
glabel func_800FECC0
/* 091264 0x800FECC0 27BDFFE8 */ addiu	$sp, $sp, -24
/* 091265 0x800FECC4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 091266 0x800FECC8 AFA40018 */ sw	$a0, 0X18($sp)
/* 091267 0x800FECCC 14A00006 */ bnez	$a1, .L_800FECE8
/* 091268 0x800FECD0 8FA20018 */ lw	$v0, 0X18($sp)
/* 091269 0x800FECD4 8FA40018 */ lw	$a0, 0X18($sp)
/* 091270 0x800FECD8 0C02258C */ jal	_blkclr
/* 091271 0x800FECDC 00C02825 */ move	$a1, $a2
/* 091272 0x800FECE0 10000014 */ b	.L_800FED34
/* 091273 0x800FECE4 8FA20018 */ lw	$v0, 0X18($sp)
.L_800FECE8:
/* 091274 0x800FECE8 18C00011 */ blez	$a2, .L_800FED30
/* 091275 0x800FECEC 00C01825 */ move	$v1, $a2
/* 091276 0x800FECF0 30C70003 */ andi	$a3, $a2, 0X3
/* 091277 0x800FECF4 00073823 */ negu	$a3, $a3
/* 091278 0x800FECF8 10E00006 */ beqz	$a3, .L_800FED14
/* 091279 0x800FECFC 00E62021 */ addu	$a0, $a3, $a2
.L_800FED00:
/* 091280 0x800FED00 2463FFFF */ addiu	$v1, $v1, -1
/* 091281 0x800FED04 A0450000 */ sb	$a1, 0X0($v0)
/* 091282 0x800FED08 1483FFFD */ bne	$a0, $v1, .L_800FED00
/* 091283 0x800FED0C 24420001 */ addiu	$v0, $v0, 1
/* 091284 0x800FED10 10600007 */ beqz	$v1, .L_800FED30
.L_800FED14:
/* 091285 0x800FED14 2463FFFC */ addiu	$v1, $v1, -4
/* 091286 0x800FED18 A0450001 */ sb	$a1, 0X1($v0)
/* 091287 0x800FED1C A0450002 */ sb	$a1, 0X2($v0)
/* 091288 0x800FED20 A0450003 */ sb	$a1, 0X3($v0)
/* 091289 0x800FED24 24420004 */ addiu	$v0, $v0, 4
/* 091290 0x800FED28 1460FFFA */ bnez	$v1, .L_800FED14
/* 091291 0x800FED2C A045FFFC */ sb	$a1, -0X4($v0)
.L_800FED30:
/* 091292 0x800FED30 8FA20018 */ lw	$v0, 0X18($sp)
.L_800FED34:
/* 091293 0x800FED34 8FBF0014 */ lw	$ra, 0X14($sp)
/* 091294 0x800FED38 27BD0018 */ addiu	$sp, $sp, 24
/* 091295 0x800FED3C 03E00008 */ jr	$ra
/* 091296 0x800FED40 00000000 */ nop
)

#endif

f32 func_800FED44(s16 a0) {
    return coss(a0) * D_801DDA80;
}

f32 func_800FED84(s16 a0) {
    return sins(a0) * D_801DDA84;
}

s32 func_800FEDC4(s32 a0, s32 a1, s32 a2) {
    s32 v1;

    if (a1 >= a0) {
        v1 = a0 + a2;
        if (a1 >= v1) {
            return v1;
        }
    } else {
        v1 = a0 - a2;
        if (v1 >= a1) {
            return v1;
        }
    }
    return a1;
}

UNK_RET func_800FEE08(u32* a0, u32 a1, u32 a2) {
    *a0 = func_800FEDC4(*a0, a1, a2);
}

UNK_TYPE func_800FEE34(u32* a0, u32 a1, u32 a2) {
    func_800FEE08(a0, a1, a2);

    return a1 == *a0;
}

UNK_TYPE func_800FEE70(s16* a0, s16 a1, s16 a2) {
    f32 f0;

    if (a2 != 0) {
        f0 = D_801D1508;

        if ((s16)(*a0 - a1) > 0) {
            a2 = -a2;
        }

        *a0 += (s16)(a2 * f0);

        if (((s16)(*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }

    return 0;
}

UNK_TYPE func_800FEF2C(s16* a0, s16 a1, s16 a2) {
    if (a2 != 0) {
        if (a1 < *a0) {
            a2 = -a2;
        }

        *a0 += a2;

        if (((*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }

    return 0;
}

UNK_TYPE func_800FEFB4(s8* a0, s8 a1, s8 a2) {
    if (a2 != 0) {
        if (a1 < *a0) {
            a2 = -a2;
        }

        *a0 += a2;

        if (((*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }

    return 0;
}

#ifdef NONMATCHING

UNK_TYPE func_800FF03C(f32* a0, f32 a1, f32 a2) {
    if (a2 != 0) {
        // XXX: regalloc is messed up
        if (a1 < *a0) {
            a2 = -a2;
        }

        *a0 += a2;

        if (((*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 != *a0) {
        return 1;
    }

    return 0;
}

#else

GLOBAL_ASM(
glabel func_800FF03C
/* 091487 0x800FF03C 44857000 */ mtc1	$a1, $f14
/* 091488 0x800FF040 44866000 */ mtc1	$a2, $f12
/* 091489 0x800FF044 44802000 */ mtc1	$zero, $f4
/* 091490 0x800FF048 00000000 */ nop
/* 091491 0x800FF04C 46046032 */ c.eq.s	$f12, $f4
/* 091492 0x800FF050 00000000 */ nop
/* 091493 0x800FF054 45030015 */ bc1tl .L_800FF0AC
/* 091494 0x800FF058 C4840000 */ lwc1	$f4, 0X0($a0)
/* 091495 0x800FF05C C4800000 */ lwc1	$f0, 0X0($a0)
/* 091496 0x800FF060 24020001 */ li	$v0, 1
/* 091497 0x800FF064 4600703C */ c.lt.s	$f14, $f0
/* 091498 0x800FF068 00000000 */ nop
/* 091499 0x800FF06C 45020003 */ bc1fl .L_800FF07C
/* 091500 0x800FF070 460C0180 */ add.s	$f6, $f0, $f12
/* 091501 0x800FF074 46006307 */ neg.s	$f12, $f12
/* 091502 0x800FF078 460C0180 */ add.s	$f6, $f0, $f12
.L_800FF07C:
/* 091503 0x800FF07C 44809000 */ mtc1	$zero, $f18
/* 091504 0x800FF080 E4860000 */ swc1	$f6, 0X0($a0)
/* 091505 0x800FF084 C4880000 */ lwc1	$f8, 0X0($a0)
/* 091506 0x800FF088 460E4281 */ sub.s	$f10, $f8, $f14
/* 091507 0x800FF08C 460C5402 */ mul.s	$f16, $f10, $f12
/* 091508 0x800FF090 4610903E */ c.le.s	$f18, $f16
/* 091509 0x800FF094 00000000 */ nop
/* 091510 0x800FF098 4502000B */ bc1fl .L_800FF0C8
/* 091511 0x800FF09C 00001025 */ move	$v0, $zero
/* 091512 0x800FF0A0 03E00008 */ jr	$ra
/* 091513 0x800FF0A4 E48E0000 */ swc1	$f14, 0X0($a0)
/* 091514 0x800FF0A8 C4840000 */ lwc1	$f4, 0X0($a0)
.L_800FF0AC:
/* 091515 0x800FF0AC 46047032 */ c.eq.s	$f14, $f4
/* 091516 0x800FF0B0 00000000 */ nop
/* 091517 0x800FF0B4 45020004 */ bc1fl .L_800FF0C8
/* 091518 0x800FF0B8 00001025 */ move	$v0, $zero
/* 091519 0x800FF0BC 03E00008 */ jr	$ra
/* 091520 0x800FF0C0 24020001 */ li	$v0, 1
/* 091521 0x800FF0C4 00001025 */ move	$v0, $zero
.L_800FF0C8:
/* 091522 0x800FF0C8 03E00008 */ jr	$ra
/* 091523 0x800FF0CC 00000000 */ nop
)

#endif

#ifdef NONMATCHING

UNK_TYPE func_800FF0D0(s16* a0, s16 a1, s16 a2) {
    s32 v0 = *a0;

    // XXX: regalloc is messed up
    *a0 += a2;

    if (((*a0 - a1) * (v0 - a1)) <= 0) {
        *a0 = a1;

        return 1;
    }

    return 0;
}

#else

GLOBAL_ASM(
glabel func_800FF0D0
/* 091524 0x800FF0D0 AFA50004 */ sw	$a1, 0X4($sp)
/* 091525 0x800FF0D4 AFA60008 */ sw	$a2, 0X8($sp)
/* 091526 0x800FF0D8 00063400 */ sll	$a2, $a2, 16
/* 091527 0x800FF0DC 00052C00 */ sll	$a1, $a1, 16
/* 091528 0x800FF0E0 00052C03 */ sra	$a1, $a1, 16
/* 091529 0x800FF0E4 00063403 */ sra	$a2, $a2, 16
/* 091530 0x800FF0E8 84820000 */ lh	$v0, 0X0($a0)
/* 091531 0x800FF0EC 00467021 */ addu	$t6, $v0, $a2
/* 091532 0x800FF0F0 A48E0000 */ sh	$t6, 0X0($a0)
/* 091533 0x800FF0F4 848F0000 */ lh	$t7, 0X0($a0)
/* 091534 0x800FF0F8 00454823 */ subu	$t1, $v0, $a1
/* 091535 0x800FF0FC 00095400 */ sll	$t2, $t1, 16
/* 091536 0x800FF100 01E5C023 */ subu	$t8, $t7, $a1
/* 091537 0x800FF104 0018CC00 */ sll	$t9, $t8, 16
/* 091538 0x800FF108 00194403 */ sra	$t0, $t9, 16
/* 091539 0x800FF10C 000A5C03 */ sra	$t3, $t2, 16
/* 091540 0x800FF110 010B0019 */ multu	$t0, $t3
/* 091541 0x800FF114 00001025 */ move	$v0, $zero
/* 091542 0x800FF118 00006012 */ mflo	$t4
/* 091543 0x800FF11C 1D800004 */ bgtz	$t4, .L_800FF130
/* 091544 0x800FF120 00000000 */ nop
/* 091545 0x800FF124 A4850000 */ sh	$a1, 0X0($a0)
/* 091546 0x800FF128 03E00008 */ jr	$ra
/* 091547 0x800FF12C 24020001 */ li	$v0, 1
.L_800FF130:
/* 091548 0x800FF130 03E00008 */ jr	$ra
/* 091549 0x800FF134 00000000 */ nop
)

#endif

#ifdef NONMATCHING

UNK_RET func_800FF138() {

}

#else

GLOBAL_ASM(
glabel func_800FF138
/* 091550 0x800FF138 AFA50004 */ sw	$a1, 0X4($sp)
/* 091551 0x800FF13C AFA60008 */ sw	$a2, 0X8($sp)
/* 091552 0x800FF140 00063400 */ sll	$a2, $a2, 16
/* 091553 0x800FF144 00052C00 */ sll	$a1, $a1, 16
/* 091554 0x800FF148 00052C03 */ sra	$a1, $a1, 16
/* 091555 0x800FF14C 00063403 */ sra	$a2, $a2, 16
/* 091556 0x800FF150 84830000 */ lh	$v1, 0X0($a0)
/* 091557 0x800FF154 34018000 */ ori	$at, $zero, 0X8000
/* 091558 0x800FF158 3C0FFFFF */ lui	$t7, 0xFFFF
/* 091559 0x800FF15C 00A31023 */ subu	$v0, $a1, $v1
/* 091560 0x800FF160 04410004 */ bgez	$v0, .L_800FF174
/* 091561 0x800FF164 0041082A */ slt	$at, $v0, $at
/* 091562 0x800FF168 00063023 */ negu	$a2, $a2
/* 091563 0x800FF16C 00063400 */ sll	$a2, $a2, 16
/* 091564 0x800FF170 00063403 */ sra	$a2, $a2, 16
.L_800FF174:
/* 091565 0x800FF174 14200007 */ bnez	$at, .L_800FF194
/* 091566 0x800FF178 00027023 */ negu	$t6, $v0
/* 091567 0x800FF17C 00063023 */ negu	$a2, $a2
/* 091568 0x800FF180 00063400 */ sll	$a2, $a2, 16
/* 091569 0x800FF184 35EF0001 */ ori	$t7, $t7, 0X1
/* 091570 0x800FF188 00063403 */ sra	$a2, $a2, 16
/* 091571 0x800FF18C 10000009 */ b	.L_800FF1B4
/* 091572 0x800FF190 01EE1023 */ subu	$v0, $t7, $t6
.L_800FF194:
/* 091573 0x800FF194 28418001 */ slti	$at, $v0, -32767
/* 091574 0x800FF198 10200006 */ beqz	$at, .L_800FF1B4
/* 091575 0x800FF19C 00000000 */ nop
/* 091576 0x800FF1A0 00063023 */ negu	$a2, $a2
/* 091577 0x800FF1A4 3401FFFF */ ori	$at, $zero, 0XFFFF
/* 091578 0x800FF1A8 00063400 */ sll	$a2, $a2, 16
/* 091579 0x800FF1AC 00411021 */ addu	$v0, $v0, $at
/* 091580 0x800FF1B0 00063403 */ sra	$a2, $a2, 16
.L_800FF1B4:
/* 091581 0x800FF1B4 10C0000A */ beqz	$a2, .L_800FF1E0
/* 091582 0x800FF1B8 00000000 */ nop
/* 091583 0x800FF1BC 00C20019 */ multu	$a2, $v0
/* 091584 0x800FF1C0 0066C021 */ addu	$t8, $v1, $a2
/* 091585 0x800FF1C4 A4980000 */ sh	$t8, 0X0($a0)
/* 091586 0x800FF1C8 24020001 */ li	$v0, 1
/* 091587 0x800FF1CC 0000C812 */ mflo	$t9
/* 091588 0x800FF1D0 5F200008 */ bgtzl	$t9, .L_800FF1F4
/* 091589 0x800FF1D4 00001025 */ move	$v0, $zero
/* 091590 0x800FF1D8 03E00008 */ jr	$ra
/* 091591 0x800FF1DC A4850000 */ sh	$a1, 0X0($a0)
.L_800FF1E0:
/* 091592 0x800FF1E0 54A30004 */ bnel	$a1, $v1, .L_800FF1F4
/* 091593 0x800FF1E4 00001025 */ move	$v0, $zero
/* 091594 0x800FF1E8 03E00008 */ jr	$ra
/* 091595 0x800FF1EC 24020001 */ li	$v0, 1
/* 091596 0x800FF1F0 00001025 */ move	$v0, $zero
.L_800FF1F4:
/* 091597 0x800FF1F4 03E00008 */ jr	$ra
/* 091598 0x800FF1F8 00000000 */ nop
)

#endif

#ifdef NONMATCHING

UNK_RET func_800FF1FC() {

}

#else

GLOBAL_ASM(
glabel func_800FF1FC
/* 091599 0x800FF1FC AFA50004 */ sw	$a1, 0X4($sp)
/* 091600 0x800FF200 AFA60008 */ sw	$a2, 0X8($sp)
/* 091601 0x800FF204 AFA7000C */ sw	$a3, 0XC($sp)
/* 091602 0x800FF208 00073C00 */ sll	$a3, $a3, 16
/* 091603 0x800FF20C 00063400 */ sll	$a2, $a2, 16
/* 091604 0x800FF210 00052C00 */ sll	$a1, $a1, 16
/* 091605 0x800FF214 00052C03 */ sra	$a1, $a1, 16
/* 091606 0x800FF218 00063403 */ sra	$a2, $a2, 16
/* 091607 0x800FF21C 00073C03 */ sra	$a3, $a3, 16
/* 091608 0x800FF220 84820000 */ lh	$v0, 0X0($a0)
/* 091609 0x800FF224 00071C00 */ sll	$v1, $a3, 16
/* 091610 0x800FF228 00031C03 */ sra	$v1, $v1, 16
/* 091611 0x800FF22C 00A27023 */ subu	$t6, $a1, $v0
/* 091612 0x800FF230 05C00004 */ bltz	$t6, .L_800FF244
/* 091613 0x800FF234 00A2082A */ slt	$at, $a1, $v0
/* 091614 0x800FF238 00061C00 */ sll	$v1, $a2, 16
/* 091615 0x800FF23C 10000001 */ b	.L_800FF244
/* 091616 0x800FF240 00031C03 */ sra	$v1, $v1, 16
.L_800FF244:
/* 091617 0x800FF244 10600011 */ beqz	$v1, .L_800FF28C
/* 091618 0x800FF248 00000000 */ nop
/* 091619 0x800FF24C 50200005 */ beqzl	$at, .L_800FF264
/* 091620 0x800FF250 00437821 */ addu	$t7, $v0, $v1
/* 091621 0x800FF254 00031823 */ negu	$v1, $v1
/* 091622 0x800FF258 00031C00 */ sll	$v1, $v1, 16
/* 091623 0x800FF25C 00031C03 */ sra	$v1, $v1, 16
/* 091624 0x800FF260 00437821 */ addu	$t7, $v0, $v1
.L_800FF264:
/* 091625 0x800FF264 A48F0000 */ sh	$t7, 0X0($a0)
/* 091626 0x800FF268 84980000 */ lh	$t8, 0X0($a0)
/* 091627 0x800FF26C 24020001 */ li	$v0, 1
/* 091628 0x800FF270 0305C823 */ subu	$t9, $t8, $a1
/* 091629 0x800FF274 03230019 */ multu	$t9, $v1
/* 091630 0x800FF278 00004012 */ mflo	$t0
/* 091631 0x800FF27C 05020008 */ bltzl	$t0, .L_800FF2A0
/* 091632 0x800FF280 00001025 */ move	$v0, $zero
/* 091633 0x800FF284 03E00008 */ jr	$ra
/* 091634 0x800FF288 A4850000 */ sh	$a1, 0X0($a0)
.L_800FF28C:
/* 091635 0x800FF28C 54A20004 */ bnel	$a1, $v0, .L_800FF2A0
/* 091636 0x800FF290 00001025 */ move	$v0, $zero
/* 091637 0x800FF294 03E00008 */ jr	$ra
/* 091638 0x800FF298 24020001 */ li	$v0, 1
/* 091639 0x800FF29C 00001025 */ move	$v0, $zero
.L_800FF2A0:
/* 091640 0x800FF2A0 03E00008 */ jr	$ra
/* 091641 0x800FF2A4 00000000 */ nop
)

#endif

#ifdef NONMATCHING

UNK_RET func_800FF2A8() {

}

#else

GLOBAL_ASM(
glabel func_800FF2A8
/* 091642 0x800FF2A8 44857000 */ mtc1	$a1, $f14
/* 091643 0x800FF2AC 44866000 */ mtc1	$a2, $f12
/* 091644 0x800FF2B0 00001025 */ move	$v0, $zero
/* 091645 0x800FF2B4 C4820000 */ lwc1	$f2, 0X0($a0)
/* 091646 0x800FF2B8 44803000 */ mtc1	$zero, $f6
/* 091647 0x800FF2BC 460C1100 */ add.s	$f4, $f2, $f12
/* 091648 0x800FF2C0 460E1401 */ sub.s	$f16, $f2, $f14
/* 091649 0x800FF2C4 E4840000 */ swc1	$f4, 0X0($a0)
/* 091650 0x800FF2C8 C4880000 */ lwc1	$f8, 0X0($a0)
/* 091651 0x800FF2CC 460E4281 */ sub.s	$f10, $f8, $f14
/* 091652 0x800FF2D0 46105482 */ mul.s	$f18, $f10, $f16
/* 091653 0x800FF2D4 4606903E */ c.le.s	$f18, $f6
/* 091654 0x800FF2D8 00000000 */ nop
/* 091655 0x800FF2DC 45000004 */ bc1f .L_800FF2F0
/* 091656 0x800FF2E0 00000000 */ nop
/* 091657 0x800FF2E4 E48E0000 */ swc1	$f14, 0X0($a0)
/* 091658 0x800FF2E8 03E00008 */ jr	$ra
/* 091659 0x800FF2EC 24020001 */ li	$v0, 1
.L_800FF2F0:
/* 091660 0x800FF2F0 03E00008 */ jr	$ra
/* 091661 0x800FF2F4 00000000 */ nop
)

#endif

#ifdef NONMATCHING

UNK_RET func_800FF2F8() {

}

#else

GLOBAL_ASM(
glabel func_800FF2F8
/* 091662 0x800FF2F8 44856000 */ mtc1	$a1, $f12
/* 091663 0x800FF2FC 44867000 */ mtc1	$a2, $f14
/* 091664 0x800FF300 AFA7000C */ sw	$a3, 0XC($sp)
/* 091665 0x800FF304 C4800000 */ lwc1	$f0, 0X0($a0)
/* 091666 0x800FF308 C7A2000C */ lwc1	$f2, 0XC($sp)
/* 091667 0x800FF30C 460C003E */ c.le.s	$f0, $f12
/* 091668 0x800FF310 00000000 */ nop
/* 091669 0x800FF314 45000003 */ bc1f .L_800FF324
/* 091670 0x800FF318 00000000 */ nop
/* 091671 0x800FF31C 10000001 */ b	.L_800FF324
/* 091672 0x800FF320 46007086 */ mov.s	$f2, $f14
.L_800FF324:
/* 091673 0x800FF324 44807000 */ mtc1	$zero, $f14
/* 091674 0x800FF328 00000000 */ nop
/* 091675 0x800FF32C 460E1032 */ c.eq.s	$f2, $f14
/* 091676 0x800FF330 00000000 */ nop
/* 091677 0x800FF334 45030012 */ bc1tl .L_800FF380
/* 091678 0x800FF338 46006032 */ c.eq.s	$f12, $f0
/* 091679 0x800FF33C 4600603C */ c.lt.s	$f12, $f0
/* 091680 0x800FF340 24020001 */ li	$v0, 1
/* 091681 0x800FF344 45020003 */ bc1fl .L_800FF354
/* 091682 0x800FF348 46020100 */ add.s	$f4, $f0, $f2
/* 091683 0x800FF34C 46001087 */ neg.s	$f2, $f2
/* 091684 0x800FF350 46020100 */ add.s	$f4, $f0, $f2
.L_800FF354:
/* 091685 0x800FF354 E4840000 */ swc1	$f4, 0X0($a0)
/* 091686 0x800FF358 C4860000 */ lwc1	$f6, 0X0($a0)
/* 091687 0x800FF35C 460C3201 */ sub.s	$f8, $f6, $f12
/* 091688 0x800FF360 46024282 */ mul.s	$f10, $f8, $f2
/* 091689 0x800FF364 460A703E */ c.le.s	$f14, $f10
/* 091690 0x800FF368 00000000 */ nop
/* 091691 0x800FF36C 4502000A */ bc1fl .L_800FF398
/* 091692 0x800FF370 00001025 */ move	$v0, $zero
/* 091693 0x800FF374 03E00008 */ jr	$ra
/* 091694 0x800FF378 E48C0000 */ swc1	$f12, 0X0($a0)
/* 091695 0x800FF37C 46006032 */ c.eq.s	$f12, $f0
.L_800FF380:
/* 091696 0x800FF380 00000000 */ nop
/* 091697 0x800FF384 45020004 */ bc1fl .L_800FF398
/* 091698 0x800FF388 00001025 */ move	$v0, $zero
/* 091699 0x800FF38C 03E00008 */ jr	$ra
/* 091700 0x800FF390 24020001 */ li	$v0, 1
/* 091701 0x800FF394 00001025 */ move	$v0, $zero
.L_800FF398:
/* 091702 0x800FF398 03E00008 */ jr	$ra
/* 091703 0x800FF39C 00000000 */ nop
)

#endif

#ifdef NONMATCHING

UNK_RET func_800FF3A0() {

}

#else

GLOBAL_ASM(
glabel func_800FF3A0
/* 091704 0x800FF3A0 3C014270 */ lui	$at, 0x4270
/* 091705 0x800FF3A4 27BDFFE8 */ addiu	$sp, $sp, -24
/* 091706 0x800FF3A8 44817000 */ mtc1	$at, $f14
/* 091707 0x800FF3AC AFBF0014 */ sw	$ra, 0X14($sp)
/* 091708 0x800FF3B0 80CE0014 */ lb	$t6, 0X14($a2)
/* 091709 0x800FF3B4 80CF0015 */ lb	$t7, 0X15($a2)
/* 091710 0x800FF3B8 44808000 */ mtc1	$zero, $f16
/* 091711 0x800FF3BC 448E2000 */ mtc1	$t6, $f4
/* 091712 0x800FF3C0 448F3000 */ mtc1	$t7, $f6
/* 091713 0x800FF3C4 468020A0 */ cvt.s.w	$f2, $f4
/* 091714 0x800FF3C8 46803320 */ cvt.s.w	$f12, $f6
/* 091715 0x800FF3CC 46021202 */ mul.s	$f8, $f2, $f2
/* 091716 0x800FF3D0 00000000 */ nop
/* 091717 0x800FF3D4 460C6282 */ mul.s	$f10, $f12, $f12
/* 091718 0x800FF3D8 460A4000 */ add.s	$f0, $f8, $f10
/* 091719 0x800FF3DC 46000004 */ sqrt.s	$f0, $f0
/* 091720 0x800FF3E0 4600703C */ c.lt.s	$f14, $f0
/* 091721 0x800FF3E4 00000000 */ nop
/* 091722 0x800FF3E8 45000003 */ bc1f .L_800FF3F8
/* 091723 0x800FF3EC 00000000 */ nop
/* 091724 0x800FF3F0 10000002 */ b	.L_800FF3FC
/* 091725 0x800FF3F4 E48E0000 */ swc1	$f14, 0X0($a0)
.L_800FF3F8:
/* 091726 0x800FF3F8 E4800000 */ swc1	$f0, 0X0($a0)
.L_800FF3FC:
/* 091727 0x800FF3FC 4600803C */ c.lt.s	$f16, $f0
/* 091728 0x800FF400 00000000 */ nop
/* 091729 0x800FF404 4502000E */ bc1fl .L_800FF440
/* 091730 0x800FF408 A4A00000 */ sh	$zero, 0X0($a1)
/* 091731 0x800FF40C 80D80002 */ lb	$t8, 0X2($a2)
/* 091732 0x800FF410 80D90003 */ lb	$t9, 0X3($a2)
/* 091733 0x800FF414 AFA5001C */ sw	$a1, 0X1C($sp)
/* 091734 0x800FF418 44989000 */ mtc1	$t8, $f18
/* 091735 0x800FF41C 44992000 */ mtc1	$t9, $f4
/* 091736 0x800FF420 468090A0 */ cvt.s.w	$f2, $f18
/* 091737 0x800FF424 46802320 */ cvt.s.w	$f12, $f4
/* 091738 0x800FF428 0C060040 */ jal	func_80180100
/* 091739 0x800FF42C 46001387 */ neg.s	$f14, $f2
/* 091740 0x800FF430 8FA5001C */ lw	$a1, 0X1C($sp)
/* 091741 0x800FF434 10000002 */ b	.L_800FF440
/* 091742 0x800FF438 A4A20000 */ sh	$v0, 0X0($a1)
/* 091743 0x800FF43C A4A00000 */ sh	$zero, 0X0($a1)
.L_800FF440:
/* 091744 0x800FF440 8FBF0014 */ lw	$ra, 0X14($sp)
/* 091745 0x800FF444 27BD0018 */ addiu	$sp, $sp, 24
/* 091746 0x800FF448 03E00008 */ jr	$ra
/* 091747 0x800FF44C 00000000 */ nop
)

#endif

s16 func_800FF450(s16 a0, s16 a1) {
    return (s16)(func_80086FDC() * a1) + a0;
}

s16 func_800FF4A4(s16 a0, s16 a1, s16 a2) {
    return (s16)(func_80086FDC() * a2) * a1 + a0;
}

UNK_RET func_800FF50C(z_Vector3D* dst, z_Vector3D* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET func_800FF52C(z_Vector3Ds16* dst, z_Vector3Ds16* src) {
    s16 x = src->x;
    s16 y = src->y;
    s16 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET func_800FF54C(z_Vector3D* dst, z_Vector3Ds16* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET func_800FF584(z_Vector3Ds16* dst, z_Vector3D* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET func_800FF5BC(z_Vector3D* a0, z_Vector3D* a1, z_Vector3D* a2) {
    a2->x = a0->x + a1->x;
    a2->y = a0->y + a1->y;
    a2->z = a0->z + a1->z;
}

UNK_RET func_800FF5F4(z_Vector3D* a0, z_Vector3D* a1, z_Vector3D* a2) {
    a2->x = a0->x - a1->x;
    a2->y = a0->y - a1->y;
    a2->z = a0->z - a1->z;
}

UNK_RET func_800FF62C(z_Vector3D* a0, z_Vector3Ds16* a1, z_Vector3Ds16* a2) {
    a0->x = a1->x - a2->x;
    a0->y = a1->y - a2->y;
    a0->z = a1->z - a2->z;
}

UNK_RET func_800FF688(z_Vector3D* a0, f32 a1) {
    a0->x *= a1;
    a0->y *= a1;
    a0->z *= a1;
}

UNK_RET func_800FF6C4(z_Vector3D* a0, f32 a1, z_Vector3D* a2) {
    a2->x = a0->x * a1;
    a2->y = a0->y * a1;
    a2->z = a0->z * a1;
}

UNK_RET func_800FF6F8(z_Vector3D* a0, z_Vector3D* a1, f32 a2, z_Vector3D* a3) {
    a3->x = (a1->x - a0->x) * a2 + a0->x;
    a3->y = (a1->y - a0->y) * a2 + a0->y;
    a3->z = (a1->z - a0->z) * a2 + a0->z;
}

UNK_RET func_800FF750(z_Vector3D* a0, z_Vector3D* a1, f32 a2, z_Vector3D* a3) {
    a3->x = a1->x * a2 + a0->x;
    a3->y = a1->y * a2 + a0->y;
    a3->z = a1->z * a2 + a0->z;
}

UNK_RET func_800FF79C(z_Vector3D* a0, f32 a1, z_Vector3D* a2) {
    a2->x = func_801795C0(a1) + a0->x;
    a2->y = func_801795C0(a1) + a0->y;
    a2->z = func_801795C0(a1) + a0->z;
}

void func_800FF810(z_Vector3D* a0, z_Vector3D* a1, f32 a2, z_Vector3D* a3) {
    f32 f0 = func_800FF8D4(a0, a1, a3);
    f32 f2;

    if (f0 == 0) {
        return;
    }

    f2 = a2 / f0;

    a3->x *= f2;
    a3->y *= f2;
    a3->z *= f2;
}

f32 func_800FF884(z_Vector3D* a0, z_Vector3D* a1) {
    z_Vector3D sp1C;
    func_800FF5F4(a1, a0, &sp1C);
    return sqrtf((sp1C.x * sp1C.x) + (sp1C.y * sp1C.y) + (sp1C.z * sp1C.z));
}

f32 func_800FF8D4(z_Vector3D* a0, z_Vector3D* a1, z_Vector3D* a2) {
    func_800FF5F4(a1, a0, a2);
    return sqrtf((a2->x * a2->x) + (a2->y * a2->y) + (a2->z * a2->z));
}

f32 func_800FF92C(z_Vector3D* a0, z_Vector3D* a1) {
    f32 dx = a1->x - a0->x;
    f32 dz = a1->z - a0->z;
    return sqrtf((dx * dx) + (dz * dz));
}

f32 func_800FF960(z_Vector3D* a0, z_Vector3D* a1, f32* a2, f32* a3) {
    *a2 = a1->x - a0->x;
    *a3 = a1->z - a0->z;
    return sqrtf((*a2 * *a2) + (*a3 * *a3));
}

#ifdef NONMATCHING

UNK_RET func_800FF9A4(z_Vector3D* a0, z_Vector3D* a1, f32 a2) {
    f32 sp24;
    f32 sp20;
    f32 f0 = func_800FF960(a1, a0, &sp24, &sp20);
    f32 f2 = f0 - a2;

    if ((f0 >= a2) && (f2 != 0)) {
        f2 /= f0;
    } else {
        f2 = 0;
    }

    a0->x = a1->x + sp24 * f2;
    a0->z = a1->z + sp20 * f2;
}

#else

GLOBAL_ASM(
glabel func_800FF9A4
/* 092089 0x800FF9A4 27BDFFD8 */ addiu	$sp, $sp, -40
/* 092090 0x800FF9A8 AFA5002C */ sw	$a1, 0X2C($sp)
/* 092091 0x800FF9AC 00802825 */ move	$a1, $a0
/* 092092 0x800FF9B0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 092093 0x800FF9B4 AFA40028 */ sw	$a0, 0X28($sp)
/* 092094 0x800FF9B8 AFA60030 */ sw	$a2, 0X30($sp)
/* 092095 0x800FF9BC 8FA4002C */ lw	$a0, 0X2C($sp)
/* 092096 0x800FF9C0 27A60024 */ addiu	$a2, $sp, 36
/* 092097 0x800FF9C4 27A70020 */ addiu	$a3, $sp, 32
/* 092098 0x800FF9C8 0C03FE58 */ jal	func_800FF960
/* 092099 0x800FF9CC AFA50028 */ sw	$a1, 0X28($sp)
/* 092100 0x800FF9D0 C7A20030 */ lwc1	$f2, 0X30($sp)
/* 092101 0x800FF9D4 44807000 */ mtc1	$zero, $f14
/* 092102 0x800FF9D8 8FA2002C */ lw	$v0, 0X2C($sp)
/* 092103 0x800FF9DC 4602003C */ c.lt.s	$f0, $f2
/* 092104 0x800FF9E0 8FA50028 */ lw	$a1, 0X28($sp)
/* 092105 0x800FF9E4 C7A60024 */ lwc1	$f6, 0X24($sp)
/* 092106 0x800FF9E8 46020301 */ sub.s	$f12, $f0, $f2
/* 092107 0x800FF9EC 45020004 */ bc1fl .L_800FFA00
/* 092108 0x800FF9F0 460E6032 */ c.eq.s	$f12, $f14
/* 092109 0x800FF9F4 44806000 */ mtc1	$zero, $f12
/* 092110 0x800FF9F8 00000000 */ nop
/* 092111 0x800FF9FC 460E6032 */ c.eq.s	$f12, $f14
.L_800FFA00:
/* 092112 0x800FFA00 00000000 */ nop
/* 092113 0x800FFA04 45020004 */ bc1fl .L_800FFA18
/* 092114 0x800FFA08 46006083 */ div.s	$f2, $f12, $f0
/* 092115 0x800FFA0C 10000002 */ b	.L_800FFA18
/* 092116 0x800FFA10 46007086 */ mov.s	$f2, $f14
/* 092117 0x800FFA14 46006083 */ div.s	$f2, $f12, $f0
.L_800FFA18:
/* 092118 0x800FFA18 46023202 */ mul.s	$f8, $f6, $f2
/* 092119 0x800FFA1C C4440000 */ lwc1	$f4, 0X0($v0)
/* 092120 0x800FFA20 46006006 */ mov.s	$f0, $f12
/* 092121 0x800FFA24 46082280 */ add.s	$f10, $f4, $f8
/* 092122 0x800FFA28 E4AA0000 */ swc1	$f10, 0X0($a1)
/* 092123 0x800FFA2C C7B20020 */ lwc1	$f18, 0X20($sp)
/* 092124 0x800FFA30 C4500008 */ lwc1	$f16, 0X8($v0)
/* 092125 0x800FFA34 46029182 */ mul.s	$f6, $f18, $f2
/* 092126 0x800FFA38 46068100 */ add.s	$f4, $f16, $f6
/* 092127 0x800FFA3C E4A40008 */ swc1	$f4, 0X8($a1)
/* 092128 0x800FFA40 8FBF0014 */ lw	$ra, 0X14($sp)
/* 092129 0x800FFA44 03E00008 */ jr	$ra
/* 092130 0x800FFA48 27BD0028 */ addiu	$sp, $sp, 40
)

#endif

f32 func_800FFA4C(z_Vector3D* a0, z_Vector3D* a1) {
    return a1->y - a0->y;
}

UNK_TYPE func_800FFA60(z_Vector3D* a0, z_Vector3D* a1) {
    f32 f14 = a1->x - a0->x;
    f32 f12 = a1->z - a0->z;
    return func_80180100(f12, f14);
}

UNK_TYPE func_800FFA94(z_Vector3D* a0, z_Vector3D* a1) {
    return func_80180100(func_800FF92C(a0, a1), a0->y - a1->y);
}

void func_800FFADC(z_Actor* a0, z_ActorCompInitEntry* a1) {
    do {
        D_801BE960[a1->type]((u8*)a0, a1);
    } while ((a1++)->cont);
}

UNK_RET func_800FFB54(u8* a0, z_ActorCompInitEntry* a1) {
    *(u8*)(a0 + a1->offset) = (u8)(a1->value);
}

UNK_RET func_800FFB70(u8* a0, z_ActorCompInitEntry* a1) {
    *(u8*)(a0 + a1->offset) = (u8)(a1->value);
}

UNK_RET func_800FFB8C(u8* a0, z_ActorCompInitEntry* a1) {
    *(u16*)(a0 + a1->offset) = (u16)(a1->value);
}

UNK_RET func_800FFBA8(u8* a0, z_ActorCompInitEntry* a1) {
    *(u16*)(a0 + a1->offset) = (u16)(a1->value);
}

UNK_RET func_800FFBC4(u8* a0, z_ActorCompInitEntry* a1) {
    *(u32*)(a0 + a1->offset) = (u32)(a1->value);
}

UNK_RET func_800FFBE0(u8* a0, z_ActorCompInitEntry* a1) {
    *(u32*)(a0 + a1->offset) = (u32)(a1->value);
}

UNK_RET func_800FFBFC(u8* a0, z_ActorCompInitEntry* a1) {
    *(f32*)(a0 + a1->offset) = (f32)(a1->value);
}

UNK_RET func_800FFC20(u8* a0, z_ActorCompInitEntry* a1) {
    *(f32*)(a0 + a1->offset) = (f32)(a1->value) / 1000;
}

UNK_RET func_800FFC50(u8* a0, z_ActorCompInitEntry* a1) {
    z_Vector3D* v0 = (z_Vector3D*)(a0 + a1->offset);
    f32 f0 = (f32)(a1->value);

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

UNK_RET func_800FFC7C(u8* a0, z_ActorCompInitEntry* a1) {
    z_Vector3D* v0 = (z_Vector3D*)(a0 + a1->offset);
    f32 f0 = (f32)(a1->value) / 1000;

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

UNK_RET func_800FFCB4(u8* a0, z_ActorCompInitEntry* a1) {
    z_Vector3Ds16* v0 = (z_Vector3Ds16*)(a0 + a1->offset);
    s16 v1 = (s16)(a1->value);

    v0->z = v1;
    v0->y = v1;
    v0->x = v1;
}

f32 func_800FFCD8(f32* a0, f32 a1, f32 a2, f32 a3, f32 a4) {
    f32 f0;

    if (*a0 != a1) {
        f0 = (a1 - *a0) * a2;

        if ((f0 >= a4) || (f0 <= -a4)) {
            if (f0 > a3) {
                f0 = a3;
            }

            if (f0 < -a3) {
                f0 = -a3;
            }

            *a0 += f0;
        } else {
            if (f0 > 0) {
                if (f0 < a4) {
                    *a0 += a4;

                    if (a1 < *a0) {
                        *a0 = a1;
                    }
                }
            } else {
                if (-a4 < f0) {
                    *a0 += -a4;

                    if (*a0 < a1) {
                        *a0 = a1;
                    }
                }
            }
        }
    }

    return fabsf(a1 - *a0);
}

UNK_RET func_800FFDF8(f32* a0, f32 a1, f32 a2, f32 a3) {
    f32 f2;

    if (*a0 != a1) {
        f2 = (a1 - *a0) * a2;

        if (f2 > a3) {
            f2 = a3;
        } else if (f2 < -a3) {
            f2 = -a3;
        }

        *a0 += f2;
    }
}

void func_800FFE68(f32* a0, f32 a1, f32 a2) {
  f32 f0 = *a0 * a1;

  if (a2 < f0) {
    f0 = a2;
  } else if (f0 < -a2) {
    f0 = -a2;
  }

  *a0 = *a0 - f0;
}

#ifdef NONMATCHING

s16 func_800FFEBC(s16* a0, s16 a1, s16 a2, s16 a3, s16 a4) {

}

#else

GLOBAL_ASM(
glabel func_800FFEBC
/* 092415 0x800FFEBC AFA50004 */ sw	$a1, 0X4($sp)
/* 092416 0x800FFEC0 AFA60008 */ sw	$a2, 0X8($sp)
/* 092417 0x800FFEC4 00063400 */ sll	$a2, $a2, 16
/* 092418 0x800FFEC8 00052C00 */ sll	$a1, $a1, 16
/* 092419 0x800FFECC 00052C03 */ sra	$a1, $a1, 16
/* 092420 0x800FFED0 00063403 */ sra	$a2, $a2, 16
/* 092421 0x800FFED4 AFA7000C */ sw	$a3, 0XC($sp)
/* 092422 0x800FFED8 84880000 */ lh	$t0, 0X0($a0)
/* 092423 0x800FFEDC 87A90012 */ lh	$t1, 0X12($sp)
/* 092424 0x800FFEE0 00A81823 */ subu	$v1, $a1, $t0
/* 092425 0x800FFEE4 00031C00 */ sll	$v1, $v1, 16
/* 092426 0x800FFEE8 10A80038 */ beq	$a1, $t0, .L_800FFFCC
/* 092427 0x800FFEEC 00031C03 */ sra	$v1, $v1, 16
/* 092428 0x800FFEF0 0066001A */ div	$zero, $v1, $a2
/* 092429 0x800FFEF4 14C00002 */ bnez	$a2, .L_800FFF00
/* 092430 0x800FFEF8 00000000 */ nop
/* 092431 0x800FFEFC 0007000D */ break	0x00007
.L_800FFF00:
/* 092432 0x800FFF00 2401FFFF */ li	$at, -1
/* 092433 0x800FFF04 14C10004 */ bne	$a2, $at, .L_800FFF18
/* 092434 0x800FFF08 3C018000 */ lui	$at, 0x8000
/* 092435 0x800FFF0C 14610002 */ bne	$v1, $at, .L_800FFF18
/* 092436 0x800FFF10 00000000 */ nop
/* 092437 0x800FFF14 0006000D */ break	0x00006
.L_800FFF18:
/* 092438 0x800FFF18 00003812 */ mflo	$a3
/* 092439 0x800FFF1C 00075400 */ sll	$t2, $a3, 16
/* 092440 0x800FFF20 000A5403 */ sra	$t2, $t2, 16
/* 092441 0x800FFF24 00071400 */ sll	$v0, $a3, 16
/* 092442 0x800FFF28 012A082A */ slt	$at, $t1, $t2
/* 092443 0x800FFF2C 14200005 */ bnez	$at, .L_800FFF44
/* 092444 0x800FFF30 00021403 */ sra	$v0, $v0, 16
/* 092445 0x800FFF34 00097023 */ negu	$t6, $t1
/* 092446 0x800FFF38 014E082A */ slt	$at, $t2, $t6
/* 092447 0x800FFF3C 1020000F */ beqz	$at, .L_800FFF7C
/* 092448 0x800FFF40 00000000 */ nop
.L_800FFF44:
/* 092449 0x800FFF44 87AF000E */ lh	$t7, 0XE($sp)
/* 092450 0x800FFF48 87A5000E */ lh	$a1, 0XE($sp)
/* 092451 0x800FFF4C 01EA082A */ slt	$at, $t7, $t2
/* 092452 0x800FFF50 10200002 */ beqz	$at, .L_800FFF5C
/* 092453 0x800FFF54 00052823 */ negu	$a1, $a1
/* 092454 0x800FFF58 01E01025 */ move	$v0, $t7
.L_800FFF5C:
/* 092455 0x800FFF5C 0045082A */ slt	$at, $v0, $a1
/* 092456 0x800FFF60 50200004 */ beqzl	$at, .L_800FFF74
/* 092457 0x800FFF64 0102C021 */ addu	$t8, $t0, $v0
/* 092458 0x800FFF68 00051400 */ sll	$v0, $a1, 16
/* 092459 0x800FFF6C 00021403 */ sra	$v0, $v0, 16
/* 092460 0x800FFF70 0102C021 */ addu	$t8, $t0, $v0
.L_800FFF74:
/* 092461 0x800FFF74 10000015 */ b	.L_800FFFCC
/* 092462 0x800FFF78 A4980000 */ sh	$t8, 0X0($a0)
.L_800FFF7C:
/* 092463 0x800FFF7C 0460000B */ bltz	$v1, .L_800FFFAC
/* 092464 0x800FFF80 01097823 */ subu	$t7, $t0, $t1
/* 092465 0x800FFF84 0109C821 */ addu	$t9, $t0, $t1
/* 092466 0x800FFF88 A4990000 */ sh	$t9, 0X0($a0)
/* 092467 0x800FFF8C 848B0000 */ lh	$t3, 0X0($a0)
/* 092468 0x800FFF90 00AB6023 */ subu	$t4, $a1, $t3
/* 092469 0x800FFF94 000C6C00 */ sll	$t5, $t4, 16
/* 092470 0x800FFF98 000D7403 */ sra	$t6, $t5, 16
/* 092471 0x800FFF9C 5DC0000C */ bgtzl	$t6, .L_800FFFD0
/* 092472 0x800FFFA0 00601025 */ move	$v0, $v1
/* 092473 0x800FFFA4 10000009 */ b	.L_800FFFCC
/* 092474 0x800FFFA8 A4850000 */ sh	$a1, 0X0($a0)
.L_800FFFAC:
/* 092475 0x800FFFAC A48F0000 */ sh	$t7, 0X0($a0)
/* 092476 0x800FFFB0 84980000 */ lh	$t8, 0X0($a0)
/* 092477 0x800FFFB4 00B8C823 */ subu	$t9, $a1, $t8
/* 092478 0x800FFFB8 00195C00 */ sll	$t3, $t9, 16
/* 092479 0x800FFFBC 000B6403 */ sra	$t4, $t3, 16
/* 092480 0x800FFFC0 05820003 */ bltzl	$t4, .L_800FFFD0
/* 092481 0x800FFFC4 00601025 */ move	$v0, $v1
/* 092482 0x800FFFC8 A4850000 */ sh	$a1, 0X0($a0)
.L_800FFFCC:
/* 092483 0x800FFFCC 00601025 */ move	$v0, $v1
.L_800FFFD0:
/* 092484 0x800FFFD0 03E00008 */ jr	$ra
/* 092485 0x800FFFD4 00000000 */ nop
)

#endif

void func_800FFFD8(s16* a0, s16 a1, s16 a2, s16 a3) {
    s16 v0 = a1 - *a0;
    v0 /= a2;

    if (v0 > a3) {
        *a0 += a3;
        return;
    }

    if (v0 < -a3) {
        *a0 -= a3;
        return;
    }

    *a0 += v0;
}

UNK_RET func_8010007C(u8* a0, u8* a1) {
    a0[0] = a1[0];
    a0[1] = a1[1];
    a0[2] = a1[2];
    a0[3] = a1[3];
}

UNK_RET func_801000A4(u16 a0) {
    func_8019F0C8(a0);
}

UNK_RET func_801000CC(u16 a0) {
    func_8019F128(a0);
}

UNK_RET func_801000F4(UNK_TYPE a0, u16 a1) {
    func_8019F1C0(a0, a1);
}

void func_8010011C(z_Vector3D* a0, s16 a1, z_Vector3D* a2, z_Vector3D* a3) {
    f32 sp1C;
    f32 f0;

    sp1C = func_800FED44(a1);
    f0 = func_800FED84(a1);
    a3->x = a0->x + (a2->x * sp1C + a2->z * f0);
    a3->y = a0->y + a2->y;
    a3->z = a0->z + (a2->z * sp1C - a2->x * f0);
}

#ifdef NONMATCHING

void func_801001B8(u8* a0, u8* a1, f32 a2, u8* a3) {
    // XXX regalloc is slightly off
    a3[0] = (f32)a0[0] + ((f32)a1[0] - (f32)a0[0]) * a2;
    a3[1] = (f32)a0[1] + ((f32)a1[1] - (f32)a0[1]) * a2;
    a3[2] = (f32)a0[2] + ((f32)a1[2] - (f32)a0[2]) * a2;
}

#else

GLOBAL_ASM(
glabel func_801001B8
/* 092606 0x801001B8 44866000 */ mtc1	$a2, $f12
/* 092607 0x801001BC 00000000 */ nop
/* 092608 0x801001C0 908E0000 */ lbu	$t6, 0X0($a0)
/* 092609 0x801001C4 3C014F80 */ lui	$at, 0x4F80
/* 092610 0x801001C8 448E2000 */ mtc1	$t6, $f4
/* 092611 0x801001CC 05C10004 */ bgez	$t6, .L_801001E0
/* 092612 0x801001D0 46802020 */ cvt.s.w	$f0, $f4
/* 092613 0x801001D4 44813000 */ mtc1	$at, $f6
/* 092614 0x801001D8 00000000 */ nop
/* 092615 0x801001DC 46060000 */ add.s	$f0, $f0, $f6
.L_801001E0:
/* 092616 0x801001E0 90AF0000 */ lbu	$t7, 0X0($a1)
/* 092617 0x801001E4 3C014F80 */ lui	$at, 0x4F80
/* 092618 0x801001E8 448F4000 */ mtc1	$t7, $f8
/* 092619 0x801001EC 05E10004 */ bgez	$t7, .L_80100200
/* 092620 0x801001F0 468042A0 */ cvt.s.w	$f10, $f8
/* 092621 0x801001F4 44818000 */ mtc1	$at, $f16
/* 092622 0x801001F8 00000000 */ nop
/* 092623 0x801001FC 46105280 */ add.s	$f10, $f10, $f16
.L_80100200:
/* 092624 0x80100200 46005481 */ sub.s	$f18, $f10, $f0
/* 092625 0x80100204 24190001 */ li	$t9, 1
/* 092626 0x80100208 3C014F00 */ lui	$at, 0x4F00
/* 092627 0x8010020C 460C9102 */ mul.s	$f4, $f18, $f12
/* 092628 0x80100210 46002180 */ add.s	$f6, $f4, $f0
/* 092629 0x80100214 4458F800 */ cfc1	$t8, $31
/* 092630 0x80100218 44D9F800 */ ctc1	$t9, $31
/* 092631 0x8010021C 00000000 */ nop
/* 092632 0x80100220 46003224 */ cvt.w.s	$f8, $f6
/* 092633 0x80100224 4459F800 */ cfc1	$t9, $31
/* 092634 0x80100228 00000000 */ nop
/* 092635 0x8010022C 33390078 */ andi	$t9, $t9, 0X78
/* 092636 0x80100230 53200013 */ beqzl	$t9, .L_80100280
/* 092637 0x80100234 44194000 */ mfc1	$t9, $f8
/* 092638 0x80100238 44814000 */ mtc1	$at, $f8
/* 092639 0x8010023C 24190001 */ li	$t9, 1
/* 092640 0x80100240 46083201 */ sub.s	$f8, $f6, $f8
/* 092641 0x80100244 44D9F800 */ ctc1	$t9, $31
/* 092642 0x80100248 00000000 */ nop
/* 092643 0x8010024C 46004224 */ cvt.w.s	$f8, $f8
/* 092644 0x80100250 4459F800 */ cfc1	$t9, $31
/* 092645 0x80100254 00000000 */ nop
/* 092646 0x80100258 33390078 */ andi	$t9, $t9, 0X78
/* 092647 0x8010025C 17200005 */ bnez	$t9, .L_80100274
/* 092648 0x80100260 00000000 */ nop
/* 092649 0x80100264 44194000 */ mfc1	$t9, $f8
/* 092650 0x80100268 3C018000 */ lui	$at, 0x8000
/* 092651 0x8010026C 10000007 */ b	.L_8010028C
/* 092652 0x80100270 0321C825 */ or	$t9, $t9, $at
.L_80100274:
/* 092653 0x80100274 10000005 */ b	.L_8010028C
/* 092654 0x80100278 2419FFFF */ li	$t9, -1
/* 092655 0x8010027C 44194000 */ mfc1	$t9, $f8
.L_80100280:
/* 092656 0x80100280 00000000 */ nop
/* 092657 0x80100284 0720FFFB */ bltz	$t9, .L_80100274
/* 092658 0x80100288 00000000 */ nop
.L_8010028C:
/* 092659 0x8010028C A0F90000 */ sb	$t9, 0X0($a3)
/* 092660 0x80100290 90880001 */ lbu	$t0, 0X1($a0)
/* 092661 0x80100294 44D8F800 */ ctc1	$t8, $31
/* 092662 0x80100298 3C014F80 */ lui	$at, 0x4F80
/* 092663 0x8010029C 44888000 */ mtc1	$t0, $f16
/* 092664 0x801002A0 05010004 */ bgez	$t0, .L_801002B4
/* 092665 0x801002A4 46808020 */ cvt.s.w	$f0, $f16
/* 092666 0x801002A8 44815000 */ mtc1	$at, $f10
/* 092667 0x801002AC 00000000 */ nop
/* 092668 0x801002B0 460A0000 */ add.s	$f0, $f0, $f10
.L_801002B4:
/* 092669 0x801002B4 90A90001 */ lbu	$t1, 0X1($a1)
/* 092670 0x801002B8 3C014F80 */ lui	$at, 0x4F80
/* 092671 0x801002BC 44899000 */ mtc1	$t1, $f18
/* 092672 0x801002C0 05210004 */ bgez	$t1, .L_801002D4
/* 092673 0x801002C4 46809120 */ cvt.s.w	$f4, $f18
/* 092674 0x801002C8 44813000 */ mtc1	$at, $f6
/* 092675 0x801002CC 00000000 */ nop
/* 092676 0x801002D0 46062100 */ add.s	$f4, $f4, $f6
.L_801002D4:
/* 092677 0x801002D4 46002201 */ sub.s	$f8, $f4, $f0
/* 092678 0x801002D8 240B0001 */ li	$t3, 1
/* 092679 0x801002DC 3C014F00 */ lui	$at, 0x4F00
/* 092680 0x801002E0 460C4402 */ mul.s	$f16, $f8, $f12
/* 092681 0x801002E4 46008280 */ add.s	$f10, $f16, $f0
/* 092682 0x801002E8 444AF800 */ cfc1	$t2, $31
/* 092683 0x801002EC 44CBF800 */ ctc1	$t3, $31
/* 092684 0x801002F0 00000000 */ nop
/* 092685 0x801002F4 460054A4 */ cvt.w.s	$f18, $f10
/* 092686 0x801002F8 444BF800 */ cfc1	$t3, $31
/* 092687 0x801002FC 00000000 */ nop
/* 092688 0x80100300 316B0078 */ andi	$t3, $t3, 0X78
/* 092689 0x80100304 51600013 */ beqzl	$t3, .L_80100354
/* 092690 0x80100308 440B9000 */ mfc1	$t3, $f18
/* 092691 0x8010030C 44819000 */ mtc1	$at, $f18
/* 092692 0x80100310 240B0001 */ li	$t3, 1
/* 092693 0x80100314 46125481 */ sub.s	$f18, $f10, $f18
/* 092694 0x80100318 44CBF800 */ ctc1	$t3, $31
/* 092695 0x8010031C 00000000 */ nop
/* 092696 0x80100320 460094A4 */ cvt.w.s	$f18, $f18
/* 092697 0x80100324 444BF800 */ cfc1	$t3, $31
/* 092698 0x80100328 00000000 */ nop
/* 092699 0x8010032C 316B0078 */ andi	$t3, $t3, 0X78
/* 092700 0x80100330 15600005 */ bnez	$t3, .L_80100348
/* 092701 0x80100334 00000000 */ nop
/* 092702 0x80100338 440B9000 */ mfc1	$t3, $f18
/* 092703 0x8010033C 3C018000 */ lui	$at, 0x8000
/* 092704 0x80100340 10000007 */ b	.L_80100360
/* 092705 0x80100344 01615825 */ or	$t3, $t3, $at
.L_80100348:
/* 092706 0x80100348 10000005 */ b	.L_80100360
/* 092707 0x8010034C 240BFFFF */ li	$t3, -1
/* 092708 0x80100350 440B9000 */ mfc1	$t3, $f18
.L_80100354:
/* 092709 0x80100354 00000000 */ nop
/* 092710 0x80100358 0560FFFB */ bltz	$t3, .L_80100348
/* 092711 0x8010035C 00000000 */ nop
.L_80100360:
/* 092712 0x80100360 A0EB0001 */ sb	$t3, 0X1($a3)
/* 092713 0x80100364 908C0002 */ lbu	$t4, 0X2($a0)
/* 092714 0x80100368 44CAF800 */ ctc1	$t2, $31
/* 092715 0x8010036C 3C014F80 */ lui	$at, 0x4F80
/* 092716 0x80100370 448C3000 */ mtc1	$t4, $f6
/* 092717 0x80100374 05810004 */ bgez	$t4, .L_80100388
/* 092718 0x80100378 46803020 */ cvt.s.w	$f0, $f6
/* 092719 0x8010037C 44812000 */ mtc1	$at, $f4
/* 092720 0x80100380 00000000 */ nop
/* 092721 0x80100384 46040000 */ add.s	$f0, $f0, $f4
.L_80100388:
/* 092722 0x80100388 90AD0002 */ lbu	$t5, 0X2($a1)
/* 092723 0x8010038C 3C014F80 */ lui	$at, 0x4F80
/* 092724 0x80100390 448D4000 */ mtc1	$t5, $f8
/* 092725 0x80100394 05A10004 */ bgez	$t5, .L_801003A8
/* 092726 0x80100398 46804420 */ cvt.s.w	$f16, $f8
/* 092727 0x8010039C 44815000 */ mtc1	$at, $f10
/* 092728 0x801003A0 00000000 */ nop
/* 092729 0x801003A4 460A8400 */ add.s	$f16, $f16, $f10
.L_801003A8:
/* 092730 0x801003A8 46008481 */ sub.s	$f18, $f16, $f0
/* 092731 0x801003AC 240F0001 */ li	$t7, 1
/* 092732 0x801003B0 3C014F00 */ lui	$at, 0x4F00
/* 092733 0x801003B4 460C9182 */ mul.s	$f6, $f18, $f12
/* 092734 0x801003B8 46003100 */ add.s	$f4, $f6, $f0
/* 092735 0x801003BC 444EF800 */ cfc1	$t6, $31
/* 092736 0x801003C0 44CFF800 */ ctc1	$t7, $31
/* 092737 0x801003C4 00000000 */ nop
/* 092738 0x801003C8 46002224 */ cvt.w.s	$f8, $f4
/* 092739 0x801003CC 444FF800 */ cfc1	$t7, $31
/* 092740 0x801003D0 00000000 */ nop
/* 092741 0x801003D4 31EF0078 */ andi	$t7, $t7, 0X78
/* 092742 0x801003D8 51E00013 */ beqzl	$t7, .L_80100428
/* 092743 0x801003DC 440F4000 */ mfc1	$t7, $f8
/* 092744 0x801003E0 44814000 */ mtc1	$at, $f8
/* 092745 0x801003E4 240F0001 */ li	$t7, 1
/* 092746 0x801003E8 46082201 */ sub.s	$f8, $f4, $f8
/* 092747 0x801003EC 44CFF800 */ ctc1	$t7, $31
/* 092748 0x801003F0 00000000 */ nop
/* 092749 0x801003F4 46004224 */ cvt.w.s	$f8, $f8
/* 092750 0x801003F8 444FF800 */ cfc1	$t7, $31
/* 092751 0x801003FC 00000000 */ nop
/* 092752 0x80100400 31EF0078 */ andi	$t7, $t7, 0X78
/* 092753 0x80100404 15E00005 */ bnez	$t7, .L_8010041C
/* 092754 0x80100408 00000000 */ nop
/* 092755 0x8010040C 440F4000 */ mfc1	$t7, $f8
/* 092756 0x80100410 3C018000 */ lui	$at, 0x8000
/* 092757 0x80100414 10000007 */ b	.L_80100434
/* 092758 0x80100418 01E17825 */ or	$t7, $t7, $at
.L_8010041C:
/* 092759 0x8010041C 10000005 */ b	.L_80100434
/* 092760 0x80100420 240FFFFF */ li	$t7, -1
/* 092761 0x80100424 440F4000 */ mfc1	$t7, $f8
.L_80100428:
/* 092762 0x80100428 00000000 */ nop
/* 092763 0x8010042C 05E0FFFB */ bltz	$t7, .L_8010041C
/* 092764 0x80100430 00000000 */ nop
.L_80100434:
/* 092765 0x80100434 44CEF800 */ ctc1	$t6, $31
/* 092766 0x80100438 A0EF0002 */ sb	$t7, 0X2($a3)
/* 092767 0x8010043C 00000000 */ nop
/* 092768 0x80100440 03E00008 */ jr	$ra
/* 092769 0x80100444 00000000 */ nop
)

#endif

f32 func_80100448(z_Vector3D* a0, z_Vector3D* a1, f32 a2) {
    z_Vector3D sp24;
    f32 f2;
    f32 f0;

    func_800FF5F4(a1, a0, &sp24);
    f0 = func_8017A6D4(&sp24);
    if (a2 < f0) {
        f2 = a2 / f0;
        f0 = f0 - a2;
        a0->x = a0->x + f2 * sp24.x;
        a0->y = a0->y + f2 * sp24.y;
        a0->z = a0->z + f2 * sp24.z;
    } else {
        func_800FF50C(a0, a1);
        f0 = 0;
    }

    return f0;
}

void func_801004FC(void) {}

UNK_TYPE func_80100504(u32 a0) {
    return(D_801F8180[(a0 << 4) >> 28] + (a0 & 0xFFFFFF)) + 0x80000000;
}

UNK_TYPE func_8010053C(u32 a0) {
    if ((a0 >> 28) == 0) {
        return a0;
    }

    return(D_801F8180[(a0 << 4) >> 28] + (a0 & 0xFFFFFF)) + 0x80000000;
}

UNK_TYPE func_80100584(UNK_TYPE a0) {
    if (a0 == 0) {
        return 0;
    } else {
        return a0 + 0x80000000;
    }
}

UNK_TYPE func_801005A0(UNK_TYPE a0) {
    if (a0 == 0) {
        return 0;
    } else {
        return a0 + 0x80000000;
    }
}