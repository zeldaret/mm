#ifndef Z_EN_SEKIHI_H
#define Z_EN_SEKIHI_H

#include "global.h"

#define ENSIKIHI_GET_F(thisx) ((thisx)->params & 0xF)

struct EnSekihi;

typedef void (*EnSekihiActionFunc)(struct EnSekihi*, PlayState*);

typedef struct EnSekihi {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ Gfx* opaDList;
    /* 0x160 */ Gfx* xluDList;
    /* 0x164 */ s8 objectIndex;
    /* 0x168 */ EnSekihiActionFunc actionFunc;
} EnSekihi; // size = 0x16C

extern const ActorInit En_Sekihi_InitVars;

#endif // Z_EN_SEKIHI_H
