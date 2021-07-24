#ifndef Z_OBJ_ENTOTU_H
#define Z_OBJ_ENTOTU_H

#include "global.h"

struct ObjEntotu;

typedef struct ObjEntotu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x84];
} ObjEntotu; // size = 0x1C8

extern const ActorInit Obj_Entotu_InitVars;

#endif // Z_OBJ_ENTOTU_H
