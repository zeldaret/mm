#include "global.h"

s32 Object_Spawn(ObjectContext* objectCtx, s16 id) {
    size_t size;

    objectCtx->status[objectCtx->num].id = id;
    size = objectFileTable[id].vromEnd - objectFileTable[id].vromStart;

    if (1) {}

    if (size != 0) {
        DmaMgr_SendRequest0(objectCtx->status[objectCtx->num].segment, objectFileTable[id].vromStart, size);
    }

    if (objectCtx->num < OBJECT_EXCHANGE_BANK_MAX - 1) {
        objectCtx->status[objectCtx->num + 1].segment = ALIGN16((u32)objectCtx->status[objectCtx->num].segment + size);
    }

    objectCtx->num++;
    objectCtx->spawnedObjectCount = objectCtx->num;

    return objectCtx->num - 1;
}

void Object_InitBank(GameState* gameState, ObjectContext* objectCtx) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    s32 pad;
    u32 spaceSize;
    s32 i;

    if (globalCtx->sceneNum == SCENE_CLOCKTOWER || globalCtx->sceneNum == SCENE_TOWN ||
        globalCtx->sceneNum == SCENE_BACKTOWN || globalCtx->sceneNum == SCENE_ICHIBA) {
        spaceSize = OBJECT_SPACE_SIZE_CLOCK_TOWN;
    } else if (globalCtx->sceneNum == SCENE_MILK_BAR) {
        spaceSize = OBJECT_SPACE_SIZE_MILK_BAR;
    } else if (globalCtx->sceneNum == SCENE_00KEIKOKU) {
        spaceSize = OBJECT_SPACE_SIZE_TERMINA_FIELD;
    } else {
        spaceSize = OBJECT_SPACE_SIZE_DEFAULT;
    }

    objectCtx->num = 0;
    objectCtx->spawnedObjectCount = 0;
    objectCtx->mainKeepIndex = 0;
    objectCtx->subKeepIndex = 0;

    // clang-format off
    for (i = 0; i < OBJECT_EXCHANGE_BANK_MAX; i++) { objectCtx->status[i].id = 0; }
    // clang-format on

    objectCtx->spaceStart = objectCtx->status[0].segment = THA_AllocEndAlign16(&gameState->heap, spaceSize);
    objectCtx->spaceEnd = (void*)((u32)objectCtx->spaceStart + spaceSize);
    objectCtx->mainKeepIndex = Object_Spawn(objectCtx, GAMEPLAY_KEEP);

    gSegments[0x04] = PHYSICAL_TO_VIRTUAL(objectCtx->status[objectCtx->mainKeepIndex].segment);
}

void Object_UpdateBank(ObjectContext* objectCtx) {
    s32 i;
    ObjectStatus* status = &objectCtx->status[0];
    RomFile* objectFile;
    size_t size;

    for (i = 0; i < objectCtx->num; i++) {
        if (status->id < 0) {
            s32 id = -status->id;

            if (status->dmaReq.vromAddr == 0) {
                objectFile = &objectFileTable[id];
                size = objectFile->vromEnd - objectFile->vromStart;

                if (size == 0) {
                    status->id = 0;
                } else {
                    osCreateMesgQueue(&status->loadQueue, &status->loadMsg, 1);
                    DmaMgr_SendRequestImpl(&status->dmaReq, status->segment, objectFile->vromStart, size, 0,
                                           &status->loadQueue, NULL);
                }
            } else if (!osRecvMesg(&status->loadQueue, NULL, OS_MESG_NOBLOCK)) {
                status->id = id;
            }
        }

        status++;
    }
}

s32 Object_GetIndex(ObjectContext* objectCtx, s16 objectId) {
    s32 i;

    for (i = 0; i < objectCtx->num; i++) {
        if ((objectCtx->status[i].id < 0 ? -objectCtx->status[i].id : objectCtx->status[i].id) == objectId) {
            return i;
        }
    }

    return -1;
}

s32 Object_IsLoaded(ObjectContext* objectCtx, s32 index) {
    if (objectCtx->status[index].id > 0) {
        return true;
    } else {
        return false;
    }
}

void Object_LoadAll(ObjectContext* objectCtx) {
    s32 i;
    s32 id;
    u32 vromSize;

    for (i = 0; i < objectCtx->num; i++) {
        id = objectCtx->status[i].id;
        vromSize = objectFileTable[id].vromEnd - objectFileTable[id].vromStart;

        if (vromSize == 0) {
            continue;
        }

        DmaMgr_SendRequest0(objectCtx->status[i].segment, objectFileTable[id].vromStart, vromSize);
    }
}

void* func_8012F73C(ObjectContext* objectCtx, s32 iParm2, s16 id) {
    u32 addr;
    u32 vromSize;
    RomFile* fileTableEntry;

    objectCtx->status[iParm2].id = -id;
    objectCtx->status[iParm2].dmaReq.vromAddr = 0;

    fileTableEntry = &objectFileTable[id];
    vromSize = fileTableEntry->vromEnd - fileTableEntry->vromStart;

    // TODO: UB to cast void to u32
    addr = ((u32)objectCtx->status[iParm2].segment) + vromSize;
    addr = ALIGN16(addr);

    return (void*)addr;
}

// SceneTableEntry Header Command 0x00: Spawn List
void Scene_HeaderCmdSpawnList(GlobalContext* globalCtx, SceneCmd* cmd) {
    GlobalContext* globalCtx2 = globalCtx;
    s32 loadedCount;
    void* nextObject;
    s16 playerObjectId;
    u8 playerForm;

    globalCtx->linkActorEntry = (ActorEntry*)Lib_SegmentedToVirtual(cmd->spawnList.segment) +
                                globalCtx->setupEntranceList[globalCtx->curSpawn].spawn;
    if ((globalCtx->linkActorEntry->params & 0x0F00) >> 8 == 0x0C ||
        (gSaveContext.respawnFlag == 0x02 && gSaveContext.respawn[RESTART_MODE_RETURN].playerParams == 0x0CFF)) {
        // Skull Kid Object
        Object_Spawn(&globalCtx->objectCtx, OBJECT_STK);
        return;
    }

    loadedCount = Object_Spawn(&globalCtx->objectCtx, OBJECT_LINK_CHILD);
    nextObject = globalCtx2->objectCtx.status[globalCtx2->objectCtx.num].segment;
    globalCtx->objectCtx.num = loadedCount;
    globalCtx->objectCtx.spawnedObjectCount = loadedCount;
    playerForm = gSaveContext.save.playerForm;
    playerObjectId = gLinkFormObjectIndexes[playerForm];
    gActorOverlayTable[0].initInfo->objectId = playerObjectId;
    Object_Spawn(&globalCtx->objectCtx, playerObjectId);

    globalCtx->objectCtx.status[globalCtx->objectCtx.num].segment = nextObject;
}

// SceneTableEntry Header Command 0x01: Actor List
void Scene_HeaderCmdActorList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->numSetupActors = cmd->actorList.num;
    globalCtx->setupActorList = Lib_SegmentedToVirtual(cmd->actorList.segment);
    globalCtx->actorCtx.unkC = 0;
}

// SceneTableEntry Header Command 0x02: List of cameras for actor cutscenes
void Scene_HeaderCmdActorCutsceneCamList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->csCamData = Lib_SegmentedToVirtual(cmd->csCameraList.segment);
}

// SceneTableEntry Header Command 0x03: Collision Header
void Scene_HeaderCmdColHeader(GlobalContext* globalCtx, SceneCmd* cmd) {
    CollisionHeader* colHeaderTemp;
    CollisionHeader* colHeader;

    colHeaderTemp = Lib_SegmentedToVirtual(cmd->colHeader.segment);
    colHeader = colHeaderTemp;
    colHeader->vtxList = Lib_SegmentedToVirtual(colHeaderTemp->vtxList);
    colHeader->polyList = Lib_SegmentedToVirtual(colHeader->polyList);

    if (colHeader->surfaceTypeList != NULL) {
        colHeader->surfaceTypeList = Lib_SegmentedToVirtual(colHeader->surfaceTypeList);
    }

    if (colHeader->cameraDataList != NULL) {
        colHeader->cameraDataList = Lib_SegmentedToVirtual(colHeader->cameraDataList);
    }

    if (colHeader->waterBoxes != NULL) {
        colHeader->waterBoxes = Lib_SegmentedToVirtual(colHeader->waterBoxes);
    }

    BgCheck_Allocate(&globalCtx->colCtx, globalCtx, colHeader);
}

// SceneTableEntry Header Command 0x04: Room List
void Scene_HeaderCmdRoomList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->numRooms = cmd->roomList.num;
    globalCtx->roomList = Lib_SegmentedToVirtual(cmd->roomList.segment);
}

// SceneTableEntry Header Command 0x06: Entrance List
void Scene_HeaderCmdEntranceList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->setupEntranceList = Lib_SegmentedToVirtual(cmd->entranceList.segment);
}

// SceneTableEntry Header Command 0x07: Special Files
void Scene_HeaderCmdSpecialFiles(GlobalContext* globalCtx, SceneCmd* cmd) {
    static RomFile tatlMessageFiles[2] = {
        { SEGMENT_ROM_START(elf_message_field), SEGMENT_ROM_END(elf_message_field) },
        { SEGMENT_ROM_START(elf_message_ydan), SEGMENT_ROM_END(elf_message_ydan) },
    };

    if (cmd->specialFiles.subKeepIndex != 0) {
        globalCtx->objectCtx.subKeepIndex = Object_Spawn(&globalCtx->objectCtx, cmd->specialFiles.subKeepIndex);
        // TODO: Segment number enum?
        gSegments[0x05] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[globalCtx->objectCtx.subKeepIndex].segment);
    }

    if (cmd->specialFiles.cUpElfMsgNum != 0) {
        globalCtx->unk_18868 = Play_LoadScene(globalCtx, &tatlMessageFiles[cmd->specialFiles.cUpElfMsgNum - 1]);
    }
}

// SceneTableEntry Header Command 0x08: Room Behavior
void Scene_HeaderCmdRoomBehavior(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->roomCtx.currRoom.unk3 = cmd->roomBehavior.gpFlag1;
    globalCtx->roomCtx.currRoom.unk2 = cmd->roomBehavior.gpFlag2 & 0xFF;
    globalCtx->roomCtx.currRoom.unk5 = (cmd->roomBehavior.gpFlag2 >> 8) & 1;
    globalCtx->msgCtx.unk12044 = (cmd->roomBehavior.gpFlag2 >> 0xa) & 1;
    globalCtx->roomCtx.currRoom.enablePosLights = (cmd->roomBehavior.gpFlag2 >> 0xb) & 1;
    globalCtx->envCtx.unk_E2 = (cmd->roomBehavior.gpFlag2 >> 0xc) & 1;
}

// SceneTableEntry Header Command 0x0A: Mesh Header
void Scene_HeaderCmdMesh(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->roomCtx.currRoom.mesh = Lib_SegmentedToVirtual(cmd->mesh.segment);
}

// SceneTableEntry Header Command 0x0B:  Object List
void Scene_HeaderCmdObjectList(GlobalContext* globalCtx, SceneCmd* cmd) {
    s32 i;
    s32 j;
    s32 k;
    ObjectStatus* firstObject;
    ObjectStatus* status;
    ObjectStatus* status2;
    s16* objectEntry;
    void* nextPtr;

    objectEntry = Lib_SegmentedToVirtual(cmd->objectList.segment);
    k = 0;
    i = globalCtx->objectCtx.spawnedObjectCount;
    status = &globalCtx->objectCtx.status[i];
    firstObject = globalCtx->objectCtx.status;

    while (i < globalCtx->objectCtx.num) {
        if (status->id != *objectEntry) {
            status2 = &globalCtx->objectCtx.status[i];

            for (j = i; j < globalCtx->objectCtx.num; j++) {
                status2->id = 0;
                status2++;
            }

            globalCtx->objectCtx.num = i;
            func_800BA6FC(globalCtx, &globalCtx->actorCtx);

            continue;
        }

        i++;
        k++;
        objectEntry++;
        status++;
    }

    while (k < cmd->objectList.num) {
        nextPtr = func_8012F73C(&globalCtx->objectCtx, i, *objectEntry);

        if (i < OBJECT_EXCHANGE_BANK_MAX - 1) {
            firstObject[i + 1].segment = nextPtr;
        }

        i++;
        k++;
        objectEntry++;
    }

    globalCtx->objectCtx.num = i;
}

// SceneTableEntry Header Command 0x0C: Light List
void Scene_HeaderCmdLightList(GlobalContext* globalCtx, SceneCmd* cmd) {
    s32 i;
    LightInfo* lightInfo = Lib_SegmentedToVirtual(cmd->lightList.segment);

    for (i = 0; i < cmd->lightList.num; i++) {
        LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, lightInfo);
        lightInfo++;
    }
}

// SceneTableEntry Header Command 0x0D: Path List
void Scene_HeaderCmdPathList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->setupPathList = Lib_SegmentedToVirtual(cmd->pathList.segment);
}

// SceneTableEntry Header Command 0x0E: Transition Actor List
void Scene_HeaderCmdTransiActorList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->doorCtx.numTransitionActors = cmd->transiActorList.num;
    globalCtx->doorCtx.transitionActorList = Lib_SegmentedToVirtual(cmd->transiActorList.segment);
    func_80105818(globalCtx, globalCtx->doorCtx.numTransitionActors, globalCtx->doorCtx.transitionActorList);
}

// Init function for the transition system.
void Door_InitContext(GameState* state, DoorContext* doorCtx) {
    doorCtx->numTransitionActors = 0;
}

// SceneTableEntry Header Command 0x0F: Environment Light Settings List
void Scene_HeaderCmdEnvLightSettings(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->envCtx.numLightSettings = cmd->lightSettingList.num;
    globalCtx->envCtx.lightSettingsList = Lib_SegmentedToVirtual(cmd->lightSettingList.segment);
}

/**
 * Loads different texture files for each region of the world.
 * These later are stored in segment 0x06, and used in maps.
 */
s32 Scene_LoadAreaTextures(GlobalContext* globalCtx, s32 fileIndex) {
    static RomFile sceneTextureFiles[9] = {
        { 0, 0 }, // Default
        { SEGMENT_ROM_START(scene_texture_01), SEGMENT_ROM_END(scene_texture_01) },
        { SEGMENT_ROM_START(scene_texture_02), SEGMENT_ROM_END(scene_texture_02) },
        { SEGMENT_ROM_START(scene_texture_03), SEGMENT_ROM_END(scene_texture_03) },
        { SEGMENT_ROM_START(scene_texture_04), SEGMENT_ROM_END(scene_texture_04) },
        { SEGMENT_ROM_START(scene_texture_05), SEGMENT_ROM_END(scene_texture_05) },
        { SEGMENT_ROM_START(scene_texture_06), SEGMENT_ROM_END(scene_texture_06) },
        { SEGMENT_ROM_START(scene_texture_07), SEGMENT_ROM_END(scene_texture_07) },
        { SEGMENT_ROM_START(scene_texture_08), SEGMENT_ROM_END(scene_texture_08) },
    };
    u32 vromStart = sceneTextureFiles[fileIndex].vromStart;
    size_t size = sceneTextureFiles[fileIndex].vromEnd - vromStart;

    if (size != 0) {
        globalCtx->roomCtx.unk74 = THA_AllocEndAlign16(&globalCtx->state.heap, size);
        return DmaMgr_SendRequest0(globalCtx->roomCtx.unk74, vromStart, size);
    }

    // UB: Undefined behaviour to not have a return statement here, but it breaks matching to add one.
}

// SceneTableEntry Header Command 0x11: Skybox Settings
void Scene_HeaderCmdSkyboxSettings(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->skyboxId = cmd->skyboxSettings.skyboxId & 3;
    globalCtx->envCtx.unk_17 = globalCtx->envCtx.unk_18 = cmd->skyboxSettings.unk5;
    globalCtx->envCtx.unk_1E = cmd->skyboxSettings.unk6;
    Scene_LoadAreaTextures(globalCtx, cmd->skyboxSettings.data1);
}

// SceneTableEntry Header Command 0x12: Skybox Disables
void Scene_HeaderCmdSkyboxDisables(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->envCtx.skyboxDisabled = cmd->skyboxDisables.unk4;
    globalCtx->envCtx.sunMoonDisabled = cmd->skyboxDisables.unk5;
}

// SceneTableEntry Header Command 0x10: Time Settings
void Scene_HeaderCmdTimeSettings(GlobalContext* globalCtx, SceneCmd* cmd) {
    u32 dayTime;

    if (cmd->timeSettings.hour != 0xFF && cmd->timeSettings.min != 0xFF) {
        gSaveContext.environmentTime = gSaveContext.save.time =
            (u16)(((cmd->timeSettings.hour + (cmd->timeSettings.min / 60.0f)) * 60.0f) / 0.021972656f);
    }

    if (cmd->timeSettings.unk6 != 0xFF) {
        globalCtx->envCtx.timeIncrement = cmd->timeSettings.unk6;
    } else {
        globalCtx->envCtx.timeIncrement = 0;
    }

    if ((gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) && (globalCtx->envCtx.timeIncrement != 0)) {
        globalCtx->envCtx.timeIncrement = 5;
    }

    if (gSaveContext.sunsSongState == SUNSSONG_INACTIVE) {
        REG(15) = globalCtx->envCtx.timeIncrement;
    }

    dayTime = gSaveContext.save.time;
    globalCtx->envCtx.unk_4 = -(Math_SinS(dayTime - 0x8000) * 120.0f) * 25.0f;
    dayTime = gSaveContext.save.time;
    globalCtx->envCtx.unk_8 = (Math_CosS(dayTime - 0x8000) * 120.0f) * 25.0f;
    dayTime = gSaveContext.save.time;
    globalCtx->envCtx.unk_C = (Math_CosS(dayTime - 0x8000) * 20.0f) * 25.0f;

    if (globalCtx->envCtx.timeIncrement == 0 && gSaveContext.save.cutscene < 0xFFF0) {
        gSaveContext.environmentTime = gSaveContext.save.time;

        if (gSaveContext.environmentTime >= CLOCK_TIME(4, 0) && gSaveContext.environmentTime < CLOCK_TIME(6, 30)) {
            gSaveContext.environmentTime = CLOCK_TIME(5, 0);
        } else if (gSaveContext.environmentTime >= CLOCK_TIME(6, 30) &&
                   gSaveContext.environmentTime < CLOCK_TIME(8, 0)) {
            gSaveContext.environmentTime = CLOCK_TIME(8, 0);
        } else if (gSaveContext.environmentTime >= CLOCK_TIME(16, 0) &&
                   gSaveContext.environmentTime < CLOCK_TIME(17, 0)) {
            gSaveContext.environmentTime = CLOCK_TIME(17, 0);
        } else if (gSaveContext.environmentTime >= CLOCK_TIME(18, 0) &&
                   gSaveContext.environmentTime < CLOCK_TIME(19, 0)) {
            gSaveContext.environmentTime = CLOCK_TIME(19, 0);
        }
    }
}

// SceneTableEntry Header Command 0x05: Wind Settings
void Scene_HeaderCmdWindSettings(GlobalContext* globalCtx, SceneCmd* cmd) {
    s8 temp1 = cmd->windSettings.west;
    s8 temp2 = cmd->windSettings.vertical;
    s8 temp3 = cmd->windSettings.south;

    globalCtx->envCtx.windDir.x = temp1;
    globalCtx->envCtx.windDir.y = temp2;
    globalCtx->envCtx.windDir.z = temp3;
    globalCtx->envCtx.windSpeed = cmd->windSettings.clothIntensity;
}

// SceneTableEntry Header Command 0x13: Exit List
void Scene_HeaderCmdExitList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->setupExitList = Lib_SegmentedToVirtual(cmd->exitList.segment);
}

// SceneTableEntry Header Command 0x09: Undefined
void Scene_HeaderCmd09(GlobalContext* globalCtx, SceneCmd* cmd) {
}

// SceneTableEntry Header Command 0x15: Sound Settings=
void Scene_HeaderCmdSoundSettings(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->soundCtx.seqIndex = cmd->soundSettings.musicSeq;
    globalCtx->soundCtx.nightSeqIndex = cmd->soundSettings.nighttimeSFX;

    if (gSaveContext.seqIndex == (u8)NA_BGM_DISABLED || func_801A8A50(0) == NA_BGM_FINAL_HOURS) {
        audio_setBGM(cmd->soundSettings.bgmId);
    }
}

// SceneTableEntry Header Command 0x16: Echo Setting
void Scene_HeaderCmdEchoSetting(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->roomCtx.currRoom.echo = cmd->echoSettings.echo;
}

// SceneTableEntry Header Command 0x18: Alternate Header List=
void Scene_HeaderCmdAltHeaderList(GlobalContext* globalCtx, SceneCmd* cmd) {
    SceneCmd** altHeaderList;
    SceneCmd* altHeader;

    if (gSaveContext.sceneSetupIndex) {
        altHeaderList = Lib_SegmentedToVirtual(cmd->altHeaders.segment);
        altHeader = altHeaderList[gSaveContext.sceneSetupIndex - 1];

        if (altHeader != NULL) {
            Scene_ProcessHeader(globalCtx, Lib_SegmentedToVirtual(altHeader));
            (cmd + 1)->base.code = 0x14;
        }
    }
}

// SceneTableEntry Header Command 0x17: Cutscene List
void Scene_HeaderCmdCutsceneList(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->csCtx.sceneCsCount = cmd->base.data1;
    globalCtx->csCtx.sceneCsList = Lib_SegmentedToVirtual(cmd->base.data2);
}

// SceneTableEntry Header Command 0x1B: Actor Cutscene List
void Scene_HeaderCmdActorCutsceneList(GlobalContext* globalCtx, SceneCmd* cmd) {
    ActorCutscene_Init(globalCtx, Lib_SegmentedToVirtual(cmd->cutsceneActorList.segment), cmd->cutsceneActorList.num);
}

// SceneTableEntry Header Command 0x1C: Mini Maps
void Scene_HeaderCmdMiniMap(GlobalContext* globalCtx, SceneCmd* cmd) {
    func_80104CF4(globalCtx);
    func_8010549C(globalCtx, cmd->minimapSettings.segment);
}

// SceneTableEntry Header Command 0x1D: Undefined
void Scene_HeaderCmd1D(GlobalContext* globalCtx, SceneCmd* cmd) {
}

// SceneTableEntry Header Command 0x1E: Minimap Compass Icon Info
void Scene_HeaderCmdMiniMapCompassInfo(GlobalContext* globalCtx, SceneCmd* cmd) {
    func_8010565C(globalCtx, cmd->minimapChests.num, cmd->minimapChests.segment);
}

// SceneTableEntry Header Command 0x1A: Sets Area Visited Flag
void Scene_HeaderCmdSetAreaVisitedFlag(GlobalContext* globalCtx, SceneCmd* cmd) {
    s16 j = 0;
    s16 i = 0;

    while (true) {
        if (gScenesPerRegion[i][j] == 0xFFFF) {
            i++;
            j = 0;

            if (i == ARRAY_COUNT(gScenesPerRegion)) {
                break;
            }
        }

        if (globalCtx->sceneNum == gScenesPerRegion[i][j]) {
            break;
        }

        j++;
    }

    if (i < ARRAY_COUNT(gScenesPerRegion)) {
        gSaveContext.save.mapsVisited = (gBitFlags[i] | gSaveContext.save.mapsVisited) | gSaveContext.save.mapsVisited;
    }
}

// SceneTableEntry Header Command 0x1A: Material Animations
void Scene_HeaderCmdAnimatedMaterials(GlobalContext* globalCtx, SceneCmd* cmd) {
    globalCtx->sceneMaterialAnims = (AnimatedMaterial*)Lib_SegmentedToVirtual(cmd->textureAnimations.segment);
}

/**
 * Sets the exit fade from the next entrance index.
 */
void Scene_SetExitFade(GlobalContext* globalCtx) {
    globalCtx->unk_1887F = Entrance_GetTransitionFlags(globalCtx->nextEntranceIndex) & 0x7F;
}

/**
 * Executes all of the commands in a scene or room header.
 */
s32 Scene_ProcessHeader(GlobalContext* globalCtx, SceneCmd* header) {
    static void (*sceneCmdHandlers[])(GlobalContext*, SceneCmd*) = {
        Scene_HeaderCmdSpawnList,
        Scene_HeaderCmdActorList,
        Scene_HeaderCmdActorCutsceneCamList,
        Scene_HeaderCmdColHeader,
        Scene_HeaderCmdRoomList,
        Scene_HeaderCmdWindSettings,
        Scene_HeaderCmdEntranceList,
        Scene_HeaderCmdSpecialFiles,
        Scene_HeaderCmdRoomBehavior,
        Scene_HeaderCmd09,
        Scene_HeaderCmdMesh,
        Scene_HeaderCmdObjectList,
        Scene_HeaderCmdLightList,
        Scene_HeaderCmdPathList,
        Scene_HeaderCmdTransiActorList,
        Scene_HeaderCmdEnvLightSettings,
        Scene_HeaderCmdTimeSettings,
        Scene_HeaderCmdSkyboxSettings,
        Scene_HeaderCmdSkyboxDisables,
        Scene_HeaderCmdExitList,
        NULL,
        Scene_HeaderCmdSoundSettings,
        Scene_HeaderCmdEchoSetting,
        Scene_HeaderCmdCutsceneList,
        Scene_HeaderCmdAltHeaderList,
        Scene_HeaderCmdSetAreaVisitedFlag,
        Scene_HeaderCmdAnimatedMaterials,
        Scene_HeaderCmdActorCutsceneList,
        Scene_HeaderCmdMiniMap,
        Scene_HeaderCmd1D,
        Scene_HeaderCmdMiniMapCompassInfo,
    };
    u32 cmdId;

    while (true) {
        cmdId = header->base.code;

        if (cmdId == SCENE_CMD_ID_END) {
            break;
        }

        if (cmdId < SCENE_CMD_MAX) {
            sceneCmdHandlers[cmdId](globalCtx, header);
        }

        header++;
    }

    return 0;
}

/**
 * Creates an entrance index from the scene index, spawn index, and scene setup.
 */
u16 Entrance_CreateIndex(s32 sceneIndex, s32 spawnIndex, s32 sceneSetup) {
    return (((sceneIndex << 9) | (spawnIndex << 4)) | sceneSetup) & 0xFFFF;
}

/**
 * Creates an entrance index from the current entrance index with the given spawn index.
 */
u16 Entrance_CreateIndexFromSpawn(s32 spawnIndex) {
    return Entrance_CreateIndex(gSaveContext.save.entranceIndex >> 9, spawnIndex, 0);
}
