#ifndef Z_OBJ_ROTLIFT_H
#define Z_OBJ_ROTLIFT_H

#include "global.h"

#include "overlays/actors/ovl_Obj_Etcetera/z_obj_etcetera.h"

#define OBJROTLIFT_GET_TYPE(thisx) ((thisx)->params & 1)
#define OBJROTLIFT_GET_4000(thisx) ((thisx)->params & 0x4000)

struct ObjRotlift;

typedef struct ObjRotlift {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjEtcetera* dekuFlowers[2];
} ObjRotlift; // size = 0x164

extern const ActorInit Obj_Rotlift_InitVars;

#endif // Z_OBJ_ROTLIFT_H
