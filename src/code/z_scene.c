#include <ultra64.h>
#include <global.h>

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_LoadObject.asm")

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_Init.asm")

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_ReloadUnloadedObjects.asm")

s32 Scene_FindSceneObjectIndex(SceneContext* sceneCtxt, s16 objectId) {
    s32 i;

    for(i = 0; i < sceneCtxt->objectCount; i++) {
        if((sceneCtxt->objects[i].id < 0 ? -sceneCtxt->objects[i].id : sceneCtxt->objects[i].id) == objectId) {
            return i;
        }
    }

    return -1;
}

s32 Scene_IsObjectLoaded(SceneContext* iParm1, s32 index) {
    if (iParm1->objects[index].id > 0) {
        return 1;
    } else {
        return 0;
    }
}

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_DmaAllObjects.asm")

GLOBAL_ASM("./asm/non_matchings/z_scene/func_8012F73C.asm")

// Scene Command 0x00: Link Spawn List
void Scene_HeaderCommand00(GlobalContext* ctxt, SceneCmd* entry) {
    GlobalContext* global;
    s32 loadReturn;
    void* objectVramAddr;
    s16 temp16;
    u8 unk20;

    ctxt->linkActorEntry = (ActorEntry*)Lib_PtrSegToVirt((void*)entry->spawnList.segment) +
                    ctxt->setupEntranceList[ctxt->curSpawn].spawn;

    if ( (ctxt->linkActorEntry->params & 0x0F00) >> 8 == 0x0C ||
         (gSaveContext.extra.unk10 == 0x02 && gSaveContext.extra.unk42 == 0x0CFF)
    ) {
        Scene_LoadObject(&ctxt->sceneContext, 0x192);
        return;
    }

    loadReturn = Scene_LoadObject(&ctxt->sceneContext, 0x11);

    global = ctxt;
    objectVramAddr = global->sceneContext.objects[global->sceneContext.objectCount].vramAddr;

    ctxt->sceneContext.objectCount = loadReturn;
    ctxt->sceneContext.unk9 = loadReturn;

    unk20 = gSaveContext.perm.unk20;
    temp16 = D_801C2730[unk20];

    actorOverlayTable[0].initInfo->objectId = temp16;

    Scene_LoadObject(&ctxt->sceneContext, temp16);

    ctxt->sceneContext.objects[ctxt->sceneContext.objectCount].vramAddr = objectVramAddr;
}

// Scene Command 0x01: Actor List
void Scene_HeaderCommand01(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->sceneNumActorsToLoad = (u16) entry->base.data1;
    ctxt->setupActorList = (ActorEntry*)Lib_PtrSegToVirt((void*)entry->base.data2);
    ctxt->actorCtx.unkC = (u16)0;
}

// Scene Command 0x02: Cutscene Camera List
void Scene_HeaderCommand02(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->unk18858 = (UNK_PTR)Lib_PtrSegToVirt((void*)entry->base.data2);
}

// Scene Command 0x03: Collision Header
void Scene_HeaderCommand03(GlobalContext* ctxt, SceneCmd* entry) {
    BgMeshHeader* temp_ret;
    BgMeshHeader* temp_s0;

    temp_ret = (BgMeshHeader*)Lib_PtrSegToVirt((void*)entry->base.data2);
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

    BgCheck_Init(&ctxt->colCtx, ctxt, temp_s0);
}

// Scene Command 0x04: Room List
void Scene_HeaderCommand04(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->numRooms = (u8) entry->base.data1;
    ctxt->roomList = (RoomFileLocation*)Lib_PtrSegToVirt((void*)entry->base.data2);
}

// Scene Command 0x06: Entrance List
void Scene_HeaderCommand06(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->setupEntranceList = (EntranceEntry*)Lib_PtrSegToVirt((void*)entry->base.data2);
}

// Scene Command 0x07: Special Files
void Scene_HeaderCommand07(GlobalContext* ctxt, SceneCmd* entry) {
    if (entry->base.data2 != 0) {
        ctxt->sceneContext.keepObjectId = Scene_LoadObject(&ctxt->sceneContext, entry->base.data2);
        gRspSegmentPhysAddrs[5] = (u32)(ctxt->sceneContext.objects[ctxt->sceneContext.keepObjectId].vramAddr) + 0x80000000;
    }

    if (entry->base.data1 != 0) {
        ctxt->unk18868 = Play_LoadScene(ctxt, &D_801C2650[entry->base.data1 - 1]);
    }
}

// Scene Command 0x08: Room Behavior
void Scene_HeaderCommand08(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.unk3 = entry->base.data1;
    ctxt->roomContext.currRoom.unk2 = entry->base.data2 & 0xFF;
    ctxt->roomContext.currRoom.unk5 = (entry->base.data2 >> 8) & 1;
    ctxt->msgCtx.unk12044 = (entry->base.data2 >> 0xa) & 1;
    ctxt->roomContext.currRoom.enablePosLights = (entry->base.data2 >> 0xb) & 1;
    ctxt->kankyoContext.unkE2 = (entry->base.data2 >> 0xc) & 1;
}

// Scene Command 0x0A: Mesh Header
void Scene_HeaderCommand0A(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.mesh = (RoomMesh*)Lib_PtrSegToVirt((void*)entry->base.data2);
}

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_HeaderCommand0B.asm")

// Scene Command 0x0C: Light List
void Scene_HeaderCommand0C(GlobalContext* ctxt, SceneCmd* entry) {
    s32 i;
    LightInfo* lightInfo;

    lightInfo = (LightInfo*)Lib_PtrSegToVirt((void*)entry->base.data2);
    for (i = 0; i < entry->base.data1; i++)
    {
        Lights_Insert(ctxt, &ctxt->lightCtx, lightInfo);
        lightInfo++;
    }
}

// Scene Command 0x0D: Path List
void Scene_HeaderCommand0D(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->setupPathList = (void*)Lib_PtrSegToVirt((void*)entry->base.data2);
}

// Scene Command 0x0E: Transition Actor List
void Scene_HeaderCommand0E(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->transitionActorCount = entry->base.data1;
    ctxt->transitionActorList = (TransitionActorInit*)Lib_PtrSegToVirt((void*)entry->base.data2);
    func_80105818(ctxt, ctxt->transitionActorCount, ctxt->transitionActorList);
}

void func_8012FEBC(GlobalContext* ctxt, u8* nbTransitionActors) {
    *nbTransitionActors = 0;
}

// Scene Command 0x0F: Light Setting List
void Scene_HeaderCommand0F(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->kankyoContext.environmentSettingsCount = entry->base.data1;
    ctxt->kankyoContext.environmentSettingsList = (void*)Lib_PtrSegToVirt((void*)entry->base.data2);
}

s32 func_8012FF10(GlobalContext* ctxt, s32 fileIndex) {
    s32 vromStart = D_801C2660[fileIndex].vromStart;
    s32 fileSize = D_801C2660[fileIndex].vromEnd - vromStart;

    if (fileSize) {
        ctxt->roomContext.unk74 = GameStateHeap_AllocFromEnd(&ctxt->state.heap, fileSize);
        return DmaMgr_SendRequest0((s32)ctxt->roomContext.unk74, vromStart, fileSize);
    }

    // UB: Undefined behaviour to not have a return statement here, but it breaks matching to add one.
}

// Scene Command 0x11: Skybox Settings
void Scene_HeaderCommand11(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->unk18874 = entry->skyboxSettings.skyboxId & 3;
    ctxt->kankyoContext.unk17 = ctxt->kankyoContext.unk18 = entry->skyboxSettings.unk5;
    ctxt->kankyoContext.unk1E = entry->skyboxSettings.unk6;
    func_8012FF10(ctxt, entry->skyboxSettings.data1);
}

// Scene Command 0x12: Skybox Disables
void Scene_HeaderCommand12(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->kankyoContext.unk15 = entry->skyboxDisables.unk4;
    ctxt->kankyoContext.unk16 = entry->skyboxDisables.unk5;
}

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_HeaderCommand10.asm")

// Scene Command 0x05: Wind Settings
void Scene_HeaderCommand05(GlobalContext* ctxt, SceneCmd* entry) {
    s8 temp1 = entry->windSettings.unk4;
    s8 temp2 = entry->windSettings.unk5;
    s8 temp3 = entry->windSettings.unk6;

    ctxt->kankyoContext.unkAC = temp1;
    ctxt->kankyoContext.unkAE = temp2;
    ctxt->kankyoContext.unkB0 = temp3;
    ctxt->kankyoContext.unkB4 = entry->windSettings.unk7;
}

void Scene_HeaderCommand13(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->setupExitList = (void*)Lib_PtrSegToVirt((void*)entry->exitList.segment);
}

// Scene Command 0x09: Undefined
void Scene_HeaderCommand09(GlobalContext* ctxt, SceneCmd* entry) {

}

// Scene Command 0x15: Sound Settings
void Scene_HeaderCommand15(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->unk814 = entry->soundSettings.musicSeq;
    ctxt->unk815 = entry->soundSettings.nighttimeSFX;
    if (gSaveContext.extra.unk276 == 0xFF || func_801A8A50(0) == 0x57) {
        audio_setBGM(entry->soundSettings.bgmId);
    }
}

// Scene Command 0x16: Echo Setting
void Scene_HeaderCommand16(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.echo = entry->echoSettings.echo;
}

// Scene Command 0x18: Alternate Headers
void Scene_HeaderCommand18(GlobalContext* ctxt, SceneCmd* entry) {
    SceneCmd** altHeaderList;
    SceneCmd* altHeader;

    if (gSaveContext.extra.sceneSetupIndex) {
        altHeaderList = (SceneCmd**)Lib_PtrSegToVirt((void*)entry->altHeaders.segment);
        altHeader = altHeaderList[gSaveContext.extra.sceneSetupIndex - 1];

        if (altHeader != NULL) {
           Scene_ProcessHeader(ctxt, (SceneCmd*)Lib_PtrSegToVirt(altHeader));
           (entry + 1)->base.code = 0x14;
        }
    }
}

// Scene Command 0x17: Cutscene Data
void Scene_HeaderCommand17(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->csCtx.cutsceneCount = (u8)entry->base.data1;
    ctxt->cutsceneList = (CutsceneEntry*)Lib_PtrSegToVirt((void*)entry->base.data2);
}

// Scene Command 0x1B: Cutscene Actor List
void Scene_HeaderCommand1B(GlobalContext* ctxt, SceneCmd* entry) {
    ActorCutscene_Init(ctxt, (ActorCutscene*)Lib_PtrSegToVirt((void*)entry->cutsceneActorList.segment), entry->cutsceneActorList.num);
}

// Scene Command 0x1C: Mini Maps
void Scene_HeaderCommand1C(GlobalContext* ctxt, SceneCmd* entry) {
    func_80104CF4(ctxt);
    func_8010549C(ctxt, entry->minimapSettings.segment);
}

// Scene Command 0x1D: Undefined
void Scene_HeaderCommand1D(GlobalContext* ctxt, SceneCmd* entry) {

}

// Scene Command 0x1E: Minimap Chests
void Scene_HeaderCommand1E(GlobalContext* ctxt, SceneCmd* entry) {
    func_8010565C(ctxt, entry->minimapChests.num, entry->minimapChests.segment);
}

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_HeaderCommand19.asm")

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_HeaderCommand1A.asm")

GLOBAL_ASM("./asm/non_matchings/z_scene/func_801306A4.asm")

GLOBAL_ASM("./asm/non_matchings/z_scene/Scene_ProcessHeader.asm")

u32 Scene_CreateEntrance(u32 sceneIndex, u32 spawnIndex, u32 offset) {
    return (((sceneIndex << 9) | (spawnIndex << 4)) | offset) & 0xFFFF;
}

GLOBAL_ASM("./asm/non_matchings/z_scene/func_80130784.asm")
