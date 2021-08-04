#ifndef Z_EN_WIZ_H
#define Z_EN_WIZ_H

#include "global.h"

struct EnWiz;

typedef void (*EnWizActionFunc)(struct EnWiz* this, GlobalContext* globalCtx);

typedef struct EnWiz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x268];
    /* 0x03AC */ EnWizActionFunc actionFunc;
    /* 0x03B0 */ char unk_3B0[0x9D0];
} EnWiz; // size = 0xD80

extern const ActorInit En_Wiz_InitVars;

#endif // Z_EN_WIZ_H
