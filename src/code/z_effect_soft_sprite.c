#include <ultra64.h>
#include <global.h>

void EffectSS_Init(z_GlobalContext* ctxt, s32 numEntries) {
    u32 i;
    z_LoadedParticleEntry* iter;
    z_ParticleOverlayTableEntry* iter2;

    EffectSS2Info.data_table = (z_LoadedParticleEntry*)GameStateHeap_AllocFromEnd(&ctxt->unk74, numEntries * sizeof(z_LoadedParticleEntry));
    EffectSS2Info.searchIndex = 0;
    EffectSS2Info.size = numEntries;

    for (iter = EffectSS2Info.data_table; iter < EffectSS2Info.data_table + EffectSS2Info.size; iter++) {
        EffectSS_ResetLoadedParticleEntry(iter);
    }

    for (i = 0, iter2 = particleOverlayTable; i != 0x27; i++) {
        (iter2++)->loadedRamAddr = 0;
    }
}

void EffectSS_Clear(z_GlobalContext* ctxt) {
    u32 i;
    z_LoadedParticleEntry* iter;
    z_ParticleOverlayTableEntry* iter2;
    void* addr;

    EffectSS2Info.data_table = NULL;
    EffectSS2Info.searchIndex = 0;
    EffectSS2Info.size = 0;

    // This code is completely useless, as data_table was juest to NULL and size to 0
    for (iter = EffectSS2Info.data_table; iter < EffectSS2Info.data_table + EffectSS2Info.size; iter++) {
        EffectSS_Delete(iter);
    }

    // Free memory from loaded particle overlays
    for (i = 0, iter2 = particleOverlayTable; i != 0x27; i++) {
        addr = (void*)iter2->loadedRamAddr;
        if (addr != NULL) {
            zelda_free(addr);
        }
        (iter2++)->loadedRamAddr = 0;
    }
}

z_LoadedParticleEntry* EffectSS_GetTable() {
    return EffectSS2Info.data_table;
}

void EffectSS_Delete(z_LoadedParticleEntry* a0) {
    if (a0->flags & 0x2) {
        func_801A72CC((UNK_PTR)&a0->position);
    }

    if (a0->flags & 0x4) {
        func_801A72CC((UNK_PTR)&a0->unk2C);
    }

    EffectSS_ResetLoadedParticleEntry(a0);
}

void EffectSS_ResetLoadedParticleEntry(z_LoadedParticleEntry* particle) {
    u32 i;

    particle->type = 0x27;
    particle->acceleration.z = 0;
    particle->acceleration.y = 0;
    particle->acceleration.x = 0;
    particle->velocity.z = 0;
    particle->velocity.y = 0;
    particle->velocity.x = 0;
    particle->unk34 = 0;
    particle->unk30 = 0;
    particle->unk2C = 0;
    particle->position.z = 0;
    particle->position.y = 0;
    particle->position.x = 0;
    particle->life = -1;
    particle->flags = 0;
    particle->priority = 128;
    particle->draw = NULL;
    particle->update = NULL;
    particle->unk38 = 0;
    particle->unk3C = 0;

    for (i = 0; i != 13; i++) {
        particle->unk40[i] = 0;
    }
}

// XXX Some regalloc differences and instruction ordering
#ifdef NONMATCHING

s32 EffectSS_FindFreeSpace(u32 priority, u32* tableEntry) {
    s32 ret = 0;
    s32 i;

    if (EffectSS2Info.size <= EffectSS2Info.searchIndex) {
        EffectSS2Info.searchIndex = 0;
    }

    // Search for a unused entry
    for (i = EffectSS2Info.searchIndex;;) {
        if (EffectSS2Info.data_table[i].life == -1) {
            ret = 1;
            break;
        }

        i += 1;

        if (EffectSS2Info.size <= i) {
            i = 0;
        }

        if (i == EffectSS2Info.searchIndex) break;
    }

    if (ret == 1) {
        ret = 0;
    } else {
        // If the entire table is full, look for a lower priority entry instead
        for (;;) {
            if (priority <= EffectSS2Info.data_table[i].priority &&
                (priority != EffectSS2Info.data_table[i].priority || (EffectSS2Info.data_table[i].flags & 0x1) == 0)) {
                ret = 0;
                break;
            }

            i += 1;

            if (EffectSS2Info.size <= i) {
                i = 0;
            }

            if (i == EffectSS2Info.searchIndex) {
                ret = 1;
                return ret;
            }
        }

    }

    *tableEntry = i;

    return ret;
}

#else

GLOBAL_ASM(
glabel EffectSS_FindFreeSpace
/* 010769 0x800B0304 27BDFFF8 */ addiu	$sp, $sp, -8
/* 010770 0x800B0308 AFB00004 */ sw	$s0, 0X4($sp)
/* 010771 0x800B030C 3C06801B */ lui	$a2, %hi(EffectSS2Info)
/* 010772 0x800B0310 24C6E3A0 */ addiu	$a2, %lo(EffectSS2Info)
/* 010773 0x800B0314 00808025 */ move	$s0, $a0
/* 010774 0x800B0318 AFA5000C */ sw	$a1, 0XC($sp)
/* 010775 0x800B031C 8CC20004 */ lw	$v0, 0X4($a2)
/* 010776 0x800B0320 8CC30008 */ lw	$v1, 0X8($a2)
/* 010777 0x800B0324 00002825 */ move	$a1, $zero
/* 010778 0x800B0328 2408FFFF */ li	$t0, -1
/* 010779 0x800B032C 0043082A */ slt	$at, $v0, $v1
/* 010780 0x800B0330 14200003 */ bnez	$at, .L_800B0340
/* 010781 0x800B0334 00000000 */ nop
/* 010782 0x800B0338 ACC00004 */ sw	$zero, 0X4($a2)
/* 010783 0x800B033C 00001025 */ move	$v0, $zero
.L_800B0340:
/* 010784 0x800B0340 3C06801B */ lui	$a2, %hi(EffectSS2Info)
/* 010785 0x800B0344 8CC6E3A0 */ lw	$a2, %lo(EffectSS2Info)($a2)
/* 010786 0x800B0348 00027080 */ sll	$t6, $v0, 2
/* 010787 0x800B034C 01C27023 */ subu	$t6, $t6, $v0
/* 010788 0x800B0350 000E7140 */ sll	$t6, $t6, 5
/* 010789 0x800B0354 00402025 */ move	$a0, $v0
/* 010790 0x800B0358 00CE3821 */ addu	$a3, $a2, $t6
.L_800B035C:
/* 010791 0x800B035C 84EF005C */ lh	$t7, 0X5C($a3)
/* 010792 0x800B0360 550F0004 */ bnel	$t0, $t7, .L_800B0374
/* 010793 0x800B0364 24840001 */ addiu	$a0, $a0, 1
/* 010794 0x800B0368 1000000C */ b	.L_800B039C
/* 010795 0x800B036C 24050001 */ li	$a1, 1
/* 010796 0x800B0370 24840001 */ addiu	$a0, $a0, 1
.L_800B0374:
/* 010797 0x800B0374 0083082A */ slt	$at, $a0, $v1
/* 010798 0x800B0378 14200002 */ bnez	$at, .L_800B0384
/* 010799 0x800B037C 00000000 */ nop
/* 010800 0x800B0380 00002025 */ move	$a0, $zero
.L_800B0384:
/* 010801 0x800B0384 10820005 */ beq	$a0, $v0, .L_800B039C
/* 010802 0x800B0388 0004C080 */ sll	$t8, $a0, 2
/* 010803 0x800B038C 0304C023 */ subu	$t8, $t8, $a0
/* 010804 0x800B0390 0018C140 */ sll	$t8, $t8, 5
/* 010805 0x800B0394 1000FFF1 */ b	.L_800B035C
/* 010806 0x800B0398 00D83821 */ addu	$a3, $a2, $t8
.L_800B039C:
/* 010807 0x800B039C 24010001 */ li	$at, 1
/* 010808 0x800B03A0 14A10005 */ bne	$a1, $at, .L_800B03B8
/* 010809 0x800B03A4 00024880 */ sll	$t1, $v0, 2
/* 010810 0x800B03A8 8FB9000C */ lw	$t9, 0XC($sp)
/* 010811 0x800B03AC 00001025 */ move	$v0, $zero
/* 010812 0x800B03B0 1000001F */ b	.L_800B0430
/* 010813 0x800B03B4 AF240000 */ sw	$a0, 0X0($t9)
.L_800B03B8:
/* 010814 0x800B03B8 01224823 */ subu	$t1, $t1, $v0
/* 010815 0x800B03BC 00094940 */ sll	$t1, $t1, 5
/* 010816 0x800B03C0 00402025 */ move	$a0, $v0
/* 010817 0x800B03C4 00C93821 */ addu	$a3, $a2, $t1
.L_800B03C8:
/* 010818 0x800B03C8 90E5005E */ lbu	$a1, 0X5E($a3)
/* 010819 0x800B03CC 00B0082A */ slt	$at, $a1, $s0
/* 010820 0x800B03D0 54200008 */ bnezl	$at, .L_800B03F4
/* 010821 0x800B03D4 24840001 */ addiu	$a0, $a0, 1
/* 010822 0x800B03D8 56050013 */ bnel	$s0, $a1, .L_800B0428
/* 010823 0x800B03DC 8FAD000C */ lw	$t5, 0XC($sp)
/* 010824 0x800B03E0 94EA005A */ lhu	$t2, 0X5A($a3)
/* 010825 0x800B03E4 314B0001 */ andi	$t3, $t2, 0X1
/* 010826 0x800B03E8 5160000F */ beqzl	$t3, .L_800B0428
/* 010827 0x800B03EC 8FAD000C */ lw	$t5, 0XC($sp)
/* 010828 0x800B03F0 24840001 */ addiu	$a0, $a0, 1
.L_800B03F4:
/* 010829 0x800B03F4 0083082A */ slt	$at, $a0, $v1
/* 010830 0x800B03F8 14200002 */ bnez	$at, .L_800B0404
/* 010831 0x800B03FC 00000000 */ nop
/* 010832 0x800B0400 00002025 */ move	$a0, $zero
.L_800B0404:
/* 010833 0x800B0404 14820003 */ bne	$a0, $v0, .L_800B0414
/* 010834 0x800B0408 00046080 */ sll	$t4, $a0, 2
/* 010835 0x800B040C 10000008 */ b	.L_800B0430
/* 010836 0x800B0410 24020001 */ li	$v0, 1
.L_800B0414:
/* 010837 0x800B0414 01846023 */ subu	$t4, $t4, $a0
/* 010838 0x800B0418 000C6140 */ sll	$t4, $t4, 5
/* 010839 0x800B041C 1000FFEA */ b	.L_800B03C8
/* 010840 0x800B0420 00CC3821 */ addu	$a3, $a2, $t4
/* 010841 0x800B0424 8FAD000C */ lw	$t5, 0XC($sp)
.L_800B0428:
/* 010842 0x800B0428 00001025 */ move	$v0, $zero
/* 010843 0x800B042C ADA40000 */ sw	$a0, 0X0($t5)
.L_800B0430:
/* 010844 0x800B0430 8FB00004 */ lw	$s0, 0X4($sp)
/* 010845 0x800B0434 03E00008 */ jr	$ra
/* 010846 0x800B0438 27BD0008 */ addiu	$sp, $sp, 8
)

#endif

void EffectSS_Copy(z_GlobalContext* ctxt, z_LoadedParticleEntry* a1) {
    u32 index;
    if (func_8016A01C(ctxt) != 1) {
        if (EffectSS_FindFreeSpace(a1->priority, &index) == 0) {
            EffectSS2Info.searchIndex = index + 1;
            EffectSS2Info.data_table[index] = *a1;
        }
    }
}

#ifdef NONMATCHING

void EffectSS_LoadParticle(z_GlobalContext* ctxt, u32 type, u32 priority, void* initData) {
    u32 index;
    u32 initRet;
    u32 overlaySize;
    z_ParticleOverlayInfo* overlayInfo;
    z_ParticleOverlayTableEntry* entry = &particleOverlayTable[type];

    if (EffectSS_FindFreeSpace(priority, &index) != 0) {
        return;
    }

    EffectSS2Info.searchIndex = index + 1;
    if (entry->vramStart == 0) {
        overlayInfo = entry->overlayInfo;
    } else {
        // XXX this subtraction is done earlier
        overlaySize = entry->vramEnd - entry->vramStart;
        if (entry->loadedRamAddr == 0) {
            entry->loadedRamAddr = (u32)zelda_mallocR(overlaySize);

            if (entry->loadedRamAddr == 0) {
                return;
            }

            load_and_relocate_overlay(entry->vromStart, entry->vromEnd, entry->vramStart, entry->vramEnd, entry->loadedRamAddr);
        }

        // XXX this should use a0, but it doesn't
        if (entry->overlayInfo != NULL) {
            overlayInfo = (z_ParticleOverlayInfo*)(-(entry->vramStart - entry->loadedRamAddr) + (u32)entry->overlayInfo);
        } else {
            overlayInfo = NULL;
        }
    }

    if (overlayInfo->init != 0) {
        EffectSS_Delete(&EffectSS2Info.data_table[index]);

        EffectSS2Info.data_table[index].type = type;
        EffectSS2Info.data_table[index].priority = priority;

        initRet = (*overlayInfo->init)(ctxt, index, &EffectSS2Info.data_table[index], initData);

        if (initRet == 0) {
            EffectSS_ResetLoadedParticleEntry(&EffectSS2Info.data_table[index]);
        }
    }
}

#else

GLOBAL_ASM(
glabel EffectSS_LoadParticle
/* 010885 0x800B04D4 27BDFFC0 */ addiu	$sp, $sp, -64
/* 010886 0x800B04D8 AFBF001C */ sw	$ra, 0X1C($sp)
/* 010887 0x800B04DC AFA40040 */ sw	$a0, 0X40($sp)
/* 010888 0x800B04E0 AFA50044 */ sw	$a1, 0X44($sp)
/* 010889 0x800B04E4 AFA60048 */ sw	$a2, 0X48($sp)
/* 010890 0x800B04E8 AFA7004C */ sw	$a3, 0X4C($sp)
/* 010891 0x800B04EC 8FA40048 */ lw	$a0, 0X48($sp)
/* 010892 0x800B04F0 0C02C0C1 */ jal	EffectSS_FindFreeSpace
/* 010893 0x800B04F4 27A5003C */ addiu	$a1, $sp, 60
/* 010894 0x800B04F8 1440005C */ bnez	$v0, .L_800B066C
/* 010895 0x800B04FC 8FAE003C */ lw	$t6, 0X3C($sp)
/* 010896 0x800B0500 8FB80044 */ lw	$t8, 0X44($sp)
/* 010897 0x800B0504 3C09801B */ lui	$t1, %hi(particleOverlayTable)
/* 010898 0x800B0508 25CF0001 */ addiu	$t7, $t6, 1
/* 010899 0x800B050C 0018C8C0 */ sll	$t9, $t8, 3
/* 010900 0x800B0510 0338C823 */ subu	$t9, $t9, $t8
/* 010901 0x800B0514 3C01801B */ lui	$at, %hi(D_801AE3A4)
/* 010902 0x800B0518 0019C880 */ sll	$t9, $t9, 2
/* 010903 0x800B051C 2529E4A0 */ addiu	$t1, %lo(particleOverlayTable)
/* 010904 0x800B0520 AC2FE3A4 */ sw	$t7, %lo(D_801AE3A4)($at)
/* 010905 0x800B0524 03291821 */ addu	$v1, $t9, $t1
/* 010906 0x800B0528 8C620008 */ lw	$v0, 0X8($v1)
/* 010907 0x800B052C 8C6A000C */ lw	$t2, 0XC($v1)
/* 010908 0x800B0530 14400003 */ bnez	$v0, .L_800B0540
/* 010909 0x800B0534 01422023 */ subu	$a0, $t2, $v0
/* 010910 0x800B0538 1000001B */ b	.L_800B05A8
/* 010911 0x800B053C 8C620014 */ lw	$v0, 0X14($v1)
.L_800B0540:
/* 010912 0x800B0540 8C6B0010 */ lw	$t3, 0X10($v1)
/* 010913 0x800B0544 5560000F */ bnezl	$t3, .L_800B0584
/* 010914 0x800B0548 8C620014 */ lw	$v0, 0X14($v1)
/* 010915 0x800B054C 0C040B22 */ jal	zelda_mallocR
/* 010916 0x800B0550 AFA30028 */ sw	$v1, 0X28($sp)
/* 010917 0x800B0554 8FA30028 */ lw	$v1, 0X28($sp)
/* 010918 0x800B0558 10400044 */ beqz	$v0, .L_800B066C
/* 010919 0x800B055C AC620010 */ sw	$v0, 0X10($v1)
/* 010920 0x800B0560 8C640000 */ lw	$a0, 0X0($v1)
/* 010921 0x800B0564 8C650004 */ lw	$a1, 0X4($v1)
/* 010922 0x800B0568 8C660008 */ lw	$a2, 0X8($v1)
/* 010923 0x800B056C 8C67000C */ lw	$a3, 0XC($v1)
/* 010924 0x800B0570 AFA30028 */ sw	$v1, 0X28($sp)
/* 010925 0x800B0574 0C021407 */ jal	load_and_relocate_overlay
/* 010926 0x800B0578 AFA20010 */ sw	$v0, 0X10($sp)
/* 010927 0x800B057C 8FA30028 */ lw	$v1, 0X28($sp)
/* 010928 0x800B0580 8C620014 */ lw	$v0, 0X14($v1)
.L_800B0584:
/* 010929 0x800B0584 00002025 */ move	$a0, $zero
/* 010930 0x800B0588 10400006 */ beqz	$v0, .L_800B05A4
/* 010931 0x800B058C 00000000 */ nop
/* 010932 0x800B0590 8C6D0008 */ lw	$t5, 0X8($v1)
/* 010933 0x800B0594 8C6E0010 */ lw	$t6, 0X10($v1)
/* 010934 0x800B0598 01AE7823 */ subu	$t7, $t5, $t6
/* 010935 0x800B059C 10000001 */ b	.L_800B05A4
/* 010936 0x800B05A0 004F2023 */ subu	$a0, $v0, $t7
.L_800B05A4:
/* 010937 0x800B05A4 00801025 */ move	$v0, $a0
.L_800B05A8:
/* 010938 0x800B05A8 8C580004 */ lw	$t8, 0X4($v0)
/* 010939 0x800B05AC 8FB9003C */ lw	$t9, 0X3C($sp)
/* 010940 0x800B05B0 3C0A801B */ lui	$t2, %hi(EffectSS2Info)
/* 010941 0x800B05B4 1300002D */ beqz	$t8, .L_800B066C
/* 010942 0x800B05B8 00194880 */ sll	$t1, $t9, 2
/* 010943 0x800B05BC 8D4AE3A0 */ lw	$t2, %lo(EffectSS2Info)($t2)
/* 010944 0x800B05C0 01394823 */ subu	$t1, $t1, $t9
/* 010945 0x800B05C4 00094940 */ sll	$t1, $t1, 5
/* 010946 0x800B05C8 AFA20030 */ sw	$v0, 0X30($sp)
/* 010947 0x800B05CC 0C02C084 */ jal	EffectSS_Delete
/* 010948 0x800B05D0 012A2021 */ addu	$a0, $t1, $t2
/* 010949 0x800B05D4 8FAD003C */ lw	$t5, 0X3C($sp)
/* 010950 0x800B05D8 24030060 */ li	$v1, 96
/* 010951 0x800B05DC 3C08801B */ lui	$t0, %hi(EffectSS2Info)
/* 010952 0x800B05E0 01A30019 */ multu	$t5, $v1
/* 010953 0x800B05E4 2508E3A0 */ addiu	$t0, %lo(EffectSS2Info)
/* 010954 0x800B05E8 8D0C0000 */ lw	$t4, 0X0($t0)
/* 010955 0x800B05EC 8FAB0044 */ lw	$t3, 0X44($sp)
/* 010956 0x800B05F0 8FA20030 */ lw	$v0, 0X30($sp)
/* 010957 0x800B05F4 00007012 */ mflo	$t6
/* 010958 0x800B05F8 018E7821 */ addu	$t7, $t4, $t6
/* 010959 0x800B05FC A1EB005F */ sb	$t3, 0X5F($t7)
/* 010960 0x800B0600 8FA9003C */ lw	$t1, 0X3C($sp)
/* 010961 0x800B0604 8D190000 */ lw	$t9, 0X0($t0)
/* 010962 0x800B0608 8FB80048 */ lw	$t8, 0X48($sp)
/* 010963 0x800B060C 01230019 */ multu	$t1, $v1
/* 010964 0x800B0610 00005012 */ mflo	$t2
/* 010965 0x800B0614 032A6821 */ addu	$t5, $t9, $t2
/* 010966 0x800B0618 A1B8005E */ sb	$t8, 0X5E($t5)
/* 010967 0x800B061C 8FA5003C */ lw	$a1, 0X3C($sp)
/* 010968 0x800B0620 8C590004 */ lw	$t9, 0X4($v0)
/* 010969 0x800B0624 8D0B0000 */ lw	$t3, 0X0($t0)
/* 010970 0x800B0628 00A30019 */ multu	$a1, $v1
/* 010971 0x800B062C 8FA7004C */ lw	$a3, 0X4C($sp)
/* 010972 0x800B0630 8FA40040 */ lw	$a0, 0X40($sp)
/* 010973 0x800B0634 00007012 */ mflo	$t6
/* 010974 0x800B0638 01CB3021 */ addu	$a2, $t6, $t3
/* 010975 0x800B063C 0320F809 */ jalr	$t9
/* 010976 0x800B0640 00000000 */ nop
/* 010977 0x800B0644 14400009 */ bnez	$v0, .L_800B066C
/* 010978 0x800B0648 24030060 */ li	$v1, 96
/* 010979 0x800B064C 8FAF003C */ lw	$t7, 0X3C($sp)
/* 010980 0x800B0650 3C0A801B */ lui	$t2, %hi(EffectSS2Info)
/* 010981 0x800B0654 8D4AE3A0 */ lw	$t2, %lo(EffectSS2Info)($t2)
/* 010982 0x800B0658 01E30019 */ multu	$t7, $v1
/* 010983 0x800B065C 00004812 */ mflo	$t1
/* 010984 0x800B0660 012A2021 */ addu	$a0, $t1, $t2
/* 010985 0x800B0664 0C02C09C */ jal	EffectSS_ResetLoadedParticleEntry
/* 010986 0x800B0668 00000000 */ nop
.L_800B066C:
/* 010987 0x800B066C 8FBF001C */ lw	$ra, 0X1C($sp)
/* 010988 0x800B0670 27BD0040 */ addiu	$sp, $sp, 64
/* 010989 0x800B0674 03E00008 */ jr	$ra
/* 010990 0x800B0678 00000000 */ nop
)

#endif

// XXX regalloc is wrong
#ifdef NONMATCHING

void EffectSS_UpdateParticle(z_GlobalContext* ctxt, u32 index) {
    z_LoadedParticleEntry* particle = &EffectSS2Info.data_table[index];

    if (particle->update != NULL) {
        particle->velocity.x += particle->acceleration.x;
        particle->velocity.y += particle->acceleration.y;
        particle->velocity.z += particle->acceleration.z;

        particle->position.x += particle->velocity.x;
        particle->position.y += particle->velocity.y;
        particle->position.z += particle->velocity.z;

        (*particle->update)(ctxt);
    }
}

#else

GLOBAL_ASM(
glabel EffectSS_UpdateParticle
/* 010991 0x800B067C 27BDFFE8 */ addiu	$sp, $sp, -24
/* 010992 0x800B0680 AFBF0014 */ sw	$ra, 0X14($sp)
/* 010993 0x800B0684 3C0F801B */ lui	$t7, %hi(EffectSS2Info)
/* 010994 0x800B0688 8DEFE3A0 */ lw	$t7, %lo(EffectSS2Info)($t7)
/* 010995 0x800B068C 00057080 */ sll	$t6, $a1, 2
/* 010996 0x800B0690 01C57023 */ subu	$t6, $t6, $a1
/* 010997 0x800B0694 000E7140 */ sll	$t6, $t6, 5
/* 010998 0x800B0698 01CF3021 */ addu	$a2, $t6, $t7
/* 010999 0x800B069C 8CC20024 */ lw	$v0, 0X24($a2)
/* 011000 0x800B06A0 5040001B */ beqzl	$v0, .L_800B0710
/* 011001 0x800B06A4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011002 0x800B06A8 C4C4000C */ lwc1	$f4, 0XC($a2)
/* 011003 0x800B06AC C4C60018 */ lwc1	$f6, 0X18($a2)
/* 011004 0x800B06B0 C4CA0010 */ lwc1	$f10, 0X10($a2)
/* 011005 0x800B06B4 C4D0001C */ lwc1	$f16, 0X1C($a2)
/* 011006 0x800B06B8 46062200 */ add.s	$f8, $f4, $f6
/* 011007 0x800B06BC C4C60020 */ lwc1	$f6, 0X20($a2)
/* 011008 0x800B06C0 C4C40014 */ lwc1	$f4, 0X14($a2)
/* 011009 0x800B06C4 46105480 */ add.s	$f18, $f10, $f16
/* 011010 0x800B06C8 E4C8000C */ swc1	$f8, 0XC($a2)
/* 011011 0x800B06CC C4D0000C */ lwc1	$f16, 0XC($a2)
/* 011012 0x800B06D0 C4CA0000 */ lwc1	$f10, 0X0($a2)
/* 011013 0x800B06D4 46062200 */ add.s	$f8, $f4, $f6
/* 011014 0x800B06D8 E4D20010 */ swc1	$f18, 0X10($a2)
/* 011015 0x800B06DC C4C60010 */ lwc1	$f6, 0X10($a2)
/* 011016 0x800B06E0 46105480 */ add.s	$f18, $f10, $f16
/* 011017 0x800B06E4 E4C80014 */ swc1	$f8, 0X14($a2)
/* 011018 0x800B06E8 C4C40004 */ lwc1	$f4, 0X4($a2)
/* 011019 0x800B06EC C4D00014 */ lwc1	$f16, 0X14($a2)
/* 011020 0x800B06F0 C4CA0008 */ lwc1	$f10, 0X8($a2)
/* 011021 0x800B06F4 E4D20000 */ swc1	$f18, 0X0($a2)
/* 011022 0x800B06F8 46062200 */ add.s	$f8, $f4, $f6
/* 011023 0x800B06FC 46105480 */ add.s	$f18, $f10, $f16
/* 011024 0x800B0700 E4C80004 */ swc1	$f8, 0X4($a2)
/* 011025 0x800B0704 0040F809 */ jalr	$v0
/* 011026 0x800B0708 E4D20008 */ swc1	$f18, 0X8($a2)
/* 011027 0x800B070C 8FBF0014 */ lw	$ra, 0X14($sp)
.L_800B0710:
/* 011028 0x800B0710 27BD0018 */ addiu	$sp, $sp, 24
/* 011029 0x800B0714 03E00008 */ jr	$ra
/* 011030 0x800B0718 00000000 */ nop
)

#endif

void EffectSS_UpdateAllParticles(z_GlobalContext* ctxt) {
    s32 i;

    for (i = 0; i < EffectSS2Info.size; i++) {
        if (EffectSS2Info.data_table[i].life > -1) {
            EffectSS2Info.data_table[i].life--;

            if (EffectSS2Info.data_table[i].life < 0) {
                EffectSS_Delete(&EffectSS2Info.data_table[i]);
            }
        }

        if (EffectSS2Info.data_table[i].life > -1) {
            EffectSS_UpdateParticle(ctxt, i);
        }
    }
}

// XXX regalloc is wrong
#ifdef NONMATCHING

void EffectSS_DrawParticle(z_GlobalContext* ctxt, s32 index) {
    z_LoadedParticleEntry* entry = &EffectSS2Info.data_table[index];
    if (entry->draw != 0) {
        (*entry->draw)(ctxt);
    }
}

#else

GLOBAL_ASM(
glabel EffectSS_DrawParticle
/* 011078 0x800B07D8 27BDFFE8 */ addiu	$sp, $sp, -24
/* 011079 0x800B07DC AFBF0014 */ sw	$ra, 0X14($sp)
/* 011080 0x800B07E0 3C0F801B */ lui	$t7, %hi(EffectSS2Info)
/* 011081 0x800B07E4 8DEFE3A0 */ lw	$t7, %lo(EffectSS2Info)($t7)
/* 011082 0x800B07E8 00057080 */ sll	$t6, $a1, 2
/* 011083 0x800B07EC 01C57023 */ subu	$t6, $t6, $a1
/* 011084 0x800B07F0 000E7140 */ sll	$t6, $t6, 5
/* 011085 0x800B07F4 01CF3021 */ addu	$a2, $t6, $t7
/* 011086 0x800B07F8 8CC20028 */ lw	$v0, 0X28($a2)
/* 011087 0x800B07FC 50400004 */ beqzl	$v0, .L_800B0810
/* 011088 0x800B0800 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011089 0x800B0804 0040F809 */ jalr	$v0
/* 011090 0x800B0808 00000000 */ nop
/* 011091 0x800B080C 8FBF0014 */ lw	$ra, 0X14($sp)
.L_800B0810:
/* 011092 0x800B0810 27BD0018 */ addiu	$sp, $sp, 24
/* 011093 0x800B0814 03E00008 */ jr	$ra
/* 011094 0x800B0818 00000000 */ nop
)

#endif

void EffectSS_DrawAllParticles(z_GlobalContext* ctxt) {
    UNK_TYPE s0;
    s32 i;

    s0 = Lights_CreateMapper(&ctxt->unk818, ctxt->unk0);
    Lights_MapLights(s0, ctxt->unk818, 0, ctxt);
    Lights_UploadLights(s0, ctxt->unk0);

    for (i = 0; i < EffectSS2Info.size; i++) {
        if (EffectSS2Info.data_table[i].life > -1) {
            if (EffectSS2Info.data_table[i].position.x > 32000 ||
                EffectSS2Info.data_table[i].position.x < -32000 ||
                EffectSS2Info.data_table[i].position.y > 32000 ||
                EffectSS2Info.data_table[i].position.y < -32000 ||
                EffectSS2Info.data_table[i].position.z > 32000 ||
                EffectSS2Info.data_table[i].position.z < -32000
            ) {
                EffectSS_Delete(&EffectSS2Info.data_table[i]);
            } else {
                EffectSS_DrawParticle(ctxt, i);
            }
        }
    }
}

#ifdef NONMATCHING

s16 func_800B096C(s16 a0, s16 a1, s32 a2) {
    s16 ret;

    if (a2 == 0) {
        ret = a1;
    } else {
        // XXX result of the division is put in t0 instead of t8
        ret = a0 + (s16)((a1 - a0) / (f32)a2);
    }

    return ret;
}

#else

GLOBAL_ASM(
glabel func_800B096C
/* 011179 0x800B096C AFA40000 */ sw	$a0, 0X0($sp)
/* 011180 0x800B0970 AFA50004 */ sw	$a1, 0X4($sp)
/* 011181 0x800B0974 00052C00 */ sll	$a1, $a1, 16
/* 011182 0x800B0978 00042400 */ sll	$a0, $a0, 16
/* 011183 0x800B097C 00042403 */ sra	$a0, $a0, 16
/* 011184 0x800B0980 00052C03 */ sra	$a1, $a1, 16
/* 011185 0x800B0984 14C00004 */ bnez	$a2, .L_800B0998
/* 011186 0x800B0988 00A47023 */ subu	$t6, $a1, $a0
/* 011187 0x800B098C 00051C00 */ sll	$v1, $a1, 16
/* 011188 0x800B0990 1000000C */ b	.L_800B09C4
/* 011189 0x800B0994 00031C03 */ sra	$v1, $v1, 16
.L_800B0998:
/* 011190 0x800B0998 448E2000 */ mtc1	$t6, $f4
/* 011191 0x800B099C 44864000 */ mtc1	$a2, $f8
/* 011192 0x800B09A0 468021A0 */ cvt.s.w	$f6, $f4
/* 011193 0x800B09A4 468042A0 */ cvt.s.w	$f10, $f8
/* 011194 0x800B09A8 460A3403 */ div.s	$f16, $f6, $f10
/* 011195 0x800B09AC 4600848D */ trunc.w.s	$f18, $f16
/* 011196 0x800B09B0 44189000 */ mfc1	$t8, $f18
/* 011197 0x800B09B4 00000000 */ nop
/* 011198 0x800B09B8 00981821 */ addu	$v1, $a0, $t8
/* 011199 0x800B09BC 00031C00 */ sll	$v1, $v1, 16
/* 011200 0x800B09C0 00031C03 */ sra	$v1, $v1, 16
.L_800B09C4:
/* 011201 0x800B09C4 00601025 */ move	$v0, $v1
/* 011202 0x800B09C8 03E00008 */ jr	$ra
/* 011203 0x800B09CC 00000000 */ nop
)

#endif

s16 func_800B09D0(s16 a0, s16 a1, f32 a2) {
    return a2 * (a1 - a0) + a0;
}

u8 func_800B0A24(u8 a0, u8 a1, f32 a2) {
    return a2 * ((f32)a1 - (f32)a0) + a0;
}
