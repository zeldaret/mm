#ifndef Z_BG_LAST_BWALL_H
#define Z_BG_LAST_BWALL_H

#include "global.h"
#include "objects/object_last_obj/object_last_obj.h"

struct BgLastBwall;

typedef void (*BgLastBwallActionFunc)(struct BgLastBwall*, PlayState*);

#define BGLASTBWALL_GET_SWITCHFLAGS(thisx) (((thisx)->params & 0x7F))
#define BGLASTBWALL_GET_F000(thisx) (((thisx)->params >> 0xC) & 0xF)

typedef struct {
    Vec3s* unk0;
    s16* unk4;
    s32 unk6;
} InitColliderStruct;

typedef struct {
    Gfx* dList;
    s32 unk4;
    CollisionHeader* colHeader;
} ModelInfo;

typedef struct BgLastBwall {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgLastBwallActionFunc actionFunc;
    /* 0x160 */ ColliderTris colliderTris;
    /* 0x180 */ ColliderTrisElement colliderTrisElement;
    /* 0x1DC */ u8 pad1DC[0x5C];
    /* 0x238 */ u8 unk238;
    /* 0x23A */ s16 nextCutscene;
} BgLastBwall; // size = 0x23C

extern const ActorInit Bg_Last_Bwall_InitVars;

#endif // Z_BG_LAST_BWALL_H
