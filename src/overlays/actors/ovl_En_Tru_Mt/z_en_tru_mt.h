#ifndef Z_EN_TRU_MT_H
#define Z_EN_TRU_MT_H

#include "global.h"

struct EnTruMt;

typedef struct EnTruMt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x264];
} EnTruMt; // size = 0x3A8

extern const ActorInit En_Tru_Mt_InitVars;

#endif // Z_EN_TRU_MT_H
