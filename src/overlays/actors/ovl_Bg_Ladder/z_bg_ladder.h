#ifndef Z_BG_LADDER_H
#define Z_BG_LADDER_H

#include <global.h>

#define GET_BGLADDER_SIZE(actor) ((actor)->params & 0xFF)
#define GET_BGLADDER_SWITCHFLAG(actor) (((actor)->params >> 8) & 0xFF)

struct BgLadder;

typedef void (*BgLadderActionFn)(struct BgLadder*, GlobalContext*);

typedef struct BgLadder {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgLadderActionFn action;
    /* 0x160 */ s16 alpha;
    /* 0x162 */ s16 switchFlag;
} BgLadder; // size = 0x164

typedef enum {
    LADDER_SIZE_12RUNG,
    LADDER_SIZE_16RUNG,
    LADDER_SIZE_20RUNG,
    LADDER_SIZE_24RUNG,
} BgLadderSize;

extern const ActorInit Bg_Ladder_InitVars;

#endif // Z_BG_LADDER_H
