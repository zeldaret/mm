#include "global.h"

static s16 sPlayerInitialPosX = 0;
static s16 sPlayerInitialPosZ = 0;
static s16 sPlayerInitialDirection = 0;

static s32 sDungeonAndBossScenes[] = {
    SCENE_MITURIN,    SCENE_HAKUGIN,    SCENE_SEA,    SCENE_INISIE_N,  SCENE_INISIE_R,
    SCENE_MITURIN_BS, SCENE_HAKUGIN_BS, SCENE_SEA_BS, SCENE_INISIE_BS,
};

static s32 sDungeonScenes[] = {
    SCENE_MITURIN, SCENE_HAKUGIN, SCENE_SEA, SCENE_INISIE_N, SCENE_INISIE_R,
};

static s32 sBossScenes[] = {
    SCENE_MITURIN_BS,
    SCENE_HAKUGIN_BS,
    SCENE_SEA_BS,
    SCENE_INISIE_BS,
};

static s32 D_801BF5A4[] = {
    SCENE_22DEKUCITY,
    SCENE_KOEPONARACE,
    SCENE_F01,
};

static s16 sLastRoomNum = 99;

s32 Map_GetDungeonOrBossAreaIndex(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDungeonAndBossScenes); i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == sDungeonAndBossScenes[i]) {
            return i;
        }
    }

    return -1;
}

s32 Map_IsInDungeonOrBossArea(PlayState* play) {
    if (Map_GetDungeonOrBossAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 func_8010A0A4(PlayState* play) {
    if ((Map_GetDungeonOrBossAreaIndex(play) == -1) || (func_80102EF0(play) == 0)) {
        return false;
    }

    return true;
}

s32 Map_GetDungeonAreaIndex(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDungeonScenes); i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == sDungeonScenes[i]) {
            return i;
        }
    }

    return -1;
}

s32 Map_IsInDungeonArea(PlayState* play) {
    if (Map_GetDungeonAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 Map_GetBossAreaIndex(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBossScenes); i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == sBossScenes[i]) {
            return i;
        }
    }

    return -1;
}

s32 Map_IsInBossArea(PlayState* play) {
    if (Map_GetBossAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 func_8010A238(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801BF5A4); i++) {
        if (Play_GetOriginalSceneNumber(play->sceneNum) == D_801BF5A4[i]) {
            return i;
        }
    }

    return -1;
}

s32 func_8010A2AC(PlayState* play) {
    if (func_8010A238(play) == -1) {
        return false;
    }

    return true;
}

void Map_SavePlayerInitialInfo(PlayState* play) {
    Player* player = GET_PLAYER(play);

    sPlayerInitialPosX = player->actor.world.pos.x;
    sPlayerInitialPosZ = player->actor.world.pos.z;
    sPlayerInitialDirection = ((0x7FFF - player->actor.shape.rot.y) / 0x400);
}

void Map_InitRoomData(PlayState* play, s16 room) {
    s32 mapIndex;
    InterfaceContext* interfaceCtx;

    mapIndex = gSaveContext.mapIndex;
    func_80105C40(room);
    if (room >= 0) {
        if (Map_IsInDungeonOrBossArea(play)) {
            interfaceCtx = &play->interfaceCtx;
            gSaveContext.save.permanentSceneFlags[Play_GetOriginalSceneNumber(play->sceneNum)].unk_18 |=
                gBitFlags[room];
            interfaceCtx->mapRoomNum = room;
            interfaceCtx->unk_27A = mapIndex;
        }
    } else {
        play->interfaceCtx.mapRoomNum = 0;
    }

    if (gSaveContext.sunsSongState != SUNSSONG_SPEED_TIME) {
        gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
    }
}

void Map_Destroy(void) {
    func_80105A40();
}

void Map_Init(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s32 dungeonIndex;

    func_80105C40(play->roomCtx.currRoom.num);
    interfaceCtx->unk_278 = -1;
    interfaceCtx->unk_27A = -1;
    interfaceCtx->mapSegment = THA_AllocEndAlign16(&play->state.heap, 0x1000);
    if (func_8010A2AC(play)) {
        gSaveContext.mapIndex = func_8010A238(play);
        return;
    }

    if (Map_IsInDungeonOrBossArea(play)) {
        dungeonIndex = Map_GetDungeonOrBossAreaIndex(play);
        gSaveContext.mapIndex = dungeonIndex;
        switch (play->sceneNum) {
            case SCENE_MITURIN_BS:
                dungeonIndex = 0;
                break;
            case SCENE_HAKUGIN_BS:
                dungeonIndex = 1;
                break;
            case SCENE_SEA_BS:
                dungeonIndex = 2;
                break;
            case SCENE_INISIE_BS:
                dungeonIndex = 3;
                break;
        }

        gSaveContext.unk_48C8 = dungeonIndex;
        Map_InitRoomData(play, play->roomCtx.currRoom.num);
    }
}

void Minimap_Draw(PlayState* play) {
    func_80106644(play, sPlayerInitialPosX, sPlayerInitialPosZ, sPlayerInitialDirection);
}

void Map_Update(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    Input* controller = CONTROLLER1(&play->state);
    s32 pad1;
    s16 temp_v0_2;
    s32 pad2;

    if ((play->pauseCtx.state < 4) && (CHECK_BTN_ALL(controller->press.button, BTN_L)) && (!Play_InCsMode(play)) &&
        (!func_80106530(play))) {
        if (!XREG(95)) {
            play_sound(NA_SE_SY_CAMERA_ZOOM_UP);
        } else {
            play_sound(NA_SE_SY_CAMERA_ZOOM_DOWN);
        }

        XREG(95) ^= 1;
    }

    func_80105B34(play);

    if ((play->pauseCtx.state == 0) && (play->pauseCtx.debugState == 0)) {
        if (Map_IsInDungeonArea(play)) {
            temp_v0_2 = func_80109124(player->actor.world.pos.y);
            if (temp_v0_2 != -1) {
                gSaveContext.save.permanentSceneFlags[Play_GetOriginalSceneNumber(play->sceneNum)].unk_14 |=
                    gBitFlags[4 - temp_v0_2];
                XREG(94) = 4 - temp_v0_2;
                if (interfaceCtx->mapRoomNum != sLastRoomNum) {
                    sLastRoomNum = interfaceCtx->mapRoomNum;
                }
            }
        } else if (Map_IsInBossArea(play)) {
            func_80105294();
            XREG(94) = 4 - func_80105318();
        }
    }
}
