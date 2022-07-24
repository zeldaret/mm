#ifndef Z_EN_INVISIBLE_RUPPE_H
#define Z_EN_INVISIBLE_RUPPE_H

#include "global.h"

struct EnInvisibleRuppe;

typedef void (*EnInvisibleRuppeActionFunc)(struct EnInvisibleRuppe*, PlayState*);

#define INVISIBLERUPPE_GET_3(thisx) ((thisx)->actor.params & 3)
#define INVISIBLERUPPE_GET_1FC(thisx) (((thisx)->actor.params & 0x1FC) >> 2)

typedef struct EnInvisibleRuppe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ s16 unk_190;
    /* 0x192 */ s16 unk_192;
    /* 0x194 */ EnInvisibleRuppeActionFunc actionFunc;
} EnInvisibleRuppe; // size = 0x198

extern const ActorInit En_Invisible_Ruppe_InitVars;

#endif // Z_EN_INVISIBLE_RUPPE_H
