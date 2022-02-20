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
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3s rot;
    /* 0x12 */ UNK_TYPE1 unk_12[0x2];
} WoodenFlowerPetalPosRot; // size = 0x14

typedef struct BgNumaHana {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ FireObj fire;
    /* 0x1E8 */ ColliderCylinder torchCollider;
    /* 0x234 */ BgNumaHanaActionFunc actionFunc;
    /* 0x238 */ WoodenFlowerPetalPosRot innerPetalPosRot[6];
    /* 0x2B0 */ WoodenFlowerPetalPosRot outerPetalPosRot[6];
    /* 0x328 */ s16 petalZRotation;
    /* 0x32A */ s16 innerPetalZRotation;
    /* 0x32C */ s16 innerPetalZRotationalVelocity;
    /* 0x32E */ s16 settleZRotation;
    /* 0x330 */ s16 settleAngle;
    /* 0x334 */ f32 settleScale;
    /* 0x338 */ s16 outerPetalZRotation;
    /* 0x33A */ s16 outerPetalZRotationalVelocity;
    /* 0x33C */ s16 flowerRotationalVelocity;
    /* 0x33E */ s16 transitionTimer;
} BgNumaHana; // size = 0x340

extern const ActorInit Bg_Numa_Hana_InitVars;

#endif // Z_BG_NUMA_HANA_H
