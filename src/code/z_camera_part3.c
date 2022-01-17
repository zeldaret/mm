#include "global.h"

#define CAM_CHANGE_SET_FLAG_1 (1 << 0)
#define CAM_CHANGE_SET_FLAG_2 (1 << 1)
#define CAM_CHANGE_SET_FLAG_4 (1 << 2)
#define CAM_CHANGE_SET_FLAG_8 (1 << 3)

f32 Camera_fabsf(f32 f);
f32 Camera_Vec3fMagnitude(Vec3f* vec);
f32 Camera_GetRunSpeedLimit(Camera* camera);
s32 func_800CB854(Camera* camera);
s32 func_800CB7CC(Camera* camera);
s32 Camera_IsUsingZoraFins(Camera* camera);
s32 Camera_IsDekuHovering(Camera* camera);
s32 Camera_IsMountedOnHorse(Camera* camera);
s32 Camera_IsSwimming(Camera* camera);

f32 Camera_GetTrackedActorHeight(Camera* camera);
s32 Camera_GetBgCamDataId(Camera* camera, s32* bgId, CollisionPoly* poly);
void Camera_UpdateInterface(s32 flags);
Vec3f* Camera_CalcUpFromPitchYawRoll(Vec3f* dest, s16 pitch, s16 yaw, s16 roll);
s32 Camera_GetWaterBoxCamSetting(Camera* camera, f32* waterY);
void Camera_ResetActionFuncState(Camera* camera, s32 mode);
f32 Camera_GetFloorYNorm(Camera* camera, Vec3f* floorNorm, Vec3f* chkPos, s32* bgId);
s32 Camera_IsDiving(Camera* camera);
s32 Camera_IsPlayerFormZora(Camera* camera);
s32 Camera_IsUnderwaterAsZora(Camera* camera);
s16 Camera_GetCamDataSetting(Camera* camera, u32 camDataId);
void Camera_SetUpdateRatesSlow(Camera* camera);
void Camera_UpdateAtActorOffset(Camera* camera, Vec3f* actorOffset);
s32 func_800CBB88(Camera* camera);


extern CameraSetting sCameraSettings[];
extern GlobalContext* D_801EDC28;
extern s16 sNextUID;
extern s32 sCameraShrinkWindowVal;
extern s32 sCameraInterfaceAlpha;
extern s32 sCameraInterfaceFlags;
extern s16* sGlobalCamDataSettingsPtr;
extern s32 (*sCameraActionFunctions[])(Camera*);
extern s32 sCameraNegOne;
extern s32 sCameraInitSceneTimer;
extern s32 sUpdateCameraDirection;
extern s32 sIsFalse;


/*===============================================================*/
/*                    Camera Public Functions                    */
/*===============================================================*/

Camera* Camera_Create(View* view, CollisionContext* colCtx, GlobalContext* globalCtx) {
    Camera* newCamera = ZeldaArena_Malloc(sizeof(*newCamera));

    if (newCamera != NULL) {
        Camera_Init(newCamera, view, colCtx, globalCtx);
    }
    return newCamera;
}

void Camera_Destroy(Camera* camera) {
    if (camera != NULL) {
        ZeldaArena_Free(camera);
    }
}

void Camera_Init(Camera* camera, View* view, CollisionContext* colCtx, GlobalContext* globalCtx) {
    Camera* cameraPtr;
    s32 i;
    s16 curUID;
    s16 j;

    __osMemset(camera, 0, sizeof(*camera));

    camera->globalCtx = D_801EDC28 = globalCtx;
    curUID = sNextUID;
    sNextUID++;
    while (curUID != 0) {
        if (curUID == 0) {
            sNextUID++;
        }

        for (j = 0; j < NUM_CAMS; j++) {
            cameraPtr = camera->globalCtx->cameraPtrs[j];
            if ((cameraPtr != NULL) && (curUID == cameraPtr->uid)) {
                break;
            }
        }

        if (j == NUM_CAMS) {
            break;
        }

        curUID = sNextUID++;
    }

    camera->inputDir.y = 0x4000;
    camera->uid = curUID;
    camera->camDir = camera->inputDir;
    camera->nextCamSceneDataId = -1;
    camera->up.z = camera->up.x = 0.0f;
    camera->up.y = 1.0f;
    camera->fov = 60.0f;
    camera->yOffsetUpdateRate = 0.05f;
    camera->xzOffsetUpdateRate = 0.05f;
    camera->fovUpdateRate = 0.05f;
    camera->rUpdateRateInv = 10.0f;
    camera->yawUpdateRateInv = 10.0f;
    camera->pitchUpdateRateInv = 16.0f;
    sCameraShrinkWindowVal = 0x20;
    sCameraInterfaceAlpha = 0;
    camera->setting = camera->prevSetting = CAM_SET_FREE0;
    camera->bgCamDataId = camera->prevBgCamDataId = -1;
    camera->flags2 = 0;
    camera->mode = CAM_MODE_NORMAL;
    camera->bgId = BGCHECK_SCENE;
    camera->unk168 = 0xF;
    camera->unk160 = -1;
    camera->trackActor = NULL;
    camera->target = NULL;
    Camera_SetFlags(camera, CAM_FLAG2_4000);
    camera->skyboxOffset.z = camera->skyboxOffset.y = camera->skyboxOffset.x = 0;
    camera->up.z = camera->up.x = 0.0f;
    camera->atLERPStepScale = 1;
    camera->up.y = 1.0f;
    sCameraInterfaceFlags = SHRINKWINVAL_PREV | IFACE_ALPHA(0xF);
    sCameraInitSceneTimer = 3;
}

/**
 * OoT: func_80057FC4
 */
void func_800DDFE0(Camera* camera) {
    if (camera != &camera->globalCtx->mainCamera) {
        camera->prevSetting = camera->setting = CAM_SET_FREE0;
        Camera_UnsetFlags(camera, CAM_FLAG2_4);
    } else {
        switch (camera->globalCtx->roomCtx.currRoom.unk3) {
            case 1:
                camera->prevSetting = CAM_SET_DUNGEON0;
                Camera_ChangeSettingFlags(camera, CAM_SET_DUNGEON0, CAM_CHANGE_SET_FLAG_2);
                break;
            case 0:
                camera->prevSetting = CAM_SET_NORMAL0;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL0, CAM_CHANGE_SET_FLAG_2);
                break;
            case 2:
                camera->prevSetting = CAM_SET_ROOM0;
                Camera_ChangeSettingFlags(camera, CAM_SET_ROOM0, CAM_CHANGE_SET_FLAG_2);
                break;
            default:
                camera->prevSetting = CAM_SET_NORMAL0;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL0, CAM_CHANGE_SET_FLAG_2);
                break;
        }
        Camera_SetFlags(camera, CAM_FLAG2_4);
    }
}

/**
 * Unused empty function
 */
void Camera_Stub800DE0E0(Camera* camera) {
}

void Camera_InitPlayerSettings(Camera* camera, Player* player) {
    PosRot playerPosShape;
    VecSph eyeNextAtOffset;
    s32 bgId;
    Vec3f floorPos;
    s32 upXZ;
    f32 trackHeight;
    Vec3f* eye = &camera->eye;
    s32 pad;

    Actor_GetWorldPosShapeRot(&playerPosShape, &player->actor);
    camera->trackActor = &player->actor;
    trackHeight = Camera_GetTrackedActorHeight(camera);
    camera->trackActorPosRot = playerPosShape;
    camera->dist = eyeNextAtOffset.r = 180.0f;
    camera->inputDir.y = playerPosShape.rot.y;
    eyeNextAtOffset.yaw = BINANG_ROT180(camera->inputDir.y);
    camera->inputDir.x = eyeNextAtOffset.pitch = 0x71C;
    camera->inputDir.z = 0;
    camera->camDir = camera->inputDir;
    camera->xzSpeed = 0.0f;
    camera->trackActorOffset.y = 0.0f;
    camera->at = playerPosShape.pos;
    camera->at.y += trackHeight;

    camera->atActorOffset.x = 0;
    camera->atActorOffset.y = trackHeight;
    camera->atActorOffset.z = 0;

    OLib_VecSphAddToVec3f(&camera->eyeNext, &camera->at, &eyeNextAtOffset);
    *eye = camera->eyeNext;
    camera->roll = 0;

    upXZ = 0;
    camera->up.z = upXZ;
    camera->up.y = 1.0f;
    camera->up.x = upXZ;

    {
        Vec3f* at = &camera->at;

        if (Camera_GetFloorYNorm(camera, &floorPos, at, &bgId) != BGCHECK_Y_MIN) {
            camera->bgId = bgId;
        }
    }

    camera->waterPrevBgCamDataId = -1;
    camera->waterPrevCamSetting = -1;
dummy:;
    camera->waterQuakeId = -1;
    func_800DDFE0(camera);

    Camera_SetFlags(camera, CAM_FLAG2_4);

    camera->paramFlags = 0;
    camera->nextCamSceneDataId = -1;
    camera->yOffsetUpdateRate = 0.01f;
    camera->xzOffsetUpdateRate = 0.01f;
    camera->fovUpdateRate = 0.01f;
    camera->atLERPStepScale = 1;
    Camera_ResetActionFuncState(camera, camera->mode);

    if (camera == &camera->globalCtx->mainCamera) {
        sCameraInterfaceFlags = SHRINKWIN_MAG | SHRINKWINVAL_LARGE | IFACE_ALPHA(2);
        func_800F15D8(camera);
    } else {
        sCameraInterfaceFlags = SHRINKWINVAL_LARGE | IFACE_ALPHA(2);
    }
    Camera_CheckWater(camera);
}

/**
 * Updates the camera status
 */
s32 Camera_ChangeStatus(Camera* camera, s16 status) {
    camera->status = status;
    return camera->status;
}

s32 Camera_CheckWater(Camera* camera) {
    f32 waterY;
    s16 camSetting;
    s32 pad[2];
    s32* waterPrevCamSetting = &camera->waterPrevCamSetting;
    s16 prevBgId;

    if (!(camera->flags2 & CAM_FLAG2_2) || (sCameraSettings[camera->setting].flags & 0x40000000)) {
        return false;
    }

    if (camera->flags2 & CAM_FLAG2_200) {
        if (Camera_IsDiving(camera)) {
            if (!Camera_IsPlayerFormZora(camera)) {
                Camera_ChangeSettingFlags(camera, CAM_SET_PIVOT_DIVING, CAM_CHANGE_SET_FLAG_4 | CAM_CHANGE_SET_FLAG_2);
            } else {
                Camera_ChangeSettingFlags(camera, CAM_SET_ZORA_DIVING, CAM_CHANGE_SET_FLAG_4 | CAM_CHANGE_SET_FLAG_2);
            }
            Camera_SetFlags(camera, CAM_FLAG2_8000);
        } else if (camera->flags2 & (s16)CAM_FLAG2_8000) {
            Camera_ChangeSettingFlags(camera, *waterPrevCamSetting, CAM_CHANGE_SET_FLAG_4 | CAM_CHANGE_SET_FLAG_2);
            Camera_UnsetFlags(camera, CAM_FLAG2_8000);
        }
    }

    if (!(camera->flags2 & (s16)CAM_FLAG2_8000)) {
        camSetting = Camera_GetWaterBoxCamSetting(camera, &waterY);
        if (camSetting == -2) {
            // CAM_SET_NONE
            if (!(camera->flags2 & CAM_FLAG2_200)) {
                Camera_SetFlags(camera, CAM_FLAG2_200);
                camera->waterPrevBgCamDataId = camera->bgCamDataId;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight) < 11.0f) ||
                (Camera_IsSwimming(camera) && !Camera_IsUnderwaterAsZora(camera))) {
                prevBgId = camera->bgId;
                camera->bgId = BGCHECK_SCENE;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL3, CAM_CHANGE_SET_FLAG_2);
                *waterPrevCamSetting = camera->setting;
                camera->bgId = prevBgId;
                camera->bgCamDataId = -2;
            }

        } else if (camSetting != -1) {
            // player is in a water box
            if (!(camera->flags2 & CAM_FLAG2_200)) {
                Camera_SetFlags(camera, CAM_FLAG2_200);
                camera->waterPrevBgCamDataId = camera->bgCamDataId;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight) < 11.0f) ||
                (Camera_IsSwimming(camera) && !Camera_IsUnderwaterAsZora(camera))) {
                prevBgId = camera->bgId;
                camera->bgId = BGCHECK_SCENE;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, camSetting, CAM_CHANGE_SET_FLAG_2);
                *waterPrevCamSetting = camera->setting;
                camera->bgId = prevBgId;
            }

        } else if (camera->flags2 & CAM_FLAG2_200) {
            // player is out of a water box.
            Camera_UnsetFlags(camera, CAM_FLAG2_200);
            prevBgId = camera->bgId;
            camera->bgId = BGCHECK_SCENE;
            if (camera->waterPrevBgCamDataId < 0) {
                func_800DDFE0(camera);
                camera->bgCamDataId = -1;
            } else {
                Camera_ChangeDataIdx(camera, camera->waterPrevBgCamDataId);
            }
            camera->bgId = prevBgId;
        }
        camera->waterYPos = waterY;
    }
    return true;
}

void Camera_EarthquakeDay3(Camera* camera) {
    static s16 earthquakeTimer = 0;
    u16 dayTime;
    s16 quake;
    s32 changeZeldaTime;
    s16 earthquakeFreq[] = {
        0x0FFC, // 1 Large Earthquake  between CLOCK_TIME(0, 00) to CLOCK_TIME(1, 30)
        0x07FC, // 2 Large Earthquakes between CLOCK_TIME(1, 30) to CLOCK_TIME(3, 00)
        0x03FC, // 4 Large Earthquakes between CLOCK_TIME(3, 00) to CLOCK_TIME(4, 30)
        0x01FC, // 8 Large Earthquakes between CLOCK_TIME(4, 30) to CLOCK_TIME(6, 00)
    };

    if ((CURRENT_DAY == 3) && (ActorCutscene_GetCurrentIndex() == -1)) {
        dayTime = gSaveContext.time;
        changeZeldaTime = gSaveContext.unk_14;

        // Large earthquake created
        // Times based on sEarthquakeFreq
        if ((dayTime > CLOCK_TIME(0, 0)) && (dayTime < CLOCK_TIME(6, 0)) &&
            ((earthquakeFreq[dayTime >> 12] & dayTime) == 0) && (Quake_NumActiveQuakes() < 2)) {
            quake = Quake_Add(camera, 4);
            if (quake != 0) {
                Quake_SetSpeed(quake, 30000);
                Quake_SetQuakeValues(quake, (dayTime >> 12) + 2, 1, 5, 60);
                earthquakeTimer = ((dayTime >> 10) - changeZeldaTime) + 80;
                Quake_SetCountdown(quake, earthquakeTimer);
            }
        }

        // Small earthquake created
        // Around CLOCK_TIME(17, 33) || Around CLOCK_TIME(20, 33) || Every 1024 frames (around every 51s)
        if (((((dayTime + 0x4D2) & 0xDFFC) == 0xC000) || ((camera->globalCtx->state.frames % 1024) == 0)) &&
            (Quake_NumActiveQuakes() < 2)) {
            quake = Quake_Add(camera, 3);
            if (quake != 0) {
                Quake_SetSpeed(quake, 16000);
                Quake_SetQuakeValues(quake, 1, 0, 0, dayTime & 0x3F); // %64
                earthquakeTimer = 120 - changeZeldaTime;
                Quake_SetCountdown(quake, earthquakeTimer);
            }
        }

        if (earthquakeTimer != 0) {
            earthquakeTimer--;
            func_8019F128(NA_SE_SY_EARTHQUAKE_OUTDOOR - SFX_FLAG);
        }
    }
}

/**
 * Sets the distortion to type 1 for a hot room
 * Remnant of OoT as no room in any MM scene is set to a hot-room
 */
s32 Camera_SetHotRoomDistortion(Camera* camera) {
    Distortion_ClearType(1);
    if (camera->globalCtx->roomCtx.currRoom.unk2 == 3) {
        Distortion_SetType(1);
    }
    return true;
}

s32 Camera_SetSwordDistortion(Camera* camera) {
    switch (func_800CBB88(camera)) {
        case 1:
            // non-magic spin attack
            if (Distortion_GetType() != 0x40) {
                Distortion_SetType(0x40);
                Distortion_SetCountdown(12);
            }
            break;
        case 2:
            // Unused: case 2 is impossible to achieve
            if (Distortion_GetType() != 0x80) {
                Distortion_SetType(0x80);
                Distortion_SetCountdown(5);
            }
            break;
        case 3:
            if (Distortion_GetType() != 0x100) {
                Distortion_SetType(0x100);
                Distortion_SetCountdown(15);
            }
            break;
    }
    return true;
}

s32 Camera_IsWearingGiantsMask(Camera* camera) {
    Player* player = GET_PLAYER(camera->globalCtx);

    if ((camera->camId == CAM_ID_MAIN) && (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) &&
        (player->currentMask == PLAYER_MASK_GIANT)) {
        Camera_ChangeSettingFlags(camera, CAM_SET_GIANT, CAM_CHANGE_SET_FLAG_2);
        return true;
    } else {
        return false;
    }
}

Vec3s* Camera_Update(Vec3s* inputDir, Camera* camera) {
    Vec3f viewAt;
    Vec3f viewEye;
    Vec3f viewUp;
    Vec3f spA0;
    s32 bgId;
    s32 sp98;
    s32 changeCamSceneDataType;
    CollisionPoly* sp90;
    CollisionPoly* sp8C;
    f32 runSpeedLimit;
    f32 sp84;
    f32 viewFov;
    DynaPolyActor* meshActor;
    PosRot trackActorPosRot;
    QuakeCamCalc quake;
    Actor* trackActor = camera->trackActor;
    VecSph sp3C;
    s16 bgCamDataId;
    f32 playerFloorHeight;

    // Camera of status CUT only updates to this point
    if (camera->status == CAM_STATUS_CUT) {
        *inputDir = camera->inputDir;
        return inputDir;
    }

    sUpdateCameraDirection = false;
    sIsFalse = false;

    if (camera->globalCtx->view.unk164 == 0) {
        if (camera->trackActor != NULL) {
            // Updates camera info on the actor it's tracking

            if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
                Actor_GetWorldPosShapeRot(&trackActorPosRot, camera->trackActor);
            } else {
                Actor_GetWorld(&trackActorPosRot, camera->trackActor);
            }
            camera->trackActorOffset.x = trackActorPosRot.pos.x - camera->trackActorPosRot.pos.x;
            camera->trackActorOffset.y = trackActorPosRot.pos.y - camera->trackActorPosRot.pos.y;
            camera->trackActorOffset.z = trackActorPosRot.pos.z - camera->trackActorPosRot.pos.z;

            // bg related to tracked actor
            sp98 = 0;
            if (Camera_IsMountedOnHorse(camera)) {
                if (((Player*)trackActor)->rideActor->floorPoly != NULL) {
                    sp90 = ((Player*)trackActor)->rideActor->floorPoly;
                    camera->bgId = ((Player*)trackActor)->rideActor->floorBgId;
                    camera->playerFloorHeight = ((Player*)trackActor)->rideActor->floorHeight;
                    sp98 = 3;
                }
            } else if (func_800CB7CC(camera)) {
                if (camera->trackActor->floorPoly != NULL) {
                    sp90 = camera->trackActor->floorPoly;
                    camera->bgId = camera->trackActor->floorBgId;
                    camera->playerFloorHeight = camera->trackActor->floorHeight;
                    sp98 = 1;
                }
            } else {
                spA0 = trackActorPosRot.pos;
                spA0.y += Camera_GetTrackedActorHeight(camera);
                playerFloorHeight = BgCheck_EntityRaycastFloor5_3(camera->globalCtx, &camera->globalCtx->colCtx, &sp90,
                                                                  &bgId, camera->trackActor, &spA0);
                if (playerFloorHeight != BGCHECK_Y_MIN) {
                    camera->bgId = bgId;
                    camera->playerFloorHeight = playerFloorHeight;
                    sp98 = 2;
                }
            }

            if ((sp98 != 0) && (Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight) < 11.0f)) {
                meshActor = DynaPoly_GetActor(&camera->globalCtx->colCtx, camera->bgId);
                if (meshActor != NULL) {
                    camera->floorNorm.x = COLPOLY_GET_NORMAL(sp90->normal.x);
                    camera->floorNorm.y = COLPOLY_GET_NORMAL(sp90->normal.y);
                    camera->floorNorm.z = COLPOLY_GET_NORMAL(sp90->normal.z);
                    camera->trackActorOffset.x -= meshActor->actor.world.pos.x - camera->meshActorPos.x;
                    camera->trackActorOffset.y -= meshActor->actor.world.pos.y - camera->meshActorPos.y;
                    camera->trackActorOffset.z -= meshActor->actor.world.pos.z - camera->meshActorPos.z;
                    camera->meshActorPos = meshActor->actor.world.pos;
                }
            }

            // Set camera speed
            runSpeedLimit = Camera_GetRunSpeedLimit(camera) * 1.5f;
            sp84 = Camera_Vec3fMagnitude(&camera->trackActorOffset);
            camera->xzSpeed = OLib_ClampMaxDist(sp84, runSpeedLimit);
            camera->speedRatio = OLib_ClampMaxDist(sp84 / runSpeedLimit, 1.8f);
            camera->trackActorPosRot = trackActorPosRot;

            if (camera->camId == CAM_ID_MAIN) {
                Camera_CheckWater(camera);
                Camera_SetHotRoomDistortion(camera);
                Camera_EarthquakeDay3(camera);
                Camera_SetSwordDistortion(camera);
            }

            /**
             * This section is about updating the camera setting based on the camera scene data
             *
             */

            // If doorTimer1 is active, set CAM_FLAG2_400 which suppresses bg camera scene data from being read
            if (camera->doorTimer1 != 0) {
                Camera_SetFlags(camera, CAM_FLAG2_400);
            } else if (!(camera->flags2 & CAM_FLAG2_4)) {
                camera->nextCamSceneDataId = -1;
            }

            changeCamSceneDataType = 0; // default to no change in the cam scene data
            bgId = camera->bgId;

            // Sets the next cam scene data Index based on the bg surface
            if ((camera->flags2 & CAM_FLAG2_1) && (camera->flags2 & CAM_FLAG2_4) && !(camera->flags2 & CAM_FLAG2_400) &&
                (!(camera->flags2 & CAM_FLAG2_200) || Camera_IsUnderwaterAsZora(camera)) &&
                !(camera->flags2 & (s16)CAM_FLAG2_8000) && !Camera_IsMountedOnHorse(camera) &&
                !Camera_IsWearingGiantsMask(camera) && !Camera_IsDekuHovering(camera) && (sp98 != 0)) {

                bgCamDataId = Camera_GetBgCamDataId(camera, &bgId, sp90);
                if ((bgCamDataId != -1) && (camera->bgId == BGCHECK_SCENE)) {
                    if (Camera_IsUsingZoraFins(camera) == 0) {
                        camera->nextCamSceneDataId = bgCamDataId | 0x1000;
                    }
                }
                spA0 = trackActorPosRot.pos;
                spA0.y += Camera_GetTrackedActorHeight(camera);
                playerFloorHeight = BgCheck_CameraRaycastFloor2(&camera->globalCtx->colCtx, &sp8C, &bgId, &spA0);
                if ((playerFloorHeight != BGCHECK_Y_MIN) && (sp8C != sp90) && (bgId == BGCHECK_SCENE) &&
                    ((camera->playerFloorHeight - 2.0f) < playerFloorHeight)) {
                    bgCamDataId = Camera_GetBgCamDataId(camera, &bgId, sp8C);
                    if ((bgCamDataId != -1) && (bgId == BGCHECK_SCENE)) {
                        camera->nextCamSceneDataId = bgCamDataId | 0x1000;
                        changeCamSceneDataType = 1; // change cam scene data based on the bg cam data
                    }
                }
            }

            if (camera->doorTimer1 != 0) {
                camera->doorTimer1--;
                if (camera->doorTimer1 == 0) {
                    Camera_UnsetFlags(camera, CAM_FLAG2_400);
                    changeCamSceneDataType = 5; // change cam scene data based on the cutscene cam data
                }
            }

            if (((camera->camId == CAM_ID_MAIN) || (camera->flags2 & CAM_FLAG2_40)) &&
                ((camera->bgId == BGCHECK_SCENE) || ((bgId == BGCHECK_SCENE) && (changeCamSceneDataType != 0))) &&
                (camera->nextCamSceneDataId != -1) && (camera->doorTimer1 == 0) &&
                ((Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight) < 11.0f) ||
                 (changeCamSceneDataType != 0)) &&
                (!(camera->flags2 & CAM_FLAG2_200) || Camera_IsUnderwaterAsZora(camera))) {

                Camera_ChangeDataIdx(camera, camera->nextCamSceneDataId);
                camera->nextCamSceneDataId = -1;
                if (camera->doorTimer2 != 0) {
                    camera->doorTimer1 = camera->doorTimer2;
                    camera->doorTimer2 = 0;
                }
            }
        }

        // Camera of status WAIT only updates to this point
        if (camera->status == CAM_STATUS_WAIT) {
            *inputDir = camera->inputDir;
            return inputDir;
        }

        camera->flags1 = 0;
        Camera_UnsetFlags(camera, CAM_FLAG2_400 | CAM_FLAG2_20);
        Camera_SetFlags(camera, CAM_FLAG2_10);
    }

    // Call the Action Function
    sCameraActionFunctions[sCameraSettings[camera->setting].cameraModes[camera->mode].funcId](camera);

    // Update the interface
    if (sCameraInitSceneTimer != 0) {
        sCameraInitSceneTimer--;
    }
    if (camera->status == CAM_STATUS_ACTIVE) {
        if (((sCameraInitSceneTimer != 0) || func_800CB854(camera)) && (camera->camId == CAM_ID_MAIN)) {
            // Surpresses the interface for the first few frames of a scene
            sCameraInterfaceFlags = SHRINKWINVAL_LARGE | IFACE_ALPHA(2);
            Camera_UpdateInterface(sCameraInterfaceFlags);
        } else if ((camera->globalCtx->unk_18B4A != 0) && (camera->camId != CAM_ID_MAIN)) {
            sCameraInterfaceFlags = SHRINKWINVAL_PREV | IFACE_ALPHA(0xF);
            Camera_UpdateInterface(sCameraInterfaceFlags);
        } else {
            Camera_UpdateInterface(sCameraInterfaceFlags);
        }
    }

    // Camera of status UNK3 only updates to this point
    if (camera->status == CAM_STATUS_UNK3) {
        *inputDir = camera->inputDir;
        return inputDir;
    }

    /**
     * This section is about updating view structs from the active camera,
     * which view uses to calculate the viewing/projection matrices
     */

    // Set view at, eye, fov
    bgId = Quake_Calc(camera, &quake);
    if (bgId != 0) {
        viewAt.x = camera->at.x + quake.atOffset.x;
        viewAt.y = camera->at.y + quake.atOffset.y;
        viewAt.z = camera->at.z + quake.atOffset.z;
        viewEye.x = camera->eye.x + quake.eyeOffset.x;
        viewEye.y = camera->eye.y + quake.eyeOffset.y;
        viewEye.z = camera->eye.z + quake.eyeOffset.z;
        OLib_Vec3fDiffToVecSphGeo(&sp3C, &viewEye, &viewAt);
        Camera_CalcUpFromPitchYawRoll(&viewUp, sp3C.pitch, sp3C.yaw, camera->roll + quake.rollOffset);
        viewFov = camera->fov + BINANG_TO_DEGF(quake.zoom);
    } else if (sIsFalse) {
        //! @bug: Condition is impossible to achieve
        viewAt = camera->at;
        viewEye = camera->eye;
        OLib_Vec3fDiffToVecSphGeo(&sp3C, &viewEye, &viewAt);
        viewUp = camera->up;
        viewFov = camera->fov;
    } else {
        viewAt = camera->at;
        viewEye = camera->eye;
        OLib_Vec3fDiffToVecSphGeo(&sp3C, &viewEye, &viewAt);
        Camera_CalcUpFromPitchYawRoll(&viewUp, sp3C.pitch, sp3C.yaw, camera->roll);
        viewFov = camera->fov;
    }
    // set view up
    if (camera->paramFlags & CAM_PARAM_FLAG_4) {
        camera->paramFlags &= ~CAM_PARAM_FLAG_4;
        viewUp = camera->up;
    } else {
        camera->up = viewUp;
    }

    camera->skyboxOffset = quake.eyeOffset;
    View_SetScale(&camera->globalCtx->view, (OREG(67) * 0.01f) + 1.0f);
    camera->globalCtx->view.fovy = viewFov;
    View_SetViewOrientation(&camera->globalCtx->view, &viewEye, &viewAt, &viewUp);
    camera->camDir.x = sp3C.pitch;
    camera->camDir.y = sp3C.yaw;
    camera->camDir.z = 0;
    if (!sUpdateCameraDirection) {
        camera->inputDir.x = sp3C.pitch;
        camera->inputDir.y = sp3C.yaw;
        camera->inputDir.z = 0;
    }

    *inputDir = camera->inputDir;
    return inputDir;
}

s32 func_800DF498(Camera* camera) {
    Camera_SetFlags(camera, CAM_FLAG2_8 | CAM_FLAG2_4); // CAM_FLAG2_8 is set only immediately to be unset
    Camera_UnsetFlags(camera, CAM_FLAG2_1000 | CAM_FLAG2_8);
    return true;
}

s32 Camera_ChangeModeFlags(Camera* camera, s16 mode, u8 forceChange) {
    static s32 modeChangeFlags = 0;

    if (camera->setting == CAM_SET_TELESCOPE) {
        if ((mode == CAM_MODE_FIRSTPERSON) || (mode == CAM_MODE_DEKUHIDE)) {
            forceChange = true;
        }
    }

    if ((camera->flags2 & CAM_FLAG2_20) && !forceChange) {
        camera->flags1 |= CAM_FLAG1_MODE_2;
        return -1;
    }

    if (!(sCameraSettings[camera->setting].validModes & (1 << mode))) {
        if (camera->mode != CAM_MODE_NORMAL) {
            camera->mode = CAM_MODE_NORMAL;
            Camera_ResetActionFuncState(camera, camera->mode);
            func_800DF498(camera);
            return 0xC0000000 | mode;
        } else {
            camera->flags1 |= CAM_FLAG1_MODE_2;
            camera->flags1 |= CAM_FLAG1_MODE_1;
            return 0;
        }
    } else {
        if ((mode == camera->mode) && !forceChange) {
            camera->flags1 |= CAM_FLAG1_MODE_2;
            return -1;
        }
        camera->flags1 |= CAM_FLAG1_MODE_2;
        camera->flags1 |= CAM_FLAG1_MODE_1;

        Camera_ResetActionFuncState(camera, mode);

        modeChangeFlags = 0;

        switch (mode) {
            case CAM_MODE_FIRSTPERSON:
                modeChangeFlags = 0x20;
                break;
            case CAM_MODE_BATTLE:
                modeChangeFlags = 4;
                break;
            case CAM_MODE_FOLLOWTARGET:
                if (camera->target != NULL && camera->target->id != ACTOR_EN_BOOM) {
                    modeChangeFlags = 8;
                }
                break;
            case CAM_MODE_BOWARROWZ:
            case CAM_MODE_TARGET:
            case CAM_MODE_TALK:
            case CAM_MODE_HANGZ:
            case CAM_MODE_PUSHPULL:
                modeChangeFlags = 2;
                break;
            case CAM_MODE_NORMAL:
            case CAM_MODE_HANG:
                modeChangeFlags = 0x10;
                break;
        }

        switch (camera->mode) {
            case CAM_MODE_FIRSTPERSON:
                if (modeChangeFlags & 0x20) {
                    camera->actionFuncState = 10;
                }
                break;
            case CAM_MODE_JUMP:
            case CAM_MODE_HANG:
                if (modeChangeFlags & 0x10) {
                    camera->actionFuncState = 20;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_CHARGE:
                if (modeChangeFlags & 0x10) {
                    camera->actionFuncState = 20;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_FOLLOWTARGET:
                if (modeChangeFlags & 8) {
                    camera->actionFuncState = 10;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_BATTLE:
                if (modeChangeFlags & 4) {
                    camera->actionFuncState = 10;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_BOWARROWZ:
            case CAM_MODE_HANGZ:
            case CAM_MODE_PUSHPULL:
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_NORMAL:
                if (modeChangeFlags & 0x10) {
                    camera->actionFuncState = 20;
                }
                break;
        }

        modeChangeFlags &= ~0x10;

        if (camera->status == CAM_STATUS_ACTIVE) {
            switch (modeChangeFlags) {
                case 1:
                    play_sound(0);
                    break;
                case 2:
                    if (camera->globalCtx->roomCtx.currRoom.unk3 == 1) {
                        play_sound(NA_SE_SY_ATTENTION_URGENCY);
                    } else {

                        play_sound(NA_SE_SY_ATTENTION_ON);
                    }
                    break;
                case 4:
                    play_sound(NA_SE_SY_ATTENTION_URGENCY);
                    break;
                case 8:
                    play_sound(NA_SE_SY_ATTENTION_ON);
                    break;
            }
        }
        func_800DF498(camera);
        camera->mode = mode;
        return 0x80000000 | mode;
    }
}

s32 Camera_ChangeMode(Camera* camera, s16 mode) {
    return Camera_ChangeModeFlags(camera, mode, false);
}

s32 Camera_CheckValidMode(Camera* camera, s16 mode) {
    if (camera->flags2 & CAM_FLAG2_20) {
        return 0;
    } else if (!(sCameraSettings[camera->setting].validModes & (1 << mode))) {
        return 0;
    } else if (mode == camera->mode) {
        return -1;
    } else {
        return mode | 0x80000000;
    }
}

s16 Camera_ChangeSettingFlags(Camera* camera, s16 setting, s16 flags) {
    if ((camera->flags1 & CAM_FLAG1_SET_USE_PRIORITY) &&
        ((sCameraSettings[camera->setting].flags & 0xF) >= (sCameraSettings[setting].flags & 0xF))) {
        camera->flags1 |= CAM_FLAG1_SET_2;
        if (!(flags & CAM_CHANGE_SET_FLAG_2)) {
            camera->flags1 |= CAM_FLAG1_SET_USE_PRIORITY;
        }
        return -2;
    }

    if (setting == CAM_SET_NONE) {
        return 0;
    }

    if (setting >= CAM_SET_MAX) {
        return -99;
    }

    if ((setting == camera->setting) && !(flags & CAM_CHANGE_SET_FLAG_1)) {
        camera->flags1 |= CAM_FLAG1_SET_2;
        if (!(flags & CAM_CHANGE_SET_FLAG_2)) {
            camera->flags1 |= CAM_FLAG1_SET_USE_PRIORITY;
        }
        return -1;
    }

    camera->flags1 |= CAM_FLAG1_SET_2;

    if (!(flags & CAM_CHANGE_SET_FLAG_2)) {
        camera->flags1 |= CAM_FLAG1_SET_USE_PRIORITY;
    }

    func_800DF498(camera);

    if (!(sCameraSettings[camera->setting].flags & 0x40000000)) {
        camera->prevSetting = camera->setting;
    }

    if (flags & CAM_CHANGE_SET_FLAG_8) {
        camera->bgCamDataId = camera->prevBgCamDataId;
        camera->prevBgCamDataId = -1;
    } else if (!(flags & CAM_CHANGE_SET_FLAG_4)) {
        if (!(sCameraSettings[camera->setting].flags & 0x40000000)) {
            camera->prevBgCamDataId = camera->bgCamDataId;
        }
        camera->bgCamDataId = -1;
    }

    camera->setting = setting;

    if (Camera_ChangeModeFlags(camera, camera->mode, true) >= 0) {
        Camera_ResetActionFuncState(camera, camera->mode);
    }

    return setting;
}

s32 Camera_ChangeSetting(Camera* camera, s16 setting) {
    s32 settingChangeSuccessful = Camera_ChangeSettingFlags(camera, setting, 0);

    if (settingChangeSuccessful >= 0) {
        camera->bgCamDataId = -1;
    }
    return settingChangeSuccessful;
}

s32 Camera_ChangeDataIdx(Camera* camera, s32 bgCamDataId) {
    s16 setting;

    if (bgCamDataId == -1 || bgCamDataId == camera->bgCamDataId) {
        camera->flags1 |= CAM_FLAG1_SCENE_DATA_2;
        return -1;
    }

    if (bgCamDataId < 0) {
        setting = sGlobalCamDataSettingsPtr[bgCamDataId];
    } else if (!(camera->flags1 & CAM_FLAG1_SCENE_DATA_2)) {
        setting = Camera_GetCamDataSetting(camera, bgCamDataId);
    } else {
        return -1;
    }

    camera->flags1 |= CAM_FLAG1_SCENE_DATA_2;
    // Sets camera setting based on bg/scene data
    if ((Camera_ChangeSettingFlags(camera, setting, CAM_CHANGE_SET_FLAG_4 | CAM_CHANGE_SET_FLAG_1) >= 0) ||
        (sCameraSettings[camera->setting].flags & 0x80000000)) {
        camera->bgCamDataId = bgCamDataId;
        camera->flags1 |= CAM_FLAG1_SCENE_DATA_1;
        Camera_ResetActionFuncState(camera, camera->mode);
    }

    return bgCamDataId | 0x80000000;
}

Vec3s* Camera_GetInputDir(Vec3s* dst, Camera* camera) {
    *dst = camera->inputDir;
    return dst;
}

s16 Camera_GetInputDirPitch(Camera* camera) {
    Vec3s dir;

    Camera_GetInputDir(&dir, camera);
    return dir.x;
}

s16 Camera_GetInputDirYaw(Camera* camera) {
    Vec3s dir;

    Camera_GetInputDir(&dir, camera);
    return dir.y;
}

Vec3s* Camera_GetCamDir(Vec3s* dst, Camera* camera) {
    *dst = camera->camDir;
    return dst;
}

s16 Camera_GetCamDirPitch(Camera* camera) {
    Vec3s camDir;

    Camera_GetCamDir(&camDir, camera);
    return camDir.x;
}

s16 Camera_GetCamDirYaw(Camera* camera) {
    Vec3s camDir;

    Camera_GetCamDir(&camDir, camera);
    return camDir.y;
}

s32 Camera_AddQuake(Camera* camera, s32 arg1, s16 y, s32 countdown) {
    s16 quakeIdx = Quake_Add(camera, 3);

    if (quakeIdx == 0) {
        return false;
    }

    Quake_SetSpeed(quakeIdx, 25000);
    Quake_SetQuakeValues(quakeIdx, y, 0, 0, 0);
    Quake_SetCountdown(quakeIdx, countdown);
    return true;
}

s32 Camera_SetParam(Camera* camera, s32 paramFlag, void* value) {
    s32 pad[3];

    if (value != NULL) {
        switch (paramFlag) {
            case CAM_PARAM_FLAG_1:
                camera->paramFlags &= ~(CAM_PARAM_FLAG_10 | CAM_PARAM_FLAG_8 | CAM_PARAM_FLAG_1);
                camera->at = *(Vec3f*)value;
                break;
            case CAM_PARAM_FLAG_10:
                camera->paramFlags &= ~(CAM_PARAM_FLAG_10 | CAM_PARAM_FLAG_8 | CAM_PARAM_FLAG_1);
                camera->targetPosRot.pos = *(Vec3f*)value;
                break;
            case CAM_PARAM_FLAG_8:
                camera->target = (Actor*)value;
                camera->paramFlags &= ~(CAM_PARAM_FLAG_10 | CAM_PARAM_FLAG_8 | CAM_PARAM_FLAG_1);
                break;
            case CAM_PARAM_FLAG_2:
                camera->eye = camera->eyeNext = *(Vec3f*)value;
                break;
            case CAM_PARAM_FLAG_4:
                camera->up = *(Vec3f*)value;
                break;
            case CAM_PARAM_FLAG_40:
                camera->roll = DEGF_TO_BINANG(*(f32*)value);
                break;
            case CAM_PARAM_FLAG_20:
                camera->fov = *(f32*)value;
                break;
            default:
                return false;
        }
        camera->paramFlags |= paramFlag;
    } else {
        return false;
    }
    return true;
}

s32 Camera_UnsetParam(Camera* camera, s16 paramFlags) {
    camera->paramFlags &= ~paramFlags;
    return true;
}

s32 Camera_OverwriteFlags(Camera* camera, s16 flags) {
    camera->flags2 = flags;
    return true;
}

s32 Camera_ResetActionFuncStateUnused(Camera* camera) {
    camera->actionFuncState = 0;
    return true;
}

/**
 * Unused Remnant of OoT
 */
s32 Camera_SetCsParams(Camera* camera, CutsceneCameraPoint* atPoints, CutsceneCameraPoint* eyePoints, Player* player,
                       s16 relativeToPlayer) {
    return true;
}

s16 Camera_SetFlags(Camera* camera, s16 flags) {
    camera->flags2 |= flags;
    return camera->flags2;
}

s16 Camera_UnsetFlags(Camera* camera, s16 flags) {
    camera->flags2 &= ~flags;
    return camera->flags2;
}

s32 Camera_ChangeDoorCam(Camera* camera, Actor* doorActor, s16 bgCamDataId, f32 arg3, s16 timer1, s16 timer2,
                         s16 timer3) {
    DoorParams* doorParams = (DoorParams*)camera->actionFuncHeap;

    if (camera->setting == CAM_SET_DOORC) {
        return 0;
    }

    doorParams->doorActor = doorActor;
    doorParams->timer1 = timer1;
    doorParams->timer2 = timer2;
    doorParams->timer3 = timer3;
    doorParams->bgCamDataId = bgCamDataId;

    if (bgCamDataId == -99) {
        Camera_ResetActionFuncState(camera, camera->mode);
        return -99;
    }

    if (bgCamDataId == -1) {
        Camera_ChangeSettingFlags(camera, CAM_SET_DOORC, 0);
    } else if (bgCamDataId == -2) {
        Camera_ChangeSettingFlags(camera, CAM_SET_SPIRAL_DOOR, 0);
    } else {
        camera->nextCamSceneDataId = bgCamDataId;
        camera->doorTimer1 = timer1;
        camera->doorTimer2 = timer2 + timer3;
    }

    Camera_ResetActionFuncState(camera, camera->mode);
    return -1;
}

s32 Camera_Copy(Camera* dstCam, Camera* srcCam) {
    s32 pad;

    dstCam->atActorOffset.z = 0.0f;
    dstCam->atActorOffset.y = 0.0f;
    dstCam->atActorOffset.x = 0.0f;
    dstCam->atLERPStepScale = 0.1f;
    dstCam->at = srcCam->at;

    dstCam->eye = dstCam->eyeNext = srcCam->eye;

    dstCam->dist = OLib_Vec3fDist(&dstCam->at, &dstCam->eye);
    dstCam->fov = srcCam->fov;
    dstCam->roll = srcCam->roll;
    Camera_SetUpdateRatesSlow(dstCam);

    if (dstCam->trackActor != NULL) {
        if (dstCam->trackActor == &GET_PLAYER(dstCam->globalCtx)->actor) {
            Actor_GetWorldPosShapeRot(&dstCam->trackActorPosRot, dstCam->trackActor);
        } else {
            Actor_GetWorld(&dstCam->trackActorPosRot, dstCam->trackActor);
        }
        Camera_UpdateAtActorOffset(dstCam, &dstCam->trackActorPosRot.pos);
    }
    return true;
}

/**
 * Unused Remnant of OoT/Debug
 */
s32 Camera_GetDbgCamEnabled(void) {
    return 0;
}

Vec3f* Camera_GetSkyboxOffset(Vec3f* dst, Camera* camera) {
    *dst = camera->skyboxOffset;
    return dst;
}

void Camera_SetCameraData(Camera* camera, s16 setDataFlags, void* data0, void* data1, s16 data2, s16 data3) {
    if (setDataFlags & 1) {
        camera->data0 = data0;
    }

    if (setDataFlags & 2) {
        camera->data1 = data1;
    }

    if (setDataFlags & 4) {
        camera->data2 = data2;
    }

    if (setDataFlags & 8) {
        camera->data3 = data3;
    }
}

s32 Camera_GetNegOne(void) {
    return sCameraNegOne;
}

s16 func_800E0238(Camera* camera) {
    Camera_SetFlags(camera, CAM_FLAG2_8);
    if ((camera->camId == CAM_ID_MAIN) && (camera->globalCtx->activeCamera != CAM_ID_MAIN)) {
        Camera_SetFlags(GET_ACTIVE_CAM(camera->globalCtx), CAM_FLAG2_8);
        return camera->globalCtx->activeCamera;
    } else {
        return camera->camId;
    }
}

void Camera_SetToTrackActor(Camera* camera, Actor* actor) {
    camera->trackActor = actor;
    if (actor == &GET_PLAYER(camera->globalCtx)->actor) {
        Actor_GetWorldPosShapeRot(&camera->trackActorPosRot, actor);
    } else {
        Actor_GetWorld(&camera->trackActorPosRot, camera->trackActor);
    }

    camera->actionFuncState = 0;
}

void Camera_SetTargetActor(Camera* camera, Actor* actor) {
    camera->target = actor;
    camera->actionFuncState = 20;
}

f32 Camera_GetWaterYPos(Camera* camera) {
    // if underwater
    if (camera->flags2 & CAM_FLAG2_100) {
        return camera->waterYPos;
    } else {
        return BGCHECK_Y_MIN;
    }
}

void func_800E0348(Camera* camera) {
    if (!RELOAD_PARAMS) {
        camera->actionFuncState = 999;
        Camera_SetFlags(camera, CAM_FLAG2_400 | CAM_FLAG2_10 | CAM_FLAG2_4 | CAM_FLAG2_2);
    } else {
        camera->actionFuncState = 666;
    }
}
