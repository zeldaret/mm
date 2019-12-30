#include <ultra64.h>
#include <global.h>

void Room_nop8012D510(GlobalContext* ctxt, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4) {}

void Room_DrawType3Mesh(GlobalContext* ctxt, Room* room, u32 flags) {}

void Room_DrawType0Mesh(GlobalContext* ctxt, Room* room, u32 flags) {
    RoomMeshType0* mesh;
    s32 i;
    RoomMeshType0Params* meshParams;
    GraphicsContext* gCtxt;
    UNK_TYPE4 pad;

    gCtxt = ctxt->common.gCtxt;
    if (flags & 1) {
        func_800BCBF4(&D_801C1D10, ctxt);
        gSPSegment(gCtxt->polyOpa.append++, 0x03, room->vramAddr);
        func_8012C268(ctxt);
        gSPMatrix(gCtxt->polyOpa.append++, &D_801D1DE0, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & 2) {
        func_800BCC68(&D_801C1D10, ctxt);
        gSPSegment(gCtxt->polyXlu.append++, 0x03, room->vramAddr);
        func_8012C2DC(ctxt->common.gCtxt);
        gSPMatrix(gCtxt->polyXlu.append++, &D_801D1DE0, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    mesh = &room->mesh->type0;
    meshParams = (RoomMeshType0Params*)Lib_PtrSegToVirt(mesh->paramsStart);
    for (i = 0; i < mesh->count; i++) {
        if ((flags & 1) && (meshParams->opaqueDl != NULL)) {
            gSPDisplayList(gCtxt->polyOpa.append++, meshParams->opaqueDl);
        }

        if ((flags & 2) && (meshParams->translucentDl != NULL)) {
            gSPDisplayList(gCtxt->polyXlu.append++, meshParams->translucentDl);
        }

        meshParams++;
    }
}

GLOBAL_ASM("asm/nonmatching/z_room/Room_DrawType2Mesh.asm")

GLOBAL_ASM("asm/nonmatching/z_room/func_8012DEE8.asm")

GLOBAL_ASM("asm/nonmatching/z_room/func_8012E254.asm")

GLOBAL_ASM("asm/nonmatching/z_room/func_8012E32C.asm")

void Room_DrawType1Mesh(GlobalContext* ctxt, Room* room, u32 flags) {
    RoomMeshType1* mesh = &room->mesh->type1;
    if (mesh->format == 1) {
        func_8012DEE8(ctxt,room,flags);
    } else if (mesh->format == 2) {
        func_8012E32C(ctxt,room,flags);
    } else {
        func_80086280(D_801DDFAC,0x3c5);
    }
}

void Room_Init(GlobalContext* ctxt, RoomContext* roomCtxt) {
    s32 i;
    roomCtxt->currRoom.index = -1;
    roomCtxt->currRoom.vramAddr = 0;
    roomCtxt->unk78 = 1;
    roomCtxt->unk79 = 0;
    for (i = 0; i < 3; i++) {
        roomCtxt->unk7A[i] = 0;
    }
}

GLOBAL_ASM("asm/nonmatching/z_room/Room_AllocateAndLoad.asm")

#ifdef NONMATCHING
s32 Room_StartRoomTransition(GlobalContext* ctxt, RoomContext* roomCtxt, s32 index) {
    u32 size;

    // XXX: this should use a branch-likely
    if (roomCtxt->unk31 == 0) {
        roomCtxt->prevRoom = roomCtxt->currRoom;
        roomCtxt->currRoom.index = index;
        roomCtxt->currRoom.vramAddr = NULL;
        roomCtxt->unk31 = 1;

        size = ctxt->roomAddrs[index].vromEnd - ctxt->roomAddrs[index].vromStart;
        roomCtxt->activeRoomVram = ((s32)roomCtxt->roomMemPages[roomCtxt->activeMemPage] - (size + 8) * roomCtxt->activeMemPage + 8) & 0xfffffff0;

        osCreateMesgQueue(&roomCtxt->roomDmaCallback, roomCtxt->roomDmaCallbackMsg, 1);
        Dmamgr_SendRequest(&roomCtxt->dmaReq, roomCtxt->activeRoomVram, ctxt->roomAddrs[index].vromStart, size,
                      0, &roomCtxt->roomDmaCallback, NULL);
        roomCtxt->activeMemPage ^= 1;

        return 1;
    }

    return 0;
}
#else
GLOBAL_ASM("asm/nonmatching/z_room/Room_StartRoomTransition.asm")
#endif

s32 Room_HandleLoadCallbacks(GlobalContext* ctxt, RoomContext* roomCtxt) {
    if (roomCtxt->unk31 == 1)
    {
        if (!osRecvMesg(&roomCtxt->roomDmaCallback, NULL, OS_MESG_NOBLOCK))
        {
            roomCtxt->unk31 = 0;
            roomCtxt->currRoom.vramAddr = (void*)(roomCtxt->activeRoomVram);
            gRspSegmentPhysAddrs[3] = roomCtxt->activeRoomVram + 0x80000000;

            Scene_ProcessHeader(ctxt, (SceneHeaderEntry*)roomCtxt->currRoom.vramAddr);
            func_80123140(ctxt, (ActorPlayer*)ctxt->actorContext.actorTypeLists[2].head);
            Actor_SpawnTransitionActors(ctxt, &ctxt->actorContext);

            if (((ctxt->currentScene != 0x13) || (roomCtxt->currRoom.index != 1)) && (ctxt->currentScene != 0x56)) {
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
    if (room->vramAddr != NULL) {
        gRspSegmentPhysAddrs[3] = (u32)room->vramAddr + 0x80000000;
        roomDrawFuncs[room->mesh->type0.type](ctxt,room,flags);
    }
    return;
}

void func_8012EBF8(GlobalContext* ctxt, RoomContext* roomCtxt){
    roomCtxt->prevRoom.index = -1;
    roomCtxt->prevRoom.vramAddr = NULL;
    func_800BA798(ctxt, &ctxt->actorContext);
    Actor_SpawnTransitionActors(ctxt, &ctxt->actorContext);
    if (-1 < roomCtxt->currRoom.index) {
        func_8010A33C(ctxt, roomCtxt->currRoom.index);
        func_8010A2DC(ctxt);
    }
    func_801A3CD8(ctxt->roomContext.currRoom.unk4);
}
