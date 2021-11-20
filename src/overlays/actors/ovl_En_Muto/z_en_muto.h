#ifndef Z_EN_MUTO_H
#define Z_EN_MUTO_H

#include "global.h"

struct EnMuto;

typedef void (*EnMutoActionFunc)(struct EnMuto*, GlobalContext*);

typedef struct EnMuto {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[17];
    /* 0x01EE */ Vec3s morphTable[17];
    /* 0x0254 */ EnMutoActionFunc actionFunc;
    /* 0x0258 */ Vec3s headRot;
    /* 0x025E */ Vec3s headRotTarget;
    /* 0x0262 */ Vec3s waistRot;
    /* 0x026A */ Vec3s waistRotTarget;
    /* 0x0270 */ s16 unusedCounter;
    /* 0x0274 */ f32 frameIndex;
    /* 0x0278 */ s16 isInDialogue;
    /* 0x027A */ s16 textIdIndex;
    /* 0x027C */ s16 yawTowardsTarget;
    /* 0x0280 */ s32 isInMayorsRoom;
    /* 0x0284 */ s32 shouldSetHeadRotation;
    /* 0x0288 */ Actor* targetActor;
    /* 0x028C */ s32 cutsceneState;
    /* 0x0290 */ s32 animIndex;
    /* 0x0294 */ ColliderCylinder collider;
} EnMuto; // size = 0x2E0

extern const ActorInit En_Muto_InitVars;

#endif // Z_EN_MUTO_H
