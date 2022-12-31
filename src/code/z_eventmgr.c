/**
 * @file z_eventmgr.c
 *
 * Manages all cutscenes except for manual
 */
#include "global.h"
#include "z64shrink_window.h"

ActorCutscene sGlobalActorCutscenes[8] = {
    // CS_ID_GLOBAL_78
    { -100, -1, CS_CAM_ID_NONE, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE_ALT, 255, CS_HUD_VISIBILITY_ALL_ALT, 255,
      255 },
    // CS_ID_GLOBAL_79
    { -100, -1, CS_CAM_ID_NONE, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE_ALT, 255, CS_HUD_VISIBILITY_ALL_ALT, 255,
      255 },
    // CS_ID_GLOBAL_7A
    { -100, -1, CS_CAM_ID_NONE, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE_ALT, 255, CS_HUD_VISIBILITY_ALL_ALT, 255,
      255 },
    // CS_ID_GLOBAL_ELEGY
    { 2, -1, CS_CAM_ID_GLOBAL_ELEGY, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE_ALT, 255, CS_HUD_VISIBILITY_NONE,
      CS_END_CAM_0, 32 },
    // CS_ID_GLOBAL_TALK
    { 32765, -1, CS_CAM_ID_NONE, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE_ALT, 255, CS_HUD_VISIBILITY_ALL_ALT,
      CS_END_CAM_0, 255 },
    // CS_ID_GLOBAL_DOOR
    { 32764, -1, CS_CAM_ID_NONE, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE_ALT, 255, CS_HUD_VISIBILITY_ALL_ALT,
      CS_END_CAM_0, 255 },
    // CS_ID_GLOBAL_RETURN_TO_CAM
    { 32766, -2, CS_CAM_ID_GLOBAL_CONNECT, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE, 255,
      CS_HUD_VISIBILITY_ALL_ALT, CS_END_CAM_0, 32 },
    // CS_ID_GLOBAL_END
    { 0, -1, CS_CAM_ID_NONE, CS_SCRIPT_ID_NONE, CS_ID_NONE, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_ALL_ALT,
      CS_END_CAM_0, 32 },
};

typedef enum {
    /* 0 */ CS_START_0,
    /* 1 */ CS_START_1,
    /* 2 */ CS_START_2,
} ActorCutsceneStartMethod;

typedef struct {
    /* 0x00 */ s16 csId;
    /* 0x02 */ s16 length;
    /* 0x04 */ s16 endCsId;
    /* 0x06 */ s16 subCamId;
    /* 0x08 */ Actor* targetActor;
    /* 0x0C */ s32 startMethod;
    /* 0x10 */ PlayState* play;
    /* 0x14 */ s16 retCamId;
    /* 0x16 */ s16 isCameraStored;
} ActorCutsceneManager; // size = 0x18

ActorCutsceneManager sActorCsMgr = {
    CS_ID_NONE, 0, CS_ID_NONE, SUB_CAM_ID_DONE, NULL, CS_START_0, NULL, CAM_ID_MAIN, false,
};

s16 CutsceneManager_SetHudVisibility(s16 csHudVisibility) {
    u16 hudVisibility;

    switch (csHudVisibility) {
        case CS_HUD_VISIBILITY_NONE:
            hudVisibility = HUD_VISIBILITY_NONE_ALT;
            break;

        case CS_HUD_VISIBILITY_ALL:
            hudVisibility = HUD_VISIBILITY_ALL;
            break;

        case CS_HUD_VISIBILITY_A_HEARTS_MAGIC:
            hudVisibility = HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE;
            break;

        case CS_HUD_VISIBILITY_C_HEARTS_MAGIC:
            hudVisibility = HUD_VISIBILITY_HEARTS_MAGIC_C;
            break;

        case CS_HUD_VISIBILITY_ALL_NO_MINIMAP:
            hudVisibility = HUD_VISIBILITY_ALL_NO_MINIMAP;
            break;

        case CS_HUD_VISIBILITY_A_B_C:
            hudVisibility = HUD_VISIBILITY_A_B_C;
            break;

        case CS_HUD_VISIBILITY_B_MINIMAP:
            hudVisibility = HUD_VISIBILITY_B_MINIMAP;
            break;

        case CS_HUD_VISIBILITY_A:
            hudVisibility = HUD_VISIBILITY_A;
            break;

        default:
            hudVisibility = HUD_VISIBILITY_ALL;
            break;
    }

    Interface_SetHudVisibility(hudVisibility);

    return hudVisibility;
}

ActorCutscene* CutsceneManager_GetCutsceneImpl(s16 csId) {
    if (csId < CS_ID_GLOBAL_78) {
        return &sActorCutsceneList[csId];
    } else {
        csId -= CS_ID_GLOBAL_78;
        return &sGlobalActorCutscenes[csId];
    }
}

void CutsceneManager_Init(PlayState* play, ActorCutscene* actorCutsceneList, s16 num) {
    s32 i;

    sActorCutsceneList = actorCutsceneList;
    sActorCutsceneCount = num;

    for (i = 0; i < ARRAY_COUNT(sWaitingActorCutsceneList); i++) {
        sWaitingActorCutsceneList[i] = 0;
        sNextActorCutsceneList[i] = 0;
    }

    sActorCsMgr.endCsId = CS_ID_NONE;
    sActorCsMgr.play = play;
    sActorCsMgr.length = -1;
    sActorCsMgr.targetActor = NULL;
    sActorCsMgr.subCamId = SUB_CAM_ID_DONE;
    sActorCsMgr.isCameraStored = false;
    sActorCsMgr.csId = sActorCsMgr.endCsId;
}

/**
 * Store camera into subCam 2, and keep subCam 2 INACTIVE to preserve the struct.
 */
void CutsceneManager_StoreCamera(Camera* camera) {
    if (camera != NULL) {
        memcpy(&sActorCsMgr.play->subCameras[2], camera, sizeof(Camera));
        sActorCsMgr.play->subCameras[2].camId = camera->camId;
        Camera_ChangeStatus(&sActorCsMgr.play->subCameras[2], CAM_STATUS_INACTIVE);
        sActorCsMgr.isCameraStored = true;
    }
}

void CutsceneManager_ClearWaiting(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sWaitingActorCutsceneList); i++) {
        sWaitingActorCutsceneList[i] = 0;
    }
}

void CutsceneManager_ClearNextCutscenes(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sNextActorCutsceneList); i++) {
        sNextActorCutsceneList[i] = 0;
    }
}

s16 CutsceneManager_MarkNextCutscenes(void) {
    s16 bit;
    s32 i;
    s32 j;
    s32 count = 0;
    s16 actorCsIdMax = CS_ID_NONE;
    s16 priorityMax = SHT_MAX; // lower number means higher priority
    s16 csId;
    s16 priority;

    for (i = 0; i < ARRAY_COUNT(sNextActorCutsceneList); i++) {
        for (bit = 1, j = 0; j < 8; j++) {
            if (sWaitingActorCutsceneList[i] & bit) {
                csId = (i << 3) | j;
                priority = CutsceneManager_GetCutsceneImpl(csId)->priority;

                if ((priority ^ 0) == -1) {
                    sNextActorCutsceneList[i] |= bit;
                } else if ((priority < priorityMax) && (priority > 0)) {
                    actorCsIdMax = csId;
                    priorityMax = priority;
                }
                count++;
            }
            bit <<= 1;
        }
    }
    if (actorCsIdMax != CS_ID_NONE) {
        sNextActorCutsceneList[actorCsIdMax >> 3] |= 1 << (actorCsIdMax & 7);
    }
    return count;
}

void CutsceneManager_End(void) {
    ActorCutscene* actorCs;
    s16 oldCamId;
    s16 oldStateFlags;

    switch (sActorCsMgr.startMethod) {
        case CS_START_2:
            sActorCsMgr.targetActor->flags &= ~ACTOR_FLAG_100000;
            // fallthrough
        case CS_START_1:
            func_800B7298(sActorCsMgr.play, 0, PLAYER_CSMODE_END);
            sActorCsMgr.startMethod = CS_START_0;
            break;

        default:
            break;
    }

    actorCs = CutsceneManager_GetCutsceneImpl(sActorCsMgr.csId);

    switch (actorCs->endSfx) {
        case CS_END_SFX_TRE_BOX_APPEAR:
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            break;

        case CS_END_SFX_CORRECT_CHIME:
            play_sound(NA_SE_SY_CORRECT_CHIME);
            break;

        default: // CS_END_SFX_NONE
            break;
    }

#define RET_CAM sActorCsMgr.play->cameraPtrs[sActorCsMgr.retCamId]
#define CUR_CAM sActorCsMgr.play->cameraPtrs[sActorCsMgr.subCamId]

    switch (actorCs->endCam) {
        case CS_END_CAM_SMOOTH:
            Play_CopyCamera(sActorCsMgr.play, sActorCsMgr.retCamId, sActorCsMgr.subCamId);
            RET_CAM->stateFlags =
                (RET_CAM->stateFlags & ~CAM_STATE_UNDERWATER) | (CUR_CAM->stateFlags & CAM_STATE_UNDERWATER);
            CutsceneManager_Queue(CS_ID_GLOBAL_RETURN_TO_CAM);
            break;

        case CS_END_CAM_0:
        default:
            Play_CopyCamera(sActorCsMgr.play, sActorCsMgr.retCamId, sActorCsMgr.subCamId);
            RET_CAM->stateFlags =
                (RET_CAM->stateFlags & ~CAM_STATE_UNDERWATER) | (CUR_CAM->stateFlags & CAM_STATE_UNDERWATER);
            break;

        case CS_END_CAM_1:
            oldCamId = RET_CAM->camId;
            oldStateFlags = RET_CAM->stateFlags;

            if (sActorCsMgr.isCameraStored) {
                // Restore the camera that was stored in subCam 2
                memcpy(RET_CAM, &sActorCsMgr.play->subCameras[2], sizeof(Camera));

                RET_CAM->stateFlags =
                    (RET_CAM->stateFlags & ~CAM_STATE_UNDERWATER) | (CUR_CAM->stateFlags & CAM_STATE_UNDERWATER);

                RET_CAM->stateFlags = (RET_CAM->stateFlags & ~CAM_STATE_2) | (oldStateFlags & CAM_STATE_2);
                sActorCsMgr.isCameraStored = false;
            }
            RET_CAM->camId = oldCamId;
            break;
    }

    if (sActorCsMgr.subCamId != SUB_CAM_ID_DONE) {
        Play_ClearCamera(sActorCsMgr.play, sActorCsMgr.subCamId);
        Play_ChangeCameraStatus(sActorCsMgr.play, sActorCsMgr.retCamId, CAM_STATUS_ACTIVE);
    }

    sActorCsMgr.csId = CS_ID_NONE;
    sActorCsMgr.endCsId = CS_ID_NONE;
    sActorCsMgr.length = -1;
    sActorCsMgr.targetActor = NULL;
    sActorCsMgr.subCamId = SUB_CAM_ID_DONE;
}

s16 CutsceneManager_Update(void) {
    s16 sp1E = 0;

    if (CutsceneManager_IsNext(CS_ID_GLOBAL_RETURN_TO_CAM) != 0) {
        CutsceneManager_StartWithPlayerCs(CS_ID_GLOBAL_RETURN_TO_CAM, &GET_PLAYER(sActorCsMgr.play)->actor);
    }

    if (sActorCsMgr.endCsId == CS_ID_NONE) {
        if (sActorCsMgr.csId != CS_ID_NONE) {
            if (sActorCsMgr.length > 0) {
                sActorCsMgr.length--;
            }
            sp1E = 1;
            if (sActorCsMgr.length == 0) {
                CutsceneManager_Stop(sActorCsMgr.csId);
            }
        }
    }

    if (sActorCsMgr.endCsId != CS_ID_NONE) {
        CutsceneManager_End();
        sp1E = 2;
    }

    CutsceneManager_ClearNextCutscenes();

    if (sActorCsMgr.csId == CS_ID_NONE) {
        if ((CutsceneManager_MarkNextCutscenes() == 0) && (sp1E != 0)) {
            ShrinkWindow_Letterbox_SetSizeTarget(0);
        } else if (sp1E == 0) {
            CutsceneManager_StoreCamera(Play_GetCamera(sActorCsMgr.play, sActorCsMgr.retCamId));
        }
    }
    return sp1E;
}

void CutsceneManager_Queue(s16 csId) {
    if (csId >= 0) {
        sWaitingActorCutsceneList[csId >> 3] |= 1 << (csId & 7);
    }
}

s16 CutsceneManager_IsNext(s16 csId) {
    if (csId == CS_ID_GLOBAL_END) {
        if (sActorCsMgr.csId == CS_ID_NONE) {
            return CS_ID_GLOBAL_END;
        } else {
            return 0;
        }
    }
    if (csId <= CS_ID_NONE) {
        return -1;
    }
    return (sNextActorCutsceneList[csId >> 3] & (1 << (csId & 7))) ? true : false;
}

/**
 * Start an actor cutscene, activate Player Cutscene Mode "Wait"
 */
s16 CutsceneManager_StartWithPlayerCs(s16 csId, Actor* actor) {
    s16 startCsId = CutsceneManager_Start(csId, actor);

    if (startCsId >= 0) {
        func_800B7298(sActorCsMgr.play, 0, PLAYER_CSMODE_WAIT);
        if (sActorCsMgr.length == 0) {
            CutsceneManager_Stop(sActorCsMgr.csId);
        }
        sActorCsMgr.startMethod = CS_START_1;
    }
    return startCsId;
}

/**
 * Start an actor cutscene, activate Player Cutscene Mode "Wait", turn on ACTOR_FLAG_100000
 */
s16 CutsceneManager_StartWithPlayerCsAndSetFlag(s16 csId, Actor* actor) {
    s16 startCsId = CutsceneManager_Start(csId, actor);

    if (startCsId >= 0) {
        func_800B7298(sActorCsMgr.play, 0, PLAYER_CSMODE_WAIT);
        if (sActorCsMgr.length == 0) {
            CutsceneManager_Stop(sActorCsMgr.csId);
        }
        if (actor != NULL) {
            actor->flags |= ACTOR_FLAG_100000;
            sActorCsMgr.startMethod = CS_START_2;
        } else {
            sActorCsMgr.startMethod = CS_START_1;
        }
    }
    return startCsId;
}

s16 CutsceneManager_Start(s16 csId, Actor* actor) {
    ActorCutscene* actorCs;
    Camera* subCam;
    Camera* retCam;
    s32 sp20 = 0;

    if ((csId < 0) || (sActorCsMgr.csId != CS_ID_NONE)) {
        return csId;
    }

    sActorCsMgr.startMethod = CS_START_0;
    actorCs = CutsceneManager_GetCutsceneImpl(csId);

    ShrinkWindow_Letterbox_SetSizeTarget(actorCs->letterboxSize);
    CutsceneManager_SetHudVisibility(actorCs->hudVisibility);

    if (csId == CS_ID_GLOBAL_END) {
        sp20 = 1;
    } else if (actorCs->scriptIndex != CS_SCRIPT_ID_NONE) {
        // scripted cutscene
        sp20 = 1;
    } else if ((csId != CS_ID_GLOBAL_DOOR) && (csId != CS_ID_GLOBAL_TALK)) {
        sp20 = 2;
    }

    if (sp20 != 0) {
        sActorCsMgr.retCamId = Play_GetActiveCamId(sActorCsMgr.play);
        sActorCsMgr.subCamId = Play_CreateSubCamera(sActorCsMgr.play);

        subCam = Play_GetCamera(sActorCsMgr.play, sActorCsMgr.subCamId);
        retCam = Play_GetCamera(sActorCsMgr.play, sActorCsMgr.retCamId);

        if ((retCam->setting == CAM_SET_START0) || (retCam->setting == CAM_SET_START2) ||
            (retCam->setting == CAM_SET_START1)) {
            if (CutsceneManager_FindEntranceCsId() != csId) {
                func_800E0348(retCam);
            } else {
                Camera_ClearFlags(retCam, CAM_STATE_2);
            }
        }

        memcpy(subCam, retCam, sizeof(Camera));
        subCam->camId = sActorCsMgr.subCamId;
        Camera_ClearFlags(subCam, CAM_STATE_6 | CAM_STATE_0);

        Play_ChangeCameraStatus(sActorCsMgr.play, sActorCsMgr.retCamId, CAM_STATUS_WAIT);
        Play_ChangeCameraStatus(sActorCsMgr.play, sActorCsMgr.subCamId, CAM_STATUS_ACTIVE);

        subCam->target = sActorCsMgr.targetActor = actor;
        subCam->behaviorFlags = 0;

        if (sp20 == 1) {
            Camera_ChangeSetting(subCam, CAM_SET_FREE0);
            Cutscene_SetScript(sActorCsMgr.play, actorCs->scriptIndex);
            sActorCsMgr.length = actorCs->length;
        } else {
            if (actorCs->csCamId != CS_CAM_ID_NONE) {
                Camera_ChangeDataIdx(subCam, actorCs->csCamId);
            } else {
                Camera_ChangeSetting(subCam, CAM_SET_FREE0);
            }
            sActorCsMgr.length = actorCs->length;
        }
    }
    sActorCsMgr.csId = csId;

    return csId;
}

s16 CutsceneManager_Stop(s16 csId) {
    ActorCutscene* actorCs;

    if (csId < 0) {
        return csId;
    }

    actorCs = CutsceneManager_GetCutsceneImpl(sActorCsMgr.csId);
    if ((sActorCsMgr.length > 0) && (actorCs->scriptIndex == CS_SCRIPT_ID_NONE)) {
        return -2;
    }
    if ((csId != CS_ID_GLOBAL_END) && (actorCs->scriptIndex != CS_SCRIPT_ID_NONE)) {
        return -3;
    }

    if (csId == CS_ID_GLOBAL_END) {
        csId = sActorCsMgr.csId;
    }
    if (csId == sActorCsMgr.csId) {
        sActorCsMgr.endCsId = sActorCsMgr.csId;
        return sActorCsMgr.endCsId;
    }
    return -1;
}

s16 CutsceneManager_GetCurrentCsId(void) {
    return sActorCsMgr.csId;
}

ActorCutscene* CutsceneManager_GetCutscene(s16 csId) {
    return CutsceneManager_GetCutsceneImpl(csId);
}

s16 CutsceneManager_GetAdditionalCsId(s16 csId) {
    if (csId < 0) {
        return CS_ID_NONE;
    }
    return CutsceneManager_GetCutsceneImpl(csId)->additionalCsId;
}

s16 CutsceneManager_GetLength(s16 csId) {
    if (csId < 0) {
        return -1;
    }
    return CutsceneManager_GetCutsceneImpl(csId)->length;
}

s16 CutsceneManager_GetCutsceneScriptIndex(s16 csId) {
    if (csId < 0) {
        return -1;
    }
    return CutsceneManager_GetCutsceneImpl(csId)->scriptIndex;
}

s16 CutsceneManager_GetCutsceneCustomValue(s16 csId) {
    if (csId < 0) {
        return -1;
    }
    return CutsceneManager_GetCutsceneImpl(csId)->customValue;
}

s16 CutsceneManager_GetCurrentSubCamId(s16 csId) {
    return sActorCsMgr.subCamId;
}

s16 CutsceneManager_FindEntranceCsId(void) {
    PlayState* play;
    s32 csId;

    for (csId = 0; csId < sActorCutsceneCount; csId++) {
        //! FAKE:
        if ((sActorCutsceneList[csId].scriptIndex != CS_SCRIPT_ID_NONE) &&
            (sActorCutsceneList[csId].scriptIndex < (play = sActorCsMgr.play)->csCtx.scriptListCount) &&
            (sActorCsMgr.play->curSpawn ==
             sActorCsMgr.play->csCtx.scriptList[sActorCutsceneList[csId].scriptIndex].spawn)) {
            return csId;
        }
    }

    for (csId = 0; csId < sActorCutsceneCount; csId++) {
        if ((sActorCutsceneList[csId].customValue >= 100) &&
            (sActorCutsceneList[csId].customValue == (sActorCsMgr.play->curSpawn + 100))) {
            return csId;
        }
    }

    return -1;
}

s32 func_800F22C4(s16 csId, Actor* actor) {
    f32 dist;
    s16 screenPosX;
    s16 screenPosY;

    if ((sActorCsMgr.csId == CS_ID_NONE) || (csId == CS_ID_NONE)) {
        return 4;
    }

    Actor_GetScreenPos(sActorCsMgr.play, actor, &screenPosX, &screenPosY);

    dist = OLib_Vec3fDist(&actor->focus.pos, &Play_GetCamera(sActorCsMgr.play, sActorCsMgr.subCamId)->eye);

    if ((screenPosX > 40) && (screenPosX < SCREEN_WIDTH - 40) && (screenPosY > 40) &&
        (screenPosY < SCREEN_HEIGHT - 40) && (dist < 700.0f)) {
        return 1;
    }
    if (sActorCsMgr.length < 6) {
        return 2;
    }
    if (csId == sActorCsMgr.csId) {
        return 0;
    }
    return 3;
}

void CutsceneManager_SetReturnCamera(s16 camId) {
    sActorCsMgr.retCamId = camId;
}
