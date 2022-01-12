#include "prevent_bss_reordering.h"
#include "ultra64.h"
#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

/**
 * @file camera.c
 * Implements the camera system. Camera functionality depends on the current combination of
 * setting and mode.
 *
 * When working with the camera, you should be familiar with MM's coordinate system.
 * Relative to the camera, the coordinate system follows the right hand rule:
 *          +X points right.
 *          +Y points up.
 *          +Z points out of the screen.
 *
 * You should also be familiar with Euler angles: 'pitch', 'yaw', and 'roll'.
 *      pitch: rotation about the X-axis, measured from +Y.
 *          Unlike yaw and roll, pitch is bounded in +-0x4000 (90 degrees).
 *          Pitch is 0 when the camera points parallel to the xz-plane (+Y points straight up).
 *
 *      yaw: rotation about the Y-axis, measured from (absolute) +Z.
 *          Positive yaw rotates clockwise, towards +X.
 *
 *      roll: rotation about the Z-axis, measured from the camera's right direction.
 *          Unfortunately, it's weird: For some reason, roll is flipped. Positive roll makes the camera
 *          rotate counterclockwise, which means the WORLD rotates clockwise. Luckily roll is rarely
 *          used.
 *
 *      Remember the right hand rule: make a thumbs-up with your right hand, stick your thumb in the
 *      +direction (except for roll), and the angle follows the rotation of your curled fingers.
 *
 * Illustrations:
 * Following the right hand rule, each hidden axis's positive direction points out of the screen.
 *
 *       YZ-Plane (pitch)        XZ-Plane (yaw)          XY-Plane (roll -- Note flipped)
 *          +Y                      -Z                      +Y
 *           ^                       ^ (into the             ^
 *         --|--                     |   screen)             |<-
 * +pitch /  |  \ -pitch             |                       |  \ -roll
 *       v   |   v                   |                       |   |
 * +Z <------O------> -Z   -X <------O------> +X   -X <------O------> +X
 *           |                   ^   |   ^                   |   |
 *           |                    \  |  /                    |  / +roll
 *           |               -yaw  --|--  +yaw               |<-
 *           v                       v                       v
 *          -Y                      +Z                      -Y
 *
 */

void func_800DDFE0(Camera* camera);
s32 Camera_ChangeMode(Camera* camera, s16 mode);
s16 Camera_ChangeSettingFlags(Camera* camera, s16 setting, s16 flags);
s16 Camera_UnsetFlags(Camera* camera, s16 flags);

#include "z_camera_data.c"

GlobalContext* D_801EDC28;
SwingAnimation D_801EDC30[4];
Vec3f D_801EDDD0;
Vec3f D_801EDDE0;
Vec3f D_801EDDF0;

#define CAM_CHANGE_SET_FLAG_1 (1 << 0)
#define CAM_CHANGE_SET_FLAG_2 (1 << 1)
#define CAM_CHANGE_SET_FLAG_4 (1 << 2)
#define CAM_CHANGE_SET_FLAG_8 (1 << 3)

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
s32 Camera_BGCheckInfo(Camera* camera, Vec3f* from, CamColChk* to) {
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
s32 Camera_BGCheck(Camera* camera, Vec3f* from, Vec3f* to) {
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
        Camera_BGCheckInfo(camera, &playerPos, &D_801EDC00);
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

// OoT func_80044ADC
f32 func_800CCCEC(Camera* camera, s16 arg1) {
    static s32 D_801B9E5C = 0;
    static f32 D_801B9E60 = 0.0f;
    Vec3f sp7C;
    Vec3f sp70;
    PosRot sp5C;    // 5C-60-64 -- 68-6A-6C
    CamColChk sp34; // 34-38-3C -- 40-44-48 -- 4C -- 50-54-56 -- 58
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

        if ((Camera_BGCheckInfo(camera, &sp70, &sp34) != 0) && (Camera_CheckOOB(camera, &sp7C, &sp70) != 0)) {
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
        if ((Camera_BGCheckInfo(camera, &sp70, &sp34) != 0) && (Camera_CheckOOB(camera, &sp7C, &sp70) != 0)) {
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
    Vec3f* at = &camera->at; // 28-2C-30
    s32 pad1[2];
    s32 atEyeBgId; // 60
    s32 eyeAtBgId; // 5C
    s32 ret;       // 58
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

        eyeAtBgId = Camera_BGCheckInfo(camera, &camera->eye, atChk);

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

    if (Camera_BGCheck(camera, &sp38, &sp44)) {
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

/*===============================================================*/
/*     Camera Action Functions (Chosen by Settings & Modes)      */
/*===============================================================*/

s32 Camera_Noop(Camera* camera) {
    return true;
}

// SP, FLOATS - Many temps reused to get the stack pointer down, even though it doesn't seem logical
#ifdef NON_EQUIVALENT
s32 Camera_Normal1(Camera* camera) {
    CameraModeValue* values;
    f32 phi_f16_2;
    Vec3f spD8; // D8-DC-E0
    f32 spD4;
    f32 spD0;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    VecSph spB4; // B4-B8-BA
    VecSph spAC; // AC-B0-B2
    VecSph spA4; // A4-A8-AA
    VecSph sp9C; // 9C-A0-A2
    VecSph sp74; // 74-78-7A
    s16 sp72;
    f32 sp6C;
    VecSph sp64; // 64-68-6A
    CollisionPoly* sp60;
    f32 sp88 = Camera_GetTrackedActorHeight(camera);
    s32 sp5C; // BgID
    f32 sp58;
    f32 phi_f2;
    // Vec3f *sp48;
    // Vec3f *sp44;

    // f32 phi_f0;
    f32 phi_f2_2;
    f32 phi_f0_4;
    s32 phi_v1_2;
    Vec3f* sp4C = &camera->eye;
    PosRot* sp40 = &camera->trackActorPosRot;
    // f32 phi_f16_5;

    s16 phi_a0;
    s16 temp_a0_3; // May be fake
    Vec3f* new_var3;

    Normal1FixedData* fixedData = CAM_GET_STATIC_DATA(Normal1);
    Normal1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Normal1);

    // sp48 = &camera->at;
    // sp4C;/
    // sp44 = &camera->eyeNext;
    // sp40;
    // sp88;

    values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
    fixedData->unk_00 = READ_STATIC_DATA_VAL * (sp88 * 0.01f * (0.8f - ((68.0f / sp88) * -0.2f)));
    fixedData->unk_04 = READ_STATIC_DATA_VAL * (sp88 * 0.01f * (0.8f - ((68.0f / sp88) * -0.2f)));
    fixedData->unk_08 = READ_STATIC_DATA_VAL * (sp88 * 0.01f * (0.8f - ((68.0f / sp88) * -0.2f)));
    fixedData->unk_04 = fixedData->unk_08 - (fixedData->unk_08 - fixedData->unk_04);

    if (RELOAD_PARAMS) {
        fixedData->unk_20 = (s16)((READ_STATIC_DATA_VAL * 182.04167f) + .5f);
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = 40.0f - (40.0f - fixedData->unk_0C);
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_14 = 1.0f - (1.0f - fixedData->unk_14);
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_1C = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_22 = READ_STATIC_DATA_VAL;
    }

    sCameraInterfaceFlags = fixedData->unk_22;
    OLib_Vec3fDiffToVecSphGeo(&spA4, &camera->at, sp4C);
    OLib_Vec3fDiffToVecSphGeo(&sp9C, &camera->at, &camera->eyeNext);

    switch (camera->actionFuncState) {
        case 20:
            Camera_SetUpdateRatesFastYaw(camera);
            // fallthrough?
        case 0:
            dynamicData->unk_0C = 1;
            if (!(fixedData->unk_22 & NORM1_FLG_8) && (camera->actionFuncState != 20)) {
                dynamicData->unk_0C |= 0x1000;
            }
            // fallthrough?
        case 10:
            if (camera->actionFuncState == 10) {
                dynamicData->unk_0C = 0;
            }
            dynamicData->unk_08 = 0;
            D_801EDC30[camera->camId].yaw = D_801EDC30[camera->camId].pitch = D_801EDC30[camera->camId].unk_64 = 0;
            dynamicData->unk_0A = 0x514;
            D_801EDC30[camera->camId].swingUpdateRate = fixedData->unk_0C;
            dynamicData->unk_00 = camera->trackActorPosRot.pos.y;
            dynamicData->unk_04 = camera->xzSpeed;
            D_801EDC30[camera->camId].unk_66 = 0;
            sUpdateCameraDirection = false;
            dynamicData->unk_10 = 120.0f;
    }

    camera->actionFuncState = 1;
    sUpdateCameraDirection = true;

    if ((camera->speedRatio < 0.01f) || (dynamicData->unk_0A > 0x4B0)) {
        if (dynamicData->unk_0A > -0x4B0) {
            dynamicData->unk_0A--;
        }
    } else {
        dynamicData->unk_0A = 0x4B0;
    }

    if (func_800CB950(camera)) {
        dynamicData->unk_00 = camera->trackActorPosRot.pos.y;
    }

    if (dynamicData->unk_0C & 0x1000) {
        spC8 = camera->speedRatio;
    } else {
        spC8 = ((camera->speedRatio * 3.0f) + 1.0f) * 0.25f;
    }

    spD8 = camera->atActorOffset;
    spD8.y -= sp88 + fixedData->unk_00;
    spC4 = Camera_Vec3fMagnitude(&spD8);

    if ((fixedData->unk_04 + fixedData->unk_08) < spC4) {
        spC4 = 1.0f;
    } else {
        spC4 = spC4 / (fixedData->unk_04 + fixedData->unk_08);
    }

    // Everything above matches except stack pointers
    // PERM_RANDOMIZE(

    phi_f16_2 = 0.2f;

    phi_f2 = (camera->xzSpeed - dynamicData->unk_04) * 0.2f;
    phi_f0_4 = phi_f2;
    if (phi_f2 < 0.0f) {
        phi_f0_4 = 0.0f;
    }

    spC0 = OLib_ClampMaxDist(SQ(phi_f0_4), 1.0f);
    camera->yOffsetUpdateRate =
        Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, (0.5f * spC8) + (0.5f * spC4), 0.0001f);
    camera->xzOffsetUpdateRate =
        Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, (0.5f * spC8) + (0.5f * spC4), 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, (0.5f * spC8) + (0.5f * spC4), 0.0001f);

    if (D_801EDC30[camera->camId].unk_64 == 1) {
        phi_f2 = 0.5f;
    } else {
        phi_f2 = (0.5f * spC8) + (0.5f * spC4);
    }

    dynamicData->unk_04 = camera->xzSpeed;

    if (D_801EDC30[camera->camId].unk_66 != 0) {
        camera->yawUpdateRateInv =
            Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + D_801EDC30[camera->camId].swingUpdateRate,
                             camera->yawUpdateRateInv, phi_f2, 0.1f);
        if (fixedData->unk_22 & NORM1_FLG_8) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(100.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else {
            camera->pitchUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + 16.0f,
                                                          camera->pitchUpdateRateInv, 0.2f, 0.1f);
        }
        D_801EDC30[camera->camId].unk_66--;
    } else {
        camera->yawUpdateRateInv = Camera_LERPCeilF(D_801EDC30[camera->camId].swingUpdateRate -
                                                        (D_801EDC30[camera->camId].swingUpdateRate * 0.7f * spC0),
                                                    camera->yawUpdateRateInv, phi_f2, 0.1f);
        if ((fixedData->unk_22 & NORM1_FLG_8) && (camera->speedRatio > 0.01f)) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(100.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else if (D_801ED920 != NULL) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(32.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        }
    }

    if (fixedData->unk_22 & NORM1_FLG_1) {
        if (!spC8) {}
        temp_a0_3 = func_800CC9C0(camera, spA4.yaw + 0x8000, dynamicData->unk_0C & 1);
        phi_f2 = (1.0f / fixedData->unk_10) * 0.7f;
        phi_f16_2 = (1.0f / fixedData->unk_10) * 0.3f * (1.0f - camera->speedRatio);
        spD0 = phi_f16_2;
        dynamicData->unk_08 = Camera_LERPCeilS(temp_a0_3, dynamicData->unk_08, phi_f2 + phi_f16_2, 5);
    } else {
        dynamicData->unk_08 = 0;
    }

    if ((D_801EDC30[camera->camId].unk_64 == 1) && (fixedData->unk_00 > -40.0f)) {
        phi_f0_4 = Math_SinS(D_801EDC30[camera->camId].pitch);
        phi_f2 = fixedData->unk_00;
        phi_f2 = phi_f2 * (1.0f - phi_f0_4); // TODO: phi_f2 should not be on the LHS and RHS
        // phi_f2 = fixedData->unk_00 * (1.0f - phi_f0_4);
        camera->yawUpdateRateInv = 80.0f;
        camera->pitchUpdateRateInv = 80.0f;
        phi_f2_2 = ((-40.0f) * phi_f0_4) + phi_f2;
        phi_f16_2 = phi_f0_4;
    } else {
        phi_f2_2 = fixedData->unk_00;
    }

    if (fixedData->unk_22 & (NORM1_FLG_40 | NORM1_FLG_20)) {
        if (camera->dist < fixedData->unk_04) {
            phi_f16_2 = 0.0f;
        } else if (fixedData->unk_08 < camera->dist) {
            phi_f16_2 = 1.0f;
        } else if (fixedData->unk_08 == fixedData->unk_04) {
            phi_f16_2 = 1.0f;
        } else {
            // phi_f16_2 = camera->dist - fixedData->unk_04;
            spD4 = (camera->dist - fixedData->unk_04) / (fixedData->unk_08 - fixedData->unk_04);
            phi_f16_2 = spD4;
        }

        func_800CDA14(camera, &sp9C, phi_f2_2, 25.0f * phi_f16_2 * camera->speedRatio);
        dynamicData->unk_10 = 120.0f;
        spD0 = phi_f16_2;
    } else if ((fixedData->unk_22 & NORM1_FLG_80) && (dynamicData->unk_0A < 0)) {
        phi_f0_4 = dynamicData->unk_0A / -1200.0f; // May be used to swap $f registers
        func_800CDA14(camera, &sp9C,
                      phi_f2_2 - ((phi_f2_2 - ((0.8f - ((68.0f / sp88) * -0.2f)) * sp88 * -0.45f)) * phi_f0_4 * 0.75f),
                      10.0f * phi_f0_4);
        dynamicData->unk_10 = 120.0f;
        spD0 = phi_f16_2;
        if (0) {}
    } else if (fixedData->unk_22 & NORM1_FLG_8) {
        spD0 = phi_f16_2;
        func_800CD834(camera, &sp9C, fixedData->unk_00, &dynamicData->unk_00, dynamicData->unk_10);
        if (dynamicData->unk_10 > 20.0f) {
            dynamicData->unk_10 -= 0.2f;
        }
    } else {
        spD0 = phi_f16_2;
        Camera_CalcAtDefault(camera, &sp9C, phi_f2_2, fixedData->unk_22 & NORM1_FLG_1);
        dynamicData->unk_10 = 120.0f;
    }

    phi_f16_2 = spD0;
    OLib_Vec3fDiffToVecSphGeo(&spB4, &camera->at, &camera->eyeNext);
    if ((fixedData->unk_22 & NORM1_FLG_80) && (dynamicData->unk_0A < 0)) {
        if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
            switch (((Player*)camera->trackActor)->transformation) {
                case PLAYER_FORM_HUMAN:
                    phi_f16_2 = 66.0f;
                    break;
                case PLAYER_FORM_DEKU:
                    phi_f16_2 = 66.0f;
                    break;
                case PLAYER_FORM_ZORA:
                    phi_f16_2 = 115.0f;
                    break;
                case PLAYER_FORM_GORON:
                    phi_f16_2 = 115.0f;
                    break;
                case PLAYER_FORM_FIERCE_DEITY:
                    phi_f16_2 = fixedData->unk_04;
                    break;
                default:
                    phi_f16_2 = fixedData->unk_04;
                    break;
            }
        }
        phi_f0_4 = Camera_ClampDist2(camera, spB4.r, phi_f16_2, phi_f16_2, 0);
    } else if (fixedData->unk_22 & NORM1_FLG_80) {
        phi_f0_4 = Camera_ClampDist2(camera, spB4.r, fixedData->unk_04, fixedData->unk_08, 1);
    } else {
        phi_f0_4 = Camera_ClampDist1(camera, spB4.r, fixedData->unk_04, fixedData->unk_08, dynamicData->unk_0A > 0);
    }

    camera->dist = spB4.r = phi_f0_4;

    if (D_801EDC30[camera->camId].unk_64 != 0) {
        if (phi_v1_2) {}
        spB4.pitch = Camera_LERPCeilS(D_801EDC30[camera->camId].pitch, sp9C.pitch, 1.0f / camera->yawUpdateRateInv, 5);
        spB4.yaw = Camera_LERPCeilS(D_801EDC30[camera->camId].yaw, sp9C.yaw, 1.0f / camera->yawUpdateRateInv, 5);
    } else {
        if (fixedData->unk_22 & NORM1_FLG_20) {
            spB4.yaw = sp9C.yaw;
            spB4.pitch = sp9C.pitch;
            camera->actionFuncState = 20;
        } else {
            if (D_801ED920 != NULL) {
                if (sp40) {}
                new_var3 = &D_801ED920->world.pos;
                OLib_Vec3fDiffToVecSphGeo(&sp74, &sp40->pos, new_var3); // TODO: arg0 & arg1 swapped
                sp72 = sp40->rot.y - sp74.yaw;
                // Interface and shrink-window flags
                if ((fixedData->unk_22 & 0xFF00) == 0xFF00) {
                    sp6C = 1.0f;
                } else {
                    sp6C = 1.0f - (ABS(sp72) / 10922.0f);
                }

                if (ABS((s16)(sp9C.yaw - sp74.yaw)) < 0x4000) {
                    sp74.yaw += 0x8000;
                }

                if (!(fixedData->unk_22 & NORM1_FLG_8) || !func_800CB924(camera)) {
                    spB4.yaw = Camera_CalcDefaultYaw(camera, sp9C.yaw, (s16)(sp40->rot.y - (s16)(sp72 * sp6C)),
                                                     fixedData->unk_14, spC0);
                }

                if (!(fixedData->unk_22 & NORM1_FLG_8) || (camera->speedRatio < 0.01f)) {
                    spB4.pitch = Camera_CalcDefaultPitch(
                        camera, sp9C.pitch, fixedData->unk_20 + (s16)((fixedData->unk_20 - sp74.pitch) * sp6C * 0.75f),
                        dynamicData->unk_08);
                }
            dummy:; // TODO: Will this be needed?
            } else if (fixedData->unk_22 & NORM1_FLG_2) {
                if ((camera->speedRatio > 0.1f) || (dynamicData->unk_0A > 0x4B0)) {
                    OLib_Vec3fToVecSphGeo(&sp64, &camera->trackActorOffset);
                    if (!(fixedData->unk_22 & NORM1_FLG_8) || !func_800CB924(camera)) {
                        spB4.yaw = Camera_CalcDefaultYaw(camera, sp9C.yaw, sp64.yaw, fixedData->unk_14, spC0);
                    }
                    if (!(fixedData->unk_22 & NORM1_FLG_8)) {
                        spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, fixedData->unk_20, dynamicData->unk_08);
                    } else if ((camera->trackActorOffset.y > 0.0f) && func_800CB924(camera)) {
                        spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, fixedData->unk_20, dynamicData->unk_08);
                    }
                } else {
                    spB4.yaw = sp9C.yaw;
                    spB4.pitch = sp9C.pitch;
                dummy4:; // TODO: Will this be needed?
                }
            } else {
                spB4.yaw = Camera_CalcDefaultYaw(camera, sp9C.yaw, sp40->rot.y, fixedData->unk_14, spC0);
                if (!(fixedData->unk_22 & NORM1_FLG_8) || (camera->speedRatio < 0.1f)) {
                    spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, fixedData->unk_20, dynamicData->unk_08);
                }
            }
        }
    }

    // 76.9 degrees
    if (spB4.pitch > 0x36B0) {
        spB4.pitch = 0x36B0;
    }

    // -76.9 degrees
    if (spB4.pitch < -0x36B0) {
        spB4.pitch = -0x36B0;
    }

    OLib_VecSphAddToVec3f(&camera->eyeNext, &camera->at, &spB4);
    if ((camera->status == CAM_STATUS_ACTIVE) && !(fixedData->unk_22 & NORM1_FLG_10) && (spC4 <= 0.9f)) {

        if (func_800CBA7C(camera) == 0) {
            func_800CED90(camera, &spB4, &sp9C, fixedData->unk_04, fixedData->unk_0C, &D_801EDC30[camera->camId],
                          &dynamicData->unk_0C);
            sp58 = BgCheck_CameraRaycastFloor2(&camera->globalCtx->colCtx, &sp60, &sp5C, sp4C);
            if ((fixedData->unk_22 & NORM1_FLG_8) && func_800CB924(camera)) {
                phi_f16_2 = 25.0f;
            } else {
                phi_f16_2 = 5.0f;
            }
            spD0 = sp4C->y; // TODO: another fake reuse of temp
            phi_f0_4 = sp4C->y;
            phi_f0_4 -= sp58;
            // new_var2 = sp4C->y;
            if ((sp58 != BGCHECK_Y_MIN) && (phi_f0_4 < phi_f16_2)) {
                sp4C->y = sp58 + phi_f16_2;
            } else if ((camera->waterYPos != camera->playerFloorHeight) && ((spD0 - camera->waterYPos) < 5.0f) &&
                       ((spD0 - camera->waterYPos) > -5.0f)) {
                sp4C->y = camera->waterYPos + 5.0f;
            }
        }

        OLib_Vec3fDiffToVecSphGeo(&spAC, sp4C, &camera->at);
        camera->inputDir.x = spAC.pitch;
        camera->inputDir.y = spAC.yaw;
        camera->inputDir.z = 0;
        if (gSaveContext.health < 17) {
            phi_v1_2 = (camera->globalCtx->state.frames << 0x18);
            phi_v1_2 = (s16)((phi_v1_2 >> 0x15) & 0xFD68);
            camera->inputDir.y += phi_v1_2;
        }
    } else {
        D_801EDC30[camera->camId].swingUpdateRate = fixedData->unk_0C;
        D_801EDC30[camera->camId].unk_64 = 0;
        sUpdateCameraDirection = false;
        *sp4C = camera->eyeNext;
    }

    // Everything below OLib_Vec3fDiffToVecSphGeo matches except stack pointers
    // )

    phi_f2 = (gSaveContext.health <= 16) ? 0.8f : 1.0f;
    camera->fov = Camera_LERPCeilF(fixedData->unk_18 * phi_f2, camera->fov, camera->fovUpdateRate, 0.1f);

    if (fixedData->unk_22 & NORM1_FLG_4) {
        spD4 = Math_SinS((s16)(spA4.yaw - spB4.yaw));
        camera->roll =
            Camera_LERPCeilS(((Rand_ZeroOne() - 0.5f) * 500.0f * camera->speedRatio) + (spD4 * spD4 * spD4 * 10000.0f),
                             camera->roll, 0.1f, 5);
    } else {
        if (gSaveContext.health <= 16) {
            phi_a0 = (Rand_ZeroOne() - 0.5f) * 100.0f * camera->speedRatio;
        } else {
            phi_a0 = 0.0f;
        }
        camera->roll = Camera_LERPCeilS(phi_a0, camera->roll, 0.2f, 5);
    }

    camera->atLERPStepScale = Camera_ClampLERPScale(camera, fixedData->unk_1C);
    dynamicData->unk_0C &= ~1;
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal1.s")
#endif


/**
 * Unused Camera RemoteBomb Setting
 */
s32 Camera_Normal2(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Riding Epona and Zora
 */
s32 Camera_Normal3(Camera* camera) {
    Normal3FixedData* fixedData = CAM_GET_STATIC_DATA(Normal3);
    Normal3DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Normal3);
    f32 sp8C;
    f32 sp90;
    f32 temp_f2; // multi-use temp
    f32 sp88;
    VecSph sp80;
    VecSph sp78;
    VecSph sp70;
    VecSph sp68;
    f32 phi_f2;
    s16 sp62;
    s16 phi_v1_2;
    Player* player = (Player*)camera->trackActor;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* playerPosRot = &camera->trackActorPosRot;

    temp_f2 = Camera_GetTrackedActorHeight(camera);

    if ((camera->setting == CAM_SET_HORSE) && (player->rideActor == NULL)) {
        Camera_ChangeSettingFlags(camera, camera->prevSetting, CAM_CHANGE_SET_FLAG_2);
        return true;
    }

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        temp_f2 = SCALED_STATIC_DATA(temp_f2);

        fixedData->yOffset = READ_STATIC_DATA_VAL * temp_f2;
        fixedData->distMin = READ_STATIC_DATA_VAL * temp_f2;
        fixedData->distMax = READ_STATIC_DATA_VAL * temp_f2;
        fixedData->pitchTarget = DEGF_TO_BINANG(READ_STATIC_DATA_VAL);
        fixedData->yawUpdateRateInv = READ_STATIC_DATA_VAL;
        fixedData->pitchUpdateRateInv = READ_STATIC_DATA_VAL;
        fixedData->fovTarget = READ_STATIC_DATA_VAL;
        fixedData->maxAtLERPScale = READ_SCALED_STATIC_DATA_VAL;
        fixedData->flags = READ_STATIC_DATA_VAL;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp70, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&sp68, at, eyeNext);
    sUpdateCameraDirection = true;
    sCameraInterfaceFlags = fixedData->flags;

    phi_v1_2 = camera->actionFuncState;
    if (!(((phi_v1_2 == 0) || (phi_v1_2 == 10)) || (phi_v1_2 == 20))) {
    } else {
        dynamicData->isZero = 0;
        dynamicData->curPitch = 0;
        dynamicData->yPosOffset = camera->playerFloorHeight;

        D_801EDC30[camera->camId].yaw = D_801EDC30[camera->camId].pitch = D_801EDC30[camera->camId].unk_64 = 0;
        D_801EDC30[camera->camId].swingUpdateRate = fixedData->yawUpdateRateInv;
        dynamicData->yawUpdateRate = SUB16(BINANG_ROT180(camera->trackActorPosRot.rot.y), sp70.yaw) * (1.0f / 6.0f);
        dynamicData->distTimer = 0;
        dynamicData->is1200 = 1200;

        if (fixedData->flags & NORM3_FLG_2) {
            dynamicData->yawTimer = 6;
            Camera_SetFlags(camera, CAM_FLAG2_20);
        } else {
            dynamicData->yawTimer = 0;
        }

        camera->actionFuncState = 1;
        D_801EDC30[camera->camId].unk_66 = 0;
        dynamicData->flag = 1;
    }

    if (dynamicData->distTimer != 0) {
        dynamicData->distTimer--;
    }

    sp90 = ((camera->speedRatio * 3.0f) + 1.0f) * 0.25f * 0.5f;
    sp8C = (temp_f2 = camera->speedRatio * 0.2f);

    if (D_801EDC30[camera->camId].unk_66 != 0) {
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + fixedData->yawUpdateRateInv,
                                                    camera->yawUpdateRateInv, sp90, 0.1f);
        camera->pitchUpdateRateInv =
            Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + 16.0f, camera->pitchUpdateRateInv, sp8C, 0.1f);
        D_801EDC30[camera->camId].unk_66--;
    } else {
        camera->yawUpdateRateInv = Camera_LERPCeilF(fixedData->yawUpdateRateInv, camera->yawUpdateRateInv, sp90, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, sp8C, 0.1f);
    }

    camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, sp90, 0.001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp8C, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, sp8C, 0.0001f);

    phi_v1_2 = func_800CC9C0(camera, BINANG_ROT180(sp70.yaw), dynamicData->flag & 1);
    temp_f2 = ((1.0f / fixedData->pitchUpdateRateInv) * 0.5f) * (1.0f - camera->speedRatio);
    dynamicData->curPitch =
        Camera_LERPCeilS(phi_v1_2, dynamicData->curPitch, ((1.0f / fixedData->pitchUpdateRateInv) * 0.5f) + temp_f2, 5);

    if ((fixedData->flags & NORM3_FLG_40) || (player->rideActor == NULL)) {
        Camera_CalcAtDefault(camera, &sp68, fixedData->yOffset, 1);
    } else {
        Camera_CalcAtForHorse(camera, &sp68, fixedData->yOffset, &dynamicData->yPosOffset, 1);
    }

    sp88 = (fixedData->distMax + fixedData->distMin) * 0.5f;
    OLib_Vec3fDiffToVecSphGeo(&sp80, at, eyeNext);
    temp_f2 = Camera_ClampDist1(camera, sp80.r, fixedData->distMin, fixedData->distMax, dynamicData->distTimer);

    phi_f2 = ((sp88 - temp_f2));
    phi_f2 *= 0.002f;
    camera->dist = sp80.r = temp_f2 + phi_f2;

    if (fixedData->flags & NORM3_FLG_80) {
        sp80.pitch = Camera_LERPCeilS(camera->trackActor->focus.rot.x - dynamicData->curPitch, sp68.pitch, 0.25f, 5);
    } else {
        sp62 = fixedData->pitchTarget - dynamicData->curPitch;
        sp80.pitch = Camera_LERPCeilS(sp62, sp68.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
    }

    sp80.pitch = CLAMP_MAX(sp80.pitch, 0x38A4); // 79.7 degrees

    // -30 degrees
    if (sp80.pitch < -0x1554) {
        sp80.pitch = -0x1554;
    }

    if (fixedData->flags & NORM3_FLG_80) {
        sp62 = SUB16(camera->trackActor->focus.rot.y, BINANG_ROT180(sp68.yaw));
        temp_f2 = 1.0f;
    } else {
        sp62 = SUB16(playerPosRot->rot.y, BINANG_ROT180(sp68.yaw));
        OLib_Vec3fToVecSphGeo(&sp78, &camera->trackActorOffset);
        phi_v1_2 = playerPosRot->rot.y - sp78.yaw;
        if (phi_v1_2 < 0) {
            phi_v1_2 *= -1;
        }

        if (phi_v1_2 < 0x555A) {
            temp_f2 = 1.0f;
        } else {
            temp_f2 = ((f32)0x8000 - phi_v1_2) / (f32)0x2AA6;
        }
    }

    sp90 = (sp62 * ((SQ(camera->speedRatio) * 0.8f) + 0.2f) * temp_f2) / camera->yawUpdateRateInv;
    if ((Camera_fabsf(sp90) > 150.0f) && (camera->speedRatio > 0.05f)) {
        sp80.yaw = sp68.yaw + sp90;
    }

    if (dynamicData->yawTimer > 0) {
        sp80.yaw += dynamicData->yawUpdateRate;
        dynamicData->yawTimer--;
        if (dynamicData->yawTimer == 0) {
            Camera_UnsetFlags(camera, CAM_FLAG2_20);
        }
    }

    OLib_VecSphAddToVec3f(eyeNext, at, &sp80);
    if (camera->status == CAM_STATUS_ACTIVE) {
        *eye = *eyeNext;
        func_800CBFA4(camera, at, eye, 0);
    } else {
        *eye = *eyeNext;
    }

    camera->fov = Camera_LERPCeilF(fixedData->fovTarget, camera->fov, camera->fovUpdateRate, 0.1f);
    if (fixedData->flags & NORM3_FLG_20) {
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.05f, 5);
    } else {
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
    }

    camera->atLERPStepScale = Camera_ClampLERPScale(camera, fixedData->maxAtLERPScale);
    dynamicData->flag &= ~1;
    return true;
}

/**
 * Used for the unknown Naname setting. 
 * Identical to Normal1 except reads camera scene data to apply a camera roll
 */
s32 Camera_Normal4(Camera* camera) {
    SubCamData* bgCamData;
    s16 roll;

    if (RELOAD_PARAMS) {
        bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
        D_801EDBF0 = bgCamData->rot.z;
    }

    roll = camera->roll;
    Camera_Normal1(camera);
    camera->roll = Camera_LERPCeilS(D_801EDBF0, roll, 0.05f, 5);
    return true;
}

s32 Camera_Normal0(Camera* camera) {
    f32 phi_f0;
    f32 temp_f2;
    s32 pad;
    f32 temp_f0;
    f32 spA4;
    f32 spA0;
    VecSph sp98;
    VecSph sp90;
    VecSph sp88;
    VecSph sp80;
    VecSph sp78;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* sp34 = &camera->trackActorPosRot;
    s16 temp_v1_2;
    s16 phi_a1;
    s16 phi_a0;
    SubCamData* bgCamData;
    f32 new_var;
    Normal0FixedData* fixedData = CAM_GET_STATIC_DATA(Normal0);
    Normal0DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Normal0);

    if (phi_a1) {}

    temp_f0 = Player_GetHeight((Player*)camera->trackActor);
    temp_f2 = 0.8f - ((68.0f / temp_f0) * -0.2f);

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * temp_f0 * temp_f2;
        fixedData->unk_04 = READ_SCALED_STATIC_DATA_VAL * temp_f0 * temp_f2;
        fixedData->unk_08 = READ_SCALED_STATIC_DATA_VAL * temp_f0 * temp_f2;
        fixedData->unk_1C = DEGF_TO_BINANG(READ_STATIC_DATA_VAL);
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_1E = READ_STATIC_DATA_VAL;
    }

    sCameraInterfaceFlags = fixedData->unk_1E;

    if (RELOAD_PARAMS) {
        bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
        Camera_Vec3sToVec3f(&dynamicData->unk_00, &bgCamData->pos);
        dynamicData->unk_20 = bgCamData->rot.x;
        dynamicData->unk_22 = bgCamData->rot.y;
        dynamicData->unk_24 = sp34->pos.y;
        if (bgCamData->fov == -1) {
            dynamicData->unk_1C = fixedData->unk_14;
        } else {
            if (bgCamData->fov > 360) {
                phi_f0 = bgCamData->fov * 0.01f;
            } else {
                phi_f0 = bgCamData->fov;
            }
            dynamicData->unk_1C = phi_f0;
        }

        if (bgCamData->unk_0E == -1) {
            dynamicData->unk_2C = 0;
        } else {
            dynamicData->unk_2C = bgCamData->unk_0E;
        }

        dynamicData->unk_18 = 0.0f;
        dynamicData->unk_28 = 120.0f;
        if (fixedData->unk_1E & NORM0_FLG_4) {
            sp88.pitch = dynamicData->unk_20;
            sp88.yaw = dynamicData->unk_22;
            sp88.r = 100.0f;
            OLib_VecSphGeoToVec3f(&dynamicData->unk_0C, &sp88);
        }
        camera->actionFuncState = 1;
        camera->yawUpdateRateInv = 50.0f;
    } else {
        if (func_800CB950(camera)) {
            dynamicData->unk_24 = sp34->pos.y;
        }
        if (1) {}
    }

    OLib_Vec3fDiffToVecSphGeo(&sp80, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&sp78, at, eyeNext);
    camera->speedRatio *= 0.50f;
    spA4 = camera->speedRatio * 0.5f;
    spA0 = camera->speedRatio * 0.2f;
    camera->yawUpdateRateInv =
        Camera_LERPCeilF(fixedData->unk_0C, camera->yawUpdateRateInv * camera->speedRatio, 0.5f, 0.1f);
    camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, spA0, 0.1f);
    camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, spA4, 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, spA0, 0.0001f);
    // TODO: 0.05 instead of 0.05f?
    camera->fovUpdateRate = Camera_LERPCeilF(0.05, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);

    if (!(fixedData->unk_1E & NORM0_FLG_80)) {
        Camera_CalcAtDefault(camera, &sp78, fixedData->unk_00, fixedData->unk_1E & NORM0_FLG_1);
        dynamicData->unk_28 = 120.0f;
    } else {
        func_800CD834(camera, &sp78, fixedData->unk_00, &dynamicData->unk_24, dynamicData->unk_28);
        if (dynamicData->unk_28 > 20.0f) {
            dynamicData->unk_28 -= 0.2f;
        }
    }

    if (fixedData->unk_1E & NORM0_FLG_4) {
        dynamicData->unk_00.x = sp34->pos.x + dynamicData->unk_0C.x;
        dynamicData->unk_00.z = sp34->pos.z + dynamicData->unk_0C.z;
    }

    dynamicData->unk_00.y = sp34->pos.y;
    OLib_Vec3fDiffToVecSphGeo(&sp88, &dynamicData->unk_00, at);
    OLib_Vec3fDiffToVecSphGeo(&sp90, at, eyeNext);

    if (dynamicData->unk_2C & 2) {
        phi_a1 = dynamicData->unk_22;
    } else {
        phi_a1 = fixedData->unk_1C;
    }

    temp_v1_2 = sp90.yaw - sp88.yaw;
    if (((phi_a1 <= 0x4000) && (phi_a1 < ABS(temp_v1_2))) || ((phi_a1 > 0x4000) && (ABS(temp_v1_2) < phi_a1))) {
        if (1) {}
        if (1) {}
        if (1) {}
        if (1) {}       // Needed to swap v0/v1
        new_var = 1.0f; // needed because the *1.0f isn't being multiplied

        if (temp_v1_2 < 0) {
            phi_a0 = -phi_a1;
        } else {
            phi_a0 = phi_a1;
        }

        phi_a0 += sp88.yaw;
        sp98.yaw =
            Camera_LERPCeilS(phi_a0, sp80.yaw, (1.0f / camera->yawUpdateRateInv) * new_var * camera->speedRatio, 5);
        if (dynamicData->unk_2C & 1) {
            sp98.pitch = Camera_CalcDefaultPitch(camera, sp78.pitch, dynamicData->unk_20, 0);
        } else {
            sp98.pitch = sp80.pitch;
        }
    } else {
        sp98 = sp90;
    }

    camera->dist = sp98.r = Camera_ClampDist1(camera, sp90.r, fixedData->unk_04, fixedData->unk_08, 0);
    if (!(dynamicData->unk_2C & 1)) {
        if (sp98.pitch > 0xE38) { // 20 degrees
            sp98.pitch += ((s16)(0xE38 - sp98.pitch) >> 2);
        }
        if (sp98.pitch < 0) {
            sp98.pitch += ((s16)(-0x38E - sp98.pitch) >> 2);
        }
    }
    OLib_VecSphAddToVec3f(eyeNext, at, &sp98);

    *eye = *eyeNext;

    if (camera->status == CAM_STATUS_ACTIVE) {
        if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (fixedData->unk_1E & NORM0_FLG_10)) {
            Camera_BGCheck(camera, at, eye);
        } else {
            func_800CBFA4(camera, at, eye, 3);
            OLib_Vec3fDiffToVecSphGeo(&sp98, eye, at);
            camera->inputDir.x = sp98.pitch;
            camera->inputDir.y = sp98.yaw;
            camera->inputDir.z = 0;
        }
    }
    camera->fov = Camera_LERPCeilF(dynamicData->unk_1C, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, fixedData->unk_18);
    return 1;
}

/**
 * Used for targeting
 */
s32 Camera_Parallel1(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Vec3f spB0;
    Vec3f spA4;
    f32 spA0;
    f32 sp9C;
    PosRot* sp38 = &camera->trackActorPosRot;
    VecSph sp90;
    VecSph sp88;
    VecSph sp80;
    VecSph sp78;
    SubCamData* bgCamData;
    s16 sp72;
    s16 tangle;
    Parallel1FixedData* fixedData = CAM_GET_STATIC_DATA(Parallel1);
    Parallel1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Parallel1);
    s32 new_var3;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    s16 new_var2;
    s16 phi_a0;
    s32 phi_a0_2;
    CameraModeValue* values;
    f32 sp50;

    if (!RELOAD_PARAMS) {
    } else {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * trackHeight * (0.8f - ((68.0f / trackHeight) * -0.2f));
        fixedData->unk_04 = READ_SCALED_STATIC_DATA_VAL * trackHeight * (0.8f - ((68.0f / trackHeight) * -0.2f));
        fixedData->unk_08 = READ_SCALED_STATIC_DATA_VAL * trackHeight * (0.8f - ((68.0f / trackHeight) * -0.2f));
        fixedData->unk_20 = DEGF_TO_BINANG(READ_STATIC_DATA_VAL);
        fixedData->unk_22 = DEGF_TO_BINANG(READ_STATIC_DATA_VAL);
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_26 = READ_STATIC_DATA_VAL;
        fixedData->unk_1C = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_24 = READ_STATIC_DATA_VAL;
        dynamicData->unk_00 = fixedData->unk_04;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp80, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&sp78, at, eyeNext);
    func_800CBAD4(&spA4, camera);

    switch (camera->actionFuncState) {
        case 20:
            if ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == 0) {
                Camera_SetUpdateRatesFastYaw(camera);
            }
            // fallthrough
        case 0:
        case 10:
            if ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_4 | PARA1_FLG_2)) {
                dynamicData->unk_10 = sp38->pos;
            } else {
                camera->xzOffsetUpdateRate = 0.5f;
                camera->yOffsetUpdateRate = 0.5f;
            }

            if ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == PARA1_FLG_8) {
                dynamicData->unk_10 = camera->trackActorPosRot.pos;
            }

            dynamicData->unk_0C = 200.0f;

            if ((2.0f * fixedData->unk_04) < camera->dist) {
                camera->dist = 2.0f * fixedData->unk_04;
                sp78.r = camera->dist;
                sp80.r = sp78.r;
                OLib_VecSphAddToVec3f(eye, at, &sp80);
                *eyeNext = *eye;
            }

            dynamicData->unk_1C = 0;

            if (fixedData->unk_26 & PARA1_FLG_4) {
                dynamicData->unk_22 = 0x14;
            } else {
                dynamicData->unk_22 = 6;
            }

            if ((camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) &&
                (camera->mode == CAM_MODE_CHARGE)) {
                dynamicData->unk_22 = 0x1E;
                if (((Player*)camera->trackActor)->transformation == PLAYER_FORM_DEKU) {
                    fixedData->unk_24 = -1;
                }
            }

            if ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_8 | PARA1_FLG_2)) {
                dynamicData->unk_22 = 1;
                sp50 = 0.8f - ((68.0f / trackHeight) * -0.2f);
                bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
                dynamicData->unk_20 = bgCamData->rot.x;
                dynamicData->unk_1E = bgCamData->rot.y;
                dynamicData->unk_08 = (bgCamData->fov == -1)   ? fixedData->unk_14
                               : (bgCamData->fov > 360) ? bgCamData->fov * 0.01f
                                                        : bgCamData->fov;
                dynamicData->unk_00 = (bgCamData->unk_0E == -1) ? fixedData->unk_04 : bgCamData->unk_0E * 0.01f * trackHeight * sp50;
            dummy:; // TODO: is needed?
            } else {
                dynamicData->unk_08 = fixedData->unk_14;
                dynamicData->unk_00 = fixedData->unk_04;
            }

            dynamicData->unk_24 = fixedData->unk_24;
            dynamicData->unk_04 = sp38->pos.y - camera->trackActorOffset.y;
            dynamicData->unk_26 = 1;
            camera->actionFuncState = 1;
            sCameraInterfaceFlags = fixedData->unk_26;
    }

    if (dynamicData->unk_22 != 0) {
        switch (fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) {
            case PARA1_FLG_2:
            case (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2):
                dynamicData->unk_1E = BINANG_ROT180(camera->trackActorPosRot.rot.y) + fixedData->unk_22;
                dynamicData->unk_20 = fixedData->unk_20;
                break;
            case PARA1_FLG_4:
                dynamicData->unk_1E = fixedData->unk_22;
                dynamicData->unk_20 = fixedData->unk_20;
                break;
            case (PARA1_FLG_4 | PARA1_FLG_2):
                if (dynamicData->unk_24 == 1) {
                    OLib_Vec3fDiffToVecSphGeo(&sp88, &dynamicData->unk_10, &spA4);
                    dynamicData->unk_1E = ((ABS(SUB16(sp88.yaw, sp80.yaw)) < 0x3A98) || Camera_IsClimbingLedge(camera))
                                       ? sp80.yaw
                                       : sp80.yaw + (s16)((SUB16(sp88.yaw, sp80.yaw) >> 2) * 3);
                }
                dynamicData->unk_20 = fixedData->unk_20;
                break;
            case PARA1_FLG_8:
                dynamicData->unk_1E = sp80.yaw;
                dynamicData->unk_20 = fixedData->unk_20;
                break;
            case (PARA1_FLG_8 | PARA1_FLG_2):
                break;
            default:
                dynamicData->unk_1E = sp78.yaw + fixedData->unk_22;
                dynamicData->unk_20 = fixedData->unk_20;
                break;
        }
    } else if (fixedData->unk_26 & PARA1_FLG_20) {
        dynamicData->unk_1E = BINANG_ROT180(camera->trackActorPosRot.rot.y) + fixedData->unk_22;
    }

    if (camera->actionFuncState == 21) {
        camera->actionFuncState = 1;
    } else if (camera->actionFuncState == 11) {
        camera->actionFuncState = 1;
    }

    spA0 = camera->speedRatio * 0.5f;
    sp9C = camera->speedRatio * 0.2f;

    if (((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_4 | PARA1_FLG_2)) || ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == PARA1_FLG_8) ||
        (fixedData->unk_26 & PARA1_FLG_20)) {
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
        camera->yawUpdateRateInv = Camera_LERPCeilF(fixedData->unk_0C, camera->yawUpdateRateInv, 0.5f, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
    } else {
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, spA0, 0.1f);
        camera->yawUpdateRateInv = Camera_LERPCeilF(fixedData->unk_0C, camera->yawUpdateRateInv, spA0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(2.0f, camera->pitchUpdateRateInv, sp9C, 0.1f);
    }

    if ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.1f, camera->yOffsetUpdateRate, spA0, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.1f, camera->xzOffsetUpdateRate, sp9C, 0.0001f);
    } else if (fixedData->unk_26 & PARA1_FLG_80) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.5f, camera->yOffsetUpdateRate, spA0, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.5f, camera->xzOffsetUpdateRate, sp9C, 0.0001f);
    } else {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, spA0, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp9C, 0.0001f);
    }

    // TODO: Extra 0 needed?
    camera->fovUpdateRate = Camera_LERPCeilF(0.050f, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);

    if (fixedData->unk_26 & PARA1_FLG_1) {
        tangle = func_800CC9C0(camera, BINANG_ROT180(sp80.yaw), dynamicData->unk_26 = 1);
        spA0 = ((1.0f / fixedData->unk_10));
        spA0 *= 0.6f;
        sp9C = ((1.0f / fixedData->unk_10) * 0.4f) * (1.0f - camera->speedRatio);
        dynamicData->unk_1C = Camera_LERPCeilS(tangle, dynamicData->unk_1C, spA0 + sp9C, 5);
    } else {
        dynamicData->unk_1C = 0;
    }

    // (stateFlags1 & 0x1000) charging spin attack
    // (stateFlags3 & 0x100) Deku flower dive
    if (func_800CB950(camera) || (((Player*)camera->trackActor)->stateFlags1 & 0x1000) ||
        (((Player*)camera->trackActor)->stateFlags3 & 0x100)) {
        dynamicData->unk_04 = camera->trackActorPosRot.pos.y;
        sp72 = false;
    } else {
        sp72 = true;
    }

    // (stateFlags1 & 0x4) Climbing ledge
    if ((((Player*)camera->trackActor)->stateFlags1 & 0x4000) || (((Player*)camera->trackActor)->stateFlags1 & 4) ||
        ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_4 | PARA1_FLG_2))) {
        spB0 = spA4;
        spB0.y += ((trackHeight * 0.6f) + fixedData->unk_00);
        Camera_LERPCeilVec3f(&spB0, at, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.0001f);
        Camera_UpdateAtActorOffset(camera, &sp38->pos);
    } else {
        if ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) {
            spB0 = sp38->pos;
            spB0.y += trackHeight + fixedData->unk_00;
            Camera_LERPCeilVec3f(&spB0, at, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.0001f);
            Camera_UpdateAtActorOffset(camera, &sp38->pos);
        } else if (dynamicData->unk_22 != 0) {
            Camera_CalcAtDefault(camera, &sp78, fixedData->unk_00, 0);
            dynamicData->unk_0C = 200.0f;
        } else if (!(fixedData->unk_26 & PARA1_FLG_80) && !sp72) {
            func_800CDB6C(camera, &sp78, fixedData->unk_00, fixedData->unk_08, &dynamicData->unk_04, fixedData->unk_26 & (PARA1_FLG_40 | PARA1_FLG_1));
            dynamicData->unk_0C = 200.0f;
        } else {
            func_800CD834(camera, &sp78, fixedData->unk_00, &dynamicData->unk_04, dynamicData->unk_0C);
            if (dynamicData->unk_0C > 10.0f) {
                dynamicData->unk_0C--;
            }
        }
    }

    camera->dist = Camera_LERPCeilF(dynamicData->unk_00, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);

    if (dynamicData->unk_22 != 0) {
        if (dynamicData->unk_24 <= 0) {
            if (dynamicData->unk_24 == 0) {
                Camera_SetFlags(camera, CAM_FLAG2_20);
            }

            tangle = ((dynamicData->unk_22 + 1) * dynamicData->unk_22) >> 1;
            sp90.yaw = sp80.yaw + ((SUB16(dynamicData->unk_1E, sp80.yaw) / tangle) * dynamicData->unk_22);
            phi_a0 = ((fixedData->unk_26 & PARA1_FLG_1) ? SUB16(dynamicData->unk_20, dynamicData->unk_1C) : dynamicData->unk_20);
            new_var2 = SUB16(phi_a0, sp80.pitch);
            sp90.pitch = sp80.pitch + ((new_var2 / tangle) * dynamicData->unk_22);
            sp90.r = camera->dist;
            dynamicData->unk_22--;
        } else {
            sp90 = sp80;
            sp90.r = camera->dist;
        }
    } else {
        OLib_Vec3fDiffToVecSphGeo(&sp90, at, eyeNext);
        sp90.r = camera->dist;

        if (fixedData->unk_26 & PARA1_FLG_2) {
            sp90.yaw = Camera_LERPCeilS(dynamicData->unk_1E, sp78.yaw, 1.0f / camera->yawUpdateRateInv, 0xC8);
        }

        new_var3 = (fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2));

        if (fixedData->unk_26 & PARA1_FLG_1) {
            phi_a0 = (dynamicData->unk_20 - dynamicData->unk_1C);
        } else {
            phi_a0 = dynamicData->unk_20;
        }

        if (new_var3 == (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) {
            spA0 = CLAMP_MAX(camera->speedRatio, 1.0f);
            phi_a0 = (sp90.pitch * spA0) + (phi_a0 * (1.0f - spA0));
            sp90.pitch = Camera_LERPCeilS(phi_a0, sp78.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        } else if (new_var3 != PARA1_FLG_8) {
            sp90.pitch = Camera_LERPCeilS(phi_a0, sp78.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }

        // 79.7 degrees
        if (sp90.pitch > 0x38A4) {
            sp90.pitch = 0x38A4;
        }

        // -30 degrees
        if (sp90.pitch < -0x1554) {
            sp90.pitch = -0x1554;
        }
    }

    if (dynamicData->unk_24 > 0) {
        dynamicData->unk_24--;
    }

    OLib_VecSphAddToVec3f(eyeNext, at, &sp90);

    if (camera->status == CAM_STATUS_ACTIVE) {
        if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (fixedData->unk_26 & PARA1_FLG_10)) {
            spB0 = *at;
            // (stateFlags1 & 0x4) Climbing ledge
            if ((((Player*)camera->trackActor)->stateFlags1 & 0x4000) ||
                (((Player*)camera->trackActor)->stateFlags1 & 4) || ((fixedData->unk_26 & (PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2)) == (PARA1_FLG_4 | PARA1_FLG_2))) {
                spB0.y += trackHeight;
            }
            *eye = *eyeNext;
            func_800CBFA4(camera, &spB0, eye, 0);
        } else {
            *eye = *eyeNext;
            func_800CBFA4(camera, at, eye, 3);
        }

        if (dynamicData->unk_22 != 0) {
            sUpdateCameraDirection = true;
        } else {
            sUpdateCameraDirection = false;
        }
    }

    camera->fov = Camera_LERPCeilF(dynamicData->unk_08, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, sp72 ? fixedData->unk_1C : fixedData->unk_18);
    dynamicData->unk_26 &= ~1;
    return true;
}

/**
 * Unused Camera Maze Setting
 */
s32 Camera_Parallel2(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Parallel3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Parallel4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Parallel0(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Jump1(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Camera for climbing structures
 * 
 * This function is matching but rodata was improperly split between Camera_Jump2 and Camera_Jump3
 * This will successfully match when Camera_Jump3 is matching
 * (has been verified by manually moving rodata asm after extraction)
 */
#ifdef NON_MATCHING
s32 Camera_Jump2(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Vec3f spC8;
    Vec3f spBC;
    VecSph spB4;
    VecSph spAC;
    VecSph spA4;
    VecSph sp9C;
    s16 temp_t2;
    s16 yawDiff;
    f32 temp_f0_2;
    f32 sp90;
    f32 sp8C;
    s32 sp88;
    CamColChk sp60;
    PosRot* sp2C = &camera->trackActorPosRot;
    Jump2FixedData* fixedData = CAM_GET_STATIC_DATA(Jump2);
    Jump2DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Jump2);
    f32 phi_f2;
    f32 yNormal; // used twice
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    f32 temp_f16;

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        yNormal = 0.8f - (-0.2f * (68.0f / trackHeight));

        if (camera->trackActorOffset.y > 0.0f) {
            phi_f2 = -10.0f;
        } else {
            phi_f2 = 10.0f;
        }

        fixedData->unk_00 = SCALED_STATIC_DATA(phi_f2 + READ_STATIC_DATA_VAL) * trackHeight * yNormal;
        fixedData->unk_04 = READ_SCALED_STATIC_DATA_VAL * trackHeight * yNormal;
        fixedData->unk_08 = READ_SCALED_STATIC_DATA_VAL * trackHeight * yNormal;
        fixedData->unk_0C = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_1C = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_20 = READ_STATIC_DATA_VAL;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp9C, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&spA4, at, eyeNext);

    sCameraInterfaceFlags = fixedData->unk_20;

    if (RELOAD_PARAMS) {
        spC8 = sp2C->pos;
        temp_f0_2 = Camera_GetFloorY(camera, &spC8);
        dynamicData->unk_00 = temp_f0_2;
        dynamicData->unk_04 = spA4.yaw;
        dynamicData->unk_06 = 0;
        if (temp_f0_2 == BGCHECK_Y_MIN) {
            dynamicData->unk_0A = -1;
            dynamicData->unk_00 = sp2C->pos.y - 1000.0f;
        } else if ((sp2C->pos.y - dynamicData->unk_00) < trackHeight) {
            dynamicData->unk_0A = 1;
        } else {
            dynamicData->unk_0A = -1;
        }

        yawDiff = SUB16(BINANG_ROT180(sp2C->rot.y), spA4.yaw);
        dynamicData->unk_06 = ((yawDiff / 6) / 4) * 3;
        if (fixedData->unk_20 & JUMP2_FLG_2) {
            dynamicData->unk_08 = 10;
        } else {
            dynamicData->unk_08 = 10000;
        }

        sp2C->pos.x -= camera->trackActorOffset.x;
        sp2C->pos.y -= camera->trackActorOffset.y;
        sp2C->pos.z -= camera->trackActorOffset.z;
        dynamicData->unk_0C = 6;
        camera->actionFuncState++;
        camera->atLERPStepScale = fixedData->unk_1C;
    }

    sp90 = camera->speedRatio * 0.5f;
    sp8C = camera->speedRatio * 0.2f;
    camera->yawUpdateRateInv = Camera_LERPCeilF(fixedData->unk_10, camera->yawUpdateRateInv, sp90, 0.1f);
    camera->yOffsetUpdateRate = Camera_LERPCeilF(fixedData->unk_14, camera->yOffsetUpdateRate, sp90, 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp8C, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, camera->speedRatio * .05f, 0.0001f);
    camera->rUpdateRateInv = 1800.0f;
    Camera_CalcAtDefault(camera, &spA4, fixedData->unk_00, 0);
    OLib_Vec3fDiffToVecSphGeo(&spB4, at, eye);

    yNormal = fixedData->unk_04; // required to match

    phi_f2 = fixedData->unk_08 + (fixedData->unk_08 * fixedData->unk_0C);
    temp_f16 = fixedData->unk_04 - (fixedData->unk_04 * fixedData->unk_0C);

    if (spB4.r > phi_f2) {
        spB4.r = phi_f2;
    } else if (spB4.r < temp_f16) {
        spB4.r = temp_f16;
    }

    yawDiff = SUB16(BINANG_ROT180(sp2C->rot.y), spB4.yaw);
    if (dynamicData->unk_0C != 0) {
        dynamicData->unk_04 = BINANG_ROT180(sp2C->rot.y);
        dynamicData->unk_0C--;
        spB4.yaw = Camera_LERPCeilS(dynamicData->unk_04, spA4.yaw, 0.5f, 5);
    } else if (dynamicData->unk_08 < ABS(yawDiff)) {
        temp_t2 = BINANG_ROT180(sp2C->rot.y);
        spB4.yaw =
            Camera_LERPFloorS((yawDiff < 0) ? (temp_t2 + dynamicData->unk_08) : (temp_t2 - dynamicData->unk_08), spA4.yaw, 0.1f, 1);
    } else {
        spB4.yaw = Camera_LERPCeilS(spB4.yaw, spA4.yaw, 0.25f, 5);
    }

    spC8.x = sp2C->pos.x + (Math_SinS(sp2C->rot.y) * 25.0f);
    spC8.y = sp2C->pos.y + (trackHeight * 2.2f);
    spC8.z = sp2C->pos.z + (Math_CosS(sp2C->rot.y) * 25.0f);

    yNormal = Camera_GetFloorYNorm(camera, &spBC, &spC8, &sp88);
    if (camera->trackActor->bgCheckFlags & 0x10) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        spB4.pitch = Camera_LERPCeilS(-0x1388, spA4.pitch, 0.2f, 5);
    } else if ((yNormal != BGCHECK_Y_MIN) && (sp2C->pos.y < yNormal)) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        if (camera->trackActorOffset.y > 1.0f) {
            spB4.pitch = Camera_LERPCeilS(0x1F4, spA4.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }
    } else if ((sp2C->pos.y - dynamicData->unk_00) < trackHeight) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        if (camera->trackActorOffset.y > 1.0f) {
            spB4.pitch = Camera_LERPCeilS(0x1F4, spA4.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }
    } else {
        camera->pitchUpdateRateInv = 100.0f;
        camera->rUpdateRateInv = 100.0f;
    }

    spB4.pitch = CLAMP_MAX(spB4.pitch, 0x2AF8);  // 60.4 degrees
    spB4.pitch = CLAMP_MIN(spB4.pitch, -0x2AF8); // -60.4 degrees

    OLib_VecSphAddToVec3f(eyeNext, at, &spB4);
    sp60.pos = *eyeNext;
    if (func_800CBC84(camera, at, &sp60, 0) != 0) {
        spC8 = sp60.pos;
        spAC.pitch = 0;
        spAC.r = spB4.r;
        spAC.yaw = spB4.yaw;
        OLib_VecSphAddToVec3f(&sp60.pos, at, &spAC);
        if (func_800CBC84(camera, at, &sp60, 0) != 0) {
            *eye = spC8;
        } else {
            spB4.pitch = Camera_LERPCeilS(0, spB4.pitch, 0.2f, 5);
            OLib_VecSphAddToVec3f(eye, at, &spB4);
            func_800CBFA4(camera, at, eye, 0);
        }
    } else {
        *eye = *eyeNext;
    }

    camera->dist = spB4.r;
    camera->fov = Camera_LERPCeilF(fixedData->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump2.s")
#endif

/**
 * Used for water-based camera settings
 * e.g. Gyorg, Pinnacle Rock, whirlpool, water
 */
#ifdef NON_EQUIVALENT
s32 Camera_Jump3(Camera* camera) {
    Vec3f* sp48 = &camera->eye;
    Vec3f* sp44 = &camera->at;
    Vec3f* sp40 = &camera->eyeNext;
    f32 spD0;
    f32 spCC;
    PosRot* sp3C = &camera->trackActorPosRot;
    f32 phi_f0;
    f32 spC0;
    Vec3f spB4;
    VecSph spAC;
    CameraModeValue* values;
    f32 phi_f14;
    VecSph sp9C;
    VecSph sp94;
    f32 phi_f2_2;
    f32 temp_f0;
    f32 pad1; // Fake Temp
    f32 pad2; // UNUSED - Available for temp
    f32 pad3; // UNUSED - Available for temp
    f32 pad4; // UNUSED - Available for temp
    f32 sp78;
    Jump3FixedData* fixedData = CAM_GET_STATIC_DATA(Jump3);
    Jump3DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Jump3);
    Vec3f sp64;
    f32 sp60;
    f32 sp5C;
    s32 sp58;

    sp78 = Camera_GetTrackedActorHeight(camera);
    Actor_GetFocus(&sp64, camera->trackActor);
    sp60 = camera->waterYPos - sp48->y;

    sp58 = false;

    if (RELOAD_PARAMS) {
        dynamicData->unk_0A = camera->mode;
        dynamicData->unk_0C = 0;
    }

    if (camera->mode == CAM_MODE_NORMAL) {
        if ((camera->trackActor->bgCheckFlags & 0x10) || (dynamicData->unk_0C != 0)) {
            if (dynamicData->unk_0A != 0xF) {
                dynamicData->unk_0A = 0xF;
                sp58 = true;
                dynamicData->unk_0C = 0xA;
            }
        } else if (sp60 < 50.0f) {
            if (dynamicData->unk_0A != 0) {
                dynamicData->unk_0A = 0;
                sp58 = true;
            }
        } else if (Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight) < 11.0f) {
            if (dynamicData->unk_0A != 5) {
                dynamicData->unk_0A = 5;
                sp58 = true;
            }
        } else if ((sp60 > 250.0f) && (dynamicData->unk_0A != 0x1A)) {
            dynamicData->unk_0A = 0x1A;
            sp58 = true;
        }
    }

    if (dynamicData->unk_0C != 0) {
        dynamicData->unk_0C--;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp9C, sp44, sp48);
    OLib_Vec3fDiffToVecSphGeo(&sp94, sp44, sp40);

    // Everything above is down to SP and floats

    if (!RELOAD_PARAMS && !sp58) {
    } else {
        values = sCameraSettings[camera->setting].cameraModes[dynamicData->unk_0A].values;

        sp5C = 0.8f - -0.2f * (68.0f / sp78);
        spD0 = sp78 * 0.01f * sp5C;
        // if (phi_f2) {}

        fixedData->unk_00 = READ_STATIC_DATA_VAL * spD0;
        fixedData->unk_04 = READ_STATIC_DATA_VAL * spD0;
        if (1) {}
        fixedData->unk_08 = READ_STATIC_DATA_VAL * spD0;
        fixedData->unk_20 = DEGF_TO_BINANG(READ_STATIC_DATA_VAL);
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_1C = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_22 = READ_STATIC_DATA_VAL;
    }

    sCameraInterfaceFlags = fixedData->unk_22;

    switch (camera->actionFuncState) {
        case 0:
            dynamicData->unk_10 = 0x1000;
        case 10:
        case 20:
            dynamicData->unk_00 = camera->playerFloorHeight;
            D_801EDC30[camera->camId].yaw = D_801EDC30[camera->camId].pitch = D_801EDC30[camera->camId].unk_64 = 0;
            dynamicData->unk_08 = 0xA;
            D_801EDC30[camera->camId].swingUpdateRate = fixedData->unk_0C;
            camera->actionFuncState++;
            D_801EDC30[camera->camId].unk_66 = 0;
            break;
        default:
            if (dynamicData->unk_08 != 0) {
                dynamicData->unk_08--;
            }
            break;
    }

    spC0 = sp64.y - sp3C->pos.y;
    spB4 = *sp48;

    // crazy things going on with temp_f0_2
    // temp_f0_2 = camera->speedRatio; // Removing this temp fixes large chuncks of code and destorys other chuncks of
    // code

    // PERM_RANDOMIZE(

    spD0 = camera->speedRatio;
    spD0 *= 0.5f;
    spCC = camera->speedRatio * 0.2f;
    // spCC = phi_f2;

    temp_f0 = (D_801EDC30[camera->camId].unk_64 == 1) ? 0.5f : spD0;

    if (D_801EDC30[camera->camId].unk_66 != 0) {
        // spD0 = temp_f2;
        // spCC = camera->speedRatio * 0.2f;
        camera->yawUpdateRateInv =
            Camera_LERPCeilF((D_801EDC30[camera->camId].swingUpdateRate + D_801EDC30[camera->camId].unk_66 * 2),
                             camera->yawUpdateRateInv, spD0, 0.1f);
        camera->pitchUpdateRateInv =
            Camera_LERPCeilF((40.0f + D_801EDC30[camera->camId].unk_66 * 2), camera->pitchUpdateRateInv, spCC, 0.1f);
        D_801EDC30[camera->camId].unk_66--;
    } else {
        // spCC = camera->speedRatio * 0.2f;
        // phi_f14 = camera->yawUpdateRateInv;
        camera->yawUpdateRateInv =
            Camera_LERPCeilF(D_801EDC30[camera->camId].swingUpdateRate, camera->yawUpdateRateInv, temp_f0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(40.0f, camera->pitchUpdateRateInv, spCC, 0.1f);
    }

    // NOT ELSE

    if (fixedData->unk_22 & JUMP3_FLG_80) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.01f, camera->yOffsetUpdateRate, spD0, 0.0001f);
        // sp4C = sqrtf(SQXZ(camera->trackActorOffset));
        // if (1) {} // TODO: is needed? (helps a lot)
        // temp_f0 = sqrtf((camera->trackActorOffset.x * camera->trackActorOffset.x) + (camera->trackActorOffset.z *
        // camera->trackActorOffset.z)); if (1) {}
        sp5C = sqrtf((camera->trackActorOffset.x * camera->trackActorOffset.x) +
                     (camera->trackActorOffset.z * camera->trackActorOffset.z)) /
               Camera_GetRunSpeedLimit(camera);
        camera->speedRatio = OLib_ClampMaxDist(sp5C / Camera_GetRunSpeedLimit(camera), 1.8f);
        spCC = camera->speedRatio * 0.2f;
    } else {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, phi_f14 = camera->yOffsetUpdateRate, spD0, 0.0001f);
        // spCC = phi_f2; // Currently not needed
        // spCC = camera->speedRatio * 0.2f;
    }

    // if (1) {} // TODO is needed?
    // dummy:; // TODO is needed?

    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, spCC, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.050f, (0, camera->fovUpdateRate), camera->speedRatio * 0.05f,
                                             0.0001f); // TODO: IS extra 0 needed?

    // Everything below is down to SP and floats

    if (sp60 < 50.0f) {
        sp5C = camera->waterYPos - spC0;
        if (sp60 < 0.0f) {
            phi_f14 = 1.0f;
        } else {
            phi_f14 = 1.0f - (sp60 / 50.0f);
        }
        func_800CD834(camera, &sp94, fixedData->unk_00, &sp5C, phi_f14 * 50.0f);
    } else {
        Camera_CalcAtDefault(camera, &sp94, fixedData->unk_00, fixedData->unk_22);
    }

    OLib_Vec3fDiffToVecSphGeo(&spAC, sp44, sp40);
    spAC.r = Camera_ClampDist1(camera, spAC.r, fixedData->unk_04, fixedData->unk_08, dynamicData->unk_08);
    camera->dist = spAC.r;

    if (!(Camera_fabsf(sp3C->pos.y - camera->playerFloorHeight) < 10.0f) &&
        !(Camera_fabsf(sp64.y - camera->waterYPos) < 50.f)) { // No 0?
        camera->pitchUpdateRateInv = 100.0f;
    }

    if (fixedData->unk_22 & JUMP3_FLG_20) {
        if (camera->speedRatio * 1.3f > 0.6f) {
            spD0 = 0.6f;
        } else {
            spD0 = (camera->speedRatio * 1.3f);
        }
        // spD0 = pad1;
        spAC.pitch =
            Camera_LERPCeilS((spAC.pitch * spD0) + (fixedData->unk_20 * (1.0f - spD0)), sp94.pitch,
                             1.0f / ((camera->pitchUpdateRateInv + 1.0f) - (camera->pitchUpdateRateInv * spD0)), 5);
    } else if (D_801EDC30[camera->camId].unk_64 == 1) {
        pad1 = 1.0f / camera->yawUpdateRateInv;
        spAC.yaw = Camera_LERPCeilS(D_801EDC30[camera->camId].yaw, sp94.yaw, pad1, 5);
        // temp_f0 = 1.0f / camera->yawUpdateRateInv;
        // Bug? Should be pitchUpdateRateInv
        spAC.pitch = Camera_LERPCeilS(D_801EDC30[camera->camId].pitch, sp94.pitch, 1.0f / camera->yawUpdateRateInv, 5);
    } else if (fixedData->unk_22 & (JUMP3_FLG_80 | JUMP3_FLG_8)) {
        spAC.yaw = Camera_CalcDefaultYaw(camera, sp94.yaw, sp3C->rot.y, fixedData->unk_14, 0.0f);

        if (camera->speedRatio * 1.3f > 1.0f) {
            spCC = pad2 = 1.0f;
        } else {
            spCC = pad2 = camera->speedRatio * 1.3f;
        }
        spAC.pitch =
            Camera_LERPCeilS((spAC.pitch * spCC) + (fixedData->unk_20 * (1.0f - spCC)), sp94.pitch,
                             1.0f / ((camera->pitchUpdateRateInv + 1.0f) - (camera->pitchUpdateRateInv * spCC)), 5);
    } else {
        spAC.yaw = Camera_CalcDefaultYaw(camera, sp94.yaw, sp3C->rot.y, fixedData->unk_14, 0.0f);
        spAC.pitch = Camera_CalcDefaultPitch(camera, sp94.pitch, fixedData->unk_20, 0);
    }

    // 79.7 degrees
    if (spAC.pitch > 0x38A4) {
        spAC.pitch = 0x38A4;
    }

    // -30 degrees
    if (spAC.pitch < -0x1554) {
        spAC.pitch = -0x1554;
    }

    OLib_VecSphAddToVec3f(sp40, sp44, &spAC);
    if ((camera->status == CAM_STATUS_ACTIVE) && !(fixedData->unk_22 & JUMP3_FLG_40)) {
        if (func_800CBA7C(camera) == 0) {
            func_800CED90(camera, &spAC, &sp9C, fixedData->unk_04, fixedData->unk_0C, &D_801EDC30[camera->camId],
                          &dynamicData->unk_10);
        }
        if (fixedData->unk_22 & JUMP3_FLG_4) {
            camera->inputDir.x = -sp9C.pitch;
            camera->inputDir.y = sp9C.yaw + 0x8000;
            camera->inputDir.z = 0;
        } else {
            OLib_Vec3fDiffToVecSphGeo(&spAC, sp48, sp44);
            camera->inputDir.x = spAC.pitch;
            camera->inputDir.y = spAC.yaw;
            camera->inputDir.z = 0;
        }
    } else {
        D_801EDC30[camera->camId].swingUpdateRate = fixedData->unk_0C;
        D_801EDC30[camera->camId].unk_64 = 0;
        sUpdateCameraDirection = false;
        *sp48 = *sp40;
    }

    camera->fov = Camera_LERPCeilF(fixedData->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, .5f, 5); // TODO is extra 0 in 0.50f needed? (try without f)
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, fixedData->unk_1C);
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump3.s")
#endif

s32 Camera_Jump4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Jump0(Camera* camera) {
    return Camera_Noop(camera);
}

#ifdef NON_EQUIVALENT
s32 Camera_Battle1(Camera* camera) {
    Battle1FixedData* fixedData = CAM_GET_STATIC_DATA(Battle1);
    Battle1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Battle1);
    Vec3f sp120;
    Vec3f sp114;
    f32 sp104;
    f32 spFC;
    f32 spF8;
    f32 spF8_2;
    f32 spF4;
    s32 spF0; // bool
    f32 spEC;
    Vec3f spC4;
    VecSph spBC;
    VecSph spB4;
    VecSph spAC;
    VecSph spA4;
    VecSph sp9C;
    VecSph sp94;
    PosRot* sp8C;
    s16 sp8A;
    s16 sp88;
    s16 sp86;
    s16 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp68;
    s16 sp5E;
    s16 sp5C;
    Vec3f* sp50;
    Vec3f* sp4C;
    Vec3f* sp48;
    PosRot* sp40;

    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2_3;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s32 temp_f4;
    f32 phi_f0_3;
    f32 phi_f12;

    f32 new_var;
    f32 new_var2;
    f32 new_var3;
    f32 new_var5;
    f32 new_var4;

    sp50 = &camera->eye;
    sp4C = &camera->at;
    sp48 = &camera->eyeNext;
    sp40 = &camera->targetPosRot;

    spF0 = false;
    sp8C = &camera->trackActor->focus;
    sp68 = Camera_GetTrackedActorHeight(camera);

    if ((camera->actionFuncState != 0) && (camera->actionFuncState != 0xA) && (camera->actionFuncState != 0x14)) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        fixedData->unk_00 = READ_STATIC_DATA_VAL * 0.01f * sp68 * (0.8f - ((68.0f / sp68) * -0.2f));
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->unk_08 = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = 80.0f - (80.0f - fixedData->unk_0C);
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = 0.0f - (0.0f - fixedData->unk_10);
        fixedData->unk_14 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = 40.0f - (40.0f - fixedData->unk_14);
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = 20.0f - (20.0f - fixedData->unk_18);
        fixedData->unk_1C = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_1C = 1.0f - (1.0f - fixedData->unk_1C);
        fixedData->unk_20 = READ_STATIC_DATA_VAL;
        fixedData->unk_24 = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_24 = 1.0f - (1.0f - fixedData->unk_24);
        fixedData->unk_30 = READ_STATIC_DATA_VAL;
        fixedData->unk_28 = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_28 = 0.2f - (0.2f - fixedData->unk_28);
        fixedData->unk_2C = READ_STATIC_DATA_VAL * 0.01f;
        if ((camera->actionFuncState != 0) && (camera->actionFuncState != 0xA) && (camera->actionFuncState != 0x14)) {
        } else {
            dynamicData->unk_18 = 0x28;
            camera->pitchUpdateRateInv = 9.0f;
        }
    }

    sp80 = fixedData->unk_14;
    sp7C = fixedData->unk_18;
    sp78 = fixedData->unk_20;

    if (Camera_IsChargingSwordOrDekuFlowerDive(camera)) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(18.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.2f, camera->yOffsetUpdateRate, 0.5f, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.2f, camera->xzOffsetUpdateRate, 0.5f, 0.0001f);
        if (dynamicData->unk_18 >= -0x13) {
            dynamicData->unk_18--;
        } else {
            sp80 = 50.0f;
            sp7C = 40.0f;
            sp78 = 60.0f;
        }
    } else {
        if (dynamicData->unk_18 < 0) {
            sp80 = 50.0f;
            sp7C = 40.0f;
            sp78 = 60.0f;
            dynamicData->unk_18++;
        } else {
            dynamicData->unk_18 = 0x28;
            camera->pitchUpdateRateInv = Camera_LERPCeilF(9.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
            camera->yOffsetUpdateRate =
                Camera_LERPCeilF(0.6f, camera->yOffsetUpdateRate, camera->speedRatio * 0.5f, 0.0001f);
            camera->xzOffsetUpdateRate =
                Camera_LERPCeilF(0.6f, camera->xzOffsetUpdateRate, camera->speedRatio * 0.2f, 0.0001f);
        }
    }

    camera->fovUpdateRate = Camera_LERPCeilF(0.050f, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);
    sp68 += fixedData->unk_00;
    OLib_Vec3fDiffToVecSphGeo(&sp9C, sp4C, sp50);
    OLib_Vec3fDiffToVecSphGeo(&sp94, sp4C, sp48);
    if ((camera->target == NULL) || (camera->target->update == NULL)) {
        camera->target = NULL;
        Camera_ChangeMode(camera, CAM_MODE_TARGET);
        return true;
    }

    sCameraInterfaceFlags = fixedData->unk_30;

    if ((camera->actionFuncState == 0) || (camera->actionFuncState == 0xA) || (camera->actionFuncState == 0x14)) {
        dynamicData->unk_10 = 0;
        dynamicData->unk_1A = 0;
        dynamicData->unk_08 = camera->target;
        camera->actionFuncState++;
        dynamicData->unk_16 = 7;
        dynamicData->unk_12 = sp9C.yaw;
        dynamicData->unk_14 = sp9C.pitch;
        dynamicData->unk_00 = sp9C.r;
        dynamicData->unk_04 = camera->trackActorPosRot.pos.y - camera->trackActorOffset.y;
        if ((2.0f * fixedData->unk_04) < camera->dist) {
            camera->dist = 2.0f * fixedData->unk_04;
            sp94.r = camera->dist;
            sp9C.r = sp94.r;
            OLib_VecSphAddToVec3f(sp50, sp4C, &sp9C);
            *sp48 = *sp50;
        }
    }

    if (camera->status == CAM_STATUS_ACTIVE) {
        sUpdateCameraDirection = true;
        camera->inputDir.x = -sp9C.pitch;
        camera->inputDir.y = sp9C.yaw + 0x8000;
        camera->inputDir.z = 0;
    }

    if (func_800CB950(camera)) {
        dynamicData->unk_04 = camera->trackActorPosRot.pos.y;
        sp84 = 0;
    } else {
        sp84 = 1;
    }

    if (dynamicData->unk_16 == 0) {
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, sp84 ? fixedData->unk_28 : fixedData->unk_24);
    }

    Actor_GetFocus(&sp40->pos, camera->target);

    if (dynamicData->unk_08 != camera->target) {
        camera->actionFuncState = 0;
        return true;
    }

    sp120 = camera->trackActorPosRot.pos;
    sp120.y += sp68;
    OLib_Vec3fDiffToVecSphGeo(&spA4, &sp120, &sp40->pos);
    sp104 = func_800CD6CC(camera->target);
    if (PREG(86) + 800.0f < sp104) {
        sp104 = PREG(86) + 800.0f;
    }

    // new_var5 = sp104; // TODO: Fake temp but helps when used?
    // sp104 = new_var5;

    // Above is down to SP and Floats

    if ((sp104 < spA4.r) || Camera_IsChargingSwordOrDekuFlowerDive(camera)) {
        spEC = 1.0f;
        spF8 = 10.0f;
        // dummy:; // Helps?
        // sp80 = fixedData->unk_14; // Fake & Non-equivalent but helps?
    } else {
        spEC = spA4.r / sp104;
        spF8 = 2.0f;
    }
    // spF8 should be set with swc1 twice, not once

    // sp94 is loading in too early
    func_800CE2B8(camera, &sp94.r, sp40, fixedData->unk_00, fixedData->unk_2C, 1.0f - spEC, &dynamicData->unk_04, &spA4,
                  (sp84 ? (BATT1_FLG_80 | BATT1_FLG_1) : BATT1_FLG_1) | fixedData->unk_30);

    sp88 = spA4.yaw;
    OLib_Vec3fDiffToVecSphGeo(&spBC, sp4C, sp48);
    spF4 = fixedData->unk_04 + ((fixedData->unk_08 - fixedData->unk_04) * spEC);
    camera->rUpdateRateInv = Camera_LERPCeilF(spF8, camera->rUpdateRateInv, 0.5f, 0.1f);
    spBC.r = camera->dist = Camera_LERPCeilF(spF4, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
    OLib_Vec3fDiffToVecSphGeo(&spAC, sp4C, &sp40->pos);

    spAC.r = spBC.r - (((spAC.r >= spBC.r) ? spBC.r : spAC.r) * 0.5f);

    if (dynamicData->unk_1A & 0x1000) {
        spFC = 15.0f;
    } else {
        spFC = fixedData->unk_0C + ((fixedData->unk_10 - fixedData->unk_0C) * (1.1f - spEC));
    }
    spBC.yaw = sp94.yaw;
    temp_v0_5 = (sp94.yaw + 0x8000);
    temp_v0_5 = spAC.yaw - temp_v0_5;
    if (dynamicData->unk_16 != 0) {
        if (dynamicData->unk_16 > 0) {
            sp86 = dynamicData->unk_16 - 1;
            OLib_Vec3fDiffToVecSphGeo(&spB4, sp4C, sp50);
            spB4.yaw = sp88 + 0x8000;
            new_var = (dynamicData->unk_00 - spB4.r) * 0.16666667f;
            sp8A = (s16)(dynamicData->unk_12 - spB4.yaw) * 0.16666667f;
            sp88 = (s16)(dynamicData->unk_14 - spB4.pitch) * 0.16666667f;
            spBC.r = Camera_LERPCeilF((sp86 * new_var) + spB4.r, sp9C.r, 0.5f,
                                      1.0f); // TODO: extra float calcs going on here
            spBC.yaw = Camera_LERPCeilS(spB4.yaw + (sp8A * sp86), sp9C.yaw, 0.5f, 5);
            spBC.pitch = Camera_LERPCeilS(spB4.pitch + (sp88 * sp86), sp9C.pitch, 0.5f, 5);
        } else {
            spF0 = true;
        }
        dynamicData->unk_16--;
    } else {
        // s32 phi_v0_2 = ABS(temp_v0_5);
        temp_f4 = (s16)((spFC * 182.04167f) + .5f);
        if ((temp_f4 < ABS(temp_v0_5)) && (sp84 == 0)) {

            sp8A = temp_v0_5;
            sp104 = temp_v0_5 * 0.00549325f;

            temp_f2_3 = ((OLib_ClampMaxDist(spAC.r, spBC.r) / spBC.r) * ((spFC + 10.0f) - spFC)) + spFC;
            temp_f12 = (SQ(temp_f2_3) - 2.0f) / (temp_f2_3 - 360.0f);
            new_var3 = temp_f12 * sp104;
            temp_f14 = SQ(sp104) / (new_var3 + (2.0f - (360.0f * temp_f12)));

            if (sp8A >= 0) {
                sp88 = DEGF_TO_BINANG(temp_f14);
            } else {
                sp88 = -DEGF_TO_BINANG(temp_f14);
            }

            spBC.yaw = (s16)(sp94.yaw + 0x8000) + (s16)(sp88 + 0x8000);
        } else {
            new_var2 = (1.0f - camera->speedRatio) * 0.05f;
            if (temp_v0_5 >= 0) {
                sp88 = temp_f4 & 0xFFFFu; // TODO: Is this needed?
            } else {
                sp88 = -temp_f4;
            }
            spBC.yaw = sp94.yaw - (s16)((sp88 - temp_v0_5) * new_var2);
        }
    }

    if (spF0 == false) {
        new_var4 = spAC.pitch * fixedData->unk_1C;
        temp_v0_6 = ((s16)(((((sp7C - sp80) * spEC) + sp80) * 182.04167f) + .5f) -
                     (s16)((spA4.pitch * (0.5f + (spEC * 0.5f))) + 0.5f));
        temp_v0_6 += (s16)new_var4;

        if (temp_v0_6 < -0x2AA8) {
            temp_v0_6 = -0x2AA8;
        } else if (temp_v0_6 > 0x2AA8) {
            temp_v0_6 = 0x2AA8;
        }

        spBC.pitch = Camera_LERPCeilS(temp_v0_6, sp94.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        OLib_VecSphAddToVec3f(sp48, sp4C, &spBC);
        spC4 = *sp48;
        if (camera->status == CAM_STATUS_ACTIVE) {
            if (!(fixedData->unk_30 & BATT1_FLG_10)) {
                if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (fixedData->unk_30 & BATT1_FLG_1)) {
                    if (func_800CBC84(camera, sp4C, &spC4, 0) != 0) {
                        dynamicData->unk_1A |= 0x1000;
                    } else {
                        dynamicData->unk_1A &= ~0x1000;
                    }
                } else if (fixedData->unk_30 & BATT1_FLG_2) {
                    func_800CBC84(camera, sp4C, &spC4, 3);
                } else {
                    OLib_Vec3fDistNormalize(&sp114, sp4C, &spC4);
                    spC4.x -= sp114.x;
                    spC4.y -= sp114.y;
                    spC4.z -= sp114.z;
                }
                *sp50 = spC4;
                ;
                dynamicData->unk_1A &= ~0x10;
            } else if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (fixedData->unk_30 & BATT1_FLG_1)) {
                if (func_800CBC84(camera, sp4C, &spC4, 0) != 0) {
                    dynamicData->unk_1A |= 0x1000;
                    spF8 = OLib_Vec3fDist(sp4C, sp8C);
                    spF4 = OLib_Vec3fDist(sp4C, &spC4);
                    phi_f0_3 = (dynamicData->unk_1A & 0x10) ? 40.0f : 0.0f;
                    spF8 = spF8 + phi_f0_3;
                    Actor_GetScreenPos(camera->globalCtx, camera->trackActor, &sp5E, &sp5C);
                    if ((spF4 < spF8) || ((sp5E >= 0) && (sp5E < 0x141) && (sp5C >= 0) && (sp5C < 0xF1))) {
                        dynamicData->unk_1A |= 0x10;
                        spB4.yaw = spA4.yaw + 0x8000;
                        spB4.pitch = -spA4.pitch;
                        spB4.r = 40.0f;
                        sp114 = sp8C->pos;
                        sp114.y += 40.0f;
                        OLib_VecSphAddToVec3f(&sp120, &sp114, &spB4);
                        Camera_LERPCeilVec3f(&sp120, sp50, 0.15f, 0.15f, 0.2f);
                    } else if (dynamicData->unk_1A & 0x10) {
                        if (OLib_Vec3fDist(&spC4, sp50) < 20.0f) {
                            dynamicData->unk_1A &= ~0x10;
                            *sp50 = spC4;
                        } else {
                            Camera_LERPCeilVec3f(&spC4, sp50, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        dynamicData->unk_1A &= ~0x10;
                        *sp50 = spC4;
                    }
                dummy:; // TODO: Is Needed?
                } else {
                    if (dynamicData->unk_1A & 0x10) {
                        if (OLib_Vec3fDist(&spC4, sp50) < 20.0f) {
                            dynamicData->unk_1A &= ~0x10;
                            *sp50 = spC4;
                        } else {
                            Camera_LERPCeilVec3f(&spC4, sp50, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        dynamicData->unk_1A &= ~0x10;
                        *sp50 = spC4;
                    }
                    dynamicData->unk_1A &= ~0x1000;
                }
            } else if (fixedData->unk_30 & BATT1_FLG_2) {
                dynamicData->unk_1A &= ~0x10;
                if (func_800CBC84(camera, sp4C, &spC4, 3) != 0) {
                    *sp50 = spC4;
                } else {
                    *sp50 = spC4;
                }
            } else {
                dynamicData->unk_1A &= ~0x10;
                OLib_Vec3fDistNormalize(&sp114, sp4C, &spC4);
                spC4.x -= sp114.x;
                spC4.y -= sp114.y;
                spC4.z -= sp114.z;
                *sp50 = spC4;
            }
        } else {
            dynamicData->unk_1A &= ~0x10;
            *sp50 = *sp48;
        }
    }

    if (dynamicData->unk_16 != 0) {
        sp88 = 0;
    } else {
        sp88 = (s16)(sp94.yaw - spBC.yaw) * 0.50f;
    }

    camera->roll = Camera_LERPCeilS(sp88, camera->roll, 0.06f, 5);
    if (func_800CBAAC(camera) != 0) {
        phi_f12 = ((camera->globalCtx->state.frames & 8) != 0) ? fixedData->unk_20 - (fixedData->unk_20 * 0.5f) : fixedData->unk_20;
    } else {
        phi_f12 = ((gSaveContext.health <= 16) ? 0.8f : 1.0f) * (sp78 - (sp78 * 0.05f * spEC));
    }
    camera->fov = Camera_LERPCeilF(phi_f12, camera->fov, camera->fovUpdateRate, 0.1f);

    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Battle1.s")
#endif

s32 Camera_Battle2(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Battle3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Battle4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Battle0(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Used for following a secondary target such as zora fins or a z-target
 */
#ifdef NON_EQUIVALENT
s32 Camera_KeepOn1(Camera* camera) {
    f32 pad1;
    f32* pad2;
    Vec3f* sp48 = &camera->eye;
    Vec3f* sp44 = &camera->at;
    Vec3f* sp40 = &camera->eyeNext;
    Vec3f sp130;
    Vec3f sp124;
    Vec3f sp118;
    f32 sp114;
    PosRot* sp3C = &camera->trackActorPosRot;
    PosRot* sp30 = &camera->targetPosRot;
    f32 sp104;
    f32 temp_f2_3;
    f32 new_var;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    s16 spF2;
    s16 spF0;
    VecSph spE8;
    VecSph spE0;
    VecSph spD8;
    VecSph spD0;
    VecSph spC8;
    VecSph spC0;
    f32 new_var2;
    s32 new_var3;
    f32 temp_f0;
    Vec3f spA8;
    PosRot* spA4;
    CamColChk sp7C;

    s32 sp78;
    f32 sp74;
    s16 sp72;
    s16 sp70;
    f32 sp60;
    s16 sp56;
    s16 sp54;

    s16 phi_v1_3;
    s16 phi_a0;
    KeepOn1FixedData* fixedData = CAM_GET_STATIC_DATA(KeepOn1);
    KeepOn1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(KeepOn1);
    s16 temp_v0_3;
    s16 new_var4;

    spA4 = &camera->trackActor->focus;
    if (temp_v0_3) {} // TODO: Is needed?
    sp78 = 0;
    temp_f0 = Camera_GetTrackedActorHeight(camera);
    // temp_a1 = camera->target;

    if ((camera->target == NULL) || (camera->target->update == NULL)) {
        camera->target = NULL;
        Camera_ChangeMode(camera, CAM_MODE_TARGET);
        return 1;
    }

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * temp_f0 * (0.8f - ((68.0f / temp_f0) * -0.2f));
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->unk_08 = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = 40.0f - (40.0f - fixedData->unk_14);
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = 20.0f - (20.0f - fixedData->unk_18);
        // fixedData->unk_18 = fixedData->unk_18; // TODO: Fake
        // if (!fixedData->unk_08) {}
        fixedData->unk_1C = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_1C = 1.000f - (1.00f - fixedData->unk_1C); // TODO: Necessary?
        fixedData->unk_20 = READ_STATIC_DATA_VAL;
        fixedData->unk_24 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_24 = 1.0f - (1.0f - fixedData->unk_24);
        fixedData->unk_2C = READ_STATIC_DATA_VAL;
        fixedData->unk_28 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_28 = 0.2f - (0.2f - fixedData->unk_28);
    }

    sp60 = temp_f0;
    sp114 = fixedData->unk_00; // TODO: likely fake temp
    sp60 += sp114;
    OLib_Vec3fDiffToVecSphGeo(&spC8, sp44, sp48);
    OLib_Vec3fDiffToVecSphGeo(&spC0, sp44, sp40);
    sCameraInterfaceFlags = fixedData->unk_2C;

    if (RELOAD_PARAMS) {
        camera->actionFuncState++;
        dynamicData->unk_18 = 0;
        dynamicData->unk_10 = 0;
        dynamicData->unk_04 = 0.0f;
        dynamicData->unk_0C = camera->target;
        dynamicData->unk_16 = 7;
        dynamicData->unk_12 = spC8.yaw;
        dynamicData->unk_14 = spC8.pitch;
        dynamicData->unk_00 = spC8.r;
        dynamicData->unk_08 = sp3C->pos.y - camera->trackActorOffset.y;
        if ((2.0f * fixedData->unk_04) < camera->dist) {
            camera->dist = 2.0f * fixedData->unk_04;
            spC0.r = camera->dist;
            spC8.r = spC0.r;
            OLib_VecSphAddToVec3f(sp48, sp44, &spC8);
            *sp40 = *sp48;
        }
    }

    if (camera->status == CAM_STATUS_ACTIVE) {
        sUpdateCameraDirection = true;
        camera->inputDir.x = -spC8.pitch;
        camera->inputDir.y = spC8.yaw + 0x8000;
        camera->inputDir.z = 0;
    }

    if (func_800CB950(camera)) {
        dynamicData->unk_08 = sp3C->pos.y;
    }

    sp114 = fixedData->unk_04;

    if (camera->target->id != ACTOR_EN_BOOM) {
        Actor_GetWorldPosShapeRot(sp30, camera->target);
        Actor_GetFocus(&spA8, camera->target);
        camera->targetPosRot.pos.y = spA8.y;
    } else {
        Actor_GetFocus(sp30, camera->target);
    }
    if (dynamicData->unk_0C != camera->target) {
        dynamicData->unk_0C = camera->target;
        camera->atLERPStepScale = 0.0f;
    }

    camera->yOffsetUpdateRate = Camera_LERPCeilF(1.0f, camera->yOffsetUpdateRate, camera->speedRatio * 0.5f, 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(1.0f, camera->xzOffsetUpdateRate, camera->speedRatio * 0.2f, 0.0001f);
    // TODO: No f on 0.05?
    camera->fovUpdateRate = Camera_LERPCeilF(0.05, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);

    if (func_800CB950(camera)) {
        dynamicData->unk_08 = sp3C->pos.y;
        sp70 = false;
    } else {
        sp70 = true;
    }

    Camera_CalcAtForLockOn(camera, &spC0, sp30, fixedData->unk_00, fixedData->unk_08, &dynamicData->unk_08, &spD0,
                           fixedData->unk_2C | (sp70 ? KEEP1_FLG_80 : 0));
    sp124 = sp3C->pos;
    sp124.y += sp60;
    OLib_Vec3fDiffToVecSphGeo(&spD0, &sp124, sp30);

    if (sp114 < spD0.r) {
        sp74 = 1.0f;
    } else {
        sp74 = spD0.r / sp114;
    }

    OLib_Vec3fDiffToVecSphGeo(&spE8, sp44, sp40);

    if (spE8.r < fixedData->unk_04) {
        sp114 = fixedData->unk_04;
        spF8 = 20.0f;
    } else if (fixedData->unk_08 < spE8.r) {
        sp114 = fixedData->unk_08;
        spF8 = 20.0f;
    } else {
        sp114 = spE8.r;
        spF8 = 1.0f;
    }

    camera->rUpdateRateInv = Camera_LERPCeilF(spF8, camera->rUpdateRateInv, 0.5f, 0.1f);
    camera->dist = Camera_LERPCeilF(sp114, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
    spF8 = camera->dist;
    spE8.r = camera->dist;
    sp118 = sp30->pos;
    OLib_Vec3fDiffToVecSphGeo(&spD8, sp44, &sp118);
    if (1) {}
    if (1) {}
    if (1) {}      // TODO: Is needed?
    pad1 = spD8.r; // TODO: Fake temp?
    spD8.r = spF8 - (((pad1 <= spF8) ? spD8.r : spF8) * .5f);
    camera->dist = Camera_LERPCeilF(pad1, camera->dist, 0.06f, 0.1f);
    spE8.r = camera->dist;
    spFC = fixedData->unk_0C + ((fixedData->unk_10 - fixedData->unk_0C) * (1.1f - sp74));
    spE8.yaw = spC0.yaw;
    temp_v0_3 = (s16)(spD8.yaw - (s16)(spC0.yaw + 0x8000));
    if (dynamicData->unk_16 != 0) {
        if (dynamicData->unk_16 > 0) {
            sp72 = dynamicData->unk_16 - 1;
            spF2 = spD0.yaw;
            OLib_Vec3fDiffToVecSphGeo(&spD0, sp44, sp48);
            spD0.yaw = (s16)(spF2 + 0x8000);
            sp60 = (dynamicData->unk_00 - spD0.r) * 0.16666667f;
            spF2 = (s16)(dynamicData->unk_12 - (s16)(spF2 + 0x8000)) * 0.16666667f;
            spF0 = ((s16)(dynamicData->unk_14 - (s64)spD0.pitch)); // TODO: s16 cast on F0
            spF0 = (s16)(spF0 * 0.16666667f);
            spE8.r = Camera_LERPCeilF(spD0.r + (sp60 * sp72), spC8.r, .5f, 0.1f);
            spE8.yaw = Camera_LERPCeilS(spD0.yaw + (spF2 * sp72), spC8.yaw, .5f, 5);
            spE8.pitch = Camera_LERPCeilS(spD0.pitch + (spF0 * sp72), spC8.pitch, .5f, 5);
        }
        sp78 = 1;
        dynamicData->unk_16--;
    } else {
        new_var3 = ABS(temp_v0_3); // TODO: Fake temp?
        if ((s16)((spFC * 182.04167f) + .5f) < new_var3) {
            spF2 = temp_v0_3;
            sp104 = temp_v0_3 * 0.00549325f;
            temp_f2_3 = ((OLib_ClampMaxDist(spD8.r, spE8.r) / spE8.r) * ((spFC + 10.0f) - spFC)) + spFC;
            pad2 = &sp104; // TODO: Fake temp
            temp_f2_3 = ((temp_f2_3 * temp_f2_3) - 2.0f) / (temp_f2_3 - 360.0f);
            temp_f2_3 = (sp104 * (*pad2)) / ((temp_f2_3 * (*pad2)) + (2.0f - (360.0f * temp_f2_3)));

            if (spF2 >= 0) {
                phi_v1_3 = (s16)((temp_f2_3 * 182.04167f) + .5f);
            } else {
                phi_v1_3 = -(s16)((temp_f2_3 * 182.04167f) + .5f);
            }
            spE8.yaw = (s16)(spC0.yaw + 0x8000) + (s16)(phi_v1_3 + 0x8000);
        } else {
            new_var = (1.0f - camera->speedRatio) * 0.05f; // TODO: Fake temp?
            phi_v1_3 = (temp_v0_3 >= 0) ? DEGF_TO_BINANG(spFC) : -DEGF_TO_BINANG(spFC);
            if (phi_a0) {} // TODO: Fake to shaft a registers
            spE8.yaw = (s16)(spC0.yaw - (s16)((phi_v1_3 - temp_v0_3) * new_var));
        }
    }

    if (!spF0) {} // TODO: Is needed?
    if (sp78 == 0) {
        // TODO: extra 0 on 0.050f needed?
        phi_a0 = (s16)(((fixedData->unk_14 + ((fixedData->unk_18 - fixedData->unk_14) * sp74)) * 182.04167f) + .5f);
        phi_a0 -= (s16)((spD0.pitch * (0.5f + (sp74 * 0.5f))) + 0.5f);
        if (1) {}                          // TODO: Needed?
        sp60 = spD8.pitch * fixedData->unk_1C; // TODO: Fake sp60 temp?
        phi_a0 += (s16)sp60;

        if (phi_a0 < -0x3200) {
            phi_a0 = -0x3200;
        } else if (phi_a0 > 0x3200) {
            phi_a0 = 0x3200;
        }

        spE8.pitch = Camera_LERPCeilS(phi_a0, spC0.pitch, 0.11111111f, 5);
        OLib_VecSphAddToVec3f(sp40, sp44, &spE8);
        sp7C.pos = *sp40;
        if (camera->status == CAM_STATUS_ACTIVE) {
            if (!(fixedData->unk_2C & KEEP1_FLG_10)) {
                if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (fixedData->unk_2C & KEEP1_FLG_1)) {
                    if (func_800CBC84(camera, sp44, &sp7C, 0) != 0) {
                        dynamicData->unk_18 |= 0x1000;
                    } else {
                        dynamicData->unk_18 &= ~0x1000;
                    }
                } else if (fixedData->unk_2C & KEEP1_FLG_2) {
                    func_800CBC84(camera, sp44, &sp7C, 3);
                } else {
                    OLib_Vec3fDistNormalize(&sp130, sp44, &sp7C.pos);
                    sp7C.pos.x -= sp130.x;
                    sp7C.pos.y -= sp130.y;
                    sp7C.pos.z -= sp130.z;
                }
                *sp48 = sp7C.pos;
                dynamicData->unk_18 &= ~0x10;
            } else if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (fixedData->unk_2C & KEEP1_FLG_1)) {
                if (func_800CBC84(camera, sp44, &sp7C, 0) != 0) {
                    dynamicData->unk_18 |= 0x1000;
                    spF8 = OLib_Vec3fDist(sp44, spA4);
                    spF4 = OLib_Vec3fDist(sp44, &sp7C.pos);
                    spF8 += (dynamicData->unk_18 & 0x10) ? 40 : 0.0f; // TODO: 40.0f?
                    Actor_GetScreenPos(camera->globalCtx, camera->trackActor, &sp56, &sp54);
                    if ((spF4 < spF8) || ((sp56 >= 0) && (sp56 <= 320) && (sp54 >= 0) && (sp54 <= 240))) {
                        dynamicData->unk_18 |= 0x10;
                        spE0.yaw = (s16)(spD0.yaw + 0x8000);
                        spE0.pitch = -spD0.pitch;
                        spE0.r = 40.0f;
                        sp130 = spA4->pos;
                        sp130.y += 40.0f;
                        OLib_VecSphAddToVec3f(&sp124, &sp130, &spE0);
                        Camera_LERPCeilVec3f(&sp124, sp48, 0.15f, 0.15f, 0.2f);
                    } else if (dynamicData->unk_18 & 0x10) {
                        if (OLib_Vec3fDist(&sp7C.pos, sp48) < 20.0f) {
                            dynamicData->unk_18 &= ~0x10;
                            *sp48 = sp7C.pos;
                        } else {
                            Camera_LERPCeilVec3f(&sp7C.pos, sp48, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        dynamicData->unk_18 &= ~0x10;
                        *sp48 = sp7C.pos;
                    }
                dummy:; // TODO: Is this needed?
                } else {
                    if (dynamicData->unk_18 & 0x10) {
                        if (OLib_Vec3fDist(&sp7C.pos, sp48) < 20.0f) {
                            dynamicData->unk_18 &= ~0x10;
                            *sp48 = sp7C.pos;
                        } else {
                            Camera_LERPCeilVec3f(&sp7C.pos, sp48, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        dynamicData->unk_18 &= ~0x10;
                        *sp48 = sp7C.pos;
                        // if (sp104) {} // TODO: Is this needed?
                    }
                    dynamicData->unk_18 &= ~0x1000;
                }
            } else if (fixedData->unk_2C & KEEP1_FLG_2) {
                dynamicData->unk_18 &= ~0x10;
                if (func_800CBC84(camera, sp44, &sp7C, 3) != 0) {
                    *sp48 = sp7C.pos;
                } else {
                    *sp48 = sp7C.pos;
                    ;
                }
            } else {
                dynamicData->unk_18 &= ~0x10;
                OLib_Vec3fDistNormalize(&sp130, sp44, &sp7C.pos);
                sp7C.pos.x -= sp130.x;
                sp7C.pos.y -= sp130.y;
                sp7C.pos.z -= sp130.z;
                *sp48 = sp7C.pos;
            }
        } else {
            dynamicData->unk_18 &= ~0x10;
            *sp48 = *sp40;
        }
    }

    // TODO: spF8 temp needed?
    camera->fov = Camera_LERPCeilF(spF8 = fixedData->unk_20, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.2f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, sp70 ? fixedData->unk_28 : fixedData->unk_24);

    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn1.s")
#endif

s32 Camera_KeepOn2(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Talking to an NPC
 */
s32 Camera_KeepOn3(Camera* camera) {
    Vec3f* eye = &camera->eye;
    s32 temp_f0;
    Vec3f* eyeNext = &camera->eyeNext;
    Vec3f spD8;
    Vec3f spCC;
    Vec3f spC0;
    f32 temp_f0_2;
    f32 spB8;
    f32 spB4;
    f32 swingAngle;
    Actor* spA8[2];
    VecSph spA0;
    VecSph sp98;
    VecSph sp90;
    VecSph sp88;
    VecSph sp80;
    Vec3f* at = &camera->at;
    s32 sp78;
    f32 phi_f14;
    PosRot* sp70;
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 phi_a3;
    PosRot* sp3C = &camera->trackActorPosRot;
    KeepOn3FixedData* fixedData = CAM_GET_STATIC_DATA(KeepOn3);
    KeepOn3DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(KeepOn3);
    f32 trackHeight;
    s32 i;

    sp70 = &camera->trackActor->focus; // TODO: Move above?
    sp6A = 0;
    trackHeight = Camera_GetTrackedActorHeight(camera);

    if ((camera->target == NULL) || (camera->target->update == NULL)) {
        camera->target = NULL;
        Camera_ChangeMode(camera, CAM_MODE_TARGET);
        return 1;
    }

    if (RELOAD_PARAMS) {
        if (camera->globalCtx->view.unk164 == 0) {
            Camera_SetFlags(camera, CAM_FLAG2_20);
            camera->globalCtx->view.unk164 = camera->camId | 0x50;
            return 1;
        }
        Camera_UnsetFlags(camera, CAM_FLAG2_20);
    }

    Camera_UnsetFlags(camera, CAM_FLAG2_10);
    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        
        fixedData->unk_00 = READ_STATIC_DATA_VAL * 0.01f * trackHeight * (0.8f - ((68.0f / trackHeight) * -0.2f));
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->unk_08 = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_1C = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_20 = READ_STATIC_DATA_VAL;
        fixedData->unk_24 = READ_STATIC_DATA_VAL * 0.01f;
        fixedData->unk_2C = READ_STATIC_DATA_VAL;
        fixedData->unk_2E = READ_STATIC_DATA_VAL;
        fixedData->unk_28 = READ_STATIC_DATA_VAL * 0.01f;
    }

    if (camera->actionFuncState == 10) {
        fixedData->unk_2C >>= 1;
        if (fixedData->unk_2C < 0x14) {
            fixedData->unk_2C = 0x14;
        }
    }

    OLib_Vec3fDiffToVecSphGeo(&sp88, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&sp80, at, eyeNext);
    Actor_GetFocus(&camera->targetPosRot, camera->target);
    spD8 = sp3C->pos;
    spD8.y += trackHeight;
    OLib_Vec3fDiffToVecSphGeo(&spA0, &spD8, &camera->targetPosRot.pos);

    if (RELOAD_PARAMS) {
        camera->actionFuncState++;
        spA8[0] = camera->target;
        spA8[1] = camera->trackActor;
        dynamicData->unk_0C = camera->target;
        phi_f14 = (fixedData->unk_08 < spA0.r) ? 1.0f : (spA0.r / fixedData->unk_08);

        dynamicData->unk_1C = fixedData->unk_2C;
        spB8 = ((1.0f - phi_f14) * spA0.r) / dynamicData->unk_1C;

        if (fixedData->unk_2E & KEEP3_FLG_40) {
            spA0.pitch = 0;
        }

        swingAngle = LERPIMP(fixedData->unk_14, fixedData->unk_18, phi_f14);
        sp98.pitch = DEGF_TO_BINANG(swingAngle) + ((s16) - (spA0.pitch * fixedData->unk_1C));
        swingAngle = LERPIMP(fixedData->unk_0C, fixedData->unk_10, phi_f14);

        phi_a3 = DEGF_TO_BINANG(swingAngle);

        sp78 = 1;
        if ((camera->target->category == ACTORCAT_DOOR) || (camera->target->id == ACTOR_EN_TALK)) {
            if ((s16)(camera->targetPosRot.rot.y - sp80.yaw) > 0) {
                phi_a3 = -phi_a3;
            }

            if (ABS(spA0.pitch) < 0x157C) { // 30.2 degrees
                sp98.yaw = BINANG_ROT180(spA0.yaw) + phi_a3;
                sp6A = (s16)(BINANG_ROT180(spA0.yaw) - phi_a3);
            } else {
                sp78 = 0;
                sp90.r = 30.0f;
                sp90.yaw = BINANG_ROT180(spA0.yaw) + (phi_a3 >> 2);
                sp90.pitch = -spA0.pitch;
                spCC = sp70->pos;
                spCC.y += 30.0f;
                OLib_VecSphAddToVec3f(&spC0, &spCC, &sp90);
                spCC.x = (camera->targetPosRot.pos.x + spD8.x) * 0.5f;
                spCC.y = (camera->targetPosRot.pos.y + spD8.y) * 0.5f;
                spCC.z = (camera->targetPosRot.pos.z + spD8.z) * 0.5f;
                OLib_Vec3fDiffToVecSphGeo(&sp98, &spCC, &spC0);
                if (sp98.pitch < -0x2328) { // 49.4 degrees
                    sp98.pitch = -0x2328;
                }
            }
        } else if (!(fixedData->unk_2E & KEEP3_FLG_20) && (ABS((s16)(spA0.yaw - sp80.yaw)) < 0x4000)) {
            if ((s16)(spA0.yaw - sp80.yaw) > 0) {
                phi_a3 = -phi_a3;
            }
            sp98.yaw = (s16)(spA0.yaw + phi_a3);
            sp6A = (s16)(spA0.yaw - phi_a3);
        } else {
            if ((s16)(BINANG_ROT180(spA0.yaw) - sp80.yaw) < 0) {
                phi_a3 = -phi_a3;
            }

            sp98.yaw = BINANG_ROT180(spA0.yaw) + phi_a3;
            sp6A = BINANG_ROT180(spA0.yaw) - phi_a3;
        }

        sp6C = sp98.yaw;
        sp6E = sp98.pitch;

        if (fixedData->unk_28) {}
        spB4 = spA0.r;

        phi_f14 = fixedData->unk_28;
        spA0.r = spB8 * phi_f14 + (spB4 * (1.0f - phi_f14));
        spD8 = sp3C->pos;
        spD8.y += trackHeight;

        OLib_VecSphAddToVec3f(&dynamicData->unk_10, &spD8, &spA0);
        dynamicData->unk_10.y += fixedData->unk_00;
        spA0.r = spB4;

        if (sp78 != 0) {
            sp98.r = ((fixedData->unk_04 + (spA0.r * 0.5f)) - sp80.r) + sp80.r;
            i = 0;
            sp78 = 14;
            OLib_VecSphAddToVec3f(&spCC, &dynamicData->unk_10, &sp98);
            if (!(fixedData->unk_2E & KEEP3_FLG_80)) {
                if (CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, &dynamicData->unk_10, &spCC,
                                               spA8, 2) ||
                    Camera_BGCheck(camera, &dynamicData->unk_10, &spCC)) {
                    sp98.yaw = sp6A;
                    OLib_VecSphAddToVec3f(&spCC, &dynamicData->unk_10, &sp98);
                }
                while (i < sp78) {
                    if (!CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, &dynamicData->unk_10,
                                                    &spCC, spA8, 2) &&
                        !Camera_BGCheck(camera, &dynamicData->unk_10, &spCC)) {
                        break;
                    }
                    sp98.yaw = sp6C + D_801B9E18[i];
                    sp98.pitch = sp6E + D_801B9E34[i];
                    OLib_VecSphAddToVec3f(&spCC, &dynamicData->unk_10, &sp98);
                    i++;
                }
            }
        }

        Camera_UnsetFlags(camera, CAM_FLAG2_8 | CAM_FLAG2_4);
        temp_f0 = ((dynamicData->unk_1C + 1) * dynamicData->unk_1C) >> 1;
        dynamicData->unk_04 = (f32)(s16)(sp98.yaw - sp80.yaw) / temp_f0;
        dynamicData->unk_08 = (f32)(s16)(sp98.pitch - sp80.pitch) / temp_f0;
        dynamicData->unk_00 = (sp98.r - sp80.r) / temp_f0;
        sCameraInterfaceFlags = SHRINKWINVAL_PREV | IFACE_ALPHA(0xF);
        return true;
    }

    sCameraInterfaceFlags = fixedData->unk_2E;

    if (dynamicData->unk_1C != 0) {
        temp_f0_2 = dynamicData->unk_1C;
        at->x += (dynamicData->unk_10.x - at->x) / temp_f0_2;
        at->y += (dynamicData->unk_10.y - at->y) / temp_f0_2;
        at->z += (dynamicData->unk_10.z - at->z) / temp_f0_2;
        sp98.r = (dynamicData->unk_00 * temp_f0_2) + sp80.r + 1.0f;
        sp98.yaw = sp80.yaw + (s16)(dynamicData->unk_04 * temp_f0_2);
        sp98.pitch = sp80.pitch + (s16)(dynamicData->unk_08 * temp_f0_2);
        OLib_VecSphAddToVec3f(eyeNext, at, &sp98);
        *eye = *eyeNext;
        camera->fov = Camera_LERPCeilF(fixedData->unk_20, camera->fov, 0.5f, 0.1f);
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, fixedData->unk_24);
        func_800CBFA4(camera, at, eye, 3);
        dynamicData->unk_1C--;
    } else {
        Camera_SetFlags(camera, CAM_FLAG2_400 | CAM_FLAG2_10);
    }

    Camera_UpdateAtActorOffset(camera, &sp3C->pos);
    camera->dist = OLib_Vec3fDist(at, eye);
    if (camera->flags2 & CAM_FLAG2_8) {
        sCameraInterfaceFlags = SHRINKWINVAL_NONE | IFACE_ALPHA(0);
        Camera_SetUpdateRatesSlow(camera);
        camera->atLERPStepScale = 0.0f;

        if ((camera->xzSpeed > 0.001f) || CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R)) {
            Camera_SetFlags(camera, CAM_FLAG2_4);
            Camera_UnsetFlags(camera, CAM_FLAG2_8);
        }
    }

    if (dynamicData->unk_0C != camera->target) {
        dynamicData->unk_0C = camera->target;
        camera->actionFuncState = 10;
    }

    return true;
}

/**
 * Used for settings where camera turns around and faces player 
 * eg. all item-based settings, elegy shell cutscene, death cutscene, ...
 */
s32 Camera_KeepOn4(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Actor* spCC[2];
    f32 temp_f0_2;
    f32 new_var;
    CollisionPoly* spC0;
    VecSph spB8;
    VecSph spB0;
    VecSph spA8;
    s16* sp44 = &camera->data2;
    s16 spA2;
    s16 spA0;
    s16 sp9E;
    s16 sp9C;
    s16 pad1;
    PosRot* sp38 = &camera->trackActorPosRot;
    KeepOn4FixedData* fixedData = CAM_GET_STATIC_DATA(KeepOn4);
    KeepOn4DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(KeepOn4);
    f32 trackHeight;
    s32 bgId;
    s16 sp82; // mode
    Player* player; // sp7C
    Vec3f* data;
    CameraModeValue* values;
    PosRot sp60;
    PosRot sp4C;

    if (RELOAD_PARAMS) {
        if (camera->globalCtx->view.unk164 == 0) {
            Camera_SetFlags(camera, CAM_FLAG2_20);
            Camera_UnsetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
            camera->globalCtx->view.unk164 = camera->camId | 0x50;
            return true;
        }
        dynamicData->unk_18 = *sp44;
        Camera_UnsetFlags(camera, CAM_FLAG2_20);
    }

    if (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) {
        player = (Player*)camera->trackActor;
        switch (((Player*)camera->trackActor)->transformation) {
            case PLAYER_FORM_DEKU:
                sp82 = CAM_MODE_DEKUSHOOT;
                break;
            case PLAYER_FORM_GORON:
                sp82 = CAM_MODE_GORONDASH;
                break;
            case PLAYER_FORM_ZORA:
                sp82 = CAM_MODE_DEKUFLY;
                break;
            case PLAYER_FORM_FIERCE_DEITY:
                sp82 = CAM_MODE_JUMP;
                break;
            default:
                sp82 = CAM_MODE_NORMAL;
                break;
        }

        trackHeight = Camera_GetTrackedActorHeight(camera) - (player->unk_AB8 * camera->trackActor->scale.y);
    } else {
        sp82 = CAM_MODE_NORMAL;
        trackHeight = Camera_GetTrackedActorHeight(camera);
    }

    if (dynamicData->unk_18 != *sp44) {
        camera->actionFuncState = 20;
        Camera_SetFlags(camera, CAM_FLAG2_20);
        Camera_UnsetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
        camera->globalCtx->view.unk164 = camera->camId | 0x50;
        return true;
    }

    Camera_UnsetFlags(camera, CAM_FLAG2_10);
    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[sp82].values;
        new_var = -0.5f;
        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * trackHeight * ((1.0f + new_var) - ((68.0f / trackHeight) * new_var));
        fixedData->unk_04 = READ_SCALED_STATIC_DATA_VAL * trackHeight * ((1.0f + new_var) - ((68.0f / trackHeight) * new_var));
        fixedData->unk_08 = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        fixedData->unk_1C = READ_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_1E = READ_STATIC_DATA_VAL;
    }

    sUpdateCameraDirection = true;
    sCameraInterfaceFlags = fixedData->unk_1C;
    OLib_Vec3fDiffToVecSphGeo(&spB0, at, eye);
    data = &D_801EDDD0;
    OLib_Vec3fDiffToVecSphGeo(&spA8, at, eyeNext);
    D_801EDDD0 = sp38->pos;
    D_801EDDD0.y = data->y + trackHeight;
    temp_f0_2 = BgCheck_CameraRaycastFloor2(&camera->globalCtx->colCtx, &spC0, &bgId, &D_801EDDD0);
    if ((fixedData->unk_00 + data->y) < temp_f0_2) {
        D_801EDDD0.y = temp_f0_2 + 10.0f;
    } else {
        D_801EDDD0.y = fixedData->unk_00 + data->y;
    }
    if (fixedData->unk_10 != 0.0f) {
        D_801EDDE0 = (*data);
        spB8.r = fixedData->unk_10;
        spB8.pitch = 0;
        spB8.yaw = sp38->rot.y;
        OLib_VecSphAddToVec3f(&D_801EDDD0, &D_801EDDD0, &spB8);
    }

    sp9C = 0;
    switch (camera->actionFuncState) {
        case 0:
        case 20:
            spCC[sp9C] = camera->trackActor;
            sp9C++;
            Camera_SetUpdateRatesFastPitch(camera);
            Camera_UnsetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
            dynamicData->unk_14 = fixedData->unk_1E;
            dynamicData->unk_08 = sp38->pos.y - camera->trackActorOffset.y;

            switch (fixedData->unk_1C & (KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2)) {
                case KEEP4_FLG_2:
                    spA2 = DEGF_TO_BINANG(fixedData->unk_08);
                    spA0 = SUB16(BINANG_ROT180(sp38->rot.y), spA8.yaw) < 0
                               ? BINANG_ROT180(sp38->rot.y) + DEGF_TO_BINANG(fixedData->unk_0C)
                               : BINANG_ROT180(sp38->rot.y) - DEGF_TO_BINANG(fixedData->unk_0C);
                    break;
                case (KEEP4_FLG_8 | KEEP4_FLG_4):
                    spA2 = DEGF_TO_BINANG(fixedData->unk_08);
                    pad1 = BINANG_ROT180(sp38->rot.y);
                    spA0 = pad1 + DEGF_TO_BINANG(fixedData->unk_0C);
                    break;
                case KEEP4_FLG_4:
                    spA2 = DEGF_TO_BINANG(fixedData->unk_08);
                    spA0 = DEGF_TO_BINANG(fixedData->unk_0C);
                    break;
                case (KEEP4_FLG_4 | KEEP4_FLG_2):
                    spA2 = spA8.pitch + DEGF_TO_BINANG(fixedData->unk_08);
                    spA0 = spA8.yaw + DEGF_TO_BINANG(fixedData->unk_0C);
                    break;
                case KEEP4_FLG_8:
                    if (camera->target != NULL) {
                        Actor_GetWorldPosShapeRot(&sp60, camera->target);
                        spA2 = DEGF_TO_BINANG(fixedData->unk_08) - sp60.rot.x;
                        spA0 = (SUB16(BINANG_ROT180(sp60.rot.y), spA8.yaw) > 0)
                                   ? BINANG_ROT180(sp60.rot.y) + DEGF_TO_BINANG(fixedData->unk_0C)
                                   : BINANG_ROT180(sp60.rot.y) - DEGF_TO_BINANG(fixedData->unk_0C);

                        spCC[1] = camera->target;
                        sp9C++;
                        break;
                    }
                case (KEEP4_FLG_8 | KEEP4_FLG_2):
                    if (camera->target != 0) {
                        Actor_GetWorld(&sp4C, camera->target);
                        spA2 = DEGF_TO_BINANG(fixedData->unk_08);
                        sp9E = Camera_CalcXZAngle(&sp4C.pos, &sp38->pos);
                        spA0 = (SUB16(sp9E, spA8.yaw) > 0) ? sp9E + DEGF_TO_BINANG(fixedData->unk_0C)
                                                           : sp9E - DEGF_TO_BINANG(fixedData->unk_0C);
                        spCC[1] = camera->target;
                        sp9C++;
                        break;
                    }
                case (KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2):
                    spA2 = DEGF_TO_BINANG(fixedData->unk_08);
                    spA0 = spA8.yaw;
                    break;
                default:
                    spA2 = spA8.pitch;
                    spA0 = spA8.yaw;
                    break;
            }

            spB8.pitch = spA2;
            spB8.yaw = spA0;
            spB8.r = fixedData->unk_04;
            // Odd that the return is set to bgId and remains unused
            bgId = func_800CC260(camera, &D_801EDDF0, &D_801EDDD0, &spB8, spCC, sp9C);
            dynamicData->unk_04 = (f32)(s16)(spB8.pitch - spA8.pitch) / dynamicData->unk_14;
            dynamicData->unk_00 = (f32)(s16)(spB8.yaw - spA8.yaw) / dynamicData->unk_14;
            dynamicData->unk_10 = spA8.yaw;
            dynamicData->unk_12 = spA8.pitch;
            camera->actionFuncState++;
            dynamicData->unk_16 = 1;
            break;

        case 10:
            dynamicData->unk_08 = sp38->pos.y - camera->trackActorOffset.y;
            break;
    }

    if (fixedData->unk_1C & KEEP4_FLG_40) {
        if (dynamicData->unk_14 != 0) {
            at->x += ((data->x - at->x) / dynamicData->unk_14);
            at->y += ((data->y - at->y) / dynamicData->unk_14);
            at->z += ((data->z - at->z) / dynamicData->unk_14);
            Camera_UpdateAtActorOffset(camera, &sp38->pos);
        }
        camera->yOffsetUpdateRate = 0.25f;
        camera->xzOffsetUpdateRate = 0.25f;
        camera->atLERPStepScale = 0.0f;
    } else {
        camera->yOffsetUpdateRate = 0.25f;
        camera->xzOffsetUpdateRate = 0.25f;
        camera->atLERPStepScale = 0.75f;
        Camera_LERPCeilVec3f(data, at, 0.2f, 0.2f, 0.2f);
        camera->atLERPStepScale = 0.0f;
        Camera_UpdateAtActorOffset(camera, &sp38->pos);
    }
    camera->dist = Camera_LERPCeilF(fixedData->unk_04, camera->dist, 0.25f, 1.0f);
    spB8.r = camera->dist;
    if (dynamicData->unk_14 != 0) {
        Camera_SetFlags(camera, CAM_FLAG2_20);
        dynamicData->unk_10 += (s16)dynamicData->unk_00;
        dynamicData->unk_12 += (s16)dynamicData->unk_04;
        dynamicData->unk_14--;
    } else {
        Camera_SetFlags(camera, CAM_FLAG2_400 | CAM_FLAG2_10);
    }
    spB8.yaw = Camera_LERPCeilS(dynamicData->unk_10, spA8.yaw, fixedData->unk_14, 5);
    spB8.pitch = Camera_LERPCeilS(dynamicData->unk_12, spA8.pitch, fixedData->unk_14, 5);
    OLib_VecSphAddToVec3f(eyeNext, at, &spB8);
    *eye = *eyeNext;
    func_800CBFA4(camera, at, eye, 3);
    camera->fov = Camera_LERPCeilF(fixedData->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    return true;
}

s32 Camera_KeepOn0(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Used for many fixed-based camera settings i.e. camera is fixed in rotation, and often position (but not always)
 */
s32 Camera_Fixed1(Camera* camera) {
    s32 pad[2];
    s32 yawDiff;
    VecSph eyeOffset;
    VecSph eyeAtOffset;
    VecSph sp7C;
    u32 negOne;
    Vec3f adjustedPos;
    SubCamData* bgCamData;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    CameraModeValue* values;
    PosRot* sp50;
    PosRot* sp4C;
    VecSph sp44;
    Fixed1FixedData* fixedData = CAM_GET_STATIC_DATA(Fixed1);
    Fixed1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Fixed1);

    OLib_Vec3fDiffToVecSphGeo(&sp7C, at, eye);

    if (!RELOAD_PARAMS) {
        // Pass
    } else {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values; // sp54
        bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
        Camera_Vec3sToVec3f(&dynamicData->eyePosRotTarget.pos, &bgCamData->pos);

        dynamicData->eyePosRotTarget.rot = bgCamData->rot;
        dynamicData->fov = bgCamData->fov;
        dynamicData->trackActor = camera->trackActor;

        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * trackHeight;
        fixedData->unk_04 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->fov = READ_STATIC_DATA_VAL;
        fixedData->flags = READ_STATIC_DATA_VAL;

        if (fixedData->flags & FIXD1_FLG_10) {
            if (camera->target == NULL) {
                return false;
            }

            sp50 = &camera->target->home;
            sp4C = &camera->target->world;

            OLib_Vec3fDiffToVecSphGeo(&sp44, &sp50->pos, &dynamicData->eyePosRotTarget.pos);
            sp44.yaw = sp4C->rot.y + (s16)(sp44.yaw - sp50->rot.y);
            OLib_VecSphAddToVec3f(&dynamicData->eyePosRotTarget.pos, &sp4C->pos, &sp44);
            yawDiff = (s16)(dynamicData->eyePosRotTarget.rot.y - sp50->rot.y);
            dynamicData->eyePosRotTarget.rot.y = sp4C->rot.y + yawDiff;
        }
    }

    negOne = -1;

    if (dynamicData->trackActor != camera->trackActor) {
        camera->actionFuncState = 20;
    }

    if (dynamicData->fov == (s32)negOne) {
        dynamicData->fov = fixedData->fov * 100;
    } else if (dynamicData->fov <= 360) {
        dynamicData->fov *= 100;
    }

    sCameraInterfaceFlags = fixedData->flags;

    if (camera->actionFuncState == 0) {
        camera->actionFuncState++;
        Camera_SetUpdateRatesSlow(camera);
        if (dynamicData->fov != (s32)negOne) {
            fixedData->fov = SCALED_STATIC_DATA(dynamicData->fov);
        }

        if (bgCamData->unk_0E != (s32)negOne) {
            fixedData->unk_04 = SCALED_STATIC_DATA(bgCamData->unk_0E);
        }
    }

    OLib_Vec3fDiffToVecSphGeo(&eyeAtOffset, eye, at);
    Camera_LERPCeilVec3f(&dynamicData->eyePosRotTarget.pos, eye, fixedData->unk_04, fixedData->unk_04, 0.2f);
    adjustedPos = playerPosRot->pos;
    adjustedPos.y += trackHeight;
    camera->dist = OLib_Vec3fDist(&adjustedPos, eye);
    eyeOffset.r = camera->dist;
    eyeOffset.pitch = Camera_LERPCeilS(dynamicData->eyePosRotTarget.rot.x * -1, eyeAtOffset.pitch, fixedData->unk_04, 5);
    eyeOffset.yaw = Camera_LERPCeilS(dynamicData->eyePosRotTarget.rot.y, eyeAtOffset.yaw, fixedData->unk_04, 5);
    OLib_VecSphAddToVec3f(at, eye, &eyeOffset);
    camera->eyeNext = *eye;
    Camera_BGCheck(camera, eye, at);
    camera->fov = Camera_LERPCeilF(fixedData->fov, camera->fov, fixedData->unk_04, 0.1f);
    camera->roll = 0;
    camera->atLERPStepScale = 0.0f;
    Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    camera->roll = Camera_LERPCeilS(dynamicData->eyePosRotTarget.rot.z, camera->roll, fixedData->unk_04, 5);
    return true;
}

/**
 * Used for many pivot-based camera settings i.e. camera fixed in position but free to rotate
 */
s32 Camera_Fixed2(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;
    PosRot* sp34 = &camera->trackActorPosRot;
    f32 temp_f0_3;
    f32 new_var;
    SubCamData* bgCamData;
    VecSph sp80;
    PosRot* sp7C;
    PosRot* sp78;
    VecSph sp70;
    Vec3f* new_var1;
    Vec3f* new_var2;
    Player* player;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    Actor* actor;
    Fixed2FixedData* fixedData = CAM_GET_STATIC_DATA(Fixed2);
    Fixed2DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Fixed2);
    CameraModeValue* values;
    Vec3f sp44;

    if (!RELOAD_PARAMS) {
    } else {
        if (new_var2) {}
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * trackHeight * (0.8f - ((68.0f / trackHeight) * -0.2f));
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->unk_08 = READ_STATIC_DATA_VAL;
        fixedData->unk_0C = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_SCALED_STATIC_DATA_VAL;
        fixedData->unk_14 = READ_STATIC_DATA_VAL;
        fixedData->unk_18 = READ_STATIC_DATA_VAL;
        dynamicData->unk_1C = fixedData->unk_14 * 100.0f;
        bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
        if (bgCamData != NULL) {
            if (!(fixedData->unk_18 & FIXD2_FLG_2)) {
                Camera_Vec3sToVec3f(&dynamicData->unk_00, &bgCamData->pos);
            } else {
                if (camera->trackActor != &GET_PLAYER(camera->globalCtx)->actor) {
                    player = GET_PLAYER(camera->globalCtx);
                    OLib_Vec3fDiffToVecSphGeo(&sp70, &player->actor.focus.pos, eye);
                    if (sp70.r < fixedData->unk_04) {
                        sp70.r = fixedData->unk_04;
                        if (sp70.pitch < 0xBB8) { // 16.5 degrees
                            sp70.pitch = 0xBB8;
                        }

                        new_var1 = &player->actor.focus.pos;

                        OLib_VecSphAddToVec3f(&dynamicData->unk_00, new_var1, &sp70);
                    } else {
                        dynamicData->unk_00 = *eye;
                    dummy:; // TODO: Needed?
                    }
                } else {
                    dynamicData->unk_00 = camera->eye;
                }
            }

            if (bgCamData->fov != -1) {
                if (fixedData->unk_18 & FIXD2_FLG_80) {
                    dynamicData->unk_1C = (bgCamData->fov >> 1) + (bgCamData->fov >> 2);
                    if (dynamicData->unk_1C < 0x1E) {
                        dynamicData->unk_1C = 0x1E;
                    }
                } else {
                    dynamicData->unk_1C = bgCamData->fov;
                }
            }

            if (bgCamData->unk_0E != -1) {
                dynamicData->unk_0C = bgCamData->unk_0E;
            } else {
                dynamicData->unk_0C = fixedData->unk_08;
            }

            if (bgCamData->unk_10 != -1) {
                if (fixedData->unk_18 & FIXD2_FLG_4) {
                    dynamicData->unk_14 = bgCamData->unk_10 * 0.01f;
                    dynamicData->unk_18 = fixedData->unk_0C;
                } else {
                    temp_f0_3 = bgCamData->unk_10 * 0.01f;
                    dynamicData->unk_18 = temp_f0_3;
                    dynamicData->unk_14 = temp_f0_3;
                }
            } else {
                dynamicData->unk_14 = fixedData->unk_10;
                dynamicData->unk_18 = fixedData->unk_0C;
            }
            if (fixedData->unk_18 & FIXD2_FLG_10) {
                if (camera->target == 0) {
                    return 0;
                }
                sp7C = &camera->target->home;
                sp78 = &camera->target->world;
                OLib_Vec3fDiffToVecSphGeo(&sp70, &sp7C->pos, &dynamicData->unk_00);
                sp70.yaw = sp78->rot.y + (s16)(sp70.yaw - sp7C->rot.y);
                OLib_VecSphAddToVec3f(&dynamicData->unk_00, &sp78->pos, &sp70);
            }
        } else {
            dynamicData->unk_00 = camera->eye;
            dynamicData->unk_0C = fixedData->unk_08;
            dynamicData->unk_14 = fixedData->unk_10;
            dynamicData->unk_18 = fixedData->unk_0C;
        }
        if (dynamicData->unk_1C <= 360) {
            dynamicData->unk_1C *= 100;
        }
        if (camera->actionFuncState == 20) {
            dynamicData->unk_14 = 0.2f;
        }
        if (1) {}
    }

    sCameraInterfaceFlags = fixedData->unk_18;
    new_var = 0.0f; // TODO: Fake temp?

    if (fixedData->unk_18 & FIXD2_FLG_8) {
        if (camera->target == NULL) {
            return false;
        }

        spB0.x = camera->target->focus.pos.x;
        spB0.y = camera->target->focus.pos.y;
        spB0.z = camera->target->focus.pos.z;
        camera->atActorOffset.x = spB0.x - sp34->pos.x;
        camera->atActorOffset.y = spB0.y - sp34->pos.y;
        camera->atActorOffset.z = spB0.z - sp34->pos.z;
    } else if (fixedData->unk_18 & FIXD2_FLG_40) {
        sp98.x = new_var;
        sp98.y = fixedData->unk_00 + trackHeight;
        sp98.z = new_var;

        if (camera->target != NULL) {
            new_var1 = &camera->trackActor->focus.pos;
            new_var2 = &camera->target->focus.pos;
            sp98.x = ((void)0, new_var) + ((new_var2->x - new_var1->x) * 0.4f);
            sp98.y += (new_var2->y - new_var1->y) * 0.4f;
            sp98.z = ((void)0, new_var) + ((new_var2->z - new_var1->z) * 0.4f);
        }

        Camera_LERPCeilVec3f(&sp98, &camera->atActorOffset, 0.25f, 0.25f, 0.1f);
        spB0.x = sp34->pos.x + camera->atActorOffset.x;
        spB0.y = sp34->pos.y + camera->atActorOffset.y;
        spB0.z = sp34->pos.z + camera->atActorOffset.z;
    } else if (fixedData->unk_18 & FIXD2_FLG_80) {
        sp98.x = new_var;
        sp98.y = fixedData->unk_00 + trackHeight;
        sp98.z = new_var;

        if (camera->target != NULL) {
            new_var1 = &camera->trackActor->focus.pos;
            new_var2 = &camera->target->focus.pos;
            sp98.x = ((void)0, new_var) + ((new_var2->x - new_var1->x) * 0.7f);
            sp98.y += (new_var2->y - new_var1->y) * 0.7f;
            sp98.z = ((void)0, new_var) + ((new_var2->z - new_var1->z) * 0.7f);
        }

        Camera_LERPCeilVec3f(&sp98, &camera->atActorOffset, 0.25f, 0.25f, 0.1f);
        spB0.x = sp34->pos.x + camera->atActorOffset.x;
        spB0.y = sp34->pos.y + camera->atActorOffset.y;
        spB0.z = sp34->pos.z + camera->atActorOffset.z;
    } else {
        sp98.x = new_var;
        sp98.z = new_var;

        // (stateFlags1 & 0x4) Climbing ledge
        if ((((Player*)camera->trackActor)->stateFlags1 & 0x4000) || (((Player*)camera->trackActor)->stateFlags1 & 4)) {
            sp98.y = fixedData->unk_00;
        } else {
            sp98.y = fixedData->unk_00 + trackHeight;
        }

        Camera_LERPCeilVec3f(&sp98, &camera->atActorOffset, dynamicData->unk_14, dynamicData->unk_14, 0.1f);
        spB0.x = sp34->pos.x + camera->atActorOffset.x;
        spB0.y = sp34->pos.y + camera->atActorOffset.y;
        spB0.z = sp34->pos.z + camera->atActorOffset.z;
    }

    if (camera->actionFuncState == 0) {
        Camera_SetUpdateRatesSlow(camera);
        if (!(fixedData->unk_18 & FIXD2_FLG_1)) {
            *at = spB0;
            OLib_Vec3fDiffToVecSphGeo(&sp80, at, &dynamicData->unk_00);
            if ((dynamicData->unk_0C < sp80.r) || (fixedData->unk_18 & FIXD2_FLG_20)) {
                sp80.r = dynamicData->unk_0C;
                OLib_VecSphAddToVec3f(&spA4, at, &sp80);
            } else {
                if (sp80.r < fixedData->unk_04) {
                    sp80.r = fixedData->unk_04;
                    OLib_VecSphAddToVec3f(&spA4, at, &sp80);
                } else {
                    spA4 = dynamicData->unk_00;
                }
            }
            sp44 = spA4;
            camera->eyeNext = sp44;
            *eye = sp44;
            camera->fov = dynamicData->unk_1C * 0.01f;
        }
    }

    Camera_LERPCeilVec3f(&spB0, at, dynamicData->unk_14, dynamicData->unk_14, 1.0f);
    OLib_Vec3fDiffToVecSphGeo(&sp80, at, &dynamicData->unk_00);
    if ((dynamicData->unk_0C < sp80.r) || (fixedData->unk_18 & FIXD2_FLG_20)) {
        sp80.r = dynamicData->unk_0C;
        OLib_VecSphAddToVec3f(&spA4, at, &sp80);
    } else {
        if (sp80.r < fixedData->unk_04) {
            sp80.r = fixedData->unk_04;
            OLib_VecSphAddToVec3f(&spA4, at, &sp80);
        } else {
            spA4 = dynamicData->unk_00;
        }
    }

    Camera_LERPCeilVec3f(&spA4, eyeNext, dynamicData->unk_18, dynamicData->unk_18, 0.1f);
    *eye = *eyeNext;
    camera->dist = OLib_Vec3fDist(at, eye);
    camera->roll = 0;
    camera->xzSpeed = 0;
    dynamicData->unk_10 = dynamicData->unk_1C * 0.01f;
    camera->fov = Camera_LERPCeilF(dynamicData->unk_10, camera->fov, dynamicData->unk_14, 0.1f);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
    Camera_UpdateAtActorOffset(camera, &sp34->pos);
    camera->actionFuncState = 1;
    return true;
}

/**
 * Used by the unused PREREND_FIXED Camera Setting. Remnant of OoT
 */
s32 Camera_Fixed3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Fixed4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Fixed0(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * First person view
 */
s32 Camera_Subj1(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Vec3f sp90;
    Vec3f sp84;
    VecSph sp7C;
    VecSph sp74;
    VecSph tsph;
    PosRot sp58;
    f32 sp54;
    f32 temp_f0_2;
    s16 sp4E;
    s16 sp4C;
    Subj1FixedData* fixedData = CAM_GET_STATIC_DATA(Subj1);
    Subj1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Subj1);
    CameraModeValue* values;
    f32 temp_f0;
    f32 trackHeight;

    Actor_GetFocus(&sp58, camera->trackActor);
    trackHeight = Camera_GetTrackedActorHeight(camera);
    Camera_SetUpdateRatesFastPitch(camera);

    values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
    fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * trackHeight;
    fixedData->unk_04 = READ_STATIC_DATA_VAL;
    fixedData->unk_08 = READ_STATIC_DATA_VAL;
    fixedData->unk_0C = READ_STATIC_DATA_VAL;
    fixedData->unk_10 = READ_STATIC_DATA_VAL * 0.1f;
    fixedData->unk_14 = READ_STATIC_DATA_VAL * 0.1f;
    fixedData->unk_18 = READ_STATIC_DATA_VAL * 0.1f;
    fixedData->unk_1C = READ_STATIC_DATA_VAL;
    fixedData->unk_20 = READ_STATIC_DATA_VAL;

    sp7C.r = fixedData->unk_08;
    sp7C.yaw = BINANG_ROT180(sp58.rot.y);
    sp7C.pitch = sp58.rot.x;
    sp90 = sp58.pos;
    sp90.y += fixedData->unk_00;

    OLib_VecSphAddToVec3f(&sp84, &sp90, &sp7C);
    OLib_Vec3fDiffToVecSphGeo(&sp74, &camera->at, eye);
    sCameraInterfaceFlags = fixedData->unk_20;

    if (camera->globalCtx->view.unk164 == 0) {
        camera->globalCtx->view.unk164 = camera->camId | 0x50;
        return true;
    }

    if (RELOAD_PARAMS) {
        dynamicData->unk_00 = sp74.r;
        dynamicData->unk_04 = sp74.yaw;
        dynamicData->unk_06 = sp74.pitch;

        if (fixedData->unk_20 & SUBJ1_FLG_10) {
            camera->fov = fixedData->unk_1C;
            dynamicData->unk_08 = 0;
        } else {
            dynamicData->unk_08 = 6;
        }
        camera->dist = fixedData->unk_08;
        camera->rUpdateRateInv = 1.0f;
        camera->actionFuncState++;
        camera->dist = fixedData->unk_08;
    }

    tsph.r = dynamicData->unk_00;
    tsph.pitch = dynamicData->unk_04;
    tsph.yaw = dynamicData->unk_06;

    if (dynamicData->unk_08 != 0) {
        temp_f0 = (1.0f / dynamicData->unk_08);

        VEC3F_LERPIMPDST(at, at, &sp90, temp_f0);

        sp54 = ((tsph.r - sp7C.r) * (1.0f / 6.0f));
        sp4E = SUB16(tsph.pitch, sp7C.yaw) * (1.0f / 6.0f);
        sp4C = SUB16(tsph.yaw, sp7C.pitch) * (1.0f / 6.0f);

        sp74.r = Camera_LERPCeilF((dynamicData->unk_08 * sp54) + sp7C.r, sp74.r, 0.5f, 1.0f);
        sp74.yaw = Camera_LERPCeilS(sp7C.yaw + (sp4E * dynamicData->unk_08), sp74.yaw, 0.5f, 5);
        sp74.pitch = Camera_LERPCeilS(sp7C.pitch + (sp4C * dynamicData->unk_08), sp74.pitch, 0.5f, 5);

        OLib_VecSphAddToVec3f(eyeNext, at, &sp74);
        *eye = *eyeNext;
        dynamicData->unk_08--;
    } else {
        sp54 = Math_SinS(-sp58.rot.x);
        temp_f0_2 = Math_CosS(-sp58.rot.x);

        sp90.x = fixedData->unk_10;
        sp90.y = (fixedData->unk_14 * temp_f0_2) - (fixedData->unk_18 * sp54);
        sp90.z = (fixedData->unk_14 * sp54) + (fixedData->unk_18 * temp_f0_2);

        sp54 = Math_SinS(BINANG_ROT180(sp58.rot.y));
        temp_f0_2 = Math_CosS(BINANG_ROT180(sp58.rot.y));

        fixedData->unk_10 = (sp90.z * sp54) + (sp90.x * temp_f0_2);
        fixedData->unk_14 = sp90.y;
        fixedData->unk_18 = (sp90.z * temp_f0_2) - (sp90.x * sp54);

        at->x = fixedData->unk_10 + sp58.pos.x;
        at->y = fixedData->unk_14 + sp58.pos.y;
        at->z = fixedData->unk_18 + sp58.pos.z;

        sp74.r = fixedData->unk_08;
        sp74.yaw = BINANG_ROT180(sp58.rot.y);
        sp74.pitch = sp58.rot.x;

        OLib_VecSphAddToVec3f(&camera->eyeNext, at, &sp74);
        sp74.r = fixedData->unk_04;
        OLib_VecSphAddToVec3f(eye, at, &sp74);
    }

    // TODO: is skyboxDisabled accurate here?
    if (camera->globalCtx->envCtx.skyboxDisabled == 0) {
        Camera_BGCheck(camera, at, eye);
    } else {
        func_800CBFA4(camera, at, eye, 3);
    }

    camera->fov = Camera_LERPCeilF(fixedData->unk_1C, camera->fov, 0.25f, 0.1f);
    camera->roll = 0;
    camera->atLERPStepScale = 0.0f;

    return true;
}

s32 Camera_Subj2(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Subj3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Subj4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Subj0(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Data0(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Data1(Camera* camera) {
    return Camera_Normal1(camera);
}

s32 Camera_Data2(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Data3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Data4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique1(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Player diving from the surface of the water to underwater not as zora
 * Also used when using a door to leave a scene
 */
s32 Camera_Unique2(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    f32 phi_f16;
    Vec3f sp70;
    VecSph sp68;
    VecSph sp60;
    s32 pad[3];
    Unique2FixedData* fixedData = CAM_GET_STATIC_DATA(Unique2);
    Unique2DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Unique2);
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    Vec3f* eyeNext = &camera->eyeNext;
    CameraModeValue* values;

    OLib_Vec3fDiffToVecSphGeo(&sp60, at, eye);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->unk_00 = READ_SCALED_STATIC_DATA_VAL * trackHeight * (0.8f - ((68.0f / trackHeight) * -0.2f));
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->unk_08 = 0.25f;
        fixedData->unk_0C = READ_STATIC_DATA_VAL;
        fixedData->unk_10 = READ_STATIC_DATA_VAL;
    }

    sCameraInterfaceFlags = fixedData->unk_10;

    if ((camera->actionFuncState == 0) || (dynamicData->unk_04 != fixedData->unk_10)) {
        dynamicData->unk_04 = fixedData->unk_10;
    }

    if (camera->actionFuncState == 0) {
        camera->actionFuncState = 1;
        Camera_SetUpdateRatesSlow(camera);
        dynamicData->unk_00 = 200.0f;
    }

    if (fixedData->unk_10 & UNIQ2_FLG_10) {
        *eyeNext = *eye;
        Camera_UnsetFlags(camera, CAM_FLAG2_4);
    }

    sp70 = camera->trackActorPosRot.pos;

    if (fixedData->unk_10 & UNIQ2_FLG_1) {
        phi_f16 = 1.0f;
    } else {
        phi_f16 = camera->speedRatio;
    }

    at->x += ((sp70.x - at->x) * phi_f16 * 0.3f);
    at->y += (((sp70.y + trackHeight + fixedData->unk_00) - at->y) * 0.2f);
    at->z += ((sp70.z - at->z) * phi_f16 * 0.3f);

    dynamicData->unk_00 = dynamicData->unk_00 + ((2.0f - dynamicData->unk_00) * 0.05f);

    if (fixedData->unk_10 & UNIQ2_FLG_1) {
        OLib_Vec3fDiffToVecSphGeo(&sp68, at, eyeNext);
        sp68.r = fixedData->unk_04;
        OLib_VecSphAddToVec3f(&sp70, at, &sp68);
        Camera_LERPCeilVec3f(&sp70, eye, fixedData->unk_08, fixedData->unk_08, 0.2f);
    } else if (fixedData->unk_10 & UNIQ2_FLG_2) {
        if (OLib_Vec3fDistXZ(at, eyeNext) < fixedData->unk_04) {
            OLib_Vec3fDiffToVecSphGeo(&sp68, at, eyeNext);
            sp68.yaw = Camera_LERPCeilS(sp68.yaw, sp60.yaw, 0.1f, 5);
            sp68.r = fixedData->unk_04;
            sp68.pitch = 0;
            OLib_VecSphAddToVec3f(eye, at, &sp68);
            eye->y = eyeNext->y;
        } else {
            Camera_LERPCeilVec3f(eyeNext, eye, fixedData->unk_08, fixedData->unk_08, 0.2f);
        }
    }

    if (!(fixedData->unk_10 & UNIQ2_FLG_20)) {
        Camera_BGCheck(camera, at, eye);
    }

    camera->dist = OLib_Vec3fDist(at, eye);
    camera->roll = 0;
    camera->fov = Camera_LERPCeilF(fixedData->unk_0C, camera->fov, 0.2f, 0.1f);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);

    return true;
}

/**
 * Woodfall inside the Swamp, used for normal camModes and derivative modes
 */
s32 Camera_Unique3(Camera* camera) {
    s32 ret = Camera_Normal1(camera);

    if ((camera->globalCtx->sceneNum == SCENE_21MITURINMAE) && (camera->eye.y < 5.0f)) {
        camera->eye.y = 5.0f;
    }
    return ret;
}

/**
 * Woodfall inside the Swamp, used for parallel camModes and derivative modes
 */
s32 Camera_Unique4(Camera* camera) {
    s32 ret = Camera_Parallel1(camera);

    if ((camera->globalCtx->sceneNum == SCENE_21MITURINMAE) && (camera->eye.y < 5.0f)) {
        camera->eye.y = 5.0f;
    }
    return ret;
}

/**
 * Woodfall inside the Swamp, used for battle camMode
 */
s32 Camera_Unique5(Camera* camera) {
    s32 ret = Camera_Battle1(camera);

    if ((camera->globalCtx->sceneNum == SCENE_21MITURINMAE) && (camera->eye.y < 5.0f)) {
        camera->eye.y = 5.0f;
    }
    return ret;
}

/**
 * Entering a room or scene (camera settings START0/START1/START2)
 */
s32 Camera_Unique0(Camera* camera) {
    f32 playerHeight;
    PosRot* sp40 = &camera->trackActorPosRot;
    PosRot sp9C;
    Player* player;
    Vec3f sp8C;
    VecSph sp84;
    VecSph sp7C;
    SubCamData* bgCamData;
    f32 sp74;
    s32 pad;
    s16 temp_v1;
    Unique0FixedData* fixedData = CAM_GET_STATIC_DATA(Unique0);
    Unique0DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Unique0);
    CameraModeValue* values;
    Vec3f sp54;

    playerHeight = Player_GetHeight((Player*)camera->trackActor);
    player = (Player*)camera->trackActor;
    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->unk_00 = READ_STATIC_DATA_VAL;
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->unk_08 = READ_STATIC_DATA_VAL;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp7C, &camera->at, &camera->eye);
    if (player->rideActor != NULL) {
        Actor_GetWorld(&sp9C, player->rideActor);
        sp8C = sp9C.pos;
        sp8C.y += playerHeight + 20.0f;
    } else {
        sp8C = camera->trackActorPosRot.pos;
        sp8C.y += playerHeight;
    }

    sCameraInterfaceFlags = fixedData->unk_08;

    switch (camera->actionFuncState) {
        case 0:
            bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
            Camera_Vec3sToVec3f(&dynamicData->unk_1C, &bgCamData->pos);
            camera->eye = camera->eyeNext = dynamicData->unk_1C;
            dynamicData->unk_34 = bgCamData->rot;
            temp_v1 = bgCamData->fov;
            if (temp_v1 != -1) {
                if (temp_v1 <= 360) {
                    camera->fov = temp_v1;
                } else {
                    camera->fov = temp_v1 * 0.01f;
                }
            }
            dynamicData->unk_3C = bgCamData->unk_0E;
            if (dynamicData->unk_3C == -1) {
                dynamicData->unk_3C = 60;
            }

            if (bgCamData->unk_10 != -1) {
                dynamicData->unk_18 = bgCamData->unk_10 * 0.01f;
            } else {
                dynamicData->unk_18 = fixedData->unk_04 * 0.01f;
            }

            dynamicData->unk_00 = sp40->pos;
            if (fixedData->unk_08 & UNIQ0_FLG_10) {
                dynamicData->unk_0C.x = sp40->pos.x;
                dynamicData->unk_0C.y = sp40->pos.y + playerHeight + fixedData->unk_00;
                dynamicData->unk_0C.z = sp40->pos.z;
            }
            dynamicData->unk_3A = camera->trackActor->world.rot.y;
            dynamicData->unk_3E = 0;
            camera->eye = camera->eyeNext = dynamicData->unk_1C;
            Camera_UnsetFlags(camera, CAM_FLAG2_4);
            camera->actionFuncState++;
        case 1:
            sp84.r = OLib_Vec3fDist(&sp8C, &camera->eye);
            sp84.yaw = dynamicData->unk_34.y;
            sp84.pitch = -dynamicData->unk_34.x;
            OLib_VecSphGeoToVec3f(&dynamicData->unk_28, &sp84);
            func_80179A44(&dynamicData->unk_1C, sp40, &dynamicData->unk_0C);
            camera->at = dynamicData->unk_0C;

            // Time is stopped but Link & NPC animations continue
            if (player->stateFlags1 & 0x20000000) {
                dynamicData->unk_00 = sp40->pos;
            }

            if (fixedData->unk_08 & UNIQ0_FLG_10) {
                sp54.x = sp40->pos.x;
                sp54.y = sp40->pos.y + playerHeight + fixedData->unk_00;
                sp54.z = sp40->pos.z;
                Camera_LERPCeilVec3f(&sp54, &camera->at, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
                camera->yOffsetUpdateRate = Camera_LERPCeilF(dynamicData->unk_18, camera->yOffsetUpdateRate, 0.1f, 0.0001f);
                camera->xzOffsetUpdateRate = Camera_LERPCeilF(dynamicData->unk_18, camera->xzOffsetUpdateRate, 0.1f, 0.0001f);
            }

            if ((camera->actionFuncState == 999) || (camera->actionFuncState == 666)) {
                dynamicData->unk_3E = 2;
            }
            if (fixedData->unk_08 & UNIQ0_FLG_1) {
                if (dynamicData->unk_3C > 0) {
                    dynamicData->unk_3C--;
                    dynamicData->unk_00 = sp40->pos;
                    // Time is stopped but Link & NPC animations continue
                } else if ((!(player->stateFlags1 & 0x20000000)) &&
                           ((OLib_Vec3fDistXZ(&sp40->pos, &dynamicData->unk_00) >= 10.0f) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) ||
                            (fixedData->unk_08 & UNIQ0_FLG_2))) {
                    dynamicData->unk_3E = 1;
                }
            } else {
                if (dynamicData->unk_3C > 0) {
                    dynamicData->unk_3C--;
                    if (dynamicData->unk_3C == 0) {
                        sCameraInterfaceFlags = SHRINKWINVAL_NONE | IFACE_ALPHA(0);
                    }
                } else {
                    dynamicData->unk_00 = sp40->pos;
                }

                // Time is stopped but Link & NPC animations continue
                if ((player->stateFlags1 & 0x20000000) == 0) { // TODO: Merge into 1 if-statement
                    if ((dynamicData->unk_3A != camera->trackActor->world.rot.y) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || (fixedData->unk_08 & UNIQ0_FLG_2)) {
                        dynamicData->unk_3E = 1;
                    }
                }
            }
            break;

        case 3:
            sp74 = 1.0f / dynamicData->unk_3C;
            sp8C.y -= playerHeight * 0.2f;
            Camera_LERPCeilVec3f(&sp8C, &camera->at, sp74, sp74, 0.001f);
            sp84.r = OLib_Vec3fDist(&camera->at, &camera->eye);
            sp84.pitch = sp7C.pitch;
            sp84.yaw = sp7C.yaw;
            sp84.r = Camera_LERPCeilF(100.0f, sp84.r, sp74, 1.0f);
            OLib_VecSphAddToVec3f(&sp8C, &camera->at, &sp84);
            sp74 = (QREG(64) * 0.01f) + 0.2f;
            Camera_LERPCeilVec3f(&sp8C, &camera->eye, sp74, sp74, 0.001f);
            dynamicData->unk_3C--;
            if (dynamicData->unk_3C == 0) {
                dynamicData->unk_3E = 9;
            }
    }

    if ((dynamicData->unk_3E == 1) || (dynamicData->unk_3E == 2) || (dynamicData->unk_3E == 9)) {
        camera->dist = OLib_Vec3fDist(&camera->at, &camera->eye);
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
        Camera_UpdateAtActorOffset(camera, &sp40->pos);
        camera->atLERPStepScale = 0.0f;
        Camera_ChangeSettingFlags(camera, camera->prevSetting, CAM_CHANGE_SET_FLAG_2);
        Camera_SetFlags(camera, CAM_FLAG2_4);
        camera->yawUpdateRateInv = 1200.0f;
        camera->pitchUpdateRateInv = 1200.0f;
        camera->yOffsetUpdateRate = 0.001f;
        camera->xzOffsetUpdateRate = 0.001f;
        camera->fovUpdateRate = 0.01f;
    }

    return true;
}

/**
 * Does the minimal amount of camera update.
 * Allows for manual control of camera parameters without interference from update
 */
s32 Camera_Unique6(Camera* camera) {
    f32 trackHeight;
    CameraModeValue* values;
    Vec3f playerPosDisp;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    Unique6FixedData* fixedData = CAM_GET_STATIC_DATA(Unique6);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->flags = READ_STATIC_DATA_VAL;
    }

    sCameraInterfaceFlags = fixedData->flags;

    if (camera->actionFuncState == 0) {
        camera->actionFuncState++;
        Camera_SetUpdateRatesFastPitch(camera);
    }

    if (camera->trackActor != NULL) {
        trackHeight = Camera_GetTrackedActorHeight(camera);
        playerPosDisp = playerPosRot->pos;
        playerPosDisp.y += trackHeight;
        camera->dist = OLib_Vec3fDist(&playerPosDisp, &camera->eye);
        Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    } else {
        camera->dist = OLib_Vec3fDist(&camera->at, &camera->eye);
    }

    if (fixedData->flags & UNIQ6_FLG_1) {
        if (camera->unk160 > 0) {
            camera->unk160--;
        }
    }

    return true;
}

/**
 * Used by the unused PREREND_PIVOT Camera Setting. Remnant of OoT
 */
s32 Camera_Unique7(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique8(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique9(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Used by unknown settings DEMO0 and ATTENTION
 */
s32 Camera_Demo1(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* targetPosRot = &camera->targetPosRot;
    f32 temp_f0;
    Actor* sp98[1];
    s16 sp96;
    s16 sp94;
    s32 phi_v0;
    VecSph sp88;
    PosRot sp74;
    PosRot targetHead;
    Demo1FixedData* fixedData = CAM_GET_STATIC_DATA(Demo1);
    Demo1DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Demo1);
    s32 pad;

    if (camera->actionFuncState == 0) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        
        fixedData->flags = READ_STATIC_DATA_VAL;
    }

    if (camera->actionFuncState == 0) {
        dynamicData->unk_1C = 0;
        OLib_Vec3fDiffToVecSphGeo(&dynamicData->unk_0C, &camera->targetPosRot.pos, eye);
        OLib_Vec3fDiffToVecSphGeo(&dynamicData->unk_14, &camera->at, eye);
        Actor_GetFocus(&targetHead, camera->target);
        Actor_GetWorld(&sp74, camera->target);
        camera->targetPosRot.pos.x = (sp74.pos.x + targetHead.pos.x) * 0.5f;
        camera->targetPosRot.pos.y = (sp74.pos.y + targetHead.pos.y) * 0.5f;
        camera->targetPosRot.pos.z = (sp74.pos.z + targetHead.pos.z) * 0.5f;
        camera->targetPosRot.rot = targetHead.rot;
        camera->actionFuncState++;
    }

    Actor_GetScreenPos(camera->globalCtx, camera->target, &sp96, &sp94);

    temp_f0 = dynamicData->unk_0C.r;
    if ((sp96 > 20) && (sp96 < 300) && (sp94 > 40) && (sp94 < 200)) {
        if (temp_f0 < 700.0f) {
            phi_v0 = 0;
        } else {
            phi_v0 = 1;
        }
    } else if (temp_f0 < 50.0f) {
        phi_v0 = 2;
    } else if (temp_f0 < 300.0f) {
        phi_v0 = 3;
    } else if (temp_f0 < 700.0f) {
        phi_v0 = 4;
    } else {
        phi_v0 = 5;
    }

    if (camera->target->category == ACTORCAT_DOOR) {
        if ((phi_v0 > 0) && (phi_v0 < 5)) {
            phi_v0 = 6;
        } else if (phi_v0 >= 5) {
            phi_v0 = 7;
        }
    }

    if (camera->target->category == ACTORCAT_CHEST) {
        if ((phi_v0 > 1) && (phi_v0 < 5)) {
            phi_v0 = 8;
        }
    }

    switch (phi_v0) {
        Vec3f sp44;
        case 1:
            Camera_LERPCeilVec3f(&camera->targetPosRot.pos, at, 0.1f, 0.1f, 0.1f);
            OLib_Vec3fDiffToVecSphGeo(&sp88, at, eye);
            sp88.r = dynamicData->unk_0C.r;
            OLib_VecSphAddToVec3f(eyeNext, at, &sp88);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 2:
            Camera_LERPCeilVec3f(&camera->targetPosRot.pos, &camera->at, 0.1f, 0.1f, 0.1f);
            break;
        case 3:
            eyeNext = &targetPosRot->pos;
            if (dynamicData->unk_1C == 0) {
                sp98[0] = camera->target;
                func_800CC260(camera, &dynamicData->unk_00, &targetPosRot->pos, &dynamicData->unk_14, sp98, 1);
            }
            Camera_LERPCeilVec3f(eyeNext, at, 0.1f, 0.1f, 0.1f);
            eyeNext = &camera->eyeNext;
            Camera_LERPCeilVec3f(&dynamicData->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 4:
            if (dynamicData->unk_1C == 0) {
                sp98[0] = camera->target;
                dynamicData->unk_14.r = dynamicData->unk_0C.r;
                func_800CC260(camera, &dynamicData->unk_00, &targetPosRot->pos, &dynamicData->unk_14, sp98, 1);
            }
            Camera_LERPCeilVec3f(&targetPosRot->pos, at, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&dynamicData->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 5:
            eyeNext = &targetPosRot->pos;
            if (dynamicData->unk_1C == 0) {
                sp98[0] = camera->target;
                func_800CC260(camera, &dynamicData->unk_00, &targetPosRot->pos, &dynamicData->unk_0C, sp98, 1);
            }
            *at = *eyeNext;
            sp44 = dynamicData->unk_00;
            camera->eyeNext = sp44;
            *eye = sp44;
            break;
        case 6:
            if (dynamicData->unk_1C == 0) {
                dynamicData->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                dynamicData->unk_0C.r = dynamicData->unk_14.r;
                func_800CC260(camera, &dynamicData->unk_00, &targetPosRot->pos, &dynamicData->unk_0C, sp98, 1);
            }
            Camera_LERPCeilVec3f(&targetPosRot->pos, at, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&dynamicData->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 7:
            if (dynamicData->unk_1C == 0) {
                dynamicData->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                func_800CC260(camera, &dynamicData->unk_00, &targetPosRot->pos, &dynamicData->unk_0C, sp98, 1);
            }
            *at = targetPosRot->pos;
            sp44 = dynamicData->unk_00;
            camera->eyeNext = sp44;
            *eye = sp44;
            break;
        case 8:
            if (dynamicData->unk_1C == 0) {
                dynamicData->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                func_800CC260(camera, &dynamicData->unk_00, &targetPosRot->pos, &dynamicData->unk_0C, sp98, 1);
            }
            Camera_LERPCeilVec3f(&targetPosRot->pos, at, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&dynamicData->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
    }

    dynamicData->unk_1C++;
    return true;
}

// Data for opening chests (default)
VecSph D_801B9E64[] = {
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
VecSph D_801B9EB4[] = {
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

/**
 * Opening large chests.
 * The camera position will be at a fixed point, and rotate around at different intervals.
 * The direction, and initial position is dependent on when the camera was started.
 */
s32 Camera_Demo2(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    VecSph atToEye;
    VecSph eyeOffset;
    VecSph atOffset;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;
    f32 sp60;
    s32 pad;
    u8 skipUpdateEye = false;
    f32 playerHeight = Player_GetHeight((Player*)camera->trackActor);
    s16 angle;
    VecSph* sp4C = D_801B9E64;
    Vec3f* sp48 = D_801B9E84;
    Actor* trackActor = camera->trackActor;
    Demo2FixedData* fixedData = CAM_GET_STATIC_DATA(Demo2);
    Demo2DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Demo2);

    if (((trackActor == &GET_PLAYER(camera->globalCtx)->actor) &&
         (((Player*)trackActor)->transformation == PLAYER_FORM_GORON))) {
        sp4C = D_801B9EB4;
        sp48 = D_801B9ED4;
    }

    Camera_UnsetFlags(camera, CAM_FLAG2_10);
    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        fixedData->fov = READ_STATIC_DATA_VAL;
        fixedData->unk_04 = READ_STATIC_DATA_VAL;
        fixedData->flags = READ_STATIC_DATA_VAL;
    }

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);

    sCameraInterfaceFlags = fixedData->flags;

    switch (camera->actionFuncState) {
        case 0:
            Camera_UnsetFlags(camera, CAM_FLAG2_8 | CAM_FLAG2_4);
            Camera_SetUpdateRatesSlow(camera);
            camera->fov = fixedData->fov;
            camera->roll = dynamicData->animFrame = 0;
            dynamicData->initialAt = playerPosRot->pos;
            if (camera->playerFloorHeight != BGCHECK_Y_MIN) {
                dynamicData->initialAt.y = camera->playerFloorHeight;
            }
            angle = playerPosRot->rot.y;
            sp70.x = dynamicData->initialAt.x + (Math_SinS(angle) * 40.0f);
            sp70.y = dynamicData->initialAt.y + 40.0f;
            sp70.z = dynamicData->initialAt.z + (Math_CosS(angle) * 40.0f);
            if (camera->globalCtx->state.frames & 2) {
                angle -= 0x4000;
                dynamicData->yawDir = 1;
            } else {
                angle += 0x4000;
                dynamicData->yawDir = -1;
            }

            sp7C.x = sp70.x + (sp4C[1].r * Math_SinS(angle));
            sp7C.y = dynamicData->initialAt.y + 5.0f;
            sp7C.z = sp70.z + (sp4C[1].r * Math_CosS(angle));
            if (Camera_BGCheck(camera, &sp70, &sp7C)) {
                dynamicData->yawDir = -dynamicData->yawDir;
            }

            OLib_Vec3fToVecSphGeo(&atOffset, &sp48[0]);
            atOffset.yaw += playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &dynamicData->initialAt, &atOffset);

            eyeOffset.r = sp4C[0].r;
            eyeOffset.pitch = sp4C[0].pitch;
            eyeOffset.yaw = (sp4C[0].yaw * dynamicData->yawDir) + playerPosRot->rot.y;

            dynamicData->unk_0C = 1.0f;
            break;
        case 1:
            // This is the case taken for nearly the entire cutscene
            sp60 = (dynamicData->animFrame - 2) * (1.0f / 146.0f);

            VEC3F_LERPIMPDST(&sp64, &sp48[0], &sp48[1], sp60);

            OLib_Vec3fToVecSphGeo(&atOffset, &sp64);
            atOffset.yaw = (atOffset.yaw * dynamicData->yawDir) + playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &dynamicData->initialAt, &atOffset);

            atOffset.r = LERPIMP(sp4C[0].r, sp4C[1].r, sp60);
            atOffset.pitch = BINANG_LERPIMP(sp4C[0].pitch, sp4C[1].pitch, sp60);
            atOffset.yaw = BINANG_LERPIMP(sp4C[0].yaw, sp4C[1].yaw, sp60);

            eyeOffset.r = atOffset.r;
            eyeOffset.pitch = atOffset.pitch;
            eyeOffset.yaw = (atOffset.yaw * dynamicData->yawDir) + playerPosRot->rot.y;

            dynamicData->unk_0C -= (1.0f / 365.0f);
            break;
        case 2:
            sp60 = (dynamicData->animFrame - 148) * 0.1f;

            sp64.x = LERPIMP(sp48[1].x, sp48[2].x, sp60);
            sp64.y = LERPIMP((sp48[1].y - playerHeight), sp48[2].y, sp60);
            sp64.y += playerHeight;
            sp64.z = LERPIMP(sp48[1].z, sp48[2].z, sp60);

            OLib_Vec3fToVecSphGeo(&atOffset, &sp64);
            atOffset.yaw = (atOffset.yaw * dynamicData->yawDir) + playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &dynamicData->initialAt, &atOffset);

            atOffset.r = LERPIMP(sp4C[1].r, sp4C[2].r, sp60);
            atOffset.pitch = BINANG_LERPIMP(sp4C[1].pitch, sp4C[2].pitch, sp60);
            atOffset.yaw = BINANG_LERPIMP(sp4C[1].yaw, sp4C[2].yaw, sp60);

            eyeOffset.r = atOffset.r;
            eyeOffset.pitch = atOffset.pitch;
            eyeOffset.yaw = (atOffset.yaw * dynamicData->yawDir) + playerPosRot->rot.y;

            dynamicData->unk_0C -= 0.04f;
            break;
        case 3:
            sp60 = (dynamicData->animFrame - 159) * (1.0f / 9.0f);

            sp64.x = LERPIMP(sp48[2].x, sp48[3].x, sp60);
            sp64.y = LERPIMP(sp48[2].y, sp48[3].y, sp60);
            sp64.y += playerHeight;
            sp64.z = LERPIMP(sp48[2].z, sp48[3].z, sp60);

            OLib_Vec3fToVecSphGeo(&atOffset, &sp64);
            atOffset.yaw = (atOffset.yaw * dynamicData->yawDir) + playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &dynamicData->initialAt, &atOffset);

            atOffset.r = LERPIMP(sp4C[2].r, sp4C[3].r, sp60);
            atOffset.pitch = BINANG_LERPIMP(sp4C[2].pitch, sp4C[3].pitch, sp60);
            atOffset.yaw = BINANG_LERPIMP(sp4C[2].yaw, sp4C[3].yaw, sp60);

            eyeOffset.r = atOffset.r;
            eyeOffset.pitch = atOffset.pitch;
            eyeOffset.yaw = (atOffset.yaw * dynamicData->yawDir) + playerPosRot->rot.y;

            dynamicData->unk_0C += (4.0f / 45.0f);
            break;
        case 30:
            Camera_SetFlags(camera, CAM_FLAG2_400);
            if (camera->flags2 & CAM_FLAG2_8) {
                camera->actionFuncState = 4;
            }
        case 10:
        case 20:
            // Taken on the 1st and 158th animation frame
            skipUpdateEye = true;
            break;
        case 4:
            eyeOffset.r = 80.0f;
            eyeOffset.pitch = 0;
            eyeOffset.yaw = atToEye.yaw;
            dynamicData->unk_0C = 0.1f;
            sCameraInterfaceFlags = SHRINKWINVAL_LARGE | IFACE_ALPHA(4);

            if (!(((dynamicData->animFrame < 0) || (camera->xzSpeed > 0.001f) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R)) &&
                  (camera->flags2 & CAM_FLAG2_8))) {
                goto skipeyeUpdate;
            }
        default:
            Camera_SetFlags(camera, CAM_FLAG2_10 | CAM_FLAG2_4);
            Camera_UnsetFlags(camera, CAM_FLAG2_8);
            func_800CC938(camera);
            sCameraInterfaceFlags = SHRINKWINVAL_NONE | IFACE_ALPHA(0);
        skipeyeUpdate:
            skipUpdateEye = true;
            break;
    }

    dynamicData->animFrame++;

    /**
     * Opening a large chest only lasts 135 frames
     * 
     * So for one frame, the actionFuncState is set to 10, 
     * allowing the static data to be loaded into the subCamera mini-heap
     * 
     * For the remainder of the cutscene, actionFuncState is set to 1
     */
    if (dynamicData->animFrame == 1) {
        camera->actionFuncState = 10;
    } else if (dynamicData->animFrame == 2) {
        camera->actionFuncState = 1;
    } else if (dynamicData->animFrame == 148) {
        camera->actionFuncState = 2;
    } else if (dynamicData->animFrame == 158) {
        camera->actionFuncState = 20;
    } else if (dynamicData->animFrame == 159) {
        camera->actionFuncState = 3;
    } else if (dynamicData->animFrame == 168) {
        camera->actionFuncState = 30;
    } else if (dynamicData->animFrame == 228) {
        camera->actionFuncState = 4;
    }

    if (!skipUpdateEye) {
        eyeOffset.r = Camera_LERPCeilF(eyeOffset.r, atToEye.r, dynamicData->unk_0C, 1.0f);
        eyeOffset.pitch = Camera_LERPCeilS(eyeOffset.pitch, atToEye.pitch, dynamicData->unk_0C, 5);
        eyeOffset.yaw = Camera_LERPCeilS(eyeOffset.yaw, atToEye.yaw, dynamicData->unk_0C, 5);
        OLib_VecSphAddToVec3f(eyeNext, at, &eyeOffset);
        *eye = *eyeNext;
    }

    camera->dist = OLib_Vec3fDist(at, eye);
    camera->atLERPStepScale = 0.1f;
    Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    return true;
}

/**
 * Taking the warp pad from the start of a dungeon to the boss-room
 */
s32 Camera_Demo3(Camera* camera) {
    s32 pad2;
    f32 temp;
    CameraModeValue* values;
    VecSph atToEye;
    PosRot playerHead;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Demo3FixedData* fixedData = CAM_GET_STATIC_DATA(Demo3);
    Demo3DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Demo3);

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);
    Actor_GetFocus(&playerHead, camera->trackActor);
    playerHead.pos.x = camera->trackActorPosRot.pos.x;
    playerHead.pos.z = camera->trackActorPosRot.pos.z;
    playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.4f;
    Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->flags = READ_STATIC_DATA_VAL;
        camera->actionFuncState = 0;
    }

    sCameraInterfaceFlags = fixedData->flags;

    switch (camera->actionFuncState) {
        case 0:
            // Init Data
            camera->actionFuncState++;
            dynamicData->timer = 125;
            Distortion_SetType(8);
            Distortion_SetCountdown(60);
            break;
        case 1:
            // Zoom into player, start to rise
            temp = 1.0f / dynamicData->timer;
            atToEye.r = Camera_LERPCeilF(140.0f, atToEye.r, temp, 0.1f);
            dynamicData->timer--;
            camera->fov = Camera_LERPCeilF(50.0f, camera->fov, 0.1f, 0.1f);
            if (dynamicData->timer <= 0) {
                dynamicData->timer = 20;
                camera->actionFuncState++;
                Distortion_SetType(0x10);
                Distortion_SetCountdown(80);
            }
            break;
        case 2:
            // continue rising
            dynamicData->timer--;
            if (dynamicData->timer <= 0) {
                dynamicData->unk_04 = 120;
                dynamicData->timer = 0;
                dynamicData->unk_00 = (175.0f - camera->fov) / dynamicData->unk_04;
                camera->actionFuncState++;
                Distortion_SetType(0x400);
                Distortion_SetCountdown(15);
            }
            break;
        case 3:
            dynamicData->timer++;
            camera->fov += dynamicData->unk_00 * dynamicData->timer;
            if (dynamicData->timer >= 15) {
                Distortion_ClearType(0x400);
                Distortion_ClearType(0x10);
                Distortion_ClearType(8);
                camera->actionFuncState++;
            }
            break;
    }

    OLib_VecSphAddToVec3f(eyeNext, at, &atToEye);
    *eye = *eyeNext;
    return true;
}

/**
 * Mask Transformation Cutscene 0:
 * starting as a human and transforming into anything else
 */
s32 Camera_Demo4(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    VecSph atToEye;
    CameraModeValue* values;
    PosRot playerHead;
    f32 sp58;
    f32 sin;
    Demo4FixedData* fixedData = CAM_GET_STATIC_DATA(Demo4);
    Demo4DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Demo4);
    s32 pad[2];

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->flags = READ_STATIC_DATA_VAL;
        camera->actionFuncState = 0;
        dynamicData->unk_00 = *at;
        dynamicData->unk_18 = atToEye;
        dynamicData->unk_14 = camera->fov;
    }

    Actor_GetFocus(&playerHead, camera->trackActor);
    sCameraInterfaceFlags = fixedData->flags;

    switch (camera->actionFuncState) {
        if (1) {}
        case 0:
            camera->actionFuncState++;
            dynamicData->unk_22 = 0;
            if (!(atToEye.r < 40.0f)) {
                atToEye.r = 40.0f;
            }
            camera->fov = 80.0f;
            dynamicData->unk_10 = (Rand_ZeroOne() - 0.5f) * 40.0f;
        case 1:
            // Camera fixed on human player as the mask moves from the pocket to the face
            // Camera rolls left and right
            if (dynamicData->unk_22 >= 12) {
                dynamicData->unk_0C = (dynamicData->unk_22 - 12) * 10.384615f;
                sin = sin_rad(dynamicData->unk_0C * (M_PI / 180));
                dynamicData->unk_0C = ((dynamicData->unk_10 < 0.0f) ? -1.0f : 1.0f) * sin;
                if (dynamicData->unk_22 == 12) {
                    Distortion_SetType(0x200);
                    Distortion_SetCountdown(26);
                }
            } else {
                dynamicData->unk_0C = 0.0f;
            }
            sp58 = dynamicData->unk_22 * (6.0f / 19.0f);
            dynamicData->unk_20 = playerPosRot->rot.y + 0x4000;
            playerHead.pos.x = (Math_SinS(dynamicData->unk_20) * sp58 * dynamicData->unk_0C) + playerPosRot->pos.x;
            playerHead.pos.z = (Math_CosS(dynamicData->unk_20) * sp58 * dynamicData->unk_0C) + playerPosRot->pos.z;
            playerHead.pos.y -= (playerHead.pos.y - playerPosRot->pos.y) * 0.099999994f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.2f, 0.2f, 0.1f);

            sp58 = (dynamicData->unk_22 * (30.0f / 19.0f));
            camera->roll = DEGF_TO_BINANG(sp58 * dynamicData->unk_0C);

            sp58 = 1.0f / (38 - dynamicData->unk_22);
            dynamicData->unk_22++;
            atToEye.r = Camera_LERPCeilF(30.0f, atToEye.r, sp58, 0.1f);
            atToEye.pitch = 0;
            if (dynamicData->unk_22 >= 38) {
                dynamicData->unk_22 = 24;
                camera->actionFuncState++;
                dynamicData->unk_0C = (32.0f - camera->fov) / 24.0f;
                Distortion_SetType(0x800);
            }
            break;
        case 2:
            // Camera steadies as human player is fully croutched down and hiding face
            if (dynamicData->unk_22 == 24) {
                at->x = (Math_SinS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.x;
                at->y = playerHead.pos.y - ((playerHead.pos.y - playerPosRot->pos.y) * 0.1f);
                at->z = (Math_CosS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.z;
            } else {
                playerHead.pos.x = (Math_SinS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.x;
                playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
                playerHead.pos.z = (Math_CosS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.z;
                Camera_LERPCeilVec3f(&playerHead.pos, at, 0.25f, 0.25f, 0.1f);
            }
            if (dynamicData->unk_22 > 0) {
                camera->fov += dynamicData->unk_0C;
            }
            dynamicData->unk_22--;
            atToEye.r = 35.0f;
            atToEye.pitch = 0x2000;
            camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
            if (dynamicData->unk_22 <= 0) {
                dynamicData->unk_20 = 630;
                dynamicData->unk_22 = 0;
                dynamicData->unk_0C = (60.0f - camera->fov) / dynamicData->unk_20;
                camera->actionFuncState = 3;
            }
            break;
        case 3:
            // Camera zooms into human players face with buldging eyes
            playerHead.pos.x = playerPosRot->pos.x;
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
            playerHead.pos.z = playerPosRot->pos.z;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.25f, 0.25f, 0.1f);
            camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
            dynamicData->unk_22++;
            camera->fov += dynamicData->unk_0C * dynamicData->unk_22;
            atToEye.pitch = 0x2000;
            atToEye.r = 35.0f;
            if (dynamicData->unk_22 >= 35) {
                Distortion_ClearType(0x200);
                Distortion_ClearType(0x800);
                camera->actionFuncState = 4;
            }
            break;
        case 999:
            Actor_GetFocus(&playerHead, camera->trackActor);
            Distortion_ClearType(0x200);
            Distortion_ClearType(0x800);
            camera->actionFuncState = 4;
            break;
        case 4:
            // Camera backs up as player is now in a transformed state
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);
            atToEye = dynamicData->unk_18;
            camera->fov = dynamicData->unk_14;
            camera->roll = 0;
            break;
    }

    OLib_VecSphAddToVec3f(&camera->eyeNext, at, &atToEye);
    *eye = camera->eyeNext;
    return true;
}

/**
 * Mask Transformation Cutscene 1:
 * starting as non-human/fierce diety and transforming into anything else
 */
s32 Camera_Demo5(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    VecSph atToEye;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    PosRot playerHead;
    f32 new_var;
    f32 sp58;
    f32 sin;
    Demo5FixedData* fixedData = CAM_GET_STATIC_DATA(Demo5);
    Demo5DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Demo5);
    CameraModeValue* values;


    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixedData->flags = READ_STATIC_DATA_VAL;
        camera->actionFuncState = 0;
        dynamicData->unk_00 = *at;
        dynamicData->unk_1C = atToEye;
        dynamicData->unk_18 = camera->fov;
    }

    Actor_GetFocus(&playerHead, camera->trackActor);

    sCameraInterfaceFlags = fixedData->flags;

    switch (camera->actionFuncState) {
        case 0:
            camera->actionFuncState++;
            atToEye.pitch = 0;
            dynamicData->timer = 0x12;
            dynamicData->unk_14 = 80.0f;
            atToEye.r = 30.0f;
            camera->fov = 80.0f;
            dynamicData->unk_10 = (Rand_ZeroOne() - 0.5f) * 40.0f;
            camera->roll = 0;
            playerHead.pos.x = playerPosRot->pos.x;
            playerHead.pos.z = playerPosRot->pos.z;
            *at = playerHead.pos;
        case 1:
            // Camera remains still as player moves hands to face
            dynamicData->timer--;
            if (dynamicData->timer <= 0) {
                dynamicData->timer = 0;
                camera->actionFuncState = 2;
                dynamicData->unk_24 = camera->trackActorPosRot.rot.y + 0x4000;
                dynamicData->timer = 46;
                Distortion_SetType(0x200);
                Distortion_SetCountdown(46);
            }
            break;
        case 2:
            // Camera zooms out while rolling back and forth
            dynamicData->unk_0C = dynamicData->timer * (180.0f / 23.0f);
            sp58 = dynamicData->unk_0C * (M_PI / 180);
            sin = sin_rad(sp58);
            dynamicData->unk_0C = ((dynamicData->unk_10 < 0.0f) ? -1.0f : 1.0f) * sin;
            new_var = (0x2E - dynamicData->timer) * (5.0f / 46.0f);
            playerHead.pos.x = (Math_SinS(dynamicData->unk_24) * new_var * dynamicData->unk_0C) + playerPosRot->pos.x;
            playerHead.pos.z = (Math_CosS(dynamicData->unk_24) * new_var * dynamicData->unk_0C) + playerPosRot->pos.z;
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.2f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);
            new_var = (dynamicData->timer * (10.0f / 23.0f));
            camera->roll = DEGF_TO_BINANG(dynamicData->unk_0C * new_var);
            new_var = 1.0f / dynamicData->timer;
            atToEye.r = Camera_LERPCeilF(dynamicData->unk_14, atToEye.r, new_var, 0.1f);
            dynamicData->timer--;
            atToEye.pitch = 0;
            if (dynamicData->timer <= 0) {
                camera->actionFuncState = 3;
                Distortion_ClearType(0x200);
            }
            break;
        case 999:
            Actor_GetFocus(&playerHead, camera->trackActor);
            camera->actionFuncState = 3;
            Distortion_ClearType(0x200);
            break;
        case 3:
            // Player is in new form
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);
            camera->roll = 0;
            atToEye = dynamicData->unk_1C;
            camera->fov = dynamicData->unk_18;
            break;
    }

    OLib_VecSphAddToVec3f(eyeNext, at, &atToEye);
    *eye = *eyeNext;
    return true;
}

s32 Camera_Demo6(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Demo7(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Demo8(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Demo9(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Smoothly and gradually return camera to Player after a cutscene
 * Used for global actorCsId = 0x7E (Connect Camera Setting)
 */
s32 Camera_Demo0(Camera* camera) {
    s32 pad;
    f32 temp_f0_2;
    s16 phi_v1;
    Camera* subCam = &camera->globalCtx->subCameras[2];
    Vec3f* mainEye = &camera->eye;
    Vec3f* subEye = &subCam->eye;
    Vec3f* at = &camera->at;
    Demo0FixedData* fixedData = CAM_GET_STATIC_DATA(Demo0);
    Demo0DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Demo0);

    if (camera->actionFuncState == 0) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        fixedData->unk_00 = READ_STATIC_DATA_VAL;
    }

    if (camera->actionFuncState == 0) {
        OLib_Vec3fDiffToVecSphGeo(&dynamicData->unk_04, &subCam->at, subEye);
        OLib_Vec3fDiffToVecSphGeo(&dynamicData->unk_0C, &camera->at, mainEye);
        if (dynamicData->unk_04.r < 50.0f) {
            dynamicData->unk_04.r = 50.0f;
            if (dynamicData->unk_04.pitch < 0x7D0) { // 11 degrees
                dynamicData->unk_04.pitch = 0x7D0;
            }
        }

        dynamicData->unk_00 = OLib_Vec3fDist(mainEye, subEye);
        if (dynamicData->unk_00 < 300.0f) {
            dynamicData->unk_1A = 0;
        } else {
            dynamicData->unk_1A = sqrtf(dynamicData->unk_00 - 200.0f);
        }

        dynamicData->unk_14 = subCam->inputDir.x - camera->inputDir.x;
        if (dynamicData->unk_14 >= 0) {
            phi_v1 = dynamicData->unk_14;
        } else {
            phi_v1 = -dynamicData->unk_14;
        }

        if (phi_v1 > 10000) {
            phi_v1 /= 1000;
            if (dynamicData->unk_1A < phi_v1) {
                dynamicData->unk_1A = phi_v1;
            }
        }

        dynamicData->unk_16 = subCam->inputDir.y - camera->inputDir.y;
        if (dynamicData->unk_16 >= 0) {
            phi_v1 = dynamicData->unk_16;
        } else {
            phi_v1 = -dynamicData->unk_16;
        }

        if (phi_v1 > 10000) {
            phi_v1 /= 1000;
            if (dynamicData->unk_1A < phi_v1) {
                dynamicData->unk_1A = phi_v1;
            }
        }

        dynamicData->unk_18 = subCam->inputDir.z - camera->inputDir.z;
        if (dynamicData->unk_18 >= 0) {
            phi_v1 = dynamicData->unk_18;
        } else {
            phi_v1 = -dynamicData->unk_18;
        }

        if (phi_v1 > 10000) {
            phi_v1 /= 1000;
            if (dynamicData->unk_1A < phi_v1) {
                dynamicData->unk_1A = phi_v1;
            }
        }

        if (dynamicData->unk_1A != 0) {
            dynamicData->unk_00 = (dynamicData->unk_04.r - dynamicData->unk_0C.r) / dynamicData->unk_1A;
            dynamicData->unk_14 = (s16)(dynamicData->unk_04.pitch - dynamicData->unk_0C.pitch) / dynamicData->unk_1A;
            dynamicData->unk_16 = (s16)(dynamicData->unk_04.yaw - dynamicData->unk_0C.yaw) / dynamicData->unk_1A;
            dynamicData->unk_18 = (s16)(subCam->roll - camera->roll) / dynamicData->unk_1A;
        }
        camera->actionFuncState++;
    }

    if (dynamicData->unk_1A != 0) {
        temp_f0_2 = dynamicData->unk_1A;
        at->x += (subCam->at.x - camera->at.x) / temp_f0_2;
        at->y += (subCam->at.y - camera->at.y) / temp_f0_2;
        at->z += (subCam->at.z - camera->at.z) / temp_f0_2;
        dynamicData->unk_0C.r = dynamicData->unk_0C.r + dynamicData->unk_00;
        dynamicData->unk_0C.pitch = dynamicData->unk_0C.pitch + dynamicData->unk_14;
        dynamicData->unk_0C.yaw = dynamicData->unk_0C.yaw + dynamicData->unk_16;
        camera->roll += dynamicData->unk_18;
        OLib_VecSphAddToVec3f(mainEye, at, &dynamicData->unk_0C);
        camera->eyeNext = *mainEye;
        dynamicData->unk_1A--;
    }

    if (dynamicData->unk_1A == 0) {
        ActorCutscene_Stop(0x7E);
    }

    return true;
}

s32 Camera_Special0(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special1(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special2(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special4(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Flying with hookshot
 */
s32 Camera_Special5(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot spA8;
    s16 pad1;
    s16 spA4;
    CamColChk sp7C;
    VecSph sp74;
    VecSph sp6C;
    VecSph atToEye;
    VecSph atToEyeNext;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    Special5FixedData* fixedData = CAM_GET_STATIC_DATA(Special5);
    Special5DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Special5);
    f32 rand;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        f32 yNormal = (0.8f - ((68.0f / trackHeight) * -0.2f));

        fixedData->yOffset = (READ_SCALED_STATIC_DATA_VAL * trackHeight) * yNormal;
        fixedData->eyeDist = READ_STATIC_DATA_VAL;
        fixedData->minDistForRot = READ_STATIC_DATA_VAL;
        fixedData->pitch = DEGF_TO_BINANG(READ_STATIC_DATA_VAL);
        fixedData->fovTarget = READ_STATIC_DATA_VAL;
        fixedData->atMaxLERPScale = READ_SCALED_STATIC_DATA_VAL;
        fixedData->timerInit = READ_STATIC_DATA_VAL;
        fixedData->flags = READ_STATIC_DATA_VAL;
    }

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&atToEyeNext, at, eyeNext);
    Actor_GetWorld(&spA8, camera->target);

    sCameraInterfaceFlags = fixedData->flags;

    if (camera->actionFuncState == 0) {
        camera->actionFuncState++;
        dynamicData->animTimer = fixedData->timerInit;
    }

    if (dynamicData->animTimer > 0) {
        dynamicData->animTimer--;
    } else if (dynamicData->animTimer == 0) {
        if ((camera->target == NULL) || (camera->target->update == NULL)) {
            camera->target = NULL;
            return true;
        }

        dynamicData->animTimer--;
        if (fixedData->minDistForRot < OLib_Vec3fDist(&spA8.pos, &playerPosRot->pos)) {
            sp6C.yaw = playerPosRot->rot.y;
            sp6C.pitch = -playerPosRot->rot.x;
            sp6C.r = 20.0f;
            OLib_VecSphAddToVec3f(&sp7C.pos, &spA8.pos, &sp6C);
            func_800CBC84(camera, at, &sp7C, 0);
            OLib_Vec3fToVecSphGeo(&sp6C, &sp7C.norm);
            spA4 = SUB16(playerPosRot->rot.y, sp6C.yaw);
            sp74.r = fixedData->eyeDist;
            rand = Rand_ZeroOne();
            sp74.yaw = BINANG_ROT180(playerPosRot->rot.y) +
                       (s16)(spA4 < 0 ? -(s16)(0x1553 + (s16)(rand * 2730.0f)) : (s16)(0x1553 + (s16)(rand * 2730.0f)));
            sp74.pitch = fixedData->pitch;
            OLib_VecSphAddToVec3f(eyeNext, &spA8.pos, &sp74);
            *eye = *eyeNext;
            Camera_BGCheck(camera, &spA8.pos, eye);
        }
    }

    Camera_CalcAtDefault(camera, &atToEyeNext, fixedData->yOffset, 0);
    camera->fov = Camera_LERPCeilF(fixedData->fovTarget, camera->fov, camera->atLERPStepScale * 0.05f, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, fixedData->atMaxLERPScale);
    return true;
}

s32 Camera_Special6(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special7(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Exiting a spiral staircase cutscene.
 * Camera remains fixed at given position, and tracks player for the duration of the cutscene
 */
s32 Camera_Special8(Camera* camera) {
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    Vec3f atTarget;
    Vec3f posOffsetTarget;
    f32 yNormal;
    f32 trackHeight = Camera_GetTrackedActorHeight(camera);
    DoorParams* doorParams = CAM_GET_DOOR_PARAMS(Special8);
    Special8FixedData* fixedData = CAM_GET_STATIC_DATA(Special8);
    Special8DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Special8);
    s32 pad[2];

    Camera_UnsetFlags(camera, CAM_FLAG2_10);
    yNormal = (0.8f - ((68.0f / trackHeight) * -0.2f));

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        // Initialize data
        fixedData->yOffset = READ_SCALED_STATIC_DATA_VAL * trackHeight * yNormal;
        fixedData->eyeStepScale = READ_SCALED_STATIC_DATA_VAL;
        fixedData->posStepScale = READ_SCALED_STATIC_DATA_VAL;
        fixedData->fov = READ_STATIC_DATA_VAL;
        fixedData->spiralDoorCsLength = READ_STATIC_DATA_VAL * 5;
        fixedData->flags = READ_STATIC_DATA_VAL;
        dynamicData->fov = fixedData->fov * 100.0f;
        dynamicData->spiralDoorCsFrame = 0;
        Camera_UnsetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
        dynamicData->eye.x = doorParams->eye.x;
        dynamicData->eye.y = doorParams->eye.y;
        dynamicData->eye.z = doorParams->eye.z;
    }

    // Check if cutscene is still playing
    if (dynamicData->spiralDoorCsFrame < fixedData->spiralDoorCsLength) {
        dynamicData->spiralDoorCsFrame++;
        sCameraInterfaceFlags = fixedData->flags;
        posOffsetTarget.x = 0.0f;
        posOffsetTarget.y = fixedData->yOffset + trackHeight;
        posOffsetTarget.z = 0.0f;
        Camera_LERPCeilVec3f(&posOffsetTarget, &camera->atActorOffset, fixedData->posStepScale, fixedData->posStepScale,
                             0.1f);

        // Camera follows player as they exit the stairwell
        atTarget.x = playerPosRot->pos.x + camera->atActorOffset.x;
        atTarget.y = playerPosRot->pos.y + camera->atActorOffset.y;
        atTarget.z = playerPosRot->pos.z + camera->atActorOffset.z;
        if (camera->actionFuncState == 0) {
            camera->actionFuncState++;
            if (!(fixedData->flags & SPEC8_FLG_1)) {
                camera->eyeNext = dynamicData->eye;
                camera->at = atTarget;
            }
        }

        // Update at to look at player
        Camera_LERPCeilVec3f(&atTarget, at, fixedData->posStepScale, fixedData->posStepScale, 10.0f);
        
        // Move camera position &dynamicData->eye and remain there for the entire cutscen
        Camera_LERPCeilVec3f(&dynamicData->eye, eyeNext, fixedData->eyeStepScale, fixedData->eyeStepScale, 0.1f);
        camera->eye = *eyeNext;
        camera->dist = OLib_Vec3fDist(at, &camera->eye);
        camera->roll = 0;
        camera->xzSpeed = 0.0f;
        camera->fov = SCALED_STATIC_DATA(dynamicData->fov);
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
        Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    } else {
        // Cutscene is finished
        Camera_SetFlags(camera, CAM_FLAG2_400 | CAM_FLAG2_10);
        sCameraInterfaceFlags = SHRINKWINVAL_NONE | IFACE_ALPHA(0);

        // Wait for user input to move to the next camera action function
        if ((camera->xzSpeed > 0.001f) || CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || (fixedData->flags & SPEC8_FLG_8)) {
            func_800CC938(camera);
            Camera_SetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
            Camera_UnsetFlags(camera, CAM_FLAG2_400);
        }
    }
    return true;
}

/**
 * Entering and exiting a door between rooms (eg. sliding doors)
 * Camera closely follows player on both the front and the back room
 */
s32 Camera_Special9(Camera* camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    s32 rand1;
    Vec3f spB8;
    VecSph spB0;
    VecSph spA8;
    f32 trackHeight;
    s32 phi_v1_2;
    s16 actorCsId;
    f32 sp34;
    PosRot sp84;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* sp40 = &camera->trackActorPosRot;
    DoorParams* doorParams = CAM_GET_DOOR_PARAMS(Special9);
    Special9FixedData* fixedData = CAM_GET_STATIC_DATA(Special9);
    Special9DynamicData* dynamicData = CAM_GET_DYNAMIC_DATA(Special9);
    s32 sp50[1];
    SubCamData* bgCamData;

    trackHeight = Camera_GetTrackedActorHeight(camera);
    actorCsId = ActorCutscene_GetCurrentIndex();

    if ((actorCsId != -1) && (actorCsId != 0x7D)) {
        func_800E0348(camera);
    }

    Camera_UnsetFlags(camera, CAM_FLAG2_10);
    sp34 = 0.8f - ((68.0f / trackHeight) * -0.2f);

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        fixedData->yOffset = READ_SCALED_STATIC_DATA_VAL * trackHeight * sp34;
        fixedData->fov = READ_STATIC_DATA_VAL;
        fixedData->flags = READ_STATIC_DATA_VAL;
    }

    if (doorParams->doorActor != NULL) {
        Actor_GetWorldPosShapeRot(&sp84, doorParams->doorActor);
    } else {
        sp84 = *sp40;
        sp84.pos.y += trackHeight + fixedData->yOffset;
        sp84.rot.x = 0;
    }

    OLib_Vec3fDiffToVecSphGeo(&spA8, at, eye);

    sCameraInterfaceFlags = fixedData->flags;

    switch (camera->actionFuncState) {
        case 0:
            // Init
            Camera_UnsetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
            camera->actionFuncState++;
            if (ABS((s16)(sp40->rot.y - sp84.rot.y)) > 0x4000) {
                dynamicData->unk_00 = BINANG_ROT180(sp84.rot.y);
            } else {
                dynamicData->unk_00 = sp84.rot.y;
            }
        case 1:
            // Camera is fixed in front of the door
            doorParams->timer1--;
            if (doorParams->timer1 <= 0) {
                camera->actionFuncState++;
                
                // Setup for the camera moving behind the door
                if (fixedData->flags & SPEC9_FLG_1) {
                    bgCamData = (SubCamData*)Camera_GetCamDataVec3s(camera, camera->bgCamDataId);
                    Camera_Vec3sToVec3f(eyeNext, &bgCamData->pos);
                    spB8 = *eye = *eyeNext;
                } else {
                    s16 camEyeSide;
                    s16 randFloat;

                    spB0.pitch = ((s16)(Rand_ZeroOne() * 640.0f) + 0xBB8);
                    randFloat = ((s16)(Rand_ZeroOne() * 1230.0f) + 0x5DC);

                    // The camera will either position itself either to the left or to the right 
                    // of the door when it jumps behind it. It's effectively 50/50 percent chance
                    camEyeSide = (s16)(randFloat * ((camera->globalCtx->state.frames % 2) ? 1 : -1));

                    spB0.yaw = dynamicData->unk_00 + camEyeSide;
                    spB0.r = 200.0f * sp34;
                    OLib_VecSphAddToVec3f(eyeNext, at, &spB0);
                    spB8 = *eye = *eyeNext;

                    // If the side chosen moves the camera out-of-bounds, move to the other side
                    if (Camera_CheckOOB(camera, &spB8, &sp40->pos)) {
                        camEyeSide = (s16)-camEyeSide;
                        spB0.yaw = dynamicData->unk_00 + camEyeSide;
                        OLib_VecSphAddToVec3f(eyeNext, at, &spB0);
                        *eye = *eyeNext;
                    }
                }
            } else {
                break;
            }
        case 2:
            // Camera is behind the door looking at player
            spB8 = sp40->pos;
            spB8.y += trackHeight + fixedData->yOffset;
            // Update camera at to follow the player
            Camera_LERPCeilVec3f(&spB8, at, 0.25f, 0.25f, 0.1f);

            doorParams->timer2--;
            if (doorParams->timer2 <= 0) {
                // Setup for the camera turning around to look in front of player
                camera->actionFuncState++;
                dynamicData->unk_00 = BINANG_ROT180(dynamicData->unk_00);
            } else {
                break;
            }
        case 3:
            // Camera turns around to look in front of player
            spB8 = sp40->pos;
            spB8.y += trackHeight + fixedData->yOffset;
            Camera_LERPCeilVec3f(&spB8, at, 0.5f, 0.5f, 0.1f);
            spB0.pitch = Camera_LERPCeilS(0xAAA, spA8.pitch, 0.3f, 5);
            spB0.yaw = Camera_LERPCeilS(dynamicData->unk_00, spA8.yaw, 0.3f, 5);
            spB0.r = Camera_LERPCeilF(60.0f, spA8.r, 0.3f, 1.0f);
            OLib_VecSphAddToVec3f(eyeNext, at, &spB0);
            
            *eye = *eyeNext;

            doorParams->timer3--;
            if (doorParams->timer3 <= 0) {
                camera->actionFuncState++;
            } else {
                break;
            }
        case 4:
            camera->actionFuncState++;
        case 999:
        default:
            // Door is closed and is waiting for user input to toggle to a new setting
            Camera_SetFlags(camera, CAM_FLAG2_400 | CAM_FLAG2_10);
            sCameraInterfaceFlags = SHRINKWINVAL_NONE | IFACE_ALPHA(0);

            if ((camera->xzSpeed > 0.001f) || CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || (fixedData->flags & SPEC9_FLG_8)) {

                func_800CC938(camera);
                Camera_SetFlags(camera, CAM_FLAG2_4 | CAM_FLAG2_2);
                Camera_UnsetFlags(camera, CAM_FLAG2_400);
            }
            break;
    }

    spB8 = sp40->pos;
    spB8.y += trackHeight;
    camera->dist = OLib_Vec3fDist(&spB8, eye);
    Camera_UpdateAtActorOffset(camera, &sp40->pos);
    return true;
}

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

    if ((camera->camId == CAM_ID_MAIN) &&
        (camera->trackActor == &GET_PLAYER(camera->globalCtx)->actor) &&
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
                (!(camera->flags2 & CAM_FLAG2_200) || Camera_IsUnderwaterAsZora(camera)) && !(camera->flags2 & (s16)CAM_FLAG2_8000) &&
                !Camera_IsMountedOnHorse(camera) && !Camera_IsWearingGiantsMask(camera) && !Camera_IsDekuHovering(camera) && (sp98 != 0)) {

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
                ((Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerFloorHeight) < 11.0f) || (changeCamSceneDataType != 0)) &&
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
