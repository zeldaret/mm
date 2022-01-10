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
 * Converts the number of a scene to its "original" equivalent, the default version of the area which the player first
 * enters.
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
 * Copies the flags set in ActorContext over to the current scene's CycleSceneFlags, usually using the original scene
 * number. Exception for Inverted Stone Tower Temple, which uses its own.
 */
void Play_SaveCycleSceneFlags(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    CycleSceneFlags* cycleSceneFlags;

    cycleSceneFlags = &gSaveContext.cycleSceneFlags[Play_GetOriginalSceneNumber(globalCtx->sceneNum)];
    cycleSceneFlags->chest = globalCtx->actorCtx.flags.chest;
    cycleSceneFlags->swch0 = globalCtx->actorCtx.flags.switches[0];
    cycleSceneFlags->swch1 = globalCtx->actorCtx.flags.switches[1];

    if (globalCtx->sceneNum == SCENE_INISIE_R) { // Inverted Stone Tower Temple
        cycleSceneFlags = &gSaveContext.cycleSceneFlags[globalCtx->sceneNum];
    }

    cycleSceneFlags->collectible = globalCtx->actorCtx.flags.collectible[0];
    cycleSceneFlags->clearedRoom = globalCtx->actorCtx.flags.clearedRoom;
}

void Play_SetRespawnData(GameState* gameState, s32 respawnMode, u16 entranceIndex, s32 roomIndex, s32 playerParams,
                         Vec3f* pos, s16 yaw) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    gSaveContext.respawn[respawnMode].entranceIndex = Entrance_CreateIndex(entranceIndex >> 9, 0, entranceIndex & 0xF);
    gSaveContext.respawn[respawnMode].roomIndex = roomIndex;
    gSaveContext.respawn[respawnMode].pos = *pos;
    gSaveContext.respawn[respawnMode].yaw = yaw;
    gSaveContext.respawn[respawnMode].playerParams = playerParams;
    gSaveContext.respawn[respawnMode].tempSwchFlags = globalCtx->actorCtx.flags.switches[2];
    gSaveContext.respawn[respawnMode].unk_18 = globalCtx->actorCtx.flags.collectible[1];
    gSaveContext.respawn[respawnMode].tempCollectFlags = globalCtx->actorCtx.flags.collectible[2];
}

void Play_SetupRespawnPoint(GameState* gameState, s32 respawnMode, s32 playerParams) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
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

// Gameplay_TriggerVoidOut ?
// Used by Player, Ikana_Rotaryroom, Bji01, Kakasi, LiftNuts, Test4, Warptag, WarpUzu, Roomtimer
void func_80169EFC(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    gSaveContext.respawn[0].tempSwchFlags = globalCtx->actorCtx.flags.switches[2];
    gSaveContext.respawn[0].unk_18 = globalCtx->actorCtx.flags.collectible[1];
    gSaveContext.respawn[0].tempCollectFlags = globalCtx->actorCtx.flags.collectible[2];
    globalCtx->nextEntranceIndex = gSaveContext.respawn[0].entranceIndex;
    gSaveContext.respawnFlag = 1;
    func_80169ECC(globalCtx);
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 2;
}

// Gameplay_LoadToLastEntrance ?
// Used by game_over and Test7
void func_80169F78(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    globalCtx->nextEntranceIndex = gSaveContext.respawn[2].entranceIndex;
    gSaveContext.respawnFlag = -1;
    func_80169ECC(globalCtx);
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 2;
}

// Gameplay_TriggerRespawn ?
// Used for void by Wallmaster, Deku Shrine doors. Also used by Player, Kaleido, DoorWarp1
void func_80169FDC(GameState* gameState) {
    func_80169F78(gameState);
}

// Used by Kankyo to determine how to change the lighting, e.g. for game over.
s32 func_80169FFC(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    return globalCtx->roomCtx.currRoom.mesh->type0.type != 1;
}

s32 FrameAdvance_IsEnabled(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    return globalCtx->frameAdvCtx.enabled != 0;
}

// Unused, unchanged from OoT, which uses it only in one Camera function.
/**
 * @brief Tests if \p actor is a door and the sides are different rooms.
 *
 * @param[in] gameState GameState, promoted to globalCtx inside.
 * @param[in] actor Actor to test.
 * @param[out] yaw Facing angle of the actor, or reverse if in the back room.
 * @return true if \p actor is a door and the sides are in different rooms, false otherwise
 */
s32 func_8016A02C(GameState* gameState, Actor* actor, s16* yaw) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    TransitionActorEntry* transitionActor;
    s8 frontRoom;

    if (actor->category != ACTORCAT_DOOR) {
        return false;
    }

    transitionActor = &globalCtx->doorCtx.transitionActorList[(u16)actor->params >> 10];
    frontRoom = transitionActor->sides[0].room;
    if (frontRoom == transitionActor->sides[1].room) {
        return false;
    }

    if (frontRoom == actor->room) {
        *yaw = actor->shape.rot.y;
    } else {
        *yaw = actor->shape.rot.y + 0x8000;
    }

    return true;
}

// Unused
/**
 * @brief Tests if \p pos is underwater.
 *
 * @param[in] globalCtx GlobalContext
 * @param[in] pos position to test
 * @return True if inside a waterbox and not above a void.
 */
s32 Play_IsUnderwater(GlobalContext* globalCtx, Vec3f* pos) {
    WaterBox* waterBox;
    CollisionPoly* poly;
    Vec3f waterSurfacePos;
    s32 bgId;

    waterSurfacePos = *pos;

    // == true required to match.
    if ((WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, waterSurfacePos.x, waterSurfacePos.z, &waterSurfacePos.y,
                              &waterBox) == true) &&
        (pos->y < waterSurfacePos.y) &&
        (BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, &poly, &bgId, &waterSurfacePos) != BGCHECK_Y_MIN)) {
        return true;
    } else {
        return false;
    }
}

// z_demo and EnTest4
// This data appears to be a boolean. It is only set by Play_Init.
s32 func_8016A168(void) {
    return D_801D0D50;
}

// List of cutscene numbers.
extern s16 D_801D0D64[];
// s16 D_801D0D64[] = { 0xFFFD, 0xFFFE, 0xFFFC, 0xFFFB, 0xFFF9, 0xFFF5, 0xFFF8, 0xFFF7, 0xFFFA, 0xFFF0 };
// s16 D_801D0D64[] = { -3, -2, -4, -5, -7, -11, -8, -9, -6, -16 };

// Used by Player
/**
 * Sets the cutscene numbers in globalCtx->unk_1879C.
 * Set to -1 by default. If there is an ActorCutscene where unk4 matches the appropriate element of D_801D0D64 (and
 * possibly change its priority for the zeroth one)
 */
void func_8016A178(GameState* gameState, s32 cutscene) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    s32 i;
    s16* phi_s3 = globalCtx->unk_1879C;
    s16* phi_s1 = D_801D0D64;

    for (i = 0; i < ARRAY_COUNT(globalCtx->unk_1879C); i++, phi_s3++, phi_s1++) {
        ActorCutscene* actorCutscene;
        s32 currCutscene;

        *phi_s3 = -1;

        for (currCutscene = cutscene; currCutscene != -1; currCutscene = actorCutscene->additionalCutscene) {
            actorCutscene = ActorCutscene_GetCutscene(currCutscene);

            if (actorCutscene->unk4 == *phi_s1) {
                if ((actorCutscene->unk4 == -3) && (actorCutscene->priority == 0x2BC)) {
                    actorCutscene->priority = 0x226;
                }
                *phi_s3 = currCutscene;
                break;
            }
        }
    }
}

// These regs are used by Gameplay_Draw, and several actors, purpose as yet unclear.
void func_8016A268(GameState* gameState, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    MREG(64) = arg1;
    MREG(65) = arg2;
    MREG(66) = arg3;
    MREG(67) = arg4;
    MREG(68) = arg5;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Init.s")
