#ifndef Z_OBJ_ROTLIFT_H
#define Z_OBJ_ROTLIFT_H

#include "global.h"

#include "overlays/actors/ovl_Obj_Etcetera/z_obj_etcetera.h"

#define OBJROTLIFT_GET_PARAMS(thisx) ((thisx)->params)
#define OBJROTLIFT_GET_1(thisx) ((thisx)->params & 1)
#define OBJROTLIFT_GET_4000(thisx) ((thisx)->params & 0x4000)

struct ObjRotlift;

typedef struct ObjRotlift {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjEtcetera* dekuFlowers[2];
} ObjRotlift; // size = 0x164

typedef struct AnimatedThing {
    /* 0x0 */ Gfx* dList;
    /* 0x4 */ AnimatedMaterial* animMat;
    /* 0x8 */ CollisionHeader* colHeader;
} AnimatedThing; // size = 0xC

extern const ActorInit Obj_Rotlift_InitVars;

#endif // Z_OBJ_ROTLIFT_H
