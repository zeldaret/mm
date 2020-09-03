#ifndef _Z_EN_OT_H_
#define _Z_EN_OT_H_

#include <global.h>

struct EnOt;

typedef struct EnOt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x614];
} EnOt; // size = 0x758

extern const ActorInit En_Ot_InitVars;

#endif
