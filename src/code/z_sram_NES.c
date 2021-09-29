#include "global.h"

void func_80143A10(u8 owlId) {
    gSaveContext.owlActivationFlags = ((void)0, gSaveContext.owlActivationFlags) | (u16)gBitFlags[owlId];
    if (gSaveContext.unk_44 == 0xFF) {
        gSaveContext.unk_44 = owlId;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143A54.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/Sram_IncrementDay.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/Sram_CalcChecksum.s")

void func_80144628(void) {
    gSaveContext.entranceIndex = 0x1C00;
    gSaveContext.equippedMask = 0;
    gSaveContext.unk_05 = 0;
    gSaveContext.unk_06 = 0;
    gSaveContext.linkAge = 0;
    gSaveContext.isNight = false;
    gSaveContext.unk_14 = 0;
    gSaveContext.snowheadCleared = 0;
    gSaveContext.hasTatl = false;
    gSaveContext.isOwlSave = false;
    bzero(gSaveContext.newf, 0xFE8);
}

#ifdef NON_MATCHING
void Sram_GenerateRandomSaveFields(void) {
    s16 sp2A;
    s16 temp_a0;
    s16 temp_s0;
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s16 phi_v0;
    s16 phi_s0;
    s16 phi_v1;
    s16 phi_s0_2;
    s16 phi_s0_3;
    s16 phi_v1_2;
    s16 phi_s0_4;
    s32 phi_s1;
    s32 phi_s0_5;

    func_80143A54();
    gSaveContext.lotteryCodes[0][0] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[0][1] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[0][2] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[1][0] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[1][1] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[1][2] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[2][0] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[2][1] = Rand_S16Offset(0, 0xA);
    gSaveContext.lotteryCodes[2][2] = Rand_S16Offset(0, 0xA);

/*
    phi_s0 = 0;
    do {

//         phi_v0 = 0;
// loop_2:
//         phi_v0 = phi_v0 + 1;
//         if ((s32) phi_v0 < 3) {
//             goto loop_2;
//         }

        for (phi_v0 = 0; phi_v0 < 3; phi_v0++) {

        }

        phi_s0 = phi_s0 + 1;
    } while ((s32) phi_s0 < 3);
*/
    for (phi_s0 = 0; phi_s0 < 3; phi_s0++) {
        for (phi_v0 = 0; phi_v0 < 3; phi_v0++) {

        }
    }

    phi_s0_2 = 0;
    sp2A = (s16) (Rand_S16Offset(0, 0x10) & 3);
    while (phi_s0_2 != 6) {
        temp_a0 = Rand_S16Offset(0, 0x10) & 3;
        if (sp2A != temp_a0) {
            gSaveContext.spiderHouseMaskOrder[phi_s0_2] = (s8) temp_a0;
            phi_s0_2 = (s16) (phi_s0_2 + 1);
            sp2A = temp_a0;
        }
    }

    do {
// loop_8:
//         temp_v0_2 = Rand_S16Offset(0, 6);
//         if (temp_v0_2 <= 0) {
//             goto loop_8;
//         }
        do {
            temp_v0_2 = Rand_S16Offset(0, 6);
        } while (temp_v0_2 <= 0);
    } while (temp_v0_2 >= 6);

    gSaveContext.bomberCode[0] = (s8) temp_v0_2;

    phi_s0_4 = 1;
    while (phi_s0_4 != 5) {
        phi_s1 = 0;
//loop_12:
//        temp_v0_3 = Rand_S16Offset(0, 6);
//        if (temp_v0_3 <= 0) {
//            goto loop_12;
//        }
//        if (temp_v0_3 >= 6) {
//            goto loop_12;
//        }

        do {
            do {
                temp_v0_3 = Rand_S16Offset(0, 6);
            } while (temp_v0_3 <= 0);
        } while (temp_v0_3 >= 6);

        for (phi_v1_2 = 0; phi_v1_2 < phi_s0_4; phi_v1_2++) {
            if (temp_v0_3 == gSaveContext.bomberCode[phi_v1_2]) {
                phi_s1 = 1;
            }
        }

        if (phi_s1 == 0) {
            gSaveContext.bomberCode[phi_s0_4] = (s8) temp_v0_3;
            phi_s0_4 = (s16) (phi_s0_4 + 1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/Sram_GenerateRandomSaveFields.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144890.s")

extern UNK_TYPE D_801C6970;
extern UNK_TYPE D_801C6998;
extern u8 D_801C6A48[];
extern u8 D_801C6A50[];

void Sram_InitDebugSave(void) {
    func_80144628();
    Lib_MemCpy(gSaveContext.newf, &D_801C6970, 0x28);
    Lib_MemCpy(&gSaveContext.equips, &D_801C6998, 0x22);
    Lib_MemCpy(&gSaveContext.inventory, &D_801C69BC, 0x88);
    Lib_MemCpy(&gSaveContext.checksum, &D_801C6A44, 2);

    if (gSaveContext.playerForm != 4) {
        gSaveContext.equips.buttonItems[0][2] = D_801C6A48[((void)0, gSaveContext.playerForm & 0xFF)];
        gSaveContext.equips.cButtonSlots[0][2] = D_801C6A50[((void)0, gSaveContext.playerForm & 0xFF)];
    }

    gSaveContext.hasTatl = true;

    gSaveContext.horseData.scene = SCENE_F01;
    gSaveContext.horseData.pos.x = -1420;
    gSaveContext.horseData.pos.y = 257;
    gSaveContext.horseData.pos.z = -1285;
    gSaveContext.horseData.angle = -0x7554;

    gSaveContext.entranceIndex = 0x1C00;
    gSaveContext.unk_05 = 1;

    gSaveContext.weekEventReg[0xF] |= 0x20;
    gSaveContext.weekEventReg[0x3B] |= 0x04;
    gSaveContext.weekEventReg[0x1F] |= 0x04;

    gSaveContext.unk_3F68[4][16] = 1;
    gSaveContext.roomInf[99][1] = 1;
    gSaveContext.magicLevel = 0;

    Sram_GenerateRandomSaveFields();
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144E78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_8014546C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80145698.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_801457CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146580.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146628.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/Sram_Alloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147008.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147020.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147068.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147138.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147150.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147198.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147314.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147414.s")

void Sram_nop8014750C(s32 arg0) {

}
