#ifndef Z_OBJ_LIGHTBLOCK_H
#define Z_OBJ_LIGHTBLOCK_H

#include "global.h"

#define LIGHTBLOCK_TYPE(thisx) ((thisx)->params & 1)
#define LIGHTBLOCK_DESTROYED(thisx) (((thisx)->params >> 8) & 0x7F)

struct ObjLightblock;

typedef void (*ObjLightblockActionFunc)(struct ObjLightblock*, GlobalContext*);

typedef struct ObjLightblock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ ObjLightblockActionFunc actionFunc;
    /* 0x01AC */ s8 timer;
    /* 0x01AD */ u8 opacity;
    /* 0x01AE */ s8 collisionCounter;
} ObjLightblock; // size = 0x1B0

extern const ActorInit Obj_Lightblock_InitVars;

#endif // Z_OBJ_LIGHTBLOCK_H
