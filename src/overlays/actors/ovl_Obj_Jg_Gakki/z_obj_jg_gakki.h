#ifndef Z_OBJ_JG_GAKKI_H
#define Z_OBJ_JG_GAKKI_H

#include "global.h"

struct ObjJgGakki;

/* typedef struct ObjJgGakki { */
/*     /1* 0x000 *1/ Actor actor; */
/*     /1* 0x144 *1/ char pad144[4]; */
/*     /1* 0x148 *1/ void** unk148;     /1* inferred *1/ */
/*     /1* 0x14C *1/ char pad14C[0x18]; /1* maybe part of unk148[7]? *1/ */
/*     /1* 0x164 *1/ Vec3s* unk164;     /1* inferred *1/ */
/*     /1* 0x168 *1/ char pad168[0x6C]; /1* maybe part of unk164[0x1C]? *1/ */
/* } ObjJgGakki;        &              /1* size = 0x1D4 *1/ */
/* typedef struct ObjJgGakki { */
/*     /1* 0x000 *1/ Actor actor; */
/*     /1* 0x144 *1/ char pad144[0x44]; */
/*     /1* 0x188 *1/ ColliderCylinder unk188; /1* inferred *1/ */
/* } ObjJgGakki; /1* size = 0x1D4 *1/ */

typedef struct ObjJgGakki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;               /* inferred */
    /* 0x188 */ ColliderCylinder colliderCylinder; /* maybe part of unk144[2]? */
} ObjJgGakki;                                      /* size = 0x1D4 */

extern const ActorInit Obj_Jg_Gakki_InitVars;

#endif // Z_OBJ_JG_GAKKI_H
