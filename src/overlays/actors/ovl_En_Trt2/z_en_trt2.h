#ifndef Z_EN_TRT2_H
#define Z_EN_TRT2_H

#include <global.h>

struct EnTrt2;

typedef struct EnTrt2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x298];
} EnTrt2; // size = 0x3DC

extern const ActorInit En_Trt2_InitVars;

#endif // Z_EN_TRT2_H
