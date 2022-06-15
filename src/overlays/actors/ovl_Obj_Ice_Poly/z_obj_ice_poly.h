#ifndef Z_OBJ_ICE_POLY_H
#define Z_OBJ_ICE_POLY_H

#include "global.h"

struct ObjIcePoly;

typedef void (*ObjIcePolyActionFunc)(struct ObjIcePoly*, GlobalContext*);

#define OBJICEPOLY_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

#define OBJICEPOLY_FF_FF 0xFF

typedef struct ObjIcePoly {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjIcePolyActionFunc actionFunc;
    /* 0x0148 */ u8 unk_148;
    /* 0x0149 */ u8 unk_149;
    /* 0x014A */ s16 unk_14A;
    /* 0x014C */ ColliderCylinder colliders1[2];
    /* 0x01E4 */ ColliderCylinder colliders2[2];
} ObjIcePoly; // size = 0x27C

extern const ActorInit Obj_Ice_Poly_InitVars;

#endif // Z_OBJ_ICE_POLY_H
