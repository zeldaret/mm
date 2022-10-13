#include "global.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

s16 sMinimapInitPosX = 0;
s16 sMinimapInitPosZ = 0;
s16 sMinimapInitDir = 0;

s32 sDungeonAndBossSceneIds[] = {
    SCENE_MITURIN,    SCENE_HAKUGIN,    SCENE_SEA,    SCENE_INISIE_N,  SCENE_INISIE_R,
    SCENE_MITURIN_BS, SCENE_HAKUGIN_BS, SCENE_SEA_BS, SCENE_INISIE_BS,
};

/**
 * If the current scene is a dungeon or boss scene, this function returns an index
 * indicating which one it is. Otherwise, it returns -1.
 */
s32 Map_GetDungeonOrBossAreaIndex(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDungeonAndBossSceneIds); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == sDungeonAndBossSceneIds[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Returns true if the current scene is a dungeon or boss scene, false otherwise.
 */
s32 Map_IsInDungeonOrBossArea(PlayState* play) {
    if (Map_GetDungeonOrBossAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 func_8010A0A4(PlayState* play) {
    if ((Map_GetDungeonOrBossAreaIndex(play) == -1) || !func_80102EF0(play)) {
        return false;
    }

    return true;
}

s32 sDungeonSceneIds[] = {
    SCENE_MITURIN, SCENE_HAKUGIN, SCENE_SEA, SCENE_INISIE_N, SCENE_INISIE_R,
};

/**
 * If the current scene is a dungeon scene, this function returns an index
 * indicating which one it is. Otherwise, it returns -1.
 */
s32 Map_GetDungeonAreaIndex(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDungeonSceneIds); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == sDungeonSceneIds[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Returns true if the current scene is a dungeon scene, false otherwise.
 */
s32 Map_IsInDungeonArea(PlayState* play) {
    if (Map_GetDungeonAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 sBossSceneIds[] = {
    SCENE_MITURIN_BS, // DUNGEON_INDEX_WOODFALL_TEMPLE
    SCENE_HAKUGIN_BS, // DUNGEON_INDEX_SNOWHEAD_TEMPLE
    SCENE_SEA_BS,     // DUNGEON_INDEX_GREAT_BAY_TEMPLE
    SCENE_INISIE_BS,  // DUNGEON_INDEX_STONE_TOWER_TEMPLE
};

/**
 * If the current scene is a boss scene, this function returns an index
 * indicating which one it is. Otherwise, it returns -1.
 */
s32 Map_GetBossAreaIndex(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBossSceneIds); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == sBossSceneIds[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Returns true if the current scene is a boss scene, false otherwise.
 */
s32 Map_IsInBossArea(PlayState* play) {
    if (Map_GetBossAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 D_801BF5A4[] = {
    SCENE_22DEKUCITY,
    SCENE_KOEPONARACE,
    SCENE_F01,
};

s32 func_8010A238(PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801BF5A4); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == D_801BF5A4[i]) {
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

/**
 * When a room is loaded, this function is used to save the player's position and rotation
 * so that the red arrow on the minimap can be drawn correctly.
 */
void Minimap_SavePlayerRoomInitInfo(PlayState* play) {
    Player* player = GET_PLAYER(play);

    sMinimapInitPosX = player->actor.world.pos.x;
    sMinimapInitPosZ = player->actor.world.pos.z;
    sMinimapInitDir = (0x7FFF - player->actor.shape.rot.y) / 0x400;
}

void Map_InitRoomData(PlayState* play, s16 room) {
    s32 mapIndex = gSaveContext.mapIndex;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    func_80105C40(room);

    if (room >= 0) {
        if (Map_IsInDungeonOrBossArea(play)) {
            gSaveContext.save.permanentSceneFlags[Play_GetOriginalSceneId(play->sceneId)].rooms |= gBitFlags[room];
            interfaceCtx->mapRoomNum = room;
            interfaceCtx->dungeonOrBossAreaMapIndex = mapIndex;
        }
    } else {
        interfaceCtx->mapRoomNum = 0;
    }

    if (gSaveContext.sunsSongState != SUNSSONG_SPEED_TIME) {
        gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
    }
}

void Map_Destroy(PlayState* play) {
    func_80105A40(play);
}

void Map_Init(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s32 dungeonIndex;

    func_80105C40(play->roomCtx.curRoom.num);
    interfaceCtx->unk_278 = -1;
    interfaceCtx->dungeonOrBossAreaMapIndex = -1;
    interfaceCtx->mapSegment = THA_AllocEndAlign16(&play->state.heap, 0x1000);
    if (func_8010A2AC(play)) {
        gSaveContext.mapIndex = func_8010A238(play);
        return;
    }

    if (Map_IsInDungeonOrBossArea(play)) {
        dungeonIndex = Map_GetDungeonOrBossAreaIndex(play);
        gSaveContext.mapIndex = dungeonIndex;
        switch (play->sceneId) {
            case SCENE_MITURIN_BS:
                dungeonIndex = DUNGEON_INDEX_WOODFALL_TEMPLE;
                break;

            case SCENE_HAKUGIN_BS:
                dungeonIndex = DUNGEON_INDEX_SNOWHEAD_TEMPLE;
                break;

            case SCENE_SEA_BS:
                dungeonIndex = DUNGEON_INDEX_GREAT_BAY_TEMPLE;
                break;

            case SCENE_INISIE_BS:
                dungeonIndex = DUNGEON_INDEX_STONE_TOWER_TEMPLE;
                break;
        }

        gSaveContext.dungeonIndex = dungeonIndex;
        Map_InitRoomData(play, play->roomCtx.curRoom.num);
    }
}

void Minimap_Draw(PlayState* play) {
    func_80106644(play, sMinimapInitPosX, sMinimapInitPosZ, sMinimapInitDir);
}

s16 sLastRoomNum = 99;

void Map_Update(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    Input* controller = CONTROLLER1(&play->state);
    s32 pad1;
    s16 floor;
    s32 pad2;

    if ((play->pauseCtx.state <= PAUSE_STATE_OPENING_2) && (CHECK_BTN_ALL(controller->press.button, BTN_L)) &&
        !Play_InCsMode(play) && !func_80106530(play)) {
        if (!R_MINIMAP_DISABLED) {
            play_sound(NA_SE_SY_CAMERA_ZOOM_UP);
        } else {
            play_sound(NA_SE_SY_CAMERA_ZOOM_DOWN);
        }

        R_MINIMAP_DISABLED ^= 1;
    }

    func_80105B34(play);

    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
        if (Map_IsInDungeonArea(play)) {
            floor = func_80109124(player->actor.world.pos.y);
            if (floor != -1) {
                gSaveContext.save.permanentSceneFlags[Play_GetOriginalSceneId(play->sceneId)].unk_14 |=
                    gBitFlags[FLOOR_INDEX_MAX - floor];
                R_REVERSE_FLOOR_INDEX = FLOOR_INDEX_MAX - floor;
                if (interfaceCtx->mapRoomNum != sLastRoomNum) {
                    sLastRoomNum = interfaceCtx->mapRoomNum;
                }
            }
        } else if (Map_IsInBossArea(play)) {
            func_80105294();
            R_REVERSE_FLOOR_INDEX = FLOOR_INDEX_MAX - func_80105318();
        }
    }
}
