#ifndef Z_BG_UMAJUMP_H
#define Z_BG_UMAJUMP_H

#include "global.h"

#define BG_UMAJUMP_GET_OBJECT_INDEX(thisx) (((thisx)->params >> 8) & 0xFF)

struct BgUmajump;

typedef void (*BgUmajumpActionFunc)(struct BgUmajump*, PlayState*);

typedef struct BgUmajump {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgUmajumpActionFunc actionFunc;
    /* 0x160 */ s32 objectIndex;
    /* 0x164 */ s32 hasSoundPlayed;
    /* 0x168 */ Actor* horse;
} BgUmajump; // size = 0x16C

extern const ActorInit Bg_Umajump_InitVars;

#endif // Z_BG_UMAJUMP_H
