#include "global.h"
#include "z64shrink_window.h"

ActorCutscene sGlobalActorCutscenes[8] = {
    /* 0x78 */ { 0xFF9C, -1, -1, -1, -1, 255, 255, -1, 255, 255 },
    /* 0x79 */ { 0xFF9C, -1, -1, -1, -1, 255, 255, -1, 255, 255 },
    /* 0x7A */ { 0xFF9C, -1, -1, -1, -1, 255, 255, -1, 255, 255 },
    /* 0x7B */ { 0x0002, -1, -25, -1, -1, 255, 255, 0, 0, 32 },
    /* 0x7C */ { 0x7FFD, -1, -1, -1, -1, 255, 255, -1, 0, 255 },
    /* 0x7D */ { 0x7FFC, -1, -1, -1, -1, 255, 255, -1, 0, 255 },
    /* 0x7E */ { 0x7FFE, -2, -14, -1, -1, 0, 255, -1, 0, 32 },
    /* 0x7F */ { 0x0000, -1, -1, -1, -1, 0, 255, -1, 0, 32 },
};

typedef struct {
    /* 0x00 */ s16 actorCsId;
    /* 0x02 */ s16 length;
    /* 0x04 */ s16 endActorCsId;
    /* 0x06 */ s16 subCamId;
    /* 0x08 */ Actor* targetActor;
    /* 0x0C */ s32 startMethod;
    /* 0x10 */ PlayState* play;
    /* 0x14 */ s16 retCamId;
    /* 0x16 */ s16 unk16;
} ActorCutsceneManager; // size = 0x18

ActorCutsceneManager sActorCsMgr = {
    -1, 0, -1, SUB_CAM_ID_DONE, NULL, 0, NULL, CAM_ID_MAIN, 0,
};

s16 ActorCutscene_SetHudVisibility(s16 csHudVisibility) {
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

ActorCutscene* ActorCutscene_GetCutsceneImpl(s16 actorCsId) {
    if (actorCsId < 0x78) {
        return &sActorCutsceneList[actorCsId];
    } else {
        actorCsId -= 0x78;
        return &sGlobalActorCutscenes[actorCsId];
    }
}

void ActorCutscene_Init(PlayState* play, ActorCutscene* actorCutsceneList, s16 num) {
    s32 i;

    sActorCutsceneList = actorCutsceneList;
    sActorCutsceneCount = num;

    for (i = 0; i < ARRAY_COUNT(sActorCutsceneWaiting); i++) {
        sActorCutsceneWaiting[i] = 0;
        actorCutsceneNextCutscenes[i] = 0;
    }

    sActorCsMgr.endActorCsId = -1;
    sActorCsMgr.play = play;
    sActorCsMgr.length = -1;
    sActorCsMgr.targetActor = NULL;
    sActorCsMgr.subCamId = SUB_CAM_ID_DONE;
    sActorCsMgr.unk16 = 0;
    sActorCsMgr.actorCsId = sActorCsMgr.endActorCsId;
}

void func_800F15D8(Camera* camera) {
    if (camera != NULL) {
        memcpy(&sActorCsMgr.play->subCameras[2], camera, sizeof(Camera));
        sActorCsMgr.play->subCameras[2].camId = camera->camId;
        Camera_ChangeStatus(&sActorCsMgr.play->subCameras[2], CAM_STATUS_INACTIVE);
        sActorCsMgr.unk16 = 1;
    }
}

void ActorCutscene_ClearWaiting(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sActorCutsceneWaiting); i++) {
        sActorCutsceneWaiting[i] = 0;
    }
}

void ActorCutscene_ClearNextCutscenes(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorCutsceneNextCutscenes); i++) {
        actorCutsceneNextCutscenes[i] = 0;
    }
}

s16 ActorCutscene_MarkNextCutscenes(void) {
    s16 bit;
    s32 i;
    s32 j;
    s16 priorityMax;
    s16 actorCsIdMax;
    s32 count;
    s16 actorCsId;
    s16 priority;

    count = 0;
    actorCsIdMax = -1;
    priorityMax = SHT_MAX;
    for (i = 0; i < 16; i++) {
        for (bit = 1, j = 0; j < 8; j++) {
            if (sActorCutsceneWaiting[i] & bit) {
                actorCsId = (i << 3) | j;
                priority = ActorCutscene_GetCutsceneImpl(actorCsId)->priority;

                if ((priority ^ 0) == -1) {
                    actorCutsceneNextCutscenes[i] |= bit;
                } else if ((priority < priorityMax) && (priority > 0)) {
                    actorCsIdMax = actorCsId;
                    priorityMax = priority;
                }
                count++;
            }
            bit <<= 1;
        }
    }
    if (actorCsIdMax != -1) {
        actorCutsceneNextCutscenes[actorCsIdMax >> 3] |= 1 << (actorCsIdMax & 7);
    }
    return count;
}

void ActorCutscene_End(void) {
    ActorCutscene* actorCs;
    s16 oldCamId;
    s16 oldStateFlags;

    switch (sActorCsMgr.startMethod) {
        case 2:
            sActorCsMgr.targetActor->flags &= ~ACTOR_FLAG_100000;
            // fallthrough
        case 1:
            func_800B7298(sActorCsMgr.play, 0, PLAYER_CSMODE_END);
            sActorCsMgr.startMethod = 0;
            break;

        default:
            break;
    }

    actorCs = ActorCutscene_GetCutsceneImpl(sActorCsMgr.actorCsId);

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
            ActorCutscene_SetIntentToPlay(0x7E);
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

            if (sActorCsMgr.unk16 != 0) {
                memcpy(RET_CAM, &sActorCsMgr.play->subCameras[2], sizeof(Camera));

                RET_CAM->stateFlags =
                    (RET_CAM->stateFlags & ~CAM_STATE_UNDERWATER) | (CUR_CAM->stateFlags & CAM_STATE_UNDERWATER);

                RET_CAM->stateFlags = (RET_CAM->stateFlags & ~CAM_STATE_2) | (oldStateFlags & CAM_STATE_2);
                sActorCsMgr.unk16 = 0;
            }
            RET_CAM->camId = oldCamId;
            break;
    }

    if (sActorCsMgr.subCamId != SUB_CAM_ID_DONE) {
        Play_ClearCamera(sActorCsMgr.play, sActorCsMgr.subCamId);
        Play_ChangeCameraStatus(sActorCsMgr.play, sActorCsMgr.retCamId, CAM_STATUS_ACTIVE);
    }

    sActorCsMgr.actorCsId = -1;
    sActorCsMgr.endActorCsId = -1;
    sActorCsMgr.length = -1;
    sActorCsMgr.targetActor = NULL;
    sActorCsMgr.subCamId = SUB_CAM_ID_DONE;
}

s16 ActorCutscene_Update(void) {
    s16 sp1E = 0;

    if (ActorCutscene_GetCanPlayNext(0x7E) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields(0x7E, &GET_PLAYER(sActorCsMgr.play)->actor);
    }
    if (sActorCsMgr.endActorCsId == -1) {
        if (sActorCsMgr.actorCsId != -1) {
            if (sActorCsMgr.length > 0) {
                sActorCsMgr.length--;
            }
            sp1E = 1;
            if (sActorCsMgr.length == 0) {
                ActorCutscene_Stop(sActorCsMgr.actorCsId);
            }
        }
    }
    if (sActorCsMgr.endActorCsId != -1) {
        ActorCutscene_End();
        sp1E = 2;
    }

    ActorCutscene_ClearNextCutscenes();

    if (sActorCsMgr.actorCsId == -1) {
        if ((ActorCutscene_MarkNextCutscenes() == 0) && (sp1E != 0)) {
            ShrinkWindow_Letterbox_SetSizeTarget(0);
        } else if (sp1E == 0) {
            func_800F15D8(Play_GetCamera(sActorCsMgr.play, sActorCsMgr.retCamId));
        }
    }
    return sp1E;
}

void ActorCutscene_SetIntentToPlay(s16 index) {
    if (index >= 0) {
        sActorCutsceneWaiting[index >> 3] |= 1 << (index & 7);
    }
}

s16 ActorCutscene_GetCanPlayNext(s16 index) {
    if (index == 0x7F) {
        if (sActorCsMgr.actorCsId == -1) {
            return 0x7F;
        } else {
            return 0;
        }
    }
    if (index < 0) {
        return -1;
    }
    return (actorCutsceneNextCutscenes[index >> 3] & (1 << (index & 7))) ? true : false;
}

/**
 * Start an actor cutscene, activate Player Cutscene Mode "Wait"
 */
s16 ActorCutscene_StartAndSetUnkLinkFields(s16 index, Actor* actor) {
    s16 sp1E = ActorCutscene_Start(index, actor);

    if (sp1E >= 0) {
        func_800B7298(sActorCsMgr.play, 0, PLAYER_CSMODE_WAIT);
        if (sActorCsMgr.length == 0) {
            ActorCutscene_Stop(sActorCsMgr.actorCsId);
        }
        sActorCsMgr.startMethod = 1;
    }
    return sp1E;
}

/**
 * Start an actor cutscene, activate Player Cutscene Mode "Wait", turn on ACTOR_FLAG_100000
 */
s16 ActorCutscene_StartAndSetFlag(s16 index, Actor* actor) {
    s16 sp1E = ActorCutscene_Start(index, actor);

    if (sp1E >= 0) {
        func_800B7298(sActorCsMgr.play, 0, PLAYER_CSMODE_WAIT);
        if (sActorCsMgr.length == 0) {
            ActorCutscene_Stop(sActorCsMgr.actorCsId);
        }
        if (actor != NULL) {
            actor->flags |= ACTOR_FLAG_100000;
            sActorCsMgr.startMethod = 2;
        } else {
            sActorCsMgr.startMethod = 1;
        }
    }
    return sp1E;
}

s16 ActorCutscene_Start(s16 index, Actor* actor) {
    ActorCutscene* actorCs;
    Camera* subCam;
    Camera* retCam;
    s32 sp20 = 0;

    if ((index < 0) || (sActorCsMgr.actorCsId != -1)) {
        return index;
    }

    sActorCsMgr.startMethod = 0;
    actorCs = ActorCutscene_GetCutsceneImpl(index);

    ShrinkWindow_Letterbox_SetSizeTarget(actorCs->letterboxSize);
    ActorCutscene_SetHudVisibility(actorCs->hudVisibility);

    if (index == 0x7F) {
        sp20 = 1;
    } else if (actorCs->scriptIndex != -1) {
        sp20 = 1;
    } else if ((index != 0x7D) && (index != 0x7C)) {
        sp20 = 2;
    }

    if (sp20 != 0) {
        sActorCsMgr.retCamId = Play_GetActiveCamId(sActorCsMgr.play);
        sActorCsMgr.subCamId = Play_CreateSubCamera(sActorCsMgr.play);
        subCam = Play_GetCamera(sActorCsMgr.play, sActorCsMgr.subCamId);
        retCam = Play_GetCamera(sActorCsMgr.play, sActorCsMgr.retCamId);
        if ((retCam->setting == CAM_SET_START0) || (retCam->setting == CAM_SET_START2) ||
            (retCam->setting == CAM_SET_START1)) {
            if (ActorCutscene_FindEntranceCutscene() != index) {
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
            if (actorCs->csCamSceneDataId != -1) {
                Camera_ChangeDataIdx(subCam, actorCs->csCamSceneDataId);
            } else {
                Camera_ChangeSetting(subCam, CAM_SET_FREE0);
            }
            sActorCsMgr.length = actorCs->length;
        }
    }
    sActorCsMgr.actorCsId = index;

    return index;
}

s16 ActorCutscene_Stop(s16 index) {
    ActorCutscene* actorCs;

    if (index < 0) {
        return index;
    }

    actorCs = ActorCutscene_GetCutsceneImpl(sActorCsMgr.actorCsId);
    if ((sActorCsMgr.length > 0) && (actorCs->scriptIndex == -1)) {
        return -2;
    }
    if ((index != 0x7F) && (actorCs->scriptIndex != -1)) {
        return -3;
    }

    if (index == 0x7F) {
        index = sActorCsMgr.actorCsId;
    }
    if (index == sActorCsMgr.actorCsId) {
        sActorCsMgr.endActorCsId = sActorCsMgr.actorCsId;
        return sActorCsMgr.endActorCsId;
    }
    return -1;
}

s16 ActorCutscene_GetCurrentIndex(void) {
    return sActorCsMgr.actorCsId;
}

ActorCutscene* ActorCutscene_GetCutscene(s16 index) {
    return ActorCutscene_GetCutsceneImpl(index);
}

s16 ActorCutscene_GetAdditionalCutscene(s16 index) {
    if (index < 0) {
        return -1;
    }
    return ActorCutscene_GetCutsceneImpl(index)->additionalCutscene;
}

s16 ActorCutscene_GetLength(s16 index) {
    if (index < 0) {
        return -1;
    }
    return ActorCutscene_GetCutsceneImpl(index)->length;
}

s16 ActorCutscene_GetCutsceneScriptIndex(s16 index) {
    if (index < 0) {
        return -1;
    }
    return ActorCutscene_GetCutsceneImpl(index)->scriptIndex;
}

s16 func_800F2178(s16 index) {
    if (index < 0) {
        return -1;
    }
    return ActorCutscene_GetCutsceneImpl(index)->unkB;
}

s16 ActorCutscene_GetCurrentSubCamId(s16 index) {
    return sActorCsMgr.subCamId;
}

s16 ActorCutscene_FindEntranceCutscene(void) {
    PlayState* play;
    s32 actorCsId;

    for (actorCsId = 0; actorCsId < sActorCutsceneCount; actorCsId++) {
        //! FAKE:
        if ((sActorCutsceneList[actorCsId].scriptIndex != -1) &&
            (sActorCutsceneList[actorCsId].scriptIndex < (play = sActorCsMgr.play)->csCtx.scriptListCount) &&
            (sActorCsMgr.play->curSpawn ==
             sActorCsMgr.play->csCtx.scriptList[sActorCutsceneList[actorCsId].scriptIndex].spawn)) {
            return actorCsId;
        }
    }

    for (actorCsId = 0; actorCsId < sActorCutsceneCount; actorCsId++) {
        if ((sActorCutsceneList[actorCsId].unkB >= 100) &&
            (sActorCutsceneList[actorCsId].unkB == (sActorCsMgr.play->curSpawn + 100))) {
            return actorCsId;
        }
    }

    return -1;
}

s32 func_800F22C4(s16 actorCsId, Actor* actor) {
    f32 dist;
    s16 screenPosX;
    s16 screenPosY;

    if ((sActorCsMgr.actorCsId == -1) || (actorCsId == -1)) {
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
    if (actorCsId == sActorCsMgr.actorCsId) {
        return 0;
    }
    return 3;
}

void ActorCutscene_SetReturnCamera(s16 camId) {
    sActorCsMgr.retCamId = camId;
}
