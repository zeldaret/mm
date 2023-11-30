/*
 * File: z_obj_driftice.c
 * Overlay: ovl_Obj_Driftice
 * Description: Floating Ice Platforms in Mountain Village
 */

#include "z_obj_driftice.h"
#include "objects/object_driftice/object_driftice.h"

#define FLAGS 0x00000000

#define THIS ((ObjDriftice*)thisx)

#define Y_OFFSET_CHANGE_TIME 10

void ObjDriftice_Init(Actor* thisx, PlayState* play);
void ObjDriftice_Destroy(Actor* thisx, PlayState* play);
void ObjDriftice_Update(Actor* thisx, PlayState* play);
void ObjDriftice_Draw(Actor* thisx, PlayState* play);

void ObjDriftice_SetupDoNothing(ObjDriftice* this);
void ObjDriftice_DoNothing(ObjDriftice* this, PlayState* play);
void ObjDriftice_SetupDriftAlongPath(ObjDriftice* this);
void ObjDriftice_DriftAlongPath(ObjDriftice* this, PlayState* play);
void ObjDriftice_SetupWaitUntilPlayerIsOff(ObjDriftice* this);
void ObjDriftice_WaitUntilPlayerIsOff(ObjDriftice* this, PlayState* play);
void ObjDriftice_SetupWaitToDriftAlongPath(ObjDriftice* this);
void ObjDriftice_WaitToDriftAlongPath(ObjDriftice* this, PlayState* play);

ActorInit Obj_Driftice_InitVars = {
    /**/ ACTOR_OBJ_DRIFTICE,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_DRIFTICE,
    /**/ sizeof(ObjDriftice),
    /**/ ObjDriftice_Init,
    /**/ ObjDriftice_Destroy,
    /**/ ObjDriftice_Update,
    /**/ ObjDriftice_Draw,
};

typedef struct {
    /* 0x0 */ f32 actorScale;
    /* 0x2 */ f32 uncullZoneScale;
    /* 0x4 */ f32 uncullZoneDownward;
} ObjDrifticeScaleConsts; // size = 0xC

static ObjDrifticeScaleConsts sScaleConsts[] = {
    { 1.0f, 150.0f, 150.0f },
    { 1.5f, 250.0f, 200.0f },
    { 2.0f, 350.0f, 250.0f },
};

// these are the actor scales?
static f32 sdriftSpeeds[] = { 1.5f, 3.0f, 4.5f, 6.0f, 7.5f, 9.0f, 10.5f, 0.0f };

// Coefficients to multiply the different types of motion contributions when summed to overal motion
static f32 sDynamicsCoefficients[][4] = {
    { 0.6f, 0.5f, 0.2f, 0.4f },
    { 0.8f, 0.7f, 0.35f, 0.7f },
    { 1.0f, 1.0f, 0.8f, 1.0f },
};

typedef struct {
    /* 0x0 */ s16 argRateOfChangeBase;
    /* 0x2 */ s16 argRateOfChangeRange;
    /* 0x4 */ f32 maxMagnitudeBase;
    /* 0x8 */ f32 maxMagnitudeRange;
} ObjDrifticeOscillationRandReseedParams; // size = 0xC

static ObjDrifticeOscillationRandReseedParams sYOffsetGenericOscillationRandReseedParams[] = {
    { 0x12C, 0x64, 1.3f, 2.0f },
    { 0x258, 0x1F4, 1.2f, 1.8f },
    { 0x4B0, 0x3E8, 1.1f, 1.5f },
};

static ObjDrifticeOscillationRandReseedParams sPrecessionDueToPlayerOscillationRandReseedParams[] = {
    { 0x320, 0x190, 200.0f, 400.0f }, { 0x5DC, 0x258, 100.0f, 300.0f }
};

static ObjDrifticeOscillationRandReseedParams sPrecessionGenericOscillationRandReseedParams[] = {
    { 0x12C, 0x64, 300.0f, 700.0f },
    { 0x258, 0x258, 200.0f, 400.0f },
    { 0x4B0, 0x4B0, 100.0f, 300.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

void ObjDriftice_SetPosToPathPoint(ObjDriftice* this, s32 pathPointIdx) {
    Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, &this->pathPoints[pathPointIdx]);
}

void ObjDriftice_ClampSymetricAroundZero(s16* rot, s16 threshold) {
    if (*rot > threshold) {
        *rot = threshold;
    } else if (*rot < -threshold) {
        *rot = -threshold;
    }
}

/*
Returns the y offset contribution related to player interactions.

Updates an oscillation state and uses output. Combines with another term based on how long player has been stood
 on platform for.
*/
f32 ObjDriftice_PlayerRelatedYOffsetPhysicsUpdate(ObjDrifticeOscillationState* oscillationState, ObjDriftice* this) {
    f32 zeroF = 0.0f;
    f32 yOffset;

    if (this->timerPlayerOnTop >= Y_OFFSET_CHANGE_TIME) {
        yOffset = -8.0f;
    } else if (this->timerPlayerOnTop <= -Y_OFFSET_CHANGE_TIME) {
        yOffset = 0.0f;
    } else if (this->timerPlayerOnTop > 0) {
        yOffset = (Math_CosS(fabsf(this->timerPlayerOnTop) * (0x8000 * (1.0f / Y_OFFSET_CHANGE_TIME))) - 1.0f) *
                  4.0f; // Decrease from 0 to -8
    } else {
        yOffset = (Math_CosS(fabsf(this->timerPlayerOnTop) * (0x8000 * (1.0f / Y_OFFSET_CHANGE_TIME))) + 1.0f) *
                  -4.0f; // Increase from -8 to 0
    }

    if (this->timerPlayerOnTop > 0) {
        // If player on ice platform, every so often reroll the max oscillation magnitude, initial oscillation arg and
        // freeze the 'step' amount.
        if (oscillationState->reseedTimer > 0) {
            oscillationState->reseedTimer--;
        } else {
            oscillationState->reseedTimer = Rand_S16Offset(30, 70);
            oscillationState->argRateOfChange = Rand_S16Offset(1000, 1000);
            oscillationState->maxMagnitude = (Rand_ZeroOne() * 1.5f) + 1.0f;
            oscillationState->magnitudeRateOfChange =
                fabsf(oscillationState->maxMagnitude - oscillationState->currentMagnitude) * 0.05f;
        }
    } else {
        // If player off ice platform, set Step to decay oscillation magnitude to 0.0
        oscillationState->reseedTimer = 0;
        oscillationState->maxMagnitude = zeroF;
        oscillationState->magnitudeRateOfChange =
            (fabsf(oscillationState->maxMagnitude - oscillationState->currentMagnitude) * 0.05f) + 0.02f;
    }

    oscillationState->currentArg += oscillationState->argRateOfChange;
    Math_StepToF(&oscillationState->currentMagnitude, oscillationState->maxMagnitude,
                 oscillationState->magnitudeRateOfChange);

    yOffset += (Math_SinS(oscillationState->currentArg) * oscillationState->currentMagnitude);
    return yOffset;
}

/*
Returns the generic y offset contribution (unrelated to player interactions)

Updates three oscillation states and combines their outputs.
*/
f32 ObjDriftice_CalculateGenericYOffset(ObjDrifticeOscillationState* oscillationState, ObjDriftice* this) {
    f32 yOffset = 0.0f;
    ObjDrifticeOscillationState* oscillation;
    s32 i;

    for (i = 0; i < 3; i++) {
        oscillation = &oscillationState[i];

        if (oscillation->reseedTimer > 0) {
            oscillation->reseedTimer--;
        } else {
            oscillation->reseedTimer = Rand_S16Offset(30, 70);
            oscillation->argRateOfChange =
                Rand_S16Offset(sYOffsetGenericOscillationRandReseedParams[i].argRateOfChangeBase,
                               sYOffsetGenericOscillationRandReseedParams[i].argRateOfChangeRange);
            oscillation->maxMagnitude =
                sYOffsetGenericOscillationRandReseedParams[i].maxMagnitudeBase +
                (sYOffsetGenericOscillationRandReseedParams[i].maxMagnitudeRange * Rand_ZeroOne());
            oscillation->magnitudeRateOfChange =
                fabsf(oscillation->maxMagnitude - oscillation->currentMagnitude) * 0.05f;
        }
        oscillation->currentArg += oscillation->argRateOfChange;
        Math_StepToF(&oscillation->currentMagnitude, oscillation->maxMagnitude, oscillation->magnitudeRateOfChange);
        yOffset += Math_SinS(oscillation->currentArg) * oscillation->currentMagnitude;
    }

    return yOffset;
}

/*
Updates dynamics of platform precession based on player interaction and populates tiltMagnitude and precessionAngle.
    Value stored in tiltMagnitude approaches zero when player is not on platform.

Magnitude is calculated based on two contributions.
- tiltMagnitude1 = the combined output of two oscillation states * impactFromPlayer
- tiltMagnitude2 is based on player position and contains a feedback loop where targetTiltMagnitude2 and
    dynamics->tiltMagnitude2RateOfChange influence each other.
*/
void ObjDriftice_PlayerRelatedPrecessionPhysicsUpdate(ObjDrifticePlayerRelatedPrecessionDynamics* dynamics,
                                                      ObjDriftice* this, s16* tiltMagnitude, s16* precessionAngle) {
    ObjDrifticeOscillationState* oscillation;
    f32 tiltMagnitude1 = 0.0f;
    s16 targetTiltMagnitude2;
    s32 i;

    if (this->timerPlayerOnTop > 0) {
        f32 xzDistToPlayerNormalised = this->dyna.actor.xzDistToPlayer * this->inverseScale * 0.0007075472f; // 3 / 4240
        if (xzDistToPlayerNormalised > 1.0f) {
            xzDistToPlayerNormalised = 1.0f;
        } else if (xzDistToPlayerNormalised < 0.01f) {
            xzDistToPlayerNormalised = 0.01f;
        }
        Math_StepToS(&dynamics->precessionAngleRateOfChange, 1200.0f * xzDistToPlayerNormalised, 100);
        targetTiltMagnitude2 = 2500.0f * xzDistToPlayerNormalised;
        // target for tiltMagnitudeRateOfChange will be:
        // - higher if the platform is not already tilted much, or if player is far from the center
        // - lower if the platform is already tilted, or if player is nearer to the center
        Math_StepToS(&dynamics->tiltMagnitude2RateOfChange,
                     Math_CosS(dynamics->tiltMagnitude2 * 6.5536f) * (120.0f * xzDistToPlayerNormalised), 40);
        Math_StepToF(&dynamics->impactFromPlayer, 1.0f, 0.02f);
    } else {
        Math_StepToS(&dynamics->precessionAngleRateOfChange, 0, 150);
        targetTiltMagnitude2 = 0; // Tilt magnitude will decrease to zero over time
        Math_StepToS(&dynamics->tiltMagnitude2RateOfChange, 20,
                     7); // Tilt magnitude rate of change will quickly reach 20
        Math_StepToF(&dynamics->impactFromPlayer, 0.0f, 0.02f);
    }

    Math_ScaledStepToS(&dynamics->precessionAngle, this->dyna.actor.yawTowardsPlayer,
                       dynamics->precessionAngleRateOfChange);
    *precessionAngle = dynamics->precessionAngle;

    Math_ScaledStepToS(&dynamics->tiltMagnitude2, targetTiltMagnitude2, dynamics->tiltMagnitude2RateOfChange);
    for (i = 0; i < 2; i++) {
        oscillation = &dynamics->oscillationState[i];

        if (oscillation->reseedTimer > 0) {
            oscillation->reseedTimer--;
        } else {
            oscillation->reseedTimer = Rand_S16Offset(30, 70);
            oscillation->argRateOfChange =
                Rand_S16Offset(sPrecessionDueToPlayerOscillationRandReseedParams[i].argRateOfChangeBase,
                               sPrecessionDueToPlayerOscillationRandReseedParams[i].argRateOfChangeRange);
            oscillation->maxMagnitude =
                sPrecessionDueToPlayerOscillationRandReseedParams[i].maxMagnitudeBase +
                (sPrecessionDueToPlayerOscillationRandReseedParams[i].maxMagnitudeRange * Rand_ZeroOne());
            oscillation->magnitudeRateOfChange =
                (1.0f / 30) * fabsf(oscillation->maxMagnitude - oscillation->currentMagnitude);
        }
        oscillation->currentArg += oscillation->argRateOfChange;
        Math_StepToF(&oscillation->currentMagnitude, oscillation->maxMagnitude, oscillation->magnitudeRateOfChange);
        tiltMagnitude1 += Math_SinS(oscillation->currentArg) * oscillation->currentMagnitude;
    }
    tiltMagnitude1 *= dynamics->impactFromPlayer;
    *tiltMagnitude = (s32)tiltMagnitude1 + dynamics->tiltMagnitude2;
}

/*
Updates the state of the dynamics associated with generic precession of platform (unrelated to player interaction).
 Populates tiltMagnitude and precessionAngle

Updates three oscillation states and sums their outputs into tiltMagnitude
precessionAngle is the sum of two random angles which change over time. Always between -600 and 0.
*/
void ObjDriftice_GenericPrecessionPhysicsUpdate(ObjDrifticeGenericPrecessionDynamics* dynamics, ObjDriftice* this,
                                                s16* tiltMagnitude, s16* precessionAngle) {
    ObjDrifticeOscillationState* oscillation;
    f32 tiltMagnitudeSum = 0.0f;
    s32 i;

    if (dynamics->reseedTimer > 0) {
        dynamics->reseedTimer--;
    } else {
        dynamics->reseedTimer = Rand_S16Offset(30, 70);
        dynamics->precessionAngle1Target = Rand_S16Offset(-200, 200);
        dynamics->precessionAngle2Target = Rand_S16Offset(-400, 400);
    }

    Math_StepToS(&dynamics->precessionAngle1, dynamics->precessionAngle1Target, 50);
    Math_StepToS(&dynamics->precessionAngle2, dynamics->precessionAngle2Target, 50);
    *precessionAngle = dynamics->precessionAngle1 + dynamics->precessionAngle2;

    for (i = 0; i < 3; i++) {
        oscillation = &dynamics->oscillationState[i];

        if (oscillation->reseedTimer > 0) {
            oscillation->reseedTimer--;
        } else {
            oscillation->reseedTimer = Rand_S16Offset(30, 70);
            oscillation->argRateOfChange =
                Rand_S16Offset(sPrecessionGenericOscillationRandReseedParams[i].argRateOfChangeBase,
                               sPrecessionGenericOscillationRandReseedParams[i].argRateOfChangeRange);
            oscillation->maxMagnitude =
                sPrecessionGenericOscillationRandReseedParams[i].maxMagnitudeBase +
                (sPrecessionGenericOscillationRandReseedParams[i].maxMagnitudeRange * Rand_ZeroOne());
            oscillation->magnitudeRateOfChange =
                fabsf(oscillation->maxMagnitude - oscillation->currentMagnitude) * 0.033333335f;
        }
        oscillation->currentArg += oscillation->argRateOfChange;
        Math_StepToF(&oscillation->currentMagnitude, oscillation->maxMagnitude, oscillation->magnitudeRateOfChange);
        tiltMagnitudeSum += Math_SinS(oscillation->currentArg) * oscillation->currentMagnitude;
    }
    *tiltMagnitude = tiltMagnitudeSum;
}

// Updates dynamics of platform including the y offset (bobbing up/down) and precession (rotational tilt/sway)
void ObjDriftice_UpdateDynamics(ObjDrifticeDynamics* dynamics, ObjDriftice* this) {
    f32 temp;
    f32* coeffs = sDynamicsCoefficients[OBJDRIFTICE_DYNAMICS_MODE(&this->dyna.actor) - 1];
    s16 tiltMagnitudeGeneric;
    s16 precessionAngleGeneric;
    s16 tiltMagnitudeDueToPlayer;
    s16 precessionAngleDueToPlayer;
    f32 yOffsetDueToPlayer;
    f32 yOffsetGeneric;
    f32 tiltMagnitude;
    s16 precessionAngle;

    yOffsetDueToPlayer =
        ObjDriftice_PlayerRelatedYOffsetPhysicsUpdate(&dynamics->playerRelatedYOffsetOscillationState, this);
    yOffsetGeneric = ObjDriftice_CalculateGenericYOffset(dynamics->genericYOffsetOscillationState, this);
    ObjDriftice_PlayerRelatedPrecessionPhysicsUpdate(&dynamics->playerRelatedPrecessionDynamics, this,
                                                     &tiltMagnitudeDueToPlayer, &precessionAngleDueToPlayer);
    ObjDriftice_GenericPrecessionPhysicsUpdate(&dynamics->genericPrecessionDynamics, this, &tiltMagnitudeGeneric,
                                               &precessionAngleGeneric);

    this->dyna.actor.shape.yOffset =
        this->inverseScale * ((yOffsetGeneric * coeffs[1]) + (yOffsetDueToPlayer * coeffs[0]));
    tiltMagnitude = (tiltMagnitudeDueToPlayer * coeffs[2]) + (tiltMagnitudeGeneric * coeffs[3]) * (temp = 1.0f);
    precessionAngle = (precessionAngleGeneric + precessionAngleDueToPlayer) - this->dyna.actor.shape.rot.y;

    this->dyna.actor.shape.rot.x = Math_CosS(precessionAngle) * tiltMagnitude;
    ObjDriftice_ClampSymetricAroundZero(&this->dyna.actor.shape.rot.x, 2600);
    this->dyna.actor.shape.rot.z = -Math_SinS(precessionAngle) * tiltMagnitude;
    ObjDriftice_ClampSymetricAroundZero(&this->dyna.actor.shape.rot.z, 2600);
}

void ObjDriftice_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjDriftice* this = THIS;
    ObjDrifticeScaleConsts* scaleConsts = &sScaleConsts[OBJDRIFTICE_SCALE_TYPE(&this->dyna.actor)];
    Path* path;
    s32 dynaTransformFlags;
    s32 floatInPlace;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.world.rot.z = 0;

    Actor_SetScale(&this->dyna.actor, scaleConsts->actorScale * 0.035377357f); // 3 / 84.8
    this->dyna.actor.uncullZoneScale = scaleConsts->uncullZoneScale;
    this->dyna.actor.uncullZoneDownward = scaleConsts->uncullZoneDownward;
    this->inverseScale = 1.0f / this->dyna.actor.scale.x;
    this->driftSpeed = sdriftSpeeds[OBJDRIFTICE_GET_DRIFT_SPEED_INDEX(&this->dyna.actor)];

    floatInPlace = false;
    if (this->driftSpeed < 0.01f) {
        floatInPlace = true;
    }

    this->spinRate = thisx->home.rot.z * 45.511112f;

    dynaTransformFlags = 0;
    if (!floatInPlace) {
        dynaTransformFlags = DYNA_TRANSFORM_POS;
    }

    if (thisx->home.rot.z != 0) {
        dynaTransformFlags |= DYNA_TRANSFORM_POS | DYNA_TRANSFORM_ROT_Y;
    }

    DynaPolyActor_Init(&this->dyna, dynaTransformFlags);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_driftice_Colheader_001AA8);

    if (floatInPlace) {
        ObjDriftice_SetupDoNothing(this);
    } else {
        this->dyna.actor.flags |= ACTOR_FLAG_10;

        path = &play->setupPathList[OBJDRIFTICE_GET_PATH_INDEX(&this->dyna.actor)];
        this->curPathPointIdx = 0;
        this->finalPointIdx = path->count - 1;
        this->pathDirection = 1;

        this->pathPoints = Lib_SegmentedToVirtual(path->points);
        ObjDriftice_SetPosToPathPoint(this, this->curPathPointIdx);
        ObjDriftice_SetupDriftAlongPath(this);
    }
}

void ObjDriftice_Destroy(Actor* thisx, PlayState* play) {
    ObjDriftice* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void ObjDriftice_SetupDoNothing(ObjDriftice* this) {
    this->actionFunc = ObjDriftice_DoNothing;
}

void ObjDriftice_DoNothing(ObjDriftice* this, PlayState* play) {
}

void ObjDriftice_SetupDriftAlongPath(ObjDriftice* this) {
    this->actionFunc = ObjDriftice_DriftAlongPath;
}

void ObjDriftice_DriftAlongPath(ObjDriftice* this, PlayState* play) {
    f32 speedTarget;
    Vec3f nextPathPoint;
    f32 distToNextPathPoint;
    f32 speedStep;
    Vec3s* finalPathPoint;
    s32 snapToPathPoint;
    Actor* thisx = &this->dyna.actor;

    Math_Vec3s_ToVec3f(&nextPathPoint, &(&this->pathPoints[this->curPathPointIdx])[this->pathDirection]);
    Math_Vec3f_Diff(&nextPathPoint, &this->dyna.actor.world.pos, &thisx->velocity);

    distToNextPathPoint = Math3D_Vec3fMagnitude(&thisx->velocity);
    if (distToNextPathPoint < (this->driftSpeed * 8.0f)) {
        speedTarget = this->driftSpeed * 0.4f;
        speedStep = this->driftSpeed * 0.05f;
    } else {
        speedTarget = this->driftSpeed;
        speedStep = this->driftSpeed * 0.13f;
    }

    Math_StepToF(&this->dyna.actor.speed, speedTarget, speedStep);

    if ((this->dyna.actor.speed + 0.05f) < distToNextPathPoint) {
        Math_Vec3f_Scale(&this->dyna.actor.velocity, this->dyna.actor.speed / distToNextPathPoint);
        this->dyna.actor.world.pos.x += this->dyna.actor.velocity.x;
        this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
        this->dyna.actor.world.pos.z += this->dyna.actor.velocity.z;
    } else {
        snapToPathPoint = true;
        this->curPathPointIdx += this->pathDirection;

        if (1) {}

        this->dyna.actor.speed *= 0.5f;

        if (((this->curPathPointIdx >= this->finalPointIdx) && (this->pathDirection > 0)) ||
            ((this->curPathPointIdx <= 0) && (this->pathDirection < 0))) { // When reaching final point in the path:
            if (!OBJDRIFTICE_RESET_TO_START_OF_PATH(&this->dyna.actor)) {
                // Change direction
                this->pathDirection = -this->pathDirection;
                ObjDriftice_SetupWaitToDriftAlongPath(this);
            } else {
                // Reset to start of path
                finalPathPoint = &this->pathPoints[this->finalPointIdx];
                if (this->pathDirection > 0) {
                    this->curPathPointIdx = 0;
                } else {
                    this->curPathPointIdx = this->finalPointIdx;
                }

                // If the first and final points are not the same, disable collision to prevent moving player on reset
                if ((this->pathPoints[0].x != finalPathPoint->x) || (this->pathPoints[0].y != finalPathPoint->y) ||
                    (this->pathPoints[0].z != finalPathPoint->z)) {
                    ObjDriftice_SetupWaitUntilPlayerIsOff(this);
                    DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
                    snapToPathPoint = false;
                }
            }
        }
        if (snapToPathPoint) {
            ObjDriftice_SetPosToPathPoint(this, this->curPathPointIdx);
        }
    }
}

void ObjDriftice_SetupWaitUntilPlayerIsOff(ObjDriftice* this) {
    this->actionFunc = ObjDriftice_WaitUntilPlayerIsOff;
}

void ObjDriftice_WaitUntilPlayerIsOff(ObjDriftice* this, PlayState* play) {
    if (this->timerPlayerOnTop < 0) {
        ObjDriftice_SetPosToPathPoint(this, this->curPathPointIdx);
        DynaPoly_EnableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        ObjDriftice_SetupDriftAlongPath(this);
    }
}

void ObjDriftice_SetupWaitToDriftAlongPath(ObjDriftice* this) {
    this->timerWaitToDriftAlongPath = 10;
    this->actionFunc = ObjDriftice_WaitToDriftAlongPath;
}

void ObjDriftice_WaitToDriftAlongPath(ObjDriftice* this, PlayState* play) {
    this->timerWaitToDriftAlongPath--;
    if (this->timerWaitToDriftAlongPath <= 0) {
        this->dyna.actor.speed = 0.0f;
        ObjDriftice_SetupDriftAlongPath(this);
    }
}

void ObjDriftice_Update(Actor* thisx, PlayState* play) {
    ObjDriftice* this = THIS;

    if (DynaPolyActor_IsPlayerOnTop(&this->dyna)) {
        if (this->timerPlayerOnTop < 0) {
            this->timerPlayerOnTop = 1;
        } else {
            this->timerPlayerOnTop++;
        }
    } else {
        if (this->timerPlayerOnTop > 0) {
            this->timerPlayerOnTop = -1;
        } else {
            this->timerPlayerOnTop--;
        }
    }

    this->dyna.actor.shape.rot.y += this->spinRate;
    this->actionFunc(this, play);

    if ((OBJDRIFTICE_DYNAMICS_MODE(&this->dyna.actor) != OBJ_DRIFTICE_DYNAMICS_NONE) &&
        (this->dyna.actor.flags & ACTOR_FLAG_40)) {
        ObjDriftice_UpdateDynamics(&this->dynamics, this);
    }
}

void ObjDriftice_Draw(Actor* thisx, PlayState* play) {
    ObjDriftice* this = THIS;

    Gfx_DrawDListOpa(play, object_driftice_DL_0016A0);
}
