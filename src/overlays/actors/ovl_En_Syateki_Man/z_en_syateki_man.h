#ifndef Z_EN_SYATEKI_MAN_H
#define Z_EN_SYATEKI_MAN_H

#include "global.h"

struct EnSyatekiMan;

typedef void (*EnSyatekiManActionFunc)(struct EnSyatekiMan* this, GlobalContext* globalCtx);

typedef struct EnSyatekiMan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnSyatekiManActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0xFC];
} EnSyatekiMan; // size = 0x288

extern const ActorInit En_Syateki_Man_InitVars;

#endif // Z_EN_SYATEKI_MAN_H
