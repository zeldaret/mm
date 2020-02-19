#include <ultra64.h>
#include <global.h>

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_LoadObject.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_Init.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_ReloadUnloadedObjects.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_FindSceneObjectIndex.asm")

s32 Scene_IsObjectLoaded(SceneContext* iParm1, s32 index) {
    if (iParm1->objects[index].id > 0) {
        return 1;
    } else {
        return 0;
    }
}

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_DmaAllObjects.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/func_8012F73C.asm")

// Scene Command 0x00: Link Spawn List
#ifdef NONMATCHING
// Regalloc differences only
void Scene_HeaderCommand00(GlobalContext* ctxt, SceneCmd* entry) {
    ActorEntry* linkEntry;
    s32 loadReturn;
    void* objectVramAddr;
    s16 temp16;

    linkEntry = (ActorEntry*)Lib_PtrSegToVirt((void*)entry->base.unk4) + (ctxt->entranceList[ctxt->curSpawn].spawn & 0xFF);
    ctxt->linkActorEntry = linkEntry;

    if ( (ctxt->linkActorEntry->params & 0x0F00) >> 8 == 0x0C ||
         (gSaveContext.extra.unk010 == 0x02 && gSaveContext.extra.unk042 == 0x0CFF)
    ) {
        Scene_LoadObject(&ctxt->sceneContext, 0x192);
        return;
    }

    loadReturn = Scene_LoadObject(&ctxt->sceneContext, 0x11);

    temp16 = (&ctxt->sceneContext)->unk8;
    objectVramAddr = ctxt->sceneContext.objects[temp16].vramAddr;
    ctxt->sceneContext.unk8 = loadReturn & 0xFF;
    ctxt->sceneContext.unk9 = loadReturn & 0xFF;

    temp16 = D_801C2730[gSaveContext.perm.unk20];
    actorOverlayTable[0].initValues->objectDependency = temp16;

    Scene_LoadObject(&ctxt->sceneContext, temp16);

    ctxt->sceneContext.objects[(&ctxt->sceneContext)->unk8].vramAddr = objectVramAddr;
}
#else
GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand00.asm")
#endif

// Scene Command 0x01: Actor List
void Scene_HeaderCommand01(GlobalContext* ctxt, SceneCmd* entry) {
    GlobalContext *temp_a2;

    temp_a2 = ctxt;
    temp_a2->sceneNumActorsToLoad = (u16) entry->base.unk1;
    ctxt = temp_a2;
    ctxt->sceneActorList = (ActorEntry*)Lib_PtrSegToVirt((void*)entry->base.unk4);
    ctxt->actorContext.unkC = (u16)0;
}

// Scene Command 0x02: Cutscene Camera List
void Scene_HeaderCommand02(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->unk18858 = (UNK_PTR)Lib_PtrSegToVirt((void*)entry->base.unk4);
}

// Scene Command 0x03: Collision Header
void Scene_HeaderCommand03(GlobalContext* ctxt, SceneCmd* entry) {
    BgMeshHeader* temp_ret;
    BgMeshHeader* temp_s0;

    temp_ret = (BgMeshHeader*)Lib_PtrSegToVirt((void*)entry->base.unk4);
    temp_s0 = temp_ret;
    temp_s0->vertices = (BgVertex*)Lib_PtrSegToVirt(temp_ret->vertices);
    temp_s0->polygons = (BgPolygon*)Lib_PtrSegToVirt(temp_s0->polygons);
    if (temp_s0->attributes != 0) {
        temp_s0->attributes = (BgPolygonAttributes*)Lib_PtrSegToVirt(temp_s0->attributes);
    }
    if (temp_s0->cameraData != 0) {
        temp_s0->cameraData = (void*)Lib_PtrSegToVirt(temp_s0->cameraData);
    }
    if (temp_s0->waterboxes != 0) {
        temp_s0->waterboxes = (BgWaterBox*)Lib_PtrSegToVirt(temp_s0->waterboxes);
    }

    BgCheck_Init(&ctxt->bgCheckContext, ctxt, temp_s0);
}

// Scene Command 0x04: Room List
void Scene_HeaderCommand04(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->numRooms = (u8) entry->base.unk1;
    ctxt->roomAddrs = (RoomFileLocation*)Lib_PtrSegToVirt((void*)entry->base.unk4);
}

// Scene Command 0x06: Entrance List
void Scene_HeaderCommand06(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->entranceList = (EntranceEntry*)Lib_PtrSegToVirt((void*)entry->base.unk4);
}

// Scene Command 0x07: Special Files
void Scene_HeaderCommand07(GlobalContext* ctxt, SceneCmd* entry) {
    if (entry->base.unk4 != 0) {
        ctxt->sceneContext.keepObjectId = Scene_LoadObject(&ctxt->sceneContext, entry->base.unk4);
        gRspSegmentPhysAddrs[5] = (u32)(ctxt->sceneContext.objects[ctxt->sceneContext.keepObjectId].vramAddr) + 0x80000000;
    }

    if (entry->base.unk1 != 0) {
        // TODO:
        // OOT has D_801C2650's equivalent as a list of navi messages that store SceneTableEntry structs.
        // This needs to be something like (SceneTableEntry*)(&D_801C2650[entry->unk1])
        // Currently D_801C2650 is not typed so that can't be completed at this moment.
        ctxt->unk18868 = Play_LoadScene(ctxt, (SceneTableEntry*)(((entry->base.unk1 * 8) - 8) + &D_801C2650));
        // OR LESS MATCHING:
        //ctxt->unk18868 = Play_LoadScene(ctxt, (SceneTableEntry*)(&D_801C2650[entry->unk1 - 1]));
    }
}

// Scene Command 0x08: Room Behavior
void Scene_HeaderCommand08(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.unk3 = entry->base.unk1;
    ctxt->roomContext.currRoom.unk2 = entry->base.unk4 & 0xFF;
    ctxt->roomContext.currRoom.unk5 = (entry->base.unk4 >> 8) & 1;
    ctxt->msgContext.unk12044 = (entry->base.unk4 >> 0xa) & 1;
    ctxt->roomContext.currRoom.enablePosLights = (entry->base.unk4 >> 0xb) & 1;
    ctxt->kankyoContext.unkE2 = (entry->base.unk4 >> 0xc) & 1;
}

// Scene Command 0x0A: Mesh Header
void Scene_HeaderCommand0A(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.mesh = (RoomMesh*)Lib_PtrSegToVirt((void*)entry->base.unk4);
}

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand0B.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand0C.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand0D.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand0E.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/func_8012FEBC.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand0F.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/func_8012FF10.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand11.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand12.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand10.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand05.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand13.asm")

// Scene Command 0x09: Undefined
void Scene_HeaderCommand09(GlobalContext* ctxt, SceneCmd* entry) {

}

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand15.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand16.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand18.asm")

// Scene Command 0x17: Cutscene Data
void Scene_HeaderCommand17(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->cutsceneContext.cutsceneCount = (u8)entry->base.unk1;
    ctxt->cutsceneList = (CutsceneEntry*)Lib_PtrSegToVirt((void*)entry->base.unk4);
}

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand1B.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand1C.asm")

// Scene Command 0x1D: Undefined
void Scene_HeaderCommand1D(GlobalContext* ctxt, SceneCmd* entry) {

}

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand1E.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand19.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_HeaderCommand1A.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/func_801306A4.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene/Scene_ProcessHeader.asm")

u32 Scene_CreateEntrance(u32 sceneIndex, u32 spawnIndex, u32 offset) {
    return (((sceneIndex << 9) | (spawnIndex << 4)) | offset) & 0xFFFF;
}

GLOBAL_ASM("./asm/nonmatching/z_scene/func_80130784.asm")