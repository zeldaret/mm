#ifndef Z_EN_SC_RUPPE_H
#define Z_EN_SC_RUPPE_H

#include "global.h"

#define SCRUPPE_GET_PARAMS(thisx) ((thisx)->params & 0x1F)

struct EnScRuppe;

typedef void (*EnScRuppeActionFunc)(struct EnScRuppe*, GlobalContext*);

typedef struct EnScRuppe {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ EnScRuppeActionFunc actionFunc;
    /* 0x194 */ s16 rupeeDisplayTime;
    /* 0x196 */ s16 rupeeIndex;
} EnScRuppe; // size = 0x198

extern const ActorInit En_Sc_Ruppe_InitVars;

#endif // Z_EN_SC_RUPPE_H
