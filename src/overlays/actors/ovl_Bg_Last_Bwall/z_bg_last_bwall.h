#ifndef Z_BG_LAST_BWALL_H
#define Z_BG_LAST_BWALL_H

#include "global.h"
#include "objects/object_last_obj/object_last_obj.h"

struct BgLastBwall;

typedef void (*BgLastBwallActionFunc)(struct BgLastBwall*, PlayState*);

#define BGLASTBWALL_GET_SWITCHFLAGS(thisx) ((thisx)->params & 0x7F)
#define BGLASTBWALL_GET_TYPE(thisx) (((thisx)->params >> 0xC) & 0xF)

typedef enum {
    BGLASTBWALL_TYPE_0 = 0,
    BGLASTBWALL_TYPE_1 = 1,
} BgLastBwallType;

typedef struct BgLastBwall {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgLastBwallActionFunc actionFunc;
    /* 0x160 */ ColliderTris colliderTris;
    /* 0x180 */ ColliderTrisElement colliderTrisElement[2];
    /* 0x238 */ u8 type;
    /* 0x23A */ s16 cutscenes[1];
} BgLastBwall; // size = 0x23C

#endif // Z_BG_LAST_BWALL_H
