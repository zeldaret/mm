#ifndef Z_OBJ_ICE_POLY_H
#define Z_OBJ_ICE_POLY_H

#include "global.h"

struct ObjIcePoly;

typedef void (*ObjIcePolyActionFunc)(struct ObjIcePoly*, GlobalContext*);

typedef struct ObjIcePoly {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjIcePolyActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x134];
} ObjIcePoly; // size = 0x27C

extern const ActorInit Obj_Ice_Poly_InitVars;

#endif // Z_OBJ_ICE_POLY_H
