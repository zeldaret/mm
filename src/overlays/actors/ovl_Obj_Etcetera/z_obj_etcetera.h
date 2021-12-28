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

struct ObjEtcetera;

typedef void (*ObjEtceteraActionFunc)(struct ObjEtcetera*, GlobalContext*);

typedef struct ObjEtcetera {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ ColliderCylinder collider;
    /* 0x1EC */ Vec3s jointTable[11];
    /* 0x22E */ Vec3s morphTable[11];
    /* 0x270 */ f32 intenseOscillationScale;
    /* 0x274 */ s16 oscillationTimer;
    /* 0x276 */ u16 burrowFlag;
    /* 0x278 */ s8 objIndex;
    /* 0x27C */ Gfx* dList;
    /* 0x280 */ ObjEtceteraActionFunc actionFunc;
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif // Z_OBJ_ETCETERA_H
