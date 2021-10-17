#ifndef Z_EN_WARP_TAG_H
#define Z_EN_WARP_TAG_H

#include <global.h>

struct EnWarptag;

typedef struct EnWarptag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} EnWarptag; // size = 0x164

extern const ActorInit En_Warp_tag_InitVars;

#endif // Z_EN_WARP_TAG_H
