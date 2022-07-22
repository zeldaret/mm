#include "global.h"

void Room_nop8012D510(PlayState* play, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4) {
}

void Room_DrawType3Mesh(PlayState* play, Room* room, u32 flags) {
}

void Room_DrawType0Mesh(PlayState* play, Room* room, u32 flags) {
    RoomMeshType0* mesh;
    s32 i;
    RoomMeshType0Params* meshParams;
    GraphicsContext* gfxCtx;
    UNK_TYPE4 pad;

    gfxCtx = play->state.gfxCtx;
    if (flags & 1) {
        func_800BCBF4(&D_801C1D10, play);
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);
        func_8012C268(play);
        gSPMatrix(gfxCtx->polyOpa.p++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & 2) {
        func_800BCC68(&D_801C1D10, play);
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(gfxCtx->polyXlu.p++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    mesh = &room->mesh->type0;
    meshParams = Lib_SegmentedToVirtual(mesh->paramsStart);
    for (i = 0; i < mesh->count; i++) {
        if ((flags & 1) && (meshParams->opaqueDl != NULL)) {
            gSPDisplayList(gfxCtx->polyOpa.p++, meshParams->opaqueDl);
        }

        if ((flags & 2) && (meshParams->translucentDl != NULL)) {
            gSPDisplayList(gfxCtx->polyXlu.p++, meshParams->translucentDl);
        }

        meshParams++;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/Room_DrawType2Mesh.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_8012DEE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_8012E254.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_8012E32C.s")

void Room_DrawType1Mesh(PlayState* play, Room* room, u32 flags) {
    RoomMeshType1* mesh = &room->mesh->type1;
    if (mesh->format == 1) {
        func_8012DEE8(play, room, flags);
    } else if (mesh->format == 2) {
        func_8012E32C(play, room, flags);
    } else {
        __assert("../z_room.c", 0x3c5);
    }
}

void Room_Init(PlayState* play, RoomContext* roomCtx) {
    s32 i;
    roomCtx->currRoom.num = -1;
    roomCtx->currRoom.segment = NULL;
    roomCtx->unk78 = 1;
    roomCtx->unk79 = 0;
    for (i = 0; i < 3; i++) {
        roomCtx->unk7A[i] = 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/Room_AllocateAndLoad.s")

s32 Room_StartRoomTransition(PlayState* play, RoomContext* roomCtx, s32 index) {
    if (roomCtx->unk31 == 0) {
        s32 size;

        roomCtx->prevRoom = roomCtx->currRoom;
        roomCtx->currRoom.num = index;
        roomCtx->currRoom.segment = NULL;
        roomCtx->unk31 = 1;

        size = play->roomList[index].vromEnd - play->roomList[index].vromStart;
        roomCtx->activeRoomVram =
            (void*)(((s32)roomCtx->roomMemPages[roomCtx->activeMemPage] - (size + 8) * roomCtx->activeMemPage + 8) &
                    0xfffffff0);

        osCreateMesgQueue(&roomCtx->loadQueue, roomCtx->loadMsg, 1);
        DmaMgr_SendRequestImpl(&roomCtx->dmaRequest, roomCtx->activeRoomVram, play->roomList[index].vromStart, size, 0,
                               &roomCtx->loadQueue, NULL);
        roomCtx->activeMemPage ^= 1;

        return 1;
    }

    return 0;
}

s32 Room_HandleLoadCallbacks(PlayState* play, RoomContext* roomCtx) {
    if (roomCtx->unk31 == 1) {
        if (!osRecvMesg(&roomCtx->loadQueue, NULL, OS_MESG_NOBLOCK)) {
            roomCtx->unk31 = 0;
            roomCtx->currRoom.segment = roomCtx->activeRoomVram;
            // TODO: Segment number enum
            gSegments[0x03] = PHYSICAL_TO_VIRTUAL(roomCtx->activeRoomVram);

            Scene_ProcessHeader(play, (SceneCmd*)roomCtx->currRoom.segment);
            func_80123140(play, GET_PLAYER(play));
            Actor_SpawnTransitionActors(play, &play->actorCtx);

            if (((play->sceneNum != SCENE_IKANA) || (roomCtx->currRoom.num != 1)) &&
                (play->sceneNum != SCENE_IKNINSIDE)) {
                play->envCtx.lightSettingOverride = 0xff;
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
        // TODO: Segment number enum
        gSegments[0x03] = PHYSICAL_TO_VIRTUAL(room->segment);
        roomDrawFuncs[room->mesh->type0.type](play, room, flags);
    }
    return;
}

void func_8012EBF8(PlayState* play, RoomContext* roomCtx) {
    roomCtx->prevRoom.num = -1;
    roomCtx->prevRoom.segment = NULL;
    func_800BA798(play, &play->actorCtx);
    Actor_SpawnTransitionActors(play, &play->actorCtx);
    if (roomCtx->currRoom.num > -1) {
        Map_InitRoomData(play, roomCtx->currRoom.num);
        Minimap_SavePlayerRoomInitInfo(play);
    }
    func_801A3CD8(play->roomCtx.currRoom.echo);
}
