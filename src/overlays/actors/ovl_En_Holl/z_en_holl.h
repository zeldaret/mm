#ifndef Z_EN_HOLL_H
#define Z_EN_HOLL_H

#include "global.h"

struct EnHoll;

typedef void (*EnHollActionFunc)(struct EnHoll* this, GlobalContext* globalCtx);

typedef enum {
    /* 0 */ EN_HOLL_HORIZONTAL_VISIBLE,
    /* 1 */ EN_HOLL_VERTICAL_A,
    /* 2 */ EN_HOLL_HORIZONTAL,
    /* 3 */ EN_HOLL_VERTICAL_B,
    /* 4 */ EN_HOLL_HORIZONTAL_VISIBLE_SCENE_CHANGER
} EnHollTypes;

typedef enum {
    /* 0x00 */ EN_HOLL_INVISIBLE,
    /* 0xFF */ EN_HOLL_OPAQUE = 0xFF
} EnHollOpacities;

typedef enum {
    /* 0 */ EN_HOLL_PLAYER_BEHIND,
    /* 1 */ EN_HOLL_PLAYER_NOT_BEHIND
} EnHollPlayerSide;

typedef struct EnHoll {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s8 type;
    /* 0x145 */ u8 opacity;
    /* 0x146 */ u8 playerSide;
    /* 0x147 */ UNK_TYPE1 alwaysZero;
    /* 0x148 */ EnHollActionFunc actionFunc;
} EnHoll; // size = 0x14C

#define GET_HOLL_TYPE(this) ((this->actor.params >> 7) & 7)
#define IS_HOLL_TYPE_VISIBLE(this) ((this->type == EN_HOLL_HORIZONTAL_VISIBLE) || (this->type == EN_HOLL_HORIZONTAL_VISIBLE_SCENE_CHANGER))
#define IS_HOLL_TYPE_SCENE_CHANGER(this) (this->type == 4)

extern const ActorInit En_Holl_InitVars;

#endif // Z_EN_HOLL_H
