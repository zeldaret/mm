#include <ultra64.h>
#include <global.h>

s32 func_80080790(void* a0, void* a1, s32 a2) {
    u32 spPad;
    OSIoMesg sp96;
    OSMesgQueue sp72;
    OSMesg sp68;
    s32 ret;
    u32 s0 = D_80096B50;

    osInvalDCache(a1, a2);
    osCreateMesgQueue(&sp72, &sp68, 1);

    if (s0 != 0) {
        while (s0 < a2) {
            sp96.hdr.pri = 0;
            sp96.hdr.retQueue = &sp72;
            sp96.devAddr = (u32)a0;
            sp96.dramAddr = a1;
            sp96.size = s0;
            ret = osEPiStartDma(D_80096B40, &sp96, 0);
            if (ret) goto END;

            osRecvMesg(&sp72, NULL, 1);
            a2 -= s0;
            a0 = (u8*)a0 + s0;
            a1 = (u8*)a1 + s0;
        }
    }
    sp96.hdr.pri = 0;
    sp96.hdr.retQueue = &sp72;
    sp96.devAddr = (u32)a0;
    sp96.dramAddr = a1;
    sp96.size = (u32)a2;
    ret = osEPiStartDma(D_80096B40, &sp96, 0);
    if (ret) goto END;

    osRecvMesg(&sp72, NULL, 1);

    osInvalDCache(a1, a2);

END:
    return ret;
}

void func_800808D4(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    osEPiStartDma(pihandle, mb, direction);
}

DmadataEntry* func_800808F4(u32 a0) {
    DmadataEntry* curr;

    for (curr = dmadata; curr->vromEnd != 0; curr++) {
        if (a0 < curr->vromStart) continue;
        if (a0 >= curr->vromEnd) continue;

        return curr;
    }

    return NULL;
}

s32 func_80080950(u32 a0) {
    DmadataEntry* v0 = func_800808F4(a0);

    if (v0 != NULL) {
        if (v0->romEnd == 0) {
            return a0 + v0->romStart - v0->vromStart;
        }

        if (a0 == v0->vromStart) {
            return v0->romStart;
        }

        return -1;
    }

    return -1;
}

s32 func_800809BC(u32 a0) {
    DmadataEntry* v0 = func_800808F4(a0);

    if (v0 != NULL) {
		// TODO this uses t7 to shift instead of reusing v0
		return v0 - dmadata;
    }

    return -1;
}

UNK_TYPE* func_800809F4(u32 a0) {
    return &D_800981C0;
}

#ifdef NONMATCHING

void func_80080A08(s80080A08* a0) {
    UNK_TYPE sp52;
    UNK_TYPE sp48;
    UNK_TYPE sp44;
    UNK_TYPE sp40;
    UNK_TYPE sp36;
    UNK_TYPE sp32;
    s32 sp28;
    UNK_TYPE sp24;

    sp52 = (UNK_TYPE)a0->unk0;
    sp48 = (UNK_TYPE)a0->unk4;
    sp44 = a0->unk8;

    sp28 = func_800809BC(sp52);

    if ((sp28 >= 0) && (sp28 < D_8009B2BC)) {
        if (dmadata[sp28].romEnd == 0) {
            if (dmadata[sp28].vromEnd < (sp44 + sp52)) {
                func_80083E4C(&D_800981C4, 499);
            }
            func_80080790((u8*)((dmadata[sp28].romStart + sp52) - dmadata[sp28].vromStart), (u8*)sp48, sp44);
            return;
        }

        // TODO this part is arranged slightly different is ASM
        sp36 = dmadata[sp28].romEnd - dmadata[sp28].romStart;
        sp40 = dmadata[sp28].romStart;

        if (sp52 != dmadata[sp28].vromStart) {
            func_80083E4C(&D_800981D4, 518);
        }

        if (sp44 != (dmadata[sp28].vromEnd - dmadata[sp28].vromStart)) {
            func_80083E4C(&D_800981E4, 525);
        }

        osSetThreadPri(NULL, 10);
        func_80081178(sp40, sp48, sp36);
        osSetThreadPri(NULL, 17);
    } else {
        func_80083E4C(&D_800981F4, 558);
    }
}

#else

GLOBAL_ASM(
glabel func_80080A08
/* 000618 0x80080A08 27BDFFC8 */ addiu	$sp, $sp, -56
/* 000619 0x80080A0C AFBF0014 */ sw	$ra, 20($sp)
/* 000620 0x80080A10 00802825 */ move	$a1, $a0
/* 000621 0x80080A14 8CAE0004 */ lw	$t6, 4($a1)
/* 000622 0x80080A18 8CA40000 */ lw	$a0, 0($a1)
/* 000623 0x80080A1C AFAE0030 */ sw	$t6, 48($sp)
/* 000624 0x80080A20 8CAF0008 */ lw	$t7, 8($a1)
/* 000625 0x80080A24 AFA40034 */ sw	$a0, 52($sp)
/* 000626 0x80080A28 0C02026F */ jal	func_800809BC
/* 000627 0x80080A2C AFAF002C */ sw	$t7, 44($sp)
/* 000628 0x80080A30 8FA70034 */ lw	$a3, 52($sp)
/* 000629 0x80080A34 0440004B */ bltz	$v0, .L_80080B64
/* 000630 0x80080A38 00404025 */ move	$t0, $v0
/* 000631 0x80080A3C 3C18800A */ lui	$t8, %hi(D_8009B2BC)
/* 000632 0x80080A40 9718B2BC */ lhu	$t8, %lo(D_8009B2BC)($t8)
/* 000633 0x80080A44 3C09800A */ lui	$t1, %hi(dmadata)
/* 000634 0x80080A48 2529F8B0 */ addiu	$t1, %lo(dmadata)
/* 000635 0x80080A4C 0058082A */ slt	$at, $v0, $t8
/* 000636 0x80080A50 10200044 */ beqz	$at, .L_80080B64
/* 000637 0x80080A54 0002C900 */ sll	$t9, $v0, 4
/* 000638 0x80080A58 03292021 */ addu	$a0, $t9, $t1
/* 000639 0x80080A5C 8C85000C */ lw	$a1, 12($a0)
/* 000640 0x80080A60 8FAB002C */ lw	$t3, 44($sp)
/* 000641 0x80080A64 54A0001B */ bnezl	$a1, .L_80080AD4
/* 000642 0x80080A68 8C830008 */ lw	$v1, 8($a0)
/* 000643 0x80080A6C 8C8A0004 */ lw	$t2, 4($a0)
/* 000644 0x80080A70 00EB6021 */ addu	$t4, $a3, $t3
/* 000645 0x80080A74 3C04800A */ lui	$a0, %hi(D_800981C4)
/* 000646 0x80080A78 014C082B */ sltu	$at, $t2, $t4
/* 000647 0x80080A7C 10200007 */ beqz	$at, .L_80080A9C
/* 000648 0x80080A80 248481C4 */ addiu	$a0, %lo(D_800981C4)
/* 000649 0x80080A84 240501F3 */ li	$a1, 499
/* 000650 0x80080A88 AFA70034 */ sw	$a3, 52($sp)
/* 000651 0x80080A8C 0C020F93 */ jal	func_80083E4C
/* 000652 0x80080A90 AFA2001C */ sw	$v0, 28($sp)
/* 000653 0x80080A94 8FA70034 */ lw	$a3, 52($sp)
/* 000654 0x80080A98 8FA8001C */ lw	$t0, 28($sp)
.L_80080A9C:
/* 000655 0x80080A9C 3C0E800A */ lui	$t6, %hi(dmadata)
/* 000656 0x80080AA0 25CEF8B0 */ addiu	$t6, %lo(dmadata)
/* 000657 0x80080AA4 00086900 */ sll	$t5, $t0, 4
/* 000658 0x80080AA8 01AE1021 */ addu	$v0, $t5, $t6
/* 000659 0x80080AAC 8C4F0008 */ lw	$t7, 8($v0)
/* 000660 0x80080AB0 8C590000 */ lw	$t9, 0($v0)
/* 000661 0x80080AB4 8FA50030 */ lw	$a1, 48($sp)
/* 000662 0x80080AB8 01E7C021 */ addu	$t8, $t7, $a3
/* 000663 0x80080ABC 8FA6002C */ lw	$a2, 44($sp)
/* 000664 0x80080AC0 0C0201E4 */ jal	func_80080790
/* 000665 0x80080AC4 03192023 */ subu	$a0, $t8, $t9
/* 000666 0x80080AC8 1000002B */ b	.L_80080B78
/* 000667 0x80080ACC 8FBF0014 */ lw	$ra, 20($sp)
/* 000668 0x80080AD0 8C830008 */ lw	$v1, 8($a0)
.L_80080AD4:
/* 000669 0x80080AD4 00A34823 */ subu	$t1, $a1, $v1
/* 000670 0x80080AD8 AFA90024 */ sw	$t1, 36($sp)
/* 000671 0x80080ADC AFA30028 */ sw	$v1, 40($sp)
/* 000672 0x80080AE0 8C8B0000 */ lw	$t3, 0($a0)
/* 000673 0x80080AE4 3C04800A */ lui	$a0, %hi(D_800981D4)
/* 000674 0x80080AE8 248481D4 */ addiu	$a0, %lo(D_800981D4)
/* 000675 0x80080AEC 10EB0004 */ beq	$a3, $t3, .L_80080B00
/* 000676 0x80080AF0 24050206 */ li	$a1, 518
/* 000677 0x80080AF4 0C020F93 */ jal	func_80083E4C
/* 000678 0x80080AF8 AFA8001C */ sw	$t0, 28($sp)
/* 000679 0x80080AFC 8FA8001C */ lw	$t0, 28($sp)
.L_80080B00:
/* 000680 0x80080B00 3C0C800A */ lui	$t4, %hi(dmadata)
/* 000681 0x80080B04 258CF8B0 */ addiu	$t4, %lo(dmadata)
/* 000682 0x80080B08 00085100 */ sll	$t2, $t0, 4
/* 000683 0x80080B0C 014C1021 */ addu	$v0, $t2, $t4
/* 000684 0x80080B10 8C4E0004 */ lw	$t6, 4($v0)
/* 000685 0x80080B14 8C4F0000 */ lw	$t7, 0($v0)
/* 000686 0x80080B18 8FAD002C */ lw	$t5, 44($sp)
/* 000687 0x80080B1C 3C04800A */ lui	$a0, %hi(D_800981E4)
/* 000688 0x80080B20 01CFC023 */ subu	$t8, $t6, $t7
/* 000689 0x80080B24 11B80003 */ beq	$t5, $t8, .L_80080B34
/* 000690 0x80080B28 248481E4 */ addiu	$a0, %lo(D_800981E4)
/* 000691 0x80080B2C 0C020F93 */ jal	func_80083E4C
/* 000692 0x80080B30 2405020D */ li	$a1, 525
.L_80080B34:
/* 000693 0x80080B34 00002025 */ move	$a0, $zero
/* 000694 0x80080B38 0C023F00 */ jal	osSetThreadPri
/* 000695 0x80080B3C 2405000A */ li	$a1, 10
/* 000696 0x80080B40 8FA40028 */ lw	$a0, 40($sp)
/* 000697 0x80080B44 8FA50030 */ lw	$a1, 48($sp)
/* 000698 0x80080B48 0C02045E */ jal	func_80081178
/* 000699 0x80080B4C 8FA60024 */ lw	$a2, 36($sp)
/* 000700 0x80080B50 00002025 */ move	$a0, $zero
/* 000701 0x80080B54 0C023F00 */ jal	osSetThreadPri
/* 000702 0x80080B58 24050011 */ li	$a1, 17
/* 000703 0x80080B5C 10000006 */ b	.L_80080B78
/* 000704 0x80080B60 8FBF0014 */ lw	$ra, 20($sp)
.L_80080B64:
/* 000705 0x80080B64 3C04800A */ lui	$a0, %hi(D_800981F4)
/* 000706 0x80080B68 248481F4 */ addiu	$a0, %lo(D_800981F4)
/* 000707 0x80080B6C 0C020F93 */ jal	func_80083E4C
/* 000708 0x80080B70 2405022E */ li	$a1, 558
/* 000709 0x80080B74 8FBF0014 */ lw	$ra, 20($sp)
.L_80080B78:
/* 000710 0x80080B78 27BD0038 */ addiu	$sp, $sp, 56
/* 000711 0x80080B7C 03E00008 */ jr	$ra
/* 000712 0x80080DFC 00000000 */ nop
)

#endif

#ifdef NONMATCHING

void func_80080B84(void* a0) {
    s80080A08* sp52;
	UNK_TYPE pad;
    s80080A08* s0;

    for (;;) {
        osRecvMesg(&D_8009B2C0, (OSMesg)&sp52, 1);
        if (sp52 == NULL) return;
        s0 = sp52;
        func_80080A08(s0);
        // TODO a0 isn't being used for this comparison
        if (s0->unk24 == NULL) continue;
        osSendMesg(&D_8009B2C0, (OSMesg)s0->unk28, 0);
    }
}

#else

GLOBAL_ASM(
glabel func_80080B84
/* 000713 0x80080B84 27BDFFC8 */ addiu	$sp, $sp, -56
/* 000714 0x80080B88 AFBF0024 */ sw	$ra, 36($sp)
/* 000715 0x80080B8C AFB20020 */ sw	$s2, 32($sp)
/* 000716 0x80080B90 AFB1001C */ sw	$s1, 28($sp)
/* 000717 0x80080B94 AFB00018 */ sw	$s0, 24($sp)
/* 000718 0x80080B98 AFA40038 */ sw	$a0, 56($sp)
/* 000719 0x80080B9C 3C11800A */ lui	$s1, %hi(D_8009B2C0)
/* 000720 0x80080BA0 2631B2C0 */ addiu	$s1, %lo(D_8009B2C0)
/* 000721 0x80080BA4 27B20034 */ addiu	$s2, $sp, 52
/* 000722 0x80080BA8 02202025 */ move	$a0, $s1
.L_80080BAC:
/* 000723 0x80080BAC 02402825 */ move	$a1, $s2
/* 000724 0x80080BB0 0C021FB4 */ jal	osRecvMesg
/* 000725 0x80080BB4 24060001 */ li	$a2, 1
/* 000726 0x80080BB8 8FA40034 */ lw	$a0, 52($sp)
/* 000727 0x80080BBC 5080000C */ beqzl	$a0, .L_80080BF0
/* 000728 0x80080BC0 8FBF0024 */ lw	$ra, 36($sp)
/* 000729 0x80080BC4 0C020282 */ jal	func_80080A08
/* 000730 0x80080BC8 00808025 */ move	$s0, $a0
/* 000731 0x80080BCC 8E040018 */ lw	$a0, 24($s0)
/* 000732 0x80080BD0 5080FFF6 */ beqzl	$a0, .L_80080BAC
/* 000733 0x80080BD4 02202025 */ move	$a0, $s1
/* 000734 0x80080BD8 8E05001C */ lw	$a1, 28($s0)
/* 000735 0x80080BDC 0C021EC4 */ jal	osSendMesg
/* 000736 0x80080BE0 00003025 */ move	$a2, $zero
/* 000737 0x80080BE4 1000FFF1 */ b	.L_80080BAC
/* 000738 0x80080BE8 02202025 */ move	$a0, $s1
/* 000739 0x80080BEC 8FBF0024 */ lw	$ra, 36($sp)
.L_80080BF0:
/* 000740 0x80080BF0 8FB00018 */ lw	$s0, 24($sp)
/* 000741 0x80080BF4 8FB1001C */ lw	$s1, 28($sp)
/* 000742 0x80080BF8 8FB20020 */ lw	$s2, 32($sp)
/* 000743 0x80080BFC 03E00008 */ jr	$ra
/* 000744 0x80080C00 27BD0038 */ addiu	$sp, $sp, 56
)

#endif

#ifdef NONMATCHING

s32 func_80080C04(s80080A08* a0, UNK_FUN_PTR(a1), UNK_PTR a2, UNK_TYPE a3, UNK_TYPE sp48, OSMesgQueue* sp52, UNK_TYPE sp56) {
    // TODO this isn't correct, it uses a lui, addiu to get the address of D_80096B60, then loads it,
	// meaning that this is likely just "if (*D_80096B60 >= 2)". However, I can not get it to not
	// produce the usual lui, lw combo to load from an address :/
    if (*D_80096B60 >= 2) {
        return -2;
    }

    a0->unk0 = a2;
    a0->unk4 = a1;
    a0->unk8 = a3;
    a0->unk20 = 0;
    a0->unk24 = sp52;
    a0->unk28 = sp56;

    osSendMesg(&D_8009B2C0, (OSMesg)a0, 1);

    return 0;
}

#else

GLOBAL_ASM(
glabel func_80080C04
/* 000745 0x80080C04 27BDFFE0 */ addiu	$sp, $sp, -32
/* 000746 0x80080C08 AFB00018 */ sw	$s0, 24($sp)
/* 000747 0x80080C0C 00808025 */ move	$s0, $a0
/* 000748 0x80080C10 AFBF001C */ sw	$ra, 28($sp)
/* 000749 0x80080C14 AFA50024 */ sw	$a1, 36($sp)
/* 000750 0x80080C18 AFA60028 */ sw	$a2, 40($sp)
/* 000751 0x80080C1C 3C0E8009 */ lui	$t6, %hi(D_80096B60)
/* 000752 0x80080C20 25CE6B60 */ addiu	$t6, %lo(D_80096B60)
/* 000753 0x80080C24 8DCF0000 */ lw	$t7, 0($t6)
/* 000754 0x80080C28 8FB80028 */ lw	$t8, 40($sp)
/* 000755 0x80080C2C 3C04800A */ lui	$a0, 0x800A
/* 000756 0x80080C30 29E10002 */ slti	$at, $t7, 2
/* 000757 0x80080C34 54200004 */ bnezl	$at, .L_80080C48
/* 000758 0x80080C38 AE180000 */ sw	$t8, 0($s0)
/* 000759 0x80080C3C 1000000F */ b	.L_80080C7C
/* 000760 0x80080C40 2402FFFE */ li	$v0, -2
/* 000761 0x80080C44 AE180000 */ sw	$t8, 0($s0)
.L_80080C48:
/* 000762 0x80080C48 8FB90024 */ lw	$t9, 36($sp)
/* 000763 0x80080C4C AE070008 */ sw	$a3, 8($s0)
/* 000764 0x80080C50 AE000014 */ sw	$zero, 20($s0)
/* 000765 0x80080C54 AE190004 */ sw	$t9, 4($s0)
/* 000766 0x80080C58 8FA80034 */ lw	$t0, 52($sp)
/* 000767 0x80080C5C 2484B2C0 */ addiu	$a0, $a0, -19776
/* 000768 0x80080C60 02002825 */ move	$a1, $s0
/* 000769 0x80080C64 AE080018 */ sw	$t0, 24($s0)
/* 000770 0x80080C68 8FA90038 */ lw	$t1, 56($sp)
/* 000771 0x80080C6C 24060001 */ li	$a2, 1
/* 000772 0x80080C70 0C021EC4 */ jal	osSendMesg
/* 000773 0x80080C74 AE09001C */ sw	$t1, 28($s0)
/* 000774 0x80080C78 00001025 */ move	$v0, $zero
.L_80080C7C:
/* 000775 0x80080C7C 8FBF001C */ lw	$ra, 28($sp)
/* 000776 0x80080C80 8FB00018 */ lw	$s0, 24($sp)
/* 000777 0x80080C84 27BD0020 */ addiu	$sp, $sp, 32
/* 000778 0x80080C88 03E00008 */ jr	$ra
/* 000779 0x80080C8C 00000000 */ nop
)

#endif

s32 func_80080C90(UNK_TYPE a0, UNK_PTR a1, UNK_TYPE a2) {
	s80080A08 sp72;
    OSMesgQueue sp48;
    OSMesg sp44;
	s32 ret;

    osCreateMesgQueue(&sp48, &sp44, 1);

	ret = func_80080C04(&sp72, (UNK_FUN_ARG)a0, a1, a2, 0, &sp48, 0);

	if (ret == -1) {
		return ret;
	} else {
		osRecvMesg(&sp48, NULL, 1);
	}

	return 0;
}

#ifdef NONMATCHING

void func_80080D0C() {
	DmadataEntry* v0;
	u32 v1;
	// TODO register load ordering is wrong
	func_80080790(&dmadataRomStart, dmadata, (u8*)&dmadataRomEnd - (u8*)&dmadataRomStart);

	for (v0 = dmadata, v1 = 0; v0->vromEnd != 0; v0++, v1++);

	D_8009B2BC = (u16)v1;

	osCreateMesgQueue(&D_8009B2C0, (OSMesg)&D_8009B2D8, 32);

	func_80085320(&D_8009B2A0, &D_8009B508, &D_8009BA08, 0, 256, &D_80098204);

	osCreateThread(&D_8009B358, 18, func_80080B84, NULL, &D_8009BA08, 17);

	osStartThread(&D_8009B358);
}

#else

GLOBAL_ASM(
glabel func_80080D0C
/* 000811 0x80080D0C 27BDFFE0 */ addiu	$sp, $sp, -32
/* 000812 0x80080D10 AFBF001C */ sw	$ra, 28($sp)
/* 000813 0x80080D14 3C040002 */ lui	$a0, %hi(dmadataRomStart)
/* 000814 0x80080D18 3C0E0002 */ lui	$t6, %hi(dmadataRomEnd)
/* 000815 0x80080D1C 25CE0700 */ addiu	$t6, %lo(dmadataRomEnd)
/* 000816 0x80080D20 2484A500 */ addiu	$a0, %lo(dmadataRomStart)
/* 000817 0x80080D24 3C05800A */ lui	$a1, %hi(dmadata)
/* 000818 0x80080D28 24A5F8B0 */ addiu	$a1, %lo(dmadata)
/* 000819 0x80080D2C 0C0201E4 */ jal	func_80080790
/* 000820 0x80080D30 01C43023 */ subu	$a2, $t6, $a0
/* 000821 0x80080D34 3C04800A */ lui	$a0, %hi(dmadata)
/* 000822 0x80080D38 2484F8B0 */ addiu	$a0, %lo(dmadata)
/* 000823 0x80080D3C 8C8F0004 */ lw	$t7, 4($a0)
/* 000824 0x80080D40 00801025 */ move	$v0, $a0
/* 000825 0x80080D44 00001825 */ move	$v1, $zero
/* 000826 0x80080D48 11E00006 */ beqz	$t7, .L_80080D64
/* 000827 0x80080D4C 3C01800A */ lui	$at, %hi(D_8009B2BC)
/* 000828 0x80080D50 8C580014 */ lw	$t8, 20($v0)
.L_80080D54:
/* 000829 0x80080D54 24420010 */ addiu	$v0, $v0, 16
/* 000830 0x80080D58 24630001 */ addiu	$v1, $v1, 1
/* 000831 0x80080D5C 5700FFFD */ bnezl	$t8, .L_80080D54
/* 000832 0x80080D60 8C580014 */ lw	$t8, 20($v0)
.L_80080D64:
/* 000833 0x80080D64 A423B2BC */ sh	$v1, %lo(D_8009B2BC)($at)
/* 000834 0x80080D68 3C04800A */ lui	$a0, %hi(D_8009B2C0)
/* 000835 0x80080D6C 3C05800A */ lui	$a1, %hi(D_8009B2D8)
/* 000836 0x80080D70 24A5B2D8 */ addiu	$a1, %lo(D_8009B2D8)
/* 000837 0x80080D74 2484B2C0 */ addiu	$a0, %lo(D_8009B2C0)
/* 000838 0x80080D78 0C023C90 */ jal	osCreateMesgQueue
/* 000839 0x80080D7C 24060020 */ li	$a2, 32
/* 000840 0x80080D80 3C08800A */ lui	$t0, %hi(D_80098204)
/* 000841 0x80080D84 25088204 */ addiu	$t0, %lo(D_80098204)
/* 000842 0x80080D88 3C04800A */ lui	$a0, 0x800A
/* 000843 0x80080D8C 3C05800A */ lui	$a1, %hi(D_8009B508)
/* 000844 0x80080D90 3C06800A */ lui	$a2, %hi(D_8009BA08)
/* 000845 0x80080D94 24190100 */ li	$t9, 256
/* 000846 0x80080D98 AFB90010 */ sw	$t9, 16($sp)
/* 000847 0x80080D9C 24C6BA08 */ addiu	$a2, %lo(D_8009BA08)
/* 000848 0x80080DA0 24A5B508 */ addiu	$a1, %lo(D_8009B508)
/* 000849 0x80080DA4 2484B2A0 */ addiu	$a0, $a0, -19808
/* 000850 0x80080DA8 AFA80014 */ sw	$t0, 20($sp)
/* 000851 0x80080DAC 0C0214C8 */ jal	func_80085320
/* 000852 0x80080DB0 00003825 */ move	$a3, $zero
/* 000853 0x80080DB4 3C09800A */ lui	$t1, %hi(D_8009BA08)
/* 000854 0x80080DB8 2529BA08 */ addiu	$t1, %lo(D_8009BA08)
/* 000855 0x80080DBC 3C04800A */ lui	$a0, %hi(D_8009B358)
/* 000856 0x80080DC0 3C068008 */ lui	$a2, %hi(func_80080B84)
/* 000857 0x80080DC4 240A0011 */ li	$t2, 17
/* 000858 0x80080DC8 AFAA0014 */ sw	$t2, 20($sp)
/* 000859 0x80080DCC 24C60B84 */ addiu	$a2, %lo(func_80080B84)
/* 000860 0x80080DD0 2484B358 */ addiu	$a0, %lo(D_8009B358)
/* 000861 0x80080DD4 AFA90010 */ sw	$t1, 16($sp)
/* 000862 0x80080DD8 24050012 */ li	$a1, 18
/* 000863 0x80080DDC 0C022790 */ jal	osCreateThread
/* 000864 0x80080DE0 00003825 */ move	$a3, $zero
/* 000865 0x80080DE4 3C04800A */ lui	$a0, %hi(D_8009B358)
/* 000866 0x80080DE8 0C0255EC */ jal	osStartThread
/* 000867 0x80080DEC 2484B358 */ addiu	$a0, %lo(D_8009B358)
/* 000868 0x80080DF0 8FBF001C */ lw	$ra, 28($sp)
/* 000869 0x80080DF4 27BD0020 */ addiu	$sp, $sp, 32
/* 000870 0x80080DF8 03E00008 */ jr	$ra
/* 000871 0x80080DFC 00000000 */ nop
)

#endif

void func_80080E00() {
    osSendMesg(&D_8009B2C0, NULL, 1);
}
