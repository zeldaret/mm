#ifndef Z_EN_HIT_TAG_H
#define Z_EN_HIT_TAG_H

#include "global.h"

struct EnHitTag;

typedef struct EnHitTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} EnHitTag; // size = 0x194

extern const ActorInit En_Hit_Tag_InitVars;

#endif // Z_EN_HIT_TAG_H
