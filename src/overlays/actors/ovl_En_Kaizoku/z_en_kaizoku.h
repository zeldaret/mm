#ifndef Z_EN_KAIZOKU_H
#define Z_EN_KAIZOKU_H

#include "global.h"

struct EnKaizoku;

typedef void (*EnKaizokuActionFunc)(struct EnKaizoku*, GlobalContext*);

typedef struct EnKaizoku {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x168];
    /* 0x02AC */ EnKaizokuActionFunc actionFunc;
    /* 0x02B0 */ char unk_2B0[0x40];
    /* 0x02F0 */ f32 unk_2F0;
    /* 0x02F4 */ s16 unk_2F4;
    /* 0x02F6 */ char unk_2F6[0x2FA];
} EnKaizoku; // size = 0x5F0

extern const ActorInit En_Kaizoku_InitVars;

#endif // Z_EN_KAIZOKU_H
