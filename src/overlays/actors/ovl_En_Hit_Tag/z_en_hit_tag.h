#ifndef Z_EN_HIT_TAG_H
#define Z_EN_HIT_TAG_H

#include "global.h"

struct EnHitTag;

typedef void (*EnHitTagActionFunc)(struct EnHitTag*, GlobalContext*);

typedef struct EnHitTag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ EnHitTagActionFunc actionFunc;
} EnHitTag; // size = 0x194

extern const ActorInit En_Hit_Tag_InitVars;

#endif // Z_EN_HIT_TAG_H
