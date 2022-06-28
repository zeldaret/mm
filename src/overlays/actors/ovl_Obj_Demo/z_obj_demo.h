#ifndef Z_OBJ_DEMO_H
#define Z_OBJ_DEMO_H

#include "global.h"

struct ObjDemo;

typedef void (*ObjDemoActionFunc)(struct ObjDemo*, PlayState*);

typedef struct ObjDemo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjDemoActionFunc actionFunc;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ f32 unk_14C;
    /* 0x150 */ f32 unk_150;
} ObjDemo; // size = 0x154

extern const ActorInit Obj_Demo_InitVars;

#endif // Z_OBJ_DEMO_H
