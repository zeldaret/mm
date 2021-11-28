#ifndef Z_EN_HIT_TAG_H
#define Z_EN_HIT_TAG_H

#include "global.h"

struct EnHitTag;

typedef void (*EnHitTagActionFunc)(struct EnHitTag*, GlobalContext*);

#define ENHITTAG_GET_SWITCHFLAG(thisx) (s32)(thisx->actor.params & 0xFE00) >> 9)

typedef struct EnHitTag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder cylinder;
    /* 0x0190 */ EnHitTagActionFunc actionFunc;
} EnHitTag; // size = 0x194

extern const ActorInit En_Hit_Tag_InitVars;

#endif // Z_EN_HIT_TAG_H
