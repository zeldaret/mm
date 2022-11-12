#ifndef Z_OBJ_WIND_H
#define Z_OBJ_WIND_H

#include "global.h"

struct ObjWind;

typedef struct ObjWind {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjWind; // size = 0x148

#endif // Z_OBJ_WIND_H
