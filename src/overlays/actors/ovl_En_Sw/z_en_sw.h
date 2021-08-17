#ifndef Z_EN_SW_H
#define Z_EN_SW_H

#include "global.h"

struct EnSw;

typedef void (*EnSwActionFunc)(struct EnSw*, GlobalContext*);

typedef struct EnSw {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnSwActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x318];
} EnSw; // size = 0x4A4

extern const ActorInit En_Sw_InitVars;

#endif // Z_EN_SW_H
