#include <ultra64.h>
#include <global.h>

/*
TODO:
There are a few issues left with this file, but many rely on larger structural project changes.
I am avoiding these in the mean time in order to not break the Ghidra project structures.
We need a header file for just z_scene. Including relevant structs, scene, and object enums.
Needs definition for OBJECT_EXCHANGE_BANK_MAX
The .data, .bss, and .rodata sections are not migrated to this file yet.
*/

s32 Scene_LoadObject(SceneContext* sceneCtxt, s16 id) {
    u32 size;

    sceneCtxt->objects[sceneCtxt->objectCount].id = id;
    size = objectFileTable[id].vromEnd - objectFileTable[id].vromStart;

    if (sceneCtxt) {}

    if (size) {
        DmaMgr_SendRequest0(sceneCtxt->objects[sceneCtxt->objectCount].vramAddr, objectFileTable[id].vromStart, size);
    }

    // TODO: This 0x22 is OBJECT_EXCHANGE_BANK_MAX - 1 in OOT
    if (sceneCtxt->objectCount < 0x22) {
        sceneCtxt->objects[sceneCtxt->objectCount + 1].vramAddr =
            // UB to cast pointer to u32
            (void*)ALIGN16((u32)sceneCtxt->objects[sceneCtxt->objectCount].vramAddr + size);
    }

    sceneCtxt->objectCount++;
    sceneCtxt->spawnedObjectCount = sceneCtxt->objectCount;

    return sceneCtxt->objectCount - 1;
}

void Scene_Init(GlobalContext* ctxt, SceneContext* sceneCtxt) {
    GlobalContext* global = ctxt; // Needs to be a new variable to match (possibly a sub struct?)
    u32 unused;
    u32 spaceSize;
    s32 i;

    if (global->sceneNum == SCENE_CLOCKTOWER || global->sceneNum == SCENE_TOWN || global->sceneNum == SCENE_BACKTOWN || global->sceneNum == SCENE_ICHIBA) {
        spaceSize = 1566720;
    } else if (global->sceneNum == SCENE_MILK_BAR) {
        spaceSize = 1617920;
    } else if (global->sceneNum == SCENE_00KEIKOKU) {
        spaceSize = 1505280;
    } else {
        spaceSize = 1413120;
    }

    sceneCtxt->objectCount = 0;
    sceneCtxt->spawnedObjectCount = 0;
    sceneCtxt->mainKeepIndex = 0;
    sceneCtxt->keepObjectId = 0;

    // TODO: 0x23 is OBJECT_EXCHANGE_BANK_MAX in OOT
    for (i = 0; i < 0x23; i++) sceneCtxt->objects[i].id = 0;

    sceneCtxt->objectVramStart = sceneCtxt->objects[0].vramAddr = THA_AllocEndAlign16(&ctxt->state.heap, spaceSize);
    // UB to cast sceneCtxt->objectVramStart to s32
    sceneCtxt->objectVramEnd = (void*)((u32)sceneCtxt->objectVramStart + spaceSize);
    // TODO: Second argument here is an object enum
    sceneCtxt->mainKeepIndex = Scene_LoadObject(sceneCtxt, 1);
    // TODO: Segment number enum?
    gRspSegmentPhysAddrs[4] = PHYSICAL_TO_VIRTUAL(sceneCtxt->objects[sceneCtxt->mainKeepIndex].vramAddr);
}

void Scene_ReloadUnloadedObjects(SceneContext* sceneCtxt) {
    s32 i;
    SceneObject* status;
    ObjectFileTableEntry* objectFile;
    u32 size;

    status = &sceneCtxt->objects[0];
    for (i = 0; i < sceneCtxt->objectCount; i++) {
        if (status->id < 0) {
            s32 id = -status->id;
            if (status->dmaReq.vromAddr == 0) {
                objectFile = &objectFileTable[id];
                size = objectFile->vromEnd - objectFile->vromStart;

                if (size == 0) {
                    status->id = 0;
                } else {
                    osCreateMesgQueue(&status->loadQueue, &status->loadMsg, 1);
                    DmaMgr_SendRequestImpl(&status->dmaReq, status->vramAddr, objectFile->vromStart,
                                            size, 0, &status->loadQueue, NULL);
                }
            } else if (!osRecvMesg(&status->loadQueue, NULL, OS_MESG_NOBLOCK)) {
                status->id = id;
            }
        }
        status++;
    }
}

s32 Scene_FindSceneObjectIndex(SceneContext* sceneCtxt, s16 objectId) {
    s32 i;
    for(i = 0; i < sceneCtxt->objectCount; i++) {
        if((sceneCtxt->objects[i].id < 0 ? -sceneCtxt->objects[i].id : sceneCtxt->objects[i].id) == objectId) {
            return i;
        }
    }
    return -1;
}

s32 Scene_IsObjectLoaded(SceneContext* actorShape, s32 index) {
    if (actorShape->objects[index].id > 0) {
        return 1;
    } else {
        return 0;
    }
}

void Scene_DmaAllObjects(SceneContext* sceneCtxt) {
    s32 i;
    s32 id;
    u32 vromSize;

    for (i = 0; i < sceneCtxt->objectCount; i++) {
        id = sceneCtxt->objects[i].id;
        vromSize = objectFileTable[id].vromEnd - objectFileTable[id].vromStart;

        if (vromSize == 0) {
            continue;
        }

        DmaMgr_SendRequest0(sceneCtxt->objects[i].vramAddr, objectFileTable[id].vromStart, vromSize);
    }
}

void* func_8012F73C(SceneContext* sceneCtxt, s32 iParm2, s16 id) {
    u32 addr;
    u32 vromSize;
    ObjectFileTableEntry* fileTableEntry;

    sceneCtxt->objects[iParm2].id = -id;
    sceneCtxt->objects[iParm2].dmaReq.vromAddr = 0;

    fileTableEntry = &objectFileTable[id];
    vromSize = fileTableEntry->vromEnd - fileTableEntry->vromStart;
    // TODO: UB to cast void to u32
    addr = ((u32)sceneCtxt->objects[iParm2].vramAddr) + vromSize;
    addr = ALIGN16(addr);
    // UB to cast u32 to pointer
    return (void*)addr;
}

// Scene Command 0x00: Link Spawn List
void Scene_HeaderCommand00(GlobalContext* ctxt, SceneCmd* entry) {
    GlobalContext* global = ctxt; // Needs to be a new variable to match (possibly a sub struct?)
    s32 loadedCount;
    void* objectVramAddr;
    s16 temp16;
    u8 unk20;

    ctxt->linkActorEntry = (ActorEntry*)Lib_PtrSegToVirt(entry->spawnList.segment) +
                    ctxt->setupEntranceList[ctxt->curSpawn].spawn;
    if ( (ctxt->linkActorEntry->params & 0x0F00) >> 8 == 0x0C ||
         (gSaveContext.extra.unk10 == 0x02 && gSaveContext.extra.unk42 == 0x0CFF)
    ) {
        Scene_LoadObject(&ctxt->sceneContext, OBJECT_STK);
        return;
    }

    loadedCount = Scene_LoadObject(&ctxt->sceneContext, OBJECT_LINK_CHILD);
    objectVramAddr = global->sceneContext.objects[global->sceneContext.objectCount].vramAddr;
    ctxt->sceneContext.objectCount = loadedCount;
    ctxt->sceneContext.spawnedObjectCount = loadedCount;
    unk20 = gSaveContext.perm.unk20;
    temp16 = D_801C2730[unk20];
    gActorOverlayTable[0].initInfo->objectId = temp16;
    Scene_LoadObject(&ctxt->sceneContext, temp16);

    ctxt->sceneContext.objects[ctxt->sceneContext.objectCount].vramAddr = objectVramAddr;
}

// Scene Command 0x01: Actor List
void Scene_HeaderCommand01(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->sceneNumActorsToLoad = (u16)entry->actorList.num;
    ctxt->setupActorList = (ActorEntry*)Lib_PtrSegToVirt(entry->actorList.segment);
    ctxt->actorCtx.unkC = (u16)0;
}

// Scene Command 0x02: Cutscene Camera List
void Scene_HeaderCommand02(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->unk18858 = (UNK_PTR)Lib_PtrSegToVirt(entry->csCameraList.segment);
}

// Scene Command 0x03: Collision Header
void Scene_HeaderCommand03(GlobalContext* ctxt, SceneCmd* entry) {
    BgMeshHeader* temp_ret;
    BgMeshHeader* temp_s0;

    temp_ret = (BgMeshHeader*)Lib_PtrSegToVirt(entry->colHeader.segment);
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
    ctxt->numRooms = entry->roomList.num;
    ctxt->roomList = (RoomFileLocation*)Lib_PtrSegToVirt(entry->roomList.segment);
}

// Scene Command 0x06: Entrance List
void Scene_HeaderCommand06(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->setupEntranceList = (EntranceEntry*)Lib_PtrSegToVirt(entry->entranceList.segment);
}

// Scene Command 0x07: Special Files
void Scene_HeaderCommand07(GlobalContext* ctxt, SceneCmd* entry) {
    if (entry->specialFiles.keepObjectId != 0) {
        ctxt->sceneContext.keepObjectId = Scene_LoadObject(&ctxt->sceneContext,
                                                           entry->specialFiles.keepObjectId);
        // TODO: Segment number enum?
        gRspSegmentPhysAddrs[5] =
            PHYSICAL_TO_VIRTUAL(ctxt->sceneContext.objects[ctxt->sceneContext.keepObjectId].vramAddr);
    }

    if (entry->specialFiles.cUpElfMsgNum != 0) {
        ctxt->unk18868 = Play_LoadScene(ctxt, &D_801C2650[entry->specialFiles.cUpElfMsgNum - 1]);
    }
}

// Scene Command 0x08: Room Behavior
void Scene_HeaderCommand08(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.unk3 = entry->roomBehavior.gpFlag1;
    ctxt->roomContext.currRoom.unk2 = entry->roomBehavior.gpFlag2 & 0xFF;
    ctxt->roomContext.currRoom.unk5 = (entry->roomBehavior.gpFlag2 >> 8) & 1;
    ctxt->msgCtx.unk12044 = (entry->roomBehavior.gpFlag2 >> 0xa) & 1;
    ctxt->roomContext.currRoom.enablePosLights = (entry->roomBehavior.gpFlag2 >> 0xb) & 1;
    ctxt->kankyoContext.unkE2 = (entry->roomBehavior.gpFlag2 >> 0xc) & 1;
}

// Scene Command 0x0A: Mesh Header
void Scene_HeaderCommand0A(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->roomContext.currRoom.mesh = (RoomMesh*)Lib_PtrSegToVirt(entry->mesh.segment);
}

// Scene Command 0x0B: Object List
void Scene_HeaderCommand0B(GlobalContext *ctxt, SceneCmd *entry) {
    s32 i, j, k;
    SceneObject* firstObject;
    SceneObject* status;
    SceneObject* status2;
    s16* objectEntry;
    void* nextPtr;

    objectEntry = (s16*)Lib_PtrSegToVirt(entry->objectList.segment);
    k = 0;
    i = ctxt->sceneContext.spawnedObjectCount;
    status = &ctxt->sceneContext.objects[i];
    firstObject = ctxt->sceneContext.objects;

    while (i < ctxt->sceneContext.objectCount) {
        if (status->id != *objectEntry) {
            status2 = &ctxt->sceneContext.objects[i];
            for (j = i; j < ctxt->sceneContext.objectCount; j++) {
                status2->id = 0;
                status2++;
            }
            ctxt->sceneContext.objectCount = i;
            func_800BA6FC(ctxt, &ctxt->actorCtx);

            continue;
        }

        i++;
        k++;
        objectEntry++;
        status++;
    }

    while (k < entry->objectList.num) {
        nextPtr = func_8012F73C(&ctxt->sceneContext, i, *objectEntry);

        // TODO: This 0x22 is OBJECT_EXCHANGE_BANK_MAX - 1 in OOT
        if (i < 0x22) {
            firstObject[i + 1].vramAddr = nextPtr;
        }
        i++;
        k++;
        objectEntry++;
    }

    ctxt->sceneContext.objectCount = i;
}

// Scene Command 0x0C: Light List
void Scene_HeaderCommand0C(GlobalContext* ctxt, SceneCmd* entry) {
    s32 i;
    LightInfo* lightInfo;

    lightInfo = (LightInfo*)Lib_PtrSegToVirt(entry->lightList.segment);
    for (i = 0; i < entry->lightList.num; i++)
    {
        Lights_Insert(ctxt, &ctxt->lightCtx, lightInfo);
        lightInfo++;
    }
}

// Scene Command 0x0D: Path List
void Scene_HeaderCommand0D(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->setupPathList = (void*)Lib_PtrSegToVirt(entry->pathList.segment);
}

// Scene Command 0x0E: Transition Actor List
void Scene_HeaderCommand0E(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->transitionActorCount = entry->transiActorList.num;
    ctxt->transitionActorList = (TransitionActorEntry*)Lib_PtrSegToVirt((void*)entry->transiActorList.segment);
    func_80105818(ctxt, ctxt->transitionActorCount, ctxt->transitionActorList);
}

void func_8012FEBC(GlobalContext* ctxt, u8* nbTransitionActors) {
    *nbTransitionActors = 0;
}

// Scene Command 0x0F: Light Setting List
void Scene_HeaderCommand0F(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->kankyoContext.environmentSettingsCount = entry->lightSettingList.num;
    ctxt->kankyoContext.environmentSettingsList = (void*)Lib_PtrSegToVirt(entry->lightSettingList.segment);
}

s32 func_8012FF10(GlobalContext* ctxt, s32 fileIndex) {
    u32 vromStart = D_801C2660[fileIndex].vromStart;
    u32 fileSize = D_801C2660[fileIndex].vromEnd - vromStart;

    if (fileSize) {
        ctxt->roomContext.unk74 = THA_AllocEndAlign16(&ctxt->state.heap, fileSize);
        return DmaMgr_SendRequest0(ctxt->roomContext.unk74, vromStart, fileSize);
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

// Scene Command 0x10: Time Settings
void Scene_HeaderCommand10(GlobalContext *ctxt, SceneCmd *entry) {
    u32 dayTime;

    if (entry->timeSettings.hour != 0xFF && entry->timeSettings.min != 0xFF) {
        gSaveContext.extra.environmentTime = gSaveContext.perm.time =
            (u16)(((entry->timeSettings.hour + (entry->timeSettings.min / 60.0f)) * 60.0f) / 0.021972656f);
    }

    if (entry->timeSettings.unk6 != 0xFF) {
        ctxt->kankyoContext.unk2 = entry->timeSettings.unk6;
    } else {
        ctxt->kankyoContext.unk2 = 0;
    }

    if (gSaveContext.perm.inv.items[0] == 0xFF) {
        if (ctxt->kankyoContext.unk2 != 0) {
            ctxt->kankyoContext.unk2 = 5;
        }
    }

    if (gSaveContext.extra.unk2b8 == 0) {
        // TODO: Needs REG macro
        gStaticContext->data[0x0F] = ctxt->kankyoContext.unk2;
    }

    dayTime = gSaveContext.perm.time;
    ctxt->kankyoContext.unk4 = -(Math_Sins(dayTime - 0x8000) * 120.0f) * 25.0f;
    dayTime = gSaveContext.perm.time;
    ctxt->kankyoContext.unk8 = (Math_Coss(dayTime - 0x8000) * 120.0f) * 25.0f;
    dayTime = gSaveContext.perm.time;
    ctxt->kankyoContext.unkC = (Math_Coss(dayTime - 0x8000) * 20.0f) * 25.0f;

    if (ctxt->kankyoContext.unk2 == 0 && gSaveContext.perm.cutscene < 0xFFF0) {
        gSaveContext.extra.environmentTime = gSaveContext.perm.time;

        if (gSaveContext.extra.environmentTime >= 0x2AAA && gSaveContext.extra.environmentTime < 0x4555) {
            gSaveContext.extra.environmentTime = 0x3555;
        } else if (gSaveContext.extra.environmentTime >= 0x4555 && gSaveContext.extra.environmentTime < 0x5555) {
            gSaveContext.extra.environmentTime = 0x5555;
        } else if (gSaveContext.extra.environmentTime >= 0xAAAA && gSaveContext.extra.environmentTime < 0xB555) {
            gSaveContext.extra.environmentTime = 0xB555;
        } else if (gSaveContext.extra.environmentTime >= 0xC000 && gSaveContext.extra.environmentTime < 0xCAAA) {
            gSaveContext.extra.environmentTime = 0xCAAA;
        }
    }
}

// Scene Command 0x05: Wind Settings
void Scene_HeaderCommand05(GlobalContext* ctxt, SceneCmd* entry) {
    s8 temp1 = entry->windSettings.west;
    s8 temp2 = entry->windSettings.vertical;
    s8 temp3 = entry->windSettings.south;
    ctxt->kankyoContext.windWest = temp1;
    ctxt->kankyoContext.windVertical = temp2;
    ctxt->kankyoContext.windSouth = temp3;
    ctxt->kankyoContext.windClothIntensity = entry->windSettings.clothIntensity;
}

void Scene_HeaderCommand13(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->setupExitList = (void*)Lib_PtrSegToVirt(entry->exitList.segment);
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
        altHeaderList = (SceneCmd**)Lib_PtrSegToVirt(entry->altHeaders.segment);
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
    ActorCutscene_Init(ctxt, (ActorCutscene*)Lib_PtrSegToVirt(entry->cutsceneActorList.segment),
                                                              entry->cutsceneActorList.num);
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

// Scene Command 0x19: Misc. Settings (Camera & World Map Area)
void Scene_HeaderCommand19(GlobalContext *ctxt, SceneCmd *entry) {
    s16 j;
    s16 i;

    j = 0;
    i = 0;
    while (1) {
        if (scenesPerMapArea[i].scenes[j] == 0xFFFF) {
            i++;
            j=0;

            // 0x0B is sizeof(scenesPerMapArea) / sizeof(SceneIdList) ... but does not match calculated
            if (i == 0x0B) {
                break;
            }
        }

        if (ctxt->sceneNum == scenesPerMapArea[i].scenes[j]) {
            break;
        }

        j++;
    }

    // 0x0B is sizeof(scenesPerMapArea) / sizeof(SceneIdList) ... but does not match calculated
    if (i < 0x0B) {
        // This bitwise OR could be a macro, but all sane looking versions break matching.
        gSaveContext.perm.mapsVisited = (gBitFlags[i] | gSaveContext.perm.mapsVisited) | gSaveContext.perm.mapsVisited;
    }
}

// Scene Command 0x1A: Texture Animations
void Scene_HeaderCommand1A(GlobalContext* ctxt, SceneCmd* entry) {
    ctxt->sceneTextureAnimations = (AnimatedTexture*)Lib_PtrSegToVirt(entry->textureAnimations.segment);
}

void func_801306A4(GlobalContext *ctxt) {
    ctxt->unk1887F = func_801323A0(ctxt->unk1887A) & 0x7F;
}

s32 Scene_ProcessHeader(GlobalContext* ctxt, SceneCmd* header) {
    u32 cmdCode;

    while (1) {
        cmdCode = header->base.code;

        if (cmdCode == 0x14) {
            break;
        }

        if (cmdCode < 0x1F) {
            sceneHeaderFuncTable[cmdCode](ctxt, header);
        }

        header++;
    }

    return 0;
}

u32 Scene_CreateEntrance(u32 sceneIndex, u32 spawnIndex, u32 offset) {
    return (((sceneIndex << 9) | (spawnIndex << 4)) | offset) & 0xFFFF;
}

void func_80130784(u32 spawnIndex) {
    Scene_CreateEntrance(gSaveContext.perm.entranceIndex >> 9, spawnIndex, 0);
}
