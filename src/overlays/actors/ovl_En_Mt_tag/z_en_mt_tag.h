#ifndef Z_EN_MT_TAG_H
#define Z_EN_MT_TAG_H

#include "global.h"

struct EnMttag;

typedef void (*EnMttagActionFunc)(struct EnMttag* this, GlobalContext* globalCtx);

typedef struct EnMttag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMttagActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x20];
} EnMttag; // size = 0x168

extern const ActorInit En_Mt_tag_InitVars;

#endif // Z_EN_MT_TAG_H
