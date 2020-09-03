#ifndef _Z_EN_MUTO_H_
#define _Z_EN_MUTO_H_

#include <global.h>

struct EnMuto;

typedef struct EnMuto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x19C];
} EnMuto; // size = 0x2E0

extern const ActorInit En_Muto_InitVars;

#endif
