#include "global.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

s16 sPlayerInitPosX = 0;
s16 sPlayerInitPosZ = 0;
s16 sPlayerInitDir = 0;

/**
 * Gets the mapIndex for the current dungeon or boss scene
 * @return the current scene's mapIndex, or -1 if it isn't a dungeon or boss scene.
 */
s32 Map_GetDungeonOrBossAreaIndex(PlayState* play) {
    static s32 sDungeonAndBossSceneIds[] = {
        SCENE_MITURIN,  // DUNGEON_INDEX_WOODFALL_TEMPLE
        SCENE_HAKUGIN,  // DUNGEON_INDEX_SNOWHEAD_TEMPLE
        SCENE_SEA,      // DUNGEON_INDEX_GREAT_BAY_TEMPLE
        SCENE_INISIE_N, // DUNGEON_INDEX_STONE_TOWER_TEMPLE
        SCENE_INISIE_R, // DUNGEON_INDEX_STONE_TOWER_TEMPLE
        SCENE_MITURIN_BS, SCENE_HAKUGIN_BS, SCENE_SEA_BS, SCENE_INISIE_BS,
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDungeonAndBossSceneIds); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == sDungeonAndBossSceneIds[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Tests if the current scene is in a dungeon or boss scene.
 * @return true if the current scene is a dungeon or boss scene, false otherwise.
 */
s32 Map_IsInDungeonOrBossArea(PlayState* play) {
    if (Map_GetDungeonOrBossAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

s32 MapExp_CurRoomHasMapI(PlayState* play) {
    if ((Map_GetDungeonOrBossAreaIndex(play) == -1) || !MapDisp_CurRoomHasMapI(play)) {
        return false;
    }

    return true;
}

/**
 * Tests if the current scene is a dungeon scene, excluding boss scenes.
 * @return -1 if not a dungeon scene, else returns the dungeonIndex of the dungeon scene
 */
s32 Map_GetDungeonAreaIndex(PlayState* play) {
    static s32 sDungeonSceneIds[] = {
        SCENE_MITURIN,  // DUNGEON_INDEX_WOODFALL_TEMPLE
        SCENE_HAKUGIN,  // DUNGEON_INDEX_SNOWHEAD_TEMPLE
        SCENE_SEA,      // DUNGEON_INDEX_GREAT_BAY_TEMPLE
        SCENE_INISIE_N, // DUNGEON_INDEX_STONE_TOWER_TEMPLE
        SCENE_INISIE_R, // DUNGEON_INDEX_STONE_TOWER_TEMPLE
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sDungeonSceneIds); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == sDungeonSceneIds[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Test if the current scene is a dungeon scene, excluding boss rooms
 * @return true if the current scene is a dungeon scene, false otherwise.
 */
s32 Map_IsInDungeonScene(PlayState* play) {
    if (Map_GetDungeonAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

/**
 * Tests if the current scene is a boss scene.
 * @return -1 if not a boss scene, else returns the dungeonIndex of the boss scene
 */
s32 Map_GetBossAreaIndex(PlayState* play) {
    static s32 sBossSceneIds[] = {
        SCENE_MITURIN_BS, // DUNGEON_INDEX_WOODFALL_TEMPLE
        SCENE_HAKUGIN_BS, // DUNGEON_INDEX_SNOWHEAD_TEMPLE
        SCENE_SEA_BS,     // DUNGEON_INDEX_GREAT_BAY_TEMPLE
        SCENE_INISIE_BS,  // DUNGEON_INDEX_STONE_TOWER_TEMPLE
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBossSceneIds); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == sBossSceneIds[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Checks if the current scene is a boss scene.
 * @return true if the current scene is a boss scene, false otherwise.
 */
s32 Map_IsInBossScene(PlayState* play) {
    if (Map_GetBossAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

/**
 * Test if the current scene is in a set of overworld scenes.
 * @return -1 if not in the set, else returns the mapIndex of the overworld scene
 */
s32 Map_GetUnkOverworldAreaIndex(PlayState* play) {
    static s32 D_801BF5A4[] = {
        SCENE_22DEKUCITY,
        SCENE_KOEPONARACE,
        SCENE_F01,
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801BF5A4); i++) {
        if (Play_GetOriginalSceneId(play->sceneId) == D_801BF5A4[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Checks if the current scene is in a set of overworld scenes.
 * @return true if the current scene is in the set, false otherwise.
 */
s32 Map_IsInUnkOverworldArea(PlayState* play) {
    if (Map_GetUnkOverworldAreaIndex(play) == -1) {
        return false;
    }

    return true;
}

/**
 * Sets the position and rotation of where the player has entered the area.
 * Used to draw the red marker on the minimap.
 */
void Map_SetAreaEntrypoint(PlayState* play) {
    Player* player = GET_PLAYER(play);

    sPlayerInitPosX = player->actor.world.pos.x;
    sPlayerInitPosZ = player->actor.world.pos.z;
    sPlayerInitDir = (0x7FFF - player->actor.shape.rot.y) / 0x400;
}

void Map_InitRoomData(PlayState* play, s16 room) {
    s32 mapIndex = gSaveContext.mapIndex;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    MapDisp_SwapRooms(room);

    if (room >= 0) {
        if (Map_IsInDungeonOrBossArea(play)) {
            SET_ROOM_VISITED(Play_GetOriginalSceneId(play->sceneId), room);
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
    MapDisp_Destroy(play);
}

void Map_Init(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s32 dungeonIndex;

    MapDisp_SwapRooms(play->roomCtx.curRoom.num);
    interfaceCtx->unk_278 = -1;
    interfaceCtx->dungeonOrBossAreaMapIndex = -1;
    interfaceCtx->mapSegment = THA_AllocTailAlign16(&play->state.tha, 0x1000);
    if (Map_IsInUnkOverworldArea(play)) {
        gSaveContext.mapIndex = Map_GetUnkOverworldAreaIndex(play);
        return;
    }

    if (Map_IsInDungeonOrBossArea(play)) {
        gSaveContext.mapIndex = dungeonIndex = Map_GetDungeonOrBossAreaIndex(play);
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

void Map_DrawMinimap(PlayState* play) {
    MapDisp_DrawMinimap(play, sPlayerInitPosX, sPlayerInitPosZ, sPlayerInitDir);
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
        !Play_InCsMode(play) && !MapDisp_IsMinimapToggleBlocked(play)) {
        if (!R_MINIMAP_DISABLED) {
            Audio_PlaySfx(NA_SE_SY_CAMERA_ZOOM_UP);
        } else {
            Audio_PlaySfx(NA_SE_SY_CAMERA_ZOOM_DOWN);
        }

        R_MINIMAP_DISABLED ^= 1;
    }

    MapDisp_Update(play);

    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
        if (Map_IsInDungeonScene(play)) {
            floor = MapDisp_GetPlayerStorey(player->actor.world.pos.y);
            if (floor != -1) {
                SET_DUNGEON_FLOOR_VISITED(Play_GetOriginalSceneId(play->sceneId), FLOOR_INDEX_MAX - floor);
                R_PLAYER_FLOOR_REVERSE_INDEX = FLOOR_INDEX_MAX - floor;
                if (interfaceCtx->mapRoomNum != sLastRoomNum) {
                    sLastRoomNum = interfaceCtx->mapRoomNum;
                }
            }
        } else if (Map_IsInBossScene(play)) {
            MapDisp_GetBossIconY();
            R_PLAYER_FLOOR_REVERSE_INDEX = FLOOR_INDEX_MAX - MapDisp_GetBossRoomStorey();
        }
    }
}
