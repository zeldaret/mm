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
        func_800B81E0(&vec, player, camera);
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
        ret = (player->stateFlags1 & 0x1000);
        ret = (!!(ret)); // needed to match
        if (ret == 0) {
            ret = (player->unkA74 & 0x100);
            ret = (!!(ret)); // needed to match
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
        return 1;
    }

    return 0;
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
    CollisionPoly* floorPoly; // sp38
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
            floorPolyY = BgCheck_CameraRaycastFloor2(colCtx, &floorPoly, &floorBgId, &toNewPos);
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
// ISMATCHING: Need to move rodata
// D_801DCDE8 = 3.051851e-05
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

// s16 func_800CC260(Camera* camera, Vec3f* arg1, Vec3f* arg2, void* arg3, Actor** exclusions, s16 arg5)
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC56C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC5C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC740.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC7A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC874.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC9C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CCCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD04C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD2F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD3E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD44C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD634.asm")

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_SetFlags.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ClearFlags.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E007C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E01AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E01B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E01DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0228.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E02AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E031C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0348.asm")
