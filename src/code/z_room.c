#include "global.h"

void Room_nop8012D510(GlobalContext* globalCtx, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4) {
}

void Room_DrawType3Mesh(GlobalContext* globalCtx, Room* room, u32 flags) {
}

void Room_DrawType0Mesh(GlobalContext* globalCtx, Room* room, u32 flags) {
    RoomMeshType0* mesh;
    s32 i;
    RoomMeshType0Params* meshParams;
    GraphicsContext* gfxCtx;
    UNK_TYPE4 pad;

    gfxCtx = globalCtx->state.gfxCtx;
    if (flags & 1) {
        func_800BCBF4(&D_801C1D10, globalCtx);
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);
        func_8012C268(globalCtx);
        gSPMatrix(gfxCtx->polyOpa.p++, &gIdentityMtx, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & 2) {
        func_800BCC68(&D_801C1D10, globalCtx);
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_8012C2DC(globalCtx->state.gfxCtx);
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

void Room_DrawType1Mesh(GlobalContext* globalCtx, Room* room, u32 flags) {
    RoomMeshType1* mesh = &room->mesh->type1;
    if (mesh->format == 1) {
        func_8012DEE8(globalCtx, room, flags);
    } else if (mesh->format == 2) {
        func_8012E32C(globalCtx, room, flags);
    } else {
        __assert("../z_room.c", 0x3c5);
    }
}

void Room_Init(GlobalContext* globalCtx, RoomContext* roomCtx) {
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

s32 Room_StartRoomTransition(GlobalContext* globalCtx, RoomContext* roomCtx, s32 index) {
    if (roomCtx->unk31 == 0) {
        s32 size;

        roomCtx->prevRoom = roomCtx->currRoom;
        roomCtx->currRoom.num = index;
        roomCtx->currRoom.segment = NULL;
        roomCtx->unk31 = 1;

        size = globalCtx->roomList[index].vromEnd - globalCtx->roomList[index].vromStart;
        roomCtx->activeRoomVram =
            (void*)(((s32)roomCtx->roomMemPages[roomCtx->activeMemPage] - (size + 8) * roomCtx->activeMemPage + 8) &
                    0xfffffff0);

        osCreateMesgQueue(&roomCtx->loadQueue, roomCtx->loadMsg, 1);
        DmaMgr_SendRequestImpl(&roomCtx->dmaRequest, roomCtx->activeRoomVram, globalCtx->roomList[index].vromStart,
                               size, 0, &roomCtx->loadQueue, NULL);
        roomCtx->activeMemPage ^= 1;

        return 1;
    }

    return 0;
}

s32 Room_HandleLoadCallbacks(GlobalContext* globalCtx, RoomContext* roomCtx) {
    if (roomCtx->unk31 == 1) {
        if (!osRecvMesg(&roomCtx->loadQueue, NULL, OS_MESG_NOBLOCK)) {
            roomCtx->unk31 = 0;
            roomCtx->currRoom.segment = roomCtx->activeRoomVram;
            // TODO: Segment number enum
            gSegments[0x03] = PHYSICAL_TO_VIRTUAL(roomCtx->activeRoomVram);

            Scene_ProcessHeader(globalCtx, (SceneCmd*)roomCtx->currRoom.segment);
            func_80123140(globalCtx, GET_PLAYER(globalCtx));
            Actor_SpawnTransitionActors(globalCtx, &globalCtx->actorCtx);

            if (((globalCtx->sceneNum != SCENE_IKANA) || (roomCtx->currRoom.num != 1)) &&
                (globalCtx->sceneNum != SCENE_IKNINSIDE)) {
                globalCtx->envCtx.lightSettingOverride = 0xff;
                globalCtx->envCtx.unk_E0 = 0;
            }
            func_800FEAB0();
            if (!func_800FE4B8(globalCtx)) {
                func_800FD858(globalCtx);
            }
        } else {
            return 0;
        }
    }

    return 1;
}

void Room_Draw(GlobalContext* globalCtx, Room* room, u32 flags) {
    if (room->segment != NULL) {
        // TODO: Segment number enum
        gSegments[0x03] = PHYSICAL_TO_VIRTUAL(room->segment);
        roomDrawFuncs[room->mesh->type0.type](globalCtx, room, flags);
    }
    return;
}

void func_8012EBF8(GlobalContext* globalCtx, RoomContext* roomCtx) {
    roomCtx->prevRoom.num = -1;
    roomCtx->prevRoom.segment = NULL;
    func_800BA798(globalCtx, &globalCtx->actorCtx);
    Actor_SpawnTransitionActors(globalCtx, &globalCtx->actorCtx);
    if (-1 < roomCtx->currRoom.num) {
        func_8010A33C(globalCtx, roomCtx->currRoom.num);
        func_8010A2DC(globalCtx);
    }
    func_801A3CD8(globalCtx->roomCtx.currRoom.echo);
}
