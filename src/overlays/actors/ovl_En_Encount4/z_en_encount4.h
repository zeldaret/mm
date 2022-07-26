#ifndef Z_EN_ENCOUNT4_H
#define Z_EN_ENCOUNT4_H

#include "global.h"
#include "overlays/actors/ovl_En_Skb/z_en_skb.h"

struct EnEncount4;

typedef void (*EnEncount4ActionFunc)(struct EnEncount4*, PlayState*);

#define ENENCOUNT4_GET_SWITCH_FLAGS(thisx) ((thisx)->params & 0x7F)
#define ENENCOUNT4_GET_F000(thisx) (((thisx)->params >> 0xC) & 0xF)

typedef struct EnEncount4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnEncount4ActionFunc actionFunc;
    /* 0x0148 */ s16 unk148;
    /* 0x14A */ s16 switchFlags;
    /* 0x014C */ s16 unk14C;
    /* 0x014E */ s16 unk14E;
    /* 0x0150 */ s16 unk150;
    /* 0x0154 */ EnSkb* stalchild;
} EnEncount4; // size = 0x158

extern const ActorInit En_Encount4_InitVars;

#endif // Z_EN_ENCOUNT4_H
