#ifndef Z_EN_TEST5_H
#define Z_EN_TEST5_H

#include "global.h"

struct EnTest5;

typedef void (*EnTest5ActionFunc)(struct EnTest5*, GlobalContext*);

typedef struct EnTest5 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Vec3f unk_144;
    /* 0x0150 */ f32 unk_150;
    /* 0x0154 */ f32 unk_154;
    /* 0x0158 */ EnTest5ActionFunc actionFunc;    
} EnTest5; // size = 0x15C

extern const ActorInit En_Test5_InitVars;

#endif // Z_EN_TEST5_H
