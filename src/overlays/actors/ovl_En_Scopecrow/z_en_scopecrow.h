#ifndef Z_EN_SCOPECROW_H
#define Z_EN_SCOPECROW_H

#include "global.h"

struct EnScopecrow;

typedef struct EnScopecrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x124];
} EnScopecrow; // size = 0x268

extern const ActorInit En_Scopecrow_InitVars;

#endif // Z_EN_SCOPECROW_H
