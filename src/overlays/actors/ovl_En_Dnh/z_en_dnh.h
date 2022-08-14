#ifndef Z_EN_DNH_H
#define Z_EN_DNH_H

#include "global.h"

struct EnDnh;

typedef void (*EnDnhActionFunc)(struct EnDnh*, PlayState*);

typedef struct EnDnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDnhActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x74];
} EnDnh; // size = 0x1BC

extern const ActorInit En_Dnh_InitVars;

#endif // Z_EN_DNH_H
