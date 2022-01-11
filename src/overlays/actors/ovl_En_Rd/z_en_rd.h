#ifndef Z_EN_RD_H
#define Z_EN_RD_H

#include "global.h"

struct EnRd;

typedef void (*EnRdActionFunc)(struct EnRd*, GlobalContext*);
typedef void (*EnRdFunc)(struct EnRd*);

#define ENRD_GET_80(thisx) ((thisx)->params & 0x80)
#define ENRD_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)
#define EN_RD_GET_TYPE(thisx) ((thisx)->params)

// This limb enum is used for both Redeads and Gibdos for all actors
// that use object_rd (i.e., En_Rd, En_Railgibud, and En_Talk_Gibud)
typedef enum {
    /*  0 */ REDEAD_GIBDO_LIMB_NONE,
    /*  1 */ REDEAD_GIBDO_LIMB_ROOT,       // Root of Left Leg Root, Right Leg Root, Upper Body Root, and Pelvis
    /*  2 */ REDEAD_GIBDO_LIMB_LEFT_LEG_ROOT,
    /*  3 */ REDEAD_GIBDO_LIMB_LEFT_THIGH,
    /*  4 */ REDEAD_GIBDO_LIMB_LEFT_LOWER_LEG,
    /*  5 */ REDEAD_GIBDO_LIMB_LEFT_FOOT_ROOT,
    /*  6 */ REDEAD_GIBDO_LIMB_LEFT_FOOT,
    /*  7 */ REDEAD_GIBDO_LIMB_RIGHT_LEG_ROOT,
    /*  8 */ REDEAD_GIBDO_LIMB_RIGHT_THIGH,
    /*  9 */ REDEAD_GIBDO_LIMB_RIGHT_LOWER_LEG,
    /* 10 */ REDEAD_GIBDO_LIMB_RIGHT_FOOT_ROOT,
    /* 11 */ REDEAD_GIBDO_LIMB_RIGHT_FOOT,
    /* 12 */ REDEAD_GIBDO_LIMB_UPPER_BODY_ROOT,
    /* 13 */ REDEAD_GIBDO_LIMB_UPPER_BODY, // Root of Torso
    /* 14 */ REDEAD_GIBDO_LIMB_TORSO,      // Root of Left Arm Root, Right Arm Root, and Head Root
    /* 15 */ REDEAD_GIBDO_LIMB_LEFT_ARM_ROOT,
    /* 16 */ REDEAD_GIBDO_LIMB_LEFT_SHOULDER_AND_UPPER_ARM,
    /* 17 */ REDEAD_GIBDO_LIMB_LEFT_FOREARM,
    /* 18 */ REDEAD_GIBDO_LIMB_LEFT_HAND,
    /* 19 */ REDEAD_GIBDO_LIMB_RIGHT_ARM_ROOT,
    /* 20 */ REDEAD_GIBDO_LIMB_RIGHT_SHOULDER_AND_UPPER_ARM,
    /* 21 */ REDEAD_GIBDO_LIMB_RIGHT_FOREARM,
    /* 22 */ REDEAD_GIBDO_LIMB_RIGHT_HAND,
    /* 23 */ REDEAD_GIBDO_LIMB_HEAD_ROOT,
    /* 24 */ REDEAD_GIBDO_LIMB_HEAD,
    /* 25 */ REDEAD_GIBDO_LIMB_PELVIS,
    /* 26 */ REDEAD_GIBDO_LIMB_MAX,
} RedeadGibdoLimbs;

typedef enum {
    /* -2 */ EN_RD_TYPE_GIBDO = -2,
    /* -1 */ EN_RD_TYPE_MINUS_1 = -1,
    /*  0 */ EN_RD_TYPE_0 = 0,
    /*  1 */ EN_RD_TYPE_1,
    /*  2 */ EN_RD_TYPE_CRYING,
    /*  3 */ EN_RD_TYPE_INVISIBLE,
    /*  4 */ EN_RD_TYPE_FROZEN,
    /*  5 */ EN_RD_TYPE_SQUATTING_DANCE,
    /*  6 */ EN_RD_TYPE_CLAPPING_DANCE,
    /*  7 */ EN_RD_TYPE_PIROUETTE,
} EnRdType;

typedef struct EnRd {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnRdActionFunc actionFunc;
    /* 0x018C */ EnRdFunc unkFunc;
    /* 0x0190 */ ColliderCylinder collider;
    /* 0x01DC */ Vec3f limbPos[15];
    /* 0x0290 */ s32 limbIndex;
    /* 0x0294 */ f32 effectAlpha;
    /* 0x0298 */ f32 effectScale;
    /* 0x029C */ Vec3s jointTable[REDEAD_GIBDO_LIMB_MAX];
    /* 0x0338 */ Vec3s morphTable[REDEAD_GIBDO_LIMB_MAX];
    /* 0x03D4 */ union {
                    s16 headShakeTimer;
                    s16 unk_3D4;
                };
    /* 0x03D6 */ union {
                    s16 stunTimer;
                    s16 unk_3D6;
                };
    /* 0x03D8 */ s16 headYRotation;
    /* 0x03DA */ s16 upperBodyYRotation;
    /* 0x03DC */ s16 unk_3DC;
    /* 0x03DE */ s16 alpha;
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ s16 unk_3E2;
    /* 0x03E4 */ s16 unk_3E4;
    /* 0x03E6 */ s16 effectTimer;
    /* 0x03E8 */ u8 effectType;
    /* 0x03E9 */ u8 unk_3E9;
    /* 0x03EA */ u8 unk_3EA;
    /* 0x03EB */ u8 unk_3EB;
    /* 0x03EC */ u8 unk_3EC;
    /* 0x03ED */ u8 unk_3ED;
    /* 0x03EE */ u8 unk_3EE;
    /* 0x03EF */ u8 unk_3EF;
    /* 0x03F0 */ u8 unk_3F0;
    /* 0x03F1 */ s8 unk_3F1;
} EnRd; // size = 0x3F4

extern const ActorInit En_Rd_InitVars;

#endif // Z_EN_RD_H
