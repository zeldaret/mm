#ifndef Z_BG_UMAJUMP_H
#define Z_BG_UMAJUMP_H

#include "global.h"

#define BG_UMAJUMP_GET_OBJECT_INDEX(thisx) (((thisx)->params >> 8) & 0xFF)

struct BgUmajump;

typedef void (*BgUmajumpActionFunc)(struct BgUmajump*, PlayState*);

typedef struct BgUmajump {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgUmajumpActionFunc actionFunc;
    /* 0x160 */ union {
                    s32 objectIndex;
                    s32 rotationTimer; // y rotation 
                };
    /* 0x164 */ s32 hasSoundPlayed;
    /* 0x168 */ Actor* horse;
} BgUmajump; // size = 0x16C

typedef enum {
    BG_UMAJUMP_PARAM_1 = 1,
    BG_UMAJUMP_PARAM_2,
    BG_UMAJUMP_PARAM_3,
    BG_UMAJUMP_PARAM_4,
    BG_UMAJUMP_PARAM_5,
    BG_UMAJUMP_PARAM_6,
} BgUmaJumpType;

extern const ActorInit Bg_Umajump_InitVars;

#endif // Z_BG_UMAJUMP_H
