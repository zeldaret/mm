#ifndef Z_EN_GM_H
#define Z_EN_GM_H

#include "global.h"

struct EnGm;

typedef void (*EnGmActionFunc)(struct EnGm*, GlobalContext*);

typedef struct EnGm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnGmActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x278];
} EnGm; // size = 0x404

extern const ActorInit En_Gm_InitVars;

#endif // Z_EN_GM_H
