#ifndef Z_EN_MT_TAG_H
#define Z_EN_MT_TAG_H

#include <global.h>

struct EnMttag;

typedef struct EnMttag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} EnMttag; // size = 0x168

extern const ActorInit En_Mt_tag_InitVars;

#endif // Z_EN_MT_TAG_H
