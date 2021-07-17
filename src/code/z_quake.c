#include "global.h"

QuakeRequest sQuakeRequest[4];
Quake2Context sQuake2Context;

static s16 sIsQuakeInitialized = true;
static s16 sQuakeRequestCount = 0;

f32 Quake_Random(void) {
    return 2.0f * (Rand_ZeroOne() - 0.5f);
}

void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 verticalPertubation, f32 horizontalPertubation) {
    Vec3f* at = &req->camera->at;
    Vec3f* eye = &req->camera->eye;
    Vec3f atEyeOffset;
    VecSph atEyeOffsetSph2;
    VecSph eyeAtAngle;

    // isShakePerpendicular is always set to 1 before reaching this conditional
    // alternative is an unused fixed vertical shake
    if (req->isShakePerpendicular) {
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
    req->isShakePerpendicular = true;
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
            case QUAKE_SPEED:
                req->speed = value;
                break;
            case QUAKE_VERTICAL_MAG:
                req->verticalMag = value;
                break;
            case QUAKE_HORIZONTAL_MAG:
                req->horizontalMag = value;
                break;
            case QUAKE_ZOOM:
                req->zoom = value;
                break;
            case QUAKE_ROLL_OFFSET:
                req->rollOffset = value;
                break;
            case QUAKE_SHAKE_PLANE_OFFSET_X:
                req->shakePlaneOffset.x = value;
                break;
            case QUAKE_SHAKE_PLANE_OFFSET_Y:
                req->shakePlaneOffset.y = value;
                break;
            case QUAKE_SHAKE_PLANE_OFFSET_Z:
                req->shakePlaneOffset.z = value;
                break;
            case QUAKE_COUNTDOWN:
                req->countdown = value;
                req->countdownMax = req->countdown;
                break;
            case QUAKE_IS_SHAKE_PERPENDICULAR:
                req->isShakePerpendicular = value;
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

u32 Quake_SetQuakeValues2(s16 idx, s16 isShakePerpendicular, Vec3s shakePlaneOffset) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->isShakePerpendicular = isShakePerpendicular;
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
    sIsQuakeInitialized = true;
    sQuakeRequestCount = 0;
}

s16 Quake_Add(Camera* camera, u32 callbackIdx) {
    return Quake_AddImpl(camera, callbackIdx)->randIdx;
}

u32 Quake_RemoveFromIdx(s16 idx) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        Quake_Remove(req);
        return true;
    }
    return false;
}

static s16 (*sQuakeCallbacks[])(QuakeRequest*, ShakeInfo*) = {
    NULL, Quake_Callback1, Quake_Callback2, Quake_Callback3, Quake_Callback4, Quake_Callback5, Quake_Callback6,
};

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
    sQuake2Context.state = QUAKE2_INACTIVE;
}

void Quake2_SetCountdown(s16 countdown) {
    sQuake2Context.countdown = countdown;
    sQuake2Context.state = QUAKE2_SETUP;
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
    static s16 angle1 = 0x3F0;
    static s16 angle2 = 0x156;
    static s16 countdownMax = 1;
    f32 xyScaleFactor;
    f32 zScaleFactor;
    f32 speedScaleFactor;
    f32 countdownRatio;
    f32 waterYScaleFactor;
    f32 angle1Speed;
    f32 angle2Speed;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 xScale;
    f32 yScale;
    f32 zScale;
    f32 speed;
    Player* player;
    GlobalContext* globalCtx = sQuake2Context.globalCtx;
    PosRot playerPosRot;
    Camera* camera = globalCtx->cameraPtrs[globalCtx->activeCamera];
    f32 speedRatio = CLAMP_MAX(camera->speedRatio, 1.0f);

    if (sQuake2Context.type != 0) {
        if (sQuake2Context.type & 0x800) {
            sQuake2Context.countdown = 2;
            angle1 = 0x3F0;
            angle2 = 0x156;
            angle1Speed = 0.0f;
            angle2Speed = 170.0f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            xScale = -0.01f;
            yScale = 0.01f;
            zScale = 0.0f;
            speed = 0.6f;
            xyScaleFactor = zScaleFactor = sQuake2Context.countdown / 60.0f;
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 0x400) {
            if (sQuake2Context.state == QUAKE2_SETUP) {
                countdownMax = sQuake2Context.countdown;
                angle1 = 0x3F0;
                angle2 = 0x156;
            }

            angle1Speed = 0.0f;
            angle2Speed = 50.0f / countdownMax;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            xScale = 0.01f;
            yScale = 100.0f;
            zScale = 0.0f;
            speed = 0.4f;
            xyScaleFactor = zScaleFactor = ((f32)countdownMax - sQuake2Context.countdown) / (f32)countdownMax;
            speedScaleFactor = 0.5f;
        } else if (sQuake2Context.type & 0x200) {
            if (sQuake2Context.state == QUAKE2_SETUP) {
                countdownMax = sQuake2Context.countdown;
                angle1 = 0x1FC;
                angle2 = 0x156;
            }

            angle1Speed = -5.0f;
            angle2Speed = 5.0f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 2.0f;
            xScale = 0.3f;
            yScale = 0.3f;
            zScale = 0.0f;
            speed = 0.1f;
            xyScaleFactor = zScaleFactor = ((f32)countdownMax - sQuake2Context.countdown) / (f32)countdownMax;
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 0x100) {
            if (sQuake2Context.state == QUAKE2_SETUP) {
                countdownMax = sQuake2Context.countdown;
                angle1 = 0x2710;
                angle2 = 0x3E8;
            }

            angle1Speed = 0.0f;
            angle2Speed = 150.0f;
            rotX = 0;
            rotY = 0;
            rotZ = 0.2f;
            xScale = 0.025f;
            yScale = 0.02f;
            zScale = 0.01f;
            speed = 1.5f;
            if (sQuake2Context.countdown < 5) {
                xyScaleFactor = zScaleFactor = ((f32)countdownMax - sQuake2Context.countdown) / (f32)countdownMax;
            } else {
                xyScaleFactor = zScaleFactor = 0.0f;
            }
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 0x80) {
            if (sQuake2Context.state == QUAKE2_SETUP) {
                countdownMax = sQuake2Context.countdown;
                angle1 = 0x4B0;
                angle2 = 0x7D0;
            }

            angle1Speed = 0.0f;
            angle2Speed = 150.0f;
            rotX = 0;
            rotY = 0;
            rotZ = 0;
            xScale = 0.03f;
            yScale = 0.02f;
            zScale = 0.01f;
            speed = 1.5f;
            xyScaleFactor = zScaleFactor = sQuake2Context.countdown / (f32)countdownMax;
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 0x40) {
            if (sQuake2Context.state == QUAKE2_SETUP) {
                countdownMax = sQuake2Context.countdown;
                angle1 = 0x9C4;
                angle2 = 0xBB8;
            }

            angle1Speed = 0.0f;
            angle2Speed = 150.0f;
            rotX = 0;
            rotY = 0;
            rotZ = 0;
            xScale = 0.03f;
            yScale = 0.03f;
            zScale = 0.01f;
            speed = 1.3f;
            if (sQuake2Context.countdown < 4) {
                xyScaleFactor = zScaleFactor = sQuake2Context.countdown / (f32)countdownMax;
            } else {
                xyScaleFactor = zScaleFactor = 0.0f;
            }
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 0x20) {
            sQuake2Context.countdown = 2;
            if (sQuake2Context.state == QUAKE2_SETUP) {
                angle1 = 0x9C4;
                angle2 = 0xBB8;
            }

            angle1 += 0xB1;
            angle2 -= 0x2B;
            angle1Speed = -107.0f;
            angle2Speed = 158.0f;
            rotX = 0.2f;
            rotY = 1.7f;
            rotZ = -2.9f;
            xScale = -0.6f;
            yScale = -0.7f;
            zScale = 0.6f;
            speed = 0.2f;
            zScaleFactor = 1.0f;
            xyScaleFactor = 1.0f;
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 0x10) {
            if (sQuake2Context.state == QUAKE2_SETUP) {
                countdownMax = sQuake2Context.countdown;
                angle1 = 0x760;
                angle2 = 0x1BC;
            }

            angle1Speed = 248.0f;
            angle2Speed = -90.0f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            xScale = -0.4f;
            yScale = 0.4f;
            zScale = 0.2f;
            speed = 0.25f;
            countdownRatio = sQuake2Context.countdown / (f32)countdownMax;
            zScaleFactor = xyScaleFactor = countdownRatio;
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 8) {
            angle1 = 0x3F0;
            angle2 = 0x156;
            sQuake2Context.countdown = 2;
            player = PLAYER;

            if (&player->actor != NULL) {
                func_800B8248(&playerPosRot, player);
            }

            angle1Speed = 359.2f;
            angle2Speed = -18.5f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.3f;
            switch (Quake2_GetFloorQuake(player)) {
                case 3:
                    xScale = -0.06f;
                    yScale = 0.1f;
                    zScale = 0.03f;
                    speed = 0.33f;
                    break;
                case 2:
                    xScale = -0.06f;
                    yScale = 0.1f;
                    zScale = 0.03f;
                    speed = 0.33f;
                    break;
                case 1:
                    xScale = -0.06f;
                    yScale = 0.1f;
                    zScale = 0.03f;
                    speed = 0.33f;
                    break;
                default:
                    xScale = -0.06f;
                    yScale = 0.1f;
                    zScale = 0.03f;
                    speed = 0.23f;
                    break;
            }

            if (player->unk_B88 < 0) {
                xyScaleFactor = (player->unk_B88 - (f32)0x4000) / (f32)0xC000;
            } else {
                xyScaleFactor = (player->unk_B88 + (f32)0x4000) / (f32)0xC000;
            }
            zScaleFactor = -xyScaleFactor;
            speedScaleFactor = 1.0f;
        } else if (sQuake2Context.type & 4) {
            angle1 = 0x3F0;
            angle2 = 0x156;
            sQuake2Context.countdown = 2;
            player = PLAYER;
            angle1Speed = 359.2f;
            angle2Speed = -18.5f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            switch (Quake2_GetFloorQuake(player)) {
                case 3:
                    xScale = 0.12f;
                    yScale = 0.12f;
                    zScale = 0.08f;
                    speed = 0.18f;
                    break;
                case 2:
                    xScale = 0.12f;
                    yScale = 0.12f;
                    zScale = 0.08f;
                    speed = 0.12f;
                    break;
                case 1:
                    xScale = 0.12f;
                    yScale = 0.12f;
                    zScale = 0.08f;
                    speed = 0.08f;
                    break;
                default:
                    xScale = 0.12f;
                    yScale = 0.12f;
                    zScale = 0.08f;
                    speed = 0.05f;
                    break;
            }

            if ((camera->waterYPos - camera->eye.y) > 2000.0f) {
                waterYScaleFactor = 1.0f;
            } else {
                waterYScaleFactor = (camera->waterYPos - camera->eye.y) / 2000.0f;
            }

            xyScaleFactor = speedScaleFactor = (waterYScaleFactor * 0.15f) + 0.35f + (speedRatio * 0.4f);
            zScaleFactor = 0.9f - xyScaleFactor;
        } else if (sQuake2Context.type & 1) {
            angle1 = 0x3F0;
            angle2 = 0x156;
            sQuake2Context.countdown = 2;
            angle1Speed = 0.0f;
            angle2Speed = 150.0f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            xScale = -0.01f;
            yScale = 0.01f;
            zScale = 0.01f;
            speed = 0.6f;
            speedScaleFactor = 1.0f;
            zScaleFactor = 1.0f;
            xyScaleFactor = 1.0f;
        } else {
            return;
        }

        angle1 += DEGF_TO_BINANG(angle1Speed);
        angle2 += DEGF_TO_BINANG(angle2Speed);
        View_SetQuakeRotation(&sQuake2Context.globalCtx->view, Math_CosS(angle1) * (DEGF_TO_RADF(rotX) * xyScaleFactor),
                              Math_SinS(angle1) * (DEGF_TO_RADF(rotY) * xyScaleFactor),
                              Math_SinS(angle2) * (DEGF_TO_RADF(rotZ) * zScaleFactor));
        View_SetQuakeScale(&sQuake2Context.globalCtx->view, (Math_SinS(angle2) * (xScale * xyScaleFactor)) + 1.0f,
                           (Math_CosS(angle2) * (yScale * xyScaleFactor)) + 1.0f,
                           (Math_CosS(angle1) * (zScale * zScaleFactor)) + 1.0f);
        View_SetQuakeSpeed(&sQuake2Context.globalCtx->view, speed * speedScaleFactor);
        sQuake2Context.state = QUAKE2_ACTIVE;
    } else if (sQuake2Context.state != QUAKE2_INACTIVE) {
        View_ClearQuake(&globalCtx->view);
        sQuake2Context.state = QUAKE2_INACTIVE;
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
