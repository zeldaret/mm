#ifndef Z_EN_JSO_H
#define Z_EN_JSO_H

#include "global.h"

struct EnJso;

typedef void (*EnJsoActionFunc)(struct EnJso*, PlayState*);

typedef struct EnJso {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x134];
    /* 0x278 */ EnJsoActionFunc actionFunc;
    /* 0x27C */ char unk_27C[0xD70];
} EnJso; // size = 0xFEC

extern const ActorInit En_Jso_InitVars;

#endif // Z_EN_JSO_H
