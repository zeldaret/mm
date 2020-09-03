#ifndef Z_EN_TIME_TAG_H
#define Z_EN_TIME_TAG_H

#include <global.h>

struct EnTimeTag;

typedef struct EnTimeTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} EnTimeTag; // size = 0x148

extern const ActorInit En_Time_Tag_InitVars;

#endif // Z_EN_TIME_TAG_H
