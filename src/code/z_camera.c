#include "ultra64.h"
#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

#include "z_camera_data.c"

void func_800DDFE0(Camera* camera);

f32 Camera_fabsf(f32 f) {
    return ABS(f);
}

f32 Camera_Vec3fMagnitude(Vec3f* vec) {
    return sqrtf(SQ(vec->x) + SQ(vec->y) + SQ(vec->z));
}

/**
 * Interpolates along a curve between 0 and 1 with a period of
 * -a <= p <= a at time `b`
 */
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

void func_800CB544(Camera* camera) {
    camera->yawUpdateRateInv = 100.0f;
    camera->pitchUpdateRateInv = 16.0f;
    camera->rUpdateRateInv = 20.0f;
    camera->yOffsetUpdateRate = 0.05f;
    camera->xzOffsetUpdateRate = 0.05f;
    camera->fovUpdateRate = 0.05f;
}

void func_800CB584(Camera* camera) {
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

void func_800CB5DC(Camera* camera) {
    camera->rUpdateRateInv = 1800.0f;
    camera->yawUpdateRateInv = 1800.0f;
    camera->pitchUpdateRateInv = 1800.0f;
    camera->yOffsetUpdateRate = 0.01;
    camera->xzOffsetUpdateRate = 0.01;
    camera->fovUpdateRate = 0.01;
}

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

// Not explicity a function in OoT, but is implicitely
void func_800CB6C8(Camera* camera, Vec3f* vec) {
    camera->posOffset.x = camera->at.x - vec->x;
    camera->posOffset.y = camera->at.y - vec->y;
    camera->posOffset.z = camera->at.z - vec->z;
}

f32 func_800CB700(Camera* camera) {
    Player* player = camera->player;
    f32 ret;
    Vec3f vec;
    f32 pad[2];

    if (&player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        ret = func_800B6FC8(player);
    } else {
        func_800B81E0(&vec, &player->actor);
        ret = vec.y - camera->playerPosRot.pos.y;
        if (ret == 0.0f) {
            ret = 10.0f;
        }
    }
    return ret;
}

f32 func_800CB780(Camera* camera) {
    Player* player = camera->player;
    f32 ret;

    if (&player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        ret = func_800B7090(player);
    } else {
        ret = 10.0f;
    }

    return ret;
}

s32 func_800CB7CC(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags3 & 0x10;
    }

    return 0;
}

s32 func_800CB7F8(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags1 & 0x800000;
    }

    return 0;
}

s32 func_800CB828(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags3 & 0x2000;
    }

    return 0;
}

s32 func_800CB854(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags1 & 0x20;
    }

    return 0;
}

// related to player swimming (player->stateFlags1 & 0x8000000) is player swimming
s32 func_800CB880(Camera* camera) {
    Player* player = camera->player;

    if (&player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        if (player->stateFlags3 & 0x8000) {
            return 0x3E7;
        } else {
            return player->stateFlags1 & 0x8000000;
        }
    }

    return 0;
}

s32 func_800CB8C8(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags2 & 0x800;
    }

    return 0;
}

s32 func_800CB8F4(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->transformation == PLAYER_FORM_ZORA;
    }

    return 0;
}

s32 func_800CB924(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags3 & 0x1000;
    }
    return 0;
}

s32 func_800CB950(Camera* camera) {
    Player* player;
    s32 phi_v0;
    s32 phi_v1;
    f32 new_var;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        new_var = Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY);

        phi_v0 = false;
        if (new_var < 11.0f) {
            phi_v0 = true;
        } 

        phi_v1 = phi_v0;

        if (!phi_v1) {

            phi_v1 = false;
            if (camera->player->actor.gravity > -0.1f) {
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
        phi_v1 = true;
    }

    return phi_v1;
}

s32 func_800CBA08(Camera* camera) {
    Player* player = camera->player;

    if (&player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags1 & 4;
    }

    return 0;
}

s32 func_800CBA34(Camera* camera) {
    Player* player = camera->player;
    s32 ret;

    if (&player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        ret = !!(player->stateFlags1 & 0x1000);
        if (ret == 0) {
            ret = !!(player->stateFlags3 & 0x100);
        }
        return ret;
    }

    return 0;
}

s32 func_800CBA7C(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->stateFlags2 & 0x800000;
    }

    return 0;
}

s32 func_800CBAAC(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->swordState;
    }

    return 0;
}

s32 func_800CBAD4(Vec3f* dst, Camera* camera) {
    PosRot sp24;
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        *dst = player->bodyPartsPos[0];
        return dst;
    }

    func_800B8248(&sp24, &camera->player->actor);
    *dst = sp24.pos;
    return dst;
}

s32 func_800CBB58(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        return player->currentBoots == 5;
    }

    return 0;
}

s32 func_800CBB88(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        if ((player->swordState != 0) && (player->swordAnimation == 26)) {
            return 3;
        }
        if ((player->stateFlags2 & 0x20000) || ((player->swordState != 0) && (player->swordAnimation == 29))) {
            return 1;
        }
    }

    return 0;
}

s32 func_800CBC00(Camera* camera) {
    Player* player = camera->player;

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
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
            to->poly = camera->player->actor.floorPoly;
            floorBgId = camera->player->actor.floorBgId;
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

// OoT func_80044340
void func_800CBFA4(Camera* camera, Vec3f* arg1, Vec3f* arg2, s32 arg3) {
    CamColChk sp20;
    Vec3s unused;

    sp20.pos = *arg2;
    func_800CBC84(camera, arg1, &sp20, arg3);
    *arg2 = sp20.pos;
}

// OoT Camera_BGCheckInfo
s32 func_800CC000(Camera* camera, Vec3f* from, CamColChk* to) {
    CollisionPoly* floorPoly;
    Vec3f toNewPos;
    Vec3f fromToNorm;

    if (BgCheck_CameraLineTest1(&camera->globalCtx->colCtx, from, &to->pos, &toNewPos, &to->poly, 1, 1, 1, -1, &to->bgId)) {
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

s16 func_800CC260(Camera* camera, Vec3f* arg1, Vec3f* arg2, VecSph* arg3, Actor** exclusions, s16 numExclusions) {
    // sp 70-98 Could be one struct
    VecSph sp90;
    s32 pad;
    s32 sp88;
    f32 rand;
    s32 pitch;
    s32 ret;
    Vec3f sp70;
    Vec3f sp64;
    Player* player = (Player*)camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first;
    s32 i;

    sp64 = *arg2;
    func_800B81E0(&sp70, &player->actor);
    sp90 = *arg3;
    sp88 = 14;
    for (i = 0; i < sp88;i++) {
        OLib_VecSphAddToVec3f(arg1, arg2, &sp90);
        if (1) {}; // required to match

        if ((Camera_CheckOOB(camera, arg1, &sp64) || func_800CBC30(camera, arg2->y, arg1->y)) ||
            CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, arg2, arg1, exclusions,
                                        numExclusions)) {
            sp90.yaw = D_801B9E18[i] + arg3->yaw;
            rand = Rand_ZeroOne();
            sp90.pitch = D_801B9E34[i] + ((s16)(arg3->pitch * rand));
            if (sp90.pitch > 0x36B0) {
                sp90.pitch += -0x3E80;
            }
            if (sp90.pitch < (-0x36B0)) {
                sp90.pitch += 0x3A98;
            }
            sp90.r *= 0.9f;
            sp64 = *arg2;
        } else {
            break;
        }
    }

    *arg3 = sp90;

    if (i == 14) {
        ret = -1;
    } else {
        ret = i;
    }

    return ret;
}

// OoT Camera_GetFloorYLayer (Camera_GetFloorYNorm)
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

f32 func_800CC56C(Camera* camera, Vec3f* arg1) {
    Vec3f pos;  // 2C
    Vec3f norm; // 20
    s32 bgId;

    pos = *arg1;
    pos.y += 80.0f;
    return func_800CC488(camera, &norm, &pos, &bgId); // TODO: functions.h
}

f32 func_800CC5C8(Camera* camera, Vec3f* norm, Vec3f* pos, s32* bgId) {
    CollisionPoly* floorPoly;
    CollisionContext* colCtx = &camera->globalCtx->colCtx;
    f32 floorY;

    if (camera->player != NULL) {
        // OoT BgCheck_EntityRaycastFloor5
        floorY =
            func_800C41E4(camera->globalCtx, &camera->globalCtx->colCtx, &floorPoly, bgId, &camera->player->actor, pos);
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
    func_800B8248(&playerPosShape, &camera->player->actor);
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
s16 Camera_XZAngle(Vec3f* to, Vec3f* from) {
    // Math_FAtan2F in OoT
    return DEGF_TO_BINANG(RADF_TO_DEGF(func_80086B30(from->x - to->x, from->z - to->z)));
}

s16 D_801EDBF0;
// Identical to OoT func_80044ADC
s16 func_800CC9C0(Camera *camera, s16 yaw, s16 arg2) {
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
        sp2C = OLib_Vec3fDistXZ(&playerPos, &D_801EDC00.pos);
        D_801EDC00.pos.x += D_801EDC00.norm.x * 5.0f;
        D_801EDC00.pos.y += D_801EDC00.norm.y * 5.0f;
        D_801EDC00.pos.z += D_801EDC00.norm.z * 5.0f;
        if (sp2C < sp30) {
            sp30 = sp2C;
            D_801EDBF4 = D_801EDBF8 = func_800CC5C8(camera, &floornorm, &D_801EDC00.pos, &bgId);
        } else {
            D_801EDBF4 = func_800CC5C8(camera, &floornorm, &rotatedPos, &bgId);
            D_801EDBF8 = func_800CC5C8(camera, &floornorm, &D_801EDC00.pos, &bgId);
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
    PosRot sp5C; // 5C-60-64 -- 68-6A-6C
    CamColChk sp34; // 34-38-3C -- 40-44-48 -- 4C -- 50-54-56 -- 58
    f32 temp_f0;
    f32 sp2C = func_800CB700(camera);
    f32 sp28;
    f32 temp_f2;
    s16 sp22;
    f32 temp_f12;

    if (arg1 != 0) {
        D_801B9E5C = 0;
        D_801B9E60 = 0.0f;
    }

    sp5C = camera->playerPosRot;

    sp28 = Math_SinS(sp5C.rot.y);
    temp_f0 = Math_CosS(sp5C.rot.y);
    
    sp7C.x = (30.0f * sp28) + sp5C.pos.x;
    sp7C.y = sp5C.pos.y + sp2C;
    sp7C.z = 30.0f * temp_f0 + sp5C.pos.z;
    sp34.pos.x = sp5C.pos.x + (12.0f * sp28);
    sp34.pos.y = sp7C.y;
    sp34.pos.z = sp5C.pos.z + (12.0f * temp_f0);

    if ((camera->globalCtx->state.frames & 1) != 0) {
        sp22 = sp5C.rot.y + 0x2EE0;
        sp70.x = (Math_SinS(sp22) * 50.0f) + sp7C.x;
        sp70.y = sp7C.y;
        sp70.z = (Math_CosS(sp22) * 50.0f) + sp7C.z;

        if ((func_800CC000(camera, &sp70, &sp34) != 0) && (Camera_CheckOOB(camera, &sp7C, &sp70) != 0)) {
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
        sp22 = sp5C.rot.y - 0x4000;
        sp70.x = (Math_SinS(sp22) * 50.0f) + sp7C.x;
        sp70.y = sp7C.y;
        sp70.z = (Math_CosS(sp22) * 50.0f) + sp7C.z;
        if ((func_800CC000(camera, &sp70, &sp34) != 0) && (Camera_CheckOOB(camera, &sp7C, &sp70) != 0)) {
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
    Vec3f* at = &camera->at; // 28-2C-30
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
        OLib_Vec3fToVecSphGeo(&eyeChk->sphNorm, &eyeChk->norm);

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
        OLib_Vec3fToVecSphGeo(&atChk->sphNorm, &atChk->norm);

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
s32 Camera_CalcAtDefault(Camera *camera, VecSph *eyeAtDir, f32 extraYOffset, s16 calcSlope) {
    Vec3f* at = &camera->at;
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
        posOffsetTarget.y -= OLib_ClampMaxDist(
            Camera_CalcSlopeYAdj(&camera->floorNorm, playerPosRot->rot.y, eyeAtDir->yaw, 25.0f), yOffset);
    }

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);

    atTarget.x = playerPosRot->pos.x + camera->posOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->posOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->posOffset.z;

    if (atTarget.y < (camera->playerGroundY + 10.0f)) {
        atTarget.y = camera->playerGroundY + 10.0f;
    }

    Camera_LERPCeilVec3f(&atTarget, at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return true;
}

s32 func_800CD834(Camera *camera, VecSph *eyeAtDir, f32 arg2, f32* arg3, f32 arg4) {
    f32 deltaY;
    Vec3f posOffsetTarget;
    Vec3f atTarget; // 4C
    Vec3f* new_var;
    f32 temp_f2; // 44
    f32 temp_f0;
    s16 phi_v1;     // 3E-playerPosRot.rot.y
    s16 temp_v0;    // 3C-playerPosRot.rot.x
    PosRot* playerPosRot; // 30


    posOffsetTarget.y = arg2 + func_800CB700(camera);
    posOffsetTarget.x = 0.0f;
    posOffsetTarget.z = 0.0f;

    func_800B8898(camera->globalCtx, &camera->player->actor, &phi_v1, &temp_v0);
    temp_v0 -= 0x78;

    // TODO: ABS()
    if (temp_v0 >= 0) {
        phi_v1 = temp_v0;
    } else {
        phi_v1 = -temp_v0;
    }


    playerPosRot = &camera->playerPosRot;

    OLib_ClampMaxDist(phi_v1 / 120.0f, 1.0f); // Should have an output

    deltaY = playerPosRot->pos.y - *arg3;
    temp_f2 = OLib_ClampMaxDist(deltaY, arg4);

    if (phi_v1 > 0x3C) {
        phi_v1 = 0x3C;
        if (camera) {}
    }

    temp_f0 = OLib_ClampMaxDist(phi_v1/ 60.0f, 1.0f);
    posOffsetTarget.y -= temp_f2 * temp_f0 * temp_f0;

    Camera_LERPCeilVec3f((0, &posOffsetTarget), &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
    atTarget.x = playerPosRot->pos.x + camera->posOffset.x;
    atTarget.y = playerPosRot->pos.y + camera->posOffset.y;
    atTarget.z = playerPosRot->pos.z + camera->posOffset.z;

    if (atTarget.y < (camera->playerGroundY + 10.0f)) {
        atTarget.y = camera->playerGroundY + 10.0f;
    }

    Camera_LERPCeilVec3f(&atTarget, &camera->at, camera->atLERPStepScale, camera->atLERPStepScale, 0.1f);
    return true;
}

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
    Camera_LERPCeilVec3f(&sp50, &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
    sp44.x = temp_s1->pos.x + camera->posOffset.x;
    sp44.y = temp_s1->pos.y + camera->posOffset.y;
    sp44.z = temp_s1->pos.z + camera->posOffset.z;
    sp38.x = temp_s1->pos.x;
    sp38.y = sp44.y;
    sp38.z = temp_s1->pos.z;
    if (func_800CC128(camera, &sp38, &sp44)) {
        sp44.x -= camera->posOffset.x - (sp44.x - sp38.x);
        sp44.z -= camera->posOffset.z - (sp44.z - sp38.z);
    }
    temp_f0 = camera->atLERPStepScale;
    Camera_LERPCeilVec3f(&sp44, &camera->at, temp_f0, temp_f0, 0.2f);
    return 1;
}

s32 func_800CDB6C(Camera *camera, VecSph *arg1, f32 arg2, f32 arg3, f32 *arg4, s16 arg5) {
    f32 new_var;
    Vec3f sp70;
    Vec3f sp64;
    f32 temp_f0;
    f32 temp_f12;
    f32 sp58;
    f32 sp54;
    PosRot *phi_s1;
    f32 sp4C;
    VecSph sp44;
    Vec3f *sp34;


    sp4C = func_800CB700(camera);
    phi_s1 = &camera->playerPosRot;


    if (arg5 & 0x40) {
        sp44.r = func_800CCCEC(camera, arg5 & 0x10);
        sp44.yaw = phi_s1->rot.y + 0x4000;
        sp44.pitch = 0;
        OLib_VecSphGeoToVec3f(&sp70, &sp44);
    } else {
        temp_f0 = camera->posOffset.x + camera->playerPosDelta.x;
        temp_f12 = camera->posOffset.z + camera->playerPosDelta.z;
        if (sqrtf(SQ(temp_f0) + SQ(temp_f12)) < arg3) {
            sp70.x = temp_f0;
            sp70.z = temp_f12;
        } else {
            sp70.x = camera->posOffset.x;
            sp70.z = camera->posOffset.z;
        }
        sp58 = temp_f0; // TODO: Needed to match?
    }

    sp70.y = sp4C + arg2;

    if ((gGameInfo->data[364] != 0) && (arg5 != 0)) {
        sp70.y -= Camera_CalcSlopeYAdj(&camera->floorNorm, phi_s1->rot.y, arg1->yaw, 25.0f);
    }


    if (func_800CB950(camera)) {
        temp_f0 = Camera_LERPCeilF(phi_s1->pos.y, *arg4, 0.4f, 0.1f);
        *arg4 = temp_f0;
        new_var = phi_s1->pos.y - temp_f0;
        sp70.y -= new_var;
        Camera_LERPCeilVec3f(&sp70, &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
        sp34 = &camera->at;
    } else {


        sp34 = &camera->at;
        sp58 = phi_s1->pos.y - *arg4;
        sp54 = OLib_Vec3fDistXZ(sp34, &camera->eye);
        temp_f12 = func_80086760(camera->fov * 0.4f * 0.017453292f) * sp54;


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
        Camera_LERPCeilVec3f(&sp70, &camera->posOffset, 0.3f, 0.2f, 0.1f);
        camera->xzOffsetUpdateRate = 0.3f;
        camera->yOffsetUpdateRate = 0.2f;
    }

    sp64.x = phi_s1->pos.x + camera->posOffset.x;
    sp64.y = phi_s1->pos.y + camera->posOffset.y;
    sp64.z = phi_s1->pos.z + camera->posOffset.z;
    Camera_LERPCeilVec3f(&sp64, sp34, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return 1;
}

// OoTs Camera_CalcAtForLockOn
s32 Camera_CalcAtForLockOn(Camera *camera, VecSph *eyeAtDir, Vec3f *targetPos, f32 yOffset, f32 distance, f32 *yPosOffset, VecSph *outPlayerToTargetDir, s16 flags) {
    Vec3f* sp3C = &camera->at;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    f32 temp_f0_6;
    VecSph sp5C;
    f32 temp_f20;
    f32 temp_f2;
    f32 phi_f16;
    f32 temp_f0 = func_800CB700(camera);
    f32 sp50;
    PosRot *sp38 = &camera->playerPosRot;

    sp80.x = 0.0f;
    sp80.y = temp_f0 + yOffset;
    sp80.z = 0.0f;

    if (PREG(76) && (flags & 1)) {
        sp80.y -= Camera_CalcSlopeYAdj(&camera->floorNorm, camera->playerPosRot.rot.y, eyeAtDir->yaw, 25.0f);
    }

    sp74 = sp38->pos;
    sp74.y += temp_f0;

    OLib_Vec3fDiffToVecSphGeo(outPlayerToTargetDir, &sp74, targetPos);

    sp5C = *outPlayerToTargetDir;
    sp5C.r = (distance < sp5C.r) ? (sp5C.r * 0.2f) : ((sp5C.r * 0.9f) - (sp5C.r * 0.7f * (sp5C.r / distance)));

    if (flags & 0x80) {
        sp5C.r *= 0.2f;
        camera->yOffsetUpdateRate = camera->xzOffsetUpdateRate = 0.01f;
    }

    OLib_VecSphGeoToVec3f(&sp68, &sp5C);

    sp80.x += sp68.x;
    sp80.y += sp68.y;
    sp80.z += sp68.z;


    if (func_800CB950(camera)) {
        *yPosOffset = Camera_LERPCeilF(sp38->pos.y, *yPosOffset, 0.4f, 0.1f);
        temp_f20 = sp38->pos.y - *yPosOffset;
        sp80.y -= temp_f20;
        Camera_LERPCeilVec3f(&sp80, &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
    } else {
        if (!(flags & 0x80)) {
            temp_f20 = sp38->pos.y - *yPosOffset;
            sp50 = OLib_Vec3fDistXZ(sp3C, &camera->eye);
            phi_f16 = sp50;
            func_80086B30(temp_f20, sp50);
            temp_f2 = func_80086760(camera->fov * 0.4f * 0.017453292f) * phi_f16;

            if (temp_f2 < temp_f20) {
                *yPosOffset = *yPosOffset + (temp_f20 - temp_f2);
                temp_f20 = temp_f2;
            } else {
                // phi_f20 = temp_f20;
                if (temp_f20 < -temp_f2) {
                    *yPosOffset += (temp_f20 + temp_f2);
                    temp_f20 = -temp_f2;
                }
            }
            sp80.y -= temp_f20;
        } else {
            temp_f20 = sp38->pos.y - *yPosOffset;
            temp_f0_6 = func_80086B30(temp_f20, OLib_Vec3fDistXZ(sp3C, &camera->eye));

            if (temp_f0_6 > 0.34906584f) {
                phi_f16 = 1.0f - sin_rad(temp_f0_6 - 0.34906584f);
            } else if (temp_f0_6 < -0.17453292f) {
                phi_f16 = 1.0f - sin_rad(-0.17453292f - temp_f0_6);
            } else {
                phi_f16 = 1.0f;
            }
            
            sp80.y -= temp_f20 * phi_f16;
        }

        Camera_LERPCeilVec3f(&sp80, &camera->posOffset, 0.5f, 0.5f, 0.1f);
        camera->xzOffsetUpdateRate = 0.5f;
        camera->yOffsetUpdateRate = 0.5f;
    }

    sp74.x = sp38->pos.x + camera->posOffset.x;
    sp74.y = sp38->pos.y + camera->posOffset.y;
    sp74.z = sp38->pos.z + camera->posOffset.z;
    Camera_LERPCeilVec3f(&sp74, sp3C, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return 1;
}

// Camera_CalcAtForLockOn2?
s32 func_800CE2B8(Camera *camera, f32* arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 *arg6, VecSph* arg7, s16 flags) {
    PosRot* temp_s1;
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
    temp_s1 = &camera->playerPosRot;

    sp78.y = func_800CB700(camera) + arg3;
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
        temp_f20 = (0, temp_s1->pos.y - (*arg6));
        sp78.y -= temp_f20;
        Camera_LERPCeilVec3f(&sp78, &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
    } else {
        if (temp_s1->pos.x) {}
        new_var2 = *arg1;
        sp4C = new_var2;
        temp_f20 = temp_s1->pos.y - *arg6;
        temp_f0_3 = func_80086B30(temp_f20, sp4C);
        if (!(flags & 0x80)) {
            temp_f2 = func_80086760(camera->fov * 0.4f * 0.017453292f) * sp4C;
            if (temp_f2 < temp_f20) {
                *arg6 += (temp_f20 - temp_f2);
                temp_f20 = temp_f2;
            } else {
                // temp_f20 = temp_f20;
                if (temp_f20 < -temp_f2) {
                    *arg6 += (temp_f20 + temp_f2);
                    temp_f20 = -temp_f2;
                }
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
        Camera_LERPCeilVec3f(&sp78, &camera->posOffset, 0.5f, 0.5f, 0.1f);
        camera->xzOffsetUpdateRate = 0.5f;
        camera->yOffsetUpdateRate = 0.5f;
    }

    sp6C.x = temp_s1->pos.x + camera->posOffset.x;
    sp6C.y = temp_s1->pos.y + camera->posOffset.y;
    sp6C.z = temp_s1->pos.z + camera->posOffset.z;
    Camera_LERPCeilVec3f(&sp6C, &camera->at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);
    return 1;
}

s32 Camera_CalcAtForHorse(Camera* camera, VecSph* eyeAtDir, f32 yOffset, f32* yPosOffset, s16 calcSlope) {
    Vec3f* at = &camera->at;
    Vec3f posOffsetTarget;
    Vec3f focalTarget;
    s32 pad[2];
    f32 playerHeight = func_800CB700(camera);
    Player* player = camera->player;
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

    Camera_LERPCeilVec3f(&posOffsetTarget, &camera->posOffset, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.1f);
    focalTarget.x = camera->posOffset.x + horsePosRot.pos.x;
    focalTarget.y = camera->posOffset.y + horsePosRot.pos.y;
    focalTarget.z = camera->posOffset.z + horsePosRot.pos.z;
    Camera_LERPCeilVec3f(&focalTarget, at, camera->atLERPStepScale, camera->atLERPStepScale, 0.2f);

    return 1;
}

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

// TODO: May be f32* return, not void
void func_800CED90(Camera *camera, VecSph *arg1, VecSph *arg2, f32 arg3, f32 arg4, SwingAnimation *arg5, s16 *arg6) {
    // f32 sp98;
    // f32 sp94;
    // f32 sp90;
    f32 pad1[3];
    Vec3f sp90;
    s32 sp8C;
    f32 sp88;
    f32 pad2;
    s32 temp;
    s32 pad3;
    s32 phi_v0;
    s32 phi_v1_2;
    SwingAnimation *new_var;
    Vec3f *sp38 = &camera->eye;
    Vec3f *sp34 = &camera->at;
    s32 pad;
    Vec3f sp58;
    VecSph sp50;
    Vec3f* sp30;

    sp8C = 0;

    new_var = arg5;
    if (arg5->unk_64 == 1) {
        if (arg3 < (sp88 = OLib_Vec3fDist(sp34, &new_var->unk_00))) {
            dummy:;
            new_var->unk_64 = 0;
        } else if ((sp88 = Math3D_SignedDistanceFromPlane(new_var->unk_34.norm.x, new_var->unk_34.norm.y, new_var->unk_34.norm.z, new_var->unk_34.poly->dist, sp34)) > 0.0f) {
            new_var->unk_64 = 0;
        } else if ((sp88 = OLib_Vec3fDist(sp38, &new_var->unk_34.pos)) < 10.0f) {
            new_var->unk_64 = 0;
        } else if ((sp88 = Math3D_SignedDistanceFromPlane(new_var->unk_0C.norm.x, new_var->unk_0C.norm.y, new_var->unk_0C.norm.z, new_var->unk_0C.poly->dist, sp38)) > 0.0f) {
            new_var->unk_64 = 0;
        } else if (new_var->unk_0C.norm.y > 0.50f) {
            new_var->unk_64 = 0;
        } else {
            Math3D_AngleBetweenVectors(&camera->playerPosDelta, &new_var->unk_34.norm, &sp88);
            if (sp88 > 0.0f) {
                new_var->unk_64 = 0;
            }

        }

        if (new_var->unk_64 == 1) {
            sp8C = 2;
        }
    } else {
        if (new_var->unk_64 == 2) {
            new_var->unk_64 = 0;
        }
    }

    if (sp8C == 0) {
        if ((*arg6 & 2) != 0) {
            phi_v1_2 = 2;
        } else {
            phi_v1_2 = 0;
        }
        if (new_var->unk_64 != 1) {
            phi_v0 = 1;
        } else {
            phi_v0 = 0;
        }
        temp = ((s16)phi_v0 | phi_v1_2);
        sp8C = func_800CD44C(camera, arg1, &new_var->unk_0C, &new_var->unk_34, temp);
    }


    switch (sp8C) {
        default:
            sp30 = &new_var->unk_0C.pos;
            *arg6 &= 0xEFFF;
            new_var->unk_5C.r = arg4;
            *sp38 = *sp30;
            break;
        case 1:
            Camera_BGCheckCorner(&new_var->unk_00, &camera->at, &camera->eyeNext, &new_var->unk_0C, &new_var->unk_34);
        case 2:
            sp90.x = new_var->unk_00.x + (new_var->unk_0C.norm.x + new_var->unk_34.norm.x);
            sp90.y = new_var->unk_00.y + (new_var->unk_0C.norm.y + new_var->unk_34.norm.y);
            sp90.z = new_var->unk_00.z + (new_var->unk_0C.norm.z + new_var->unk_34.norm.z);

            sp30 = &camera->eyeNext;
            OLib_Vec3fDiffToVecSphGeo(&sp50, sp34, &sp90);
            sp50.r = arg1->r;
            new_var->unk_64 = 1;
            new_var->unk_5C.r = 1.5f;
            OLib_VecSphAddToVec3f(&sp58, sp34, &sp50);
            if (func_800CBC84(camera, &new_var->unk_34, &sp58, 0) == 0) {
                sp50.yaw = func_800CB674(arg1->yaw, arg2->yaw, (camera->speedRatio * 0.5f) + 0.5f) + arg2->yaw;
                sp50.pitch = func_800CB674(arg1->pitch, arg2->pitch, (camera->speedRatio * 0.5f) + 0.5f) + arg2->pitch;
                if (new_var->unk_0C.sphNorm.pitch < 0x2AA8) {
                    new_var->unk_5C.yaw = sp50.yaw;
                    new_var->unk_5C.pitch = sp50.pitch;
                } else {
                    new_var->unk_5C.yaw = arg1->yaw;
                    new_var->unk_5C.pitch = arg1->pitch;
                }
            }
            *sp38 = *sp30 = sp58;
            break;
        case 3:
        case 6:
            sp30 = &new_var->unk_0C.pos;
            sp88 = OLib_Vec3fDist(sp34, sp30);
            if (sp88 < 60.0f) {
                sp50.yaw = func_800CB674(arg1->yaw, arg2->yaw, camera->speedRatio) + arg2->yaw;
                if ((*arg6 & 0x1000) != 0) {
                    sp50.pitch = arg2->pitch;
                } else {
                    sp50.pitch = Math_CosS(new_var->unk_0C.sphNorm.pitch) * 16380.0f;
                }
                sp50.r = 60.0f - sp88;
                OLib_VecSphAddToVec3f(&sp58, sp30, &sp50);
            } else {
                sp50.yaw = func_800CB674(arg1->yaw, arg2->yaw, camera->speedRatio) + arg2->yaw;
                sp50.pitch = func_800CB674(arg1->pitch, arg2->pitch, camera->speedRatio) + arg2->pitch;
                sp50.r = arg1->r;
                OLib_VecSphAddToVec3f(&sp58, sp34, &sp50);
            }
            func_800CBC84(camera, sp34, &sp58, 0);
            *sp38 = sp58;
            break;
    }
}

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
    f32 sp88 = func_800CB700(camera);
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
    PosRot* sp40 = &camera->playerPosRot;
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
            func_800CB584(camera);;
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
            D_801EDC30[camera->thisIdx].unk_5C.yaw = D_801EDC30[camera->thisIdx].unk_5C.pitch = D_801EDC30[camera->thisIdx].unk_64 = 0;
            anim->unk_0A = 0x514;
            D_801EDC30[camera->thisIdx].unk_5C.r = norm1->unk_0C;
            anim->unk_00 = camera->playerPosRot.pos.y;
            anim->unk_04 = camera->xzSpeed;
            D_801EDC30[camera->thisIdx].unk_66 = 0;
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
        anim->unk_00 = camera->playerPosRot.pos.y;
    }

    if (anim->unk_0C & 0x1000) {
        spC8 = camera->speedRatio;
    } else {
        spC8 = ((camera->speedRatio * 3.0f) + 1.0f) * 0.25f;
    }
    
    spD8 = camera->posOffset;
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
    
    if (D_801EDC30[camera->thisIdx].unk_64 == 1) {
        phi_f2 = 0.5f;
    } else {
        phi_f2 = (0.5f * spC8) + (0.5f * spC4);
    }

    anim->unk_04 = camera->xzSpeed;

    if (D_801EDC30[camera->thisIdx].unk_66 != 0) {
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->thisIdx].unk_66 * 2) + D_801EDC30[camera->thisIdx].unk_5C.r, camera->yawUpdateRateInv, phi_f2, 0.1f);
        if (norm1->unk_22 & 8) {
            camera->pitchUpdateRateInv = Camera_LERPCeilF(100.0f, camera->pitchUpdateRateInv, 0.5f, 0.1f);
        } else {
            camera->pitchUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->thisIdx].unk_66 * 2) + 16.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        }
        D_801EDC30[camera->thisIdx].unk_66--;
    } else {
        camera->yawUpdateRateInv = Camera_LERPCeilF(D_801EDC30[camera->thisIdx].unk_5C.r - (D_801EDC30[camera->thisIdx].unk_5C.r * 0.7f * spC0), camera->yawUpdateRateInv, phi_f2, 0.1f);
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

    if ((D_801EDC30[camera->thisIdx].unk_64 == 1) && (norm1->unk_00 > -40.0f)) {
        phi_f0_4 = Math_SinS(D_801EDC30[camera->thisIdx].unk_5C.pitch);
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
        if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
            switch (camera->player->transformation) {
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
        phi_f0_4 = func_800CE930(camera, spB4.r, phi_f16_2, phi_f16_2, 0);
    } else if (norm1->unk_22 & 0x80) {
        phi_f0_4 = func_800CE930(camera, spB4.r, norm1->unk_04, norm1->unk_08, 1);
    } else {
        phi_f0_4 = func_800CE79C(camera, spB4.r, norm1->unk_04, norm1->unk_08, anim->unk_0A > 0);
    }

    camera->dist = spB4.r = phi_f0_4;

    if (D_801EDC30[camera->thisIdx].unk_64 != 0) {
        if (phi_v1_2) {} 
        spB4.pitch = Camera_LERPCeilS(D_801EDC30[camera->thisIdx].unk_5C.pitch, sp9C.pitch, 1.0f / camera->yawUpdateRateInv, 5);
        spB4.yaw = Camera_LERPCeilS(D_801EDC30[camera->thisIdx].unk_5C.yaw, sp9C.yaw, 1.0f / camera->yawUpdateRateInv, 5);
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

    if (spB4.pitch > 0x36B0) {
        spB4.pitch = 0x36B0;
    }
    if (spB4.pitch < -0x36B0) {
        spB4.pitch = -0x36B0;
    }

    OLib_VecSphAddToVec3f(&camera->eyeNext, &camera->at, &spB4);
    if ((camera->status == CAM_STAT_ACTIVE) && !(norm1->unk_22 & 0x10) && (spC4 <= 0.9f)) {
        
        if (func_800CBA7C(camera) == 0) {
            func_800CED90(camera, &spB4, &sp9C, norm1->unk_04, norm1->unk_0C, &D_801EDC30[camera->thisIdx], &anim->unk_0C);
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
        D_801EDC30[camera->thisIdx].unk_5C.r = norm1->unk_0C;
        D_801EDC30[camera->thisIdx].unk_64 = 0;
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

// TODO: Get D_801EDC30 Size (Check this still matches with bss declared outside)
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
    struct Player* sp5C = camera->player;
    Vec3f* sp3C = &camera->eye;
    Vec3f* sp38 = &camera->at;
    Vec3f* sp34 = &camera->eyeNext;
    PosRot* sp30 = &camera->playerPosRot;

    temp_f2 = func_800CB700(camera);

    if ((camera->setting == CAM_SET_HORSE0) && (sp5C->rideActor == NULL)) {
        Camera_ChangeSettingFlags(camera, camera->prevSetting, 2);
        return 1;
    }

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        temp_f2 = PCT(temp_f2);

        norm3->unk_00 = NEXTSETTING * temp_f2;
        norm3->unk_04 = NEXTSETTING * temp_f2;
        norm3->unk_08 = NEXTSETTING * temp_f2;
        norm3->unk_1C = DEGF_TO_BINANG(NEXTSETTING);
        norm3->unk_0C = NEXTSETTING;
        norm3->unk_10 = NEXTSETTING;
        norm3->unk_14 = NEXTSETTING;
        norm3->unk_18 = NEXTPCT;
        norm3->unk_1E = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp70, sp38, sp3C);
    OLib_Vec3fDiffToVecSphGeo(&sp68, sp38, sp34);
    sUpdateCameraDirection = true;
    sCameraInterfaceFlags = norm3->unk_1E;

    phi_v1_2 = camera->animState;
    if (!(((phi_v1_2 == 0) || (phi_v1_2 == 10)) || (phi_v1_2 == 20))) {
    } else {
        anim->unk_00 = 0;
        anim->unk_08 = 0;
        anim->unk_04 = camera->playerGroundY;

        D_801EDC30[camera->thisIdx].unk_5C.yaw = D_801EDC30[camera->thisIdx].unk_5C.pitch = D_801EDC30[camera->thisIdx].unk_64 = 0;
        D_801EDC30[camera->thisIdx].unk_5C.r = norm3->unk_0C;
        anim->unk_0A = (s16)((s16)(camera->playerPosRot.rot.y + 0x8000) - sp70.yaw) * 0.16666667f;
        anim->unk_0E = 0;
        anim->unk_12 = 0x4B0;

        if (norm3->unk_1E & 2) {
            anim->unk_0C = 6;
            Camera_SetFlags(camera, 0x20);
        } else {
            anim->unk_0C = 0;
        }

        camera->animState = 1;
        D_801EDC30[camera->thisIdx].unk_66 = 0;
        anim->unk_10 = 1;
    }

    if (anim->unk_0E != 0) {
        anim->unk_0E--;
    }

    sp90 = ((camera->speedRatio * 3.0f) + 1.0f) * 0.25f * 0.5f;
    sp8C = (temp_f2 = camera->speedRatio * 0.2f);

    if (D_801EDC30[camera->thisIdx].unk_66 != 0) {
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->thisIdx].unk_66 * 2) + norm3->unk_0C, camera->yawUpdateRateInv, sp90, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->thisIdx].unk_66 * 2) + 16.0f, camera->pitchUpdateRateInv, sp8C, 0.1f);
        D_801EDC30[camera->thisIdx].unk_66--;
    } else {
        camera->yawUpdateRateInv = Camera_LERPCeilF(norm3->unk_0C, camera->yawUpdateRateInv, sp90, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(16.0f, camera->pitchUpdateRateInv, sp8C, 0.1f);
    }

    camera->yOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->yOffsetUpdateRate, sp90, 0.001f);
    camera->xzOffsetUpdateRate = Camera_LERPCeilF(0.05f, camera->xzOffsetUpdateRate, sp8C, 0.0001f);
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, sp8C, 0.0001f);

    phi_v1_2 = func_800CC9C0(camera, sp70.yaw + 0x8000, anim->unk_10 & 1);
    temp_f2 = ((1.0f / norm3->unk_10) * 0.5f) * (1.0f - camera->speedRatio);
    anim->unk_08 = Camera_LERPCeilS(phi_v1_2, anim->unk_08, 
        ((1.0f / norm3->unk_10) * 0.5f) + temp_f2, 5);

    if ((norm3->unk_1E & 0x40) || (sp5C->rideActor == NULL)) {
        Camera_CalcAtDefault(camera, &sp68, norm3->unk_00, 1);
    } else {
        Camera_CalcAtForHorse(camera, &sp68, norm3->unk_00, &anim->unk_04, 1);
    }

    sp88 = (norm3->unk_08 + norm3->unk_04) * 0.5f;
    OLib_Vec3fDiffToVecSphGeo(&sp80, sp38, sp34);
    temp_f2 = func_800CE79C(camera, sp80.r, norm3->unk_04, norm3->unk_08, anim->unk_0E);

    phi_f2 = ((sp88 - temp_f2));
    phi_f2 = phi_f2 *  0.002f;
    camera->dist = sp80.r = temp_f2 + phi_f2;

    if (norm3->unk_1E & 0x80) {
        sp80.pitch = Camera_LERPCeilS(camera->player->actor.focus.rot.x - anim->unk_08, sp68.pitch, 0.25f, 5);
    } else {
        sp62 = norm3->unk_1C - anim->unk_08;
        sp80.pitch = Camera_LERPCeilS(sp62, sp68.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
    }

    if (sp80.pitch > 0x38A4) {
        sp80.pitch = 0x38A4;
    }

    if (sp80.pitch < -0x1554) {
        sp80.pitch = -0x1554;
    }

    if (norm3->unk_1E & 0x80) {
        sp62 = camera->player->actor.focus.rot.y - (s16)(sp68.yaw + 0x8000);
        temp_f2 = 1.0f;
    } else {
        sp62 = sp30->rot.y - (s16)(sp68.yaw + 0x8000);
        OLib_Vec3fToVecSphGeo(&sp78, &camera->playerPosDelta);
        phi_v1_2 = sp30->rot.y - sp78.yaw;
        if (phi_v1_2 < 0) {
            phi_v1_2 *= -1;
        }
        
        if (phi_v1_2 < 0x555A) {
            temp_f2 = 1.0f;
        } else {
            temp_f2 = (32768.0f - phi_v1_2) / 10918.0f;
        }
    }

    sp90 = (sp62 * ((camera->speedRatio * camera->speedRatio * 0.8f) + 0.2f) * temp_f2) / camera->yawUpdateRateInv;
    if ((Camera_fabsf(sp90) > 150.0f) && (camera->speedRatio > 0.05f)) {
        sp80.yaw = sp68.yaw + sp90;
    }

    if (anim->unk_0C > 0) {
        sp80.yaw += anim->unk_0A;
        anim->unk_0C--;
        if (anim->unk_0C == 0) {
            Camera_ClearFlags(camera, 0x20);
        }
    }

    OLib_VecSphAddToVec3f(sp34, sp38, &sp80);
    if (camera->status == CAM_STAT_ACTIVE) {
        *sp3C = *sp34;
        func_800CBFA4(camera, sp38, sp3C, 0);
    } else {
        *sp3C = *sp34;
    }

    camera->fov = Camera_LERPCeilF(norm3->unk_14, camera->fov, camera->fovUpdateRate, 0.1f);
    if (norm3->unk_1E & 0x20) {
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.05f, 5);
    } else {
        camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
    }

    camera->atLERPStepScale = Camera_ClampLERPScale(camera, norm3->unk_18);
    anim->unk_10 &= ~1;
    return 1;
}

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

// NON_EQUIVALENT?
#ifdef NON_MATCHING
s32 Camera_Normal0(Camera *camera) {
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
    Vec3f *sp40 = &camera->eye;
    Vec3f *sp3C = &camera->at;
    Vec3f *sp38 = &camera->eyeNext;
    PosRot* sp34 = &camera->playerPosRot;
    Normal0Anim* anim = &norm0->anim;
    f32 phi_f0;
    Vec3s *sp5C;
    s16 temp_v1_2;
    s16 phi_a1;
    s16 phi_a0;
    f32 new_var;

    if (phi_a1) {}

    temp_f0 = func_800B6FC8(camera->player);
    temp_f2 = 0.8f - ((68.0f / temp_f0) * -0.2f);

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        norm0->unk_00 = NEXTSETTING * 0.01f * temp_f0 * temp_f2;
        norm0->unk_04 = NEXTSETTING * 0.01f * temp_f0 * temp_f2;
        norm0->unk_08 = NEXTSETTING * 0.01f * temp_f0 * temp_f2;
        norm0->unk_1C = (NEXTSETTING * 182.04167f) + 0.5f;
        norm0->unk_0C = NEXTSETTING;
        norm0->unk_10 = NEXTSETTING * 0.01f;
        norm0->unk_14 = NEXTSETTING;
        norm0->unk_18 = NEXTSETTING * 0.01f;
        norm0->unk_1E = NEXTSETTING;
    }

    sCameraInterfaceFlags = norm0->unk_1E;

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        sp5C = Camera_GetCamBGData(camera, camera->camDataIdx);
        Camera_Vec3sToVec3f(&anim->unk_00, &BGCAM_POS(sp5C));
        anim->unk_20 = BGCAM_ROT(sp5C).x;
        anim->unk_22 = BGCAM_ROT(sp5C).y;
        anim->unk_24 = sp34->pos.y;
        if (BGCAM_FOV(sp5C) == -1) {
            anim->unk_1C = norm0->unk_14;
        } else {
            if (BGCAM_FOV(sp5C) >= 0x169) {
                phi_f0 = BGCAM_FOV(sp5C) * 0.01f;
            } else {
                phi_f0 = BGCAM_FOV(sp5C);
            }
            anim->unk_1C = phi_f0;
        }

        if (BGCAM_UNK_1(sp5C) == -1) {
            anim->unk_2C = 0;
        } else {
            anim->unk_2C = BGCAM_UNK_1(sp5C);
        }
        
        anim->unk_18 = 0.0f;
        anim->unk_28 = 120.0f;
        if (norm0->unk_1E & 4) {
            sp88.pitch = anim->unk_20;
            sp88.yaw = anim->unk_22;
            sp88.r = 100.0f;
            OLib_VecSphGeoToVec3f(&anim->unk_0C, &sp88);
            // OLib_VecSphGeoToVec3f(0.01f, &anim->unk_0C, &sp88, sp5C);
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

    camera->dist = sp98.r = func_800CE79C(camera, sp90.r, norm0->unk_04, norm0->unk_08, 0);
    if (!(anim->unk_2C & 1)) {
        if (sp98.pitch > 0xE38) {
            sp98.pitch += ((s16)(0xE38 - sp98.pitch) >> 2);
        }
        if (sp98.pitch < 0) {
            sp98.pitch += ((s16)(-0x38E - sp98.pitch) >> 2);
        }
    }
    OLib_VecSphAddToVec3f(sp38, sp3C, &sp98);
    
    *sp40 = *sp38;

    if (camera->status == CAM_STAT_ACTIVE) {
        if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (norm0->unk_1E & 0x10)) {
            func_800CC128(camera, sp3C, sp40);
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Normal0.s")
#endif

#ifdef NON_MATCHING
s32 Camera_Parallel1(Camera *camera) {
    Vec3f *sp44 = &camera->eye;
    Vec3f *sp40 = &camera->at;
    Vec3f *sp3C = &camera->eyeNext;
    Vec3f spB0;
    Vec3f spA4;
    f32 spA0;
    f32 sp9C;
    PosRot *sp38 = &camera->playerPosRot;
    VecSph sp90;
    VecSph sp88;
    VecSph sp80;
    VecSph sp78;
    Parallel1* para1 = (Parallel1*)camera->paramData;
    s16 sp72;
    s16 tangle; // tangle (reused?)
    Parallel1Anim* anim = &para1->anim;
    Vec3s *temp_v0_4;
    s32 new_var3;
    f32 sp60;
    s16 new_var2; 
    s16 phi_a0;
    s32 phi_a0_2;
    // s16 phi_a0_3;
    CameraModeValue* values;
    f32 sp50;

    sp60 = func_800CB700(camera);

    if ((camera->animState != 0) && (camera->animState != 0xA) && (camera->animState != 0x14)) {
    } else {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        para1->unk_00 = NEXTSETTING * 0.01f * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        para1->unk_04 = NEXTSETTING * 0.01f * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        para1->unk_08 = NEXTSETTING * 0.01f * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        para1->unk_20 = NEXTSETTING * 182.04167f + .5f;
        para1->unk_22 = NEXTSETTING * 182.04167f + .5f;
        para1->unk_0C = NEXTSETTING;
        para1->unk_10 = NEXTSETTING;
        para1->unk_14 = NEXTSETTING;
        para1->unk_18 = NEXTSETTING * 0.01f;
        para1->unk_26 = NEXTSETTING;
        para1->unk_1C = NEXTSETTING * 0.01f;
        para1->unk_24 = NEXTSETTING;
        anim->unk_00 = para1->unk_04;
    }
    
    OLib_Vec3fDiffToVecSphGeo(&sp80, sp40, sp44);
    OLib_Vec3fDiffToVecSphGeo(&sp78, sp40, sp3C);
    func_800CBAD4(&spA4, camera);

    switch (camera->animState) {
        case 0x14:
            if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 0) {
                func_800CB584(camera);
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
                anim->unk_10 = camera->playerPosRot.pos;
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

            if ((&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) && (camera->mode == CAM_MODE_CHARGE)) {
                anim->unk_22 = 0x1E;
                if (camera->player->transformation == PLAYER_FORM_DEKU) {
                    para1->unk_24 = -1;
                }
            }

            if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x8 | 0x2)) {
                anim->unk_22 = 1;
                sp50 = 0.8f - ((68.0f / sp60) * -0.2f);
                temp_v0_4 = Camera_GetCamBGData(camera, camera->camDataIdx);
                anim->unk_20 = BGCAM_ROT(temp_v0_4).x;
                anim->unk_1E = BGCAM_ROT(temp_v0_4).y;
                anim->unk_08 = (BGCAM_FOV(temp_v0_4) == -1) ? para1->unk_14 : (BGCAM_FOV(temp_v0_4) > 360) ? BGCAM_FOV(temp_v0_4) * 0.01f : BGCAM_FOV(temp_v0_4);
                anim->unk_00 = (BGCAM_UNK_1(temp_v0_4) == -1) ? para1->unk_04 : BGCAM_UNK_1(temp_v0_4) * 0.01f * sp60 * sp50;
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
                anim->unk_1E = BINANG_ROT180(camera->playerPosRot.rot.y) + para1->unk_22;
                anim->unk_20 = para1->unk_20;
                break;
            case 0x4:
                anim->unk_1E = para1->unk_22;
                anim->unk_20 = para1->unk_20;
                break;
            case (0x4 | 0x2):
                if (anim->unk_24 == 1) {
                    OLib_Vec3fDiffToVecSphGeo(&sp88, &anim->unk_10, &spA4);
                    anim->unk_1E = ((ABS(BINANG_SUB(sp88.yaw, sp80.yaw)) < 0x3A98) || func_800CBA08(camera)) ? sp80.yaw : sp80.yaw + (s16)((BINANG_SUB(sp88.yaw, sp80.yaw) >> 2) * 3);
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
        anim->unk_1E = BINANG_ROT180(camera->playerPosRot.rot.y) + para1->unk_22;
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

    if (func_800CB950(camera) || (camera->player->stateFlags1 & 0x1000) || (camera->player->stateFlags3 & 0x100)) {
        anim->unk_04 = camera->playerPosRot.pos.y; sp72 = false;
    } else {
        sp72 = true;
    }

    if ((camera->player->stateFlags1 & 0x4000) || (camera->player->stateFlags1 & 4) || ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 6)) {
        spB0 = spA4;
        spB0.y += ((sp60 * 0.6f) + para1->unk_00);
        Camera_LERPCeilVec3f(&spB0, sp40, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.0001f);
        func_800CB6C8(camera, &sp38->pos);
    } else {
        if ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == (0x8 | 0x4 | 0x2)) {
            spB0 = sp38->pos;
            spB0.y += sp60 + para1->unk_00;
            Camera_LERPCeilVec3f(&spB0, sp40, camera->xzOffsetUpdateRate, camera->yOffsetUpdateRate, 0.0001f);
            func_800CB6C8(camera, &sp38->pos);
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
            sp90.yaw = sp80.yaw + ((BINANG_SUB(anim->unk_1E, sp80.yaw) / tangle) * anim->unk_22);
            phi_a0 = ((para1->unk_26 & 1) ? BINANG_SUB(anim->unk_20, anim->unk_1C) : anim->unk_20);
            new_var2 = BINANG_SUB(phi_a0, sp80.pitch);
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

        // TODO: Everything above is fine
        new_var3 = (para1->unk_26 & (0x8 | 0x4 | 0x2));

        /**
         * TODO: 
         * When phi_a0_2 is s16:
         *      - IDO is making SP out of phi_a0_2 when it shouldn't.
         *      - A s16 cast is missing, so phi_a0_2 is set to another arbitrary s16: tangle
         *      - Not using tangle still has the extra SP problem
         * When phi_a0_2 is s32:
         *      - No more SP
         *      - An extra s16 cast is make on the else if (new_var3 != 0x8) branch below
         *      - These are s16 angles, so likely s16. But not guarenteed
         */

        // PERM_RANDOMIZE(

        if (para1->unk_26 & 1) {
            phi_a0 = (anim->unk_20 - anim->unk_1C);
            // phi_a0_2 = tangle; // resued temp needed for extra s16 cast
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

        // )

         // TODO: Everything below is fine

        if (sp90.pitch > 0x38A4) {
            sp90.pitch = 0x38A4;
        }
        if (sp90.pitch < -0x1554) {
            sp90.pitch = -0x1554;
        }
        
    }


   

    if (anim->unk_24 > 0) {
        anim->unk_24--;
    }

    
    OLib_VecSphAddToVec3f(sp3C, sp40, &sp90);

    if (camera->status == CAM_STAT_ACTIVE) {
        if ((camera->globalCtx->envCtx.skyboxDisabled == 0) || (para1->unk_26 & 0x10)) {
            spB0 = *sp40;
            if ((camera->player->stateFlags1 & 0x4000) || (camera->player->stateFlags1 & 4) || ((para1->unk_26 & (0x8 | 0x4 | 0x2)) == 6)) {
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
    return 1;
    
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Parallel1.s")
#endif


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

// Rodata/Bss Issues
#ifdef NON_MATCHING
s32 Camera_Jump2(Camera *camera) {
    Jump2* jump2 = (Jump2*)camera->paramData;
    f32 temp_f0_2;
    f32 temp_f0_5;
    Vec3f spC8;
    Vec3f spBC;
    VecSph spB4;
    VecSph spAC;
    VecSph spA4;
    VecSph sp9C;
    s16 temp_t2;
    s16 new_var;
    s32 pad2;
    f32 sp90;
    f32 sp8C;
    s32 sp88;
    s16 phi_v1_2;
    Vec3f *sp38 = &camera->eye;
    Vec3f *sp34 = &camera->at;
    Vec3f *sp30 = &camera->eyeNext;
    PosRot *sp2C = &camera->playerPosRot;
    f32 new_var2;
    f32 pad1;
    Vec3f sp60;
    s32 pad[2];
    Jump2Anim* anim = &jump2->anim; // sp28
    f32 phi_f2;
    f32 temp_f14;
    f32 sp48;
    f32 temp_f16;



    sp48 = func_800CB700(camera);

    if (RELOAD_PARAMS) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;

        temp_f14 = 0.8f - (-0.2f * (68.0f / sp48));

        if (camera->playerPosDelta.y > 0.0f) {
            phi_f2 = -10.0f;
        } else {
            phi_f2 = 10.0f;
        }

        jump2->unk_00 = PCT(phi_f2 + NEXTSETTING) * sp48 * temp_f14;
        jump2->unk_04 = NEXTPCT * sp48 * temp_f14;
        jump2->unk_08 = NEXTPCT * sp48 * temp_f14;
        jump2->unk_0C = NEXTPCT;
        jump2->unk_10 = NEXTSETTING;
        jump2->unk_14 = NEXTPCT;
        jump2->unk_18 = NEXTSETTING;
        jump2->unk_1C = NEXTPCT;
        jump2->unk_20 = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp9C, sp34, sp38);
    OLib_Vec3fDiffToVecSphGeo(&spA4, sp34, sp30);

    sCameraInterfaceFlags = jump2->unk_20;

    if (RELOAD_PARAMS) {    
        spC8 = sp2C->pos;
        temp_f0_2 = func_800CC56C(camera, &spC8);
        anim->unk_00 = temp_f0_2;
        anim->unk_04 = spA4.yaw;
        anim->unk_06 = 0;
        if (temp_f0_2 == BGCHECK_Y_MIN) {
            anim->unk_0A = -1;
            anim->unk_00 = sp2C->pos.y - 1000.0f;
        } else if ((sp2C->pos.y - anim->unk_00) < sp48) {
            anim->unk_0A = 1;
        } else {
            anim->unk_0A = -1;
        }

        new_var = (s16)(((s16)(sp2C->rot.y + 0x8000)) - spA4.yaw);
        anim->unk_06 = ((new_var / 6) / 4) * 3;
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
    camera->fovUpdateRate = Camera_LERPCeilF(0.05f, camera->fovUpdateRate, camera->speedRatio * 0.050f, 0.0001f);
    camera->rUpdateRateInv = 1800.0f;
    Camera_CalcAtDefault(camera, &spA4, jump2->unk_00, 0);
    OLib_Vec3fDiffToVecSphGeo(&spB4, sp34, sp38);

    new_var2 = jump2->unk_04;
    phi_f2 = jump2->unk_08 + (jump2->unk_08 * jump2->unk_0C);
    temp_f16 = new_var2 - (jump2->unk_04 * jump2->unk_0C);



    if (spB4.r > phi_f2) {
        spB4.r = phi_f2;
    } else if (spB4.r < temp_f16) {
        spB4.r = temp_f16;
    }

    new_var = (s16)(((s16)(sp2C->rot.y + 0x8000)) - spB4.yaw);
    if (anim->unk_0C != 0) {
        anim->unk_04 = ((s16)(sp2C->rot.y + 0x8000));
        anim->unk_0C--;
        spB4.yaw = Camera_LERPCeilS(anim->unk_04, spA4.yaw, 0.5f, 5);
    } else if (anim->unk_08 < ABS(new_var)) {
        temp_t2 = (s16)(sp2C->rot.y + 0x8000);
        spB4.yaw = Camera_LERPFloorS((new_var < 0) ? (temp_t2 + anim->unk_08) : (temp_t2 - anim->unk_08), spA4.yaw, 0.1f, 1);
    } else {
        spB4.yaw = Camera_LERPCeilS(spB4.yaw, spA4.yaw, 0.25f, 5);
    }
    
    spC8.x = sp2C->pos.x + (Math_SinS(sp2C->rot.y) * 25.0f);
    spC8.y = sp2C->pos.y + (sp48 * 2.2f);
    spC8.z = sp2C->pos.z + (Math_CosS(sp2C->rot.y) * 25.0f);

    temp_f0_5 = func_800CC488(camera, &spBC, &spC8, &sp88);
    if (camera->player->actor.bgCheckFlags & 0x10) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        spB4.pitch = Camera_LERPCeilS(-0x1388, spA4.pitch, 0.2f, 5);
    } else if ((temp_f0_5 != BGCHECK_Y_MIN) && (sp2C->pos.y < temp_f0_5)) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        if (camera->playerPosDelta.y > 1.0f) {
            spB4.pitch = Camera_LERPCeilS(0x1F4, spA4.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }
    } else if ((sp2C->pos.y - anim->unk_00) < sp48) {
        camera->pitchUpdateRateInv = Camera_LERPCeilF(20.0f, camera->pitchUpdateRateInv, 0.2f, 0.1f);
        camera->rUpdateRateInv = Camera_LERPCeilF(20.0f, camera->rUpdateRateInv, 0.2f, 0.1f);
        if (camera->playerPosDelta.y > 1.0f) {
            spB4.pitch = Camera_LERPCeilS(0x1F4, spA4.pitch, 1.0f / camera->pitchUpdateRateInv, 5);
        }
    } else {
        camera->pitchUpdateRateInv = 100.0f;
        camera->rUpdateRateInv = 100.0f;
    }

    if (spB4.pitch > 0x2AF8) {
        spB4.pitch = 0x2AF8;
    }
    if (spB4.pitch < -0x2AF8) {
        spB4.pitch = -0x2AF8;
    }
    OLib_VecSphAddToVec3f(sp30, sp34, &spB4);
    sp60 = *sp30;
    if (func_800CBC84(camera, sp34, &sp60, 0) != 0) {
        spC8 = sp60;
        spAC.pitch = 0;
        spAC.r = spB4.r;
        spAC.yaw = spB4.yaw;
        OLib_VecSphAddToVec3f(&sp60, sp34, &spAC);
        if (func_800CBC84(camera, sp34, &sp60, 0) != 0) {
            *sp38 = spC8;
        } else {
            spB4.pitch = Camera_LERPCeilS(0, spB4.pitch, 0.2f, 5);
            OLib_VecSphAddToVec3f(sp38, sp34, &spB4);
            func_800CBFA4(camera, sp34, sp38, 0);
        }
    } else {
        *sp38 = *sp30;
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
    PosRot* sp3C = &camera->playerPosRot;
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

    sp78 = func_800CB700(camera);
    func_800B81E0(&sp64, camera->player);
    sp60 = camera->waterYPos - sp48->y;

    sp58 = false;

    if (RELOAD_PARAMS) {
        anim->unk_0A = camera->mode;
        anim->unk_0C = 0;
    }

    if (camera->mode == CAM_MODE_NORMAL) {
        if ((camera->player->actor.bgCheckFlags & 0x10) || (anim->unk_0C != 0)) {
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
        } else if (Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) {
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
            D_801EDC30[camera->thisIdx].unk_5C.yaw = D_801EDC30[camera->thisIdx].unk_5C.pitch = D_801EDC30[camera->thisIdx].unk_64 = 0;
            anim->unk_08 = 0xA;
            D_801EDC30[camera->thisIdx].unk_5C.r = jump3->unk_0C;
            camera->animState++;
            D_801EDC30[camera->thisIdx].unk_66 = 0;
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

    temp_f0 = (D_801EDC30[camera->thisIdx].unk_64 == 1) ? 0.5f : spD0;



    if (D_801EDC30[camera->thisIdx].unk_66 != 0) {
        // spD0 = temp_f2;
        // spCC = camera->speedRatio * 0.2f;
        camera->yawUpdateRateInv = Camera_LERPCeilF((D_801EDC30[camera->thisIdx].unk_5C.r + D_801EDC30[camera->thisIdx].unk_66 * 2), camera->yawUpdateRateInv, spD0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF((40.0f + D_801EDC30[camera->thisIdx].unk_66 * 2), camera->pitchUpdateRateInv, spCC, 0.1f);
        D_801EDC30[camera->thisIdx].unk_66--;
    } else {
        // spCC = camera->speedRatio * 0.2f;
        // phi_f14 = camera->yawUpdateRateInv;
        camera->yawUpdateRateInv = Camera_LERPCeilF(D_801EDC30[camera->thisIdx].unk_5C.r, camera->yawUpdateRateInv, temp_f0, 0.1f);
        camera->pitchUpdateRateInv = Camera_LERPCeilF(40.0f, camera->pitchUpdateRateInv, spCC, 0.1f);
    }

    // NOT ELSE
    // PERM_RANDOMIZE(

    if (jump3->unk_22 & 0x80) {
        camera->yOffsetUpdateRate = Camera_LERPCeilF(0.01f, camera->yOffsetUpdateRate, spD0, 0.0001f);
        // sp4C = sqrtf(SQXZ(camera->playerPosDelta));
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
    spAC.r = func_800CE79C(camera, spAC.r, jump3->unk_04, jump3->unk_08, anim->unk_08);
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
    } else if (D_801EDC30[camera->thisIdx].unk_64 == 1) {
        pad1 = 1.0f / camera->yawUpdateRateInv;
        spAC.yaw = Camera_LERPCeilS(D_801EDC30[camera->thisIdx].unk_5C.yaw, sp94.yaw, pad1, 5);
        // temp_f0 = 1.0f / camera->yawUpdateRateInv;
        // Bug? Should be pitchUpdateRateInv
        spAC.pitch = Camera_LERPCeilS(D_801EDC30[camera->thisIdx].unk_5C.pitch, sp94.pitch, 1.0f / camera->yawUpdateRateInv, 5);
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
    
    if (spAC.pitch > 0x38A4) {
        spAC.pitch = 0x38A4;
    }

    if (spAC.pitch < -0x1554) {
        spAC.pitch = -0x1554;
    }

    OLib_VecSphAddToVec3f(sp40, sp44, &spAC);
    if ((camera->status == CAM_STAT_ACTIVE) && !(jump3->unk_22 & 0x40)) {
        if (func_800CBA7C(camera) == 0) {
            func_800CED90(camera, &spAC, &sp9C, jump3->unk_04, jump3->unk_0C, &D_801EDC30[camera->thisIdx], &anim->unk_10);
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
        D_801EDC30[camera->thisIdx].unk_5C.r = jump3->unk_0C;
        D_801EDC30[camera->thisIdx].unk_64 = 0;
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
    sp8C = &camera->player->actor.focus;
    sp68 = func_800CB700(camera);
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
        anim->unk_04 = camera->playerPosRot.pos.y - camera->playerPosDelta.y;
        if ((2.0f * batt1->unk_04) < camera->dist) {
            camera->dist = 2.0f * batt1->unk_04;
            sp94.r = camera->dist;
            sp9C.r = sp94.r;
            OLib_VecSphAddToVec3f(sp50, sp4C, &sp9C);
            *sp48 = *sp50;
        }
    }

    if (camera->status == CAM_STAT_ACTIVE) {
        sUpdateCameraDirection = true;
        camera->inputDir.x = -sp9C.pitch;
        camera->inputDir.y = sp9C.yaw + 0x8000;
        camera->inputDir.z = 0;
    }

    if (func_800CB950(camera)) {
        anim->unk_04 = camera->playerPosRot.pos.y;
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

    func_800B81E0(&sp40->pos, camera->target);

    if (anim->unk_08 != camera->target) {
        camera->animState = 0;
        return true;
    } 

    sp120 = camera->playerPosRot.pos;
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
        if (camera->status == CAM_STAT_ACTIVE) {
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
    PosRot *sp3C = &camera->playerPosRot;
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



    spA4 = &camera->player->actor.focus;
    if (temp_v0_3) {} // TODO: Is needed?
    sp78 = 0;
    temp_f0 = func_800CB700(camera);
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


    if (camera->status == CAM_STAT_ACTIVE) {
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
        func_800B8248(sp30, camera->target);
        func_800B81E0(&spA8, camera->target);
        camera->targetPosRot.pos.y = spA8.y;
    } else {
        func_800B81E0(sp30, camera->target);
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
        if (camera->status == CAM_STAT_ACTIVE) {
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

#ifdef NON_MATCHING
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
    PosRot* sp3C = &camera->playerPosRot;
    KeepOn3Anim* anim = &keep3->anim;
    f32 sp58;
    s32 i;

    sp70 = &camera->player->actor.focus; // TODO: Move above?
    sp6A = 0;
    sp58 = func_800CB700(camera);

    if ((camera->target == NULL) || (camera->target->update == NULL)) {
        camera->target = NULL;
        Camera_ChangeMode(camera, CAM_MODE_TARGET);
        return 1;
    }

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        if (camera->globalCtx->view.unk164 == 0) {
            Camera_SetFlags(camera, 0x20);
            camera->globalCtx->view.unk164 = camera->thisIdx | 0x50;
            return 1;
        }
        Camera_ClearFlags(camera, 0x20);
    }

    Camera_ClearFlags(camera, 0x10);
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
    func_800B81E0(&camera->targetPosRot, camera->target);
    spD8 = sp3C->pos;
    spD8.y += sp58;
    OLib_Vec3fDiffToVecSphGeo(&spA0, &spD8, &camera->targetPosRot);

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {

        camera->animState++;
        spA8[0] = camera->target;
        spA8[1] = &camera->player->actor;
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

            if (ABS(spA0.pitch) < 0x157C) {
                sp98.yaw = (s16)(spA0.yaw + 0x8000) + phi_a3;
                sp6A = (s16)((s16)(spA0.yaw + 0x8000) - phi_a3);
            } else {
                sp78 = 0;
                sp90.r = 30.0f;
                sp90.yaw = (s16)(spA0.yaw + 0x8000) + (phi_a3 >> 2);
                sp90.pitch = -spA0.pitch;
                spCC = sp70->pos;
                spCC.y += 30.0f;
                OLib_VecSphAddToVec3f(&spC0, &spCC, &sp90);
                spCC.x = (camera->targetPosRot.pos.x + spD8.x) * 0.5f;
                spCC.y = (camera->targetPosRot.pos.y + spD8.y) * 0.5f;
                spCC.z = (camera->targetPosRot.pos.z + spD8.z) * 0.5f;
                OLib_Vec3fDiffToVecSphGeo(&sp98, &spCC, &spC0);
                if (sp98.pitch < -0x2328) {
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
            if ((s16)((s16)(spA0.yaw + 0x8000) - sp80.yaw) < 0) {
                phi_a3 = -phi_a3;
            }

            sp98.yaw = (s16)(spA0.yaw + 0x8000) + phi_a3;
            sp6A = (s16)(spA0.yaw + 0x8000) - phi_a3;
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
                if (CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, &anim->unk_10, &spCC, &spA8, 2) || func_800CC128(camera, &anim->unk_10, &spCC)) {
                    sp98.yaw = sp6A;
                    OLib_VecSphAddToVec3f(&spCC, &anim->unk_10, &sp98);
                }
                while (i < sp78) {
                    if (!CollisionCheck_LineOCCheck(camera->globalCtx, &camera->globalCtx->colChkCtx, &anim->unk_10,
                                                    &spCC, &spA8, 2) &&
                        !func_800CC128(camera, &anim->unk_10, &spCC)) {
                        break;
                    }
                    sp98.yaw = sp6C + D_801B9E18[i];
                    sp98.pitch = sp6E + D_801B9E34[i];
                    OLib_VecSphAddToVec3f(&spCC, &anim->unk_10, &sp98);
                    i++;
                }
            }
        }
        
        Camera_ClearFlags(camera, 0xC);
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

    func_800CB6C8(camera, sp3C);
    camera->dist = OLib_Vec3fDist(temp_s0, sp48);
    if (camera->flags2 & 8) {
        sCameraInterfaceFlags = 0;
        func_800CB5DC(camera);
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
            Camera_ClearFlags(camera, 0x8);
        }
    }

    if (anim->unk_0C != camera->target) {
        anim->unk_0C = camera->target;
        camera->animState = 0xA;
    }

    return 1;

}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_KeepOn3.s")
#endif

s32 Camera_KeepOn4(Camera* camera) {
    static Vec3f D_801EDDD0;
    static Vec3f D_801EDDE0;
    static Vec3f D_801EDDF0;
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
    PosRot* sp38 = &camera->playerPosRot;
    f32 temp_f0_2;
    KeepOn4Anim* anim = &keep4->anim;
    f32 sp88;
    s32 sp84; // bgId
    s16 sp82; // mode
    Player* sp7C; // player
    Vec3f* data;
    CameraModeValue* values;
    PosRot sp60;
    PosRot sp4C;

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        if (camera->globalCtx->view.unk164 == 0) {
            Camera_SetFlags(camera, 0x20);
            Camera_ClearFlags(camera, 6);
            camera->globalCtx->view.unk164 = camera->thisIdx | 0x50;
            return 1;
        }
        anim->unk_18 = *sp44;
        Camera_ClearFlags(camera, 0x20);
    }

    if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        sp7C = camera->player;
        switch (camera->player->transformation) {
            case PLAYER_FORM_DEKU:
                sp82 = CAM_MODE_NUTSSHOT;
                break;
            case PLAYER_FORM_GORON:
                sp82 = CAM_MODE_GORONDASH;
                break;
            case PLAYER_FORM_ZORA:
                sp82 = CAM_MODE_NUTSFLY;
                break;
            case PLAYER_FORM_FIERCE_DEITY:
                sp82 = CAM_MODE_JUMP;
                break;
            default:
                sp82 = CAM_MODE_NORMAL;
                break;
        }

        sp88 = func_800CB700(camera) - (sp7C->unk_AB8 * camera->player->actor.scale.y);
    } else {
        sp82 = CAM_MODE_NORMAL;
        sp88 = func_800CB700(camera);
    }

    if (anim->unk_18 != *sp44) {
        camera->animState = 0x14;
        Camera_SetFlags(camera, 0x20);
        Camera_ClearFlags(camera, (0x4 | 0x2));
        camera->globalCtx->view.unk164 = camera->thisIdx | 0x50;
        return 1;
    }

    Camera_ClearFlags(camera, 0x10);
    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        values = sCameraSettings[camera->setting].cameraModes[sp82].values;
        new_var = -0.5f;
        keep4->unk_00 = NEXTSETTING * 0.01f * sp88 * ((1.0f + new_var) - ((68.0f / sp88) * new_var));
        keep4->unk_04 = NEXTSETTING * 0.01f * sp88 * ((1.0f + new_var) - ((68.0f / sp88) * new_var));
        keep4->unk_08 = NEXTSETTING;
        keep4->unk_0C = NEXTSETTING;
        keep4->unk_10 = NEXTSETTING;
        keep4->unk_18 = NEXTSETTING;
        keep4->unk_1C = NEXTSETTING;
        keep4->unk_14 = NEXTSETTING * 0.01f;
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
            spCC[sp9C] = &camera->player->actor;
            sp9C++;
            func_800CB544(camera);
            Camera_ClearFlags(camera, 6);
            anim->unk_14 = keep4->unk_1E;
            anim->unk_08 = sp38->pos.y - camera->playerPosDelta.y;

            switch (keep4->unk_1C & (0x8 | 0x4 | 0x2)) {
                case 0x2:
                    spA2 = DEGF_TO_BINANG(keep4->unk_08);
                    spA0 = BINANG_SUB(BINANG_ROT180(sp38->rot.y), spA8.yaw) < 0
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
                    if (camera->target != 0) {
                        func_800B8248(&sp60, camera->target);
                        spA2 = DEGF_TO_BINANG(keep4->unk_08) - sp60.rot.x;
                        spA0 = (BINANG_SUB(BINANG_ROT180(sp60.rot.y), spA8.yaw) > 0) 
                                ? BINANG_ROT180(sp60.rot.y) + DEGF_TO_BINANG(keep4->unk_0C)
                                : BINANG_ROT180(sp60.rot.y) - DEGF_TO_BINANG(keep4->unk_0C);
                        
                        spCC[1] = camera->target;
                        sp9C++;
                        break;
                    }
                case (0x8 | 0x2):
                    if (camera->target != 0) {
                        func_800B8214(&sp4C, camera->target); // TODO: update function.h (Actor_GetWorld)
                        spA2 = DEGF_TO_BINANG(keep4->unk_08);
                        sp9E = Camera_XZAngle(&sp4C.pos, &sp38->pos);
                        spA0 = (BINANG_SUB(sp9E, spA8.yaw) > 0) 
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
            func_800CB6C8(camera, &sp38->pos);
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
        func_800CB6C8(camera, &sp38->pos);
    }
    camera->dist = Camera_LERPCeilF(keep4->unk_04, camera->dist, 0.25f, 1.0f);
    spB8.r = camera->dist;
    if (anim->unk_14 != 0) {
        Camera_SetFlags(camera, 0x20);
        anim->unk_10 += (s16)anim->unk_00;
        anim->unk_12 += (s16)anim->unk_04;
        anim->unk_14--;
    } else {
        Camera_SetFlags(camera, 0x410);
    }
    spB8.yaw = Camera_LERPCeilS(anim->unk_10, spA8.yaw, keep4->unk_14, 5);
    spB8.pitch = Camera_LERPCeilS(anim->unk_12, spA8.pitch, keep4->unk_14, 5);
    OLib_VecSphAddToVec3f(sp3C, sp40, &spB8);
    *sp44_2 = *sp3C;
    func_800CBFA4(camera, sp40, sp44_2, 3);
    camera->fov = Camera_LERPCeilF(keep4->unk_18, camera->fov, camera->fovUpdateRate, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    return 1;

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
    Vec3s* sceneCamData;
    Vec3f* eye = &camera->eye;
    Vec3f* at = &camera->at;
    PosRot* playerPosRot = &camera->playerPosRot;
    f32 playerHeight;
    CameraModeValue* values;
    PosRot* sp50;
    PosRot* sp4C;
    VecSph sp44;
    Fixed1Anim* anim = &fixd1->anim;
    s32 pad2;

    playerHeight = func_800CB700(camera);
    OLib_Vec3fDiffToVecSphGeo(&sp7C, at, eye);

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

            OLib_Vec3fDiffToVecSphGeo(&sp44, &sp50->pos, &anim->eyePosRotTarget.pos);
            sp44.yaw = sp4C->rot.y + (s16)(sp44.yaw - sp50->rot.y);
            OLib_VecSphAddToVec3f(&anim->eyePosRotTarget.pos, &sp4C->pos, &sp44);
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

        if (BGCAM_UNK_1(sceneCamData) != negOne) {
            fixd1->jfifId = PCT(BGCAM_UNK_1(sceneCamData));
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
    func_800CC128(camera, eye, at);
    camera->fov = Camera_LERPCeilF(fixd1->fov, camera->fov, fixd1->jfifId, 0.1f);
    camera->roll = 0;
    camera->atLERPStepScale = 0.0f;
    func_800CB6C8(camera, &playerPosRot->pos);
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
    PosRot* sp34 = &camera->playerPosRot;
    f32 temp_f0_3;
    f32 new_var;
    Vec3s* sp88;
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

    sp60 = func_800CB700(camera);

    if (!RELOAD_PARAMS) {
    } else {
        if (new_var2) {}
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        fixd2->unk_00 = NEXTSETTING * 0.01f * sp60 * (0.8f - ((68.0f / sp60) * -0.2f));
        fixd2->unk_04 = NEXTSETTING;
        fixd2->unk_08 = NEXTSETTING;
        fixd2->unk_0C = NEXTSETTING * 0.01f;
        fixd2->unk_10 = NEXTSETTING * 0.01f;
        fixd2->unk_14 = NEXTSETTING;
        fixd2->unk_18 = NEXTSETTING;
        anim->unk_1C = fixd2->unk_14 * 100.0f;
        sp88 = Camera_GetCamBGData(camera, camera->camDataIdx);
        if (sp88 != NULL) {
            if ((fixd2->unk_18 & 2) == 0) {
                Camera_Vec3sToVec3f(&anim->unk_00, &BGCAM_POS(sp88));
            } else {
                if (&camera->player->actor !=  camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
                    player = (Player*)camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first;
                    OLib_Vec3fDiffToVecSphGeo(&sp70, &player->actor.focus.pos, sp40);
                    if (sp70.r < fixd2->unk_04) {
                        sp70.r = fixd2->unk_04;
                        if (sp70.pitch < 0xBB8) {
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

            if (BGCAM_FOV(sp88) != -1) {
                if (fixd2->unk_18 & 0x80) {
                    anim->unk_1C = (BGCAM_FOV(sp88) >> 2) + (BGCAM_FOV(sp88) >> 1);
                    if (anim->unk_1C < 0x1E) {
                        anim->unk_1C = 0x1E;
                    }
                } else {
                    anim->unk_1C = BGCAM_FOV(sp88);
                }
            }

            if (BGCAM_UNK_1(sp88) != -1) {
                anim->unk_0C = BGCAM_UNK_1(sp88);
            } else {
                anim->unk_0C = fixd2->unk_08;
            }

            if (BGCAM_UNK_2(sp88) != -1) {
                if (fixd2->unk_18 & 4) {
                    anim->unk_14 = BGCAM_UNK_2(sp88) * 0.01f;
                    anim->unk_18 = fixd2->unk_0C;
                } else {
                    temp_f0_3 = BGCAM_UNK_2(sp88) * 0.01f;
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
        if (anim->unk_1C < 0x169) {
            anim->unk_1C = anim->unk_1C * 0x64;
        }
        if (camera->animState == 0x14) {
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
        camera->posOffset.x = spB0.x - sp34->pos.x;
        camera->posOffset.y = spB0.y - sp34->pos.y;
        camera->posOffset.z = spB0.z - sp34->pos.z;
    } else if (fixd2->unk_18 & 0x40) {
        sp98.x = new_var;
        sp98.y = fixd2->unk_00 + sp60;
        sp98.z = new_var;

        if (camera->target != NULL) {
            new_var1 = &camera->player->actor.focus.pos;
            new_var2 = &camera->target->focus.pos;
            sp98.x = (0, new_var) + ((new_var2->x - new_var1->x) * 0.4f);
            sp98.y += (new_var2->y - new_var1->y) * 0.4f;
            sp98.z = (0, new_var) + ((new_var2->z - new_var1->z) * 0.4f);
        }

        Camera_LERPCeilVec3f(&sp98, &camera->posOffset, 0.25f, 0.25f, 0.1f);
        spB0.x = sp34->pos.x + camera->posOffset.x;
        spB0.y = sp34->pos.y + camera->posOffset.y;
        spB0.z = sp34->pos.z + camera->posOffset.z;
    } else if (fixd2->unk_18 & 0x80) {
        sp98.x = new_var;
        sp98.y = fixd2->unk_00 + sp60;
        sp98.z = new_var;
       
        if (camera->target != NULL) {
            new_var1 = &camera->player->actor.focus.pos;
            new_var2 = &camera->target->focus.pos;
            sp98.x = (0, new_var) + ((new_var2->x - new_var1->x)* 0.7f);
            sp98.y += (new_var2->y - new_var1->y) * 0.7f;
            sp98.z = (0, new_var) + ((new_var2->z - new_var1->z) * 0.7f);
        }

        Camera_LERPCeilVec3f(&sp98, &camera->posOffset, 0.25f, 0.25f, 0.1f);
        spB0.x = sp34->pos.x + camera->posOffset.x;
        spB0.y = sp34->pos.y + camera->posOffset.y;
        spB0.z = sp34->pos.z + camera->posOffset.z;
    } else {
        sp98.x = new_var;
        sp98.z = new_var;
        if ((camera->player->stateFlags1 & 0x4000)|| (camera->player->stateFlags1 & 4)) {
            sp98.y = fixd2->unk_00;
        } else {
            sp98.y = fixd2->unk_00 + sp60;
        }

        Camera_LERPCeilVec3f(&sp98, &camera->posOffset, anim->unk_14, anim->unk_14, 0.1f);
        spB0.x = sp34->pos.x + camera->posOffset.x;
        spB0.y = sp34->pos.y + camera->posOffset.y;
        spB0.z = sp34->pos.z + camera->posOffset.z;
    }

    if (camera->animState == 0) {
        func_800CB5DC(camera);
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
    func_800CB6C8(camera, &sp34->pos);
    camera->animState = 1;
    return 1;

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
    Vec3f* sp34 = &camera->eye;
    Vec3f* temp_s1 = &camera->at;
    Vec3f* sp2C = &camera->eyeNext;
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


    func_800B81E0(&sp58.pos, &camera->player->actor);
    sp38 = func_800CB700(camera);
    func_800CB544(camera);

    values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
    subj1->unk_00 = NEXTSETTING * 0.01f * sp38;
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
    OLib_Vec3fDiffToVecSphGeo(&sp74, &camera->at, sp34);
    sCameraInterfaceFlags = subj1->unk_20;

    if (camera->globalCtx->view.unk164 == 0) {
        camera->globalCtx->view.unk164 = camera->thisIdx | 0x50;
        return 1;
    }

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
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

        temp_s1->x = temp_s1->x + ((sp90.x - temp_s1->x) * temp_f0);
        temp_s1->y = temp_s1->y + ((sp90.y - temp_s1->y) * temp_f0);
        temp_s1->z = temp_s1->z + ((sp90.z - temp_s1->z) * temp_f0);

        sp54 = ((tsph.r - sp7C.r) * 0.16666667f);
        sp4E = BINANG_SUB(tsph.pitch, sp7C.yaw) * 0.16666667f;
        sp4C = BINANG_SUB(tsph.yaw, sp7C.pitch) * 0.16666667f;

        sp74.r = Camera_LERPCeilF((anim->unk_08 * sp54) + sp7C.r, sp74.r, 0.5f, 1.0f);
        sp74.yaw = Camera_LERPCeilS(sp7C.yaw + (sp4E * anim->unk_08), sp74.yaw, 0.5f, 5);
        sp74.pitch = Camera_LERPCeilS(sp7C.pitch + (sp4C * anim->unk_08), sp74.pitch, 0.5f, 5);

        OLib_VecSphAddToVec3f(sp2C, temp_s1, &sp74);
        *sp34 = *sp2C;
        anim->unk_08--;
    } else {
        sp54 = Math_SinS(-sp58.rot.x);
        temp_f0_2 = Math_CosS(-sp58.rot.x);

        sp90.x = subj1->unk_10;
        sp90.y = (subj1->unk_14 * temp_f0_2) - (subj1->unk_18 * sp54);
        sp90.z = (subj1->unk_14 * sp54) + (subj1->unk_18 * temp_f0_2);

        sp54 = Math_SinS(sp58.rot.y + 0x8000);
        temp_f0_2 = Math_CosS(sp58.rot.y + 0x8000);

        subj1->unk_10 = (sp90.z * sp54) + (sp90.x * temp_f0_2);
        subj1->unk_14 = sp90.y;
        subj1->unk_18 = (sp90.z * temp_f0_2) - (sp90.x * sp54);

        temp_s1->x = subj1->unk_10 + sp58.pos.x;
        temp_s1->y = subj1->unk_14 + sp58.pos.y;
        temp_s1->z = subj1->unk_18 + sp58.pos.z;

        sp74.r = subj1->unk_08;
        sp74.yaw = sp58.rot.y + 0x8000;
        sp74.pitch = sp58.rot.x;

        OLib_VecSphAddToVec3f(&camera->eyeNext, temp_s1, &sp74);
        sp74.r = subj1->unk_04;
        OLib_VecSphAddToVec3f(sp34, temp_s1, &sp74);
    }

    if (camera->globalCtx->envCtx.skyboxDisabled == 0) {
        func_800CC128(camera, temp_s1, sp34);
    } else {
        func_800CBFA4(camera, temp_s1, sp34, 3);
    }

    camera->fov = Camera_LERPCeilF(subj1->unk_1C, camera->fov, 0.25f, 0.1f);
    camera->roll = 0;
    camera->atLERPStepScale = 0.0f;

    return 1;
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
    f32 sp48 = func_800CB700(camera);
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
        func_800CB5DC(camera);
        anim->unk_00 = 200.0f;
    }

    if (uniq2->unk_10 & 0x10) {
        *sp34 = *sp3C;
        Camera_ClearFlags(camera, 4);
    }

    sp70 = camera->playerPosRot.pos;

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
        func_800CC128(camera, temp_s1, sp3C);
    }

    camera->dist = OLib_Vec3fDist(temp_s1, sp3C);
    camera->roll = 0;
    camera->fov = Camera_LERPCeilF(uniq2->unk_0C, camera->fov, 0.2f, 0.1f);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);

    return 1;
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
    f32 spB4;
    PosRot* sp40 = &camera->playerPosRot;
    PosRot sp9C;
    struct Player* sp98;
    Vec3f sp8C;
    VecSph sp84;
    VecSph sp7C;
    Vec3s* sp78;
    f32 sp74;
    s32 pad;
    s16 temp_v1;
    Unique0* uniq0 = (Unique0*)camera->paramData;
    Unique0Anim* anim = &uniq0->anim;
    CameraModeValue* values;
    Vec3f sp54;

    spB4 = func_800B6FC8(camera->player);
    sp98 = camera->player;
    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        uniq0->unk_00 = NEXTSETTING;
        uniq0->unk_04 = NEXTSETTING;
        uniq0->unk_08 = NEXTSETTING;
    }


    OLib_Vec3fDiffToVecSphGeo(&sp7C, &camera->at, &camera->eye);
    if (sp98->rideActor != NULL) {
        func_800B8214(&sp9C, sp98->rideActor);
        sp8C = sp9C.pos;
        sp8C.y += spB4 + 20.0f;
    } else {
        sp8C = camera->playerPosRot.pos;
        sp8C.y += spB4;
    }

    sCameraInterfaceFlags = uniq0->unk_08;

    switch (camera->animState) {
        case 0:
            sp78 = Camera_GetCamBGData(camera, camera->camDataIdx);
            Camera_Vec3sToVec3f(&anim->unk_1C, &BGCAM_POS(sp78));
            camera->eye = camera->eyeNext = anim->unk_1C;
            anim->unk_34 = BGCAM_ROT(sp78);
            temp_v1 = BGCAM_FOV(sp78);
            if (temp_v1 != -1) {
                if (temp_v1 < 0x169) {
                    camera->fov = temp_v1;
                } else {
                    camera->fov = temp_v1 * 0.01f;
                }
            }
            anim->unk_3C = BGCAM_UNK_1(sp78);
            if (anim->unk_3C == -1) {
                anim->unk_3C = 0x3C;
            }

            if (BGCAM_UNK_2(sp78) != -1) {
                anim->unk_18 = BGCAM_UNK_2(sp78) * 0.01f;
            } else {
                anim->unk_18 = uniq0->unk_04 * 0.01f;
            }

            anim->unk_00 = sp40->pos;
            if ((uniq0->unk_08 & 0x10) != 0) {
                anim->unk_0C.x = sp40->pos.x;
                anim->unk_0C.y = sp40->pos.y + spB4 + uniq0->unk_00;
                anim->unk_0C.z = sp40->pos.z;
            }
            anim->unk_3A = camera->player->actor.world.rot.y;
            anim->unk_3E = 0;
            camera->eye = camera->eyeNext = anim->unk_1C;
            Camera_ClearFlags(camera, 4);
            camera->animState++;
        case 1:
            sp84.r = OLib_Vec3fDist(&sp8C, &camera->eye);
            sp84.yaw = anim->unk_34.y;
            sp84.pitch = -anim->unk_34.x;
            OLib_VecSphGeoToVec3f(&anim->unk_28, &sp84);
            func_80179A44(&anim->unk_1C, sp40, &anim->unk_0C);
            camera->at = anim->unk_0C; 

            if (sp98->stateFlags1 & 0x20000000) {
                anim->unk_00 = sp40->pos;
            }

            if (uniq0->unk_08 & 0x10) {
                sp54.x = sp40->pos.x;
                sp54.y = sp40->pos.y + spB4 + uniq0->unk_00;
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
                } else if ((!(sp98->stateFlags1 & 0x20000000)) &&
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
                if ((sp98->stateFlags1 & 0x20000000) == 0) { // TODO: Merge into 1 if-statement
                    if ((anim->unk_3A != camera->player->actor.world.rot.y) || 
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
            sp8C.y -= spB4 * 0.2f;
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
        func_800CB6C8(camera, &sp40->pos);
        camera->atLERPStepScale = 0.0f;
        Camera_ChangeSettingFlags(camera, camera->prevSetting, 2);
        Camera_SetFlags(camera, 4);
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
        camera->dist = OLib_Vec3fDist(&playerPosDisp, &camera->eye);
        func_800CB6C8(camera, &playerPosRot->pos);
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
    Vec3f* temp_s1 = &camera->eye;
    Vec3f* sp3C = &camera->at;
    Vec3f* sp38 = &camera->eyeNext;
    Vec3f* sp38_2 = &camera->targetPosRot.pos;
    f32 temp_f0;
    Actor* sp98[1];
    s16 sp96;
    s16 sp94;
    s32 phi_v0;
    VecSph sp88;
    PosRot sp74;
    PosRot sp60;
    Demo1* demo1 = (Demo1*)camera->paramData;
    Demo1Anim* anim = &demo1->anim;
    s32 pad;
    
    if (camera->animState == 0) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo1->interfaceFlags = NEXTSETTING;
    }

    if (camera->animState == 0) {
        anim->unk_1C = 0;
        OLib_Vec3fDiffToVecSphGeo(&anim->unk_0C, &camera->targetPosRot.pos, temp_s1);
        OLib_Vec3fDiffToVecSphGeo(&anim->unk_14, &camera->at, temp_s1);
        func_800B81E0(&sp60.pos, camera->target);
        func_800B8214(&sp74, camera->target);
        camera->targetPosRot.pos.x = (sp74.pos.x + sp60.pos.x) * 0.5f;
        camera->targetPosRot.pos.y = (sp74.pos.y + sp60.pos.y) * 0.5f;
        camera->targetPosRot.pos.z = (sp74.pos.z + sp60.pos.z) * 0.5f;
        camera->targetPosRot.rot = sp60.rot;
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
            Camera_LERPCeilVec3f(&camera->targetPosRot.pos, sp3C, 0.1f, 0.1f, 0.1f);
            OLib_Vec3fDiffToVecSphGeo(&sp88, sp3C, temp_s1);
            sp88.r = anim->unk_0C.r;
            OLib_VecSphAddToVec3f(sp38, sp3C, &sp88);
            *temp_s1 = *sp38;
            func_800CC128(camera, sp3C, temp_s1);
            break;
        case 2:
            Camera_LERPCeilVec3f(&camera->targetPosRot.pos, &camera->at, 0.1f, 0.1f, 0.1f);
            break;
        case 3:
            sp38 = sp38_2;
            if (anim->unk_1C == 0) {
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, sp38_2, &anim->unk_14, sp98, 1);
            }
            Camera_LERPCeilVec3f(sp38, sp3C, 0.1f, 0.1f, 0.1f);
            sp38 = &camera->eyeNext;
            Camera_LERPCeilVec3f(&anim->unk_00, sp38, 0.1f, 0.1f, 0.1f);
            *temp_s1 = *sp38;
            func_800CC128(camera, sp3C, temp_s1);
            break;
        case 4:
            if (anim->unk_1C == 0) {
                sp98[0] = camera->target;
                anim->unk_14.r = anim->unk_0C.r;
                func_800CC260(camera, &anim->unk_00, sp38_2, &anim->unk_14, sp98, 1);
            }
            Camera_LERPCeilVec3f(sp38_2, sp3C, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&anim->unk_00, sp38, 0.1f, 0.1f, 0.1f);
            *temp_s1 = *sp38;
            func_800CC128(camera, sp3C, temp_s1);
            break;
        case 5:
            sp38 = sp38_2;
            if (anim->unk_1C == 0) {
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, sp38_2, &anim->unk_0C, sp98, 1);
            }
            *sp3C = *sp38;
            sp44 = anim->unk_00;
            camera->eyeNext = sp44;
            *temp_s1 = sp44;
            break;
        case 6:
            if (anim->unk_1C == 0) {
                anim->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                anim->unk_0C.r = anim->unk_14.r;
                func_800CC260(camera, &anim->unk_00, sp38_2, &anim->unk_0C, sp98, 1);
            }
            Camera_LERPCeilVec3f(sp38_2, sp3C, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&anim->unk_00, sp38, 0.1f, 0.1f, 0.1f);
            *temp_s1 = *sp38;
            func_800CC128(camera, sp3C, temp_s1);
            break;
        case 7:
            if (anim->unk_1C == 0) {
                anim->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, sp38_2, &anim->unk_0C, sp98, 1);
            }
            *sp3C = *sp38_2;
            sp44 = anim->unk_00;
            camera->eyeNext = sp44;
            *temp_s1 = sp44;
            break;
        case 8:
            if (anim->unk_1C == 0) {
                anim->unk_0C.yaw = camera->target->shape.rot.y;
                sp98[0] = camera->target;
                func_800CC260(camera, &anim->unk_00, sp38_2, &anim->unk_0C, sp98, 1);
            }
            Camera_LERPCeilVec3f(sp38_2, sp3C, 0.1f, 0.1f, 0.1f);
            Camera_LERPCeilVec3f(&anim->unk_00, sp38, 0.1f, 0.1f, 0.1f);
            *temp_s1 = *sp38;
            func_800CC128(camera, sp3C, temp_s1);
            break;
    }

    anim->unk_1C++;
    return true;
}

s32 Camera_Demo2(Camera* camera) {
    Vec3f* sp34 = &camera->eye;
    Vec3f* sp30 = &camera->at;
    Vec3f* pad1 = &camera->eyeNext;
    PosRot* sp28 = &camera->playerPosRot;
    VecSph sp98;
    VecSph sp90;
    VecSph sp88;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;
    f32 sp60;
    s32 pad2;
    u8 sp5B;
    f32 sp54;
    s16 sp52;
    VecSph* sp4C;
    Vec3f* sp48;
    Player* player;
    Demo2* demo2 = (Demo2*)camera->paramData;
    Demo2Anim* anim = &demo2->anim;

    sp5B = 0;
    sp54 = func_800B6FC8(camera->player);
    player = camera->player;

    sp4C = D_801B9E64;
    sp48 = D_801B9E84;
    if (((&player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) && (player->transformation == PLAYER_FORM_GORON))) {
        sp4C = D_801B9EB4;
        sp48 = D_801B9ED4;
    }

    Camera_ClearFlags(camera, 0x10);
    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo2->unk_00 = NEXTSETTING;
        demo2->unk_04 = NEXTSETTING;
        demo2->unk_08 = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp98, sp30, sp34);

    sCameraInterfaceFlags = demo2->unk_08;

    switch (camera->animState) {
        case 0:
            Camera_ClearFlags(camera, 0xC);
            func_800CB5DC(camera);
            camera->fov = demo2->unk_00;
            anim->unk_10 = 0;
            camera->roll = anim->unk_10;
            anim->unk_00 = sp28->pos;
            if (camera->playerGroundY != BGCHECK_Y_MIN) {
                anim->unk_00.y = camera->playerGroundY;
            }

            sp52 = sp28->rot.y;
            sp70.x = (Math_SinS(sp52) * 40.0f) + anim->unk_00.x;
            sp70.y = anim->unk_00.y + 40.0f;
            sp70.z = (Math_CosS(sp52) * 40.0f) + anim->unk_00.z;
            if ((camera->globalCtx->state.frames & 2) != 0) {
                sp52 -= 0x4000;
                anim->unk_12 = 1;
            } else {
                sp52 += 0x4000;
                anim->unk_12 = -1;
            }

            sp7C.x = (sp4C[1].r * Math_SinS(sp52)) + sp70.x;
            sp7C.y = anim->unk_00.y + 5.0f;
            sp7C.z = (sp4C[1].r * Math_CosS(sp52)) + sp70.z;
            if (func_800CC128(camera, &sp70, &sp7C) != 0) {
                anim->unk_12 = -anim->unk_12;
            }

            OLib_Vec3fToVecSphGeo(&sp88, sp48);
            sp88.yaw += sp28->rot.y;
            OLib_VecSphAddToVec3f(sp30, &anim->unk_00, &sp88);
            sp90.r = sp4C[0].r;
            sp90.pitch = sp4C[0].pitch;
            sp90.yaw = (sp4C[0].yaw * anim->unk_12) + sp28->rot.y;
            anim->unk_0C = 1.0f;
            break;
        case 1:
            sp60 = (anim->unk_10 - 2) * 0.006849315f;
            sp64.x = sp48[0].x + ((sp48[1].x - sp48[0].x) * sp60);
            sp64.y = sp48[0].y + ((sp48[1].y - sp48[0].y) * sp60);
            sp64.z = sp48[0].z + ((sp48[1].z - sp48[0].z) * sp60);
            OLib_Vec3fToVecSphGeo(&sp88, &sp64);
            sp88.yaw = (sp88.yaw * anim->unk_12) + sp28->rot.y;
            OLib_VecSphAddToVec3f(sp30, &anim->unk_00, &sp88);
            sp88.r = sp4C[0].r + ((sp4C[1].r - sp4C[0].r) * sp60);
            sp88.pitch = sp4C[0].pitch + (s16)((s16)(sp4C[1].pitch - sp4C[0].pitch) * sp60);
            sp88.yaw = sp4C[0].yaw + (s16)((s16)(sp4C[1].yaw - sp4C[0].yaw) * sp60);
            sp90.r = sp88.r;
            sp90.pitch = sp88.pitch;
            sp90.yaw = (sp88.yaw * anim->unk_12) + sp28->rot.y;
            anim->unk_0C -= 0.002739726f;
            break;
        case 2:
            sp60 = (anim->unk_10 - 0x94) * 0.1f;
            sp64.x = sp48[1].x + ((sp48[2].x - sp48[1].x) * sp60);
            sp64.y = (sp48[1].y - sp54) + ((sp48[2].y - (sp48[1].y - sp54)) * sp60);
            sp64.y += sp54;
            sp64.z = sp48[1].z + ((sp48[2].z - sp48[1].z) * sp60);
            OLib_Vec3fToVecSphGeo(&sp88, &sp64);
            sp88.yaw = (sp88.yaw * anim->unk_12) + sp28->rot.y;
            OLib_VecSphAddToVec3f(sp30, &anim->unk_00, &sp88);
            sp88.r = sp4C[1].r + ((sp4C[2].r - sp4C[1].r) * sp60);
            sp88.pitch = sp4C[1].pitch + (s16)((s16)(sp4C[2].pitch - sp4C[1].pitch) * sp60);
            sp88.yaw = sp4C[1].yaw + (s16)((s16)(sp4C[2].yaw - sp4C[1].yaw) * sp60);
            sp90.r = sp88.r;
            sp90.pitch = sp88.pitch;
            sp90.yaw = (sp88.yaw * anim->unk_12) + sp28->rot.y;
            anim->unk_0C = anim->unk_0C - 0.04f;
            break;
        case 3:
            sp60 = (anim->unk_10 - 0x9F) * 0.11111111f;
            sp64.x = sp48[2].x + ((sp48[3].x - sp48[2].x) * sp60);
            sp64.y = sp48[2].y + ((sp48[3].y - sp48[2].y) * sp60);
            sp64.y += sp54;
            sp64.z = sp48[2].z + ((sp48[3].z - sp48[2].z) * sp60);
            OLib_Vec3fToVecSphGeo(&sp88, &sp64);
            sp88.yaw = (sp88.yaw * anim->unk_12) + sp28->rot.y;
            OLib_VecSphAddToVec3f(sp30, &anim->unk_00, &sp88);
            sp88.r = sp4C[2].r + ((sp4C[3].r - sp4C[2].r) * sp60);
            sp88.pitch = sp4C[2].pitch + (s16)((s16)(sp4C[3].pitch - sp4C[2].pitch) * sp60);
            sp88.yaw = sp4C[2].yaw + (s16)((s16)(sp4C[3].yaw - sp4C[2].yaw) * sp60);
            sp90.r = sp88.r;
            sp90.pitch = sp88.pitch;
            sp90.yaw = (sp88.yaw * anim->unk_12) + sp28->rot.y;
            anim->unk_0C = anim->unk_0C + 0.08888889f;
            break;
        case 30:
            Camera_SetFlags(camera, 0x400);
            if (camera->flags2 & 8) {
                camera->animState = 4;
            }
        case 10:
        case 20:
            sp5B = 1;
            break;
        case 4:
            sp90.r = 80.0f;
            sp90.pitch = 0;
            sp90.yaw = sp98.yaw;
            anim->unk_0C = 0.1f;
            sCameraInterfaceFlags = 0x3400;

            if ( !((
                (anim->unk_10 < 0) ||
                (camera->xzSpeed > 0.001f) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_A) ||
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_B) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CUP) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CDOWN) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CLEFT) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_CRIGHT) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_Z) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_L) || 
                CHECK_BTN_ALL(CONTROLLER1(camera->globalCtx)->press.button, BTN_R)
            ) && (camera->flags2 & 8) 
            )) {
                goto block_35;
            }
        default:
            Camera_SetFlags(camera, 0x14);
            Camera_ClearFlags(camera, 8);
            func_800CC938(camera);
            sCameraInterfaceFlags = 0;
            block_35:
            sp5B = 1;
            break;
    }

    anim->unk_10++;
    if (anim->unk_10 == 1) {
        camera->animState = 0xA;
    } else if (anim->unk_10 == 2) {
        camera->animState = 1;
    } else if (anim->unk_10 == 0x94) {
        camera->animState = 2;
    } else if (anim->unk_10 == 0x9E) {
        camera->animState = 0x14;
    } else if (anim->unk_10 == 0x9F) {
        camera->animState = 3;
    } else if (anim->unk_10 == 0xA8) {
        camera->animState = 0x1E;
    } else if (anim->unk_10 == 0xE4) {
        camera->animState = 4;
    }

    if (sp5B == 0) {
        sp90.r = Camera_LERPCeilF(sp90.r, sp98.r, anim->unk_0C, 1.0f);
        sp90.pitch = Camera_LERPCeilS(sp90.pitch, sp98.pitch, anim->unk_0C, 5);
        sp90.yaw = Camera_LERPCeilS(sp90.yaw, sp98.yaw, anim->unk_0C, 5);
        OLib_VecSphAddToVec3f(pad1, sp30, &sp90);
        *sp34 = *pad1;
    }

    camera->dist = OLib_Vec3fDist(sp30, sp34);
    camera->atLERPStepScale = 0.1f;
    func_800CB6C8(camera, &sp28->pos);
    return 1;
}

s32 Camera_Demo3(Camera *camera) {
    s32 pad2;
    s32 pad3;
    s32 pad4;
    VecSph sp64;
    CameraModeValue* values;
    Demo3* demo3 = (Demo3*)camera->paramData;
    Vec3f playerPos; // sp50-54-58
    Vec3f* eye = &camera->eye; // sp34;
    Vec3f* at = &camera->at; // sp30
    Vec3f* eyeNext = &camera->eyeNext; // sp24
    Demo3Anim* anim = &demo3->anim;
    f32 temp;


    OLib_Vec3fDiffToVecSphGeo(&sp64, at, eye);
    func_800B81E0(&playerPos, &camera->player->actor);
    playerPos.x = camera->playerPosRot.pos.x;
    playerPos.z = camera->playerPosRot.pos.z;
    playerPos.y -= (playerPos.y - camera->playerPosRot.pos.y) * 0.4f;
    Camera_LERPCeilVec3f(&playerPos, at, 0.1f, 0.1f, 0.1f);

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

    OLib_VecSphAddToVec3f(eyeNext, at, &sp64);
    *eye = *eyeNext;
    return true;
}

s32 Camera_Demo4(Camera *camera) {
    Vec3f *sp38 = &camera->eye;
    Vec3f *sp34 = &camera->at;
    PosRot *sp30 = &camera->playerPosRot;
    VecSph sp74;
    CameraModeValue* values;
    Demo4* demo4 = (Demo4*)camera->paramData;
    Demo4Anim* anim = &demo4->anim;
    Vec3f sp5C;
    f32 sp58;
    f32 new_var;
    f32 new_var2;  
    s32 pad[3];

    OLib_Vec3fDiffToVecSphGeo(&sp74, sp34, sp38);

    if (RELOAD_PARAMS) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo4->interfaceFlags = NEXTSETTING;                
        camera->animState = 0;
        anim->unk_00 = *sp34;
        anim->unk_18 = sp74;
        anim->unk_14 = camera->fov;
    }

    func_800B81E0(&sp5C, &camera->player->actor);
    sCameraInterfaceFlags = demo4->interfaceFlags;

    switch (camera->animState) {
        if (1) {}
        case 0:
            camera->animState++;
            anim->unk_22 = 0;
            if (!(sp74.r < 40.0f)) {
                sp74.r = 40.0f;
            }
            camera->fov = 80.0f;
            anim->unk_10 = (Rand_ZeroOne() - 0.5f) * 40.0f;
        case 1:
            if (anim->unk_22 >= 12) {
                anim->unk_0C = (anim->unk_22 - 12) * 10.384615f;
                new_var = sin_rad(anim->unk_0C * 0.017453292f);
                anim->unk_0C = ((anim->unk_10 < 0.0f) ? -1.0f : 1.0f) * new_var;
                if (anim->unk_22 == 12) {
                    Quake2_SetType(0x200);
                    Quake2_SetCountdown(26);
                }
            } else {
                anim->unk_0C = 0.0f;
            }
            sp58 = anim->unk_22 * 0.31578946f;
            anim->unk_20 = sp30->rot.y + 0x4000;
            sp5C.x = (Math_SinS(anim->unk_20) * sp58 * anim->unk_0C) + sp30->pos.x;
            sp5C.z = (Math_CosS(anim->unk_20) * sp58 * anim->unk_0C) + sp30->pos.z;
            sp5C.y -= (sp5C.y - sp30->pos.y) * 0.099999994f;
            Camera_LERPCeilVec3f(&sp5C, sp34, 0.2f, 0.2f, 0.1f);
            sp58 = (anim->unk_22 * 1.5789474f);
            camera->roll = DEGF_TO_BINANG(sp58 * anim->unk_0C);
            sp58 = 1.0f / (38 - anim->unk_22);
            anim->unk_22++;
            sp74.r = Camera_LERPCeilF(30.0f, sp74.r, sp58, 0.1f);
            sp74.pitch = 0;
            if (anim->unk_22 >= 38) {
                anim->unk_22 = 24;
                camera->animState++;
                anim->unk_0C = (32.0f - camera->fov) / 24.0f;
                Quake2_SetType(0x800);
            }
            break;
        case 2:
            if (anim->unk_22 == 0x18) {
                sp34->x = (Math_SinS(sp30->rot.y) * -7.0f) + sp30->pos.x;
                sp34->y = sp5C.y - ((sp5C.y - sp30->pos.y) * 0.1f);
                sp34->z = (Math_CosS(sp30->rot.y) * -7.0f) + sp30->pos.z;
            } else {
                sp5C.x = (Math_SinS(sp30->rot.y) * -7.0f) + sp30->pos.x;
                sp5C.y -= (sp5C.y - camera->playerPosRot.pos.y) * 0.1f;
                sp5C.z = (Math_CosS(sp30->rot.y) * -7.0f) + sp30->pos.z;
                Camera_LERPCeilVec3f(&sp5C, sp34, 0.25f, 0.25f, 0.1f);
            }
            if (anim->unk_22 > 0) {
                camera->fov += anim->unk_0C;
            }
            anim->unk_22--;
            sp74.r = 35.0f;
            sp74.pitch = 0x2000;
            camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
            if (anim->unk_22 <= 0) {
                anim->unk_20 = 0x276;
                anim->unk_22 = 0;
                anim->unk_0C = (60.0f - camera->fov) / anim->unk_20;
                camera->animState = 3;
            }
            break;
        case 3:
            sp5C.x = sp30->pos.x;
            sp5C.y -= (sp5C.y - camera->playerPosRot.pos.y) * 0.1f;
            sp5C.z = sp30->pos.z;
            Camera_LERPCeilVec3f(&sp5C, sp34, 0.25f, 0.25f, 0.1f);
            camera->roll = Camera_LERPCeilS(0, camera->roll, 0.1f, 5);
            anim->unk_22++;
            camera->fov += anim->unk_0C * anim->unk_22;
            sp74.pitch = 0x2000;
            sp74.r = 35.0f;
            if (anim->unk_22 >= 0x23) {
                Quake2_ClearType(0x200);
                Quake2_ClearType(0x800);
                camera->animState = 4;
            }
            break;
        case 999:
            func_800B81E0(&sp5C, &camera->player->actor);
            Quake2_ClearType(0x200);
            Quake2_ClearType(0x800);
            camera->animState = 4;
            break;
        case 4:
            sp5C.y -= (sp5C.y - camera->playerPosRot.pos.y) * 0.1f;
            Camera_LERPCeilVec3f(&sp5C, sp34, 0.1f, 0.1f, 0.1f);
            sp74 = anim->unk_18;
            camera->fov = anim->unk_14;
            camera->roll = 0;
            break;

    }

    OLib_VecSphAddToVec3f(&camera->eyeNext, sp34, &sp74);
    *sp38 = camera->eyeNext;
    return 1;
}

s32 Camera_Demo5(Camera* camera) {
    Vec3f* sp38 = &camera->eye;
    Vec3f* sp34 = &camera->at;
    Vec3f* pad2 = &camera->eyeNext;
    VecSph sp74;
    PosRot* sp30 = &camera->playerPosRot;
    f32 new_var3;
    f32 phi_f0;
    Vec3f sp5C;
    f32 new_var;
    f32 sp58;
    Demo5* demo5 = (Demo5*)camera->paramData;
    Demo5Anim* anim = &demo5->anim;
    CameraModeValue* values;
    f32 pad;

    OLib_Vec3fDiffToVecSphGeo(&sp74, sp34, sp38);

    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        demo5->interfaceFlags = NEXTSETTING;                
        camera->animState = 0;
        anim->unk_00 = *sp34;
        anim->unk_1C = sp74;
        anim->unk_18 = camera->fov;
    }

    func_800B81E0(&sp5C, &camera->player->actor);
    
    sCameraInterfaceFlags = demo5->interfaceFlags;

    switch (camera->animState) {
        case 0:
            camera->animState++;
            sp74.pitch = 0;
            anim->unk_26 = 0x12;
            anim->unk_14 = 80.0f;
            sp74.r = 30.0f;
            camera->fov = 80.0f;
            anim->unk_10 = (Rand_ZeroOne() - 0.5f) * 40.0f;
            camera->roll = 0;
            sp5C.x = sp30->pos.x;
            sp5C.z = sp30->pos.z;
            *sp34 = sp5C;
        case 1:
            anim->unk_26--;
            if (anim->unk_26 <= 0) {
                anim->unk_26 = 0;
                camera->animState = 2;
                anim->unk_24 = camera->playerPosRot.rot.y + 0x4000;
                anim->unk_26 = 0x2E;
                Quake2_SetType(0x200);
                Quake2_SetCountdown(0x2E);
            }
            break;
        case 2:
            anim->unk_0C = anim->unk_26 * 7.826087f;
            sp58 = anim->unk_0C * 0.017453292f;
            new_var3 = sin_rad(sp58);
            anim->unk_0C = ((anim->unk_10 < 0.0f) ? -1.0f : 1.0f) * new_var3;
            new_var = (0x2E - anim->unk_26) * 0.10869565f;
            sp5C.x = (Math_SinS(anim->unk_24) * new_var * anim->unk_0C) + sp30->pos.x;
            sp5C.z = (Math_CosS(anim->unk_24) * new_var * anim->unk_0C) + sp30->pos.z;
            sp5C.y -= (sp5C.y - camera->playerPosRot.pos.y) * 0.2f;
            Camera_LERPCeilVec3f(&sp5C, sp34, 0.1f, 0.1f, 0.1f);
            new_var = (anim->unk_26 * 0.4347826f);
            camera->roll = (s16) (( anim->unk_0C * new_var * 182.04167f) + .5f);
            new_var = 1.0f / anim->unk_26;
            sp74.r = Camera_LERPCeilF(anim->unk_14, sp74.r, new_var, 0.1f);
            anim->unk_26--;
            sp74.pitch = 0;
            if (anim->unk_26 <= 0) {
                camera->animState = 3;
                Quake2_ClearType(0x200);
            }
            break;
        case 999:
            func_800B81E0(&sp5C, &camera->player->actor);
            camera->animState = 3;
            Quake2_ClearType(0x200);
            break;
        case 3:
            sp5C.y -= (sp5C.y - camera->playerPosRot.pos.y) * 0.1f;
            Camera_LERPCeilVec3f(&sp5C, sp34, 0.1f, 0.1f, 0.1f);
            camera->roll = 0;
            sp74 = anim->unk_1C;
            camera->fov = anim->unk_18;
            break;
    }

    OLib_VecSphAddToVec3f(pad2, sp34, &sp74);
    *sp38 = *pad2;
    return 1;
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
            if (anim->unk_04.pitch < 0x7D0) {
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

s32 Camera_Special5(Camera *camera) {
    Special5* spec5 = (Special5*)camera->paramData;
    f32 temp_f0_2;
    s32 phi_v0;
    PosRot spA8;
    s16 pad6;
    s16 spA4;
    s32 pad0[4];
    Vec3f sp88;
    Vec3f sp7C;
    VecSph sp74;
    VecSph sp6C;
    VecSph sp64;
    VecSph sp5C;
    s32 pad1;
    f32 temp_f0;
    Vec3f *sp38 = &camera->eye;
    Vec3f *sp34 = &camera->at;
    Vec3f *sp30 = &camera->eyeNext;
    PosRot *sp2C = &camera->playerPosRot;
    Special5Anim* anim = &spec5->anim;

    temp_f0 = func_800CB700(camera);
    if ((camera->animState == 0) || (camera->animState == 0xA) || (camera->animState == 0x14)) {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;


        spec5->unk_00 = NEXTSETTING * 0.01f * temp_f0 * (0.8f - ((68.0f / temp_f0) * -0.2f));
        spec5->unk_04 = NEXTSETTING;
        spec5->unk_08 = NEXTSETTING;
        spec5->unk_16 = (NEXTSETTING * 182.04167f) + 0.5f;
        spec5->unk_0C = NEXTSETTING;
        spec5->unk_10 = NEXTSETTING * 0.01f;
        spec5->unk_14 = NEXTSETTING;
        spec5->unk_18 = NEXTSETTING;
    }

    OLib_Vec3fDiffToVecSphGeo(&sp64, sp34, sp38);
    OLib_Vec3fDiffToVecSphGeo(&sp5C, sp34, sp30);
    func_800B8214(&spA8, camera->target); // May be Vec3f arg0
    sCameraInterfaceFlags = spec5->unk_18;

    if ( camera->animState == 0) {
        camera->animState++;
        anim->unk_00 = spec5->unk_14;
    }

    if (anim->unk_00 > 0) {
        anim->unk_00--;
    } else if (anim->unk_00 == 0) {
        if ((camera->target == 0) || (camera->target->update == 0)) {
            camera->target = NULL;
            return 1;
        } else {
            anim->unk_00--;
            if (spec5->unk_08 < OLib_Vec3fDist(&spA8.pos, &sp2C->pos)) {
                sp6C.yaw = sp2C->rot.y;
                sp6C.pitch = -sp2C->rot.x;
                sp6C.r = 20.0f;
                OLib_VecSphAddToVec3f(&sp7C, &spA8.pos, &sp6C);
                func_800CBC84(camera, sp34, &sp7C, 0);
                OLib_Vec3fToVecSphGeo(&sp6C, &sp88);
                spA4 = sp2C->rot.y - sp6C.yaw;
                sp74.r = spec5->unk_04;
                temp_f0_2 = Rand_ZeroOne();

                // clang-format off
                if (spA4 < 0) {
                    phi_v0 = (s16)((s16)(temp_f0_2 * 2730.0f) + 0x1553);
                    phi_v0 = -phi_v0;
                } else {
                    phi_v0 = (s16)((s16)(temp_f0_2 * 2730.0f) + 0x1553); \
                } \
                \
                sp74.yaw = (s16)phi_v0 + (s16)(sp2C->rot.y + 0x8000);
                // clang-format on  

                sp74.pitch = spec5->unk_16;     
                
                OLib_VecSphAddToVec3f(sp30, &spA8.pos, &sp74);
                *sp38 = *sp30;
                func_800CC128(camera, &spA8.pos, sp38);
            }
        }
    } 

    Camera_CalcAtDefault(camera, &sp5C, spec5->unk_00, 0);
    camera->fov = Camera_LERPCeilF(spec5->unk_0C, camera->fov, camera->atLERPStepScale * 0.05f, 0.1f);
    camera->roll = Camera_LERPCeilS(0, camera->roll, 0.5f, 5);
    camera->atLERPStepScale = Camera_ClampLERPScale(camera, spec5->unk_10);
    return 1;
}

s32 Camera_Special6(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special7(Camera* camera) {
    return Camera_Noop(camera);
}

s32 Camera_Special8(Camera *camera) {
    Vec3f *sp38 = &camera->at;
    Vec3f *sp34 = &camera->eyeNext;
    PosRot *sp30 = &camera->playerPosRot;
    Vec3f sp68;
    Vec3f sp5C;
    f32 temp_f0;
    f32 sp54;
    Special8* spec8 = (Special8*)camera->paramData;
    Special8Params* params = &spec8->params; // sp2C
    Special8Anim* anim = &params->anim; // sp2C
    s32 pad1;
    s32 pad2;

    sp54 = func_800CB700(camera);

    Camera_ClearFlags(camera, 0x10);
    temp_f0 = (0.8f - ((68.0f / sp54) * -0.2f));

    if ((camera->animState != 0) && (camera->animState != 0xA) && (camera->animState != 0x14)) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        params->unk_00 = NEXTSETTING * 0.01f * sp54 * temp_f0;
        params->unk_04 = NEXTSETTING * 0.01f;
        params->unk_08 = NEXTSETTING * 0.01f;
        params->unk_0C = NEXTSETTING;
        params->unk_10 = NEXTSETTING * 5;
        params->unk_12 = NEXTSETTING;
        anim->unk_0E = params->unk_0C * 100.0f;
        anim->unk_0C = 0;   
        Camera_ClearFlags(camera, 6);
        anim->unk_00.x = spec8->doorParams.timer1;
        anim->unk_00.y = spec8->doorParams.timer2;
        anim->unk_00.z = spec8->doorParams.timer3;
    }
    if (anim->unk_0C < params->unk_10) {
        anim->unk_0C++;
        sCameraInterfaceFlags = params->unk_12;
        sp5C.x = 0.0f;
        sp5C.y = params->unk_00 + sp54;
        sp5C.z = 0.0f;
        Camera_LERPCeilVec3f(&sp5C, &camera->posOffset, params->unk_08, params->unk_08, 0.1f);
        sp68.x = sp30->pos.x + camera->posOffset.x;
        sp68.y = sp30->pos.y + camera->posOffset.y;
        sp68.z = sp30->pos.z + camera->posOffset.z;
        if (camera->animState == 0) {
            camera->animState++;
            if ((params->unk_12 & 1) == 0) {
                camera->eyeNext = anim->unk_00;
                camera->at = sp68;
            }
        }

        Camera_LERPCeilVec3f(&sp68, sp38, params->unk_08, params->unk_08, 10.0f);
        Camera_LERPCeilVec3f(&anim->unk_00, sp34, params->unk_04, params->unk_04, 0.1f);
        camera->eye = *sp34;
        camera->dist = OLib_Vec3fDist(sp38, &camera->eye);
        camera->roll = 0;
        camera->xzSpeed = 0.0f;
        camera->fov = anim->unk_0E * 0.01f;
        camera->atLERPStepScale = Camera_ClampLERPScale(camera, 1.0f);
        func_800CB6C8(camera, &sp30->pos);
    } else {
        Camera_SetFlags(camera, 0x410);
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
            (params->unk_12 & 8)) {
                func_800CC938(camera);
                Camera_SetFlags(camera, 6);
                Camera_ClearFlags(camera, 0x400);
        }
    }
    return 1;
}

s32 Camera_Special9(Camera *camera) {
    Vec3f *sp4C = &camera->eye;
    Vec3f *sp48 = &camera->at;
    s32 rand1;
    Vec3f spB8;
    VecSph spB0;
    VecSph spA8;
    f32 spA4;
    s32 phi_v1_2;
    s16 temp_v0;
    f32 sp34;
    PosRot sp84;
    Vec3f *sp44 = &camera->eyeNext;
    PosRot *sp40 = &camera->playerPosRot;
    Special9* spec9 = (Special9*)camera->paramData;
    Special9Params* params = &spec9->params; // sp3C
    Special9Anim* anim = &params->anim; // sp38
    s32 sp50[1];
    Vec3s *temp_v0_5;
    
    spA4 = func_800CB700(camera);
    temp_v0 = ActorCutscene_GetCurrentIndex();

    if ((temp_v0 != -1) && (temp_v0 != 0x7D)) {
        func_800E0348(camera);
    }

    Camera_ClearFlags(camera, 0x10);
    sp34 = 0.8f - ((68.0f / spA4) * -0.2f);

    if (!RELOAD_PARAMS) {
    } else {
        CameraModeValue* values = sCameraSettings[camera->setting].cameraModes[camera->mode].values;
        params->unk_00 = NEXTSETTING * 0.01f * spA4 * sp34;
        params->unk_04 = NEXTSETTING;
        params->unk_08 = NEXTSETTING;
    }


    if (spec9->doorParams.doorActor != NULL) {
        func_800B8248(&sp84, spec9->doorParams.doorActor); // TODO: Change to Actor*
    } else {
        sp84 = *sp40;
        sp84.pos.y += spA4 + params->unk_00;
        sp84.rot.x = 0;
    }

    OLib_Vec3fDiffToVecSphGeo(&spA8, sp48, sp4C);

    sCameraInterfaceFlags = params->unk_08;

    switch (camera->animState) {
        case 0:
            Camera_ClearFlags(camera, (0x4 | 0x2));
            camera->animState++;
            if (ABS((s16)(sp40->rot.y - sp84.rot.y)) > 0x4000) {
                anim->unk_00 = (s16)(sp84.rot.y + 0x8000);
            } else {
                anim->unk_00 = sp84.rot.y;
            }
        case 1:
            spec9->doorParams.timer1--;
            if (spec9->doorParams.timer1 <= 0) {
                camera->animState++;
                if (params->unk_08 & 1) {
                    temp_v0_5 = Camera_GetCamBGData(camera, camera->camDataIdx);
                    Camera_Vec3sToVec3f(sp44, &BGCAM_POS(temp_v0_5));
                    spB8 = *sp4C = *sp44;
                } else {
                    s16 sp30;
                    s16 randFloat;
                    spB0.pitch = (s16)((s16)(Rand_ZeroOne() * 640.0f) + 0xBB8);
                    randFloat = (s16)((s16)(Rand_ZeroOne() * 1230.0f) + (s16)0x5DC);
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
                Camera_ClearFlags(camera, 0x400);
            }
            break;
    }

    spB8 = sp40->pos;
    spB8.y += spA4;
    camera->dist = OLib_Vec3fDist(&spB8, sp4C);
    func_800CB6C8(camera, &sp40->pos);
    return true;
}

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
    Camera* camP;
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
    camera->setting = camera->prevSetting= CAM_SET_FREE0;
    camera->camDataIdx = camera->prevCamDataIdx = -1;
    camera->flags2 = 0;
    camera->mode = CAM_MODE_NORMAL;
    camera->bgCheckId = 0x32;
    camera->unk168 = 0xF;
    camera->unk160 = -1;
    camera->player = NULL;
    camera->target = NULL;
    Camera_SetFlags(camera, 0x4000);
    camera->skyboxOffset.z = camera->skyboxOffset.y = camera->skyboxOffset.x = 0;
    camera->up.z = camera->up.x = 0.0f;
    camera->atLERPStepScale = 1;
    camera->up.y = 1.0f;
    sCameraInterfaceFlags = 0xFF00;
    D_801B9E58 = 3;
}

void func_800DDFE0(Camera* camera) {
    if (camera != &camera->globalCtx->mainCamera) {
        camera->setting = CAM_SET_FREE0;
        camera->prevSetting = camera->setting;
        Camera_ClearFlags(camera, 4);
    } else {
        switch (camera->globalCtx->roomCtx.currRoom.unk3) {
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

void Camera_InitPlayerSettings(Camera* camera, Player* player) {
    PosRot playerPosShape;
    VecSph eyeNextAtOffset;
    s32 bgId;
    Vec3f floorPos;
    s32 upXZ;
    f32 playerYOffset;
    Vec3f* eye = &camera->eye;
    s32 pad;

    func_800B8248(&playerPosShape, &player->actor);
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
    camera->at = playerPosShape.pos;
    camera->at.y += playerYOffset;

    camera->posOffset.x = 0;
    camera->posOffset.y = playerYOffset;
    camera->posOffset.z = 0;

    OLib_VecSphAddToVec3f(&camera->eyeNext, &camera->at, &eyeNextAtOffset);
    *eye = camera->eyeNext;
    camera->roll = 0;

    upXZ = 0;
    camera->up.z = upXZ;
    camera->up.y = 1.0f;
    camera->up.x = upXZ;

    {
        Vec3f* at = &camera->at;
        if (func_800CC488(camera, &floorPos, at, &bgId) != BGCHECK_Y_MIN) {
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

    if (!(camera->flags2 & 2) || (sCameraSettings[camera->setting].unk_04 & 0x40000000)) {
        return false;
    }

    if (camera->flags2 & 0x200) {
        if (func_800CB8C8(camera) != 0) {
            if (func_800CB8F4(camera) == 0) {
                Camera_ChangeSettingFlags(camera, CAM_SET_CIRCLE5, 6);
            } else {
                Camera_ChangeSettingFlags(camera, CAM_SET_ZORA0, 6);
            }
            Camera_SetFlags(camera, -0x8000);
        } else if (camera->flags2 & (s16)0x8000) {
            Camera_ChangeSettingFlags(camera, *waterPrevCamSetting, 6); // unk11E
            Camera_ClearFlags(camera, -0x8000);
        }
    }

    if (!(camera->flags2 & (s16)0x8000)) {
        waterCamIdx = Camera_GetWaterBoxDataIdx(camera, &waterY);
        if (waterCamIdx == -2) {
            if (!(camera->flags2 & 0x200)) {
                Camera_SetFlags(camera, 0x200);
                camera->waterPrevCamIdx = camera->camDataIdx;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) ||
                ((func_800CB880(camera) != 0) && !func_800CBB58(camera))) {
                prevBgId = camera->bgCheckId;
                camera->bgCheckId = 0x32;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, CAM_SET_NORMAL3, 2);
                *waterPrevCamSetting = camera->setting;
                camera->bgCheckId = prevBgId;
                camera->camDataIdx = -2;
            }

        } else if (waterCamIdx != -1) {
            if ((camera->flags2 & 0x200) == 0) {
                Camera_SetFlags(camera, 0x200);
                camera->waterPrevCamIdx = camera->camDataIdx;
                camera->waterQuakeId = -1;
            }

            if (!(Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) ||
                ((func_800CB880(camera) != 0) && !func_800CBB58(camera))) {
                prevBgId = camera->bgCheckId;
                camera->bgCheckId = 0x32;
                waterPrevCamSetting = &camera->waterPrevCamSetting;
                Camera_ChangeSettingFlags(camera, waterCamIdx, 2);
                *waterPrevCamSetting = camera->setting;
                camera->bgCheckId = prevBgId;
            }

        } else if (camera->flags2 & 0x200) {
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

    if ((camera->thisIdx == MAIN_CAM) && (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) && (player->currentMask == PLAYER_MASK_GIANTS_MASK)) {
        Camera_ChangeSettingFlags(camera, CAM_SET_GIANT, 2);
        return true;
    } else {
        return false;
    }
}

Vec3s* Camera_Update(Vec3s* inputDir, Camera* camera) {
    Vec3f spC4;
    Vec3f spB8;
    Vec3f spAC;
    Vec3f spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    CollisionPoly* sp90;
    CollisionPoly* sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    DynaPolyActor* meshActor;
    PosRot sp68;
    QuakeCamCalc sp48;
    Player* sp44 = camera->player;
    VecSph sp3C;
    s16 sp3A; // playerGroundY
    f32 temp_f0; // playerGroundY

    if (camera->status == CAM_STAT_CUT) {
        *inputDir = camera->inputDir;
        return inputDir;

    }

    sUpdateCameraDirection = false;
    D_801B9E54 = 0;

    if (camera->globalCtx->view.unk164 == 0) {
        if (camera->player != NULL) {
            if (&camera->player->actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
                func_800B8248(&sp68, &camera->player->actor);
            } else {
                func_800B8214(&sp68, &camera->player->actor);
            }
            camera->playerPosDelta.x = sp68.pos.x - camera->playerPosRot.pos.x;
            camera->playerPosDelta.y = sp68.pos.y - camera->playerPosRot.pos.y;
            camera->playerPosDelta.z = sp68.pos.z - camera->playerPosRot.pos.z;

            sp98 = 0;
            if (func_800CB7F8(camera)) {
                if (sp44->rideActor->floorPoly != NULL) {
                    sp90 = sp44->rideActor->floorPoly;
                    camera->bgCheckId = sp44->rideActor->floorBgId;
                    camera->playerGroundY = sp44->rideActor->floorHeight;
                    sp98 = 3;
                }
            } else if (func_800CB7CC(camera)) {
                if (camera->player->actor.floorPoly != NULL) {
                    sp90 = camera->player->actor.floorPoly;
                    camera->bgCheckId = camera->player->actor.floorBgId;
                    camera->playerGroundY = camera->player->actor.floorHeight;
                    sp98 = 1;
                }
            } else {
                spA0 = sp68.pos;
                spA0.y += func_800CB700(camera);
                temp_f0 = func_800C41E4(camera->globalCtx, &camera->globalCtx->colCtx, &sp90, &sp9C, &camera->player->actor, &spA0);
                if (temp_f0 != BGCHECK_Y_MIN) {
                    camera->bgCheckId = sp9C;
                    camera->playerGroundY = temp_f0;
                    sp98 = 2;
                }
            }

            if ((sp98 != 0) && (Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f)) {
                meshActor = BgCheck_GetActorOfMesh(&camera->globalCtx->colCtx, camera->bgCheckId);
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
            camera->playerPosRot = sp68;

            if (camera->thisIdx == MAIN_CAM) {
                Camera_CheckWater(camera);
                Camera_SetRoomHotFlag(camera);
                func_800DE62C(camera);
                func_800DE890(camera);
            }

            if (camera->unk150 != 0) {
                Camera_SetFlags(camera, 0x400);
            } else if (!(camera->flags2 & 4)) {
                camera->nextCamDataIdx = -1;
            }

            sp94 = 0;
            sp9C = camera->bgCheckId;

            if ((camera->flags2 & 1) && (camera->flags2 & 4) && !(camera->flags2 & 0x400) && 
                (!(camera->flags2 & 0x200) || func_800CBB58(camera)) && !(camera->flags2 & (s16)0x8000) && 
                !func_800CB7F8(camera) && !func_800DE954(camera) && !func_800CB828(camera) && (sp98 != 0)) {

                sp3A = Camera_GetDataIdxForPoly(camera, &sp9C, sp90);
                if ((sp3A != -1) && (camera->bgCheckId == 0x32)) {
                    if (func_800CBC00(camera) == 0) {
                        camera->nextCamDataIdx = sp3A | 0x1000;
                    }
                }
                spA0 = sp68.pos;
                spA0.y += func_800CB700(camera);
                temp_f0 = func_800C4488(&camera->globalCtx->colCtx, &sp8C, &sp9C, &spA0);
                if ((temp_f0 != BGCHECK_Y_MIN) && (sp8C != sp90) && (sp9C == 0x32) && ((camera->playerGroundY - 2.0f) < temp_f0)) {
                    sp3A = Camera_GetDataIdxForPoly(camera, &sp9C, sp8C);
                    if ((sp3A != -1) && (sp9C == 0x32)) {
                        camera->nextCamDataIdx = sp3A | 0x1000;
                        sp94 = 1;
                    }
                }

            }
            if (camera->unk150 != 0) {
                camera->unk150--;
                if (camera->unk150 == 0) {
                    Camera_ClearFlags(camera, 0x400);
                    sp94 = 5;
                }
            }
            if (((camera->thisIdx == MAIN_CAM) || (camera->flags2 & 0x40)) &&
                ((camera->bgCheckId == 0x32) || ((sp9C == 0x32) && (sp94 != 0))) &&
                (camera->nextCamDataIdx != -1) && (camera->unk150 == 0) &&
                ((Camera_fabsf(camera->playerPosRot.pos.y - camera->playerGroundY) < 11.0f) || (sp94 != 0)) &&
                (!(camera->flags2 & 0x200) || func_800CBB58(camera))) {

                Camera_ChangeDataIdx(camera, camera->nextCamDataIdx);
                camera->nextCamDataIdx = -1;
                if (camera->timer != 0) {
                    camera->unk150 = camera->timer;
                    camera->timer = 0;
                }       
            }
        }

        if (camera->status == CAM_STAT_WAIT) {
            *inputDir = camera->inputDir;
            return inputDir;
        } 
        
        camera->flags1 = 0;
        Camera_ClearFlags(camera, 0x420);
        Camera_SetFlags(camera, 0x10);

    }
        
    sCameraFunctions[sCameraSettings[camera->setting].cameraModes[camera->mode].funcIdx](camera);
    if (D_801B9E58 != 0) {
        D_801B9E58--;
    }

    if (camera->status == CAM_STAT_ACTIVE) {
        if (((D_801B9E58 != 0) || func_800CB854(camera)) && (camera->thisIdx == MAIN_CAM)){
            sCameraInterfaceFlags = 0x3200;
            Camera_UpdateInterface(sCameraInterfaceFlags);
        } else if ((camera->globalCtx->unk_18B4A != 0) && (camera->thisIdx != MAIN_CAM)) {
            sCameraInterfaceFlags = 0xFF00;
            Camera_UpdateInterface(sCameraInterfaceFlags);
        } else {
            Camera_UpdateInterface(sCameraInterfaceFlags);
        }
    }

    if (camera->status == CAM_STAT_UNK3) {
        *inputDir = camera->inputDir;
        return inputDir;
    }

    sp9C = Quake_Calc(camera, &sp48);
    if (sp9C != 0) {
        spC4.x = camera->at.x + sp48.atOffset.x;
        spC4.y = camera->at.y + sp48.atOffset.y;
        spC4.z = camera->at.z + sp48.atOffset.z;
        spB8.x = camera->eye.x + sp48.eyeOffset.x;
        spB8.y = camera->eye.y + sp48.eyeOffset.y;
        spB8.z = camera->eye.z + sp48.eyeOffset.z;
        OLib_Vec3fDiffToVecSphGeo(&sp3C, &spB8, &spC4);
        Camera_CalcUpFromPitchYawRoll(&spAC, sp3C.pitch, sp3C.yaw, camera->roll + sp48.rollOffset);
        sp80 = camera->fov + (sp48.zoom * 0.00549325f);
    } else if (D_801B9E54 != 0) {
        spC4 = camera->at;
        spB8 = camera->eye;
        OLib_Vec3fDiffToVecSphGeo(&sp3C, &spB8, &spC4);
        spAC = camera->up;
        sp80 = camera->fov;
    } else {
        spC4 = camera->at;
        spB8 = camera->eye;
        OLib_Vec3fDiffToVecSphGeo(&sp3C, &spB8, &spC4);
        Camera_CalcUpFromPitchYawRoll(&spAC, sp3C.pitch, sp3C.yaw, camera->roll);
        sp80 = camera->fov;
    }

    if (camera->paramFlags & 4) {
        camera->paramFlags &= ~4;
        spAC = camera->up;
    } else {
        camera->up = spAC;
    }

    camera->skyboxOffset = sp48.eyeOffset;
    View_SetScale(&camera->globalCtx->view, (gGameInfo->data[259] * 0.01f) + 1.0f);
    camera->globalCtx->view.fovy = sp80;
    View_SetViewOrientation(&camera->globalCtx->view, &spB8, &spC4, &spAC);
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
    Camera_ClearFlags(camera, 0x1000 | 0x8);
    return true;
}

s32 Camera_ChangeModeFlags(Camera* camera, s16 mode, u8 flags) {
    static s32 modeChangeFlags = 0;

    if (camera->setting == CAM_SET_TELESCOPE) {
        if ((mode == CAM_MODE_FIRSTPERSON) || (mode == CAM_MODE_NUTSHIDE)) {
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

        if (camera->status == CAM_STAT_ACTIVE) {
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
    if ((camera->flags2 & 0x20) != 0) {
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
        camera->flags1 |= 0x40;
        return -1;
    }

    if (camDataIdx < 0) {
        setting = D_801B9CE4[camDataIdx];
    } else if (!(camera->flags1 & 0x40)) {
        setting = func_800CC740(camera, camDataIdx);
    } else {
        return -1;
    }

    camera->flags1 |= 0x40;
    if ((Camera_ChangeSettingFlags(camera, setting, 5) >= 0) || (sCameraSettings[camera->setting].unk_04 & 0x80000000)) {
        camera->camDataIdx = camDataIdx;
        camera->flags1 |= 4;
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

s32 func_800DFEF0(Camera* camera, s16 paramFlags) {
    camera->paramFlags &= ~paramFlags;
    return 1;
}

s32 func_800DFF18(Camera* camera, s16 flags) {
    camera->flags2 = flags;
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
    camera->flags2 |= flags;
    return camera->flags2;
}

s16 Camera_ClearFlags(Camera* camera, s16 flags) {
    camera->flags2 &= ~flags;
    return camera->flags2;
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
        camera->unk150 = timer1;
        camera->timer = timer2 + timer3;
    }

    Camera_ResetAnim(camera, camera->mode);
    return -1;
}

s32 Camera_Copy(Camera* dstCamera, Camera* srcCamera) {
    s32 pad;

    dstCamera->posOffset.z = 0.0f;
    dstCamera->posOffset.y = 0.0f;
    dstCamera->posOffset.x = 0.0f;
    dstCamera->atLERPStepScale = 0.1f;
    dstCamera->at = srcCamera->at;

    dstCamera->eye = dstCamera->eyeNext = srcCamera->eye;

    dstCamera->dist = OLib_Vec3fDist(&dstCamera->at, &dstCamera->eye);
    dstCamera->fov = srcCamera->fov;
    dstCamera->roll = srcCamera->roll;
    func_800CB5DC(dstCamera);

    if (dstCamera->player != NULL) {
        if (&dstCamera->player->actor == dstCamera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
            func_800B8248(&dstCamera->playerPosRot, &dstCamera->player->actor);
        } else {
            func_800B8214(&dstCamera->playerPosRot, &dstCamera->player->actor);
        }
        func_800CB6C8(dstCamera, &dstCamera->playerPosRot.pos);
    }
    return true;
}

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

void func_800E02AC(Camera* camera, Actor* actor) {
    camera->player = (Player*)actor;
    if (actor == camera->globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first) {
        func_800B8248(&camera->playerPosRot, actor);
    } else {
        
        func_800B8214(&camera->playerPosRot, &camera->player->actor);
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
    if ((camera->animState != 0) && (camera->animState != 10) && (camera->animState != 20)) {
        camera->animState = 999;
        Camera_SetFlags(camera, 0x400 | 0x10 | 0x4 | 0x2);
    } else {
        camera->animState = 666;
    }
}
