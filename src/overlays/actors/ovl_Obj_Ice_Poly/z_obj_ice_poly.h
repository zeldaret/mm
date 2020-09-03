#ifndef _Z_OBJ_ICE_POLY_H_
#define _Z_OBJ_ICE_POLY_H_

#include <global.h>

struct ObjIcePoly;

typedef struct ObjIcePoly {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x138];
} ObjIcePoly; // size = 0x27C

extern const ActorInit Obj_Ice_Poly_InitVars;

#endif
