#ifndef _Z_OBJ_PURIFY_H_
#define _Z_OBJ_PURIFY_H_

#include <global.h>

struct ObjPurify;

typedef struct ObjPurify {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} ObjPurify; // size = 0x170

extern const ActorInit Obj_Purify_InitVars;

#endif
