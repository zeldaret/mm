#ifndef Z_OBJ_DEMO_H
#define Z_OBJ_DEMO_H

#include "global.h"

struct ObjDemo;

typedef void (*ObjDemoActionFunc)(struct ObjDemo*, GlobalContext*);

typedef struct ObjDemo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjDemoActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0xC];
} ObjDemo; // size = 0x154

extern const ActorInit Obj_Demo_InitVars;

#endif // Z_OBJ_DEMO_H
