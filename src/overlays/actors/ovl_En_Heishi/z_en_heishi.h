#ifndef Z_EN_HEISHI_H
#define Z_EN_HEISHI_H

#include "global.h"

struct EnHeishi;

typedef void (*EnHeishiActionFunc)(struct EnHeishi*, GlobalContext*);

typedef struct EnHeishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[17];
    /* 0x01EE */ Vec3s morphTable[17];
    /* 0x0254 */ EnHeishiActionFunc actionFunc;
    /* 0x0258 */ s16 headRotY;
    /* 0x025A */ s16 headRotX;
    /* 0x025C */ s16 headRotZ;
    /* 0x025E */ s16 headRotYTarget;
    /* 0x0260 */ s16 headRotXTarget;
    /* 0x0262 */ s16 headRotZTarget;
    /* 0x0264 */ s32 animIndex;
    /* 0x0268 */ s32 paramCopy;
    /* 0x026C */ s32 unk26C;
    /* 0x0270 */ s16 unk270;
    /* 0x0272 */ s16 yawTowardsPlayer;
    /* 0x0274 */ f32 frameCount;
    /* 0x0278 */ s16 unk278;
    /* 0x027C */ char unk_27C[0x8];
    /* 0x0284 */ ColliderCylinder colliderCylinder;
} EnHeishi; // size = 0x2D0

extern const ActorInit En_Heishi_InitVars;

#endif // Z_EN_HEISHI_H
