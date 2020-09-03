#ifndef _Z_EN_AOB_01_H_
#define _Z_EN_AOB_01_H_

#include <global.h>

struct EnAob01;

typedef struct EnAob01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x300];
} EnAob01; // size = 0x444

extern const ActorInit En_Aob_01_InitVars;

#endif
