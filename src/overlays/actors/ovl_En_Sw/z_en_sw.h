#ifndef Z_EN_SW_H
#define Z_EN_SW_H

#include <global.h>

struct EnSw;

typedef struct EnSw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x360];
} EnSw; // size = 0x4A4

extern const ActorInit En_Sw_InitVars;

#endif // Z_EN_SW_H
