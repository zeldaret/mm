#ifndef Z_EN_DEMO_HEISHI_H
#define Z_EN_DEMO_HEISHI_H

#include "global.h"

struct EnDemoheishi;

typedef void (*EnDemoheishiActionFunc)(struct EnDemoheishi*, GlobalContext*);

typedef enum {
    /*  0 */ DEMOHEISHI_LIMB_NONE,
    /*  1 */ DEMOHEISHI_LIMB_ROOT,
    /*  2 */ DEMOHEISHI_LIMB_PELVIS,
    /*  3 */ DEMOHEISHI_LIMB_LEFT_THIGH,
    /*  4 */ DEMOHEISHI_LIMB_LEFT_SHIN,
    /*  5 */ DEMOHEISHI_LIMB_LEFT_FOOT,
    /*  6 */ DEMOHEISHI_LIMB_RIGHT_THIGH,
    /*  7 */ DEMOHEISHI_LIMB_RIGHT_SHIN,
    /*  8 */ DEMOHEISHI_LIMB_RIGHT_FOOT,
    /*  9 */ DEMOHEISHI_LIMB_TORSO,
    /* 10 */ DEMOHEISHI_LIMB_LEFT_SHOULDER,
    /* 11 */ DEMOHEISHI_LIMB_LEFT_FOREARM,
    /* 12 */ DEMOHEISHI_LIMB_LEFT_HAND,
    /* 13 */ DEMOHEISHI_LIMB_RIGHT_SHOULDER,
    /* 14 */ DEMOHEISHI_LIMB_RIGHT_FOREARM,
    /* 15 */ DEMOHEISHI_LIMB_RIGHT_HAND_WITH_SPEAR,
    /* 16 */ DEMOHEISHI_LIMB_HEAD,
    /* 17 */ DEMOHEISHI_LIMB_MAX
} EnDemoheishiLimbs;

typedef struct EnDemoheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[DEMOHEISHI_LIMB_MAX];
    /* 0x1EE */ Vec3s morphTable[DEMOHEISHI_LIMB_MAX];
    /* 0x254 */ EnDemoheishiActionFunc actionFunc;
    /* 0x258 */ s16 headRotY;
    /* 0x25A */ s16 headRotX;
    /* 0x25C */ s16 headRotZ;
    /* 0x25E */ s16 headRotYTarget;
    /* 0x260 */ s16 headRotXTarget;
    /* 0x262 */ s16 headRotZTarget;
    /* 0x264 */ s32 animIndex;
    /* 0x268 */ s16 timer;
    /* 0x26C */ f32 frameCount;
    /* 0x270 */ s16 isTalking;
    /* 0x272 */ s16 textIdIndex;
    /* 0x274 */ ColliderCylinder colliderCylinder;
} EnDemoheishi; //size = 0x2C0

extern const ActorInit En_Demo_heishi_InitVars;

#endif // Z_EN_DEMO_HEISHI_H
