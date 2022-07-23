#ifndef Z_OBJ_TARU_H
#define Z_OBJ_TARU_H

#include "global.h"

#define OBJ_TARU_P001F(thisx) ((thisx)->params & 0x1F)

struct ObjTaru;

typedef void (*ObjTaruActionFunc)(struct ObjTaru*, PlayState*);

typedef struct ObjTaru {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderCylinder collider;
    /* 0x1A8 */ ObjTaruActionFunc actionFunc;
    /* 0x1AC */ s8 unk1AC;
    /* 0x1AD */ s8 unk1AD;
    /* 0x1AE */ char pad1AE[2];
} ObjTaru; // size = 0x1B0

extern const ActorInit Obj_Taru_InitVars;

#endif // Z_OBJ_TARU_H
