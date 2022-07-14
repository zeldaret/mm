#ifndef Z_OBJ_UM_H
#define Z_OBJ_UM_H

#include "global.h"

struct ObjUm;

typedef void (*ObjUmActionFunc)(struct ObjUm*, PlayState*);

typedef struct ObjUm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ ObjUmActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x384];
} ObjUm; // size = 0x4E4

extern const ActorInit Obj_Um_InitVars;

#endif // Z_OBJ_UM_H
