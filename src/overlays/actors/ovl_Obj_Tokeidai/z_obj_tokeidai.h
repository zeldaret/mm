#ifndef Z_OBJ_TOKEIDAI_H
#define Z_OBJ_TOKEIDAI_H

#include "global.h"

#define OBJ_TOKEIDAI_TYPE(thisx) (((thisx)->params & 0xF000) >> 12)
#define OBJ_TOKEIDAI_GET_CURRENT_HOUR(this) ((s32)((this)->currentTime * (24.0f / 0x10000)))
#define OBJ_TOKEIDAI_GET_CURRENT_MINUTE(this) ((s32)((this)->currentTime * (360 * 2.0f / 0x10000)) % 30)
#define OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour) ((s16)(currentHour * (0x10000 / 24.0f)))
#define OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute) ((s16)(currentMinute * (0x10000 * 12.0f / 360)))

struct ObjTokeidai;

typedef void (*ObjTokeidaiActionFunc)(struct ObjTokeidai*, GlobalContext*);

typedef struct ObjTokeidai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Gfx* opaDList;
    /* 0x148 */ Gfx* xluDList;
    /* 0x14C */ s16 outerRingOrGearRotation;
    /* 0x14E */ s16 outerRingOrGearRotationalVelocity;
    /* 0x150 */ s16 outerRingOrGearRotationTimer;
    /* 0x152 */ s16 clockFaceRotation;
    /* 0x154 */ union {
                    s16 clockFaceRotationalVelocity;
                    s16 settleTimer;
                    s16 counterweightRotationalVelocity;
                    s16 openingWaitTimer;
                    s16 slidingClockFaceAngle;
                };
    /* 0x156 */ union {
                    s16 clockFaceRotationTimer;
                    s16 settleAmount;
                    s16 counterweightRotationalAcceleration;
                    s16 aerialClockFaceSpeed;
                };
    /* 0x158 */ s32 sunMoonDiskRotation;
    /* 0x15C */ union {
                    s16 sunMoonDiskRotationalVelocity;
                    s16 fallingClockFaceRotationalVelocity;
                };
    /* 0x15E */ s16 yTranslation;
    /* 0x160 */ s16 xRotation;
    /* 0x162 */ s16 clockFaceZTranslation; // amount the clock face recesses inwards once it transforms
    /* 0x164 */ s16 boundCount;
    /* 0x168 */ s32 clockMinute; // only 30 minutes in an hour
    /* 0x16C */ union {
                    s32 clockHour;
                    s32 spotlightIntensity;
                };
    /* 0x170 */ u16 currentTime;
    /* 0x174 */ ObjTokeidaiActionFunc actionFunc;
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif // Z_OBJ_TOKEIDAI_H
