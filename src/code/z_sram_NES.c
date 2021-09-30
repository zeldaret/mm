#include "global.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"

#define CHECK_NEWF(newf)                                                                                 \
    ((newf)[0] != 'Z' || (newf)[1] != 'E' || (newf)[2] != 'L' || (newf)[3] != 'D' || (newf)[4] != 'A' || \
     (newf)[5] != '3')



extern s32 D_801C6818[];
extern s32 D_801C67C8[];
extern s32 D_801C67F0[];
extern s32 D_801C6840[];
extern s32 D_801C6850[];

extern UNK_TYPE D_801C6898;
extern UNK_TYPE D_801C68C0;

extern UNK_TYPE D_801C6970;
extern UNK_TYPE D_801C6998;
extern u8 D_801C6A48[];
extern u8 D_801C6A50[];
extern s32 D_801C67CC[];
extern s32 D_801C67F4[];



void func_80143A10(u8 owlId) {
    gSaveContext.save.playerData.owlActivationFlags = ((void)0, gSaveContext.save.playerData.owlActivationFlags) | (u16)gBitFlags[owlId];
    if (gSaveContext.save.playerData.unk_20 == 0xFF) {
        gSaveContext.save.playerData.unk_20 = owlId;
    }
}

void func_80143A54(void) {
    gSaveContext.save.roomInf[127][3] = (gSaveContext.save.roomInf[127][3] & 0xFFFF) | 0x130000;
    gSaveContext.save.roomInf[127][3] = (gSaveContext.save.roomInf[127][3] & 0xFFFF0000) | 0xA;
    gSaveContext.save.roomInf[127][4] = 0x1770;
    gSaveContext.save.roomInf[127][6] = (gSaveContext.save.roomInf[127][6] & 0xFFFF0000) | 0x27;
    gSaveContext.save.roomInf[127][6] = (gSaveContext.save.roomInf[127][6] & 0xFFFF) | 0xA0000;
    gSaveContext.save.roomInf[123][0] = 0x1D4C;
    gSaveContext.save.roomInf[123][1] = 0x1D4C;
    gSaveContext.save.roomInf[123][2] = 0x1DB0;
}

void func_80143AC4(void) {
    gSaveContext.save.weekEventReg[55] &= 0xFD;
    gSaveContext.save.weekEventReg[90] &= 0xFE;
    gSaveContext.save.weekEventReg[89] &= 0xBF;
    gSaveContext.save.weekEventReg[89] &= 0xF7;
    gSaveContext.save.weekEventReg[85] &= 0x7F;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143B0C.s")

void Sram_IncrementDay(void) {
    if (CURRENT_DAY < 4) {
        gSaveContext.save.day++;
        gSaveContext.save.daysElapsed++;
    }

    gSaveContext.save.bombersCaughtNum = 0;
    gSaveContext.save.bombersCaughtOrder[0] = 0;
    gSaveContext.save.bombersCaughtOrder[1] = 0;
    gSaveContext.save.bombersCaughtOrder[2] = 0;
    gSaveContext.save.bombersCaughtOrder[3] = 0;
    gSaveContext.save.bombersCaughtOrder[4] = 0;
    gSaveContext.save.weekEventReg[0x49] &= (u8)~0x10;
    gSaveContext.save.weekEventReg[0x55] &= (u8)~0x02;
}

u16 Sram_CalcChecksum(void* data, size_t count) {
    u8* dataPtr = data;
    u16 chkSum = 0;

    while (count-- > 0) {
        chkSum += *dataPtr;
        dataPtr++;
    }
    return chkSum;
}

void func_80144628(void) {
    gSaveContext.save.entranceIndex = 0x1C00;
    gSaveContext.save.equippedMask = 0;
    gSaveContext.save.firstCycleFlag = 0;
    gSaveContext.save.unk_06 = 0;
    gSaveContext.save.linkAge = 0;
    gSaveContext.save.isNight = false;
    gSaveContext.save.daySpeed = 0;
    gSaveContext.save.snowheadCleared = 0;
    gSaveContext.save.hasTatl = false;
    gSaveContext.save.isOwlSave = false;

    // Instead of bloating all save context accesses with an extra sub-struct, the size of the would-be sub-struct
    // is calculated manually
    bzero(&gSaveContext.save.playerData, sizeof(Save) - OFFSETOF(Save, playerData));
}

void Sram_GenerateRandomSaveFields(void) {
    s32 randBombers;
    s16 sp2A;
    s16 phi_v1_2;
    s16 i;
    s16 j;
    s32 k;
    s16 randSpiderHouse;

    func_80143A54();

    gSaveContext.save.lotteryCodes[0][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[0][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[0][2] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][2] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][2] = Rand_S16Offset(0, 10);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

        }
    }

    i = 0;
    sp2A = Rand_S16Offset(0, 16) & 3;
    k = 6;
    while (i != k) {
        randSpiderHouse = Rand_S16Offset(0, 16) & 3;
        if (sp2A != randSpiderHouse) {
            gSaveContext.save.spiderHouseMaskOrder[i] = randSpiderHouse;
            i++;
            sp2A = randSpiderHouse;
        }
    }

    do {
        randBombers = Rand_S16Offset(0, 6);
    } while (randBombers <= 0 || randBombers >= 6);

    gSaveContext.save.bomberCode[0] = randBombers;

    i = 1;
    while (i != 5) {
        k = false;

        do {
            randBombers = Rand_S16Offset(0, 6);
        } while (randBombers <= 0 || randBombers >= 6);

        sp2A = 0;
        do {
            if (randBombers == gSaveContext.save.bomberCode[sp2A]) {
                k = true;
            }
            sp2A++;
        }while (sp2A < i);

        if (k == false) {
            gSaveContext.save.bomberCode[i] = randBombers;
            i++;
        }
    }
}

void func_80144890(void) {
    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.save.daysElapsed = 0;
    gSaveContext.save.day = 0;
    gSaveContext.save.time = CLOCK_TIME(6, 0)-1;
    func_80144628();

    Lib_MemCpy(&gSaveContext.save.playerData, &D_801C6898, sizeof(SavePlayerData));
    Lib_MemCpy(&gSaveContext.save.equips, &D_801C68C0, sizeof(ItemEquips));
    Lib_MemCpy(&gSaveContext.save.inventory, &gSaveDefaultInventory, sizeof(Inventory));
    Lib_MemCpy(&gSaveContext.save.checksum, &gSaveDefaultChecksum, sizeof(gSaveContext.save.checksum));

    gSaveContext.save.horseData.scene = SCENE_F01;
    gSaveContext.save.horseData.pos.x = -1420;
    gSaveContext.save.horseData.pos.y = 257;
    gSaveContext.save.horseData.pos.z = -1285;
    gSaveContext.save.horseData.angle = -0x7554;

    gSaveContext.nextCutsceneIndex = 0;
    gSaveContext.save.playerData.magicLevel = 0;
    Sram_GenerateRandomSaveFields();
}

void Sram_InitDebugSave(void) {
    func_80144628();

    Lib_MemCpy(&gSaveContext.save.playerData, &D_801C6970, sizeof(SavePlayerData));
    Lib_MemCpy(&gSaveContext.save.equips, &D_801C6998, sizeof(ItemEquips));
    Lib_MemCpy(&gSaveContext.save.inventory, &D_801C69BC, sizeof(Inventory));
    Lib_MemCpy(&gSaveContext.save.checksum, &D_801C6A44, sizeof(gSaveContext.save.checksum));

    if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
        gSaveContext.save.equips.buttonItems[0][2] = D_801C6A48[((void)0, gSaveContext.save.playerForm & 0xFF)];
        gSaveContext.save.equips.cButtonSlots[0][2] = D_801C6A50[((void)0, gSaveContext.save.playerForm & 0xFF)];
    }

    gSaveContext.save.hasTatl = true;

    gSaveContext.save.horseData.scene = SCENE_F01;
    gSaveContext.save.horseData.pos.x = -1420;
    gSaveContext.save.horseData.pos.y = 257;
    gSaveContext.save.horseData.pos.z = -1285;
    gSaveContext.save.horseData.angle = -0x7554;

    gSaveContext.save.entranceIndex = 0x1C00;
    gSaveContext.save.firstCycleFlag = 1;

    gSaveContext.save.weekEventReg[0x0F] |= 0x20;
    gSaveContext.save.weekEventReg[0x3B] |= 0x04;
    gSaveContext.save.weekEventReg[0x1F] |= 0x04;

    gSaveContext.cycleSceneFlags[99][1] = 1;
    gSaveContext.save.roomInf[99][1] = 1;
    gSaveContext.save.playerData.magicLevel = 0;

    Sram_GenerateRandomSaveFields();
}

void func_80144A94(SramContext* sramCtx) {
    s32 i;
    s32 cutscene = gSaveContext.save.cutscene;

    bzero(sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));

    if (func_80185968(sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]) !=
        0) {
        func_80185968(sramCtx->saveBuf, D_801C67CC[gSaveContext.fileNum * 2], D_801C67F4[gSaveContext.fileNum * 2]);
    }
    Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));
    if (CHECK_NEWF(gSaveContext.save.playerData.newf)) {
        func_80185968(sramCtx->saveBuf, D_801C67CC[gSaveContext.fileNum * 2], D_801C67F4[gSaveContext.fileNum * 2]);
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, sizeof(Save));
    }
    gSaveContext.save.cutscene = cutscene;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
        gSaveContext.eventInf[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.cycleSceneFlags[i][0] = gSaveContext.save.roomInf[i][0];
        gSaveContext.cycleSceneFlags[i][1] = gSaveContext.save.roomInf[i][1];
        gSaveContext.cycleSceneFlags[i][2] = gSaveContext.save.roomInf[i][2];
        gSaveContext.cycleSceneFlags[i][3] = gSaveContext.save.roomInf[i][3];
        gSaveContext.cycleSceneFlags[i][4] = gSaveContext.save.roomInf[i][4];
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.unk_3DD0); i++) {
        gSaveContext.unk_3DD0[i] = 0;
        gSaveContext.unk_3DE0[i] = 0;
        gSaveContext.unk_3E18[i] = 0;
        gSaveContext.unk_3E50[i] = 0;
        gSaveContext.unk_3E88[i] = 0;
        gSaveContext.unk_3EC0[i] = 0;
    }

    D_801BDAA0 = 1;
    D_801BDA9C = 0;
    gSaveContext.powderKegTimer = 0;
    gSaveContext.unk_1014 = 0;
    gSaveContext.jinxTimer = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144E78.s")

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_8014546C.s")
void func_8014546C(SramContext* sramCtx) {
    s32 i;

    if (gSaveContext.save.isOwlSave) {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.save.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
            gSaveContext.save.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
            gSaveContext.save.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
            gSaveContext.save.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
            gSaveContext.save.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
        }

        gSaveContext.save.checksum = 0;
        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, OFFSETOF(SaveContext, fileNum));

        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, OFFSETOF(SaveContext, fileNum));
    } else {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.save.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
            gSaveContext.save.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
            gSaveContext.save.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
            gSaveContext.save.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
            gSaveContext.save.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
        }

        gSaveContext.save.checksum = 0;
        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, sizeof(Save));

        if (gSaveContext.unk_3F3F) {
            Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, sizeof(Save));
            Lib_MemCpy(&(*sramCtx->saveBuf)[0x2000], &gSaveContext, sizeof(Save));
        }
    }
}

/**
 * Save permanent scene flags, calculate checksum, copy save context to the save buffer
 */
void func_80145698(SramContext* sramCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.save.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
        gSaveContext.save.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
        gSaveContext.save.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
        gSaveContext.save.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
        gSaveContext.save.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
    }

    gSaveContext.save.checksum = 0;
    gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, sizeof(Save));
    if (gSaveContext.unk_3F3F != 0) {
        Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext, sizeof(Save));
        Lib_MemCpy(&(*sramCtx->saveBuf)[0x2000], &gSaveContext, sizeof(Save));
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_801457CC.s")

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146580.s")

extern u16 D_801F6AF0;
extern u8 D_801F6AF2;

void func_80146580(GameState* gameState, SramContext* sramCtx, s32 fileNum) {
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    s32 pad;

    if (gSaveContext.unk_3F3F) {
        if (fileChooseCtx->unk_2446A[fileNum]) {
            func_80147314(sramCtx, fileNum);
            fileChooseCtx->unk_2446A[fileNum] = 0;
        }
        bzero(sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, sizeof(Save));
    }
    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146628.s")

void func_80146AA0(GameState* gameState, SramContext* sramCtx) {
    s32 phi_v0;
    u16 phi_v1;
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    s16 phi_a0;

    if (gSaveContext.unk_3F3F) {
        func_80144890();
        if (fileChooseCtx->unk_24480 == 0) {
            gSaveContext.save.cutscene = 0xFFF0;
        }

        for (phi_v0 = 0; phi_v0 != ARRAY_COUNT(gSaveContext.save.playerData.playerName); phi_v0++) {
            gSaveContext.save.playerData.playerName[phi_v0] =
                fileChooseCtx->unk_24414[fileChooseCtx->unk_24480][phi_v0];
        }

        gSaveContext.save.playerData.newf[0] = 'Z';
        gSaveContext.save.playerData.newf[1] = 'E';
        gSaveContext.save.playerData.newf[2] = 'L';
        gSaveContext.save.playerData.newf[3] = 'D';
        gSaveContext.save.playerData.newf[4] = 'A';
        gSaveContext.save.playerData.newf[5] = '3';

        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, sizeof(Save));

        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, sizeof(Save));
        Lib_MemCpy(&(*sramCtx->saveBuf)[0x2000], &gSaveContext, sizeof(Save));

        for (phi_v1 = 0; phi_v1 < ARRAY_COUNT(gSaveContext.save.playerData.newf); phi_v1++) {
            fileChooseCtx->newf[fileChooseCtx->unk_24480][phi_v1] = gSaveContext.save.playerData.newf[phi_v1];
        }

        fileChooseCtx->unk_2440C[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.deaths;

        for (phi_v1 = 0; phi_v1 < ARRAY_COUNT(gSaveContext.save.playerData.playerName); phi_v1++) {
            fileChooseCtx->unk_24414[fileChooseCtx->unk_24480][phi_v1] =
                gSaveContext.save.playerData.playerName[phi_v1];
        }

        fileChooseCtx->healthCapacity[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.healthCapacity;
        fileChooseCtx->health[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.health;
        fileChooseCtx->unk_24454[fileChooseCtx->unk_24480] = gSaveContext.save.inventory.dungeonKeys[9];
        fileChooseCtx->unk_24444[fileChooseCtx->unk_24480] = gSaveContext.save.inventory.questItems;
        fileChooseCtx->unk_24458[fileChooseCtx->unk_24480] = gSaveContext.save.time;
        fileChooseCtx->unk_24460[fileChooseCtx->unk_24480] = gSaveContext.save.day;
        fileChooseCtx->unk_24468[fileChooseCtx->unk_24480] = gSaveContext.save.isOwlSave;
        fileChooseCtx->rupees[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.rupees;
        fileChooseCtx->unk_24474[fileChooseCtx->unk_24480] =
            (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

        for (phi_v1 = 0, phi_a0 = 0; phi_v1 < 24; phi_v1++) {
            if (gSaveContext.save.inventory.masks[(s32)phi_v1] != 0xFF) {
                phi_a0++;
            }
        }

        fileChooseCtx->unk_24478[fileChooseCtx->unk_24480] = phi_a0;
        fileChooseCtx->unk_2447C[fileChooseCtx->unk_24480] =
            (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
    }
    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}

void func_80146DF8(SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F) {
        gSaveContext.language = 1;
        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext.optionId, 6);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146E40.s")

void Sram_Alloc(GameState* gamestate, SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F != 0) {
        sramCtx->saveBuf = THA_AllocEndAlign16(&gamestate->heap, 0x4000);
        sramCtx->status = 0;
    }
}

void func_80146EBC(SramContext* sramCtx, s32 curPage, s32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    func_80185F64(sramCtx->saveBuf, curPage, numPages);
}


void func_80146EE8(GameState* gameState) {
    s32 pad;
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    SramContext* sramCtx = &globalCtx->sramCtx;

    gSaveContext.save.firstCycleFlag = 1;
    gSaveContext.save.isOwlSave = false;
    func_80145698(sramCtx);
    func_80185F64(sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C6818[gSaveContext.fileNum * 2]);
}


void func_80146F5C(GameState* gameState) {
    s32 cutscene;
    s32 day;
    u16 time;
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    cutscene = gSaveContext.save.cutscene;
    time = gSaveContext.save.time;
    day = gSaveContext.save.day;
    gSaveContext.save.weekEventReg[0x54] &= (u8)0xDF;

    func_80143B0C(globalCtx);
    func_8014546C(&globalCtx->sramCtx);

    gSaveContext.save.day = day;
    gSaveContext.save.time = time;
    gSaveContext.save.cutscene = cutscene;
    func_80185F64(globalCtx->sramCtx.saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]);
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

void func_80147314(SramContext* sramCtx, s32 fileNum) {
    s32 pad;

    gSaveContext.save.isOwlSave = false;

    gSaveContext.save.playerData.newf[0] = '\0';
    gSaveContext.save.playerData.newf[1] = '\0';
    gSaveContext.save.playerData.newf[2] = '\0';
    gSaveContext.save.playerData.newf[3] = '\0';
    gSaveContext.save.playerData.newf[4] = '\0';
    gSaveContext.save.playerData.newf[5] = '\0';

    gSaveContext.save.checksum = 0;
    gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, 0x3CA0);

    Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, 0x3CA0);
    func_80146EBC(sramCtx, D_801C6840[fileNum*2], D_801C6850[fileNum*2]);
    func_80146EBC(sramCtx, D_801C6840[fileNum*2+1], D_801C6850[fileNum*2]);

    gSaveContext.save.isOwlSave = true;

    gSaveContext.save.playerData.newf[0] = 'Z';
    gSaveContext.save.playerData.newf[1] = 'E';
    gSaveContext.save.playerData.newf[2] = 'L';
    gSaveContext.save.playerData.newf[3] = 'D';
    gSaveContext.save.playerData.newf[4] = 'A';
    gSaveContext.save.playerData.newf[5] = '3';
}

void func_80147414(SramContext* sramCtx, s32 fileNum, s32 arg2) {
    s32 pad;

    // Clear save buffer
    bzero(sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));

    // Read save file
    if (func_80185968(sramCtx->saveBuf, D_801C6840[fileNum*2], D_801C6850[fileNum*2]) != 0) {
        // If failed, read backup save file
        func_80185968(sramCtx->saveBuf, D_801C6840[fileNum*2+1], D_801C6850[fileNum*2+1]);
    }

    // Copy buffer to save context
    Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, 0x3CA0);

    func_80146EBC(sramCtx, D_801C6840[arg2*2], D_801C6850[arg2*2]);
    func_80146EBC(sramCtx, D_801C6840[arg2*2+1], D_801C6850[arg2*2]);
}

void Sram_nop8014750C(s32 arg0) {
}
