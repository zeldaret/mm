#include <ultra64.h>
#include <global.h>

void Room_nop8012D510(GlobalContext* ctxt, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4) {}

void Room_DrawType3Mesh(GlobalContext* ctxt, Room* room, u32 flags) {}

void Room_DrawType0Mesh(GlobalContext* ctxt, Room* room, u32 flags) {
    RoomMeshType0* mesh;
    s32 i;
    RoomMeshType0Params* meshParams;
    GraphicsContext* gfxCtx;
    UNK_TYPE4 pad;

    gfxCtx = ctxt->state.gfxCtx;
    if (flags & 1) {
        func_800BCBF4(&D_801C1D10, ctxt);
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);
        func_8012C268(ctxt);
        gSPMatrix(gfxCtx->polyOpa.p++, &D_801D1DE0, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & 2) {
        func_800BCC68(&D_801C1D10, ctxt);
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_8012C2DC(ctxt->state.gfxCtx);
        gSPMatrix(gfxCtx->polyXlu.p++, &D_801D1DE0, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    mesh = &room->mesh->type0;
    meshParams = (RoomMeshType0Params*)Lib_PtrSegToVirt(mesh->paramsStart);
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

GLOBAL_ASM("asm/non_matchings/z_room/Room_DrawType2Mesh.asm")

GLOBAL_ASM("asm/non_matchings/z_room/func_8012DEE8.asm")

GLOBAL_ASM("asm/non_matchings/z_room/func_8012E254.asm")

GLOBAL_ASM("asm/non_matchings/z_room/func_8012E32C.asm")

void Room_DrawType1Mesh(GlobalContext* ctxt, Room* room, u32 flags) {
    RoomMeshType1* mesh = &room->mesh->type1;
    if (mesh->format == 1) {
        func_8012DEE8(ctxt,room,flags);
    } else if (mesh->format == 2) {
        func_8012E32C(ctxt,room,flags);
    } else {
        assert_fail(D_801DDFAC,0x3c5);
    }
}

void Room_Init(GlobalContext* ctxt, RoomContext* roomCtxt) {
    s32 i;
    roomCtxt->currRoom.num = -1;
    roomCtxt->currRoom.segment = NULL;
    roomCtxt->unk78 = 1;
    roomCtxt->unk79 = 0;
    for (i = 0; i < 3; i++) {
        roomCtxt->unk7A[i] = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/z_room/Room_AllocateAndLoad.asm")

#ifdef NON_MATCHING
s32 Room_StartRoomTransition(GlobalContext* ctxt, RoomContext* roomCtxt, s32 index) {
    u32 size;

    // XXX: this should use a branch-likely
    if (roomCtxt->unk31 == 0) {
        roomCtxt->prevRoom = roomCtxt->currRoom;
        roomCtxt->currRoom.num = index;
        roomCtxt->currRoom.segment = NULL;
        roomCtxt->unk31 = 1;

        size = ctxt->roomAddrs[index].vromEnd - ctxt->roomAddrs[index].vromStart;
        roomCtxt->activeRoomVram = ((s32)roomCtxt->roomMemPages[roomCtxt->activeMemPage] - (size + 8) * roomCtxt->activeMemPage + 8) & 0xfffffff0;

        osCreateMesgQueue(&roomCtxt->loadQueue, roomCtxt->loadMsg, 1);
        DmaMgr_SendRequestImpl(&roomCtxt->dmaRequest, roomCtxt->activeRoomVram, ctxt->roomAddrs[index].vromStart, size,
                      0, &roomCtxt->loadQueue, NULL);
        roomCtxt->activeMemPage ^= 1;

        return 1;
    }

    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/z_room/Room_StartRoomTransition.asm")
#endif

s32 Room_HandleLoadCallbacks(GlobalContext* ctxt, RoomContext* roomCtxt) {
    if (roomCtxt->unk31 == 1)
    {
        if (!osRecvMesg(&roomCtxt->loadQueue, NULL, OS_MESG_NOBLOCK))
        {
            roomCtxt->unk31 = 0;
            roomCtxt->currRoom.segment = (void*)(roomCtxt->activeRoomVram);
            gRspSegmentPhysAddrs[3] = roomCtxt->activeRoomVram + 0x80000000;

            Scene_ProcessHeader(ctxt, (SceneCmd*)roomCtxt->currRoom.segment);
            func_80123140(ctxt, (ActorPlayer*)ctxt->actorCtx.actorList[2].first);
            Actor_SpawnTransitionActors(ctxt, &ctxt->actorCtx);

            if (((ctxt->sceneNum != 0x13) || (roomCtxt->currRoom.num != 1)) && (ctxt->sceneNum != 0x56)) {
                ctxt->kankyoContext.unkC3 = 0xff;
                ctxt->kankyoContext.unkE0 = 0;
            }
            func_800FEAB0();
            if (!func_800FE4B8(ctxt)) {
                func_800FD858(ctxt);
            }
        } else {
            return 0;
        }
    }

    return 1;
}

void Room_Draw(GlobalContext* ctxt, Room* room, u32 flags) {
    if (room->segment != NULL) {
        gRspSegmentPhysAddrs[3] = (u32)room->segment + 0x80000000;
        roomDrawFuncs[room->mesh->type0.type](ctxt, room, flags);
    }
    return;
}

void func_8012EBF8(GlobalContext* ctxt, RoomContext* roomCtxt){
    roomCtxt->prevRoom.num = -1;
    roomCtxt->prevRoom.segment = NULL;
    func_800BA798(ctxt, &ctxt->actorCtx);
    Actor_SpawnTransitionActors(ctxt, &ctxt->actorCtx);
    if (-1 < roomCtxt->currRoom.num) {
        func_8010A33C(ctxt, roomCtxt->currRoom.num);
        func_8010A2DC(ctxt);
    }
    func_801A3CD8(ctxt->roomContext.currRoom.unk4);
}
