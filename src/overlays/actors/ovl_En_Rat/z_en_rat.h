#ifndef Z_EN_RAT_H
#define Z_EN_RAT_H

#include <global.h>

struct EnRat;

typedef struct EnRat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x17C];
} EnRat; // size = 0x2C0

extern const ActorInit En_Rat_InitVars;

#endif // Z_EN_RAT_H
