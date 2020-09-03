#ifndef _Z_EN_COW_H_
#define _Z_EN_COW_H_

#include <global.h>

struct EnCow;

typedef struct EnCow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x134];
} EnCow; // size = 0x278

extern const ActorInit En_Cow_InitVars;

#endif
