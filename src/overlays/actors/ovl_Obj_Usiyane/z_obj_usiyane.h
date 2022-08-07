#ifndef Z_OBJ_USIYANE_H
#define Z_OBJ_USIYANE_H

#include "global.h"

struct ObjUsiyane;

typedef void (*ObjUsiyaneActionFunc)(struct ObjUsiyane*, PlayState*);

typedef struct ObjUsiyane {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ ObjUsiyaneActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x5E8];
} ObjUsiyane; // size = 0x748

extern const ActorInit Obj_Usiyane_InitVars;

#endif // Z_OBJ_USIYANE_H
