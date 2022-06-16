#ifndef Z_EN_SC_RUPPE_H
#define Z_EN_SC_RUPPE_H

#include "global.h"

#define SCRUPPE_GET_TYPE(thisx) ((thisx)->params & 0x1F)

struct EnScRuppe;

typedef void (*EnScRuppeActionFunc)(struct EnScRuppe*, GlobalContext*);

typedef struct EnScRuppe {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ EnScRuppeActionFunc actionFunc;
    /* 0x194 */ s16 ruppeDisplayTime;
    /* 0x196 */ s16 ruppeIndex;
} EnScRuppe; // size = 0x198

typedef enum {
    /* 0 */ RUPPE_GREEN,
    /* 1 */ RUPPE_BLUE,
    /* 2 */ RUPPE_RED,
    /* 3 */ RUPPE_ORANGE,
    /* 4 */ RUPPE_PURPLE,
    /* 5 */ RUPPE_UNUSED,
} RupeeType;

extern const ActorInit En_Sc_Ruppe_InitVars;

#endif // Z_EN_SC_RUPPE_H
