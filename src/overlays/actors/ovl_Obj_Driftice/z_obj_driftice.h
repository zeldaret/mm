#ifndef _Z_OBJ_DRIFTICE_H_
#define _Z_OBJ_DRIFTICE_H_

#include <global.h>

struct ObjDriftice;

typedef struct ObjDriftice {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10C];
} ObjDriftice; // size = 0x250

extern const ActorInit Obj_Driftice_InitVars;

#endif
