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
    /* 1 */ EN_TALK_GIBUD_GRAB_IN_PROGRESS,
    /* 2 */ EN_TALK_GIBUD_GRAB_RELEASE,
} EnTalkGibudGrabState;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_REQUESTED_ITEM_MET,
    /* 1 */ EN_TALK_GIBUD_REQUESTED_ITEM_NOT_ENOUGH_AMMO,
    /* 2 */ EN_TALK_GIBUD_REQUESTED_ITEM_NOT_MET,
} EnTalkGibudRequestedItemState;

struct EnTalkGibud;

typedef void (*EnTalkGibudActionFunc)(struct EnTalkGibud*, GlobalContext*);

typedef struct EnTalkGibud {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnTalkGibudActionFunc actionFunc;
    /* 0x01D8 */ Vec3f limbPos[15];
    /* 0x028C */ s32 limbIndex;
    /* 0x0290 */ s32 requestedItemIndex;
    /* 0x0294 */ s32 itemActionParam;
    /* 0x0298 */ s32 switchFlag;
    /* 0x029C */ f32 effectAlpha;
    /* 0x02A0 */ f32 effectScale;
    /* 0x02A4 */ Vec3s jointTable[26];
    /* 0x0340 */ Vec3s morphTable[26];
    /* 0x03DC */ s16 textId;
    /* 0x03DE */ Vec3s headRotation;
    /* 0x03E4 */ Vec3s upperBodyRotation;
    /* 0x03EA */ s16 unk_3EA;
    /* 0x03EC */ s16 grabState;
    /* 0x03EE */ s16 unk_3EE;
    /* 0x03F0 */ s16 effectTimer;
    /* 0x03F2 */ s16 type;
    /* 0x03F4 */ s16 isTalking;
    /* 0x03F6 */ u8 effectType;
    /* 0x03F7 */ s8 unk_3F7;
} EnTalkGibud; // size = 0x3F8

extern const ActorInit En_Talk_Gibud_InitVars;

#endif // Z_EN_TALK_GIBUD_H
