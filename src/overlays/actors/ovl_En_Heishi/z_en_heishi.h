#ifndef Z_EN_HEISHI_H
#define Z_EN_HEISHI_H

#include "global.h"

struct EnHeishi;

typedef void (*EnHeishiActionFunc)(struct EnHeishi*, GlobalContext*);

typedef enum {
    /*  0 */ HEISHI_LIMB_NONE,
    /*  1 */ HEISHI_LIMB_ROOT,
    /*  2 */ HEISHI_LIMB_PELVIS,
    /*  3 */ HEISHI_LIMB_LEFT_THIGH,
    /*  4 */ HEISHI_LIMB_LEFT_CALF,
    /*  5 */ HEISHI_LIMB_LEFT_FOOT,
    /*  6 */ HEISHI_LIMB_RIGHT_THIGH,
    /*  7 */ HEISHI_LIMB_RIGHT_CALF,
    /*  8 */ HEISHI_LIMB_RIGHT_FOOT,
    /*  9 */ HEISHI_LIMB_TORSO,
    /* 10 */ HEISHI_LIMB_LEFT_SHOULDER,
    /* 11 */ HEISHI_LIMB_LEFT_FOREARM,
    /* 12 */ HEISHI_LIMB_LEFT_HAND,
    /* 13 */ HEISHI_LIMB_RIGHT_SHOULDER,
    /* 14 */ HEISHI_LIMB_RIGHT_FOREARM,
    /* 15 */ HEISHI_LIMB_RIGHT_HAND_WITH_SPEAR,
    /* 16 */ HEISHI_LIMB_HEAD,
    /* 17 */ HEISHI_LIMB_MAX
} EnHeishiLimbs;

typedef struct EnHeishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[HEISHI_LIMB_MAX];
    /* 0x01EE */ Vec3s morphTable[HEISHI_LIMB_MAX];
    /* 0x0254 */ EnHeishiActionFunc actionFunc;
    /* 0x0258 */ s16 headRotY;
    /* 0x025A */ s16 headRotX;
    /* 0x025C */ s16 headRotZ;
    /* 0x025E */ s16 headRotYTarget;
    /* 0x0260 */ s16 headRotXTarget;
    /* 0x0262 */ s16 headRotZTarget;
    /* 0x0264 */ s32 animIndex;
    /* 0x0268 */ s32 paramsCopy;
    /* 0x026C */ s32 shouldSetHeadRotation;
    /* 0x0270 */ s16 timer;
    /* 0x0272 */ s16 yawTowardsPlayer;
    /* 0x0274 */ f32 frameCount;
    /* 0x0278 */ s16 unk278;    // set and not used
    /* 0x027C */ UNK_TYPE1 unk_27C[0x8];
    /* 0x0284 */ ColliderCylinder colliderCylinder;
} EnHeishi; // size = 0x2D0

#endif // Z_EN_HEISHI_H
