#ifndef Z_EN_OKARINA_TAG_H
#define Z_EN_OKARINA_TAG_H

#include "global.h"

struct EnOkarinaTag;

typedef void (*EnOkarinaTagActionFunc)(struct EnOkarinaTag*, PlayState*);

typedef struct EnOkarinaTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnOkarinaTagActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x14];
} EnOkarinaTag; // size = 0x15C

extern const ActorInit En_Okarina_Tag_InitVars;

#endif // Z_EN_OKARINA_TAG_H
