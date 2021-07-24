#ifndef Z_EN_WF_H
#define Z_EN_WF_H

#include "global.h"

struct EnWf;

typedef struct EnWf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3A4];
} EnWf; // size = 0x4E8

extern const ActorInit En_Wf_InitVars;

#endif // Z_EN_WF_H
