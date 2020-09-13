#ifndef Z_OBJ_DRIFTICE_H
#define Z_OBJ_DRIFTICE_H

#include <global.h>

struct ObjDriftice;

typedef struct ObjDriftice {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10C];
} ObjDriftice; // size = 0x250

extern const ActorInit Obj_Driftice_InitVars;

#endif // Z_OBJ_DRIFTICE_H
