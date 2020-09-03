#ifndef _Z_EN_ESTONE_H_
#define _Z_EN_ESTONE_H_

#include <global.h>

struct EnEstone;

typedef struct EnEstone {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x2C30];
} EnEstone; // size = 0x2D74

extern const ActorInit En_Estone_InitVars;

#endif
