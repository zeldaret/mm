#ifndef Z_EN_JSO2_H
#define Z_EN_JSO2_H

#include "global.h"

struct EnJso2;

typedef void (*EnJso2ActionFunc)(struct EnJso2* this, GlobalContext* globalCtx);

typedef struct EnJso2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x134];
    /* 0x0278 */ EnJso2ActionFunc actionFunc;
    /* 0x027C */ char unk_27C[0xE14];
} EnJso2; // size = 0x1090

extern const ActorInit En_Jso2_InitVars;

#endif // Z_EN_JSO2_H
