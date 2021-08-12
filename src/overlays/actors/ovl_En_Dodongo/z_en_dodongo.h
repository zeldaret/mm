#ifndef Z_EN_DODONGO_H
#define Z_EN_DODONGO_H

#include "global.h"

struct EnDodongo;

typedef void (*EnDodongoActionFunc)(struct EnDodongo*, GlobalContext*);

typedef struct EnDodongo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1B8];
    /* 0x02FC */ EnDodongoActionFunc actionFunc;
    /* 0x0300 */ char unk_300[0x514];
} EnDodongo; // size = 0x814

extern const ActorInit En_Dodongo_InitVars;

#endif // Z_EN_DODONGO_H
