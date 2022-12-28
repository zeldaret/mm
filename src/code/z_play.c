#include "global.h"
#include "z64quake.h"
#include "z64shrink_window.h"
#include "z64view.h"

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_CompressI8ToI5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_DecompressI5ToI8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801668B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166968.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80166B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80167DE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80167F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80168DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Main.s")

s32 Play_InCsMode(PlayState* this) {
    return (this->csCtx.state != 0) || Player_InCsMode(this);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_80169100.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801691F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_LoadScene.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_8016927C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/func_801692C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_SceneInit.s")

void Play_GetScreenPos(PlayState* this, Vec3f* worldPos, Vec3f* screenPos) {
    f32 invW;

    // screenPos temporarily stores the projectedPos
    Actor_GetProjectedPos(this, worldPos, screenPos, &invW);

    screenPos->x = (SCREEN_WIDTH / 2) + (screenPos->x * invW * (SCREEN_WIDTH / 2));
    screenPos->y = (SCREEN_HEIGHT / 2) - (screenPos->y * invW * (SCREEN_HEIGHT / 2));
}

s16 Play_CreateSubCamera(PlayState* this) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (this->cameraPtrs[subCamId] == NULL) {
            break;
        }
    }

    // if no subCameras available
    if (subCamId == NUM_CAMS) {
        return CAM_ID_NONE;
    }

    this->cameraPtrs[subCamId] = &this->subCameras[subCamId - CAM_ID_SUB_FIRST];
    Camera_Init(this->cameraPtrs[subCamId], &this->view, &this->colCtx, this);
    this->cameraPtrs[subCamId]->camId = subCamId;

    return subCamId;
}

s16 Play_GetActiveCamId(PlayState* this) {
    return this->activeCamId;
}

s32 Play_ChangeCameraStatus(PlayState* this, s16 camId, s16 status) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    if (status == CAM_STATUS_ACTIVE) {
        this->activeCamId = camIdx;
    }

    return Camera_ChangeStatus(this->cameraPtrs[camIdx], status);
}

void Play_ClearCamera(PlayState* this, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    if (this->cameraPtrs[camIdx] != NULL) {
        Camera_ChangeStatus(this->cameraPtrs[camIdx], CAM_STATUS_INACTIVE);
        this->cameraPtrs[camIdx] = NULL;
    }
}

void Play_ClearAllSubCameras(PlayState* this) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (this->cameraPtrs[subCamId] != NULL) {
            Play_ClearCamera(this, subCamId);
        }
    }

    this->activeCamId = CAM_ID_MAIN;
}

Camera* Play_GetCamera(PlayState* this, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    return this->cameraPtrs[camIdx];
}

/**
 * @return bit-packed success if each of the params were applied
 */
s32 Play_SetCameraAtEye(PlayState* this, s16 camId, Vec3f* at, Vec3f* eye) {
    s32 successfullySet = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_AT, at);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_EYE, eye);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->focalActor != NULL) {
        camera->atActorOffset.x = at->x - camera->focalActor->world.pos.x;
        camera->atActorOffset.y = at->y - camera->focalActor->world.pos.y;
        camera->atActorOffset.z = at->z - camera->focalActor->world.pos.z;
    } else {
        camera->atActorOffset.x = camera->atActorOffset.y = camera->atActorOffset.z = 0.0f;
    }

    camera->atLerpStepScale = 0.01f;

    return successfullySet;
}

/**
 * @return bit-packed success if each of the params were applied
 */
s32 Play_SetCameraAtEyeUp(PlayState* this, s16 camId, Vec3f* at, Vec3f* eye, Vec3f* up) {
    s32 successfullySet = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_AT, at);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_EYE, eye);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_UP, up);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->focalActor != NULL) {
        camera->atActorOffset.x = at->x - camera->focalActor->world.pos.x;
        camera->atActorOffset.y = at->y - camera->focalActor->world.pos.y;
        camera->atActorOffset.z = at->z - camera->focalActor->world.pos.z;
    } else {
        camera->atActorOffset.x = camera->atActorOffset.y = camera->atActorOffset.z = 0.0f;
    }

    camera->atLerpStepScale = 0.01f;

    return successfullySet;
}

/**
 * @return true if the fov was successfully set
 */
s32 Play_SetCameraFov(PlayState* this, s16 camId, f32 fov) {
    s32 successfullySet = Camera_SetViewParam(this->cameraPtrs[camId], CAM_VIEW_FOV, &fov) & 1;

    if (1) {}
    return successfullySet;
}

s32 Play_SetCameraRoll(PlayState* this, s16 camId, s16 roll) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    camera->roll = roll;

    return 1;
}

void Play_CopyCamera(PlayState* this, s16 destCamId, s16 srcCamId) {
    s16 srcCamId2 = (srcCamId == CAM_ID_NONE) ? this->activeCamId : srcCamId;
    s16 destCamId1 = (destCamId == CAM_ID_NONE) ? this->activeCamId : destCamId;

    Camera_Copy(this->cameraPtrs[destCamId1], this->cameraPtrs[srcCamId2]);
}

// Same as Play_ChangeCameraSetting but also calls Camera_InitPlayerSettings
s32 func_80169A50(PlayState* this, s16 camId, Player* player, s16 setting) {
    Camera* camera;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    camera = this->cameraPtrs[camIdx];
    Camera_InitPlayerSettings(camera, player);
    return Camera_ChangeSetting(camera, setting);
}

s32 Play_ChangeCameraSetting(PlayState* this, s16 camId, s16 setting) {
    return Camera_ChangeSetting(Play_GetCamera(this, camId), setting);
}

// Related to bosses and fishing
void func_80169AFC(PlayState* this, s16 camId, s16 timer) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    s16 i;

    Play_ClearCamera(this, camIdx);

    for (i = CAM_ID_SUB_FIRST; i < NUM_CAMS; i++) {
        if (this->cameraPtrs[i] != NULL) {
            Play_ClearCamera(this, i);
        }
    }

    if (timer <= 0) {
        Play_ChangeCameraStatus(this, CAM_ID_MAIN, CAM_STATUS_ACTIVE);
        this->cameraPtrs[CAM_ID_MAIN]->childCamId = this->cameraPtrs[CAM_ID_MAIN]->doorTimer2 = 0;
    }
}

s16 Play_GetCameraUID(PlayState* this, s16 camId) {
    Camera* camera = this->cameraPtrs[camId];

    if (camera != NULL) {
        return camera->uid;
    } else {
        return -1;
    }
}

// Unused in both MM and OoT, purpose is very unclear
s16 func_80169BF8(PlayState* this, s16 camId, s16 uid) {
    Camera* camera = this->cameraPtrs[camId];

    if (camera != NULL) {
        return 0;
    } else if (camera->uid != uid) {
        return 0;
    } else if (camera->status != CAM_STATUS_ACTIVE) {
        return 2;
    } else {
        return 1;
    }
}

u16 Play_GetActorCsCamSetting(PlayState* this, s32 csCamDataIndex) {
    ActorCsCamInfo* actorCsCamList = &this->actorCsCamList[csCamDataIndex];

    return actorCsCamList->setting;
}

Vec3s* Play_GetActorCsCamFuncData(PlayState* this, s32 csCamDataIndex) {
    ActorCsCamInfo* actorCsCamList = &this->actorCsCamList[csCamDataIndex];

    return Lib_SegmentedToVirtual(actorCsCamList->actorCsCamFuncData);
}

/**
 * Converts the number of a scene to its "original" equivalent, the default version of the area which the player first
 * enters.
 */
s16 Play_GetOriginalSceneId(s16 sceneId) {
    // Inverted Stone Tower Temple -> Stone Tower Temple
    if (sceneId == SCENE_INISIE_R) {
        return SCENE_INISIE_N;
    }

    // Purified Southern Swamp -> Poisoned Sothern Swamp
    if (sceneId == SCENE_20SICHITAI2) {
        return SCENE_20SICHITAI;
    }

    // Spring Mountain Village -> Winter Mountain Village
    if (sceneId == SCENE_10YUKIYAMANOMURA2) {
        return SCENE_10YUKIYAMANOMURA;
    }

    // Spring Goron Village -> Winter Goron Village
    if (sceneId == SCENE_11GORONNOSATO2) {
        return SCENE_11GORONNOSATO;
    }

    // Spring Path to Goron Village -> Winter Path to Goron Village
    if (sceneId == SCENE_17SETUGEN2) {
        return SCENE_17SETUGEN;
    }

    // Inverted Stone Tower -> Stone Tower
    if (sceneId == SCENE_F41) {
        return SCENE_F40;
    }

    return sceneId;
}

/**
 * Copies the flags set in ActorContext over to the current scene's CycleSceneFlags, usually using the original scene
 * number. Exception for Inverted Stone Tower Temple, which uses its own.
 */
void Play_SaveCycleSceneFlags(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    CycleSceneFlags* cycleSceneFlags;

    cycleSceneFlags = &gSaveContext.cycleSceneFlags[Play_GetOriginalSceneId(this->sceneId)];
    cycleSceneFlags->chest = this->actorCtx.sceneFlags.chest;
    cycleSceneFlags->switch0 = this->actorCtx.sceneFlags.switches[0];
    cycleSceneFlags->switch1 = this->actorCtx.sceneFlags.switches[1];

    if (this->sceneId == SCENE_INISIE_R) { // Inverted Stone Tower Temple
        cycleSceneFlags = &gSaveContext.cycleSceneFlags[this->sceneId];
    }

    cycleSceneFlags->collectible = this->actorCtx.sceneFlags.collectible[0];
    cycleSceneFlags->clearedRoom = this->actorCtx.sceneFlags.clearedRoom;
}

void Play_SetRespawnData(GameState* thisx, s32 respawnMode, u16 entrance, s32 roomIndex, s32 playerParams, Vec3f* pos,
                         s16 yaw) {
    PlayState* this = (PlayState*)thisx;

    gSaveContext.respawn[respawnMode].entrance = Entrance_Create(entrance >> 9, 0, entrance & 0xF);
    gSaveContext.respawn[respawnMode].roomIndex = roomIndex;
    gSaveContext.respawn[respawnMode].pos = *pos;
    gSaveContext.respawn[respawnMode].yaw = yaw;
    gSaveContext.respawn[respawnMode].playerParams = playerParams;
    gSaveContext.respawn[respawnMode].tempSwitchFlags = this->actorCtx.sceneFlags.switches[2];
    gSaveContext.respawn[respawnMode].unk_18 = this->actorCtx.sceneFlags.collectible[1];
    gSaveContext.respawn[respawnMode].tempCollectFlags = this->actorCtx.sceneFlags.collectible[2];
}

void Play_SetupRespawnPoint(GameState* thisx, s32 respawnMode, s32 playerParams) {
    PlayState* this = (PlayState*)thisx;
    Player* player = GET_PLAYER(this);

    if (this->sceneId != SCENE_KAKUSIANA) { // Grottos
        Play_SetRespawnData(&this->state, respawnMode, (u16)((void)0, gSaveContext.save.entrance),
                            this->roomCtx.curRoom.num, playerParams, &player->actor.world.pos,
                            player->actor.shape.rot.y);
    }
}

// Override respawn data in Sakon's Hideout
void func_80169ECC(PlayState* this) {
    if (this->sceneId == SCENE_SECOM) {
        this->nextEntrance = ENTRANCE(IKANA_CANYON, 6);
        gSaveContext.respawnFlag = -7;
    }
}

// Gameplay_TriggerVoidOut ?
// Used by Player, Ikana_Rotaryroom, Bji01, Kakasi, LiftNuts, Test4, Warptag, WarpUzu, Roomtimer
void func_80169EFC(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    gSaveContext.respawn[RESPAWN_MODE_DOWN].tempSwitchFlags = this->actorCtx.sceneFlags.switches[2];
    gSaveContext.respawn[RESPAWN_MODE_DOWN].unk_18 = this->actorCtx.sceneFlags.collectible[1];
    gSaveContext.respawn[RESPAWN_MODE_DOWN].tempCollectFlags = this->actorCtx.sceneFlags.collectible[2];
    this->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance;
    gSaveContext.respawnFlag = 1;
    func_80169ECC(this);
    this->transitionTrigger = TRANS_TRIGGER_START;
    this->transitionType = TRANS_TYPE_02;
}

// Gameplay_LoadToLastEntrance ?
// Used by game_over and Test7
void func_80169F78(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    this->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_TOP].entrance;
    gSaveContext.respawnFlag = -1;
    func_80169ECC(this);
    this->transitionTrigger = TRANS_TRIGGER_START;
    this->transitionType = TRANS_TYPE_02;
}

// Gameplay_TriggerRespawn ?
// Used for void by Wallmaster, Deku Shrine doors. Also used by Player, Kaleido, DoorWarp1
void func_80169FDC(GameState* thisx) {
    func_80169F78(thisx);
}

// Used by Kankyo to determine how to change the lighting, e.g. for game over.
s32 func_80169FFC(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    return this->roomCtx.curRoom.mesh->type0.type != 1;
}

s32 FrameAdvance_IsEnabled(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    return this->frameAdvCtx.enabled != 0;
}

// Unused, unchanged from OoT, which uses it only in one Camera function.
/**
 * @brief Tests if \p actor is a door and the sides are different rooms.
 *
 * @param[in] thisx GameState, promoted to play inside.
 * @param[in] actor Actor to test.
 * @param[out] yaw Facing angle of the actor, or reverse if in the back room.
 * @return true if \p actor is a door and the sides are in different rooms, false otherwise
 */
s32 func_8016A02C(GameState* thisx, Actor* actor, s16* yaw) {
    PlayState* this = (PlayState*)thisx;
    TransitionActorEntry* transitionActor;
    s8 frontRoom;

    if (actor->category != ACTORCAT_DOOR) {
        return false;
    }

    transitionActor = &this->doorCtx.transitionActorList[(u16)actor->params >> 10];
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
 * @param[in] play PlayState
 * @param[in] pos position to test
 * @return true if inside a waterbox and not above a void.
 */
s32 Play_IsUnderwater(PlayState* this, Vec3f* pos) {
    WaterBox* waterBox;
    CollisionPoly* poly;
    Vec3f waterSurfacePos;
    s32 bgId;

    waterSurfacePos = *pos;

    if ((WaterBox_GetSurface1(this, &this->colCtx, waterSurfacePos.x, waterSurfacePos.z, &waterSurfacePos.y,
                              &waterBox) == true) &&
        (pos->y < waterSurfacePos.y) &&
        (BgCheck_EntityRaycastFloor3(&this->colCtx, &poly, &bgId, &waterSurfacePos) != BGCHECK_Y_MIN)) {
        return true;
    } else {
        return false;
    }
}

s32 Play_IsDebugCamEnabled(void) {
    return gDbgCamEnabled;
}

// A mapping from playerCsIds to sGlobalCamDataSettings indices.
extern s16 D_801D0D64[];
// s16 D_801D0D64[] = { -3, -2, -4, -5, -7, -11, -8, -9, -6, -16 };

// Used by Player
/**
 * Extract the common actor cutscene ids used by Player from the scene and set the actor cutscene ids in
 * this->playerCsIds. If a playerActorCsId is not present in the scene, then that particular id is set
 * to -1. Otherwise, if there is an ActorCutscene where csCamSceneDataId matches the appropriate element of D_801D0D64,
 * set the corresponding playerActorCsId (and possibly change its priority for the zeroth one)
 */
void Play_AssignPlayerCsIdsFromScene(GameState* thisx, s32 startActorCsId) {
    PlayState* this = (PlayState*)thisx;
    s32 i;
    s16* curPlayerCsId = this->playerCsIds;
    s16* phi_s1 = D_801D0D64;

    for (i = 0; i < ARRAY_COUNT(this->playerCsIds); i++, curPlayerCsId++, phi_s1++) {
        ActorCutscene* actorCutscene;
        s32 curCsId;

        *curPlayerCsId = CS_ID_NONE;

        for (curCsId = startActorCsId; curCsId != CS_ID_NONE; curCsId = actorCutscene->additionalCsId) {
            actorCutscene = ActorCutscene_GetCutscene(curCsId);

            if (actorCutscene->csCamSceneDataId == *phi_s1) {
                if ((actorCutscene->csCamSceneDataId == -3) &&
                    (actorCutscene->priority == 700)) { // override ocarina cs priority
                    actorCutscene->priority = 550;
                }
                *curPlayerCsId = curCsId;
                break;
            }
        }
    }
}

// Set values to fill screen
void Play_FillScreen(GameState* thisx, s16 fillScreenOn, u8 red, u8 green, u8 blue, u8 alpha) {
    R_PLAY_FILL_SCREEN_ON = fillScreenOn;
    R_PLAY_FILL_SCREEN_R = red;
    R_PLAY_FILL_SCREEN_G = green;
    R_PLAY_FILL_SCREEN_B = blue;
    R_PLAY_FILL_SCREEN_ALPHA = alpha;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_Init.s")
