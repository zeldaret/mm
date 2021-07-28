#ifndef Z_EN_TK_H
#define Z_EN_TK_H

#include "global.h"

struct EnTk;

typedef struct EnTk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2B0];
} EnTk; // size = 0x3F4

extern const ActorInit En_Tk_InitVars;

#endif // Z_EN_TK_H
