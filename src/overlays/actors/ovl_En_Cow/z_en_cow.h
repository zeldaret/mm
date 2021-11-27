#ifndef Z_EN_COW_H
#define Z_EN_COW_H

#include "global.h"

struct EnCow;

typedef void (*EnCowActionFunc)(struct EnCow*, GlobalContext*);

typedef struct EnCow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x130];
    /* 0x0274 */ EnCowActionFunc actionFunc;
} EnCow; // size = 0x278

extern const ActorInit En_Cow_InitVars;

#endif // Z_EN_COW_H
