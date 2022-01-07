#ifndef Z_EN_DEMO_HEISHI_H
#define Z_EN_DEMO_HEISHI_H

#include "global.h"

struct EnDemoheishi;

typedef void (*EnDemoheishiActionFunc)(struct EnDemoheishi*, GlobalContext*);

typedef struct EnDemoheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[17];
    /* 0x1EE */ Vec3s morphTable[17];
    /* 0x254 */ EnDemoheishiActionFunc actionFunc;
    /* 0x258 */ s16 headRotY;
    /* 0x25A */ s16 headRotX;
    /* 0x25C */ s16 headRotZ;
    /* 0x25E */ s16 headRotYTarget;
    /* 0x260 */ s16 headRotXTarget;
    /* 0x262 */ s16 headRotZTarget;
    /* 0x264 */ s32 animIndex;
    /* 0x268 */ s16 unk268;
    /* 0x26C */ f32 frameCount;
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ ColliderCylinder colliderCylinder;
} EnDemoheishi; //size = 0x2C0

extern const ActorInit En_Demo_heishi_InitVars;

#endif // Z_EN_DEMO_HEISHI_H
