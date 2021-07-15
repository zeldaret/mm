#include "global.h"

// bss
QuakeRequest sQuakeRequest[4];
Quake2Context sQuake2Context;

// data
s16 D_801C0EC0 = 1;
s16 sQuakeRequestCount = 0;

s16 (*sQuakeCallbacks[])(QuakeRequest*, ShakeInfo*) = {
    NULL, Quake_Callback1, Quake_Callback2, Quake_Callback3, Quake_Callback4, Quake_Callback5, Quake_Callback6,
};

s16 D_801C0EE4 = 0x03F0;
s16 D_801C0EE8 = 0x0156;
s16 D_801C0EEC = 0x0001;

f32 Quake_Random(void) {
    return 2.0f * (Rand_ZeroOne() - 0.5f);
}

void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 verticalPertubation, f32 horizontalPertubation) {
    Vec3f* at = &req->camera->at;
    Vec3f* eye = &req->camera->eye;

    Vec3f atEyeOffset;
    VecSph atEyeOffsetSph2;
    VecSph eyeAtAngle;

    // isPerpendicularShake is always set to 1 before reaching this conditional
    // alternative is an unused fixed vertical shake
    if (req->isPerpendicularShake) {
        atEyeOffset.x = 0;
        atEyeOffset.y = 0;
        atEyeOffset.z = 0;
        OLib_Vec3fDiffToVecSphGeo(&eyeAtAngle, eye, at);

        atEyeOffsetSph2.r = req->verticalMag * verticalPertubation;
        atEyeOffsetSph2.pitch = eyeAtAngle.pitch + req->shakePlaneOffset.x + 0x4000;
        atEyeOffsetSph2.yaw = eyeAtAngle.yaw + req->shakePlaneOffset.y;
        OLib_VecSphAddToVec3f(&atEyeOffset, &atEyeOffset, &atEyeOffsetSph2);

        atEyeOffsetSph2.r = req->horizontalMag * horizontalPertubation;
        atEyeOffsetSph2.pitch = eyeAtAngle.pitch + req->shakePlaneOffset.x;
        atEyeOffsetSph2.yaw = eyeAtAngle.yaw + req->shakePlaneOffset.y + 0x4000;
        OLib_VecSphAddToVec3f(&atEyeOffset, &atEyeOffset, &atEyeOffsetSph2);
    } else {
        atEyeOffset.x = 0;
        atEyeOffset.y = req->verticalMag * verticalPertubation;
        atEyeOffset.z = 0;

        atEyeOffsetSph2.r = req->horizontalMag * horizontalPertubation;
        atEyeOffsetSph2.pitch = req->shakePlaneOffset.x;
        atEyeOffsetSph2.yaw = req->shakePlaneOffset.y;

        OLib_VecSphAddToVec3f(&atEyeOffset, &atEyeOffset, &atEyeOffsetSph2);
    }

    shake->atOffset = shake->eyeOffset = atEyeOffset;
    shake->rollOffset = req->rollOffset * verticalPertubation;
    shake->zoom = req->zoom * verticalPertubation;
}

s16 Quake_Callback1(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Math_SinS(req->speed * req->countdown);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback5(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Math_SinS(req->speed * req->countdown);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback6(QuakeRequest* req, ShakeInfo* shake) {
    f32 perpendicularPertubation;

    req->countdown--;
    perpendicularPertubation = Math_SinS(req->speed * ((req->countdown & 0xF) + 500));
    Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
    return 1;
}

s16 Quake_Callback3(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation =
            Math_SinS(req->speed * req->countdown) * ((f32)req->countdown / (f32)req->countdownMax);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback2(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Quake_Random();

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback4(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Quake_Random() * ((f32)req->countdown / (f32)req->countdownMax);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_GetFreeIndex(void) {
    s32 i;
    s32 ret = 0;
    s32 min = 0x10000;

    for (i = 0; i < ARRAY_COUNT(sQuakeRequest); i++) {
        if (sQuakeRequest[i].callbackIdx == 0) {
            ret = i;
            break;
        }

        if (sQuakeRequest[i].countdown < min) {
            min = sQuakeRequest[i].countdown;
            ret = i;
        }
    }

    return ret;
}

QuakeRequest* Quake_AddImpl(Camera* camera, u32 callbackIdx) {
    s16 idx = Quake_GetFreeIndex();
    QuakeRequest* req = &sQuakeRequest[idx];

    func_80096880(req, 0, sizeof(QuakeRequest)); // memset
    req->camera = camera;
    req->cameraPtrsIdx = camera->thisIdx;
    req->callbackIdx = callbackIdx;
    req->isPerpendicularShake = true;
    req->randIdx = ((s16)(Rand_ZeroOne() * (f32)0x10000) & ~3) + idx;
    sQuakeRequestCount++;

    return req;
}

void Quake_Remove(QuakeRequest* req) {
    req->callbackIdx = 0;
    req->countdown = -1;
    sQuakeRequestCount--;
}

QuakeRequest* Quake_GetRequest(s16 idx) {
    QuakeRequest* req = &sQuakeRequest[idx & 3];

    if (req->callbackIdx == 0) {
        return NULL;
    }

    if (idx != req->randIdx) {
        return NULL;
    }

    return req;
}

u32 Quake_SetValue(s16 idx, s16 valueType, s16 value) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req == NULL) {
        return false;
    } else {
        switch (valueType) {
            case 1:
                req->speed = value;
                break;
            case 2:
                req->verticalMag = value;
                break;
            case 4:
                req->horizontalMag = value;
                break;
            case 8:
                req->zoom = value;
                break;
            case 0x10:
                req->rollOffset = value;
                break;
            case 0x20:
                req->shakePlaneOffset.x = value;
                break;
            case 0x40:
                req->shakePlaneOffset.y = value;
                break;
            case 0x80:
                req->shakePlaneOffset.z = value;
                break;
            case 0x100:
                req->countdown = value;
                req->countdownMax = req->countdown;
                break;
            case 0x200:
                req->isPerpendicularShake = value;
                break;
        }
        return true;
    }
}

u32 Quake_SetSpeed(s16 idx, s16 value) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->speed = value;
        return true;
    }
    return false;
}

u32 Quake_SetCountdown(s16 idx, s16 value) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->countdown = value;
        req->countdownMax = req->countdown;
        return true;
    }
    return false;
}

s16 Quake_GetCountdown(s16 idx) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        return req->countdown;
    }
    return 0;
}

u32 Quake_SetQuakeValues(s16 idx, s16 verticalMag, s16 horizontalMag, s16 zoom, s16 rollOffset) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->verticalMag = verticalMag;
        req->horizontalMag = horizontalMag;
        req->zoom = zoom;
        req->rollOffset = rollOffset;
        return true;
    }
    return false;
}

u32 Quake_SetQuakeValues2(s16 idx, s16 isPerpendicularShake, Vec3s shakePlaneOffset) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->isPerpendicularShake = isPerpendicularShake;
        req->shakePlaneOffset = shakePlaneOffset;
        return true;
    }
    return false;
}

void Quake_Init(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(sQuakeRequest); i++) {
        sQuakeRequest[i].callbackIdx = 0;
        sQuakeRequest[i].countdown = 0;
    }
    D_801C0EC0 = 1;
    sQuakeRequestCount = 0;
}

s16 Quake_Add(Camera* cam, u32 callbackIdx) {
    return Quake_AddImpl(cam, callbackIdx)->randIdx;
}

u32 Quake_RemoveFromIdx(s16 idx) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        Quake_Remove(req);
        return true;
    }
    return false;
}

s16 Quake_Calc(Camera* camera, QuakeCamCalc* camData) {
    s32 pad;
    QuakeRequest* req;
    ShakeInfo shake;
    f32 absSpeedDiv;
    f32 maxCurr;
    f32 maxNext;
    s32 idx;
    s32 ret;
    u32 eq;
    Vec3f originVec;
    GlobalContext* globalCtx = camera->globalCtx;

    originVec.x = 0.0f;
    originVec.y = 0.0f;
    originVec.z = 0.0f;
    camData->atOffset.x = 0.0f;
    camData->atOffset.y = 0.0f;
    camData->atOffset.z = 0.0f;
    camData->eyeOffset.x = 0.0f;
    camData->eyeOffset.y = 0.0f;
    camData->eyeOffset.z = 0.0f;
    camData->rollOffset = 0;
    camData->zoom = 0;
    camData->max = 0.0f;

    if (sQuakeRequestCount == 0) {
        return 0;
    }

    ret = 0;
    for (idx = 0; idx < ARRAY_COUNT(sQuakeRequest); idx++) {
        req = &sQuakeRequest[idx];
        if (req->callbackIdx != 0) {
            if (globalCtx->cameraPtrs[req->cameraPtrsIdx] == NULL) {
                Quake_Remove(req);
            } else {
                eq = (camera->thisIdx != req->camera->thisIdx);
                absSpeedDiv = ABS(req->speed) / (f32)0x8000;
                if (sQuakeCallbacks[req->callbackIdx](req, &shake) == 0) {
                    Quake_Remove(req);
                } else if (eq == 0) {
                    if (fabsf(camData->atOffset.x) < fabsf(shake.atOffset.x)) {
                        camData->atOffset.x = shake.atOffset.x;
                    }
                    if (fabsf(camData->atOffset.y) < fabsf(shake.atOffset.y)) {
                        camData->atOffset.y = shake.atOffset.y;
                    }
                    if (fabsf(camData->atOffset.z) < fabsf(shake.atOffset.z)) {
                        camData->atOffset.z = shake.atOffset.z;
                    }
                    if (fabsf(camData->eyeOffset.x) < fabsf(shake.eyeOffset.x)) {
                        camData->eyeOffset.x = shake.eyeOffset.x;
                    }
                    if (fabsf(camData->eyeOffset.y) < fabsf(shake.eyeOffset.y)) {
                        camData->eyeOffset.y = shake.eyeOffset.y;
                    }
                    if (fabsf(camData->eyeOffset.z) < fabsf(shake.eyeOffset.z)) {
                        camData->eyeOffset.z = shake.eyeOffset.z;
                    }
                    if (camData->rollOffset < shake.rollOffset) {
                        camData->rollOffset = shake.rollOffset;
                    }
                    if (camData->zoom < shake.zoom) {
                        camData->zoom = shake.zoom;
                    }

                    maxCurr = OLib_Vec3fDist(&shake.atOffset, &originVec) * absSpeedDiv;

                    maxNext = OLib_Vec3fDist(&shake.eyeOffset, &originVec) * absSpeedDiv;
                    maxCurr = CLAMP_MIN(maxCurr, maxNext);

                    maxNext = (camData->rollOffset * (7.0f / 2500.0f)) * absSpeedDiv;
                    maxCurr = CLAMP_MIN(maxCurr, maxNext);

                    maxNext = (camData->zoom * (7.0f / 2500.0f)) * absSpeedDiv;
                    maxCurr = CLAMP_MIN(maxCurr, maxNext);

                    if (camData->max < maxCurr) {
                        camData->max = maxCurr;
                    }

                    ret++;
                }
            }
        }
    }
    return ret;
}

void Quake2_Init(GlobalContext* globalCtx) {
    sQuake2Context.globalCtx = globalCtx;
    View_ClearQuake(&globalCtx->view);
    sQuake2Context.type = 0;
    sQuake2Context.countdown = 0;
    sQuake2Context.state = 0;
}

void Quake2_SetCountdown(s16 countdown) {
    sQuake2Context.countdown = countdown;
    sQuake2Context.state = 2;
}

s16 Quake2_GetCountdown(void) {
    return sQuake2Context.countdown;
}

s16 Quake2_GetType(void) {
    return sQuake2Context.type;
}

void Quake2_SetType(s32 type) {
    if (sQuake2Context.type < type) {
        sQuake2Context.type = type;
    }
}

void Quake2_ClearType(s32 type) {
    if (sQuake2Context.type == type) {
        sQuake2Context.type = 0;
    }
}

s32 Quake2_GetFloorQuake(Player* player) {
    if (func_800C9D8C(&sQuake2Context.globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId) == 0) {
        return func_800C9E18(&sQuake2Context.globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId);
    }
    return 0;
}

void Quake2_Update(void) {
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 temp_f12;
    f32 phi_f2;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    Player* player;
    GlobalContext* globalCtx = sQuake2Context.globalCtx;
    PosRot sp3C;
    Camera* camera = globalCtx->cameraPtrs[globalCtx->activeCamera];
    f32 speedRatio = CLAMP_MAX(camera->speedRatio, 1.0f);

    if (sQuake2Context.type != 0) {
        if (sQuake2Context.type & 0x800) {
            sQuake2Context.countdown = 2;
            D_801C0EE4 = 1008;
            D_801C0EE8 = 342;
            sp78 = 0.0f;
            sp74 = 170.0f;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 0.0f;
            sp64 = -0.01f;
            sp60 = 0.01f;
            sp5C = 0.0f;
            sp58 = 0.6f;
            sp8C = sp88 = sQuake2Context.countdown / 60.0f;
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 0x400) {
            if (sQuake2Context.state == 2) {
                D_801C0EEC = sQuake2Context.countdown;
                D_801C0EE4 = 1008;
                D_801C0EE8 = 342;
            }

            sp78 = 0.0f;
            sp74 = 50.0f / D_801C0EEC;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 0.0f;
            sp64 = 0.01f;
            sp60 = 100.0f;
            sp5C = 0.0f;
            sp58 = 0.4f;
            sp8C = sp88 = ((f32)D_801C0EEC - sQuake2Context.countdown) / (f32)D_801C0EEC;
            sp84 = 0.5f;
        } else if (sQuake2Context.type & 0x200) {
            if (sQuake2Context.state == 2) {
                D_801C0EEC = sQuake2Context.countdown;
                D_801C0EE4 = 508;
                D_801C0EE8 = 342;
            }

            sp78 = -5.0f;
            sp74 = 5.0f;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 2.0f;
            sp64 = 0.3f;
            sp60 = 0.3f;
            sp5C = 0.0f;
            sp58 = 0.1f;
            sp8C = sp88 = ((f32)D_801C0EEC - sQuake2Context.countdown) / (f32)D_801C0EEC;
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 0x100) {
            if (sQuake2Context.state == 2) {
                D_801C0EEC = sQuake2Context.countdown;
                D_801C0EE4 = 10000;
                D_801C0EE8 = 1000;
            }

            sp78 = 0.0f;
            sp74 = 150.0f;
            sp70 = 0;
            sp6C = 0;
            sp68 = 0.2f;
            sp64 = 0.025f;
            sp60 = 0.02f;
            sp5C = 0.01f;
            sp58 = 1.5f;
            if (sQuake2Context.countdown < 5) {
                sp8C = sp88 = ((f32)D_801C0EEC - sQuake2Context.countdown) / (f32)D_801C0EEC;
            } else {
                sp8C = sp88 = 0.0f;
            }
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 0x80) {
            if (sQuake2Context.state == 2) {
                D_801C0EEC = sQuake2Context.countdown;
                D_801C0EE4 = 1200;
                D_801C0EE8 = 2000;
            }

            sp78 = 0.0f;
            sp74 = 150.0f;
            sp70 = 0;
            sp6C = 0;
            sp68 = 0;
            sp64 = 0.03f;
            sp60 = 0.02f;
            sp5C = 0.01f;
            sp58 = 1.5f;

            sp8C = sp88 = sQuake2Context.countdown / (f32)D_801C0EEC;
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 0x40) {
            if (sQuake2Context.state == 2) {
                D_801C0EEC = sQuake2Context.countdown;
                D_801C0EE4 = 2500;
                D_801C0EE8 = 3000;
            }

            sp78 = 0.0f;
            sp74 = 150.0f;
            sp70 = 0;
            sp6C = 0;
            sp68 = 0;
            sp64 = 0.03f;
            sp60 = 0.03f;
            sp5C = 0.01f;
            sp58 = 1.3f;
            if (sQuake2Context.countdown < 4) {
                sp8C = sp88 = sQuake2Context.countdown / (f32)D_801C0EEC;
            } else {
                sp8C = sp88 = 0.0f;
            }
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 0x20) {
            sQuake2Context.countdown = 2;
            if (sQuake2Context.state == 2) {
                D_801C0EE4 = 2500;
                D_801C0EE8 = 3000;
            }

            D_801C0EE4 += 0xB1;
            D_801C0EE8 -= 0x2B;

            sp78 = -107.0f;
            sp74 = 158.0f;
            sp70 = 0.2f;
            sp6C = 1.7f;
            sp68 = -2.9f;
            sp64 = -0.6f;
            sp60 = -0.7f;
            sp5C = 0.6f;
            sp58 = 0.2f;
            sp88 = 1.0f;
            sp8C = 1.0f;
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 0x10) {
            if (sQuake2Context.state == 2) {
                D_801C0EEC = sQuake2Context.countdown;
                D_801C0EE4 = 1888;
                D_801C0EE8 = 444;
            }
            sp78 = 248.0f;
            sp74 = -90.0f;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 0.0f;
            sp64 = -0.4f;
            sp60 = 0.4f;
            sp5C = 0.2f;
            sp58 = 0.25f;
            phi_f2 = sQuake2Context.countdown / (f32)D_801C0EEC;
            sp88 = sp8C = phi_f2;
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 8) {
            D_801C0EE4 = 1008;
            D_801C0EE8 = 342;
            sQuake2Context.countdown = 2;

            player = PLAYER;

            if (&player->actor != NULL) {
                func_800B8248(&sp3C, player);
            }

            sp78 = 359.2f;
            sp74 = -18.5f;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 0.3f;

            switch (Quake2_GetFloorQuake(player)) {
                case 3:
                    sp64 = -0.06f;
                    sp60 = 0.1f;
                    sp5C = 0.03f;
                    sp58 = 0.33f;
                    break;
                case 2:
                    sp64 = -0.06f;
                    sp60 = 0.1f;
                    sp5C = 0.03f;
                    sp58 = 0.33f;
                    break;
                case 1:
                    sp64 = -0.06f;
                    sp60 = 0.1f;
                    sp5C = 0.03f;
                    sp58 = 0.33f;
                    break;
                default:
                    sp64 = -0.06f;
                    sp60 = 0.1f;
                    sp5C = 0.03f;
                    sp58 = 0.23f;
                    break;
            }

            if (player->unk_B88 < 0) {
                sp8C = (player->unk_B88 - (f32)0x4000) / (f32)0xC000;
            } else {
                sp8C = (player->unk_B88 + (f32)0x4000) / (f32)0xC000;
            }
            sp88 = -sp8C;
            sp84 = 1.0f;
        } else if (sQuake2Context.type & 4) {
            D_801C0EE4 = 1008;
            D_801C0EE8 = 342;
            sQuake2Context.countdown = 2;
            player = PLAYER;
            sp78 = 359.2f;
            sp74 = -18.5f;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 0.0f;

            switch (Quake2_GetFloorQuake(player)) {
                case 3:
                    sp64 = 0.12f;
                    sp60 = 0.12f;
                    sp5C = 0.08f;
                    sp58 = 0.18f;
                    break;
                case 2:
                    sp64 = 0.12f;
                    sp60 = 0.12f;
                    sp5C = 0.08f;
                    sp58 = 0.12f;
                    break;
                case 1:
                    sp64 = 0.12f;
                    sp60 = 0.12f;
                    sp5C = 0.08f;
                    sp58 = 0.08f;
                    break;
                default:
                    sp64 = 0.12f;
                    sp60 = 0.12f;
                    sp5C = 0.08f;
                    sp58 = 0.05f;
                    break;
            }

            if ((camera->waterYPos - camera->eye.y) > 2000.0f) {
                phi_f2 = 1.0f;
            } else {
                phi_f2 = (camera->waterYPos - camera->eye.y) / 2000.0f;
            }

            sp8C = sp84 = (phi_f2 * 0.15f) + 0.35f + (speedRatio * 0.4f);
            sp88 = 0.9f - sp8C;
        } else if (sQuake2Context.type & 1) {
            D_801C0EE4 = 1008;
            D_801C0EE8 = 342;
            sQuake2Context.countdown = 2;
            sp78 = 0.0f;
            sp74 = 150.0f;
            sp70 = 0.0f;
            sp6C = 0.0f;
            sp68 = 0.0f;
            sp64 = -0.01f;
            sp60 = 0.01f;
            sp5C = 0.01f;
            sp58 = 0.6f;
            sp84 = 1.0f;
            sp88 = 1.0f;
            sp8C = 1.0f;
        } else {
            return;
        }

        D_801C0EE4 += DEGF_TO_BINANG(sp78);
        D_801C0EE8 += DEGF_TO_BINANG(sp74);
        View_SetQuakeRotation(&sQuake2Context.globalCtx->view, Math_CosS(D_801C0EE4) * (DEGF_TO_RADF(sp70) * sp8C),
                              Math_SinS(D_801C0EE4) * (DEGF_TO_RADF(sp6C) * sp8C),
                              Math_SinS(D_801C0EE8) * (DEGF_TO_RADF(sp68) * sp88));
        View_SetQuakeScale(&sQuake2Context.globalCtx->view, (Math_SinS(D_801C0EE8) * (sp64 * sp8C)) + 1.0f,
                           (Math_CosS(D_801C0EE8) * (sp60 * sp8C)) + 1.0f,
                           (Math_CosS(D_801C0EE4) * (sp5C * sp88)) + 1.0f);
        View_SetQuakeSpeed(&sQuake2Context.globalCtx->view, sp58 * sp84);
        sQuake2Context.state = 1;
    } else if (sQuake2Context.state != 0) {
        View_ClearQuake(&globalCtx->view);
        sQuake2Context.state = 0;
        sQuake2Context.countdown = 0;
    }

    if (sQuake2Context.countdown != 0) {
        sQuake2Context.countdown--;
        if (sQuake2Context.countdown == 0) {
            sQuake2Context.type = 0;
        }
    }
}

s32 Quake_NumActiveQuakes(void) {
    QuakeRequest* req = sQuakeRequest;
    s32 numActiveQuakes = 0;

    if (req[0].callbackIdx != 0) {
        numActiveQuakes++;
    }
    if (req[1].callbackIdx != 0) {
        numActiveQuakes++;
    }
    if (req[2].callbackIdx != 0) {
        numActiveQuakes++;
    }
    if (req[3].callbackIdx != 0) {
        numActiveQuakes++;
    }

    return numActiveQuakes;
}
