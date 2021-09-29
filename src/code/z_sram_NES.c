#include "global.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"



extern s32 D_801C6818[];
extern s32 D_801C67C8[];
extern s32 D_801C67F0[];

// fake probably
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} struct_801C6840;

extern struct_801C6840 D_801C6840[];
extern struct_801C6840 D_801C6850[];


void func_80143A10(u8 owlId) {
    gSaveContext.owlActivationFlags = ((void)0, gSaveContext.owlActivationFlags) | (u16)gBitFlags[owlId];
    if (gSaveContext.unk_44 == 0xFF) {
        gSaveContext.unk_44 = owlId;
    }
}

void func_80143A54(void) {
    //gSaveContext.save.roomInf[127][3] = (gSaveContext.save.roomInf[127][3] & 0xFFFF) | 0x130000;
    //gSaveContext.save.roomInf[127][3] = (gSaveContext.save.roomInf[127][3] & 0xFFFF0000) | 0xA;
    //gSaveContext.save.roomInf[127][4] = 0x1770;
    //gSaveContext.save.roomInf[127][6] = (gSaveContext.save.roomInf[127][6] & 0xFFFF0000) | 0x27;
    //gSaveContext.save.roomInf[127][6] = (gSaveContext.save.roomInf[127][6] & 0xFFFF) | 0xA0000;
    //gSaveContext.save.roomInf[123][0] = 0x1D4C;
    //gSaveContext.save.roomInf[123][1] = 0x1D4C;
    //gSaveContext.save.roomInf[123][2] = 0x1DB0;
    gSaveContext.roomInf[127][3] = (gSaveContext.roomInf[127][3] & 0xFFFF) | 0x130000;
    gSaveContext.roomInf[127][3] = (gSaveContext.roomInf[127][3] & 0xFFFF0000) | 0xA;
    gSaveContext.roomInf[127][4] = 0x1770;
    gSaveContext.roomInf[127][6] = (gSaveContext.roomInf[127][6] & 0xFFFF0000) | 0x27;
    gSaveContext.roomInf[127][6] = (gSaveContext.roomInf[127][6] & 0xFFFF) | 0xA0000;
    gSaveContext.roomInf[123][0] = 0x1D4C;
    gSaveContext.roomInf[123][1] = 0x1D4C;
    gSaveContext.roomInf[123][2] = 0x1DB0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143B0C.s")

void Sram_IncrementDay(void) {
    if (CURRENT_DAY < 4) {
        gSaveContext.day++;
        gSaveContext.daysElapsed++;
    }

    gSaveContext.unk_FE6 = 0;
    gSaveContext.unk_FE7[0] = 0;
    gSaveContext.unk_FE7[1] = 0;
    gSaveContext.unk_FE7[2] = 0;
    gSaveContext.unk_FE7[3] = 0;
    gSaveContext.unk_FE7[4] = 0;
    gSaveContext.weekEventReg[0x49] &= (u8)~0x10;
    gSaveContext.weekEventReg[0x55] &= (u8)~0x02;
}

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

extern UNK_TYPE D_801C6898;
extern UNK_TYPE D_801C68C0;
void func_80144890(void) {
    gSaveContext.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.daysElapsed = 0;
    gSaveContext.day = 0;
    gSaveContext.time = CLOCK_TIME(6, 0)-1;
    func_80144628();

    Lib_MemCpy(gSaveContext.newf, &D_801C6898, 0x28);
    Lib_MemCpy(&gSaveContext.equips, &D_801C68C0, 0x22);
    Lib_MemCpy(&gSaveContext.inventory, &gSaveDefaultInventory, 0x88);
    Lib_MemCpy(&gSaveContext.checksum, &gSaveDefaultChecksum, 2);

    gSaveContext.horseData.scene = SCENE_F01;
    gSaveContext.horseData.pos.x = -1420;
    gSaveContext.horseData.pos.y = 257;
    gSaveContext.horseData.pos.z = -1285;
    gSaveContext.horseData.angle = -0x7554;

    gSaveContext.nextCutsceneIndex = 0;
    gSaveContext.magicLevel = 0;
    Sram_GenerateRandomSaveFields();
}


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

    gSaveContext.cycleSceneFlags[99][1] = 1;
    gSaveContext.roomInf[99][1] = 1;
    gSaveContext.magicLevel = 0;

    Sram_GenerateRandomSaveFields();
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144E78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_8014546C.s")

void func_80145698(SramContext* sramCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
        gSaveContext.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
        gSaveContext.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
        gSaveContext.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
        gSaveContext.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
    }

    gSaveContext.checksum = 0;
    gSaveContext.checksum = Sram_CalcChecksum((u8* ) &gSaveContext, 0x100CU);
    if (gSaveContext.unk_3F3F != 0) {
        Lib_MemCpy(sramCtx->flashReadBuff, &gSaveContext, 0x100C);
        Lib_MemCpy((sramCtx->flashReadBuff + 0x2000/4), &gSaveContext, 0x100C);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_801457CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146580.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146628.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146E40.s")

void Sram_Alloc(GameState* gamestate, SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F != 0) {
        sramCtx->flashReadBuff = THA_AllocEndAlign16(&gamestate->heap, 0x4000);
        sramCtx->status = 0;
    }
}

void func_80146EBC(SramContext* sramCtx, s32 curPage, s32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    func_80185F64(sramCtx->flashReadBuff, curPage, numPages);
}


void func_80146EE8(GameState* gameState) {
    s32 pad;
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    SramContext* sramCtx = &globalCtx->sramCtx;

    gSaveContext.unk_05 = 1;
    gSaveContext.isOwlSave = false;
    func_80145698(sramCtx);
    func_80185F64(sramCtx->flashReadBuff, D_801C67C8[gSaveContext.fileNum * 2], D_801C6818[gSaveContext.fileNum * 2]);
}


void func_80146F5C(GameState* gameState) {
    s32 cutscene;
    s32 day;
    u16 time;
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    cutscene = gSaveContext.cutscene;
    time = gSaveContext.time;
    day = gSaveContext.day;
    gSaveContext.weekEventReg[0x54] &= (u8)0xDF;

    func_80143B0C(globalCtx);
    func_8014546C(&globalCtx->sramCtx);

    gSaveContext.day = day;
    gSaveContext.time = time;
    gSaveContext.cutscene = cutscene;
    func_80185F64(globalCtx->sramCtx.flashReadBuff, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]);
}


void func_80147008(SramContext* sramCtx, u32 curPage, u32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    sramCtx->status = 1;
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147020.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147068.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147138.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147150.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147198.s")

#ifdef NON_MATCHING
void func_80147314(SramContext* sramCtx, s32 arg1) {
    s32 pad;

    gSaveContext.isOwlSave = 0;
    gSaveContext.newf[0] = 0;
    gSaveContext.newf[1] = 0;
    gSaveContext.newf[2] = 0;
    gSaveContext.newf[3] = 0;
    gSaveContext.newf[4] = 0;
    gSaveContext.newf[5] = 0;
    gSaveContext.checksum = 0;
    gSaveContext.checksum = Sram_CalcChecksum((u8* ) &gSaveContext, 0x3CA0);
    Lib_MemCpy(sramCtx->flashReadBuff, &gSaveContext, 0x3CA0);
    func_80146EBC(sramCtx, D_801C6840[arg1].unk_00, D_801C6850[arg1].unk_00);
    func_80146EBC(sramCtx, D_801C6840[arg1].unk_04, D_801C6850[arg1].unk_00);
    gSaveContext.isOwlSave = 1;
    gSaveContext.newf[0] = 'Z';
    gSaveContext.newf[1] = 'E';
    gSaveContext.newf[2] = 'L';
    gSaveContext.newf[3] = 'D';
    gSaveContext.newf[4] = 'A';
    gSaveContext.newf[5] = '3';
}
#else
void func_80147314(SramContext* sramCtx, s32 arg1);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147314.s")
#endif

#ifdef NON_MATCHING
void func_80147414(SramContext* sramCtx, s32 arg1, s32 arg2) {
    s32 pad;

    bzero(sramCtx->flashReadBuff, 0x4000);
    if (func_80185968(sramCtx->flashReadBuff, D_801C6840[arg1].unk_00, D_801C6850[arg1].unk_00) != 0) {
        func_80185968(sramCtx->flashReadBuff, D_801C6840[arg1].unk_04, D_801C6850[arg1].unk_04);
    }

    Lib_MemCpy(&gSaveContext, sramCtx->flashReadBuff, 0x3CA0);
    func_80146EBC(sramCtx, D_801C6840[arg2].unk_00, D_801C6850[arg2].unk_00);
    func_80146EBC(sramCtx, D_801C6840[arg2].unk_04, D_801C6850[arg2].unk_00);
}
#else
void func_80147414(SramContext* sramCtx, s32 arg1, s32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80147414.s")
#endif

void Sram_nop8014750C(s32 arg0) {
}
