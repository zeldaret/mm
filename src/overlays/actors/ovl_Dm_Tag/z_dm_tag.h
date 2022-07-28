#ifndef Z_DM_TAG_H
#define Z_DM_TAG_H

#include "global.h"

struct DmTag;

typedef void (*DmTagActionFunc)(struct DmTag*, PlayState*);

typedef struct DmTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ DmTagActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x20];
} DmTag; // size = 0x1AC

extern const ActorInit Dm_Tag_InitVars;

#endif // Z_DM_TAG_H
