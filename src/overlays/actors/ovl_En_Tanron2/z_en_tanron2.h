#ifndef Z_EN_TANRON2_H
#define Z_EN_TANRON2_H

#include <global.h>

struct EnTanron2;

typedef struct EnTanron2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xB8];
} EnTanron2; // size = 0x1FC

extern const ActorInit En_Tanron2_InitVars;

#endif // Z_EN_TANRON2_H
