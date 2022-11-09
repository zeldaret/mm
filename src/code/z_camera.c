//#include "prevent_bss_reordering.h"
#include "global.h"
#include "z64quake.h"
#include "z64shrink_window.h"
#include "z64view.h"

#include "z_camera_data.inc.c"

// BSS
s16 D_801EDBF0;
f32 D_801EDBF4;
f32 D_801EDBF8;
CameraCollision D_801EDC00;

PlayState* sCamPlayState;
SwingAnimation D_801EDC30[4];
Vec3f D_801EDDD0;
Vec3f D_801EDDE0;
Vec3f D_801EDDF0;

/**
 * Returns the absolute value for floats
 */
f32 Camera_fabsf(f32 f) {
    return ABS(f);
}

/**
 * Returns the magnitude for 3D float vectors
 */
f32 Camera_Vec3fMagnitude(Vec3f* vec) {
    return sqrtf(SQ(vec->x) + SQ(vec->y) + SQ(vec->z));
}

/**
 * Interpolates along the curve shown below
 * returns value y ranging from 0.0f to 1.0f for -xMax <= x <= xMax
 * returns 1.0f otherwise
 *
 * y = 1.0f    ________                   _________
 *                     __               __
 *                       _             _
 * y axis                 _           _
 *                         ___     ___
 *                            _____
 * y = 0.0f           |         |         |
 *                 -xMax        0       xMax
 *
 *                           x axis
 */
f32 Camera_QuadraticAttenuation(f32 xRange, f32 x) {
    f32 y;
    f32 absX;
    f32 percent40 = 0.4f;
    f32 percent60;
    f32 xQuadratic;
    f32 xMaxQuadratic; // Normalizing constant

    absX = Camera_fabsf(x);

    if (absX > xRange) {
        // fixed value outside xMax range
        y = 1.0f;
    } else {
        // inside xMax range
        percent60 = 1.0f - percent40;

        if (absX < (xRange * percent60)) {
            // quadratic curve in the inner 60% of xMax range: +concavity (upward curve)
            xQuadratic = SQ(x) * (1.0f - percent40);
            xMaxQuadratic = SQ(xRange * percent60);

            y = xQuadratic / xMaxQuadratic;
        } else {
            // quadratic curve in the outer 40% of xMax range: -concavity (flattening curve)
            xQuadratic = SQ(xRange - absX) * percent40;
            xMaxQuadratic = SQ(0.4f * xRange);

            y = 1.0f - (xQuadratic / xMaxQuadratic);
        }
    }
    return y;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, the result is rounded up to `target`
 */
f32 Camera_LerpCeilF(f32 target, f32 cur, f32 stepScale, f32 minDiff) {
    f32 diff = target - cur;
    f32 step = diff * stepScale;

    return (Camera_fabsf(diff) >= minDiff) ? cur + step : target;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, the result is rounded up to `target`
 */
s16 Camera_LerpCeilS(s16 target, s16 cur, f32 stepScale, s16 minDiff) {
    s16 diff = target - cur;
    s16 step = diff * stepScale + 0.5f;

    return (ABS(diff) >= minDiff) ? cur + step : target;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, the result is rounded down to `cur`
 */
s16 Camera_LerpFloorS(s16 target, s16 cur, f32 stepScale, s16 minDiff) {
    s16 diff = target - cur;
    s16 step = diff * stepScale + 0.5f;

    return (ABS(diff) >= minDiff) ? cur + step : cur;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, the result is rounded up to `target`. Output is written to `cur`
 */
void Camera_LerpCeilVec3f(Vec3f* target, Vec3f* cur, f32 xzStepScale, f32 yStepScale, f32 minDiff) {
    cur->x = Camera_LerpCeilF(target->x, cur->x, xzStepScale, minDiff);
    cur->y = Camera_LerpCeilF(target->y, cur->y, yStepScale, minDiff);
    cur->z = Camera_LerpCeilF(target->z, cur->z, xzStepScale, minDiff);
}

void Camera_SetUpdateRatesFastPitch(Camera* camera) {
    camera->yawUpdateRateInv = 100.0f;
    camera->pitchUpdateRateInv = 16.0f;
    camera->rUpdateRateInv = 20.0f;
    camera->yOffsetUpdateRate = 0.05f;
    camera->xzOffsetUpdateRate = 0.05f;
    camera->fovUpdateRate = 0.05f;
}

void Camera_SetUpdateRatesFastYaw(Camera* camera) {
    camera->rUpdateRateInv = 50.0f;
    camera->pitchUpdateRateInv = 100.0f;
    camera->yawUpdateRateInv = 50.0f;
    camera->yOffsetUpdateRate = 0.01f;
    camera->xzOffsetUpdateRate = 0.1f;
    camera->fovUpdateRate = 0.01f;
    if (camera->speedRatio > 1.0f) {
        camera->speedRatio = 1.0f;
    }
}

void Camera_SetUpdateRatesSlow(Camera* camera) {
    camera->rUpdateRateInv = 1800.0f;
    camera->yawUpdateRateInv = 1800.0f;
    camera->pitchUpdateRateInv = 1800.0f;
    camera->yOffsetUpdateRate = 0.01;
    camera->xzOffsetUpdateRate = 0.01;
    camera->fovUpdateRate = 0.01;
}

/**
 * Converts a 3D s16 vector into a 3D f32 vector
 */
Vec3f* Camera_Vec3sToVec3f(Vec3f* dest, Vec3s* src) {
    Vec3f copy;

    copy.x = src->x;
    copy.y = src->y;
    copy.z = src->z;

    *dest = copy;
    return dest;
}

/**
 * Returns the difference between two angles and scales the difference up
 */
s16 Camera_AngleDiffAndScale(s16 angle1, s16 angle2, f32 scale) {
    return BINANG_SUB(angle1, angle2) * scale;
}

/**
 * Calculates the current offset between the camera's at-coordinates and the centered actor's coordinates
 */
void Camera_UpdateAtActorOffset(Camera* camera, Vec3f* actorOffset) {
    camera->atActorOffset.x = camera->at.x - actorOffset->x;
    camera->atActorOffset.y = camera->at.y - actorOffset->y;
    camera->atActorOffset.z = camera->at.z - actorOffset->z;
}

f32 Camera_GetFocalActorHeight(Camera* camera) {
    PosRot actorFocus;
    Actor* focalActor = camera->focalActor;
    f32 focalHeight;

    if (focalActor == &GET_PLAYER(camera->play)->actor) {
        focalHeight = Player_GetHeight((Player*)focalActor);
    } else {
        Actor_GetFocus(&actorFocus, focalActor);
        focalHeight = actorFocus.pos.y - camera->focalActorPosRot.pos.y;
        if (focalHeight == 0.0f) {
            focalHeight = 10.0f;
        }
    }
    return focalHeight;
}

f32 Camera_GetRunSpeedLimit(Camera* camera) {
    Actor* focalActor = camera->focalActor;
    f32 runSpeedLimit;

    if (focalActor == &GET_PLAYER(camera->play)->actor) {
        runSpeedLimit = Player_GetRunSpeedLimit((Player*)focalActor);
    } else {
        runSpeedLimit = 10.0f;
    }

    return runSpeedLimit;
}

s32 func_800CB7CC(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags3 & PLAYER_STATE3_10;
    } else {
        return 0;
    }
}
s32 Camera_IsMountedOnHorse(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_800000;
    } else {
        return 0;
    }
}

s32 Camera_IsDekuHovering(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags3 & PLAYER_STATE3_2000;
    } else {
        return 0;
    }
}

/**
 * When walking in a cutscene? Used during Postman's minigame.
 */
s32 func_800CB854(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_20;
    } else {
        return 0;
    }
}

s32 Camera_IsSwimming(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (focalActor == &GET_PLAYER(camera->play)->actor) {
        if (((Player*)focalActor)->stateFlags3 & PLAYER_STATE3_8000) {
            // Swimming as Zora
            return 999;
        } else {
            // Swimming as Human or Fierce Deity
            return ((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_8000000;
        }
    } else {
        // Camera not focused on player
        return 0;
    }
}

s32 Camera_IsDiving(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags2 & PLAYER_STATE2_800;
    } else {
        return 0;
    }
}

s32 Camera_IsPlayerFormZora(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->transformation == PLAYER_FORM_ZORA;
    } else {
        return false;
    }
}

s32 func_800CB924(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags3 & PLAYER_STATE3_1000;
    } else {
        return 0;
    }
}

s32 func_800CB950(Camera* camera) {
    Player* player;
    s32 phi_v0;
    s32 ret;
    f32 yDiff;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        yDiff = Camera_fabsf(camera->focalActorPosRot.pos.y - camera->playerFloorHeight);

        phi_v0 = false;
        if (yDiff < 11.0f) {
            phi_v0 = true;
        }

        ret = phi_v0;

        if (!ret) {

            ret = false;

            if (camera->focalActor->gravity > -0.1f) {
                ret = true;
            }

            player = (Player*)camera->focalActor;
            if (!ret) {
                // Using zora fins
                ret = player->stateFlags1 & PLAYER_STATE1_200000;
                ret = !!ret;
            }
        }
        return ret;
    } else {
        return true;
    }
}

s32 Camera_IsClimbingLedge(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_4;
    } else {
        return 0;
    }
}

s32 Camera_IsChargingSwordOrDekuFlowerDive(Camera* camera) {
    Actor* focalActor = camera->focalActor;
    s32 ret;

    if (focalActor == &GET_PLAYER(camera->play)->actor) {
        // Charging Sword
        ret = !!(((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_1000);
        if (!ret) {
            // Deku Flower Dive
            ret = !!(((Player*)focalActor)->stateFlags3 & PLAYER_STATE3_100);
        }
        return ret;
    } else {
        return false;
    }
}

s32 func_800CBA7C(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags2 & PLAYER_STATE2_800000;
    } else {
        return 0;
    }
}

s32 func_800CBAAC(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->meleeWeaponState;
    } else {
        return 0;
    }
}

s32 Camera_GetFocalActorPos(Vec3f* dst, Camera* camera) {
    PosRot focalPosRot;
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        *dst = ((Player*)focalActor)->bodyPartsPos[0];
        return dst;
    } else {
        Actor_GetWorldPosShapeRot(&focalPosRot, camera->focalActor);
        *dst = focalPosRot.pos;
        return dst;
    }
}

s32 Camera_IsUnderwaterAsZora(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER;
    } else {
        return 0;
    }
}

/**
 * Evaluate if player is in one of two sword animations
 */
s32 func_800CBB88(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        if ((((Player*)focalActor)->meleeWeaponState != 0) &&
            (((Player*)focalActor)->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_BUTT)) {
            return 3;
        }

        if ((((Player*)focalActor)->stateFlags2 & PLAYER_STATE2_20000) ||
            ((((Player*)focalActor)->meleeWeaponState != 0) &&
             (((Player*)focalActor)->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_KICK))) {
            return 1;
        }
    }

    return 0;
}

s32 Camera_IsUsingZoraFins(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (camera->focalActor == &GET_PLAYER(camera->play)->actor) {
        return ((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_200000;
    } else {
        return 0;
    }
}

s32 func_800CBC30(Camera* camera, f32 waterYMax, f32 waterYMin) {
    if ((camera->playerFloorHeight != camera->waterYPos) && (camera->waterYPos < waterYMax) &&
        (camera->waterYPos > waterYMin)) {
        return true;
    } else {
        return false;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC000.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC128.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC1C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC260.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC488.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC5C8.s")

#define CAM_DATA_IS_BG (1 << 12) // if not set, then cam data is for actor cutscenes

/**
 * Returns the CameraSettingType of the camera from either the bgCam or the actorCsCam at index `camDataId`
 */
s16 Camera_GetBgCamOrActorCsCamSetting(Camera* camera, u32 camDataId) {
    if (camDataId & CAM_DATA_IS_BG) {
        return BgCheck_GetBgCamSettingImpl(&camera->play->colCtx, camDataId & ~CAM_DATA_IS_BG, BGCHECK_SCENE);
    } else {
        return Play_GetActorCsCamSetting(camera->play, camDataId);
    }
}

/**
 * Returns either the bgCam data or the actorCsCam data at index `camDataId`
 */
Vec3s* Camera_GetBgCamOrActorCsCamFuncData(Camera* camera, u32 camDataId) {
    if (camDataId & CAM_DATA_IS_BG) {
        return BgCheck_GetBgCamFuncDataImpl(&camera->play->colCtx, camDataId & ~CAM_DATA_IS_BG, BGCHECK_SCENE);
    } else {
        return Play_GetActorCsCamFuncData(camera->play, camDataId);
    }
}

/**
 * Gets the bgCam index for the poly `poly`, returns -1 if
 * there is no camera data for that poly.
 */
s32 Camera_GetBgCamIndex(Camera* camera, s32* bgId, CollisionPoly* poly) {
    s32 bgCamIndex = SurfaceType_GetBgCamIndex(&camera->play->colCtx, poly, *bgId);
    s32 ret;

    if (BgCheck_GetBgCamSettingImpl(&camera->play->colCtx, bgCamIndex, *bgId) == CAM_SET_NONE) {
        ret = -1;
    } else {
        ret = bgCamIndex;
    }

    return ret;
}

/**
 * Gets the Camera setting for the water box the player is in.
 * Returns -1 if the player is not in a water box, or does not have a swimming state.
 * Returns -2 if there is no bgCam index for the water box.
 * Returns the camera setting otherwise.
 */
s32 Camera_GetWaterBoxBgCamSetting(Camera* camera, f32* waterY) {
    PosRot playerPosShape;
    WaterBox* waterBox;
    s32 camSetting;
    s32 bgId;

    Actor_GetWorldPosShapeRot(&playerPosShape, camera->focalActor);
    *waterY = playerPosShape.pos.y;

    if (!WaterBox_GetSurfaceImpl(camera->play, &camera->play->colCtx, playerPosShape.pos.x, playerPosShape.pos.z,
                                 waterY, &waterBox, &bgId)) {
        // player's position is not in a waterbox
        *waterY = playerPosShape.pos.y;
        return -1;
    }

    if (!Camera_IsSwimming(camera)) {
        return -1;
    }

    camSetting = WaterBox_GetBgCamSetting(&camera->play->colCtx, waterBox, bgId);

    // -2: no bgCam index
    return (camSetting == CAM_SET_NONE) ? -2 : camSetting;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC938.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC958.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC9C0.s")

s32 D_801B9E5C = 0;
f32 D_801B9E60 = 0.0f;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CCCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD288.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD2F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD3E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD44C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD634.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD834.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CDA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CDB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CDE6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE79C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE930.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CEAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CEC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CED90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Noop.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Parallel1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Parallel2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Parallel3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Parallel4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Parallel0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Battle1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Battle2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Battle3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Battle4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Battle0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Fixed1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Fixed2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Fixed3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Fixed4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Fixed0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Subject1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Subject2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Subject3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Subject4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Subject0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Data0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Data1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Data2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Data3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Data4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique6.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique7.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Unique9.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo1.s")

// Data for opening chests (default)
VecGeo D_801B9E64[] = {
    { 50.0f, 0xEE3A, 0xD558 },
    { 75.0f, 0x0000, 0x8008 },
    { 80.0f, 0xEE3A, 0x8008 },
    { 15.0f, 0xEE3A, 0x8008 },
};
Vec3f D_801B9E84[] = {
    { 0.0f, 40.0f, 20.0f },
    { 0.0f, 40.0f, 0.0f },
    { 0.0f, 3.0f, -3.0f },
    { 0.0f, 3.0f, -3.0f },
};

// Data for opening chests (goron)
VecGeo D_801B9EB4[] = {
    { 60.0f, 0xEE3A, 0xD558 },
    { 95.0f, 0x0000, 0x8008 },
    { 90.0f, 0xEE3A, 0x8008 },
    { 20.0f, 0xEE3A, 0x8008 },
};
Vec3f D_801B9ED4[] = {
    { 0.0f, 40.0f, 20.0f },
    { 0.0f, 40.0f, 0.0f },
    { 0.0f, 3.0f, -3.0f },
    { 0.0f, 3.0f, -3.0f },
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo6.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo7.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo9.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Demo0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special6.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special7.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Special9.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Alloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Free.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DDFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_InitPlayerSettings.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeStatus.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE324.s")

s16 sEarthquakeFreq[] = {
    0xFFC, // 1 Large Earthquake  between CLOCK_TIME(0, 00) to CLOCK_TIME(1, 30)
    0x7FC, // 2 Large Earthquakes between CLOCK_TIME(1, 30) to CLOCK_TIME(3, 00)
    0x3FC, // 4 Large Earthquakes between CLOCK_TIME(3, 00) to CLOCK_TIME(4, 30)
    0x1FC, // 8 Large Earthquakes between CLOCK_TIME(4, 30) to CLOCK_TIME(6, 00)
};
s16 sEarthquakeTimer = 0;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE840.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE890.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE954.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Update.s")

s32 sModeChangeFlags = 0;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DF498.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DF86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DF8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeSetting.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeDataIdx.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFC1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetInputDirYaw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetCamDir.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetCamDirPitch.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetCamDirYaw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_AddQuake.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetViewParam.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetFlags.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ClearFlags.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeDoorCam.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Copy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E01AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetQuakeOffset.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E01DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E0228.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E0238.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetToTrackActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetTargetActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetWaterYPos.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E0348.s")
