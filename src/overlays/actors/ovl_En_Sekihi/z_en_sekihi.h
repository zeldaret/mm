#ifndef Z_EN_SEKIHI_H
#define Z_EN_SEKIHI_H

#include "global.h"

struct EnSekihi;

typedef void (*EnSekihiActionFunc)(struct EnSekihi*, PlayState*);

typedef struct EnSekihi {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ s32 unk160;
    /* 0x164 */ s8 objectIndex;
    /* 0x165 */ UNK_TYPE1 pad165[3];
    /* 0x168 */ EnSekihiActionFunc actionFunc;
} EnSekihi; // size = 0x16C

extern const ActorInit En_Sekihi_InitVars;

#endif // Z_EN_SEKIHI_H
