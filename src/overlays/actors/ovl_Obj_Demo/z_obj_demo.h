#ifndef _Z_OBJ_DEMO_H_
#define _Z_OBJ_DEMO_H_

#include <global.h>

struct ObjDemo;

typedef struct ObjDemo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10];
} ObjDemo; // size = 0x154

extern const ActorInit Obj_Demo_InitVars;

#endif
