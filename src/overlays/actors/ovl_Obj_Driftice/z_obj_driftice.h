#ifndef Z_OBJ_DRIFTICE_H
#define Z_OBJ_DRIFTICE_H

#include "global.h"

struct ObjDriftice;

typedef void (*ObjDrifticeActionFunc)(struct ObjDriftice*, PlayState*);

#define OBJDRIFTICE_SCALE_TYPE(thisx) ((thisx)->params & 3)
#define OBJDRIFTICE_GET_PATH_INDEX(thisx) (((thisx)->params >> 2) & 0x7F)
#define OBJDRIFTICE_GET_DRIFT_SPEED_INDEX(thisx) (((thisx)->params >> 9) & 7)
#define OBJDRIFTICE_RESET_TO_START_OF_PATH(thisx) (((thisx)->params >> 0xC) & 1)
#define OBJDRIFTICE_DYNAMICS_MODE(thisx) ((thisx)->home.rot.x & 3)

typedef enum {
    /* 0 */ OBJ_DRIFTICE_DYNAMICS_NONE,
    /* 1 */ OBJ_DRIFTICE_DYNAMICS_MODE1, // use sDynamicsCoefficients[0]
    /* 2 */ OBJ_DRIFTICE_DYNAMICS_MODE2, // use sDynamicsCoefficients[1]
    /* 3 */ OBJ_DRIFTICE_DYNAMICS_MODE3  // use sDynamicsCoefficients[2]
} ObjDrifticeDynamicsMode;

typedef struct {
    /* 0x00 */ s16 reseedTimer; // when timer reaches 0 some variable in this struct are rerolled by rng
    /* 0x02 */ s16 currentArg;
    /* 0x04 */ s16 argRateOfChange;
    /* 0x08 */ f32 currentMagnitude; 
    /* 0x0C */ f32 maxMagnitude;
    /* 0x10 */ f32 magnitudeRateOfChange; // how much to step currentMagnitude per frame (calculated fresh each frame)
} ObjDrifticeOscillationState; // size = 0x14

typedef struct {
    /* 0x00 */ s16 precessionAngle;
    /* 0x02 */ s16 precessionAngleRateOfChange; // between 0 (player not standing) and some max value (player stood and fully tipped)
    /* 0x04 */ s16 tiltMagnitude2;
    /* 0x06 */ s16 tiltMagnitude2RateOfChange;
    /* 0x08 */ f32 impactFromPlayer; // Between 0.02 and 1.0. Incremented/Decremented while player is on/off platform.
    /* 0x0C */ ObjDrifticeOscillationState oscillationState[2];
} ObjDrifticePlayerRelatedPrecessionDynamics; // size = 0x34

typedef struct {
    /* 0x00 */ s16 reseedTimer;
    /* 0x02 */ s16 precessionAngle1;
    /* 0x04 */ s16 precessionAngle1Target;
    /* 0x06 */ s16 precessionAngle2;
    /* 0x08 */ s16 precessionAngle2Target;
    /* 0x0C */ ObjDrifticeOscillationState oscillationState[3];
} ObjDrifticeGenericPrecessionDynamics; // size = 0x48

typedef struct {
    /* 0x00 */ ObjDrifticeOscillationState playerRelatedYOffsetOscillationState; // playerRelatedYOffsetOscillationState
    /* 0x14 */ ObjDrifticeOscillationState genericYOffsetOscillationState[3]; // genericYOffsetOscillationState
    /* 0x50 */ ObjDrifticePlayerRelatedPrecessionDynamics playerRelatedPrecessionDynamics;
    /* 0x84 */ ObjDrifticeGenericPrecessionDynamics genericPrecessionDynamics;
} ObjDrifticeDynamics; // size = 0xCC

typedef struct ObjDriftice {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjDrifticeActionFunc actionFunc;
    /* 0x160 */ s32 finalPointIdx;
    /* 0x164 */ s32 curPathPointIdx;
    /* 0x168 */ s32 pathDirection;
    /* 0x16C */ Vec3s* pathPoints;
    /* 0x170 */ ObjDrifticeDynamics dynamics;
    /* 0x23C */ f32 driftSpeed;
    /* 0x240 */ f32 inverseScale;
    /* 0x244 */ s16 spinRate;
    /* 0x248 */ s32 timerPlayerOnTop;
    /* 0x24C */ s32 timerWaitToDriftAlongPath;
} ObjDriftice; // size = 0x250

#endif // Z_OBJ_DRIFTICE_H
