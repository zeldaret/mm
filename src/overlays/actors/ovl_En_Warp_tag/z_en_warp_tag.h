#ifndef Z_EN_WARP_TAG_H
#define Z_EN_WARP_TAG_H

#include "global.h"

struct EnWarptag;

typedef void (*EnWarptagActionFunc)(struct EnWarptag*, GlobalContext*);

typedef struct EnWarptag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ EnWarptagActionFunc actionFunc;
} EnWarptag; // size = 0x164

extern const ActorInit En_Warp_tag_InitVars;

#endif // Z_EN_WARP_TAG_H
