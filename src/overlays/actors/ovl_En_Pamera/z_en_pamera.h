#ifndef Z_EN_PAMERA_H
#define Z_EN_PAMERA_H

#include "global.h"

struct EnPamera;

typedef enum {
    /* 00 */ PAMERA_LIMB_NONE,
    /* 01 */ PAMERA_LIMB_ROOT,
    /* 02 */ PAMERA_LIMB_SHOULDER_LEFT,
    /* 03 */ PAMERA_LIMB_FOREARM_LEFT,
    /* 04 */ PAMERA_LIMB_HAND_LEFT,
    /* 05 */ PAMERA_LIMB_SHOULDER_RIGHT,
    /* 06 */ PAMERA_LIMB_FOREARM_RIGHT,
    /* 07 */ PAMERA_LIMB_HAND_RIGHT,
    /* 08 */ PAMERA_LIMB_HEAD_FRONT_AND_TOP,
    /* 09 */ PAMERA_LIMB_HAIR,
    /* 10 */ PAMERA_LIMB_TORSO_FRONT,
    /* 11 */ PAMERA_LIMB_NECK,
    /* 12 */ PAMERA_LIMB_THIGH_LEFT,
    /* 13 */ PAMERA_LIMB_LEG_LEFT,
    /* 14 */ PAMERA_LIMB_FOOT_LEFT,
    /* 15 */ PAMERA_LIMB_THIGH_RIGHT,
    /* 16 */ PAMERA_LIMB_LEG_RIGHT,
    /* 17 */ PAMERA_LIMB_FOOT_RIGHT,
    /* 18 */ PAMERA_DRESS_FRONT,
    /* 19 */ PAMERA_DRESS_BACK,
    /* 20 */ PAMERA_DRESS_SIDES,
    /* 21 */ PAMERA_LIMB_UNK,
    /* 22 */ PAMERA_LIMB_UNK2,
    /* 23 */ PAMERA_LIMB_MAX
} ObjectPameraLimbs;

typedef void (*EnPameraActionFunc)(struct EnPamera*, GlobalContext*);
typedef void (*EnPameraSetupFunc)(struct EnPamera*, GlobalContext*);

typedef struct EnPamera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnPameraActionFunc actionFunc;
    /* 0x1D8 */ EnPameraSetupFunc setupFunc;
    /* 0x1DC */ Vec3s* pathPoints;
    /* 0x1E0 */ s32 pathIndex;
    /* 0x1E4 */ s32 pathPointsCount;
    /* 0x1E8 */ s32 pathId; 
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ Vec3s jointTable[PAMERA_LIMB_MAX];
    /* 0x27A */ Vec3s morphTable[PAMERA_LIMB_MAX];
    /* 0x304 */ Vec3s limb9Rot;
    /* 0x30A */ Vec3s limb8Rot;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ s16 unk_314;
    /* 0x316 */ s16 unk_316;
    /* 0x318 */ s16 cutscenes[2];
    /* 0x31C */ s16 hideInisdeTimer;
    /* 0x31E */ s16 unk_31E;
    /* 0x320 */ UNK_TYPE1 unk_320[0x2];
    /* 0x322 */ s16 unk_322;
    /* 0x324 */ u16 unk_324;
    /* 0x326 */ u16 unk_326;
} EnPamera; // size = 0x328

extern const ActorInit En_Pamera_InitVars;

#endif // Z_EN_PAMERA_H
