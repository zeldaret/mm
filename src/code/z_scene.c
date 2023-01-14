#include "global.h"

s32 Object_Spawn(ObjectContext* objectCtx, s16 id) {
    size_t size;

    objectCtx->status[objectCtx->num].id = id;
    size = gObjectTable[id].vromEnd - gObjectTable[id].vromStart;

    if (1) {}

    if (size != 0) {
        DmaMgr_SendRequest0(objectCtx->status[objectCtx->num].segment, gObjectTable[id].vromStart, size);
    }

    if (objectCtx->num < OBJECT_EXCHANGE_BANK_MAX - 1) {
        objectCtx->status[objectCtx->num + 1].segment = ALIGN16((u32)objectCtx->status[objectCtx->num].segment + size);
    }

    objectCtx->num++;
    objectCtx->spawnedObjectCount = objectCtx->num;

    return objectCtx->num - 1;
}

void Object_InitBank(GameState* gameState, ObjectContext* objectCtx) {
    PlayState* play = (PlayState*)gameState;
    s32 pad;
    u32 spaceSize;
    s32 i;

    if (play->sceneId == SCENE_CLOCKTOWER || play->sceneId == SCENE_TOWN || play->sceneId == SCENE_BACKTOWN ||
        play->sceneId == SCENE_ICHIBA) {
        spaceSize = OBJECT_SPACE_SIZE_CLOCK_TOWN;
    } else if (play->sceneId == SCENE_MILK_BAR) {
        spaceSize = OBJECT_SPACE_SIZE_MILK_BAR;
    } else if (play->sceneId == SCENE_00KEIKOKU) {
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

    gSegments[0x04] = VIRTUAL_TO_PHYSICAL(objectCtx->status[objectCtx->mainKeepIndex].segment);
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
                objectFile = &gObjectTable[id];
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
    uintptr_t vromSize;

    for (i = 0; i < objectCtx->num; i++) {
        id = objectCtx->status[i].id;
        vromSize = gObjectTable[id].vromEnd - gObjectTable[id].vromStart;

        if (vromSize == 0) {
            continue;
        }

        DmaMgr_SendRequest0(objectCtx->status[i].segment, gObjectTable[id].vromStart, vromSize);
    }
}

void* func_8012F73C(ObjectContext* objectCtx, s32 iParm2, s16 id) {
    u32 addr;
    uintptr_t vromSize;
    RomFile* fileTableEntry;

    objectCtx->status[iParm2].id = -id;
    objectCtx->status[iParm2].dmaReq.vromAddr = 0;

    fileTableEntry = &gObjectTable[id];
    vromSize = fileTableEntry->vromEnd - fileTableEntry->vromStart;

    // TODO: UB to cast void to u32
    addr = ((u32)objectCtx->status[iParm2].segment) + vromSize;
    addr = ALIGN16(addr);

    return (void*)addr;
}

// SceneTableEntry Header Command 0x00: Spawn List
void Scene_HeaderCmdSpawnList(PlayState* play, SceneCmd* cmd) {
    s32 loadedCount;
    s16 playerObjectId;
    void* nextObject;

    play->linkActorEntry =
        (ActorEntry*)Lib_SegmentedToVirtual(cmd->spawnList.segment) + play->setupEntranceList[play->curSpawn].spawn;
    if ((PLAYER_GET_INITMODE(play->linkActorEntry) == PLAYER_INITMODE_TELESCOPE) ||
        ((gSaveContext.respawnFlag == 2) &&
         (gSaveContext.respawn[RESPAWN_MODE_RETURN].playerParams == PLAYER_PARAMS(0xFF, PLAYER_INITMODE_TELESCOPE)))) {
        // Skull Kid Object
        Object_Spawn(&play->objectCtx, OBJECT_STK);
        return;
    }

    loadedCount = Object_Spawn(&play->objectCtx, OBJECT_LINK_CHILD);
    nextObject = play->objectCtx.status[play->objectCtx.num].segment;
    play->objectCtx.num = loadedCount;
    play->objectCtx.spawnedObjectCount = loadedCount;
    playerObjectId = gPlayerFormObjectIndices[GET_PLAYER_FORM];
    gActorOverlayTable[0].initInfo->objectId = playerObjectId;
    Object_Spawn(&play->objectCtx, playerObjectId);

    play->objectCtx.status[play->objectCtx.num].segment = nextObject;
}

// SceneTableEntry Header Command 0x01: Actor List
void Scene_HeaderCmdActorList(PlayState* play, SceneCmd* cmd) {
    play->numSetupActors = cmd->actorList.num;
    play->setupActorList = Lib_SegmentedToVirtual(cmd->actorList.segment);
    play->actorCtx.halfDaysBit = 0;
}

// SceneTableEntry Header Command 0x02: List of camera data for actor cutscenes
void Scene_HeaderCmdActorCutsceneCamList(PlayState* play, SceneCmd* cmd) {
    play->actorCsCamList = Lib_SegmentedToVirtual(cmd->actorCsCamList.segment);
}

// SceneTableEntry Header Command 0x03: Collision Header
void Scene_HeaderCmdColHeader(PlayState* play, SceneCmd* cmd) {
    CollisionHeader* colHeaderTemp;
    CollisionHeader* colHeader;

    colHeaderTemp = Lib_SegmentedToVirtual(cmd->colHeader.segment);
    colHeader = colHeaderTemp;
    colHeader->vtxList = Lib_SegmentedToVirtual(colHeaderTemp->vtxList);
    colHeader->polyList = Lib_SegmentedToVirtual(colHeader->polyList);

    if (colHeader->surfaceTypeList != NULL) {
        colHeader->surfaceTypeList = Lib_SegmentedToVirtual(colHeader->surfaceTypeList);
    }

    if (colHeader->bgCamList != NULL) {
        colHeader->bgCamList = Lib_SegmentedToVirtual(colHeader->bgCamList);
    }

    if (colHeader->waterBoxes != NULL) {
        colHeader->waterBoxes = Lib_SegmentedToVirtual(colHeader->waterBoxes);
    }

    BgCheck_Allocate(&play->colCtx, play, colHeader);
}

// SceneTableEntry Header Command 0x04: Room List
void Scene_HeaderCmdRoomList(PlayState* play, SceneCmd* cmd) {
    play->numRooms = cmd->roomList.num;
    play->roomList = Lib_SegmentedToVirtual(cmd->roomList.segment);
}

// SceneTableEntry Header Command 0x06: Entrance List
void Scene_HeaderCmdEntranceList(PlayState* play, SceneCmd* cmd) {
    play->setupEntranceList = Lib_SegmentedToVirtual(cmd->entranceList.segment);
}

// SceneTableEntry Header Command 0x07: Special Files
void Scene_HeaderCmdSpecialFiles(PlayState* play, SceneCmd* cmd) {
    // @note These quest hint files are identical to OoT's.
    // They are not relevant in this game and the system to process these scripts has been removed.
    static RomFile naviQuestHintFiles[2] = {
        { SEGMENT_ROM_START(elf_message_field), SEGMENT_ROM_END(elf_message_field) },
        { SEGMENT_ROM_START(elf_message_ydan), SEGMENT_ROM_END(elf_message_ydan) },
    };

    if (cmd->specialFiles.subKeepIndex != 0) {
        play->objectCtx.subKeepIndex = Object_Spawn(&play->objectCtx, cmd->specialFiles.subKeepIndex);
        // TODO: Segment number enum?
        gSegments[0x05] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[play->objectCtx.subKeepIndex].segment);
    }

    if (cmd->specialFiles.naviQuestHintFileId != NAVI_QUEST_HINTS_NONE) {
        play->naviQuestHints = Play_LoadFile(play, &naviQuestHintFiles[cmd->specialFiles.naviQuestHintFileId - 1]);
    }
}

// SceneTableEntry Header Command 0x08: Room Behavior
void Scene_HeaderCmdRoomBehavior(PlayState* play, SceneCmd* cmd) {
    play->roomCtx.curRoom.unk3 = cmd->roomBehavior.gpFlag1;
    play->roomCtx.curRoom.unk2 = cmd->roomBehavior.gpFlag2 & 0xFF;
    play->roomCtx.curRoom.unk5 = (cmd->roomBehavior.gpFlag2 >> 8) & 1;
    play->msgCtx.unk12044 = (cmd->roomBehavior.gpFlag2 >> 0xA) & 1;
    play->roomCtx.curRoom.enablePosLights = (cmd->roomBehavior.gpFlag2 >> 0xB) & 1;
    play->envCtx.unk_E2 = (cmd->roomBehavior.gpFlag2 >> 0xC) & 1;
}

// SceneTableEntry Header Command 0x0A: Mesh Header
void Scene_HeaderCmdMesh(PlayState* play, SceneCmd* cmd) {
    play->roomCtx.curRoom.mesh = Lib_SegmentedToVirtual(cmd->mesh.segment);
}

// SceneTableEntry Header Command 0x0B:  Object List
void Scene_HeaderCmdObjectList(PlayState* play, SceneCmd* cmd) {
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
    i = play->objectCtx.spawnedObjectCount;
    status = &play->objectCtx.status[i];
    firstObject = play->objectCtx.status;

    while (i < play->objectCtx.num) {
        if (status->id != *objectEntry) {
            status2 = &play->objectCtx.status[i];

            for (j = i; j < play->objectCtx.num; j++) {
                status2->id = 0;
                status2++;
            }

            play->objectCtx.num = i;
            Actor_KillAllWithMissingObject(play, &play->actorCtx);

            continue;
        }

        i++;
        k++;
        objectEntry++;
        status++;
    }

    while (k < cmd->objectList.num) {
        nextPtr = func_8012F73C(&play->objectCtx, i, *objectEntry);

        if (i < OBJECT_EXCHANGE_BANK_MAX - 1) {
            firstObject[i + 1].segment = nextPtr;
        }

        i++;
        k++;
        objectEntry++;
    }

    play->objectCtx.num = i;
}

// SceneTableEntry Header Command 0x0C: Light List
void Scene_HeaderCmdLightList(PlayState* play, SceneCmd* cmd) {
    s32 i;
    LightInfo* lightInfo = Lib_SegmentedToVirtual(cmd->lightList.segment);

    for (i = 0; i < cmd->lightList.num; i++) {
        LightContext_InsertLight(play, &play->lightCtx, lightInfo);
        lightInfo++;
    }
}

// SceneTableEntry Header Command 0x0D: Path List
void Scene_HeaderCmdPathList(PlayState* play, SceneCmd* cmd) {
    play->setupPathList = Lib_SegmentedToVirtual(cmd->pathList.segment);
}

// SceneTableEntry Header Command 0x0E: Transition Actor List
void Scene_HeaderCmdTransiActorList(PlayState* play, SceneCmd* cmd) {
    play->doorCtx.numTransitionActors = cmd->transiActorList.num;
    play->doorCtx.transitionActorList = Lib_SegmentedToVirtual(cmd->transiActorList.segment);
    func_80105818(play, play->doorCtx.numTransitionActors, play->doorCtx.transitionActorList);
}

// Init function for the transition system.
void Door_InitContext(GameState* state, DoorContext* doorCtx) {
    doorCtx->numTransitionActors = 0;
}

// SceneTableEntry Header Command 0x0F: Environment Light Settings List
void Scene_HeaderCmdEnvLightSettings(PlayState* play, SceneCmd* cmd) {
    play->envCtx.numLightSettings = cmd->lightSettingList.num;
    play->envCtx.lightSettingsList = Lib_SegmentedToVirtual(cmd->lightSettingList.segment);
}

/**
 * Loads different texture files for each region of the world.
 * These later are stored in segment 0x06, and used in maps.
 */
void Scene_LoadAreaTextures(PlayState* play, s32 fileIndex) {
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
    uintptr_t vromStart = sceneTextureFiles[fileIndex].vromStart;
    size_t size = sceneTextureFiles[fileIndex].vromEnd - vromStart;

    if (size != 0) {
        play->roomCtx.unk74 = THA_AllocEndAlign16(&play->state.heap, size);
        DmaMgr_SendRequest0(play->roomCtx.unk74, vromStart, size);
    }
}

// SceneTableEntry Header Command 0x11: Skybox Settings
void Scene_HeaderCmdSkyboxSettings(PlayState* play, SceneCmd* cmd) {
    play->skyboxId = cmd->skyboxSettings.skyboxId & 3;
    play->envCtx.unk_17 = play->envCtx.unk_18 = cmd->skyboxSettings.unk5;
    play->envCtx.unk_1E = cmd->skyboxSettings.unk6;
    Scene_LoadAreaTextures(play, cmd->skyboxSettings.data1);
}

// SceneTableEntry Header Command 0x12: Skybox Disables
void Scene_HeaderCmdSkyboxDisables(PlayState* play, SceneCmd* cmd) {
    play->envCtx.skyboxDisabled = cmd->skyboxDisables.unk4;
    play->envCtx.sunMoonDisabled = cmd->skyboxDisables.unk5;
}

// SceneTableEntry Header Command 0x10: Time Settings
void Scene_HeaderCmdTimeSettings(PlayState* play, SceneCmd* cmd) {
    if ((cmd->timeSettings.hour != 0xFF) && (cmd->timeSettings.min != 0xFF)) {
        gSaveContext.skyboxTime = gSaveContext.save.time =
            CLOCK_TIME_ALT2_F(cmd->timeSettings.hour, cmd->timeSettings.min);
    }

    if (cmd->timeSettings.timeSpeed != 0xFF) {
        play->envCtx.sceneTimeSpeed = cmd->timeSettings.timeSpeed;
    } else {
        play->envCtx.sceneTimeSpeed = 0;
    }

    // Increase time speed during first cycle
    if ((gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) && (play->envCtx.sceneTimeSpeed != 0)) {
        play->envCtx.sceneTimeSpeed = 5;
    }

    if (gSaveContext.sunsSongState == SUNSSONG_INACTIVE) {
        R_TIME_SPEED = play->envCtx.sceneTimeSpeed;
    }

    play->envCtx.sunPos.x = -(Math_SinS(((void)0, gSaveContext.save.time) - CLOCK_TIME(12, 0)) * 120.0f) * 25.0f;
    play->envCtx.sunPos.y = (Math_CosS(((void)0, gSaveContext.save.time) - CLOCK_TIME(12, 0)) * 120.0f) * 25.0f;
    play->envCtx.sunPos.z = (Math_CosS(((void)0, gSaveContext.save.time) - CLOCK_TIME(12, 0)) * 20.0f) * 25.0f;

    if ((play->envCtx.sceneTimeSpeed == 0) && (gSaveContext.save.cutscene < 0xFFF0)) {
        gSaveContext.skyboxTime = gSaveContext.save.time;

        if ((gSaveContext.skyboxTime >= CLOCK_TIME(4, 0)) && (gSaveContext.skyboxTime < CLOCK_TIME(6, 30))) {
            gSaveContext.skyboxTime = CLOCK_TIME(5, 0);
        } else if ((gSaveContext.skyboxTime >= CLOCK_TIME(6, 30)) && (gSaveContext.skyboxTime < CLOCK_TIME(8, 0))) {
            gSaveContext.skyboxTime = CLOCK_TIME(8, 0);
        } else if ((gSaveContext.skyboxTime >= CLOCK_TIME(16, 0)) && (gSaveContext.skyboxTime < CLOCK_TIME(17, 0))) {
            gSaveContext.skyboxTime = CLOCK_TIME(17, 0);
        } else if ((gSaveContext.skyboxTime >= CLOCK_TIME(18, 0)) && (gSaveContext.skyboxTime < CLOCK_TIME(19, 0))) {
            gSaveContext.skyboxTime = CLOCK_TIME(19, 0);
        }
    }
}

// SceneTableEntry Header Command 0x05: Wind Settings
void Scene_HeaderCmdWindSettings(PlayState* play, SceneCmd* cmd) {
    s8 temp1 = cmd->windSettings.west;
    s8 temp2 = cmd->windSettings.vertical;
    s8 temp3 = cmd->windSettings.south;

    play->envCtx.windDir.x = temp1;
    play->envCtx.windDir.y = temp2;
    play->envCtx.windDir.z = temp3;
    play->envCtx.windSpeed = cmd->windSettings.clothIntensity;
}

// SceneTableEntry Header Command 0x13: Exit List
void Scene_HeaderCmdExitList(PlayState* play, SceneCmd* cmd) {
    play->setupExitList = Lib_SegmentedToVirtual(cmd->exitList.segment);
}

// SceneTableEntry Header Command 0x09: Undefined
void Scene_HeaderCmd09(PlayState* play, SceneCmd* cmd) {
}

// SceneTableEntry Header Command 0x15: Sound Settings=
void Scene_HeaderCmdSoundSettings(PlayState* play, SceneCmd* cmd) {
    play->sequenceCtx.seqId = cmd->soundSettings.seqId;
    play->sequenceCtx.ambienceId = cmd->soundSettings.ambienceId;

    if (gSaveContext.seqId == (u8)NA_BGM_DISABLED ||
        Audio_GetActiveSequence(SEQ_PLAYER_BGM_MAIN) == NA_BGM_FINAL_HOURS) {
        Audio_SetSpec(cmd->soundSettings.specId);
    }
}

// SceneTableEntry Header Command 0x16: Echo Setting
void Scene_HeaderCmdEchoSetting(PlayState* play, SceneCmd* cmd) {
    play->roomCtx.curRoom.echo = cmd->echoSettings.echo;
}

// SceneTableEntry Header Command 0x18: Alternate Header List=
void Scene_HeaderCmdAltHeaderList(PlayState* play, SceneCmd* cmd) {
    SceneCmd** altHeaderList;
    SceneCmd* altHeader;

    if (gSaveContext.sceneLayer != 0) {
        altHeaderList = Lib_SegmentedToVirtual(cmd->altHeaders.segment);
        altHeader = altHeaderList[gSaveContext.sceneLayer - 1];

        if (altHeader != NULL) {
            Scene_ProcessHeader(play, Lib_SegmentedToVirtual(altHeader));
            (cmd + 1)->base.code = 0x14;
        }
    }
}

// SceneTableEntry Header Command 0x17: Cutscene List
void Scene_HeaderCmdCutsceneList(PlayState* play, SceneCmd* cmd) {
    play->csCtx.sceneCsCount = cmd->cutsceneList.sceneCsCount;
    play->csCtx.sceneCsList = Lib_SegmentedToVirtual(cmd->cutsceneList.segment);
}

// SceneTableEntry Header Command 0x1B: Actor Cutscene List
void Scene_HeaderCmdActorCutsceneList(PlayState* play, SceneCmd* cmd) {
    ActorCutscene_Init(play, Lib_SegmentedToVirtual(cmd->cutsceneActorList.segment), cmd->cutsceneActorList.num);
}

// SceneTableEntry Header Command 0x1C: Mini Maps
void Scene_HeaderCmdMiniMap(PlayState* play, SceneCmd* cmd) {
    func_80104CF4(play);
    func_8010549C(play, cmd->minimapSettings.segment);
}

// SceneTableEntry Header Command 0x1D: Undefined
void Scene_HeaderCmd1D(PlayState* play, SceneCmd* cmd) {
}

// SceneTableEntry Header Command 0x1E: Minimap Compass Icon Info
void Scene_HeaderCmdMiniMapCompassInfo(PlayState* play, SceneCmd* cmd) {
    func_8010565C(play, cmd->minimapChests.num, cmd->minimapChests.segment);
}

// SceneTableEntry Header Command 0x19: Sets Region Visited Flag
void Scene_HeaderCmdSetRegionVisitedFlag(PlayState* play, SceneCmd* cmd) {
    s16 j = 0;
    s16 i = 0;

    while (true) {
        if (gSceneIdsPerRegion[i][j] == 0xFFFF) {
            i++;
            j = 0;

            if (i == REGION_MAX) {
                break;
            }
        }

        if (play->sceneId == gSceneIdsPerRegion[i][j]) {
            break;
        }

        j++;
    }

    if (i < REGION_MAX) {
        gSaveContext.save.regionsVisited =
            (gBitFlags[i] | gSaveContext.save.regionsVisited) | gSaveContext.save.regionsVisited;
    }
}

// SceneTableEntry Header Command 0x1A: Material Animations
void Scene_HeaderCmdAnimatedMaterials(PlayState* play, SceneCmd* cmd) {
    play->sceneMaterialAnims = (AnimatedMaterial*)Lib_SegmentedToVirtual(cmd->textureAnimations.segment);
}

/**
 * Sets the exit fade from the next entrance index.
 */
void Scene_SetExitFade(PlayState* play) {
    play->transitionType = Entrance_GetTransitionFlags(play->nextEntrance) & 0x7F;
}

/**
 * Executes all of the commands in a scene or room header.
 */
s32 Scene_ProcessHeader(PlayState* play, SceneCmd* header) {
    static void (*sceneCmdHandlers[])(PlayState*, SceneCmd*) = {
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
        Scene_HeaderCmdSetRegionVisitedFlag,
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
            sceneCmdHandlers[cmdId](play, header);
        }

        header++;
    }

    return 0;
}

/**
 * Creates an entrance from the scene, spawn, and layer.
 */
u16 Entrance_Create(s32 scene, s32 spawn, s32 layer) {
    return (scene << 9) | (spawn << 4) | layer;
}

/**
 * Creates an layer 0 entranace from the current entrance and the given spawn.
 */
u16 Entrance_CreateFromSpawn(s32 spawn) {
    return Entrance_Create((u32)gSaveContext.save.entrance >> 9, spawn, 0);
}
