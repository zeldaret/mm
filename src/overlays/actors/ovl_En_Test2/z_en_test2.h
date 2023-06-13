#ifndef Z_EN_TEST2_H
#define Z_EN_TEST2_H

#include "global.h"

struct EnTest2;

typedef struct EnTest2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ AnimatedMaterial* animMat;
} EnTest2; // size = 0x148

typedef enum {
    /* 0xB */ EN_TEST2_PARAM_B = 0xB,
    /* 0xC */ EN_TEST2_PARAM_C
} EnTest2_Param;

#endif // Z_EN_TEST2_H
