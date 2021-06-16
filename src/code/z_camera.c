#include "ultra64.h"
#include "global.h"

#include "z_camera_data.c"

f32 Camera_fabsf(f32 f) {
    return ABS(f);
}

f32 Camera_Vec3fMagnitude(Vec3f* vec) {
    return sqrtf(SQ(vec->x) + SQ(vec->y) + SQ(vec->z));
}

// ISMATCHING: Need to move rodata
// D_801DCDC0 = 0.4f
/**
 * Interpolates along a curve between 0 and 1 with a period of
 * -a <= p <= a at time `b`
 */
#ifdef NON_MATCHING
f32 Camera_InterpolateCurve(f32 a, f32 b) {
    f32 ret;
    f32 absB;
    f32 t = 0.4f;
    f32 t2;
    f32 t3;
    f32 t4;

    absB = Camera_fabsf(b);
    if (a < absB) {
        ret = 1.0f;
    } else {
        t2 = 1.0f - t;
        if ((a * t2) > absB) {
            t3 = SQ(b) * (1.0f - t);
            t4 = SQ(a * t2);
            ret = t3 / t4;
        } else {
            t3 = SQ(a - absB) * t;
            t4 = SQ(0.4f * a);
            ret = 1.0f - (t3 / t4);
        }
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_InterpolateCurve.asm")
#endif

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

// ISMATCHING: Need to move rodata
// D_801DCDC4 = 0.05f
#ifdef NON_MATCHING
void func_800CB544(Camera* camera) {
    camera->yawUpdateRateInv = 100.0f;
    camera->pitchUpdateRateInv = 16.0f;
    camera->rUpdateRateInv = 20.0f;
    camera->xzOffsetUpdateRate = 0.05f;
    camera->yOffsetUpdateRate = 0.05f;
    camera->fovUpdateRate = 0.05f;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB544.asm")
#endif

// ISMATCHING: Need to move rodata
// D_801DCDC8 = 0.01
// D_801DCDCC = 0.1
#ifdef NON_MATCHING
void func_800CB584(Camera* camera) {
    camera->rUpdateRateInv = 50.0f;
    camera->pitchUpdateRateInv = 100.0f;
    camera->yawUpdateRateInv = 50.0f;
    camera->xzOffsetUpdateRate = 0.01f;
    camera->yOffsetUpdateRate = 0.1f;
    camera->fovUpdateRate = 0.01f;
    if (camera->speedRatio > 1.0f) {
        camera->speedRatio = 1.0f;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB584.asm")
#endif

// ISMATCHING: Need to move rodata
// D_801DCDD0 = 0.01
#ifdef NON_MATCHING
void func_800CB5DC(Camera* camera) {
    camera->rUpdateRateInv = 1800.0f;
    camera->yawUpdateRateInv = 1800.0f;
    camera->pitchUpdateRateInv = 1800.0f;
    camera->xzOffsetUpdateRate = 0.01;
    camera->yOffsetUpdateRate = 0.01;
    camera->fovUpdateRate = 0.01;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB5DC.asm")
#endif

Vec3f* Camera_Vec3sToVec3f(Vec3f* dest, Vec3s* src) {
    Vec3f copy;

    copy.x = src->x;
    copy.y = src->y;
    copy.z = src->z;

    *dest = copy;
    return dest;
}

s16 func_800CB674(s16 arg0, s16 arg1, f32 arg2) {
    return (s16)(arg0 - arg1) * arg2;
}

void func_800CB6C8(Camera* camera, Vec3f* vec) {
    camera->posOffset.x = camera->focalPoint.x - vec->x;
    camera->posOffset.y = camera->focalPoint.y - vec->y;
    camera->posOffset.z = camera->focalPoint.z - vec->z;
}

f32 func_800CB700(Camera* camera) {
    ActorPlayer* player = camera->player;
    f32 ret;
    Vec3f vec;
    f32 pad[2];

    if (&player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        ret = func_800B6FC8(player);
    } else {
        func_800B81E0(&vec, player); // TODO: camera as arg2? functions.h
        ret = vec.y - camera->playerPosRot.pos.y;
        if (ret == 0.0f) {
            ret = 10.0f;
        }
    }
    return ret;
}

f32 func_800CB780(Camera* camera) {
    ActorPlayer* player = camera->player;
    f32 ret;

    if (&player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        ret = func_800B7090(player);
    } else {
        ret = 10.0f;
    }

    return ret;
}

s32 func_800CB7CC(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->unkA74 & 0x10;
    }

    return 0;
}

s32 func_800CB7F8(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->stateFlags1 & 0x800000;
    }

    return 0;
}

s32 func_800CB828(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->unkA74 & 0x2000;
    }

    return 0;
}

s32 func_800CB854(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->stateFlags1 & 0x20;
    }

    return 0;
}

// related to player swimming (player->stateFlags1 & 0x8000000) is player swimming
s32 func_800CB880(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        if (player->unkA74 & 0x8000) {
            return 0x3E7;
        } else {
            return player->stateFlags1 & 0x8000000;
        }
    }

    return 0;
}

s32 func_800CB8C8(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->unkA70 & 0x800;
    }

    return 0;
}

s32 func_800CB8F4(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->linkForm == 2;
    }

    return 0;
}

s32 func_800CB924(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->unkA74 & 0x1000;
    }
    return 0;
}

#ifdef NON_EQUIVALENT
s32 func_800CB950(Camera* camera) {
    ActorPlayer* player;
    s32 phi_return;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        if (Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) {
            phi_return = 1;
        } else {
            phi_return = 0;
        }

        if (phi_return == 0) {

            if (D_801DCDD4 < camera->player->base.gravity) {
                phi_return = 1;
            } else {
                phi_return = 0;
            }
            if (phi_return == 0) {
                phi_return = camera->player->stateFlags1 & 0x200000;
            }
        }
    } else {
        phi_return = 1;
    }

    return phi_return;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB950.asm")
#endif

s32 func_800CBA08(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->stateFlags1 & 4;
    }

    return 0;
}

s32 func_800CBA34(Camera* camera) {
    ActorPlayer* player = camera->player;
    s32 ret;

    if (&player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        ret = !!(player->stateFlags1 & 0x1000);
        if (ret == 0) {
            ret = !!(player->unkA74 & 0x100);
        }
        return ret;
    }

    return 0;
}

s32 func_800CBA7C(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->unkA70 & 0x800000;
    }

    return 0;
}

s32 func_800CBAAC(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->unkADB;
    }

    return 0;
}

s32 func_800CBAD4(Vec3f* dst, Camera* camera) {
    PosRot sp24;
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        *dst = player->bodyPartsPos[0];
        return dst;
    }

    func_800B8248(&sp24, camera->player);
    *dst = sp24.pos;
    return dst;
}

s32 func_800CBB58(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->currentBoots == 5;
    }

    return 0;
}

s32 func_800CBB88(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        if ((player->unkADB != 0) && (player->unkADA == 26)) {
            return 3;
        }
        if ((player->unkA70 & 0x20000) || ((player->unkADB != 0) && (player->unkADA == 29))) {
            return 1;
        }
    }

    return 0;
}

s32 func_800CBC00(Camera* camera) {
    ActorPlayer* player = camera->player;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        return player->stateFlags1 & 0x200000;
    }

    return 0;
}

s32 func_800CBC30(Camera* camera, f32 arg1, f32 arg2) {
    if ((camera->playerGroundY != camera->waterYPos) && (camera->waterYPos < arg1) && (camera->waterYPos > arg2)) {
        return true;
    }

    return false;
}

// OoT func_80043F94
// D_801DCDD8 = 3.051851e-05
// D_801DCDE4 = 3.051851e-05
#ifdef NON_EQUIVALENT
s32 func_800CBC84(Camera* camera, Vec3f* from, CamColChk* to, s32 arg3) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx; // sp74
    Vec3f toNewPos;                                        // 68-6C-70
    Vec3f toPoint;                                         // 5C-60-64
    Vec3f fromToNorm;                                      // 50-54-58
    f32 floorPolyY;
    CollisionPoly* floorPoly; // cosYaw
    s32 floorBgId;            // sp44
    s32 chkWall;
    s32 chkCeil;

    OLib_Vec3fDistNormalize(&fromToNorm.x, from, &to->pos);
    toPoint.x = to->pos.x + fromToNorm.x;
    toPoint.y = to->pos.y + fromToNorm.y;
    toPoint.z = to->pos.z + fromToNorm.z;
    chkWall = (arg3 & 1) ? 0 : 1;
    chkCeil = (arg3 & 2) ? 0 : 1;
    floorPoly = NULL;

    if (!BgCheck_CameraLineTest1(colCtx, from, &toPoint, &toNewPos, &to->poly, chkWall, 1, chkCeil, -1, &floorBgId)) {
        toNewPos = to->pos;
        toNewPos.y += 5.0f;
        if ((arg3 != 0) && func_800CB7CC(camera)) {
            to->poly = camera->player->base.floorPoly;
            floorBgId = camera->player->base.floorBgId;
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
            floorPolyY = func_800C4488(colCtx, &floorPoly, &floorBgId, &toNewPos);
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
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBC84.asm")
#endif

// OoT func_80044340
void func_800CBFA4(Camera* camera, Vec3f* arg1, Vec3f* arg2, s32 arg3) {
    CamColChk sp20;
    Vec3s unused;

    sp20.pos = *arg2;
    func_800CBC84(camera, arg1, &sp20, arg3);
    *arg2 = sp20.pos;
}

// OoT Camera_BGCheckInfo
// D_801DCDE8 = 3.051851e-05
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 func_800CC000(Camera* camera, Vec3f* from, CamColChk* to) {
    CollisionPoly* floorPoly;
    Vec3f toNewPos;
    Vec3f fromToNorm;

    if (BgCheck_CameraLineTest1(&camera->globalCtx->colCtx, from, to, &toNewPos, &to->poly, 1, 1, 1, -1, &to->bgId)) {
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
#else
s32 func_800CC000(Camera* camera, Vec3f* from, CamColChk* to);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC000.asm")
#endif

s32 func_800CC128(Camera* camera, Vec3f* from, Vec3f* to) {
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

// D_801DCDEC = 0.9f
#ifdef NON_EQUIVALENT
s16 func_800CC260(Camera* camera, Vec3f* arg1, Vec3f* arg2, VecSph* arg3, Actor** exclusions, s32 numExclusions) {
    // sp 70-98 likely all one struct
    VecSph sp90; // 90-94-96
    s32 sp88;
    Vec3f sp70; // 70-74-78 (7C-80-84?)
    Vec3f sp64; // 64-68-6C
    ActorPlayer* player = camera->globalCtx->actorCtx.actorList[2].first;
    // s32 phi_s3_2;
    // s16 phi_v1;
    s32 pitch;
    s32 ret;
    s32 i;

    sp64 = *arg2;
    func_800B81E0(&sp70, player); // TODO: functions.h
    sp90.r = arg3->r;
    sp90.pitch = arg3->pitch;
    sp88 = 14;

    for (i = 0; i < sp88;) {
        func_8010C7B8(arg1, arg2, &sp90);
        if (Camera_CheckOOB(camera, arg1, &sp64) || func_800CBC30(camera, arg2->y, arg1->y) ||
            CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colCheckCtx, arg2, arg1, exclusions,
                                       numExclusions)) {
            sp90.yaw = D_801B9E18[i] + arg3->yaw;
            pitch = (arg3->pitch * Rand_ZeroOne());
            sp90.pitch = D_801B9E34[i] + pitch;
            if (sp90.pitch >= 0x36B1) {
                sp90.pitch += -0x3E80;
            }
            if (sp90.pitch < -0x36B0) {
                sp90.pitch += 0x3A98;
            }
            sp90.r *= 0.9f;
            sp64 = *arg2;
            i++;
        }
    }

    *arg3 = sp90;

    // phi_v1 = phi_s3_2;
    if (i == 14) {
        ret = -1;
    } else {
        ret = i;
    }

    return ret;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC260.asm")
#endif

// OoT Camera_GetFloorYLayer
// D_801DCDF0 =  = 3.051851e-05
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
f32 func_800CC488(Camera* camera, Vec3f* norm, Vec3f* pos, s32* bgId) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    CollisionPoly* floorPoly;
    f32 floorY = func_800C40B4(colCtx, &floorPoly, bgId, pos);

    if (floorY == BGCHECK_Y_MIN) {
        norm->x = 0.0f;
        norm->y = 1.0f;
        norm->z = 0.0f;
    } else {
        norm->x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        norm->y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        norm->z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
    }

    return floorY;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC488.asm")
#endif

// TODO: Is this s32 or void return? It's not f32 return.
s32 func_800CC56C(Camera* camera, Vec3f* arg1) {
    Vec3f pos;  // 2C
    Vec3f norm; // 20
    s32 bgId;

    pos = *arg1;
    pos.y += 80.0f;
    return func_800CC488(camera, &norm, &pos, &bgId); // TODO: functions.h
}

// D_801DCDF4 = 3.051851e-05
// D_801DCDF8 = 3.051851e-05
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
f32 func_800CC5C8(Camera* camera, Vec3f* norm, Vec3f* pos, s32* bgId) {
    CollisionPoly* floorPoly;
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    f32 floorY;

    if (camera->player != NULL) {
        // OoT BgCheck_EntityRaycastFloor5
        floorY =
            func_800C41E4(camera->globalCtx, &camera->globalCtx->colCtx, &floorPoly, bgId, &camera->player->base, pos);
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
#else
f32 func_800CC5C8(Camera* camera, Vec3f* norm, Vec3f* pos, s32* bgId);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC5C8.asm")
#endif

s16 func_800CC740(Camera* camera, u32 flags) {
    if (flags & 0x1000) {
        return func_800C9728(&camera->globalCtx->colCtx, flags & ~0x1000, 50); // TODO: functions.h
    } else {
        return func_80169C64(camera->globalCtx, flags); // TODO: functions.h
    }
}

s32 func_800CC7A8(Camera* camera, u32 flags) {
    if (flags & 0x1000) {
        return func_800C98CC(&camera->globalCtx->colCtx, flags & ~0x1000, 50); // TODO: functions.h
    } else {
        return func_80169C84(camera->globalCtx, flags); // TODO: functions.h
    }
}

/**
 * Gets the scene's camera index for the poly `poly`, returns -1 if
 * there is no camera data for that poly.
 */
s32 Camera_GetDataIdxForPoly(Camera* camera, s32* bgId, CollisionPoly* poly) {
    s32 camDataIdx;
    s32 ret;

    camDataIdx = SurfaceType_GetCamDataIndex(&camera->globalCtx->colCtx, poly, *bgId);

    if (func_800C9728(&camera->globalCtx->colCtx, camDataIdx, *bgId) == 0) { // == CAM_SET_NONE
        ret = -1;
    } else {
        ret = camDataIdx;
    }

    return ret;
}

/**
 * Gets the Camera information for the water box the player is in.
 * Returns -1 if the player is not in a water box, or does not have a swimming state.
 * Returns -2 if there is no camera index for the water box.
 * Returns the camera data index otherwise.
 */
// Camera_GetWaterBoxDataIdx
#ifdef NON_EQUIVALENT
s32 func_800CC874(Camera* camera, f32* waterY) {
    PosRot playerPosShape;
    WaterBox* waterBox;
    s32 ret;
    s32 sp30;

    // Actor_GetWorldPosShapeRot
    func_800B8248(&playerPosShape, camera->player); // &camera->player->base
    *waterY = playerPosShape.pos.y;

    // WaterBox_GetSurface1
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

    // WaterBox_GetCamDataIndex
    ret = func_800CA648(&camera->globalCtx->colCtx, waterBox, sp30);
    if (ret == 0) {
        // no camera data idx
        return -2;
    }

    return ret;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC874.asm")
#endif

void func_800CC938(Camera* camera) { // May be void arguments
    func_800DDFE0(camera);
}

/**
 * Calculates the angle between points `from` and `to`
 */
// D_801DCDFC = 57.295776
// D_801DCE00 = 182.04167
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s16 Camera_XZAngle(Vec3f* to, Vec3f* from) {
    // Math_FAtan2F in OoT
    return DEGF_TO_BINANG(RADF_TO_DEGF(func_80086B30(from->x - to->x, from->z - to->z)));
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_XZAngle.asm")
#endif

// D_801DCE04 = 1.2
// D_801DCE08 = 0.8
// D_801DCE0C = 0.19999999
// D_801DCE10 = 57.295776
// D_801DCE14 = 182.04167
// D_801DCE18 = 57.295776
// D_801DCE1C = 182.04167
// Identical to OoT func_80044ADC
// ISMATCHING: Need to move rodata and monkaBSS
#ifdef NON_MATCHING
s16 func_800CC9C0(Camera *camera, s16 yaw, s16 arg2) {
    static f32 D_801EDBF4;
    static f32 D_801EDBF8;
    static CamColChk D_801EDC00;
    Vec3f playerPos; // sp64-68-6C
    Vec3f rotatedPos; // sp58-5C-60
    Vec3f floornorm; // sp4C
    f32 temp_f2;
    s16 temp_s0;
    s16 temp_s1;
    f32 phi_f18; // sp40
    f32 sinYaw; // sp3C
    f32 cosYaw; // sp38
    s32 bgId; // sp34
    f32 sp30;
    f32 sp2C;
    f32 phi_f16;
    f32 playerHeight;

    sinYaw = Math_SinS(yaw);
    cosYaw = Math_CosS(yaw);
    playerHeight = func_800CB700(camera); // TODO: Confirm? Or regular height
    temp_f2 = (playerHeight * 1.2f);
    sp2C = playerHeight * 2.5f;
    sp30 = playerHeight;
    playerPos.x = camera->playerPosRot.pos.x;
    playerPos.y = camera->playerGroundY + temp_f2;
    playerPos.z = camera->playerPosRot.pos.z;
    rotatedPos.x = (playerHeight * sinYaw) + playerPos.x;
    rotatedPos.y = playerPos.y;
    rotatedPos.z = (playerHeight * cosYaw) + playerPos.z;


    if (arg2 || ((camera->globalCtx->state.frames % 2) == 0)) {
        D_801EDC00.pos.x = playerPos.x + (sp2C * sinYaw);
        D_801EDC00.pos.y = playerPos.y;
        D_801EDC00.pos.z = playerPos.z + (sp2C * cosYaw); // TODO: D_801EDC04 may be D_801EDC00 or D_801EDC04.x = D_801EDC04.y
        func_800CC000(camera, &playerPos, &D_801EDC00);
        if (arg2) {
            D_801EDBF4 = D_801EDBF8 = camera->playerGroundY;
        }
    } else {
        sp2C = CamMath_DistanceXZ(&playerPos, &D_801EDC00.pos);
        D_801EDC00.pos.x += D_801EDC00.norm.x * 5.0f;
        D_801EDC00.pos.y += D_801EDC00.norm.y * 5.0f;
        D_801EDC00.pos.z += D_801EDC00.norm.z * 5.0f;
        if (sp2C < sp30) {
            sp30 = sp2C;
            D_801EDBF4 = D_801EDBF8 = func_800CC5C8(camera, &floornorm, &D_801EDC00, &bgId);
        } else {
            D_801EDBF4 = func_800CC5C8(camera, &floornorm, &rotatedPos, &bgId);
            D_801EDBF8 = func_800CC5C8(camera, &floornorm, &D_801EDC00, &bgId);
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
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC9C0.asm")
#endif

// OoT func_80044ADC
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CCCEC.asm")

Vec3f *Camera_CalcUpFromPitchYawRoll(Vec3f *dest, s16 pitch, s16 yaw, s16 roll) {
    f32 sinPitch;
    f32 cosPitch;
    f32 sinYaw;
    f32 cosYaw;
    f32 sinNegRoll;
    f32 cosNegRoll;
    Vec3f spA4;
    f32 pad;
    f32 sp54;
    f32 sp4C;
    f32 cosPitchCosYawSinRoll;
    f32 negSinPitch;
    f32 temp_f10_2;
    f32 cosPitchcosYaw;
    f32 temp_f14;
    f32 negSinPitchSinYaw;
    f32 negSinPitchCosYaw;
    f32 cosPitchSinYaw;
    f32 temp_f4_2;
    f32 temp_f6;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;

    sinPitch = Math_SinS(pitch);
    cosPitch = Math_CosS(pitch);
    sinYaw = Math_SinS(yaw);
    cosYaw = Math_CosS(yaw);
    negSinPitch = -sinPitch;
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

// D_801DCE20 = 0.12
// D_801DCE24 = 1.1
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
f32 Camera_ClampLERPScale(Camera *camera, f32 maxLERPScale) {
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
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ClampLERPScale.asm")
#endif

void Camera_ResetAnim(Camera *camera, s32 mode) {
    camera->animState = 0;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD2F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD3E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD44C.asm")

/**
 * Calculates how much to adjust the camera at's y value when on a slope.
 */
f32 Camera_CalcSlopeYAdj(Vec3f* floorNorm, s16 playerYRot, s16 eyeAtYaw, f32 adjAmt) {
    f32 tmp;
    VecSph floorNormSph;

    func_8010C6C8(&floorNormSph, floorNorm);

    tmp = Math_CosS(floorNormSph.pitch) * Math_CosS(playerYRot - floorNormSph.yaw);
    return (Camera_fabsf(tmp) * adjAmt) * Math_CosS(playerYRot - eyeAtYaw);
}

// Used in Battle1, unkArg-> related to unk data D_801AECF0, wait for unkArg info
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD6CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDE6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE79C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CEAD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CEC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CED90.asm")

s32 Camera_Noop(Camera* camera) {
    return true;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Normal1.asm")

s32 Camera_Normal2(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Normal3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Normal4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Normal0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Parallel1.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Jump2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Jump3.asm")

s32 Camera_Jump4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Jump0(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Battle1.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_KeepOn1.asm")

s32 Camera_KeepOn2(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_KeepOn3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_KeepOn4.asm")

s32 Camera_KeepOn0(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Fixed1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Fixed2.asm")

s32 Camera_Fixed3(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Fixed4(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Fixed0(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Subj1.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique5.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique6.asm")

s32 Camera_Unique7(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique8(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Unique9(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo5.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo0.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Special5.asm")

s32 Camera_Special6(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special7(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Special8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Special9.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Alloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Free.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DDFE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE0E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE0EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE954.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_SetMode.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF8EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFAC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFB14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFCB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFCDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFD04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFD78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFF18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFF34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFF44.asm")

s16 Camera_SetFlags(Camera* camera, s16 flags) {
    camera->flags |= flags;
    return camera->flags;
}

s16 Camera_ClearFlags(Camera* camera, s16 flags) {
    camera->flags &= ~flags;
    return camera->flags;
}

s32 Camera_ChangeDoorCam(Camera *camera, Actor *doorActor, s16 camDataIdx, f32 arg3, s16 timer1, s16 timer2, s16 timer3) {
    DoorParams* doorParams = (DoorParams*)camera->paramData;
    
    if (camera->setting == 8) {
        return 0;
    }

    doorParams->doorActor = doorActor;
    doorParams->timer1 = timer1;
    doorParams->timer2 = timer2;
    doorParams->timer3 = timer3;
    doorParams->camDataIdx = camDataIdx;

    if (camDataIdx == -99) {
        Camera_ResetAnim(camera, camera->mode);
        return -99;
    }

    if (camDataIdx == -1) {
        func_800DF8EC(camera, 8, 0);
    } else if (camDataIdx == -2) {
        func_800DF8EC(camera, 0x10, 0);
    } else {
        camera->nextCamDataIdx = camDataIdx;
        camera->unk_150 = timer1;
        camera->timer = timer2 + timer3;
    }

    Camera_ResetAnim(camera, camera->mode);
    return -1;
}

// D_801DD5B0 = 0.1f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 Camera_Copy(Camera* dstCamera, Camera* srcCamera) {
    s32 pad;

    dstCamera->posOffset.z = 0.0f;
    dstCamera->posOffset.y = 0.0f;
    dstCamera->posOffset.x = 0.0f;
    dstCamera->atLERPStepScale = 0.1f;
    dstCamera->focalPoint = srcCamera->focalPoint;

    dstCamera->eye = dstCamera->eyeNext = srcCamera->eye;

    dstCamera->dist = CamMath_Distance(&dstCamera->focalPoint, &dstCamera->eye);
    dstCamera->fov = srcCamera->fov;
    dstCamera->roll = srcCamera->roll;
    func_800CB5DC(dstCamera);

    if (dstCamera->player != NULL) {
        if (&dstCamera->player->base == dstCamera->globalCtx->actorCtx.actorList[2].first) {
            func_800B8248(&dstCamera->playerPosRot, dstCamera->player);
        } else {
            func_800B8214(&dstCamera->playerPosRot, dstCamera->player);
        }
        func_800CB6C8(dstCamera, &dstCamera->playerPosRot);
    }
    return true;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Copy.asm")
#endif

// Unused
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

s32 func_800E0228(void) {
    return D_801B9E14;
}

s16 func_800E0238(Camera* camera) {
    Camera_SetFlags(camera, 0x8);
    if ((camera->thisIdx == MAIN_CAM) && (camera->globalCtx->activeCamera != MAIN_CAM)) {
        Camera_SetFlags(camera->globalCtx->cameraPtrs[camera->globalCtx->activeCamera], 0x8);
        return camera->globalCtx->activeCamera;
    } else {
        return camera->thisIdx;
    }

}

void func_800E02AC(Camera* camera, ActorPlayer* player) {
    camera->player = player;
    if (&player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        func_800B8248(&camera->playerPosRot, player);
    } else {
        camera = camera;
        func_800B8214(&camera->playerPosRot, &camera->player->base);
    }

    camera->animState = 0;
}

void func_800E0308(Camera* camera, Actor* actor) {
    camera->target = actor;
    camera->animState = 20;
}

f32 func_800E031C(Camera* camera) {
    if (camera->flags & 0x100) {
        return camera->waterYPos;
    } else {
        return BGCHECK_Y_MIN;
    }
}

void func_800E0348(Camera* camera) {
    if ((camera->animState != 0) && (camera->animState != 10) && (camera->animState != 20)) {
        camera->animState = 999;
        Camera_SetFlags(camera, 0x400 | 0x10 | 0x4 | 0x2);
    } else {
        camera->animState = 666;
    }
}
