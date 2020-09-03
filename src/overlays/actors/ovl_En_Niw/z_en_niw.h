#ifndef Z_EN_NIW_H
#define Z_EN_NIW_H

#include <global.h>

struct EnNiw;

typedef struct EnNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x678];
} EnNiw; // size = 0x7BC

extern const ActorInit En_Niw_InitVars;

#endif // Z_EN_NIW_H
