#include "global.h"
#include "z64quake.h"
#include "z64view.h"

typedef struct {
    /* 0x00 */ s16 randIndex;
    /* 0x02 */ s16 countdownMax;
    /* 0x04 */ Camera* camera;
    /* 0x08 */ u32 type;
    /* 0x0C */ s16 verticalMag;
    /* 0x0E */ s16 horizontalMag;
    /* 0x10 */ s16 zoom;
    /* 0x12 */ s16 rollOffset;
    /* 0x14 */ Vec3s shakePlaneOffset; // angle deviations from shaking in the perpendicular plane
    /* 0x1A */ s16 speed;
    /* 0x1C */ s16 isShakePerpendicular;
    /* 0x1E */ s16 countdown;
    /* 0x20 */ s16 camId;
} QuakeRequest; // size = 0x24

typedef struct {
    /* 0x0 */ PlayState* play;
    /* 0x4 */ s32 type; // bitfield, highest set bit determines type
    /* 0x8 */ s16 countdown;
    /* 0xA */ s16 state;
} DistortionRequest; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f atOffset;
    /* 0x0C */ Vec3f eyeOffset;
    /* 0x18 */ s16 rollOffset;
    /* 0x1A */ s16 zoom;
} ShakeInfo; // size = 0x1C

typedef s16 (*QuakeCallbackFunc)(QuakeRequest*, ShakeInfo*);

typedef enum {
    /* 0 */ DISTORTION_INACTIVE,
    /* 1 */ DISTORTION_ACTIVE,
    /* 2 */ DISTORTION_SETUP
} DistortionState;

QuakeRequest sQuakeRequest[4];
DistortionRequest sDistortionRequest;

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

s16 Quake_CallbackType1(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Math_SinS(req->speed * req->countdown);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_CallbackType5(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Math_SinS(req->speed * req->countdown);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_CallbackType6(QuakeRequest* req, ShakeInfo* shake) {
    f32 perpendicularPertubation;

    req->countdown--;
    perpendicularPertubation = Math_SinS(req->speed * ((req->countdown & 0xF) + 500));
    Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
    return 1;
}

s16 Quake_CallbackType3(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation =
            Math_SinS(req->speed * req->countdown) * ((f32)req->countdown / (f32)req->countdownMax);

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_CallbackType2(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 perpendicularPertubation = Quake_Random();

        Quake_UpdateShakeInfo(req, shake, perpendicularPertubation, Rand_ZeroOne() * perpendicularPertubation);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_CallbackType4(QuakeRequest* req, ShakeInfo* shake) {
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
        if (sQuakeRequest[i].type == 0) {
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

QuakeRequest* Quake_AddImpl(Camera* camera, u32 type) {
    s16 index = Quake_GetFreeIndex();
    QuakeRequest* req = &sQuakeRequest[index];

    __osMemset(req, 0, sizeof(QuakeRequest));
    req->camera = camera;
    req->camId = camera->camId;
    req->type = type;
    req->isShakePerpendicular = true;
    req->randIndex = ((s16)(Rand_ZeroOne() * 0x10000) & ~3) + index;
    sQuakeRequestCount++;

    return req;
}

void Quake_RemoveRequest(QuakeRequest* req) {
    req->type = 0;
    req->countdown = -1;
    sQuakeRequestCount--;
}

QuakeRequest* Quake_GetRequest(s16 quakeIndex) {
    QuakeRequest* req = &sQuakeRequest[quakeIndex & 3];

    if (req->type == 0) {
        return NULL;
    }

    if (quakeIndex != req->randIndex) {
        return NULL;
    }

    return req;
}

u32 Quake_SetValue(s16 quakeIndex, s16 valueType, s16 value) {
    QuakeRequest* req = Quake_GetRequest(quakeIndex);

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

            default:
                break;
        }

        return true;
    }
}

u32 Quake_SetSpeed(s16 quakeIndex, s16 speed) {
    QuakeRequest* req = Quake_GetRequest(quakeIndex);

    if (req != NULL) {
        req->speed = speed;
        return true;
    }
    return false;
}

u32 Quake_SetCountdown(s16 quakeIndex, s16 countdown) {
    QuakeRequest* req = Quake_GetRequest(quakeIndex);

    if (req != NULL) {
        req->countdown = countdown;
        req->countdownMax = req->countdown;
        return true;
    }
    return false;
}

s16 Quake_GetCountdown(s16 quakeIndex) {
    QuakeRequest* req = Quake_GetRequest(quakeIndex);

    if (req != NULL) {
        return req->countdown;
    }
    return 0;
}

u32 Quake_SetQuakeValues(s16 quakeIndex, s16 verticalMag, s16 horizontalMag, s16 zoom, s16 rollOffset) {
    QuakeRequest* req = Quake_GetRequest(quakeIndex);

    if (req != NULL) {
        req->verticalMag = verticalMag;
        req->horizontalMag = horizontalMag;
        req->zoom = zoom;
        req->rollOffset = rollOffset;
        return true;
    }
    return false;
}

u32 Quake_SetQuakeValues2(s16 quakeIndex, s16 isShakePerpendicular, Vec3s shakePlaneOffset) {
    QuakeRequest* req = Quake_GetRequest(quakeIndex);

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
        sQuakeRequest[i].type = 0;
        sQuakeRequest[i].countdown = 0;
    }
    sIsQuakeInitialized = true;
    sQuakeRequestCount = 0;
}

s16 Quake_Add(Camera* camera, u32 type) {
    return Quake_AddImpl(camera, type)->randIndex;
}

u32 Quake_Remove(s16 index) {
    QuakeRequest* req = Quake_GetRequest(index);

    if (req != NULL) {
        Quake_RemoveRequest(req);
        return true;
    }
    return false;
}

static QuakeCallbackFunc sQuakeCallbacks[] = {
    NULL,
    Quake_CallbackType1,
    Quake_CallbackType2,
    Quake_CallbackType3,
    Quake_CallbackType4,
    Quake_CallbackType5,
    Quake_CallbackType6,
};

s16 Quake_Calc(Camera* camera, QuakeCamCalc* camData) {
    s32 pad;
    QuakeRequest* req;
    ShakeInfo shake;
    f32 absSpeedDiv;
    f32 maxCurr;
    f32 maxNext;
    s32 index;
    s32 ret;
    u32 eq;
    Vec3f originVec;
    PlayState* play = camera->play;

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
    for (index = 0; index < ARRAY_COUNT(sQuakeRequest); index++) {
        req = &sQuakeRequest[index];
        if (req->type != 0) {
            if (play->cameraPtrs[req->camId] == NULL) {
                Quake_RemoveRequest(req);
            } else {
                eq = (camera->camId != req->camera->camId);
                absSpeedDiv = ABS(req->speed) / (f32)0x8000;
                if (sQuakeCallbacks[req->type](req, &shake) == 0) {
                    Quake_RemoveRequest(req);
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

void Distortion_Init(PlayState* play) {
    sDistortionRequest.play = play;
    View_ClearDistortion(&play->view);
    sDistortionRequest.type = 0;
    sDistortionRequest.countdown = 0;
    sDistortionRequest.state = DISTORTION_INACTIVE;
}

void Distortion_SetCountdown(s16 countdown) {
    sDistortionRequest.countdown = countdown;
    sDistortionRequest.state = DISTORTION_SETUP;
}

s16 Distortion_GetCountdown(void) {
    return sDistortionRequest.countdown;
}

s16 Distortion_GetType(void) {
    return sDistortionRequest.type;
}

void Distortion_SetType(s32 type) {
    if (sDistortionRequest.type < type) {
        sDistortionRequest.type = type;
    }
}

void Distortion_ClearType(s32 type) {
    if (sDistortionRequest.type == type) {
        sDistortionRequest.type = 0;
    }
}

/**
 * Checks that the bg surface is an underwater conveyor type and if so, returns the conveyor speed
 */
s32 Distortion_GetUnderwaterCurrentSpeed(Player* player) {
    if (!SurfaceType_IsFloorConveyor(&sDistortionRequest.play->colCtx, player->actor.floorPoly,
                                     player->actor.floorBgId)) {
        return SurfaceType_GetConveyorSpeed(&sDistortionRequest.play->colCtx, player->actor.floorPoly,
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
    PlayState* play = sDistortionRequest.play;
    PosRot playerPosRot;
    Camera* camera = GET_ACTIVE_CAM(play);
    f32 speedRatio = CLAMP_MAX(camera->speedRatio, 1.0f);

    if (sDistortionRequest.type != 0) {
        if (sDistortionRequest.type & DISTORTION_TYPE_B) {
            sDistortionRequest.countdown = 2;
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
            xyScaleFactor = zScaleFactor = sDistortionRequest.countdown / 60.0f;
            speedScaleFactor = 1.0f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_A) {
            if (sDistortionRequest.state == DISTORTION_SETUP) {
                countdownMax = sDistortionRequest.countdown;
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
            xyScaleFactor = zScaleFactor = ((f32)countdownMax - sDistortionRequest.countdown) / (f32)countdownMax;
            speedScaleFactor = 0.5f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_9) {
            if (sDistortionRequest.state == DISTORTION_SETUP) {
                countdownMax = sDistortionRequest.countdown;
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
            xyScaleFactor = zScaleFactor = ((f32)countdownMax - sDistortionRequest.countdown) / (f32)countdownMax;
            speedScaleFactor = 1.0f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_8) {
            if (sDistortionRequest.state == DISTORTION_SETUP) {
                countdownMax = sDistortionRequest.countdown;
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
            if (sDistortionRequest.countdown < 5) {
                xyScaleFactor = zScaleFactor = ((f32)countdownMax - sDistortionRequest.countdown) / (f32)countdownMax;
            } else {
                xyScaleFactor = zScaleFactor = 0.0f;
            }
            speedScaleFactor = 1.0f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_7) {
            if (sDistortionRequest.state == DISTORTION_SETUP) {
                countdownMax = sDistortionRequest.countdown;
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
            xyScaleFactor = zScaleFactor = sDistortionRequest.countdown / (f32)countdownMax;
            speedScaleFactor = 1.0f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_6) {
            if (sDistortionRequest.state == DISTORTION_SETUP) {
                countdownMax = sDistortionRequest.countdown;
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
            if (sDistortionRequest.countdown < 4) {
                xyScaleFactor = zScaleFactor = sDistortionRequest.countdown / (f32)countdownMax;
            } else {
                xyScaleFactor = zScaleFactor = 0.0f;
            }
            speedScaleFactor = 1.0f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_5) {
            sDistortionRequest.countdown = 2;
            if (sDistortionRequest.state == DISTORTION_SETUP) {
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
        } else if (sDistortionRequest.type & DISTORTION_TYPE_4) {
            if (sDistortionRequest.state == DISTORTION_SETUP) {
                countdownMax = sDistortionRequest.countdown;
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
            countdownRatio = sDistortionRequest.countdown / (f32)countdownMax;
            zScaleFactor = xyScaleFactor = countdownRatio;
            speedScaleFactor = 1.0f;
        } else if (sDistortionRequest.type & DISTORTION_TYPE_3) {
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            sDistortionRequest.countdown = 2;
            player = GET_PLAYER(play);

            if (player != NULL) {
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
        } else if (sDistortionRequest.type & DISTORTION_TYPE_2) {
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            sDistortionRequest.countdown = 2;
            player = GET_PLAYER(play);

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
        } else if (sDistortionRequest.type & DISTORTION_TYPE_0) {
            // Gives a small mirage-like appearance
            depthPhase = 0x3F0;
            screenPlanePhase = 0x156;

            sDistortionRequest.countdown = 2;
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

        depthPhase += CAM_DEG_TO_BINANG(depthPhaseStep);
        screenPlanePhase += CAM_DEG_TO_BINANG(screenPlanePhaseStep);

        View_SetDistortionOrientation(&sDistortionRequest.play->view,
                                      Math_CosS(depthPhase) * (DEGF_TO_RADF(rotX) * xyScaleFactor),
                                      Math_SinS(depthPhase) * (DEGF_TO_RADF(rotY) * xyScaleFactor),
                                      Math_SinS(screenPlanePhase) * (DEGF_TO_RADF(rotZ) * zScaleFactor));
        View_SetDistortionScale(&sDistortionRequest.play->view,
                                (Math_SinS(screenPlanePhase) * (xScale * xyScaleFactor)) + 1.0f,
                                (Math_CosS(screenPlanePhase) * (yScale * xyScaleFactor)) + 1.0f,
                                (Math_CosS(depthPhase) * (zScale * zScaleFactor)) + 1.0f);
        View_SetDistortionSpeed(&sDistortionRequest.play->view, speed * speedScaleFactor);

        sDistortionRequest.state = DISTORTION_ACTIVE;

    } else if (sDistortionRequest.state != DISTORTION_INACTIVE) {
        View_ClearDistortion(&play->view);

        sDistortionRequest.state = DISTORTION_INACTIVE;
        sDistortionRequest.countdown = 0;
    }

    if (sDistortionRequest.countdown != 0) {
        sDistortionRequest.countdown--;
        if (sDistortionRequest.countdown == 0) {
            sDistortionRequest.type = 0;
        }
    }
}

s32 Quake_NumActiveQuakes(void) {
    QuakeRequest* req = sQuakeRequest;
    s32 numActiveQuakes = 0;

    if (req[0].type != 0) {
        numActiveQuakes++;
    }
    if (req[1].type != 0) {
        numActiveQuakes++;
    }
    if (req[2].type != 0) {
        numActiveQuakes++;
    }
    if (req[3].type != 0) {
        numActiveQuakes++;
    }

    return numActiveQuakes;
}
