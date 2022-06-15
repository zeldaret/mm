#ifndef Z_EN_DNH_H
#define Z_EN_DNH_H

#include "global.h"

struct EnDnh;

typedef void (*EnDnhActionFunc)(struct EnDnh*, GlobalContext*);

typedef struct EnDnh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnDnhActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x74];
} EnDnh; // size = 0x1BC

extern const ActorInit En_Dnh_InitVars;

#endif // Z_EN_DNH_H
