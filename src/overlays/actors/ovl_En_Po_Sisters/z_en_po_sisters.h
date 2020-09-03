#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include <global.h>

struct EnPoSisters;

typedef struct EnPoSisters {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x254];
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
