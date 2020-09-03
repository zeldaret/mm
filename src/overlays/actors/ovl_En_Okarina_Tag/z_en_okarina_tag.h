#ifndef _Z_EN_OKARINA_TAG_H_
#define _Z_EN_OKARINA_TAG_H_

#include <global.h>

struct EnOkarinaTag;

typedef struct EnOkarinaTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} EnOkarinaTag; // size = 0x15C

extern const ActorInit En_Okarina_Tag_InitVars;

#endif
