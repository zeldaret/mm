#ifndef Z_EN_IN_H
#define Z_EN_IN_H

#include "global.h"

struct EnIn;

typedef void (*EnInActionFunc)(struct EnIn*, PlayState*);

typedef enum {
    /* 0 */ ENIN_UNK_TYPE,
    /* 1 */ ENIN_HORSE_RIDER_YELLOW_SHIRT,
    /* 2 */ ENIN_HORSE_RIDER_BLUE_SHIRT,
    /* 3 */ ENIN_YELLOW_SHIRT,
    /* 4 */ ENIN_BLUE_SHIRT
} EnInType;

#define ENIN_GET_TYPE(thisx) ((thisx)->params & 0x1FF)
#define ENIN_GET_PATH(thisx) (((thisx)->params & 0x7E00) >> 9) // Only used with ENIN_UNK_TYPE

typedef struct EnIn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnInActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderJntSph colliderJntSph;
    /* 0x1AC */ ColliderJntSphElement colliderJntSphElement;
    /* 0x1EC */ ColliderCylinder colliderCylinder;
    /* 0x238 */ char unk238[0x4];
    /* 0x23C */ u8 unk23C;
    /* 0x23D */ u8 unk23D;
    /* 0x240 */ Path* path;
    /* 0x244 */ s16 unk244;
    /* 0x248 */ Vec3f unk248;
    /* 0x254 */ Vec3f unk254;
    /* 0x260 */ u8 unk260;
    /* 0x261 */ u8 unk261;
    /* 0x262 */ Vec3s jointTable[20];
    /* 0x2DA */ Vec3s morphTable[20];
    /* 0x352 */ Vec3s trackTarget;
    /* 0x358 */ Vec3s headRot;
    /* 0x35E */ Vec3s torsoRot;
    /* 0x364 */ char unk364[0x12];
    /* 0x376 */ s16 unk376[20];
    /* 0x39E */ s16 unk39E[20];
    /* 0x3C6 */ char unk3C6[0xBC];
    /* 0x482 */ s16 unk482;
    /* 0x484 */ s16 unk484;
    /* 0x486 */ s16 unk486;
    /* 0x488 */ s16 unk488;
    /* 0x48A */ u16 unk48A;
    /* 0x48C */ s32 unk48C;
    /* 0x490 */ char unk490[0x4];
    /* 0x494 */ s32 unk494;
    /* 0x498 */ char unk498[0xC];
    /* 0x4A4 */ struct EnIn* unk4A4;
    /* 0x4A8 */ s32 unk4A8;
    /* 0x4AC */ s32 unk4AC;
    /* 0x4B0 */ s32 unk4B0;
    /* 0x4B4 */ Vec3f unk4B4;
    /* 0x4C0 */ f32 unk4C0;
    /* 0x4C0 */ f32 unk4C4;
    /* 0x4C0 */ s32 prevTalkState;
} EnIn; // size = 0x4CC

extern const ActorInit En_In_InitVars;

#endif // Z_EN_IN_H
