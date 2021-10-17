#ifndef Z_DM_TAG_H
#define Z_DM_TAG_H

#include <global.h>

struct DmTag;

typedef struct DmTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x68];
} DmTag; // size = 0x1AC

extern const ActorInit Dm_Tag_InitVars;

#endif // Z_DM_TAG_H
