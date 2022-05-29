#ifndef Z_EN_RD_H
#define Z_EN_RD_H

#include "global.h"
#include "objects/object_rd/object_rd.h"

struct EnRd;

typedef void (*EnRdActionFunc)(struct EnRd*, GlobalContext*);
typedef void (*EnRdSetupDanceFunc)(struct EnRd*);

#define EN_RD_GET_80(thisx) ((thisx)->params & 0x80)
#define EN_RD_GET_FLAGS(thisx) (((thisx)->params & 0xFF00) >> 8)
#define EN_RD_GET_TYPE(thisx) ((thisx)->params)
#define EN_RD_GET_SWITCH_FLAG(this) ((this)->flags & 0x7F)

#define EN_RD_FLAG_CANNOT_FREEZE_PLAYER (1 << 7)

typedef enum {
    /* -3 */ EN_RD_TYPE_GIBDO_RISING_OUT_OF_COFFIN = -3, // Unused OoT leftover
    /* -2 */ EN_RD_TYPE_GIBDO = -2, // Unused OoT leftover
    /* -1 */ EN_RD_TYPE_DOES_NOT_MOURN = -1, // Unused OoT leftover
    /*  0 */ EN_RD_TYPE_DOES_NOT_MOURN_IF_WALKING = 0, // Unused OoT leftover. Still mourns, but it must come to a complete stop first
    /*  1 */ EN_RD_TYPE_REGULAR, // Unused OoT leftover
    /*  2 */ EN_RD_TYPE_CRYING, // Unused in the final game
    /*  3 */ EN_RD_TYPE_INVISIBLE, // Unused OoT leftover
    /*  4 */ EN_RD_TYPE_FROZEN, // Unused in the final game
    /*  5 */ EN_RD_TYPE_SQUATTING_DANCE,
    /*  6 */ EN_RD_TYPE_CLAPPING_DANCE,
    /*  7 */ EN_RD_TYPE_PIROUETTE,
} EnRdType;

typedef struct EnRd {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnRdActionFunc actionFunc;
    /* 0x018C */ EnRdSetupDanceFunc setupDanceFunc;
    /* 0x0190 */ ColliderCylinder collider;
    /* 0x01DC */ Vec3f limbPos[15];
    /* 0x0290 */ s32 limbIndex;
    /* 0x0294 */ f32 drawDmgEffAlpha;
    /* 0x0298 */ f32 drawDmgEffScale;
    /* 0x029C */ Vec3s jointTable[REDEAD_LIMB_MAX];
    /* 0x0338 */ Vec3s morphTable[REDEAD_LIMB_MAX];
    /* 0x03D4 */ s16 headShakeTimer;
    /* 0x03D6 */ union {
                    s16 animationJudderTimer;
                    s16 stunTimer;
                    s16 deathTimer;
                    s16 coffinRiseForwardAccelTimer;
                };
    /* 0x03D8 */ s16 headYRotation;
    /* 0x03DA */ s16 upperBodyYRotation;
    /* 0x03DC */ s16 flags;
    /* 0x03DE */ s16 alpha;
    /* 0x03E0 */ s16 sunsSongStunTimer;
    /* 0x03E2 */ UNK_TYPE1 unk3E2[0x2];
    /* 0x03E4 */ union {
                    s16 danceEndTimer;
                    s16 pirouetteRotationalVelocity;
                };
    /* 0x03E6 */ s16 drawDmgEffTimer;
    /* 0x03E8 */ u8 drawDmgEffType;
    /* 0x03E9 */ u8 stunnedBySunsSong;
    /* 0x03EA */ u8 grabDamageTimer;
    /* 0x03EB */ u8 grabState;
    /* 0x03EC */ u8 isMourning;
    /* 0x03ED */ u8 playerStunWaitTimer; // Cannot stun the player if this is non-zero
    /* 0x03EE */ u8 grabWaitTimer; // Cannot grab the player if this is non-zero
    /* 0x03EF */ u8 action;
    /* 0x03F0 */ u8 damageEffect;
    /* 0x03F1 */ s8 unk_3F1; // related to player->unk_ADD
} EnRd; // size = 0x3F4

extern const ActorInit En_Rd_InitVars;

#endif // Z_EN_RD_H
