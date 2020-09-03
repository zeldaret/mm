#ifndef Z_OBJ_DEMO_H
#define Z_OBJ_DEMO_H

#include <global.h>

struct ObjDemo;

typedef struct ObjDemo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10];
} ObjDemo; // size = 0x154

extern const ActorInit Obj_Demo_InitVars;

#endif // Z_OBJ_DEMO_H
