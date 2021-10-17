#ifndef Z_EN_DNQ_H
#define Z_EN_DNQ_H

#include <global.h>

struct EnDnq;

typedef struct EnDnq {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x264];
} EnDnq; // size = 0x3A8

extern const ActorInit En_Dnq_InitVars;

#endif // Z_EN_DNQ_H
