#ifndef Z_OBJ_DEMO_H
#define Z_OBJ_DEMO_H

#include "global.h"

#define OBJDEMO_GET_FF(thisx) ((thisx)->params & 0xFF)
#define OBJDEMO_FF_FF 0xFF
struct ObjDemo;

typedef void (*ObjDemoActionFunc)(struct ObjDemo*, PlayState*);

typedef struct ObjDemo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjDemoActionFunc actionFunc;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ f32 xzRange;
    /* 0x150 */ f32 yRange;
} ObjDemo; // size = 0x154

#endif // Z_OBJ_DEMO_H
