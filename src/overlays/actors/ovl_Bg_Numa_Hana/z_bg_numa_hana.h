#ifndef Z_BG_NUMA_HANA_H
#define Z_BG_NUMA_HANA_H

#include "global.h"

#define BG_NUMA_HANA_GET_TYPE(thisx) ((thisx)->params & 1)
#define BG_NUMA_HANA_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0x7F)

typedef enum {
    /* 0 */ BG_NUMA_HANA_TYPE_NORMAL,
    /* 1 */ BG_NUMA_HANA_TYPE_OPEN_FLOWER_COLLISION,
} BgNumaHanaType;

struct BgNumaHana;

typedef void (*BgNumaHanaActionFunc)(struct BgNumaHana*, GlobalContext*);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3s unk_0C;
    /* 0x12 */ char unk_12[0x2];
} UnkBgNumaHanaStruct; // size = 0x14

typedef struct BgNumaHana {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ FireObj fire;
    /* 0x1E8 */ ColliderCylinder torchCollider;
    /* 0x234 */ BgNumaHanaActionFunc actionFunc;
    /* 0x238 */ UnkBgNumaHanaStruct unk_238[6];
    /* 0x2B0 */ UnkBgNumaHanaStruct unk_2B0[6];
    /* 0x328 */ s16 unk_328; // overall petal rotation?
    /* 0x32A */ s16 unk_32A; // gets added to contribute to overall petal rotation
    /* 0x32C */ s16 unk_32C;
    /* 0x32E */ s16 unk_32E; // gets added to contibute to overall petal rotation
    /* 0x330 */ s16 unk_330;
    /* 0x334 */ f32 unk_334;
    /* 0x338 */ s16 unk_338; // second part of petal rotation?
    /* 0x33A */ s16 unk_33A;
    /* 0x33C */ s16 unk_33C; // flower's rotational velocity
    /* 0x33E */ s16 unk_33E; // jostle timer?
} BgNumaHana; // size = 0x340

extern const ActorInit Bg_Numa_Hana_InitVars;

#endif // Z_BG_NUMA_HANA_H
