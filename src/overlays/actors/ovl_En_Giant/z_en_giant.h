#ifndef Z_EN_GIANT_H
#define Z_EN_GIANT_H

#include <global.h>

struct EnGiant;

typedef struct EnGiant {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif // Z_EN_GIANT_H
