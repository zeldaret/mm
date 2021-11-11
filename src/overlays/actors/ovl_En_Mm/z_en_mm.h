#ifndef Z_EN_MM_H
#define Z_EN_MM_H

#include "global.h"

struct EnMm;

typedef void (*EnMmActionFunc)(struct EnMm*, GlobalContext*);

typedef struct EnMm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ s16 unk_190;
    /* 0x0194 */ EnMmActionFunc actionFunc;
} EnMm; // size = 0x198

//extern const ActorInit En_Mm_InitVars;

#endif // Z_EN_MM_H
