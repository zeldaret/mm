#include "global.h"

QuakeRequest sQuakeRequest[4];
DistortionContext sDistortionContext;

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

    __osMemset(req, 0, sizeof(QuakeRequest));
    req->camera = camera;
    req->camId = camera->camId;
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

static QuakeCallbackFunc sQuakeCallbacks[] = {
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
            if (globalCtx->cameraPtrs[req->camId] == NULL) {
                Quake_Remove(req);
            } else {
                eq = (camera->camId != req->camera->camId);
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

void Distortion_Init(GlobalContext* globalCtx) {
    sDistortionContext.globalCtx = globalCtx;
    View_ClearDistortion(&globalCtx->view);
    sDistortionContext.type = 0;
    sDistortionContext.countdown = 0;
    sDistortionContext.state = DISTORTION_INACTIVE;
}

void Distortion_SetCountdown(s16 countdown) {
    sDistortionContext.countdown = countdown;
    sDistortionContext.state = DISTORTION_SETUP;
}

s16 Distortion_GetCountdown(void) {
    return sDistortionContext.countdown;
}

s16 Distortion_GetType(void) {
    return sDistortionContext.type;
}

void Distortion_SetType(s32 type) {
    if (sDistortionContext.type < type) {
        sDistortionContext.type = type;
    }
}

void Distortion_ClearType(s32 type) {
    if (sDistortionContext.type == type) {
        sDistortionContext.type = 0;
    }
}

/**
 * Checks that the bg surface is an underwater conveyor type and if so, returns the conveyor speed
 */
s32 Distortion_GetUnderwaterCurrentSpeed(Player* player) {
    if (SurfaceType_GetConveyorType(&sDistortionContext.globalCtx->colCtx, player->actor.floorPoly,
                                    player->actor.floorBgId) == CONVEYOR_WATER) {
        return SurfaceType_GetConveyorSpeed(&sDistortionContext.globalCtx->colCtx, player->actor.floorPoly,
                                            player->actor.floorBgId);
    }
    return 0;
}

void Distortion_Update(void) {
    static s16 depthPhase = 0x3F0;
    static s16 screenPlanePhase = 0x156;
    static s16 countdownMax = 1;
    f32 xyScaleFactor;
    f32 zScaleFactor;
    f32 speedScaleFactor;
    f32 countdownRatio;
    f32 waterYScaleFactor;
    f32 depthPhaseStep;
    f32 screenPlanePhaseStep;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 xScale;
    f32 yScale;
    f32 zScale;
    f32 speed;
    Player* player;
    GlobalContext* globalCtx = sDistortionContext.globalCtx;
    PosRot playerPosRot;
    Camera* camera = GET_ACTIVE_CAM(globalCtx);
    f32 speedRatio = CLAMP_MAX(camera->speedRatio, 1.0f);

    if (sDistortionContext.type != 0) {
        if (sDistortionContext.type & 0x800) {
            sDistortionContext.countdown = 2;
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            depthPhaseStep = 0.0f;
            screenPlanePhaseStep = 170.0f;

            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;

            xScale = -0.01f;
            yScale = 0.01f;
            zScale = 0.0f;

            speed = 0.6f;
            xyScaleFactor = zScaleFactor = sDistortionContext.countdown / 60.0f;
            speedScaleFactor = 1.0f;
        } else if (sDistortionContext.type & 0x400) {
            if (sDistortionContext.state == DISTORTION_SETUP) {
                countdownMax = sDistortionContext.countdown;
                depthPhase = 0x3F0;
                screenPlanePhase = 0x156;
            }

            depthPhaseStep = 0.0f;
            screenPlanePhaseStep = 50.0f / countdownMax;

            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;

            xScale = 0.01f;
            yScale = 100.0f;
            zScale = 0.0f;

            speed = 0.4f;
            xyScaleFactor = zScaleFactor = ((f32)countdownMax - sDistortionContext.countdown) / (f32)countdownMax;
            speedScaleFactor = 0.5f;
        } else if (sDistortionContext.type & 0x200) {
            if (sDistortionContext.state == DISTORTION_SETUP) {
                countdownMax = sDistortionContext.countdown;
                depthPhase = 0x1FC;
                screenPlanePhase = 0x156;
            }

            depthPhaseStep = -5.0f;
            screenPlanePhaseStep = 5.0f;

            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 2.0f;

            xScale = 0.3f;
            yScale = 0.3f;
            zScale = 0.0f;

            speed = 0.1f;
            xyScaleFactor = zScaleFactor = ((f32)countdownMax - sDistortionContext.countdown) / (f32)countdownMax;
            speedScaleFactor = 1.0f;
        } else if (sDistortionContext.type & 0x100) {
            if (sDistortionContext.state == DISTORTION_SETUP) {
                countdownMax = sDistortionContext.countdown;
                depthPhase = 0x2710;
                screenPlanePhase = 0x3E8;
            }

            depthPhaseStep = 0.0f;
            screenPlanePhaseStep = 150.0f;

            rotX = 0;
            rotY = 0;
            rotZ = 0.2f;

            xScale = 0.025f;
            yScale = 0.02f;
            zScale = 0.01f;

            speed = 1.5f;
            if (sDistortionContext.countdown < 5) {
                xyScaleFactor = zScaleFactor = ((f32)countdownMax - sDistortionContext.countdown) / (f32)countdownMax;
            } else {
                xyScaleFactor = zScaleFactor = 0.0f;
            }
            speedScaleFactor = 1.0f;
        } else if (sDistortionContext.type & 0x80) {
            if (sDistortionContext.state == DISTORTION_SETUP) {
                countdownMax = sDistortionContext.countdown;
                depthPhase = 0x4B0;
                screenPlanePhase = 0x7D0;
            }

            depthPhaseStep = 0.0f;
            screenPlanePhaseStep = 150.0f;

            rotX = 0;
            rotY = 0;
            rotZ = 0;

            xScale = 0.03f;
            yScale = 0.02f;
            zScale = 0.01f;

            speed = 1.5f;
            xyScaleFactor = zScaleFactor = sDistortionContext.countdown / (f32)countdownMax;
            speedScaleFactor = 1.0f;
        } else if (sDistortionContext.type & 0x40) {
            if (sDistortionContext.state == DISTORTION_SETUP) {
                countdownMax = sDistortionContext.countdown;
                depthPhase = 0x9C4;
                screenPlanePhase = 0xBB8;
            }

            depthPhaseStep = 0.0f;
            screenPlanePhaseStep = 150.0f;

            rotX = 0;
            rotY = 0;
            rotZ = 0;

            xScale = 0.03f;
            yScale = 0.03f;
            zScale = 0.01f;

            speed = 1.3f;
            if (sDistortionContext.countdown < 4) {
                xyScaleFactor = zScaleFactor = sDistortionContext.countdown / (f32)countdownMax;
            } else {
                xyScaleFactor = zScaleFactor = 0.0f;
            }
            speedScaleFactor = 1.0f;
        } else if (sDistortionContext.type & 0x20) {
            sDistortionContext.countdown = 2;
            if (sDistortionContext.state == DISTORTION_SETUP) {
                depthPhase = 0x9C4;
                screenPlanePhase = 0xBB8;
            }

            depthPhase += 0xB1;
            screenPlanePhase -= 0x2B;

            depthPhaseStep = -107.0f;
            screenPlanePhaseStep = 158.0f;

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
        } else if (sDistortionContext.type & 0x10) {
            if (sDistortionContext.state == DISTORTION_SETUP) {
                countdownMax = sDistortionContext.countdown;
                depthPhase = 0x760;
                screenPlanePhase = 0x1BC;
            }

            depthPhaseStep = 248.0f;
            screenPlanePhaseStep = -90.0f;

            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;

            xScale = -0.4f;
            yScale = 0.4f;
            zScale = 0.2f;

            speed = 0.25f;
            countdownRatio = sDistortionContext.countdown / (f32)countdownMax;
            zScaleFactor = xyScaleFactor = countdownRatio;
            speedScaleFactor = 1.0f;
        } else if (sDistortionContext.type & 8) {
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            sDistortionContext.countdown = 2;
            player = GET_PLAYER(globalCtx);

            if (&player->actor != NULL) {
                Actor_GetWorldPosShapeRot(&playerPosRot, &player->actor);
            }

            depthPhaseStep = 359.2f;
            screenPlanePhaseStep = -18.5f;

            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.3f;

            switch (Distortion_GetUnderwaterCurrentSpeed(player)) {
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
        } else if (sDistortionContext.type & 4) {
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            sDistortionContext.countdown = 2;
            player = GET_PLAYER(globalCtx);

            depthPhaseStep = 359.2f;
            screenPlanePhaseStep = -18.5f;

            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            switch (Distortion_GetUnderwaterCurrentSpeed(player)) {
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
        } else if (sDistortionContext.type & 1) {
            // Gives a small mirage-like appearance
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            sDistortionContext.countdown = 2;
            depthPhaseStep = 0.0f;
            screenPlanePhaseStep = 150.0f;

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

        depthPhase += DEGF_TO_BINANG(depthPhaseStep);
        screenPlanePhase += DEGF_TO_BINANG(screenPlanePhaseStep);

        View_SetDistortionDirRot(&sDistortionContext.globalCtx->view,
                                 Math_CosS(depthPhase) * (DEGF_TO_RADF(rotX) * xyScaleFactor),
                                 Math_SinS(depthPhase) * (DEGF_TO_RADF(rotY) * xyScaleFactor),
                                 Math_SinS(screenPlanePhase) * (DEGF_TO_RADF(rotZ) * zScaleFactor));
        View_SetDistortionScale(&sDistortionContext.globalCtx->view,
                                (Math_SinS(screenPlanePhase) * (xScale * xyScaleFactor)) + 1.0f,
                                (Math_CosS(screenPlanePhase) * (yScale * xyScaleFactor)) + 1.0f,
                                (Math_CosS(depthPhase) * (zScale * zScaleFactor)) + 1.0f);
        View_SetDistortionSpeed(&sDistortionContext.globalCtx->view, speed * speedScaleFactor);

        sDistortionContext.state = DISTORTION_ACTIVE;

    } else if (sDistortionContext.state != DISTORTION_INACTIVE) {
        View_ClearDistortion(&globalCtx->view);

        sDistortionContext.state = DISTORTION_INACTIVE;
        sDistortionContext.countdown = 0;
    }

    if (sDistortionContext.countdown != 0) {
        sDistortionContext.countdown--;
        if (sDistortionContext.countdown == 0) {
            sDistortionContext.type = 0;
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
