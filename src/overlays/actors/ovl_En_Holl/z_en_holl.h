#ifndef Z_EN_HOLL_H
#define Z_EN_HOLL_H

#include "global.h"

struct EnHoll;

typedef void (*EnHollActionFunc)(struct EnHoll*, GlobalContext*);

typedef enum {
    /* 0 */ EN_HOLL_TYPE_DEFAULT,
    /* 1 */ EN_HOLL_TYPE_TRANSPARENT_VERTICAL_A,
    /* 2 */ EN_HOLL_TYPE_TRANSPARENT,
    /* 3 */ EN_HOLL_TYPE_TRANSPARENT_VERTICAL_B,
    /* 4 */ EN_HOLL_TYPE_SCENE_CHANGER
} EnHollTypes;

typedef enum {
    /* 0x00 */ EN_HOLL_TRANSPARENT,
    /* 0x01-FE EN_HOLL_TRANSLUCENT, */
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

#define EN_HOLL_BOTTOM_DEFAULT -50.0f
#define EN_HOLL_BOTTOM_IKANA -90.0f

#define EN_HOLL_TOP_DEFAULT 200.0f
#define EN_HOLL_TOP_PIRATE 280.0f

#define EN_HOLL_WIDTH_DEFAULT 150.0f 
#define EN_HOLL_WIDTH_IKANA 280.0f 

#define EN_HOLL_HEIGHT 200.0f
#define EN_HOLL_WIDTH 200.0f

#define EN_HOLL_GET_ID_AND(this) ((this->actor.params & 0xFFFF) >> 10)
#define EN_HOLL_GET_ID_CAST(this) ((u16) this->actor.params >> 10)
#define EN_HOLL_GET_TYPE(this) ((this->actor.params >> 7) & 0x7)
#define EN_HOLL_GET_EXIT_LIST_INDEX(this) (this->actor.params & 0x7F)
#define EN_HOLL_GET_Z_ACTOR_BITMASK_INDEX(this) (this->actor.params & 0x7)

#define EN_HOLL_IS_VISIBLE(this) ((this->type == EN_HOLL_TYPE_DEFAULT) || (this->type == EN_HOLL_TYPE_SCENE_CHANGER))
#define EN_HOLL_IS_SCENE_CHANGER(this) (this->type == EN_HOLL_TYPE_SCENE_CHANGER)

extern const ActorInit En_Holl_InitVars;

#endif // Z_EN_HOLL_H
