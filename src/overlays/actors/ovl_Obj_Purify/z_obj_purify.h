#ifndef Z_OBJ_PURIFY_H
#define Z_OBJ_PURIFY_H

#include "global.h"

struct ObjPurify;

typedef void (*ObjPurifyActionFunc)(struct ObjPurify*, PlayState*);

typedef struct ObjPurify {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ ObjPurifyActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x10];
} ObjPurify; // size = 0x170

extern const ActorInit Obj_Purify_InitVars;

#endif // Z_OBJ_PURIFY_H
