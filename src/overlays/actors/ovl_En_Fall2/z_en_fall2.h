#ifndef Z_EN_FALL2_H
#define Z_EN_FALL2_H

#include "global.h"

struct EnFall2;

typedef void (*EnFall2ActionFunc)(struct EnFall2*, PlayState*);

typedef struct EnFall2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkeletonInfo skeletonInfo;
    /* 0x174 */ Vec3s unk174;
    /* 0x17A */ char pad17A[0xAE];
    /* 0x228 */ s16 unk228;
    /* 0x22A */ char pad22A[0xB2];
    /* 0x2DC */ void* unk2DC;
    /* 0x2E0 */ f32 unk2E0;
    /* 0x2E4 */ s16 unk2E4;
    /* 0x2E6 */ u16 unk2E6;
    /* 0x2E8 */ EnFall2ActionFunc actionFunc;
} EnFall2; // size = 0x2EC

extern const ActorInit En_Fall2_InitVars;

#endif // Z_EN_FALL2_H
