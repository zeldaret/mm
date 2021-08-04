#ifndef Z_EN_KAKASI_H
#define Z_EN_KAKASI_H

#include "global.h"

struct EnKakasi;

typedef void (*EnKakasiActionFunc)(struct EnKakasi* this, GlobalContext* globalCtx);

typedef struct EnKakasi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4];
    /* 0x0148 */ EnKakasiActionFunc actionFunc;
    /* 0x014C */ char unk_14C[0x154];
} EnKakasi; // size = 0x2A0

extern const ActorInit En_Kakasi_InitVars;

#endif // Z_EN_KAKASI_H
