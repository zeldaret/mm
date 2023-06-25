#ifndef Z_OBJ_WIND_H
#define Z_OBJ_WIND_H

#include "global.h"

struct ObjWind;

typedef struct ObjWind {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 isUnderWater;
} ObjWind; // size = 0x148

#endif // Z_OBJ_WIND_H
