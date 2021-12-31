#include "global.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165460.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165608.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165630.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165658.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016566C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165690.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801656A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165E04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80165EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/D_801DFA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166060.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801660B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Fini.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801663C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166644.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801668B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166968.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80167814.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80167DE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80167F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80168DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801690CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169100.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801691F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_LoadScene.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016927C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801692C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_SceneInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169474.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801694DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_GetActiveCameraIndex.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169590.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169600.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169668.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_GetCamera.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_CameraSetAtEye.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016981C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169940.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169988.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801699D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169AC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169AFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169C84.s")

/**
 * Converts the number of a scene to its "original" equivalent, the scene with the default version which the player
 * first enters.
 */
s16 Play_GetOriginalSceneNumber(s16 sceneNum) {
    // Inverted Stone Tower Temple  -> Stone Tower Temple
    if (sceneNum == SCENE_INISIE_R) {
        return SCENE_INISIE_N;
    }

    // Purified Southern Swamp      -> Poisoned Sothern Swamp
    if (sceneNum == SCENE_20SICHITAI2) {
        return SCENE_20SICHITAI;
    }

    // Spring Mountain Village      -> Winter Mountain Village
    if (sceneNum == SCENE_10YUKIYAMANOMURA2) {
        return SCENE_10YUKIYAMANOMURA;
    }

    // Spring Goron Village         -> Winter Goron Village
    if (sceneNum == SCENE_11GORONNOSATO2) {
        return SCENE_11GORONNOSATO;
    }

    // Spring Path to Goron Village -> Winter Path to Goron Village
    if (sceneNum == SCENE_17SETUGEN2) {
        return SCENE_17SETUGEN;
    }

    // Inverted Stone Tower         -> Stone Tower
    if (sceneNum == SCENE_F41) {
        return SCENE_F40;
    }

    return sceneNum;
}

/**
 * Copies the flags set in ActorContext over to the current scene's CycleSceneFlags. Special case for Inverted Stone
 * Tower Temple
 */
void Play_SaveCycleSceneFlags(GameState* state) {
    GlobalContext* globalCtx = (GlobalContext*)state;
    CycleSceneFlags* cycleSceneFlags;

    cycleSceneFlags = &gSaveContext.cycleSceneFlags[Play_GetOriginalSceneNumber(globalCtx->sceneNum)];
    cycleSceneFlags->chest = globalCtx->actorCtx.chestFlags;
    cycleSceneFlags->swch0 = globalCtx->actorCtx.switchFlags[0];
    cycleSceneFlags->swch1 = globalCtx->actorCtx.switchFlags[1];

    if (globalCtx->sceneNum == SCENE_INISIE_R) { // Inverted Stone Tower Temple
        cycleSceneFlags = &gSaveContext.cycleSceneFlags[globalCtx->sceneNum];
    }

    cycleSceneFlags->collectible = globalCtx->actorCtx.collectibleFlags[0];
    cycleSceneFlags->clearedRoom = globalCtx->actorCtx.clearedRooms;
}

void Play_SetRespawnData(GameState* state, s32 respawnMode, u16 sceneSetup, s32 roomIndex, s32 playerParams, Vec3f* pos,
                         s16 yaw) {
    GlobalContext* globalCtx = (GlobalContext*)state;

    gSaveContext.respawn[respawnMode].entranceIndex = Entrance_CreateIndex(sceneSetup >> 9, 0, sceneSetup & 0xF);
    gSaveContext.respawn[respawnMode].roomIndex = roomIndex;
    gSaveContext.respawn[respawnMode].pos = *pos;
    gSaveContext.respawn[respawnMode].yaw = yaw;
    gSaveContext.respawn[respawnMode].playerParams = playerParams;
    gSaveContext.respawn[respawnMode].tempSwchFlags = globalCtx->actorCtx.switchFlags[2];
    gSaveContext.respawn[respawnMode].unk_18 = globalCtx->actorCtx.collectibleFlags[1];
    gSaveContext.respawn[respawnMode].tempCollectFlags = globalCtx->actorCtx.collectibleFlags[2];
}

void Play_SetupRespawnPoint(GameState* state, s32 respawnMode, s32 playerParams) {
    GlobalContext* globalCtx = (GlobalContext*)state;
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->sceneNum != SCENE_KAKUSIANA) { // Grottos
        Play_SetRespawnData(&globalCtx->state, respawnMode, (u16)((void)0, gSaveContext.entranceIndex),
                            globalCtx->roomCtx.currRoom.num, playerParams, &player->actor.world.pos,
                            player->actor.shape.rot.y);
    }
}

// Override respawn data in Sakon's Hideout
void func_80169ECC(GlobalContext* globalCtx) {
    if (globalCtx->sceneNum == SCENE_SECOM) {
        globalCtx->nextEntranceIndex = 0x2060;
        gSaveContext.respawnFlag = -7;
    }
}

// Gameplay_TriggerVoidOut
void func_80169EFC(GameState* state) {
    GlobalContext* globalCtx = (GlobalContext*)state;

    gSaveContext.respawn[0].tempSwchFlags = globalCtx->actorCtx.switchFlags[2];
    gSaveContext.respawn[0].unk_18 = globalCtx->actorCtx.collectibleFlags[1];
    gSaveContext.respawn[0].tempCollectFlags = globalCtx->actorCtx.collectibleFlags[2];
    globalCtx->nextEntranceIndex = gSaveContext.respawn[0].entranceIndex;
    gSaveContext.respawnFlag = 1;
    func_80169ECC(globalCtx);
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 2;
}

// Gameplay_LoadToLastEntrance ?
void func_80169F78(GameState* state) {
    GlobalContext* globalCtx = (GlobalContext*)state;

    globalCtx->nextEntranceIndex = gSaveContext.respawn[2].entranceIndex;
    gSaveContext.respawnFlag = -1;
    func_80169ECC(globalCtx);
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 2;
}

// Gameplay_TriggerRespawn ?
void func_80169FDC(GameState* state) {
    func_80169F78(state);
}

s32 func_80169FFC(GameState* state) {
    GlobalContext* globalCtx = (GlobalContext*)state;

    return globalCtx->roomCtx.currRoom.mesh->type0.type != 1;
}

s32 FrameAdvance_IsEnabled(GameState* state) {
    GlobalContext* globalCtx = (GlobalContext*)state;

    return globalCtx->frameAdvCtx.enabled != 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016A02C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016A0AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016A168.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016A178.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016A268.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Init.s")
