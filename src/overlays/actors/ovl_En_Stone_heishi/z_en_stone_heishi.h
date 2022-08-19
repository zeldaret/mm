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
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 textIndex;
    /* 0x274 */ s16 unk274; // Message related
    /* 0x276 */ u8 bottleDisplay;
    /* 0x277 */ u8 playerGivesBluePotion;
    /* 0x278 */ ColliderCylinder collider;
} EnStoneheishi; // size = 0x2C4

typedef enum EN_STONE_HEISHI_BOTTLE {
    /* 0 */ BOTTLE_NONE,
    /* 1 */ BOTTLE_RED_POTION,
    /* 2 */ BOTTLE_EMPTY,
    /* 3 */ BOTTLE_BLUE_POTION,
} EN_STONE_HEISHI_BOTTLE;

typedef enum EN_STONE_HEISHI_ANIMATIONS {
    /* 0 */ SOLDIER_STAND_HAND_ON_HIP,
    /* 1 */ SOLDIER_DRINK_1,
    /* 2 */ SOLDIER_CHEER_WITH_SPEAR,
    /* 3 */ SOLDIER_WAVE,
    /* 4 */ SOLDIER_SIT_AND_REACH,
    /* 5 */ SOLDIER_DRINK_2,
    /* 6 */ SOLDIER_STAND_UP,
} EN_STONE_HEISHI_ANIMATIONS;

extern const ActorInit En_Stone_heishi_InitVars;

#endif // Z_EN_STONE_HEISHI_H
