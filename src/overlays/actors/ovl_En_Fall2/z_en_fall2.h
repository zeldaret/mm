#ifndef Z_EN_FALL2_H
#define Z_EN_FALL2_H

#include "global.h"
#include "assets/objects/object_fall2/object_fall2.h"

struct EnFall2;

typedef void (*EnFall2ActionFunc)(struct EnFall2*, PlayState*);

typedef struct EnFall2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkeletonInfo skeletonInfo;
    /* 0x174 */ Vec3s unk174[30];
    /* 0x228 */ Vec3s unk228[30];
    /* 0x2DC */ AnimatedMaterial* unk2DC;
    /* 0x2E0 */ f32 alphaLevel;
    /* 0x2E4 */ s16 csActorAction;
    /* 0x2E6 */ u16 csActionIndex;
    /* 0x2E8 */ EnFall2ActionFunc actionFunc;
} EnFall2; // size = 0x2EC

extern const ActorInit En_Fall2_InitVars;

#endif // Z_EN_FALL2_H
