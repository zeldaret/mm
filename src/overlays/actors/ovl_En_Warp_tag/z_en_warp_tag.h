#ifndef Z_EN_WARP_TAG_H
#define Z_EN_WARP_TAG_H

#include "global.h"

struct EnWarptag;

typedef void (*EnWarptagActionFunc)(struct EnWarptag*, GlobalContext*);

typedef struct EnWarptag {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s8 dangeonKeepObject;
    /* 0x15E */ union {
                    s16 reusedValue;      // default name
                    s16 unkValue15E;      // passed to unk play func, mods player rotation, stepped to 0x2710
                    s16 grottoExitDelay;  // 10 frame delay before player can leave the grotto
                };
    /* 0x160 */ EnWarptagActionFunc actionFunc;
} EnWarptag; // size = 0x164

extern const ActorInit En_Warp_tag_InitVars;

#endif // Z_EN_WARP_TAG_H
