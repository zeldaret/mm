#ifndef Z_EN_STONE_HEISHI_H
#define Z_EN_STONE_HEISHI_H

#include "global.h"
#include "assets/objects/object_sdn/object_sdn.h"

struct EnStoneheishi;

typedef void (*EnStoneheishiActionFunc)(struct EnStoneheishi*, PlayState*);

typedef struct EnStoneheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[SOLDIER_LIMB_MAX];
    /* 0x1EE */ Vec3s morphTable[SOLDIER_LIMB_MAX];
    /* 0x254 */ EnStoneheishiActionFunc actionFunc;
    /* 0x258 */ s16 headRotY;
    /* 0x25A */ s16 headRotX;
    /* 0x25C */ s16 headRotZ;
    /* 0x25E */ s16 targetHeadPosY;
    /* 0x260 */ s16 targetHeadPosX;
    /* 0x264 */ s32 animIndex;
    /* 0x268 */ s16 timer;
    /* 0x26A */ s16 DrinkBottleState;
    /* 0x26C */ f32 endFrame;
    /* 0x270 */ s16 action;
    /* 0x272 */ s16 textIdIndex;
    /* 0x274 */ s16 textIdSet;
    /* 0x276 */ u8 bottleDisplay;
    /* 0x277 */ u8 playerGivesBluePotion;
    /* 0x278 */ ColliderCylinder collider;
} EnStoneheishi; // size = 0x2C4

typedef enum EN_STONE_ACTION {
    /* 0 */ EN_STONE_ACTION_0,
    /* 1 */ EN_STONE_ACTION_1,
    /* 2 */ EN_STONE_ACTION_CHECK_ITEM,
    /* 3 */ EN_STONE_ACTION_DRINK_BOTTLE,
    /* 4 */ EN_STONE_ACTION_4
} EN_STONE_ACTION;

typedef enum EN_STONE_DRINK_BOTTLE {
    /* 0 */ EN_STONE_DRINK_BOTTLE_INITIAL,
    /* 1 */ EN_STONE_DRINK_BOTTLE_DRINKING,
    /* 2 */ EN_STONE_DRINK_BOTTLE_EMPTY,
    /* 3 */ EN_STONE_DRINK_BOTTLE_STAND_UP,
    /* 4 */ EN_STONE_DRINK_BOTTLE_STANDING
} EN_STONE_DRINK_BOTTLE;

typedef enum EN_STONE_HEISHI_BOTTLE {
    /* 0 */ EN_STONE_BOTTLE_NONE,
    /* 1 */ EN_STONE_BOTTLE_RED_POTION,
    /* 2 */ EN_STONE_BOTTLE_EMPTY,
    /* 3 */ EN_STONE_BOTTLE_BLUE_POTION,
} EN_STONE_HEISHI_BOTTLE;

typedef enum EN_STONE_HEISHI_ANIMATIONS {
    /* 0 */ EN_STONE_HEISHI_STAND_HAND_ON_HIP,
    /* 1 */ EN_STONE_HEISHI_DRINK_1,
    /* 2 */ EN_STONE_HEISHI_CHEER_WITH_SPEAR,
    /* 3 */ EN_STONE_HEISHI_WAVE,
    /* 4 */ EN_STONE_HEISHI_SIT_AND_REACH,
    /* 5 */ EN_STONE_HEISHI_DRINK_2,
    /* 6 */ EN_STONE_HEISHI_STAND_UP,
} EN_STONE_HEISHI_ANIMATIONS;

extern const ActorInit En_Stone_heishi_InitVars;

#endif // Z_EN_STONE_HEISHI_H
