#ifndef Z_EN_HANABI_H
#define Z_EN_HANABI_H

#include "global.h"

struct EnHanabi;

typedef void (*EnHanabiActionFunc)(struct EnHanabi* this, GlobalContext* globalCtx);

typedef struct EnHanabi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4510];
    /* 0x4654 */ EnHanabiActionFunc actionFunc;
} EnHanabi; // size = 0x4658

extern const ActorInit En_Hanabi_InitVars;

#endif // Z_EN_HANABI_H
