#ifndef Z_EN_IN_H
#define Z_EN_IN_H

#include <global.h>

struct EnIn;

typedef struct EnIn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x388];
} EnIn; // size = 0x4CC

extern const ActorInit En_In_InitVars;

#endif // Z_EN_IN_H
