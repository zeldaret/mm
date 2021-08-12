#ifndef Z_EN_TK_H
#define Z_EN_TK_H

#include "global.h"

struct EnTk;

typedef void (*EnTkActionFunc)(struct EnTk*, GlobalContext*);

typedef struct EnTk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnTkActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x268];
} EnTk; // size = 0x3F4

extern const ActorInit En_Tk_InitVars;

#endif // Z_EN_TK_H
