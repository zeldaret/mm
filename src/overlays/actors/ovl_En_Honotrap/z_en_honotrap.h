#ifndef Z_EN_HONOTRAP_H
#define Z_EN_HONOTRAP_H

#include "global.h"

struct EnHonotrap;

typedef void (*EnHonotrapActionFunc)(struct EnHonotrap*, PlayState*);

typedef struct EnHonotrap {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnHonotrapActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x17C];
} EnHonotrap; // size = 0x2C4

extern const ActorInit En_Honotrap_InitVars;

#endif // Z_EN_HONOTRAP_H
