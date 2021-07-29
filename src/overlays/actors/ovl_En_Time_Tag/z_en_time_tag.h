#ifndef Z_EN_TIME_TAG_H
#define Z_EN_TIME_TAG_H

#include "global.h"

struct EnTimeTag;

typedef void (*EnTimeTagActionFunc)(struct EnTimeTag* this, GlobalContext* globalCtx);

typedef struct EnTimeTag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTimeTagActionFunc actionFunc;
} EnTimeTag; // size = 0x148

extern const ActorInit En_Time_Tag_InitVars;

#endif // Z_EN_TIME_TAG_H
