#ifndef Z_EN_HORSE_LINK_CHILD_H
#define Z_EN_HORSE_LINK_CHILD_H

#include "global.h"
#include "z64skin.h"

struct EnHorseLinkChild;

typedef struct EnHorseLinkChild {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
} EnHorseLinkChild; // size = 0x29C

extern const ActorInit En_Horse_Link_Child_InitVars;

#endif // Z_EN_HORSE_LINK_CHILD_H
