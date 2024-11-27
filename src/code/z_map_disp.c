#include "prevent_bss_reordering.h"
#include "global.h"
#include "gfx.h"
#include "sys_cmpdma.h"
#include "assets/interface/icon_item_dungeon_static/icon_item_dungeon_static.h"
#include "assets/interface/parameter_static/parameter_static.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

void MapDisp_DestroyMapI(PlayState* play);
void MapDisp_InitMapI(PlayState* play);

#include "gDPLoadTextureBlock_Runtime.inc.c"

static UNK_TYPE4 D_801BEB30[2] = { 0, 0 };

static u64 sWhiteSquareTex[] = {
#include "assets/code/z_map_disp/white_square.i4.inc.c"
};
static MapDisp sMapDisp = {
    NULL, -1, 210, 140, 0, 0,    NULL, -1, NULL, 0,    0, 0, 0,    NULL, NULL, 0,
    0,    0,  0,   0,   0, NULL, 0,    0,  0,    NULL, 0, 0, NULL, 0,    0,
};

MapDataRoom sMapDataRooms[ROOM_MAX];
MapDataChest sMapDataChests[32];
static MapDataScene sMapDataScene = {
    sMapDataRooms,
    80,
};
static s32 sSceneNumRooms = 0; // current scene's no. of rooms
static s32 sNumChests = 0;     // MinimapChest count
static TransitionActorList sTransitionActorList = { 0, NULL };
static Color_RGBA8 sMinimapActorCategoryColors[12] = {
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 255, 0, 255 },     { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }, { 255, 0, 0, 255 },     { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }, { 255, 0, 0, 255 },     { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
};

TransitionActorEntry sTransitionActors[ROOM_TRANSITION_MAX];
PauseDungeonMap sPauseDungeonMap;

void MapDisp_GetMapITexture(void* dst, s32 mapCompactId) {
    if (MapDisp_GetSizeOfMapITex(mapCompactId) != 0) {
        CmpDma_LoadFile(SEGMENT_ROM_START(map_i_static), mapCompactId, dst, MapDisp_GetSizeOfMapITex(mapCompactId));
    }
}

void MapDisp_InitRoomStoreyRecord(PlayState* play, s16* roomStorey) {
    *roomStorey = -1;
}

void MapDisp_DestroyRoomStoreyRecord(PlayState* play, s16* roomStory) {
}

void func_80102EB4(u32 flag) {
    sMapDisp.unk20 |= flag;
}

void func_80102ED0(u32 flag) {
    sMapDisp.unk20 &= ~flag;
}

s32 MapDisp_CurRoomHasMapI(PlayState* play) {
    MapDataRoom* mapDataRoom;
    s8 curRoom;

    if (Map_IsInBossScene(play) == true) {
        return true;
    }
    curRoom = play->roomCtx.curRoom.num;
    if (curRoom == -1) {
        return false;
    }
    mapDataRoom = &sMapDisp.mapDataScene->rooms[curRoom];
    if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
        return false;
    }
    if (MapData_GetMapIId(mapDataRoom->mapId) == MAPDATA_MAP_I_MAX) {
        return false;
    }
    return true;
}

/**
 * Computes the storey containing checkY and returns the floor Y value.
 * @note Only used to check if a chest is on the same storey as the player.
 */
f32 MapDisp_GetStoreyY(f32 checkY) {
    s32 i;

    if ((sMapDisp.storeyYList[sMapDisp.numStoreys - 1] - 80.0f) < checkY) {
        return sMapDisp.storeyYList[sMapDisp.numStoreys - 1];
    }
    for (i = sMapDisp.numStoreys - 2; i >= 0; i--) {
        if (((sMapDisp.storeyYList[i] - 80.0f) < checkY) && (checkY < (sMapDisp.storeyYList[i + 1] + 80.0f))) {
            return sMapDisp.storeyYList[i];
        }
    }
    if (checkY < (sMapDisp.storeyYList[0] + 80.0f)) {
        return sMapDisp.storeyYList[0];
    }
    return 0.0f;
}

void MapDisp_GetMapTexDim(MapDataRoom* mapDataRoom, s32* width, s32* height) {
    MapData_GetMapTexDim(mapDataRoom->mapId, width, height);
}

void MapDisp_GetMapScale(MapDataRoom* mapDataRoom, s32* scale) {
    MapData_GetMapScale(mapDataRoom->mapId, scale);
    if (*scale == 0) {
        *scale = 20;
    }
}

void MapDisp_GetMapOffset(MapDataRoom* mapDataRoom, s32* offsetX, s32* offsetY) {
    s32 width;
    s32 height;

    if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
        *offsetX = 0;
        *offsetY = 0;
        return;
    }
    MapDisp_GetMapTexDim(mapDataRoom, &width, &height);
    MapData_GetMapTexOffset(mapDataRoom->mapId, offsetX, offsetY);
    if (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_X) {
        s32 temp = (width / 2);

        *offsetX = ((width / 2) - *offsetX) + (width / 2);
    }
    if (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_Y) {
        s32 temp = (height / 2);

        *offsetY = (temp - *offsetY) + temp;
    }
}

void MapDisp_DrawMinimapRoom(PlayState* play, TexturePtr texture, s32 x, s32 y, s32 room, f32 intensity) {
    MapDataRoom* mapDataRoom = &sMapDisp.mapDataScene->rooms[room];
    s32 texWidth;
    s32 texHeight;
    s32 dtdy;
    s32 dsdx;
    s32 t;
    s32 s;
    s16 dsdx_temp;
    s16 dtdy_temp;
    Color_RGBA8 color;
    s32 drawType;

    if ((mapDataRoom->mapId == MAP_DATA_NO_MAP) || (texture == NULL)) {
        return;
    }

    MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL39_Overlay(play->state.gfxCtx);
    MapData_GetMapColor(MapData_GetMapColorIndex(mapDataRoom->mapId), &color);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, color.r, color.g, color.b,
                    (s32)(play->interfaceCtx.minimapAlpha * intensity * color.a / 255.0f));
    MapData_GetDrawType(mapDataRoom->mapId, &drawType);

    switch (drawType) {
        case MAPDATA_DRAW_1:
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, texture, G_IM_FMT_IA, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;

        case MAPDATA_DRAW_3:
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, texture, G_IM_FMT_I, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;

        default:
        case MAPDATA_DRAW_0:
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, texture, G_IM_FMT_I, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;
    }

    s = (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_X) ? (texWidth - 1) << 5 : 0;
    t = (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_Y) ? 0 : (texHeight - 1) << 5;

    dsdx_temp = ((mapDataRoom->flags & MAP_DATA_ROOM_FLIP_X) ? -1 : 1) * (1 << 10);
    dtdy_temp = ((mapDataRoom->flags & MAP_DATA_ROOM_FLIP_Y) ? 1 : -1) * (1 << 10);

    dsdx = (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_X) ? dsdx_temp & 0xFFFF : dsdx_temp;
    dtdy = (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_Y) ? dtdy_temp : dtdy_temp & 0xFFFF;

    gSPTextureRectangle(OVERLAY_DISP++, x << 2, y << 2, (texWidth + x) << 2, (y + texHeight) << 2, G_TX_RENDERTILE, s,
                        t, dsdx, dtdy);

    CLOSE_DISPS(play->state.gfxCtx);
}

// Tests if the map data should be rotated 180 degrees
// SCENE_35TAKI is the only scene with data flipped in this manner.
s32 MapDisp_IsDataRotated(PlayState* play) {
    if (play->sceneId == SCENE_35TAKI) {
        return true;
    }
    return false;
}

s32 MapDisp_CanDrawDoors(PlayState* play) {
    if ((gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0)) && (Cutscene_GetSceneLayer(play) != 0)) {
        return false;
    }
    return true;
}

void MapDisp_Minimap_DrawActorIcon(PlayState* play, Actor* actor) {
    MapDataRoom* mapDataRoom;
    s32 posX;
    s32 posY;
    s32 texOffsetX;
    s32 texOffsetY;
    s32 texWidth;
    s32 texHeight;
    f32 scaleFrac;
    f32 unused1;
    f32 unused2;
    Player* player = GET_PLAYER(play);
    s32 scale;

    // inferred from `MapDisp_Minimap_DrawDoorActor`
    unused1 = fabsf(player->actor.world.pos.y - actor->world.pos.y);
    unused2 = 1.0f - (1 / 350.0f) * unused1;

    if (unused2 < 0.0f) {
        unused2 = 0.0f;
    }

    mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
    if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
        return;
    }

    MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
    MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);

    scale = sMapDisp.mapDataScene->scale;
    if (sMapDisp.mapDataScene->scale == 0) {
        scale = 20;
    } else if (sMapDisp.mapDataScene->scale == -1) {
        s32 scaleTemp;

        MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
        scale = scaleTemp;
    }

    scaleFrac = 1.0f / scale;
    if (!MapDisp_IsDataRotated(play)) {
        posX = (s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
        posY = (s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;
    } else {
        posX = -(s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
        posY = -(s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;
    }

    if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((actor->category == ACTORCAT_PLAYER) && (actor->flags & ACTOR_FLAG_MINIMAP_ICON_ENABLED)) {
            s16 compassRot;

            Gfx_SetupDL42_Overlay(play->state.gfxCtx);
            gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);

            Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
            Matrix_RotateXFApply(-1.6f);
            compassRot = (s32)(0x7FFF - actor->focus.rot.y) / 1024;
            if (MapDisp_IsDataRotated(play)) {
                compassRot += 0x7FFF;
            }
            Matrix_RotateYF(compassRot / 10.0f, MTXMODE_APPLY);
            Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
            MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 255, 0, play->interfaceCtx.minimapAlpha);
            gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);
        } else if ((actor->id == ACTOR_EN_BOX) && !Flags_GetTreasure(play, actor->params & 0x1F) &&
                   (MapDisp_GetStoreyY(player->actor.world.pos.y) == MapDisp_GetStoreyY(actor->world.pos.y))) {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetTextureLUT(OVERLAY_DISP++, G_TT_NONE);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, play->interfaceCtx.minimapAlpha);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
            gDPPipeSync(OVERLAY_DISP++);

            gDPLoadTextureBlock_Runtime(OVERLAY_DISP++, gMapChestIconTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                        G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, (posX - 4) << 2, (posY - 4) << 2, (posX + 4) << 2, (posY + 4) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        } else {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            if (actor->flags & ACTOR_FLAG_MINIMAP_ICON_ENABLED) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMinimapActorCategoryColors[actor->category].r,
                                sMinimapActorCategoryColors[actor->category].g,
                                sMinimapActorCategoryColors[actor->category].b, play->interfaceCtx.minimapAlpha);
                gSPTextureRectangle(OVERLAY_DISP++, (posX - 1) << 2, (posY - 1) << 2, (posX + 1) << 2, (posY + 1) << 2,
                                    G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
            }
        }
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void MapDisp_Minimap_DrawActors(PlayState* play) {
    ActorContext* actorCtx;
    s32 i;

    if (play->roomCtx.curRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &sWhiteSquareTex, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actorCtx = &play->actorCtx;
        for (i = 0; i < ACTORCAT_MAX; i++) {
            Actor* actor = actorCtx->actorLists[i].first;

            while (actor != NULL) {
                if ((actor->update != NULL) && (actor->init == NULL) &&
                    Object_IsLoaded(&play->objectCtx, actor->objectSlot) &&
                    ((actor->id == ACTOR_EN_BOX) || (i == ACTORCAT_PLAYER) ||
                     (actor->flags & ACTOR_FLAG_MINIMAP_ICON_ENABLED)) &&
                    ((sMapDisp.curRoom == actor->room) || (actor->room == -1))) {
                    MapDisp_Minimap_DrawActorIcon(play, actor);
                }
                actor = actor->next;
            }
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void MapDisp_Minimap_DrawDoorActor(PlayState* play, Actor* actor) {
    MapDataRoom* mapDataRoom;
    s32 posX;
    s32 posY;
    s32 texOffsetX;
    s32 texOffsetY;
    s32 texWidth;
    s32 texHeight;
    Player* player = GET_PLAYER(play);
    f32 scaleFrac;
    f32 yDistFromPlayer = fabsf(player->actor.world.pos.y - actor->world.pos.y);
    s32 scale;
    f32 yDistAlpha = 1.0f - (1.0f / 350.0f) * yDistFromPlayer;

    if (yDistAlpha < 0.0f) {
        yDistAlpha = 0.0f;
    }
    mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
    if (mapDataRoom->mapId != MAP_DATA_NO_MAP) {
        MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
        MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);

        scale = sMapDisp.mapDataScene->scale;
        if (sMapDisp.mapDataScene->scale == 0) {
            scale = 20;
        } else if (sMapDisp.mapDataScene->scale == -1) {
            s32 scaleTemp;

            MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
            scale = scaleTemp;
        }
        scaleFrac = 1.0f / scale;
        if (!MapDisp_IsDataRotated(play)) {
            posX = (((s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
                     sMapDisp.minimapCurX) -
                    sMapDisp.minimapBaseX) +
                   texOffsetX;
            posY = (((s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
                     sMapDisp.minimapCurY) -
                    sMapDisp.minimapBaseY) +
                   texOffsetY;
        } else {
            posX = (((sMapDisp.minimapBaseX - (s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac)) +
                     sMapDisp.minimapCurX) -
                    sMapDisp.minimapBaseX) +
                   texOffsetX;
            posY = (((sMapDisp.minimapBaseY - (s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac)) +
                     sMapDisp.minimapCurY) -
                    sMapDisp.minimapBaseY) +
                   texOffsetY;
        }
        if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
            OPEN_DISPS(play->state.gfxCtx);

            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

            if ((actor->category == ACTORCAT_DOOR) && MapDisp_CanDrawDoors(play)) {
                s32 pad;

                gDPSetPrimColor(
                    OVERLAY_DISP++, 0, 0, sMinimapActorCategoryColors[actor->category].r,
                    sMinimapActorCategoryColors[actor->category].g, sMinimapActorCategoryColors[actor->category].b,
                    (s32)((sMinimapActorCategoryColors[actor->category].a * (1.0f - sMapDisp.swapAnimTimer * 0.05f) *
                           yDistAlpha * play->interfaceCtx.minimapAlpha) /
                          255.0f));

                scale = sMapDisp.mapDataScene->scale;
                if (sMapDisp.mapDataScene->scale == 0) {
                    scale = 20;
                } else if (sMapDisp.mapDataScene->scale == -1) {
                    s32 scaleTemp;

                    MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
                    scale = scaleTemp;
                }
                if (scale <= 50) {
                    gSPTextureRectangle(OVERLAY_DISP++, (posX - 2) << 2, (posY - 2) << 2, (posX + 2) << 2,
                                        (posY + 2) << 2, G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
                } else {
                    gSPTextureRectangle(OVERLAY_DISP++, (posX - 1) << 2, (posY - 1) << 2, (posX + 1) << 2,
                                        (posY + 1) << 2, G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
                }
            }

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}

void MapDisp_Minimap_DrawDoorActors(PlayState* play) {
    s32 i;
    Actor* actor;

    if (play->roomCtx.curRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &sWhiteSquareTex, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actor = play->actorCtx.actorLists[ACTORCAT_DOOR].first;
        while (actor != NULL) {
            if ((actor->update != NULL) && (actor->init == NULL) &&
                Object_IsLoaded(&play->objectCtx, actor->objectSlot) &&
                ((sMapDisp.curRoom == actor->room) || (actor->room == -1))) {
                MapDisp_Minimap_DrawDoorActor(play, actor);
            }
            actor = actor->next;
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

/**
 * @brief Waits for GAMEPLAY_DANGEON_KEEP to load, if it is a current object depenency
 *
 * @param play
 */
void MapDisp_AwaitGameplayDangeonKeep(PlayState* play) {
    s32 objectSlot = Object_GetSlot(&play->objectCtx, GAMEPLAY_DANGEON_KEEP);

    if (objectSlot <= OBJECT_SLOT_NONE) {
        sMapDisp.unk20 |= 1;
        return;
    }

    while (true) {
        if (Object_IsLoaded(&play->objectCtx, objectSlot)) {
            break;
        }
    }
}

void MapDisp_Init(PlayState* play) {
    s32 i;

    sMapDisp.mapDataScene = NULL;
    sMapDisp.curRoom = -1;
    sMapDisp.minimapBaseX = 210;
    sMapDisp.minimapBaseY = 140;
    sMapDisp.minimapCurX = 210;
    sMapDisp.minimapCurY = 140;
    sMapDisp.minimapCurTex = NULL;
    sMapDisp.prevRoom = -1;
    sMapDisp.minimapPrevTex = NULL;
    sMapDisp.minimapPrevX = 0;
    sMapDisp.minimapPrevY = 0;
    sMapDisp.unk20 = 0;
    sMapDisp.swapAnimTimer = 0;

    if (!Map_IsInBossScene(play)) {
        sSceneNumRooms = play->roomList.count;
    }
    sMapDisp.texBuff0 = THA_AllocTailAlign16(&play->state.tha, 0x4000);
    sMapDisp.texBuff1 = THA_AllocTailAlign16(&play->state.tha, 0x4000);
    MapDisp_AwaitGameplayDangeonKeep(play);
    if (!Map_IsInBossScene(play)) {
        sMapDisp.sceneMinX = 0;
        sMapDisp.sceneMinZ = 0;
        sMapDisp.sceneWidth = 100;
        sMapDisp.sceneHeight = 100;
        sMapDisp.sceneMidX = TRUNCF_BINANG((f32)sMapDisp.sceneMinX + ((f32)sMapDisp.sceneWidth * 0.5f));
        sMapDisp.sceneMidZ = TRUNCF_BINANG((f32)sMapDisp.sceneMinZ + ((f32)sMapDisp.sceneHeight * 0.5f));
    }
    sMapDisp.roomStoreyList = THA_AllocTailAlign16(&play->state.tha, sSceneNumRooms * sizeof(s16));

    for (i = 0; i < sSceneNumRooms; i++) {
        MapDisp_InitRoomStoreyRecord(play, &sMapDisp.roomStoreyList[i]);
    }
    sMapDisp.storeyYList = THA_AllocTailAlign16(&play->state.tha, ROOM_MAX * sizeof(s16));

    for (i = 0; i < ROOM_MAX; i++) {
        sMapDisp.storeyYList[i] = FLOOR_MIN_Y;
    }
    MapDisp_InitMapI(play);
    sMapDisp.bossRoomStorey = 0;
    sMapDisp.unk5A = 0;
    if (Map_IsInBossScene(play)) {
        MapDisp_InitMapData(play, NULL);
        MapDisp_InitChestData(play, 0, NULL);
    }
}

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ s16 bottomStorey;
} MapCustomBottomStorey; // size = 0x4

void MapDisp_InitSceneFloorData(PlayState* play) {
    static MapCustomBottomStorey sCustomBottomStorey[] = {
        { SCENE_HAKUGIN, -1 }, { SCENE_HAKUGIN_BS, -1 }, { SCENE_SEA, -2 },
        { SCENE_SEA_BS, -2 },  { SCENE_INISIE_N, -1 },
    };
    s32 i1;
    s32 i2;
    s32 i3;
    s32 storey;

    // init table
    for (i1 = 0; i1 < ROOM_MAX; i1++) {
        sMapDisp.storeyYList[i1] = FLOOR_MIN_Y;
    }

    // for all rooms in scene
    for (i2 = 0; i2 < sSceneNumRooms; i2++) {
        MapDataRoom* mapDataRoom = &sMapDisp.mapDataScene->rooms[i2];

        if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
            continue;
        }
        // add item to the table if it is a newish value
        for (i1 = 0; i1 < ROOM_MAX; i1++) {
            if (sMapDisp.storeyYList[i1] == FLOOR_MIN_Y) {
                sMapDisp.storeyYList[i1] = mapDataRoom->floorY;
                break;
            } else if (fabsf((f32)sMapDisp.storeyYList[i1] - (f32)mapDataRoom->floorY) < 5.0f) {
                break;
            }
        }
    }

    // sort the table in ascending order
    for (i2 = 0; i2 < sSceneNumRooms; i2++) {
        if (sMapDisp.storeyYList[i2] == FLOOR_MIN_Y) {
            break;
        }
        for (i3 = i2 + 1; i3 < sSceneNumRooms; i3++) {
            if (sMapDisp.storeyYList[i3] == FLOOR_MIN_Y) {
                break;
            }
            if (sMapDisp.storeyYList[i3] < sMapDisp.storeyYList[i2]) {
                s16 swap = sMapDisp.storeyYList[i2];

                sMapDisp.storeyYList[i2] = sMapDisp.storeyYList[i3];
                sMapDisp.storeyYList[i3] = swap;
            }
        }
    }

    for (i2 = 0; i2 < sSceneNumRooms; i2++) {
        MapDataRoom* mapDataRoom = &sMapDisp.mapDataScene->rooms[i2];

        sMapDisp.roomStoreyList[i2] = -1;

        for (storey = 0; storey < sSceneNumRooms; storey++) {
            if (sMapDisp.storeyYList[storey] != FLOOR_MIN_Y) {
                if (fabsf((f32)sMapDisp.storeyYList[storey] - (f32)mapDataRoom->floorY) < 5.0f) {
                    sMapDisp.roomStoreyList[i2] = storey;
                    break;
                }
            }
        }
    }
    sMapDisp.numStoreys = 0;
    for (i2 = 0; i2 < sSceneNumRooms; i2++) {
        if (sMapDisp.storeyYList[i2] != FLOOR_MIN_Y) {
            sMapDisp.numStoreys++;
        }
    }
    sMapDisp.bottomStorey = 0;
    for (i2 = 0; i2 < ARRAY_COUNT(sCustomBottomStorey); i2++) {
        if (play->sceneId == sCustomBottomStorey[i2].sceneId) {
            sMapDisp.bottomStorey = sCustomBottomStorey[i2].bottomStorey;
        }
    }
}

/**
 * Unused result
 * @returns the y position to place the boss room skull icon on the pause map.
 * The result position is the inverse of what it should be, stacking lower rooms above higher ones
 */
s32 MapDisp_GetBossIconY(void) {
    s32 dungeonMapFloorIconPosY[5] = { 67, 81, 95, 109, 123 };

    if ((sMapDisp.mapDataScene == NULL) || (sMapDisp.bossRoomStorey < 0) || (sMapDisp.bossRoomStorey >= 5) ||
        (sSceneNumRooms == 0)) {
        return 123;
    }
    return dungeonMapFloorIconPosY[sMapDisp.bossRoomStorey];
}

s16 MapDisp_GetBossRoomStorey(void) {
    return sMapDisp.bossRoomStorey;
}

// TransitionActor params test
s32 MapDisp_IsBossDoor(s32 params) {
    if (DOORSHUTTER_PARAMS_GET_TYPE((u16)params) == DOORSHUTTER_TYPE_BOSS_DOOR) {
        return true;
    }
    return false;
}

void MapDisp_InitBossRoomStorey(PlayState* play) {
    TransitionActorList* transitionActors = &sTransitionActorList;
    s32 storey;
    s32 i;

    for (i = 0; i < transitionActors->count; i++) {
        if (MapDisp_IsBossDoor(sTransitionActors[i].params)) {
            if (ABS_ALT(sTransitionActors[i].id) != ACTOR_EN_HOLL) {
                for (storey = 0; storey < sMapDisp.numStoreys; storey++) {
                    //! FAKE: needed for matching
                    s32 temp = (sMapDisp.storeyYList[storey] - 5);

                    if (((storey == sMapDisp.numStoreys - 1) &&
                         (sTransitionActors[i].pos.y >= (sMapDisp.storeyYList[storey] - 5))) ||
                        ((storey != sMapDisp.numStoreys - 1) &&
                         (sTransitionActors[i].pos.y >= (sMapDisp.storeyYList[storey] - 5)) &&
                         (sTransitionActors[i].pos.y < (sMapDisp.storeyYList[storey + 1] - 5)))) {
                        sMapDisp.bossRoomStorey = storey;
                        return;
                    }
                }
            }
        }
    }
    sMapDisp.bossRoomStorey = 0;
}

/**
 * @brief Initializes the MapData for the current scene
 *
 * @param play
 * @param segmentAddress
 */
void MapDisp_InitMapData(PlayState* play, void* segmentAddress) {
    MapDataScene* mapDataScene;
    MapDataRoom* mapDataRooms;
    s32 i;

    if (!Map_IsInBossScene(play)) {
        sSceneNumRooms = play->roomList.count;
        mapDataScene = Lib_SegmentedToVirtual(segmentAddress);
        sMapDataScene = *mapDataScene;
        mapDataRooms = Lib_SegmentedToVirtual(mapDataScene->rooms);

        for (i = 0; i < sSceneNumRooms; i++) {
            sMapDataRooms[i] = *mapDataRooms++;
        }

        sMapDataScene.rooms = sMapDataRooms;
        if (play->colCtx.colHeader != NULL) {
            sMapDisp.sceneMinX = play->colCtx.colHeader->minBounds.x;
            sMapDisp.sceneMinZ = play->colCtx.colHeader->minBounds.z;
            sMapDisp.sceneWidth = play->colCtx.colHeader->maxBounds.x - play->colCtx.colHeader->minBounds.x;
            sMapDisp.sceneHeight = play->colCtx.colHeader->maxBounds.z - play->colCtx.colHeader->minBounds.z;
            sMapDisp.sceneMidX = sMapDisp.sceneMinX + (sMapDisp.sceneWidth * 0.5f);
            sMapDisp.sceneMidZ = sMapDisp.sceneMinZ + (sMapDisp.sceneHeight * 0.5f);
        }
    }
    sMapDisp.mapDataScene = &sMapDataScene;
    MapDisp_InitSceneFloorData(play);
    MapDisp_InitBossRoomStorey(play);
}

/**
 * @brief Creates a deep copy of chest data from the scene data.
 *
 * @param play
 * @param num
 * @param segmentAddress
 * @note If a boss scene is loaded, no data is copied. This allows the scene to borrow the main dungeon scene data
 * instead.
 */
void MapDisp_InitChestData(PlayState* play, s32 num, void* segmentAddress) {
    MapDataChest* mapDataChests;
    s32 i;

    if (!Map_IsInBossScene(play)) {
        mapDataChests = Lib_SegmentedToVirtual(segmentAddress);
        for (i = 0; i < num; mapDataChests++, i++) {
            sMapDataChests[i] = *mapDataChests;
        }
        sNumChests = num;
    }
    sMapDisp.mapDataChests = sMapDataChests;
    sMapDisp.numChests = sNumChests;
}

/**
 * @brief Creates a deep copy of transition actors from the scene data.
 *
 * @param play
 * @param num number of transition actors within the list
 * @param transitionActorList pointer to the list of transition actors
 * @note If a boss scene is loaded, no data is copied. This allows the scene to borrow the main dungeon scene data
 * instead.
 */
void MapDisp_InitTransitionActorData(PlayState* play, s32 num, TransitionActorEntry* transitionActorList) {
    s32 i;

    if (!Map_IsInBossScene(play)) {
        sTransitionActorList.count = num;
        for (i = 0; i < num; i++) {
            sTransitionActors[i] = transitionActorList[i];
        }
        sTransitionActorList.list = sTransitionActors;
    }
}

void MapDisp_Destroy(PlayState* play) {
    s32 i;

    sMapDisp.mapDataScene = NULL;
    sMapDisp.curRoom = -1;
    sMapDisp.minimapCurX = 210;
    sMapDisp.minimapCurY = 140;
    sMapDisp.minimapCurTex = NULL;
    sMapDisp.prevRoom = -1;
    sMapDisp.minimapPrevTex = NULL;
    sMapDisp.minimapPrevX = 0;
    sMapDisp.minimapPrevY = 0;
    sMapDisp.unk20 = 0;
    sMapDisp.swapAnimTimer = 0;
    sMapDisp.texBuff0 = NULL;
    sMapDisp.texBuff1 = NULL;

    for (i = 0; i < sSceneNumRooms; i++) {
        MapDisp_DestroyRoomStoreyRecord(play, &sMapDisp.roomStoreyList[i]);
    }

    sMapDisp.roomStoreyList = NULL;
    sMapDisp.numStoreys = 0;
    sMapDisp.pauseMapCurStorey = 0;
    sMapDisp.bottomStorey = 0;
    sMapDisp.timer = 0;
    sMapDisp.storeyYList = NULL;
    sMapDisp.numChests = 0;
    sMapDisp.mapDataChests = NULL;
    MapDisp_DestroyMapI(play);
    sMapDisp.unk5A = 0;
}

void MapDisp_Update(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 currentX;
    s16 currentY;
    s16 targetX;
    s16 targetY;

    if ((sMapDisp.mapDataScene != NULL) && (sSceneNumRooms != 0)) {
        sMapDisp.pauseMapCurStorey = DUNGEON_FLOOR_INDEX_0 - pauseCtx->cursorMapDungeonItem;
        if (sMapDisp.prevRoom != -1) {
            if (sMapDisp.swapAnimTimer > 0) {
                targetX = sMapDisp.minimapBaseX;
                currentX = sMapDisp.minimapCurX;
                if (targetX != currentX) {
                    sMapDisp.minimapCurX =
                        TRUNCF_BINANG(((f32)(targetX - currentX) / (f32)sMapDisp.swapAnimTimer) + (f32)currentX);
                }
                targetY = sMapDisp.minimapBaseY;
                currentY = sMapDisp.minimapCurY;
                if (targetY != currentY) {
                    sMapDisp.minimapCurY =
                        TRUNCF_BINANG(((f32)(targetY - currentY) / (f32)sMapDisp.swapAnimTimer) + (f32)currentY);
                }
                sMapDisp.swapAnimTimer--;
            } else {
                sMapDisp.prevRoom = -1;
                sMapDisp.swapAnimTimer = 0;
                sMapDisp.minimapCurX = sMapDisp.minimapBaseX;
                sMapDisp.minimapCurY = sMapDisp.minimapBaseY;
            }
        } else {
            sMapDisp.swapAnimTimer = 0;
        }
    }
}

void MapDisp_SwapRooms(s16 nextRoom) {
    MapDataRoom* nextMapDataRoom;
    MapDataRoom* prevMapDataRoom;
    s32 minimapBaseX;
    s32 minimapBaseY;
    s32 width;
    s32 height;
    s32 offsetX;
    s32 offsetY;

    if ((sMapDisp.mapDataScene != NULL) && (sSceneNumRooms != 0) && (nextRoom != -1)) {
        nextMapDataRoom = &sMapDisp.mapDataScene->rooms[nextRoom];
        if ((nextMapDataRoom->mapId < MAPDATA_GAMEPLAY_DANGEON_KEEP_MAX) ||
            ((nextMapDataRoom->mapId >= MAPDATA_MAP_GRAND) && (nextMapDataRoom->mapId < MAPDATA_MAP_GRAND_MAX)) ||
            nextMapDataRoom->mapId == MAP_DATA_NO_MAP) {

            sMapDisp.prevRoom = sMapDisp.curRoom;
            sMapDisp.curRoom = nextRoom;
            sMapDisp.swapAnimTimer = 20;

            sMapDisp.minimapPrevTex = sMapDisp.minimapCurTex;
            minimapBaseX = sMapDisp.minimapBaseX;
            minimapBaseY = sMapDisp.minimapBaseY;

            nextMapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];

            if (nextMapDataRoom->mapId == MAP_DATA_NO_MAP) {
                sMapDisp.minimapPrevY = 0;
                sMapDisp.minimapBaseX = 210;
                sMapDisp.minimapBaseY = 140;
                sMapDisp.minimapCurX = 210;
                sMapDisp.minimapCurY = 140;
                sMapDisp.minimapCurTex = NULL;
                sMapDisp.minimapPrevX = sMapDisp.minimapPrevY;
                return;
            }
            MapDisp_GetMapOffset(nextMapDataRoom, &offsetX, &offsetY);
            MapDisp_GetMapTexDim(nextMapDataRoom, &width, &height);
            sMapDisp.minimapBaseX = 295 - width;
            sMapDisp.minimapBaseY = 220 - height;
            if (sMapDisp.prevRoom != -1) {
                prevMapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.prevRoom];
                if (prevMapDataRoom->mapId == MAP_DATA_NO_MAP) {
                    sMapDisp.minimapCurTex = NULL;
                    sMapDisp.minimapPrevX = sMapDisp.minimapPrevY = 0;
                    sMapDisp.minimapCurX = sMapDisp.minimapBaseX;
                    sMapDisp.minimapCurY = sMapDisp.minimapBaseY;
                    return;
                } else {
                    s32 prevOffsetX;
                    s32 prevOffsetY;
                    s32 scale;
                    s32 pad;

                    MapDisp_GetMapOffset(prevMapDataRoom, &prevOffsetX, &prevOffsetY);
                    scale = sMapDisp.mapDataScene->scale;
                    if (sMapDisp.mapDataScene->scale == 0) {
                        scale = 20;
                    } else if (sMapDisp.mapDataScene->scale == -1) {
                        s32 scaleTemp;

                        MapDisp_GetMapScale(nextMapDataRoom, &scaleTemp);
                        scale = scaleTemp;
                    }
                    sMapDisp.minimapPrevX =
                        TRUNCF_BINANG(((f32)offsetX + (((f32)prevMapDataRoom->centerX - (f32)nextMapDataRoom->centerX) *
                                                       (1.0f / scale))) -
                                      (f32)prevOffsetX);
                    sMapDisp.minimapPrevY =
                        TRUNCF_BINANG(((f32)offsetY + (((f32)prevMapDataRoom->centerZ - (f32)nextMapDataRoom->centerZ) *
                                                       (1.0f / scale))) -
                                      (f32)prevOffsetY);
                    sMapDisp.minimapCurX = minimapBaseX - sMapDisp.minimapPrevX;
                    sMapDisp.minimapCurY = minimapBaseY - sMapDisp.minimapPrevY;
                }
            } else {
                sMapDisp.minimapPrevX = sMapDisp.minimapPrevY = 0;
                sMapDisp.minimapCurX = sMapDisp.minimapBaseX;
                sMapDisp.minimapCurY = sMapDisp.minimapBaseY;
            }
            sMapDisp.minimapCurTex = NULL;

            switch (MapData_MID_GetType(nextMapDataRoom->mapId)) {
                case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
                    sMapDisp.minimapCurTex = MapData_GetMapTexGameplayDangeonKeep(nextMapDataRoom->mapId);
                    return;

                case MAPDATA_MID_MAP_GRAND_STATIC:
                    if (sMapDisp.minimapPrevTex == sMapDisp.texBuff0) {
                        sMapDisp.minimapCurTex = sMapDisp.texBuff1;
                    } else {
                        sMapDisp.minimapCurTex = sMapDisp.texBuff0;
                    }
                    if (MapData_GetSizeOfMapGrandTex(nextMapDataRoom->mapId) != 0) {
                        CmpDma_LoadFile(SEGMENT_ROM_START(map_grand_static),
                                        MAPDATA_GET_MAP_GRAND_ID_FROM_MAP_ID(nextMapDataRoom->mapId),
                                        sMapDisp.minimapCurTex, MapData_GetSizeOfMapGrandTex(nextMapDataRoom->mapId));
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void MapDisp_Minimap_DrawRedCompassIcon(PlayState* play, s32 x, s32 z, s32 rot) {
    MapDataRoom* mapDataRoom;
    s32 posX;
    s32 posY;
    s32 texOffsetX;
    s32 texOffsetY;
    s32 texWidth;
    s32 texHeight;
    s32 scale;
    f32 scaleFrac;

    mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
    if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
        return;
    }

    MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
    MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);
    scale = sMapDisp.mapDataScene->scale;

    if (sMapDisp.mapDataScene->scale == 0) {
        scale = 20;
    } else if (sMapDisp.mapDataScene->scale == -1) {
        s32 scaleTemp;

        MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
        scale = scaleTemp;
    }

    scaleFrac = 1.0f / scale;
    if (!MapDisp_IsDataRotated(play)) {
        posX = (s32)((x - (f32)mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               (sMapDisp.minimapCurX - sMapDisp.minimapBaseX) + texOffsetX;
        posY = (s32)((z - (f32)mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               (sMapDisp.minimapCurY - sMapDisp.minimapBaseY) + texOffsetY;
    } else {
        posX = -(s32)((x - (f32)mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               (sMapDisp.minimapCurX - sMapDisp.minimapBaseX) + texOffsetX;
        posY = -(s32)((z - (f32)mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               (sMapDisp.minimapCurY - sMapDisp.minimapBaseY) + texOffsetY;
    }

    if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL42_Overlay(play->state.gfxCtx);
        gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);
        Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
        Matrix_RotateXFApply(-1.6f);
        if (MapDisp_IsDataRotated(play)) {
            rot += 0x7FFF;
        }
        Matrix_RotateYF(rot / 10.0f, MTXMODE_APPLY);
        Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
        MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 255, 200, 0, 0, play->interfaceCtx.minimapAlpha);
        gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

s32 MapDisp_IsLocationRomaniRanchAltScene(PlayState* play) {
    if ((gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0)) && (Cutscene_GetSceneLayer(play) != 0)) {
        return true;
    }
    return false;
}

s32 MapDisp_CanDisplayMinimap(PlayState* play) {
    if ((!Map_CurRoomHasMapI(play) && Inventory_IsMapVisible(play->sceneId)) ||
        (Map_CurRoomHasMapI(play) && CHECK_DUNGEON_ITEM(DUNGEON_MAP, gSaveContext.mapIndex))) {
        return true;
    }
    return false;
}

s32 MapDisp_IsLocationMinimapBlocked(PlayState* play) {
    if (((play->csCtx.state != CS_STATE_IDLE) && !MapDisp_IsLocationRomaniRanchAltScene(play)) ||
        (sMapDisp.unk20 & 2) || Map_IsInBossScene(play)) {
        return true;
    }
    return false;
}

s32 MapDisp_IsMinimapToggleBlocked(PlayState* play) {
    if ((MapDisp_IsLocationMinimapBlocked(play) == true) || !MapDisp_CanDisplayMinimap(play)) {
        return true;
    }
    return false;
}

s32 MapDisp_AreRoomsSameStorey(s32 curRoom, s32 prevRoom) {
    MapDataRoom* mapDataRoom;
    s16* roomStoreyList;

    if ((curRoom == -1) || (prevRoom == -1)) {
        return false;
    }
    mapDataRoom = &sMapDisp.mapDataScene->rooms[curRoom];
    roomStoreyList = sMapDisp.roomStoreyList;
    if ((roomStoreyList[curRoom] <= roomStoreyList[prevRoom]) &&
        (roomStoreyList[prevRoom] <= (roomStoreyList[curRoom] + MAP_DATA_ROOM_GET_EXTRA_STOREYS(mapDataRoom)))) {
        return true;
    }
    mapDataRoom = &sMapDisp.mapDataScene->rooms[prevRoom];
    if ((roomStoreyList[prevRoom] <= roomStoreyList[curRoom]) &&
        (roomStoreyList[curRoom] <= (roomStoreyList[prevRoom] + MAP_DATA_ROOM_GET_EXTRA_STOREYS(mapDataRoom)))) {
        return true;
    }
    return false;
}

void MapDisp_DrawMinimap(PlayState* play, s32 playerInitX, s32 playerInitZ, s32 playerInitDir) {
    PauseContext* pauseCtx = &play->pauseCtx;

    if ((sMapDisp.mapDataScene != NULL) && ((s32)pauseCtx->state <= PAUSE_STATE_OPENING_2) && !R_MINIMAP_DISABLED &&
        (play->interfaceCtx.minimapAlpha != 0)) {
        if (!MapDisp_IsLocationMinimapBlocked(play) && (sSceneNumRooms != 0)) {
            if (MapDisp_CanDisplayMinimap(play)) {
                MapDisp_DrawMinimapRoom(play, sMapDisp.minimapCurTex, sMapDisp.minimapCurX, sMapDisp.minimapCurY,
                                        sMapDisp.curRoom, 1.0f - (sMapDisp.swapAnimTimer * 0.05f));
                if ((sMapDisp.curRoom != sMapDisp.prevRoom) &&
                    MapDisp_AreRoomsSameStorey(sMapDisp.curRoom, sMapDisp.prevRoom)) {
                    MapDisp_DrawMinimapRoom(play, sMapDisp.minimapPrevTex, sMapDisp.minimapCurX + sMapDisp.minimapPrevX,
                                            sMapDisp.minimapCurY + sMapDisp.minimapPrevY, sMapDisp.prevRoom,
                                            sMapDisp.swapAnimTimer * 0.05f);
                }
                MapDisp_Minimap_DrawDoorActors(play);
            }
            if ((!Map_CurRoomHasMapI(play) || CHECK_DUNGEON_ITEM(DUNGEON_COMPASS, gSaveContext.mapIndex)) &&
                (Map_CurRoomHasMapI(play) || Inventory_IsMapVisible(play->sceneId))) {
                if (play->interfaceCtx.minigameState == MINIGAME_STATE_NONE) {
                    MapDisp_Minimap_DrawRedCompassIcon(play, playerInitX, playerInitZ, playerInitDir);
                }
                MapDisp_Minimap_DrawActors(play);
            }
        }
    }
}

void MapDisp_ResetMapI(void) {
    s32 i;

    sPauseDungeonMap.textureCount = 0;
    for (i = 0; i < ROOM_MAX; i++) {
        sPauseDungeonMap.mapI_mapCompactId[i] = 0;
        sPauseDungeonMap.mapI_roomTextures[i] = NULL;
        sPauseDungeonMap.roomSprite[i] = NULL;
    }

    sPauseDungeonMap.animTimer = 0;
    sMapDisp.unk20 &= ~1;
}

void MapDisp_InitMapI(PlayState* play) {
    MapDisp_ResetMapI();
}

void MapDisp_DestroyMapI(PlayState* play) {
    MapDisp_ResetMapI();
}

// alloc pause screen dungeon map
void* MapDisp_AllocDungeonMap(PlayState* play, void* heap) {
    void* heapNext;
    s32 dungeonMapRoomIter;
    s32 sceneRoomIter;

    heapNext = heap;
    if ((sMapDisp.mapDataScene == NULL) || (sSceneNumRooms == 0)) {
        return heapNext;
    }
    sPauseDungeonMap.textureCount = 0;

    // loop for number of rooms
    for (sceneRoomIter = 0; sceneRoomIter < sSceneNumRooms; sceneRoomIter++) {
        s32 mapCompactId;
        MapDataRoom* mapDataRoom = &sMapDisp.mapDataScene->rooms[sceneRoomIter];
        s32 isDuplicateTexture = false;

        if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
            continue;
        }
        mapCompactId = MapData_GetMapCompactId(mapDataRoom->mapId);
        if (mapCompactId == -1) {
            continue;
        }
        // test if the texture reference already exists
        for (dungeonMapRoomIter = 0; dungeonMapRoomIter < sPauseDungeonMap.textureCount; dungeonMapRoomIter++) {
            if (mapCompactId == sPauseDungeonMap.mapI_mapCompactId[dungeonMapRoomIter]) {
                isDuplicateTexture = true;
                break;
            }
        }
        if (isDuplicateTexture == false) {
            sPauseDungeonMap.mapI_mapCompactId[sPauseDungeonMap.textureCount] = mapCompactId;
            sPauseDungeonMap.textureCount++;
        }
    }

    // fetch all textures from rom
    sPauseDungeonMap.mapI_roomTextures[0] = heap;
    for (dungeonMapRoomIter = 0; dungeonMapRoomIter < sPauseDungeonMap.textureCount; dungeonMapRoomIter++) {
        s32 mapCompactId = sPauseDungeonMap.mapI_mapCompactId[dungeonMapRoomIter];

        MapDisp_GetMapITexture(sPauseDungeonMap.mapI_roomTextures[dungeonMapRoomIter], mapCompactId);
        if (dungeonMapRoomIter + 1 < sPauseDungeonMap.textureCount) {
            sPauseDungeonMap.mapI_roomTextures[dungeonMapRoomIter + 1] =
                (void*)ALIGN16((uintptr_t)sPauseDungeonMap.mapI_roomTextures[dungeonMapRoomIter] +
                               MapData_CPID_GetSizeOfMapTex(mapCompactId));
        } else {
            heapNext = (void*)((uintptr_t)sPauseDungeonMap.mapI_roomTextures[dungeonMapRoomIter] +
                               MapData_CPID_GetSizeOfMapTex(mapCompactId));
        }
    }

    for (sceneRoomIter = 0; sceneRoomIter < sSceneNumRooms; sceneRoomIter++) {
        MapDataRoom* mapDataRoom = &sMapDisp.mapDataScene->rooms[sceneRoomIter];
        s32 foundTexture = false;
        s32 mapCompactId;

        if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
            sPauseDungeonMap.roomSprite[sceneRoomIter] = NULL;
        } else {
            mapCompactId = MapData_GetMapCompactId(mapDataRoom->mapId);
            for (dungeonMapRoomIter = 0; dungeonMapRoomIter < sPauseDungeonMap.textureCount; dungeonMapRoomIter++) {
                if (mapCompactId == sPauseDungeonMap.mapI_mapCompactId[dungeonMapRoomIter]) {
                    foundTexture = true;
                    break;
                }
            }
            if (!foundTexture) {
                sPauseDungeonMap.roomSprite[sceneRoomIter] = NULL;
            } else {
                void* dummy = sPauseDungeonMap.mapI_roomTextures[dungeonMapRoomIter]; //! FAKE:

                sPauseDungeonMap.roomSprite[sceneRoomIter] = sPauseDungeonMap.mapI_roomTextures[dungeonMapRoomIter];
            }
        }
    }
    return heapNext;
}

s32 MapDisp_IsOnStorey(s32 storey, f32 checkY) {
    if (storey == 0) {
        if ((sMapDisp.storeyYList[0] <= checkY) && ((sMapDisp.numStoreys == 1) || (checkY < sMapDisp.storeyYList[1]))) {
            return true;
        }
    } else if (storey >= (sMapDisp.numStoreys - 1)) {
        if (sMapDisp.storeyYList[sMapDisp.numStoreys - 1] <= checkY) {
            return true;
        }
    } else if ((sMapDisp.storeyYList[storey] <= checkY) && (checkY < sMapDisp.storeyYList[storey + 1])) {
        return true;
    }
    return false;
}

s32 MapDisp_ConvertBossSceneToDungeonScene(s32 sceneId) {
    switch (sceneId) {
        case SCENE_MITURIN_BS:
            return SCENE_MITURIN;

        case SCENE_HAKUGIN_BS:
            return SCENE_HAKUGIN;

        case SCENE_SEA_BS:
            return SCENE_SEA;

        case SCENE_INISIE_BS:
            return SCENE_INISIE_N;

        default:
            return sceneId;
    }
}

/**
 * @brief Draws the dungeon room sprites for the pause menu dungeon map
 *
 * @param play
 * @param viewX top left x position of the dungeon map view window
 * @param viewY top left y posiiton of the dungeon map view window
 * @param viewWidth width in pixels of the dungeon map view window
 * @param viewHeight height in pixels of the dungeon map view window
 * @param scaleFrac ratio to convert world space coordinates to map coordinates
 * @param dungeonSceneSharedIndex enum DungeonSceneIndex for retrieving map/compass data
 */
void MapDisp_DrawRooms(PlayState* play, s32 viewX, s32 viewY, s32 viewWidth, s32 viewHeight, f32 scaleFrac,
                       s32 dungeonSceneSharedIndex) {
    static u16 sUnvisitedRoomPal[16] = {
        0x0000, 0x0000, 0xFFC1, 0x07C1, 0x07FF, 0x003F, 0xFB3F, 0xF305,
        0x0453, 0x0577, 0x0095, 0x82E5, 0xFD27, 0x7A49, 0x94A5, 0x0001,
    }; // palette 0
    static u16 sVisitedRoomPal[16] = {
        0x0000, 0x027F, 0xFFC1, 0x07C1, 0x07FF, 0x003F, 0xFB3F, 0xF305,
        0x0453, 0x0577, 0x0095, 0x82E5, 0xFD27, 0x7A49, 0x94A5, 0x0001,
    }; // palette 1
    static u16 sCurrentRoomPal[16] = {
        0x0000, 0x0623, 0xFFC1, 0x07C1, 0x07FF, 0x003F, 0xFB3F, 0xF305,
        0x0453, 0x0577, 0x0095, 0x82E5, 0xFD27, 0x7A49, 0x94A5, 0x0001,
    }; // palette 2
    PauseContext* pauseCtx = &play->pauseCtx;
    s32 pad[4];
    s32 i;
    s32 green = ((sPauseDungeonMap.animTimer * -120.0f / 40.0f) + 200.0f) * 31.0f / 255.0f;
    s32 blue = ((sPauseDungeonMap.animTimer * 115.0f / 40.0f) + 140.0f) * 31.0f / 255.0f;

    sCurrentRoomPal[1] = (green << 6) | (blue << 1) | 1;

    if (CHECK_DUNGEON_ITEM(DUNGEON_MAP, dungeonSceneSharedIndex)) {
        s32 requiredScopeTemp;

        sUnvisitedRoomPal[15] = 0xAD5F;
        sVisitedRoomPal[15] = 0xAD5F;
        sCurrentRoomPal[15] = 0xAD5F;
    } else {
        sCurrentRoomPal[15] = sVisitedRoomPal[15] = sUnvisitedRoomPal[15] = 0;
    }

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL39_Opa(play->state.gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 0, sUnvisitedRoomPal);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 1, sVisitedRoomPal);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 2, sCurrentRoomPal);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);

    for (i = 0; i < sSceneNumRooms; i++) {
        s32 texWidth;
        s32 texHeight;
        s32 offsetX;
        s32 offsetY;
        MapDataRoom* mapDataRoom;
        TexturePtr roomTexture;
        s32 s;
        s32 t;
        s32 dsdx;
        s32 dtdy;
        s32 texPosX;
        s32 texPosY;
        s32 spE8;
        s32 two = 2;

        mapDataRoom = &sMapDisp.mapDataScene->rooms[i];
        if ((mapDataRoom->mapId == MAP_DATA_NO_MAP) || (mapDataRoom->mapId >= MAPDATA_MAP_GRAND_MAX)) {
            continue;
        }

        if ((sMapDisp.pauseMapCurStorey < sMapDisp.roomStoreyList[i]) ||
            ((sMapDisp.roomStoreyList[i] + MAP_DATA_ROOM_GET_EXTRA_STOREYS(mapDataRoom)) <
             sMapDisp.pauseMapCurStorey)) {
            continue;
        }

        roomTexture = sPauseDungeonMap.roomSprite[i];
        if (roomTexture == NULL) {
            continue;
        }

        spE8 = MapData_GetMapCompactId(mapDataRoom->mapId);
        if (spE8 == -1) {
            continue;
        }

        MapData_CPID_GetTexDim(spE8, &texWidth, &texHeight);
        MapData_CPID_GetTexOffset(spE8, &offsetX, &offsetY);

        if (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_X) {
            offsetX = ((texWidth / 2) - offsetX) + (texWidth / 2);
            s = (texWidth - 1) << 5;
            dsdx = 0xFC00;
        } else {
            s = 0;
            dsdx = 0x400;
        }

        if (mapDataRoom->flags & MAP_DATA_ROOM_FLIP_Y) {
            s32 requiredScopeTemp;

            offsetY = ((texHeight / 2) - offsetY) + (texHeight / 2);
            t = (texHeight - 1) << 5;
            dtdy = 0xFC00;
        } else {
            t = 0;
            dtdy = 0x400;
        }

        texPosX =
            ((mapDataRoom->centerX - (f32)sMapDisp.sceneMidX) * scaleFrac - offsetX) + ((viewWidth / two) + viewX);
        texPosY =
            ((mapDataRoom->centerZ - (f32)sMapDisp.sceneMidZ) * scaleFrac - offsetY) + ((viewHeight / two) + viewY);

        if (i == play->roomCtx.curRoom.num) {
            if (Map_IsInBossScene(play)) {
                gDPLoadTextureBlock_4b(POLY_OPA_DISP++, roomTexture, G_IM_FMT_CI, texWidth, texHeight, 1,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureBlock_4b(POLY_OPA_DISP++, roomTexture, G_IM_FMT_CI, texWidth, texHeight, 2,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            }
        } else if (GET_ROOM_VISITED(Play_GetOriginalSceneId(MapDisp_ConvertBossSceneToDungeonScene(play->sceneId)),
                                    i)) {
            gDPLoadTextureBlock_4b(POLY_OPA_DISP++, roomTexture, G_IM_FMT_CI, texWidth, texHeight, 1,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
        } else if (CHECK_DUNGEON_ITEM(DUNGEON_MAP, dungeonSceneSharedIndex)) {
            gDPLoadTextureBlock_4b(POLY_OPA_DISP++, roomTexture, G_IM_FMT_CI, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
        } else {
            continue;
        }
        gSPTextureRectangle(POLY_OPA_DISP++, (texPosX << 2), (texPosY << 2), (texPosX + texWidth) << 2,
                            (texPosY + texHeight) << 2, 0, s, t, dsdx, dtdy);
        gDPPipeSync(POLY_OPA_DISP++);
    }

    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * @brief Draws the chests for the pause menu dungeon map
 *
 * @param play
 * @param viewX top left x position of the dungeon map view window
 * @param viewY top left y posiiton of the dungeon map view window
 * @param viewWidth width in pixels of the dungeon map view window
 * @param viewHeight height in pixels of the dungeon map view window
 * @param scaleFrac ratio to convert world space coordinates to map coordinates
 * @param dungeonSceneSharedIndex enum DungeonSceneIndex for retrieving map/compass data
 */
void MapDisp_DrawChests(PlayState* play, s32 viewX, s32 viewY, s32 viewWidth, s32 viewHeight, f32 scaleFrac) {
    s32 pad[23];
    MapDataChest* mapDataChests = sMapDisp.mapDataChests;
    s32 room;
    MapDataRoom* mapDataRoom;
    s32 texPosX;
    s32 texPosY;
    s32 i;
    s32 isChestOpen;
    s32 offsetX = 4;
    s32 offsetZ = 4;

    if (mapDataChests == NULL) {
        return;
    }

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, play->pauseCtx.alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gDPPipeSync(POLY_OPA_DISP++);

    gDPLoadTextureBlock_Runtime(POLY_OPA_DISP++, gMapChestIconTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

    for (i = 0; i < sMapDisp.numChests; i++) {
        room = mapDataChests[i].room;
        mapDataRoom = &sMapDisp.mapDataScene->rooms[room];

        switch (play->sceneId) {
            case SCENE_MITURIN_BS:
                isChestOpen = GET_CYCLE_CHEST_OPENED(SCENE_MITURIN, mapDataChests[i].chestFlagId);
                break;

            case SCENE_HAKUGIN_BS:
                isChestOpen = GET_CYCLE_CHEST_OPENED(SCENE_HAKUGIN, mapDataChests[i].chestFlagId);
                break;

            case SCENE_SEA_BS:
                isChestOpen = GET_CYCLE_CHEST_OPENED(SCENE_SEA, mapDataChests[i].chestFlagId);
                break;

            case SCENE_INISIE_BS:
                isChestOpen = GET_CYCLE_CHEST_OPENED(SCENE_INISIE_N, mapDataChests[i].chestFlagId);
                break;

            default:
                isChestOpen = Flags_GetTreasure(play, mapDataChests[i].chestFlagId);
                break;
        }

        if ((sMapDisp.pauseMapCurStorey < sMapDisp.roomStoreyList[room]) ||
            ((sMapDisp.roomStoreyList[room] + MAP_DATA_ROOM_GET_EXTRA_STOREYS(mapDataRoom)) <
             sMapDisp.pauseMapCurStorey) ||
            (isChestOpen != 0)) {
            continue;
        }

        if (!MapDisp_IsOnStorey((s32)sMapDisp.pauseMapCurStorey, (f32)mapDataChests[i].y)) {
            continue;
        }

        texPosX =
            (s32)((((mapDataChests[i].x - (f32)sMapDisp.sceneMidX) * scaleFrac) - offsetX) + ((viewWidth / 2) + viewX));
        texPosY = (s32)((((mapDataChests[i].z - (f32)sMapDisp.sceneMidZ) * scaleFrac) - offsetZ) +
                        ((viewHeight / 2) + viewY));

        gSPTextureRectangle(POLY_OPA_DISP++, texPosX << 2, texPosY << 2, (texPosX + 8) << 2, (texPosY + 8) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * @brief Draws the room exit points for the pause menu dungeon map
 *
 * @param play
 * @param viewX top left x position of the dungeon map view window
 * @param viewY top left y posiiton of the dungeon map view window
 * @param viewWidth width in pixels of the dungeon map view window
 * @param viewHeight height in pixels of the dungeon map view window
 * @param scaleFrac ratio to convert world space coordinates to map coordinates
 * @param dungeonSceneSharedIndex enum DungeonSceneIndex for retrieving map/compass data
 */
void MapDisp_DrawRoomExits(PlayState* play, s32 viewX, s32 viewY, s32 viewWidth, s32 viewHeight, f32 scaleFrac,
                           s32 dungeonSceneSharedIndex) {
    PauseContext* pauseCtx = &play->pauseCtx;
    TransitionActorList* transitionActors = &sTransitionActorList;
    s32 texPosX;
    s32 texPosY;
    s32 i;
    s8 roomA;
    s8 roomB;

    if (transitionActors->count != 0) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, &sWhiteSquareTex, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        for (i = 0; i < transitionActors->count; i++) {
            if (MapDisp_IsOnStorey(sMapDisp.pauseMapCurStorey, sTransitionActors[i].pos.y)) {
                if ((ABS_ALT(sTransitionActors[i].id) != ACTOR_EN_HOLL) &&
                    !MapDisp_IsBossDoor(sTransitionActors[i].params)) {
                    roomA = sTransitionActors[i].sides[0].room;
                    roomB = sTransitionActors[i].sides[1].room;
                    if (CHECK_DUNGEON_ITEM(DUNGEON_MAP, gSaveContext.mapIndex) || (roomA < 0) ||
                        GET_ROOM_VISITED(Play_GetOriginalSceneId(MapDisp_ConvertBossSceneToDungeonScene(play->sceneId)),
                                         roomA) ||
                        (roomB < 0) ||
                        GET_ROOM_VISITED(Play_GetOriginalSceneId(MapDisp_ConvertBossSceneToDungeonScene(play->sceneId)),
                                         roomB)) {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

                        texPosX = ((f32)sTransitionActors[i].pos.x - sMapDisp.sceneMidX) * scaleFrac +
                                  ((viewWidth / 2) + viewX);
                        texPosY = ((f32)sTransitionActors[i].pos.z - sMapDisp.sceneMidZ) * scaleFrac +
                                  ((viewHeight / 2) + viewY);
                        gSPTextureRectangle(POLY_OPA_DISP++, ((texPosX - 1) << 2), ((texPosY - 1) << 2),
                                            ((texPosX + 1) << 2), ((texPosY + 1) << 2), G_TX_RENDERTILE, 0, 0, 1 << 10,
                                            1 << 10);
                    }
                }
            }
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

/**
 * @brief Draws the boss room icon for the pause menu dungeon map.
 *
 * @param play
 * @param viewX top left x position of the dungeon map view window
 * @param viewY top left y posiiton of the dungeon map view window
 * @param viewWidth width in pixels of the dungeon map view window
 * @param viewHeight height in pixels of the dungeon map view window
 * @param scaleFrac ratio to convert world space coordinates to map coordinates
 * @param dungeonSceneSharedIndex enum DungeonSceneIndex for retrieving map/compass data
 */
void MapDisp_DrawBossIcon(PlayState* play, s32 viewX, s32 viewY, s32 viewWidth, s32 viewHeight, f32 scaleFrac,
                          s32 dungeonSceneSharedIndex) {
    s32 i;
    TransitionActorList* transitionActorList = &sTransitionActorList;
    s32 offsetX = 4;
    s32 offsetZ = 4;
    s32 texPosX;
    s32 texPosY;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, play->pauseCtx.alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gDPPipeSync(POLY_OPA_DISP++);

    if (CHECK_DUNGEON_ITEM(DUNGEON_COMPASS, dungeonSceneSharedIndex)) {
        gDPLoadTextureBlock_Runtime(POLY_OPA_DISP++, gMapBossIconTex, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);

        for (i = 0; i < transitionActorList->count; i++) {
            if (!MapDisp_IsBossDoor(sTransitionActors[i].params)) {
                continue;
            }
            if (!MapDisp_IsOnStorey(sMapDisp.pauseMapCurStorey, sTransitionActors[i].pos.y)) {
                continue;
            }
            if (ABS_ALT(sTransitionActors[i].id) == ACTOR_EN_HOLL) {
                continue;
            }

            texPosX = ((((f32)sTransitionActors[i].pos.x - sMapDisp.sceneMidX) * scaleFrac) - offsetX) +
                      ((viewWidth / 2) + viewX);
            texPosY = ((((f32)sTransitionActors[i].pos.z - sMapDisp.sceneMidZ) * scaleFrac) - offsetZ) +
                      ((viewHeight / 2) + viewY);
            gSPTextureRectangle(POLY_OPA_DISP++, texPosX << 2, texPosY << 2, (texPosX + 8) << 2, (texPosY + 8) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

TexturePtr MapDisp_GetDungeonMapFloorTexture(s32 floorNumber) {
    static TexturePtr sDungeonMapFloorTextures[] = {
        gDungeonMap1FButtonTex, gDungeonMap2FButtonTex, gDungeonMap3FButtonTex, gDungeonMap4FButtonTex,
        gDungeonMap5FButtonTex, gDungeonMap6FButtonTex, gDungeonMap7FButtonTex, gDungeonMap8FButtonTex,
        gDungeonMapB1ButtonTex, gDungeonMapB2ButtonTex, gDungeonMapB3ButtonTex, gDungeonMapB4ButtonTex,
        gDungeonMapB5ButtonTex, gDungeonMapB6ButtonTex, gDungeonMapB7ButtonTex, gDungeonMapB8ButtonTex,
    };
    if ((floorNumber >= 0) && (floorNumber < 8)) {
        return sDungeonMapFloorTextures[floorNumber];
    }
    if ((floorNumber >= -8) && (floorNumber < 0)) {
        return sDungeonMapFloorTextures[7 + -floorNumber];
    }
    return gDungeonMapBlankFloorButtonTex;
}

/**
 * @brief Tests if the dungeon map on the Map screen should be drawn.
 *
 * @param play
 * @return true if the map should be drawn, else false.
 */
s32 MapDisp_SkipDrawDungeonMap(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    if (pauseCtx->pageIndex != PAUSE_MAP) {
        return true;
    }
    if ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) || IS_PAUSE_STATE_GAMEOVER(pauseCtx)) {
        return true;
    }
    if ((pauseCtx->state != PAUSE_STATE_MAIN) || (pauseCtx->mainState != PAUSE_MAIN_STATE_IDLE)) {
        return true;
    }
    if (pauseCtx->alpha == 0) {
        return true;
    }
    return false;
}

void MapDisp_DrawDungeonFloorSelect(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s32 texULY;
    s32 texLRY;
    s16 texULX;
    s16 texLRX;
    s32 pad;
    s32 storey;
    s32 dungeonSceneSharedIndex = 0;

    if ((sMapDisp.mapDataScene != NULL) && (sSceneNumRooms != 0) && !MapDisp_SkipDrawDungeonMap(play)) {
        if (Map_IsInBossScene(play)) {
            switch (play->sceneId) {
                case SCENE_MITURIN_BS:
                    dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_WOODFALL_TEMPLE;
                    break;

                case SCENE_HAKUGIN_BS:
                    dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_SNOWHEAD_TEMPLE;
                    break;

                case SCENE_SEA_BS:
                    dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_GREAT_BAY_TEMPLE;
                    break;

                case SCENE_INISIE_BS:
                    dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_STONE_TOWER_TEMPLE;
                    break;

                default:
                    break;
            }
        } else {
            dungeonSceneSharedIndex = gSaveContext.mapIndex;
        }
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL39_Opa(play->state.gfxCtx);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 200, pauseCtx->alpha);

        // Draw unlocked storeys
        for (storey = 0; storey < sMapDisp.numStoreys; storey++) {
            if (GET_DUNGEON_FLOOR_VISITED(
                    Play_GetOriginalSceneId(MapDisp_ConvertBossSceneToDungeonScene(play->sceneId)), 4 - storey) ||
                CHECK_DUNGEON_ITEM_ALT(DUNGEON_MAP, dungeonSceneSharedIndex)) {
                gDPLoadTextureBlock(POLY_OPA_DISP++, MapDisp_GetDungeonMapFloorTexture(sMapDisp.bottomStorey + storey),
                                    G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(POLY_OPA_DISP++, 81 << 2, (125 - storey * 15) << 2, 105 << 2,
                                    ((125 - storey * 15) + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }
        gDPPipeSync(POLY_OPA_DISP++);

        // Draw currently selected storey
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 150, 255, pauseCtx->alpha);
        gDPLoadTextureBlock(
            POLY_OPA_DISP++,
            MapDisp_GetDungeonMapFloorTexture((sMapDisp.bottomStorey - pauseCtx->cursorMapDungeonItem) + 8),
            G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        texULX = 80;
        texLRX = 106;
        texULY = (5 + (pauseCtx->cursorMapDungeonItem * 0xF));
        texLRY = texULY + 16;
        if ((pauseCtx->cursorSpecialPos == 0) && (pauseCtx->cursorXIndex[1] == 0)) {
            texLRX++;
            texULX--;
            texLRY += 4;
            texULY -= 4;
            gSPTextureRectangle(POLY_OPA_DISP++, texULX << 2, texULY << 2, texLRX << 2, (texLRY) << 2, G_TX_RENDERTILE,
                                0, 0, 0x036E, 0x02AA);
        } else {
            gSPTextureRectangle(POLY_OPA_DISP++, (texULX + 1) << 2, texULY << 2, (texLRX - 1) << 2, texLRY << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        Gfx_SetupDL42_Opa(play->state.gfxCtx);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

s32 MapDisp_IsValidStorey(s32 storey) {
    if ((sMapDisp.mapDataScene == NULL) || (sSceneNumRooms == 0)) {
        return false;
    }
    if ((storey < 0) || (storey > 5)) {
        return false;
    }
    if (sMapDisp.storeyYList[storey] != FLOOR_MIN_Y) {
        return true;
    }
    return false;
}

s32 MapDisp_GetPlayerStorey(s16 checkY) {
    s32 i;

    if ((sMapDisp.mapDataScene == NULL) || (sSceneNumRooms == 0)) {
        return -1;
    }
    if (sMapDisp.numStoreys <= 1) {
        return 0;
    }
    if ((sMapDisp.storeyYList[1] - 5) >= checkY) {
        return 0;
    }
    for (i = 1; i < sMapDisp.numStoreys; i++) {
        if (((sMapDisp.storeyYList[i] - 5) < checkY) && ((sMapDisp.storeyYList[i + 1] - 5) >= checkY)) {
            return i;
        }
    }
    return sMapDisp.numStoreys - 1;
}

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x4 */ s32 offsetX;
    /* 0x8 */ s32 offsetY;
} MapCustomPosOffset; // size = 0xC

/**
 * Draws the dungeon map within the pause menu's Map screen.
 *
 * @param play
 */
void MapDisp_DrawDungeonMap(PlayState* play) {
    static MapCustomPosOffset sCustomMapOffset[] = {
        { SCENE_MITURIN, 0, -10 },
        { SCENE_MITURIN_BS, 0, -10 },
    };
    MapDataRoom* mapDataRoom;
    f32 scaleFrac;
    s32 scale;
    s32 var_v0;
    s32 dungeonSceneSharedIndex = 0;
    s32 offsetX = 0;
    s32 offsetY = 0;

    if (MapDisp_SkipDrawDungeonMap(play)) {
        return;
    }

    if (Map_IsInBossScene(play)) {
        switch (play->sceneId) {
            case SCENE_MITURIN_BS:
                dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_WOODFALL_TEMPLE;
                break;

            case SCENE_HAKUGIN_BS:
                dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_SNOWHEAD_TEMPLE;
                break;

            case SCENE_SEA_BS:
                dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_GREAT_BAY_TEMPLE;
                break;

            case SCENE_INISIE_BS:
                dungeonSceneSharedIndex = DUNGEON_SCENE_INDEX_STONE_TOWER_TEMPLE;
                break;

            default:
                break;
        }
    } else {
        dungeonSceneSharedIndex = gSaveContext.mapIndex;
    }

    mapDataRoom = sMapDisp.mapDataScene->rooms;
    if ((mapDataRoom->mapId == MAP_DATA_NO_MAP) || (mapDataRoom->mapId >= MAPDATA_MAP_GRAND_MAX)) {
        return;
    }

    var_v0 = MapData_GetMapCompactId(mapDataRoom->mapId);
    if (var_v0 == -1) {
        return;
    }

    scale = MapData_CPID_GetMapScale(var_v0);
    if (scale == 0) {
        scale = 80;
    }

    for (var_v0 = 0; var_v0 < ARRAY_COUNT(sCustomMapOffset); var_v0++) {
        if (play->sceneId == sCustomMapOffset[var_v0].sceneId) {
            offsetX = sCustomMapOffset[var_v0].offsetX;
            offsetY = sCustomMapOffset[var_v0].offsetY;
        }
    }

    scaleFrac = 1.0f / scale;

    MapDisp_DrawRooms(play, offsetX + 144, offsetY + 85, 120, 100, scaleFrac, dungeonSceneSharedIndex);
    MapDisp_DrawRoomExits(play, offsetX + 144, offsetY + 85, 120, 100, scaleFrac, dungeonSceneSharedIndex);
    MapDisp_DrawBossIcon(play, offsetX + 144, offsetY + 85, 120, 100, scaleFrac, dungeonSceneSharedIndex);

    if (CHECK_DUNGEON_ITEM(DUNGEON_COMPASS, dungeonSceneSharedIndex)) {
        MapDisp_DrawChests(play, offsetX + 144, offsetY + 85, 120, 100, scaleFrac);
    }
}

void MapDisp_UpdateDungeonMap(PlayState* play) {
    sMapDisp.timer++;
    if (!(sMapDisp.unk20 & 1)) {
        sPauseDungeonMap.animTimer++;
        if (sPauseDungeonMap.animTimer > 40) {
            sMapDisp.unk20 |= 1;
        }
    } else {
        sPauseDungeonMap.animTimer--;
        if (sPauseDungeonMap.animTimer < 0) {
            sMapDisp.unk20 &= ~1;
        }
    }
}
