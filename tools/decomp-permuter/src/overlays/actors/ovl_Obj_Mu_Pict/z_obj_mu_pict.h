#ifndef Z_OBJ_MU_PICT_H
#define Z_OBJ_MU_PICT_H

#include <global.h>

struct ObjMuPict;

typedef struct ObjMuPict {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC];
} ObjMuPict; // size = 0x150

extern const ActorInit Obj_Mu_Pict_InitVars;

#endif // Z_OBJ_MU_PICT_H
