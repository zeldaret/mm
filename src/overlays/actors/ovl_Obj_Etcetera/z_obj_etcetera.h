#ifndef Z_OBJ_ETCETERA_H
#define Z_OBJ_ETCETERA_H

#include "global.h"

#define DEKU_FLOWER_TYPE(thisx) (((thisx)->params & 0xFF80) >> 7)

typedef enum {
    /* 0 */ DEKU_FLOWER_TYPE_PINK,
    /* 1 */ DEKU_FLOWER_TYPE_PINK_SPAWNED_FROM_MAD_SCRUB,
    /* 2 */ DEKU_FLOWER_TYPE_GOLD,
    /* 3 */ DEKU_FLOWER_TYPE_GOLD_SPAWNED_FROM_MAD_SCRUB,
    /* 4 */ DEKU_FLOWER_TYPE_MAX,
} DekuFlowerType;

/**
 * For the petal/leaf directions, "back" is negative and "front" is positive
 * on the flower's local Z-axis. "Left" and "right" are relative to the front
 * and back.
 */
typedef enum {
    /*  0 */ DEKU_FLOWER_LIMB_NONE,
    /*  1 */ DEKU_FLOWER_LIMB_BASE,
    /*  2 */ DEKU_FLOWER_LIMB_CENTER,
    /*  3 */ DEKU_FLOWER_LIMB_BACK_PETAL_OR_LEAF,
    /*  4 */ DEKU_FLOWER_LIMB_FRONT_PETAL_OR_LEAF,
    /*  5 */ DEKU_FLOWER_LIMB_FRONT_RIGHT_PETAL,
    /*  6 */ DEKU_FLOWER_LIMB_BACK_RIGHT_PETAL,
    /*  7 */ DEKU_FLOWER_LIMB_RIGHT_PETAL_OR_LEAF,
    /*  8 */ DEKU_FLOWER_LIMB_FRONT_LEFT_PETAL,
    /*  9 */ DEKU_FLOWER_LIMB_LEFT_PETAL_OR_LEAF,
    /* 10 */ DEKU_FLOWER_LIMB_BACK_LEFT_PETAL,
    /* 11 */ DEKU_FLOWER_LIMB_MAX,
} DekuFlowerLimbs;

struct ObjEtcetera;

typedef void (*ObjEtceteraActionFunc)(struct ObjEtcetera*, GlobalContext*);

typedef struct ObjEtcetera {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ ColliderCylinder collider;
    /* 0x1EC */ Vec3s jointTable[DEKU_FLOWER_LIMB_MAX];
    /* 0x22E */ Vec3s morphTable[DEKU_FLOWER_LIMB_MAX];
    /* 0x270 */ f32 bounceOscillationScale;
    /* 0x274 */ s16 oscillationTimer;
    /* 0x276 */ u16 burrowFlag;
    /* 0x278 */ s8 objIndex;
    /* 0x27C */ Gfx* dList;
    /* 0x280 */ ObjEtceteraActionFunc actionFunc;
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif // Z_OBJ_ETCETERA_H
