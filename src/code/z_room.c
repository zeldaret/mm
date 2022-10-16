#include "global.h"

static Vec3f sZeroVec = { 0.0f, 0.0f, 0.0f };

void (*sRoomDrawHandlers[])(PlayState* play, Room* room, u32 flags) = {
    Room_DrawNormal,   // ROOM_SHAPE_TYPE_NORMAL
    Room_DrawImage,    // ROOM_SHAPE_TYPE_IMAGE
    Room_DrawCullable, // ROOM_SHAPE_TYPE_CULLABLE
    Room_DrawNone,     // ROOM_SHAPE_TYPE_NONE
};

void Room_Update(PlayState* play, Room* room, Input* input, s32 arg3) {
}

void Room_DrawNone(PlayState* play, Room* room, u32 flags) {
}

void Room_DrawNormal(PlayState* play, Room* room, u32 flags) {
    RoomShapeNormal* roomShape;
    RoomShapeDListsEntry* entry;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    if (flags & ROOM_DRAW_OPA) {
        func_800BCBF4(&sZeroVec, play);
        gSPSegment(POLY_OPA_DISP++, 0x03, room->segment);
        func_8012C268(play);
        gSPMatrix(POLY_OPA_DISP++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & ROOM_DRAW_XLU) {
        func_800BCC68(&sZeroVec, play);
        gSPSegment(POLY_XLU_DISP++, 0x03, room->segment);
        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    roomShape = &room->roomShape->normal;
    entry = Lib_SegmentedToVirtual(roomShape->entries);
    for (i = 0; i < roomShape->numEntries; i++) {
        if ((flags & ROOM_DRAW_OPA) && (entry->opa != NULL)) {
            gSPDisplayList(POLY_OPA_DISP++, entry->opa);
        }

        if ((flags & ROOM_DRAW_XLU) && (entry->xlu != NULL)) {
            gSPDisplayList(POLY_XLU_DISP++, entry->xlu);
        }

        entry++;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

typedef enum {
    /* 0 */ ROOM_CULL_DEBUG_MODE_OFF,
    /* 1 */ ROOM_CULL_DEBUG_MODE_UP_TO_TARGET,
    /* 2 */ ROOM_CULL_DEBUG_MODE_ONLY_TARGET
} RoomCullableDebugMode;

typedef struct RoomShapeCullableEntryLinked {
    /* 0x00 */ RoomShapeCullableEntry* entry;
    /* 0x04 */ f32 boundsNearZ;
    /* 0x08 */ struct RoomShapeCullableEntryLinked* prev;
    /* 0x0C */ struct RoomShapeCullableEntryLinked* next;
} RoomShapeCullableEntryLinked; // size = 0x10

#ifdef NON_EQUIVALENT
// Still a WIP, started with OoT function but lots has changed
// Currently piecing together the new parts in MM
void Room_DrawCullable(PlayState* play, Room* room, u32 flags) {
    RoomShapeCullable* roomShape;
    RoomShapeCullableEntry* roomShapeCullableEntry;
    RoomShapeCullableEntryLinked linkedEntriesBuffer[ROOM_SHAPE_CULLABLE_MAX_ENTRIES];
    RoomShapeCullableEntryLinked* head = NULL;
    RoomShapeCullableEntryLinked* tail = NULL;
    RoomShapeCullableEntryLinked* iter;
    s32 pad;
    RoomShapeCullableEntryLinked* insert;
    s32 j;
    s32 i;
    Vec3f pos;
    Vec3f projectedPos;
    f32 projectedW;
    s32 pad2;
    RoomShapeCullableEntry* roomShapeCullableEntries;
    RoomShapeCullableEntry* roomShapeCullableEntryIter;
    f32 entryBoundsNearZ;

    OPEN_DISPS(play->state.gfxCtx);

    if (flags & ROOM_DRAW_OPA) {
        func_800BCBF4(&sZeroVec, play);
        gSPSegment(POLY_OPA_DISP++, 0x03, room->segment);
        if (play->roomCtx.unk74 != NULL) {
            gSPSegment(POLY_OPA_DISP++, 0x06, play->roomCtx.unk74);
        }
        func_8012C268(play);
        gSPMatrix(POLY_OPA_DISP++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (1) {}

    if (flags & ROOM_DRAW_XLU) {
        func_800BCC68(&sZeroVec, play);
        gSPSegment(POLY_XLU_DISP++, 0x03, room->segment);
        if (play->roomCtx.unk74 != NULL) {
            gSPSegment(POLY_XLU_DISP++, 0x06, play->roomCtx.unk74);
        }
        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if ((room->enablePosLights != 0) || (MREG(93) != 0)) {
        gSPSetGeometryMode(POLY_OPA_DISP++, 0x00400000);
        gSPSetGeometryMode(POLY_XLU_DISP++, 0x00400000);
    }

    roomShape = &room->roomShape->cullable;
    roomShapeCullableEntry = Lib_SegmentedToVirtual(roomShape->entries);
    insert = linkedEntriesBuffer;

    roomShapeCullableEntries = roomShapeCullableEntry;

    if (play->roomCtx.unk78 < 0) {
        for (i = 0; i < roomShape->numEntries; i++, roomShapeCullableEntry++) {
            Gfx* displayList;
            if (R_ROOM_CULL_DEBUG_MODE != 0) {
                if (((R_ROOM_CULL_DEBUG_MODE == ROOM_CULL_DEBUG_MODE_UP_TO_TARGET) &&
                     (i <= R_ROOM_CULL_DEBUG_TARGET)) ||
                    ((R_ROOM_CULL_DEBUG_MODE == ROOM_CULL_DEBUG_MODE_ONLY_TARGET) && (i == R_ROOM_CULL_DEBUG_TARGET))) {
                    if (flags & ROOM_DRAW_OPA) {
                        displayList = roomShapeCullableEntry->opa;
                        if (displayList != NULL) {
                            gSPDisplayList(POLY_OPA_DISP++, displayList);
                        }
                    }

                    if (flags & ROOM_DRAW_XLU) {
                        displayList = roomShapeCullableEntry->xlu;
                        if (displayList != NULL) {
                            gSPDisplayList(POLY_XLU_DISP++, displayList);
                        }
                    }
                }
            } else {
                if (flags & ROOM_DRAW_OPA) {
                    displayList = roomShapeCullableEntry->opa;
                    if (displayList != NULL) {
                        gSPDisplayList(POLY_OPA_DISP++, displayList);
                    }
                }

                if (flags & ROOM_DRAW_XLU) {
                    displayList = roomShapeCullableEntry->xlu;
                    if (displayList != NULL) {
                        gSPDisplayList(POLY_XLU_DISP++, displayList);
                    }
                }
            }
        }
    } else {
        // Pick and sort entries by depth
        for (i = 0; i < roomShape->numEntries; i++, roomShapeCullableEntry++) {

            // Project the entry position, to get the depth it is at.
            pos.x = roomShapeCullableEntry->boundsSphereCenter.x;
            pos.y = roomShapeCullableEntry->boundsSphereCenter.y;
            pos.z = roomShapeCullableEntry->boundsSphereCenter.z;
            SkinMatrix_Vec3fMtxFMultXYZW(&play->viewProjectionMtxF, &pos, &projectedPos, &projectedW);

            // If the entry bounding sphere isn't fully before the rendered depth range
            if (-(f32)roomShapeCullableEntry->boundsSphereRadius < projectedPos.z) {

                // Compute the depth of the nearest point in the entry's bounding sphere
                entryBoundsNearZ = projectedPos.z - roomShapeCullableEntry->boundsSphereRadius;

                // If the entry bounding sphere isn't fully beyond the rendered depth range
                if (entryBoundsNearZ < play->lightCtx.unkC) {

                    // This entry will be rendered
                    insert->entry = roomShapeCullableEntry;
                    insert->boundsNearZ = entryBoundsNearZ;

                    // Insert into the linked list, ordered by ascending depth of the nearest point in the bounding
                    // sphere
                    iter = head;
                    if (iter == NULL) {
                        head = tail = insert;
                        insert->prev = insert->next = NULL;
                    } else {
                        do {
                            if (insert->boundsNearZ < iter->boundsNearZ) {
                                break;
                            }
                            iter = iter->next;
                        } while (iter != NULL);

                        if (iter == NULL) {
                            insert->prev = tail;
                            insert->next = NULL;
                            tail->next = insert;
                            tail = insert;
                        } else {
                            insert->prev = iter->prev;
                            if (insert->prev == NULL) {
                                head = insert;
                            } else {
                                insert->prev->next = insert;
                            }
                            iter->prev = insert;
                            insert->next = iter;
                        }
                    }

                    insert++;
                }
            }
        }

        // if this is real then I might not be
        R_ROOM_CULL_NUM_ENTRIES = roomShape->numEntries & 0xFFFF & 0xFFFF & 0xFFFF;

        // Draw entries, from nearest to furthest
        for (i = 1; head != NULL; head = head->next, i++) {
            Gfx* displayList;

            roomShapeCullableEntry = head->entry;

            if (R_ROOM_CULL_DEBUG_MODE != ROOM_CULL_DEBUG_MODE_OFF) {
                // Debug mode drawing

                if (((R_ROOM_CULL_DEBUG_MODE == ROOM_CULL_DEBUG_MODE_UP_TO_TARGET) &&
                     (i <= R_ROOM_CULL_DEBUG_TARGET)) ||
                    ((R_ROOM_CULL_DEBUG_MODE == ROOM_CULL_DEBUG_MODE_ONLY_TARGET) && (i == R_ROOM_CULL_DEBUG_TARGET))) {
                    if (flags & ROOM_DRAW_OPA) {
                        displayList = roomShapeCullableEntry->opa;
                        if (displayList != NULL) {
                            gSPDisplayList(POLY_OPA_DISP++, displayList);
                        }
                    }
                }
            } else {
                if (flags & ROOM_DRAW_OPA) {
                    displayList = roomShapeCullableEntry->opa;
                    if (displayList != NULL) {
                        gSPDisplayList(POLY_OPA_DISP++, displayList);
                    }
                }
            }
        }

        for (i = 1; head != NULL; head = head->next, i++) {
            Gfx* displayList;

            roomShapeCullableEntry = head->entry;

            if (head->next != NULL) {
                if (flags & ROOM_DRAW_XLU) {
                    displayList = roomShapeCullableEntry->xlu;
                    if (displayList != NULL) {
                        gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0xFF, 0xFF, iREG(93));
                        gSPDisplayList(POLY_XLU_DISP++, displayList);
                    }
                } else {
                    displayList = roomShapeCullableEntry->xlu;
                    if (displayList != NULL) {
                        gSPDisplayList(POLY_XLU_DISP++, displayList);
                    }
                }
            }
        }

        R_ROOM_CULL_USED_ENTRIES = i - 1;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/Room_DrawCullable.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/Room_DrawImageSingle.s")

RoomShapeImageMultiBgEntry* Room_GetImageMultiBgEntry(RoomShapeImageMulti* roomShapeImageMulti, PlayState* play) {
    Camera* activeCam = GET_ACTIVE_CAM(play);
    s32 bgCamIndex = activeCam->bgCamDataId;
    s16 overrideBgCamIndex;
    Player* player;
    RoomShapeImageMultiBgEntry* bgEntry;
    s32 i;

    overrideBgCamIndex = ((BgCamFuncData*)BgCheck_GetBgCamFuncDataImpl(&play->colCtx, bgCamIndex, BGCHECK_SCENE))
                             ->roomImageOverrideBgCamIndex;
    if (overrideBgCamIndex >= 0) {
        bgCamIndex = overrideBgCamIndex;
    }

    player = GET_PLAYER(play);
    player->actor.params = (player->actor.params & 0xFF00) | bgCamIndex;

    bgEntry = Lib_SegmentedToVirtual(roomShapeImageMulti->backgrounds);
    for (i = 0; i < roomShapeImageMulti->numBackgrounds; i++) {
        if (bgEntry->bgCamIndex == bgCamIndex) {
            return bgEntry;
        }
        bgEntry++;
    }

    __assert("../z_room.c", 849);

    return NULL;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/Room_DrawImageMulti.s")

void Room_DrawImage(PlayState* play, Room* room, u32 flags) {
    RoomShapeImageBase* roomShape = &room->roomShape->image.base;

    if (roomShape->amountType == ROOM_SHAPE_IMAGE_AMOUNT_SINGLE) {
        Room_DrawImageSingle(play, room, flags);
    } else if (roomShape->amountType == ROOM_SHAPE_IMAGE_AMOUNT_MULTI) {
        Room_DrawImageMulti(play, room, flags);
    } else {
        __assert("../z_room.c", 965);
    }
}

void Room_Init(PlayState* play, RoomContext* roomCtx) {
    s32 i;

    roomCtx->curRoom.num = -1;
    roomCtx->curRoom.segment = NULL;
    roomCtx->unk78 = 1;
    roomCtx->unk79 = 0;
    for (i = 0; i < ARRAY_COUNT(roomCtx->unk7A); i++) {
        roomCtx->unk7A[i] = 0;
    }
}

// OoT func_80096FE8
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/Room_AllocateAndLoad.s")

s32 Room_StartRoomTransition(PlayState* play, RoomContext* roomCtx, s32 index) {
    if (roomCtx->status == 0) {
        u32 size;

        roomCtx->prevRoom = roomCtx->curRoom;
        roomCtx->curRoom.num = index;
        roomCtx->curRoom.segment = NULL;
        roomCtx->status = 1;

        size = play->roomList[index].vromEnd - play->roomList[index].vromStart;
        roomCtx->activeRoomVram = (void*)(ALIGN16((u32)roomCtx->roomMemPages[roomCtx->activeMemPage] -
                                                  (size + 8) * roomCtx->activeMemPage - 7));

        osCreateMesgQueue(&roomCtx->loadQueue, roomCtx->loadMsg, 1);
        DmaMgr_SendRequestImpl(&roomCtx->dmaRequest, roomCtx->activeRoomVram, play->roomList[index].vromStart, size, 0,
                               &roomCtx->loadQueue, NULL);
        roomCtx->activeMemPage ^= 1;

        return 1;
    }

    return 0;
}

// TODO: better name
s32 Room_HandleLoadCallbacks(PlayState* play, RoomContext* roomCtx) {
    if (roomCtx->status == 1) {
        if (osRecvMesg(&roomCtx->loadQueue, NULL, OS_MESG_NOBLOCK) == 0) {
            roomCtx->status = 0;
            roomCtx->curRoom.segment = roomCtx->activeRoomVram;
            gSegments[3] = VIRTUAL_TO_PHYSICAL(roomCtx->activeRoomVram);

            Scene_ExecuteCommands(play, roomCtx->curRoom.segment);
            func_80123140(play, GET_PLAYER(play));
            Actor_SpawnTransitionActors(play, &play->actorCtx);

            if (((play->sceneId != SCENE_IKANA) || (roomCtx->curRoom.num != 1)) && (play->sceneId != SCENE_IKNINSIDE)) {
                play->envCtx.lightSettingOverride = 0xFF;
                play->envCtx.unk_E0 = 0;
            }
            func_800FEAB0();
            if (!func_800FE4B8(play)) {
                func_800FD858(play);
            }
        } else {
            return 0;
        }
    }

    return 1;
}

void Room_Draw(PlayState* play, Room* room, u32 flags) {
    if (room->segment != NULL) {
        gSegments[3] = VIRTUAL_TO_PHYSICAL(room->segment);
        sRoomDrawHandlers[room->roomShape->base.type](play, room, flags);
    }
    return;
}

void func_8012EBF8(PlayState* play, RoomContext* roomCtx) {
    roomCtx->prevRoom.num = -1;
    roomCtx->prevRoom.segment = NULL;
    func_800BA798(play, &play->actorCtx);
    Actor_SpawnTransitionActors(play, &play->actorCtx);
    if (roomCtx->curRoom.num > -1) {
        Map_InitRoomData(play, roomCtx->curRoom.num);
        Minimap_SavePlayerRoomInitInfo(play);
    }
    func_801A3CD8(play->roomCtx.curRoom.echo);
}
