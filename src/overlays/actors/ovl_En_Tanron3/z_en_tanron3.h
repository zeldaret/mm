#ifndef Z_EN_TANRON3_H
#define Z_EN_TANRON3_H

#include "global.h"

struct EnTanron3;

typedef void (*EnTanron3ActionFunc)(struct EnTanron3*, GlobalContext*);

typedef struct EnTanron3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[10];
    /* 0x1C4 */ Vec3s morphTable[10];
    /* 0x200 */ s16 timer;
    /* 0x202 */ u8 isPassive;
    /* 0x203 */ u8 isBeached;
    /* 0x204 */ s16 workTimer[3];
    /* 0x20A */ s16 deathTimer;
    /* 0x20C */ s16 fogTimer;
    /* 0x210 */ Vec3f targetPos;
    /* 0x21C */ Vec3f currentPos;
    /* 0x228 */ Vec3f deviationFromCurrentPos;
    /* 0x234 */ s16 rotationStep;
    /* 0x236 */ s16 targetRotationStep;
    /* 0x238 */ s16 rotationScale;
    /* 0x23C */ f32 targetSpeedXZ;
    /* 0x240 */ f32 speedMaxStep;
    /* 0x244 */ f32 waterSurfaceYPos;
    /* 0x248 */ Vec3s targetShapeRotation;
    /* 0x250 */ s32 currentRotationAngle;
    /* 0x254 */ s32 nextRotationAngle;
    /* 0x258 */ s16 tailRotation;
    /* 0x25A */ s16 trunkRotation;
    /* 0x25C */ s16 bodyRotation;
    /* 0x260 */ ColliderCylinder atCollider;
    /* 0x2AC */ ColliderCylinder acCollider;
    /* 0x2F8 */ EnTanron3ActionFunc actionFunc;
} EnTanron3; // size = 0x2FC

extern const ActorInit En_Tanron3_InitVars;

#endif // Z_EN_TANRON3_H
