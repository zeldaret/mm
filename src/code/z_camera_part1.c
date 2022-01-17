#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

extern s16 D_801B9E18[14];
extern s16 D_801B9E34[14];
extern s32 sCameraShrinkWindowVal;
extern s32 sCameraInterfaceAlpha;

/*===============================================================*/
/*                   Camera Internal Functions                   */
/*===============================================================*/

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

    // fixed value outside xMax range
    if (absX > xRange) {
        y = 1.0f;

        // inside xMax range
    } else {
        percent60 = 1.0f - percent40;

        // quadratic curve in the inner 60% of xMax range: +concavity (upward curve)
        if (absX < (xRange * percent60)) {
            xQuadratic = SQ(x) * (1.0f - percent40);
            xMaxQuadratic = SQ(xRange * percent60);

            y = xQuadratic / xMaxQuadratic;
            // quadratic curve in the outer 40% of xMax range: -concavity (flattening curve)
        } else {
            xQuadratic = SQ(xRange - absX) * percent40;
            xMaxQuadratic = SQ(0.4f * xRange);

            y = 1.0f - (xQuadratic / xMaxQuadratic);
        }
    }
    return y;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, The result is rounded up to `target`
 */
f32 Camera_LERPCeilF(f32 target, f32 cur, f32 stepScale, f32 minDiff) {
    f32 diff = target - cur;
    f32 step = diff * stepScale;

    return (Camera_fabsf(diff) >= minDiff) ? cur + step : target;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, The result is rounded up to `target`
 */
s16 Camera_LERPCeilS(s16 target, s16 cur, f32 stepScale, s16 minDiff) {
    s16 diff = target - cur;
    s16 step = diff * stepScale + 0.5f;

    return (ABS(diff) >= minDiff) ? cur + step : target;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, The result is rounded down to `cur`
 */
s16 Camera_LERPFloorS(s16 target, s16 cur, f32 stepScale, s16 minDiff) {
    s16 diff = target - cur;
    s16 step = diff * stepScale + 0.5f;

    return (ABS(diff) >= minDiff) ? cur + step : cur;
}

/*
 * Performs linear interpoloation between `cur` and `target`.  If `cur` is within
 * `minDiff` units, The result is rounded up to `target`
 */
void Camera_LERPCeilVec3f(Vec3f* target, Vec3f* cur, f32 xzStepScale, f32 yStepScale, f32 minDiff) {
    cur->x = Camera_LERPCeilF(target->x, cur->x, xzStepScale, minDiff);
    cur->y = Camera_LERPCeilF(target->y, cur->y, yStepScale, minDiff);
    cur->z = Camera_LERPCeilF(target->z, cur->z, xzStepScale, minDiff);
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
    return SUB16(angle1, angle2) * scale;
}

// TODO: docs - not explicity a function in OoT, but is implicitely
/**
 * Calculates the current offset between the camera's at-coordinates and the centered actors coordinates
 */
void Camera_UpdateAtActorOffset(Camera* camera, Vec3f* actorOffset) {
    camera->atActorOffset.x = camera->at.x - actorOffset->x;
    camera->atActorOffset.y = camera->at.y - actorOffset->y;
    camera->atActorOffset.z = camera->at.z - actorOffset->z;
}

f32 Camera_GetTrackedActorHeight(Camera* camera) {
    PosRot actorFocus;
    Actor* trackActor = camera->trackActor;
    f32 trackHeight;

    if (trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        trackHeight = Player_GetHeight((Player*)trackActor);
    } else {
        Actor_GetFocus(&actorFocus, trackActor);
        trackHeight = actorFocus.pos.y - camera->trackActorPosRot.pos.y;
        if (trackHeight == 0.0f) {
            trackHeight = 10.0f;
        }
    }
    return trackHeight;
}

f32 Camera_GetRunSpeedLimit(Camera* camera) {
    Actor* trackActor = camera->trackActor;
    f32 runSpeedLimit;

    if (trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        runSpeedLimit = Player_GetRunSpeedLimit((Player*)trackActor);
    } else {
        runSpeedLimit = 10.0f;
    }

    return runSpeedLimit;
}

s32 func_800CB7CC(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    // stateFlags3 & 0x10: Turned off in the first line of Player_Update (func_808460B8)
    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags3 & 0x10;
    } else {
        return 0;
    }
}

s32 Camera_IsMountedOnHorse(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags1 & 0x800000;
    } else {
        return 0;
    }
}

s32 Camera_IsDekuHovering(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags3 & 0x2000;
    } else {
        return 0;
    }
}

/**
 * When walking in a cutscene? Used during Postman's minigame.
 */
s32 func_800CB854(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags1 & 0x20;
    } else {
        return 0;
    }
}

// related to player swimming (player->stateFlags1 & 0x8000000) is player swimming
s32 Camera_IsSwimming(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        if (((Player*)trackActor)->stateFlags3 & 0x8000) {
            // Swimming as Zora
            return 999;
        } else {
            // Swimming as non-Zora
            return ((Player*)trackActor)->stateFlags1 & 0x8000000;
        }
    } else {
        return 0;
    }
}

s32 Camera_IsDiving(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags2 & 0x800;
    } else {
        return 0;
    }
}

s32 Camera_IsPlayerFormZora(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->transformation == PLAYER_FORM_ZORA;
    } else {
        return false;
    }
}

s32 func_800CB924(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags3 & 0x1000;
    } else {
        return 0;
    }
}

s32 func_800CB950(Camera* camera) {
    Player* player;
    s32 phi_v0;
    s32 ret;
    f32 new_var;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        new_var = Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight);

        phi_v0 = false;
        if (new_var < 11.0f) {
            phi_v0 = true;
        }

        ret = phi_v0;

        if (!ret) {

            ret = false;

            if (camera->trackActor->gravity > -0.1f) {
                ret = true;
            }

            player = (Player*)camera->trackActor;
            if (!ret) {
                // Using zora fins
                ret = player->stateFlags1 & 0x200000;
                ret = !!ret;
            }
        }
        return ret;
    } else {
        return true;
    }
}

s32 Camera_IsClimbingLedge(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags1 & 4;
    } else {
        return 0;
    }
}

s32 Camera_IsChargingSwordOrDekuFlowerDive(Camera* camera) {
    Actor* trackActor = camera->trackActor;
    s32 ret;

    if (trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        // Charging Sword
        ret = !!(((Player*)trackActor)->stateFlags1 & 0x1000);
        if (!ret) {
            // Deku Flower Dive
            ret = !!(((Player*)trackActor)->stateFlags3 & 0x100);
        }
        return ret;
    } else {
        return false;
    }
}

s32 func_800CBA7C(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags2 & 0x800000;
    } else {
        return 0;
    }
}

s32 func_800CBAAC(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->swordState;
    } else {
        return 0;
    }
}

s32 func_800CBAD4(Vec3f* dst, Camera* camera) {
    PosRot sp24;
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        *dst = ((Player*)trackActor)->bodyPartsPos[0];
        return dst;
    } else {
        Actor_GetWorldPosShapeRot(&sp24, camera->trackActor);
        *dst = sp24.pos;
        return dst;
    }
}

s32 Camera_IsUnderwaterAsZora(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER;
    } else {
        return 0;
    }
}

/**
 * Evaluate if player is in one of two sword animations
 */
s32 func_800CBB88(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        // unknown sword animation
        if ((((Player*)trackActor)->swordState != 0) && (((Player*)trackActor)->swordAnimation == 26)) {
            return 3;
        }

        // A non-magic spin attack
        if ((((Player*)trackActor)->stateFlags2 & 0x20000) ||
            ((((Player*)trackActor)->swordState != 0) && (((Player*)trackActor)->swordAnimation == 29))) {
            return 1;
        }
    }

    return 0;
}

s32 Camera_IsUsingZoraFins(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        return ((Player*)trackActor)->stateFlags1 & 0x200000;
    } else {
        return 0;
    }
}

s32 func_800CBC30(Camera* camera, f32 arg1, f32 arg2) {
    if ((camera->playerFloorHeight != camera->waterYPos) && (camera->waterYPos < arg1) && (camera->waterYPos > arg2)) {
        return true;
    } else {
        return false;
    }
}

// OoT func_80043F94
s32 func_800CBC84(Camera* camera, Vec3f* from, CamColChk* to, s32 arg3) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    Vec3f toNewPos;
    Vec3f toPoint;
    Vec3f fromToNorm;
    f32 floorPolyY;
    CollisionPoly** floorPoly;
    s32 floorBgId;

    OLib_Vec3fDistNormalize(&fromToNorm, from, &to->pos);
    toPoint.x = to->pos.x + fromToNorm.x;
    toPoint.y = to->pos.y + fromToNorm.y;
    toPoint.z = to->pos.z + fromToNorm.z;
    floorPoly = &to->poly;

    if (!BgCheck_CameraLineTest1(colCtx, from, &toPoint, &toNewPos, floorPoly, (arg3 & 1) ? 0 : 1, 1,
                                 (arg3 & 2) ? 0 : 1, -1, &floorBgId)) {
        toNewPos = to->pos;
        if (1) {}
        if (1) {}
        toNewPos.y += 5.0f;
        if ((arg3 != 0) && func_800CB7CC(camera)) {
            to->poly = camera->trackActor->floorPoly;
            floorBgId = camera->trackActor->floorBgId;
            to->norm.x = COLPOLY_GET_NORMAL(to->poly->normal.x);
            to->norm.y = COLPOLY_GET_NORMAL(to->poly->normal.y);
            to->norm.z = COLPOLY_GET_NORMAL(to->poly->normal.z);

            if (!Math3D_LineSegVsPlane(to->norm.x, to->norm.y, to->norm.z, to->poly->dist, from, &toPoint, &toNewPos,
                                       1)) {
                floorPolyY = to->pos.y - 20.0f;
            } else {
                toNewPos.y += 5.0f;
                floorPolyY = to->pos.y;
            }
        } else {
            floorPolyY = BgCheck_CameraRaycastFloor2(colCtx, floorPoly, &floorBgId, &toNewPos);
        }

        if ((to->pos.y - floorPolyY) > 5.0f) {
            to->norm.x = -fromToNorm.x;
            to->norm.y = -fromToNorm.y;
            to->norm.z = -fromToNorm.z;
            return 0;
        }
    }

    to->bgId = floorBgId;
    to->norm.x = COLPOLY_GET_NORMAL(to->poly->normal.x);
    to->norm.y = COLPOLY_GET_NORMAL(to->poly->normal.y);
    to->norm.z = COLPOLY_GET_NORMAL(to->poly->normal.z);
    to->pos.x = to->norm.x + toNewPos.x;
    to->pos.y = to->norm.y + toNewPos.y;
    to->pos.z = to->norm.z + toNewPos.z;
    return floorBgId + 1;
}

// OoT func_80044340
void func_800CBFA4(Camera* camera, Vec3f* arg1, Vec3f* arg2, s32 arg3) {
    CamColChk sp20;
    s32 pad;

    sp20.pos = *arg2;
    func_800CBC84(camera, arg1, &sp20, arg3);
    *arg2 = sp20.pos;
}

/**
 * Detects the collision poly between `from` and `to`, places collision info in `to`
 */
s32 Camera_BgCheckInfo(Camera* camera, Vec3f* from, CamColChk* to) {
    CollisionPoly* floorPoly;
    Vec3f toNewPos;
    Vec3f fromToNorm;

    if (BgCheck_CameraLineTest1(&camera->globalCtx->colCtx, from, &to->pos, &toNewPos, &to->poly, 1, 1, 1, -1,
                                &to->bgId)) {
        floorPoly = to->poly;
        to->norm.x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        to->norm.y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        to->norm.z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
        to->pos = toNewPos;
        return to->bgId + 1;
    }

    OLib_Vec3fDistNormalize(&fromToNorm, from, &to->pos);
    to->norm.x = -fromToNorm.x;
    to->norm.y = -fromToNorm.y;
    to->norm.z = -fromToNorm.z;
    return 0;
}

/**
 * Detects if there is collision between `from` and `to`
 */
s32 Camera_BgCheck(Camera* camera, Vec3f* from, Vec3f* to) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    Vec3f intersect;
    s32 bgId;
    CollisionPoly* poly = NULL;

    if (BgCheck_CameraLineTest1(colCtx, from, to, &intersect, &poly, 1, 1, 1, -1, &bgId)) {
        *to = intersect;
        return true;
    }

    return false;
}

s32 Camera_CheckOOB(Camera* camera, Vec3f* from, Vec3f* to) {
    s32 pad;
    Vec3f intersect;
    s32 pad2;
    s32 bgId;
    CollisionPoly* poly;
    CollisionContext* colCtx = &camera->globalCtx->colCtx;

    poly = NULL;
    if ((BgCheck_CameraLineTest1(colCtx, from, to, &intersect, &poly, 1, 1, 1, 0, &bgId)) &&
        (CollisionPoly_GetPointDistanceFromPlane(poly, from) < 0.0f)) {
        return true;
    }

    return false;
}

s16 func_800CC260(Camera* camera, Vec3f* arg1, Vec3f* arg2, VecSph* arg3, Actor** exclusions, s16 numExclusions) {
    // sp 70-98 Could be one struct
    VecSph sp90;
    s32 ret;
    s32 angleCount;
    f32 rand;
    PosRot playerHead;
    Vec3f sp64;
    Player* player = GET_PLAYER(camera->globalCtx);
    s32 i;

    sp64 = *arg2;
    Actor_GetFocus(&playerHead, &player->actor); // playerHead unused
    sp90 = *arg3;

    angleCount = ARRAY_COUNT(D_801B9E18);
    for (i = 0; i < angleCount; i++) {
        OLib_VecSphAddToVec3f(arg1, arg2, &sp90);
        if (1) {};

        if (Camera_CheckOOB(camera, arg1, &sp64) || func_800CBC30(camera, arg2->y, arg1->y) ||
            CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, arg2, arg1, exclusions,
                                       numExclusions)) {
            sp90.yaw = D_801B9E18[i] + arg3->yaw;
            rand = Rand_ZeroOne();
            sp90.pitch = D_801B9E34[i] + ((s16)(arg3->pitch * rand));
            if (sp90.pitch > 0x36B0) { // 76.9 degrees
                sp90.pitch -= 0x3E80;  // -87.9 degrees
            }
            if (sp90.pitch < -0x36B0) { // -76.9 degrees
                sp90.pitch += 0x3A98;   // 82.4 degrees
            }
            sp90.r *= 0.9f;
            sp64 = *arg2;
        } else {
            break;
        }
    }

    *arg3 = sp90;

    if (i == angleCount) {
        ret = -1;
    } else {
        ret = i;
    }

    return ret;
}

/**
 * Gets the floor position underneath `chkPos`, and returns the normal of the floor to `floorNorm`,
 * and bgId to `bgId`.  If no floor is found, then the normal is a flat surface pointing upwards.
 */
f32 Camera_GetFloorYNorm(Camera* camera, Vec3f* floorNorm, Vec3f* chkPos, s32* bgId) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    CollisionPoly* floorPoly;
    f32 floorY = BgCheck_EntityRaycastFloor3(colCtx, &floorPoly, bgId, chkPos);

    if (floorY == BGCHECK_Y_MIN) {
        // no floor
        floorNorm->x = 0.0f;
        floorNorm->y = 1.0f;
        floorNorm->z = 0.0f;
    } else {
        floorNorm->x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        floorNorm->y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        floorNorm->z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
    }

    return floorY;
}

/**
 * Gets the position of the floor from `pos`
 */
f32 Camera_GetFloorY(Camera* camera, Vec3f* pos) {
    Vec3f posCheck;
    Vec3f floorNorm;
    s32 bgId;

    posCheck = *pos;
    posCheck.y += 80.0f;

    return Camera_GetFloorYNorm(camera, &floorNorm, &posCheck, &bgId);
}

/**
 * Gets the position of the floor from `pos`, and if the floor is considered not solid,
 * it checks the next floor below that.  Returns the normal of the floor into `norm`
 */
f32 Camera_GetFloorYLayer(Camera* camera, Vec3f* norm, Vec3f* pos, s32* bgId) {
    CollisionPoly* floorPoly;
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    f32 floorY;

    if (camera->trackActor != NULL) {
        floorY = BgCheck_EntityRaycastFloor5_3(camera->globalCtx, &camera->globalCtx->colCtx, &floorPoly, bgId,
                                               camera->trackActor, pos);
    } else {
        floorY = BgCheck_CameraRaycastFloor2(colCtx, &floorPoly, bgId, pos);
    }

    if ((floorY == BGCHECK_Y_MIN) ||
        ((camera->playerFloorHeight < floorY) && !(COLPOLY_GET_NORMAL(floorPoly->normal.y) > 0.5f))) {
        // no floor, or player is below the floor and floor is not considered steep
        norm->x = 0.0f;
        norm->y = 1.0f;
        norm->z = 0.0f;
        floorY = BGCHECK_Y_MIN;
    } else {
        norm->x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        norm->y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        norm->z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
    }

    return floorY;
}

// TODO: below is more than scene
/**
 * Returns the CameraSettingType of the camera at index `bgCamDataId`
 */
s16 Camera_GetCamDataSetting(Camera* camera, u32 camDataId) {
    if (camDataId & 0x1000) {
        return BgCheck_GetBgCamDataSetting(&camera->globalCtx->colCtx, camDataId & ~0x1000, BGCHECK_SCENE);
    } else {
        // Gets setting from globalCtx->csCamData[bgCamDataId]->setting which gets scene cmd->csCameraList.segment
        return Play_GetCsCamDataSetting(camera->globalCtx, camDataId);
    }
}

/**
 * Returns the scene camera info of the camera at index `camDataId`
 */
Vec3s* Camera_GetCamDataVec3s(Camera* camera, u32 camDataId) {
    if (camDataId & 0x1000) {
        // Returns scene data
        return BgCheck_GetBgCamDataVec3s(&camera->globalCtx->colCtx, camDataId & ~0x1000, BGCHECK_SCENE);
    } else {
        // Gets actor scene data from globalCtx->csCamData[camDataId]->data
        return Play_GetCsCamDataVec3s(camera->globalCtx, camDataId);
    }
}

/**
 * Gets the scene's camera index for the poly `poly`, returns -1 if
 * there is no camera data for that poly.
 */
s32 Camera_GetBgCamDataId(Camera* camera, s32* bgId, CollisionPoly* poly) {
    s32 bgCamDataId = SurfaceType_GetCamDataIndex(&camera->globalCtx->colCtx, poly, *bgId);
    s32 ret;

    if (BgCheck_GetBgCamDataSetting(&camera->globalCtx->colCtx, bgCamDataId, *bgId) == CAM_SET_NONE) {
        ret = -1;
    } else {
        ret = bgCamDataId;
    }

    return ret;
}

/**
 * Gets the Camera information for the water box the player is in.
 * Returns -1 if the player is not in a water box, or does not have a swimming state.
 * Returns -2 if there is no camera index for the water box.
 * Returns the camera data index otherwise.
 */
s32 Camera_GetWaterBoxCamSetting(Camera* camera, f32* waterY) {
    PosRot playerPosShape;
    WaterBox* waterBox;
    s32 camSetting;
    s32 sp30;

    Actor_GetWorldPosShapeRot(&playerPosShape, camera->trackActor);
    *waterY = playerPosShape.pos.y;

    if (!WaterBox_GetSurfaceImpl(camera->globalCtx, &camera->globalCtx->colCtx, playerPosShape.pos.x,
                                 playerPosShape.pos.z, waterY, &waterBox, &sp30)) {
        // player's position is not in a waterbox
        *waterY = playerPosShape.pos.y;
        return -1;
    }

    if (!Camera_IsSwimming(camera)) {
        return -1;
    }

    camSetting = WaterBox_GetCameraSetting(&camera->globalCtx->colCtx, waterBox, sp30);

    // -2: no camera data idx
    return (camSetting == CAM_SET_NONE) ? -2 : camSetting;
}

void func_800CC938(Camera* camera) {
    func_800DDFE0(camera);
}

/**
 * Calculates the angle between points `from` and `to`
 */
s16 Camera_CalcXZAngle(Vec3f* to, Vec3f* from) {
    // Math_FAtan2F in OoT
    return DEGF_TO_BINANG(RADF_TO_DEGF(func_80086B30(from->x - to->x, from->z - to->z)));
}

// BSS
s16 D_801EDBF0;

// Identical to OoT func_80044ADC
s16 func_800CC9C0(Camera* camera, s16 yaw, s16 arg2) {
    static f32 D_801EDBF4;
    static f32 D_801EDBF8;
    static s32 pad;
    static CamColChk D_801EDC00;
    Vec3f playerPos;
    Vec3f rotatedPos;
    Vec3f floornorm;
    f32 temp_f2;
    s16 temp_s0;
    s16 temp_s1;
    f32 phi_f18;
    f32 sinYaw = Math_SinS(yaw);
    f32 cosYaw = Math_CosS(yaw);
    s32 bgId;
    f32 sp30;
    f32 sp2C;
    f32 phi_f16;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);

    temp_f2 = (trackHeight * 1.2f);
    sp2C = trackHeight * 2.5f;
    sp30 = trackHeight;
    playerPos.x = camera->trackActorPosRot.pos.x;
    playerPos.y = camera->playerFloorHeight + temp_f2;
    playerPos.z = camera->trackActorPosRot.pos.z;
    rotatedPos.x = (trackHeight * sinYaw) + playerPos.x;
    rotatedPos.y = playerPos.y;
    rotatedPos.z = (trackHeight * cosYaw) + playerPos.z;

    if (arg2 || ((camera->globalCtx->state.frames % 2) == 0)) {
        D_801EDC00.pos.x = playerPos.x + (sp2C * sinYaw);
        D_801EDC00.pos.y = playerPos.y;
        D_801EDC00.pos.z =
            playerPos.z + (sp2C * cosYaw); // TODO: D_801EDC04 may be D_801EDC00 or D_801EDC04.x = D_801EDC04.y
        Camera_BgCheckInfo(camera, &playerPos, &D_801EDC00);
        if (arg2) {
            D_801EDBF4 = D_801EDBF8 = camera->playerFloorHeight;
        }
    } else {
        sp2C = OLib_Vec3fDistXZ(&playerPos, &D_801EDC00.pos);
        D_801EDC00.pos.x += D_801EDC00.norm.x * 5.0f;
        D_801EDC00.pos.y += D_801EDC00.norm.y * 5.0f;
        D_801EDC00.pos.z += D_801EDC00.norm.z * 5.0f;
        if (sp2C < sp30) {
            sp30 = sp2C;
            D_801EDBF4 = D_801EDBF8 = Camera_GetFloorYLayer(camera, &floornorm, &D_801EDC00.pos, &bgId);
        } else {
            D_801EDBF4 = Camera_GetFloorYLayer(camera, &floornorm, &rotatedPos, &bgId);
            D_801EDBF8 = Camera_GetFloorYLayer(camera, &floornorm, &D_801EDC00.pos, &bgId);
        }

        if (D_801EDBF4 == BGCHECK_Y_MIN) {
            D_801EDBF4 = camera->playerFloorHeight;
        }

        if (D_801EDBF8 == BGCHECK_Y_MIN) {
            D_801EDBF8 = D_801EDBF4;
        }
    }

    phi_f16 = (D_801EDBF4 - camera->playerFloorHeight) * 0.8f;
    phi_f18 = (D_801EDBF8 - camera->playerFloorHeight) * 0.19999999f;
    temp_s0 = DEGF_TO_BINANG(RADF_TO_DEGF(func_80086B30(phi_f16, sp30)));
    temp_s1 = DEGF_TO_BINANG(RADF_TO_DEGF(func_80086B30(phi_f18, sp2C)));
    return temp_s0 + temp_s1;
}

f32 func_800CCCEC(Camera* camera, s16 arg1) {
    static s32 D_801B9E5C = 0;
    static f32 D_801B9E60 = 0.0f;
    Vec3f sp7C;
    Vec3f sp70;
    PosRot sp5C;
    CamColChk sp34;
    f32 temp_f0;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    f32 sp28;
    f32 temp_f2;
    s16 sp22;
    f32 temp_f12;

    if (arg1 != 0) {
        D_801B9E5C = 0;
        D_801B9E60 = 0.0f;
    }

    sp5C = camera->trackActorPosRot;

    sp28 = Math_SinS(sp5C.rot.y);
    temp_f0 = Math_CosS(sp5C.rot.y);

    sp7C.x = (30.0f * sp28) + sp5C.pos.x;
    sp7C.y = sp5C.pos.y + trackHeight;
    sp7C.z = 30.0f * temp_f0 + sp5C.pos.z;
    sp34.pos.x = sp5C.pos.x + (12.0f * sp28);
    sp34.pos.y = sp7C.y;
    sp34.pos.z = sp5C.pos.z + (12.0f * temp_f0);

    if ((camera->globalCtx->state.frames & 1) != 0) {
        sp22 = sp5C.rot.y + 0x2EE0;
        sp70.x = (Math_SinS(sp22) * 50.0f) + sp7C.x;
        sp70.y = sp7C.y;
        sp70.z = (Math_CosS(sp22) * 50.0f) + sp7C.z;

        if ((Camera_BgCheckInfo(camera, &sp70, &sp34) != 0) && (Camera_CheckOOB(camera, &sp7C, &sp70) != 0)) {
            temp_f0 = OLib_Vec3fDistXZ(&sp7C, &sp34.pos);
            if ((D_801B9E5C != 2) || !((50.0f - temp_f0) <= -D_801B9E60)) {
                D_801B9E5C = 1;
                temp_f2 = 50.0f - temp_f0;
                D_801B9E60 = temp_f2;
                if (temp_f2 == -temp_f2) {
                    temp_f12 = 0.0f;
                } else {
                    temp_f12 = temp_f2;
                }
                return temp_f12;
            }
        }
    } else {
        sp22 = SUB16(sp5C.rot.y, 0x4000);
        sp70.x = (Math_SinS(sp22) * 50.0f) + sp7C.x;
        sp70.y = sp7C.y;
        sp70.z = (Math_CosS(sp22) * 50.0f) + sp7C.z;
        if ((Camera_BgCheckInfo(camera, &sp70, &sp34) != 0) && (Camera_CheckOOB(camera, &sp7C, &sp70) != 0)) {
            temp_f0 = OLib_Vec3fDistXZ(&sp7C, &sp34.pos);
            if ((D_801B9E5C != 1) || !(-(temp_f0 - 50.0f) <= D_801B9E60)) {
                D_801B9E5C = 2;
                temp_f2 = temp_f0 - 50.0f;
                D_801B9E60 = temp_f2;
                if (temp_f2 == -temp_f2) {
                    temp_f12 = 0.0f;
                } else {
                    temp_f12 = temp_f2;
                }
                return temp_f12;
            }
        }
    }

    if (D_801B9E5C != 0) {
        temp_f2 = D_801B9E60;
    } else {
        temp_f2 = 0.0f;
    }

    D_801B9E5C = 0;
    D_801B9E60 = 0.0f;
    return temp_f2;
}

Vec3f* Camera_CalcUpFromPitchYawRoll(Vec3f* dest, s16 pitch, s16 yaw, s16 roll) {
    f32 sinPitch = Math_SinS(pitch);
    f32 cosPitch = Math_CosS(pitch);
    f32 sinYaw = Math_SinS(yaw);
    f32 cosYaw = Math_CosS(yaw);
    f32 sinNegRoll;
    f32 cosNegRoll;
    Vec3f spA4;
    f32 negSinPitch = -sinPitch;
    f32 sp54;
    f32 sp4C;
    f32 cosPitchCosYawSinRoll;
    f32 temp_f4_2;
    f32 temp_f10_2;
    f32 cosPitchcosYaw;
    f32 temp_f14;
    f32 negSinPitchSinYaw;
    f32 negSinPitchCosYaw;
    f32 cosPitchSinYaw;
    f32 temp_f6;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 pad;

    sinNegRoll = Math_SinS(-roll);
    cosNegRoll = Math_CosS(-roll);

    negSinPitchSinYaw = negSinPitch * sinYaw;
    temp_f14 = 1.0f - cosNegRoll;

    cosPitchSinYaw = cosPitch * sinYaw;
    sp54 = SQ(cosPitchSinYaw);
    sp4C = (cosPitchSinYaw * sinPitch) * temp_f14;
    cosPitchcosYaw = cosPitch * cosYaw;

    temp_f4_2 = ((1.0f - sp54) * cosNegRoll) + sp54;
    cosPitchCosYawSinRoll = cosPitchcosYaw * sinNegRoll;
    negSinPitchCosYaw = negSinPitch * cosYaw;
    temp_f6 = (cosPitchcosYaw * cosPitchSinYaw) * temp_f14;
    temp_f10_2 = sinPitch * sinNegRoll;

    spA4.x = ((negSinPitchSinYaw * temp_f4_2) + (cosPitch * (sp4C - cosPitchCosYawSinRoll))) +
             (negSinPitchCosYaw * (temp_f6 + temp_f10_2));
    sp54 = SQ(sinPitch);
    temp_f4_2 = (sinPitch * cosPitchcosYaw) * temp_f14;
    temp_f8_3 = cosPitchSinYaw * sinNegRoll;
    temp_f8 = sp4C + cosPitchCosYawSinRoll;
    spA4.y = ((negSinPitchSinYaw * temp_f8) + (cosPitch * (((1.0f - sp54) * cosNegRoll) + sp54))) +
             (negSinPitchCosYaw * (temp_f4_2 - temp_f8_3));
    temp_f8_2 = temp_f6 - temp_f10_2;
    spA4.z = ((negSinPitchSinYaw * temp_f8_2) + (cosPitch * (temp_f4_2 + temp_f8_3))) +
             (negSinPitchCosYaw * (((1.0f - SQ(cosPitchcosYaw)) * cosNegRoll) + SQ(cosPitchcosYaw)));
    *dest = spA4;
    return dest;
}

f32 Camera_ClampLERPScale(Camera* camera, f32 maxLERPScale) {
    f32 ret;

    if (camera->atLERPStepScale < 0.12f) {
        ret = 0.12f;
    } else if (camera->atLERPStepScale >= maxLERPScale) {
        ret = maxLERPScale;
    } else {
        ret = 1.1f * camera->atLERPStepScale;
    }

    return ret;
}

void Camera_ResetActionFuncState(Camera* camera, s32 mode) {
    camera->actionFuncState = 0;
}

void Camera_UpdateInterface(s32 flags) {
    s32 interfaceAlpha;

    if ((flags & SHRINKWIN_MASK) != SHRINKWINVAL_PREV) {
        switch (flags & SHRINKWINVAL_MASK) {
            case SHRINKWINVAL_SMALL:
                sCameraShrinkWindowVal = 0x1A;
                break;
            case SHRINKWINVAL_MEDIUM:
                sCameraShrinkWindowVal = 0x1B;
                break;
            case SHRINKWINVAL_LARGE:
                sCameraShrinkWindowVal = 0x20;
                break;
            default:
                sCameraShrinkWindowVal = 0;
                break;
        }

        if (flags & SHRINKWIN_MAG) {
            ShrinkWindow_SetLetterboxMagnitude(sCameraShrinkWindowVal);
        } else {
            ShrinkWindow_SetLetterboxTarget(sCameraShrinkWindowVal);
        }
    }

    if ((flags & IFACE_ALPHA_MASK) != IFACE_ALPHA_MASK) {
        interfaceAlpha = (flags & IFACE_ALPHA_MASK) >> 8;
        if (interfaceAlpha == 0) {
            interfaceAlpha = 50;
        }
        if (interfaceAlpha != sCameraInterfaceAlpha) {
            sCameraInterfaceAlpha = interfaceAlpha;
            Interface_ChangeAlpha(sCameraInterfaceAlpha);
        }
    }
}

Vec3f* Camera_BgCheckCorner(Vec3f* dst, Vec3f* linePointA, Vec3f* linePointB, CamColChk* pointAColChk,
                            CamColChk* pointBColChk) {
    Vec3f closestPoint;

    func_800CAA14(pointAColChk->poly, pointBColChk->poly, linePointA, linePointB, &closestPoint);
    *dst = closestPoint;
    return dst;
}

/**
 * TODO: Update OoT description to MM description
 * Checks collision between at and eyeNext, if `checkEye` is set, if there is no collsion between
 * eyeNext->at, then eye->at is also checked.
 * Returns:
 * 0 if no collsion is found between at->eyeNext
 * 2 if the angle between the polys is between 60 degrees and 120 degrees
 * 3 ?
 * 6 if the angle between the polys is greater than 120 degrees
 */
s32 func_800CD44C(Camera* camera, VecSph* diffSph, CamColChk* eyeChk, CamColChk* atChk, s16 checkEye) {
    Vec3f* at = &camera->at;
    s32 pad1[2];
    s32 atEyeBgId;
    s32 eyeAtBgId;
    s32 ret;
    f32 cosEyeAt;
    s32 pad2[9];
    void* sp2C;

    eyeChk->pos = camera->eyeNext;

    ret = 0;

    atEyeBgId = func_800CBC84(camera, at, eyeChk, 0);
    if (atEyeBgId != 0) {
        // collision found between at->ey
        atChk->pos = *at;

        OLib_Vec3fToVecSphGeo(&eyeChk->sphNorm, &eyeChk->norm);

        if (eyeChk->sphNorm.pitch > 0x2EE0) { // 65.9 degrees
            eyeChk->sphNorm.yaw = diffSph->yaw;
        }

        if (checkEye & 1) {
            memcpy(&sp2C, atChk, 40);
        }

        eyeAtBgId = Camera_BgCheckInfo(camera, &camera->eye, atChk);

        if (eyeAtBgId == 0) {
            if (checkEye & 1) {
                memcpy(atChk, &sp2C, 40);
            } else {
                return 3;
            }
        }

        if (eyeChk->poly == atChk->poly) {
            return 3;
        }

        OLib_Vec3fToVecSphGeo(&atChk->sphNorm, &atChk->norm);

        if (atChk->sphNorm.pitch > 0x2EE0) { // 65.9 degrees
            atChk->sphNorm.yaw = BINANG_ROT180(diffSph->yaw);
        }

        if (atEyeBgId != eyeAtBgId) {
            ret = 3;
        } else {
            cosEyeAt = Math3D_Parallel(&eyeChk->norm, &atChk->norm);
            if (cosEyeAt < -0.5f) {
                ret = 6;
            } else if ((cosEyeAt > 0.5f) || (checkEye & 2)) {
                ret = 3;
            } else {
                ret = 1;
            }
        }
    }
    return ret;
}

/**
 * Calculates how much to adjust the camera at's y value when on a slope.
 */
f32 Camera_CalcSlopeYAdj(Vec3f* floorNorm, s16 playerYRot, s16 eyeAtYaw, f32 adjAmt) {
    f32 tmp;
    VecSph floorNormSph;

    OLib_Vec3fToVecSphGeo(&floorNormSph, floorNorm);

    tmp = Math_CosS(floorNormSph.pitch) * Math_CosS(playerYRot - floorNormSph.yaw);
    return (Camera_fabsf(tmp) * adjAmt) * Math_CosS(playerYRot - eyeAtYaw);
}

f32 func_800CD6CC(Actor* actor) {
    return sqrtf(gTargetRanges[actor->targetMode].rangeSq / gTargetRanges[actor->targetMode].leashScale);
}

/**
 * Calculates new at vector for the camera pointing in `eyeAtDir`
 */
s32 Camera_CalcAtDefault(Camera* camera, VecSph* eyeAtDir, f32 yOffset, s16 calcSlope) {
    Vec3f* at = &camera->at;
    Vec3f posOffsetTarget;
    Vec3f atTarget;
    s32 pad;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);

    posOffsetTarget.x = 0.0f;
    posOffsetTarget.y = trackHeight + yOffset;
    posOffsetTarget.z = 0.0f;

    if (calcSlope) {
        posOffsetTarget.y -= OLib_ClampMaxDist(
            Camera_CalcSlopeYAdj(&camera->floorNorm, playerPosRot->rot.y, eyeAtDir->yaw, 25.0f), trackHeight);
    }

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->atActorOffset, camera->xzOffsetUpdateRate,
                         camera->yOffsetUpdateRate, 0.1f);

    atTarget.x = playerPosRot->pos.x + camera->atActorOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->atActorOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->atActorOffset.z;

    if (atTarget.y < (camera->playerFloorHeight + 10.0f)) {
        atTarget.y = camera->playerFloorHeight + 10.0f;
    }

    Camera_LERPCeilVec3f(&atTarget, at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return true;
}

s32 func_800CD834(Camera* camera, VecSph* eyeAtDir, f32 yOffset, f32* arg3, f32 arg4) {
    f32 deltaY;
    Vec3f posOffsetTarget;
    Vec3f atTarget;
    Vec3f* new_var;
    f32 temp_f2;
    f32 temp_f0;
    s16 phi_v1;
    s16 temp_v0;
    PosRot* playerPosRot;

    posOffsetTarget.y = yOffset + Camera_GetTrackedActorHeight(camera);
    posOffsetTarget.x = 0.0f;
    posOffsetTarget.z = 0.0f;

    Actor_GetScreenPos(camera->globalCtx, camera->trackActor, &phi_v1, &temp_v0);
    temp_v0 -= 120;

    phi_v1 = ABS(temp_v0);
    playerPosRot = &camera->trackActorPosRot;

    OLib_ClampMaxDist(phi_v1 / 120.0f, 1.0f); // Should have an output

    deltaY = playerPosRot->pos.y - *arg3;
    temp_f2 = OLib_ClampMaxDist(deltaY, arg4);

    if (phi_v1 > 60) {
        phi_v1 = 60;
        if (camera) {}
    }

    temp_f0 = OLib_ClampMaxDist(phi_v1 / 60.0f, 1.0f);
    posOffsetTarget.y -= temp_f2 * temp_f0 * temp_f0;

    Camera_LERPCeilVec3f(((void)0, &posOffsetTarget), &camera->atActorOffset, camera->xzOffsetUpdateRate,
                         camera->yOffsetUpdateRate, 0.1f);
    atTarget.x = playerPosRot->pos.x + camera->atActorOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->atActorOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->atActorOffset.z;
    atTarget.y = CLAMP_MIN(atTarget.y, camera->playerFloorHeight + 10.0f);

    Camera_LERPCeilVec3f(&atTarget, &camera->at, camera->atLERPStepScale, camera->atLERPStepScale, 0.1f);
    return true;
}

s32 func_800CDA14(Camera* camera, VecSph* arg1, f32 yOffset, f32 arg3) {
    PosRot* temp_s1 = &camera->trackActorPosRot;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 atLERPStepScale;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);

    sp50.x = Math_SinS(temp_s1->rot.y) * arg3;
    sp50.z = Math_CosS(temp_s1->rot.y) * arg3;
    sp50.y = trackHeight + yOffset;
    Camera_LERPCeilVec3f(&sp50, &camera->atActorOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);

    sp44.x = temp_s1->pos.x + camera->atActorOffset.x;
    sp44.y = temp_s1->pos.y + camera->atActorOffset.y;
    sp44.z = temp_s1->pos.z + camera->atActorOffset.z;
    sp38.x = temp_s1->pos.x;
    sp38.y = sp44.y;
    sp38.z = temp_s1->pos.z;

    if (Camera_BgCheck(camera, &sp38, &sp44)) {
        sp44.x -= camera->atActorOffset.x - (sp44.x - sp38.x);
        sp44.z -= camera->atActorOffset.z - (sp44.z - sp38.z);
    }

    atLERPStepScale = camera->atLERPStepScale;
    Camera_LERPCeilVec3f(&sp44, &camera->at, atLERPStepScale, atLERPStepScale, 0.2f);
    return true;
}

s32 func_800CDB6C(Camera* camera, VecSph* arg1, f32 yOffset, f32 arg3, f32* arg4, s16 arg5) {
    f32 new_var;
    Vec3f sp70;
    Vec3f sp64;
    f32 temp_f0;
    f32 temp_f12;
    f32 sp58;
    f32 sp54;
    PosRot* trackActorPosRot = &camera->trackActorPosRot;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    VecSph sp44;
    Vec3f* at = &camera->at;

    if (arg5 & 0x40) {
        sp44.r = func_800CCCEC(camera, arg5 & 0x10);
        sp44.yaw = trackActorPosRot->rot.y + 0x4000;
        sp44.pitch = 0;
        OLib_VecSphGeoToVec3f(&sp70, &sp44);
    } else {
        temp_f0 = camera->atActorOffset.x + camera->trackActorOffset.x;
        temp_f12 = camera->atActorOffset.z + camera->trackActorOffset.z;
        if (sqrtf(SQ(temp_f0) + SQ(temp_f12)) < arg3) {
            sp70.x = temp_f0;
            sp70.z = temp_f12;
        } else {
            sp70.x = camera->atActorOffset.x;
            sp70.z = camera->atActorOffset.z;
        }
        sp58 = temp_f0; // TODO: Needed to match?
    }

    sp70.y = trackHeight + yOffset;

    if ((PREG(76) != 0) && (arg5 != 0)) {
        sp70.y -= Camera_CalcSlopeYAdj(&camera->floorNorm, trackActorPosRot->rot.y, arg1->yaw, 25.0f);
    }

    if (func_800CB950(camera)) {
        temp_f0 = Camera_LERPCeilF(trackActorPosRot->pos.y, *arg4, 0.4f, 0.1f);
        *arg4 = temp_f0;
        new_var = trackActorPosRot->pos.y - temp_f0;
        sp70.y -= new_var;
        Camera_LERPCeilVec3f(&sp70, &camera->atActorOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate,
                             0.1f);
    } else {
        sp58 = trackActorPosRot->pos.y - *arg4;
        sp54 = OLib_Vec3fDistXZ(at, &camera->eye);
        temp_f12 = func_80086760(camera->fov * 0.4f * (M_PI / 180)) * sp54;

        if (temp_f12 < sp58) {
            if (1) {} // TODO: Needed to match?
            *arg4 += (sp58 - temp_f12);
            sp58 = temp_f12;
        } else {
            temp_f0 = -temp_f12;
            if (sp58 < temp_f0) {
                *arg4 += (sp58 + temp_f12);
                sp58 = temp_f0;
            }
        }

        sp70.y -= sp58;
        Camera_LERPCeilVec3f(&sp70, &camera->atActorOffset, 0.3f, 0.2f, 0.1f);
        camera->xzOffsetUpdateRate = 0.3f;
        camera->yOffsetUpdateRate = 0.2f;
    }

    sp64.x = trackActorPosRot->pos.x + camera->atActorOffset.x;
    sp64.y = trackActorPosRot->pos.y + camera->atActorOffset.y;
    sp64.z = trackActorPosRot->pos.z + camera->atActorOffset.z;
    Camera_LERPCeilVec3f(&sp64, at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return true;
}

s32 Camera_CalcAtForLockOn(Camera* camera, VecSph* eyeAtDir, Vec3f* targetPos, f32 yOffset, f32 distance,
                           f32* yPosOffset, VecSph* outPlayerToTargetDir, s16 flags) {
    Vec3f* sp3C = &camera->at;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    f32 temp_f0_6;
    VecSph sp5C;
    f32 temp_f20;
    f32 temp_f2;
    f32 phi_f16;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    f32 sp50;
    PosRot* trackActorPosRot = &camera->trackActorPosRot;

    sp80.x = 0.0f;
    sp80.y = trackHeight + yOffset;
    sp80.z = 0.0f;

    if (PREG(76) && (flags & FLG_ADJSLOPE)) {
        sp80.y -= Camera_CalcSlopeYAdj(&camera->floorNorm, camera->trackActorPosRot.rot.y, eyeAtDir->yaw, 25.0f);
    }

    sp74 = trackActorPosRot->pos;
    sp74.y += trackHeight;

    OLib_Vec3fDiffToVecSphGeo(outPlayerToTargetDir, &sp74, targetPos);

    sp5C = *outPlayerToTargetDir;
    sp5C.r = (distance < sp5C.r) ? (sp5C.r * 0.2f) : ((sp5C.r * 0.9f) - (sp5C.r * 0.7f * (sp5C.r / distance)));

    if (flags & FLG_OFFGROUND) {
        sp5C.r *= 0.2f;
        camera->yOffsetUpdateRate = camera->xzOffsetUpdateRate = 0.01f;
    }

    OLib_VecSphGeoToVec3f(&sp68, &sp5C);

    sp80.x += sp68.x;
    sp80.y += sp68.y;
    sp80.z += sp68.z;

    if (func_800CB950(camera)) {
        *yPosOffset = Camera_LERPCeilF(trackActorPosRot->pos.y, *yPosOffset, 0.4f, 0.1f);
        temp_f20 = trackActorPosRot->pos.y - *yPosOffset;
        sp80.y -= temp_f20;
        Camera_LERPCeilVec3f(&sp80, &camera->atActorOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate,
                             0.1f);
    } else {
        if (!(flags & 0x80)) {
            temp_f20 = trackActorPosRot->pos.y - *yPosOffset;
            sp50 = OLib_Vec3fDistXZ(sp3C, &camera->eye);
            phi_f16 = sp50;
            func_80086B30(temp_f20, sp50);
            temp_f2 = func_80086760(camera->fov * 0.4f * (M_PI / 180)) * phi_f16;

            if (temp_f2 < temp_f20) {
                *yPosOffset = *yPosOffset + (temp_f20 - temp_f2);
                temp_f20 = temp_f2;
            } else if (temp_f20 < -temp_f2) {
                *yPosOffset += (temp_f20 + temp_f2);
                temp_f20 = -temp_f2;
            }
            sp80.y -= temp_f20;
        } else {
            temp_f20 = trackActorPosRot->pos.y - *yPosOffset;
            temp_f0_6 = func_80086B30(temp_f20, OLib_Vec3fDistXZ(sp3C, &camera->eye));

            if (temp_f0_6 > 0.34906584f) { // (M_PI / 9)
                phi_f16 = 1.0f - sin_rad(temp_f0_6 - 0.34906584f);
            } else if (temp_f0_6 < -0.17453292f) {
                phi_f16 = 1.0f - sin_rad(-0.17453292f - temp_f0_6);
            } else {
                phi_f16 = 1.0f;
            }

            sp80.y -= temp_f20 * phi_f16;
        }

        Camera_LERPCeilVec3f(&sp80, &camera->atActorOffset, 0.5f, 0.5f, 0.1f);
        camera->xzOffsetUpdateRate = 0.5f;
        camera->yOffsetUpdateRate = 0.5f;
    }

    sp74.x = trackActorPosRot->pos.x + camera->atActorOffset.x;
    sp74.y = trackActorPosRot->pos.y + camera->atActorOffset.y;
    sp74.z = trackActorPosRot->pos.z + camera->atActorOffset.z;
    Camera_LERPCeilVec3f(&sp74, sp3C, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return 1;
}

// Camera_CalcAtForLockOn2?
s32 func_800CE2B8(Camera* camera, f32* arg1, s32 arg2, f32 yOffset, f32 arg4, f32 arg5, f32* arg6, VecSph* arg7,
                  s16 flags) {
    PosRot* temp_s1 = &camera->trackActorPosRot;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    VecSph sp58;
    f32 temp_f0_3;
    f32 temp_f20;
    f32 new_var2;
    f32 sp4C;
    f32 phi_f14;
    f32 temp_f2;

    sp78.y = Camera_GetTrackedActorHeight(camera) + yOffset;
    sp78.x = 0.0f;
    sp78.z = 0.0f;
    sp58 = *arg7;
    sp58.r = arg7->r * (arg5 * arg4);
    if (flags & 0x80) {
        camera->yOffsetUpdateRate = 0.01f;
        camera->xzOffsetUpdateRate = 0.01f;
    }

    OLib_VecSphGeoToVec3f(&sp60, &sp58);
    sp78.x += sp60.x;
    sp78.y += sp60.y;
    sp78.z += sp60.z;
    if (func_800CB950(camera)) {
        phi_f14 = *arg6;
        *arg6 = Camera_LERPCeilF(temp_s1->pos.y, phi_f14, 0.4f, 0.1f);
        // new_var = temp_s1->pos.y;
        temp_f20 = ((void)0, temp_s1->pos.y - (*arg6));
        sp78.y -= temp_f20;
        Camera_LERPCeilVec3f(&sp78, &camera->atActorOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate,
                             0.1f);
    } else {
        if (temp_s1->pos.x) {}
        new_var2 = *arg1;
        sp4C = new_var2;
        temp_f20 = temp_s1->pos.y - *arg6;
        temp_f0_3 = func_80086B30(temp_f20, sp4C);
        if (!(flags & 0x80)) {
            temp_f2 = func_80086760(camera->fov * 0.4f * (M_PI / 180)) * sp4C;
            if (temp_f2 < temp_f20) {
                *arg6 += (temp_f20 - temp_f2);
                temp_f20 = temp_f2;
            } else if (temp_f20 < -temp_f2) {
                *arg6 += (temp_f20 + temp_f2);
                temp_f20 = -temp_f2;
            }
            sp78.y -= temp_f20;
        } else {
            if (0.34906584f < temp_f0_3) {
                phi_f14 = 1.0f - sin_rad(temp_f0_3 - 0.34906584f);
            } else if (temp_f0_3 < -0.17453292f) {
                phi_f14 = 1.0f - sin_rad(-0.17453292f - temp_f0_3);
            } else {
                phi_f14 = 1.0f;
            }

            sp78.y -= temp_f20 * phi_f14;
        }
        Camera_LERPCeilVec3f(&sp78, &camera->atActorOffset, 0.5f, 0.5f, 0.1f);
        camera->xzOffsetUpdateRate = 0.5f;
        camera->yOffsetUpdateRate = 0.5f;
    }

    sp6C.x = temp_s1->pos.x + camera->atActorOffset.x;
    sp6C.y = temp_s1->pos.y + camera->atActorOffset.y;
    sp6C.z = temp_s1->pos.z + camera->atActorOffset.z;
    Camera_LERPCeilVec3f(&sp6C, &camera->at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return true;
}

s32 Camera_CalcAtForHorse(Camera* camera, VecSph* eyeAtDir, f32 yOffset, f32* yPosOffset, s16 calcSlope) {
    Vec3f* at = &camera->at;
    Vec3f posOffsetTarget;
    Vec3f focalTarget;
    s32 pad[2];
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    Player* player = (Player*)camera->trackActor;
    PosRot horsePosRot;

    Actor_GetWorld(&horsePosRot, player->rideActor);

    if (EN_HORSE_CHECK_JUMPING((EnHorse*)player->rideActor)) {
        horsePosRot.pos.y -= 49.0f;
        *yPosOffset = Camera_LERPCeilF(horsePosRot.pos.y, *yPosOffset, 0.1f, 0.1f);
        camera->atLERPStepScale = Camera_LERPCeilF(0.4f, camera->atLERPStepScale, 0.2f, 0.02f);
    } else {
        *yPosOffset = Camera_LERPCeilF(horsePosRot.pos.y, *yPosOffset, 0.5f, 0.1f);
    }

    posOffsetTarget.x = 0.0f;
    posOffsetTarget.y = trackHeight + yOffset;
    posOffsetTarget.z = 0.0f;

    if (calcSlope != 0) {
        posOffsetTarget.y -=
            Camera_CalcSlopeYAdj(&camera->floorNorm, camera->trackActorPosRot.rot.y, eyeAtDir->yaw, 25.0f);
    }

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->atActorOffset, camera->xzOffsetUpdateRate,
                         camera->yOffsetUpdateRate, 0.1f);

    focalTarget.x = camera->atActorOffset.x + horsePosRot.pos.x;
    focalTarget.y = camera->atActorOffset.y + horsePosRot.pos.y;
    focalTarget.z = camera->atActorOffset.z + horsePosRot.pos.z;
    Camera_LERPCeilVec3f(&focalTarget, at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);

    return true;
}

f32 Camera_ClampDist1(Camera* camera, f32 dist, f32 minDist, f32 maxDist, s16 timer) {
    f32 distTarget;

    if ((dist / maxDist) > 1.2f) {
        distTarget = maxDist;

        camera->rUpdateRateInv = 20.0f / (dist / maxDist);
        if ((20.0f / (dist / maxDist)) < 10) {
            camera->rUpdateRateInv = 10;
        }
    } else if (dist < minDist) {
        distTarget = minDist;

        camera->rUpdateRateInv = Camera_LERPCeilF((timer != 0) ? 10.0f : 20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else if (maxDist < dist) {
        distTarget = maxDist;

        camera->rUpdateRateInv = Camera_LERPCeilF((timer != 0) ? 10.0f : 20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else {
        distTarget = dist;

        camera->rUpdateRateInv = Camera_LERPCeilF((timer != 0) ? 20.0f : 1.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    }

    return Camera_LERPCeilF(distTarget, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
}

f32 Camera_ClampDist2(Camera* camera, f32 dist, f32 minDist, f32 maxDist, s16 timer) {
    f32 distTarget;

    if (timer == 0) {
        distTarget = ((maxDist * 0.25f) > 80.0f) ? maxDist * 0.25f : 80.0f;

        camera->rUpdateRateInv = Camera_LERPCeilF(1000.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else if ((dist / maxDist) > 1.2f) {
        distTarget = maxDist;

        camera->rUpdateRateInv = 20.0f / (dist / maxDist);
        if ((20.0f / (dist / maxDist)) < 10.0f) {
            camera->rUpdateRateInv = 10.0f;
        }
    } else if (dist < minDist) {
        distTarget = minDist;

        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else if (maxDist < dist) {
        distTarget = maxDist;

        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else {
        distTarget = dist;

        camera->rUpdateRateInv = Camera_LERPCeilF(1.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    }

    return Camera_LERPCeilF(distTarget, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
}

/**
 * Calculates the camera pitch to update to as player moves around
 * The pitch target starts with a default value on a flat surface, then standing on a sloped surface will create an
 * offset in default pitch Camera "AI" for pitch
 */
s16 Camera_CalcDefaultPitch(Camera* camera, s16 pitch, s16 flatSurfacePitchTarget, s16 slopePitchAdj) {
    f32 attenuation;
    f32 pitchStepScale;
    f32 t;
    s16 slopePitchAdjAttenuated;
    s16 pitchMag = ABS(pitch);
    s16 pitchTarget;

    // if slopePitchAdj is positive, then it is attenuated by a factor of Math_CosS(slopePitchAdj)
    slopePitchAdjAttenuated = slopePitchAdj > 0 ? (s16)(Math_CosS(slopePitchAdj) * slopePitchAdj) : slopePitchAdj;
    pitchTarget = flatSurfacePitchTarget - slopePitchAdjAttenuated;

    if (ABS(pitchTarget) < pitchMag) {
        // pitch is decreasing
        pitchStepScale = (1.0f / camera->pitchUpdateRateInv) * 3.0f;
    } else {
        // pitch is increasing
        t = pitchMag * (1.0f / 0x38A4); // ratio of pitch to 79.7 degrees
        attenuation =
            Camera_QuadraticAttenuation(0.8f, 1.0f - t); // attenuation starts above pitch = 0xB54 (16 degrees)
        pitchStepScale = (1.0f / camera->pitchUpdateRateInv) * attenuation;
    }

    return Camera_LERPCeilS(pitchTarget, pitch, pitchStepScale, 5);
}

/**
 * Calculates the camera pitch to update to as player moves around
 * The yaw target starts with a default value, but will only update to that target yaw in proportion to players velocity
 * No velocity means yaw does not update
 * Camera "AI" for yaw
 */
s16 Camera_CalcDefaultYaw(Camera* camera, s16 yaw, s16 target, f32 attenuationYawDiffRange,
                          f32 attenuationYawDiffInterpParam) {
    f32 attenuationYawDiffAdj;
    f32 attenuationYawDiff;
    f32 attenuationYawDiffParam;
    f32 attenuationSpeedRatio;
    f32 yawUpdRate;
    s16 yawDiffToTarget;

    if (camera->xzSpeed > 0.001f) {
        yawDiffToTarget = target - BINANG_ROT180(yaw);
        attenuationYawDiffParam = BINANG_ROT180(yawDiffToTarget) / (f32)0x8000;
    } else {
        yawDiffToTarget = target - BINANG_ROT180(yaw);
        attenuationYawDiffParam = 0.3f;
    }

    // Attenuation 1 based on YawDiffToTarget.
    attenuationYawDiff = Camera_QuadraticAttenuation(attenuationYawDiffRange, attenuationYawDiffParam);
    attenuationYawDiffAdj = LERPIMP(attenuationYawDiff, 1.0f, attenuationYawDiffInterpParam);
    attenuationYawDiffAdj = CLAMP_MIN(attenuationYawDiffAdj, 0.0f);

    // attenuation 2 based on SpeedRatio
    attenuationSpeedRatio = Camera_QuadraticAttenuation(0.5f, camera->speedRatio);

    yawUpdRate = 1.0f / camera->yawUpdateRateInv;
    return yaw + (s16)(yawDiffToTarget * attenuationYawDiffAdj * attenuationSpeedRatio * yawUpdRate);
}

// TODO: May be f32* return, not void
void func_800CED90(Camera* camera, VecSph* arg1, VecSph* arg2, f32 arg3, f32 arg4, SwingAnimation* swing2, s16* flags) {
    SwingAnimation* swing = swing2;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f peekAroundPoint;
    s32 sp8C = 0;
    f32 sp88;
    s32 checkEyeBit1;
    s32 checkEyeBit2;
    CamColChk sp58;
    VecSph sp50;
    Vec3f* sp30;

    if (swing->unk_64 == 1) {
        if (arg3 < (sp88 = OLib_Vec3fDist(at, &swing->collisionClosePoint))) {
        dummy:;
            swing->unk_64 = 0;
        } else if ((sp88 = Math3D_SignedDistanceFromPlane(swing->eyeAtColChk.norm.x, swing->eyeAtColChk.norm.y,
                                                          swing->eyeAtColChk.norm.z, swing->eyeAtColChk.poly->dist,
                                                          at)) > 0.0f) {
            swing->unk_64 = 0;
        } else if ((sp88 = OLib_Vec3fDist(eye, &swing->eyeAtColChk.pos)) < 10.0f) {
            swing->unk_64 = 0;
        } else if ((sp88 = Math3D_SignedDistanceFromPlane(swing->atEyeColChk.norm.x, swing->atEyeColChk.norm.y,
                                                          swing->atEyeColChk.norm.z, swing->atEyeColChk.poly->dist,
                                                          eye)) > 0.0f) {
            swing->unk_64 = 0;
        } else if (swing->atEyeColChk.norm.y > 0.50f) {
            swing->unk_64 = 0;
        } else {
            Math3D_AngleBetweenVectors(&camera->trackActorOffset, &swing->eyeAtColChk.norm, &sp88);
            if (sp88 > 0.0f) {
                swing->unk_64 = 0;
            }
        }

        if (swing->unk_64 == 1) {
            sp8C = 2;
        }
    } else if (swing->unk_64 == 2) {
        swing->unk_64 = 0;
    }

    if (sp8C == 0) {
        if (*flags & 2) {
            checkEyeBit1 = 1 << 1;
        } else {
            checkEyeBit1 = 0;
        }

        if (swing->unk_64 != 1) {
            checkEyeBit2 = 1 << 0;
        } else {
            checkEyeBit2 = 0;
        }

        sp8C =
            func_800CD44C(camera, arg1, &swing->atEyeColChk, &swing->eyeAtColChk, ((s16)checkEyeBit2 | checkEyeBit1));
    }

    switch (sp8C) {
        default:
            sp30 = &swing->atEyeColChk.pos;
            *flags &= ~0x1000;
            swing->swingUpdateRate = arg4;
            *eye = *sp30;
            break;
        case 1:
            Camera_BgCheckCorner(&swing->collisionClosePoint, &camera->at, &camera->eyeNext, &swing->atEyeColChk,
                                 &swing->eyeAtColChk);
        case 2:
            peekAroundPoint.x = swing->collisionClosePoint.x + (swing->atEyeColChk.norm.x + swing->eyeAtColChk.norm.x);
            peekAroundPoint.y = swing->collisionClosePoint.y + (swing->atEyeColChk.norm.y + swing->eyeAtColChk.norm.y);
            peekAroundPoint.z = swing->collisionClosePoint.z + (swing->atEyeColChk.norm.z + swing->eyeAtColChk.norm.z);

            sp30 = &camera->eyeNext;
            OLib_Vec3fDiffToVecSphGeo(&sp50, at, &peekAroundPoint);
            sp50.r = arg1->r;
            swing->unk_64 = 1;
            swing->swingUpdateRate = 1.5f;
            OLib_VecSphAddToVec3f(&sp58.pos, at, &sp50);
            if (func_800CBC84(camera, &swing->eyeAtColChk.pos, &sp58, 0) == 0) {
                sp50.yaw =
                    Camera_AngleDiffAndScale(arg1->yaw, arg2->yaw, (camera->speedRatio * 0.5f) + 0.5f) + arg2->yaw;
                sp50.pitch = Camera_AngleDiffAndScale(arg1->pitch, arg2->pitch, (camera->speedRatio * 0.5f) + 0.5f) +
                             arg2->pitch;
                if (swing->atEyeColChk.sphNorm.pitch < 0x2AA8) { // 60 degrees
                    swing->yaw = sp50.yaw;
                    swing->pitch = sp50.pitch;
                } else {
                    swing->yaw = arg1->yaw;
                    swing->pitch = arg1->pitch;
                }
            }
            *eye = *sp30 = sp58.pos;
            break;
        case 3:
        case 6:
            sp30 = &swing->atEyeColChk.pos;
            sp88 = OLib_Vec3fDist(at, sp30);
            if (sp88 < 60.0f) {
                sp50.yaw = Camera_AngleDiffAndScale(arg1->yaw, arg2->yaw, camera->speedRatio) + arg2->yaw;
                if (*flags & 0x1000) {
                    sp50.pitch = arg2->pitch;
                } else {
                    sp50.pitch = Math_CosS(swing->atEyeColChk.sphNorm.pitch) * 0x3FFC;
                }
                sp50.r = 60.0f - sp88;
                OLib_VecSphAddToVec3f(&sp58.pos, sp30, &sp50);
            } else {
                sp50.yaw = Camera_AngleDiffAndScale(arg1->yaw, arg2->yaw, camera->speedRatio) + arg2->yaw;
                sp50.pitch = Camera_AngleDiffAndScale(arg1->pitch, arg2->pitch, camera->speedRatio) + arg2->pitch;
                sp50.r = arg1->r;
                OLib_VecSphAddToVec3f(&sp58.pos, at, &sp50);
            }
            func_800CBC84(camera, at, &sp58, 0);
            *eye = sp58.pos;
            break;
    }
}
