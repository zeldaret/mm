#ifndef Z_EN_KAIZOKU_H
#define Z_EN_KAIZOKU_H

#include "global.h"

struct EnKaizoku;

typedef void (*EnKaizokuActionFunc)(struct EnKaizoku*, PlayState*);

typedef struct EnKaizoku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x168];
    /* 0x2AC */ EnKaizokuActionFunc actionFunc;
    /* 0x2B0 */ char unk_2B0[0x40];
    /* 0x2F0 */ f32 unk_2F0;
    /* 0x2F4 */ s16 unk_2F4;
    /* 0x2F6 */ char unk_2F6[0x2FA];
} EnKaizoku; // size = 0x5F0

extern const ActorInit En_Kaizoku_InitVars;

#endif // Z_EN_KAIZOKU_H
