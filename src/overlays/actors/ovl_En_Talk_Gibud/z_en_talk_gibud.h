#ifndef Z_EN_TALK_GIBUD_H
#define Z_EN_TALK_GIBUD_H

#include "global.h"

#define EN_TALK_GIBUD_REQUESTED_ITEM_INDEX(thisx) ((thisx)->params & 0xF)
#define EN_TALK_GIBUD_SWITCH_FLAG(thisx) (((thisx)->params & 0xFF0) >> 4)

typedef enum {
    /*  0 */ EN_TALK_GIBUD_ANIMATION_GRAB_ATTACK,
    /*  1 */ EN_TALK_GIBUD_ANIMATION_GRAB_END,
    /*  2 */ EN_TALK_GIBUD_ANIMATION_GRAB_START,
    /*  3 */ EN_TALK_GIBUD_ANIMATION_LOOK_AWAY,
    /*  4 */ EN_TALK_GIBUD_ANIMATION_CROUCH_WIPING_TEARS,
    /*  5 */ EN_TALK_GIBUD_ANIMATION_CROUCH_CRYING,
    /*  6 */ EN_TALK_GIBUD_ANIMATION_DEATH,
    /*  7 */ EN_TALK_GIBUD_ANIMATION_DAMAGE,
    /*  8 */ EN_TALK_GIBUD_ANIMATION_CROUCH_END,
    /*  9 */ EN_TALK_GIBUD_ANIMATION_IDLE,
    /* 10 */ EN_TALK_GIBUD_ANIMATION_WALK,
    /* 11 */ EN_TALK_GIBUD_ANIMATION_DANCE_SQUAT,
    /* 12 */ EN_TALK_GIBUD_ANIMATION_DANCE_PIROUETTE,
    /* 13 */ EN_TALK_GIBUD_ANIMATION_DANCE_CLAP,
} EnTalkGibudAnimations;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_TYPE_GIBDO,
    /* 1 */ EN_TALK_GIBUD_TYPE_REDEAD,
} EnTalkGibudType;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_GRAB_START,
    /* 1 */ EN_TALK_GIBUD_GRAB_ATTACK,
    /* 2 */ EN_TALK_GIBUD_GRAB_RELEASE,
} EnTalkGibudGrabState;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_REQUESTED_ITEM_MET,
    /* 1 */ EN_TALK_GIBUD_REQUESTED_ITEM_NOT_ENOUGH_AMMO,
    /* 2 */ EN_TALK_GIBUD_REQUESTED_ITEM_NOT_MET,
} EnTalkGibudRequestedItemState;

typedef enum {
    /*  0 */ EN_TALK_GIBUD_LIMB_NONE,
    /*  1 */ EN_TALK_GIBUD_LIMB_ROOT,       // Root of Left Leg Root, Right Leg Root, Upper Body Root, and Pelvis
    /*  2 */ EN_TALK_GIBUD_LIMB_LEFT_LEG_ROOT,
    /*  3 */ EN_TALK_GIBUD_LIMB_LEFT_THIGH,
    /*  4 */ EN_TALK_GIBUD_LIMB_LEFT_LOWER_LEG,
    /*  5 */ EN_TALK_GIBUD_LIMB_LEFT_FOOT_ROOT,
    /*  6 */ EN_TALK_GIBUD_LIMB_LEFT_FOOT,
    /*  7 */ EN_TALK_GIBUD_LIMB_RIGHT_LEG_ROOT,
    /*  8 */ EN_TALK_GIBUD_LIMB_RIGHT_THIGH,
    /*  9 */ EN_TALK_GIBUD_LIMB_RIGHT_LOWER_LEG,
    /* 10 */ EN_TALK_GIBUD_LIMB_RIGHT_FOOT_ROOT,
    /* 11 */ EN_TALK_GIBUD_LIMB_RIGHT_FOOT,
    /* 12 */ EN_TALK_GIBUD_LIMB_UPPER_BODY_ROOT,
    /* 13 */ EN_TALK_GIBUD_LIMB_UPPER_BODY, // Root of Torso
    /* 14 */ EN_TALK_GIBUD_LIMB_TORSO,      // Root of Left Arm Root, Right Arm Root, and Head Root
    /* 15 */ EN_TALK_GIBUD_LIMB_LEFT_ARM_ROOT,
    /* 16 */ EN_TALK_GIBUD_LIMB_LEFT_SHOULDER_AND_UPPER_ARM,
    /* 17 */ EN_TALK_GIBUD_LIMB_LEFT_FOREARM,
    /* 18 */ EN_TALK_GIBUD_LIMB_LEFT_HAND,
    /* 19 */ EN_TALK_GIBUD_LIMB_RIGHT_ARM_ROOT,
    /* 20 */ EN_TALK_GIBUD_LIMB_RIGHT_SHOULDER_AND_UPPER_ARM,
    /* 21 */ EN_TALK_GIBUD_LIMB_RIGHT_FOREARM,
    /* 22 */ EN_TALK_GIBUD_LIMB_RIGHT_HAND,
    /* 23 */ EN_TALK_GIBUD_LIMB_HEAD_ROOT,
    /* 24 */ EN_TALK_GIBUD_LIMB_HEAD,
    /* 25 */ EN_TALK_GIBUD_LIMB_PELVIS,
    /* 26 */ EN_TALK_GIBUD_LIMB_MAX,
} EnTalkGibudLimbs;

typedef enum {
    /*  0 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BLUE_POTION,
    /*  1 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BEANS,
    /*  2 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_SPRING_WATER,
    /*  3 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_FISH,
    /*  4 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BUGS,
    /*  5 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_DEKU_NUTS,
    /*  6 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BOMBS,
    /*  7 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_HOT_SPRING_WATER,
    /*  8 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_BIG_POE,
    /*  9 */ EN_TALK_GIBUD_REQUESTED_ITEM_INDEX_MILK,
} EnTalkGibudRequestedItemIndex;

struct EnTalkGibud;

typedef void (*EnTalkGibudActionFunc)(struct EnTalkGibud*, GlobalContext*);

typedef struct EnTalkGibud {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnTalkGibudActionFunc actionFunc;
    /* 0x1D8 */ Vec3f limbPos[15];
    /* 0x28C */ s32 limbIndex;
    /* 0x290 */ s32 requestedItemIndex;
    /* 0x294 */ s32 itemActionParam;
    /* 0x298 */ s32 switchFlag;
    /* 0x29C */ f32 effectAlpha;
    /* 0x2A0 */ f32 effectScale;
    /* 0x2A4 */ Vec3s jointTable[EN_TALK_GIBUD_LIMB_MAX];
    /* 0x340 */ Vec3s morphTable[EN_TALK_GIBUD_LIMB_MAX];
    /* 0x3DC */ s16 textId;
    /* 0x3DE */ Vec3s headRotation;
    /* 0x3E4 */ Vec3s upperBodyRotation;
    /* 0x3EA */ union {
        s16 playerStunWaitTimer; // Cannot stun the player if this is non-zero
        s16 grabDamageTimer;
        s16 headShakeTimer;
        s16 stunTimer;
        s16 deathTimer;
        s16 disappearanceTimer;
    };
    /* 0x3EC */ s16 grabState;
    /* 0x3EE */ s16 grabWaitTimer; // Cannot grab the player if this is non-zero
    /* 0x3F0 */ s16 effectTimer;
    /* 0x3F2 */ s16 type;
    /* 0x3F4 */ s16 isTalking;
    /* 0x3F6 */ u8 effectType;
    /* 0x3F7 */ s8 unk_3F7; // related to player->unk_ADD
} EnTalkGibud; // size = 0x3F8

extern const ActorInit En_Talk_Gibud_InitVars;

#endif // Z_EN_TALK_GIBUD_H
