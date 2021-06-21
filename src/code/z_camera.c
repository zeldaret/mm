#include "ultra64.h"
#include "global.h"
#include "src/overlays/actors/ovl_En_Horse/z_en_horse.h"

#include "z_camera_data.c"

void func_800DDFE0(Camera* camera);

f32 Camera_fabsf(f32 f) {
    return ABS(f);
}

f32 Camera_Vec3fMagnitude(Vec3f* vec) {
    return sqrtf(SQ(vec->x) + SQ(vec->y) + SQ(vec->z));
}

// D_801DCDC0 = 0.4f
/**
 * Interpolates along a curve between 0 and 1 with a period of
 * -a <= p <= a at time `b`
 */
// ISMATCHING: Need to move rodata
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
f32 Camera_InterpolateCurve(f32 a, f32 b);
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

// D_801DCDC4 = 0.05f
// ISMATCHING: Need to move rodata
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
void func_800CB544(Camera* camera);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB544.asm")
#endif

// D_801DCDC8 = 0.01
// D_801DCDCC = 0.1
// ISMATCHING: Need to move rodata
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
void func_800CB584(Camera* camera);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB584.asm")
#endif

// D_801DCDD0 = 0.01
// ISMATCHING: Need to move rodata
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
void func_800CB5DC(Camera* camera);
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

// D_801DCDD4 = -0.1f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 func_800CB950(Camera* camera) {
    ActorPlayer* player;
    s32 phi_v0;
    s32 phi_v1;
    f32 new_var;

    if (&camera->player->base == camera->globalCtx->actorCtx.actorList[2].first) {
        new_var = Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY);

        phi_v0 = false;
        if (new_var < 11.0f) {
            phi_v0 = true;
        } 

        phi_v1 = phi_v0;

        if (!phi_v1) {

            phi_v1 = false;
            if (camera->player->base.gravity > 0.1f) {
                phi_v1 = true;
            } 

            player = camera->player;
            if (!phi_v1) {
                phi_v1 = player->stateFlags1 & 0x200000;
                phi_v1 = !!phi_v1;
            }
        }
        return phi_v1;
    } else {
        phi_v1 = 1;
    }

    return phi_v1;
}
#else
s32 func_800CB950(Camera* camera);
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
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 func_800CBC84(Camera* camera, Vec3f* from, CamColChk* to, s32 arg3) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx; // sp74
    Vec3f toNewPos;                                        // 68-6C-70
    Vec3f toPoint;                                         // 5C-60-64
    Vec3f fromToNorm;                                      // 50-54-58
    f32 floorPolyY;
    CollisionPoly** floorPoly; // cosYaw
    s32 floorBgId;            // sp44


    OLib_Vec3fDistNormalize(&fromToNorm, from, &to->pos);
    toPoint.x = to->pos.x + fromToNorm.x;
    toPoint.y = to->pos.y + fromToNorm.y;
    toPoint.z = to->pos.z + fromToNorm.z;
    floorPoly = &to->poly;

    if (!BgCheck_CameraLineTest1(colCtx, from, &toPoint, &toNewPos, floorPoly, (arg3 & 1) ? 0 : 1, 1, (arg3 & 2) ? 0 : 1, -1, &floorBgId)) {
        toNewPos = to->pos;
        if (1) {} if (1) {} // required to match
        toNewPos.y += 5.0f;
        if ((arg3 != 0) && func_800CB7CC(camera)) {
            to->poly = camera->player->base.floorPoly;
            floorBgId = camera->player->base.floorBgId;
            to->norm.x = COLPOLY_GET_NORMAL(to->poly->normal.x);
            to->norm.y = COLPOLY_GET_NORMAL(to->poly->normal.y);
            to->norm.z = COLPOLY_GET_NORMAL(to->poly->normal.z);

            if (!Math3D_LineSegVsPlane(to->norm.x, to->norm.y, to->norm.z, to->poly->dist, from, &toPoint, &toNewPos, 1)) {
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
#else
s32 func_800CBC84(Camera* camera, Vec3f* from, CamColChk* to, s32 arg3);
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
s16 func_800CC260(Camera* camera, Vec3f* arg1, Vec3f* arg2, VecSph* arg3, Actor** exclusions, s32 numExclusions);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC260.asm")
#endif

// OoT Camera_GetFloorYLayer (Camera_GetFloorYNorm)
// D_801DCDF0 =  = 3.051851e-05
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
f32 func_800CC488(Camera* camera, Vec3f* floorNorm, Vec3f* chkPos, s32* bgId) {
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    CollisionPoly* floorPoly;
    f32 floorY = func_800C40B4(colCtx, &floorPoly, bgId, chkPos);

    if (floorY == BGCHECK_Y_MIN) {
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
#else
f32 func_800CC488(Camera* camera, Vec3f* floorNorm, Vec3f* chkPos, s32* bgId);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC488.asm")
#endif

f32 func_800CC56C(Camera* camera, Vec3f* arg1) {
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

Vec3s* Camera_GetCamBGData(Camera* camera, u32 flags) {
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
s32 Camera_GetWaterBoxDataIdx(Camera* camera, f32* waterY) {
    PosRot playerPosShape;
    WaterBox* waterBox;
    s32 camDataIdx;
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

    camDataIdx = WaterBox_GetCamDataIndex(&camera->globalCtx->colCtx, waterBox, sp30);

    // -2: no camera data idx
    return (camDataIdx == 0) ? -2 : camDataIdx;
}

void func_800CC938(Camera* camera) {
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
s16 Camera_XZAngle(Vec3f* to, Vec3f* from);
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
    Vec3f playerPos;
    Vec3f rotatedPos;
    Vec3f floornorm;
    f32 temp_f2;
    s16 temp_s0;
    s16 temp_s1;
    f32 phi_f18;
    f32 sinYaw;
    f32 cosYaw;
    s32 bgId;
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
s16 func_800CC9C0(Camera *camera, s16 yaw, s16 arg2);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC9C0.asm")
#endif

// OoT func_80044ADC
#ifdef NON_EQUIVALENT
f32 func_800CCCEC(Camera* camera, s16 arg1) {
    Vec3f rotatedPos1; // 7C-80-84
    Vec3f rotatedPos2; // 70-74-78
    PosRot playerPosRot; // 5C-60-64 -- 68-6A-6C
    CamColChk sp34; // 34-38-3C -- 40-44-48 -- 4C -- 50-54-56 -- 58
    f32 playerHeight; // 2C
    f32 sinYaw; // 28
    f32 cosYaw;
    s16 sp22;
    f32 temp_f0;
    f32 ret;


    playerHeight = func_800CB700(camera);

    if (arg1 != 0) {
        D_801B9E5C = 0;
        D_801B9E60 = 0.0f;
    }

    // 94-98-9C -- A0-A2-A4
    playerPosRot = camera->playerPosRot;

    sinYaw = Math_SinS(playerPosRot.rot.y);
    cosYaw = Math_CosS(playerPosRot.rot.y);

    rotatedPos1.x = playerPosRot.pos.x + 30.0f * sinYaw;
    rotatedPos1.y = playerPosRot.pos.y + playerHeight;
    rotatedPos1.z = playerPosRot.pos.z + 30.0f * cosYaw;
    
    sp34.pos.x = playerPosRot.pos.x + 12.0f * sinYaw;
    sp34.pos.y = rotatedPos1.y;
    sp34.pos.z = playerPosRot.pos.z + 12.0f * cosYaw;

    if ((camera->globalCtx->state.frames % 2) != 0) {
        sp22 = playerPosRot.rot.y + 0x2EE0;
        rotatedPos2.x = rotatedPos1.x + Math_SinS(sp22) * 50.0f;
        rotatedPos2.y = rotatedPos1.y;
        rotatedPos2.z = rotatedPos1.z + Math_CosS(sp22) * 50.0f;

        if ((func_800CC000(camera, &rotatedPos2, &sp34) != 0) && Camera_CheckOOB(camera, &rotatedPos1, &rotatedPos2)) {
            
            temp_f0 = CamMath_DistanceXZ(&rotatedPos1, &sp34.pos);
            if ((D_801B9E5C != 2) || (!((50.0f - temp_f0) <= -D_801B9E60))) {
                D_801B9E5C = 1;
                D_801B9E60 = (50.0f - temp_f0);

                ret = 0.0f;
                if (-D_801B9E60 != D_801B9E60) {
                    ret = D_801B9E60;
                } 
                return ret;
            }
        }

    } else {
        sp22 = playerPosRot.rot.y - 0x4000;
        rotatedPos2.x = rotatedPos1.x + Math_SinS(sp22) * 50.0f;
        rotatedPos2.y = rotatedPos1.y;
        rotatedPos2.z = rotatedPos1.z + Math_CosS(sp22) * 50.0f;

        if ((func_800CC000(camera, &rotatedPos2, &sp34) != 0) && Camera_CheckOOB(camera, &rotatedPos1, &rotatedPos2)) {
            temp_f0 = CamMath_DistanceXZ(&rotatedPos1, &sp34.pos);
            if ((D_801B9E5C != 1) || (!(-(temp_f0 - 50.0f) <= D_801B9E60))) {
                D_801B9E5C = 2;
                D_801B9E60 = (temp_f0 - 50.0f);

                if (D_801B9E60 != -D_801B9E60) {
                    return D_801B9E60;
                } else {
                    return 0.0f;
                }
            }

        }
    }

    if (D_801B9E5C != 0) {
        ret = D_801B9E60;
    } else {
        ret = 0.0f;
    }

    D_801B9E5C = 0;
    D_801B9E60 = 0.0f;

    return ret;
}
#else
f32 func_800CCCEC(Camera* camera, s16 arg1);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CCCEC.asm")
#endif

Vec3f* Camera_CalcUpFromPitchYawRoll(Vec3f* dest, s16 pitch, s16 yaw, s16 roll) {
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
f32 Camera_ClampLERPScale(Camera *camera, f32 maxLERPScale);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ClampLERPScale.asm")
#endif

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

Vec3f* Camera_BGCheckCorner(Vec3f *dst, Vec3f *linePointA, Vec3f *linePointB, CamColChk *pointAColChk, CamColChk *pointBColChk) {
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
s32 func_800CD44C(Camera *camera, VecSph *diffSph, CamColChk *eyeChk, CamColChk *atChk, s16 checkEye) {
    Vec3f* at = &camera->focalPoint; // 28-2C-30
    s32 pad1[2];
    s32 atEyeBgId; // 60
    s32 eyeAtBgId; // 5C
    s32 ret; // 58
    f32 cosEyeAt;
    s32 pad2[9];
    void* sp2C;

    eyeChk->pos = camera->eyeNext;

    ret = 0;

    atEyeBgId = func_800CBC84(camera, at, eyeChk, 0);
    if (atEyeBgId != 0) {
        // collision found between at->ey
        atChk->pos = *at;

        // OLib_Vec3fToVecSphGeo
        func_8010C6C8(&eyeChk->sphNorm, &eyeChk->norm);

        if (eyeChk->sphNorm.pitch > 0x2EE0) {
            eyeChk->sphNorm.yaw = diffSph->yaw;
        }

        if (checkEye & 1) {
            memcpy(&sp2C, atChk, 40);
        }

        eyeAtBgId = func_800CC000(camera, &camera->eye, atChk);

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

        // OLib_Vec3fToVecSphGeo
        func_8010C6C8(&atChk->sphNorm, &atChk->norm);

        if (atChk->sphNorm.pitch > 0x2EE0) {
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

    func_8010C6C8(&floorNormSph, floorNorm);

    tmp = Math_CosS(floorNormSph.pitch) * Math_CosS(playerYRot - floorNormSph.yaw);
    return (Camera_fabsf(tmp) * adjAmt) * Math_CosS(playerYRot - eyeAtYaw);
}

// Used in Battle1, unkArg-> related to unk data D_801AECF0, wait for unkArg info
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD6CC.asm")

/**
 * Calculates new at vector for the camera pointing in `eyeAtDir`
 */
// 0x801DCE28 = 0.1
// 0x801DCE2C = 0.2
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 Camera_CalcAtDefault(Camera *camera, VecSph *eyeAtDir, f32 extraYOffset, s16 calcSlope) {
    Vec3f* focalPoint = &camera->focalPoint;
    Vec3f posOffsetTarget; // 50-54-58
    Vec3f atTarget; // 44-48-4C
    s32 pad;
    PosRot* playerPosRot = &camera->playerPosRot; // 2C
    f32 yOffset; // 38 TODO: playerHeight

    yOffset = func_800CB700(camera);
    
    posOffsetTarget.x = 0.0f;
    posOffsetTarget.y = yOffset + extraYOffset;
    posOffsetTarget.z = 0.0f;

    if (calcSlope) {
        posOffsetTarget.y -= func_8010C36C(
            Camera_CalcSlopeYAdj(&camera->floorNorm, playerPosRot->rot.y, eyeAtDir->yaw, 25.0f), yOffset);
    }

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->posOffset, camera->yOffsetUpdateRate, camera->xzOffsetUpdateRate, 0.1f);

    atTarget.x = playerPosRot->pos.x + camera->posOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->posOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->posOffset.z;

    if (atTarget.y < (camera->playerGroundY + 10.0f)) {
        atTarget.y = camera->playerGroundY + 10.0f;
    }

    Camera_LERPCeilVec3f(&atTarget, focalPoint, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return true;
}
#else
s32 Camera_CalcAtDefault(Camera *camera, VecSph *eyeAtDir, f32 extraYOffset, s16 calcSlope);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_CalcAtDefault.asm")
#endif

// D_801DCE30 = 0.1
// D_801DCE34 = 0.1
#ifdef NON_EQUIVALENT
s32 func_800CD834(Camera *camera, VecSph *eyeAtDir, f32 arg2, f32* arg3, f32 arg4) {
    Vec3f posOffsetTarget;
    Vec3f atTarget; // 4C
    PosRot* playerPosRot = &camera->playerPosRot; // 30-34-38 -- 3C-3E-40
    f32 temp_f0;
    f32 deltaY;
    // f32 temp;


    f32 temp_f2; // 44
    s16 temp_v0;    // 3C-playerPosRot.rot.x
    s16 phi_v1;     // 3E-playerPosRot.rot.y

    posOffsetTarget.y = func_800CB700(camera) + arg2;
    posOffsetTarget.x = 0.0f;
    posOffsetTarget.z = 0.0f;

    func_800B8898(camera->globalCtx, camera->player, &playerPosRot->rot.y, &playerPosRot->rot.x);
    temp_v0 = playerPosRot->rot.x - 0x78;
    phi_v1 = ABS(temp_v0);
    // temp = phi_v1;

    func_8010C36C(phi_v1 / 120.0f, 1.0f); // Should have an output

    deltaY = playerPosRot->pos.y - *arg3;
    temp_f2 = func_8010C36C(deltaY, arg4);

    if (phi_v1 > 0x3C) {
        phi_v1 = 0x3C;
    }

    temp_f0 = func_8010C36C(phi_v1 / 60.0f, 1.0f);
    posOffsetTarget.y -= temp_f2 * temp_f0 * temp_f0;

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->posOffset, camera->yOffsetUpdateRate, camera->xzOffsetUpdateRate, 0.1f);
    atTarget.x = playerPosRot->pos.x + camera->posOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->posOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->posOffset.z;

    if (atTarget.y < (camera->playerGroundY + 10.0f)) {
        atTarget.y = camera->playerGroundY + 10.0f;
    }

    Camera_LERPCeilVec3f(&atTarget, &camera->focalPoint, camera->atLERPStepScale, camera->atLERPStepScale, 0.1f);
    return true;
}
#else
s32 func_800CD834(Camera *camera, VecSph *eyeAtDir, f32 arg2, f32* arg3, f32 arg4);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD834.asm")
#endif

// D_801DCE38 = 0.1f
// D_801DCE3C = 0.2f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 func_800CDA14(Camera *camera, VecSph *arg1, f32 arg2, f32 arg3) {
    PosRot* temp_s1 = &camera->playerPosRot;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 temp_f0;
    f32 sp30;

    sp30 = func_800CB700(camera);
    sp50.x = Math_SinS(temp_s1->rot.y) * arg3;
    sp50.z = Math_CosS(temp_s1->rot.y) * arg3;
    sp50.y = sp30 + arg2;
    Camera_LERPCeilVec3f(&sp50, &camera->posOffset, camera->yOffsetUpdateRate, camera->xzOffsetUpdateRate, 0.1f);
    sp44.x = temp_s1->pos.x + camera->posOffset.x;
    sp44.y = temp_s1->pos.y + camera->posOffset.y;
    sp44.z = temp_s1->pos.z + camera->posOffset.z;
    sp38.x = temp_s1->pos.x;
    sp38.y = sp44.y;
    sp38.z = temp_s1->pos.z;
    if (func_800CC128(camera, &sp38, &sp44) != 0) {
        sp44.x -= camera->posOffset.x - (sp44.x - sp38.x);
        sp44.z -= camera->posOffset.z - (sp44.z - sp38.z);
    }
    temp_f0 = camera->atLERPStepScale;
    Camera_LERPCeilVec3f(&sp44, &camera->focalPoint, temp_f0, temp_f0, 0.2f);
    return 1;
}
#else
s32 func_800CDA14(Camera *camera, VecSph *arg1, f32 arg2, f32 arg3);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDA14.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDE6C.asm")

// D_801DCE8C = 0.01
// D_801DCE90 = 0.1
// D_801DCE94 = 0.4
// D_801DCE98 = 0.017453292
// D_801DCE9C = 0.34906584
// D_801DCEA0 = -0.17453292
// D_801DCEA4 = 0.1
// D_801DCEA8 = 0.2
#ifdef NON_EQUIVALENT
s32 func_800CE2B8(Camera *camera, f32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 *arg6, Vec2f *arg7, s16 flags) {
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec2f sp58;
    f32 sp4C;
    s32 sp38;
    PosRot* temp_s1;

    f32 temp_f0_3;
    // f32 temp_f0_4;
    f32 temp_f20;
    f32 temp_f2;
    f32 phi_f20;
    f32 phi_f14;
    temp_s1 = &camera->playerPosRot;

    sp78.y = func_800CB700(camera) + arg3;
    sp78.x = 0.0f;
    sp78.z = 0.0f;
    sp58 = *arg7;
    // sp58[1] = arg7->y;
    sp58.x = arg7->x * (arg5 * arg4);
    sp38 = flags & 0x80;
    if (sp38 != 0) {
        camera->xzOffsetUpdateRate = 0.01f;
        camera->yOffsetUpdateRate = 0.01f;
    }
    func_8010C530(&sp60, &sp58); // TODO: Probably not Vec2f
    sp78.x += sp60.x;
    sp78.y += sp60.y;
    sp78.z += sp60.z;
    if (func_800CB950(camera) != 0) {
        *arg6 = Camera_LERPCeilF(temp_s1->pos.y, *arg6, 0.4f, 0.1f);
        sp78.y -= temp_s1->pos.y - *arg6;
        Camera_LERPCeilVec3f(&sp78, &camera->posOffset, camera->yOffsetUpdateRate, camera->xzOffsetUpdateRate, 0.1f);
    } else {
        sp4C = arg1;
        temp_f20 = temp_s1->pos.y - *arg6;
        temp_f0_3 = func_80086B30(temp_f20, sp4C);
        if (sp38 == 0) {
            temp_f2 = func_80086760(camera->fov * 0.4f * 0.017453292f, sp4C) * sp4C;
            if (temp_f2 < temp_f20) {
                *arg6 += (temp_f20 - temp_f2);
                phi_f20 = temp_f2;
            } else {
                phi_f20 = temp_f20;
                if (temp_f20 < -temp_f2) {
                    *arg6 += (temp_f20 + temp_f2);
                    phi_f20 = -temp_f2;
                }
            }
            sp78.y -= phi_f20;
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
        Camera_LERPCeilVec3f(&sp78, &camera->posOffset, 0.5f, 0.5f, 0.1f);
        camera->yOffsetUpdateRate = 0.5f;
        camera->xzOffsetUpdateRate = 0.5f;
    }

    sp6C.x = temp_s1->pos.x + camera->posOffset.x;
    sp6C.y = temp_s1->pos.y + camera->posOffset.y;
    sp6C.z = temp_s1->pos.z + camera->posOffset.z;
    Camera_LERPCeilVec3f(&sp6C, &camera->focalPoint, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE2B8.asm")
#endif


// D_801DCEAC = 0.1f
// D_801DCEB0 = 0.4f
// D_801DCEB4 = 0.1f
// D_801DCEB8 = 0.2f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 Camera_CalcAtForHorse(Camera* camera, VecSph* eyeAtDir, f32 yOffset, f32* yPosOffset, s16 calcSlope) {
    Vec3f* focalPoint = &camera->focalPoint;
    Vec3f posOffsetTarget;
    Vec3f focalTarget;
    s32 pad[2];
    f32 playerHeight = func_800CB700(camera);
    ActorPlayer* player = camera->player;
    PosRot horsePosRot;

    func_800B8214(&horsePosRot, player->rideActor);

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
        posOffsetTarget.y -= Camera_CalcSlopeYAdj(&camera->floorNorm, camera->playerPosRot.rot.y, eyeAtDir->yaw, 25.0f);
    }

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->posOffset, camera->yOffsetUpdateRate, camera->xzOffsetUpdateRate, 0.1f);
    focalTarget.x = camera->posOffset.x + horsePosRot.pos.x;
    focalTarget.y = camera->posOffset.y + horsePosRot.pos.y;
    focalTarget.z = camera->posOffset.z + horsePosRot.pos.z;
    Camera_LERPCeilVec3f(&focalTarget, focalPoint, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);

    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_CalcAtForHorse.asm")
#endif

// D_801DCEBC = 1.2f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
f32 func_800CE79C(Camera *camera, f32 dist, f32 minDist, f32 maxDist, s16 timer) {
    f32 sp24;

    if ((dist / maxDist) > 1.2f) {
        // temp_f0 = 20.0f / (dist / maxDist);
        sp24 = maxDist;
        camera->rUpdateRateInv = 20.0f / (dist / maxDist);
        if ((20.0f / (dist / maxDist)) < 10) {
            camera->rUpdateRateInv = 10;
        }
    } else if (dist < minDist) {
        sp24 = minDist;
        // phi_f12 = (timer != 0) ? 10.0f : 20.0f;
        camera->rUpdateRateInv = Camera_LERPCeilF((timer != 0) ? 10.0f : 20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else if (maxDist < dist) {
        sp24 = maxDist;
        // phi_f12 = (timer != 0) ? 10.0f : 20.0f;
        camera->rUpdateRateInv = Camera_LERPCeilF((timer != 0) ? 10.0f : 20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else {
        sp24 = dist;
        // phi_f12 = (timer != 0) ? 20.0f : 1.0f;
        camera->rUpdateRateInv = Camera_LERPCeilF((timer != 0) ? 20.0f : 1.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    }
    
    return Camera_LERPCeilF(sp24, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
}
#else
f32 func_800CE79C(Camera *camera, f32 dist, f32 minDist, f32 maxDist, s16 timer);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE79C.asm")
#endif


// D_801DCEC0 = 1.2f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
f32 func_800CE930(Camera *camera, f32 dist, f32 minDist, f32 maxDist, s16 timer) {
    f32 phi_f20;

    if (timer == 0) {
        phi_f20 = ((maxDist * 0.25f) > 80.0f) ? maxDist * 0.25f : 80.0f;
        camera->rUpdateRateInv = Camera_LERPCeilF(1000.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else if ((dist / maxDist) > 1.2f) {
        phi_f20 = maxDist;
        camera->rUpdateRateInv = 20.0f / (dist / maxDist);
        if ((20.0f / (dist / maxDist)) < 10.0f) {
            camera->rUpdateRateInv = 10.0f;
        } 
    } else if (dist < minDist) {
        phi_f20 = minDist;
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else if (maxDist < dist) {
        phi_f20 = maxDist;
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    } else {
        phi_f20 = dist;
        camera->rUpdateRateInv = Camera_LERPCeilF(1.0f, camera->rUpdateRateInv, 0.5f, 0.1f);
    }

    return Camera_LERPCeilF(phi_f20, camera->dist, 1.0f / camera->rUpdateRateInv, 0.1f);
}
#else
f32 func_800CE930(Camera *camera, f32 dist, f32 minDist, f32 maxDist, s16 timer);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE930.asm")
#endif

// D_801DCEC4 = 0.8f
// D_801DCEC8 = 6.896552e-05f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s16 Camera_CalcDefaultPitch(Camera* camera, s16 arg1, s16 arg2, s16 arg3) {
    f32 pad;
    f32 phi_a2;
    f32 t;
    s16 phi_v0;
    s16 phi_v1;
    s16 sp1C;

    phi_v1 = ABS(arg1);
    phi_v0 = arg3 > 0 ? (s16)(Math_CosS(arg3) * arg3) : arg3;
    sp1C = arg2 - phi_v0;

    if (ABS(sp1C) < phi_v1) {
        phi_a2 = (1.0f / camera->pitchUpdateRateInv) * 3.0f;
    } else {
        t = phi_v1 * 6.896552e-05f;
        pad = Camera_InterpolateCurve(0.8f, 1.0f - t);
        phi_a2 = (1.0f / camera->pitchUpdateRateInv) * pad;
    }
    return Camera_LERPCeilS(sp1C, arg1, phi_a2, 5);
}
#else
s16 Camera_CalcDefaultPitch(Camera* camera, s16 arg1, s16 arg2, s16 arg3);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_CalcDefaultPitch.asm")
#endif

// D_801DCECC = 0.001f
// D_801DCED0 = 0.3f;
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s16 Camera_CalcDefaultYaw(Camera* camera, s16 cur, s16 target, f32 arg3, f32 accel) {
    f32 velocity; // sp34
    s16 angDelta; // sp1C
    f32 updSpeed;
    f32 speedT;
    f32 velFactor;
    f32 yawUpdRate;

    if (camera->xzSpeed > 0.001f) {
        angDelta = target - (s16)(cur + 0x8000);
        speedT = (s16)(angDelta + 0x8000) / 32768.0f; // TODO: Macros
    } else {
        angDelta = target - (s16)(cur + 0x8000);
        speedT = 0.3f;
    }

    updSpeed = Camera_InterpolateCurve(arg3, speedT);

    velocity = ((1.0f - updSpeed) * accel) + updSpeed;

    if (velocity < 0.0f) {
        velocity = 0.0f;
    }

    velFactor = Camera_InterpolateCurve(0.5f, camera->speedRatio);
    yawUpdRate = (1.0f / camera->yawUpdateRateInv);
    return cur + (s16)(angDelta * velocity * velFactor * yawUpdRate);
}
#else
s16 Camera_CalcDefaultYaw(Camera* camera, s16 cur, s16 target, f32 arg3, f32 accel);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_CalcDefaultYaw.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CED90.asm")

s32 Camera_Noop(Camera* camera) {
    return true;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Normal1.asm")

s32 Camera_Normal2(Camera* camera) {
    return Camera_Noop(camera);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Normal3.asm")

s32 Camera_Normal4(Camera* camera) {
    Vec3s* sceneCamData;
    s16 roll;

    if (RELOAD_PARAMS) {
        sceneCamData = Camera_GetCamBGData(camera, camera->camDataIdx);
        D_801EDBF0 = BGCAM_ROT(sceneCamData).z;
    }

    roll = camera->roll;
    Camera_Normal1(camera);
    camera->roll = Camera_LERPCeilS(D_801EDBF0, roll, 0.05f, 5);
    return true;
}

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


// D_801DD1D4 = D_801DD1D8 = D_801DD1DC = D_801DD1E0 = 0.01f
// D_801DD1E4 = 0.2f
#ifdef NON_EQUIVALENT
s32 Camera_Fixed1(Camera *camera) {
    // s32 pad1;
    Fixed1* fixd1 = (Fixed1*)camera->paramData;
    s32 pad3;
    s32 yawDiff;
    s32 pad2;
    VecSph eyeOffset; // sp8C-90-92
    VecSph eyeAtOffset; // sp84-88-8A
    VecSph sp7C;
    Vec3f adjustedPos; //sp6C-70-74
    Vec3s* sceneCamData; // sp68
    u32 negOne;
    // Vec3f temp;
    Fixed1Anim* anim = &fixd1->anim;
    f32 playerHeight; // sp58
    CameraModeValue* values; // sp54
    PosRot* sp50;
    PosRot* sp4C;
    VecSph sp44; // sp44-48-4A
    Vec3f* eye = &camera->eye; // sp38
    Vec3f* focalPoint = &camera->focalPoint; // sp34
    PosRot* playerPosRot = &camera->playerPosRot; // sp30


    playerHeight = func_800CB700(camera);
    func_8010C764(&sp7C, focalPoint, eye);

    if (!RELOAD_PARAMS) {
        // Pass
    } else {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values; // sp54
        sceneCamData = Camera_GetCamBGData(camera, camera->camDataIdx);
        Camera_Vec3sToVec3f(&anim->eyePosRotTarget.pos, &BGCAM_POS(sceneCamData));

        anim->eyePosRotTarget.rot = BGCAM_ROT(sceneCamData);
        anim->fov = BGCAM_FOV(sceneCamData);
        anim->player = camera->player;

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

            func_8010C764(&sp44, sp50, &anim->eyePosRotTarget.pos);
            sp44.yaw = sp4C->rot.y + (s16)(sp44.yaw - sp50->rot.y);
            func_8010C7B8(&anim->eyePosRotTarget.pos, &sp4C->pos, &sp44);
            yawDiff = (s16)(anim->eyePosRotTarget.rot.y - sp50->rot.y);
            anim->eyePosRotTarget.rot.y = sp4C->rot.y + yawDiff;
        }
    }

    negOne = -1;

    if (anim->player != camera->player) {
        camera->animState = 20;
    }

    if (anim->fov == negOne) {
        anim->fov = fixd1->fov * 100;
    } else if (anim->fov < 361) {
        anim->fov *= 100;
    }

    sCameraInterfaceFlags = fixd1->interfaceFlags;

    if (camera->animState == 0) {
        camera->animState++;
        func_800CB5DC(camera);
        if (anim->fov != negOne) {
            fixd1->fov = PCT(anim->fov);
        }

        if (BGCAM_JFIFID(sceneCamData) != negOne) {
            fixd1->jfifId = PCT(BGCAM_JFIFID(sceneCamData));
        }
    }

    func_8010C764(&eyeAtOffset, eye, focalPoint);
    Camera_LERPCeilVec3f(&anim->eyePosRotTarget.pos, eye, fixd1->jfifId, fixd1->jfifId, 0.2f);
    adjustedPos = playerPosRot->pos;
    adjustedPos.y += playerHeight;
    camera->dist = CamMath_Distance(&adjustedPos, eye);
    eyeOffset.r = camera->dist;
    eyeOffset.pitch = Camera_LERPCeilS(anim->eyePosRotTarget.rot.x * -1, eyeAtOffset.pitch, fixd1->jfifId, 5);
    eyeOffset.yaw = Camera_LERPCeilS(anim->eyePosRotTarget.rot.y, eyeAtOffset.yaw, fixd1->jfifId, 5);
    func_8010C7B8(focalPoint, eye, &eyeOffset);
    camera->eyeNext = *eye;
    func_800CC128(camera, eye, focalPoint);
    camera->fov = Camera_LERPCeilF(fixd1->fov, camera->fov, fixd1->jfifId, 0.1f);
    camera->roll = 0;
    camera->atLERPStepScale = 0.0f;
    func_800CB6C8(camera, &playerPosRot->pos);
    camera->roll = Camera_LERPCeilS(anim->eyePosRotTarget.rot.z, camera->roll, fixd1->jfifId, 5);
    return true;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Fixed1.asm")
#endif


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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Unique0.asm")

s32 Camera_Unique6(Camera *camera) {
    Unique6* uniq6 = (Unique6*)camera->paramData;
    CameraModeValue* values;
    Vec3f playerPosDisp;
    PosRot* playerPosRot = &camera->playerPosRot;
    f32 playerHeight;

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        uniq6->interfaceFlags = NEXTSETTING;
    }

    sCameraInterfaceFlags = uniq6->interfaceFlags;

    if (camera->animState == 0) {
        camera->animState++;
        func_800CB544(camera);
    }

    if (camera->player != NULL) {
        playerHeight = func_800CB700(camera);
        playerPosDisp = playerPosRot->pos;
        playerPosDisp.y += playerHeight;
        camera->dist = CamMath_Distance(&playerPosDisp, &camera->eye);
        func_800CB6C8(camera, &playerPosRot->pos);
    } else {
        camera->dist = CamMath_Distance(&camera->focalPoint, &camera->eye);
    }

    if ((uniq6->interfaceFlags & 1) != 0) {
        if (camera->unk_160 > 0) {
            camera->unk_160--;
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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo2.asm")

// D_801DD368 = 0.1
// D_801DD36C = 0.4
// D_801DD370 = D_801DD374 = 0.1
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 Camera_Demo3(Camera *camera) {
    s32 pad2;
    s32 pad3;
    s32 pad4;
    VecSph sp64;
    CameraModeValue* values;
    Demo3* demo3 = (Demo3*)camera->paramData;
    Vec3f playerPos; // sp50-54-58
    Vec3f* eye = &camera->eye; // sp34;
    Vec3f* focalPoint = &camera->focalPoint; // sp30
    Vec3f* eyeNext = &camera->eyeNext; // sp24
    Demo3Anim* anim = &demo3->anim;
    f32 temp;


    func_8010C764(&sp64, focalPoint, eye);
    func_800B81E0(&playerPos, camera->player);
    playerPos.x = camera->playerPosRot.pos.x;
    playerPos.z = camera->playerPosRot.pos.z;
    playerPos.y -= (playerPos.y - camera->playerPosRot.pos.y) * 0.4f;
    Camera_LERPCeilVec3f(&playerPos, focalPoint, 0.1f, 0.1f, 0.1f);

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
            sp64.r = Camera_LERPCeilF(140.0f, sp64.r, temp, 0.1f);
            anim->unk_06--;
            camera->fov = Camera_LERPCeilF(50.0f, camera->fov, 0.1f, 0.1f);
            if (anim->unk_06 <= 0) {
                anim->unk_06 = 20;
                camera->animState += 1;
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
                camera->animState += 1;
            }
            break;
    }

    func_8010C7B8(eyeNext, focalPoint, &sp64);
    *eye = *eyeNext;
    return true;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Demo3.asm")
#endif


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

// D_801DD44C = 0.05f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
void Camera_Init(Camera* camera, View* view, CollisionContext* colCtx, GlobalContext* globalCtx) {
    Camera* camP;
    s32 i;
    s16 curUID;
    s16 j;

    func_80096880(camera, 0, sizeof(*camera));

    camera->globalCtx = D_801EDC28 = globalCtx;
    curUID = sNextUID;
    sNextUID++;
    while (curUID != 0) {
        if (curUID == 0) {
            sNextUID++;
        }

        for (j = 0; j < NUM_CAMS; j++) {
            camP = camera->globalCtx->cameraPtrs[j];
            if (camP != NULL && (curUID == camP->uid)) {
                break;
            }
        }

        if (j == 4) {
            break;
        }

        curUID = sNextUID++;
    }

    camera->inputDir.y = 0x4000;
    camera->uid = curUID;
    camera->camDir = camera->inputDir;
    camera->nextCamDataIdx = -1;
    camera->upDir.z = camera->upDir.x = 0.0f;
    camera->upDir.y = 1.0f;
    camera->fov = 60.0f;
    camera->xzOffsetUpdateRate = 0.05f;
    camera->yOffsetUpdateRate = 0.05f;
    camera->fovUpdateRate = 0.05f;
    camera->rUpdateRateInv = 10.0f;
    camera->yawUpdateRateInv = 10.0f;
    camera->pitchUpdateRateInv = 16.0f;
    sCameraShrinkWindowVal = 0x20;
    sCameraInterfaceAlpha = 0;
    camera->setting = camera->prevSetting= CAM_SET_FREE0;
    camera->camDataIdx = camera->prevCamDataIdx = -1;
    camera->flags = 0;
    camera->mode = CAM_MODE_NORMAL;
    camera->bgCheckId = 0x32;
    camera->unk_168 = 0xF;
    camera->unk_160 = -1;
    camera->player = NULL;
    camera->target = NULL;
    Camera_SetFlags(camera, 0x4000);
    camera->skyboxOffset.z = camera->skyboxOffset.y = camera->skyboxOffset.x = 0;
    camera->upDir.z = camera->upDir.x = 0.0f;
    camera->atLERPStepScale = 1;
    camera->upDir.y = 1.0f;
    sCameraInterfaceFlags = 0xFF00;
    D_801B9E58 = 3;
}
#else
void Camera_Init(Camera* camera, View* view, CollisionContext* colCtx, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Init.asm")
#endif

void func_800DDFE0(Camera* camera) {
    if (camera != &camera->globalCtx->mainCamera) {
        camera->setting = CAM_SET_FREE0;
        camera->prevSetting = camera->setting;
        Camera_ClearFlags(camera, 4);
    } else {
        switch (camera->globalCtx->roomContext.currRoom.unk3) {
            case 1:
                camera->prevSetting = CAM_SET_DUNGEON0;
                Camera_ChangeSettingFlags(camera, CAM_SET_DUNGEON0, 2);
                break;
            case 0:
                camera->prevSetting = CAM_SET_NORMAL0;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL0, 2);
                break;
            case 2:
                camera->prevSetting = CAM_SET_ROOM0;
                Camera_ChangeSettingFlags(camera, CAM_SET_ROOM0, 2);
                break;
            default:
                camera->prevSetting = CAM_SET_NORMAL0;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL0, 2);
                break;
        }
        Camera_SetFlags(camera, 4);
    }

}

void Camera_Stub800DE0E0(Camera* camera) {
}

// D_801DD450 = 0.01f
// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
void Camera_InitPlayerSettings(Camera* camera, ActorPlayer* player) {
    PosRot playerPosShape;
    VecSph eyeNextAtOffset;
    s32 bgId;
    Vec3f floorPos;
    s32 upXZ;
    f32 playerYOffset;
    Vec3f* eye = &camera->eye;
    s32 pad;

    func_800B8248(&playerPosShape, player);
    camera->player = player;
    playerYOffset = func_800CB700(camera);
    camera->playerPosRot = playerPosShape;
    camera->dist = eyeNextAtOffset.r = 180.0f;
    camera->inputDir.y = playerPosShape.rot.y;
    eyeNextAtOffset.yaw = BINANG_ROT180(camera->inputDir.y);
    camera->inputDir.x = eyeNextAtOffset.pitch = 0x71C;
    camera->inputDir.z = 0;
    camera->camDir = camera->inputDir;
    camera->xzSpeed = 0.0f;
    camera->playerPosDelta.y = 0.0f;
    camera->focalPoint = playerPosShape.pos;
    camera->focalPoint.y += playerYOffset;

    camera->posOffset.x = 0;
    camera->posOffset.y = playerYOffset;
    camera->posOffset.z = 0;

    func_8010C7B8(&camera->eyeNext, &camera->focalPoint, &eyeNextAtOffset);
    *eye = camera->eyeNext;
    camera->roll = 0;

    upXZ = 0;
    camera->upDir.z = upXZ;
    camera->upDir.y = 1.0f;
    camera->upDir.x = upXZ;

    {
        Vec3f* focalPoint = &camera->focalPoint;
        if (func_800CC488(camera, &floorPos, focalPoint, &bgId) != BGCHECK_Y_MIN) {
            camera->bgCheckId = bgId;
        }
    }

    camera->waterPrevCamIdx = -1;
    camera->waterPrevCamSetting = -1;
    dummy:; // necessary to match
    camera->waterQuakeId = -1;
    func_800DDFE0(camera);

    Camera_SetFlags(camera, 4);

    camera->paramFlags = 0;
    camera->nextCamDataIdx = -1;
    camera->xzOffsetUpdateRate = 0.01f;
    camera->yOffsetUpdateRate = 0.01f;
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
#else
void Camera_InitPlayerSettings(Camera* camera, ActorPlayer* player);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_InitPlayerSettings.asm")
#endif

s32 Camera_ChangeStatus(Camera* camera, s16 status) {
    camera->status = status;
    return camera->status;
}

s32 Camera_CheckWater(Camera* camera) {
    f32 waterY;
    s16 waterCamIdx;
    s32 pad[2];
    s32* waterPrevCamSetting = &camera->waterPrevCamSetting;
    s16 prevBgId;

    if (!(camera->flags & 2) || (sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
        return false;
    }

    if (camera->flags & 0x200) {
        if (func_800CB8C8(camera) != 0) {
            if (func_800CB8F4(camera) == 0) {
                Camera_ChangeSettingFlags(camera, CAM_SET_CIRCLE5, 6);
            } else {
                Camera_ChangeSettingFlags(camera, CAM_SET_ZORA0, 6);
            }
            Camera_SetFlags(camera, -0x8000);
        } else if (camera->flags & (s16)0x8000) {
            Camera_ChangeSettingFlags(camera, *waterPrevCamSetting, 6); // unk11E
            Camera_ClearFlags(camera, -0x8000);
        }
    }

    if (!(camera->flags & (s16)0x8000)) {
        waterCamIdx = Camera_GetWaterBoxDataIdx(camera, &waterY);
        if (waterCamIdx == -2) {
            if (!(camera->flags & 0x200)) {
                Camera_SetFlags(camera, 0x200);
                camera->waterPrevCamIdx = camera->camDataIdx;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) ||
                ((func_800CB880(camera) != 0) && (func_800CBB58(camera) == 0))) {
                prevBgId = camera->bgCheckId;
                camera->bgCheckId = 0x32;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL3, 2);
                *waterPrevCamSetting = camera->setting;
                camera->bgCheckId = prevBgId;
                camera->camDataIdx = -2;
            }

        } else if (waterCamIdx != -1) {
            if ((camera->flags & 0x200) == 0) {
                Camera_SetFlags(camera, 0x200);
                camera->waterPrevCamIdx = camera->camDataIdx;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) ||
                ((func_800CB880(camera) != 0) && (func_800CBB58(camera) == 0))) {
                prevBgId = camera->bgCheckId;
                camera->bgCheckId = 0x32;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, waterCamIdx, 2);
                *waterPrevCamSetting = camera->setting;
                camera->bgCheckId = prevBgId;
            }

        } else if (camera->flags & 0x200) {
            Camera_ClearFlags(camera, 0x200);
            prevBgId = camera->bgCheckId;
            camera->bgCheckId = 0x32;
            if (camera->waterPrevCamIdx < 0) {
                func_800DDFE0(camera);
                camera->camDataIdx = -1;
            } else {
                Camera_ChangeDataIdx(camera, camera->waterPrevCamIdx);
            }
            camera->bgCheckId = prevBgId;
        }
        camera->waterYPos = waterY;
    }
    return true;
}

static s16 D_801B9F04[] = {
    0x0FFC, 0x07FC, 0x03FC, 0x01FC,
};

void func_800DE62C(Camera* camera) {
    static s16 D_801B9F0C = 0;
    u16 dayTime;
    s16 quake;
    s32 changeZeldaTime;
    s16 sp30[4] = D_801B9F04;

    if ((CURRENT_DAY == 3) && (ActorCutscene_GetCurrentIndex() == -1)) {
        dayTime = gSaveContext.time;
        changeZeldaTime = gSaveContext.unk_14;
        if ((dayTime > 0) && (dayTime < 0x4000) && ((sp30[dayTime >> 12] & dayTime) == 0) && (Quake_NumActiveQuakes() < 2)) {
            quake = Quake_Add(camera, 4);
            if (quake != 0) {
                Quake_SetSpeed(quake, 30000);
                Quake_SetQuakeValues(quake, (dayTime >> 12) + 2, 1, 5, 60);
                D_801B9F0C = ((dayTime >> 10) - changeZeldaTime) + 80;
                Quake_SetCountdown(quake, D_801B9F0C);
            }
        }

        if (((((dayTime + 0x4D2) & 0xDFFC) == 0xC000) || ((camera->globalCtx->state.frames % 1024) == 0)) && (Quake_NumActiveQuakes() < 2)) {
            quake = Quake_Add(camera, 3);
            if (quake != 0) {
                Quake_SetSpeed(quake, 16000);
                Quake_SetQuakeValues(quake, 1, 0, 0, dayTime & 0x3F); // %64
                D_801B9F0C = 120 - changeZeldaTime;
                Quake_SetCountdown(quake, D_801B9F0C);
            }
        }

        if (D_801B9F0C != 0) {
            D_801B9F0C--;
            func_8019F128(NA_SE_SY_EARTHQUAKE_OUTDOOR - SFX_FLAG);
        }
    }
}

/**
 * Sets the room to be hot camera quake flag
 */
s32 Camera_SetRoomHotFlag(Camera* camera) {
    Quake2_ClearType(1);
    if (camera->globalCtx->roomContext.currRoom.unk2 == 3) {
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
    ActorPlayer* player = (ActorPlayer*)camera->globalCtx->actorCtx.actorList[2].first;

    if ((camera->thisIdx == MAIN_CAM) && (camera->player == (ActorPlayer*)camera->globalCtx->actorCtx.actorList[2].first) && ((player)->unk153 == 20)) {
        Camera_ChangeSettingFlags(camera, CAM_SET_GIANT, 2);
        return true;
    } else {
        return false;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Update.asm")

s32 func_800DF498(Camera* camera) {
    Camera_SetFlags(camera, 0x8 | 0x4); // flag 0x8 is set only immediately to be unset
    Camera_ClearFlags(camera, 0x1000 | 0x8);
    return true;
}

// ISMATCHING: Need to move rodata
#ifdef NON_MATCHING
s32 Camera_ChangeModeFlags(Camera* camera, s16 mode, u8 flags) {
    static s32 modeChangeFlags = 0;

    if (camera->setting == CAM_SET_TELESCOPE) {
        if ((mode == CAM_MODE_FIRSTPERSON) || (mode == CAM_MODE_NUTSHIDE)) {
            flags = 1;
        }
    }

    if ((camera->flags & 0x20) && (flags == 0)) {
        camera->unk_14A |= 0x20;
        return -1;
    }

    if (!(sCameraSettings[camera->setting].validModes & (1 << mode))) {
        if (camera->mode != CAM_MODE_NORMAL) {
            camera->mode = CAM_MODE_NORMAL;
            Camera_ResetAnim(camera, camera->mode);
            func_800DF498(camera);
            return 0xC0000000 | mode;
        } else {
            camera->unk_14A |= 0x20;
            camera->unk_14A |= 2;
            return 0;
        }
    } else {
        if ((mode == camera->mode) && (flags == 0)) {
            camera->unk_14A |= 0x20;
            return -1;
        }
        camera->unk_14A |= 0x20;
        camera->unk_14A |= 2;
        
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
                if (camera->target != NULL && camera->target->id != 0x20) {
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

        if (camera->status == CAM_STAT_ACTIVE) {
            switch (modeChangeFlags) {
                case 1:
                    play_sound(0);
                    break;
                case 2:
                    if (camera->globalCtx->roomContext.currRoom.unk3 == 1) {
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
#else
static s32 modeChangeFlags = 0;
s32 Camera_ChangeModeFlags(Camera* camera, s16 mode, u8 flags);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ChangeModeFlags.asm")
#endif

s32 Camera_ChangeMode(Camera* camera, s16 mode) {
    return Camera_ChangeModeFlags(camera, mode, 0);
}

s32 Camera_CheckValidMode(Camera* camera, s16 mode) {
    if ((camera->flags & 0x20) != 0) {
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
    if ((camera->unk_14A & 1) && ((sCameraSettings[camera->setting].unk_04 & 0xF) >= (sCameraSettings[setting].unk_04 & 0xF))) {
        camera->unk_14A |= 0x10;
        if (!(flags & 2)) {
            camera->unk_14A |= 1;
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
        camera->unk_14A |= 0x10;
        if (!(flags & 2)) {
            camera->unk_14A |= 1;
        }
        return -1;
    }

    camera->unk_14A |= 0x10;

    if (!(flags & 2)) {
        camera->unk_14A |= 1;
    }

    func_800DF498(camera);

    if (!(sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
        camera->prevSetting = camera->setting;
    }

    if (flags & 8) {
        camera->camDataIdx = camera->prevCamDataIdx;
        camera->prevCamDataIdx = -1;
    } else if (!(flags & 4)) {
        if (!(sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
            camera->prevCamDataIdx = camera->camDataIdx;
        }
        camera->camDataIdx = -1;
    }

    camera->setting = setting;

    if (Camera_ChangeModeFlags(camera, camera->mode, 1) >= 0) {
        Camera_ResetAnim(camera, camera->mode);
    }

    return setting;
}

s32 Camera_ChangeSetting(Camera* camera, s16 setting) {
    s32 settingChangeSuccessful = Camera_ChangeSettingFlags(camera, setting, 0);

    if (settingChangeSuccessful >= 0) {
        camera->camDataIdx = -1;
    }
    return settingChangeSuccessful;
}

s32 Camera_ChangeDataIdx(Camera* camera, s32 camDataIdx) {
    s16 setting;

    if (camDataIdx == -1 || camDataIdx == camera->camDataIdx) {
        camera->unk_14A |= 0x40;
        return -1;
    }

    if (camDataIdx < 0) {
        setting = D_801B9CE4[camDataIdx];
    } else if (!(camera->unk_14A & 0x40)) {
        setting = func_800CC740(camera, camDataIdx);
    } else {
        return -1;
    }

    camera->unk_14A |= 0x40;
    if ((Camera_ChangeSettingFlags(camera, setting, 5) >= 0) || (sCameraSettings[camera->setting].unk_04 & 0x80000000)) {
        camera->camDataIdx = camDataIdx;
        camera->unk_14A |= 4;
        Camera_ResetAnim(camera, camera->mode);
    }

    return camDataIdx | 0x80000000;
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
        return 0;
    }
    Quake_SetSpeed(quakeIdx, 0x61A8);
    Quake_SetQuakeValues(quakeIdx, y, 0, 0, 0);
    Quake_SetCountdown(quakeIdx, countdown);
    return 1;
}

// D_801DD5AC = 182.04167
// ISMATCHING: Need to move rodata (TODO: check jump table values)
#ifdef NON_MATCHING
s32 Camera_SetParam(Camera* camera, s32 param, void* value) {
    s32 pad[3];

    if (value != NULL) {
        switch (param) {
            case 1:
                camera->paramFlags &= ~(0x10 | 0x8 | 0x1);
                camera->focalPoint = *(Vec3f*)value;
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
                camera->upDir = *(Vec3f*)value;
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
#else
s32 Camera_SetParam(Camera* camera, s32 param, void* value);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_SetParam.asm")
#endif

s32 func_800DFEF0(Camera* camera, s16 paramFlags) {
    camera->paramFlags &= ~paramFlags;
    return 1;
}

s32 func_800DFF18(Camera* camera, s16 flags) {
    camera->flags = flags;
    return 1;
}

s32 func_800DFF34(Camera* camera) {
    camera->animState = 0;
    return 1;
}

s32 func_800DFF44(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 1;
}

s16 Camera_SetFlags(Camera* camera, s16 flags) {
    camera->flags |= flags;
    return camera->flags;
}

s16 Camera_ClearFlags(Camera* camera, s16 flags) {
    camera->flags &= ~flags;
    return camera->flags;
}

s32 Camera_ChangeDoorCam(Camera* camera, Actor* doorActor, s16 camDataIdx, f32 arg3, s16 timer1, s16 timer2,
                         s16 timer3) {
    DoorParams* doorParams = (DoorParams*)camera->paramData;

    if (camera->setting == CAM_SET_DOORC) {
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
        Camera_ChangeSettingFlags(camera, CAM_SET_DOORC, 0);
    } else if (camDataIdx == -2) {
        Camera_ChangeSettingFlags(camera, CAM_SET_SPIRAL, 0);
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
s32 Camera_Copy(Camera* dstCamera, Camera* srcCamera);
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
