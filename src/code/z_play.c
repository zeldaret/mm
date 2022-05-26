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

s32 Play_InCsMode(GlobalContext* globalCtx) {
    return (globalCtx->csCtx.state != 0) || Player_InCsMode(&globalCtx->state);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169100.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801691F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_LoadScene.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016927C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801692C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_SceneInit.s")

void Play_GetScreenPos(GlobalContext* globalCtx, Vec3f* src, Vec3f* dest) {
    f32 cappedInvW;

    Actor_GetProjectedPos(globalCtx, src, dest, &cappedInvW);

    dest->x = (SCREEN_WIDTH / 2) + (dest->x * cappedInvW * (SCREEN_WIDTH / 2));
    dest->y = (SCREEN_HEIGHT / 2) - (dest->y * cappedInvW * (SCREEN_HEIGHT / 2));
}

s16 Play_CreateSubCamera(GlobalContext* globalCtx) {
    s16 i;

    for (i = CAM_ID_SUB_FIRST; i < NUM_CAMS; i++) {
        if (globalCtx->cameraPtrs[i] == NULL) {
            break;
        }
    }

    if (i == NUM_CAMS) {
        return CAM_ID_NONE;
    }

    globalCtx->cameraPtrs[i] = &globalCtx->subCameras[i - CAM_ID_SUB_FIRST];
    Camera_Init(globalCtx->cameraPtrs[i], &globalCtx->view, &globalCtx->colCtx, globalCtx);
    globalCtx->cameraPtrs[i]->camId = i;

    return i;
}

s16 Play_GetActiveCamId(GlobalContext* globalCtx) {
    return globalCtx->activeCamId;
}

s32 Play_CameraChangeStatus(GlobalContext* globalCtx, s16 camId, s16 status) {
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;

    if (status == CAM_STATUS_ACTIVE) {
        globalCtx->activeCamId = camIdx;
    }

    return Camera_ChangeStatus(globalCtx->cameraPtrs[camIdx], status);
}

void Play_ClearCamera(GlobalContext* globalCtx, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;

    if (globalCtx->cameraPtrs[camIdx] != NULL) {
        Camera_ChangeStatus(globalCtx->cameraPtrs[camIdx], CAM_STATUS_INACTIVE);
        globalCtx->cameraPtrs[camIdx] = NULL;
    }
}

void Play_ClearAllSubCameras(GlobalContext* globalCtx) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (globalCtx->cameraPtrs[subCamId] != NULL) {
            Play_ClearCamera(globalCtx, subCamId);
        }
    }

    globalCtx->activeCamId = CAM_ID_MAIN;
}

Camera* Play_GetCamera(GlobalContext* globalCtx, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;

    return globalCtx->cameraPtrs[camIdx];
}

s32 Play_CameraSetAtEye(GlobalContext* globalCtx, s16 camId, Vec3f* at, Vec3f* eye) {
    s32 ret = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;
    Camera* camera = globalCtx->cameraPtrs[camIdx];

    ret |= Camera_SetParam(camera, CAM_PARAM_FLAG_1, at);
    ret *= 2;
    ret |= Camera_SetParam(camera, CAM_PARAM_FLAG_2, eye);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->trackActor != NULL) {
        camera->atActorOffset.x = at->x - camera->trackActor->world.pos.x;
        camera->atActorOffset.y = at->y - camera->trackActor->world.pos.y;
        camera->atActorOffset.z = at->z - camera->trackActor->world.pos.z;
    } else {
        camera->atActorOffset.x = camera->atActorOffset.y = camera->atActorOffset.z = 0.0f;
    }

    camera->atLERPStepScale = 0.01f;

    return ret;
}

s32 Play_CameraSetAtEyeUp(GlobalContext* globalCtx, s16 camId, Vec3f* at, Vec3f* eye, Vec3f* up) {
    s32 ret = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;
    Camera* camera = globalCtx->cameraPtrs[camIdx];

    ret |= Camera_SetParam(camera, CAM_PARAM_FLAG_1, at);
    ret <<= 1;
    ret |= Camera_SetParam(camera, CAM_PARAM_FLAG_2, eye);
    ret <<= 1;
    ret |= Camera_SetParam(camera, CAM_PARAM_FLAG_4, up);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->trackActor != NULL) {
        camera->atActorOffset.x = at->x - camera->trackActor->world.pos.x;
        camera->atActorOffset.y = at->y - camera->trackActor->world.pos.y;
        camera->atActorOffset.z = at->z - camera->trackActor->world.pos.z;
    } else {
        camera->atActorOffset.x = camera->atActorOffset.y = camera->atActorOffset.z = 0.0f;
    }

    camera->atLERPStepScale = 0.01f;

    return ret;
}

s32 Play_CameraSetFov(GlobalContext* globalCtx, s16 camId, f32 fov) {
    s32 ret = Camera_SetParam(globalCtx->cameraPtrs[camId], 0x20, &fov) & 1;

    if (1) {}
    return ret;
}

s32 Play_CameraSetRoll(GlobalContext* globalCtx, s16 camId, s16 roll) {
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;
    Camera* camera = globalCtx->cameraPtrs[camIdx];

    camera->roll = roll;

    return 1;
}

void Play_CopyCamera(GlobalContext* globalCtx, s16 destCamId, s16 srcCamId) {
    s16 srcCamId2 = (srcCamId == CAM_ID_NONE) ? globalCtx->activeCamId : srcCamId;
    s16 destCamId1 = (destCamId == CAM_ID_NONE) ? globalCtx->activeCamId : destCamId;

    Camera_Copy(globalCtx->cameraPtrs[destCamId1], globalCtx->cameraPtrs[srcCamId2]);
}

s32 func_80169A50(GlobalContext* globalCtx, s16 camId, Player* player, s16 setting) {
    Camera* camera;
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;

    camera = globalCtx->cameraPtrs[camIdx];
    Camera_InitPlayerSettings(camera, player);
    return Camera_ChangeSetting(camera, setting);
}

s32 Play_CameraChangeSetting(GlobalContext* globalCtx, s16 camId, s16 setting) {
    return Camera_ChangeSetting(Play_GetCamera(globalCtx, camId), setting);
}

void func_80169AFC(GlobalContext* globalCtx, s16 camId, s16 arg2) {
    s16 camIdx = (camId == CAM_ID_NONE) ? globalCtx->activeCamId : camId;
    s16 i;

    Play_ClearCamera(globalCtx, camIdx);

    for (i = CAM_ID_SUB_FIRST; i < NUM_CAMS; i++) {
        if (globalCtx->cameraPtrs[i] != NULL) {
            Play_ClearCamera(globalCtx, i);
        }
    }

    if (arg2 <= 0) {
        Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, CAM_STATUS_ACTIVE);
        globalCtx->cameraPtrs[CAM_ID_MAIN]->childCamId = globalCtx->cameraPtrs[CAM_ID_MAIN]->doorTimer2 = CAM_ID_MAIN;
    }
}

s16 Play_CameraGetUID(GlobalContext* globalCtx, s16 camId) {
    Camera* camera = globalCtx->cameraPtrs[camId];

    if (camera != NULL) {
        return camera->uid;
    } else {
        return -1;
    }
}

s16 func_80169BF8(GlobalContext* globalCtx, s16 camId, s16 arg2) {
    Camera* camera = globalCtx->cameraPtrs[camId];

    if (camera != NULL) {
        return 0;
    } else if (camera->uid != arg2) {
        return 0;
    } else if (camera->status != CAM_STATUS_ACTIVE) {
        return 2;
    } else {
        return 1;
    }
}

u16 Play_GetCsCamDataSetting(GlobalContext* globalCtx, s32 camId) {
    CsCamData* csCamData = &globalCtx->csCamData[camId];

    return csCamData->setting;
}

Vec3s* Play_GetCsCamDataVec3s(GlobalContext* globalCtx, s32 camId) {
    CsCamData* csCamData = &globalCtx->csCamData[camId];

    return Lib_SegmentedToVirtual(csCamData->data);
}

/**
 * Converts the number of a scene to its "original" equivalent, the default version of the area which the player first
 * enters.
 */
s16 Play_GetOriginalSceneNumber(s16 sceneNum) {
    // Inverted Stone Tower Temple -> Stone Tower Temple
    if (sceneNum == SCENE_INISIE_R) {
        return SCENE_INISIE_N;
    }

    // Purified Southern Swamp -> Poisoned Sothern Swamp
    if (sceneNum == SCENE_20SICHITAI2) {
        return SCENE_20SICHITAI;
    }

    // Spring Mountain Village -> Winter Mountain Village
    if (sceneNum == SCENE_10YUKIYAMANOMURA2) {
        return SCENE_10YUKIYAMANOMURA;
    }

    // Spring Goron Village -> Winter Goron Village
    if (sceneNum == SCENE_11GORONNOSATO2) {
        return SCENE_11GORONNOSATO;
    }

    // Spring Path to Goron Village -> Winter Path to Goron Village
    if (sceneNum == SCENE_17SETUGEN2) {
        return SCENE_17SETUGEN;
    }

    // Inverted Stone Tower -> Stone Tower
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
    cycleSceneFlags->switch0 = globalCtx->actorCtx.flags.switches[0];
    cycleSceneFlags->switch1 = globalCtx->actorCtx.flags.switches[1];

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
    gSaveContext.respawn[respawnMode].tempSwitchFlags = globalCtx->actorCtx.flags.switches[2];
    gSaveContext.respawn[respawnMode].unk_18 = globalCtx->actorCtx.flags.collectible[1];
    gSaveContext.respawn[respawnMode].tempCollectFlags = globalCtx->actorCtx.flags.collectible[2];
}

void Play_SetupRespawnPoint(GameState* gameState, s32 respawnMode, s32 playerParams) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->sceneNum != SCENE_KAKUSIANA) { // Grottos
        Play_SetRespawnData(&globalCtx->state, respawnMode, (u16)((void)0, gSaveContext.save.entranceIndex),
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

    gSaveContext.respawn[RESTART_MODE_DOWN].tempSwitchFlags = globalCtx->actorCtx.flags.switches[2];
    gSaveContext.respawn[RESTART_MODE_DOWN].unk_18 = globalCtx->actorCtx.flags.collectible[1];
    gSaveContext.respawn[RESTART_MODE_DOWN].tempCollectFlags = globalCtx->actorCtx.flags.collectible[2];
    globalCtx->nextEntranceIndex = gSaveContext.respawn[RESTART_MODE_DOWN].entranceIndex;
    gSaveContext.respawnFlag = 1;
    func_80169ECC(globalCtx);
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 2;
}

// Gameplay_LoadToLastEntrance ?
// Used by game_over and Test7
void func_80169F78(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    globalCtx->nextEntranceIndex = gSaveContext.respawn[RESTART_MODE_TOP].entranceIndex;
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
 * @return true if inside a waterbox and not above a void.
 */
s32 Play_IsUnderwater(GlobalContext* globalCtx, Vec3f* pos) {
    WaterBox* waterBox;
    CollisionPoly* poly;
    Vec3f waterSurfacePos;
    s32 bgId;

    waterSurfacePos = *pos;

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

// A mapping from playerActorCsIds to sGlobalCamDataSettings indices.
extern s16 D_801D0D64[];
// s16 D_801D0D64[] = { -3, -2, -4, -5, -7, -11, -8, -9, -6, -16 };

// Used by Player
/**
 * Extract the common actor cutscene ids used by Player from the scene and set the actor cutscene ids in
 * globalCtx->playerActorCsIds. If a playerActorCsId is not present in the scene, then that particular id is set
 * to -1. Otherwise, if there is an ActorCutscene where csCamSceneDataId matches the appropriate element of D_801D0D64,
 * set the corresponding playerActorCsId (and possibly change its priority for the zeroth one)
 */
void Play_AssignPlayerActorCsIdsFromScene(GameState* gameState, s32 startActorCsId) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    s32 i;
    s16* curPlayerActorCsId = globalCtx->playerActorCsIds;
    s16* phi_s1 = D_801D0D64;

    for (i = 0; i < ARRAY_COUNT(globalCtx->playerActorCsIds); i++, curPlayerActorCsId++, phi_s1++) {
        ActorCutscene* actorCutscene;
        s32 curActorCsId;

        *curPlayerActorCsId = -1;

        for (curActorCsId = startActorCsId; curActorCsId != -1; curActorCsId = actorCutscene->additionalCutscene) {
            actorCutscene = ActorCutscene_GetCutscene(curActorCsId);

            if (actorCutscene->csCamSceneDataId == *phi_s1) {
                if ((actorCutscene->csCamSceneDataId == -3) &&
                    (actorCutscene->priority == 700)) { // override ocarina cs priority
                    actorCutscene->priority = 550;
                }
                *curPlayerActorCsId = curActorCsId;
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
