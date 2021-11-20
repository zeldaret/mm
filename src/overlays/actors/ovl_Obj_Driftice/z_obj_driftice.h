#ifndef Z_OBJ_DRIFTICE_H
#define Z_OBJ_DRIFTICE_H

#include "global.h"

struct ObjDriftice;

typedef void (*ObjDrifticeActionFunc)(struct ObjDriftice*, GlobalContext*);

typedef struct ObjDriftice {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjDrifticeActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0xF0];
} ObjDriftice; // size = 0x250

extern const ActorInit Obj_Driftice_InitVars;

#endif // Z_OBJ_DRIFTICE_H
