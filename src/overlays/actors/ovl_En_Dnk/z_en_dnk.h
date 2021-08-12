#ifndef Z_EN_DNK_H
#define Z_EN_DNK_H

#include "global.h"

struct EnDnk;

typedef void (*EnDnkActionFunc)(struct EnDnk*, GlobalContext*);

typedef struct EnDnk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDnkActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x118];
} EnDnk; // size = 0x2A4

extern const ActorInit En_Dnk_InitVars;

#endif // Z_EN_DNK_H
