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

#include "z_camera_data.c"

// UnkStruct_D801ED920* D_801ED920;
GlobalContext* D_801EDC28;
SwingAnimation D_801EDC30[4];
static Vec3f D_801EDDD0;
static Vec3f D_801EDDE0;
static Vec3f D_801EDDF0;

/*===============================================================*/
/*                    Camera Private Functions                   */
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
    return sqrtf(SQXYZ(vec));
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
    Actor* actor = (Actor*)camera->trackActor;
    f32 trackActorHeight;

    if (actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        trackActorHeight = Player_GetHeight((Player*)actor);
    } else {
        Actor_GetFocus(&actorFocus, actor);
        trackActorHeight = actorFocus.pos.y - camera->trackActorPosRot.pos.y;
        if (trackActorHeight == 0.0f) {
            trackActorHeight = 10.0f;
        }
    }
    return trackActorHeight;
}

f32 func_800CB780(Camera* camera) {
    Actor* trackActor = camera->trackActor;
    f32 ret;

    if (trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        ret = func_800B7090((Player*)trackActor);
    } else {
        ret = 10.0f;
    }

    return ret;
}

s32 func_800CB7CC(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags3 & 0x10;
    } else {
        return 0;
    }
}

s32 func_800CB7F8(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags1 & 0x800000;
    } else {
        return 0;
    }
}

s32 func_800CB828(Camera* camera) {
    Actor* trackActor = (Actor*)camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags3 & 0x2000;
    } else {
        return 0;
    }
}

s32 func_800CB854(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags1 & 0x20;
    } else {
        return 0;
    }
}

// related to player swimming (player->stateFlags1 & 0x8000000) is player swimming
s32 func_800CB880(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        if (((Player*)trackActor)->stateFlags3 & 0x8000) {
            return 999;
        } else {
            return ((Player*)trackActor)->stateFlags1 & 0x8000000;
        }
    } else {
        return 0;
    }
}

s32 func_800CB8C8(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags2 & 0x800;
    } else {
        return 0;
    }
}

s32 Camera_IsPlayerFormZora(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->transformation == PLAYER_FORM_ZORA;
    } else {
        return false;
    }
}

s32 func_800CB924(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags3 & 0x1000;
    } else {
        return 0;
    }
}

s32 func_800CB950(Camera* camera) {
    Actor* trackActor;
    s32 phi_v0;
    s32 ret;
    f32 new_var;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        new_var = Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerGroundY);

        phi_v0 = false;
        if (new_var < 11.0f) {
            phi_v0 = true;
        }

        ret = phi_v0;

        if (!ret) {

            ret = false;
            if (((Actor*)camera->trackActor)->gravity > -0.1f) {
                ret = true;
            }

            trackActor = camera->trackActor;
            if (!ret) {
                ret = ((Player*)trackActor)->stateFlags1 & 0x200000;
                ret = !!ret;
            }
        }
        return ret;
    } else {
        return true;
    }
}

s32 func_800CBA08(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if (trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags1 & 4;
    } else {
        return 0;
    }
}

s32 func_800CBA34(Camera* camera) {
    Actor* trackActor = camera->trackActor;
    s32 ret;

    if (trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        ret = !!(((Player*)trackActor)->stateFlags1 & 0x1000);
        if (!ret) {
            ret = !!(((Player*)trackActor)->stateFlags3 & 0x100);
        }
        return ret;
    } else {
        return false;
    }
}

s32 func_800CBA7C(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags2 & 0x800000;
    } else {
        return 0;
    }
}

s32 func_800CBAAC(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->swordState;
    } else {
        return 0;
    }
}

s32 func_800CBAD4(Vec3f* dst, Camera* camera) {
    PosRot sp24;
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        *dst = ((Player*)trackActor)->bodyPartsPos[0];
        return dst;
    } else {
        Actor_GetWorldPosShapeRot(&sp24, (Actor*)camera->trackActor);
        *dst = sp24.pos;
        return dst;
    }
}

s32 func_800CBB58(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->currentBoots == 5;
    } else {
        return 0;
    }
}

s32 func_800CBB88(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        if ((((Player*)trackActor)->swordState != 0) && (((Player*)trackActor)->swordAnimation == 26)) {
            return 3;
        }
        if ((((Player*)trackActor)->stateFlags2 & 0x20000) || ((((Player*)trackActor)->swordState != 0) && (((Player*)trackActor)->swordAnimation == 29))) {
            return 1;
        }
    }

    return 0;
}

s32 func_800CBC00(Camera* camera) {
    Actor* trackActor = camera->trackActor;

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return ((Player*)trackActor)->stateFlags1 & 0x200000;
    } else {
        return 0;
    }
}

s32 func_800CBC30(Camera* camera, f32 arg1, f32 arg2) {
    if ((camera->playerGroundY != camera->waterYPos) && (camera->waterYPos < arg1) && (camera->waterYPos > arg2)) {
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

    if (!func_800C54AC(colCtx, from, &toPoint, &toNewPos, floorPoly, (arg3 & 1) ? 0 : 1, 1,
                                 (arg3 & 2) ? 0 : 1, -1, &floorBgId)) {
        toNewPos = to->pos;
        if (1) {}
        if (1) {}
        toNewPos.y += 5.0f;
        if ((arg3 != 0) && func_800CB7CC(camera)) {
            to->poly = ((Actor*)camera->trackActor)->floorPoly;
            floorBgId = ((Actor*)camera->trackActor)->floorBgId;
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
            floorPolyY = func_800C4488(colCtx, floorPoly, &floorBgId, &toNewPos);
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

    if (func_800C54AC(&camera->globalCtx->colCtx, from, &to->pos, &toNewPos, &to->poly, 1, 1, 1, -1,
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

    if (func_800C54AC(colCtx, from, to, &intersect, &poly, 1, 1, 1, -1, &bgId)) {
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
    if ((func_800C54AC(colCtx, from, to, &intersect, &poly, 1, 1, 1, 0, &bgId)) &&
        (func_800C01B8(poly, from) < 0.0f)) {
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
    Player* player = (Player*)camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first;
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
    f32 floorY = func_800C40B4(colCtx, &floorPoly, bgId, chkPos);

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
        floorY = func_800C41E4(camera->globalCtx, &camera->globalCtx->colCtx, &floorPoly, bgId,
                               (Actor*)camera->trackActor, pos);
    } else {
        floorY = func_800C4488(colCtx, &floorPoly, bgId, pos);
    }

    if ((floorY == BGCHECK_Y_MIN) ||
        ((camera->playerGroundY < floorY) && !(COLPOLY_GET_NORMAL(floorPoly->normal.y) > 0.5f))) {
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

// TODO: bgCamDataId?
/**
 * Returns the CameraSettingType of the camera at index `bgCamDataId`
 */
s16 Camera_GetCamDataSetting(Camera* camera, u32 bgCamDataId) {
    if (bgCamDataId & 0x1000) {
        return func_800C9728(&camera->globalCtx->colCtx, bgCamDataId & ~0x1000, BGCHECK_SCENE);
    } else {
        return func_80169C64(camera->globalCtx, bgCamDataId);
    }
}

/**
 * Returns the scene camera info of the camera at index `bgCamDataId`
 */
Vec3s* Camera_GetSurfaceBgCamData(Camera* camera, u32 bgCamDataId) {
    if (bgCamDataId & 0x1000) {
        return func_800C98CC(&camera->globalCtx->colCtx, bgCamDataId & ~0x1000, BGCHECK_SCENE);
    } else {
        return func_80169C84(camera->globalCtx, bgCamDataId);
    }
}

/**
 * Gets the scene's camera index for the poly `poly`, returns -1 if
 * there is no camera data for that poly.
 */
s32 Camera_GetDataIdxForPoly(Camera* camera, s32* bgId, CollisionPoly* poly) {
    s32 bgCamDataId = func_800C9704(&camera->globalCtx->colCtx, poly, *bgId);
    s32 ret;

    if (func_800C9728(&camera->globalCtx->colCtx, bgCamDataId, *bgId) == 0) { // == CAM_SET_NONE
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

    Actor_GetWorldPosShapeRot(&playerPosShape, (Actor*)camera->trackActor);
    *waterY = playerPosShape.pos.y;

    // WaterBox_GetSurfaceImpl
    if (!func_800C9EBC(camera->globalCtx, &camera->globalCtx->colCtx, playerPosShape.pos.x, playerPosShape.pos.z,
                       waterY, &waterBox, &sp30)) {
        // player's position is not in a waterbox
        *waterY = playerPosShape.pos.y;
        return -1;
    }

    if (!func_800CB880(camera)) {
        // player is not swimming
        return -1;
    }

    // WaterBox_GetCameraSType
    camSetting = func_800CA648(&camera->globalCtx->colCtx, waterBox, sp30);

    // -2: no camera data idx
    return (camSetting == CAM_SET_NONE) ? -2 : camSetting;
}

void func_800CC938(Camera* camera) {
    func_800DDFE0(camera);
}

/**
 * Calculates the angle between points `from` and `to`
 */
s16 Camera_XZAngle(Vec3f* to, Vec3f* from) {
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
    f32 trackActorHeight = Camera_GetTrackedActorHeight(camera);

    temp_f2 = (trackActorHeight * 1.2f);
    sp2C = trackActorHeight * 2.5f;
    sp30 = trackActorHeight;
    playerPos.x = camera->trackActorPosRot.pos.x;
    playerPos.y = camera->playerGroundY + temp_f2;
    playerPos.z = camera->trackActorPosRot.pos.z;
    rotatedPos.x = (trackActorHeight * sinYaw) + playerPos.x;
    rotatedPos.y = playerPos.y;
    rotatedPos.z = (trackActorHeight * cosYaw) + playerPos.z;

    if (arg2 || ((camera->globalCtx->state.frames % 2) == 0)) {
        D_801EDC00.pos.x = playerPos.x + (sp2C * sinYaw);
        D_801EDC00.pos.y = playerPos.y;
        D_801EDC00.pos.z =
            playerPos.z + (sp2C * cosYaw); // TODO: D_801EDC04 may be D_801EDC00 or D_801EDC04.x = D_801EDC04.y
        Camera_BGCheckInfo(camera, &playerPos, &D_801EDC00);
        if (arg2) {
            D_801EDBF4 = D_801EDBF8 = camera->playerGroundY;
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
            D_801EDBF4 = camera->playerGroundY;
        }

        if (D_801EDBF8 == BGCHECK_Y_MIN) {
            D_801EDBF8 = D_801EDBF4;
        }
    }

    phi_f16 = (D_801EDBF4 - camera->playerGroundY) * 0.8f;
    phi_f18 = (D_801EDBF8 - camera->playerGroundY) * 0.19999999f;
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
    f32 trackActorHeight = Camera_GetTrackedActorHeight(camera);
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
    sp7C.y = sp5C.pos.y + trackActorHeight;
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

void Camera_ResetAnim(Camera* camera, s32 mode) {
    camera->animState = 0;
}

void Camera_UpdateInterface(s32 flags) {
    s32 interfaceAlpha;

    if ((flags & SHRINKWIN_MASK) != SHRINKWIN_MASK) {
        switch (flags & SHRINKWINVAL_MASK) {
            case 0x1000:
                sCameraShrinkWindowVal = 0x1A;
                break;
            case 0x2000:
                sCameraShrinkWindowVal = 0x1B;
                break;
            case 0x3000:
                sCameraShrinkWindowVal = 0x20;
                break;
            default:
                sCameraShrinkWindowVal = 0;
                break;
        }

        if (flags & SHRINKWIN_CURVAL) {
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

Vec3f* Camera_BGCheckCorner(Vec3f* dst, Vec3f* linePointA, Vec3f* linePointB, CamColChk* pointAColChk,
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

// TODO: D_801AECF0 as Vec2f matchecd, but real data type is unknown
// Note: D_801AECF0 size is unknown but OoT arrays indexed by actor->targetMode are size 10
f32 func_800CD6CC(Actor* actor) {
    return sqrtf(D_801AECF0[actor->targetMode].x / D_801AECF0[actor->targetMode].y);
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
    f32 trackActorHeight = Camera_GetTrackedActorHeight(camera);

    posOffsetTarget.x = 0.0f;
    posOffsetTarget.y = trackActorHeight + yOffset;
    posOffsetTarget.z = 0.0f;

    if (calcSlope) {
        posOffsetTarget.y -= OLib_ClampMaxDist(
            Camera_CalcSlopeYAdj(&camera->floorNorm, playerPosRot->rot.y, eyeAtDir->yaw, 25.0f), trackActorHeight);
    }

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->atActorOffset, camera->xzOffsetUpdateRate,
                         camera->yOffsetUpdateRate, 0.1f);

    atTarget.x = playerPosRot->pos.x + camera->atActorOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->atActorOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->atActorOffset.z;

    if (atTarget.y < (camera->playerGroundY + 10.0f)) {
        atTarget.y = camera->playerGroundY + 10.0f;
    }

    Camera_LERPCeilVec3f(&atTarget, at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return true;
}

s32 func_800CD834(Camera* camera, VecSph* eyeAtDir, f32 yOffset, f32* arg3, f32 arg4) {
    f32 deltaY;
    Vec3f posOffsetTarget;
    Vec3f atTarget; // 4C
    Vec3f* new_var;
    f32 temp_f2; // 44
    f32 temp_f0;
    s16 phi_v1;           // 3E-playerPosRot.rot.y
    s16 temp_v0;          // 3C-playerPosRot.rot.x
    PosRot* playerPosRot; // 30

    posOffsetTarget.y = yOffset + Camera_GetTrackedActorHeight(camera);
    posOffsetTarget.x = 0.0f;
    posOffsetTarget.z = 0.0f;

    func_800B8898(camera->globalCtx, (Actor*)camera->trackActor, &phi_v1, &temp_v0);
    temp_v0 -= 0x78;

    phi_v1 = ABS(temp_v0);
    playerPosRot = &camera->trackActorPosRot;

    OLib_ClampMaxDist(phi_v1 / 120.0f, 1.0f); // Should have an output

    deltaY = playerPosRot->pos.y - *arg3;
    temp_f2 = OLib_ClampMaxDist(deltaY, arg4);

    if (phi_v1 > 0x3C) {
        phi_v1 = 0x3C;
        if (camera) {}
    }

    temp_f0 = OLib_ClampMaxDist(phi_v1 / 60.0f, 1.0f);
    posOffsetTarget.y -= temp_f2 * temp_f0 * temp_f0;

    Camera_LERPCeilVec3f(((void)0, &posOffsetTarget), &camera->atActorOffset, camera->xzOffsetUpdateRate,
                         camera->yOffsetUpdateRate, 0.1f);
    atTarget.x = playerPosRot->pos.x + camera->atActorOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->atActorOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->atActorOffset.z;
    atTarget.y = CLAMP_MIN(atTarget.y, camera->playerGroundY + 10.0f);

    Camera_LERPCeilVec3f(&atTarget, &camera->at, camera->atLERPStepScale, camera->atLERPStepScale, 0.1f);
    return true;
}

s32 func_800CDA14(Camera* camera, VecSph* arg1, f32 yOffset, f32 arg3) {
    PosRot* temp_s1 = &camera->trackActorPosRot;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 atLERPStepScale;
    f32 trackActorHeight = Camera_GetTrackedActorHeight(camera);

    sp50.x = Math_SinS(temp_s1->rot.y) * arg3;
    sp50.z = Math_CosS(temp_s1->rot.y) * arg3;
    sp50.y = trackActorHeight + yOffset;
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
    f32 trackActorHeight = Camera_GetTrackedActorHeight(camera);
    VecSph sp44;
    Vec3f* at = &camera->at;

    if (arg5 & 0x40) {
        sp44.r = func_800CCCEC(camera, arg5 & 0x10);
        sp44.yaw = trackActorPosRot->rot.y + 0x4000;
        sp44.pitch = 0;
        OLib_VecSphGeoToVec3f(&sp70, &sp44);
    } else {
        temp_f0 = camera->atActorOffset.x + camera->playerPosDelta.x;
        temp_f12 = camera->atActorOffset.z + camera->playerPosDelta.z;
        if (sqrtf(SQ(temp_f0) + SQ(temp_f12)) < arg3) {
            sp70.x = temp_f0;
            sp70.z = temp_f12;
        } else {
            sp70.x = camera->atActorOffset.x;
            sp70.z = camera->atActorOffset.z;
        }
        sp58 = temp_f0; // TODO: Needed to match?
    }

    sp70.y = trackActorHeight + yOffset;

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
    f32 trackActorHeight = Camera_GetTrackedActorHeight(camera);
    f32 sp50;
    PosRot* trackActorPosRot = &camera->trackActorPosRot;

    sp80.x = 0.0f;
    sp80.y = trackActorHeight + yOffset;
    sp80.z = 0.0f;

    if (PREG(76) && (flags & FLG_ADJSLOPE)) {
        sp80.y -= Camera_CalcSlopeYAdj(&camera->floorNorm, camera->trackActorPosRot.rot.y, eyeAtDir->yaw, 25.0f);
    }

    sp74 = trackActorPosRot->pos;
    sp74.y += trackActorHeight;

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
    f32 playerHeight = Camera_GetTrackedActorHeight(camera);
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
    posOffsetTarget.y = playerHeight + yOffset;
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
 * The pitch target starts with a default value on a flat surface, then standing on a sloped surface will create an offset in default pitch
 * Camera "AI" for pitch
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
        t = pitchMag * (1.0f / 0x38A4);  // ratio of pitch to 79.7 degrees
        attenuation = Camera_QuadraticAttenuation(0.8f, 1.0f - t); // attenuation starts above pitch = 0xB54 (16 degrees)
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
s16 Camera_CalcDefaultYaw(Camera* camera, s16 yaw, s16 target, f32 attenuationYawDiffRange, f32 attenuationYawDiffInterpParam) {
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
    attenuationYawDiffAdj = F32_LERPIMP(attenuationYawDiff, 1.0f, attenuationYawDiffInterpParam);
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
            Math3D_AngleBetweenVectors(&camera->playerPosDelta, &swing->eyeAtColChk.norm, &sp88);
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
            Camera_BGCheckCorner(&swing->collisionClosePoint, &camera->at, &camera->eyeNext, &swing->atEyeColChk,
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
s32 Camera_Normal1(Camera *camera) {
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
    CollisionPoly *sp60;
    f32 sp88 = Camera_GetTrackedActorHeight(camera);
    s32 sp5C; //BgID
    f32 sp58;
    f32 phi_f2;
    // Vec3f *sp48;
    // Vec3f *sp44;

    // f32 phi_f0;
    f32 phi_f2_2;
    f32 phi_f0_4;
    s32 phi_v1_2;
    Vec3f *sp4C = &camera->eye;
    PosRot* sp40 = &camera->trackActorPosRot;
    // f32 phi_f16_5;


    s16 phi_a0;
    s16 temp_a0_3; // May be fake
    Vec3f* new_var3;

    Normal1* norm1 = (Normal1*)camera->paramData;
    Normal1Anim* anim = &norm1->anim; // sp34(sp3C)

    // sp48 = &camera->at;
    // sp4C;/
    // sp44 = &camera->eyeNext;
    // sp40;
    // sp88;

    
    values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
    norm1->unk_00 = NEXTSETTING * (sp88 * 0.01f * (0.8f - ((68.0f / sp88) * -0.2f)));
    norm1->unk_04 = NEXTSETTING * (sp88 * 0.01f * (0.8f - ((68.0f / sp88) * -0.2f)));
    norm1->unk_08 = NEXTSETTING * (sp88 * 0.01f * (0.8f - ((68.0f / sp88) * -0.2f)));
    norm1->unk_04 = norm1->unk_08 - (norm1->unk_08 - norm1->unk_04);

    if (RELOAD_PARAMS) {
        norm1->unk_20 = (s16)((NEXTSETTING * 182.04167f) + .5f);
        norm1->unk_0C = NEXTSETTING;
        norm1->unk_0C = 40.0f - (40.0f - norm1->unk_0C);
        norm1->unk_10 = NEXTSETTING;
        norm1->unk_14 = NEXTSETTING * 0.01f;
        norm1->unk_14 = 1.0f - (1.0f - norm1->unk_14);
        norm1->unk_18 = NEXTSETTING;
        norm1->unk_1C = NEXTSETTING * 0.01f;
        norm1->unk_22 = NEXTSETTING;
    }

    sCameraInterfaceFlags = norm1->unk_22;
    OLib_Vec3fDiffToVecSphGeo(&spA4, &camera->at, sp4C);
    OLib_Vec3fDiffToVecSphGeo(&sp9C, &camera->at, &camera->eyeNext);

    switch (camera->animState) {
        case 20:
            Camera_SetUpdateRatesFastYaw(camera);;
        case 0:
            anim->unk_0C = 1;
            if (!(norm1->unk_22 & 8) && (camera->animState != 20)) {
                anim->unk_0C |= 0x1000;
            }
        case 10:
            if (camera->animState == 0xA) {
                anim->unk_0C = 0;
            }
            anim->unk_08 = 0;
            D_801EDC30[camera->camId].yaw = D_801EDC30[camera->camId].pitch = D_801EDC30[camera->camId].unk_64 = 0;
            anim->unk_0A = 0x514;
            D_801EDC30[camera->camId].swingUpdateRate = norm1->unk_0C;
            anim->unk_00 = camera->trackActorPosRot.pos.y;
            anim->unk_04 = camera->xzSpeed;
            D_801EDC30[camera->camId].unk_66 = 0;
            sUpdateCameraDirection = false;
            anim->unk_10 = 120.0f;
    }

    camera->animState = 1;
    sUpdateCameraDirection = true;

    if ((camera->speedRatio < 0.01f) || (anim->unk_0A > 0x4B0)) {
        if (anim->unk_0A > -0x4B0) {
            anim->unk_0A--;
        }
    } else {
        anim->unk_0A = 0x4B0;
    }

    if (func_800CB950(camera)) {
        anim->unk_00 = camera->trackActorPosRot.pos.y;
    }

    if (anim->unk_0C & 0x1000) {
        spC8 = camera->speedRatio;
    } else {
        spC8 = ((camera->speedRatio * 3.0f) + 1.0f) * 0.25f;
    }
    
    spD8 = camera->atActorOffset;
    spD8.y -= sp88 + norm1->unk_00;
    spC4 = Camera_Vec3fMagnitude(&spD8);

    if ((norm1->unk_04 + norm1->unk_08) < spC4) {
        spC4 = 1.0f;
    } else {
        spC4 = spC4 / (norm1->unk_04 + norm1->unk_08);
    }

    // Everything above matches except stack pointers
    // PERM_RANDOMIZE(

    phi_f16_2 = 0.2f;
    
    phi_f2 = (camera->xzSpeed - anim->unk_04) * 0.2f;
    phi_f0_4 = phi_f2;
    if (phi_f2 < 0.0f) {
        phi_f0_4 = 0.0f;
    } 

    spC0 = OLib_ClampMaxDist(SQ(phi_f0_4), 1.0f);
    camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, (0.5f * spC8) + (0.5f * spC4), 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, (0.5f * spC8) + (0.5f * spC4), 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, (0.5f * spC8) + (0.5f * spC4), 0.0001f);
    
    if (D_801EDC30[camera->camId].unk_64 == 1) {
        phi_f2 = 0.5f;
    } else {
        phi_f2 = (0.5f * spC8) + (0.5f * spC4);
    }

    anim->unk_04 = camera->xzSpeed;

    if (D_801EDC30[camera->camId].unk_66 != 0) {
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + D_801EDC30[camera->camId].swingUpdateRate, camera->yawUpdateRateInv, phi_f2, 0.1f);
        if (norm1->unk_22 & 8) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(100.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else {
            camera->pitchUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + 16.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        }
        D_801EDC30[camera->camId].unk_66--;
    } else {
        camera->yawUpdateRateInv = Camera_LERPCeilF(D_801EDC30[camera->camId].swingUpdateRate - (D_801EDC30[camera->camId].swingUpdateRate * 0.7f * spC0), camera->yawUpdateRateInv, phi_f2, 0.1f);
        if ((norm1->unk_22 & 8) && (camera->speedRatio > 0.01f)) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(100.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else if (D_801ED920 != NULL) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(32.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        }
    }

    if (norm1->unk_22 & 1) {
        if (!spC8) {}
        temp_a0_3 = func_800CC9C0(camera, spA4.yaw + 0x8000, anim->unk_0C & 1);
        phi_f2 = (1.0f / norm1->unk_10) * 0.7f;
        phi_f16_2 = (1.0f / norm1->unk_10) * 0.3f * (1.0f - camera->speedRatio);
        spD0 = phi_f16_2;
        anim->unk_08 = Camera_LERPCeilS(temp_a0_3, anim->unk_08, phi_f2 + phi_f16_2, 5);
    } else {
        anim->unk_08 = 0;
    }

    if ((D_801EDC30[camera->camId].unk_64 == 1) && (norm1->unk_00 > -40.0f)) {
        phi_f0_4 = Math_SinS(D_801EDC30[camera->camId].pitch);
        phi_f2 = norm1->unk_00;
        phi_f2 = phi_f2 * (1.0f - phi_f0_4); // TODO: phi_f2 should not be on the LHS and RHS
        // phi_f2 = norm1->unk_00 * (1.0f - phi_f0_4);
        camera->yawUpdateRateInv = 80.0f;
        camera->pitchUpdateRateInv = 80.0f;
        phi_f2_2 = ((-40.0f) * phi_f0_4) + phi_f2;
        phi_f16_2 = phi_f0_4;
    } else {
        phi_f2_2 = norm1->unk_00;
    }

    if (norm1->unk_22 & 0x60) {
        if (camera->dist < norm1->unk_04) {
            phi_f16_2 = 0.0f;
        } else if (norm1->unk_08 < camera->dist) {
            phi_f16_2 = 1.0f;
        } else if (norm1->unk_08 == norm1->unk_04) {
            phi_f16_2 = 1.0f;
        } else {
            // phi_f16_2 = camera->dist - norm1->unk_04;
            spD4 = (camera->dist - norm1->unk_04) / (norm1->unk_08 - norm1->unk_04);
            phi_f16_2 = spD4;
        }
        
        func_800CDA14(camera, &sp9C, phi_f2_2, 25.0f * phi_f16_2 * camera->speedRatio);
        anim->unk_10 = 120.0f;
        spD0 = phi_f16_2;
    } else if ((norm1->unk_22 & 0x80) && (anim->unk_0A < 0)) {
        phi_f0_4 = anim->unk_0A / -1200.0f; // May be used to swap $f registers
        func_800CDA14(camera, &sp9C, phi_f2_2 - ((phi_f2_2 - ((0.8f - ((68.0f / sp88) * -0.2f)) * sp88 * -0.45f)) * phi_f0_4 * 0.75f), 10.0f * phi_f0_4);
        anim->unk_10 = 120.0f;
        spD0 = phi_f16_2;
        if (0) { }
    } else if (norm1->unk_22 & 8) {
        spD0 = phi_f16_2;
        func_800CD834(camera, &sp9C, norm1->unk_00, &anim->unk_00, anim->unk_10);
        if (anim->unk_10 > 20.0f) {
            anim->unk_10 -= 0.2f;
        }
    } else {
        spD0 = phi_f16_2;
        Camera_CalcAtDefault(camera, &sp9C, phi_f2_2, norm1->unk_22 & 1);
        anim->unk_10 = 120.0f;
    }

    phi_f16_2 = spD0;
    OLib_Vec3fDiffToVecSphGeo(&spB4, &camera->at, &camera->eyeNext);
    if ((norm1->unk_22 & 0x80) && (anim->unk_0A < 0)) {
        if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
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
                    phi_f16_2 = norm1->unk_04;
                    break;
                default:
                    phi_f16_2 = norm1->unk_04;
                    break;
            } 
        }
        phi_f0_4 = Camera_ClampDist2(camera, spB4.r, phi_f16_2, phi_f16_2, 0);
    } else if (norm1->unk_22 & 0x80) {
        phi_f0_4 = Camera_ClampDist2(camera, spB4.r, norm1->unk_04, norm1->unk_08, 1);
    } else {
        phi_f0_4 = Camera_ClampDist1(camera, spB4.r, norm1->unk_04, norm1->unk_08, anim->unk_0A > 0);
    }

    camera->dist = spB4.r = phi_f0_4;

    if (D_801EDC30[camera->camId].unk_64 != 0) {
        if (phi_v1_2) {} 
        spB4.pitch = Camera_LERPCeilS(D_801EDC30[camera->camId].pitch, sp9C.pitch, 1.0f / camera->yawUpdateRateInv, 5);
        spB4.yaw = Camera_LERPCeilS(D_801EDC30[camera->camId].yaw, sp9C.yaw, 1.0f / camera->yawUpdateRateInv, 5);
    } else {
        if (norm1->unk_22 & 0x20) {
            spB4.yaw = sp9C.yaw;
            spB4.pitch = sp9C.pitch;
            camera->animState = 0x14;
        } else {
            if (D_801ED920 != NULL) {
                if (sp40) {}
                new_var3 = &D_801ED920->unk_24;
                OLib_Vec3fDiffToVecSphGeo(&sp74, &sp40->pos, new_var3); // TODO: arg0 & arg1 swapped
                sp72 = sp40->rot.y - sp74.yaw;
                if ((norm1->unk_22 & 0xFF00) == 0xFF00) {
                    sp6C = 1.0f;
                } else {
                    sp6C = 1.0f - (ABS(sp72) / 10922.0f);
                }

                if (ABS((s16)(sp9C.yaw - sp74.yaw)) < 0x4000) {
                    sp74.yaw += 0x8000;
                }

                if (!(norm1->unk_22 & 8) || !func_800CB924(camera)) {
                    spB4.yaw = Camera_CalcDefaultYaw(camera, sp9C.yaw, (s16)(sp40->rot.y - (s16)(sp72 * sp6C)), norm1->unk_14, spC0);
                }

                if (!(norm1->unk_22 & 8) || (camera->speedRatio < 0.01f)) {
                    spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, norm1->unk_20 + (s16)((norm1->unk_20 - sp74.pitch) * sp6C * 0.75f), anim->unk_08);
                }
                dummy:; // TODO: Will this be needed?
            } else if (norm1->unk_22 & 2) {
                if ((camera->speedRatio > 0.1f) || (anim->unk_0A > 0x4B0)) {
                    OLib_Vec3fToVecSphGeo(&sp64, &camera->playerPosDelta);
                    if (!(norm1->unk_22 & 8) || !func_800CB924(camera)) {
                        spB4.yaw = Camera_CalcDefaultYaw(camera, sp9C.yaw, sp64.yaw, norm1->unk_14, spC0);
                    }
                    if (!(norm1->unk_22 & 8)) {
                        spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, norm1->unk_20, anim->unk_08);
                    } else if ((camera->playerPosDelta.y > 0.0f) && func_800CB924(camera)) {
                        spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, norm1->unk_20, anim->unk_08);
                    }
                } else {
                    spB4.yaw = sp9C.yaw;
                    spB4.pitch = sp9C.pitch;
                    dummy4:; // TODO: Will this be needed?
                }
            } else {
                spB4.yaw = Camera_CalcDefaultYaw(camera, sp9C.yaw, sp40->rot.y, norm1->unk_14, spC0);
                if (!(norm1->unk_22 & 8) || (camera->speedRatio < 0.1f)) {
                    spB4.pitch = Camera_CalcDefaultPitch(camera, sp9C.pitch, norm1->unk_20, anim->unk_08);
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
    if ((camera->status == CAM_STATUS_ACTIVE) && !(norm1->unk_22 & 0x10) && (spC4 <= 0.9f)) {
        
        if (func_800CBA7C(camera) == 0) {
            func_800CED90(camera, &spB4, &sp9C, norm1->unk_04, norm1->unk_0C, &D_801EDC30[camera->camId], &anim->unk_0C);
            sp58 = func_800C4488(&camera->globalCtx->colCtx, &sp60, &sp5C, sp4C);
            if ((norm1->unk_22 & 8) &&  func_800CB924(camera)) {
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
            } else if ((camera->waterYPos != camera->playerGroundY) && ((spD0 - camera->waterYPos) < 5.0f) && ((spD0 - camera->waterYPos) > -5.0f)) {
                sp4C->y = camera->waterYPos + 5.0f;
            }
        }

        OLib_Vec3fDiffToVecSphGeo(&spAC, sp4C, &camera->at);
        camera->inputDir.x = spAC.pitch;
        camera->inputDir.y = spAC.yaw;
        camera->inputDir.z = 0;
        if (gSaveContext.health < 17) {
            phi_v1_2 = (camera->globalCtx->state.frames << 0x18);
            phi_v1_2 = (s16) ((phi_v1_2 >> 0x15) & 0xFD68);
            camera->inputDir.y += phi_v1_2;
        }
    } else {
        D_801EDC30[camera->camId].swingUpdateRate = norm1->unk_0C;
        D_801EDC30[camera->camId].unk_64 = 0;
        sUpdateCameraDirection = false;
        *sp4C = camera->eyeNext;
    }

    // Everything below OLib_Vec3fDiffToVecSphGeo matches except stack pointers
    // )

    phi_f2 = (gSaveContext.health <= 16) ? 0.8f : 1.0f;
    camera->fov = Camera_LERPCeilF(norm1->unk_18 * phi_f2, camera->fov, camera->fovUpdateRate, 0.1f);

    if (norm1->unk_22 & 4) {
        spD4 = Math_SinS((s16)(spA4.yaw - spB4.yaw));
        camera->roll = Camera_LERPCeilS(((Rand_ZeroOne() - 0.5f) * 500.0f * camera->speedRatio) + (spD4 * spD4 * spD4 * 10000.0f), camera->roll, 0.1f, 5);
    } else {
        if (gSaveContext.health <= 16) {
            phi_a0 = (Rand_ZeroOne() - 0.5f) * 100.0f * camera->speedRatio;
        } else {
            phi_a0 = 0.0f;
        }
        camera->roll = Camera_LERPCeilS(phi_a0, camera->roll, 0.2f, 5);
    }
    
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, norm1->unk_1C);
    anim->unk_0C &= ~1;
    return true;


}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal1.s")
#endif


s32 Camera_Normal2(Camera* camera) {
    return Camera_Noop(camera);
}

/**
 * Riding Epona
 */
s32 Camera_Normal3(Camera *camera) {
    Normal3* norm3 = (Normal3*)camera->paramData;
    Normal3Anim* anim = &norm3->anim;
    f32 sp8C;
    f32 sp90;
    f32 temp_f2;
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
        Camera_ChangeSettingFlags(camera, camera->prevSetting, 0x2);
        return true;
    }

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        temp_f2 = PCT(temp_f2);

        norm3->yOffset = NEXTSETTING * temp_f2;
        norm3->distMin = NEXTSETTING * temp_f2;
        norm3->distMax = NEXTSETTING * temp_f2;
        norm3->pitchTarget = DEGF_TO_BINANG(NEXTSETTING);
        norm3->yawUpdateRateInv = NEXTSETTING;
        norm3->pitchUpdateRateInv = NEXTSETTING;
        norm3->fovTarget = NEXTSETTING;
        norm3->maxAtLERPScale = NEXTPCT;
        norm3->interfaceFlags = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp70, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&sp68, at, eyeNext);
    sUpdateCameraDirection = true;
    sCameraInterfaceFlags = norm3->interfaceFlags;

    phi_v1_2 = camera->animState;
    if (!(((phi_v1_2 == 0) || (phi_v1_2 == 10)) || (phi_v1_2 == 20))) {
    } else {
        anim->isZero = 0;
        anim->curPitch = 0;
        anim->yPosOffset = camera->playerGroundY;

        D_801EDC30[camera->camId].yaw = D_801EDC30[camera->camId].pitch = D_801EDC30[camera->camId].unk_64 = 0;
        D_801EDC30[camera->camId].swingUpdateRate = norm3->yawUpdateRateInv;
        anim->yawUpdateRate = SUB16(BINANG_ROT180(camera->trackActorPosRot.rot.y), sp70.yaw) * (1.0f / 6.0f);
        anim->distTimer = 0;
        anim->is1200 = 1200;

        if (norm3->interfaceFlags & 2) {
            anim->yawTimer = 6;
            Camera_SetFlags(camera, 0x20);
        } else {
            anim->yawTimer = 0;
        }

        camera->animState = 1;
        D_801EDC30[camera->camId].unk_66 = 0;
        anim->flag = 1;
    }

    if (anim->distTimer != 0) {
        anim->distTimer--;
    }

    sp90 = ((camera->speedRatio * 3.0f) + 1.0f) * 0.25f * 0.5f;
    sp8C = (temp_f2 = camera->speedRatio * 0.2f);

    if (D_801EDC30[camera->camId].unk_66 != 0) {
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + norm3->yawUpdateRateInv, camera->yawUpdateRateInv, sp90, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].unk_66 * 2) + 16.0f, camera->pitchUpdateRateInv, sp8C, 0.1f);
        D_801EDC30[camera->camId].unk_66--;
    } else {
        camera->yawUpdateRateInv = Camera_LERPCeilF(norm3->yawUpdateRateInv, camera->yawUpdateRateInv, sp90, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, sp8C, 0.1f);
    }

    camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, sp90, 0.001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp8C, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, sp8C, 0.0001f);

    phi_v1_2 = func_800CC9C0(camera, BINANG_ROT180(sp70.yaw), anim->flag & 1);
    temp_f2 = ((1.0f / norm3->pitchUpdateRateInv) * 0.5f) * (1.0f - camera->speedRatio);
    anim->curPitch = Camera_LERPCeilS(phi_v1_2, anim->curPitch, 
        ((1.0f / norm3->pitchUpdateRateInv) * 0.5f) + temp_f2, 5);

    if ((norm3->interfaceFlags & 0x40) || (player->rideActor == NULL)) {
        Camera_CalcAtDefault(camera, &sp68, norm3->yOffset, 1);
    } else {
        Camera_CalcAtForHorse(camera, &sp68, norm3->yOffset, &anim->yPosOffset, 1);
    }

    sp88 = (norm3->distMax + norm3->distMin) * 0.5f;
    OLib_Vec3fDiffToVecSphGeo(&sp80, at, eyeNext);
    temp_f2 = Camera_ClampDist1(camera, sp80.r, norm3->distMin, norm3->distMax, anim->distTimer);

    phi_f2 = ((sp88 - temp_f2));
    phi_f2 *= 0.002f;
    camera->dist = sp80.r = temp_f2 + phi_f2;

    if (norm3->interfaceFlags & 0x80) {
        sp80.pitch = Camera_LERPCeilS(((Actor*)camera->trackActor)->focus.rot.x - anim->curPitch, sp68.pitch, 0.25f, 5);
    } else {
        sp62 = norm3->pitchTarget - anim->curPitch;
        sp80.pitch = Camera_LERPCeilS(sp62, sp68.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
    }

    sp80.pitch = CLAMP_MAX(sp80.pitch, 0x38A4); // 79.7 degrees

    // -30 degrees
    if (sp80.pitch < -0x1554) {
        sp80.pitch = -0x1554;
    }

    if (norm3->interfaceFlags & 0x80) {
        sp62 = SUB16(((Actor*)camera->trackActor)->focus.rot.y, BINANG_ROT180(sp68.yaw));
        temp_f2 = 1.0f;
    } else {
        sp62 = SUB16(playerPosRot->rot.y, BINANG_ROT180(sp68.yaw));
        OLib_Vec3fToVecSphGeo(&sp78, &camera->playerPosDelta);
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

    if (anim->yawTimer > 0) {
        sp80.yaw += anim->yawUpdateRate;
        anim->yawTimer--;
        if (anim->yawTimer == 0) {
            Camera_UnsetFlags(camera, 0x20);
        }
    }

    OLib_VecSphAddToVec3f(eyeNext, at, &sp80);
    if (camera->status == CAM_STATUS_ACTIVE) {
        *eye = *eyeNext;
        func_800CBFA4(camera, at, eye, 0);
    } else {
        *eye = *eyeNext;
    }

    camera->fov = Camera_LERPCeilF(norm3->fovTarget, camera->fov, camera->fovUpdateRate, 0.1f);
    if (norm3->interfaceFlags & 0x20) {
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.05f, 5);
    } else {
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
    }

    camera->atLERPStepScale = Camera_ClampLERPScale(camera, norm3->maxAtLERPScale);
    anim->flag &= ~1;
    return true;
}

s32 Camera_Normal4(Camera* camera) {
    SubBgCamData* bgCamData;
    s16 roll;

    if (RELOAD_PARAMS) {
        bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
        D_801EDBF0 = bgCamData->rot.z;
    }

    roll = camera->roll;
    Camera_Normal1(camera);
    camera->roll = Camera_LERPCeilS(D_801EDBF0, roll, 0.05f, 5);
    return true;
}

s32 Camera_Normal0(Camera* camera) {
    Normal0* norm0 = (Normal0*)camera->paramData;
    f32 temp_f2;
    s32 pad[1];
    f32 temp_f0;
    f32 spA4;
    f32 spA0;
    VecSph sp98;
    VecSph sp90;
    VecSph sp88;
    VecSph sp80;
    VecSph sp78;
    Vec3f* sp40 = &camera->eye;
    Vec3f* sp3C = &camera->at;
    Vec3f* sp38 = &camera->eyeNext;
    PosRot* sp34 = &camera->trackActorPosRot;
    Normal0Anim* anim = &norm0->anim;
    f32 phi_f0;
    SubBgCamData* bgCamData;
    s16 temp_v1_2;
    s16 phi_a1;
    s16 phi_a0;
    f32 new_var;

    if (phi_a1) {}

    temp_f0 = Player_GetHeight((Player*)camera->trackActor);
    temp_f2 = 0.8f - ((68.0f / temp_f0) * -0.2f);

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        norm0->unk_00 = NEXTPCT * temp_f0 * temp_f2;
        norm0->unk_04 = NEXTPCT * temp_f0 * temp_f2;
        norm0->unk_08 = NEXTPCT * temp_f0 * temp_f2;
        norm0->unk_1C = DEGF_TO_BINANG(NEXTSETTING);
        norm0->unk_0C = NEXTSETTING;
        norm0->unk_10 = NEXTPCT;
        norm0->unk_14 = NEXTSETTING;
        norm0->unk_18 = NEXTPCT;
        norm0->unk_1E = NEXTSETTING;
    }

    sCameraInterfaceFlags = norm0->unk_1E;

    if ((camera->animState == 0) || (camera->animState == 10) || (camera->animState == 20)) {
        bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
        Camera_Vec3sToVec3f(&anim->unk_00, &bgCamData->pos);
        anim->unk_20 = bgCamData->rot.x;
        anim->unk_22 = bgCamData->rot.y;
        anim->unk_24 = sp34->pos.y;
        if (bgCamData->fov == -1) {
            anim->unk_1C = norm0->unk_14;
        } else {
            if (bgCamData->fov > 360) {
                phi_f0 = bgCamData->fov * 0.01f;
            } else {
                phi_f0 = bgCamData->fov;
            }
            anim->unk_1C = phi_f0;
        }

        if (bgCamData->unk_0E == -1) {
            anim->unk_2C = 0;
        } else {
            anim->unk_2C = bgCamData->unk_0E;
        }
        
        anim->unk_18 = 0.0f;
        anim->unk_28 = 120.0f;
        if (norm0->unk_1E & 4) {
            sp88.pitch = anim->unk_20;
            sp88.yaw = anim->unk_22;
            sp88.r = 100.0f;
            OLib_VecSphGeoToVec3f(&anim->unk_0C, &sp88);
        }
        camera->animState = 1;
        camera->yawUpdateRateInv = 50.0f;
    } else {
        if (func_800CB950(camera)) {
            anim->unk_24 = sp34->pos.y;
        }
        if (1) {}
    }

    OLib_Vec3fDiffToVecSphGeo(&sp80, sp3C, sp40);
    OLib_Vec3fDiffToVecSphGeo(&sp78, sp3C, sp38);
    camera->speedRatio *= 0.50f;
    spA4 = camera->speedRatio * 0.5f;
    spA0 = camera->speedRatio * 0.2f;
    camera->yawUpdateRateInv = Camera_LERPCeilF(norm0->unk_0C, camera->yawUpdateRateInv * camera->speedRatio, 0.5f, 0.1f);
    camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, spA0, 0.1f);
    camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, spA4, 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, spA0, 0.0001f);
    // TODO: 0.05 instead of 0.05f?
    camera->fovUpdateRate = Camera_LERPCeilF(0.05, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);


    if (!(norm0->unk_1E & 0x80)) {
        Camera_CalcAtDefault(camera, &sp78, norm0->unk_00, norm0->unk_1E & 1);
        anim->unk_28 = 120.0f;
    } else {
        func_800CD834(camera, &sp78, norm0->unk_00, &anim->unk_24, anim->unk_28);
        if (anim->unk_28 > 20.0f) {
            anim->unk_28 -= 0.2f;
        }
    }


    if (norm0->unk_1E & 4) {
        anim->unk_00.x = sp34->pos.x + anim->unk_0C.x;
        anim->unk_00.z = sp34->pos.z + anim->unk_0C.z;
    }


    anim->unk_00.y = sp34->pos.y;
    OLib_Vec3fDiffToVecSphGeo(&sp88, &anim->unk_00, sp3C);
    OLib_Vec3fDiffToVecSphGeo(&sp90, sp3C, sp38);

    if (anim->unk_2C & 2) {
        phi_a1 = anim->unk_22;
    } else {
        phi_a1 = norm0->unk_1C;
    }

    temp_v1_2 = sp90.yaw - sp88.yaw;
    if (((phi_a1 <= 0x4000) && (phi_a1 < ABS(temp_v1_2))) || ((phi_a1 > 0x4000) && (ABS(temp_v1_2) < phi_a1))) {
        if (1) { } if (1) { } if (1) { } if (1) { } // Needed to swap v0/v1
        new_var = 1.0f; // needed because the *1.0f isn't being multiplied

        if (temp_v1_2 < 0) {
            phi_a0 = -phi_a1;
        } else {
            phi_a0 = phi_a1;
        }

        phi_a0 += sp88.yaw;       
        sp98.yaw = Camera_LERPCeilS(phi_a0, sp80.yaw, (1.0f / camera->yawUpdateRateInv) * new_var * camera->speedRatio, 5);
        if (anim->unk_2C & 1) {
            sp98.pitch = Camera_CalcDefaultPitch(camera, sp78.pitch, anim->unk_20, 0);
        } else {
            sp98.pitch = sp80.pitch;
        }
    } else {
        sp98 = sp90;
    }

    camera->dist = sp98.r = Camera_ClampDist1(camera, sp90.r, norm0->unk_04, norm0->unk_08, 0);
    if (!(anim->unk_2C & 1)) {
        if (sp98.pitch > 0xE38) { // 20 degrees
            sp98.pitch += ((s16)(0xE38 - sp98.pitch) >> 2);
        }
        if (sp98.pitch < 0) {
            sp98.pitch += ((s16)(-0x38E - sp98.pitch) >> 2);
        }
    }
    OLib_VecSphAddToVec3f(sp38, sp3C, &sp98);
    
    *sp40 = *sp38;

    if (camera->status == CAM_STATUS_ACTIVE) {
        if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (norm0->unk_1E & 0x10)) {
            Camera_BGCheck(camera, sp3C, sp40);
        } else {
            func_800CBFA4(camera, sp3C, sp40, 3);
            OLib_Vec3fDiffToVecSphGeo(&sp98, sp40, sp3C);
            camera->inputDir.x = sp98.pitch;
            camera->inputDir.y = sp98.yaw;
            camera->inputDir.z = 0;
        }
    }
    camera->fov = Camera_LERPCeilF(anim->unk_1C, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, norm0->unk_18);
    return 1;
}

s32 Camera_Parallel1(Camera *camera) {
    Vec3f *sp44 = &camera->eye;
    Vec3f *sp40 = &camera->at;
    Vec3f *sp3C = &camera->eyeNext;
    Vec3f spB0;
    Vec3f spA4;
    f32 spA0;
    f32 sp9C;
    PosRot *sp38 = &camera->trackActorPosRot;
    VecSph sp90;
    VecSph sp88;
    VecSph sp80;
    VecSph sp78;
    Parallel1* para1 = (Parallel1*)camera->paramData;
    s16 sp72;
    s16 tangle;
    Parallel1Anim* anim = &para1->anim;
    SubBgCamData* bgCamData;
    s32 new_var3;
    f32 sp60;
    s16 new_var2; 
    s16 phi_a0;
    s32 phi_a0_2;
    CameraModeValue* values;
    f32 sp50;

    sp60 = Camera_GetTrackedActorHeight(camera);

    if (!RELOAD_PARAMS) {
    } else {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        para1->unk_00 = NEXTPCT * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        para1->unk_04 = NEXTPCT * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        para1->unk_08 = NEXTPCT * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        para1->unk_20 = DEGF_TO_BINANG(NEXTSETTING);
        para1->unk_22 = DEGF_TO_BINANG(NEXTSETTING);
        para1->unk_0C = NEXTSETTING;
        para1->unk_10 = NEXTSETTING;
        para1->unk_14 = NEXTSETTING;
        para1->unk_18 = NEXTPCT;
        para1->unk_26 = NEXTSETTING;
        para1->unk_1C = NEXTPCT;
        para1->unk_24 = NEXTSETTING;
        anim->unk_00 = para1->unk_04;
    }
    
    OLib_Vec3fDiffToVecSphGeo(&sp80, sp40, sp44);
    OLib_Vec3fDiffToVecSphGeo(&sp78, sp40, sp3C);
    func_800CBAD4(&spA4, camera);

    switch (camera->animState) {
        case 0x14:
            if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 0) {
                Camera_SetUpdateRatesFastYaw(camera);
            }
        case 0:
        case 0xA:
            if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x4 | 0x2)) {
                anim->unk_10 = sp38->pos;
            } else {
                camera->xzOffsetUpdateRate = 0.5f;
                camera->yOffsetUpdateRate = 0.5f;
            }

            if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 0x8) {
                anim->unk_10 = camera->trackActorPosRot.pos;
            }

            anim->unk_0C = 200.0f;

            if ((2.0f * para1->unk_04) < camera->dist) {
                camera->dist = 2.0f * para1->unk_04;
                sp78.r = camera->dist;
                sp80.r = sp78.r;
                OLib_VecSphAddToVec3f(sp44, sp40, &sp80);
                *sp3C = *sp44;
            }

            anim->unk_1C = 0;

            if (para1->unk_26 & 4) {
                anim->unk_22 = 0x14;
            } else {
                anim->unk_22 = 6;
            }

            if (((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) && (camera->mode == CAM_MODE_CHARGE)) {
                anim->unk_22 = 0x1E;
                if (((Player*)camera->trackActor)->transformation == PLAYER_FORM_DEKU) {
                    para1->unk_24 = -1;
                }
            }

            if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x8 | 0x2)) {
                anim->unk_22 = 1;
                sp50 = 0.8f - ((68.0f / sp60) * -0.2f);
                bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
                anim->unk_20 = bgCamData->rot.x;
                anim->unk_1E = bgCamData->rot.y;
                anim->unk_08 = (bgCamData->fov == -1) ? para1->unk_14 : (bgCamData->fov > 360) ? bgCamData->fov * 0.01f : bgCamData->fov;
                anim->unk_00 = (bgCamData->unk_0E == -1) ? para1->unk_04 : bgCamData->unk_0E * 0.01f * sp60 * sp50;
                dummy:; // TODO: is needed?
            } else {
                anim->unk_08 = para1->unk_14;
                anim->unk_00 = para1->unk_04;
            }

            anim->unk_24 = para1->unk_24;
            anim->unk_04 = sp38->pos.y - camera->playerPosDelta.y;
            anim->unk_26 = 1;
            camera->animState = 1;
            sCameraInterfaceFlags = para1->unk_26;
    }

    if (anim->unk_22 != 0) {
        switch (para1->unk_26 & (0x8 | 0x4 | 0x2)) {
            case 0x2:
            case (0x8 | 0x4 | 0x2):
                anim->unk_1E = BINANG_ROT180(camera->trackActorPosRot.rot.y) + para1->unk_22;
                anim->unk_20 = para1->unk_20;
                break;
            case 0x4:
                anim->unk_1E = para1->unk_22;
                anim->unk_20 = para1->unk_20;
                break;
            case (0x4 | 0x2):
                if (anim->unk_24 == 1) {
                    OLib_Vec3fDiffToVecSphGeo(&sp88, &anim->unk_10, &spA4);
                    anim->unk_1E = ((ABS(SUB16(sp88.yaw, sp80.yaw)) < 0x3A98) || func_800CBA08(camera)) ? sp80.yaw : sp80.yaw + (s16)((SUB16(sp88.yaw, sp80.yaw) >> 2) * 3);
                }
                anim->unk_20 = para1->unk_20;
                break;
            case 0x8:
                anim->unk_1E = sp80.yaw;
                anim->unk_20 = para1->unk_20;
                break;
            case (0x8 | 0x2):
                break;
            default:
                anim->unk_1E = sp78.yaw + para1->unk_22;
                anim->unk_20 = para1->unk_20;
                break;
        }
    } else if (para1->unk_26 & 0x20) {
        anim->unk_1E = BINANG_ROT180(camera->trackActorPosRot.rot.y) + para1->unk_22;
    }

    if (camera->animState == 0x15) {
        camera->animState = 1;
    } else if (camera->animState == 0xB) {
        camera->animState = 1;
    }

    spA0 = camera->speedRatio * 0.5f;
    sp9C = camera->speedRatio * 0.2f;

    if (((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x4 | 0x2)) || ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 0x8) || (para1->unk_26 & 0x20)) {
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
        camera->yawUpdateRateInv = Camera_LERPCeilF(para1->unk_0C, camera->yawUpdateRateInv, 0.5f, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
    } else {
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, spA0, 0.1f);
        camera->yawUpdateRateInv = Camera_LERPCeilF(para1->unk_0C, camera->yawUpdateRateInv, spA0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(2.0f, camera->pitchUpdateRateInv, sp9C, 0.1f);
    }

    if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x8 | 0x4 | 0x2)) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.1f, camera->yOffsetUpdateRate, spA0, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.1f, camera->xzOffsetUpdateRate, sp9C, 0.0001f);
    } else if (para1->unk_26 & 0x80) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.5f, camera->yOffsetUpdateRate, spA0, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.5f, camera->xzOffsetUpdateRate, sp9C, 0.0001f);
    } else {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, spA0, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp9C, 0.0001f);
    }

    // TODO: Extra 0 needed?
    camera->fovUpdateRate = Camera_LERPCeilF(0.050f, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);

    if (para1->unk_26 & 1) {
        tangle = func_800CC9C0(camera, BINANG_ROT180(sp80.yaw), anim->unk_26 = 1);
        spA0 = ((1.0f / para1->unk_10));
        spA0 *= 0.6f;
        sp9C = ((1.0f / para1->unk_10) * 0.4f) * (1.0f - camera->speedRatio);
        anim->unk_1C = Camera_LERPCeilS(tangle, anim->unk_1C, spA0 + sp9C, 5);
    } else {
        anim->unk_1C = 0;
    }

    if (func_800CB950(camera) || (((Player*)camera->trackActor)->stateFlags1 & 0x1000) || (((Player*)camera->trackActor)->stateFlags3 & 0x100)) {
        anim->unk_04 = camera->trackActorPosRot.pos.y; sp72 = false;
    } else {
        sp72 = true;
    }

    if ((((Player*)camera->trackActor)->stateFlags1 & 0x4000) || (((Player*)camera->trackActor)->stateFlags1 & 4) || ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 6)) {
        spB0 = spA4;
        spB0.y += ((sp60 * 0.6f) + para1->unk_00);
        Camera_LERPCeilVec3f(&spB0, sp40, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.0001f);
        Camera_UpdateAtActorOffset(camera, &sp38->pos);
    } else {
        if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x8 | 0x4 | 0x2)) {
            spB0 = sp38->pos;
            spB0.y += sp60 + para1->unk_00;
            Camera_LERPCeilVec3f(&spB0, sp40, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.0001f);
            Camera_UpdateAtActorOffset(camera, &sp38->pos);
        } else if (anim->unk_22 != 0) {
            Camera_CalcAtDefault(camera, &sp78, para1->unk_00, 0);
            anim->unk_0C = 200.0f;
        } else if (!(para1->unk_26 & 0x80) && !sp72) {
            func_800CDB6C(camera, &sp78, para1->unk_00, para1->unk_08, &anim->unk_04, para1->unk_26 & 0x41);
            anim->unk_0C = 200.0f;
        } else {
            func_800CD834(camera, &sp78, para1->unk_00, &anim->unk_04, anim->unk_0C);
            if (anim->unk_0C > 10.0f) {
                anim->unk_0C--;
            }
        }
    }

    camera->dist = Camera_LERPCeilF(anim->unk_00, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);

    if (anim->unk_22 != 0) {
        if (anim->unk_24 <= 0) {
            if (anim->unk_24 == 0) {
                Camera_SetFlags(camera, 0x20);
            }


            tangle = ((anim->unk_22 + 1) * anim->unk_22) >> 1;
            sp90.yaw = sp80.yaw + ((SUB16(anim->unk_1E, sp80.yaw) / tangle) * anim->unk_22);
            phi_a0 = ((para1->unk_26 & 1) ? SUB16(anim->unk_20, anim->unk_1C) : anim->unk_20);
            new_var2 = SUB16(phi_a0, sp80.pitch);
            sp90.pitch = sp80.pitch + ((new_var2 / tangle) * anim->unk_22);
            sp90.r = camera->dist;
            anim->unk_22--;
        } else {
            sp90 = sp80;
            sp90.r = camera->dist;
        }
    } else {
        OLib_Vec3fDiffToVecSphGeo(&sp90, sp40, sp3C);
        sp90.r = camera->dist;

        if (para1->unk_26 & 2) {
            sp90.yaw = Camera_LERPCeilS(anim->unk_1E, sp78.yaw, 1.0f / camera->yawUpdateRateInv, 0xC8);
        }

        new_var3 = (para1->unk_26 & (0x8 | 0x4 | 0x2));

        if (para1->unk_26 & 1) {
            phi_a0 = (anim->unk_20 - anim->unk_1C);
        } else {
            phi_a0 = anim->unk_20;
        }

        if (new_var3 == (0x8 | 0x4 | 0x2)) {
            spA0 = CLAMP_MAX(camera->speedRatio, 1.0f);
            phi_a0 = (sp90.pitch * spA0) + (phi_a0 * (1.0f - spA0));
            sp90.pitch = Camera_LERPCeilS(phi_a0, sp78.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        } else if (new_var3 != 0x8) {
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

    if (anim->unk_24 > 0) {
        anim->unk_24--;
    }

    
    OLib_VecSphAddToVec3f(sp3C, sp40, &sp90);

    if (camera->status == CAM_STATUS_ACTIVE) {
        if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (para1->unk_26 & 0x10)) {
            spB0 = *sp40;
            if ((((Player*)camera->trackActor)->stateFlags1 & 0x4000) || (((Player*)camera->trackActor)->stateFlags1 & 4) || ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 6)) {
                spB0.y += sp60;
            }
            *sp44 = *sp3C;
            func_800CBFA4(camera, &spB0, sp44, 0);
        } else {
            *sp44 = *sp3C;
            func_800CBFA4(camera, sp40, sp44, 3);
        }

        if (anim->unk_22 != 0) {
            sUpdateCameraDirection = true;
        } else {
            sUpdateCameraDirection = false;
        }
    }

    camera->fov = Camera_LERPCeilF(anim->unk_08, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, sp72 ? para1->unk_1C : para1->unk_18);
    anim->unk_26 &= ~1;
    return true;
}

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
 * This function is matching but rodata was improperly split between Camera_Jump2 and Camera_Jump3
 * This will successfully match when Camera_Jump3 is matching 
 * (has been verified by manually moving rodata asm after extraction)
 */
#ifdef NON_MATCHING
s32 Camera_Jump2(Camera *camera) {
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
    Jump2* jump2 = (Jump2*)camera->paramData;
    f32 sp90;
    f32 sp8C;
    s32 sp88;
    CamColChk sp60;
    PosRot *sp2C = &camera->trackActorPosRot;
    f32 temp_f0_2;
    Jump2Anim* anim = &jump2->anim; // sp28
    f32 phi_f2;
    f32 yNormal; // used twice
    f32 actorHeight = Camera_GetTrackedActorHeight(camera);
    f32 temp_f16;

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        yNormal = 0.8f - (-0.2f * (68.0f / actorHeight));

        if (camera->playerPosDelta.y > 0.0f) {
            phi_f2 = -10.0f;
        } else {
            phi_f2 = 10.0f;
        }

        jump2->unk_00 = PCT(phi_f2 + NEXTSETTING) * actorHeight * yNormal;
        jump2->unk_04 = NEXTPCT * actorHeight * yNormal;
        jump2->unk_08 = NEXTPCT * actorHeight * yNormal;
        jump2->unk_0C = NEXTPCT;
        jump2->unk_10 = NEXTSETTING;
        jump2->unk_14 = NEXTPCT;
        jump2->unk_18 = NEXTSETTING;
        jump2->unk_1C = NEXTPCT;
        jump2->unk_20 = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp9C, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&spA4, at, eyeNext);

    sCameraInterfaceFlags = jump2->unk_20;

    if (RELOAD_PARAMS) {    
        spC8 = sp2C->pos;
        temp_f0_2 = Camera_GetFloorY(camera, &spC8);
        anim->unk_00 = temp_f0_2;
        anim->unk_04 = spA4.yaw;
        anim->unk_06 = 0;
        if (temp_f0_2 == BGCHECK_Y_MIN) {
            anim->unk_0A = -1;
            anim->unk_00 = sp2C->pos.y - 1000.0f;
        } else if ((sp2C->pos.y - anim->unk_00) < actorHeight) {
            anim->unk_0A = 1;
        } else {
            anim->unk_0A = -1;
        }

        yawDiff = SUB16(BINANG_ROT180(sp2C->rot.y), spA4.yaw);
        anim->unk_06 = ((yawDiff / 6) / 4) * 3;
        if (jump2->unk_20 & 2) {
            anim->unk_08 = 10;
        } else {
            anim->unk_08 = 10000;
        }

        sp2C->pos.x -= camera->playerPosDelta.x;
        sp2C->pos.y -= camera->playerPosDelta.y;
        sp2C->pos.z -= camera->playerPosDelta.z;
        anim->unk_0C = 6;
        camera->animState++;
        camera->atLERPStepScale = jump2->unk_1C;
    }

    sp90 = camera->speedRatio * 0.5f;
    sp8C = camera->speedRatio * 0.2f;
    camera->yawUpdateRateInv = Camera_LERPCeilF(jump2->unk_10, camera->yawUpdateRateInv, sp90, 0.1f);
    camera->yOffsetUpdateRate = Camera_LERPCeilF(jump2->unk_14, camera->yOffsetUpdateRate, sp90, 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp8C, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, camera->speedRatio * .05f, 0.0001f);
    camera->rUpdateRateInv = 1800.0f;
    Camera_CalcAtDefault(camera, &spA4, jump2->unk_00, 0);
    OLib_Vec3fDiffToVecSphGeo(&spB4, at, eye);

    yNormal = jump2->unk_04; // required to match
    
    phi_f2 = jump2->unk_08 + (jump2->unk_08 * jump2->unk_0C);
    temp_f16 = jump2->unk_04 - (jump2->unk_04 * jump2->unk_0C);

    if (spB4.r > phi_f2) {
        spB4.r = phi_f2;
    } else if (spB4.r < temp_f16) {
        spB4.r = temp_f16;
    }

    yawDiff = SUB16(BINANG_ROT180(sp2C->rot.y), spB4.yaw);
    if (anim->unk_0C != 0) {
        anim->unk_04 = BINANG_ROT180(sp2C->rot.y);
        anim->unk_0C--;
        spB4.yaw = Camera_LERPCeilS(anim->unk_04, spA4.yaw, 0.5f, 5);
    } else if (anim->unk_08 < ABS(yawDiff)) {
        temp_t2 = BINANG_ROT180(sp2C->rot.y);
        spB4.yaw = Camera_LERPFloorS((yawDiff < 0) ? (temp_t2 + anim->unk_08) : (temp_t2 - anim->unk_08), spA4.yaw, 0.1f, 1);
    } else {
        spB4.yaw = Camera_LERPCeilS(spB4.yaw, spA4.yaw, 0.25f, 5);
    }
    
    spC8.x = sp2C->pos.x + (Math_SinS(sp2C->rot.y) * 25.0f);
    spC8.y = sp2C->pos.y + (actorHeight * 2.2f);
    spC8.z = sp2C->pos.z + (Math_CosS(sp2C->rot.y) * 25.0f);

    yNormal = Camera_GetFloorYNorm(camera, &spBC, &spC8, &sp88);
    if (((Actor*)camera->trackActor)->bgCheckFlags & 0x10) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        spB4.pitch = Camera_LERPCeilS(-0x1388, spA4.pitch, 0.2f, 5);
    } else if ((yNormal != BGCHECK_Y_MIN) && (sp2C->pos.y < yNormal)) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        if (camera->playerPosDelta.y > 1.0f) {
            spB4.pitch = Camera_LERPCeilS(0x1F4, spA4.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }
    } else if ((sp2C->pos.y - anim->unk_00) < actorHeight) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        if (camera->playerPosDelta.y > 1.0f) {
            spB4.pitch = Camera_LERPCeilS(0x1F4, spA4.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }
    } else {
        camera->pitchUpdateRateInv = 100.0f;
        camera->rUpdateRateInv = 100.0f;
    }

    spB4.pitch = CLAMP_MAX(spB4.pitch, 0x2AF8); // 60.4 degrees
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
    camera->fov = Camera_LERPCeilF(jump2->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Jump2.s")
#endif

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
    Jump3* jump3 = (Jump3*)camera->paramData;
    Jump3Anim* anim = &jump3->anim; // sp28
    Vec3f sp64;
    f32 sp60;
    f32 sp5C;
    s32 sp58;

    sp78 = Camera_GetTrackedActorHeight(camera);
    Actor_GetFocus(&sp64, camera->trackActor);
    sp60 = camera->waterYPos - sp48->y;

    sp58 = false;

    if (RELOAD_PARAMS) {
        anim->unk_0A = camera->mode;
        anim->unk_0C = 0;
    }

    if (camera->mode == CAM_MODE_NORMAL) {
        if ((((Actor*)camera->trackActor)->bgCheckFlags & 0x10) || (anim->unk_0C != 0)) {
            if (anim->unk_0A != 0xF) {
                anim->unk_0A = 0xF;
                sp58 = true;
                anim->unk_0C = 0xA;
            }
        } else if (sp60 < 50.0f) {
            if (anim->unk_0A != 0) {
                anim->unk_0A = 0;
                sp58 = true;
            }
        } else if (Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerGroundY) < 11.0f) {
            if (anim->unk_0A != 5) {
                anim->unk_0A = 5;
                sp58 = true;
            }
        } else if ((sp60 > 250.0f) && (anim->unk_0A != 0x1A)) {
            anim->unk_0A = 0x1A;
            sp58 = true;
        }
    }

    if (anim->unk_0C != 0) {
        anim->unk_0C--;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp9C, sp44, sp48);
    OLib_Vec3fDiffToVecSphGeo(&sp94, sp44, sp40);


    // Everything above is down to SP and floats
    // PERM_RANDOMIZE(
    
    if (!RELOAD_PARAMS && !sp58) {
    } else {
        values = sCameraSettings[camera->setting].cameraModes[anim->unk_0A].values;
        
        sp5C = 0.8f - -0.2f * (68.0f / sp78);
        spD0 = sp78 * 0.01f * sp5C;
        // if (phi_f2) {}
        
        jump3->unk_00 = NEXTSETTING * spD0;
        jump3->unk_04 = NEXTSETTING * spD0;
        if (1) {}
        jump3->unk_08 = NEXTSETTING * spD0;
        jump3->unk_20 = DEGF_TO_BINANG(NEXTSETTING);
        jump3->unk_0C = NEXTSETTING;
        jump3->unk_10 = NEXTSETTING;
        jump3->unk_14 = NEXTSETTING * 0.01f;
        jump3->unk_18 = NEXTSETTING;
        jump3->unk_1C = NEXTSETTING * 0.01f;
        jump3->unk_22 = NEXTSETTING;
    }


    sCameraInterfaceFlags = jump3->unk_22;


    switch (camera->animState) {
        case 0:
            anim->unk_10 = 0x1000;
        case 10:
        case 20:
            anim->unk_00 = camera->playerGroundY;
            D_801EDC30[camera->camId].yaw = D_801EDC30[camera->camId].pitch = D_801EDC30[camera->camId].unk_64 = 0;
            anim->unk_08 = 0xA;
            D_801EDC30[camera->camId].swingUpdateRate = jump3->unk_0C;
            camera->animState++;
            D_801EDC30[camera->camId].unk_66 = 0;
            break;
        default:
            if (anim->unk_08 != 0) {
                anim->unk_08--;
            }
            break;
    }

    spC0 = sp64.y - sp3C->pos.y;
    spB4 = *sp48;

    // crazy things going on with temp_f0_2
    // temp_f0_2 = camera->speedRatio; // Removing this temp fixes large chuncks of code and destorys other chuncks of code

    
    // PERM_RANDOMIZE(

    spD0 = camera->speedRatio;
    spD0 *=  0.5f;
    spCC = camera->speedRatio * 0.2f;
    // spCC = phi_f2;

    temp_f0 = (D_801EDC30[camera->camId].unk_64 == 1) ? 0.5f : spD0;



    if (D_801EDC30[camera->camId].unk_66 != 0) {
        // spD0 = temp_f2;
        // spCC = camera->speedRatio * 0.2f;
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->camId].swingUpdateRate + D_801EDC30[camera->camId].unk_66 * 2), camera->yawUpdateRateInv, spD0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF((40.0f + D_801EDC30[camera->camId].unk_66 * 2), camera->pitchUpdateRateInv, spCC, 0.1f);
        D_801EDC30[camera->camId].unk_66--;
    } else {
        // spCC = camera->speedRatio * 0.2f;
        // phi_f14 = camera->yawUpdateRateInv;
        camera->yawUpdateRateInv = Camera_LERPCeilF(D_801EDC30[camera->camId].swingUpdateRate, camera->yawUpdateRateInv, temp_f0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(40.0f, camera->pitchUpdateRateInv, spCC, 0.1f);
    }

    // NOT ELSE
    // PERM_RANDOMIZE(

    if (jump3->unk_22 & 0x80) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.01f, camera->yOffsetUpdateRate, spD0, 0.0001f);
        // sp4C = sqrtf(SQXZ(&camera->playerPosDelta));
        // if (1) {} // TODO: is needed? (helps a lot)
        // temp_f0 = sqrtf((camera->playerPosDelta.x * camera->playerPosDelta.x) + (camera->playerPosDelta.z * camera->playerPosDelta.z));
        // if (1) {}
        sp5C = sqrtf((camera->playerPosDelta.x * camera->playerPosDelta.x) + (camera->playerPosDelta.z * camera->playerPosDelta.z)) / func_800CB780(camera);
        camera->speedRatio = OLib_ClampMaxDist(sp5C / func_800CB780(camera), 1.8f);
        spCC = camera->speedRatio * 0.2f;
    } else {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, phi_f14 = camera->yOffsetUpdateRate, spD0, 0.0001f);
        // spCC = phi_f2; // Currently not needed
        // spCC = camera->speedRatio * 0.2f;
    }

    // if (1) {} // TODO is needed?
    // dummy:; // TODO is needed?
    

    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, spCC, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.050f, (0, camera->fovUpdateRate), camera->speedRatio * 0.05f, 0.0001f); // TODO: IS extra 0 needed?

    // Everything below is down to SP and floats
    // )

    if (sp60 < 50.0f) {
        sp5C = camera->waterYPos - spC0;
        if (sp60 < 0.0f) {
            phi_f14 = 1.0f;
        } else {
            phi_f14 = 1.0f - (sp60 / 50.0f);
        }
        func_800CD834(camera, &sp94, jump3->unk_00, &sp5C, phi_f14 * 50.0f);
    } else {
        Camera_CalcAtDefault(camera, &sp94, jump3->unk_00, jump3->unk_22);
    }

    OLib_Vec3fDiffToVecSphGeo(&spAC, sp44, sp40);
    spAC.r = Camera_ClampDist1(camera, spAC.r, jump3->unk_04, jump3->unk_08, anim->unk_08);
    camera->dist = spAC.r;

    if (!(Camera_fabsf(sp3C->pos.y - camera->playerGroundY) < 10.0f) && !(Camera_fabsf(sp64.y - camera->waterYPos) < 50.f)) { // No 0?
        camera->pitchUpdateRateInv = 100.0f;
    }

    // PERM_RANDOMIZE(
    if (jump3->unk_22 & 0x20) {
        if (camera->speedRatio * 1.3f > 0.6f) {
            spD0 = 0.6f;
        } else {
            spD0 = (camera->speedRatio * 1.3f);
        }
        // spD0 = pad1;
        spAC.pitch = Camera_LERPCeilS((spAC.pitch * spD0) + (jump3->unk_20 * (1.0f - spD0)), sp94.pitch, 1.0f / ((camera->pitchUpdateRateInv + 1.0f) - (camera->pitchUpdateRateInv * spD0)), 5);
    } else if (D_801EDC30[camera->camId].unk_64 == 1) {
        pad1 = 1.0f / camera->yawUpdateRateInv;
        spAC.yaw = Camera_LERPCeilS(D_801EDC30[camera->camId].yaw, sp94.yaw, pad1, 5);
        // temp_f0 = 1.0f / camera->yawUpdateRateInv;
        // Bug? Should be pitchUpdateRateInv
        spAC.pitch = Camera_LERPCeilS(D_801EDC30[camera->camId].pitch, sp94.pitch, 1.0f / camera->yawUpdateRateInv, 5);
    } else if (jump3->unk_22 & (0x80 | 0x8)) {
        spAC.yaw = Camera_CalcDefaultYaw(camera, sp94.yaw, sp3C->rot.y, jump3->unk_14, 0.0f);
        
        if (camera->speedRatio * 1.3f > 1.0f) {
            spCC = pad2 = 1.0f;
        } else {
            spCC = pad2 = camera->speedRatio * 1.3f;
        }
        spAC.pitch = Camera_LERPCeilS((spAC.pitch * spCC) + (jump3->unk_20 * (1.0f - spCC)), sp94.pitch, 1.0f / ((camera->pitchUpdateRateInv + 1.0f) - (camera->pitchUpdateRateInv * spCC)), 5);
    } else {
        spAC.yaw = Camera_CalcDefaultYaw(camera, sp94.yaw, sp3C->rot.y, jump3->unk_14, 0.0f);
        spAC.pitch = Camera_CalcDefaultPitch(camera, sp94.pitch, jump3->unk_20, 0);
    }
    // )
    
    // 79.7 degrees
    if (spAC.pitch > 0x38A4) {
        spAC.pitch = 0x38A4;
    }

    // -30 degrees
    if (spAC.pitch < -0x1554) {
        spAC.pitch = -0x1554;
    }

    OLib_VecSphAddToVec3f(sp40, sp44, &spAC);
    if ((camera->status == CAM_STATUS_ACTIVE) && !(jump3->unk_22 & 0x40)) {
        if (func_800CBA7C(camera) == 0) {
            func_800CED90(camera, &spAC, &sp9C, jump3->unk_04, jump3->unk_0C, &D_801EDC30[camera->camId], &anim->unk_10);
        }
        if (jump3->unk_22 & 4) {
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
        D_801EDC30[camera->camId].swingUpdateRate = jump3->unk_0C;
        D_801EDC30[camera->camId].unk_64 = 0;
        sUpdateCameraDirection = false;
        *sp48 = *sp40;
    }

    camera->fov = Camera_LERPCeilF(jump3->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, .5f, 5); // TODO is extra 0 in 0.50f needed? (try without f)
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, jump3->unk_1C);
    return true;
    // )
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
s32 Camera_Battle1(Camera *camera) {
    Battle1* batt1 = (Battle1*)camera->paramData;
    Battle1Anim* anim = &batt1->anim;
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
    PosRot *sp8C;
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
    Vec3f *sp50;
    Vec3f *sp4C;
    Vec3f *sp48;
    PosRot *sp40;

    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2_2;
    f32 temp_f2_3;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s32 temp_f4;
    f32 phi_f0;
    f32 phi_f0_3;
    f32 phi_f12;
    f32 phi_f0_4;
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
    sp8C = &((Actor*)camera->trackActor)->focus;
    sp68 = Camera_GetTrackedActorHeight(camera);
    if ((camera->animState != 0) && (camera->animState != 0xA) && (camera->animState != 0x14)) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        batt1->unk_00 = NEXTSETTING* 0.01f * sp68 * (0.8f - ((68.0f / sp68) * -0.2f));
        batt1->unk_04 = NEXTSETTING;
        batt1->unk_08 = NEXTSETTING;
        batt1->unk_0C = NEXTSETTING;
        batt1->unk_0C = 80.0f - (80.0f - batt1->unk_0C);
        batt1->unk_10 = NEXTSETTING;
        batt1->unk_10 = 0.0f - (0.0f - batt1->unk_10);
        batt1->unk_14 = NEXTSETTING;
        batt1->unk_14 = 40.0f - (40.0f - batt1->unk_14);
        batt1->unk_18 = NEXTSETTING;
        batt1->unk_18 = 20.0f - (20.0f - batt1->unk_18);
        batt1->unk_1C = NEXTSETTING * 0.01f;
        batt1->unk_1C = 1.0f - (1.0f - batt1->unk_1C);
        batt1->unk_20 = NEXTSETTING;
        batt1->unk_24 = NEXTSETTING * 0.01f;
        batt1->unk_24 = 1.0f - (1.0f - batt1->unk_24);
        batt1->unk_30 = NEXTSETTING;
        batt1->unk_28 = NEXTSETTING * 0.01f;
        batt1->unk_28 = 0.2f - (0.2f - batt1->unk_28);
        batt1->unk_2C = NEXTSETTING * 0.01f;
        if ((camera->animState != 0) && (camera->animState != 0xA) && (camera->animState != 0x14)) {
        } else {
            anim->unk_18 = 0x28;
            camera->pitchUpdateRateInv = 9.0f;
        }
    }

    sp80 = batt1->unk_14;
    sp7C = batt1->unk_18;
    sp78 = batt1->unk_20;
    
    if (func_800CBA34(camera)) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(18.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.2f, camera->yOffsetUpdateRate, 0.5f, 0.0001f);
        camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.2f, camera->xzOffsetUpdateRate, 0.5f, 0.0001f);
        if (anim->unk_18 >= -0x13) {
            anim->unk_18--;
        } else {
            sp80 = 50.0f;
            sp7C = 40.0f;
            sp78 = 60.0f;
        }
    } else {
        if (anim->unk_18 < 0) {
            sp80 = 50.0f;
            sp7C = 40.0f;
            sp78 = 60.0f;
            anim->unk_18++;
        } else {
            anim->unk_18 = 0x28;
            camera->pitchUpdateRateInv = Camera_LERPCeilF(9.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
            camera->yOffsetUpdateRate = Camera_LERPCeilF(0.6f, camera->yOffsetUpdateRate, camera->speedRatio * 0.5f, 0.0001f);
            camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.6f, camera->xzOffsetUpdateRate, camera->speedRatio * 0.2f, 0.0001f);
        }
    }

    camera->fovUpdateRate = Camera_LERPCeilF(0.050f, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);
    sp68 += batt1->unk_00;
    OLib_Vec3fDiffToVecSphGeo(&sp9C, sp4C, sp50);
    OLib_Vec3fDiffToVecSphGeo(&sp94, sp4C, sp48);
    if ((camera->target == NULL) || (camera->target->update == NULL)) {
        camera->target = NULL;
        Camera_ChangeMode(camera, CAM_MODE_TARGET);
        return true;
    } 
    
    sCameraInterfaceFlags = batt1->unk_30;

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        anim->unk_10 = 0;
        anim->unk_1A = 0;
        anim->unk_08 = camera->target;
        camera->animState++;
        anim->unk_16 = 7;
        anim->unk_12 = sp9C.yaw;
        anim->unk_14 = sp9C.pitch;
        anim->unk_00 = sp9C.r;
        anim->unk_04 = camera->trackActorPosRot.pos.y - camera->playerPosDelta.y;
        if ((2.0f * batt1->unk_04) < camera->dist) {
            camera->dist = 2.0f * batt1->unk_04;
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
        anim->unk_04 = camera->trackActorPosRot.pos.y;
        sp84 = 0;
    } else {
        sp84 = 1;
    }


    if (anim->unk_16 == 0) {
        if (sp84 != 0) {
            phi_f0 = batt1->unk_28;
        } else {
            phi_f0 = batt1->unk_24;
        }
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, phi_f0);
    }

    Actor_GetFocus(&sp40->pos, camera->target);

    if (anim->unk_08 != camera->target) {
        camera->animState = 0;
        return true;
    } 

    sp120 = camera->trackActorPosRot.pos;
    sp120.y += sp68;
    OLib_Vec3fDiffToVecSphGeo(&spA4, &sp120, &sp40->pos);
    sp104 = func_800CD6CC(camera->target);
    temp_f2_2 = PREG(86) + 800.0f;
    if (temp_f2_2 < sp104) {
        sp104 = temp_f2_2;
    }

    // new_var5 = sp104; // TODO: Fake temp but helps when used?
    // sp104 = new_var5;

    // Above is down to SP and Floats
    
    if ((sp104 < spA4.r) || func_800CBA34(camera)) {
        spEC = 1.0f;
        spF8 = 10.0f;
        // dummy:; // Helps?
        // sp80 = batt1->unk_14; // Fake & Non-equivalent but helps?
    } else {
        spEC = spA4.r / sp104;
        spF8 = 2.0f;
    }
    // spF8 should be set with swc1 twice, not once

    // sp94 is loading in too early
    func_800CE2B8(camera, &sp94.r, sp40, batt1->unk_00, batt1->unk_2C, 1.0f - spEC, &anim->unk_04, &spA4, (sp84 ? 0x81 : 1) | batt1->unk_30);
    
    
    sp88 = spA4.yaw;
    OLib_Vec3fDiffToVecSphGeo(&spBC, sp4C, sp48);
    spF4 = batt1->unk_04 + ((batt1->unk_08 - batt1->unk_04) * spEC);
    camera->rUpdateRateInv = Camera_LERPCeilF(spF8, camera->rUpdateRateInv, 0.5f, 0.1f);
    spBC.r = camera->dist = Camera_LERPCeilF(spF4, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
    OLib_Vec3fDiffToVecSphGeo(&spAC, sp4C, &sp40->pos);

    spAC.r = spBC.r - (((spAC.r >= spBC.r) ? spBC.r : spAC.r) * 0.5f);

    if (anim->unk_1A & 0x1000) {
        spFC = 15.0f;
    } else {
        spFC = batt1->unk_0C + ((batt1->unk_10 - batt1->unk_0C) * (1.1f - spEC));
    }
    spBC.yaw = sp94.yaw;
    temp_v0_5 = (sp94.yaw + 0x8000);
    temp_v0_5 = spAC.yaw - temp_v0_5;
    if (anim->unk_16 != 0) {
        if (anim->unk_16 > 0) {
            sp86 = anim->unk_16 - 1;
            OLib_Vec3fDiffToVecSphGeo(&spB4, sp4C, sp50);
            spB4.yaw = sp88 + 0x8000;
            new_var = (anim->unk_00 - spB4.r) * 0.16666667f;
            sp8A = (s16)(anim->unk_12 - spB4.yaw) * 0.16666667f;
            sp88 = (s16)(anim->unk_14 - spB4.pitch) * 0.16666667f;
            spBC.r = Camera_LERPCeilF((sp86 * new_var) + spB4.r, sp9C.r, 0.5f, 1.0f); // TODO: extra float calcs going on here
            spBC.yaw = Camera_LERPCeilS(spB4.yaw + (sp8A * sp86), sp9C.yaw, 0.5f, 5);
            spBC.pitch = Camera_LERPCeilS(spB4.pitch + (sp88 * sp86), sp9C.pitch, 0.5f, 5);
        } else {
            spF0 = true;
        }
        anim->unk_16--;
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
        new_var4 = spAC.pitch * batt1->unk_1C;
        temp_v0_6 = ((s16)(((((sp7C - sp80) * spEC) + sp80) * 182.04167f) + .5f) - (s16)((spA4.pitch * (0.5f + (spEC * 0.5f))) + 0.5f));
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
            if (!(batt1->unk_30 & 0x10)) {
                if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (batt1->unk_30 & 1)) {
                    if (func_800CBC84(camera, sp4C, &spC4, 0) != 0) {
                        anim->unk_1A |= 0x1000;
                    } else {
                        anim->unk_1A &= ~0x1000;
                    }
                } else if (batt1->unk_30 & 2) {
                    func_800CBC84(camera, sp4C, &spC4, 3);
                } else {
                    OLib_Vec3fDistNormalize(&sp114, sp4C, &spC4);
                    spC4.x -= sp114.x;
                    spC4.y -= sp114.y;
                    spC4.z -= sp114.z;
                }
                *sp50 = spC4;;
                anim->unk_1A &= ~0x10;
            } else if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || ((batt1->unk_30 & 1) != 0)) {
                if (func_800CBC84(camera, sp4C, &spC4, 0) != 0) {
                    anim->unk_1A |= 0x1000;
                    spF8 = OLib_Vec3fDist(sp4C, sp8C);
                    spF4 = OLib_Vec3fDist(sp4C, &spC4);
                    if (anim->unk_1A & 0x10) {
                        phi_f0_3 = 40.0f;
                    } else {
                        phi_f0_3 = 0.0f;
                    }
                    spF8 = spF8 + phi_f0_3;
                    func_800B8898(camera->globalCtx, camera->player, &sp5E, &sp5C);
                    if ((spF4 < spF8) ||((sp5E >= 0) && (sp5E < 0x141) && (sp5C >= 0) && (sp5C < 0xF1)) ) {
                            anim->unk_1A |= 0x10;
                            spB4.yaw = spA4.yaw + 0x8000;
                            spB4.pitch = -spA4.pitch;
                            spB4.r = 40.0f;
                            sp114 = sp8C->pos;
                            sp114.y += 40.0f;
                            OLib_VecSphAddToVec3f(&sp120, &sp114, &spB4);
                            Camera_LERPCeilVec3f(&sp120, sp50, 0.15f, 0.15f, 0.2f);
                    } else if (anim->unk_1A & 0x10) {
                        if (OLib_Vec3fDist(&spC4, sp50) < 20.0f) {
                            anim->unk_1A &= ~0x10;
                            *sp50 = spC4;
                        } else {
                            Camera_LERPCeilVec3f(&spC4, sp50, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        anim->unk_1A &= ~0x10;
                        *sp50 = spC4;
                    }
                    dummy:; // TODO: Is Needed?
                } else {
                    if (anim->unk_1A & 0x10) {
                        if (OLib_Vec3fDist(&spC4, sp50) < 20.0f) {
                            anim->unk_1A &= ~0x10;
                            *sp50 = spC4;
                        } else {
                            Camera_LERPCeilVec3f(&spC4, sp50, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        anim->unk_1A &= ~0x10;
                        *sp50 = spC4;
                    }
                    anim->unk_1A &= ~0x1000;
                }
            } else if (batt1->unk_30 & 2) {
                anim->unk_1A &= ~0x10;
                if (func_800CBC84(camera, sp4C, &spC4, 3) != 0) {
                    *sp50 = spC4;
                } else {
                    *sp50 = spC4;
                }
            } else {
                anim->unk_1A &= ~0x10;
                OLib_Vec3fDistNormalize(&sp114, sp4C, &spC4);
                spC4.x -= sp114.x;
                spC4.y -= sp114.y;
                spC4.z -= sp114.z;
                *sp50 = spC4;
            }
        } else {
            anim->unk_1A &= ~0x10;
            *sp50 = *sp48;
        }
    }

    if (anim->unk_16 != 0) {
        sp88 = 0;
    } else {
        sp88 = (s16)(sp94.yaw - spBC.yaw) * 0.50f;
    }

    camera->roll = Camera_LERPCeilS(sp88, camera->roll, 0.06f, 5);
    if (func_800CBAAC(camera) != 0) {
        if ((camera->globalCtx->state.frames & 8) != 0) {
            phi_f12 = batt1->unk_20 - (batt1->unk_20 * 0.5f);
        } else {
            phi_f12 = batt1->unk_20;
        }
    } else {
        if (gSaveContext.health <= 16) {
            phi_f0_4 = 0.8f;
        } else {
            phi_f0_4 = 1.0f;
        }
        phi_f12 = phi_f0_4 * (sp78 - (sp78 * 0.05f * spEC));
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

#ifdef NON_EQUIVALENT
s32 Camera_KeepOn1(Camera *camera) {
    f32 pad1;
    f32* pad2;
    Vec3f *sp48 = &camera->eye;
    Vec3f *sp44 = &camera->at;
    Vec3f *sp40 = &camera->eyeNext;
    Vec3f sp130;
    Vec3f sp124;
    Vec3f sp118;
    f32 sp114;
    PosRot *sp3C = &camera->trackActorPosRot;
    PosRot *sp30 = &camera->targetPosRot;
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
    PosRot *spA4;
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
    KeepOn1* keep1 = (KeepOn1*)camera->paramData;
    KeepOn1Anim* anim = &keep1->anim;
    s16 temp_v0_3;
    s16 new_var4;



    spA4 = &((Actor*)camera->trackActor)->focus;
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
        keep1->unk_00 = NEXTPCT * temp_f0 * (0.8f - ((68.0f / temp_f0) * -0.2f));
        keep1->unk_04 = NEXTSETTING;
        keep1->unk_08 = NEXTSETTING;
        keep1->unk_0C = NEXTSETTING;
        keep1->unk_10 = NEXTSETTING;
        keep1->unk_14 = NEXTSETTING;
        keep1->unk_14 = 40.0f - (40.0f - keep1->unk_14);
        keep1->unk_18 = NEXTSETTING;
        keep1->unk_18 = 20.0f - (20.0f - keep1->unk_18);
        // keep1->unk_18 = keep1->unk_18; // TODO: Fake
        // if (!keep1->unk_08) {}
        keep1->unk_1C = NEXTPCT;
        keep1->unk_1C = 1.000f - (1.00f - keep1->unk_1C); // TODO: Necessary?
        keep1->unk_20 = NEXTSETTING;
        keep1->unk_24 = NEXTPCT;
        keep1->unk_24 = 1.0f - (1.0f - keep1->unk_24);
        keep1->unk_2C = NEXTSETTING;
        keep1->unk_28 = NEXTPCT;
        keep1->unk_28 = 0.2f - (0.2f - keep1->unk_28);
    }

    sp60 = temp_f0;
    sp114 = keep1->unk_00; // TODO: likely fake temp
    sp60 += sp114;
    OLib_Vec3fDiffToVecSphGeo(&spC8, sp44, sp48);
    OLib_Vec3fDiffToVecSphGeo(&spC0, sp44, sp40);
    sCameraInterfaceFlags = keep1->unk_2C;


    if (RELOAD_PARAMS) {
        camera->animState++;
        anim->unk_18 = 0;
        anim->unk_10 = 0;
        anim->unk_04 = 0.0f;
        anim->unk_0C = camera->target;
        anim->unk_16 = 7;
        anim->unk_12 = spC8.yaw;
        anim->unk_14 = spC8.pitch;
        anim->unk_00 = spC8.r;
        anim->unk_08 = sp3C->pos.y - camera->playerPosDelta.y;
        if ((2.0f * keep1->unk_04) < camera->dist) {
            camera->dist = 2.0f * keep1->unk_04;
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
        anim->unk_08 = sp3C->pos.y;
    }
    
    sp114 = keep1->unk_04;

    if (camera->target->id != ACTOR_EN_BOOM) {
        Actor_GetWorldPosShapeRot(sp30, camera->target);
        Actor_GetFocus(&spA8, camera->target);
        camera->targetPosRot.pos.y = spA8.y;
    } else {
        Actor_GetFocus(sp30, camera->target);
    }
    if (anim->unk_0C != camera->target) {
        anim->unk_0C = camera->target;
        camera->atLERPStepScale = 0.0f;
    }

    camera->yOffsetUpdateRate = Camera_LERPCeilF(1.0f, camera->yOffsetUpdateRate, camera->speedRatio * 0.5f, 0.0001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(1.0f, camera->xzOffsetUpdateRate, camera->speedRatio * 0.2f, 0.0001f);
    // TODO: No f on 0.05?
    camera->fovUpdateRate = Camera_LERPCeilF(0.05, camera->fovUpdateRate, camera->speedRatio * 0.05f, 0.0001f);

    if (func_800CB950(camera)) {
        anim->unk_08 = sp3C->pos.y;
        sp70 = false;
    } else {
        sp70 = true;
    }


    Camera_CalcAtForLockOn(camera, &spC0, sp30, keep1->unk_00, keep1->unk_08, &anim->unk_08, &spD0, keep1->unk_2C | (sp70 ? 0x80 : 0));
    sp124 = sp3C->pos;
    sp124.y += sp60;
    OLib_Vec3fDiffToVecSphGeo(&spD0, &sp124, sp30);

    if (sp114 < spD0.r) {
        sp74 = 1.0f;
    } else {
        sp74 = spD0.r / sp114;
    }

    OLib_Vec3fDiffToVecSphGeo(&spE8, sp44, sp40);

    if (spE8.r < keep1->unk_04) {
        sp114 = keep1->unk_04;
        spF8 = 20.0f;
    } else if (keep1->unk_08 < spE8.r) {
        sp114 = keep1->unk_08;
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
    if (1) { } if (1) { } if (1) { } // TODO: Is needed?
    pad1 = spD8.r; // TODO: Fake temp?
    spD8.r = spF8 - (((pad1 <= spF8) ? spD8.r : spF8) * .5f);
    camera->dist = Camera_LERPCeilF(pad1, camera->dist, 0.06f, 0.1f);
    spE8.r = camera->dist;
    spFC = keep1->unk_0C + ((keep1->unk_10 - keep1->unk_0C) * (1.1f - sp74));
    spE8.yaw = spC0.yaw;
    temp_v0_3 = (s16)(spD8.yaw - (s16)(spC0.yaw + 0x8000));
    if (anim->unk_16 != 0) {
        if (anim->unk_16 > 0) {
            sp72 = anim->unk_16 - 1;
            spF2 = spD0.yaw;
            OLib_Vec3fDiffToVecSphGeo(&spD0, sp44, sp48);
            spD0.yaw = (s16)(spF2 + 0x8000);
            sp60 = (anim->unk_00 - spD0.r) * 0.16666667f;
            spF2 = (s16)(anim->unk_12 - (s16)(spF2 + 0x8000)) * 0.16666667f;
            spF0 = ((s16)(anim->unk_14 - (s64)spD0.pitch)); // TODO: s16 cast on F0
            spF0 = (s16)(spF0 * 0.16666667f);
            spE8.r = Camera_LERPCeilF(spD0.r + (sp60 * sp72), spC8.r, .5f, 0.1f);
            spE8.yaw = Camera_LERPCeilS(spD0.yaw + (spF2 * sp72), spC8.yaw, .5f, 5);
            spE8.pitch = Camera_LERPCeilS(spD0.pitch + (spF0 * sp72), spC8.pitch, .5f, 5);
        }
        sp78 = 1;
        anim->unk_16--;
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
        phi_a0 = (s16)(((keep1->unk_14 + ((keep1->unk_18 - keep1->unk_14) * sp74)) * 182.04167f) + .5f);
        phi_a0 -= (s16)((spD0.pitch * (0.5f + (sp74 * 0.5f))) + 0.5f);
        if (1) {} // TODO: Needed?
        sp60 = spD8.pitch * keep1->unk_1C; // TODO: Fake sp60 temp?
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
            if (!(keep1->unk_2C & 0x10)) {
                if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (keep1->unk_2C & 1)) {
                    if (func_800CBC84(camera, sp44, &sp7C, 0) != 0) {
                        anim->unk_18 |= 0x1000;
                    } else {
                        anim->unk_18 &= ~0x1000;
                    }
                } else if (keep1->unk_2C & 2) {
                    func_800CBC84(camera, sp44, &sp7C, 3);
                } else {
                    OLib_Vec3fDistNormalize(&sp130, sp44, &sp7C.pos);
                    sp7C.pos.x -= sp130.x;
                    sp7C.pos.y -= sp130.y;
                    sp7C.pos.z -= sp130.z;
                }
                *sp48 = sp7C.pos;
                anim->unk_18 &= ~0x10;
            } else if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (keep1->unk_2C & 1)) {
                if (func_800CBC84(camera, sp44, &sp7C, 0) != 0) {
                    anim->unk_18 |= 0x1000;
                    spF8 = OLib_Vec3fDist(sp44, spA4);
                    spF4 = OLib_Vec3fDist(sp44, &sp7C.pos);
                    spF8 += (anim->unk_18 & 0x10) ? 40 : 0.0f; // TODO: 40.0f?
                    func_800B8898(camera->globalCtx, camera->player, &sp56, &sp54);
                    if ((spF4 < spF8) || ((sp56 >= 0) && (sp56 <= 320) && (sp54 >= 0) && (sp54 <= 240))) {
                        anim->unk_18 |= 0x10;
                        spE0.yaw = (s16)(spD0.yaw + 0x8000);
                        spE0.pitch = -spD0.pitch;
                        spE0.r = 40.0f;
                        sp130 = spA4->pos;
                        sp130.y += 40.0f;
                        OLib_VecSphAddToVec3f(&sp124, &sp130, &spE0);
                        Camera_LERPCeilVec3f(&sp124, sp48, 0.15f, 0.15f, 0.2f);
                    } else if (anim->unk_18 & 0x10) {
                        if (OLib_Vec3fDist(&sp7C.pos, sp48) < 20.0f) {
                            anim->unk_18 &= ~0x10;
                            *sp48 = sp7C.pos;
                        } else {
                            Camera_LERPCeilVec3f(&sp7C.pos, sp48, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        anim->unk_18 &= ~0x10;
                        *sp48 = sp7C.pos;
                    }
                    dummy:; // TODO: Is this needed?
                } else {
                    if (anim->unk_18 & 0x10) {
                        if (OLib_Vec3fDist(&sp7C.pos, sp48) < 20.0f) {
                            anim->unk_18 &= ~0x10;
                            *sp48 = sp7C.pos;
                        } else {
                            Camera_LERPCeilVec3f(&sp7C.pos, sp48, 0.15f, 0.15f, 0.2f);
                        }
                    } else {
                        anim->unk_18 &= ~0x10;
                        *sp48 = sp7C.pos;
                        // if (sp104) {} // TODO: Is this needed?
                    }
                    anim->unk_18 &= ~0x1000;
                }
            } else if (keep1->unk_2C & 2) {
                anim->unk_18 &= ~0x10;
                if (func_800CBC84(camera, sp44, &sp7C, 3) != 0) {
                    *sp48 = sp7C.pos;
                } else {
                    *sp48 = sp7C.pos;;
                }
            } else {
                anim->unk_18 &= ~0x10;
                OLib_Vec3fDistNormalize(&sp130, sp44, &sp7C.pos);
                sp7C.pos.x -= sp130.x;
                sp7C.pos.y -= sp130.y;
                sp7C.pos.z -= sp130.z;
                *sp48 = sp7C.pos;
                
            }
        } else {
            anim->unk_18 &= ~0x10;
            *sp48 = *sp40;
        }
    }

    // TODO: spF8 temp needed?
    camera->fov = Camera_LERPCeilF(spF8 = keep1->unk_20, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.2f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, sp70 ? keep1->unk_28 : keep1->unk_24);
    
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn1.s")
#endif

s32 Camera_KeepOn2(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_KeepOn3(Camera* camera) {
    Vec3f* sp48 = &camera->eye;
    s32 temp_f0;
    Vec3f* pad = &camera->eyeNext;
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
    Vec3f* temp_s0 = &camera->at;
    s32 sp78;
    f32 phi_f14;
    PosRot* sp70;
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 phi_a3;
    KeepOn3* keep3 = (KeepOn3*)camera->paramData;
    PosRot* sp3C = &camera->trackActorPosRot;
    KeepOn3Anim* anim = &keep3->anim;
    f32 sp58;
    s32 i;

    sp70 = &((Actor*)camera->trackActor)->focus; // TODO: Move above?
    sp6A = 0;
    sp58 = Camera_GetTrackedActorHeight(camera);

    if ((camera->target == NULL) || (camera->target->update == NULL)) {
        camera->target = NULL;
        Camera_ChangeMode(camera, CAM_MODE_TARGET);
        return 1;
    }

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        if (camera->globalCtx->view.unk164 == 0) {
            Camera_SetFlags(camera, 0x20);
            camera->globalCtx->view.unk164 = camera->camId | 0x50;
            return 1;
        }
        Camera_UnsetFlags(camera, 0x20);
    }

    Camera_UnsetFlags(camera, 0x10);
    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        keep3->unk_00 = NEXTSETTING * 0.01f * sp58 * (0.8f - ((68.0f / sp58) * -0.2f));
        keep3->unk_04 = NEXTSETTING;
        keep3->unk_08 = NEXTSETTING;
        keep3->unk_0C = NEXTSETTING;
        keep3->unk_10 = NEXTSETTING;
        keep3->unk_14 = NEXTSETTING;
        keep3->unk_18 = NEXTSETTING;
        keep3->unk_1C = NEXTSETTING * 0.01f;
        keep3->unk_20 = NEXTSETTING;
        keep3->unk_24 = NEXTSETTING * 0.01f;
        keep3->unk_2C = NEXTSETTING;
        keep3->unk_2E = NEXTSETTING;
        keep3->unk_28 = NEXTSETTING * 0.01f;
    }

    if (camera->animState == 0xA) {
        keep3->unk_2C >>= 1;
        if (keep3->unk_2C < 0x14) {
            keep3->unk_2C = 0x14;
        }
    }

    OLib_Vec3fDiffToVecSphGeo(&sp88, temp_s0, sp48);
    OLib_Vec3fDiffToVecSphGeo(&sp80, temp_s0, pad);
    Actor_GetFocus(&camera->targetPosRot, camera->target);
    spD8 = sp3C->pos;
    spD8.y += sp58;
    OLib_Vec3fDiffToVecSphGeo(&spA0, &spD8, &camera->targetPosRot.pos);

    if (RELOAD_PARAMS) {
        camera->animState++;
        spA8[0] = camera->target;
        spA8[1] = (Actor*)camera->trackActor;
        anim->unk_0C = camera->target;
        phi_f14 = (keep3->unk_08 < spA0.r) ? 1.0f : (spA0.r / keep3->unk_08);

        anim->unk_1C = keep3->unk_2C;
        spB8 = ((1.0f - phi_f14) * spA0.r) / anim->unk_1C;

        if (keep3->unk_2E & 0x40) {
            spA0.pitch = 0;
        }

        swingAngle = F32_LERPIMP(keep3->unk_14, keep3->unk_18, phi_f14);
        sp98.pitch = DEGF_TO_BINANG(swingAngle) + ((s16)-(spA0.pitch * keep3->unk_1C));
        swingAngle = F32_LERPIMP(keep3->unk_0C, keep3->unk_10, phi_f14);
        
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
        } else if (!(keep3->unk_2E & 0x20) && (ABS((s16)(spA0.yaw - sp80.yaw)) < 0x4000)) {
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

        if (keep3->unk_28) {}
        spB4 = spA0.r;

        phi_f14 = keep3->unk_28;
        spA0.r = spB8 * phi_f14 + (spB4 * (1.0f - phi_f14));
        spD8 = sp3C->pos;
        spD8.y += sp58;

        // Camera_Vec3fVecSphGeoAdd (OoT)
        OLib_VecSphAddToVec3f(&anim->unk_10, &spD8, &spA0);
        anim->unk_10.y += keep3->unk_00;
        spA0.r = spB4;

        if (sp78 != 0) {
            sp98.r = ((keep3->unk_04 + (spA0.r * 0.5f)) - sp80.r) + sp80.r;
            i = 0;
            sp78 = 14;
            OLib_VecSphAddToVec3f(&spCC, &anim->unk_10, &sp98);
            if (!(keep3->unk_2E & 0x80)) {
                if (CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, &anim->unk_10, &spCC, spA8, 2) || Camera_BGCheck(camera, &anim->unk_10, &spCC)) {
                    sp98.yaw = sp6A;
                    OLib_VecSphAddToVec3f(&spCC, &anim->unk_10, &sp98);
                }
                while (i < sp78) {
                    if (!CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, &anim->unk_10,
                                                    &spCC, spA8, 2) &&
                        !Camera_BGCheck(camera, &anim->unk_10, &spCC)) {
                        break;
                    }
                    sp98.yaw = sp6C + D_801B9E18[i];
                    sp98.pitch = sp6E + D_801B9E34[i];
                    OLib_VecSphAddToVec3f(&spCC, &anim->unk_10, &sp98);
                    i++;
                }
            }
        }
        
        Camera_UnsetFlags(camera, 0xC);
        temp_f0 = ((anim->unk_1C + 1) * anim->unk_1C) >> 1;
        anim->unk_04 = (f32)(s16)(sp98.yaw - sp80.yaw) / temp_f0;
        anim->unk_08 = (f32)(s16)(sp98.pitch - sp80.pitch) / temp_f0;
        anim->unk_00 = (sp98.r - sp80.r) / temp_f0;
        sCameraInterfaceFlags = 0xFF00;
        return true;
    }

    sCameraInterfaceFlags = keep3->unk_2E;
    
    if (anim->unk_1C != 0) {
        temp_f0_2 = anim->unk_1C;
        temp_s0->x += (anim->unk_10.x - temp_s0->x) / temp_f0_2;
        temp_s0->y += (anim->unk_10.y - temp_s0->y) / temp_f0_2;
        temp_s0->z += (anim->unk_10.z - temp_s0->z) / temp_f0_2;
        sp98.r = (anim->unk_00 * temp_f0_2) + sp80.r + 1.0f;
        sp98.yaw = sp80.yaw + (s16)(anim->unk_04 * temp_f0_2);
        sp98.pitch = sp80.pitch + (s16)(anim->unk_08 * temp_f0_2);
        OLib_VecSphAddToVec3f(pad, temp_s0, &sp98);
        *sp48 = *pad;
        camera->fov = Camera_LERPCeilF(keep3->unk_20, camera->fov, 0.5f, 0.1f);
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, keep3->unk_24);
        func_800CBFA4(camera, temp_s0, sp48, 3);
        anim->unk_1C--;
    } else {
        Camera_SetFlags(camera, 0x400 | 0x10);
    }

    Camera_UpdateAtActorOffset(camera, &sp3C->pos);
    camera->dist = OLib_Vec3fDist(temp_s0, sp48);
    if (camera->flags2 & 8) {
        sCameraInterfaceFlags = 0;
        Camera_SetUpdateRatesSlow(camera);
        camera->atLERPStepScale = 0.0f;

        if ((camera->xzSpeed > 0.001f) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R)
            ) {
            Camera_SetFlags(camera, 0x4);
            Camera_UnsetFlags(camera, 0x8);
        }
    }

    if (anim->unk_0C != camera->target) {
        anim->unk_0C = camera->target;
        camera->animState = 10;
    }

    return true;

}

s32 Camera_KeepOn4(Camera* camera) {
    KeepOn4* keep4 = (KeepOn4*)camera->paramData;
    f32 new_var;
    Vec3f* sp44_2 = &camera->eye;
    Actor* spCC[2];
    Vec3f* sp40 = &camera->at;
    Vec3f* sp3C = &camera->eyeNext;
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
    f32 temp_f0_2;
    KeepOn4Anim* anim = &keep4->anim;
    f32 sp88;
    s32 sp84; // bgId
    s16 sp82; // mode
    Player* player;
    Vec3f* data;
    CameraModeValue* values;
    PosRot sp60;
    PosRot sp4C;

    if (RELOAD_PARAMS) {
        if (camera->globalCtx->view.unk164 == 0) {
            Camera_SetFlags(camera, 0x20);
            Camera_UnsetFlags(camera, 0x4 | 0x2);
            camera->globalCtx->view.unk164 = camera->camId | 0x50;
            return true;
        }
        anim->unk_18 = *sp44;
        Camera_UnsetFlags(camera, 0x20);
    }

    if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        player = (Player*)camera->trackActor;
        switch (((Player*)camera->trackActor)->transformation) {
            case PLAYER_FORM_DEKU:
                sp82 = CAM_MODE_DEKUSHOT;
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

        sp88 = Camera_GetTrackedActorHeight(camera) - (player->unk_AB8 * ((Actor*)camera->trackActor)->scale.y);
    } else {
        sp82 = CAM_MODE_NORMAL;
        sp88 = Camera_GetTrackedActorHeight(camera);
    }

    if (anim->unk_18 != *sp44) {
        camera->animState = 20;
        Camera_SetFlags(camera, 0x20);
        Camera_UnsetFlags(camera, 0x4 | 0x2);
        camera->globalCtx->view.unk164 = camera->camId | 0x50;
        return true;
    }

    Camera_UnsetFlags(camera, 0x10);
    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[sp82].values;
        new_var = -0.5f;
        keep4->unk_00 = NEXTPCT * sp88 * ((1.0f + new_var) - ((68.0f / sp88) * new_var));
        keep4->unk_04 = NEXTPCT * sp88 * ((1.0f + new_var) - ((68.0f / sp88) * new_var));
        keep4->unk_08 = NEXTSETTING;
        keep4->unk_0C = NEXTSETTING;
        keep4->unk_10 = NEXTSETTING;
        keep4->unk_18 = NEXTSETTING;
        keep4->unk_1C = NEXTSETTING;
        keep4->unk_14 = NEXTPCT;
        keep4->unk_1E = NEXTSETTING;
    }

    sUpdateCameraDirection = 1;
    sCameraInterfaceFlags = keep4->unk_1C;
    OLib_Vec3fDiffToVecSphGeo(&spB0, sp40, sp44_2);
    data = &D_801EDDD0;
    OLib_Vec3fDiffToVecSphGeo(&spA8, sp40, sp3C);
    D_801EDDD0 = sp38->pos;
    D_801EDDD0.y = data->y + sp88;
    temp_f0_2 = func_800C4488(&camera->globalCtx->colCtx, &spC0, &sp84, &D_801EDDD0);
    if ((keep4->unk_00 + data->y) < temp_f0_2) {
        D_801EDDD0.y = temp_f0_2 + 10.0f;
    } else {
        D_801EDDD0.y = keep4->unk_00 + data->y;
    }
    if (keep4->unk_10 != 0.0f) {
        D_801EDDE0 = (*data);
        spB8.r = keep4->unk_10;
        spB8.pitch = 0;
        spB8.yaw = sp38->rot.y;
        OLib_VecSphAddToVec3f(&D_801EDDD0, &D_801EDDD0, &spB8);
    }

    sp9C = 0;
    switch (camera->animState) {
        case 0:
        case 0x14:
            spCC[sp9C] = (Actor*)camera->trackActor;
            sp9C++;
            Camera_SetUpdateRatesFastPitch(camera);
            Camera_UnsetFlags(camera, 6);
            anim->unk_14 = keep4->unk_1E;
            anim->unk_08 = sp38->pos.y - camera->playerPosDelta.y;

            switch (keep4->unk_1C & (0x8 | 0x4 | 0x2)) {
                case 0x2:
                    spA2 = DEGF_TO_BINANG(keep4->unk_08);
                    spA0 = SUB16(BINANG_ROT180(sp38->rot.y), spA8.yaw) < 0
                           ? BINANG_ROT180(sp38->rot.y) + DEGF_TO_BINANG(keep4->unk_0C)
                           : BINANG_ROT180(sp38->rot.y) - DEGF_TO_BINANG(keep4->unk_0C);
                    break;
                case (0x8 | 0x4):
                    spA2 = DEGF_TO_BINANG(keep4->unk_08);
                    pad1 = BINANG_ROT180(sp38->rot.y);
                    spA0 = pad1 + DEGF_TO_BINANG(keep4->unk_0C);
                    break;
                case 0x4:
                    spA2 = DEGF_TO_BINANG(keep4->unk_08);
                    spA0 = DEGF_TO_BINANG(keep4->unk_0C);
                    break;
                case (0x4 | 0x2):
                    spA2 = spA8.pitch + DEGF_TO_BINANG(keep4->unk_08);
                    spA0 = spA8.yaw + DEGF_TO_BINANG(keep4->unk_0C);
                    break;
                case 0x8:
                    if (camera->target != NULL) {
                        Actor_GetWorldPosShapeRot(&sp60, camera->target);
                        spA2 = DEGF_TO_BINANG(keep4->unk_08) - sp60.rot.x;
                        spA0 = (SUB16(BINANG_ROT180(sp60.rot.y), spA8.yaw) > 0) 
                                ? BINANG_ROT180(sp60.rot.y) + DEGF_TO_BINANG(keep4->unk_0C)
                                : BINANG_ROT180(sp60.rot.y) - DEGF_TO_BINANG(keep4->unk_0C);
                        
                        spCC[1] = camera->target;
                        sp9C++;
                        break;
                    }
                case (0x8 | 0x2):
                    if (camera->target != 0) {
                        Actor_GetWorld(&sp4C, camera->target);
                        spA2 = DEGF_TO_BINANG(keep4->unk_08);
                        sp9E = Camera_XZAngle(&sp4C.pos, &sp38->pos);
                        spA0 = (SUB16(sp9E, spA8.yaw) > 0) 
                                ? sp9E + DEGF_TO_BINANG(keep4->unk_0C)
                                : sp9E - DEGF_TO_BINANG(keep4->unk_0C);
                        spCC[1] = camera->target;
                        sp9C++;
                        break;
                    } 
                case (0x8 | 0x4 | 0x2):
                    spA2 = DEGF_TO_BINANG(keep4->unk_08);
                    spA0 = spA8.yaw;
                    break;
                default:
                    spA2 = spA8.pitch;
                    spA0 = spA8.yaw;
                    break;
            }

            spB8.pitch = spA2;
            spB8.yaw = spA0;
            spB8.r = keep4->unk_04;
            sp84 = func_800CC260(camera, &D_801EDDF0, &D_801EDDD0, &spB8, spCC, sp9C);
            anim->unk_04 = (f32)(s16)(spB8.pitch - spA8.pitch) / anim->unk_14;
            anim->unk_00 = (f32)(s16)(spB8.yaw - spA8.yaw) / anim->unk_14;
            anim->unk_10 = spA8.yaw;
            anim->unk_12 = spA8.pitch;
            camera->animState++;
            anim->unk_16 = 1;
            break;

        case 0xA:
            anim->unk_08 = sp38->pos.y - camera->playerPosDelta.y;
            break;
    }

    if (keep4->unk_1C & 0x40) {
        if (anim->unk_14 != 0) {
            sp40->x += ((data->x - sp40->x) / anim->unk_14);
            sp40->y += ((data->y - sp40->y) / anim->unk_14);
            sp40->z += ((data->z - sp40->z) / anim->unk_14);
            Camera_UpdateAtActorOffset(camera, &sp38->pos);
        }
        camera->yOffsetUpdateRate = 0.25f;
        camera->xzOffsetUpdateRate = 0.25f;
        camera->atLERPStepScale = 0.0f;
    } else {
        camera->yOffsetUpdateRate = 0.25f;
        camera->xzOffsetUpdateRate = 0.25f;
        camera->atLERPStepScale = 0.75f;
        Camera_LERPCeilVec3f(data, sp40, 0.2f, 0.2f, 0.2f);
        camera->atLERPStepScale = 0.0f;
        Camera_UpdateAtActorOffset(camera, &sp38->pos);
    }
    camera->dist = Camera_LERPCeilF(keep4->unk_04, camera->dist, 0.25f, 1.0f);
    spB8.r = camera->dist;
    if (anim->unk_14 != 0) {
        Camera_SetFlags(camera, 0x20);
        anim->unk_10 += (s16)anim->unk_00;
        anim->unk_12 += (s16)anim->unk_04;
        anim->unk_14--;
    } else {
        Camera_SetFlags(camera, 0x400 | 0x10);
    }
    spB8.yaw = Camera_LERPCeilS(anim->unk_10, spA8.yaw, keep4->unk_14, 5);
    spB8.pitch = Camera_LERPCeilS(anim->unk_12, spA8.pitch, keep4->unk_14, 5);
    OLib_VecSphAddToVec3f(sp3C, sp40, &spB8);
    *sp44_2 = *sp3C;
    func_800CBFA4(camera, sp40, sp44_2, 3);
    camera->fov = Camera_LERPCeilF(keep4->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    return true;

}

s32 Camera_KeepOn0(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Fixed1(Camera *camera) {
    Fixed1* fixd1 = (Fixed1*)camera->paramData;
    s32 pad3;
    s32 yawDiff;
    VecSph eyeOffset;
    VecSph eyeAtOffset;
    VecSph sp7C;
    u32 negOne;
    Vec3f adjustedPos;
    SubBgCamData* bgCamData;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    f32 playerHeight = Camera_GetTrackedActorHeight(camera);
    CameraModeValue* values;
    PosRot* sp50;
    PosRot* sp4C;
    VecSph sp44;
    Fixed1Anim* anim = &fixd1->anim;
    s32 pad2;

    OLib_Vec3fDiffToVecSphGeo(&sp7C, at, eye);

    if (!RELOAD_PARAMS) {
        // Pass
    } else {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values; // sp54
        bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
        Camera_Vec3sToVec3f(&anim->eyePosRotTarget.pos, &bgCamData->pos);

        anim->eyePosRotTarget.rot = bgCamData->rot;
        anim->fov = bgCamData->fov;
        anim->trackActor = camera->trackActor;

        fixd1->unk_00 = NEXTPCT * playerHeight;
        fixd1->jfifId = NEXTPCT;
        fixd1->fov = NEXTSETTING;
        fixd1->interfaceFlags = NEXTSETTING;

        if (fixd1->interfaceFlags & 0x10) {
            if (camera->target == NULL) {
                return false;
            }

            sp50 = &camera->target->home;
            sp4C = &camera->target->world;

            OLib_Vec3fDiffToVecSphGeo(&sp44, &sp50->pos, &anim->eyePosRotTarget.pos);
            sp44.yaw = sp4C->rot.y + (s16)(sp44.yaw - sp50->rot.y);
            OLib_VecSphAddToVec3f(&anim->eyePosRotTarget.pos, &sp4C->pos, &sp44);
            yawDiff = (s16)(anim->eyePosRotTarget.rot.y - sp50->rot.y);
            anim->eyePosRotTarget.rot.y = sp4C->rot.y + yawDiff;
        }
    }

    negOne = -1;

    if (anim->trackActor != camera->trackActor) {
        camera->animState = 20;
    }

    if (anim->fov == (s32)negOne) {
        anim->fov = fixd1->fov * 100;
    } else if (anim->fov <= 360) {
        anim->fov *= 100;
    }

    sCameraInterfaceFlags = fixd1->interfaceFlags;

    if (camera->animState == 0) {
        camera->animState++;
        Camera_SetUpdateRatesSlow(camera);
        if (anim->fov != (s32)negOne) {
            fixd1->fov = PCT(anim->fov);
        }

        if (bgCamData->unk_0E != (s32)negOne) {
            fixd1->jfifId = PCT(bgCamData->unk_0E);
        }
    }

    OLib_Vec3fDiffToVecSphGeo(&eyeAtOffset, eye, at);
    Camera_LERPCeilVec3f(&anim->eyePosRotTarget.pos, eye, fixd1->jfifId, fixd1->jfifId, 0.2f);
    adjustedPos = playerPosRot->pos;
    adjustedPos.y += playerHeight;
    camera->dist = OLib_Vec3fDist(&adjustedPos, eye);
    eyeOffset.r = camera->dist;
    eyeOffset.pitch = Camera_LERPCeilS(anim->eyePosRotTarget.rot.x * -1, eyeAtOffset.pitch, fixd1->jfifId, 5);
    eyeOffset.yaw = Camera_LERPCeilS(anim->eyePosRotTarget.rot.y, eyeAtOffset.yaw, fixd1->jfifId, 5);
    OLib_VecSphAddToVec3f(at, eye, &eyeOffset);
    camera->eyeNext = *eye;
    Camera_BGCheck(camera, eye, at);
    camera->fov = Camera_LERPCeilF(fixd1->fov, camera->fov, fixd1->jfifId, 0.1f);
    camera->roll = 0;
    camera->atLERPStepScale = 0.0f;
    Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    camera->roll = Camera_LERPCeilS(anim->eyePosRotTarget.rot.z, camera->roll, fixd1->jfifId, 5);
    return true;
}

s32 Camera_Fixed2(Camera* camera) {
    Vec3f* sp40 = &camera->eye;
    Vec3f* sp3C = &camera->at;
    Vec3f* sp38 = &camera->eyeNext;
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;
    PosRot* sp34 = &camera->trackActorPosRot;
    f32 temp_f0_3;
    f32 new_var;
    SubBgCamData* bgCamData;
    VecSph sp80;
    PosRot* sp7C;
    PosRot* sp78;
    VecSph sp70;
    Fixed2* fixd2 = (Fixed2*)camera->paramData;
    Fixed2Anim* anim = &fixd2->anim;
    CameraModeValue* values;
    f32 sp60;
    Vec3f* new_var1;
    Vec3f* new_var2;
    Player* player;
    Actor* actor;
    Vec3f sp44;

    anim = anim; // TODO: Is needed?

    sp60 = Camera_GetTrackedActorHeight(camera);

    if (!RELOAD_PARAMS) {
    } else {
        if (new_var2) {}
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixd2->unk_00 = NEXTPCT * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        fixd2->unk_04 = NEXTSETTING;
        fixd2->unk_08 = NEXTSETTING;
        fixd2->unk_0C = NEXTPCT;
        fixd2->unk_10 = NEXTPCT;
        fixd2->unk_14 = NEXTSETTING;
        fixd2->unk_18 = NEXTSETTING;
        anim->unk_1C = fixd2->unk_14 * 100.0f;
        bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
        if (bgCamData != NULL) {
            if ((fixd2->unk_18 & 2) == 0) {
                Camera_Vec3sToVec3f(&anim->unk_00, &bgCamData->pos);
            } else {
                if ((Actor*)camera->trackActor !=  camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
                    player = (Player*)camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first;
                    OLib_Vec3fDiffToVecSphGeo(&sp70, &player->actor.focus.pos, sp40);
                    if (sp70.r < fixd2->unk_04) {
                        sp70.r = fixd2->unk_04;
                        if (sp70.pitch < 0xBB8) { // 16.5 degrees
                            sp70.pitch = 0xBB8;
                        }

                        new_var1 = &player->actor.focus.pos;

                        OLib_VecSphAddToVec3f(&anim->unk_00, new_var1, &sp70);
                    } else {
                        anim->unk_00 = *sp40;
                        dummy:; // TODO: Needed?
                    }
                } else {
                    anim->unk_00 = camera->eye;
                }
            }

            if (bgCamData->fov != -1) {
                if (fixd2->unk_18 & 0x80) {
                    anim->unk_1C = (bgCamData->fov >> 1) + (bgCamData->fov >> 2);
                    if (anim->unk_1C < 0x1E) {
                        anim->unk_1C = 0x1E;
                    }
                } else {
                    anim->unk_1C = bgCamData->fov;
                }
            }

            if (bgCamData->unk_0E != -1) {
                anim->unk_0C = bgCamData->unk_0E;
            } else {
                anim->unk_0C = fixd2->unk_08;
            }

            if (bgCamData->unk_10 != -1) {
                if (fixd2->unk_18 & 4) {
                    anim->unk_14 = bgCamData->unk_10 * 0.01f;
                    anim->unk_18 = fixd2->unk_0C;
                } else {
                    temp_f0_3 = bgCamData->unk_10 * 0.01f;
                    anim->unk_18 = temp_f0_3;
                    anim->unk_14 = temp_f0_3;
                }
            } else {
                anim->unk_14 = fixd2->unk_10;
                anim->unk_18 = fixd2->unk_0C;
            }
            if (fixd2->unk_18 & 0x10) {
                if (camera->target == 0) {
                    return 0;
                }
                sp7C = &camera->target->home;
                sp78 = &camera->target->world;
                OLib_Vec3fDiffToVecSphGeo(&sp70, &sp7C->pos, &anim->unk_00);
                sp70.yaw = sp78->rot.y + (s16)(sp70.yaw - sp7C->rot.y);
                OLib_VecSphAddToVec3f(&anim->unk_00, &sp78->pos, &sp70);
            }
        } else {
            anim->unk_00 = camera->eye;
            anim->unk_0C = fixd2->unk_08;
            anim->unk_14 = fixd2->unk_10;
            anim->unk_18 = fixd2->unk_0C;
        }
        if (anim->unk_1C <= 360) {
            anim->unk_1C *= 100;
        }
        if (camera->animState == 20) {
            anim->unk_14 = 0.2f;
        }
        if (1) {}
    }

    sCameraInterfaceFlags = fixd2->unk_18;    
    new_var = 0.0f; // TODO: Fake temp?

    if (fixd2->unk_18 & 8) {
        if (camera->target == NULL) {
            return false;
        }

        spB0.x = camera->target->focus.pos.x;
        spB0.y = camera->target->focus.pos.y;
        spB0.z = camera->target->focus.pos.z;
        camera->atActorOffset.x = spB0.x - sp34->pos.x;
        camera->atActorOffset.y = spB0.y - sp34->pos.y;
        camera->atActorOffset.z = spB0.z - sp34->pos.z;
    } else if (fixd2->unk_18 & 0x40) {
        sp98.x = new_var;
        sp98.y = fixd2->unk_00 + sp60;
        sp98.z = new_var;

        if (camera->target != NULL) {
            new_var1 = &((Actor*)camera->trackActor)->focus.pos;
            new_var2 = &camera->target->focus.pos;
            sp98.x = ((void)0, new_var) + ((new_var2->x - new_var1->x) * 0.4f);
            sp98.y += (new_var2->y - new_var1->y) * 0.4f;
            sp98.z = ((void)0, new_var) + ((new_var2->z - new_var1->z) * 0.4f);
        }

        Camera_LERPCeilVec3f(&sp98, &camera->atActorOffset, 0.25f, 0.25f, 0.1f);
        spB0.x = sp34->pos.x + camera->atActorOffset.x;
        spB0.y = sp34->pos.y + camera->atActorOffset.y;
        spB0.z = sp34->pos.z + camera->atActorOffset.z;
    } else if (fixd2->unk_18 & 0x80) {
        sp98.x = new_var;
        sp98.y = fixd2->unk_00 + sp60;
        sp98.z = new_var;
       
        if (camera->target != NULL) {
            new_var1 = &((Actor*)camera->trackActor)->focus.pos;
            new_var2 = &camera->target->focus.pos;
            sp98.x = ((void)0, new_var) + ((new_var2->x - new_var1->x)* 0.7f);
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
        if ((((Player*)camera->trackActor)->stateFlags1 & 0x4000)|| (((Player*)camera->trackActor)->stateFlags1 & 4)) {
            sp98.y = fixd2->unk_00;
        } else {
            sp98.y = fixd2->unk_00 + sp60;
        }

        Camera_LERPCeilVec3f(&sp98, &camera->atActorOffset, anim->unk_14, anim->unk_14, 0.1f);
        spB0.x = sp34->pos.x + camera->atActorOffset.x;
        spB0.y = sp34->pos.y + camera->atActorOffset.y;
        spB0.z = sp34->pos.z + camera->atActorOffset.z;
    }

    if (camera->animState == 0) {
        Camera_SetUpdateRatesSlow(camera);
        if ((fixd2->unk_18 & 1) == 0) {
            *sp3C = spB0;
            OLib_Vec3fDiffToVecSphGeo(&sp80, sp3C, &anim->unk_00);
            if ((anim->unk_0C < sp80.r) || ((fixd2->unk_18 & 0x20) != 0)) {
                sp80.r = anim->unk_0C;
                OLib_VecSphAddToVec3f(&spA4, sp3C, &sp80);
            } else {
                if (sp80.r < fixd2->unk_04) {
                    sp80.r = fixd2->unk_04;
                    OLib_VecSphAddToVec3f(&spA4, sp3C, &sp80);
                } else {
                    spA4 = anim->unk_00;
                }
            }
            sp44 = spA4;
            camera->eyeNext = sp44;
            *sp40 = sp44;
            camera->fov = anim->unk_1C * 0.01f;
        }
    }

    Camera_LERPCeilVec3f(&spB0, sp3C, anim->unk_14, anim->unk_14, 1.0f);
    OLib_Vec3fDiffToVecSphGeo(&sp80, sp3C, &anim->unk_00);
    if ((anim->unk_0C < sp80.r) || ((fixd2->unk_18 & 0x20) != 0)) {
        sp80.r = anim->unk_0C;
        OLib_VecSphAddToVec3f(&spA4, sp3C, &sp80);
    } else {
        if (sp80.r < fixd2->unk_04) {
            sp80.r = fixd2->unk_04;
            OLib_VecSphAddToVec3f(&spA4, sp3C, &sp80);
        } else {
            spA4 = anim->unk_00;
        }
    }

    Camera_LERPCeilVec3f(&spA4, sp38, anim->unk_18, anim->unk_18, 0.1f);
    *sp40 = *sp38;
    camera->dist = OLib_Vec3fDist(sp3C, sp40);
    camera->roll = 0;
    camera->xzSpeed = 0;
    anim->unk_10 = anim->unk_1C * 0.01f;
    camera->fov = Camera_LERPCeilF(anim->unk_10, camera->fov, anim->unk_14, 0.1f);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
    Camera_UpdateAtActorOffset(camera, &sp34->pos);
    camera->animState = 1;
    return true;

}

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
    Subj1* subj1 = (Subj1*)camera->paramData;
    Subj1Anim* anim = &subj1->anim; // sp28
    CameraModeValue* values;
    f32 temp_f0;
    f32 sp38;


    Actor_GetFocus(&sp58, (Actor*)camera->trackActor);
    sp38 = Camera_GetTrackedActorHeight(camera);
    Camera_SetUpdateRatesFastPitch(camera);

    values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
    subj1->unk_00 = NEXTPCT * sp38;
    subj1->unk_04 = NEXTSETTING;
    subj1->unk_08 = NEXTSETTING;
    subj1->unk_0C = NEXTSETTING;
    subj1->unk_10 = NEXTSETTING * 0.1f;
    subj1->unk_14 = NEXTSETTING * 0.1f;
    subj1->unk_18 = NEXTSETTING * 0.1f;
    subj1->unk_1C = NEXTSETTING;
    subj1->unk_20 = NEXTSETTING;

    sp7C.r = subj1->unk_08;
    sp7C.yaw = BINANG_ROT180(sp58.rot.y);
    sp7C.pitch = sp58.rot.x;
    sp90 = sp58.pos;
    sp90.y += subj1->unk_00;

    OLib_VecSphAddToVec3f(&sp84, &sp90, &sp7C);
    OLib_Vec3fDiffToVecSphGeo(&sp74, &camera->at, eye);
    sCameraInterfaceFlags = subj1->unk_20;

    if (camera->globalCtx->view.unk164 == 0) {
        camera->globalCtx->view.unk164 = camera->camId | 0x50;
        return true;
    }

    if (RELOAD_PARAMS) {
        anim->unk_00 = sp74.r;
        anim->unk_04 = sp74.yaw;
        anim->unk_06 = sp74.pitch;

        if (subj1->unk_20 & 0x10) {
            camera->fov = subj1->unk_1C;
            anim->unk_08 = 0;
        } else {
            anim->unk_08 = 6;
        }
        camera->dist = subj1->unk_08;
        camera->rUpdateRateInv = 1.0f;
        camera->animState++;
        camera->dist = subj1->unk_08;
    }


    tsph.r = anim->unk_00;
    tsph.pitch = anim->unk_04;
    tsph.yaw = anim->unk_06;

    if (anim->unk_08 != 0) {
        temp_f0 = (1.0f / anim->unk_08);

        VEC3F_LERPIMPDST(at, at, &sp90, temp_f0);

        sp54 = ((tsph.r - sp7C.r) * (1.0f / 6.0f));
        sp4E = SUB16(tsph.pitch, sp7C.yaw) * (1.0f / 6.0f);
        sp4C = SUB16(tsph.yaw, sp7C.pitch) * (1.0f / 6.0f);

        sp74.r = Camera_LERPCeilF((anim->unk_08 * sp54) + sp7C.r, sp74.r, 0.5f, 1.0f);
        sp74.yaw = Camera_LERPCeilS(sp7C.yaw + (sp4E * anim->unk_08), sp74.yaw, 0.5f, 5);
        sp74.pitch = Camera_LERPCeilS(sp7C.pitch + (sp4C * anim->unk_08), sp74.pitch, 0.5f, 5);

        OLib_VecSphAddToVec3f(eyeNext, at, &sp74);
        *eye = *eyeNext;
        anim->unk_08--;
    } else {
        sp54 = Math_SinS(-sp58.rot.x);
        temp_f0_2 = Math_CosS(-sp58.rot.x);

        sp90.x = subj1->unk_10;
        sp90.y = (subj1->unk_14 * temp_f0_2) - (subj1->unk_18 * sp54);
        sp90.z = (subj1->unk_14 * sp54) + (subj1->unk_18 * temp_f0_2);

        sp54 = Math_SinS(BINANG_ROT180(sp58.rot.y));
        temp_f0_2 = Math_CosS(BINANG_ROT180(sp58.rot.y));

        subj1->unk_10 = (sp90.z * sp54) + (sp90.x * temp_f0_2);
        subj1->unk_14 = sp90.y;
        subj1->unk_18 = (sp90.z * temp_f0_2) - (sp90.x * sp54);

        at->x = subj1->unk_10 + sp58.pos.x;
        at->y = subj1->unk_14 + sp58.pos.y;
        at->z = subj1->unk_18 + sp58.pos.z;

        sp74.r = subj1->unk_08;
        sp74.yaw = BINANG_ROT180(sp58.rot.y);
        sp74.pitch = sp58.rot.x;

        OLib_VecSphAddToVec3f(&camera->eyeNext, at, &sp74);
        sp74.r = subj1->unk_04;
        OLib_VecSphAddToVec3f(eye, at, &sp74);
    }

    // TODO: is skyboxDisabled accurate here?
    if (camera->globalCtx->envCtx.skyboxDisabled == 0) {
        Camera_BGCheck(camera, at, eye);
    } else {
        func_800CBFA4(camera, at, eye, 3);
    }

    camera->fov = Camera_LERPCeilF(subj1->unk_1C, camera->fov, 0.25f, 0.1f);
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

s32 Camera_Unique2(Camera *camera) {
    Vec3f* sp3C = &camera->eye;
    Vec3f *temp_s1 = &camera->at;
    Unique2* uniq2 = (Unique2*)camera->paramData;
    Vec3f sp70;
    VecSph sp68;
    VecSph sp60;
    f32 phi_f16;
    s32 pad[2];
    Vec3f* pad1[1];
    Unique2Anim* anim = &uniq2->anim;
    f32 sp48 = Camera_GetTrackedActorHeight(camera);
    Vec3f* sp34 = &camera->eyeNext;
    CameraModeValue* values;

    // sp48;
    OLib_Vec3fDiffToVecSphGeo(&sp60, temp_s1, sp3C);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        uniq2->unk_00 = NEXTPCT * sp48 * (0.8f - ((68.0f / sp48) * -0.2f));
        uniq2->unk_04 = NEXTSETTING;
        uniq2->unk_08 = 0.25f;
        uniq2->unk_0C = NEXTSETTING;
        uniq2->unk_10 = NEXTSETTING;
    }

    sCameraInterfaceFlags = uniq2->unk_10;

    if ((camera->animState == 0) || (anim->unk_04 != uniq2->unk_10)) {
        anim->unk_04 = uniq2->unk_10;
    }

    if (camera->animState == 0) {
        camera->animState = 1;
        Camera_SetUpdateRatesSlow(camera);
        anim->unk_00 = 200.0f;
    }

    if (uniq2->unk_10 & 0x10) {
        *sp34 = *sp3C;
        Camera_UnsetFlags(camera, 4);
    }

    sp70 = camera->trackActorPosRot.pos;

    if (uniq2->unk_10 & 1) {
        phi_f16 = 1.0f;
    } else {
        phi_f16 = camera->speedRatio;
    }

    temp_s1->x += ((sp70.x - temp_s1->x) * phi_f16 * 0.3f);
    temp_s1->y += (((sp70.y + sp48 + uniq2->unk_00) - temp_s1->y) * 0.2f);
    temp_s1->z += ((sp70.z - temp_s1->z) * phi_f16 * 0.3f);

    anim->unk_00 = anim->unk_00 + ((2.0f - anim->unk_00) * 0.05f);

    if (uniq2->unk_10 & 1) {
        OLib_Vec3fDiffToVecSphGeo(&sp68, temp_s1, sp34);
        sp68.r = uniq2->unk_04;
        OLib_VecSphAddToVec3f(&sp70, temp_s1, &sp68);
        Camera_LERPCeilVec3f(&sp70, sp3C, uniq2->unk_08, uniq2->unk_08, 0.2f);
    } else if (uniq2->unk_10 & 2) {
        if (OLib_Vec3fDistXZ(temp_s1, sp34) < uniq2->unk_04) {
            OLib_Vec3fDiffToVecSphGeo(&sp68, temp_s1, sp34);
            sp68.yaw = Camera_LERPCeilS(sp68.yaw, sp60.yaw, 0.1f, 5);
            sp68.r = uniq2->unk_04;
            sp68.pitch = 0;
            OLib_VecSphAddToVec3f(sp3C, temp_s1, &sp68);
            sp3C->y = sp34->y;
        } else {
            Camera_LERPCeilVec3f(sp34, sp3C, uniq2->unk_08, uniq2->unk_08, 0.2f);
        }
    }

    if ((uniq2->unk_10 & 0x20) == 0) {
        Camera_BGCheck(camera, temp_s1, sp3C);
    }

    camera->dist = OLib_Vec3fDist(temp_s1, sp3C);
    camera->roll = 0;
    camera->fov = Camera_LERPCeilF(uniq2->unk_0C, camera->fov, 0.2f, 0.1f);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);

    return true;
}

s32 Camera_Unique3(Camera* camera) {
    s32 ret = Camera_Normal1(camera);

    if ((camera->globalCtx->sceneNum == SCENE_21MITURINMAE) && (camera->eye.y < 5.0f)) {
        camera->eye.y = 5.0f;
    }
    return ret;
}

s32 Camera_Unique4(Camera* camera) {
    s32 ret = Camera_Parallel1(camera);

    if ((camera->globalCtx->sceneNum == SCENE_21MITURINMAE) && (camera->eye.y < 5.0f)) {
        camera->eye.y = 5.0f;
    }
    return ret;
}

s32 Camera_Unique5(Camera* camera) {
    s32 ret = Camera_Battle1(camera);

    if ((camera->globalCtx->sceneNum == SCENE_21MITURINMAE) && (camera->eye.y < 5.0f)) {
        camera->eye.y = 5.0f;
    }
    return ret;
}

s32 Camera_Unique0(Camera* camera) {
    f32 playerHeight;
    PosRot* sp40 = &camera->trackActorPosRot;
    PosRot sp9C;
    Player* player;
    Vec3f sp8C;
    VecSph sp84;
    VecSph sp7C;
    SubBgCamData* bgCamData;
    f32 sp74;
    s32 pad;
    s16 temp_v1;
    Unique0* uniq0 = (Unique0*)camera->paramData;
    Unique0Anim* anim = &uniq0->anim;
    CameraModeValue* values;
    Vec3f sp54;

    playerHeight = Player_GetHeight((Player*)camera->trackActor);
    player = (Player*)camera->trackActor;
    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        uniq0->unk_00 = NEXTSETTING;
        uniq0->unk_04 = NEXTSETTING;
        uniq0->unk_08 = NEXTSETTING;
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

    sCameraInterfaceFlags = uniq0->unk_08;

    switch (camera->animState) {
        case 0:
            bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
            Camera_Vec3sToVec3f(&anim->unk_1C, &bgCamData->pos);
            camera->eye = camera->eyeNext = anim->unk_1C;
            anim->unk_34 = bgCamData->rot;
            temp_v1 = bgCamData->fov;
            if (temp_v1 != -1) {
                if (temp_v1 <= 360) {
                    camera->fov = temp_v1;
                } else {
                    camera->fov = temp_v1 * 0.01f;
                }
            }
            anim->unk_3C = bgCamData->unk_0E;
            if (anim->unk_3C == -1) {
                anim->unk_3C = 0x3C;
            }

            if (bgCamData->unk_10 != -1) {
                anim->unk_18 = bgCamData->unk_10 * 0.01f;
            } else {
                anim->unk_18 = uniq0->unk_04 * 0.01f;
            }

            anim->unk_00 = sp40->pos;
            if ((uniq0->unk_08 & 0x10) != 0) {
                anim->unk_0C.x = sp40->pos.x;
                anim->unk_0C.y = sp40->pos.y + playerHeight + uniq0->unk_00;
                anim->unk_0C.z = sp40->pos.z;
            }
            anim->unk_3A = ((Actor*)camera->trackActor)->world.rot.y;
            anim->unk_3E = 0;
            camera->eye = camera->eyeNext = anim->unk_1C;
            Camera_UnsetFlags(camera, 4);
            camera->animState++;
        case 1:
            sp84.r = OLib_Vec3fDist(&sp8C, &camera->eye);
            sp84.yaw = anim->unk_34.y;
            sp84.pitch = -anim->unk_34.x;
            OLib_VecSphGeoToVec3f(&anim->unk_28, &sp84);
            func_80179A44(&anim->unk_1C, sp40, &anim->unk_0C);
            camera->at = anim->unk_0C; 

            if (player->stateFlags1 & 0x20000000) {
                anim->unk_00 = sp40->pos;
            }

            if (uniq0->unk_08 & 0x10) {
                sp54.x = sp40->pos.x;
                sp54.y = sp40->pos.y + playerHeight + uniq0->unk_00;
                sp54.z = sp40->pos.z;
                Camera_LERPCeilVec3f(&sp54, &camera->at, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
                camera->yOffsetUpdateRate = Camera_LERPCeilF(anim->unk_18, camera->yOffsetUpdateRate, 0.1f, 0.0001f);
                camera->xzOffsetUpdateRate = Camera_LERPCeilF(anim->unk_18, camera->xzOffsetUpdateRate, 0.1f, 0.0001f);
            }

            if ((camera->animState == 0x3E7) || (camera->animState == 0x29A)) {
                anim->unk_3E = 2;
            }
            if (uniq0->unk_08 & 1) {
                if (anim->unk_3C > 0) {
                    anim->unk_3C--;
                    anim->unk_00 = sp40->pos;
                } else if ((!(player->stateFlags1 & 0x20000000)) &&
                        ((OLib_Vec3fDistXZ(&sp40->pos, &anim->unk_00) >= 10.0f) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) || 
                            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || 
                            (uniq0->unk_08 & 2))) {
                                anim->unk_3E = 1;
                        
                }
            } else {
                if (anim->unk_3C > 0) {
                    anim->unk_3C--;
                    if (anim->unk_3C == 0) {
                        sCameraInterfaceFlags = 0;
                    }
                } else {
                    anim->unk_00 = sp40->pos;
                }
                if ((player->stateFlags1 & 0x20000000) == 0) { // TODO: Merge into 1 if-statement
                    if ((anim->unk_3A != ((Actor*)camera->trackActor)->world.rot.y) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) || 
                        CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || 
                        (uniq0->unk_08 & 2)) {
                            anim->unk_3E = 1;
                    }
                }
            }
            break;

        case 3:
            sp74 = 1.0f / anim->unk_3C;
            sp8C.y -= playerHeight * 0.2f;
            Camera_LERPCeilVec3f(&sp8C, &camera->at, sp74, sp74, 0.001f);
            sp84.r = OLib_Vec3fDist(&camera->at, &camera->eye);
            sp84.pitch = sp7C.pitch;
            sp84.yaw = sp7C.yaw;
            sp84.r = Camera_LERPCeilF(100.0f, sp84.r, sp74, 1.0f);
            OLib_VecSphAddToVec3f(&sp8C, &camera->at, &sp84);
            sp74 = (QREG(64) * 0.01f) + 0.2f;
            Camera_LERPCeilVec3f(&sp8C, &camera->eye, sp74, sp74, 0.001f);
            anim->unk_3C--;
            if (anim->unk_3C == 0) {
                anim->unk_3E = 9;
            }
    }

    if ((anim->unk_3E == 1) || (anim->unk_3E == 2) || (anim->unk_3E == 9)) {
        camera->dist = OLib_Vec3fDist(&camera->at, &camera->eye);
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
        Camera_UpdateAtActorOffset(camera, &sp40->pos);
        camera->atLERPStepScale = 0.0f;
        Camera_ChangeSettingFlags(camera, camera->prevSetting, 0x2);
        Camera_SetFlags(camera, 0x4);
        camera->yawUpdateRateInv = 1200.0f;
        camera->pitchUpdateRateInv = 1200.0f;
        camera->yOffsetUpdateRate = 0.001f;
        camera->xzOffsetUpdateRate = 0.001f;
        camera->fovUpdateRate = 0.01f;
    }

    return true;
}

s32 Camera_Unique6(Camera *camera) {
    Unique6* uniq6 = (Unique6*)camera->paramData;
    CameraModeValue* values;
    Vec3f playerPosDisp;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    f32 playerHeight;

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        uniq6->interfaceFlags = NEXTSETTING;
    }

    sCameraInterfaceFlags = uniq6->interfaceFlags;

    if (camera->animState == 0) {
        camera->animState++;
        Camera_SetUpdateRatesFastPitch(camera);
    }

    if (camera->trackActor != NULL) {
        playerHeight = Camera_GetTrackedActorHeight(camera);
        playerPosDisp = playerPosRot->pos;
        playerPosDisp.y += playerHeight;
        camera->dist = OLib_Vec3fDist(&playerPosDisp, &camera->eye);
        Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    } else {
        camera->dist = OLib_Vec3fDist(&camera->at, &camera->eye);
    }

    if (uniq6->interfaceFlags & 1) {
        if (camera->unk160 > 0) {
            camera->unk160--;
        }
    }

    return true;
}

s32 Camera_Unique7(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique8(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique9(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Demo1(Camera *camera) {
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
    Demo1* demo1 = (Demo1*)camera->paramData;
    Demo1Anim* anim = &demo1->anim;
    s32 pad;
    
    if (camera->animState == 0) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo1->interfaceFlags = NEXTSETTING;
    }

    if (camera->animState == 0) {
        anim->unk_1C = 0;
        OLib_Vec3fDiffToVecSphGeo(&anim->unk_0C, &camera->targetPosRot.pos, eye);
        OLib_Vec3fDiffToVecSphGeo(&anim->unk_14, &camera->at, eye);
        Actor_GetFocus(&targetHead, camera->target);
        Actor_GetWorld(&sp74, camera->target);
        camera->targetPosRot.pos.x = (sp74.pos.x + targetHead.pos.x) * 0.5f;
        camera->targetPosRot.pos.y = (sp74.pos.y + targetHead.pos.y) * 0.5f;
        camera->targetPosRot.pos.z = (sp74.pos.z + targetHead.pos.z) * 0.5f;
        camera->targetPosRot.rot = targetHead.rot;
        camera->animState++;
    }

    func_800B8898(camera->globalCtx, camera->target, &sp96, &sp94);
    
    temp_f0 = anim->unk_0C.r;
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
            sp88.r = anim->unk_0C.r;
            OLib_VecSphAddToVec3f(eyeNext, at, &sp88);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 2:
            Camera_LERPCeilVec3f(&camera->targetPosRot.pos, &camera->at, 0.1f, 0.1f, 0.1f);
            break;
        case 3:
            eyeNext = &targetPosRot->pos;
            if (anim->unk_1C == 0) {
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, &targetPosRot->pos, &anim->unk_14, sp98, 1);
            }
            Camera_LERPCeilVec3f(eyeNext, at, 0.1f, 0.1f, 0.1f);
            eyeNext = &camera->eyeNext;
            Camera_LERPCeilVec3f(&anim->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 4:
            if (anim->unk_1C == 0) {
                sp98[0] = camera->target;
                anim->unk_14.r = anim->unk_0C.r;
                func_800CC260(camera, &anim->unk_00, &targetPosRot->pos, &anim->unk_14, sp98, 1);
            }
            Camera_LERPCeilVec3f(&targetPosRot->pos, at, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&anim->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 5:
            eyeNext = &targetPosRot->pos;
            if (anim->unk_1C == 0) {
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, &targetPosRot->pos, &anim->unk_0C, sp98, 1);
            }
            *at = *eyeNext;
            sp44 = anim->unk_00;
            camera->eyeNext = sp44;
            *eye = sp44;
            break;
        case 6:
            if (anim->unk_1C == 0) {
                anim->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                anim->unk_0C.r = anim->unk_14.r;
                func_800CC260(camera, &anim->unk_00, &targetPosRot->pos, &anim->unk_0C, sp98, 1);
            }
            Camera_LERPCeilVec3f(&targetPosRot->pos, at, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&anim->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
        case 7:
            if (anim->unk_1C == 0) {
                anim->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, &targetPosRot->pos, &anim->unk_0C, sp98, 1);
            }
            *at = targetPosRot->pos;
            sp44 = anim->unk_00;
            camera->eyeNext = sp44;
            *eye = sp44;
            break;
        case 8:
            if (anim->unk_1C == 0) {
                anim->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, &targetPosRot->pos, &anim->unk_0C, sp98, 1);
            }
            Camera_LERPCeilVec3f(&targetPosRot->pos, at, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&anim->unk_00, eyeNext, 0.1f, 0.1f, 0.1f);
            *eye = *eyeNext;
            Camera_BGCheck(camera, at, eye);
            break;
    }

    anim->unk_1C++;
    return true;
}

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
    Actor* trackActor = (Actor*)camera->trackActor;
    Demo2* demo2 = (Demo2*)camera->paramData;
    Demo2Anim* anim = &demo2->anim;

    if (((trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) &&
         (((Player*)trackActor)->transformation == PLAYER_FORM_GORON))) {
        sp4C = D_801B9EB4;
        sp48 = D_801B9ED4;
    }

    Camera_UnsetFlags(camera, 0x10);
    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo2->fov = NEXTSETTING;
        demo2->unk_04 = NEXTSETTING;
        demo2->interfaceFlags = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);

    sCameraInterfaceFlags = demo2->interfaceFlags;

    switch (camera->animState) {
        case 0:
            Camera_UnsetFlags(camera, 0x8 | 0x4);
            Camera_SetUpdateRatesSlow(camera);
            camera->fov = demo2->fov;
            camera->roll = anim->animFrame = 0;
            anim->initialAt = playerPosRot->pos;
            if (camera->playerGroundY != BGCHECK_Y_MIN) {
                anim->initialAt.y = camera->playerGroundY;
            }
            angle = playerPosRot->rot.y;
            sp70.x = anim->initialAt.x + (Math_SinS(angle) * 40.0f);
            sp70.y = anim->initialAt.y + 40.0f;
            sp70.z = anim->initialAt.z + (Math_CosS(angle) * 40.0f);
            if (camera->globalCtx->state.frames & 2) {
                angle -= 0x4000;
                anim->yawDir = 1;
            } else {
                angle += 0x4000;
                anim->yawDir = -1;
            }

            sp7C.x = sp70.x + (sp4C[1].r * Math_SinS(angle));
            sp7C.y = anim->initialAt.y + 5.0f;
            sp7C.z = sp70.z + (sp4C[1].r * Math_CosS(angle));
            if (Camera_BGCheck(camera, &sp70, &sp7C)) {
                anim->yawDir = -anim->yawDir;
            }

            OLib_Vec3fToVecSphGeo(&atOffset, &sp48[0]);
            atOffset.yaw += playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &anim->initialAt, &atOffset);

            eyeOffset.r = sp4C[0].r;
            eyeOffset.pitch = sp4C[0].pitch;
            eyeOffset.yaw = (sp4C[0].yaw * anim->yawDir) + playerPosRot->rot.y;

            anim->unk_0C = 1.0f;
            break;
        case 1:
            sp60 = (anim->animFrame - 2) * (1.0f / 146.0f);

            VEC3F_LERPIMPDST(&sp64, &sp48[0], &sp48[1], sp60);

            OLib_Vec3fToVecSphGeo(&atOffset, &sp64);
            atOffset.yaw = (atOffset.yaw * anim->yawDir) + playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &anim->initialAt, &atOffset);

            atOffset.r = F32_LERPIMP(sp4C[0].r, sp4C[1].r, sp60);
            atOffset.pitch = BINANG_LERPIMP(sp4C[0].pitch, sp4C[1].pitch, sp60);
            atOffset.yaw = BINANG_LERPIMP(sp4C[0].yaw, sp4C[1].yaw, sp60);

            eyeOffset.r = atOffset.r;
            eyeOffset.pitch = atOffset.pitch;
            eyeOffset.yaw = (atOffset.yaw * anim->yawDir) + playerPosRot->rot.y;

            anim->unk_0C -= (1.0f / 365.0f);
            break;
        case 2:
            sp60 = (anim->animFrame - 148) * 0.1f;

            sp64.x = F32_LERPIMP(sp48[1].x, sp48[2].x, sp60);
            sp64.y = F32_LERPIMP((sp48[1].y - playerHeight), sp48[2].y, sp60);
            sp64.y += playerHeight;
            sp64.z = F32_LERPIMP(sp48[1].z, sp48[2].z, sp60);

            OLib_Vec3fToVecSphGeo(&atOffset, &sp64);
            atOffset.yaw = (atOffset.yaw * anim->yawDir) + playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &anim->initialAt, &atOffset);

            atOffset.r = F32_LERPIMP(sp4C[1].r, sp4C[2].r, sp60);
            atOffset.pitch = BINANG_LERPIMP(sp4C[1].pitch, sp4C[2].pitch, sp60);
            atOffset.yaw = BINANG_LERPIMP(sp4C[1].yaw, sp4C[2].yaw, sp60);

            eyeOffset.r = atOffset.r;
            eyeOffset.pitch = atOffset.pitch;
            eyeOffset.yaw = (atOffset.yaw * anim->yawDir) + playerPosRot->rot.y;

            anim->unk_0C -= 0.04f;
            break;
        case 3:
            sp60 = (anim->animFrame - 159) * (1.0f / 9.0f);

            sp64.x = F32_LERPIMP(sp48[2].x, sp48[3].x, sp60);
            sp64.y = F32_LERPIMP(sp48[2].y, sp48[3].y, sp60);
            sp64.y += playerHeight;
            sp64.z = F32_LERPIMP(sp48[2].z, sp48[3].z, sp60);

            OLib_Vec3fToVecSphGeo(&atOffset, &sp64);
            atOffset.yaw = (atOffset.yaw * anim->yawDir) + playerPosRot->rot.y;
            OLib_VecSphAddToVec3f(at, &anim->initialAt, &atOffset);

            atOffset.r = F32_LERPIMP(sp4C[2].r, sp4C[3].r, sp60);
            atOffset.pitch = BINANG_LERPIMP(sp4C[2].pitch, sp4C[3].pitch, sp60);
            atOffset.yaw = BINANG_LERPIMP(sp4C[2].yaw, sp4C[3].yaw, sp60);

            eyeOffset.r = atOffset.r;
            eyeOffset.pitch = atOffset.pitch;
            eyeOffset.yaw = (atOffset.yaw * anim->yawDir) + playerPosRot->rot.y;

            anim->unk_0C += (4.0f / 45.0f);
            break;
        case 30:
            Camera_SetFlags(camera, 0x400);
            if (camera->flags2 & 8) {
                camera->animState = 4;
            }
        case 10:
        case 20:
            skipUpdateEye = true;
            break;
        case 4:
            eyeOffset.r = 80.0f;
            eyeOffset.pitch = 0;
            eyeOffset.yaw = atToEye.yaw;
            anim->unk_0C = 0.1f;
            sCameraInterfaceFlags = 0x3400;

            if (!(((anim->animFrame < 0) || (camera->xzSpeed > 0.001f) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) ||
                   CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R)) &&
                  (camera->flags2 & 8))) {
                goto skipeyeUpdate;
            }
        default:
            Camera_SetFlags(camera, 0x10 | 0x4);
            Camera_UnsetFlags(camera, 0x8);
            func_800CC938(camera);
            sCameraInterfaceFlags = 0;
        skipeyeUpdate:
            skipUpdateEye = true;
            break;
    }

    anim->animFrame++;

    if (anim->animFrame == 1) {
        camera->animState = 0xA;
    } else if (anim->animFrame == 2) {
        camera->animState = 1;
    } else if (anim->animFrame == 148) {
        camera->animState = 2;
    } else if (anim->animFrame == 158) {
        camera->animState = 20;
    } else if (anim->animFrame == 159) {
        camera->animState = 3;
    } else if (anim->animFrame == 168) {
        camera->animState = 30;
    } else if (anim->animFrame == 228) {
        camera->animState = 4;
    }

    if (!skipUpdateEye) {
        eyeOffset.r = Camera_LERPCeilF(eyeOffset.r, atToEye.r, anim->unk_0C, 1.0f);
        eyeOffset.pitch = Camera_LERPCeilS(eyeOffset.pitch, atToEye.pitch, anim->unk_0C, 5);
        eyeOffset.yaw = Camera_LERPCeilS(eyeOffset.yaw, atToEye.yaw, anim->unk_0C, 5);
        OLib_VecSphAddToVec3f(eyeNext, at, &eyeOffset);
        *eye = *eyeNext;
    }

    camera->dist = OLib_Vec3fDist(at, eye);
    camera->atLERPStepScale = 0.1f;
    Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    return true;
}

s32 Camera_Demo3(Camera *camera) {
    s32 pad2;
    CameraModeValue* values;
    Demo3* demo3 = (Demo3*)camera->paramData;
    VecSph atToEye;
    PosRot playerHead;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    Demo3Anim* anim = &demo3->anim;
    f32 temp;


    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);
    Actor_GetFocus(&playerHead, (Actor*)camera->trackActor);
    playerHead.pos.x = camera->trackActorPosRot.pos.x;
    playerHead.pos.z = camera->trackActorPosRot.pos.z;
    playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.4f;
    Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo3->interfaceFlags = NEXTSETTING;
        camera->animState = 0;
    }

    sCameraInterfaceFlags = demo3->interfaceFlags;

    switch (camera->animState) {
        case 0:
            camera->animState++;
            anim->unk_06 = 125;
            Quake2_SetType(8);
            Quake2_SetCountdown(60);
            break;
        case 1:
            temp =  1.0f / anim->unk_06;
            atToEye.r = Camera_LERPCeilF(140.0f, atToEye.r, temp, 0.1f);
            anim->unk_06--;
            camera->fov = Camera_LERPCeilF(50.0f, camera->fov, 0.1f, 0.1f);
            if (anim->unk_06 <= 0) {
                anim->unk_06 = 20;
                camera->animState++;
                Quake2_SetType(0x10);
                Quake2_SetCountdown(80);
            }
            break;
        case 2:
            anim->unk_06--;
            if (anim->unk_06 <= 0) {
                anim->unk_04 = 120;
                anim->unk_06 = 0;
                anim->unk_00 = (175.0f - camera->fov) / anim->unk_04;
                camera->animState++;
                Quake2_SetType(0x400);
                Quake2_SetCountdown(15);
            }
            break;
        case 3:
            anim->unk_06++;
            camera->fov += anim->unk_00 * anim->unk_06;
            if (anim->unk_06 >= 15) {
                Quake2_ClearType(0x400);
                Quake2_ClearType(0x10);
                Quake2_ClearType(8);
                camera->animState++;
            }
            break;
    }

    OLib_VecSphAddToVec3f(eyeNext, at, &atToEye);
    *eye = *eyeNext;
    return true;
}

s32 Camera_Demo4(Camera *camera) {
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    VecSph atToEye;
    CameraModeValue* values;
    PosRot playerHead;
    f32 sp58;
    f32 sin;
    Demo4* demo4 = (Demo4*)camera->paramData;
    Demo4Anim* anim = &demo4->anim;
    s32 pad[2];

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo4->interfaceFlags = NEXTSETTING;                
        camera->animState = 0;
        anim->unk_00 = *at;
        anim->unk_18 = atToEye;
        anim->unk_14 = camera->fov;
    }

    Actor_GetFocus(&playerHead, (Actor*)camera->trackActor);
    sCameraInterfaceFlags = demo4->interfaceFlags;

    switch (camera->animState) {
        if (1) {}
        case 0:
            camera->animState++;
            anim->unk_22 = 0;
            if (!(atToEye.r < 40.0f)) {
                atToEye.r = 40.0f;
            }
            camera->fov = 80.0f;
            anim->unk_10 = (Rand_ZeroOne() - 0.5f) * 40.0f;
        case 1:
            if (anim->unk_22 >= 12) {
                anim->unk_0C = (anim->unk_22 - 12) * 10.384615f;
                sin = sin_rad(anim->unk_0C * (M_PI / 180));
                anim->unk_0C = ((anim->unk_10 < 0.0f) ? -1.0f : 1.0f) * sin;
                if (anim->unk_22 == 12) {
                    Quake2_SetType(0x200);
                    Quake2_SetCountdown(26);
                }
            } else {
                anim->unk_0C = 0.0f;
            }
            sp58 = anim->unk_22 * (6.0f / 19.0f);
            anim->unk_20 = playerPosRot->rot.y + 0x4000;
            playerHead.pos.x = (Math_SinS(anim->unk_20) * sp58 * anim->unk_0C) + playerPosRot->pos.x;
            playerHead.pos.z = (Math_CosS(anim->unk_20) * sp58 * anim->unk_0C) + playerPosRot->pos.z;
            playerHead.pos.y -= (playerHead.pos.y - playerPosRot->pos.y) * 0.099999994f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.2f, 0.2f, 0.1f);
            sp58 = (anim->unk_22 * (30.0f / 19.0f));
            camera->roll = DEGF_TO_BINANG(sp58 * anim->unk_0C);
            sp58 = 1.0f / (38 - anim->unk_22);
            anim->unk_22++;
            atToEye.r = Camera_LERPCeilF(30.0f, atToEye.r, sp58, 0.1f);
            atToEye.pitch = 0;
            if (anim->unk_22 >= 38) {
                anim->unk_22 = 24;
                camera->animState++;
                anim->unk_0C = (32.0f - camera->fov) / 24.0f;
                Quake2_SetType(0x800);
            }
            break;
        case 2:
            if (anim->unk_22 == 0x18) {
                at->x = (Math_SinS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.x;
                at->y = playerHead.pos.y - ((playerHead.pos.y - playerPosRot->pos.y) * 0.1f);
                at->z = (Math_CosS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.z;
            } else {
                playerHead.pos.x = (Math_SinS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.x;
                playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
                playerHead.pos.z = (Math_CosS(playerPosRot->rot.y) * -7.0f) + playerPosRot->pos.z;
                Camera_LERPCeilVec3f(&playerHead.pos, at, 0.25f, 0.25f, 0.1f);
            }
            if (anim->unk_22 > 0) {
                camera->fov += anim->unk_0C;
            }
            anim->unk_22--;
            atToEye.r = 35.0f;
            atToEye.pitch = 0x2000;
            camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
            if (anim->unk_22 <= 0) {
                anim->unk_20 = 0x276;
                anim->unk_22 = 0;
                anim->unk_0C = (60.0f - camera->fov) / anim->unk_20;
                camera->animState = 3;
            }
            break;
        case 3:
            playerHead.pos.x = playerPosRot->pos.x;
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
            playerHead.pos.z = playerPosRot->pos.z;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.25f, 0.25f, 0.1f);
            camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
            anim->unk_22++;
            camera->fov += anim->unk_0C * anim->unk_22;
            atToEye.pitch = 0x2000;
            atToEye.r = 35.0f;
            if (anim->unk_22 >= 0x23) {
                Quake2_ClearType(0x200);
                Quake2_ClearType(0x800);
                camera->animState = 4;
            }
            break;
        case 999:
            Actor_GetFocus(&playerHead, (Actor*)camera->trackActor);
            Quake2_ClearType(0x200);
            Quake2_ClearType(0x800);
            camera->animState = 4;
            break;
        case 4:
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);
            atToEye = anim->unk_18;
            camera->fov = anim->unk_14;
            camera->roll = 0;
            break;

    }

    OLib_VecSphAddToVec3f(&camera->eyeNext, at, &atToEye);
    *eye = camera->eyeNext;
    return true;
}

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
    Demo5* demo5 = (Demo5*)camera->paramData;
    Demo5Anim* anim = &demo5->anim;
    CameraModeValue* values;

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo5->interfaceFlags = NEXTSETTING;                
        camera->animState = 0;
        anim->unk_00 = *at;
        anim->unk_1C = atToEye;
        anim->unk_18 = camera->fov;
    }

    Actor_GetFocus(&playerHead, (Actor*)camera->trackActor);
    
    sCameraInterfaceFlags = demo5->interfaceFlags;

    switch (camera->animState) {
        case 0:
            camera->animState++;
            atToEye.pitch = 0;
            anim->unk_26 = 0x12;
            anim->unk_14 = 80.0f;
            atToEye.r = 30.0f;
            camera->fov = 80.0f;
            anim->unk_10 = (Rand_ZeroOne() - 0.5f) * 40.0f;
            camera->roll = 0;
            playerHead.pos.x = playerPosRot->pos.x;
            playerHead.pos.z = playerPosRot->pos.z;
            *at = playerHead.pos;
        case 1:
            anim->unk_26--;
            if (anim->unk_26 <= 0) {
                anim->unk_26 = 0;
                camera->animState = 2;
                anim->unk_24 = camera->trackActorPosRot.rot.y + 0x4000;
                anim->unk_26 = 0x2E;
                Quake2_SetType(0x200);
                Quake2_SetCountdown(46);
            }
            break;
        case 2:
            anim->unk_0C = anim->unk_26 * (180.0f / 23.0f);
            sp58 = anim->unk_0C * (M_PI / 180);
            sin = sin_rad(sp58);
            anim->unk_0C = ((anim->unk_10 < 0.0f) ? -1.0f : 1.0f) * sin;
            new_var = (0x2E - anim->unk_26) * (5.0f / 46.0f);
            playerHead.pos.x = (Math_SinS(anim->unk_24) * new_var * anim->unk_0C) + playerPosRot->pos.x;
            playerHead.pos.z = (Math_CosS(anim->unk_24) * new_var * anim->unk_0C) + playerPosRot->pos.z;
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.2f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);
            new_var = (anim->unk_26 * (10.0f / 23.0f));
            camera->roll = DEGF_TO_BINANG(anim->unk_0C * new_var);
            new_var = 1.0f / anim->unk_26;
            atToEye.r = Camera_LERPCeilF(anim->unk_14, atToEye.r, new_var, 0.1f);
            anim->unk_26--;
            atToEye.pitch = 0;
            if (anim->unk_26 <= 0) {
                camera->animState = 3;
                Quake2_ClearType(0x200);
            }
            break;
        case 999:
            Actor_GetFocus(&playerHead, (Actor*)camera->trackActor);
            camera->animState = 3;
            Quake2_ClearType(0x200);
            break;
        case 3:
            playerHead.pos.y -= (playerHead.pos.y - camera->trackActorPosRot.pos.y) * 0.1f;
            Camera_LERPCeilVec3f(&playerHead.pos, at, 0.1f, 0.1f, 0.1f);
            camera->roll = 0;
            atToEye = anim->unk_1C;
            camera->fov = anim->unk_18;
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

s32 Camera_Demo0(Camera* camera) {
    Demo0* demo0 = (Demo0*)camera->paramData;
    f32 temp_f0_2;
    s16 phi_v1;
    Camera* subCam = &camera->globalCtx->subCameras[2];
    Vec3f* mainEye = &camera->eye;
    Vec3f* subEye = &subCam->eye;
    Vec3f* at = &camera->at;
    Demo0Anim* anim = &demo0->anim;
    s32 pad;

    if (camera->animState == 0) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo0->unk_00 = NEXTSETTING;
    }

    if (camera->animState == 0) {
        OLib_Vec3fDiffToVecSphGeo(&anim->unk_04, &subCam->at, subEye);
        OLib_Vec3fDiffToVecSphGeo(&anim->unk_0C, &camera->at, mainEye);
        if (anim->unk_04.r < 50.0f) {
            anim->unk_04.r = 50.0f;
            if (anim->unk_04.pitch < 0x7D0) { // 11 degrees
                anim->unk_04.pitch = 0x7D0;
            }
        }

        anim->unk_00 = OLib_Vec3fDist(mainEye, subEye);
        if (anim->unk_00 < 300.0f) {
            anim->unk_1A = 0;
        } else {
            anim->unk_1A = sqrtf(anim->unk_00 - 200.0f);
        }

        anim->unk_14 = subCam->inputDir.x - camera->inputDir.x;
        if (anim->unk_14 >= 0) {
            phi_v1 = anim->unk_14;
        } else {
            phi_v1 = -anim->unk_14;
        }

        if (phi_v1 >= 0x2711) {
            phi_v1 /= 0x3E8;
            if (anim->unk_1A < phi_v1) {
                anim->unk_1A = phi_v1;
            }
        }

        anim->unk_16 = subCam->inputDir.y - camera->inputDir.y;
        if (anim->unk_16 >= 0) {
            phi_v1 = anim->unk_16;
        } else {
            phi_v1 = -anim->unk_16;
        }
        
        if (phi_v1 >= 0x2711) {
            phi_v1 /= 0x3E8;
            if (anim->unk_1A < phi_v1) {
                anim->unk_1A = phi_v1;
            }
        }

        anim->unk_18 = subCam->inputDir.z - camera->inputDir.z;
        if (anim->unk_18 >= 0) {
            phi_v1 = anim->unk_18;
        } else {
            phi_v1 = -anim->unk_18;
        }

        if (phi_v1 >= 0x2711) {
            phi_v1 /= 0x3E8;
            if (anim->unk_1A < phi_v1) {
                anim->unk_1A = phi_v1;
            }
        }

        if (anim->unk_1A != 0) {
            anim->unk_00 = (anim->unk_04.r - anim->unk_0C.r) / anim->unk_1A;
            anim->unk_14 = (s16)(anim->unk_04.pitch - anim->unk_0C.pitch) / anim->unk_1A;
            anim->unk_16 = (s16)(anim->unk_04.yaw - anim->unk_0C.yaw) / anim->unk_1A;
            anim->unk_18 = (s16)(subCam->roll - camera->roll) / anim->unk_1A;
        }
        camera->animState++;
    }

    if (anim->unk_1A != 0) {
        temp_f0_2 = anim->unk_1A;
        at->x += (subCam->at.x - camera->at.x) / temp_f0_2;
        at->y += (subCam->at.y - camera->at.y) / temp_f0_2;
        at->z += (subCam->at.z - camera->at.z) / temp_f0_2;
        anim->unk_0C.r = anim->unk_0C.r + anim->unk_00;
        anim->unk_0C.pitch = anim->unk_0C.pitch + anim->unk_14;
        anim->unk_0C.yaw = anim->unk_0C.yaw + anim->unk_16;
        camera->roll += anim->unk_18;
        OLib_VecSphAddToVec3f(mainEye, at, &anim->unk_0C);
        camera->eyeNext = *mainEye;
        anim->unk_1A--;
    }

    if (anim->unk_1A == 0) {
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
s32 Camera_Special5(Camera *camera) {
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
    Special5* spec5 = (Special5*)camera->paramData;
    Special5Anim* anim = &spec5->anim;
    f32 rand;
    f32 yOffset = Camera_GetTrackedActorHeight(camera);
    
    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        f32 yNormal = (0.8f - ((68.0f / yOffset) * -0.2f));
        spec5->yOffset = (NEXTPCT * yOffset) * yNormal;
        spec5->eyeDist = NEXTSETTING;
        spec5->minDistForRot = NEXTSETTING;
        spec5->pitch = DEGF_TO_BINANG(NEXTSETTING);
        spec5->fovTarget = NEXTSETTING;
        spec5->atMaxLERPScale = NEXTPCT;
        spec5->timerInit = NEXTSETTING;
        spec5->interfaceFlags = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&atToEye, at, eye);
    OLib_Vec3fDiffToVecSphGeo(&atToEyeNext, at, eyeNext);
    Actor_GetWorld(&spA8, camera->target);

    sCameraInterfaceFlags = spec5->interfaceFlags;

    if (camera->animState == 0) {
        camera->animState++;
        anim->animTimer = spec5->timerInit;
    }

    if (anim->animTimer > 0) {
        anim->animTimer--;
    } else if (anim->animTimer == 0) {
        if ((camera->target == NULL) || (camera->target->update == NULL)) {
            camera->target = NULL;
            return true;
        }
        
        anim->animTimer--;
        if (spec5->minDistForRot < OLib_Vec3fDist(&spA8.pos, &playerPosRot->pos)) {
            sp6C.yaw = playerPosRot->rot.y;
            sp6C.pitch = -playerPosRot->rot.x;
            sp6C.r = 20.0f;
            OLib_VecSphAddToVec3f(&sp7C.pos, &spA8.pos, &sp6C);
            func_800CBC84(camera, at, &sp7C, 0);
            OLib_Vec3fToVecSphGeo(&sp6C, &sp7C.norm);
            spA4 = SUB16(playerPosRot->rot.y, sp6C.yaw);
            sp74.r = spec5->eyeDist;
            rand = Rand_ZeroOne();
            sp74.yaw =
                BINANG_ROT180(playerPosRot->rot.y) + (s16)(spA4 < 0 ? -(s16)(0x1553 + (s16)(rand * 2730.0f))
                                                                    : (s16)(0x1553 + (s16)(rand * 2730.0f)));
            sp74.pitch = spec5->pitch;     
            OLib_VecSphAddToVec3f(eyeNext, &spA8.pos, &sp74);
            *eye = *eyeNext;
            Camera_BGCheck(camera, &spA8.pos, eye);
        }
    } 

    Camera_CalcAtDefault(camera, &atToEyeNext, spec5->yOffset, 0);
    camera->fov = Camera_LERPCeilF(spec5->fovTarget, camera->fov, camera->atLERPStepScale * 0.05f, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, spec5->atMaxLERPScale);
    return true;
}

s32 Camera_Special6(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special7(Camera* camera) {
    return Camera_Noop(camera);
}


/**
 * When opening certain doors, the camera will jump to the next room for a mini "cutscene"
 */ 
s32 Camera_Special8(Camera *camera) {
    Vec3f* at = &camera->at;
    Vec3f* eyeNext = &camera->eyeNext;
    PosRot* playerPosRot = &camera->trackActorPosRot;
    Vec3f atTarget;
    Vec3f posOffsetTarget;
    f32 yNormal;
    f32 yOffset = Camera_GetTrackedActorHeight(camera);
    Special8* spec8 = (Special8*)camera->paramData;
    Special8Params* params = &spec8->params;
    Special8Anim* anim = &params->anim;
    s32 pad[2];

    Camera_UnsetFlags(camera, 0x10);
    yNormal = (0.8f - ((68.0f / yOffset) * -0.2f));

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        params->yOffset = NEXTPCT * yOffset * yNormal;
        params->eyeStepScale = NEXTPCT;
        params->posStepScale = NEXTPCT;
        params->fov = NEXTSETTING;
        params->maxDoorCutsceneCounter = NEXTSETTING * 5;
        params->interfaceFlags = NEXTSETTING;
        anim->fov = params->fov * 100.0f;
        anim->doorCutsceneCounter = 0;   
        Camera_UnsetFlags(camera, 0x4 | 0x2);
        anim->eye.x = spec8->doorParams.eye.x;
        anim->eye.y = spec8->doorParams.eye.y;
        anim->eye.z = spec8->doorParams.eye.z;
    }

    if (anim->doorCutsceneCounter < params->maxDoorCutsceneCounter) {
        anim->doorCutsceneCounter++;
        sCameraInterfaceFlags = params->interfaceFlags;
        posOffsetTarget.x = 0.0f;
        posOffsetTarget.y = params->yOffset + yOffset;
        posOffsetTarget.z = 0.0f;
        Camera_LERPCeilVec3f(&posOffsetTarget, &camera->atActorOffset, params->posStepScale, params->posStepScale, 0.1f);
        atTarget.x = playerPosRot->pos.x + camera->atActorOffset.x;
        atTarget.y = playerPosRot->pos.y + camera->atActorOffset.y;
        atTarget.z = playerPosRot->pos.z + camera->atActorOffset.z;
        if (camera->animState == 0) {
            camera->animState++;
            if ((params->interfaceFlags & 1) == 0) {
                camera->eyeNext = anim->eye;
                camera->at = atTarget;
            }
        }

        Camera_LERPCeilVec3f(&atTarget, at, params->posStepScale, params->posStepScale, 10.0f);
        Camera_LERPCeilVec3f(&anim->eye, eyeNext, params->eyeStepScale, params->eyeStepScale, 0.1f);
        camera->eye = *eyeNext;
        camera->dist = OLib_Vec3fDist(at, &camera->eye);
        camera->roll = 0;
        camera->xzSpeed = 0.0f;
        camera->fov = PCT(anim->fov);
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
        Camera_UpdateAtActorOffset(camera, &playerPosRot->pos);
    } else {
        Camera_SetFlags(camera, 0x400 | 0x10);
        sCameraInterfaceFlags = 0;
        if ((camera->xzSpeed > 0.001f) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) || 
            CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || 
            (params->interfaceFlags & 8)) {
                func_800CC938(camera);
                Camera_SetFlags(camera, 0x4 | 0x2);
                Camera_UnsetFlags(camera, 0x400);
        }
    }
    return true;
}

s32 Camera_Special9(Camera *camera) {
    Vec3f* sp4C = &camera->eye;
    Vec3f* sp48 = &camera->at;
    s32 rand1;
    Vec3f spB8;
    VecSph spB0;
    VecSph spA8;
    f32 spA4;
    s32 phi_v1_2;
    s16 csIndex;
    f32 sp34;
    PosRot sp84;
    Vec3f* sp44 = &camera->eyeNext;
    PosRot* sp40 = &camera->trackActorPosRot;
    Special9* spec9 = (Special9*)camera->paramData;
    Special9Params* params = &spec9->params;
    Special9Anim* anim = &params->anim;
    s32 sp50[1];
    SubBgCamData* bgCamData;
    
    spA4 = Camera_GetTrackedActorHeight(camera);
    csIndex = ActorCutscene_GetCurrentIndex();

    if ((csIndex != -1) && (csIndex != 0x7D)) {
        func_800E0348(camera);
    }

    Camera_UnsetFlags(camera, 0x10);
    sp34 = 0.8f - ((68.0f / spA4) * -0.2f);

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        params->unk_00 = NEXTPCT * spA4 * sp34;
        params->unk_04 = NEXTSETTING;
        params->unk_08 = NEXTSETTING;
    }


    if (spec9->doorParams.doorActor != NULL) {
        Actor_GetWorldPosShapeRot(&sp84, spec9->doorParams.doorActor);
    } else {
        sp84 = *sp40;
        sp84.pos.y += spA4 + params->unk_00;
        sp84.rot.x = 0;
    }

    OLib_Vec3fDiffToVecSphGeo(&spA8, sp48, sp4C);

    sCameraInterfaceFlags = params->unk_08;

    switch (camera->animState) {
        case 0:
            Camera_UnsetFlags(camera, (0x4 | 0x2));
            camera->animState++;
            if (ABS((s16)(sp40->rot.y - sp84.rot.y)) > 0x4000) {
                anim->unk_00 = BINANG_ROT180(sp84.rot.y);
            } else {
                anim->unk_00 = sp84.rot.y;
            }
        case 1:
            spec9->doorParams.timer1--;
            if (spec9->doorParams.timer1 <= 0) {
                camera->animState++;
                if (params->unk_08 & 1) {
                    bgCamData = (SubBgCamData*)Camera_GetSurfaceBgCamData(camera, camera->bgCamDataId);
                    Camera_Vec3sToVec3f(sp44, &bgCamData->pos);
                    spB8 = *sp4C = *sp44;
                } else {
                    s16 sp30;
                    s16 randFloat;
                    spB0.pitch = ((s16)(Rand_ZeroOne() * 640.0f) + 0xBB8);
                    randFloat = ((s16)(Rand_ZeroOne() * 1230.0f) + 0x5DC);
                    sp30 = (s16)(randFloat * ((camera->globalCtx->state.frames % 2) ? 1 : -1));
                    spB0.yaw = anim->unk_00 + sp30;
                    spB0.r = 200.0f * sp34;
                    OLib_VecSphAddToVec3f(sp44, sp48, &spB0);
                    spB8 = *sp4C = *sp44;
                    if (Camera_CheckOOB(camera, &spB8, &sp40->pos)) {
                        sp30 = (s16)-sp30;
                        spB0.yaw = anim->unk_00 + sp30;
                        OLib_VecSphAddToVec3f(sp44, sp48, &spB0);
                        *sp4C = *sp44;
                    }
                }
            } else {
                break;
            }
        case 2:
            spB8 = sp40->pos;
            spB8.y += spA4 + params->unk_00;

            Camera_LERPCeilVec3f(&spB8, sp48, 0.25f, 0.25f, 0.1f);
            spec9->doorParams.timer2--;
            if (spec9->doorParams.timer2 <= 0) {
                camera->animState++;
                anim->unk_00 = BINANG_ROT180(anim->unk_00);
            } else {
                break;
            }
        case 3:
            spB8 = sp40->pos;
            spB8.y += spA4 + params->unk_00;
            Camera_LERPCeilVec3f(&spB8, sp48, 0.5f, 0.5f, 0.1f);
            spB0.pitch = Camera_LERPCeilS(0xAAA, spA8.pitch, 0.3f, 5);
            spB0.yaw = Camera_LERPCeilS(anim->unk_00, spA8.yaw, 0.3f, 5);
            spB0.r = Camera_LERPCeilF(60.0f, spA8.r, 0.3f, 1.0f);
            OLib_VecSphAddToVec3f(sp44, sp48, &spB0);
            *sp4C = *sp44;
            spec9->doorParams.timer3--;
            if (spec9->doorParams.timer3 <= 0) {
                camera->animState++;
            } else {
                break;
            }
        case 4:
            camera->animState++;
        case 999:
        default:
            Camera_SetFlags(camera, 0x400 | 0x10);
            sCameraInterfaceFlags = 0;

            if ((camera->xzSpeed > 0.001f) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R) || 
                (params->unk_08 & 8)) {

                func_800CC938(camera);
                Camera_SetFlags(camera, 0x4 | 0x2);
                Camera_UnsetFlags(camera, 0x400);
            }
            break;
    }

    spB8 = sp40->pos;
    spB8.y += spA4;
    camera->dist = OLib_Vec3fDist(&spB8, sp4C);
    Camera_UpdateAtActorOffset(camera, &sp40->pos);
    return true;
}

/*===============================================================*/
/*                    Camera Public Functions                    */
/*===============================================================*/

Camera* Camera_Create(View *view, CollisionContext *colCtx, GlobalContext *globalCtx) {
    Camera* newCamera = zelda_malloc(sizeof(*newCamera));

    if (newCamera != NULL) {
        Camera_Init(newCamera, view, colCtx, globalCtx);
    }
    return newCamera;
}

void Camera_Destroy(Camera* camera) {
    if (camera != NULL) {
        zelda_free(camera);
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
    camera->nextBgCamDataId = -1;
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
    Camera_SetFlags(camera, 0x4000);
    camera->skyboxOffset.z = camera->skyboxOffset.y = camera->skyboxOffset.x = 0;
    camera->up.z = camera->up.x = 0.0f;
    camera->atLERPStepScale = 1;
    camera->up.y = 1.0f;
    sCameraInterfaceFlags = 0xFF00;
    sCameraInitCounter = 3;
}


/**
 * OoT: func_80057FC4
 */
void func_800DDFE0(Camera* camera) {
    if (camera != &camera->globalCtx->mainCamera) {
        camera->prevSetting = camera->setting = CAM_SET_FREE0;
        Camera_UnsetFlags(camera, 0x4);
    } else {
        switch (camera->globalCtx->roomCtx.currRoom.unk3) {
            case 1:
                camera->prevSetting = CAM_SET_DUNGEON0;
                Camera_ChangeSettingFlags(camera, CAM_SET_DUNGEON0, 0x2);
                break;
            case 0:
                camera->prevSetting = CAM_SET_NORMAL0;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL0, 0x2);
                break;
            case 2:
                camera->prevSetting = CAM_SET_ROOM0;
                Camera_ChangeSettingFlags(camera, CAM_SET_ROOM0, 0x2);
                break;
            default:
                camera->prevSetting = CAM_SET_NORMAL0;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL0, 0x2);
                break;
        }
        Camera_SetFlags(camera, 0x4);
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
    f32 playerYOffset;
    Vec3f* eye = &camera->eye;
    s32 pad;

    Actor_GetWorldPosShapeRot(&playerPosShape, &player->actor);
    camera->trackActor = &player->actor;
    playerYOffset = Camera_GetTrackedActorHeight(camera);
    camera->trackActorPosRot = playerPosShape;
    camera->dist = eyeNextAtOffset.r = 180.0f;
    camera->inputDir.y = playerPosShape.rot.y;
    eyeNextAtOffset.yaw = BINANG_ROT180(camera->inputDir.y);
    camera->inputDir.x = eyeNextAtOffset.pitch = 0x71C;
    camera->inputDir.z = 0;
    camera->camDir = camera->inputDir;
    camera->xzSpeed = 0.0f;
    camera->playerPosDelta.y = 0.0f;
    camera->at = playerPosShape.pos;
    camera->at.y += playerYOffset;

    camera->atActorOffset.x = 0;
    camera->atActorOffset.y = playerYOffset;
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

    Camera_SetFlags(camera, 0x4);

    camera->paramFlags = 0;
    camera->nextBgCamDataId = -1;
    camera->yOffsetUpdateRate = 0.01f;
    camera->xzOffsetUpdateRate = 0.01f;
    camera->fovUpdateRate = 0.01f;
    camera->atLERPStepScale = 1;
    Camera_ResetAnim(camera, camera->mode);

    if (camera == &camera->globalCtx->mainCamera) {
        sCameraInterfaceFlags = 0xB200;
        func_800F15D8(camera);
    } else {
        sCameraInterfaceFlags = 0x3200;
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

    if (!(camera->flags2 & 2) || (sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
        return false;
    }

    if (camera->flags2 & 0x200) {
        if (func_800CB8C8(camera) != 0) {
            if (!Camera_IsPlayerFormZora(camera)) {
                Camera_ChangeSettingFlags(camera, CAM_SET_CIRCLE5, 0x4 | 0x2);
            } else {
                Camera_ChangeSettingFlags(camera, CAM_SET_ZORA, 0x4 | 0x2);
            }
            Camera_SetFlags(camera, 0x8000);
        } else if (camera->flags2 & (s16)0x8000) {
            Camera_ChangeSettingFlags(camera, *waterPrevCamSetting, 0x4 | 0x2); // unk11E
            Camera_UnsetFlags(camera, 0x8000);
        }
    }

    if (!(camera->flags2 & (s16)0x8000)) {
        camSetting = Camera_GetWaterBoxCamSetting(camera, &waterY);
        if (camSetting == -2) {
            // CAM_SET_NONE
            if (!(camera->flags2 & 0x200)) {
                Camera_SetFlags(camera, 0x200);
                camera->waterPrevBgCamDataId = camera->bgCamDataId;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerGroundY) < 11.0f) ||
                ((func_800CB880(camera) != 0) && !func_800CBB58(camera))) {
                prevBgId = camera->bgId;
                camera->bgId = BGCHECK_SCENE;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL3, 0x2);
                *waterPrevCamSetting = camera->setting;
                camera->bgId = prevBgId;
                camera->bgCamDataId = -2;
            }

        } else if (camSetting != -1) {
            // player is in a water box
            if (!(camera->flags2 & 0x200)) {
                Camera_SetFlags(camera, 0x200);
                camera->waterPrevBgCamDataId = camera->bgCamDataId;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerGroundY) < 11.0f) ||
                ((func_800CB880(camera) != 0) && !func_800CBB58(camera))) {
                prevBgId = camera->bgId;
                camera->bgId = BGCHECK_SCENE;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, camSetting, 0x2);
                *waterPrevCamSetting = camera->setting;
                camera->bgId = prevBgId;
            }

        } else if (camera->flags2 & 0x200) {
            // player is out of a water box.
            Camera_UnsetFlags(camera, 0x200);
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
        if ((dayTime > CLOCK_TIME(0, 0)) && (dayTime < CLOCK_TIME(6, 0)) && ((earthquakeFreq[dayTime >> 12] & dayTime) == 0) && (Quake_NumActiveQuakes() < 2)) {
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
        if (((((dayTime + 0x4D2) & 0xDFFC) == 0xC000) || ((camera->globalCtx->state.frames % 1024) == 0)) && (Quake_NumActiveQuakes() < 2)) {
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
 * TODO: This description and name is wrong, there is no hot room in MM
 * Sets the room to be hot camera quake flag
 */
s32 Camera_SetRoomHotFlag(Camera* camera) {
    Quake2_ClearType(1);
    if (camera->globalCtx->roomCtx.currRoom.unk2 == 3) {
        Quake2_SetType(1);
    }
    return true;
}

s32 func_800DE890(Camera* camera) {
    switch(func_800CBB88(camera)) {
        case 1:
            if (Quake2_GetType() != 0x40) {
                Quake2_SetType(0x40);
                Quake2_SetCountdown(12);
            }
            break;
        //! @bug: Case 2 is impossible to achieve
        case 2:
            if (Quake2_GetType() != 0x80) {
                Quake2_SetType(0x80);
                Quake2_SetCountdown(5);
            }
            break;
        case 3:
            if (Quake2_GetType() != 0x100) {
                Quake2_SetType(0x100);
                Quake2_SetCountdown(15);
            }
            break;
    }
    return true;
}

s32 func_800DE954(Camera* camera) {
    Player* player = (Player*)camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first;

    if ((camera->camId == CAM_ID_MAIN) && ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) && (player->currentMask == PLAYER_MASK_GIANTS_MASK)) {
        Camera_ChangeSettingFlags(camera, CAM_SET_GIANT, 0x2);
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
    s32 sp94;
    CollisionPoly* sp90;
    CollisionPoly* sp8C;
    f32 sp88;
    f32 sp84;
    f32 viewFov;
    DynaPolyActor* meshActor;
    PosRot sp68;
    QuakeCamCalc quake;
    Actor* trackActor = camera->trackActor;
    VecSph sp3C;
    s16 bgCamDataId;
    f32 playerGroundY;

    if (camera->status == CAM_STATUS_CUT) {
        *inputDir = camera->inputDir;
        return inputDir;

    }

    sUpdateCameraDirection = false;
    sIsFalse = false;

    if (camera->globalCtx->view.unk164 == 0) {
        if (camera->trackActor != NULL) {
            if ((Actor*)camera->trackActor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
                Actor_GetWorldPosShapeRot(&sp68, (Actor*)camera->trackActor);
            } else {
                Actor_GetWorld(&sp68, (Actor*)camera->trackActor);
            }
            camera->playerPosDelta.x = sp68.pos.x - camera->trackActorPosRot.pos.x;
            camera->playerPosDelta.y = sp68.pos.y - camera->trackActorPosRot.pos.y;
            camera->playerPosDelta.z = sp68.pos.z - camera->trackActorPosRot.pos.z;

            sp98 = 0;
            if (func_800CB7F8(camera)) {
                if (((Player*)trackActor)->rideActor->floorPoly != NULL) {
                    sp90 = ((Player*)trackActor)->rideActor->floorPoly;
                    camera->bgId = ((Player*)trackActor)->rideActor->floorBgId;
                    camera->playerGroundY = ((Player*)trackActor)->rideActor->floorHeight;
                    sp98 = 3;
                }
            } else if (func_800CB7CC(camera)) {
                if (((Actor*)camera->trackActor)->floorPoly != NULL) {
                    sp90 = ((Actor*)camera->trackActor)->floorPoly;
                    camera->bgId = ((Actor*)camera->trackActor)->floorBgId;
                    camera->playerGroundY = ((Actor*)camera->trackActor)->floorHeight;
                    sp98 = 1;
                }
            } else {
                spA0 = sp68.pos;
                spA0.y += Camera_GetTrackedActorHeight(camera);
                playerGroundY = func_800C41E4(camera->globalCtx, &camera->globalCtx->colCtx, &sp90, &bgId, (Actor*)camera->trackActor, &spA0);
                if (playerGroundY != BGCHECK_Y_MIN) {
                    camera->bgId = bgId;
                    camera->playerGroundY = playerGroundY;
                    sp98 = 2;
                }
            }

            if ((sp98 != 0) && (Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerGroundY) < 11.0f)) {
                meshActor = BgCheck_GetActorOfMesh(&camera->globalCtx->colCtx, camera->bgId);
                if (meshActor != NULL) {
                    camera->floorNorm.x = COLPOLY_GET_NORMAL(sp90->normal.x);
                    camera->floorNorm.y = COLPOLY_GET_NORMAL(sp90->normal.y);
                    camera->floorNorm.z = COLPOLY_GET_NORMAL(sp90->normal.z);
                    camera->playerPosDelta.x -= meshActor->actor.world.pos.x - camera->meshActorPos.x;
                    camera->playerPosDelta.y -= meshActor->actor.world.pos.y - camera->meshActorPos.y;
                    camera->playerPosDelta.z -= meshActor->actor.world.pos.z - camera->meshActorPos.z;
                    camera->meshActorPos = meshActor->actor.world.pos;
                }
            }

            sp88 = func_800CB780(camera) * 1.5f;
            sp84 = Camera_Vec3fMagnitude(&camera->playerPosDelta);
            camera->xzSpeed = OLib_ClampMaxDist(sp84, sp88);
            camera->speedRatio = OLib_ClampMaxDist(sp84 / sp88, 1.8f);
            camera->trackActorPosRot = sp68;

            if (camera->camId == CAM_ID_MAIN) {
                Camera_CheckWater(camera);
                Camera_SetRoomHotFlag(camera);
                Camera_EarthquakeDay3(camera);
                func_800DE890(camera);
            }

            if (camera->unk150 != 0) {
                Camera_SetFlags(camera, 0x400);
            } else if (!(camera->flags2 & 0x4)) {
                camera->nextBgCamDataId = -1;
            }

            sp94 = 0;
            bgId = camera->bgId;

            if ((camera->flags2 & 1) && (camera->flags2 & 4) && !(camera->flags2 & 0x400) && 
                (!(camera->flags2 & 0x200) || func_800CBB58(camera)) && !(camera->flags2 & (s16)0x8000) && 
                !func_800CB7F8(camera) && !func_800DE954(camera) && !func_800CB828(camera) && (sp98 != 0)) {

                bgCamDataId = Camera_GetDataIdxForPoly(camera, &bgId, sp90);
                if ((bgCamDataId != -1) && (camera->bgId == BGCHECK_SCENE)) {
                    if (func_800CBC00(camera) == 0) {
                        camera->nextBgCamDataId = bgCamDataId | 0x1000;
                    }
                }
                spA0 = sp68.pos;
                spA0.y += Camera_GetTrackedActorHeight(camera);
                playerGroundY = func_800C4488(&camera->globalCtx->colCtx, &sp8C, &bgId, &spA0);
                if ((playerGroundY != BGCHECK_Y_MIN) && (sp8C != sp90) && (bgId == BGCHECK_SCENE) && ((camera->playerGroundY - 2.0f) < playerGroundY)) {
                    bgCamDataId = Camera_GetDataIdxForPoly(camera, &bgId, sp8C);
                    if ((bgCamDataId != -1) && (bgId == BGCHECK_SCENE)) {
                        camera->nextBgCamDataId = bgCamDataId | 0x1000;
                        sp94 = 1;
                    }
                }

            }
            if (camera->unk150 != 0) {
                camera->unk150--;
                if (camera->unk150 == 0) {
                    Camera_UnsetFlags(camera, 0x400);
                    sp94 = 5;
                }
            }
            if (((camera->camId == CAM_ID_MAIN) || (camera->flags2 & 0x40)) &&
                ((camera->bgId == BGCHECK_SCENE) || ((bgId == BGCHECK_SCENE) && (sp94 != 0))) &&
                (camera->nextBgCamDataId != -1) && (camera->unk150 == 0) &&
                ((Camera_fabsf(camera->trackActorPosRot.pos.y - camera->playerGroundY) < 11.0f) || (sp94 != 0)) &&
                (!(camera->flags2 & 0x200) || func_800CBB58(camera))) {

                Camera_ChangeDataIdx(camera, camera->nextBgCamDataId);
                camera->nextBgCamDataId = -1;
                if (camera->timer != 0) {
                    camera->unk150 = camera->timer;
                    camera->timer = 0;
                }       
            }
        }

        if (camera->status == CAM_STATUS_WAIT) {
            *inputDir = camera->inputDir;
            return inputDir;
        } 
        
        camera->flags1 = 0;
        Camera_UnsetFlags(camera, 0x400 | 0x20);
        Camera_SetFlags(camera, 0x10);

    }
        
    sCameraFunctions[sCameraSettings[camera->setting].cameraModes[camera->mode].funcIdx](camera);
    if (sCameraInitCounter != 0) {
        sCameraInitCounter--;
    }

    if (camera->status == CAM_STATUS_ACTIVE) {
        if (((sCameraInitCounter != 0) || func_800CB854(camera)) && (camera->camId == CAM_ID_MAIN)){
            sCameraInterfaceFlags = 0x3200;
            Camera_UpdateInterface(sCameraInterfaceFlags);
        } else if ((camera->globalCtx->unk_18B4A != 0) && (camera->camId != CAM_ID_MAIN)) {
            sCameraInterfaceFlags = 0xFF00;
            Camera_UpdateInterface(sCameraInterfaceFlags);
        } else {
            Camera_UpdateInterface(sCameraInterfaceFlags);
        }
    }

    if (camera->status == CAM_STATUS_UNK3) {
        *inputDir = camera->inputDir;
        return inputDir;
    }

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
    //! @bug: Condition is impossible to achieve
    } else if (sIsFalse) {
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

    if (camera->paramFlags & 4) {
        camera->paramFlags &= ~4;
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
    Camera_SetFlags(camera, 0x8 | 0x4); // flag 0x8 is set only immediately to be unset
    Camera_UnsetFlags(camera, 0x1000 | 0x8);
    return true;
}

s32 Camera_ChangeModeFlags(Camera* camera, s16 mode, u8 flags) {
    static s32 modeChangeFlags = 0;

    if (camera->setting == CAM_SET_TELESCOPE) {
        if ((mode == CAM_MODE_FIRSTPERSON) || (mode == CAM_MODE_DEKUHIDE)) {
            flags = 1;
        }
    }   

    if ((camera->flags2 & 0x20) && (flags == 0)) {
        camera->flags1 |= 0x20;
        return -1;
    }

    if (!(sCameraSettings[camera->setting].validModes & (1 << mode))) {
        if (camera->mode != CAM_MODE_NORMAL) {
            camera->mode = CAM_MODE_NORMAL;
            Camera_ResetAnim(camera, camera->mode);
            func_800DF498(camera);
            return 0xC0000000 | mode;
        } else {
            camera->flags1 |= 0x20;
            camera->flags1 |= 2;
            return 0;
        }
    } else {
        if ((mode == camera->mode) && (flags == 0)) {
            camera->flags1 |= 0x20;
            return -1;
        }
        camera->flags1 |= 0x20;
        camera->flags1 |= 2;
        
        Camera_ResetAnim(camera, mode);

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

        switch(camera->mode) {
            case CAM_MODE_FIRSTPERSON:
                if (modeChangeFlags & 0x20) {
                    camera->animState = 10;
                }
                break;
            case CAM_MODE_JUMP:
            case CAM_MODE_HANG:
                if (modeChangeFlags & 0x10) {
                    camera->animState = 20;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_CHARGE:
                if (modeChangeFlags & 0x10) {
                    camera->animState = 20;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_FOLLOWTARGET:
                if (modeChangeFlags & 8) {
                    camera->animState = 10;
                }
                modeChangeFlags |= 1;
                break;
            case CAM_MODE_BATTLE:
                if (modeChangeFlags & 4) {
                    camera->animState = 10;
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
                    camera->animState = 20;
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
    return Camera_ChangeModeFlags(camera, mode, 0);
}

s32 Camera_CheckValidMode(Camera* camera, s16 mode) {
    if (camera->flags2 & 0x20) {
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
    if ((camera->flags1 & 1) && ((sCameraSettings[camera->setting].unk_04 & 0xF) >= (sCameraSettings[setting].unk_04 & 0xF))) {
        camera->flags1 |= 0x10;
        if (!(flags & 2)) {
            camera->flags1 |= 1;
        }
        return -2;
    }

    if (setting == CAM_SET_NONE) {
        return 0;
    }

    if (setting >= CAM_SET_MAX) {
        return -99;
    }
    
    if ((setting == camera->setting) && !(flags & 1)) {
        camera->flags1 |= 0x10;
        if (!(flags & 2)) {
            camera->flags1 |= 1;
        }
        return -1;
    }

    camera->flags1 |= 0x10;

    if (!(flags & 2)) {
        camera->flags1 |= 1;
    }

    func_800DF498(camera);

    if (!(sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
        camera->prevSetting = camera->setting;
    }

    if (flags & 8) {
        camera->bgCamDataId = camera->prevBgCamDataId;
        camera->prevBgCamDataId = -1;
    } else if (!(flags & 4)) {
        if (!(sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
            camera->prevBgCamDataId = camera->bgCamDataId;
        }
        camera->bgCamDataId = -1;
    }

    camera->setting = setting;

    if (Camera_ChangeModeFlags(camera, camera->mode, 1) >= 0) {
        Camera_ResetAnim(camera, camera->mode);
    }

    return setting;
}

s32 Camera_ChangeSetting(Camera* camera, s16 setting) {
    s32 settingChangeSuccessful = Camera_ChangeSettingFlags(camera, setting, 0x0);

    if (settingChangeSuccessful >= 0) {
        camera->bgCamDataId = -1;
    }
    return settingChangeSuccessful;
}

s32 Camera_ChangeDataIdx(Camera* camera, s32 bgCamDataId) {
    s16 setting;

    if (bgCamDataId == -1 || bgCamDataId == camera->bgCamDataId) {
        camera->flags1 |= 0x40;
        return -1;
    }

    if (bgCamDataId < 0) {
        setting = D_801B9CE4[bgCamDataId];
    } else if (!(camera->flags1 & 0x40)) {
        setting = Camera_GetCamDataSetting(camera, bgCamDataId);
    } else {
        return -1;
    }

    camera->flags1 |= 0x40;
    // Sets camera setting based on bg/scene data
    if ((Camera_ChangeSettingFlags(camera, setting, 0x4 | 0x1) >= 0) || (sCameraSettings[camera->setting].unk_04 & 0x80000000)) {
        camera->bgCamDataId = bgCamDataId;
        camera->flags1 |= 4;
        Camera_ResetAnim(camera, camera->mode);
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

    Quake_SetSpeed(quakeIdx, 0x61A8);
    Quake_SetQuakeValues(quakeIdx, y, 0, 0, 0);
    Quake_SetCountdown(quakeIdx, countdown);
    return true;
}

s32 Camera_SetParam(Camera* camera, s32 param, void* value) {
    s32 pad[3];

    if (value != NULL) {
        switch (param) {
            case 1:
                camera->paramFlags &= ~(0x10 | 0x8 | 0x1);
                camera->at = *(Vec3f*)value;
                break;
            case 16:
                camera->paramFlags &= ~(0x10 | 0x8 | 0x1);
                camera->targetPosRot.pos = *(Vec3f*)value;
                break;
            case 8:
                camera->target = (Actor*)value;
                camera->paramFlags &= ~(0x10 | 0x8 | 0x1);
                break;
            case 2:
                camera->eye = camera->eyeNext = *(Vec3f*)value;
                break;
            case 4:
                camera->up = *(Vec3f*)value;
                break;
            case 0x40:
                camera->roll = DEGF_TO_BINANG(*(f32*)value);
                break;
            case 0x20:
                camera->fov = *(f32*)value;
                break;
            default:
                return false;
        }
        camera->paramFlags |= param;
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

s32 Camera_ResetAnimUnused(Camera* camera) {
    camera->animState = 0;
    return true;
}

/**
 * Unused Remnant of OoT
 */
s32 Camera_SetCSParams(Camera* camera, CutsceneCameraPoint* atPoints, CutsceneCameraPoint* eyePoints, Player* player,
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
    DoorParams* doorParams = (DoorParams*)camera->paramData;

    if (camera->setting == CAM_SET_DOORC) {
        return 0;
    }

    doorParams->doorActor = doorActor;
    doorParams->timer1 = timer1;
    doorParams->timer2 = timer2;
    doorParams->timer3 = timer3;
    doorParams->bgCamDataId = bgCamDataId;

    if (bgCamDataId == -99) {
        Camera_ResetAnim(camera, camera->mode);
        return -99;
    }

    if (bgCamDataId == -1) {
        Camera_ChangeSettingFlags(camera, CAM_SET_DOORC, 0x0);
    } else if (bgCamDataId == -2) {
        Camera_ChangeSettingFlags(camera, CAM_SET_SPIRAL, 0x0);
    } else {
        camera->nextBgCamDataId = bgCamDataId;
        camera->unk150 = timer1;
        camera->timer = timer2 + timer3;
    }

    Camera_ResetAnim(camera, camera->mode);
    return -1;
}

s32 Camera_Copy(Camera* dstCamera, Camera* srcCamera) {
    s32 pad;

    dstCamera->atActorOffset.z = 0.0f;
    dstCamera->atActorOffset.y = 0.0f;
    dstCamera->atActorOffset.x = 0.0f;
    dstCamera->atLERPStepScale = 0.1f;
    dstCamera->at = srcCamera->at;

    dstCamera->eye = dstCamera->eyeNext = srcCamera->eye;

    dstCamera->dist = OLib_Vec3fDist(&dstCamera->at, &dstCamera->eye);
    dstCamera->fov = srcCamera->fov;
    dstCamera->roll = srcCamera->roll;
    Camera_SetUpdateRatesSlow(dstCamera);

    if (dstCamera->trackActor != NULL) {
        if ((Actor*)dstCamera->trackActor == dstCamera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
            Actor_GetWorldPosShapeRot(&dstCamera->trackActorPosRot, (Actor*)dstCamera->trackActor);
        } else {
            Actor_GetWorld(&dstCamera->trackActorPosRot, (Actor*)dstCamera->trackActor);
        }
        Camera_UpdateAtActorOffset(dstCamera, &dstCamera->trackActorPosRot.pos);
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
    Camera_SetFlags(camera, 0x8);
    if ((camera->camId == CAM_ID_MAIN) && (camera->globalCtx->activeCamera != CAM_ID_MAIN)) {
        Camera_SetFlags(camera->globalCtx->cameraPtrs[camera->globalCtx->activeCamera], 0x8);
        return camera->globalCtx->activeCamera;
    } else {
        return camera->camId;
    }
}

void Camera_SetToTrackActor(Camera* camera, Actor* actor) {
    camera->trackActor = actor;
    if (actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        Actor_GetWorldPosShapeRot(&camera->trackActorPosRot, actor);
    } else {
        Actor_GetWorld(&camera->trackActorPosRot, (Actor*)camera->trackActor);
    }

    camera->animState = 0;
}

void func_800E0308(Camera* camera, Actor* actor) {
    camera->target = actor;
    camera->animState = 20;
}

f32 func_800E031C(Camera* camera) {
    if (camera->flags2 & 0x100) {
        return camera->waterYPos;
    } else {
        return BGCHECK_Y_MIN;
    }
}

void func_800E0348(Camera* camera) {
    if (!RELOAD_PARAMS) {
        camera->animState = 999;
        Camera_SetFlags(camera, 0x400 | 0x10 | 0x4 | 0x2);
    } else {
        camera->animState = 666;
    }
}
