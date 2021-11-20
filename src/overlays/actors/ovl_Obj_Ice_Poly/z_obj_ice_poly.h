#ifndef Z_OBJ_ICE_POLY_H
#define Z_OBJ_ICE_POLY_H

#include "global.h"

struct ObjIcePoly;

typedef void (*ObjIcePolyActionFunc)(struct ObjIcePoly*, GlobalContext*);

typedef struct ObjIcePoly {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjIcePolyActionFunc actionFunc;
    /* 0x0148 */ u8 unk_148;
    /* 0x0149 */ char unk_149[0x133];
} ObjIcePoly; // size = 0x27C

extern const ActorInit Obj_Ice_Poly_InitVars;

#endif // Z_OBJ_ICE_POLY_H
