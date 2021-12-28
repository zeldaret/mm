#ifndef Z_EN_TALK_GIBUD_H
#define Z_EN_TALK_GIBUD_H

#include "global.h"
#include "overlays/actors/ovl_En_Rd/z_en_rd.h"

#define EN_TALK_GIBUD_REQUESTED_ITEM_INDEX(thisx) ((thisx)->params & 0xF)
#define EN_TALK_GIBUD_SWITCH_FLAG(thisx) (((thisx)->params & 0xFF0) >> 4)

typedef enum {
    /* 0 */ EN_TALK_GIBUD_TYPE_GIBDO,
    /* 1 */ EN_TALK_GIBUD_TYPE_REDEAD,
} EnTalkGibudType;

typedef enum {
    /* 0 */ EN_TALK_GIBUD_GRAB_START,
    /* 1 */ EN_TALK_GIBUD_GRAB_ATTACK,
    /* 2 */ EN_TALK_GIBUD_GRAB_RELEASE,
} EnTalkGibudGrabState;

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
    /* 0x2A4 */ Vec3s jointTable[REDEAD_GIBDO_LIMB_MAX];
    /* 0x340 */ Vec3s morphTable[REDEAD_GIBDO_LIMB_MAX];
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
