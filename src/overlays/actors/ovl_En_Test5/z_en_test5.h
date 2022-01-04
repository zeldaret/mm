#ifndef Z_EN_TEST5_H
#define Z_EN_TEST5_H

#include "global.h"

#define ENTEST5_IS_HOT_SPRING(thisx) ((thisx)->params != 0)

struct EnTest5; // SpringWaterModifier

typedef void (*EnTest5ActionFunc)(struct EnTest5*, GlobalContext*);

typedef struct EnTest5 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Vec3f minPos;
    /* 0x0150 */ f32 xLength;
    /* 0x0154 */ f32 zLength;
    /* 0x0158 */ EnTest5ActionFunc actionFunc;    
} EnTest5; // size = 0x15C

extern const ActorInit En_Test5_InitVars;

#endif // Z_EN_TEST5_H
