#ifndef Z_EN_ESTONE_H
#define Z_EN_ESTONE_H

#include <global.h>

struct EnEstone;

typedef struct EnEstone {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x2C30];
} EnEstone; // size = 0x2D74

extern const ActorInit En_Estone_InitVars;

#endif // Z_EN_ESTONE_H
